#ifndef _PPP_KESHPTAIL2X_H_
#define _PPP_KESHPTAIL2X_H_

#include "ffcc/partMng.h"

struct pppKeShpTail2X
{
    _pppPObject m_object;
};

struct pppKeShpTail2XUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail2X(struct pppKeShpTail2X*, struct pppKeShpTail2XUnkB*, _pppCtrlTable*);
void pppKeShpTail2XDraw(struct pppKeShpTail2X*, struct pppKeShpTail2XUnkB*, _pppCtrlTable*);
void pppKeShpTail2XCon(_pppPObject*, _pppCtrlTable*);
void pppKeShpTail2XDes(_pppPObject*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL2X_H_
