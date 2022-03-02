//---------------------------------------------------------------------------

#ifndef SettingsFormH
#define SettingsFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include <deque.h>
//---------------------------------------------------------------------------
class TSettingsForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TButton *CancelButton;
    TButton *SaveButton;
    TLabel *LanguageLabel;
    TComboBox *LanguagesComboBox;
    TCheckBox *HideOpenFolderCheckBox;
    TCheckBox *HideOpenFileCheckBox;
    TLabel *IntTextSizeLabel;
    TComboBox *IntTextSizeComboBox;
    TPanel *Panel3;
    TPageControl *PageControl1;
    TTabSheet *SettingsGeneralTabSheet;
    TTabSheet *SettingsRecentTabSheet;
    TListView *RecentListView;
    TLabel *MaxRecentLabel;
    TEdit *MaxRecentEdit;
    TButton *MoveUpButton;
    TButton *MoveDownButton;
    TButton *RemoveButton;
    TCheckBox *ReplaceRNCheckBox;
    void __fastcall RecentListViewSelectItem(TObject *Sender, TListItem *Item, bool Selected);
    void __fastcall MoveUpButtonClick(TObject *Sender);
    void __fastcall MoveDownButtonClick(TObject *Sender);
    void __fastcall RemoveButtonClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
    __fastcall TSettingsForm(TComponent* Owner);

    deque <AnsiString> recentFiles;
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsForm *SettingsForm;
//---------------------------------------------------------------------------
#endif
