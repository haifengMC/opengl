#pragma once

#include "vgl.h"
#include "hSingleton.h"

class hAppBase : public Singleton<hAppBase>
{
protected:
	GLFWwindow* _pWin = NULL;
	uint64_t _startTime;

public:
	hAppBase();
	uint64_t appTime();
};