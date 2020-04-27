#include "global.h"

#include "vgl.h"
#include "vapp.h"

#include "LoadShaders.h"

BEGIN_APP_DECLARATION(LoadBinaryProgram)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();

private:
	GLuint vao = 0, vbo = 0;
END_APP_DECLARATION()
DEFINE_APP(LoadBinaryProgram, "load binary program")

void LoadBinaryProgram::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	ErrMsg errMsg = { GLLS_ERRMSG_ALL };
	GLuint prog = LoadProgramByBinary("triangleNotByVermilion.bin", &errMsg);
	if (!errMsg.msg.empty())
		OutputDebugStringA(errMsg.msg.c_str());

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);

	GLfloat vertices[] =
	{
		0.0f, 0.9f,
		-0.9f, -0.9f,
		0.9f, -0.9f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, GL_FLOAT, vertices, GL_STATIC_DRAW);

	glUseProgram(prog);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
}

void LoadBinaryProgram::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	base::Display(auto_redraw);
}

void LoadBinaryProgram::Finalize()
{

}
