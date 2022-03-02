//---------------------------------------------------------------------------

#include <vcl.h>
#include <jpeg.hpp>
#include <pngimage.hpp>
#include <tchar.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <Commctrl.h>

#pragma hdrstop

#include "main.h"
#include "ScriptForm.h"
#include "SettingsForm.h"
#include "FOMODClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define TEG_NONE        0x00
#define TEG_OPEN        0x01
#define TEG_CLOSE       0x02
#define TEG_WAITCLOSE   0x04
#define TEG_INNERTEXT   0x08
#define TEG_READY       0x10

#define AMB_UNDEFINED      -1

#define AMB_VISIBILITY      0
#define AMB_DIRECTTYPE      1
#define AMB_PATTERN         2

#define AMB_REQINSTFILES    3
#define AMB_INSTSTEPS       4
#define AMB_CONDINSTFILES   5


const wchar_t BOM = 0xFEFF;

TMainForm *MainForm;

CFOMOD FOMOD;
UnicodeString RootDirectory;
UnicodeString AppPath;


TSettings Settings;
vector <TLanguagePair> LanguageTable;

int StepCount       = 0;
int CurrentStepIndx = 0;

//---------------------------------------------------------------------------

bool dirExists(UnicodeString dirName_in)
{
  DWORD ftyp = GetFileAttributes(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}
UnicodeString GetFileVersionOfApplication(LPTSTR lpszFilePath)
{
   DWORD dwDummy;
   DWORD dwFVISize = GetFileVersionInfoSize( lpszFilePath , &dwDummy );

   LPBYTE lpVersionInfo = new BYTE[dwFVISize];

   GetFileVersionInfo( lpszFilePath , 0 , dwFVISize , lpVersionInfo );

   UINT uLen;
   VS_FIXEDFILEINFO *lpFfi;

   VerQueryValue( lpVersionInfo , _T("\\") , (LPVOID *)&lpFfi , &uLen );

   DWORD dwFileVersionMS = lpFfi->dwFileVersionMS;
   DWORD dwFileVersionLS = lpFfi->dwFileVersionLS;

   delete [] lpVersionInfo;

//   printf( "Higher: %x\n" , dwFileVersionMS );
//
//   printf( "Lower: %x\n" , dwFileVersionLS );

   DWORD dwLeftMost     = HIWORD(dwFileVersionMS);
   DWORD dwSecondLeft   = LOWORD(dwFileVersionMS);
   DWORD dwSecondRight  = HIWORD(dwFileVersionLS);
   DWORD dwRightMost    = LOWORD(dwFileVersionLS);

   _TCHAR str[128];

   _stprintf(str, _T("%d.%d.%d.%d") , dwLeftMost, dwSecondLeft,
      dwSecondRight, dwRightMost);

   return UnicodeString(str);
}
//---------------------------------------------------------------------------

_TCHAR *ParseXMLString(_TCHAR *xml_string, UnicodeString &tegname, UnicodeString &teginner, vector < pair<UnicodeString, UnicodeString> > &tegprops, int &state)
{
    _TCHAR w_letter;
    unsigned int str_len;
    UnicodeString ustr;
    int i;
    int exit_cicle = 0;

    str_len = _tcslen(xml_string);
    for(i = 0; i < str_len; i++)
    {
        w_letter = xml_string[i];
        switch(state)
        {
            case TEG_NONE:
                if(w_letter == '<')
                {
                    state = TEG_OPEN;
                    tegprops.clear();
                    tegname = "";
                    teginner = "";
                    ustr = "";
                }
                break;
            case TEG_OPEN:
                if( ustr != "" && tegname != "" && (w_letter == '"' || w_letter == '=' || w_letter == '>') )
                {
                    if(tegprops.size() > 0)
                    {
                        if( (tegprops.end()-1)->second == "" )
                            (tegprops.end()-1)->second = ustr;
                        else
                        {
                            pair <UnicodeString, UnicodeString> new_pair;
                            new_pair.first = ustr;
                            new_pair.second = "";
                            tegprops.push_back(new_pair);
                        }
                    }
                    else
                    {
                        pair <UnicodeString, UnicodeString> new_pair;
                        new_pair.first = ustr;
                        new_pair.second = "";
                        tegprops.push_back(new_pair);
                    }
                    ustr = "";
                }
                if( ustr != "" && tegname == "" && (w_letter == ' ' || w_letter == '\t' || w_letter == '>') )
                {
                    tegname = UnicodeString(ustr);
                    ustr = "";
                }

                if(w_letter == '/' || w_letter == '?')
                    state = TEG_CLOSE;
                else if(w_letter == '>')
                {
                    state = TEG_INNERTEXT;
                    teginner = "";
                    ustr = "";
                }
                else if(w_letter != '=' && w_letter != '"')
                    ustr = ustr + w_letter;

                break;
            case TEG_CLOSE:
                if(w_letter == '>')
                {
                    state = TEG_READY;
                    break;
                }
                else if(w_letter == '\t' || w_letter != ' ')
                    ustr = ustr + w_letter;
                break;
            case TEG_INNERTEXT:
                if(w_letter != '<')
                {
                    if( !(ustr == "" && (w_letter == ' ' || w_letter == '\t' || w_letter == '\r' || w_letter == '\n')) )
                        ustr = ustr + w_letter;
                }
                else
                {
                    teginner = ustr;
                    state = TEG_READY;
                }
                break;
        }
        if( state == TEG_READY )
            break;
    }
    if(state == TEG_INNERTEXT)
        teginner = ustr;

    return (&xml_string[i]);
}

void RunBatFile(_TCHAR *filename, CFOMOD &fomod)
{
    _TCHAR
        t_bat_path[256],
        str[512],
        buf[16],
        cmd[512];
    unsigned int len, i, j;

    FILE *fp = _tfopen(filename, _T("r"));
    if(fp)
    {
        _tcscpy(t_bat_path, filename);
        _tcscat(t_bat_path, _T(".bat"));
        FILE *fpbat = _tfopen(t_bat_path, _T("w"));

        while(_fgetts(str, 512, fp))
        {
            cmd[0] = '\0';
            len = _tcslen(str);
            for(i = 0; i < len; i++)
            {
                if(str[i] == '$')
                {
                    j = i+1;
                    while(j < len && str[j] != '$') j++;
                    memset(buf, 0, 16*sizeof(_TCHAR));
                    if(j-i < 16)
                        _tcsncpy(buf, &str[i], j-i+1);
                    if(_tcscmp(buf, _T("$MODNAME$")) == 0)
                    {
                        _tcsncat(cmd, fomod.Name.c_str(), fomod.Name.Length());
                        i = j;
                    }
                    if(_tcscmp(buf, _T("$MODAUTHOR$")) == 0)
                    {
                        _tcsncat(cmd, fomod.AuthorName.c_str(), fomod.AuthorName.Length());
                        i = j;
                    }
                    if(_tcscmp(buf, _T("$MODVERSION$")) == 0)
                    {
                        _tcsncat(cmd, fomod.Version.c_str(), fomod.Version.Length());
                        i = j;
                    }
                    if(_tcscmp(buf, _T("$MODROOT$")) == 0)
                    {
                        _tcsncat(cmd, RootDirectory.c_str(), RootDirectory.Length());
                        i = j;
                    }
                    if(_tcscmp(buf, _T("$DATE$")) == 0)
                    {
                        time_t t = time(NULL);
                        struct tm *now = localtime(&t);
                        _stprintf(buf, _T("%02d-%02d-%04d"), now->tm_mday, now->tm_mon+1, now->tm_year+1900);
                        _tcsncat(cmd, buf, _tcslen(buf));
                        i = j;
                    }
                    if(_tcscmp(buf, _T("$TIME$")) == 0)
                    {
                        time_t t = time(NULL);
                        struct tm *now = localtime(&t);
                        _stprintf(buf, _T("%02d-%02d-%02d"), now->tm_hour, now->tm_min, now->tm_sec);
                        _tcsncat(cmd, buf, _tcslen(buf));
                        i = j;
                    }
                    if(_tcscmp(buf, _T("$RANDOM$")) == 0)
                    {
                        srand(time(NULL));
                        _stprintf(buf, _T("%d"), rand()%32767);
                        _tcsncat(cmd, buf, _tcslen(buf));
                        i = j;
                    }
                }
                else
                    _tcsncat(cmd, &str[i], 1);
            }
            if(fpbat)
            {
                _ftprintf(fpbat, _T("%s\n"), cmd);
            }
        }
        fclose(fp);
        fclose(fpbat);

        _tcscpy( cmd, _T("cmd /c \"") );
        _tcscat( cmd, t_bat_path);
        _tcscat( cmd, _T("\""));
        _tsystem(cmd);
        _tremove( t_bat_path );
    }
}

UnicodeString getProperDestinationPath(UnicodeString path)
{
    UnicodeString u_temp;
    _TCHAR t_temp[256];
    unsigned int t_len;


    if(    !(path.SubString(path.Length()-3, 4).LowerCase().Compare(UnicodeString(".esp")))
        || !(path.SubString(path.Length()-3, 4).LowerCase().Compare(UnicodeString(".esm")))  )
    {
        _tcscpy(t_temp, path.c_str());
        for(int i = _tcslen(t_temp); i > 0; i--)
            if( t_temp[i] == _T('\\') )
            {
                path = &t_temp[i+1];
                break;
            }
    }
    else
    {
        _tcscpy(t_temp, path.c_str());
        t_len = _tcslen(t_temp);
        for(int i = 0, start = 0; i < t_len; i++)
            if( t_temp[i] == _T('\\') )
            {
                t_temp[i] = _T('\0');
                u_temp = &t_temp[start];
                if(    !(u_temp.UpperCase().Compare(UnicodeString("STRINGS")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("TEXTURES")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("MUSIC")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("SOUND")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("INTERFACE")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("MESHES")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("PROGRAMS")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("MATERIALS")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("LODSETTINGS")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("VIS")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("MISC")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("SCRIPTS")))
                    || !(u_temp.UpperCase().Compare(UnicodeString("SHADERSFX")))    )
                    {
                        t_temp[i] = _T('\\');
                        path = &t_temp[start];
                        break;
                    }
                    else
                        start = i+1;
            }
    }
    return path;
}

bool LoadFOMODFromXML(_TCHAR *filename, CFOMOD &fomod)
{
    bool result = false;

    unsigned int fsize;
    _TCHAR
        *t_str, *t_str_p;
    UnicodeString
        teginner;
    UnicodeString
        tegname;
    vector < pair<UnicodeString, UnicodeString> > tegprops;

    int state = TEG_NONE;

    FILE *fpModuleConfigxml = _tfopen(filename, _T("rb"));
    if(fpModuleConfigxml)
    {
        fseek(fpModuleConfigxml, 0, SEEK_END);
        fsize = ftell (fpModuleConfigxml);
        rewind(fpModuleConfigxml);
        t_str = new _TCHAR [(fsize/sizeof(_TCHAR))+1];
        fread(t_str, sizeof(_TCHAR), fsize/sizeof(_TCHAR), fpModuleConfigxml);
        t_str[(fsize/sizeof(_TCHAR))] = _T('\0');


        int ambiguity_section = AMB_UNDEFINED;
        int ambiguity_depend = AMB_UNDEFINED;
        int ambiguity_type = AMB_UNDEFINED;
        int curr_step = -1;
        int curr_group = -1;
        int curr_plugin = -1;
        int curr_pattern = -1;
        int curr_condinstfile = -1;
        t_str_p = ParseXMLString(t_str, tegname, teginner, tegprops, state);
        while( *t_str_p != _T('\0') )
        {
            if(state == TEG_READY)
            {
                UnicodeString tegname_l = tegname.LowerCase();
                if(tegname_l == "installstep")
                {
                    CStep new_step;
                    if(tegprops.size() > 0)
                        new_step.Name = tegprops[0].second;
                    else
                        new_step.Name = "Step" + IntToStr(curr_step+1);
                    fomod.Steps.push_back(new_step);
                    curr_step = fomod.Steps.size()-1;
                }
                if(tegname_l == "flagdependency")
                {
                    if(tegprops.size() > 1)
                    {
                        CDependency new_dependency;
                        if(curr_step > -1)
                        {
                            new_dependency.Type = _T("flag");
                            new_dependency.Name = tegprops[0].second;
                            new_dependency.Value = tegprops[1].second;

                            if(ambiguity_depend == AMB_VISIBILITY && ambiguity_section == AMB_INSTSTEPS)
                                fomod.Steps[curr_step].VisibilityDependencies.push_back(new_dependency);
                            else if(ambiguity_depend == AMB_PATTERN && ambiguity_section == AMB_INSTSTEPS)
                                fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns[curr_pattern].Dependencies.push_back(new_dependency);

                        }
                        if(ambiguity_section == AMB_CONDINSTFILES)
                            fomod.ConditionalFiles[curr_condinstfile].Dependencies.push_back(new_dependency);
                    }
                }
                if(tegname_l == "filedependency")
                {
                    if(tegprops.size() > 1)
                    {
                        CDependency new_dependency;
                        if(curr_step > -1)
                        {
                            new_dependency.Type = _T("file");
                            new_dependency.Name = tegprops[0].second;
                            new_dependency.Value = tegprops[1].second;

                            if(ambiguity_depend == AMB_VISIBILITY && ambiguity_section == AMB_INSTSTEPS)
                                fomod.Steps[curr_step].VisibilityDependencies.push_back(new_dependency);
                            else if(ambiguity_depend == AMB_PATTERN && ambiguity_section == AMB_INSTSTEPS)
                                fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns[curr_pattern].Dependencies.push_back(new_dependency);
                        }
                        if(ambiguity_section == AMB_CONDINSTFILES)
                            fomod.ConditionalFiles[curr_condinstfile].Dependencies.push_back(new_dependency);
                    }
                }
                if(tegname_l == "type")
                {
                    if(curr_step > -1)
                    {
                        if(tegprops.size() > 0)
                        {
                            if(ambiguity_type == AMB_DIRECTTYPE)
                                fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DefaultType = tegprops[0].second;
                            else if(ambiguity_type == AMB_PATTERN)
                                fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns[curr_pattern].Type = tegprops[0].second;
                        }
                    }
                }
                if(tegname_l == "dependencies")
                {
                    if(tegprops.size() > 0)
                    {
                        if(curr_step > -1)
                        {
                            if(ambiguity_section == AMB_INSTSTEPS)
                                fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns[curr_pattern].Operator = tegprops[0].second;
                        }
                        if(ambiguity_section == AMB_CONDINSTFILES)
                            fomod.ConditionalFiles[curr_condinstfile].Operator = tegprops[0].second;

                    }
                }
                if(tegname_l == "group")
                {
                    if(curr_step > -1)
                    {
                        CPluginGroup new_group;
                        if(tegprops.size() > 1)
                        {
                            new_group.Name = tegprops[0].second;
                            new_group.Type = tegprops[1].second;
                            fomod.Steps[curr_step].PluginGroups.push_back(new_group);
                            curr_group = fomod.Steps[curr_step].PluginGroups.size()-1;
                        }
                    }
                }
                if(tegname_l == "plugin")
                {
                    if(curr_step > -1 && curr_group > -1)
                    {
                        CPlugin new_plugin;
                        if(tegprops.size() > 0)
                        {
                            new_plugin.Name = tegprops[0].second;
                            fomod.Steps[curr_step].PluginGroups[curr_group].Plugins.push_back(new_plugin);
                            curr_plugin = fomod.Steps[curr_step].PluginGroups[curr_group].Plugins.size()-1;
                        }
                    }
                }
                if(tegname_l == "description")
                {
                    if(curr_step > -1 && curr_group > -1 && curr_plugin > -1 && teginner != _T("\n"))
                        if(fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Description == "")
                            fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Description = teginner;
                        else
                            fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Description =
                                fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Description + teginner;
                }
                if(tegname_l == "image")
                {
                    if(curr_step > -1 && curr_group > -1 && curr_plugin > -1)
                        if(tegprops.size() > 0)
                            fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].ImagePath = tegprops[0].second;
                }
                if(tegname_l == "flag")
                {
                    if(curr_step > -1 && curr_group > -1 && curr_plugin > -1)
                    {
                        CCondition new_var;
                        if(tegprops.size() > 0)
                            new_var.Name = tegprops[0].second;
                        new_var.Value = teginner;
                        fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].ConditionSet.push_back(new_var);
                    }
                }
                if(tegname_l == "file")
                {
                    CFile new_file;
                    new_file.Type = "file";
                    if(tegprops.size() > 1)
                    {
                        new_file.SrcPath = tegprops[0].second;
                        new_file.DstPath = tegprops[1].second;
                    }
                    if(ambiguity_section == AMB_REQINSTFILES)
                        fomod.RequiredFiles.push_back(new_file);
                    else if(ambiguity_section == AMB_INSTSTEPS)
                        fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Files.push_back(new_file);
                    else if(ambiguity_section == AMB_CONDINSTFILES)
                        fomod.ConditionalFiles[curr_condinstfile].Files.push_back(new_file);
                }
                if(tegname_l == "folder")
                {
                    CFile new_file;
                    new_file.Type = "folder";
                    if(tegprops.size() > 1)
                    {
                        new_file.SrcPath = tegprops[0].second;
                        new_file.DstPath = tegprops[1].second;
                    }
                    if(ambiguity_section == AMB_REQINSTFILES)
                        fomod.RequiredFiles.push_back(new_file);
                    else if(ambiguity_section == AMB_INSTSTEPS)
                        fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Files.push_back(new_file);
                    else if(ambiguity_section == AMB_CONDINSTFILES)
                        fomod.ConditionalFiles[curr_condinstfile].Files.push_back(new_file);
                }
                if(tegname_l == "requiredinstallfiles")
                {
                    ambiguity_section = AMB_REQINSTFILES;
                }
                if(tegname_l == "installsteps")
                {
                    ambiguity_section = AMB_INSTSTEPS;
                }
                if(tegname_l == "conditionalfileinstalls")
                {
                    ambiguity_section = AMB_CONDINSTFILES;
                    ambiguity_depend = AMB_CONDINSTFILES;
                }
                if(tegname_l == "visible")
                {
                    ambiguity_depend = AMB_VISIBILITY;
                }
                if(tegname_l == "typedescriptor")
                {
                    ambiguity_type = AMB_DIRECTTYPE;
                }
                if(tegname_l == "pattern")
                {
                    if(ambiguity_section == AMB_INSTSTEPS)
                    {
                        CDependencyPattern tdp;
                        fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns.push_back(tdp);
                        curr_pattern = fomod.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns.size()-1;
                    }
                    else if(ambiguity_section == AMB_CONDINSTFILES)
                    {
                        CConditionalFile new_condinstfile;
                        fomod.ConditionalFiles.push_back(new_condinstfile);
                        curr_condinstfile = fomod.ConditionalFiles.size() - 1;
                    }

                    ambiguity_type = AMB_PATTERN;
                    ambiguity_depend = AMB_PATTERN;
                }
            }
            state = TEG_NONE;
            t_str_p = ParseXMLString(t_str_p, tegname, teginner, tegprops, state);
        }
        result = true;
        fclose(fpModuleConfigxml);
        delete [] t_str;
    }

    return result;
}

