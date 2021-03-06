//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <jpeg.hpp>
#pragma hdrstop

#include "SplashScreen.h"
#include "main.h"
#include "ScriptForm.h"
#include "SettingsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSplashForm *SplashForm;

extern TSettings Settings;
extern std::vector <TLanguagePair> LanguageTable;
extern UnicodeString AppPath;
extern bool LoadSettings(TSettings &settings);
extern void LoadLangugeFile(UnicodeString filename, std::vector <TLanguagePair> &table);
extern UnicodeString GetLangText(UnicodeString key, std::vector <TLanguagePair> &table);
extern void ApplyLanguage(TWinControl *container, std::vector <TLanguagePair> &table);
//---------------------------------------------------------------------------
__fastcall TSplashForm::TSplashForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSplashForm::Timer1Timer(TObject *Sender)
{
    static int secCount = 0;
    Timer1->Enabled = false;
    if(secCount == 0)
    {
        Label1->Caption = "Loading... config.ini";
        Label1->Refresh();
        if(LoadSettings(Settings))
        {
            MainForm->OpenMenu->Visible = !Settings.hideOpenFolder;
            MainForm->OpenfileMenu->Visible = !Settings.hideOpenFile;
            MainForm->Font->Size = Settings.interfaceTextSize;
            SettingsForm->Font->Size = Settings.interfaceTextSize;
            ScriptForm1->Font->Size = Settings.interfaceTextSize;
            Label1->Caption = "Loading... " + Settings.langFile;
            Label1->Refresh();
            LoadLangugeFile(AppPath + "\\language\\" + Settings.langFile, LanguageTable);
            ApplyLanguage(MainForm, LanguageTable);
            ApplyLanguage(SettingsForm, LanguageTable);
            ApplyLanguage(ScriptForm1, LanguageTable);
            SettingsForm->Caption = GetLangText(MainForm->SettingsMenu->Name, LanguageTable);

            MainForm->NewMenu->Caption = GetLangText(MainForm->NewMenu->Name, LanguageTable);
            MainForm->OpenMenu->Caption = GetLangText(MainForm->OpenMenu->Name, LanguageTable);
            MainForm->OpenfileMenu->Caption = GetLangText(MainForm->OpenfileMenu->Name, LanguageTable);
            MainForm->SaveMenu->Caption = GetLangText(MainForm->SaveMenu->Name, LanguageTable);
            MainForm->MergeFOMODMenu->Caption = GetLangText(MainForm->MergeFOMODMenu->Name, LanguageTable);
            MainForm->RecentMenu->Caption = GetLangText(MainForm->RecentMenu->Name, LanguageTable);
            MainForm->ExitMenu->Caption = GetLangText(MainForm->ExitMenu->Name, LanguageTable);
            MainForm->OptionsMenu->Caption = GetLangText(MainForm->OptionsMenu->Name, LanguageTable);
            MainForm->SettingsMenu->Caption = GetLangText(MainForm->SettingsMenu->Name, LanguageTable);
            MainForm->RunBeforeSaveMenu->Caption = GetLangText(MainForm->RunBeforeSaveMenu->Name, LanguageTable);
            MainForm->RunAfterSaveMenu->Caption = GetLangText(MainForm->RunAfterSaveMenu->Name, LanguageTable);
            MainForm->EditListElementCMenu->Caption = GetLangText(MainForm->EditListElementCMenu->Name, LanguageTable);

            for(int i = 0; i < Settings.RecentFiles.size(); i++)
            {
                TMenuItem *new_recent = new TMenuItem(MainForm->RecentMenu);
                new_recent->Caption = Settings.RecentFiles[i];
                new_recent->OnClick = MainForm->RecentFileTemplate->OnClick;
                MainForm->RecentMenu->Insert(i, new_recent);
            }
        }
    }
    secCount++;
    if(secCount >= Settings.splashScreenSeconds)
    {
		Hide();
        MainForm->Show();
    }
    else
    {
        Label1->Caption = "Loading...";
        Timer1->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TSplashForm::FormCreate(TObject *Sender)
{
	Application->MainFormOnTaskBar = false;
	DWORD dwExStyle = GetWindowLong(Application->Handle, GWL_EXSTYLE);
    dwExStyle &= ~WS_EX_APPWINDOW;
    dwExStyle |= WS_EX_TOOLWINDOW;
	SetWindowLong(Application->Handle, GWL_EXSTYLE, dwExStyle);
	FILE *fp = fopen("logo.jpg", "r");
	if(fp)
	{
		fclose(fp);
		TJPEGImage *jpg = new TJPEGImage;
		jpg->LoadFromFile("logo.jpg");
		LogoImage->Picture->Bitmap->Assign(jpg);
		delete jpg;
		SplashForm->Height = LogoImage->Height;
		SplashForm->Width = LogoImage->Width;
	}
}
//---------------------------------------------------------------------------

void __fastcall TSplashForm::CreateParams(TCreateParams &Params)
{
    TForm::CreateParams(Params);
    Params.ExStyle &= ~WS_EX_APPWINDOW;
    Params.ExStyle |= WS_EX_TOOLWINDOW;
}
//---------------------------------------------------------------------------

void __fastcall TSplashForm::FormActivate(TObject *Sender)
{
	ShowWindow(Application->Handle, SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TSplashForm::FormShow(TObject *Sender)
{
	ShowWindow(Application->Handle, SW_HIDE);
}
//---------------------------------------------------------------------------

