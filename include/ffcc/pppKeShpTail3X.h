#ifndef _PPP_KESHPTAIL3X_H_
#define _PPP_KESHPTAIL3X_H_

#include "ffcc/partMng.h"

struct pppKeShpTail3X
{
    _pppPObject m_object;
};

struct pppKeShpTail3XUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail3X(struct pppKeShpTail3X*, struct pppKeShpTail3XUnkB*, struct _pppCtrlTable*);
void pppKeShpTail3XDraw(struct pppKeShpTail3X*, struct pppKeShpTail3XUnkB*, struct _pppCtrlTable*);
void pppKeShpTail3XCon(struct pppKeShpTail3X*, struct _pppCtrlTable*);
void pppKeShpTail3XDes(_pppPObjLink* obj, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL3X_H_
