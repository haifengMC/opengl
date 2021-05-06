#include "global.h"
#include "vgl.h"
#include "hTool.h"
#include "hRect.h"
#include "hObject.h"
#include "hButton.h"

hButton::hButton(PWhObj parent, const hRect& r) : hObject(parent)
{
	_rect = r;
}


#if 0
GLuint hButton::getBufSize()
{
	return hObject::getBufSize() + 24 * sizeof(GLfloat);
}

GLuint hButton::getEleBufSize()
{
	return hObject::getEleBufSize() + 4 * sizeof(GLuint);
}

void hButton::initialize(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset)
{
	hObject::initialize(winSize, vbo, bOffset, veo, eOffset);

	_bOffset = bOffset;
	_eOffset = eOffset;
	GLuint idBase = bOffset / sizeof(GLfloat) / 3;
	GLuint indices[4] = {};
	for (GLuint i = 0; i < 4; ++i)
	{
		indices[i] = idBase + 2 * i;
		GLfloat vertBuf[3] = {};
		getPointByIndex(i).norm(vertBuf, winSize);
		glNamedBufferSubData(vbo, bOffset, sizeof(vertBuf), vertBuf);
		bOffset += sizeof(vertBuf);
		GLfloat colorBuf[3] = { 1.0f, 0.0f, 0.0f };
		glNamedBufferSubData(vbo, bOffset, sizeof(colorBuf), colorBuf);
		bOffset += sizeof(colorBuf);
	}
	glNamedBufferSubData(veo, eOffset, sizeof(indices), indices);
	eOffset += sizeof(indices);

	//glPointSize(10.f);

	GLfloat showBuf[24] = {};
	glGetNamedBufferSubData(vbo, _bOffset, sizeof(showBuf), showBuf);
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
	glGetNamedBufferSubData(veo, _eOffset, sizeof(showEle), showEle);
	os.str("");
	os << std::setprecision(2);
	for (GLuint i = 0; i < 4; ++i)
		os << showEle[i] << " ";
	OutputDebugStringA(os.str().c_str());
}

void hButton::display()
{
	hObject::display();
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (GLvoid*)_eOffset);
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
#endif
