#ifndef _PPP_KESHPTAIL_H_
#define _PPP_KESHPTAIL_H_

#include "ffcc/pppPart.h"

struct pppKeShpTailUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail(_pppPObject*, pppKeShpTailUnkB*, _pppCtrlTable*);
void pppKeShpTailCon(_pppPObject* obj, _pppCtrlTable* ctrlTable);
void pppKeShpTailDraw(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL_H_
