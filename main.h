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

#include <deque.h>
//---------------------------------------------------------------------------

typedef struct SSettings
{
    AnsiString langFile;
    bool hideOpenFolder;
    bool hideOpenFile;
    int interfaceTextSize;
    int splashScreenSeconds;
    int MaxRecentFiles;
    int RecentFilesNum;
    deque <AnsiString> RecentFiles;
} TSettings;

typedef struct SLanguagePair
{
    UnicodeString Name;
    UnicodeString Text;
} TLanguagePair;

class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl;
    TTabSheet *ModInfoTabSheet;
    TTabSheet *StepsTabSheet;
    TGroupBox *ModInfoGroupBox;
    TGroupBox *WorkSpaceGroupBox;
    TButton *OpenRootDirButton;
    TButton *ProceedButton;
    TGroupBox *StepSettingsGroupBox;
    TGroupBox *ConditionSetGroupBox;
    TLabel *IfLabel;
    TComboBox *ConditionComboBox;
    TLabel *equalsLabel;
    TComboBox *ConditionValueComboBox;
    TListView *ConditionListView;
    TButton *AddConditionButton;
    TButton *DeleteConditionButton;
    TGroupBox *GroupsGroupBox;
    TLabeledEdit *GroupNameEdit;
    TLabel *GTypeLabel;
    TComboBox *GroupTypeComboBox;
    TButton *AddGroupButton;
    TButton *RemoveGroupButton;
    TLabeledEdit *PluginNameEdit;
    TButton *RemovePluginButton;
    TButton *AddPluginButton;
    TPanel *Panel1;
    TLabel *PluginDescLabel;
    TMemo *PluginDescriptionMemo;
    TComboBox *VaribleComboBox;
    TLabel *FNameLabel;
    TLabel *FSetLabel;
    TComboBox *VaribleValueComboBox;
    TListView *FlagSetListView;
    TButton *AddVaribleButton;
    TButton *DeleteVaribleButton;
    TGroupBox *FilesGroupBox;
    TListView *SrcFilesListView;
    TLabel *CpyLabel;
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
    TTabSheet *Step1;
    TMemo *Memo1;
    TListView *DstFilesListView;
    TLabel *DataLabel;
    TButton *GroupUpButton;
    TButton *GroupDownButton;
    TButton *PluginUpButton;
    TButton *PluginDownButton;
    TButton *MoveLeftButton;
    TButton *MoveRightButton;
    TMainMenu *MainMenu;
    TMenuItem *FOMODMenu;
    TMenuItem *NewMenu;
    TMenuItem *OpenMenu;
    TMenuItem *SaveMenu;
    TMenuItem *ExitMenu;
    TMenuItem *N1;
    TMenuItem *OptionsMenu;
    TMenuItem *RunBeforeSaveMenu;
    TMenuItem *RunAfterSaveMenu;
    TMemo *ModDesccriptionMemo;
    TLabel *ModDescriptionLabel;
    TListView *PluginListView;
    TPanel *Panel5;
    TPanel *Panel6;
    TPageControl *PageControl2;
    TTabSheet *FlagSetTabSheet;
    TTabSheet *PluginDependenciesTabSheet;
    TListView *PluginDependenciesListView;
    TLabel *pdValueLabel;
    TComboBox *pdStateValueComboBox;
    TButton *pdAddButton;
    TButton *pdDeleteButton;
    TComboBox *pdDependencyTypeComboBox;
    TLabel *pdDepTypeLabel;
    TLabel *pdNameLabel;
    TLabel *pdOperatorLabel;
    TComboBox *pdOperatorComboBox;
    TLabel *pdDefTypeNameLabel;
    TComboBox *pdDefTypeComboBox;
    TShape *Shape1;
    TShape *Shape2;
    TComboBox *pdTypeNameComboBox;
    TLabel *pdTypeNameLabel;
    TPanel *SaveConfirmationPanel;
    TLabel *SavingInfoLabel;
    TLabel *SavingConfigLabel;
    TLabel *mdlconfXMLStateLabel;
    TLabel *infoXMLStateLabel;
    TTimer *ShowConfirmationTimer;
    TShape *Shape3;
    TLabel *NoImageLabel;
    TPageControl *pdPatternsPageControl;
    TButton *pdDeletePatternButton;
    TButton *pdNewPatternButton;
    TPopupMenu *PopupMenu;
    TMenuItem *EditListElementCMenu;
    TPanel *FilesPanel;
    TPanel *Panel7;
    TPanel *Panel8;
    TPanel *Panel9;
    TPanel *Panel10;
    TLabel *typeLabel;
    TComboBox *VisibilityTypeComboBox;
    TTabSheet *RequiredInstallsTabSheet;
    TTabSheet *ConditionalInstallsTabSheet;
    TPanel *Panel11;
    TLabel *CpyLabel2;
    TLabel *DataLabel2;
    TButton *AddRequiredFileButton;
    TButton *AddRequiredFolderButton;
    TListView *RequiredFilesDstListView;
    TButton *RemoveRequiredFileFolderButton;
    TListView *RequiredFilesSrcListView;
    TPageControl *ConiditionalFilesPageControl;
    TPanel *Panel12;
    TPanel *Panel13;
    TButton *RemoveCondFilePatternButton;
    TButton *AddCondFilePatternButton;
    TButton *MoveLeftCondFilePatternButton;
    TButton *MoveRightCondFilePatternButton;
    TPanel *Panel14;
    TPanel *Panel15;
    TLabel *DataLabel3;
    TListView *CondFilesDstListView;
    TListView *CondFilesSrcListView;
    TLabel *CpyLabel3;
    TButton *CondFileAddFileButton;
    TButton *CondFileAddFolderButton;
    TButton *CondFileRemoveFileFolderButton;
    TLabel *ciOperatorLabel;
    TComboBox *CondFilePatternOperatorComboBox;
    TComboBox *CondFileDependTypeComboBox;
    TLabel *ciDepTypeLabel;
    TLabel *ciNameLabel;
    TLabel *ciValueLabel;
    TComboBox *CondFileDependValueComboBox;
    TListView *CondFilePatternListView;
    TButton *AddCondFileConditionButton;
    TButton *RemoveCondFileConditionButton;
    TComboBox *pdFileFlagNameComboBox;
    TComboBox *CondFileDependNameComboBox;
    TPanel *Panel16;
    TPanel *Panel17;
    TPanel *Panel18;
    TMenuItem *OpenfileMenu;
    TMenuItem *MergeFOMODMenu;
    TComboBox *ModCategoryComboBox;
    TLabel *ModCategoryLabel;
    TEdit *ModNameEdit;
    TEdit *ModAuthorEdit;
    TEdit *ModVersionEdit;
    TEdit *ModURLEdit;
    TLabel *ModNameLabel;
    TLabel *ModAuthorLabel;
    TLabel *ModVersionLabel;
    TLabel *ModURLLabel;
    TEdit *RootDirEdit;
    TLabel *RootDirLabel;
    TMenuItem *N2;
    TMenuItem *SettingsMenu;
    TEdit *StepNameEdit;
    TLabel *StepNameLabel;
    TMenuItem *RecentMenu;
    TMenuItem *RecentFileTemplate;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall OpenRootDirButtonClick(TObject *Sender);
    void __fastcall RootDirEditChange(TObject *Sender);
    void __fastcall ModNameEditChange(TObject *Sender);
    void __fastcall ModAuthorEditChange(TObject *Sender);
    void __fastcall ModVersionEditChange(TObject *Sender);
    void __fastcall ModCategoryEditChange(TObject *Sender);
    void __fastcall ModURLEditChange(TObject *Sender);
    void __fastcall ModDesccriptionMemoChange(TObject *Sender);
    void __fastcall ProceedButtonClick(TObject *Sender);
    void __fastcall StepNameEditChange(TObject *Sender);
    void __fastcall AddConditionButtonClick(TObject *Sender);
    void __fastcall DeleteConditionButtonClick(TObject *Sender);
    void __fastcall ConditionListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall AddGroupButtonClick(TObject *Sender);
    void __fastcall RemoveGroupButtonClick(TObject *Sender);
    void __fastcall GroupListViewEdited(TObject *Sender, TListItem *Item, UnicodeString &S);
    void __fastcall GroupUpButtonClick(TObject *Sender);
    void __fastcall GroupDownButtonClick(TObject *Sender);
    void __fastcall GroupListViewSelectItem(TObject *Sender, TListItem *Item, bool Selected);
    void __fastcall AddPluginButtonClick(TObject *Sender);
    void __fastcall RemovePluginButtonClick(TObject *Sender);
    void __fastcall PluginUpButtonClick(TObject *Sender);
    void __fastcall PluginDownButtonClick(TObject *Sender);
    void __fastcall PluginListViewSelectItem(TObject *Sender, TListItem *Item, bool Selected);
    void __fastcall PluginListViewEdited(TObject *Sender, TListItem *Item, UnicodeString &S);
    void __fastcall AddVaribleButtonClick(TObject *Sender);
    void __fastcall DeleteVaribleButtonClick(TObject *Sender);
    void __fastcall FlagSetListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall PluginDescriptionMemoChange(TObject *Sender);
    void __fastcall AddFileButtonClick(TObject *Sender);
    void __fastcall AddFolderButtonClick(TObject *Sender);
    void __fastcall RemoveFileFolderButtonClick(TObject *Sender);
    void __fastcall SrcFilesListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall DstFilesListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall ChoosePluginImageButtonClick(TObject *Sender);
    void __fastcall ClearPluginImageButtonClick(TObject *Sender);
    void __fastcall NewStepButtonClick(TObject *Sender);
    void __fastcall StepsTabControlChange(TObject *Sender);
    void __fastcall DeleteStepButtonClick(TObject *Sender);
    void __fastcall DstFilesListViewEdited(TObject *Sender, TListItem *Item, UnicodeString &S);
    void __fastcall MoveLeftButtonClick(TObject *Sender);
    void __fastcall MoveRightButtonClick(TObject *Sender);
    void __fastcall SaveMenuClick(TObject *Sender);
    void __fastcall ShowConfirmationTimerTimer(TObject *Sender);
    void __fastcall NewMenuClick(TObject *Sender);
    void __fastcall OpenMenuClick(TObject *Sender);
    void __fastcall OpenfileMenuClick(TObject *Sender);
    void __fastcall MergeFOMODMenuClick(TObject *Sender);
    void __fastcall RunBeforeSaveMenuClick(TObject *Sender);
    void __fastcall RunAfterSaveMenuClick(TObject *Sender);
    void __fastcall ExitMenuClick(TObject *Sender);
    void __fastcall pdDefTypeComboBoxChange(TObject *Sender);
    void __fastcall pdDependencyTypeComboBoxChange(TObject *Sender);
    void __fastcall pdOperatorComboBoxChange(TObject *Sender);
    void __fastcall pdTypeNameComboBoxChange(TObject *Sender);
    void __fastcall pdAddButtonClick(TObject *Sender);
    void __fastcall pdNewPatternButtonClick(TObject *Sender);
    void __fastcall pdPatternsPageControlChange(TObject *Sender);
    void __fastcall pdDeletePatternButtonClick(TObject *Sender);
    void __fastcall pdDeleteButtonClick(TObject *Sender);                                            
    void __fastcall PluginDependenciesListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall EditListElementCMenuClick(TObject *Sender);
    void __fastcall PopupMenuPopup(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall VisibilityTypeComboBoxChange(TObject *Sender);
    void __fastcall AddRequiredFileButtonClick(TObject *Sender);
    void __fastcall AddRequiredFolderButtonClick(TObject *Sender);
    void __fastcall RequiredFilesSrcListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall RequiredFilesDstListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall RemoveRequiredFileFolderButtonClick(TObject *Sender);
    void __fastcall RequiredFilesDstListViewEdited(TObject *Sender, TListItem *Item,
          UnicodeString &S);
    void __fastcall CondFileDependTypeComboBoxChange(TObject *Sender);
    void __fastcall ConiditionalFilesPageControlChange(TObject *Sender);
    void __fastcall CondFilePatternListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall AddCondFilePatternButtonClick(TObject *Sender);
    void __fastcall RemoveCondFilePatternButtonClick(TObject *Sender);
    void __fastcall MoveLeftCondFilePatternButtonClick(TObject *Sender);
    void __fastcall MoveRightCondFilePatternButtonClick(TObject *Sender);
    void __fastcall CondFilesDstListViewEdited(TObject *Sender, TListItem *Item,
          UnicodeString &S);
    void __fastcall CondFilePatternOperatorComboBoxChange(TObject *Sender);
    void __fastcall CondFileAddFileButtonClick(TObject *Sender);
    void __fastcall CondFileAddFolderButtonClick(TObject *Sender);
    void __fastcall CondFileRemoveFileFolderButtonClick(TObject *Sender);
    void __fastcall CondFilesSrcListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall CondFilesDstListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall AddCondFileConditionButtonClick(TObject *Sender);
    void __fastcall RemoveCondFileConditionButtonClick(TObject *Sender);
    void __fastcall SettingsMenuClick(TObject *Sender);
    void __fastcall RecentFileTemplateClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
