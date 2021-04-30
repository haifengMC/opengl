#include "global.h"

#include "hTime.h"
#include "hRect.h"
#include "hAppBaseData.h"

bool hAppBaseData::createWin()
{
	//if (!_winRect.width() || !_winRect.height())
	//	_winRect = "x0 y0 w800 h600"_Rect;
	if (_appName.empty())
		_appName = "Application";

	//_pWin = glfwCreateWindow(
	//	_winRect.width(), _winRect.height(),
	//	_appName.c_str(), nullptr, nullptr);

	_pWin = glfwCreateWindow(
		800, 600,
		_appName.c_str(), nullptr, nullptr);

	return _pWin;
}
