#pragma once
#include "hAppBase.h"

class ButtonTestUi : public hObject
{
public:
	bool loadUi();
};

class ButtonTestApp : public hAppBase
{
public:
	bool preInit();
};