#include "global.h"
#include "hTime.h"
#include "hRect.h"
#include "hAppBaseData.h"
#include "hAppBase.h"

uint64_t hAppBase::appTime()
{
	return (getNow() - _pData->getBegTime()).count();
}

void hAppBase::loop()
{
	if (init())
		run();
	
	final();
}

bool hAppBase::init()
{
	_pData.emplace(getNow());
	if (!_pData)
	{
		OutputDebugStringA("基础数据初始化失败...");
		return false;
	}

	if (!preInit())
	{
		OutputDebugStringA("预初始化失败...");
		return false;
	}

	if (!glfwInit())
	{
		OutputDebugStringA("glfwInit()失败...");
		return false;
	}
	
	if (!_pData->createWin())
	{
		OutputDebugStringA("创建窗口失败...");
		return false;
	}

	glfwSetWindowUserPointer(_pData->getWin(), this);

	if (!onInit())
	{
		OutputDebugStringA("初始化失败...");
		return false;
	}

	return true;
}

void hAppBase::run()
{
	do
	{
		onDisplay();
		glfwSwapBuffers(_pData->getWin());
		glfwPollEvents();
	} while (!glfwWindowShouldClose(_pData->getWin()));
}

void hAppBase::final()
{
	onFinal();
}

