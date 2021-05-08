#pragma once
#include "hUi.h"

class hColor;
class hPoint;
class hButton : public hUi
{
	void* _pData = NULL;
public:
	hButton(hUi* parent);
	hButton(hUi* parent, const hRect& r);
	~hButton();

	bool onInitUi(UiParamInit& param);
	bool onShowUi(GLuint vao);

	GLuint getBufSize();
	GLuint getEleBufSize();
private:
	hPoint getPointByIndex(GLuint i);
};