#include "global.h"

#include "hColor.h"
#include "hRect.h"
#include "hButton.h"
#include "ButtonTestUi.h"

bool ButtonTestUi::onLoadUi()
{
	new hButton(this, "x20 y20 w100 h50"_Rect);
	new hButton(this, "x20 y90 w100 h50"_Rect);

	std::ostringstream os;
	Debug(os, (hObject&)*this) << "\n";
	OutputDebugStringA(os.str().c_str());

	return true;
}

