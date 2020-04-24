#include "global.h"

#include "vgl.h"
#include "vapp.h"

#include "LoadShaders.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (2 != argc)
	{
		cout << "./svBinProg.exe [filename]" << endl;
		return -1;
	}
	const GLchar* name = argv[1];

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1, 1, "save shader program binary", NULL, NULL);
	glfwMakeContextCurrent(window);
	gl3wInit();
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	GLint formats = 0;
	glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
	if (!formats)
	{
		cout << "当前环境不支持编译为二进制文件" << endl;
		return -1;
	}

	ShaderInfo shaders[countof(suffixes)];
	memset(shaders, 0, sizeof(shaders));
	GLuint count = 0;
	const GLuint nameLen = 128;
	std::string errMsg;
	for (GLuint i = 0; i < countof(suffixes); ++i)
	{
		GLchar* nameBuf = new GLchar[nameLen];
		sprintf_s(nameBuf, nameLen, "%s%s", name, suffixes[i].suffix);
		ShaderInfo tmpSh = { suffixes[i].type, nameBuf, 0 };
		if (!LoadShader(&tmpSh, &errMsg, GLLS_ERRMSG_SHADER))
		{
			delete[] nameBuf;
			continue;
		}

		memcpy(shaders + count++, &tmpSh, sizeof(ShaderInfo));
	}
	if (!errMsg.empty())
	{
		cout << errMsg;
	}

	if (!count)
	{
		cout << "无效着色器" << endl;
		return -1;
	}

	GLuint prog = glCreateProgram();
	glProgramParameteri(prog, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

	for (GLuint i = 0; i < count; ++i)
		glAttachShader(prog, shaders[i].shader);

	glLinkProgram(prog);

	GLint linked = 0;
	glGetProgramiv(prog, GL_LINK_STATUS, &linked);
	if (!linked) {
		GLsizei len;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(prog, len, &len, log);
		std::ostringstream os;
		os << "Program[" << prog << "] shader linking failed: " << log << std::endl;
#ifdef WIN32
		OutputDebugStringA(os.str().c_str());
#endif /* DEBUG */

		return -1;
	}

	GLint* binaryFormats = new GLint[formats];
	glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, binaryFormats);
	GLint len = 0;
	glGetProgramiv(prog, GL_PROGRAM_BINARY_LENGTH, &len);
	GLubyte* binary = new GLubyte[len];
	glGetProgramBinary(prog, len, NULL, (GLenum*)binaryFormats, binary);

	GLchar fileName[64] = "";
	sprintf_s(fileName, "%s%s", name, ".bin");
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "wb");
	fwrite(binary, len, 1, fp);

	fclose(fp);
	delete[] binary;
	
	for (GLuint i = 0; i < count; ++i)
	{
		delete[] shaders[i].filename;
		shaders[i].filename = NULL;
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	cout << "编译为二进制文件成功" << endl;
	return 0;
}