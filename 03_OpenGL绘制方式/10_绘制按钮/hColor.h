#pragma once
#include "hTextOpt.h"

//¾ØÐÎ
class hColor
{
	uint8_t _red = 0, _green = 0, _blue = 0, _alpha = 100;
public:
	hColor() {}
	constexpr hColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
		_red(r), _green(g), _blue(b), _alpha(a) {}

	uint8_t red() const { return _red; }
	uint8_t green() const { return _green; }
	uint8_t blue() const { return _blue; }
	uint8_t alpha() const { return _alpha; }

	void norm(float (&buf)[3]);
};
TEXTOPT(hColor, _Col, r, g, b, a);