#include "global.h"

#include "vgl.h"
#include "vapp.h"
#include "vtype.h"
#include "vcommon.h"
#include "vbuffer.h"
#include "hConfig.h"

#include "LoadShaders.h"

typedef std::pair<GLfloat, GLfloat> Point;

BEG_CFGDATA(AsyncBufferMapTestCfg)
{
	DECL_CFGDATA(AsyncBufferMapTestCfg);

	std::string shaderName;
	std::string dataName;
	GLfloat invalidCoord;
	GLfloat pointSize;
	GLfloat vertice[3][2];
	GLfloat colors[3][3];
}
END_CFGDATA(AsyncBufferMapTestCfg, shaderName, dataName, invalidCoord, pointSize, vertice, colors)

BEGIN_APP_DECLARATION(AsyncBufferMapTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();

	virtual void OnMouse(int button, int action, int mods);
	virtual void OnCursorNorm(float x, float y);
private:
	GLuint vao = 0, vbo = 0;
	GLint pointId = -1;

	BufferCountManager<> bufCntMgr;
	AsyncBufferMapTestCfg cfg = AsyncBufferMapTestCfg("AsyncBufferMapData.yml");

	GLboolean isPress = GL_FALSE;
	GLfloat oldX, oldY;

	void refreshPointId(const Point& cursor);
	GLboolean surroundPoint(const Point& p1, const Point& p2, const GLfloat& diff = 0.05f);
END_APP_DECLARATION()

DEFINE_APP(AsyncBufferMapTest, "asynchronous buffer map test")

void AsyncBufferMapTest::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	if (!cfg.loadCfg())
	{
		OutputDebugStringA("配置加载失败！");
		return;
	}

	ErrMsg err = { GLLS_ERRMSG_ALL };
	GLuint prog = LoadProgramByBinary(cfg.shaderName.c_str(), &err);
	if (!err.msg.empty())
	{
		OutputDebugStringA(err.msg.c_str());
		return;
	}

	oldX = oldY = cfg.invalidCoord;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	bufCntMgr.addData("vertice", sizeof(GLfloat), 2 * 3);
	bufCntMgr.addData("colors", sizeof(GLfloat), 3 * 3);
	glBufferData(GL_ARRAY_BUFFER, bufCntMgr.getSize(), NULL, GL_DYNAMIC_DRAW);
	void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	FILE* infile;
	fopen_s(&infile, cfg.dataName.c_str(), "rb");
	
	if (infile)
	{
		fread(data, 1, bufCntMgr.getSize(), infile);
		fclose(infile);
	}
	else
	{
		memcpy((GLchar*)data + bufCntMgr.getOffset("vertice"), cfg.vertice, bufCntMgr.getSize("vertice"));
		memcpy((GLchar*)data + bufCntMgr.getOffset("colors"), cfg.colors, bufCntMgr.getSize("colors"));
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUseProgram(prog);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)bufCntMgr.getOffset("vertice"));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)bufCntMgr.getOffset("colors"));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glPointSize(cfg.pointSize);
}

void AsyncBufferMapTest::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	if (-1 != pointId)
		glDrawArrays(GL_POINTS, pointId, 1);

	base::Display(auto_redraw);
}

void AsyncBufferMapTest::Finalize()
{
	FILE* infile;
	fopen_s(&infile, cfg.dataName.c_str(), "wb");
	if (infile)
	{
		void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
		fwrite(data, 1, bufCntMgr.getSize(), infile);
		fclose(infile);
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}

void AsyncBufferMapTest::OnMouse(int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		switch (action)
		{
		case  GLFW_PRESS:
			isPress = GL_TRUE;
			break;
		case GLFW_RELEASE:
			isPress = GL_FALSE;
			oldX = oldY = cfg.invalidCoord;
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
			GLvoid* data = glMapBufferRange(GL_ARRAY_BUFFER, 0, bufCntMgr.getSize(),
					GL_MAP_WRITE_BIT | GL_MAP_FLUSH_EXPLICIT_BIT| GL_MAP_UNSYNCHRONIZED_BIT);
			GLfloat(&vert)[3][2] = *(GLfloat(*)[3][2])((GLchar*)data + bufCntMgr.getOffset("vertice"));
			GLfloat(&color)[3][3] = *(GLfloat(*)[3][3])((GLchar*)data + bufCntMgr.getOffset("colors"));

			if (-1 == pointId)
			{
				memcpy(vert, cfg.vertice, sizeof(vert));
				memcpy(color, cfg.colors, sizeof(color));
			}
			else
			{
				std::random_device rd;  // 将用于获得随机数引擎的种子
				std::mt19937 gen(rd()); // 以 rd() 播种的标准 mersenne_twister_engine
				std::uniform_real_distribution<GLfloat> dis(0, 1);
			
				for (GLfloat& c : color[pointId])
					c = dis(gen);
				glFlushMappedBufferRange(GL_ARRAY_BUFFER,
					bufCntMgr.getOffset("colors", countof(color[pointId]) * pointId),
					sizeof(color[pointId]));
			}
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}
	}
	break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (GLFW_PRESS == action)
		{
			GLchar* data = (GLchar*)glMapBufferRange(GL_ARRAY_BUFFER, 0, bufCntMgr.getSize(), GL_MAP_READ_BIT);
			memcpy(cfg.vertice, data + bufCntMgr.getOffset("vertice"), bufCntMgr.getSize("vertice"));
			memcpy(cfg.colors, data + bufCntMgr.getOffset("colors"), bufCntMgr.getSize("colors"));
			glUnmapBuffer(GL_ARRAY_BUFFER);
			cfg.saveCfg();
		}
	}
	break;
	default:
		break;
	}
}

void AsyncBufferMapTest::OnCursorNorm(float x, float y)
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

	if (cfg.invalidCoord == oldX || cfg.invalidCoord == oldY)
	{
		oldX = x;
		oldY = y;
		return;
	}
	GLfloat(&vert)[2] = 
		*(GLfloat(*)[2])glMapBufferRange(GL_ARRAY_BUFFER, 
			bufCntMgr.getOffset("vertice", 2 * pointId), 2 * sizeof(GL_FLOAT),
			GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

	vert[0] += x - oldX;
	vert[1] += y - oldY;
	oldX = x;
	oldY = y;
	
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void AsyncBufferMapTest::refreshPointId(const Point& cursor)
{
	GLfloat(&vert)[3][2] = 
		*(GLfloat(*)[3][2])glMapBufferRange(GL_ARRAY_BUFFER, 
			bufCntMgr.getOffset("vertice"), bufCntMgr.getSize("vertice"), 
			GL_MAP_READ_BIT /*| GL_MAP_UNSYNCHRONIZED_BIT*/);

	if (-1 != pointId && !surroundPoint({ vert[pointId][0], vert[pointId][1] }, cursor))
	{
		pointId = -1;
		glUnmapBuffer(GL_ARRAY_BUFFER);
		return;
	}

	pointId = 0;
	for (GLfloat(&p)[2] : vert)
	{
		if (surroundPoint({ p[0], p[1] }, cursor))
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			return;
		}
		++pointId;
	}
	pointId = -1;
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

GLboolean AsyncBufferMapTest::surroundPoint(const Point& p1, const Point& p2, const GLfloat& diff)
{
	GLfloat
		distX = p1.first - p2.first,
		distY = p1.second - p2.second;

	GLfloat distance = distX * distX + distY * distY;
	GLfloat distDiff = diff * diff;

	return distance < distDiff ? GL_TRUE : GL_FALSE;
}

