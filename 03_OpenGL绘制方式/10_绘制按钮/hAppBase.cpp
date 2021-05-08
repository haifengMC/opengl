#include "global.h"
#include "hTime.h"
#include "hRect.h"
#include "hObject.h"
#include "hAppBase.h"
#include "hUi.h"
#include "hAppBaseData.h"
#include "hAppUiData.h"

#define BASE_DT reinterpret_cast<hAppBaseData*>(_pData[AppDataType_Base])
#define UI_DT reinterpret_cast<hAppUiData*>(_pData[AppDataType_Ui])

void hAppBase::setName(const char* name)
{
	BASE_DT->setName(name);
}

void hAppBase::setUi(void* pUi)
{
	if (!pUi)
		return;

	hUi* pNewUi = reinterpret_cast<hUi*>(pUi);
	hUi* pOldUi = UI_DT->setUi(pNewUi);

	if (pOldUi)
		DEL(pOldUi);
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

bool hAppBase::initCallback()
{
	_pData[AppDataType_Base] = new hAppBaseData(getNow());
	if (!BASE_DT)
	{
		setErr("�������ݴ���ʧ��...");
		return false;
	}

	_pData[AppDataType_Ui] = new hAppUiData;
	if (!UI_DT)
	{
		setErr("UI���ݴ���ʧ��...");
		return false;
	}

	if (!preInit())
	{
		setErr("Ԥ��ʼ��ʧ��...");
		return false;
	}

	if (!UI_DT->preInitCallback(BASE_DT))
	{
		setErr("UIԤ��ʼ��ʧ��...");
		return false;
	}

	if (!glfwInit())
	{
		setErr("glfw��ʼ��ʧ��...");
		return false;
	}

	if (!BASE_DT->createWin())
	{
		setErr("��������ʧ��...");
		return false;
	}

	glfwSetWindowUserPointer(BASE_DT->getWin(), this);
	glfwSetWindowSizeCallback(BASE_DT->getWin(), winSizeCallback);

	glfwMakeContextCurrent(BASE_DT->getWin());
	gl3wInit();
	if (!BASE_DT->initOpenGL())
		return false;

	if (!UI_DT->initCallback())
	{
		setErr("UI��ʼ��ʧ��...");
		return false;
	}

	if (!onInit())
	{
		setErr("��ʼ��ʧ��...");
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
	onFinal();

	for (auto pDt : _pData)
		DEL(pDt);
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

#undef BASE_DT 
#undef UI_DT 
