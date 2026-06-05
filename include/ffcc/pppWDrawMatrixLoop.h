#ifndef _PPP_WDRAWMATRIXLOOP_H_
#define _PPP_WDRAWMATRIXLOOP_H_

#include "ffcc/partMng.h"

struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppWDrawMatrixLoop(_pppPObject* object, pppNoStep* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_WDRAWMATRIXLOOP_H_
