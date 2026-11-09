#ifndef _FFCC_PPPCHANGEBGCOLOR_H_
#define _FFCC_PPPCHANGEBGCOLOR_H_

#include "ffcc/partMng.h"

struct _GXColor;
struct pppNoStep;

typedef _pppPObject pppChangeBGColor;

#ifdef __cplusplus
extern "C" {
#endif

void pppConChangeBGColor(_pppPObjLink*, _pppCtrlTable*);
void pppDesChangeBGColor(_pppPObjLink*, _pppCtrlTable*);
void pppFrameChangeBGColor(pppChangeBGColor* changeBGColor, pppNoStep* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGEBGCOLOR_H_
