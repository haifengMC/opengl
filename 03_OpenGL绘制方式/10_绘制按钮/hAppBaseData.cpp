#include "global.h"

#include "hTime.h"
#include "hRect.h"
#include "hAppBase.h"
#include "hAppBaseData.h"

bool hAppBaseData::createWin()
{
	if (!_winRect.width() || !_winRect.height())
		_winRect = "x0 y0 w800 h600"_Rect;
	if (_appName.empty())
		_appName = "Application";

	_pWin = glfwCreateWindow(
		_winRect.width(), _winRect.height(),
		_appName.c_str(), nullptr, nullptr);

	return _pWin;
}

void hAppBaseData::resize(int width, int height)
{
	_winRect.resize(width, height); 
	glViewport(0, 0, _winRect.width(), _winRect.height());
}

bool hAppBaseData::initOpenGL()
{
	_prog = loadShaders();
	if (!_prog)
		return false;

	glUseProgram(_prog);

	return true;
}

void hAppBaseData::putOutErr()
{
	if (_errMsg.empty())
		return;

	OutputDebugStringA(_errMsg.c_str());
}

uint32_t hAppBaseData::loadShaders()
{
	if (_shaders.empty())
	{
		putInErr("未找到可用着色器...");
		return 0;
	}

	GLuint program = glCreateProgram();
	std::list<GLuint> shaderList;
	for (auto& pr : _shaders)
	{
		GLuint shader = glCreateShader(pr.first);
		shaderList.push_back(shader);
		const GLchar* source = readShader(pr.second);
		if (!source)
		{
			for (auto& sh : shaderList)
				glDeleteShader(sh);

			return 0;
		}

		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::ostringstream os;
			os << "着色器[" << shader << "] 编译失败: " << log;
			delete[] log;
			putInErr(os.str().c_str());
			return 0;
		}

		glAttachShader(program, shader);
	}

	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		std::ostringstream os;
		os << "程序[" << program << "] 着色器链接失败: " << log;
		putInErr(os.str().c_str());
		delete[] log;

		for (auto& sh : shaderList)
			glDeleteShader(sh);

		return 0;
	}

	return program;
}

const char* hAppBaseData::readShader(const std::string& filename)
{
	FILE* infile;
	fopen_s(&infile, filename.c_str(), "rb");

	if (!infile) 
	{
		std::ostringstream os;
		os << "不能打开文件 '" << filename << "'";
		putInErr(os.str().c_str());
		return NULL;
	}

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	char* source = new char[len + 1];

	fread(source, 1, len, infile);
	fclose(infile);

	source[len] = 0;

	return source;
}