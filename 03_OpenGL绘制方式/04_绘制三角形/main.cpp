#include "global.h"

#include "vgl.h"
#include "vapp.h"

#include "LoadShaders.h"

BEGIN_APP_DECLARATION(DrawTriangleTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
	
	virtual void OnKey(int key, int scancode, int action, int mods);
	virtual void OnMouse(int button, int action, int mods);
	virtual void OnScroll(double x, double y);
private:
	GLuint drawId = 0;
	GLenum draws[3] = { GL_TRIANGLES, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP };
	GLuint modeId = 0;
	GLenum modes[3] = { GL_FILL, GL_LINE, GL_POINT };
	GLboolean isCull = GL_FALSE;
	GLuint cullId = 0;
	GLenum culls[3] = { GL_FRONT, GL_BACK, GL_FRONT_AND_BACK };
	GLuint faceId = 0;
	GLenum faces[2] = { GL_CCW, GL_CW };

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
	glFrontFace(faces[faceId % countof(faces)]);
	if (isCull % 2)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
	glCullFace(culls[cullId % countof(culls)]);
	glDrawArrays(draws[drawId % countof(draws)], 0, countof(vertices) / 2);

	base::Display(auto_redraw);
}

void DrawTriangleTest::Finalize()
{

}

void DrawTriangleTest::OnKey(int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_Z:
		{
			if (GLFW_PRESS == action)
				++faceId;
		}
		break;
	default:
		break;
	}
}

void DrawTriangleTest::OnMouse(int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		{
			if (GLFW_PRESS == action)
				++drawId;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		{
			if (GLFW_PRESS == action)
				++modeId;
		}
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		{
			if (GLFW_PRESS == action)
				++isCull;
		}
		break;
	default:
		break;
	}
}

void DrawTriangleTest::OnScroll(double x, double y)
{
	if (y >= 0 || cullId >= -y)
	{
		cullId += y;
		return;
	}

	cullId += countof(culls) + y;
}