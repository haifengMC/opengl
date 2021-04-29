#include "vgl.h"
#include "global.h"
#include "hRect.h"

constexpr hPoint operator""_P(const char* col, size_t n)
{
	const char* end = col + n;
	const char* x = NULL, * y = NULL;
	int xV = 0, yV = 0;
	for (const char* p = col; p != end; ++p)
	{
		switch (*p)
		{
		case 'x': x = p; break;
		case 'y': y = p; break;
		default: break;
		}
	}

	if (x) xV = atoi(x + 1);
	if (y) yV = atoi(y + 1);
	return hPoint(xV, yV);
}

constexpr hSize operator""_S(const char* col, size_t n)
{
	const char* end = col + n;
	const char* w = NULL, * h = NULL;
	GLint wV = 0, hV = 0;
	for (const char* p = col; p != end; ++p)
	{
		switch (*p)
		{
		case 'w': w = p; break;
		case 'h': h = p; break;
		default: break;
		}
	}

	if (w) wV = atoi(w + 1);
	if (h) hV = atoi(h + 1);
	return hSize(wV, hV);
}

hRect::hRect(const hPoint& p, const hSize& s)
{
	_left = p.x();
	_top = p.y();
	_right = _left + s.width();
	_bottom = _left + s.height();
}

bool hRect::contains(const hPoint& p)
{
	return _left <= p.x() && _right >= p.x() &&
		_top <= p.y() && _bottom >= p.y();
}

bool hRect::contains(const hRect& r)
{
	return _left <= r.left() && _right >= r.right() &&
		_top <= r.top() && _bottom >= r.bottom();
}

bool hRect::contains(int x, int y)
{
	return _left <= x && _right >= x &&
		_top <= y && _bottom >= y;
}

constexpr hRect operator""_Rect(const char* col, size_t n)
{
	const char* end = col + n;
	const char* x = NULL, *y = NULL, *w = NULL, *h = NULL;
	int xV = 0, yV = 0, wV = 0, hV = 0;
	for (const char* p = col; p != end; ++p)
	{
		switch (*p)
		{
		case 'x': x = p; break;
		case 'y': y = p; break;
		case 'w': w = p; break;
		case 'h': h = p; break;
		default: break;
		}
	}

	if (x) xV = atoi(x + 1);
	if (y) yV = atoi(y + 1);
	if (w) wV = atoi(w + 1);
	if (h) hV = atoi(h + 1);
	return hRect(xV, yV, wV, hV);
}

void hPoint::norm(float* buf, const hSize& size)
{
	buf[0] = (float)(_x * 2 - size.width()) / size.width();
	buf[1] = (float)(size.height() - _y * 2) / size.height();
}
