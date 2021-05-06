#pragma once
#include "hAppBase.h"

class ButtonTest : public hAppBase
{
	GLuint vao;
	GLuint vbo;
public:
	bool preInit();
	bool onInit();
	bool onDisplay();
	bool onFinal() { return true; }
};

#if 0
BEGIN_UI_DECLARATION(ButtonTest)
{
	~ButtonTestUi();
	void loadUi();
}
END_UI_DECLARATION();

BEGIN_APP_DECLARATION(ButtonTest)
{
	~ButtonTestApp();
	void initialize(GLuint uiBufSize, GLuint uiEleBufSize);
	void display(bool auto_redraw /* = true */) {}
	void finalize();

	void onMouse(int button, int action, int mods);
	virtual void onCursor(double x, double y);
	void onCursorNorm(float x, float y);
}
END_APP_DECLARATION();

DECLARATION_APP(ButtonTest);

#endif