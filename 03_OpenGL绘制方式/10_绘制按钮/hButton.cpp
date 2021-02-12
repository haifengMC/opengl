#include "global.h"
#include "vgl.h"
#include "hTool.h"
#include "hObject.h"
#include "hRect.h"
#include "hButton.h"

hButton::hButton(hPWObj parent, const hRect& r) : hObject(parent)
{
	_rect = r;
}
