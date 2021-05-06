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
	if (init())
		run();
	else
		errCallBack();
	
	final();
}

bool hAppBase::init()
{
	_pData[AppDataType_Base].bind(new hAppBaseData(getNow()));
	auto pBaseDt = BASE_DT;
	if (!pBaseDt)
	{
		setErr("基础数据创建失败...");
		return false;
	}

	_pData[AppDataType_Ui].bind(new hAppUiData);
	auto pUiDt = UI_DT;
	if (!pUiDt)
	{
		setErr("UI数据创建失败...");
		return false;
	}

	if (!preInit())
	{
		setErr("预初始化失败...");
		return false;
	}

	if (!loadUi())
	{
		setErr("UI加载失败...");
		return false;
	}

	if (!glfwInit())
	{
		setErr("glfw初始化失败...");
		return false;
	}
	
	if (!pBaseDt->createWin())
	{
		setErr("创建窗口失败...");
		return false;
	}

	glfwSetWindowUserPointer(pBaseDt->getWin(), this);
	glfwSetWindowSizeCallback(pBaseDt->getWin(), winSizeCallback);

	glfwMakeContextCurrent(pBaseDt->getWin());
	gl3wInit();
	if (!pBaseDt->initOpenGL())
		return false;

	if (!onInit())
	{
		setErr("初始化失败...");
		return false;
	}

	return true;
}

void hAppBase::run()
{
	do
	{
		glClear(GL_COLOR_BUFFER_BIT);
		onDisplay();
		glfwSwapBuffers(BASE_DT->getWin());
		glfwPollEvents();
	} while (!glfwWindowShouldClose(BASE_DT->getWin()));
}

void hAppBase::final()
{
	if (!BASE_DT)
		return;

	onFinal();
}

void hAppBase::resize(int width, int height)
{
	BASE_DT->resize(width, height);
	glViewport(0, 0, width, height);
	onResize();
}

bool hAppBase::loadUi()
{
	if (UI_DT->getUi())
		return UI_DT->loadUiCallback();

	UI_DT->setUi(new hObject);
	return true;
}

void hAppBase::errCallBack()
{
	BASE_DT->putOutErr();
}

void hAppBase::winSizeCallback(GLFWwindow* win, int width, int height)
{
	hAppBase* pThis = (hAppBase*)glfwGetWindowUserPointer(win);

	pThis->resize(width, height);
}

