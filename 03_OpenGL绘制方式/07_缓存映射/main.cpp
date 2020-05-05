#include "global.h"

#include "vgl.h"
#include "vapp.h"
#include "vtype.h"

#include "LoadShaders.h"

#define INVALID_COORD -2.0f
typedef std::pair<GLfloat, GLfloat> Point;

BEGIN_APP_DECLARATION(BufferMapTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
	
	virtual void OnMouse(int button, int action, int mods);
	virtual void OnCursorNorm(float x, float y);
private:
	GLuint vao = 0, vbo = 0;
	GLint pointId = -1;

	std::array<vec2, 3> vert;
	std::array<vec3, 3> color;
	GLboolean isPress = GL_FALSE;
	GLfloat oldX = INVALID_COORD, oldY = INVALID_COORD;

	void refreshPointId(const Point& cursor);
	GLboolean surroundPoint(const Point& p1, const Point& p2, const GLfloat& diff = 0.05f);
END_APP_DECLARATION()

DEFINE_APP(BufferMapTest, "buffer map test")

void BufferMapTest::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	ErrMsg err = { GLLS_ERRMSG_ALL };
	GLuint prog = LoadProgramByBinary("BufferMap.bin", &err);
	if (!err.msg.empty())
	{
		OutputDebugStringA(err.msg.c_str());
		return;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vert.size() * vert[0].size() + color.size() * color[0].size(), NULL, GL_DYNAMIC_DRAW);

	void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	FILE* infile;
	fopen_s(&infile, "BufferMapData.bin", "rb");
	if (infile)
	{
		fread(data, 1, vert.size() * vert[0].size() + color.size() * color[0].size(), infile);
		GLuint offset = 0;
		for (vec2 & v : vert)
			offset += v.read((GLchar*)data + offset, v.size());
		for (vec3& c : color)
			offset += c.read((GLchar*)data + offset, c.size());
		fclose(infile);
	}
	else
	{
		vert = { vec2(0.0f, 0.9f), vec2(-0.9f, -0.9f), vec2(0.9f, -0.9f) };
		GLuint offset = 0;
		for (vec2& v : vert)
			offset += v.write((GLchar*)data + offset, v.size());
		color = { vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f) };
		for (vec3& v : color)
			offset += v.write((GLchar*)data + offset, v.size());
	}


	glUnmapBuffer(GL_ARRAY_BUFFER);

	glUseProgram(prog);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(vert.size() * vert[0].size()));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glPointSize(10.0f);
}

void BufferMapTest::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);	
	if (-1 != pointId)
		glDrawArrays(GL_POINTS, pointId, 1);

	base::Display(auto_redraw);
}

void BufferMapTest::Finalize()
{
	FILE* infile;
	fopen_s(&infile, "BufferMapData.bin", "wb");
	if (infile)
	{
		void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
		fwrite(data, 1, vert.size() * vert[0].size() + color.size() * color[0].size(), infile);
		fclose(infile);
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}


void BufferMapTest::OnMouse(int button, int action, int mods)
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
			void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			if (-1 == pointId)
			{
				vert = { vec2(0.0f, 0.9f), vec2(-0.9f, -0.9f), vec2(0.9f, -0.9f) };
				GLuint offset = 0;
				for (vec2& v : vert)
					offset += v.write((GLchar*)data + offset, v.size());
				color = { vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f) };
				for (vec3& v : color)
					offset += v.write((GLchar*)data + offset, v.size());
			}
			else
			{
				std::random_device rd;  // 将用于获得随机数引擎的种子
				std::mt19937 gen(rd()); // 以 rd() 播种的标准 mersenne_twister_engine
				std::uniform_real_distribution<GLfloat> dis(0, 1);

				vec3& v = color[pointId];
				v = { dis(gen), dis(gen), dis(gen) };
				v.write((GLchar*)data + vert.size() * vert[0].size() + pointId * v.size(), v.size());
			}
			glUnmapBuffer(GL_ARRAY_BUFFER);
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

void BufferMapTest::OnCursorNorm(float x, float y)
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

	vec2 &p = vert[pointId];
	p[0] += x - oldX;
	p[1] += y - oldY;
	oldX = x;
	oldY = y;

	void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	p.write((GLchar*)data + p.size() * pointId, p.size());
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void BufferMapTest::refreshPointId(const Point& cursor)
{
	if (-1 != pointId && !surroundPoint({ vert[pointId][0], vert[pointId][1] }, cursor))
	{
		pointId = -1;
		return;
	}

	pointId = 0;
	for (vec2& p : vert)
	{
		if (surroundPoint({ p[0], p[1] }, cursor))
			return;
		++pointId;
	}
	pointId = -1;
}

GLboolean BufferMapTest::surroundPoint(const Point& p1, const Point& p2, const GLfloat& diff)
{
	GLfloat
		distX = p1.first - p2.first,
		distY = p1.second - p2.second;

	GLfloat distance = distX * distX + distY * distY;
	GLfloat distDiff = diff * diff;

	return distance < distDiff ? GL_TRUE : GL_FALSE;
}
