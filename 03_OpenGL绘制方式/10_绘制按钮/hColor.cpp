#include "global.h"

#include "hColor.h"

void hColor::norm(float(&buf)[3])
{
	buf[0] = (float)(_red) / 255;
	buf[1] = (float)(_green) / 255;
	buf[2] = (float)(_blue) / 255;
}