#pragma once

class hObject;
typedef hTool::hWeakPtr<hObject> PWhObj;
typedef hTool::hAutoPtr<hObject> PhObj;
typedef std::list<PhObj> hObjList;
typedef hObjList::iterator hObjListIt;

class hObject
{
	DefLog_Init();
	PWhObj _parent;
	hObjList _children;
	hObjListIt _thisIt;//�����ڸ����еĵ�����
public:
	hObject(PWhObj parent = PWhObj());
	virtual ~hObject() {}

	virtual bool loadUi() { return true; }
	virtual bool onInit(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset) { return true; }
	virtual bool onDisplay(GLuint vao) { return true; }

	virtual GLuint getBufSize() { return 0; }
	virtual GLuint getEleBufSize() { return 0; }
	//virtual void finalize();

	bool loadUiCallback();
	bool initUiCallback(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset);
	bool displayCallback(GLuint vao);

	GLuint calcBufSizeCallback();
	GLuint calcEleBufSizeCallback();
private:
	void addChild(PhObj obj);
	//virtual void removeChild(hObjListIt objIt);
};
DefLog(hObject, _children);
