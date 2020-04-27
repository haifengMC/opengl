#include "global.h"

#include "vgl.h"
#include "vapp.h"

#include "LoadShaders.h"

BEGIN_APP_DECLARATION(DrawLineTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();

	virtual void OnMouse(int button, int action, int mods);
	virtual void OnScroll(double x, double y);
private:
	GLuint vao = 0, vbo = 0;
	GLenum drawModes[3] = { GL_LINES, GL_LINE_LOOP, GL_LINE_STRIP };
	GLuint drawIdx = 0;
	GLfloat lineWidth = 5.0f;
END_APP_DECLARATION()
DEFINE_APP(DrawLineTest, "draw line test")

void DrawLineTest::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glCreateBuffers(1, &vbo);
	GLfloat vert[] =
	{
		-0.5f, 0.8f,
		-0.5f, -0.8f,
		0.5f, 0.8f,
		0.5f, -0.8f
	};
	glNamedBufferStorage(vbo, sizeof(vert), vert, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	ShaderInfo shaders[] =
	{
		{GL_VERTEX_SHADER, "DrawLineTest.vert"},
		{GL_FRAGMENT_SHADER, "DrawLineTest.frag"},
		{GL_NONE, NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glLineWidth(lineWidth);
}

void DrawLineTest::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(drawModes[drawIdx % countof(drawModes)], 0, 4);

	base::Display(auto_redraw);
}

void DrawLineTest::Finalize()
{

}

void DrawLineTest::OnMouse(int button, int action, int mods)
{
	if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_PRESS == action)
		++drawIdx;
}

void DrawLineTest::OnScroll(double x, double y)
{
	if (lineWidth + y > 1.0f)
		lineWidth += y;
	else
		lineWidth = 1.0f;

	glLineWidth(lineWidth);
}