#include "global.h"

#include "vgl.h"
#include "vapp.h"

#include "LoadShaders.h"

#define INVALID_COORD -2.0f
typedef std::pair<GLfloat, GLfloat> Point;

BEGIN_APP_DECLARATION(NamedBufferOperation)
virtual void Initialize(const char* title /* = 0 */);
virtual void Display(bool auto_redraw /* = true */);
virtual void Finalize();

virtual void OnMouse(int button, int action, int mods);
virtual void OnCursorNorm(float x, float y);
private:
	GLuint vao = 0, vbo[2];
	GLint pointId = -1;
	GLfloat triangle[3][2] =
	{
		{ 0.0f, 0.9f },
		{ -0.9f, -0.9f },
		{ 0.9f, -0.9f },
	};
	GLfloat color[3][3] =
	{
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
	};
	GLboolean isPress = GL_FALSE;
	GLfloat oldX = INVALID_COORD, oldY = INVALID_COORD;

	void refreshPointId(const Point& cursor);
	GLboolean surroundPoint(const Point& p1, const Point& p2, const GLfloat& diff = 0.05f);
END_APP_DECLARATION()

DEFINE_APP(NamedBufferOperation, "named buffer operation")

void NamedBufferOperation::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	ErrMsg errMsg = { GLLS_ERRMSG_ALL };
	GLuint prog = LoadProgramByBinary("NamedBufferOperation.bin", &errMsg);
	if (errMsg.err())
	{
		OutputDebugStringA(errMsg.msg.c_str());
		return;
	}
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_COPY_READ_BUFFER, vbo[1]);
	glNamedBufferStorage(vbo[0], sizeof(triangle) + sizeof(color), triangle, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(vbo[0], sizeof(triangle), sizeof(color), color);
	glNamedBufferStorage(vbo[1], sizeof(triangle), triangle, 0);

	glUseProgram(prog);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(triangle));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glPointSize(10.0f);
}

void NamedBufferOperation::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	if (-1 != pointId)
		glDrawArrays(GL_POINTS, pointId, 1);

	base::Display(auto_redraw);
}

void NamedBufferOperation::Finalize()
{

}


void NamedBufferOperation::OnMouse(int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		switch (action)
		{
		case  GLFW_PRESS:
		{
			isPress = GL_TRUE;
		}
		break;
		case GLFW_RELEASE:
		{
			isPress = GL_FALSE;
			oldX = oldY = INVALID_COORD;
		}
		break;
		default:
			break;
		}
	}
	break;
	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		if (GLFW_PRESS == action)
		{
			glCopyNamedBufferSubData(vbo[1], vbo[0], 0, 0, sizeof(triangle));
			glGetNamedBufferSubData(vbo[0], 0, sizeof(triangle), triangle);
		}
	}
	break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (GLFW_PRESS == action)
		{
			GLfloat tmpTriangle[6];
			glGetNamedBufferSubData(vbo[0], 0, sizeof(tmpTriangle), tmpTriangle);
			std::stringstream os;
			for (GLfloat f : tmpTriangle)
				os << f << " ";
			OutputDebugStringA(os.str().c_str());
		}
	}
	break;
	default:
		break;
	}
}

void NamedBufferOperation::OnCursorNorm(float x, float y)
{
	if (!isPress)
	{
		GLint oldPointId = pointId;
		refreshPointId({ x, y });
		if (oldPointId != pointId)
		{
			char buf[64] = "";
			sprintf_s(buf, "%d\n", pointId);
			OutputDebugStringA(buf);
		}
	}

	if (!isPress || -1 == pointId) return;

	if (INVALID_COORD == oldX || INVALID_COORD == oldY)
	{
		oldX = x;
		oldY = y;
		return;
	}

	GLfloat(&p)[2] = triangle[pointId];
	p[0] += x - oldX;
	p[1] += y - oldY;
	oldX = x;
	oldY = y;
	glClearNamedBufferSubData(vbo[0], GL_RG32F, sizeof(p) * pointId, sizeof(p), GL_RG, GL_FLOAT, p);
}

void NamedBufferOperation::refreshPointId(const Point& cursor)
{
	if (-1 != pointId && !surroundPoint({ triangle[pointId][0], triangle[pointId][1] }, cursor))
	{
		pointId = -1;
		return;
	}

	pointId = 0;
	for (GLfloat(&p)[2] : triangle)
	{
		if (surroundPoint({ p[0], p[1] }, cursor))
			return;
		++pointId;
	}
	pointId = -1;
}

GLboolean NamedBufferOperation::surroundPoint(const Point& p1, const Point& p2, const GLfloat& diff)
{
	GLfloat
		distX = p1.first - p2.first,
		distY = p1.second - p2.second;

	GLfloat distance = distX * distX + distY * distY;
	GLfloat distDiff = diff * diff;

	return distance < distDiff ? GL_TRUE : GL_FALSE;
}
