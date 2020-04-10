#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(SpirVTest)
	virtual void Initialize(const char* title /* = 0 */);
	virtual void Display(bool auto_redraw /* = true */);
	virtual void Finalize();
private:
	
END_APP_DECLARATION()

DEFINE_APP(SpirVTest, "SPIR-V test")

void SpirVTest::Initialize(const char* title)
{
	base::Initialize(title);

	ShaderInfo shaders[] =
	{
		{GL_VERTEX_SHADER, "triangleSPIR-V.vert.sqv"},
		{GL_FRAGMENT_SHADER, "triangleSPIR-V.frag.sqv"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShadersBySpirV(shaders);

}

void SpirVTest::Display(bool auto_redraw)
{


	base::Display(auto_redraw);
}

void SpirVTest::Finalize()
{
}
