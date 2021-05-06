#include "global.h"

#include "hRect.h"
#include "hObject.h"
#include "hButton.h"

#include "hConfig.h"

#include "LoadShaders.h"
#include "ButtonTest.h"
#include "ButtonTestUi.h"

#if 0
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
#endif

bool ButtonTestUi::loadUi()
{
	new hButton(getThis<hObject>(), hRect(20, 20, 100, 50));

	std::ostringstream os;
	Debug(os, (hObject&)*this) << "\n";
	OutputDebugStringA(os.str().c_str());

	return true;
}
