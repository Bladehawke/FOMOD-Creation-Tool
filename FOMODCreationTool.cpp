//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("ScriptForm.cpp", ScriptForm1);
USEFORM("main.cpp", MainForm);
USEFORM("SettingsForm.cpp", SettingsForm);
USEFORM("SplashScreen.cpp", SplashForm);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
		 Application->Initialize();
		 Application->MainFormOnTaskBar = false;
		 Application->CreateForm(__classid(TSplashForm), &SplashForm);
		 Application->CreateForm(__classid(TMainForm), &MainForm);
		 Application->CreateForm(__classid(TScriptForm1), &ScriptForm1);
		 Application->CreateForm(__classid(TSettingsForm), &SettingsForm);
		 ShowWindow(Application->Handle, SW_HIDE);
		 Application->Run();
	}
	catch (Exception &exception)
	{
		 Application->ShowException(&exception);
	}
	catch (...)
	{
		 try
		 {
			 throw Exception("");
		 }
		 catch (Exception &exception)
		 {
			 Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
