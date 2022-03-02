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
#include "DataClasses.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define TEG_NONE        0x00
#define TEG_OPEN        0x01
#define TEG_CLOSE       0x02
#define TEG_WAITCLOSE   0x04
#define TEG_INNERTEXT   0x08
#define TEG_READY       0x10

#define AMB_UNDEFINED   -1
#define AMB_VISIBILITY  0
#define AMB_DIRECTTYPE  1
#define AMB_PATTERN     2

const wchar_t BOM = 0xFEFF;

TMainForm *MainForm;

CFOMOD FOMOD;
UnicodeString RootDirectory;

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

   printf( "Higher: %x\n" , dwFileVersionMS );

   printf( "Lower: %x\n" , dwFileVersionLS );

   DWORD dwLeftMost     = HIWORD(dwFileVersionMS);
   DWORD dwSecondLeft   = LOWORD(dwFileVersionMS);
   DWORD dwSecondRight  = HIWORD(dwFileVersionLS);
   DWORD dwRightMost    = LOWORD(dwFileVersionLS);

   _TCHAR str[128];

   _stprintf(str, _T("%d.%d.%d.%d\n") , dwLeftMost, dwSecondLeft,
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

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    PageControl->ActivePage = ModInfoTabSheet;
    MainForm->Caption = "FOMOD Creation Tool " + GetFileVersionOfApplication(Application->ExeName.c_str());
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
    FOMOD.ModCategory = ModCategoryEdit->Text;
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
    StepsTabSheet->TabVisible = true;
    StepsTabSheet->Show();
    ProceedButton->Enabled = false;
    OpenRootDirButton->Enabled = false;
    RootDirEdit->Enabled = false;
    SaveMenu->Enabled = true;
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

    ConditionListView->Clear();
    GroupListView->Clear();
    PluginListView->Clear();
    VaribleSetListView->Clear();
    SrcFilesListView->Clear();
    DstFilesListView->Clear();
    PluginDescriptionMemo->Clear();
    PluginImageEdit->Text = "";
    PluginImage->Picture->Bitmap = NULL;
    MoveLeftButton->Enabled = false;
    MoveRightButton->Enabled = false;

    CurrentStepIndx = StepsTabControl->ActivePageIndex;
    StepNameEdit->Text = FOMOD.Steps[CurrentStepIndx].Name;

    TotalConditionSet.clear();
    for(int step_i = 0; step_i < FOMOD.Steps.size(); step_i++)
        for(int group_j = 0; group_j < FOMOD.Steps[step_i].PluginGroups.size(); group_j++)
            for(int plugin_k = 0; plugin_k < FOMOD.Steps[step_i].PluginGroups[group_j].Plugins.size(); plugin_k++)
                for(int condition_c = 0; condition_c < FOMOD.Steps[step_i].PluginGroups[group_j].Plugins[plugin_k].ConditionSet.size(); condition_c++)
                {
                    UnicodeString condition_name = FOMOD.Steps[step_i].PluginGroups[group_j].Plugins[plugin_k].ConditionSet[condition_c].Name;
                    bool exist = false;
                    for(int i = 0; i < TotalConditionSet.size(); i++)
                        if(TotalConditionSet[i] == condition_name)
                        {
                            exist = true;
                            break;
                        }
                    if(!exist)
                        TotalConditionSet.push_back(condition_name);
                }

    ConditionComboBox->Clear();
    VaribleComboBox->Clear();
    if(TotalConditionSet.size() > 0)
    {
        for(int i = 0; i < TotalConditionSet.size(); i++)
        {
            ConditionComboBox->Items->Add(TotalConditionSet[i]);
            VaribleComboBox->Items->Add(TotalConditionSet[i]);
        }
        ConditionComboBox->ItemIndex = 0;
    }

    if(FOMOD.Steps[CurrentStepIndx].ConditionSet.size() > 0)
    {
        for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].ConditionSet.size(); i++)
        {
            TListItem *item = ConditionListView->Items->Add();
            item->Caption = FOMOD.Steps[CurrentStepIndx].ConditionSet[i].Name;
            item->SubItems->Add("==");
            item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].ConditionSet[i].Value);
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
        GroupListViewClick(Sender);
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
        item->Caption = ConditionComboBox->Text;
        item->SubItems->Add("==");
        item->SubItems->Add(ConditionValueComboBox->Text);
        item->SubItems->Add("AND");

        CCondition new_condition(ConditionComboBox->Text, ConditionValueComboBox->Text);
        FOMOD.Steps[CurrentStepIndx].ConditionSet.push_back(new_condition);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteConditionButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].ConditionSet.size() > 0 && ConditionListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].ConditionSet.erase(FOMOD.Steps[CurrentStepIndx].ConditionSet.begin()+ConditionListView->ItemIndex);
        ConditionListView->Items->Delete(ConditionListView->ItemIndex);
    }
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
        GroupListViewClick(Sender);
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
        VaribleSetListView->Clear();
        SrcFilesListView->Clear();
        DstFilesListView->Clear();
        GroupListViewClick(Sender);
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
    GroupListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GroupDownButtonClick(TObject *Sender)
{
    unsigned int temp = GroupListView->ItemIndex;
    std::iter_swap(FOMOD.Steps[CurrentStepIndx].PluginGroups.begin()+temp,
                    FOMOD.Steps[CurrentStepIndx].PluginGroups.begin()+temp+1);
    StepsTabControlChange(Sender);
    GroupListView->ItemIndex = temp + 1;
    GroupListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GroupListViewChange(TObject *Sender, TListItem *Item,
          TItemChange Change)
{
    GroupListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GroupListViewClick(TObject *Sender)
{
    PluginListView->Clear();
    VaribleSetListView->Clear();
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

    PluginListViewClick(Sender);
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
        PluginListViewClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemovePluginButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.erase(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+PluginListView->ItemIndex);
        PluginListView->Items->Delete(PluginListView->ItemIndex);
        VaribleSetListView->Clear();
        SrcFilesListView->Clear();
        DstFilesListView->Clear();
        PluginListViewClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginUpButtonClick(TObject *Sender)
{

    unsigned int temp = PluginListView->ItemIndex;
    std::iter_swap(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp,
                    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp-1);
    GroupListViewClick(Sender);
    PluginListView->ItemIndex = temp - 1;
    PluginListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginDownButtonClick(TObject *Sender)
{

    unsigned int temp = PluginListView->ItemIndex;
    std::iter_swap(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp,
                    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp+1);
    GroupListViewClick(Sender);
    PluginListView->ItemIndex = temp + 1;
    PluginListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginListViewChange(TObject *Sender, TListItem *Item,
          TItemChange Change)
{
    PluginListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginListViewClick(TObject *Sender)
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
    VaribleSetListView->Clear();
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
                TListItem *item = VaribleSetListView->Items->Add();
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
    SrcFilesListViewClick(Sender);
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

        TListItem *item = VaribleSetListView->Items->Add();
        item->Caption = VaribleComboBox->Text;
        item->SubItems->Add(" =");
        item->SubItems->Add(VaribleValueComboBox->Text);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteVaribleButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].ConditionSet.size() > 0 && VaribleSetListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].ConditionSet.erase(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].ConditionSet.begin()+VaribleSetListView->ItemIndex);
        VaribleSetListView->Items->Delete(VaribleSetListView->ItemIndex);
        VaribleSetListViewClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VaribleSetListViewChange(TObject *Sender, TListItem *Item,
          TItemChange Change)
{
    VaribleSetListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VaribleSetListViewClick(TObject *Sender)
{
    if(VaribleSetListView->ItemIndex > -1)
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
                    dst_path,
                    u_temp;

                _TCHAR t_temp[256];
                unsigned int t_len;

                src_path = dst_path = OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2);
                if(    !(dst_path.SubString(dst_path.Length()-3, 4).LowerCase().Compare(UnicodeString(".esp")))
                    || !(dst_path.SubString(dst_path.Length()-3, 4).LowerCase().Compare(UnicodeString(".esm")))  )
                {
                    _tcscpy(t_temp, dst_path.c_str());
                    for(int i = _tcslen(t_temp); i > 0; i--)
                        if( t_temp[i] == _T('\\') )
                        {
                            dst_path = &t_temp[i+1];
                            break;
                        }
                }
                else
                {
                    _tcscpy(t_temp, dst_path.c_str());
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
                                dst_path = &t_temp[start];
                                break;
                            }
                            else
                                start = i+1;
                        }
                }



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
                TListItem *item = SrcFilesListView->Items->Add();
                item->Caption = "folder";
                item->SubItems->Add(OpenFolderDialog->FileName.SubString(RootDirectory.Length()+2, OpenFolderDialog->FileName.Length()-RootDirectory.Length()+2));
                item = DstFilesListView->Items->Add();
                item->Caption = OpenFolderDialog->FileName.SubString(RootDirectory.Length()+2, OpenFolderDialog->FileName.Length()-RootDirectory.Length()+2);

                CFile new_file;
                new_file.Type = "folder";
                new_file.SrcPath = OpenFolderDialog->FileName.SubString(RootDirectory.Length()+2, OpenFolderDialog->FileName.Length()-RootDirectory.Length()+2);
                new_file.DstPath = OpenFolderDialog->FileName.SubString(RootDirectory.Length()+2, OpenFolderDialog->FileName.Length()-RootDirectory.Length()+2);
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
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Files.erase(
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].Files.begin()+
            SrcFilesListView->ItemIndex);
        DstFilesListView->Items->Delete(SrcFilesListView->ItemIndex);
        SrcFilesListView->Items->Delete(SrcFilesListView->ItemIndex);
        SrcFilesListViewClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SrcFilesListViewChange(TObject *Sender, TListItem *Item,
          TItemChange Change)
{
    SrcFilesListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SrcFilesListViewClick(TObject *Sender)
{
    if(SrcFilesListView->ItemIndex > -1)
        RemoveFileFolderButton->Enabled = true;
    else
        RemoveFileFolderButton->Enabled = false;
    DstFilesListView->ItemIndex = SrcFilesListView->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DstFilesListViewChange(TObject *Sender, TListItem *Item,
          TItemChange Change)
{
    DstFilesListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DstFilesListViewClick(TObject *Sender)
{
    if(DstFilesListView->ItemIndex > -1)
        RemoveFileFolderButton->Enabled = true;
    else
        RemoveFileFolderButton->Enabled = false;
    SrcFilesListView->ItemIndex = DstFilesListView->ItemIndex;
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

        _ftprintf(fpModuleConfigxml, _T("<!-- Created with FOMOD Creation Tool [%s] --> \n"), _T("http://www.nexusmods.com/fallout4/mods/6821"));

        _ftprintf(fpModuleConfigxml, _T("<config xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://qconsulting.ca/fo3/ModConfig5.0.xsd\"> \n"));
        _ftprintf(fpModuleConfigxml, _T("\t<moduleName>%s</moduleName> \n"), temp_fomod.Name.c_str());

        _ftprintf(fpModuleConfigxml, _T("\t<installSteps order=\"Explicit\"> \n"));
        for(int step_i = 0; step_i < temp_fomod.Steps.size(); step_i++)
        {
            _ftprintf(fpModuleConfigxml, _T("\t\t<installStep name=\"%s\"> \n"), temp_fomod.Steps[step_i].Name.c_str());
            if(temp_fomod.Steps[step_i].ConditionSet.size() > 0)
            {
                _ftprintf(fpModuleConfigxml, _T("\t\t\t<visible> \n"));
                for(int i = 0; i < temp_fomod.Steps[step_i].ConditionSet.size(); i++)
                    _ftprintf(fpModuleConfigxml, _T("\t\t\t\t<flagDependency flag=\"%s\" value=\"%s\" /> \n"),
                        temp_fomod.Steps[step_i].ConditionSet[i].Name.c_str(),
                        temp_fomod.Steps[step_i].ConditionSet[i].Value.c_str());
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

void __fastcall TMainForm::OpenMenuClick(TObject *Sender)
{
    if(OpenFolderDialog->Execute())
    {
        if(dirExists(OpenFolderDialog->FileName + "\\fomod"))
        {
            bool module_config_xml_loaded = false;
            unsigned int fsize;

            _TCHAR
                *t_str, *t_str_p;
            UnicodeString
                teginner;
            UnicodeString
                tegname;
            vector < pair<UnicodeString, UnicodeString> > tegprops;

            int state = 0;

            NewMenuClick(Sender);
            RootDirEdit->Text = OpenFolderDialog->FileName;
            RootDirectory = OpenFolderDialog->FileName;

            FILE *fpinfoxml = _tfopen((RootDirectory+"\\fomod\\info.xml").c_str(), _T("rb"));
            if(fpinfoxml)
            {
                fseek(fpinfoxml, 0, SEEK_END);
                fsize = ftell (fpinfoxml);
                rewind(fpinfoxml);
                t_str = new _TCHAR [(fsize/sizeof(_TCHAR))+1];
                fread(t_str, sizeof(_TCHAR), fsize/sizeof(_TCHAR), fpinfoxml);
                t_str[fsize] = _T('\0');

                t_str_p = ParseXMLString(t_str, tegname, teginner, tegprops, state);
                while( *t_str_p != _T('\0') )
                {
                    if( state == TEG_READY )
                    {
                        UnicodeString tegname_l = tegname.LowerCase();
                        if(tegname_l == "name")
                            FOMOD.Name = teginner;
                        if(tegname_l == "author")
                            FOMOD.AuthorName = teginner;
                        if(tegname_l == "version")
                            FOMOD.Version = teginner;
                        if(tegname_l == "website")
                            FOMOD.URL = teginner;
                        if(tegname_l == "description")
                            FOMOD.Description = teginner;
                        if(tegname_l == "element")
                            FOMOD.ModCategory = teginner;
                        tegname = "";
                    }
                    state = TEG_NONE;
                    t_str_p = ParseXMLString(t_str_p, tegname, teginner, tegprops, state);
                }
                fclose(fpinfoxml);
                delete [] t_str;
            }
            ModNameEdit->Text = FOMOD.Name;
            ModAuthorEdit->Text = FOMOD.AuthorName;
            ModVersionEdit->Text = FOMOD.Version;
            ModURLEdit->Text = FOMOD.URL;
            ModDesccriptionMemo->Lines->Text = FOMOD.Description;
            ModCategoryEdit->Text = FOMOD.ModCategory;


            FILE *fpModuleConfigxml = _tfopen((RootDirectory+"\\fomod\\ModuleConfig.xml").c_str(), _T("rb"));
            if(fpModuleConfigxml)
            {
                fseek(fpModuleConfigxml, 0, SEEK_END);
                fsize = ftell (fpModuleConfigxml);
                rewind(fpModuleConfigxml);
                t_str = new _TCHAR [(fsize/sizeof(_TCHAR))+1];
                fread(t_str, sizeof(_TCHAR), fsize/sizeof(_TCHAR), fpModuleConfigxml);
                t_str[(fsize/sizeof(_TCHAR))] = _T('\0');


                int ambiguity = AMB_UNDEFINED;
                int curr_step = -1;
                int curr_group = -1;
                int curr_plugin = -1;
                int curr_pattern = -1;
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
                            FOMOD.Steps.push_back(new_step);
                            curr_step = FOMOD.Steps.size()-1;
                        }
                        if(tegname_l == "flagdependency")
                        {
                            if(ambiguity == AMB_VISIBILITY)
                            {
                                if(curr_step > -1)
                                {
                                    if(tegprops.size() > 1)
                                    {
                                        CCondition new_condition;
                                        new_condition.Name = tegprops[0].second;
                                        if(tegprops[1].second == NULL)
                                            new_condition.Value = "";
                                        else
                                            new_condition.Value = tegprops[1].second;
                                        FOMOD.Steps[curr_step].ConditionSet.push_back(new_condition);
                                    }
                                }
                            }
                            else if(ambiguity == AMB_PATTERN)
                            {
                                if(curr_step > -1)
                                {
                                    if(tegprops.size() > 1)
                                    {
                                        CDependency new_dependency;
                                        new_dependency.Type = _T("flag");
                                        new_dependency.Name = tegprops[0].second;
                                        if(tegprops[1].second == NULL)
                                            new_dependency.Value = "";
                                        else
                                            new_dependency.Value = tegprops[1].second;
                                        FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns[curr_pattern].Dependencies.push_back(new_dependency);
                                    }
                                }
                            }
                        }
                        if(tegname_l == "filedependency")
                        {
                            if(ambiguity == AMB_PATTERN)
                            {
                                if(curr_step > -1)
                                {
                                    if(tegprops.size() > 1)
                                    {
                                        CDependency new_dependency;
                                        new_dependency.Type = _T("file");
                                        new_dependency.Name = tegprops[0].second;
                                        new_dependency.Value = tegprops[1].second;
                                        FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns[curr_pattern].Dependencies.push_back(new_dependency);
                                    }
                                }
                            }
                        }
                        if(tegname_l == "type")
                        {
                            if(ambiguity == AMB_DIRECTTYPE)
                            {
                                if(curr_step > -1)
                                {
                                    if(tegprops.size() > 0)
                                    {
                                        FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DefaultType = tegprops[0].second;
                                    }
                                }
                            }
                            else if(ambiguity == AMB_PATTERN)
                            {
                                if(curr_step > -1)
                                {
                                    if(tegprops.size() > 0)
                                    {
                                        FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns[curr_pattern].Type = tegprops[0].second;
                                    }
                                }
                            }
                        }
                        if(tegname_l == "dependencies")
                        {
                            if(curr_step > -1)
                            {
                                if(tegprops.size() > 0)
                                {
                                    FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns[curr_pattern].Operator = tegprops[0].second;
                                }
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
                                    FOMOD.Steps[curr_step].PluginGroups.push_back(new_group);
                                    curr_group = FOMOD.Steps[curr_step].PluginGroups.size()-1;
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
                                    FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins.push_back(new_plugin);
                                    curr_plugin = FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins.size()-1;
                                }
                            }
                        }
                        if(tegname_l == "description")
                        {
                            if(curr_step > -1 && curr_group > -1 && curr_plugin > -1 && teginner != _T("\n"))
                                if(FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Description == "")
                                    FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Description = teginner;
                                else
                                    FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Description =
                                    FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Description + teginner;
                        }
                        if(tegname_l == "image")
                        {
                            if(curr_step > -1 && curr_group > -1 && curr_plugin > -1)
                                if(tegprops.size() > 0)
                                    FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].ImagePath = tegprops[0].second;
                        }
                        if(tegname_l == "flag")
                        {
                            if(curr_step > -1 && curr_group > -1 && curr_plugin > -1)
                            {
                                CCondition new_var;
                                if(tegprops.size() > 0)
                                    new_var.Name = tegprops[0].second;
                                new_var.Value = teginner;
                                FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].ConditionSet.push_back(new_var);
                            }
                        }
                        if(tegname_l == "file")
                        {
                            if(curr_step > -1 && curr_group > -1 && curr_plugin > -1)
                            {
                                CFile new_file;
                                new_file.Type = "file";
                                if(tegprops.size() > 1)
                                {
                                    new_file.SrcPath = tegprops[0].second;
                                    new_file.DstPath = tegprops[1].second;
                                }
                                FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Files.push_back(new_file);
                            }
                        }
                        if(tegname_l == "folder")
                        {
                            if(curr_step > -1 && curr_group > -1 && curr_plugin > -1)
                            {
                                CFile new_file;
                                new_file.Type = "folder";
                                if(tegprops.size() > 1)
                                {
                                    new_file.SrcPath = tegprops[0].second;
                                    new_file.DstPath = tegprops[1].second;
                                }
                                FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].Files.push_back(new_file);
                            }
                        }
                        if(tegname_l == "visible")
                        {
                            ambiguity = AMB_VISIBILITY;
                        }
                        if(tegname_l == "typedescriptor")
                        {
                            ambiguity = AMB_DIRECTTYPE;
                        }
                        if(tegname_l == "pattern")
                        {
                            CDependencyPattern tdp;
                            FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns.push_back(tdp);
                            curr_pattern = FOMOD.Steps[curr_step].PluginGroups[curr_group].Plugins[curr_plugin].DependencyPatterns.size()-1;
                            ambiguity = AMB_PATTERN;
                        }
                    }
                    state = TEG_NONE;
                    t_str_p = ParseXMLString(t_str_p, tegname, teginner, tegprops, state);
                }
                module_config_xml_loaded = true;
                fclose(fpModuleConfigxml);
                delete [] t_str;
            }


            if(module_config_xml_loaded)
            {
                for(int i = 1; i < FOMOD.Steps.size(); i++)
                {
                    TTabSheet *new_tab = new TTabSheet(StepsTabControl);
                    new_tab->Caption = FOMOD.Steps[i].Name;
                    new_tab->PageControl = StepsTabControl;
                }
                StepsTabControl->Pages[0]->Caption = FOMOD.Steps[0].Name;
                StepsTabControl->ActivePage = StepsTabControl->Pages[0];
            }

            StepCount = FOMOD.Steps.size();
            CurrentStepIndx = StepCount-1;
            StepsTabControlChange(Sender);

            StepsTabSheet->TabVisible = true;
            StepsTabSheet->Show();
            ProceedButton->Enabled = false;
            OpenRootDirButton->Enabled = false;
            RootDirEdit->Enabled = false;
            SaveMenu->Enabled = true;
        }
        else
        {
            MessageBox(NULL, _T("There is no 'fomod' catalog in specified directory. Choose root directory containing 'fomod' folder."), _T("FOMOD Creation Tool"), MB_OK);
        }
    }
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
    FOMOD.Steps.clear();
    StepCount = FOMOD.Steps.size();
    CurrentStepIndx = 0;

    StepsTabSheet->TabVisible = false;
    ModInfoTabSheet->Show();
    while(StepsTabControl->PageCount > 1)
        StepsTabControl->Pages[1]->Free();
    ModNameEdit->Text = "";
    ModAuthorEdit->Text = "";
    ModVersionEdit->Text = "";
    ModURLEdit->Text = "";
    ModCategoryEdit->Text = "";
    ModDesccriptionMemo->Text = "";
    ProceedButton->Enabled = true;
    OpenRootDirButton->Enabled = true;
    RootDirEdit->Enabled = true;
    RootDirEdit->Text = "";
    SaveMenu->Enabled = false;
    DeleteStepButton->Enabled = false;
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
    ScriptForm1->Caption = "Run commands before save";
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
    ScriptForm1->Caption = "Run commands after save";
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
    if(pdDependencyTypeComboBox->Text == "file")
        Label12->Caption = "State";
    else if(pdDependencyTypeComboBox->Text == "flag")
        Label12->Caption = "Value";
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
            new_dependency.Name = pdFileFlagNameEdit->Text;
            new_dependency.Value = pdStateValueComboBox->Text;
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns[patter_indx].Dependencies.push_back(new_dependency);

            TListItem *item = PluginDependenciesListView->Items->Add();
            item->Caption = pdDependencyTypeComboBox->Text;
            item->SubItems->Add(pdFileFlagNameEdit->Text);
            item->SubItems->Add(pdStateValueComboBox->Text);
            item->SubItems->Add(pdOperatorComboBox->Text);
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
    pdFileFlagNameEdit->Enabled = false;
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
            pdFileFlagNameEdit->Enabled = true;
            pdStateValueComboBox->Enabled = true;
            pdAddButton->Enabled = true;
        }
        PluginDependenciesListViewClick(Sender);
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
            PluginDependenciesListView->Clear();
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns.erase(
                FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListView->ItemIndex].DependencyPatterns.begin()+pattern_indx);
            pdPatternsPageControl->Pages[pattern_indx]->Free();
            if(pdPatternsPageControl->PageCount == 0)
                pdDeletePatternButton->Enabled = false;
            else
                pdDeletePatternButton->Enabled = true;

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

void __fastcall TMainForm::PluginDependenciesListViewChange(TObject *Sender, TListItem *Item,
          TItemChange Change)
{
    PluginDependenciesListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginDependenciesListViewClick(TObject *Sender)
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

