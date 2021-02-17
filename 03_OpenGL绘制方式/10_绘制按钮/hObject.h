#pragma once

class hObject;
typedef std::list<hObject*> hObjList;
typedef hObjList::iterator hObjListIt;

class hObject
{
	DefLog_Init();
	hObject* _parent = NULL;
	hObjListIt _thisIt;//对象在父类中的迭代器
	hObjList _children;
public:
	hObject(hObject* parent = NULL);
	virtual ~hObject() {}
	virtual GLuint getBufSize();
	virtual GLuint getEleBufSize();
	virtual void initialize(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset);
	virtual void display();
	virtual void finalize();
	
	virtual hObjListIt insertChild(hObject* obj);
	virtual void removeChild(hObjListIt objIt);
};
DefLog(hObject, _parent, _thisIt, _children);
