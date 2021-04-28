#include "global.h"
#include "hTime.h"

uint64_t getNow()
{
	typedef std::chrono::steady_clock::period Period;
	typedef typename std::ratio_multiply<Period, std::kilo> KiloPeriod;
	return KiloPeriod::num / KiloPeriod::den;
}

