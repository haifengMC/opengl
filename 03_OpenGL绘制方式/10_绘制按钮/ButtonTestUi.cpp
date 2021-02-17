#include "global.h"

#include "hTool.h"
#include "hRect.h"
#include "hObject.h"
#include "hButton.h"

#include "vgl.h"
#include "vapp.h"
#include "hConfig.h"

#include "LoadShaders.h"
#include "ButtonTest.h"

UI_FUNCTION(ButtonTest, ~ButtonTestUi)()
{
	OutputDebugStringA("~ButtonTestUi\n");
}

void UI_FUNCTION(ButtonTest, loadUi)()
{
	new hButton(this, hRect(20, 20, 100, 50));
	new hButton(this, hRect(20, 90, 100, 50));
	std::ostringstream os;
	Debug(os, (hObject&)*this) << "\n";
	OutputDebugStringA(os.str().c_str());
}