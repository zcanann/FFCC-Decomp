#ifndef _PPP_KESHPTAIL2X_H_
#define _PPP_KESHPTAIL2X_H_

#include "ffcc/partMng.h"

struct pppKeShpTail2X
{
    u8 _pad0[0xc];
    _pppPObjectHead pppPObject;
    pppFMATRIX field_0x40;
};

struct pppKeShpTail2XUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail2X(struct pppKeShpTail2X*, struct pppKeShpTail2XUnkB*, _pppCtrlTable*);
void pppKeShpTail2XDraw(struct pppKeShpTail2X*, struct pppKeShpTail2XUnkB*, _pppCtrlTable*);
void pppKeShpTail2XCon(void*, _pppCtrlTable*);
void pppKeShpTail2XDes(void*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL2X_H_
