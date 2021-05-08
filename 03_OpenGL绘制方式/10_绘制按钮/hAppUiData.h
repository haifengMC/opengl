#pragma once

class hAppBaseData;
class hAppUiData
{
	friend class hAppBase;

	GLuint _vao = 0;
	GLuint _vbo = 0;
	GLuint _veo = 0;
	hAppBaseData* _pApp = NULL;
	hUi* _pUi = NULL;
public:
	hUi* getUi() { return _pUi; }
	hUi* setUi(hUi* pUi);

	~hAppUiData();
private:
	bool preInitCallback(hAppBaseData* pApp);
	bool initCallback();
	bool displayCallback();
};