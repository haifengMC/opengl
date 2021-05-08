#include "global.h"

#include "hRect.h"
#include "hObject.h"
#include "hAppBase.h"
#include "hUiParam.h"
#include "hUi.h"
#include "hAppBaseData.h"
#include "hAppUiData.h"

hUi* hAppUiData::setUi(hUi* ui)
{
	hUi* pOld = _pUi;
	_pUi = ui;
	return pOld;
}

hAppUiData::~hAppUiData()
{
	DEL(_pUi);
}

bool hAppUiData::preInitCallback(hAppBaseData* pApp)
{
	if (!pApp)
		return false;

	if (!_pUi)
		_pUi = new hUi;

	if (!_pUi)
		return false;

	_pApp = pApp;
	if (!_pUi->preInitCallback(NULL))
		return false;

	return true;
}

bool hAppUiData::initCallback()
{
	glGenVertexArrays(1, &_vao);
	if (!_vao)
		return false;

	glGenBuffers(1, &_vbo);
	if (!_vbo)
		return false;

	glGenBuffers(1, &_veo);
	if (!_veo)
		return false;

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _pUi->calcBufSizeCallback(), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _veo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _pUi->calcEleBufSizeCallback(), NULL, GL_DYNAMIC_DRAW);

	UiParamInit param = { _vbo, 0, _veo, 0, _pApp->getSize() };
	if (!_pUi->initCallback(&param))
		return false;

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);
	return true;
}

bool hAppUiData::displayCallback()
{
	return _pUi->showUiCallback(_vao);
}


