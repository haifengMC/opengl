#include "global.h"

#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(BufferBlockTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();

	GLuint bufObj;
	GLfloat buf = 0.0f;
END_APP_DECLARATION()
DEFINE_APP(BufferBlockTest, "buffer block test")

void BufferBlockTest::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);
	ShaderInfo shader[] =
	{
		{GL_VERTEX_SHADER, "bufferBlockTest.vert"},
		{GL_FRAGMENT_SHADER, "bufferBlockTest.frag"},
		{GL_NONE, NULL},
	};
	GLuint program = LoadShaders(shader);
	glUseProgram(program);
	glPointSize(10);
	glCreateBuffers(1, &bufObj);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufObj);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, bufObj);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(buf), &buf, GL_DYNAMIC_COPY);
}

void BufferBlockTest::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, 1); 

	base::Display(auto_redraw);

	if (buf)
	{
		GLchar cBuf[128] = "";
		sprintf_s(cBuf, "%f\n", buf);
		OutputDebugString(cBuf);
	}
}

void BufferBlockTest::Finalize()
{

}