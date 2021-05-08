#pragma once
#include "hObject.h"

struct UiParamInit;
class hUi : public hObject
{
	friend class hAppUiData;
public:
	hUi(hUi* parent = NULL) : hObject(parent) {}

	virtual bool onLoadUi() { return true; }
	virtual bool onInitUi(UiParamInit& param) { return true; }
	virtual bool onShowUi(GLuint vao) { return true; }

	virtual GLuint getBufSize() { return 0; }
	virtual GLuint getEleBufSize() { return 0; }
private:
	bool onPreInit(void* pDt);
	bool onInit(void* pDt);

//»Øµ÷º¯Êý
	bool showUiCallback(GLuint vao);
	GLuint calcBufSizeCallback();
	GLuint calcEleBufSizeCallback();
};