bool LoadFOMODInfoFromXML(_TCHAR *filename, CFOMOD &fomod)
{
    bool result = false;

    unsigned int fsize;
    _TCHAR
        *t_str, *t_str_p;
    UnicodeString
        teginner;
    UnicodeString
        tegname;
    vector < pair<UnicodeString, UnicodeString> > tegprops;

    int state = TEG_NONE;


    FILE *fpinfoxml = _tfopen(filename, _T("rb"));
    if(fpinfoxml)
    {
        fseek(fpinfoxml, 0, SEEK_END);
        fsize = ftell (fpinfoxml);
        rewind(fpinfoxml);
        t_str = new _TCHAR [(fsize/sizeof(_TCHAR))+1];
        fread(t_str, sizeof(_TCHAR), fsize/sizeof(_TCHAR), fpinfoxml);
        t_str[(fsize/sizeof(_TCHAR))] = _T('\0');

        t_str_p = ParseXMLString(t_str, tegname, teginner, tegprops, state);
        while( *t_str_p != _T('\0') )
        {
            if( state == TEG_READY )
            {
                UnicodeString tegname_l = tegname.LowerCase();
                if(tegname_l == "name")
                    fomod.Name = teginner;
                if(tegname_l == "author")
                    fomod.AuthorName = teginner;
                if(tegname_l == "version")
                    fomod.Version = teginner;
                if(tegname_l == "website")
                    fomod.URL = teginner;
                if(tegname_l == "description")
                    fomod.Description = teginner;
                if(tegname_l == "element")
                    fomod.ModCategory = teginner;
                tegname = "";
            }
            state = TEG_NONE;
            t_str_p = ParseXMLString(t_str_p, tegname, teginner, tegprops, state);
        }
        fclose(fpinfoxml);
        delete [] t_str;
        result = true;
    }

    return result;
}

void SaveConfig(TSettings Settings)
{
    FILE *fp = _tfopen( (AppPath+"\\config.ini").c_str(), _T("w"));
    if(fp)
    {
        fprintf(fp, "[General]\n");
        fprintf(fp, "bHideOpenFolder = %d\n", (int)Settings.hideOpenFolder);
        fprintf(fp, "bHideOpenFile = %d\n", (int)Settings.hideOpenFile);
        fprintf(fp, "iInterfaceTextSize = %d\n", Settings.interfaceTextSize);
        fprintf(fp, "iSplashScreenSec = %d\n", Settings.splashScreenSeconds);
        fprintf(fp, "sLanguage = %s\n", Settings.langFile.c_str());

        fprintf(fp, "\n[RecentFiles]\n");
        fprintf(fp, "iMaxRecentFiles = %d\n", Settings.MaxRecentFiles);
        fprintf(fp, "iRecentFilesNum = %d\n", Settings.RecentFiles.size());
        fprintf(fp, "sRecentFiles = \n");
        for(int i = 0; i < Settings.RecentFiles.size(); i++)
            fprintf(fp, "%s\n", Settings.RecentFiles[i].c_str());

        fclose(fp);
    }
}

bool LoadSettings(TSettings &settings)
{
    bool result = false;
    FILE *fp = fopen("config.ini", "r");
    if(fp)
    {
        char cstr[256];
        int slen, i;
        AnsiString token1;

        while(!feof(fp))
        {
            fgets(cstr, 256, fp);
            slen = strlen(cstr);
            if(cstr[slen-1] == '\n')
                cstr[slen-1] = '\0';
            token1 = "";
            for(i = 0; i < slen; i++)
                if(cstr[i] != ' ' && cstr[i] != '=')
                    token1 = token1 + cstr[i];
                else
                    break;

            if(token1.LowerCase() == "slanguage")
            {
                while(cstr[i] == ' ' || cstr[i] == '=')
                    i++;
                settings.langFile = &cstr[i];
            }
            else if(token1.LowerCase() == "bhideopenfolder")
            {
                while(cstr[i] == ' ' || cstr[i] == '=')
                    i++;
                settings.hideOpenFolder = bool(atoi(&cstr[i]));
            }
            else if(token1.LowerCase() == "bhideopenfile")
            {
                while(cstr[i] == ' ' || cstr[i] == '=')
                    i++;
                settings.hideOpenFile = bool(atoi(&cstr[i]));
            }
            else if(token1.LowerCase() == "iinterfacetextsize")
            {
                while(cstr[i] == ' ' || cstr[i] == '=')
                    i++;
                settings.interfaceTextSize = atoi(&cstr[i]);
            }
            else if(token1.LowerCase() == "isplashscreensec")
            {
                while(cstr[i] == ' ' || cstr[i] == '=')
                    i++;
                settings.splashScreenSeconds = atoi(&cstr[i]);
            }
            else if(token1.LowerCase() == "imaxrecentfiles")
            {
                while(cstr[i] == ' ' || cstr[i] == '=')
                    i++;
                settings.MaxRecentFiles = atoi(&cstr[i]);
            }
            else if(token1.LowerCase() == "irecentfilesnum")
            {
                while(cstr[i] == ' ' || cstr[i] == '=')
                    i++;
                settings.RecentFilesNum = atoi(&cstr[i]);
            }
            else if(token1.LowerCase() == "srecentfiles")
            {
                settings.RecentFiles.clear();
                for(int j = 0; j < settings.RecentFilesNum && !feof(fp); j++)
                {
                    fgets(cstr, 256, fp);
                    if(cstr[strlen(cstr)-1] == '\n')
                        cstr[strlen(cstr)-1] = '\0';
                    token1 = cstr;
                    settings.RecentFiles.push_back(token1);
                }

            }
        }

        fclose(fp);
        result = true;
    }

    return result;
}

void LoadLangugeFile(UnicodeString filename, vector <TLanguagePair> &table)
{

    unsigned int
        fsize,
        tnum;
    int state;
    _TCHAR
        *t_str;
    TLanguagePair new_pair;

    FILE *fp = _tfopen(filename.c_str(), _T("rb"));
    if(fp)
    {
        fseek(fp, 0, SEEK_END);
        fsize = ftell (fp);
        rewind(fp);
        tnum = fsize/sizeof(_TCHAR);
        t_str = new _TCHAR [tnum+1];
        fread(t_str, sizeof(_TCHAR), tnum, fp);
        t_str[tnum] = _T('\0');

        new_pair.Name = new_pair.Text = "";
        state = 0;
        table.clear();
        for(unsigned int i = 1; i < tnum; i++)
        {
            if(state == 0)
            {
                if(t_str[i] != _T(' ') && t_str[i] != _T('='))
                {
                    if(t_str[i] != _T('\r') && t_str[i] != _T('\n'))
                        new_pair.Name = new_pair.Name + t_str[i];
                }
                else
                {
                    state = 1;
                    while( (t_str[i] == _T(' ') || t_str[i] == _T('=')) && i < tnum )
                        i++;
                }
            }
            else if(state == 1)
            {
                if(t_str[i] != _T('\r') && t_str[i] != _T('\n') && t_str[i] != _T('\0'))
                {
                    if(t_str[i] != _T('\"'))
                        new_pair.Text = new_pair.Text + t_str[i];
                }
                else
                {
                    table.push_back(new_pair);
                    new_pair.Name = new_pair.Text = "";
                    state = 0;
                }
            }
        }
        if(new_pair.Name != "" && new_pair.Text != "")
            table.push_back(new_pair);


        fclose(fp);
    }
}

UnicodeString GetLangText(UnicodeString key, vector <TLanguagePair> &table)
{
    UnicodeString result = key;

    vector <TLanguagePair> :: iterator it;
    for(it = table.begin(); it != table.end(); it++)
        if(it->Name.UpperCase() == key.UpperCase())
        {
            result = it->Text;
            break;
        }

    return result;
}

void ApplyLanguage(TWinControl *container, vector <TLanguagePair> &table)
{
    for(int i = 0; i < container->ControlCount; i++)
    {
        TControl *control = container->Controls[i];

        TLabel *label = dynamic_cast<TLabel *>(control);
        if(label)
            if(label->Caption != "")
                label->Caption = GetLangText(label->Name, table);

        TButton *button = dynamic_cast<TButton *>(control);
        if(button)
            button->Caption = GetLangText(button->Name, table);

        TLabeledEdit *labelededit = dynamic_cast<TLabeledEdit *>(control);
        if(labelededit)
            labelededit->EditLabel->Caption = GetLangText(labelededit->Name, table);

        TCheckBox *checkbox = dynamic_cast<TCheckBox *>(control);
        if(checkbox)
            checkbox->Caption = GetLangText(checkbox->Name, table);

        TGroupBox *groupbox = dynamic_cast<TGroupBox *>(control);
        if(groupbox)
        {
            groupbox->Caption = GetLangText(groupbox->Name, table);
            ApplyLanguage(groupbox, table);
        }

        TTabSheet *sheet = dynamic_cast<TTabSheet *>(control);
        if(sheet)
        {
            sheet->Caption = GetLangText(sheet->Name, table);
            ApplyLanguage(sheet, table);
        }

        TPanel *panel = dynamic_cast<TPanel *>(control);
        if(panel)
            ApplyLanguage(panel, table);

        TPageControl *pagecontrol = dynamic_cast<TPageControl *>(control);
        if(pagecontrol)
        {
            if(    pagecontrol->Name != "StepsTabControl"
                && pagecontrol->Name != "pdPatternsPageControl"
                && pagecontrol->Name != "ConiditionalFilesPageControl")
                ApplyLanguage(pagecontrol, table);
        }

        TScrollBox *scrollbox = dynamic_cast<TScrollBox *>(control);
        if(scrollbox)
            ApplyLanguage(scrollbox, table);

    }
}

