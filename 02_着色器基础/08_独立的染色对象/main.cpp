#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"

#include <iostream>
#include <sstream>

BEGIN_APP_DECLARATION(SeparateShaderObjects)
	void Initialize(const char* title /* = 0 */);
	void Display(bool auto_redraw /* = true */);
	void Finalize();

	void OnMouse(int button, int action, int mods);
private:
	GLuint SeparateShaderProgram(GLuint shader);

	GLuint pipeline;

	GLuint vProgram = 0;
	GLuint fPrograms[2];
	GLuint fProgIdx = 0;

	GLuint vao = 0, vbo = 0;
END_APP_DECLARATION()
DEFINE_APP(SeparateShaderObjects, "separate shader objects test")

void SeparateShaderObjects::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);
	
	ShaderInfo shaders[]
	{
		{GL_VERTEX_SHADER, "SeparateShaderTest.vert"},
		{GL_FRAGMENT_SHADER, "SeparateShaderTest1.frag"},
		{GL_FRAGMENT_SHADER, "SeparateShaderTest2.frag"},
	};
	GLuint vshader = LoadShader(shaders);
	GLuint fshader1 = LoadShader(shaders + 1);
	GLuint fshader2 = LoadShader(shaders + 2);
	if (!vshader || !fshader1 || !fshader2)
		return;

	vProgram = SeparateShaderProgram(vshader);
	fPrograms[0] = SeparateShaderProgram(fshader1);
	fPrograms[1] = SeparateShaderProgram(fshader2);
	if (!vProgram || !fPrograms[0] || !fPrograms[1])
		return;

	glDeleteShader(vshader);
	glDeleteShader(fshader1);
	glDeleteShader(fshader2);

	GLfloat vPos[] =
	{
		0.0f, 0.9f,
		-0.9f, -0.9f,
		0.9f, -0.9f,
	};

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glNamedBufferStorage(vbo, sizeof(vPos), vPos, 0);
	
	glCreateProgramPipelines(1, &pipeline);
	glBindProgramPipeline(pipeline);
	glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vProgram);
	glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fPrograms[0]);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
}

void SeparateShaderObjects::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	base::Display(auto_redraw);
}

void SeparateShaderObjects::Finalize()
{

}

void SeparateShaderObjects::OnMouse(int button, int action, int mods)
{
	if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_PRESS == action)
	{
		glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fPrograms[++fProgIdx % 2]);
	}
}

GLuint SeparateShaderObjects::SeparateShaderProgram(GLuint	shader)
{
	GLuint program = glCreateProgram();

	if (!program)
		return 0;

	glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);

	glAttachShader(program, shader);
	glLinkProgram(program);
	GLint link = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link);
	if (!link)
	{
#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		std::ostringstream os;
		os << "Program[" << program << "] shader linking failed: " << log << std::endl;
#ifdef WIN32
		OutputDebugString(os.str().c_str());
#endif // WIN32
		std::cerr << os.str();
		delete[] log;
#endif /* DEBUG */

		return 0;
	}

	glDetachShader(program, shader);
	return program;
}