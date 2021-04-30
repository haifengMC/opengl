#include "global.h"
#include "hTime.h"

hTimePoint getNow()
{
	return std::chrono::steady_clock::now();
}

