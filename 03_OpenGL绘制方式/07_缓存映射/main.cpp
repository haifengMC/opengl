#include "global.h"

#include "vgl.h"
#include "vapp.h"
#include "vtype.h"

#include "LoadShaders.h"

BEGIN_APP_DECLARATION(BufferMapTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
	
	virtual void OnMouse(int button, int action, int mods);
private:
	GLuint vao = 0, vbo = 0;

	std::array<vec2, 3> vert;
	vec3 color[3] =
	{
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f},
	};
END_APP_DECLARATION()

DEFINE_APP(BufferMapTest, "buffer map test")

void BufferMapTest::Initialize(const char* title /* = 0 */)
{
	base::Initialize(title);

	ErrMsg err = { GLLS_ERRMSG_ALL };
	GLuint prog = LoadProgramByBinary("BufferMap.bin", &err);
	if (!err.msg.empty())
	{
		OutputDebugStringA(err.msg.c_str());
		return;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vert.size() * vert[0].size() + countof(color) * color->size(), NULL, GL_DYNAMIC_DRAW);

	void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	FILE* infile;
	fopen_s(&infile, "BufferMapData.bin", "rb");
	if (infile)
	{
		fread(data, 1, vert.size() * vert[0].size(), infile);
		GLuint offset = 0;
		for (vec2 & v : vert)
			offset += v.read((GLchar*)data + offset, v.size());
		fclose(infile);
	}
	else
	{
		vert = { vec2(0.0f, 0.9f), vec2(-0.9f, -0.9f), vec2(0.9f, -0.9f) };
		GLuint offset = 0;
		for (vec2& v : vert)
			offset += v.write((GLchar*)data + offset, v.size());
	}

	GLuint offset = vert.size() * vert[0].size();
	for (vec3 & v : color)
		offset += v.write((GLchar*)data + offset, v.size());
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glUseProgram(prog);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(vert.size() * vert[0].size()));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glPointSize(10.0f);
}

void BufferMapTest::Display(bool auto_redraw /* = true */)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	base::Display(auto_redraw);
}

void BufferMapTest::Finalize()
{
	
}


void BufferMapTest::OnMouse(int button, int action, int mods)
{
	
}