void ManageRecentFiles(UnicodeString path)
{
    deque<AnsiString>::iterator it;

    if(path != NULL)
    {
        for(it = Settings.RecentFiles.begin(); it != Settings.RecentFiles.end(); it++)
            if(path == *it)
            {
                Settings.RecentFiles.erase(it);
                break;
            }
        while(Settings.RecentFiles.size() >= Settings.MaxRecentFiles)
            Settings.RecentFiles.pop_back();
        Settings.RecentFiles.push_front(path);
        SaveConfig(Settings);
    }
    while(MainForm->RecentMenu->Count > 1)
        if(MainForm->RecentMenu->Items[0]->Name != "RecentFileTemplate")
            MainForm->RecentMenu->Remove(MainForm->RecentMenu->Items[0]);
    for(int i = 0; i < Settings.RecentFiles.size(); i++)
    {
        TMenuItem *new_recent = new TMenuItem(MainForm->RecentMenu);
        new_recent->Caption = Settings.RecentFiles[i];
        new_recent->OnClick = MainForm->RecentFileTemplate->OnClick;
        MainForm->RecentMenu->Insert(i, new_recent);
    }
}
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    PageControl->ActivePage = ModInfoTabSheet;
    Caption = "FOMOD Creation Tool " + GetFileVersionOfApplication(Application->ExeName.c_str());

    _TCHAR temp[256];
    _tcscpy(temp, Application->ExeName.c_str());
    for(int i = _tcslen(temp); i > 0; i--)
        if(temp[i] == _T('\\'))
        {
            temp[i] = _T('\0');
            break;
        }
    AppPath = &temp[0];
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenRootDirButtonClick(TObject *Sender)
{
    if(OpenFolderDialog->Execute())
    {
        if(dirExists(OpenFolderDialog->FileName + "\\fomod"))
        {
            RootDirEdit->Text = OpenFolderDialog->FileName;
        }
        else
        {
            if(MessageBox(NULL, _T("There is no 'fomod' catalog in specified directory. Create one?"), _T("FOMOD Creation Tool"),  MB_YESNO) == IDYES)
            {
                CreateDirectory((OpenFolderDialog->FileName + "\\fomod").c_str(), NULL);
                RootDirEdit->Text = OpenFolderDialog->FileName;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RootDirEditChange(TObject *Sender)
{
    RootDirectory = RootDirEdit->Text;
    if(RootDirectory != "")
        if(dirExists(OpenFolderDialog->FileName + "\\fomod"))
            ProceedButton->Enabled = true;
        else
            ProceedButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ModNameEditChange(TObject *Sender)
{
    FOMOD.Name = ModNameEdit->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ModAuthorEditChange(TObject *Sender)
{
    FOMOD.AuthorName = ModAuthorEdit->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ModVersionEditChange(TObject *Sender)
{
    FOMOD.Version = ModVersionEdit->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ModCategoryEditChange(TObject *Sender)
{
    FOMOD.ModCategory = ModCategoryComboBox->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ModURLEditChange(TObject *Sender)
{
    FOMOD.URL = ModURLEdit->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ModDesccriptionMemoChange(TObject *Sender)
{
    FOMOD.Description = ModDesccriptionMemo->Lines->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProceedButtonClick(TObject *Sender)
{
    CStep new_step("Step" + IntToStr(StepCount+1));
    FOMOD.Steps.push_back(new_step);
    StepCount = FOMOD.Steps.size();
    StepsTabSheet->Enabled = true;
    RequiredInstallsTabSheet->Enabled = true;
    ConditionalInstallsTabSheet->Enabled = true;
    StepsTabSheet->Show();
    ProceedButton->Enabled = false;
    OpenRootDirButton->Enabled = false;
    RootDirEdit->Enabled = false;
    SaveMenu->Enabled = true;
    MergeFOMODMenu->Enabled = true;
    StepsTabControlChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StepNameEditChange(TObject *Sender)
{
    FOMOD.Steps[CurrentStepIndx].Name = StepNameEdit->Text;
    if(StepNameEdit->Text.Length())
        StepsTabControl->Pages[CurrentStepIndx]->Caption = StepNameEdit->Text;
    else
        StepsTabControl->Pages[CurrentStepIndx]->Caption = "[No name!]";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StepsTabControlChange(TObject *Sender)
{
    vector <UnicodeString> TotalConditionSet;
    vector <UnicodeString> TotalValueSet;
    vector <UnicodeString> TotalDependencySet;

    ConditionListView->Clear();
    GroupListView->Clear();
    PluginListView->Clear();
    FlagSetListView->Clear();
    SrcFilesListView->Clear();
    DstFilesListView->Clear();
    PluginDescriptionMemo->Clear();
    ConditionComboBox->Clear();
    VaribleComboBox->Clear();
    CondFileDependNameComboBox->Clear();
    ConditionValueComboBox->Clear();
    CondFileDependValueComboBox->Clear();
    VaribleValueComboBox->Clear();
    pdFileFlagNameComboBox->Clear();
    PluginImageEdit->Text = "";
    PluginImage->Picture->Bitmap = NULL;
    MoveLeftButton->Enabled = false;
    MoveRightButton->Enabled = false;

    CurrentStepIndx = StepsTabControl->ActivePageIndex;
    if(CurrentStepIndx < FOMOD.Steps.size())
        StepNameEdit->Text = FOMOD.Steps[CurrentStepIndx].Name;


    TotalValueSet.push_back("On");
    TotalValueSet.push_back("Off");
    TotalValueSet.push_back("Active");
    TotalValueSet.push_back("Inactive");
    TotalValueSet.push_back("Missing");

    for(int step_i = 0; step_i < FOMOD.Steps.size(); step_i++)
        for(int group_j = 0; group_j < FOMOD.Steps[step_i].PluginGroups.size(); group_j++)
            for(int plugin_k = 0; plugin_k < FOMOD.Steps[step_i].PluginGroups[group_j].Plugins.size(); plugin_k++)
            {
                for(int condition_c = 0; condition_c < FOMOD.Steps[step_i].PluginGroups[group_j].Plugins[plugin_k].ConditionSet.size(); condition_c++)
                {
                    UnicodeString
                        flag_name = FOMOD.Steps[step_i].PluginGroups[group_j].Plugins[plugin_k].ConditionSet[condition_c].Name,
                        flag_value = FOMOD.Steps[step_i].PluginGroups[group_j].Plugins[plugin_k].ConditionSet[condition_c].Value;
                    bool exist = false;
                    for(int i = 0; i < TotalConditionSet.size(); i++)
                        if(TotalConditionSet[i] == flag_name)
                        {
                            exist = true;
                            break;
                        }
                    if(!exist)
                        TotalConditionSet.push_back(flag_name);
                    exist = false;
                    for(int i = 0; i < TotalValueSet.size(); i++)
                        if(TotalValueSet[i] == flag_value)
                        {
                            exist = true;
                            break;
                        }
                    if(!exist)
                        TotalValueSet.push_back(flag_value);

                }
                for(int pattern_c = 0; pattern_c < FOMOD.Steps[step_i].PluginGroups[group_j].Plugins[plugin_k].DependencyPatterns.size(); pattern_c++)
                    for(int dependency_n = 0; dependency_n < FOMOD.Steps[step_i].PluginGroups[group_j].Plugins[plugin_k].DependencyPatterns[pattern_c].Dependencies.size(); dependency_n++)
                        {
                            UnicodeString dependency_name = FOMOD.Steps[step_i].PluginGroups[group_j].Plugins[plugin_k].DependencyPatterns[pattern_c].Dependencies[dependency_n].Name;
                            bool exist = false;

                            for(int i = 0; i < TotalDependencySet.size(); i++)
                                if(TotalDependencySet[i] == dependency_name)
                                {
                                    exist = true;
                                    break;
                                }
                            if(!exist)
                                TotalDependencySet.push_back(dependency_name);
                        }
            }


    if(TotalConditionSet.size() > 0)
    {
        for(int i = 0; i < TotalConditionSet.size(); i++)
        {
            VaribleComboBox->Items->Add(TotalConditionSet[i]);

            ConditionComboBox->Items->Add(TotalConditionSet[i]);
            CondFileDependNameComboBox->Items->Add(TotalConditionSet[i]);
            pdFileFlagNameComboBox->Items->Add(TotalConditionSet[i]);
        }
        ConditionComboBox->ItemIndex = 0;
    }
    for(int i = 0; i < TotalValueSet.size(); i++)
    {
        ConditionValueComboBox->Items->Add(TotalValueSet[i]);
        VaribleValueComboBox->Items->Add(TotalValueSet[i]);
        CondFileDependValueComboBox->Items->Add(TotalValueSet[i]);
    }
    for(int i = 0; i < TotalDependencySet.size(); i++)
    {
        ConditionComboBox->Items->Add(TotalDependencySet[i]);
        CondFileDependNameComboBox->Items->Add(TotalDependencySet[i]);
        pdFileFlagNameComboBox->Items->Add(TotalDependencySet[i]);
    }

    ConditionValueComboBox->ItemIndex = 0;

    if(CurrentStepIndx < FOMOD.Steps.size())
    {
        if(FOMOD.Steps[CurrentStepIndx].VisibilityDependencies.size() > 0)
        {
            for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].VisibilityDependencies.size(); i++)
            {
                TListItem *item = ConditionListView->Items->Add();
                item->Caption = FOMOD.Steps[CurrentStepIndx].VisibilityDependencies[i].Type;
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].VisibilityDependencies[i].Name);
                item->SubItems->Add("==");
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].VisibilityDependencies[i].Value);
                item->SubItems->Add("AND");
            }
        }

        if(FOMOD.Steps[CurrentStepIndx].PluginGroups.size() > 0)
        {
            for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].PluginGroups.size(); i++)
            {
                TListItem *item = GroupListView->Items->Add();
                item->Caption = FOMOD.Steps[CurrentStepIndx].PluginGroups[i].Name;
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[i].Type);
            }
            GroupListView->ItemIndex = 0;
            GroupListViewSelectItem(Sender, NULL, NULL);
        }
    }

    if(CurrentStepIndx > 0)
        MoveLeftButton->Enabled = true;
    if(CurrentStepIndx < StepCount-1)
        MoveRightButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddConditionButtonClick(TObject *Sender)
{
    if(ConditionComboBox->Items->Count > 0 && ConditionComboBox->ItemIndex > -1)
    {
        TListItem *item = ConditionListView->Items->Add();
        item->Caption = VisibilityTypeComboBox->Text;
        item->SubItems->Add(ConditionComboBox->Text);
        item->SubItems->Add("==");
        item->SubItems->Add(ConditionValueComboBox->Text);
        item->SubItems->Add("AND");

        CDependency new_dependency;
        new_dependency.Type = VisibilityTypeComboBox->Text;
        new_dependency.Name = ConditionComboBox->Text;
        new_dependency.Value = ConditionValueComboBox->Text;
        FOMOD.Steps[CurrentStepIndx].VisibilityDependencies.push_back(new_dependency);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteConditionButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].VisibilityDependencies.size() > 0 && ConditionListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].VisibilityDependencies.erase(FOMOD.Steps[CurrentStepIndx].VisibilityDependencies.begin()+ConditionListView->ItemIndex);
        ConditionListView->Items->Delete(ConditionListView->ItemIndex);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ConditionListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    if(ConditionListView->ItemIndex > -1)
        DeleteConditionButton->Enabled = true;
    else
        DeleteConditionButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddGroupButtonClick(TObject *Sender)
{
    if(GroupNameEdit->Text != "")
    {
        CPluginGroup new_group(GroupNameEdit->Text, GroupTypeComboBox->Text);
        FOMOD.Steps[CurrentStepIndx].PluginGroups.push_back(new_group);

        TListItem *item = GroupListView->Items->Add();
        item->Caption = GroupNameEdit->Text;
        item->SubItems->Add(GroupTypeComboBox->Text);
        GroupListView->ItemIndex = GroupListView->Items->Count-1;
        GroupListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemoveGroupButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups.size() > 0 && GroupListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups.erase(FOMOD.Steps[CurrentStepIndx].PluginGroups.begin()+GroupListView->ItemIndex);
        GroupListView->Items->Delete(GroupListView->ItemIndex);
        PluginListView->Clear();
        FlagSetListView->Clear();
        SrcFilesListView->Clear();
        DstFilesListView->Clear();
        GroupListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GroupListViewEdited(TObject *Sender, TListItem *Item, UnicodeString &S)
{
    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Name = S;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GroupUpButtonClick(TObject *Sender)
{
    unsigned int temp = GroupListView->ItemIndex;
    std::iter_swap(FOMOD.Steps[CurrentStepIndx].PluginGroups.begin()+temp,
                    FOMOD.Steps[CurrentStepIndx].PluginGroups.begin()+temp-1);
    StepsTabControlChange(Sender);
    GroupListView->ItemIndex = temp - 1;
    GroupListViewSelectItem(Sender, NULL, NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GroupDownButtonClick(TObject *Sender)
{
    unsigned int temp = GroupListView->ItemIndex;
    std::iter_swap(FOMOD.Steps[CurrentStepIndx].PluginGroups.begin()+temp,
                    FOMOD.Steps[CurrentStepIndx].PluginGroups.begin()+temp+1);
    StepsTabControlChange(Sender);
    GroupListView->ItemIndex = temp + 1;
    GroupListViewSelectItem(Sender, NULL, NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GroupListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    PluginListView->Clear();
    FlagSetListView->Clear();
    SrcFilesListView->Clear();
    DstFilesListView->Clear();
    PluginDescriptionMemo->Clear();
    PluginImageEdit->Text = "";
    PluginImage->Picture->Bitmap = NULL;
    RemoveGroupButton->Enabled = false;
    AddPluginButton->Enabled = false;
    GroupUpButton->Enabled = false;
    GroupDownButton->Enabled = false;

    if(FOMOD.Steps[CurrentStepIndx].PluginGroups.size() > 0 && GroupListView->ItemIndex > -1)
    {
        for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size(); i++)
        {
            PluginListView->Items->Add()->Caption = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[i].Name;
        }
        if(PluginListView->Items->Count > 0)
        {
            PluginListView->ItemIndex = 0;
        }

        RemoveGroupButton->Enabled = true;
        AddPluginButton->Enabled = true;
        if(GroupListView->ItemIndex > 0)
            GroupUpButton->Enabled = true;
        if(GroupListView->ItemIndex < GroupListView->Items->Count - 1)
            GroupDownButton->Enabled = true;
    }

    PluginListViewSelectItem(Sender, NULL, NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddPluginButtonClick(TObject *Sender)
{
    if(PluginNameEdit->Text != "" && FOMOD.Steps[CurrentStepIndx].PluginGroups.size() > 0 && GroupListView->ItemIndex > -1)
    {
        CPlugin new_plugin(PluginNameEdit->Text);
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.push_back(new_plugin);
        PluginListView->Items->Add()->Caption = PluginNameEdit->Text;
        PluginListView->ItemIndex = PluginListView->Items->Count-1;
        PluginListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemovePluginButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.erase(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+PluginListView->ItemIndex);
        PluginListView->Items->Delete(PluginListView->ItemIndex);
        FlagSetListView->Clear();
        SrcFilesListView->Clear();
        DstFilesListView->Clear();
        PluginListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginUpButtonClick(TObject *Sender)
{

    unsigned int temp = PluginListView->ItemIndex;
    std::iter_swap(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp,
                    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp-1);
    GroupListViewSelectItem(Sender, NULL, NULL);
    PluginListView->ItemIndex = temp - 1;
    PluginListViewSelectItem(Sender, NULL, NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginDownButtonClick(TObject *Sender)
{

    unsigned int temp = PluginListView->ItemIndex;
    std::iter_swap(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp,
                    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp+1);
    GroupListViewSelectItem(Sender, NULL, NULL);
    PluginListView->ItemIndex = temp + 1;
    PluginListViewSelectItem(Sender, NULL, NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    RemovePluginButton->Enabled = false;
    PluginDescriptionMemo->Enabled = false;
    AddVaribleButton->Enabled = false;
    DeleteVaribleButton->Enabled = false;
    ChoosePluginImageButton->Enabled = false;
    ClearPluginImageButton->Enabled = false;
    PluginImageEdit->Enabled = false;
    AddFileButton->Enabled = false;
    AddFolderButton->Enabled = false;
    PluginUpButton->Enabled = false;
    PluginDownButton->Enabled = false;
    pdDefTypeComboBox->Enabled = false;
    pdNewPatternButton->Enabled = false;
    pdDeletePatternButton->Enabled = false;
    pdOperatorComboBox->Enabled = false;
    pdTypeNameComboBox->Enabled = false;
    for(int i = pdPatternsPageControl->PageCount-1; i >= 0; i--)
        pdPatternsPageControl->Pages[i]->Free();
    FlagSetListView->Clear();
    SrcFilesListView->Clear();
    DstFilesListView->Clear();
    PluginDependenciesListView->Clear();
    PluginDescriptionMemo->Clear();
    PluginImageEdit->Text = "";
    PluginImage->Picture->Bitmap = NULL;

    int plugin_indx = PluginListView->ItemIndex;
    if(plugin_indx > -1)
    {
        if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].ConditionSet.size() > 0)
        {
            for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].ConditionSet.size(); i++)
            {
                TListItem *item = FlagSetListView->Items->Add();
                item->Caption = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].ConditionSet[i].Name;
                item->SubItems->Add(" =");
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].ConditionSet[i].Value);
            }
        }
        if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].Files.size() > 0)
        {
            for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].Files.size(); i++)
            {
                TListItem *item = SrcFilesListView->Items->Add();
                item->Caption = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].Files[i].Type;
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].Files[i].SrcPath);
                item = DstFilesListView->Items->Add();
                item->Caption = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].Files[i].DstPath;
            }
        }
        PluginDescriptionMemo->Lines->Text = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].Description;
        PluginImageEdit->Text = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].ImagePath;
        if(PluginImageEdit->Text != "")
        {
            FILE *tfp = _tfopen( (RootDirectory + "\\" + PluginImageEdit->Text).c_str(), _T("r") );
            if(tfp)
            {
                fclose(tfp);
                PluginImage->Picture->LoadFromFile(RootDirectory + "\\" + PluginImageEdit->Text);
            }
            else
            {
                MessageBox(NULL, _T("Image file not found. Image field for this plugin will be cleared."), _T("FOMOD Creation Tool"),  MB_OK);
                FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].ImagePath = "";
                PluginImageEdit->Text = "";
            }
        }

        pdDefTypeComboBox->Text = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].DefaultType;

        RemovePluginButton->Enabled = true;
        PluginDescriptionMemo->Enabled = true;
        AddVaribleButton->Enabled = true;
        ChoosePluginImageButton->Enabled = true;
        ClearPluginImageButton->Enabled = true;
        PluginImageEdit->Enabled = true;
        AddFileButton->Enabled = true;
        AddFolderButton->Enabled = true;
        pdDefTypeComboBox->Enabled = true;
        pdNewPatternButton->Enabled = true;
        for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[plugin_indx].DependencyPatterns.size(); i++)
        {
            TTabSheet *new_tab = new TTabSheet(pdPatternsPageControl);
            new_tab->Caption = "Pattern[" + IntToStr(i) + "]";
            new_tab->PageControl = pdPatternsPageControl;
        }
        if(pdPatternsPageControl->PageCount == 0)
            pdDeletePatternButton->Enabled = false;
        else
            pdDeletePatternButton->Enabled = true;
        pdOperatorComboBox->Enabled = true;
        pdTypeNameComboBox->Enabled = true;
        pdPatternsPageControlChange(Sender);
        if(plugin_indx > 0)
            PluginUpButton->Enabled = true;
        if(plugin_indx < PluginListView->Items->Count-1)
            PluginDownButton->Enabled = true;

    }
    SrcFilesListViewSelectItem(Sender, NULL, NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginListViewEdited(TObject *Sender, TListItem *Item,
          UnicodeString &S)
{
    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Name = S;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddVaribleButtonClick(TObject *Sender)
{
    if(VaribleComboBox->Text != "" && PluginListView->ItemIndex > -1)
    {
        CCondition new_condition(VaribleComboBox->Text, VaribleValueComboBox->Text);
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].ConditionSet.push_back(new_condition);

        TListItem *item = FlagSetListView->Items->Add();
        item->Caption = VaribleComboBox->Text;
        item->SubItems->Add(" =");
        item->SubItems->Add(VaribleValueComboBox->Text);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteVaribleButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].ConditionSet.size() > 0 && FlagSetListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].ConditionSet.erase(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].ConditionSet.begin()+FlagSetListView->ItemIndex);
        FlagSetListView->Items->Delete(FlagSetListView->ItemIndex);
        FlagSetListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FlagSetListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    if(FlagSetListView->ItemIndex > -1)
        DeleteVaribleButton->Enabled = true;
    else
        DeleteVaribleButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginDescriptionMemoChange(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        int len = _tcslen(PluginDescriptionMemo->Lines[0].Text.c_str());
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Description =
            PluginDescriptionMemo->Lines->Text;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddFileButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        OpenDialog->Filter = "";
        if(OpenDialog->Execute())
        {
            UnicodeString temp = OpenFolderDialog->FileName.SubString(0, RootDirectory.Length()).UpperCase();
            if(!(temp.Compare(RootDirectory.UpperCase())))
            {
                UnicodeString
                    src_path,
                    dst_path;

                src_path = OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2);
                dst_path = getProperDestinationPath(src_path);

                TListItem *item = SrcFilesListView->Items->Add();
                item->Caption = "file";
                item->SubItems->Add(src_path);
                item = DstFilesListView->Items->Add();
                item->Caption = dst_path;

                CFile new_file;
                new_file.Type = "file";
                new_file.SrcPath = src_path;
                new_file.DstPath = dst_path;
                FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Files.push_back(new_file);
            }
            else
            {
                MessageBox(NULL, _T("File is out of root directory"), _T("FOMOD Creation Tool"),  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddFolderButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        if(OpenFolderDialog->Execute())
        {
            UnicodeString temp = OpenFolderDialog->FileName.SubString(0, RootDirectory.Length()).UpperCase();
            if(!(temp.Compare(RootDirectory.UpperCase())))
            {
                UnicodeString
                    src_path,
                    dst_path;

                src_path = OpenFolderDialog->FileName.SubString(RootDirectory.Length()+2, OpenFolderDialog->FileName.Length()-RootDirectory.Length()+2);
                dst_path = getProperDestinationPath(src_path);

                TListItem *item = SrcFilesListView->Items->Add();
                item->Caption = "folder";
                item->SubItems->Add(src_path);
                item = DstFilesListView->Items->Add();
                item->Caption = dst_path;

                CFile new_file;
                new_file.Type = "folder";
                new_file.SrcPath = src_path;
                new_file.DstPath = dst_path;
                FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Files.push_back(new_file);
            }
            else
            {
                MessageBox(NULL, _T("Folder is out of root directory"), _T("FOMOD Creation Tool"),  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemoveFileFolderButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Files.size() > 0 &&
        SrcFilesListView->ItemIndex > -1)
    {
        int ind = SrcFilesListView->ItemIndex;
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Files.erase(
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Files.begin() +
            ind);
        SrcFilesListView->ItemIndex = -1;
        DstFilesListView->ItemIndex = -1;
        DstFilesListView->Items->Delete(ind);
        SrcFilesListView->Items->Delete(ind);
        if( ind < SrcFilesListView->Items->Count-1 )
        {
            SrcFilesListView->ItemIndex = ind;
            DstFilesListView->ItemIndex = ind;
        }
        else if( ind >= SrcFilesListView->Items->Count-1)
        {
            SrcFilesListView->ItemIndex = SrcFilesListView->Items->Count-1;
            DstFilesListView->ItemIndex = SrcFilesListView->Items->Count-1;
        }
        SrcFilesListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SrcFilesListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    DstFilesListView->ItemIndex = SrcFilesListView->ItemIndex;
    if(SrcFilesListView->ItemIndex > -1)
    {
        ListView_EnsureVisible(DstFilesListView->Handle, SrcFilesListView->ItemIndex, false);
        RemoveFileFolderButton->Enabled = true;
    }
    else
        RemoveFileFolderButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DstFilesListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    SrcFilesListView->ItemIndex = DstFilesListView->ItemIndex;
    if(DstFilesListView->ItemIndex > -1)
    {
        ListView_EnsureVisible(SrcFilesListView->Handle, DstFilesListView->ItemIndex, false);
        RemoveFileFolderButton->Enabled = true;
    }
    else
        RemoveFileFolderButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DstFilesListViewEdited(TObject *Sender, TListItem *Item,
          UnicodeString &S)
{
    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Files[SrcFilesListView->ItemIndex].DstPath = S;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ChoosePluginImageButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        OpenDialog->Filter = "";
        if(OpenDialog->Execute())
        {
            UnicodeString temp = OpenDialog->FileName.SubString(0, RootDirectory.Length()).UpperCase();
            if(!(temp.Compare(RootDirectory.UpperCase())))
            {
                PluginImageEdit->Text = OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2);
                UnicodeString ext = OpenDialog->FileName.SubString(OpenDialog->FileName.Length()-2, 3);
                try{
                    if(ext == "jpg")
                    {
                        TJPEGImage *jpg = new TJPEGImage;
                        jpg->LoadFromFile(OpenDialog->FileName);
                        PluginImage->Picture->Bitmap->Assign(jpg);
                        delete jpg;
                    }
                    else if(ext == "png")
                    {
                        TPngImage *png = new TPngImage;
                        png->LoadFromFile(OpenDialog->FileName);
                        PluginImage->Picture->Bitmap->Assign(png);
                    delete png;
                    }
                    else
                        PluginImage->Picture->LoadFromFile(OpenDialog->FileName);
                }
                catch(...){}

                FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].ImagePath = PluginImageEdit->Text;
            }
            else
            {
                MessageBox(NULL, _T("File is out of root directory"), _T("FOMOD Creation Tool"),  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClearPluginImageButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        PluginImageEdit->Text = "";
        PluginImage->Picture->Bitmap = NULL;
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].ImagePath = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NewStepButtonClick(TObject *Sender)
{
    CStep new_step("Step" + IntToStr(StepCount+1));
    FOMOD.Steps.push_back(new_step);
    TTabSheet *new_tab = new TTabSheet(StepsTabControl);
    new_tab->Caption = "Step" + IntToStr(StepCount+1);
    new_tab->PageControl = StepsTabControl;
    StepsTabControl->ActivePage = new_tab;
    StepsTabControlChange(Sender);
    StepCount = FOMOD.Steps.size();
    DeleteStepButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteStepButtonClick(TObject *Sender)
{
    FOMOD.Steps.erase(FOMOD.Steps.begin()+CurrentStepIndx);
    StepsTabControl->Pages[CurrentStepIndx]->Free();
    StepCount = FOMOD.Steps.size();
    StepsTabControlChange(Sender);
    if(StepsTabControl->PageCount == 1)
        DeleteStepButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MoveLeftButtonClick(TObject *Sender)
{
    std::iter_swap(FOMOD.Steps.begin()+CurrentStepIndx,
                    FOMOD.Steps.begin()+CurrentStepIndx-1);
    StepsTabControl->Pages[CurrentStepIndx]->Caption = FOMOD.Steps[CurrentStepIndx].Name;
    CurrentStepIndx--;
    StepsTabControl->Pages[CurrentStepIndx]->Caption = FOMOD.Steps[CurrentStepIndx].Name;
    StepsTabControl->ActivePage = StepsTabControl->Pages[CurrentStepIndx];
    if(CurrentStepIndx == 0)
        MoveLeftButton->Enabled = false;
    MoveRightButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MoveRightButtonClick(TObject *Sender)
{
    std::iter_swap(FOMOD.Steps.begin()+CurrentStepIndx,
                    FOMOD.Steps.begin()+CurrentStepIndx+1);
    StepsTabControl->Pages[CurrentStepIndx]->Caption = FOMOD.Steps[CurrentStepIndx].Name;
    CurrentStepIndx++;
    StepsTabControl->Pages[CurrentStepIndx]->Caption = FOMOD.Steps[CurrentStepIndx].Name;
    StepsTabControl->ActivePage = StepsTabControl->Pages[CurrentStepIndx];
    if(CurrentStepIndx == StepCount-1)
        MoveRightButton->Enabled = false;
    MoveLeftButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveMenuClick(TObject *Sender)
{
    CFOMOD temp_fomod = FOMOD;
    _TCHAR t_path[256];

    SaveConfirmationPanel->Left = (MainForm->ClientWidth - SaveConfirmationPanel->Width) / 2;
    SaveConfirmationPanel->Top = (MainForm->ClientHeight - SaveConfirmationPanel->Height) / 2;
    infoXMLStateLabel->Caption = "";
    mdlconfXMLStateLabel->Caption = "";
    SaveConfirmationPanel->Visible = true;
    ShowConfirmationTimer->Enabled = true;

    _tcscpy(t_path, Application->ExeName.c_str());
    for(int i = _tcslen(t_path); i > 0; i--)
        if( t_path[i] == _T('\\') )
        {
            t_path[i+1] = _T('\0');
            break;
        }
    _tcscat(t_path, _T("runbefore.txt"));
    RunBatFile(t_path, temp_fomod);

    FILE *fpinfoxml = _tfopen((RootDirectory+"\\fomod\\info.xml").c_str(), _T("wb"));
    if(fpinfoxml)
    {
        // BOM
        if(sizeof(_TCHAR) > 1)
            fwrite(&BOM, sizeof(_TCHAR), 1, fpinfoxml);

        _ftprintf(fpinfoxml, _T("<fomod> \n"));
        _ftprintf(fpinfoxml, _T("\t<Name>%s</Name> \n"), temp_fomod.Name.c_str());
        _ftprintf(fpinfoxml, _T("\t<Author>%s</Author> \n"), temp_fomod.AuthorName.c_str());
        _ftprintf(fpinfoxml, _T("\t<Version>%s</Version> \n"), temp_fomod.Version.c_str());
        _ftprintf(fpinfoxml, _T("\t<Website>%s</Website> \n"), temp_fomod.URL.c_str());
        _ftprintf(fpinfoxml, _T("\t<Description>%s</Description> \n"), temp_fomod.Description.c_str());
        _ftprintf(fpinfoxml, _T("\t<Groups>\n\t\t<element>%s</element>\n\t</Groups> \n"), temp_fomod.ModCategory.c_str());
        _ftprintf(fpinfoxml, _T("</fomod> \n"));

        fclose(fpinfoxml);

        infoXMLStateLabel->Caption = "OK";
    }
    else
    {
        MessageBox(NULL, _T("Can't open 'fomod\\info.xml' for write"), _T("temp_fomod Creation Tool"),  MB_OK);
        infoXMLStateLabel->Caption = "Error";
    }


    FILE *fpModuleConfigxml = _tfopen((RootDirectory+"\\fomod\\ModuleConfig.xml").c_str(), _T("wb"));
    if(fpModuleConfigxml)
    {
        // BOM
        if(sizeof(_TCHAR) > 1)
            fwrite(&BOM, sizeof(_TCHAR), 1, fpModuleConfigxml);

        _ftprintf(fpModuleConfigxml, _T("<!-- Powered by FOMOD Creation Tool %s [%s] --> \n"), GetFileVersionOfApplication(Application->ExeName.c_str()), _T("http://www.nexusmods.com/fallout4/mods/6821"));

        _ftprintf(fpModuleConfigxml, _T("<config xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://qconsulting.ca/fo3/ModConfig5.0.xsd\"> \n"));
        _ftprintf(fpModuleConfigxml, _T("\t<moduleName>%s</moduleName> \n"), temp_fomod.Name.c_str());

        if(temp_fomod.RequiredFiles.size() > 0)
        {
            _ftprintf(fpModuleConfigxml, _T("\t<requiredInstallFiles> \n"));
            for(int i = 0; i < temp_fomod.RequiredFiles.size(); i++)
                _ftprintf(fpModuleConfigxml, _T("\t\t<%s source=\"%s\" destination=\"%s\" /> \n"),
                    temp_fomod.RequiredFiles[i].Type.c_str(),
                    temp_fomod.RequiredFiles[i].SrcPath.c_str(),
                    temp_fomod.RequiredFiles[i].DstPath.c_str());
            _ftprintf(fpModuleConfigxml, _T("\t</requiredInstallFiles> \n"));
        }

        _ftprintf(fpModuleConfigxml, _T("\t<installSteps order=\"Explicit\"> \n"));
        for(int step_i = 0; step_i < temp_fomod.Steps.size(); step_i++)
        {
            _ftprintf(fpModuleConfigxml, _T("\t\t<installStep name=\"%s\"> \n"), temp_fomod.Steps[step_i].Name.c_str());
            if(temp_fomod.Steps[step_i].VisibilityDependencies.size() > 0)
            {
                _ftprintf(fpModuleConfigxml, _T("\t\t\t<visible> \n"));
                for(int i = 0; i < temp_fomod.Steps[step_i].VisibilityDependencies.size(); i++)
                {
                    if(temp_fomod.Steps[step_i].VisibilityDependencies[i].Type == _T("file"))
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t<fileDependency file=\"%s\" state=\"%s\"/> \n"),
                            temp_fomod.Steps[step_i].VisibilityDependencies[i].Name.c_str(),
                            temp_fomod.Steps[step_i].VisibilityDependencies[i].Value.c_str());
                    else if(temp_fomod.Steps[step_i].VisibilityDependencies[i].Type == _T("flag"))
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t<flagDependency flag=\"%s\" value=\"%s\"/> \n"),
                            temp_fomod.Steps[step_i].VisibilityDependencies[i].Name.c_str(),
                            temp_fomod.Steps[step_i].VisibilityDependencies[i].Value.c_str());
                }
                _ftprintf(fpModuleConfigxml, _T("\t\t\t</visible> \n"));
            }

            _ftprintf(fpModuleConfigxml, _T("\t\t\t<optionalFileGroups order=\"Explicit\"> \n"));
            for(int group_i = 0; group_i < temp_fomod.Steps[step_i].PluginGroups.size(); group_i++)
            {
                _ftprintf(fpModuleConfigxml, _T("\t\t\t\t<group name=\"%s\" type=\"%s\"> \n"),
                    temp_fomod.Steps[step_i].PluginGroups[group_i].Name.c_str(),
                    temp_fomod.Steps[step_i].PluginGroups[group_i].Type.c_str());

                _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t<plugins order=\"Explicit\"> \n"));
                for(int plugin_i = 0; plugin_i < temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins.size(); plugin_i++)
                {
                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t<plugin name=\"%s\"> \n"),
                        temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Name.c_str());
                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t<description>%s</description> \n"),
                        temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Description.c_str());
                    if(temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ImagePath != "")
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t<image path=\"%s\" /> \n"),
                            temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ImagePath.c_str());
                    if(temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ConditionSet.size() > 0)
                    {
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t<conditionFlags> \n"));
                        for(int i = 0; i < temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ConditionSet.size(); i++)
                            _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t<flag name=\"%s\">%s</flag> \n"),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ConditionSet[i].Name.c_str(),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ConditionSet[i].Value.c_str());
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t</conditionFlags> \n"));
                    }
                    if(temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files.size() > 0)
                    {
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t<files> \n"));
                        for(int i = 0; i < temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files.size(); i++)
                            _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t<%s source=\"%s\" destination=\"%s\" /> \n"),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files[i].Type.c_str(),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files[i].SrcPath.c_str(),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files[i].DstPath.c_str());
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t</files> \n"));
                    }
                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t<typeDescriptor> \n"));
                    if(temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns.size() == 0)
                    {
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t<type name=\"%s\"/> \n"),
                            temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DefaultType.c_str());
                    }
                    else
                    {
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t<dependencyType> \n"));
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t<defaultType name=\"%s\"/> \n"),
                            temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DefaultType.c_str());
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t<patterns> \n"));
                        for(int i = 0; i < temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns.size(); i++)
                        {
                            _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t\t<pattern> \n"));
                            _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t\t\t<dependencies operator=\"%s\"> \n"),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns[i].Operator.c_str());
                            for(int j = 0; j < temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns[i].Dependencies.size(); j++)
                            {
                                if(temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns[i].Dependencies[j].Type == _T("file"))
                                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t\t\t\t<fileDependency file=\"%s\" state=\"%s\"/> \n"),
                                        temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns[i].Dependencies[j].Name.c_str(),
                                        temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns[i].Dependencies[j].Value.c_str());
                                else if(temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns[i].Dependencies[j].Type == _T("flag"))
                                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t\t\t\t<flagDependency flag=\"%s\" value=\"%s\"/> \n"),
                                        temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns[i].Dependencies[j].Name.c_str(),
                                        temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns[i].Dependencies[j].Value.c_str());
                            }
                            _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t\t\t</dependencies> \n"));
                            _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t\t\t<type name=\"%s\"/> \n"),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].DependencyPatterns[i].Type.c_str());

                            _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t\t</pattern> \n"));
                        }
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t\t</patterns> \n"));
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t\t</dependencyType> \n"));
                    }
                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t\t</typeDescriptor> \n"));

                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t\t</plugin> \n"));
                }
                _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t</plugins> \n"));

                _ftprintf(fpModuleConfigxml, _T("\t\t\t\t</group> \n"));
            }
            _ftprintf(fpModuleConfigxml, _T("\t\t\t</optionalFileGroups> \n"));

            _ftprintf(fpModuleConfigxml, _T("\t\t</installStep> \n"));
        }
        _ftprintf(fpModuleConfigxml, _T("\t</installSteps> \n"));

        if(temp_fomod.ConditionalFiles.size() > 0)
        {
            _ftprintf(fpModuleConfigxml, _T("\t<conditionalFileInstalls> \n"));
            _ftprintf(fpModuleConfigxml, _T("\t\t<patterns> \n"));
            for(int i = 0; i < temp_fomod.ConditionalFiles.size(); i++)
            {
                _ftprintf(fpModuleConfigxml, _T("\t\t\t<pattern> \n"));
                if(temp_fomod.ConditionalFiles[i].Dependencies.size() > 0)
                {
                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t<dependencies operator=\"%s\"> \n"), temp_fomod.ConditionalFiles[i].Operator.c_str());
                    for(int j = 0; j < temp_fomod.ConditionalFiles[i].Dependencies.size(); j++)
                    {
                        if(temp_fomod.ConditionalFiles[i].Dependencies[j].Type == _T("file"))
                            _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t<fileDependency file=\"%s\" state=\"%s\"/> \n"),
                                temp_fomod.ConditionalFiles[i].Dependencies[j].Name.c_str(),
                                temp_fomod.ConditionalFiles[i].Dependencies[j].Value.c_str());
                        else if(temp_fomod.ConditionalFiles[i].Dependencies[j].Type == _T("flag"))
                            _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t<flagDependency flag=\"%s\" value=\"%s\"/> \n"),
                                temp_fomod.ConditionalFiles[i].Dependencies[j].Name.c_str(),
                                temp_fomod.ConditionalFiles[i].Dependencies[j].Value.c_str());
                    }
                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t</dependencies> \n"));
                }
                if(temp_fomod.ConditionalFiles[i].Files.size() > 0)
                {
                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t<files> \n"));
                    for(int j = 0; j < temp_fomod.ConditionalFiles[i].Files.size(); j++)
                        _ftprintf(fpModuleConfigxml, _T("\t\t\t\t\t<%s source=\"%s\" destination=\"%s\" /> \n"),
                            temp_fomod.ConditionalFiles[i].Files[j].Type.c_str(),
                            temp_fomod.ConditionalFiles[i].Files[j].SrcPath.c_str(),
                            temp_fomod.ConditionalFiles[i].Files[j].DstPath.c_str());
                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t</files> \n"));
                }
                _ftprintf(fpModuleConfigxml, _T("\t\t\t</pattern> \n"));
            }
            _ftprintf(fpModuleConfigxml, _T("\t\t</patterns> \n"));
            _ftprintf(fpModuleConfigxml, _T("\t</conditionalFileInstalls> \n"));
        }

        _ftprintf(fpModuleConfigxml, _T("</config>"));

        fclose(fpModuleConfigxml);

        _tcscpy(t_path, Application->ExeName.c_str());
        for(int i = _tcslen(t_path); i > 0; i--)
            if( t_path[i] == _T('\\') )
            {
                t_path[i+1] = _T('\0');
                break;
            }
        _tcscat(t_path, _T("runafter.txt"));
        RunBatFile(t_path, temp_fomod);

        mdlconfXMLStateLabel->Caption = "OK";

        ManageRecentFiles(RootDirectory);
    }
    else
    {
        MessageBox(NULL, _T("Can't open 'fomod\\ModuleConfig.xml' for write"), _T("FOMOD Creation Tool"),  MB_OK);
        mdlconfXMLStateLabel->Caption = "Error";
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ShowConfirmationTimerTimer(TObject *Sender)
{
    SaveConfirmationPanel->Visible = false;
    ShowConfirmationTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NewMenuClick(TObject *Sender)
{
    FOMOD.Name = "";
    FOMOD.AuthorName = "";
    FOMOD.Version = "";
    FOMOD.URL = "";
    FOMOD.ModCategory = "";
    FOMOD.Description = "";
    FOMOD.RequiredFiles.clear();
    FOMOD.Steps.clear();
    FOMOD.ConditionalFiles.clear();
    StepCount = FOMOD.Steps.size();
    CurrentStepIndx = 0;

    StepsTabSheet->Enabled = false;
    RequiredInstallsTabSheet->Enabled = false;
    ConditionalInstallsTabSheet->Enabled = false;
    ModInfoTabSheet->Show();
    while(StepsTabControl->PageCount > 1)
        StepsTabControl->Pages[1]->Free();
    while(ConiditionalFilesPageControl->PageCount > 0)
        ConiditionalFilesPageControl->Pages[0]->Free();
    ModNameEdit->Text = "";
    ModAuthorEdit->Text = "";
    ModVersionEdit->Text = "";
    ModURLEdit->Text = "";
    ModCategoryComboBox->Text = "";
    ModDesccriptionMemo->Text = "";
    ProceedButton->Enabled = true;
    OpenRootDirButton->Enabled = true;
    RootDirEdit->Enabled = true;
    RootDirEdit->Text = "";
    SaveMenu->Enabled = false;
    MergeFOMODMenu->Enabled = false;
    DeleteStepButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenMenuClick(TObject *Sender)
{
    if(OpenFolderDialog->Execute())
    {
        if(dirExists(OpenFolderDialog->FileName + "\\fomod"))
        {
            bool
                module_config_xml_loaded = false,
                info_xml_loaded = false;

            NewMenuClick(Sender);

            RootDirEdit->Text = OpenFolderDialog->FileName;
            RootDirectory = OpenFolderDialog->FileName;

            try{
                info_xml_loaded = LoadFOMODInfoFromXML((RootDirectory+"\\fomod\\info.xml").c_str(), FOMOD);
            }
            catch(...){}
            try{
                module_config_xml_loaded = LoadFOMODFromXML((RootDirectory+"\\fomod\\ModuleConfig.xml").c_str(), FOMOD);
            }
            catch(...){}

            if(info_xml_loaded)
            {
                ModNameEdit->Text = FOMOD.Name;
                ModAuthorEdit->Text = FOMOD.AuthorName;
                ModVersionEdit->Text = FOMOD.Version;
                ModURLEdit->Text = FOMOD.URL;
                ModDesccriptionMemo->Lines->Text = FOMOD.Description;
                ModCategoryComboBox->Text = FOMOD.ModCategory;
            }
            if(module_config_xml_loaded)
            {
                for(int i = 1; i < FOMOD.Steps.size(); i++)
                {
                    TTabSheet *new_tab = new TTabSheet(StepsTabControl);
                    new_tab->Caption = FOMOD.Steps[i].Name;
                    new_tab->PageControl = StepsTabControl;
                }
                for(int i = 0; i < FOMOD.RequiredFiles.size(); i++)
                {
                    TListItem *item = RequiredFilesSrcListView->Items->Add();
                    item->Caption = FOMOD.RequiredFiles[i].Type;
                    item->SubItems->Add(FOMOD.RequiredFiles[i].SrcPath);
                    item = RequiredFilesDstListView->Items->Add();
                    item->Caption = FOMOD.RequiredFiles[i].DstPath;
                }
                for(int i = 0; i < FOMOD.ConditionalFiles.size(); i++)
                {
                    TTabSheet *new_tab = new TTabSheet(ConiditionalFilesPageControl);
                    new_tab->Caption = "Pattern[" + IntToStr(i) + "]";
                    new_tab->PageControl = ConiditionalFilesPageControl;
                }
                StepsTabControl->Pages[0]->Caption = FOMOD.Steps[0].Name;
                StepsTabControl->ActivePage = StepsTabControl->Pages[0];
                ConiditionalFilesPageControlChange(Sender);

                ManageRecentFiles(RootDirectory);
            }


            StepCount = FOMOD.Steps.size();
            CurrentStepIndx = StepCount-1;
            StepsTabControlChange(Sender);

            StepsTabSheet->Enabled = true;
            RequiredInstallsTabSheet->Enabled = true;
            ConditionalInstallsTabSheet->Enabled = true;
            StepsTabSheet->Show();
            ProceedButton->Enabled = false;
            OpenRootDirButton->Enabled = false;
            RootDirEdit->Enabled = false;
            SaveMenu->Enabled = true;
            MergeFOMODMenu->Enabled = true;
        }
        else
        {
            MessageBox(NULL, _T("There is no 'fomod' catalog in specified directory. Choose root directory containing 'fomod' folder."), _T("FOMOD Creation Tool"), MB_OK);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenfileMenuClick(TObject *Sender)
{
    OpenDialog->Filter = "|*.xml";
    if(OpenDialog->Execute())
    {
        _TCHAR path[256];
        UnicodeString
            fileName,
            rootDir = "";
        bool
            module_config_xml_loaded = false,
            info_xml_loaded = false;

        _tcscpy(path, OpenDialog->FileName.c_str());
        for(int i = _tcslen(path); i > 0; i--)
            if(path[i] == _T('\\'))
            {
                fileName = &path[i+1];
                for(int j = i-1; j > 0; j--)
                    if(path[j] == _T('\\'))
                    {
                        path[j] = _T('\0');
                        rootDir = path;
                        break;
                    }
                break;
            }

        NewMenuClick(Sender);

        RootDirEdit->Text = rootDir;
        RootDirectory = rootDir;

        if( !(fileName.UpperCase().Compare("INFO.XML")) )
        {
            try{
                info_xml_loaded = LoadFOMODInfoFromXML(OpenDialog->FileName.c_str(), FOMOD);
            }
            catch(...){}
            try{
                module_config_xml_loaded = LoadFOMODFromXML((RootDirectory+"\\fomod\\ModuleConfig.xml").c_str(), FOMOD);
            }
            catch(...){}
        }
        else if( !(fileName.UpperCase().Compare("MODULECONFIG.XML")) )
        {
            try{
                info_xml_loaded = LoadFOMODInfoFromXML((RootDirectory+"\\fomod\\info.xml").c_str(), FOMOD);
            }
            catch(...){}
            try{
                module_config_xml_loaded = LoadFOMODFromXML(OpenDialog->FileName.c_str(), FOMOD);
            }
            catch(...){}
        }

        if(info_xml_loaded)
        {
            ModNameEdit->Text = FOMOD.Name;
            ModAuthorEdit->Text = FOMOD.AuthorName;
            ModVersionEdit->Text = FOMOD.Version;
            ModURLEdit->Text = FOMOD.URL;
            ModDesccriptionMemo->Lines->Text = FOMOD.Description;
            ModCategoryComboBox->Text = FOMOD.ModCategory;
        }
        if(module_config_xml_loaded)
        {
            for(int i = 1; i < FOMOD.Steps.size(); i++)
            {
                TTabSheet *new_tab = new TTabSheet(StepsTabControl);
                new_tab->Caption = FOMOD.Steps[i].Name;
                new_tab->PageControl = StepsTabControl;
            }
            for(int i = 0; i < FOMOD.RequiredFiles.size(); i++)
            {
                TListItem *item = RequiredFilesSrcListView->Items->Add();
                item->Caption = FOMOD.RequiredFiles[i].Type;
                item->SubItems->Add(FOMOD.RequiredFiles[i].SrcPath);
                item = RequiredFilesDstListView->Items->Add();
                item->Caption = FOMOD.RequiredFiles[i].DstPath;
            }
            for(int i = 0; i < FOMOD.ConditionalFiles.size(); i++)
            {
                TTabSheet *new_tab = new TTabSheet(ConiditionalFilesPageControl);
                new_tab->Caption = "Pattern[" + IntToStr(i) + "]";
                new_tab->PageControl = ConiditionalFilesPageControl;
            }
            StepsTabControl->Pages[0]->Caption = FOMOD.Steps[0].Name;
            StepsTabControl->ActivePage = StepsTabControl->Pages[0];
            ConiditionalFilesPageControlChange(Sender);

            ManageRecentFiles(RootDirectory);
        }


        StepCount = FOMOD.Steps.size();
        CurrentStepIndx = StepCount-1;
        StepsTabControlChange(Sender);

        StepsTabSheet->Enabled = true;
        RequiredInstallsTabSheet->Enabled = true;
        ConditionalInstallsTabSheet->Enabled = true;
        StepsTabSheet->Show();
        ProceedButton->Enabled = false;
        OpenRootDirButton->Enabled = false;
        RootDirEdit->Enabled = false;
        SaveMenu->Enabled = true;
        MergeFOMODMenu->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MergeFOMODMenuClick(TObject *Sender)
{
    OpenDialog->Filter = "|*.xml";
    if(OpenDialog->Execute())
    {
        CFOMOD merge_fomod;
        bool loaded = false;

        try{
            loaded = LoadFOMODFromXML(OpenDialog->FileName.c_str(), FOMOD);
        }
        catch(...){}

        if(loaded)
        {
            FOMOD.Steps.insert(FOMOD.Steps.begin(), merge_fomod.Steps.begin(), merge_fomod.Steps.end());
            FOMOD.RequiredFiles.insert(FOMOD.RequiredFiles.begin(), merge_fomod.RequiredFiles.begin(), merge_fomod.RequiredFiles.end());
            FOMOD.ConditionalFiles.insert(FOMOD.ConditionalFiles.begin(), merge_fomod.ConditionalFiles.begin(), merge_fomod.ConditionalFiles.end());

            while(StepsTabControl->PageCount > 1)
                StepsTabControl->Pages[1]->Free();
            while(ConiditionalFilesPageControl->PageCount > 0)
                ConiditionalFilesPageControl->Pages[0]->Free();
            RequiredFilesSrcListView->Clear();

            for(int i = 1; i < FOMOD.Steps.size(); i++)
            {
                TTabSheet *new_tab = new TTabSheet(StepsTabControl);
                new_tab->Caption = FOMOD.Steps[i].Name;
                new_tab->PageControl = StepsTabControl;
            }
            for(int i = 0; i < FOMOD.RequiredFiles.size(); i++)
            {
                TListItem *item = RequiredFilesSrcListView->Items->Add();
                item->Caption = FOMOD.RequiredFiles[i].Type;
                item->SubItems->Add(FOMOD.RequiredFiles[i].SrcPath);
                item = RequiredFilesDstListView->Items->Add();
                item->Caption = FOMOD.RequiredFiles[i].DstPath;
            }
            for(int i = 0; i < FOMOD.ConditionalFiles.size(); i++)
            {
                TTabSheet *new_tab = new TTabSheet(ConiditionalFilesPageControl);
                new_tab->Caption = "Pattern[" + IntToStr(i) + "]";
                new_tab->PageControl = ConiditionalFilesPageControl;
            }
            StepsTabControl->Pages[0]->Caption = FOMOD.Steps[0].Name;
            StepsTabControl->ActivePage = StepsTabControl->Pages[0];
            ConiditionalFilesPageControlChange(Sender);

            StepCount = FOMOD.Steps.size();
            CurrentStepIndx = StepCount-1;
            StepsTabControlChange(Sender);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RunBeforeSaveMenuClick(TObject *Sender)
{
    _TCHAR t_path[256];
    _tcscpy(t_path, Application->ExeName.c_str());
    for(int i = _tcslen(t_path); i > 0; i--)
        if( t_path[i] == _T('\\') )
        {
            t_path[i+1] = _T('\0');
            break;
        }
    _tcscat(t_path, _T("runbefore.txt"));
    FILE *fp = _tfopen(t_path, _T("r"));
    if(fp)
    {
        fclose(fp);
        ScriptForm1->ScriptMemo->Clear();
        ScriptForm1->ScriptMemo->Lines->LoadFromFile(t_path);
    }
    else
        ScriptForm1->ScriptMemo->Clear();
    ScriptForm1->Caption = GetLangText(RunBeforeSaveMenu->Name, LanguageTable);
    ScriptForm1->ShowModal();
    if(ScriptForm1->ModalResult == mrOk)
    {
        ScriptForm1->ScriptMemo->Lines->SaveToFile(t_path);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RunAfterSaveMenuClick(TObject *Sender)
{
    _TCHAR t_path[256];
    _tcscpy(t_path, Application->ExeName.c_str());
    for(int i = _tcslen(t_path); i > 0; i--)
        if( t_path[i] == _T('\\') )
        {
            t_path[i+1] = _T('\0');
            break;
        }
    _tcscat(t_path, _T("runafter.txt"));
    FILE *fp = _tfopen(t_path, _T("r"));
    if(fp)
    {
        fclose(fp);
        ScriptForm1->ScriptMemo->Clear();
        ScriptForm1->ScriptMemo->Lines->LoadFromFile(t_path);
    }
    else
        ScriptForm1->ScriptMemo->Clear();
    ScriptForm1->Caption = GetLangText(RunAfterSaveMenu->Name, LanguageTable);
    ScriptForm1->ShowModal();
    if(ScriptForm1->ModalResult == mrOk)
    {
        ScriptForm1->ScriptMemo->Lines->SaveToFile(t_path);
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitMenuClick(TObject *Sender)
{
    exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pdDefTypeComboBoxChange(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DefaultType = pdDefTypeComboBox->Text;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pdDependencyTypeComboBoxChange(TObject *Sender)
{
    pdValueLabel->Caption = GetLangText(pdValueLabel->Name + pdDependencyTypeComboBox->Text, LanguageTable);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pdOperatorComboBoxChange(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        int pattern_indx = pdPatternsPageControl->ActivePageIndex;
        if( pattern_indx > -1 )
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pattern_indx].Operator = pdOperatorComboBox->Text;

        pdPatternsPageControlChange(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pdTypeNameComboBoxChange(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        int pattern_indx = pdPatternsPageControl->ActivePageIndex;
        if( pattern_indx > -1 )
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pattern_indx].Type = pdTypeNameComboBox->Text;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pdAddButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        int patter_indx = pdPatternsPageControl->ActivePageIndex;
        if(patter_indx > -1)
        {
            CDependency new_dependency;
            new_dependency.Type = pdDependencyTypeComboBox->Text;
            new_dependency.Name = pdFileFlagNameComboBox->Text;
            new_dependency.Value = pdStateValueComboBox->Text;
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[patter_indx].Dependencies.push_back(new_dependency);

            TListItem *item = PluginDependenciesListView->Items->Add();
            item->Caption = pdDependencyTypeComboBox->Text;
            item->SubItems->Add(pdFileFlagNameComboBox->Text);
            item->SubItems->Add(pdStateValueComboBox->Text);
            item->SubItems->Add(pdOperatorComboBox->Text);



            _TCHAR tstr[512];
            vector<UnicodeString> itemslist;
            UnicodeString token1;
            bool exist;
            _tcscpy(tstr, pdFileFlagNameComboBox->Items[0].Text.c_str());
            for(int i = 0; i < _tcslen(tstr); i++)
                if(tstr[i] != _T('\r') && tstr[i] != _T('\n'))
                    token1 = token1 + tstr[i];
                else
                    if(token1 != "")
                    {
                        itemslist.push_back(token1);
                        token1 = "";
                    }
            for(int i = 0; i < itemslist.size(); i++)
                if(itemslist[i] == pdFileFlagNameComboBox->Text)
                {
                    exist = true;
                    break;
                }
            if(!exist)
                pdFileFlagNameComboBox->Items->Add(pdFileFlagNameComboBox->Text);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pdNewPatternButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        CDependencyPattern new_pattern;
        new_pattern.Operator = pdOperatorComboBox->Text;
        new_pattern.Type = pdTypeNameComboBox->Text;
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns.push_back(new_pattern);

        TTabSheet *new_tab = new TTabSheet(pdPatternsPageControl);
        new_tab->Caption = "Pattern[" + IntToStr(int(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns.size()-1)) + "]";
        new_tab->PageControl = pdPatternsPageControl;
        pdPatternsPageControl->ActivePage = new_tab;
        pdPatternsPageControlChange(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pdPatternsPageControlChange(TObject *Sender)
{
    PluginDependenciesListView->Clear();
    if(pdPatternsPageControl->PageCount == 0)
        pdDeletePatternButton->Enabled = false;
    else
        pdDeletePatternButton->Enabled = true;
    pdDependencyTypeComboBox->Enabled = false;
    pdFileFlagNameComboBox->Enabled = false;
    pdStateValueComboBox->Enabled = false;
    pdDeleteButton->Enabled = false;
    pdAddButton->Enabled = false;

    if(    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0
        && PluginListView->ItemIndex > -1 )
    {

        int pattern_indx = pdPatternsPageControl->ActivePageIndex;
        if(pattern_indx > -1)
        {
            for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pattern_indx].Dependencies.size(); i++)
            {
                TListItem *item = PluginDependenciesListView->Items->Add();
                item->Caption = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pattern_indx].Dependencies[i].Type;
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pattern_indx].Dependencies[i].Name);
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pattern_indx].Dependencies[i].Value);
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pattern_indx].Operator);
            }
            pdOperatorComboBox->Text = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pattern_indx].Operator;
            pdTypeNameComboBox->Text = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pattern_indx].Type;

            pdDependencyTypeComboBox->Enabled = true;
            pdFileFlagNameComboBox->Enabled = true;
            pdStateValueComboBox->Enabled = true;
            pdAddButton->Enabled = true;
        }
        PluginDependenciesListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pdDeletePatternButtonClick(TObject *Sender)
{
    if(    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0
        && PluginListView->ItemIndex > -1 )
    {
        int pattern_indx = pdPatternsPageControl->ActivePageIndex;
        if(pattern_indx > -1)
        {
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns.erase(
                FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns.begin()+pattern_indx);
            pdPatternsPageControl->Pages[pattern_indx]->Free();

            pdPatternsPageControlChange(Sender);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pdDeleteButtonClick(TObject *Sender)
{
    if(PluginDependenciesListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pdPatternsPageControl->ActivePageIndex].Dependencies.erase(
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[pdPatternsPageControl->ActivePageIndex].Dependencies.begin()+PluginDependenciesListView->ItemIndex);
        PluginDependenciesListView->Items->Delete(PluginDependenciesListView->ItemIndex);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginDependenciesListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    if(PluginDependenciesListView->ItemIndex > -1)
        pdDeleteButton->Enabled = true;
    else
        pdDeleteButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditListElementCMenuClick(TObject *Sender)
{
    TListView *clicked_list = static_cast<TListView*>(PopupMenu->PopupComponent);
    if(clicked_list->ItemIndex > -1)
        ListView_EditLabel(clicked_list->Handle, clicked_list->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PopupMenuPopup(TObject *Sender)
{
    TListView *clicked_list = static_cast<TListView*>(PopupMenu->PopupComponent);
    if(clicked_list->ItemIndex > -1)
        EditListElementCMenu->Enabled = true;
    else
        EditListElementCMenu->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormResize(TObject *Sender)
{
    if(ScrollBox1->Height > 0)
        GroupsGroupBox->Height = ScrollBox1->Height * 0.715;
    if(FilesPanel->ClientHeight - SrcFilesListView->Top - 10 > 0)
    {
        SrcFilesListView->Height = FilesPanel->ClientHeight - SrcFilesListView->Top - 10;
        DstFilesListView->Height = FilesPanel->ClientHeight - DstFilesListView->Top - 10;
    }
    if(Panel11->ClientHeight - RequiredFilesSrcListView->Top - 10 > 0)
    {
        RequiredFilesSrcListView->Height = Panel11->ClientHeight - RequiredFilesSrcListView->Top - 10;
        RequiredFilesDstListView->Height = Panel11->ClientHeight - RequiredFilesDstListView->Top - 10;
    }
    if(Panel15->ClientHeight - CondFilesSrcListView->Top - 10 > 0)
    {
        CondFilesSrcListView->Height = Panel15->ClientHeight - CondFilesSrcListView->Top - 10;
        CondFilesDstListView->Height = Panel15->ClientHeight - CondFilesSrcListView->Top - 10;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VisibilityTypeComboBoxChange(TObject *Sender)
{
    equalsLabel->Caption = GetLangText(equalsLabel->Name + VisibilityTypeComboBox->Text, LanguageTable);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::AddRequiredFileButtonClick(TObject *Sender)
{
    if(RootDirectory != "")
    {
        OpenDialog->Filter = "";
        if(OpenDialog->Execute())
        {
            UnicodeString temp = OpenFolderDialog->FileName.SubString(0, RootDirectory.Length()).UpperCase();
            if(!(temp.Compare(RootDirectory.UpperCase())))
            {
                UnicodeString
                    src_path,
                    dst_path;

                src_path = OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2);
                dst_path = getProperDestinationPath(src_path);

                TListItem *item = RequiredFilesSrcListView->Items->Add();
                item->Caption = "file";
                item->SubItems->Add(src_path);
                item = RequiredFilesDstListView->Items->Add();
                item->Caption = dst_path;

                CFile new_file;
                new_file.Type = "file";
                new_file.SrcPath = src_path;
                new_file.DstPath = dst_path;
                FOMOD.RequiredFiles.push_back(new_file);
            }
            else
            {
                MessageBox(NULL, _T("File is out of root directory"), _T("FOMOD Creation Tool"),  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddRequiredFolderButtonClick(TObject *Sender)
{
    if(RootDirectory != "")
    {
        if(OpenFolderDialog->Execute())
        {
            UnicodeString temp = OpenFolderDialog->FileName.SubString(0, RootDirectory.Length()).UpperCase();
            if(!(temp.Compare(RootDirectory.UpperCase())))
            {
                UnicodeString
                    src_path,
                    dst_path;

                src_path = OpenFolderDialog->FileName.SubString(RootDirectory.Length()+2, OpenFolderDialog->FileName.Length()-RootDirectory.Length()+2);
                dst_path = getProperDestinationPath(src_path);

                TListItem *item = RequiredFilesSrcListView->Items->Add();
                item->Caption = "folder";
                item->SubItems->Add(src_path);
                item = RequiredFilesDstListView->Items->Add();
                item->Caption = dst_path;

                CFile new_file;
                new_file.Type = "folder";
                new_file.SrcPath = src_path;
                new_file.DstPath = dst_path;
                FOMOD.RequiredFiles.push_back(new_file);
            }
            else
            {
                MessageBox(NULL, _T("Folder is out of root directory"), _T("FOMOD Creation Tool"),  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RequiredFilesSrcListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    RequiredFilesDstListView->ItemIndex = RequiredFilesSrcListView->ItemIndex;
    if(RequiredFilesSrcListView->ItemIndex > -1)
    {
        ListView_EnsureVisible(RequiredFilesDstListView->Handle, RequiredFilesSrcListView->ItemIndex, false);
        RemoveRequiredFileFolderButton->Enabled = true;
    }
    else
        RemoveRequiredFileFolderButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RequiredFilesDstListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    RequiredFilesSrcListView->ItemIndex = RequiredFilesDstListView->ItemIndex;
    if(RequiredFilesSrcListView->ItemIndex > -1)
    {
        ListView_EnsureVisible(RequiredFilesSrcListView->Handle, RequiredFilesDstListView->ItemIndex, false);
        RemoveRequiredFileFolderButton->Enabled = true;
    }
    else
        RemoveRequiredFileFolderButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemoveRequiredFileFolderButtonClick(TObject *Sender)
{
    if(RequiredFilesSrcListView->ItemIndex > -1)
    {
        int ind = RequiredFilesSrcListView->ItemIndex;
        FOMOD.RequiredFiles.erase(FOMOD.RequiredFiles.begin()+ind);
        RequiredFilesSrcListView->ItemIndex = -1;
        RequiredFilesDstListView->ItemIndex = -1;
        RequiredFilesDstListView->Items->Delete(ind);
        RequiredFilesSrcListView->Items->Delete(ind);
        if( ind < RequiredFilesSrcListView->Items->Count-1 )
        {
            RequiredFilesSrcListView->ItemIndex = ind;
            RequiredFilesDstListView->ItemIndex = ind;
        }
        else if( ind >= RequiredFilesSrcListView->Items->Count-1)
        {
            RequiredFilesSrcListView->ItemIndex = RequiredFilesSrcListView->Items->Count-1;
            RequiredFilesDstListView->ItemIndex = RequiredFilesSrcListView->Items->Count-1;
        }
        RequiredFilesSrcListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RequiredFilesDstListViewEdited(TObject *Sender, TListItem *Item,
          UnicodeString &S)
{
    FOMOD.RequiredFiles[RequiredFilesSrcListView->ItemIndex].DstPath = S;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CondFileDependTypeComboBoxChange(TObject *Sender)
{
    ciValueLabel->Caption = GetLangText(ciValueLabel->Name + CondFileDependTypeComboBox->Text, LanguageTable);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ConiditionalFilesPageControlChange(TObject *Sender)
{
    CondFilePatternListView->Clear();
    CondFilesSrcListView->Clear();
    CondFilesDstListView->Clear();
    if(ConiditionalFilesPageControl->PageCount == 0)
        RemoveCondFilePatternButton->Enabled = false;
    else
        RemoveCondFilePatternButton->Enabled = true;
    CondFileDependTypeComboBox->Enabled = false;
    CondFileDependNameComboBox->Enabled = false;
    CondFileDependValueComboBox->Enabled = false;
    CondFilePatternOperatorComboBox->Enabled = false;
    RemoveCondFileConditionButton->Enabled = false;
    AddCondFileConditionButton->Enabled = false;
    CondFileAddFileButton->Enabled = false;
    CondFileAddFolderButton->Enabled = false;
    CondFileRemoveFileFolderButton->Enabled = false;
    MoveLeftCondFilePatternButton->Enabled = false;
    MoveRightCondFilePatternButton->Enabled = false;

    if( FOMOD.ConditionalFiles.size() > 0 )
    {
        int pattern_indx = ConiditionalFilesPageControl->ActivePageIndex;
        if(pattern_indx > -1)
        {
            for(int i = 0; i < FOMOD.ConditionalFiles[pattern_indx].Dependencies.size(); i++)
            {
                TListItem *item = CondFilePatternListView->Items->Add();
                item->Caption = FOMOD.ConditionalFiles[pattern_indx].Dependencies[i].Type;
                item->SubItems->Add(FOMOD.ConditionalFiles[pattern_indx].Dependencies[i].Name);
                item->SubItems->Add(FOMOD.ConditionalFiles[pattern_indx].Dependencies[i].Value);
                item->SubItems->Add(FOMOD.ConditionalFiles[pattern_indx].Operator);
            }
            for(int i = 0; i < FOMOD.ConditionalFiles[pattern_indx].Files.size(); i++)
            {
                TListItem *item = CondFilesSrcListView->Items->Add();
                item->Caption = FOMOD.ConditionalFiles[pattern_indx].Files[i].Type;
                item->SubItems->Add(FOMOD.ConditionalFiles[pattern_indx].Files[i].SrcPath);

                item = CondFilesDstListView->Items->Add();
                item->Caption = FOMOD.ConditionalFiles[pattern_indx].Files[i].DstPath;
            }
            CondFilePatternOperatorComboBox->Text = FOMOD.ConditionalFiles[pattern_indx].Operator;

            CondFileDependTypeComboBox->Enabled = true;
            CondFileDependNameComboBox->Enabled = true;
            CondFileDependValueComboBox->Enabled = true;
            CondFilePatternOperatorComboBox->Enabled = true;
            AddCondFileConditionButton->Enabled = true;
            CondFileAddFileButton->Enabled = true;
            CondFileAddFolderButton->Enabled = true;
        }
        if(pattern_indx > 0)
            MoveLeftCondFilePatternButton->Enabled = true;
        if(pattern_indx < ConiditionalFilesPageControl->PageCount - 1)
            MoveRightCondFilePatternButton->Enabled = true;

        CondFilePatternListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CondFilePatternListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    if(CondFilePatternListView->ItemIndex > -1)
        RemoveCondFileConditionButton->Enabled = true;
    else
        RemoveCondFileConditionButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddCondFilePatternButtonClick(TObject *Sender)
{
    CConditionalFile new_conditionalFile;
    new_conditionalFile.Operator = CondFilePatternOperatorComboBox->Text;
    FOMOD.ConditionalFiles.push_back(new_conditionalFile);

    TTabSheet *new_tab = new TTabSheet(ConiditionalFilesPageControl);
    new_tab->Caption = "Pattern[" + IntToStr(int(FOMOD.ConditionalFiles.size()-1)) + "]";
    new_tab->PageControl = ConiditionalFilesPageControl;
    ConiditionalFilesPageControl->ActivePage = new_tab;
    ConiditionalFilesPageControlChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemoveCondFilePatternButtonClick(TObject *Sender)
{
    if( FOMOD.ConditionalFiles.size() > 0 )
    {
        int pattern_indx = ConiditionalFilesPageControl->ActivePageIndex;
        if(pattern_indx > -1)
        {
            FOMOD.ConditionalFiles.erase(FOMOD.ConditionalFiles.begin()+pattern_indx);
            ConiditionalFilesPageControl->Pages[pattern_indx]->Free();

            ConiditionalFilesPageControlChange(Sender);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MoveLeftCondFilePatternButtonClick(TObject *Sender)
{
    int pattern_indx = ConiditionalFilesPageControl->ActivePageIndex;
    std::iter_swap(FOMOD.ConditionalFiles.begin()+pattern_indx,
                    FOMOD.ConditionalFiles.begin()+pattern_indx-1);
    pattern_indx--;
    ConiditionalFilesPageControl->ActivePage = ConiditionalFilesPageControl->Pages[pattern_indx];
    if(pattern_indx == 0)
        MoveLeftCondFilePatternButton->Enabled = false;
    MoveRightCondFilePatternButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MoveRightCondFilePatternButtonClick(TObject *Sender)
{
    int pattern_indx = ConiditionalFilesPageControl->ActivePageIndex;
    std::iter_swap(FOMOD.ConditionalFiles.begin()+pattern_indx,
                    FOMOD.ConditionalFiles.begin()+pattern_indx+1);
    pattern_indx++;
    ConiditionalFilesPageControl->ActivePage = ConiditionalFilesPageControl->Pages[pattern_indx];
    if(pattern_indx == FOMOD.ConditionalFiles.size()-1)
        MoveRightCondFilePatternButton->Enabled = false;
    MoveLeftCondFilePatternButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CondFilesDstListViewEdited(TObject *Sender, TListItem *Item,
          UnicodeString &S)
{
    FOMOD.ConditionalFiles[ConiditionalFilesPageControl->ActivePageIndex].Files[CondFilesDstListView->ItemIndex].DstPath = S;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CondFilePatternOperatorComboBoxChange(TObject *Sender)

{
    FOMOD.ConditionalFiles[ConiditionalFilesPageControl->ActivePageIndex].Operator = CondFilePatternOperatorComboBox->Text;
    ConiditionalFilesPageControlChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CondFileAddFileButtonClick(TObject *Sender)
{
    if(RootDirectory != "")
    {
        OpenDialog->Filter = "";
        if(OpenDialog->Execute())
        {
            UnicodeString temp = OpenFolderDialog->FileName.SubString(0, RootDirectory.Length()).UpperCase();
            if(!(temp.Compare(RootDirectory.UpperCase())))
            {
                UnicodeString
                    src_path,
                    dst_path;

                src_path = OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2);
                dst_path = getProperDestinationPath(src_path);

                TListItem *item = CondFilesSrcListView->Items->Add();
                item->Caption = "file";
                item->SubItems->Add(src_path);
                item = CondFilesDstListView->Items->Add();
                item->Caption = dst_path;

                CFile new_file;
                new_file.Type = "file";
                new_file.SrcPath = src_path;
                new_file.DstPath = dst_path;
                FOMOD.ConditionalFiles[ConiditionalFilesPageControl->ActivePageIndex].Files.push_back(new_file);
            }
            else
            {
                MessageBox(NULL, _T("File is out of root directory"), _T("FOMOD Creation Tool"),  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CondFileAddFolderButtonClick(TObject *Sender)
{
    if(RootDirectory != "")
    {
        if(OpenFolderDialog->Execute())
        {
            UnicodeString temp = OpenFolderDialog->FileName.SubString(0, RootDirectory.Length()).UpperCase();
            if(!(temp.Compare(RootDirectory.UpperCase())))
            {
                UnicodeString
                    src_path,
                    dst_path;

                src_path = OpenFolderDialog->FileName.SubString(RootDirectory.Length()+2, OpenFolderDialog->FileName.Length()-RootDirectory.Length()+2);
                dst_path = getProperDestinationPath(src_path);

                TListItem *item = CondFilesSrcListView->Items->Add();
                item->Caption = "folder";
                item->SubItems->Add(src_path);
                item = CondFilesDstListView->Items->Add();
                item->Caption = dst_path;

                CFile new_file;
                new_file.Type = "folder";
                new_file.SrcPath = src_path;
                new_file.DstPath = dst_path;
                FOMOD.ConditionalFiles[ConiditionalFilesPageControl->ActivePageIndex].Files.push_back(new_file);
            }
            else
            {
                MessageBox(NULL, _T("File is out of root directory"), _T("FOMOD Creation Tool"),  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CondFileRemoveFileFolderButtonClick(TObject *Sender)
{
    if(CondFilesSrcListView->ItemIndex > -1)
    {
        int ind = CondFilesSrcListView->ItemIndex;
        FOMOD.ConditionalFiles[ConiditionalFilesPageControl->ActivePageIndex].Files.erase(
            FOMOD.ConditionalFiles[ConiditionalFilesPageControl->ActivePageIndex].Files.begin() + ind);
        CondFilesSrcListView->ItemIndex = -1;
        CondFilesDstListView->ItemIndex = -1;
        CondFilesDstListView->Items->Delete(ind);
        CondFilesSrcListView->Items->Delete(ind);
        if( ind < CondFilesSrcListView->Items->Count-1 )
        {
            CondFilesSrcListView->ItemIndex = ind;
            CondFilesDstListView->ItemIndex = ind;
        }
        else if( ind >= CondFilesSrcListView->Items->Count-1)
        {
            CondFilesSrcListView->ItemIndex = RequiredFilesSrcListView->Items->Count-1;
            CondFilesDstListView->ItemIndex = RequiredFilesSrcListView->Items->Count-1;
        }
        RequiredFilesSrcListViewSelectItem(Sender, NULL, NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CondFilesSrcListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    CondFilesDstListView->ItemIndex = CondFilesSrcListView->ItemIndex;
    if(CondFilesSrcListView->ItemIndex > -1)
    {
        ListView_EnsureVisible(CondFilesDstListView->Handle, CondFilesSrcListView->ItemIndex, false);
        CondFileRemoveFileFolderButton->Enabled = true;
    }
    else
        CondFileRemoveFileFolderButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CondFilesDstListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    CondFilesSrcListView->ItemIndex = CondFilesDstListView->ItemIndex;
    if(CondFilesDstListView->ItemIndex > -1)
    {
        ListView_EnsureVisible(CondFilesSrcListView->Handle, CondFilesDstListView->ItemIndex, false);
        CondFileRemoveFileFolderButton->Enabled = true;
    }
    else
        CondFileRemoveFileFolderButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddCondFileConditionButtonClick(TObject *Sender)
{
    if(FOMOD.ConditionalFiles.size() > 0)
    {
        int patter_indx = ConiditionalFilesPageControl->ActivePageIndex;
        if(patter_indx > -1)
        {
            CDependency new_dependency;
            new_dependency.Type = CondFileDependTypeComboBox->Text;
            new_dependency.Name = CondFileDependNameComboBox->Text;
            new_dependency.Value = CondFileDependValueComboBox->Text;
            FOMOD.ConditionalFiles[patter_indx].Dependencies.push_back(new_dependency);

            TListItem *item = CondFilePatternListView->Items->Add();
            item->Caption = CondFileDependTypeComboBox->Text;
            item->SubItems->Add(CondFileDependNameComboBox->Text);
            item->SubItems->Add(CondFileDependValueComboBox->Text);
            item->SubItems->Add(CondFilePatternOperatorComboBox->Text);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemoveCondFileConditionButtonClick(TObject *Sender)
{
    if(CondFilePatternListView->ItemIndex > -1)
    {
        FOMOD.ConditionalFiles[ConiditionalFilesPageControl->ActivePageIndex].Dependencies.erase(
            FOMOD.ConditionalFiles[ConiditionalFilesPageControl->ActivePageIndex].Dependencies.begin()+CondFilePatternListView->ItemIndex);
        CondFilePatternListView->Items->Delete(CondFilePatternListView->ItemIndex);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SettingsMenuClick(TObject *Sender)
{
    if(LoadSettings(Settings))
    {
        char search_path[200];

        SettingsForm->HideOpenFolderCheckBox->Checked = Settings.hideOpenFolder;
        SettingsForm->HideOpenFileCheckBox->Checked = Settings.hideOpenFile;
        SettingsForm->IntTextSizeComboBox->Text = Settings.interfaceTextSize;
        SettingsForm->MaxRecentEdit->Text = Settings.MaxRecentFiles;

        SettingsForm->LanguagesComboBox->Clear();
        WIN32_FIND_DATA fd;
        HANDLE hFind = ::FindFirstFile((AppPath + "\\Language\\*.txt").c_str(), &fd);
        if(hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
                {
                    SettingsForm->LanguagesComboBox->Items->Add(fd.cFileName);
                }
            }while(::FindNextFile(hFind, &fd));
            ::FindClose(hFind);
            SettingsForm->LanguagesComboBox->Text = Settings.langFile;
        }

        SettingsForm->RecentListView->Clear();
        for(int i = 0; i < Settings.RecentFiles.size(); i++)
        {
            TListItem *item = SettingsForm->RecentListView->Items->Add();
            item->Caption = Settings.RecentFiles[i];
        }
        SettingsForm->recentFiles = Settings.RecentFiles;
    }
    SettingsForm->ShowModal();
    if(SettingsForm->ModalResult == mrOk)
    {
        Settings.hideOpenFolder = SettingsForm->HideOpenFolderCheckBox->Checked;
        Settings.hideOpenFile = SettingsForm->HideOpenFileCheckBox->Checked;
        Settings.interfaceTextSize = SettingsForm->IntTextSizeComboBox->Text.ToInt();
        Settings.langFile = SettingsForm->LanguagesComboBox->Text;
        Settings.MaxRecentFiles = SettingsForm->MaxRecentEdit->Text.ToInt();
        Settings.RecentFiles = SettingsForm->recentFiles;
        ManageRecentFiles(NULL);

        SaveConfig(Settings);

        OpenMenu->Visible = !Settings.hideOpenFolder;
        OpenfileMenu->Visible = !Settings.hideOpenFile;
        MainForm->Font->Size = Settings.interfaceTextSize;
        SettingsForm->Font->Size = Settings.interfaceTextSize;
        ScriptForm1->Font->Size = Settings.interfaceTextSize;
        LoadLangugeFile(AppPath + "\\language\\" + Settings.langFile, LanguageTable);
        ApplyLanguage(MainForm, LanguageTable);
        ApplyLanguage(SettingsForm, LanguageTable);
        ApplyLanguage(ScriptForm1, LanguageTable);
        SettingsForm->Caption = GetLangText(SettingsMenu->Name, LanguageTable);

        NewMenu->Caption = GetLangText(MainForm->NewMenu->Name, LanguageTable);
        OpenMenu->Caption = GetLangText(OpenMenu->Name, LanguageTable);
        OpenfileMenu->Caption = GetLangText(OpenfileMenu->Name, LanguageTable);
        SaveMenu->Caption = GetLangText(SaveMenu->Name, LanguageTable);
        MergeFOMODMenu->Caption = GetLangText(MergeFOMODMenu->Name, LanguageTable);
        MainForm->RecentMenu->Caption = GetLangText(MainForm->RecentMenu->Name, LanguageTable);
        ExitMenu->Caption = GetLangText(ExitMenu->Name, LanguageTable);
        OptionsMenu->Caption = GetLangText(OptionsMenu->Name, LanguageTable);
        SettingsMenu->Caption = GetLangText(SettingsMenu->Name, LanguageTable);
        RunBeforeSaveMenu->Caption = GetLangText(RunBeforeSaveMenu->Name, LanguageTable);
        RunAfterSaveMenu->Caption = GetLangText(RunAfterSaveMenu->Name, LanguageTable);
        EditListElementCMenu->Caption = GetLangText(EditListElementCMenu->Name, LanguageTable);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RecentFileTemplateClick(TObject *Sender)
{
    TMenuItem *menu_item = dynamic_cast<TMenuItem *>(Sender);
    UnicodeString temp;

    bool
        module_config_xml_loaded = false,
        info_xml_loaded = false;

    NewMenuClick(Sender);

    RootDirectory = Settings.RecentFiles[menu_item->MenuIndex];
    RootDirEdit->Text = RootDirectory;

    try{
        info_xml_loaded = LoadFOMODInfoFromXML((RootDirectory+"\\fomod\\info.xml").c_str(), FOMOD);
    }
    catch(...){}
    try{
        module_config_xml_loaded = LoadFOMODFromXML((RootDirectory+"\\fomod\\ModuleConfig.xml").c_str(), FOMOD);
    }
    catch(...){}

    if(info_xml_loaded)
    {
        ModNameEdit->Text = FOMOD.Name;
        ModAuthorEdit->Text = FOMOD.AuthorName;
        ModVersionEdit->Text = FOMOD.Version;
        ModURLEdit->Text = FOMOD.URL;
        ModDesccriptionMemo->Lines->Text = FOMOD.Description;
        ModCategoryComboBox->Text = FOMOD.ModCategory;
    }
    if(module_config_xml_loaded)
    {
        for(int i = 1; i < FOMOD.Steps.size(); i++)
        {
            TTabSheet *new_tab = new TTabSheet(StepsTabControl);
            new_tab->Caption = FOMOD.Steps[i].Name;
            new_tab->PageControl = StepsTabControl;
        }
        for(int i = 0; i < FOMOD.RequiredFiles.size(); i++)
        {
            TListItem *item = RequiredFilesSrcListView->Items->Add();
            item->Caption = FOMOD.RequiredFiles[i].Type;
            item->SubItems->Add(FOMOD.RequiredFiles[i].SrcPath);
            item = RequiredFilesDstListView->Items->Add();
            item->Caption = FOMOD.RequiredFiles[i].DstPath;
        }
        for(int i = 0; i < FOMOD.ConditionalFiles.size(); i++)
        {
            TTabSheet *new_tab = new TTabSheet(ConiditionalFilesPageControl);
            new_tab->Caption = "Pattern[" + IntToStr(i) + "]";
            new_tab->PageControl = ConiditionalFilesPageControl;
        }
        StepsTabControl->Pages[0]->Caption = FOMOD.Steps[0].Name;
        StepsTabControl->ActivePage = StepsTabControl->Pages[0];
        ConiditionalFilesPageControlChange(Sender);

        ManageRecentFiles(RootDirectory);
    }


    StepCount = FOMOD.Steps.size();
    CurrentStepIndx = StepCount-1;
    StepsTabControlChange(Sender);

    StepsTabSheet->Enabled = true;
    RequiredInstallsTabSheet->Enabled = true;
    ConditionalInstallsTabSheet->Enabled = true;
    StepsTabSheet->Show();
    ProceedButton->Enabled = false;
    OpenRootDirButton->Enabled = false;
    RootDirEdit->Enabled = false;
    SaveMenu->Enabled = true;
    MergeFOMODMenu->Enabled = true;
}
//---------------------------------------------------------------------------

