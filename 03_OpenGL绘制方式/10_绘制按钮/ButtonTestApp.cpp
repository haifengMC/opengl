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

APP_FUNCTION(ButtonTest, ~ButtonTestApp)()
{
	OutputDebugStringA("~ButtonTestApp\n");
}

void APP_FUNCTION(ButtonTest, initialize)(GLuint uiBufSize, GLuint uiEleBufSize)
{
	OutputDebugStringA("initialize\n");

	ErrMsg err = { GLLS_ERRMSG_ALL };
	GLuint prog = LoadProgramByBinary("ButtonTest.bin", &err);
	if (!err.msg.empty())
	{
		OutputDebugStringA(err.msg.c_str());
		return;
	}

	glGenVertexArrays(1, &ButtonTest::vaUi);
	glBindVertexArray(ButtonTest::vaUi);
	
	glGenBuffers(1, &ButtonTest::vbUi);
	glBindBuffer(GL_ARRAY_BUFFER, ButtonTest::vbUi);

	glGenBuffers(1, &ButtonTest::veUi);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ButtonTest::veUi);

	glNamedBufferStorage(ButtonTest::vbUi, uiBufSize, NULL, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferStorage(ButtonTest::veUi, uiEleBufSize, NULL, GL_DYNAMIC_STORAGE_BIT);
	glUseProgram(prog);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void APP_FUNCTION(ButtonTest, finalize)()
{
	OutputDebugStringA("finalize\n");
}

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