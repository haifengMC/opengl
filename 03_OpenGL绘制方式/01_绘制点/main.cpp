#include "global.h"

#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(DrawPointTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize(void);
	
	virtual void OnMouse(int button, int action, int mods);
	virtual void OnScroll(double x, double y);
private:
	GLfloat pointSize = 20;
END_APP_DECLARATION()
DEFINE_APP(DrawPointTest, "draw point test")

void DrawPointTest::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	ShaderInfo shaders[] =
	{
		{GL_VERTEX_SHADER, "DrawPointTest.vert"},
		{GL_FRAGMENT_SHADER, "DrawPointTest.frag"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShaders(shaders);
	if (!program)
		return;
	glUseProgram(program);

	glPointSize(10.0f);

	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, &pointSize);
	glEnableVertexAttribArray(0);
}

void DrawPointTest::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, 1);

	base::Display(auto_redraw);
}

void DrawPointTest::Finalize(void)
{

}

void DrawPointTest::OnMouse(int button, int action, int mods)
{
	if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_PRESS == action)
	{
		if (glIsEnabled(GL_PROGRAM_POINT_SIZE))
			glDisable(GL_PROGRAM_POINT_SIZE);
		else
			glEnable(GL_PROGRAM_POINT_SIZE);
	}
}

void DrawPointTest::OnScroll(double x, double y)
{
	if (pointSize + 2 * y >= 1)
		pointSize += 2 * y;
	else
		pointSize = 1.0f;


}
