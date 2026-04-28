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
struct pppKeShpTail2XUnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail2X(struct pppKeShpTail2X*, struct pppKeShpTail2XUnkB*, struct pppKeShpTail2XUnkC*);
void pppKeShpTail2XDraw(struct pppKeShpTail2X*, struct pppKeShpTail2XUnkB*, struct pppKeShpTail2XUnkC*);
void pppKeShpTail2XCon(void*, void*);
void pppKeShpTail2XDes(void*, void*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL2X_H_
