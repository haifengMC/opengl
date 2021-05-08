#include "global.h"

#include "hRect.h"
#include "hObject.h"
#include "hUiParam.h"
#include "hUi.h"

bool hUi::onPreInit(void* pDt)
{
	if (!onLoadUi())
		return false;

	for (auto it = _children.begin(); it != _children.end(); ++it)
	{
		hUi* pChild = dynamic_cast<hUi*>(*it);
		if (!pChild)
			return false;

		pChild->_parent = this;
		pChild->_thisIt = it;
	}

	return true;
}

bool hUi::onInit(void* pDt)
{
	if (!pDt)
		return false;

	UiParamInit* pParam = reinterpret_cast<UiParamInit*>(pDt);
	if (!onInitUi(*pParam))
		return false;

	return true;
}

bool hUi::showUiCallback(GLuint vao)
{
	if (!onShowUi(vao))
		return false;

	for (auto& pChild : _children)
	{
		if (!((hUi*)pChild)->showUiCallback(vao))
			return false;
	}

	return true;
}

GLuint hUi::calcBufSizeCallback()
{
	GLuint size = getBufSize();

	for (auto& pChild : _children)
		size += ((hUi*)pChild)->calcBufSizeCallback();

	return size;
}

GLuint hUi::calcEleBufSizeCallback()
{
	GLuint size = getEleBufSize();

	for (auto& pChild : _children)
		size += ((hUi*)pChild)->calcEleBufSizeCallback();

	return size;
}
