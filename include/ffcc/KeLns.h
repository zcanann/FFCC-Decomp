#ifndef _FFCC_KELNS_H_
#define _FFCC_KELNS_H_

#include "ffcc/partMng.h"

struct _KeLnsLp {
    char pad1[0x30];         // 0x0 to 0x30
    pppFMATRIX matrix;       // 0x30 (pppFMATRIX at offset 0x30)
    char pad2[0x2C];         // 0x60 to 0x8C
    float m_work8C;          // 0x8C
    char pad3[0x08];         // 0x90 to 0x98
    float m_work98;          // 0x98
    float field_0x9c;        // 0x9C (float at offset 0x9c)
};

typedef char _KeLnsLp_size_check[(sizeof(_KeLnsLp) == 0xA0) ? 1 : -1];

void KeLnsLp_Init(_KeLnsLp*);

#endif // _FFCC_KELNS_H_
