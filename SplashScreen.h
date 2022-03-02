//---------------------------------------------------------------------------

#ifndef SplashScreenH
#define SplashScreenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSplashForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TTimer *Timer1;
    TImage *LogoImage;
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TSplashForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSplashForm *SplashForm;
//---------------------------------------------------------------------------
#endif
