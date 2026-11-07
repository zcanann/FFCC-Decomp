#ifndef _PPP_KESHPTAIL_H_
#define _PPP_KESHPTAIL_H_

#include "ffcc/pppPart.h"

struct pppKeShpTailStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail(_pppPObject*, pppKeShpTailStep*, _pppCtrlTable*);
void pppKeShpTailCon(_pppPObject* obj, _pppCtrlTable* ctrlTable);
void pppKeShpTailDraw(_pppPObject* obj, pppKeShpTailStep* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL_H_
