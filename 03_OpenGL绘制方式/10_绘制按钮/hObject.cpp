#include "global.h"
#include "vgl.h"
#include "hTool.h"
#include "hRect.h"
#include "hObject.h"

hObject::hObject(hObject* parent)
{
	if (!parent)
		return;

	_parent = parent;
	_thisIt = parent->insertChild(this);
}

GLuint hObject::getBufSize()
{
	GLuint size = 0;
	for (auto childIt = _children.begin(); childIt != _children.end(); ++childIt)
		size += (*childIt)->getBufSize();

	return size;
}

GLuint hObject::getEleBufSize()
{
	GLuint size = 0;
	for (auto childIt = _children.begin(); childIt != _children.end(); ++childIt)
		size += (*childIt)->getEleBufSize();

	return size;
}

void hObject::initialize(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset)
{
	for (auto childIt = _children.begin(); childIt != _children.end(); ++childIt)
		(*childIt)->initialize(winSize, vbo, bOffset, veo, eOffset);
}

void hObject::display()
{
	for (auto childIt = _children.begin(); childIt != _children.end(); ++childIt)
		(*childIt)->display();
}

void hObject::finalize()
{
	if (_parent)
	{
		_parent->removeChild(_thisIt);
		_parent = NULL;
		_thisIt = hObjListIt();
	}

	for (auto childIt = _children.begin(); childIt != _children.end();)
	{
		auto pChild = *childIt++;
		pChild->finalize();
		delete pChild;
	}
}

hObjListIt hObject::insertChild(hObject* obj)
{
	if (!obj)
		return hObjListIt();

	return _children.insert(_children.end(), obj);
}

void hObject::removeChild(hObjListIt objIt)
{
	if (!objIt._Ptr)
		return;

	_children.erase(objIt);
}
