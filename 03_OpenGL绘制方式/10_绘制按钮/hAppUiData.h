#pragma once

class hAppUiData : public hAppBaseDataAdaptor
{
	PhObj _pObj;

public:
	PhObj getUi() { return _pObj; }
	void setUi(hObject* ui);

	bool loadUiCallback() { return _pObj->loadUiCallback(); }
};