#pragma once
#include "vgl.h"
//点
class hSize;
class hPoint
{
	GLint _x = 0, _y = 0;
public:
	hPoint() {}
	constexpr hPoint(GLint x, GLint y) : _x(x), _y(y) {}

	GLint x() const { return _x; }
	GLint y() const { return _y; }

	void norm(GLfloat* buf, const hSize& size);
};
constexpr hPoint operator "" _P(const char* col, size_t n);

//尺寸
class hSize
{
	GLint _width = 0, _height = 0;
public:
	hSize() {}
	constexpr hSize(GLint width, GLint height) :
		_width(width), _height(height) {}

	GLint width() const { return _width; }
	GLint height() const { return _height; }
};
constexpr hSize operator "" _S(const char* col, size_t n);

//矩形
class hRect
{
	GLint _left = 0, _right = 0, _top = 0, _bottom = 0;
public:
	hRect() {}
	hRect(const hPoint& p, const hSize& s);
	constexpr hRect(GLint x, GLint y, GLint width, GLint height) :
		_left(x), _top(y), _right(_left + width), _bottom(_top + height) {}

	GLint left() const { return _left; }
	GLint right() const { return _right; }
	GLint top() const { return _top; }
	GLint bottom() const { return _bottom; }
	hPoint location() const { return hPoint(_left, _top); }
	hSize size() const { return hSize(_right - _left, _bottom - _top); }

	//判断是否在此矩形框内
	bool contains(const hPoint& p);
	bool contains(const hRect& r);
	bool contains(GLint x, GLint y);
};
constexpr hRect operator "" _Rect(const char* col, size_t n);
