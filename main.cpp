//---------------------------------------------------------------------------

#include <vcl.h>
#include <jpeg.hpp>
#include <pngimage.hpp>
#pragma hdrstop

#include "main.h"
#include "DataClasses.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

CFOMOD FOMOD;
UnicodeString RootDirectory;

int StepCount       = 0;
int CurrentStepIndx = 0;

//---------------------------------------------------------------------------

bool dirExists(AnsiString dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}
AnsiString GetFileVersionOfApplication(LPTSTR lpszFilePath)
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

   char str[128];

   sprintf(str, "%d.%d.%d.%d\n" , dwLeftMost, dwSecondLeft,
      dwSecondRight, dwRightMost);

   return AnsiString(str);
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
            if(MessageBox(NULL, "There is no 'fomod' catalog in specified directory. Create one?", "FOMOD Creation Tool",  MB_YESNO) == IDYES)
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

void __fastcall TMainForm::ModDescEditChange(TObject *Sender)
{
    FOMOD.Description = ModDescEdit->Text;
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
    PluginListBox->Clear();
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
        PluginListBox->Clear();
        VaribleSetListView->Clear();
        SrcFilesListView->Clear();
        DstFilesListView->Clear();
        GroupListViewClick(Sender);
    }
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

void __fastcall TMainForm::GroupListViewClick(TObject *Sender)
{
    PluginListBox->Clear();
    VaribleSetListView->Clear();
    SrcFilesListView->Clear();
    DstFilesListView->Clear();
    PluginDescriptionMemo->Clear();
    PluginImageEdit->Text = "";
    PluginImage->Picture->Bitmap = NULL;
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups.size() > 0 && GroupListView->ItemIndex > -1)
    {
        for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size(); i++)
        {
            PluginListBox->Items->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[i].Name);
        }
        if(PluginListBox->Items->Count > 0)
        {
            PluginListBox->ItemIndex = 0;
        }
        RemoveGroupButton->Enabled = true;
        AddPluginButton->Enabled = true;
        GroupUpButton->Enabled = true;
        GroupDownButton->Enabled = true;
        if(GroupListView->ItemIndex == 0)
            GroupUpButton->Enabled = false;
        if(GroupListView->ItemIndex == GroupListView->Items->Count - 1)
            GroupDownButton->Enabled = false;


    }
    else
    {
        RemoveGroupButton->Enabled = false;
        AddPluginButton->Enabled = false;
        GroupUpButton->Enabled = false;
        GroupDownButton->Enabled = false;
    }
    PluginListBoxClick(Sender);
}
//---------------------------------------------------------------------------  

