#include "vgl.h"
#include "vapp.h"

#include "LoadShaders.h"

enum VaoIds { VaoId_Triangle, numVaoId };
enum BufIds { BufId_Triangle, numBufId };
const GLuint numVertices = 6;
GLuint vaos[numVaoId];
GLuint bufs[numBufId];
enum AttrId { vPosition = 0 };

void init()
{
	//1 ���䶥������������� glGenVertexArrays()
	glGenVertexArrays(numVaoId, vaos);
	//2 �󶨶���������󵽻��� glBindVertexArray()
	glBindVertexArray(vaos[VaoId_Triangle]);
	//3 ��������������� glCreateBuffers()
	glCreateBuffers(numBufId, bufs);
	//4 �󶨻������target��Ӧ�Ľ�ϵ� glBindBuffer()
	glBindBuffer(GL_ARRAY_BUFFER, bufs[BufId_Triangle]);
	//5 ��������ʼ���������Ĺ̶����ݴ洢�� glBufferStorage()
	GLfloat vertices[numVertices][2] =
	{
		{ 0.9f, 0.9f }, { 0.9f, -0.85f }, { -0.85f, 0.9f },//triangle1
		{ -0.9f, -0.9f }, { -0.9f, 0.85f }, { 0.85f, -0.9f },//triangle2
	};
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);
	//6 ���ö�������ֵ glVertexAttribPointer()
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//7 ��������� glEnableVertexAttribArray()
	glEnableVertexAttribArray(vPosition);
	//8 ������ɫ�� LoadShaders()
	ShaderInfo shaders[] =
	{
		{GL_VERTEX_SHADER, "triangleNotByVermilion.vert"},
		{GL_FRAGMENT_SHADER, "triangleNotByVermilion.frag"},
		{GL_NONE, NULL},
	};
	GLuint prog = LoadShaders(shaders);
	//9 ���õ�ǰ��ʹ�õĳ��� glUseProgram()
	glUseProgram(prog);
}

void display()
{
	//1 �����ɫ������ glClearBufferfv()
	static GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	//2 �󶨶���������󵽻��� glBindVertexArray()
	glBindVertexArray(vaos[VaoId_Triangle]);
	//3 ʹ�÷�������ʽ���� glDrawArrays()
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//1 ��ʼ��GLFW�� glfwInit()
	glfwInit();
	//2 �������ڼ��������� glfwCreateWindow()
	GLFWwindow* window = glfwCreateWindow(800, 600, "draw a triangle not by vermilion", NULL, NULL);
	//3 ���õ�ǰ��ʹ�õ������� glfwMakeContextCurrent()
	glfwMakeContextCurrent(window);
	//4 ��ʼ��GL3W�� gl3wInit()
	gl3wInit();
	//5 ��ʼ��������� init()
	init();
	//6 ������ѭ������ⴰ�ڵĹرձ�־λ glfwWindowShouldClose()
	while (!glfwWindowShouldClose(window))
	{
		//7 ���Ƴ������ display()
		display();
		//8 �������ڵ�ǰ�󻺳��� glfwSwapBuffers()
		glfwSwapBuffers(window);
		//9 �������й�����¼� glfwPollEvents()
		glfwPollEvents();
	}
	//10 ���ٴ��ڼ��������� glfwDestroyWindow()
	glfwDestroyWindow(window);
	//11 ��ֹGLFW�� glfwTerminate()
	glfwTerminate();

	return 0;
}