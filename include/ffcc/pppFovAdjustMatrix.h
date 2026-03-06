#ifndef _FFCC_PPP_FOV_ADJUST_MATRIX_H_
#define _FFCC_PPP_FOV_ADJUST_MATRIX_H_

#include "ffcc/partMng.h"

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameFovAdjustMatrix(_pppPObject*, void*, _pppCtrlTable*);
void pppConstructFovAdjustMatrix(_pppPObjLink*, _pppCtrlTable*);
void pppDestructFovAdjustMatrix(_pppPObjLink*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_FOV_ADJUST_MATRIX_H_
