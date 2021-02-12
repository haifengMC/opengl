#pragma once


class hButton : public hObject, public hTool::hAutoPtrObj<hButton>
{
	hRect _rect;
public:
	hButton(hPWObj parent) : hObject(parent) {}
	hButton(hPWObj parent, const hRect& r);
};