#include "global.h"

#include "vgl.h"
#include "vapp.h"

#include "LoadShaders.h"

#define INVALID_COORD -2.0f
typedef std::pair<GLfloat, GLfloat> Point;

BEGIN_APP_DECLARATION(UnnamedBufferOperation)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
	
	virtual void OnMouse(int button, int action, int mods);
	virtual void OnCursorNorm(float x, float y);
private:
	GLuint vao = 0, vbo = 0;
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

DEFINE_APP(UnnamedBufferOperation, "unnamed buffer operation")

void UnnamedBufferOperation::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	ErrMsg errMsg = { GLLS_ERRMSG_ALL };
	GLuint prog = LoadProgramByBinary("UnnamedBufferOperation.bin", &errMsg);
	if (errMsg.err())
	{
		OutputDebugStringA(errMsg.msg.c_str());
		return;
	}
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle) + sizeof(color), triangle, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangle), sizeof(color), color);

	glUseProgram(prog);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(triangle));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glPointSize(10.0f);
}

void UnnamedBufferOperation::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	if (-1 != pointId)
		glDrawArrays(GL_POINTS, pointId, 1);

	base::Display(auto_redraw);
}

void UnnamedBufferOperation::Finalize()
{
	
}


void UnnamedBufferOperation::OnMouse(int button, int action, int mods)
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
				GLfloat* pTriangle = (GLfloat*)triangle;
				for (const GLfloat& pt : { 0.0f, 0.9f, -0.9f, -0.9f, 0.9f, -0.9f })
					*(pTriangle++) = pt;

				//glClearBufferSubData(GL_ARRAY_BUFFER, GL_RG32F, 0, sizeof(triangle), GL_RG, GL_FLOAT, triangle);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangle), triangle);
			}
		}
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		{
			if (GLFW_PRESS == action)
			{
				GLfloat tmpTriangle[6];
				glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tmpTriangle), tmpTriangle);
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

void UnnamedBufferOperation::OnCursorNorm(float x, float y)
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
	glClearBufferSubData(GL_ARRAY_BUFFER, GL_RG32F, sizeof(p) * pointId, sizeof(p), GL_RG, GL_FLOAT, p);
}

void UnnamedBufferOperation::refreshPointId(const Point& cursor)
{
	if (-1 != pointId && !surroundPoint({ triangle[pointId][0], triangle[pointId][1] }, cursor))
	{
		pointId = -1;
		return;
	}

	pointId = 0;
	for (GLfloat (&p)[2] : triangle)
	{
		if (surroundPoint({ p[0], p[1] }, cursor))
			return;
		++pointId;
	}
	pointId = -1;
}

GLboolean UnnamedBufferOperation::surroundPoint(const Point& p1, const Point& p2, const GLfloat& diff)
{
	GLfloat 
		distX = p1.first - p2.first,
		distY = p1.second - p2.second;

	GLfloat distance = distX * distX + distY * distY;
	GLfloat distDiff = diff * diff;

	return distance < distDiff ? GL_TRUE : GL_FALSE;
}
