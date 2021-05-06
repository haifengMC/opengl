#pragma once

class hObject;
typedef hTool::hWeakPtr<hObject> PWhObj;
typedef hTool::hAutoPtr<hObject> PhObj;
typedef std::list<PWhObj> hObjList;
typedef hObjList::iterator hObjListIt;

class hObject : public hTool::hAutoPtrObj
{
	DefLog_Init();
	PWhObj _parent;
	hObjListIt _thisIt;//对象在父类中的迭代器
	hObjList _children;
public:
	hObject(PWhObj parent = PWhObj());
	virtual ~hObject() {}

	bool loadUi() { return true; }
	//virtual GLuint getBufSize();
	//virtual GLuint getEleBufSize();
	//virtual void initialize(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset);
	//virtual void display();
	//virtual void finalize();

	bool loadUiCallback();
private:
	hObjListIt insertChild(PhObj obj);
	//virtual void removeChild(hObjListIt objIt);
};
DefLog(hObject, _parent, _thisIt, _children);
