#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"

enum VaoIds { VaoId_Triangle, numVaoId };
enum BufIds { BufId_Triangle, numBufId };
enum AttrId { vPosition = 0 };

GLuint vaos[numVaoId];
GLuint bufs[numBufId];
const GLuint numVertices = 6;

BEGIN_APP_DECLARATION(TriangleByVermilion)
	void Initialize(const char* title /* = 0 */);
	void Display(bool auto_redraw /* = true */);
	void Finalize();
	void Resize(int width, int height);
END_APP_DECLARATION()
DEFINE_APP(TriangleByVermilion, "draw a triangle by vermilion")




void TriangleByVermilion::Initialize(const char* title)
{
	//1 ��ʼ������base::Initialize()
	base::Initialize(title);
	//2 ���䶥�������������glGenVertexArrays()
	glGenVertexArrays(numVaoId, vaos);
	//3 �������������󶨵�OpenGL����glBindVertexArray()
	glBindVertexArray(vaos[VaoId_Triangle]);
	//4 ���������������glGenBuffers()
	glGenBuffers(numBufId, bufs);
	//5 ���������󶨵�target��Ӧ�Ľ�ϵ�glBindBuffer()
	glBindBuffer(GL_ARRAY_BUFFER, bufs[BufId_Triangle]);
	//6 ��������ʼ��������������glBufferData()
	GLfloat vertices[numVertices][2] =
	{
		{0.9f, -0.75f}, {0.9f, 0.9f}, {-0.75f, 0.9f},//triangle1
		{-0.9f, 0.75f}, {-0.9f, -0.9f}, {0.75f, 0.9f}//triangle2
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//7 ��������ֵglVertexAttribPointer()
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
	//8 ��������ֵglEnableVertexAttriArray()
	glEnableVertexAttribArray(vPosition);
	//9 ������ɫ��LoadShader()
	ShaderInfo shaders[] =
	{
		{GL_VERTEX_SHADER, "triangleByVermilion.vert"},
		{GL_FRAGMENT_SHADER, "triangleByVermilion.frag"},
		{GL_NONE, NULL}
	};
	GLuint prog = LoadShaders(shaders);
	//10 ʹ�õ�ǰ����glUseProgram()
	glUseProgram(prog);
}

void TriangleByVermilion::Display(bool auto_redraw)
{
	//1 �����ɫ����glClear()
	glClear(GL_COLOR_BUFFER_BIT);
	//2 �������������󶨵�OpenGL����glBindVertexArray()
	glBindVertexArray(vaos[VaoId_Triangle]);
	//3 ʹ�÷�������ʽ����
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	//4 ���ƻ���
	base::Display(auto_redraw);
}

void TriangleByVermilion::Finalize()
{
	//��
}

void TriangleByVermilion::Resize(int width, int height)
{
	//�����ӿ�
	glViewport(0, 0, width, height);
}