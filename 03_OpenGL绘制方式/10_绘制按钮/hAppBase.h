#pragma once

#include "hSingleton.h"
#include "hTime.h"

class hAppBase : public Singleton<hAppBase>
{
protected:
	GLFWwindow* _pWin = NULL;
	hTimePoint _startTime;
	hRect _winRect;
	std::string _appName;

	//Ԥ��ʼ�� �������á����û�����������
	virtual bool preInit() { return true; }
	//��ʼ������
	virtual bool OnInit() { return true; }
	virtual bool run() { return true; }
	virtual bool final() { return true; }
public:
	hAppBase();
	uint64_t appTime();//ns

	void loop();

private:
	bool initCallback();
};