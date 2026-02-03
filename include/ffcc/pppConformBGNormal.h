#ifndef _FFCC_PPPCONFORMBGNORMAL_H_
#define _FFCC_PPPCONFORMBGNORMAL_H_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct pppConformBGNormal {
    u8 field0_0x0[8]; // Placeholder structure
};

struct UnkB {
    u8 m_stepValue;
    u8 padding[3];
    float m_initWOrk;
    float m_arg3;
    float m_dataValIndex;
};

struct UnkC {
    int* m_serializedDataOffsets;
};

void pppConstructConformBGNormal(struct pppConformBGNormal* conformBG, struct UnkC* param2);
void pppFrameConformBGNormal(struct pppConformBGNormal* conformBG, struct UnkB* param2, struct UnkC* param3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONFORMBGNORMAL_H_
