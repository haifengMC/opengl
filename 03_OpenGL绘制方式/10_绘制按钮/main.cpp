#include "global.h"
#include "vgl.h"
#include "vapp.h"

#include "hTool.h"
#include "hObject.h"
#include "hRect.h"
#include "vtype.h"
#include "vcommon.h"
#include "vbuffer.h"
#include "hConfig.h"
#include "hButton.h"

#include "LoadShaders.h"

typedef std::pair<GLfloat, GLfloat> Point;

BEGIN_APP_DECLARATION(ButtonTest)
{
	void Initialize(const char* title /* = 0 */);
	void Display(bool auto_redraw /* = true */) {}
	void Finalize();

	void OnMouse(int button, int action, int mods);
	virtual void OnCursor(double x, double y);
	void OnCursorNorm(float x, float y);
}
END_APP_DECLARATION();
DEFINE_APP(ButtonTest, "button test");

void APP_FUNCTION(ButtonTest, Initialize)(const char* title)
{
	auto ptr = getThis();
	new hButton(ptr);
	OutputDebugStringA("Initialize\n");
	std::ostringstream os;
	Debug(os, (hObject&)*this) << "\n";
	OutputDebugStringA(os.str().c_str());
	os.str("");
	hPObj::debugMap(os);
	OutputDebugStringA(os.str().c_str());
}

void APP_FUNCTION(ButtonTest, Finalize)()
{
	hObject::Finalize();
	OutputDebugStringA("Finalize\n");
	std::ostringstream os;
	Debug(os, (hObject&)*this) << "\n";
	OutputDebugStringA(os.str().c_str());
	os.str("");
	hPObj::debugMap(os);
	OutputDebugStringA(os.str().c_str());
}

void APP_FUNCTION(ButtonTest, OnMouse)(int button, int action, int mods)
{
	std::ostringstream os;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT: os << "1×ó¼ü"; break;
	case GLFW_MOUSE_BUTTON_RIGHT: os << "2ÓÒ¼ü"; break;
	case GLFW_MOUSE_BUTTON_MIDDLE: os << "3ÖÐ¼ü"; break;
	case GLFW_MOUSE_BUTTON_4: os << "4¼ü"; break;
	case GLFW_MOUSE_BUTTON_5: os << "5¼ü"; break;
	case GLFW_MOUSE_BUTTON_6: os << "6¼ü"; break;
	case GLFW_MOUSE_BUTTON_7: os << "7¼ü"; break;
	case GLFW_MOUSE_BUTTON_8: os << "8¼ü"; break;
	default:os << "Î´Öª¼ü"; break;
	}

	switch (action)
	{
	case GLFW_PRESS: os << "°´ÏÂ"; break;
	case GLFW_RELEASE: os << "ÊÍ·Å"; break;
	default:os << "Î´Öª"; break;
	}
	os << mods << "\n";
	OutputDebugStringA(os.str().c_str());
}

void APP_FUNCTION(ButtonTest, OnCursor)(double x, double y)
{
	std::ostringstream os;
	os << "(" << x << "," << y << ")\n";
	OutputDebugStringA(os.str().c_str());
}

void APP_FUNCTION(ButtonTest, OnCursorNorm)(float x, float y)
{
	std::ostringstream os;
	os << "(" << x << "," << y << ")\n";
	OutputDebugStringA(os.str().c_str());
}



