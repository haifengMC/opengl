#include <string>

#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"
#include "tools.h"

BEGIN_APP_DECLARATION(OutputShaderLog)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
END_APP_DECLARATION()
DEFINE_APP(OutputShaderLog, "output shader log")

void OutputShaderLog::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);
	OutputDebugString("initialize OutputShaderLog\n");

	ShaderInfo shader[] = 
	{
		{ GL_VERTEX_SHADER, "outputShaderLog.vert"},
		{ GL_FRAGMENT_SHADER, "outputShaderLog.frag"},
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shader);

	GLchar vertBuf[1024] = "";
	GLsizei vertBufLen = 0;
	glGetShaderInfoLog(shader[0].shader, sizeof(vertBuf), &vertBufLen, vertBuf);
	std::string vertStr;
	toANSI(vertBuf, vertStr);
	OutputDebugString(vertStr.c_str());

	glUseProgram(program);
}

void OutputShaderLog::Display(bool auto_redraw /* = true */)
{
	base::Display(auto_redraw);
}

void OutputShaderLog::Finalize()
{
	base::Finalize();
}