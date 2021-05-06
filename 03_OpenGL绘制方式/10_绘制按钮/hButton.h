#pragma once


class hButton : public hObject
{
	GLuint _bOffset = 0;
	GLuint _eOffset = 0;
	hRect _rect;
public:
	hButton(PWhObj parent) : hObject(parent) {}
	hButton(PWhObj parent, const hRect& r);
#if 0
	GLuint getBufSize();
	GLuint getEleBufSize();
	void initialize(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset);
	void display();
private:
	hPoint getPointByIndex(GLuint i);
#endif

};