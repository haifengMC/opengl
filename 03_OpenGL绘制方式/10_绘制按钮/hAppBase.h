#pragma once

#include "hSingleton.h"

class hAppBaseData;
class hAppBase : public Singleton<hAppBase>
{
protected:
	hTool::hAutoPtr<hAppBaseData> _pData;

	//预初始化 加载配置、设置基本窗口属性
	virtual bool preInit() { return true; }
	//初始化环境
	virtual bool onInit() { return true; }
	virtual bool onDisplay() { return true; }
	virtual bool onFinal() { return true; }
public:
	uint64_t appTime();//ns
	void loop();

private:
	bool init();
	void run();
	void final();
};