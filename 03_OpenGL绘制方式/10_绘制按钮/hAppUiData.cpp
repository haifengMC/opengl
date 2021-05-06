#include "global.h"

#include "hObject.h"
#include "hAppBase.h"
#include "hAppUiData.h"

void hAppUiData::setUi(hObject* ui)
{
	_pObj.bind(ui);
}

