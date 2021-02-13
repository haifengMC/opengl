#pragma once


class hButton : public hObject
{
	hRect _rect;
public:
	hButton(hObject* parent) : hObject(parent) {}
	hButton(hObject* parent, const hRect& r);
};