void __fastcall TMainForm::AddPluginButtonClick(TObject *Sender)
{
    if(PluginNameEdit->Text != "" && FOMOD.Steps[CurrentStepIndx].PluginGroups.size() > 0 && GroupListView->ItemIndex > -1)
    {
        CPlugin new_plugin(PluginNameEdit->Text);
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.push_back(new_plugin);
        PluginListBox->Items->Add(PluginNameEdit->Text);
        PluginListBox->ItemIndex = PluginListBox->Items->Count-1;
        PluginListBoxClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemovePluginButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListBox->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.erase(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+PluginListBox->ItemIndex);
        PluginListBox->Items->Delete(PluginListBox->ItemIndex);
        VaribleSetListView->Clear();
        SrcFilesListView->Clear();
        DstFilesListView->Clear();
        PluginListBoxClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginUpButtonClick(TObject *Sender)
{

    unsigned int temp = PluginListBox->ItemIndex;
    std::iter_swap(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp,
                    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp-1);
    GroupListViewClick(Sender);
    PluginListBox->ItemIndex = temp - 1;
    PluginListBoxClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginDownButtonClick(TObject *Sender)
{

    unsigned int temp = PluginListBox->ItemIndex;
    std::iter_swap(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp,
                    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.begin()+temp+1);
    GroupListViewClick(Sender);
    PluginListBox->ItemIndex = temp + 1;
    PluginListBoxClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginListBoxClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListBox->ItemIndex > -1)
    {
        VaribleSetListView->Clear();
        SrcFilesListView->Clear();
        DstFilesListView->Clear();
        PluginDescriptionMemo->Clear();
        PluginImageEdit->Text = "";
        PluginImage->Picture->Bitmap = NULL;

        if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ConditionSet.size() > 0)
        {
            for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ConditionSet.size(); i++)
            {
                TListItem *item = VaribleSetListView->Items->Add();
                item->Caption = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ConditionSet[i].Name;
                item->SubItems->Add(" =");
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ConditionSet[i].Value);
            }
        }
        if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files.size() > 0)
        {
            for(int i = 0; i < FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files.size(); i++)
            {
                TListItem *item = SrcFilesListView->Items->Add();
                item->Caption = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files[i].Type;
                item->SubItems->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files[i].SrcPath);
                item = DstFilesListView->Items->Add();
                item->Caption = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files[i].DstPath;
            }
        }
        PluginDescriptionMemo->Lines->Add(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Description);
        PluginImageEdit->Text = FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ImagePath;
        if(PluginImageEdit->Text != "")
            PluginImage->Picture->LoadFromFile(RootDirectory + "\\" + PluginImageEdit->Text);

        RemovePluginButton->Enabled = true;
        PluginDescriptionMemo->Enabled = true;
        AddVaribleButton->Enabled = true;
        ChoosePluginImageButton->Enabled = true;
        ClearPluginImageButton->Enabled = true;
        PluginImageEdit->Enabled = true;
        AddFileButton->Enabled = true;
        AddFolderButton->Enabled = true;
        PluginUpButton->Enabled = true;
        PluginDownButton->Enabled = true;
        if(PluginListBox->ItemIndex == 0)
            PluginUpButton->Enabled = false;
        if(PluginListBox->ItemIndex == PluginListBox->Items->Count-1)
            PluginDownButton->Enabled = false;

    }
    else
    {
        RemovePluginButton->Enabled = false;
        PluginDescriptionMemo->Enabled = false;
        AddVaribleButton->Enabled = false;
        ChoosePluginImageButton->Enabled = false;
        ClearPluginImageButton->Enabled = false;
        PluginImageEdit->Enabled = false;
        AddFileButton->Enabled = false;
        AddFolderButton->Enabled = false;
        PluginUpButton->Enabled = false;
        PluginDownButton->Enabled = false;
    }
    SrcFilesListViewClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddVaribleButtonClick(TObject *Sender)
{
    if(VaribleComboBox->Text != "" && PluginListBox->ItemIndex > -1)
    {
        CCondition new_condition(VaribleComboBox->Text, VaribleValueComboBox->Text);
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ConditionSet.push_back(new_condition);

        TListItem *item = VaribleSetListView->Items->Add();
        item->Caption = VaribleComboBox->Text;
        item->SubItems->Add(" =");
        item->SubItems->Add(VaribleValueComboBox->Text);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteVaribleButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ConditionSet.size() > 0 && VaribleSetListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ConditionSet.erase(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ConditionSet.begin()+VaribleSetListView->ItemIndex);
        VaribleSetListView->Items->Delete(VaribleSetListView->ItemIndex);
        VaribleSetListViewClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VaribleSetListViewClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ConditionSet.size() > 0 && VaribleSetListView->ItemIndex > -1)
        DeleteVaribleButton->Enabled = true;
    else
        DeleteVaribleButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PluginDescriptionMemoChange(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListBox->ItemIndex > -1)
    {
        int len = strlen(PluginDescriptionMemo->Lines[0].Text.c_str());
        char *temp = new char [len+1];
        memset(temp, 0, len+1);
        for(int i = 0; i < len && PluginDescriptionMemo->Lines[0].Text.c_str()[i] != '\r'; i++)
            temp[i] = PluginDescriptionMemo->Lines[0].Text.c_str()[i];
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Description =
            temp;
        delete [] temp;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddFileButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListBox->ItemIndex > -1)
    {
        if(OpenDialog->Execute())
        {
            UnicodeString temp = OpenFolderDialog->FileName.SubString(0, RootDirectory.Length()).UpperCase();
            if(!(temp.Compare(RootDirectory.UpperCase())))
            {
                TListItem *item = SrcFilesListView->Items->Add();
                item->Caption = "file";
                item->SubItems->Add(OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2));
                item = DstFilesListView->Items->Add();
                item->Caption = OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2);

                CFile new_file;
                new_file.Type = "file";
                new_file.SrcPath = OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2);
                new_file.DstPath = OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2);
                FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files.push_back(new_file);
            }
            else
            {
                MessageBox(NULL, "File is out of root directory", "FOMOD Creation Tool",  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddFolderButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListBox->ItemIndex > -1)
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
                FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files.push_back(new_file);
            }
            else
            {
                MessageBox(NULL, "Folder is out of root directory", "FOMOD Creation Tool",  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RemoveFileFolderButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files.size() > 0 &&
        SrcFilesListView->ItemIndex > -1)
    {
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files.erase(
            FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files.begin()+
            SrcFilesListView->ItemIndex);
        DstFilesListView->Items->Delete(SrcFilesListView->ItemIndex);
        SrcFilesListView->Items->Delete(SrcFilesListView->ItemIndex);
        SrcFilesListViewClick(Sender);
    }
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
    FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].Files[SrcFilesListView->ItemIndex].DstPath = S;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ChoosePluginImageButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListBox->ItemIndex > -1)
    {
        if(OpenDialog->Execute())
        {
            UnicodeString temp = OpenDialog->FileName.SubString(0, RootDirectory.Length()).UpperCase();
            if(!(temp.Compare(RootDirectory.UpperCase())))
            {
                PluginImageEdit->Text = OpenDialog->FileName.SubString(RootDirectory.Length()+2, OpenDialog->FileName.Length()-RootDirectory.Length()+2);
                AnsiString ext = OpenDialog->FileName.SubString(OpenDialog->FileName.Length()-2, 3);
                if(ext == "jpg")
                {
                    TJPEGImage *jpg = new TJPEGImage;
                    jpg->LoadFromFile(OpenDialog->FileName);
                    PluginImage->Picture->Bitmap->Assign(jpg);
                }
                else if(ext == "png")
                {
                    TPngImage *png = new TPngImage;
                    png->LoadFromFile(OpenDialog->FileName);
                    PluginImage->Picture->Bitmap->Assign(png);
                }
                else
                    PluginImage->Picture->LoadFromFile(OpenDialog->FileName);

                FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ImagePath = PluginImageEdit->Text;
            }
            else
            {
                MessageBox(NULL, "File is out of root directory", "FOMOD Creation Tool",  MB_OK);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClearPluginImageButtonClick(TObject *Sender)
{
    if(FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins.size() > 0 && PluginListBox->ItemIndex > -1)
    {
        PluginImageEdit->Text = "";
        PluginImage->Picture->Bitmap = NULL;
        FOMOD.Steps[CurrentStepIndx].PluginGroups[GroupListView->ItemIndex].Plugins[PluginListBox->ItemIndex].ImagePath = "";
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
    StepsTabControl->Pages[CurrentStepIndx]->~TTabSheet();
    StepCount = FOMOD.Steps.size();
    StepsTabControlChange(Sender);
    if(StepsTabControl->PageCount == 1)
        DeleteStepButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DoneButtonClick(TObject *Sender)
{
    CFOMOD temp_fomod = FOMOD;
    FILE *fpinfoxml = fopen((RootDirectory+"\\fomod\\info.xml").c_str(), "w");
    if(fpinfoxml)
    {
//        fprintf(fpinfoxml, "<!-- Created with FOMOD Creation Tool [%s] --> \n", "http://www.nexusmods.com");

        fprintf(fpinfoxml, "<?xml version=\"1.0\" encoding=\"utf-16\"?> \n");
        fprintf(fpinfoxml, "<fomod> \n");
        fprintf(fpinfoxml, "\t<Name>%s</Name> \n", temp_fomod.Name.c_str());
        fprintf(fpinfoxml, "\t<Author>%s</Author> \n", temp_fomod.AuthorName.c_str());
        fprintf(fpinfoxml, "\t<Version>%s</Version> \n", temp_fomod.Version.c_str());
        fprintf(fpinfoxml, "\t<Website>%s</Website> \n", temp_fomod.URL.c_str());
        fprintf(fpinfoxml, "\t<Description>%s</Description> \n", temp_fomod.Description.c_str());
        fprintf(fpinfoxml, "\t<Groups>\n\t\t<element>%s</element>\n\t</Groups> \n", temp_fomod.ModCategory.c_str());
        fprintf(fpinfoxml, "</fomod> \n");

        fclose(fpinfoxml);
    }
    else
        MessageBox(NULL, "Can't open 'fomod\\info.xml' for write", "temp_fomod Creation Tool",  MB_OK);


    FILE *fpModuleConfigxml = fopen((RootDirectory+"\\fomod\\ModuleConfig.xml").c_str(), "w");
    if(fpModuleConfigxml)
    {
        fprintf(fpModuleConfigxml, "<!-- Created with FOMOD Creation Tool [%s] --> \n", "http://www.nexusmods.com");

        fprintf(fpModuleConfigxml, "<config xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://qconsulting.ca/fo3/ModConfig5.0.xsd\"> \n");
        fprintf(fpModuleConfigxml, "\t<moduleName>%s</moduleName> \n", temp_fomod.Name.c_str());

        fprintf(fpModuleConfigxml, "\t<installSteps order=\"Explicit\"> \n");
        for(int step_i = 0; step_i < temp_fomod.Steps.size(); step_i++)
        {
            fprintf(fpModuleConfigxml, "\t\t<installStep name=\"%s\"> \n", temp_fomod.Steps[step_i].Name.c_str());
            if(temp_fomod.Steps[step_i].ConditionSet.size() > 0)
            {
                fprintf(fpModuleConfigxml, "\t\t\t<visible> \n");
                for(int i = 0; i < temp_fomod.Steps[step_i].ConditionSet.size(); i++)
                    fprintf(fpModuleConfigxml, "\t\t\t\t<flagDependency flag=\"%s\" value=\"%s\" /> \n",
                        temp_fomod.Steps[step_i].ConditionSet[i].Name.c_str(),
                        temp_fomod.Steps[step_i].ConditionSet[i].Value.c_str());
                fprintf(fpModuleConfigxml, "\t\t\t</visible> \n");
            }

            fprintf(fpModuleConfigxml, "\t\t\t<optionalFileGroups order=\"Explicit\"> \n");
            for(int group_i = 0; group_i < temp_fomod.Steps[step_i].PluginGroups.size(); group_i++)
            {
                fprintf(fpModuleConfigxml, "\t\t\t\t<group name=\"%s\" type=\"%s\"> \n",
                    temp_fomod.Steps[step_i].PluginGroups[group_i].Name.c_str(),
                    temp_fomod.Steps[step_i].PluginGroups[group_i].Type.c_str());

                fprintf(fpModuleConfigxml, "\t\t\t\t\t<plugins order=\"Explicit\"> \n");
                for(int plugin_i = 0; plugin_i < temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins.size(); plugin_i++)
                {
                    fprintf(fpModuleConfigxml, "\t\t\t\t\t\t<plugin name=\"%s\"> \n",
                        temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Name.c_str());
                    fprintf(fpModuleConfigxml, "\t\t\t\t\t\t\t<description>%s</description> \n",
                        temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Description.c_str());
                    if(temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ImagePath != "")
                        fprintf(fpModuleConfigxml, "\t\t\t\t\t\t\t<image path=\"%s\" /> \n",
                            temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ImagePath.c_str());
                    if(temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ConditionSet.size() > 0)
                    {
                        fprintf(fpModuleConfigxml, "\t\t\t\t\t\t\t<conditionFlags> \n");
                        for(int i = 0; i < temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ConditionSet.size(); i++)
                            fprintf(fpModuleConfigxml, "\t\t\t\t\t\t\t\t<flag name=\"%s\">%s</flag> \n",
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ConditionSet[i].Name.c_str(),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].ConditionSet[i].Value.c_str());
                        fprintf(fpModuleConfigxml, "\t\t\t\t\t\t\t</conditionFlags> \n");
                    }
                    if(temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files.size() > 0)
                    {
                        fprintf(fpModuleConfigxml, "\t\t\t\t\t\t\t<files> \n");
                        for(int i = 0; i < temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files.size(); i++)
                            fprintf(fpModuleConfigxml, "\t\t\t\t\t\t\t\t<%s source=\"%s\" destination=\"%s\" /> \n",
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files[i].Type.c_str(),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files[i].SrcPath.c_str(),
                                temp_fomod.Steps[step_i].PluginGroups[group_i].Plugins[plugin_i].Files[i].DstPath.c_str());
                        fprintf(fpModuleConfigxml, "\t\t\t\t\t\t\t</files> \n");
                    }
                    fprintf(fpModuleConfigxml, "\t\t\t\t\t\t\t<typeDescriptor>\n\t\t\t\t\t\t\t\t<type name=\"Optional\"/>\n\t\t\t\t\t\t\t</typeDescriptor> \n");
                    fprintf(fpModuleConfigxml, "\t\t\t\t\t\t</plugin> \n");
                }
                fprintf(fpModuleConfigxml, "\t\t\t\t\t</plugins> \n");

                fprintf(fpModuleConfigxml, "\t\t\t\t</group> \n");
            }
            fprintf(fpModuleConfigxml, "\t\t\t</optionalFileGroups> \n");

            fprintf(fpModuleConfigxml, "\t\t</installStep> \n");
        }
        fprintf(fpModuleConfigxml, "\t</installSteps> \n");

        fprintf(fpModuleConfigxml, "</config>");

        fclose(fpModuleConfigxml);
    }
    else
        MessageBox(NULL, "Can't open 'fomod\\ModuleConfig.xml' for write", "FOMOD Creation Tool",  MB_OK);

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

