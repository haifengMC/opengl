#include "global.h"

#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(UniformBlockTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
	virtual void OnMouse(int button, int action, int mods);
	virtual void OnCursor(double x, double y);

	GLuint bufIdx = GL_NONE;
	GLboolean isClick = GL_FALSE;
END_APP_DECLARATION()
DEFINE_APP(UniformBlockTest, "uniform block test")

struct VPos
{
	GLfloat pos[4];
	GLfloat color[4];
};

void UniformBlockTest::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);
	srand(time(NULL));

	ShaderInfo shader[] =
	{
		{GL_VERTEX_SHADER, "uniformBlockTest.vert"},
		{GL_FRAGMENT_SHADER, "uniformBlockTest.frag"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShaders(shader);
	//��ȡuniform������
	GLuint uniformIdx = glGetUniformBlockIndex(program, "vPos");
	GLint uniformSize = 0;
	//��ȡuniform���С
	glGetActiveUniformBlockiv(program, uniformIdx, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformSize);
	
	//�����������
	glCreateBuffers(1, &bufIdx);
	//��uniform�鵽�������
	//glBindBuffer(GL_UNIFORM_BUFFER, bufIdx);
	glBindBufferBase(GL_UNIFORM_BUFFER, uniformIdx, bufIdx);
	//������д�뻺�����
	VPos vp =
	{
		{0.0f, 0.0f, 0.0f, 1.0f},
		{0.5f, 0.6f, 0.7f, 1.0f}
	};
	glNamedBufferStorage(bufIdx, uniformSize, &vp, GL_DYNAMIC_STORAGE_BIT);
	
	glPointSize(10);
	glUseProgram(program);
}

void UniformBlockTest::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glDrawArrays(GL_POINTS, 0, 1);

	base::Display(auto_redraw);
}

void UniformBlockTest::Finalize()
{

}

void UniformBlockTest::OnMouse(int button, int action, int mods)
{
	if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_PRESS == action)
	{
		isClick = GL_TRUE;
	}
}

void UniformBlockTest::OnCursor(double x, double y)
{
	if (isClick)
	{
		//���������ɫ
		auto getRand = []() { return 0.1f * (rand() % 9 + 1); };
		GLfloat color[3] = { getRand() , getRand(), getRand() };
		glNamedBufferSubData(bufIdx, sizeof(VPos::pos), sizeof(color), color);

		//���������
		int width, height;
		getWindowSize(&width, &height);
		GLfloat pos[2] = { x / width * 2 - 1, - y / height * 2 + 1 };
		glNamedBufferSubData(bufIdx, 0, sizeof(pos), pos);

		isClick = GL_FALSE;
	}
}