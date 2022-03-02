//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl;
    TTabSheet *ModInfoTabSheet;
    TTabSheet *StepsTabSheet;
    TGroupBox *GroupBox1;
    TLabeledEdit *ModNameEdit;
    TLabeledEdit *ModAuthorEdit;
    TLabeledEdit *ModVersionEdit;
    TLabeledEdit *ModURLEdit;
    TLabeledEdit *ModDescEdit;
    TGroupBox *WorkSpaceGroupBox;
    TLabeledEdit *RootDirEdit;
    TButton *OpenRootDirButton;
    TButton *ProceedButton;
    TGroupBox *StepSettingsGroupBox;
    TLabeledEdit *StepNameEdit;
    TGroupBox *GroupBox4;
    TLabel *Label1;
    TComboBox *ConditionComboBox;
    TLabel *Label2;
    TLabel *Label3;
    TComboBox *ConditionValueComboBox;
    TListView *ConditionListView;
    TButton *AddConditionButton;
    TButton *DeleteConditionButton;
    TGroupBox *GroupsGroupBox;
    TListBox *PluginListBox;
    TLabeledEdit *GroupNameEdit;
    TLabel *Label4;
    TComboBox *GroupTypeComboBox;
    TButton *AddGroupButton;
    TButton *RemoveGroupButton;
    TLabeledEdit *PluginNameEdit;
    TButton *RemovePluginButton;
    TButton *AddPluginButton;
    TPanel *Panel1;
    TLabel *Label5;
    TMemo *PluginDescriptionMemo;
    TGroupBox *VaribleSetGroupBox;
    TComboBox *VaribleComboBox;
    TLabel *Label6;
    TLabel *Label7;
    TComboBox *VaribleValueComboBox;
    TListView *VaribleSetListView;
    TButton *AddVaribleButton;
    TButton *DeleteVaribleButton;
    TGroupBox *FilesGroupBox;
    TListView *SrcFilesListView;
    TLabel *Label8;
    TButton *AddFileButton;
    TButton *AddFolderButton;
    TButton *RemoveFileFolderButton;
    TButton *DeleteStepButton;
    TButton *NewStepButton;
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *Panel4;
    TImage *PluginImage;
    TButton *ChoosePluginImageButton;
    TButton *ClearPluginImageButton;
    TLabeledEdit *PluginImageEdit;
    TOpenDialog *OpenDialog;
    TFileOpenDialog *OpenFolderDialog;
    TListView *GroupListView;
    TPageControl *PageControl1;
    TTabSheet *GroupsFileTabSheet;
    TTabSheet *ConditionsTabSheet;
    TScrollBox *ScrollBox;
    TScrollBox *ScrollBox1;
    TTabSheet *InfoTabSheet;
    TPageControl *StepsTabControl;
    TTabSheet *TabSheet1;
    TMemo *Memo1;
    TListView *DstFilesListView;
    TLabel *Label9;
    TButton *GroupUpButton;
    TButton *GroupDownButton;
    TButton *PluginUpButton;
    TButton *PluginDownButton;
    TLabeledEdit *ModCategoryEdit;
    TButton *MoveLeftButton;
    TButton *MoveRightButton;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *NewMenu;
    TMenuItem *OpenMenu;
    TMenuItem *SaveMenu;
    TMenuItem *ExitMenu;
    TMenuItem *N1;
    TMenuItem *Script1;
    TMenuItem *RunBeforeSaveMenu;
    TMenuItem *RunAfterSaveMenu;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall OpenRootDirButtonClick(TObject *Sender);
    void __fastcall RootDirEditChange(TObject *Sender);
    void __fastcall ModNameEditChange(TObject *Sender);
    void __fastcall ModAuthorEditChange(TObject *Sender);
    void __fastcall ModVersionEditChange(TObject *Sender);
    void __fastcall ModCategoryEditChange(TObject *Sender);
    void __fastcall ModURLEditChange(TObject *Sender);
    void __fastcall ModDescEditChange(TObject *Sender);
    void __fastcall ProceedButtonClick(TObject *Sender);
    void __fastcall StepNameEditChange(TObject *Sender);
    void __fastcall AddConditionButtonClick(TObject *Sender);
    void __fastcall DeleteConditionButtonClick(TObject *Sender);
    void __fastcall AddGroupButtonClick(TObject *Sender);
    void __fastcall RemoveGroupButtonClick(TObject *Sender);
    void __fastcall GroupUpButtonClick(TObject *Sender);
    void __fastcall GroupDownButtonClick(TObject *Sender);
    void __fastcall GroupListViewClick(TObject *Sender);
    void __fastcall AddPluginButtonClick(TObject *Sender);
    void __fastcall RemovePluginButtonClick(TObject *Sender);
    void __fastcall PluginUpButtonClick(TObject *Sender);
    void __fastcall PluginDownButtonClick(TObject *Sender);
    void __fastcall PluginListBoxClick(TObject *Sender);
    void __fastcall AddVaribleButtonClick(TObject *Sender);
    void __fastcall DeleteVaribleButtonClick(TObject *Sender);
    void __fastcall VaribleSetListViewClick(TObject *Sender);
    void __fastcall PluginDescriptionMemoChange(TObject *Sender);
    void __fastcall AddFileButtonClick(TObject *Sender);
    void __fastcall AddFolderButtonClick(TObject *Sender);
    void __fastcall RemoveFileFolderButtonClick(TObject *Sender);
    void __fastcall SrcFilesListViewClick(TObject *Sender);
    void __fastcall DstFilesListViewClick(TObject *Sender);
    void __fastcall ChoosePluginImageButtonClick(TObject *Sender);
    void __fastcall ClearPluginImageButtonClick(TObject *Sender);
    void __fastcall NewStepButtonClick(TObject *Sender);
    void __fastcall StepsTabControlChange(TObject *Sender);
    void __fastcall DeleteStepButtonClick(TObject *Sender);
    void __fastcall DstFilesListViewEdited(TObject *Sender, TListItem *Item, UnicodeString &S);
    void __fastcall MoveLeftButtonClick(TObject *Sender);
    void __fastcall MoveRightButtonClick(TObject *Sender);
    void __fastcall SaveMenuClick(TObject *Sender);
    void __fastcall OpenMenuClick(TObject *Sender);
    void __fastcall NewMenuClick(TObject *Sender);
    void __fastcall RunBeforeSaveMenuClick(TObject *Sender);
    void __fastcall RunAfterSaveMenuClick(TObject *Sender);



private:	// User declarations
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
