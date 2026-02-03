#ifndef _FFCC_KELNS_H_
#define _FFCC_KELNS_H_

#include "ffcc/partMng.h"

struct _KeLnsLp {
    char pad1[0x30];         // 0x0 to 0x30
    pppFMATRIX matrix;       // 0x30 (pppFMATRIX at offset 0x30)
    char pad2[0x3C];         // 0x60 to 0x9C  (0x30 size of pppFMATRIX + 0x3C = 0x6C)
    float field_0x9c;        // 0x9C (float at offset 0x9c)
};

void KeLnsLp_Init(_KeLnsLp*);

#endif // _FFCC_KELNS_H_
