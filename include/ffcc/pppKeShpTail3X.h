#ifndef _PPP_KESHPTAIL3X_H_
#define _PPP_KESHPTAIL3X_H_

#include "ffcc/partMng.h"

struct pppKeShpTail3X
{
    u8 _pad0[0xc];
    _pppPObject pppPObject;
    pppFMATRIX field_0x40;
    u8 field_0x70[0xd];
    u8 field_0x7d;
};

struct pppKeShpTail3XUnkB;
struct pppKeShpTail3XUnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail3X(struct pppKeShpTail3X*, struct pppKeShpTail3XUnkB*, struct pppKeShpTail3XUnkC*);
void pppKeShpTail3XDraw(struct pppKeShpTail3X*, struct pppKeShpTail3XUnkB*, struct pppKeShpTail3XUnkC*);
void pppKeShpTail3XCon(struct pppKeShpTail3X*, struct pppKeShpTail3XUnkC*);
void pppKeShpTail3XDes(_pppPObjLink* obj, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL3X_H_
