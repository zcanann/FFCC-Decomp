#ifndef _PPP_PARMOVEMATRIX_H_
#define _PPP_PARMOVEMATRIX_H_

#include "ffcc/partMng.h"

struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppParMoveMatrix(_pppPObject* obj, pppNoStep* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_PARMOVEMATRIX_H_
