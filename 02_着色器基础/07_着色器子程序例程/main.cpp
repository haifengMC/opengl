#include "global.h"

#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(ShaderSubroutineExample)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();

	GLint materialShaderLoc = -1;
	GLuint ambientIndex = 0;
	GLuint diffuseIndex = 0;
END_APP_DECLARATION()
DEFINE_APP(ShaderSubroutineExample, "shader subroutine example")

void ShaderSubroutineExample::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	ShaderInfo shader[] =
	{
		{ GL_VERTEX_SHADER, "subroutineExample.vert" },
		{ GL_FRAGMENT_SHADER, "subroutineExample.frag" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shader);
	glUseProgram(program);

	materialShaderLoc = glGetSubroutineUniformLocation(program, GL_VERTEX_SHADER, "materialShader");
	if (materialShaderLoc < 0)
	{
		//����materialShader������ɫ�������õ��ӳ���uniform
		//uniform in the shader
		OutputDebugString("����materialShader������ɫ�������õ��ӳ���uniform");
		return;
	}
	ambientIndex = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "ambient");
	diffuseIndex = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "diffuse");
	if (ambientIndex == GL_INVALID_INDEX || diffuseIndex == GL_INVALID_INDEX)
	{
		//����ָ�����ӳ�����GL_VERTEX_SHADER�׶ε�ǰ�󶨵ĳ�����û������
		OutputDebugString("����ָ�����ӳ�����GL_VERTEX_SHADER�׶ε�ǰ�󶨵ĳ�����û������");
		return;
	}
	GLsizei n;
	glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &n);
	GLuint* indices = new GLuint[n];
	indices[materialShaderLoc] = ambientIndex;
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, n, indices);
	delete[] indices;
}

void ShaderSubroutineExample::Display(bool auto_redraw /* = true */)
{
	base::Display(auto_redraw);
}

void ShaderSubroutineExample::Finalize()
{

}