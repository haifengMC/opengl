#include "global.h"

//#include "hTool.h"
#include "hRect.h"
//#include "hObject.h"
//#include "hButton.h"
//
//#include "vapp.h"
//#include "hConfig.h"
//
//#include "LoadShaders.h"
//#include "ButtonTest.h"
#include "ButtonTest.h"

//DEFINE_APP(ButtonTest, "button test");

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ButtonTestApp app;
	app.loop();

	return 0;
}