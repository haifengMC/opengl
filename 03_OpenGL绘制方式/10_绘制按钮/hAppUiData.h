#pragma once

struct hAppUiInitData
{
	//const hSize winSize;
};

class hAppUiData : public hAppBaseDataAdaptor
{
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint veo = 0;
	PhObj _pObj;
public:
	PhObj getUi() { return _pObj; }
	void setUi(hObject* ui);

	bool loadUiCallback() { return _pObj->loadUiCallback(); }
	bool initUiCallback(const hSize& winSize);
	bool displayCallback();
};