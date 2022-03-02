//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SettingsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsForm *SettingsForm;
//---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::RecentListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
    MoveUpButton->Enabled = false;
    MoveDownButton->Enabled = false;
    RemoveButton->Enabled = false;
    if(RecentListView->ItemIndex > -1)
    {
        RemoveButton->Enabled = true;
        if(RecentListView->ItemIndex > 0)
            MoveUpButton->Enabled = true;
        if(RecentListView->ItemIndex < RecentListView->Items->Count - 1)
            MoveDownButton->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::MoveUpButtonClick(TObject *Sender)
{
    unsigned int temp = RecentListView->ItemIndex;
    std::iter_swap(recentFiles.begin()+temp, recentFiles.begin()+temp-1);
    RecentListView->Items->operator [](temp-1)->Caption = recentFiles[temp-1];
    RecentListView->Items->operator [](temp)->Caption = recentFiles[temp];
    RecentListView->ItemIndex = temp - 1;
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::MoveDownButtonClick(TObject *Sender)
{
    unsigned int temp = RecentListView->ItemIndex;
    std::iter_swap(recentFiles.begin()+temp, recentFiles.begin()+temp+1);
    RecentListView->Items->operator [](temp+1)->Caption = recentFiles[temp+1];
    RecentListView->Items->operator [](temp)->Caption = recentFiles[temp];
    RecentListView->ItemIndex = temp + 1;
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::RemoveButtonClick(TObject *Sender)
{
    recentFiles.erase(recentFiles.begin() + RecentListView->ItemIndex);
    RecentListView->Items->Delete(RecentListView->ItemIndex);
}
//---------------------------------------------------------------------------

