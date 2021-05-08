#pragma once

#include "hSingleton.h"

enum AppDataType
{
	AppDataType_Base,
	AppDataType_Ui,
	AppDataType_Max,
};

class hAppBase : public Singleton<hAppBase>
{
protected:
	void* _pData[AppDataType_Max];

	//预初始化 加载配置、设置基本窗口属性
	virtual bool preInit() { return true; }
	//初始化环境
	virtual bool onInit() { return true; }
	virtual bool onDisplay() { return true; }
	virtual bool onFinal() { return true; }
	virtual bool onResize() { return true; }

	void setName(const char* name);
	void setUi(void* pUi);
	void addShader(uint32_t type, const char* shade);

	void setErr(const char* err);
public:
	uint64_t appTime();//ns
	void loop();

private:
	bool initCallback();
	void runCallback();
	void finalCallback();
	void resizeCallback(int width, int height);

	void errCallBack();
	static void winSizeCallback(GLFWwindow* win, int width, int height);
};