#include "vgl.h"

#include "global.h"
#include "hTime.h"
#include "hRect.h"
#include "hAppBase.h"

uint64_t hAppBase::appTime()
{
	return (getNow() - _startTime).count();
}

bool hAppBase::initCallback()
{
	if (!glfwInit())
	{
		OutputDebugStringA("glfwInit() ß∞‹...");
		return false;
	}

	_startTime = getNow();
	if (!preInit())
	{
		OutputDebugStringA("‘§≥ı ºªØ ß∞‹...");
		return false;
	}

	if (!_winRect.width() || !_winRect.height())
		_winRect = "x0 y0 w800 h600"_Rect;
	if (_appName.empty())
		_appName = "Application";

	_pWin = glfwCreateWindow(
		_winRect.width(), _winRect.height(), 
		_appName.c_str(), nullptr, nullptr);

	glfwSetWindowUserPointer(_pWin, this);

	return true;
}

