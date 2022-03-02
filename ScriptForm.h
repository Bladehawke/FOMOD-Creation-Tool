//---------------------------------------------------------------------------

#ifndef ScriptFormH
#define ScriptFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TScriptForm1 : public TForm
{
__published:	// IDE-managed Components
    TButton *SaveButton;
    TButton *CancelButton;
    TMemo *ScriptMemo;
    TLabel *Label1;
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TScriptForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TScriptForm1 *ScriptForm1;
//---------------------------------------------------------------------------
#endif
