#include "global.h"
#include "hTool.h"
#include "hObject.h"

hObject::hObject(hObject* parent)
{
	if (!parent)
		return;

	_parent = parent;
	_thisIt = parent->insertChild(this);
}

void hObject::initialize(GLuint vbo, GLuint* offset)
{
	for (auto childIt = _children.begin(); childIt != _children.end(); ++childIt)
		(*childIt)->initialize();
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
