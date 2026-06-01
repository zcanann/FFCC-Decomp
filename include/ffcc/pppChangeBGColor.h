#ifndef _FFCC_PPPCHANGEBGCOLOR_H_
#define _FFCC_PPPCHANGEBGCOLOR_H_

#include "ffcc/partMng.h"

struct _GXColor;

#ifdef __cplusplus
extern "C" {
#endif

void pppConChangeBGColor(_pppPObjLink*, _pppCtrlTable*);
void pppDesChangeBGColor(_pppPObjLink*, _pppCtrlTable*);
void pppFrameChangeBGColor(_pppPObject* pppChangeBGColor, void* param_2, _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGEBGCOLOR_H_
