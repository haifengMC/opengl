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
	hPObjListIt _thisIt;//�����ڸ����еĵ�����
	hPObjList _children;
public:
	hObject(hObject* parent = NULL);
	hObject(hPWObj parent = NULL);
	virtual ~hObject() {}

	virtual void Initialize(const char* title = 0) {}
	virtual void Display(bool auto_redraw = true) {}
	virtual void Finalize(void);
	virtual void Resize(int width, int height) {}

	virtual void OnKey(int key, int scancode, int action, int mods) { /* NOTHING */ }//���̻ص�
	virtual void OnMouse(int button, int action, int mods) { /* NOTHING */ }//������ص�
	virtual void OnCursor(double x, double y) { /* NOTHING */ }//���λ�ûص�
	virtual void OnCursorNorm(float x, float y) { /* NOTHING */ }//����һ��λ�ûص�
	virtual void OnScroll(double x, double y) { /* NOTHING */ }//�����ص�
	virtual void OnChar(unsigned int codepoint) { /* NOTHING */ }
	virtual void OnDrop(int num, const char** file) { /* NOTHING */ }//�Ͻ��ļ��ص�
	
	virtual hPObjListIt insertChild(hPObj obj);
	virtual void removeChild(hPObj obj);
};
DefLog(hObject, _parent, _thisIt, _children);
