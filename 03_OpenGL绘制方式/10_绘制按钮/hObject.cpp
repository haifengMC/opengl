#include "global.h"
#include "vcommon.h"
#include "hRect.h"
#include "hObject.h"

hObject::hObject(hObject* parent)
{
	if (parent)
		parent->addChild(this);
}

hObject::~hObject()
{
	finalCallback();
}

void hObject::addChild(hObject* pChild)
{
	if (pChild)
		_children.push_back(pChild);
}

void hObject::delChild(hObjListIt childIt)
{
	if (!_thisIt._Ptr)
		return;

	_children.erase(_thisIt);
}

bool hObject::preInitCallback(void* pDt)
{
	if (!onPreInit(pDt))
		return false;

	for (auto& pChild : _children)
	{
		if (!pChild->preInitCallback(pDt))
			return false;
	}

	return true;
}

bool hObject::initCallback(void* pDt)
{
	if (!onInit(pDt))
		return false;

	for (auto& pChild : _children)
	{
		if (!pChild->initCallback(pDt))
			return false;
	}

	return true;
}

bool hObject::finalCallback()
{
	onFinal();

	if (_parent)
	{
		_parent->delChild(_thisIt);
		_parent = NULL;
		_thisIt = hObjListIt();
	}

	for (auto pChild : _children)
	{
		pChild->finalCallback();
		DEL(pChild);
	}
	_children.clear();

	return true;
}

