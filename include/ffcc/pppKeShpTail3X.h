#ifndef _PPP_KESHPTAIL3X_H_
#define _PPP_KESHPTAIL3X_H_

#include "ffcc/partMng.h"

struct pppFVECTOR4;

struct pppKeShpTail3X
{
    _pppPObject pppPObject;
    char field_0x34[0x48];
    char field_0x7d;
};

struct UnkB;
struct UnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail3X(struct pppKeShpTail3X*, struct UnkB*, struct UnkC*);
void pppKeShpTail3XDraw(struct pppKeShpTail3X*, struct UnkB*, struct UnkC*);
void pppKeShpTail3XCon(struct pppKeShpTail3X*, struct UnkC*);
void pppKeShpTail3XDes(void);
void S4ToF32(pppFVECTOR4*, short*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL3X_H_
