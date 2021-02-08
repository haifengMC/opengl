#include "global.h"

#include "vgl.h"
#include "vapp.h"

#include "vcommon.h"
#include "vbuffer.h"
#include "hTool.h"
#include "hConfig.h"
#include "LoadShaders.h"

BEG_CFGDATA(StaticVertexAttribCfg)
{
	std::string shaderName;
	GLuint vertLoc = 0;
	GLuint colorLoc = 0;
	GLfloat vertice[3][2] = {};
	GLfloat staticColor[3] = {};
	GLfloat colors[3][3] = {};
}
END_CFGDATA(StaticVertexAttribCfg, shaderName, vertLoc, colorLoc, vertice, staticColor, colors)

BEGIN_APP_DECLARATION(StaticVertexAttrib)
	void Initialize(const char* title /* = 0 */);
	void Display(bool auto_redraw /* = true */);
	void Finalize();

	void OnMouse(int button, int action, int mods);
private:
	GLuint vao = 0, vbo = 0;

	BufferCountManager<> bufCntMgr;
	StaticVertexAttribCfg cfg = StaticVertexAttribCfg("StaticVertexAttribCfg.yml");
END_APP_DECLARATION()
DEFINE_APP(StaticVertexAttrib, "static vertex attribute")

void StaticVertexAttrib::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	if (!cfg.loadCfg())
	{
		OutputDebugStringA("≈‰÷√º”‘ÿ ß∞‹£°");
		return;
	}
	

	ErrMsg err = { GLLS_ERRMSG_ALL };
	GLuint prog = LoadProgramByBinary("StaticVertexAttrib.bin", &err);
	if (!err.msg.empty())
	{
		OutputDebugStringA(err.msg.c_str());
		return;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	bufCntMgr.addData("vertice", sizeof(GLfloat), 2 * 3);
	bufCntMgr.addData("colors", sizeof(GLfloat), 3 * 3);
	glBufferData(GL_ARRAY_BUFFER, bufCntMgr.getSize(), NULL, GL_DYNAMIC_DRAW);
	void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy((GLchar*)data + bufCntMgr.getOffset("vertice"), cfg.data.vertice, bufCntMgr.getSize("vertice"));
	memcpy((GLchar*)data + bufCntMgr.getOffset("colors"), cfg.data.colors, bufCntMgr.getSize("colors"));

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUseProgram(prog);

	glVertexAttribPointer(cfg.data.vertLoc, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)bufCntMgr.getOffset("vertice"));
	glVertexAttribPointer(cfg.data.colorLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)bufCntMgr.getOffset("colors"));
	glEnableVertexAttribArray(cfg.data.vertLoc);
	//glEnableVertexAttribArray(cfg.colorLoc);
	glVertexAttrib3fv(cfg.data.colorLoc, cfg.data.staticColor);
}

void StaticVertexAttrib::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	base::Display(auto_redraw);
}

void StaticVertexAttrib::Finalize()
{
	
}

void StaticVertexAttrib::OnMouse(int button, int action, int mods)
{
	switch (button)
	{
	case  GLFW_MOUSE_BUTTON_LEFT:
		switch (action)
		{
		case  GLFW_PRESS:
			glEnableVertexAttribArray(cfg.data.colorLoc);
			break;
		case GLFW_RELEASE:
			glDisableVertexAttribArray(cfg.data.colorLoc);
			break;
		default:
			break;
		}
		break;
	}
}

