#include "global.h"

#include "hRect.h"
#include "hObject.h"
#include "hButton.h"

#include "hConfig.h"

#include "LoadShaders.h"
#include "ButtonTest.h"
#include "ButtonTestUi.h"

bool ButtonTest::preInit()
{
	setUi(new ButtonTestUi);

	setName("ButtonTest");
	addShader(GL_VERTEX_SHADER, "ButtonTest.vert");
	addShader(GL_FRAGMENT_SHADER, "ButtonTest.frag");

	return true;
}

bool ButtonTest::onInit()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLfloat vertices[6][2] =
	{
		{0.9f, -0.75f}, {0.9f, 0.9f}, {-0.75f, 0.9f},//triangle1
		{-0.9f, 0.75f}, {-0.9f, -0.9f}, {0.75f, -0.9f}//triangle2
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//7 ��������ֵglVertexAttribPointer()
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
	//8 ��������ֵglEnableVertexAttriArray()
	glEnableVertexAttribArray(0);

	return true;
}

bool ButtonTest::onDisplay()
{
	//2 �������������󶨵�OpenGL����glBindVertexArray()
	glBindVertexArray(vao);
	//3 ʹ�÷�������ʽ����
	glDrawArrays(GL_TRIANGLES, 0, 6);

	return true;
}

#if 0
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
