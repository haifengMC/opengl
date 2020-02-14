#include <sstream>

#include "vapp.h"
#include "vgl.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(ShaderSubroutineTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
	virtual void OnKey(int key, int scancode, int action, int mods);

	GLuint vao = 0;
	GLint** funcLocs = NULL;
	GLsizei numFuncLocs = 0;
	GLuint* indices = NULL;
	GLuint* idxindices = NULL;
END_APP_DECLARATION()

DEFINE_APP(ShaderSubroutineTest, "shader subroutine test")


void ShaderSubroutineTest::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	glPointSize(10);

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLfloat points[] = { -0.85f, 0.0f, 0.0f, 0.0f, 0.85f, 0.0f };
	glNamedBufferStorage(vbo, sizeof(points), points, 0);

	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "subroutineTest.vert" },
		{ GL_FRAGMENT_SHADER,"subroutineTest.frag" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	
	GLsizei maxSub, maxSubU, activeS;
	glGetIntegerv(GL_MAX_SUBROUTINES, &maxSub);
	glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &maxSubU);
	std::stringstream oss;
	oss << "Max Subroutines:" << maxSub << ", " << "Max Subroutine Uniforms:" << maxSubU << std::endl;
	OutputDebugString(oss.str().c_str());

	const GLsizei NameSize = 256;
	char name[NameSize]; int len, numCompS;
	glGetProgramStageiv(program, GL_VERTEX_SHADER, GL_ACTIVE_SUBROUTINE_UNIFORMS, &numFuncLocs);
	funcLocs = new GLint * [numFuncLocs];
	indices = new GLuint[numFuncLocs];
	idxindices = new GLuint[numFuncLocs];
	for (int i = 0; i < numFuncLocs; ++i) {
		glGetActiveSubroutineUniformName(program, GL_VERTEX_SHADER, i, NameSize, &len, name);
		oss.str("");
		oss << "Subroutine Uniform:" << i << ", " << "name:" << name << std::endl;
		OutputDebugString(oss.str().c_str());

		glGetActiveSubroutineUniformiv(program, GL_VERTEX_SHADER, i, GL_NUM_COMPATIBLE_SUBROUTINES, &numCompS);
		funcLocs[i] = new GLint[numCompS + 1];
		glGetActiveSubroutineUniformiv(program, GL_VERTEX_SHADER, i, GL_COMPATIBLE_SUBROUTINES, funcLocs[i]);
		idxindices[i] = 0;
		indices[i] = funcLocs[i][idxindices[i]];
		funcLocs[i][numCompS] = -1;

		for (GLsizei j = 0; j < numCompS; ++j)
		{
			glGetActiveSubroutineName(program, GL_VERTEX_SHADER, funcLocs[i][j], NameSize, &len, name);
			oss.str("");
			oss << "\t" << funcLocs[i][j] << " - " << name << std::endl;
			OutputDebugString(oss.str().c_str());
		}

	}
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, numFuncLocs, indices);
}

void ShaderSubroutineTest::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 3);

	base::Display(auto_redraw);
}

void ShaderSubroutineTest::Finalize()
{
	for (GLsizei i = 0; i < numFuncLocs; ++i)
	{
		delete[] funcLocs[i];
		funcLocs[i] = NULL;
	}
	delete[] funcLocs;
	delete[] indices;
	delete[] idxindices;
}

void ShaderSubroutineTest::OnKey(int key, int scancode, int action, int mods)
{
	if (GLFW_PRESS == action)
	{
		switch (key)
		{
		case GLFW_KEY_1:
		case  GLFW_KEY_KP_1:
			{
				if (-1 == funcLocs[0][idxindices[0] + 1]) indices[0] = funcLocs[0][idxindices[0] = 0];
				else indices[0] = funcLocs[0][++idxindices[0]];
				glUniformSubroutinesuiv(GL_VERTEX_SHADER, numFuncLocs, indices);
			}
			break;
		case GLFW_KEY_2:
		case  GLFW_KEY_KP_2:
			{
				if (-1 == funcLocs[0][idxindices[1] + 1]) indices[1] = funcLocs[1][idxindices[1] = 0];
				else indices[1] = funcLocs[1][++idxindices[1]];
				glUniformSubroutinesuiv(GL_VERTEX_SHADER, numFuncLocs, indices);
			}
			break;
		case GLFW_KEY_3:
		case  GLFW_KEY_KP_3:
			{
				if (-1 == funcLocs[0][idxindices[2] + 1]) indices[2] = funcLocs[2][idxindices[2] = 0];
				else indices[2] = funcLocs[2][++idxindices[2]];
				glUniformSubroutinesuiv(GL_VERTEX_SHADER, numFuncLocs, indices);
			}
			break;
		default:
			break;
		}
	}
} 