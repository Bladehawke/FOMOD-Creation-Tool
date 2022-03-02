//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ScriptForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TScriptForm1 *ScriptForm1;
//---------------------------------------------------------------------------
__fastcall TScriptForm1::TScriptForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TScriptForm1::FormCreate(TObject *Sender)
{
    Label1->Caption =
"Type there window console commands (cmd). Those will be executed befor/after project save. You can use macro defined in FMOD Creation Tool like:\n \
$MODNAME$ - will be replaced with your mod name\n \
$MODAUTHOR$ - will be replaced with mod author name\n \
$MODVERSION$ - will be replaced with your mod version\n \
$MODROOT$ - will be replaced with mod root directory you specified\n \
$DATE$ - will be replaced with current date\n \
$TIME$ - will be replaced with current time\n \
$RANDOM$ - will be replaced with random number from 0 to 32767\n \
Don't forget about quotes as you likely will need them so cmd will understand commands in right way. " ;
}
//---------------------------------------------------------------------------

