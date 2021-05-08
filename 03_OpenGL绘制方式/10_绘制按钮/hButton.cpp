#include "global.h"

#include "hColor.h"
#include "hRect.h"
#include "hUiParam.h"
#include "hButton.h"

struct  hButtonData
{
	GLuint _bOffset = 0;
	GLuint _eOffset = 0;
	hRect _rect;
	hColor _col = _col = "r84 g184 b237 a100"_Col;
};

hButton::hButton(hUi* parent) : hUi(parent)
{
	_pData = new hButtonData;
}

hButton::hButton(hUi* parent, const hRect& r) : hUi(parent)
{
	hButtonData* pData = new hButtonData;
	pData->_rect = r;
	_pData = pData;
}

hButton::~hButton()
{
	DEL(_pData);
}

#define _DT reinterpret_cast<hButtonData*>(_pData)
#define _BOFF _DT->_bOffset
#define _EOFF _DT->_eOffset
#define _RECT _DT->_rect
#define _COL _DT->_col


bool hButton::onInitUi(UiParamInit& param)
{
	glBindBuffer(GL_ARRAY_BUFFER, param.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, param.veo);

	_BOFF = param.bOffset;
	_EOFF = param.eOffset;
	GLuint idBase = _BOFF / sizeof(GLfloat) / 3;
	GLuint indices[4] = {};
	for (GLuint i = 0; i < 4; ++i)
	{
		indices[i] = idBase + 2 * i;
		GLfloat vertBuf[3] = {};
		getPointByIndex(i).norm(vertBuf, param.winSize);
		glBufferSubData(GL_ARRAY_BUFFER, param.bOffset, sizeof(vertBuf), vertBuf);
		param.bOffset += sizeof(vertBuf);
		GLfloat colorBuf[3] = {};
		_COL.norm(colorBuf);
		glBufferSubData(GL_ARRAY_BUFFER, param.bOffset, sizeof(colorBuf), colorBuf);
		param.bOffset += sizeof(colorBuf);
	}
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, param.eOffset, sizeof(indices), indices);
	param.eOffset += sizeof(indices);

	//glPointSize(10.f);

	GLfloat showBuf[24] = {};
	glGetBufferSubData(GL_ARRAY_BUFFER, _BOFF, sizeof(showBuf), showBuf);
	std::stringstream os;
	os << std::setprecision(2);
	for (GLuint i = 0; i < 24; ++i)
	{
		os << showBuf[i];

		if (0 == (i + 1) % 6)
			os << "\n";
		else if (0 == (i + 1) % 3)
			os << std::setw(5);
		else os << ",";
	}
	OutputDebugStringA(os.str().c_str());

	GLuint showEle[4] = {};
	glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _EOFF, sizeof(showEle), showEle);
	os.str("");
	os << std::setprecision(2);
	for (GLuint i = 0; i < 4; ++i)
		os << showEle[i] << " ";
	OutputDebugStringA(os.str().c_str());

	return true;
}

bool hButton::onShowUi(GLuint vao)
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (GLvoid*)_EOFF);
	return true;
}

GLuint hButton::getBufSize()
{
	return 24 * sizeof(GLfloat);
}

GLuint hButton::getEleBufSize()
{
	return 4 * sizeof(GLuint);
}

hPoint hButton::getPointByIndex(GLuint i)
{
	switch (i)
	{
	case 0: return hPoint(_RECT.right(), _RECT.top());
	case 1: return hPoint(_RECT.right(), _RECT.bottom());
	case 2: return hPoint(_RECT.left(), _RECT.top());
	case 3: return hPoint(_RECT.left(), _RECT.bottom());
	default:
		break;
	}
	return hPoint();
}

