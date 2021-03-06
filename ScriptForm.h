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
    TLabel *macroLabel0;
    TLabel *macroLabel1;
    TLabel *macroLabel2;
    TLabel *macroLabel3;
    TLabel *macroLabel4;
    TLabel *macroLabel5;
    TLabel *macroLabel6;
    TLabel *macroLabel7;
    TLabel *macroLabel8;
private:	// User declarations
public:		// User declarations
    __fastcall TScriptForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TScriptForm1 *ScriptForm1;
//---------------------------------------------------------------------------
#endif
