#include "global.h"

#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(SpirVTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
private:
	GLuint vao = 0, vbo = 0;
END_APP_DECLARATION()

DEFINE_APP(SpirVTest, "SPIR-V test")

void SpirVTest::Initialize(const char* title)
{
	base::Initialize(title);
	
	ShaderInfo shaders[] =
	{
		{GL_VERTEX_SHADER, "triangleSPIR-V.vert.sqv"},
		{GL_FRAGMENT_SHADER, "triangleSPIR-V.frag.sqv"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShadersBySpirV(shaders);

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLfloat triangle[] =
	{
		0.0f, 0.9f,
		-0.9f, -0.9f,
		0.9f, -0.9f,
	};
	glNamedBufferStorage(vbo, sizeof(triangle), triangle, 0);

	glUseProgram(program);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

}

void SpirVTest::Display(bool auto_redraw)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	base::Display(auto_redraw);
}

void SpirVTest::Finalize()
{
}
