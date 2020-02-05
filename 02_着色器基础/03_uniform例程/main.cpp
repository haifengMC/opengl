#include <stdlib.h>

#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"
#include "vtools.h"

const char vShader[] =
{
	"#version 450 core\n"
	"uniform Uniforms"
	"{"
	"	vec3	translation;"
	"	float	scale;"
	"	vec4	rotation;"
	"	bool	enabled;"
	"};"
	"layout (location = 0) in vec2 vPos;"
	//"in vec3	vColor;"
	"out vec4	fColor;"
	"void main()"
	"{"
	"	vec3	pos = vec3(vPos, 0.0);"
	"	float	angle = radians(rotation[0]);"
	"	vec3	axis = normalize(rotation.yzw);"
	"	mat3	I = mat3(1.0);"
	"	mat3	S = mat3(0,			-axis.z,	axis.y,"
	"					axis.z,		0,			-axis.x,"
	"					-axis.y,	axis.x,		0);"
	"	mat3 uuT = outerProduct(axis, axis);"
	"	mat3 rot = uuT + cos(angle) * (I - uuT) + sin(angle) * S;"
	"	pos *= scale;"
	"	pos *= rot;"
	"	pos += translation;"
	"	fColor = vec4(scale, scale, scale, 1);"
	//"	fColor = vec4(1, 0, 1, 1);"
	"	gl_Position = vec4(pos, 1);"
	"}"
};
const char fShader[] =
{
	"#version 450 core\n"
	"uniform Uniforms"
	"{"
	"	vec3	translation;"
	"	float	scale;"
	"	vec4	rotation;"
	"	bool	enabled;"
	"};"
	"in vec4 fColor;"
	"out vec4 color;"
	"void main()"
	"{"
	"	color = fColor;"
	"}"
};

BEGIN_APP_DECLARATION(UniformExample)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
	virtual void OnMouse(int button, int action, int mods);
	virtual void OnCursor(double x, double y);

	GLboolean isPress = GL_FALSE, isRecordPressed = GL_FALSE;
	GLdouble pressedX = 0, pressedY = 0;

	GLuint program;
	enum { TriangleVao, NumVaos };
	GLuint vao[NumVaos];
	enum { TriangleBuf, UniformBuf, NumBufs};
	GLuint buf[NumBufs];

	//׼���洢�ڻ�������е�ֵ
	GLfloat scale = 0.5;
	GLfloat translation[3] = { 0.0f, 0.0f, 0.0f };
	GLfloat rotation[4] = { 0, 0.0, 0.0, 1.0 };
	GLboolean enabled = GL_TRUE;

	enum { Translation, Scale, Rotation, Enabled, NumUniforms };
	//��ѯ��Ӧ�����ԣ����ж������ݻ�����д����ֵ��λ��
	GLuint indices[NumUniforms];
	GLint size[NumUniforms];
	GLint offset[NumUniforms];
	GLint type[NumUniforms];
END_APP_DECLARATION()
DEFINE_APP(UniformExample, "uniform example")

void UniformExample::Initialize(const char* title)
{
	base::Initialize(title);
	
	glClearColor(1, 0, 0, 1);//ָ�������ɫ���������õ���ɫ
	glCreateVertexArrays(NumVaos, vao);
	glBindVertexArray(vao[TriangleVao]);
	glCreateBuffers(NumBufs, buf);
	GLfloat pos[]
	{
		 0.0f,	1.0f,
		-1.0f, -1.0f,
		 1.0f, -1.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, buf[TriangleBuf]);
	glNamedBufferStorage(buf[TriangleBuf], sizeof(pos), pos, 0);

	ShaderInfo shader[] =
	{
		{GL_VERTEX_SHADER, vShader},
		{GL_FRAGMENT_SHADER, fShader},
		{GL_NONE, NULL}
	};
	program = LoadShaders(shader, GLLS_SOURCE);
	glUseProgram(program);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	//��ʼ��uniform�顰Uniforms���еı���
	GLuint uboIndex;
	GLint uboSize;
	GLvoid* buffer;

	//���ҡ�Uniforms"��uniform�������������ж�������Ĵ�С
	uboIndex = glGetUniformBlockIndex(program, "Uniforms");
	glGetActiveUniformBlockiv(program, uboIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
	buffer = malloc(uboSize);
	if (NULL == buffer)
	{
		OutputDebugString("unable to allocate buffer\n");
		return;
	}

	//���ǿ��Խ���һ�������������飬��Ӧ������֪��uniform����
	const char* names[NumUniforms] =
	{
		"translation",
		"scale",
		"rotation",
		"enabled"
	};

	glGetUniformIndices(program, NumUniforms, names, indices);
	glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_OFFSET, offset);
	glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_SIZE, size);
	glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_TYPE, type);

	//��uniform����ֵ������������
	memcpy((GLchar*)buffer + offset[Scale], &scale, size[Scale] * TypeSize(type[Scale]));
	memcpy((GLchar*)buffer + offset[Translation], &translation, size[Translation] * TypeSize(type[Translation]));
	memcpy((GLchar*)buffer + offset[Rotation], &rotation, size[Rotation] * TypeSize(type[Rotation]));
	memcpy((GLchar*)buffer + offset[Enabled], &enabled, size[Enabled] * TypeSize(type[Enabled]));

	//����uniform������󣬳�ʼ���洢���ݣ���������ɫ������������
	glBindBuffer(GL_UNIFORM_BUFFER, buf[UniformBuf]);
	glBufferData(GL_UNIFORM_BUFFER, uboSize, buffer, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex, buf[UniformBuf]);
}

void UniformExample::Display(bool auto_redraw)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao[TriangleVao]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	base::Display(auto_redraw);
}

void UniformExample::Finalize()
{

}

void UniformExample::OnMouse(int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		{
			if (GLFW_PRESS == action) isPress = isRecordPressed = GL_TRUE;
			else
			{
				pressedX = pressedY = 0;
				isPress = isRecordPressed = GL_FALSE;
			}
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		{
			rotation[0] += 10;
			glBufferSubData(GL_UNIFORM_BUFFER, offset[Rotation], sizeof(rotation[0]), rotation);
		}
		break;
	default:
		break;
	}
}

void UniformExample::OnCursor(double x, double y)
{
	if (isPress)
	{
		GLint width, height;
		getWindowSize(&width, &height);

		if (isRecordPressed)
		{
			pressedX = x - translation[0] * width / 2;
			pressedY = y + translation[1] * height / 2;
			isRecordPressed = GL_FALSE;
		}
		else
		{
			translation[0] = (x - pressedX) / width * 2;
			translation[1] = (pressedY - y) / height * 2;
			glBufferSubData(GL_UNIFORM_BUFFER, offset[Translation], sizeof(translation[0]) * 2, translation);
		}
	}
}