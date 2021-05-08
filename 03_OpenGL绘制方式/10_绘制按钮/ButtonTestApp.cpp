#include "global.h"

#include "hColor.h"
#include "hRect.h"
#include "hObject.h"
#include "hButton.h"

#include "hConfig.h"

#include "LoadShaders.h"
#include "ButtonTestApp.h"
#include "ButtonTestUi.h"

bool ButtonTestApp::preInit()
{
	setUi(new ButtonTestUi);

	setName("ButtonTest");
	addShader(GL_VERTEX_SHADER, "ButtonTest.vert");
	addShader(GL_FRAGMENT_SHADER, "ButtonTest.frag");

	return true;
}

#if 0

void APP_FUNCTION(ButtonTest, onMouse)(int button, int action, int mods)
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

void APP_FUNCTION(ButtonTest, onCursor)(double x, double y)
{
	std::ostringstream os;
	os << "(" << x << "," << y << ")\n";
	OutputDebugStringA(os.str().c_str());
}

void APP_FUNCTION(ButtonTest, onCursorNorm)(float x, float y)
{
	std::ostringstream os;
	os << "(" << x << "," << y << ")\n";
	OutputDebugStringA(os.str().c_str());
}
#endif
