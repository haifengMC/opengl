#pragma once


class hButton : public hObject
{
	GLuint _bOffset = 0;
	GLuint _eOffset = 0;
	hRect _rect;
	hColor _col = "r84 g184 b237 a100"_Col;
public:
	hButton(PWhObj parent) : hObject(parent) {}
	hButton(PWhObj parent, const hRect& r);

	bool onInit(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset);
	bool onDisplay(GLuint vao);

	GLuint getBufSize();
	GLuint getEleBufSize();
private:
	hPoint getPointByIndex(GLuint i);

};