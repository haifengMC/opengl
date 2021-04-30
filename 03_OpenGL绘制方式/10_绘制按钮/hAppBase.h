#pragma once

#include "hSingleton.h"

class hAppBaseData;
class hAppBase : public Singleton<hAppBase>
{
protected:
	hTool::hAutoPtr<hAppBaseData> _pData;

	//Ԥ��ʼ�� �������á����û�����������
	virtual bool preInit() { return true; }
	//��ʼ������
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