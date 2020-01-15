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
	//1 初始化基类base::Initialize()
	base::Initialize(title);
	//2 分配顶点数组对象到数组glGenVertexArrays()
	glGenVertexArrays(numVaoId, vaos);
	//3 将顶点数组对象绑定到OpenGL环境glBindVertexArray()
	glBindVertexArray(vaos[VaoId_Triangle]);
	//4 创建缓存对象到数组glGenBuffers()
	glGenBuffers(numBufId, bufs);
	//5 将缓存对象绑定到target对应的结合点glBindBuffer()
	glBindBuffer(GL_ARRAY_BUFFER, bufs[BufId_Triangle]);
	//6 创建并初始化缓存对象的数据glBufferData()
	GLfloat vertices[numVertices][2] =
	{
		{0.9f, -0.75f}, {0.9f, 0.9f}, {-0.75f, 0.9f},//triangle1
		{-0.9f, 0.75f}, {-0.9f, -0.9f}, {0.75f, 0.9f}//triangle2
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//7 设置属性值glVertexAttribPointer()
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
	//8 激活属性值glEnableVertexAttriArray()
	glEnableVertexAttribArray(vPosition);
	//9 加载着色器LoadShader()
	ShaderInfo shaders[] =
	{
		{GL_VERTEX_SHADER, "triangleByVermilion.vert"},
		{GL_FRAGMENT_SHADER, "triangleByVermilion.frag"},
		{GL_NONE, NULL}
	};
	GLuint prog = LoadShaders(shaders);
	//10 使用当前程序glUseProgram()
	glUseProgram(prog);
}

void TriangleByVermilion::Display(bool auto_redraw)
{
	//1 清除颜色缓存glClear()
	glClear(GL_COLOR_BUFFER_BIT);
	//2 将顶点数组对象绑定到OpenGL环境glBindVertexArray()
	glBindVertexArray(vaos[VaoId_Triangle]);
	//3 使用非索引形式绘制
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	//4 绘制基类
	base::Display(auto_redraw);
}

void TriangleByVermilion::Finalize()
{
	//略
}

void TriangleByVermilion::Resize(int width, int height)
{
	//设置视口
	glViewport(0, 0, width, height);
}