#include "global.h"

#include "hRect.h"
#include "hObject.h"
#include "hAppBase.h"
#include "hAppUiData.h"

void hAppUiData::setUi(hObject* ui)
{
	_pObj.bind(ui);
}

bool hAppUiData::initUiCallback(const hSize& winSize)
{
	glGenVertexArrays(1, &vao);
	if (!vao)
		return false;

	glGenBuffers(1, &vbo);
	if (!vbo)
		return false;

	glGenBuffers(1, &veo);
	if (!veo)
		return false;

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _pObj->calcBufSizeCallback(), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _pObj->calcEleBufSizeCallback(), NULL, GL_DYNAMIC_DRAW);

	GLuint bOffset = 0;
	GLuint eOffset = 0;
	if (!_pObj->initUiCallback(winSize, vbo, bOffset, veo, eOffset))
		return false;

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);
	return true;
}

bool hAppUiData::displayCallback()
{
	return _pObj->displayCallback(vao);
}


