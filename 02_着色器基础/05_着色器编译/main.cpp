#include "global.h"

#include "vgl.h"
#include "vapp.h"

BEGIN_APP_DECLARATION(ShaderCompile)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
	virtual void OnMouse(int button, int action, int mods);

	GLuint programs[2], progIdx = 0;
	GLuint vao;

private:
	GLuint LoadShader(GLenum shader, const GLchar* filename);
	const GLchar* ReadShader(const char* filename);
END_APP_DECLARATION()
DEFINE_APP(ShaderCompile, "shader compile")


void ShaderCompile::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLfloat vboData[] =
	{
		 0.0f,  0.5f,
		-0.5f, -0.5f,
		 0.5f, -0.5f
	};
	glNamedBufferStorage(vbo, sizeof(vboData), vboData, 0);

	GLuint vShader, fShader[2];

	vShader = LoadShader(GL_VERTEX_SHADER, "shaderCompile.vert");
	fShader[0] = LoadShader(GL_FRAGMENT_SHADER, "shaderCompile_1.frag");
	fShader[1] = LoadShader(GL_FRAGMENT_SHADER, "shaderCompile_2.frag");

	programs[0] = glCreateProgram();
	programs[1] = glCreateProgram();

	glAttachShader(programs[0], vShader);
	glAttachShader(programs[0], fShader[0]);
	glAttachShader(programs[1], vShader);
	glAttachShader(programs[1], fShader[1]);

	glLinkProgram(programs[0]);
	glLinkProgram(programs[1]);

	GLint linked[2];
	glGetProgramiv(programs[0], GL_LINK_STATUS, linked);
	glGetProgramiv(programs[1], GL_LINK_STATUS, linked + 1);
	if (!linked[0] || !linked[1])
	{
		if (!linked[0])
		{
			GLsizei len;
			glGetProgramiv(programs[0], GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(programs[0], len, &len, log);
			std::ostringstream os;
			os << "Program[" << programs[0] << "] shader linking failed: " << log << std::endl;
			OutputDebugString(os.str().c_str());
			delete[] log;
		}
		if (!linked[1])
		{
			GLsizei len;
			glGetProgramiv(programs[1], GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(programs[1], len, &len, log);
			std::ostringstream os;
			os << "Program[" << programs[1] << "] shader linking failed: " << log << std::endl;
			OutputDebugString(os.str().c_str());
			delete[] log;
		}
		return;
	}
	glUseProgram(programs[progIdx % 2]);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
}

void ShaderCompile::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	base::Display(auto_redraw);
}

void ShaderCompile::Finalize()
{

}

void ShaderCompile::OnMouse(int button, int action, int mods)
{
	if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_PRESS == action)
	{
		glUseProgram(programs[++progIdx % 2]);
	}
}

GLuint ShaderCompile::LoadShader(GLenum shader, const GLchar* filename)
{
	std::ostringstream os;

	GLuint shaderTmp = glCreateShader(shader);
	const GLchar* source = ReadShader(filename);
	if (NULL == source)
	{
		os << "Shader[" << shaderTmp << "] compilation failed: " << filename << " open failed" << std::endl;
		OutputDebugString(os.str().c_str());
		return 0;
	}
	glShaderSource(shaderTmp, 1, &source, NULL);
	glCompileShader(shaderTmp);
	GLint isCompile = GL_FALSE;
	glGetShaderiv(shaderTmp, GL_COMPILE_STATUS, &isCompile);
	if (!isCompile)
	{
		GLsizei len;
		glGetShaderiv(shaderTmp, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shaderTmp, len, &len, log);
		os << "Shader[" << shaderTmp << "] compilation failed: " << log << std::endl;
		OutputDebugString(os.str().c_str());
		delete[] log;

		return 0;
	}

	os << "Shader[" << shaderTmp << "] compilation success!" << std::endl;
	OutputDebugString(os.str().c_str());

	return shaderTmp;
}

const GLchar* ShaderCompile::ReadShader(const char* filename)
{
#ifdef WIN32
	FILE* infile;
	fopen_s(&infile, filename, "rb");
#else
	FILE* infile = fopen(filename, "rb");
#endif // WIN32

	if (!infile) {
		return NULL;
	}

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	GLchar* source = new GLchar[len + 1];

	fread(source, 1, len, infile);
	fclose(infile);

	source[len] = 0;

	return const_cast<const GLchar*>(source);
}