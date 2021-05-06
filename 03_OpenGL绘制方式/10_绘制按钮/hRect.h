#pragma once
#include "hTextOpt.h"

//��
class hSize;
class hPoint
{
	int _x = 0, _y = 0;
public:
	hPoint() {}
	constexpr hPoint(int x, int y) : _x(x), _y(y) {}

	int x() const { return _x; }
	int y() const { return _y; }

	void norm(float* buf, const hSize& size);
};
constexpr hPoint operator "" _P(const char* col, size_t n);

//�ߴ�
class hSize
{
	int _width = 0, _height = 0;
public:
	hSize() {}
	constexpr hSize(int width, int height) :
		_width(width), _height(height) {}

	int width() const { return _width; }
	int height() const { return _height; }
};
constexpr hSize operator "" _S(const char* col, size_t n);

//����
class hRect
{
	int _left = 0, _right = 0, _top = 0, _bottom = 0;
public:
	hRect() {}
	hRect(const hPoint& p, const hSize& s);
	constexpr hRect(int x, int y, int width, int height) :
		_left(x), _top(y), _right(_left + width), _bottom(_top + height) {}

	int left() const { return _left; }
	int right() const { return _right; }
	int top() const { return _top; }
	int bottom() const { return _bottom; }

	int width() const { return _right - _left; }
	int height() const { return _bottom - _top; }
	hPoint location() const { return hPoint(_left, _top); }
	hSize size() const { return hSize(_right - _left, _bottom - _top); }
	void resize(int width, int height);

	//�ж��Ƿ��ڴ˾��ο���
	bool contains(const hPoint& p);
	bool contains(const hRect& r);
	bool contains(int x, int y);
};
TEXTOPT(hRect, _Rect, x, y, w, h);
