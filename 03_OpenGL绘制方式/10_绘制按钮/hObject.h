#pragma once

class hObject;
typedef std::list<hObject*> hObjList;
typedef hObjList::iterator hObjListIt;

class hObject
{
	DefLog_Init();
	friend class hAppUiData;
protected:
	hObject* _parent;
	hObjListIt _thisIt;//对象在父类中的迭代器
	hObjList _children;
public:
	hObject(hObject* parent = NULL);
	virtual ~hObject();

	virtual bool onPreInit(void* pDt) { return true; }
	virtual bool onInit(void* pDt) { return true; }
	virtual bool onFinal() { return true; }
private:
	void addChild(hObject* pChild);
	void delChild(hObjListIt childIt);

	bool preInitCallback(void* pDt);
	bool initCallback(void* pDt);
	bool finalCallback();
};
DefLog(hObject, _parent, _thisIt, _children);
