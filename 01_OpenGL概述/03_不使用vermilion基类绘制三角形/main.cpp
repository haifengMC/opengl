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
	//1 分配顶点数组对象到数组 glGenVertexArrays()
	glGenVertexArrays(numVaoId, vaos);
	//2 绑定顶点数组对象到环境 glBindVertexArray()
	glBindVertexArray(vaos[VaoId_Triangle]);
	//3 创建缓存对象到数组 glCreateBuffers()
	glCreateBuffers(numBufId, bufs);
	//4 绑定缓存对象到target对应的结合点 glBindBuffer()
	glBindBuffer(GL_ARRAY_BUFFER, bufs[BufId_Triangle]);
	//5 创建并初始化缓存对象的固定数据存储区 glBufferStorage()
	GLfloat vertices[numVertices][2] =
	{
		{ 0.9f, 0.9f }, { 0.9f, -0.85f }, { -0.85f, 0.9f },//triangle1
		{ -0.9f, -0.9f }, { -0.9f, 0.85f }, { 0.85f, -0.9f },//triangle2
	};
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);
	//6 设置顶点属性值 glVertexAttribPointer()
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//7 激活顶点属性 glEnableVertexAttribArray()
	glEnableVertexAttribArray(vPosition);
	//8 加载着色器 LoadShaders()
	ShaderInfo shaders[] =
	{
		{GL_VERTEX_SHADER, "triangleNotByVermilion.vert"},
		{GL_FRAGMENT_SHADER, "triangleNotByVermilion.frag"},
		{GL_NONE, NULL},
	};
	GLuint prog = LoadShaders(shaders);
	//9 设置当前所使用的程序 glUseProgram()
	glUseProgram(prog);
}

void display()
{
	//1 清除颜色缓冲区 glClearBufferfv()
	static GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	//2 绑定顶点数组对象到环境 glBindVertexArray()
	glBindVertexArray(vaos[VaoId_Triangle]);
	//3 使用非索引形式绘制 glDrawArrays()
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//1 初始化GLFW库 glfwInit()
	glfwInit();
	//2 创建窗口及其上下文 glfwCreateWindow()
	GLFWwindow* window = glfwCreateWindow(800, 600, "draw a triangle not by vermilion", NULL, NULL);
	//3 设置当前所使用的上下文 glfwMakeContextCurrent()
	glfwMakeContextCurrent(window);
	//4 初始化GL3W库 gl3wInit()
	gl3wInit();
	//5 初始化程序相关 init()
	init();
	//6 创建主循环并监测窗口的关闭标志位 glfwWindowShouldClose()
	while (!glfwWindowShouldClose(window))
	{
		//7 绘制程序相关 display()
		display();
		//8 交换窗口的前后缓冲区 glfwSwapBuffers()
		glfwSwapBuffers(window);
		//9 处理所有挂起的事件 glfwPollEvents()
		glfwPollEvents();
	}
	//10 销毁窗口及其上下文 glfwDestroyWindow()
	glfwDestroyWindow(window);
	//11 终止GLFW库 glfwTerminate()
	glfwTerminate();

	return 0;
}