#pragma once

class hObject;
typedef hTool::hAutoPtr<hObject> hPObj;
typedef std::list<hPObj> hPObjList;
typedef hPObjList::iterator hPObjListIt;
typedef hTool::hWeakPtr<hObject> hPWObj;

class hObject : public hTool::hAutoPtrObj
{
	DefLog_Init();

	hPWObj _parent;
	hPObjListIt _thisIt;//对象在父类中的迭代器
	hPObjList _children;
public:
	hObject(hObject* parent = NULL);
	hObject(hPWObj parent = NULL);
	virtual ~hObject() {}

	virtual void Initialize(const char* title = 0) {}
	virtual void Display(bool auto_redraw = true) {}
	virtual void Finalize(void);
	virtual void Resize(int width, int height) {}

	virtual void OnKey(int key, int scancode, int action, int mods) { /* NOTHING */ }//键盘回调
	virtual void OnMouse(int button, int action, int mods) { /* NOTHING */ }//鼠标点击回调
	virtual void OnCursor(double x, double y) { /* NOTHING */ }//光标位置回调
	virtual void OnCursorNorm(float x, float y) { /* NOTHING */ }//光标归一化位置回调
	virtual void OnScroll(double x, double y) { /* NOTHING */ }//滚动回调
	virtual void OnChar(unsigned int codepoint) { /* NOTHING */ }
	virtual void OnDrop(int num, const char** file) { /* NOTHING */ }//拖进文件回调
	
	virtual hPObjListIt insertChild(hPObj obj);
	virtual void removeChild(hPObj obj);
};
DefLog(hObject, _parent, _thisIt, _children);
