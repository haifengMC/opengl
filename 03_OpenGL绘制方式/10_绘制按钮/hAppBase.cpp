#include "global.h"
#include "hTime.h"
#include "hAppBase.h"

hAppBase::hAppBase()
{
	_startTime = getNow();
}

uint64_t hAppBase::appTime()
{
	return 0;
	//getNow()::period::num
	//
	//return (getNow() - _startTime).count();
}

