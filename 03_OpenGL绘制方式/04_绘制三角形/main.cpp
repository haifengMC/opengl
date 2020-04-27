#include "global.h"

#include "vgl.h"
#include "vapp.h"

#include "LoadShaders.h"

BEGIN_APP_DECLARATION(DrawTriangleTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
	
	virtual void OnMouse(int button, int action, int mods);
private:
	GLuint drawId = 0;
	GLenum draws[3] = { GL_TRIANGLES, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP };
	GLuint modeId = 0;
	GLenum modes[3] = { GL_FILL, GL_LINE, GL_POINT };

	GLfloat vertices[12] =
	{
		-0.9f, -0.9f,
		0.9f, -0.9f,
		-0.3f, -0.6f,
		0.1f, -0.1f,
		-0.1f, 0.4f,
		0.1f, 0.9f,
	};
	GLuint vao = 0, vbo = 0;
END_APP_DECLARATION()

DEFINE_APP(DrawTriangleTest, "draw triangle test")

void DrawTriangleTest::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	ErrMsg err = { GLLS_ERRMSG_ALL };
	GLuint prog = LoadProgramByBinary("DrawTriangleTest.bin", &err);
	if (!err.msg.empty())
	{
		OutputDebugStringA(err.msg.c_str());
		return;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glUseProgram(prog);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glPointSize(3.0f);
}

void DrawTriangleTest::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glPolygonMode(GL_FRONT_AND_BACK, modes[modeId % countof(modes)]);
	glDrawArrays(draws[drawId % countof(draws)], 0, countof(vertices) / 2);

	base::Display(auto_redraw);
}

void DrawTriangleTest::Finalize()
{

}

void DrawTriangleTest::OnMouse(int button, int action, int mods)
{
	if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_PRESS == action)
		++drawId;
	if (GLFW_MOUSE_BUTTON_RIGHT == button && GLFW_PRESS == action)
		++modeId;
}