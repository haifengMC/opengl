#pragma once


class hButton : public hObject
{
	GLuint _bOffset = 0;
	GLuint _eOffset = 0;
	hRect _rect;
public:
	hButton(hObject* parent) : hObject(parent) {}
	hButton(hObject* parent, const hRect& r);

	GLuint getBufSize();
	GLuint getEleBufSize();
	void initialize(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset);
	void display();
private:
	hPoint getPointByIndex(GLuint i);
};