#include "global.h"
#include "hTime.h"

const hTimePoint& getNow()
{
	return std::chrono::steady_clock::now();
}

