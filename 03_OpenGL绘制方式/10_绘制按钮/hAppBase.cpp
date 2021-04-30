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
		OutputDebugStringA("�������ݳ�ʼ��ʧ��...");
		return false;
	}

	if (!preInit())
	{
		OutputDebugStringA("Ԥ��ʼ��ʧ��...");
		return false;
	}

	if (!glfwInit())
	{
		OutputDebugStringA("glfwInit()ʧ��...");
		return false;
	}
	
	if (!_pData->createWin())
	{
		OutputDebugStringA("��������ʧ��...");
		return false;
	}

	glfwSetWindowUserPointer(_pData->getWin(), this);

	if (!onInit())
	{
		OutputDebugStringA("��ʼ��ʧ��...");
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

