#include "global.h"
#include "hRect.h"
#include "hObject.h"

hObject::hObject(PWhObj parent)
{
	if (parent)
		parent->addChild(this);
}

#if 0

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
#endif

bool hObject::loadUiCallback()
{
	if (!loadUi())
		return false;

	for (auto it = _children.begin(); it != _children.end(); ++it)
	{
		auto& pChild = *it;
		pChild->_parent = this;
		pChild->_thisIt = it;

		if (!pChild->loadUiCallback())
			return false;
	}

	return true;
}

bool hObject::initUiCallback(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset)
{
	if (!onInit(winSize, vbo, bOffset, veo, eOffset))
		return false;

	for (auto& pChild : _children)
	{
		if (!pChild->initUiCallback(winSize, vbo, bOffset, veo, eOffset))
			return false;
	}

	return true;
}

bool hObject::displayCallback(GLuint vao)
{
	if (!onDisplay(vao))
		return false;

	for (auto& pChild : _children)
	{
		if (!pChild->displayCallback(vao))
			return false;
	}

	return true;
}

GLuint hObject::calcBufSizeCallback()
{
	GLuint size = getBufSize();

	for (auto& pChild : _children)
		size += pChild->calcBufSizeCallback();

	return size;
}

GLuint hObject::calcEleBufSizeCallback()
{
	GLuint size = getEleBufSize();

	for (auto& pChild : _children)
		size += pChild->calcEleBufSizeCallback();

	return size;
}

void hObject::addChild(PhObj obj)
{
	if (obj)
		_children.push_back(obj);
}
#if 0
void hObject::removeChild(hObjListIt objIt)
{
	if (!objIt._Ptr)
		return;

	_children.erase(objIt);
}
#endif

