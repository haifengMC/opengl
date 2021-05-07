#include "global.h"
#include "vgl.h"
#include "hTool.h"
#include "hColor.h"
#include "hRect.h"
#include "hObject.h"
#include "hButton.h"

hButton::hButton(PWhObj parent, const hRect& r) : hObject(parent)
{
	_rect = r;
}

bool hButton::onInit(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);

	_bOffset = bOffset;
	_eOffset = eOffset;
	GLuint idBase = _bOffset / sizeof(GLfloat) / 3;
	GLuint indices[4] = {};
	for (GLuint i = 0; i < 4; ++i)
	{
		indices[i] = idBase + 2 * i;
		GLfloat vertBuf[3] = {};
		getPointByIndex(i).norm(vertBuf, winSize);
		glBufferSubData(GL_ARRAY_BUFFER, bOffset, sizeof(vertBuf), vertBuf);
		bOffset += sizeof(vertBuf);
		GLfloat colorBuf[3] = {};
		_col.norm(colorBuf);
		glBufferSubData(GL_ARRAY_BUFFER, bOffset, sizeof(colorBuf), colorBuf);
		bOffset += sizeof(colorBuf);
	}
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, eOffset, sizeof(indices), indices);
	eOffset += sizeof(indices);

	//glPointSize(10.f);

	GLfloat showBuf[24] = {};
	glGetBufferSubData(GL_ARRAY_BUFFER, _bOffset, sizeof(showBuf), showBuf);
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
	glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _eOffset, sizeof(showEle), showEle);
	os.str("");
	os << std::setprecision(2);
	for (GLuint i = 0; i < 4; ++i)
		os << showEle[i] << " ";
	OutputDebugStringA(os.str().c_str());

	return true;
}

bool hButton::onDisplay(GLuint vao)
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (GLvoid*)_eOffset);
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
	case 0: return hPoint(_rect.right(), _rect.top());
	case 1: return hPoint(_rect.right(), _rect.bottom());
	case 2: return hPoint(_rect.left(), _rect.top());
	case 3: return hPoint(_rect.left(), _rect.bottom());
	default:
		break;
	}
	return hPoint();
}

