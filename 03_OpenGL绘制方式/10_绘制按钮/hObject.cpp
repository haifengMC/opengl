#include "global.h"
#include "hTool.h"
#include "hObject.h"

hObject::hObject(hObject* parent)
{
	if (parent)
	{
		_parent = getThis();
	}
}

hObject::hObject(hPWObj parent)
{
	if (parent)
	{
		_parent = parent;
		_thisIt = parent->insertChild(this);
	}
}

void hObject::Finalize(void)
{
	_parent = NULL;
	_thisIt = hPObjListIt();
	_children.clear();
}

hPObjListIt hObject::insertChild(hPObj obj)
{
	if (!obj)
		return hPObjListIt();

	return _children.insert(_children.end(), obj);
}

void hObject::removeChild(hPObj obj)
{
	if (!obj)
		return;
	_children.erase(obj->_thisIt);
}
