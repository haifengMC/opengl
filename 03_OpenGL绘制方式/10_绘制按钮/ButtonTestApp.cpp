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
	case GLFW_MOUSE_BUTTON_LEFT: os << "1���"; break;
	case GLFW_MOUSE_BUTTON_RIGHT: os << "2�Ҽ�"; break;
	case GLFW_MOUSE_BUTTON_MIDDLE: os << "3�м�"; break;
	case GLFW_MOUSE_BUTTON_4: os << "4��"; break;
	case GLFW_MOUSE_BUTTON_5: os << "5��"; break;
	case GLFW_MOUSE_BUTTON_6: os << "6��"; break;
	case GLFW_MOUSE_BUTTON_7: os << "7��"; break;
	case GLFW_MOUSE_BUTTON_8: os << "8��"; break;
	default:os << "δ֪��"; break;
	}

	switch (action)
	{
	case GLFW_PRESS: os << "����"; break;
	case GLFW_RELEASE: os << "�ͷ�"; break;
	default:os << "δ֪"; break;
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
