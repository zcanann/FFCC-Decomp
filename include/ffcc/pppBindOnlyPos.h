#ifndef _FFCC_PPPBINDONLYPOS_H_
#define _FFCC_PPPBINDONLYPOS_H_

#include "ffcc/partMng.h"

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructBindOnlyPos(_pppPObjLink*, _pppCtrlTable*);
void pppFrameBindOnlyPos(_pppPObject*, void*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif
