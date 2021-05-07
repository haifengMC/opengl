#include "global.h"
#include "hTime.h"
#include "hRect.h"
#include "hObject.h"
#include "hAppBase.h"
#include "hAppBaseData.h"
#include "hAppUiData.h"

#define BASE_DT _pData[AppDataType_Base].dynamic<hAppBaseData>()
#define UI_DT _pData[AppDataType_Ui].dynamic<hAppUiData>()

void hAppBase::setName(const char* name)
{
	BASE_DT->setName(name);
}

void hAppBase::setUi(hObject* ui)
{
	if (!ui)
		return;

	UI_DT->setUi(ui);
}

void hAppBase::addShader(uint32_t type, const char* shade)
{
	BASE_DT->addShader(type, shade);
}

void hAppBase::setErr(const char* err)
{
	BASE_DT->putInErr(err);
}

uint64_t hAppBase::appTime()
{
	return (getNow() - BASE_DT->getBegTime()).count();
}

void hAppBase::loop()
{
	if (initCallback())
		runCallback();
	else
		errCallBack();
	
	finalCallback();
}

bool hAppBase::loadUiCallback()
{
	if (UI_DT->getUi())
		return UI_DT->loadUiCallback();

	UI_DT->setUi(new hObject);
	return true;
}

bool hAppBase::initCallback()
{
	_pData[AppDataType_Base].bind(new hAppBaseData(getNow()));
	if (!BASE_DT)
	{
		setErr("基础数据创建失败...");
		return false;
	}

	_pData[AppDataType_Ui].bind(new hAppUiData);
	if (!UI_DT)
	{
		setErr("UI数据创建失败...");
		return false;
	}

	if (!preInit())
	{
		setErr("预初始化失败...");
		return false;
	}

	if (!loadUiCallback())
	{
		setErr("UI加载失败...");
		return false;
	}

	if (!glfwInit())
	{
		setErr("glfw初始化失败...");
		return false;
	}

	if (!BASE_DT->createWin())
	{
		setErr("创建窗口失败...");
		return false;
	}

	glfwSetWindowUserPointer(BASE_DT->getWin(), this);
	glfwSetWindowSizeCallback(BASE_DT->getWin(), winSizeCallback);

	glfwMakeContextCurrent(BASE_DT->getWin());
	gl3wInit();
	if (!BASE_DT->initOpenGL())
		return false;

	if (!UI_DT->initUiCallback(BASE_DT->getSize()))
	{
		setErr("UI加载失败...");
		return false;
	}

	if (!onInit())
	{
		setErr("初始化失败...");
		return false;
	}

	return true;
}

void hAppBase::runCallback()
{
	do
	{
		glClear(GL_COLOR_BUFFER_BIT);
		UI_DT->displayCallback();
		onDisplay();
		glfwSwapBuffers(BASE_DT->getWin());
		glfwPollEvents();
	} while (!glfwWindowShouldClose(BASE_DT->getWin()));
}

void hAppBase::finalCallback()
{
	if (!BASE_DT)
		return;

	onFinal();
}

void hAppBase::resizeCallback(int width, int height)
{
	BASE_DT->resize(width, height);
	glViewport(0, 0, width, height);
	onResize();
}

void hAppBase::errCallBack()
{
	BASE_DT->putOutErr();
}

void hAppBase::winSizeCallback(GLFWwindow* win, int width, int height)
{
	hAppBase* pThis = (hAppBase*)glfwGetWindowUserPointer(win);

	pThis->resizeCallback(width, height);
}

