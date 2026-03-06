#ifndef _FFCC_PPPCONFORMBGNORMAL_H_
#define _FFCC_PPPCONFORMBGNORMAL_H_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct pppConformBGNormal {
    u8 field0_0x0[8]; // Placeholder structure
};

struct pppConformBGNormalUnkB {
    u32 _pad0;
    float m_dataValIndex;
    float m_initWOrk;
    u8 m_stepValue;
    u8 padding[3];
    float m_arg3;
};

struct pppConformBGNormalUnkC {
    int* m_serializedDataOffsets;
};

void pppConstructConformBGNormal(struct pppConformBGNormal* conformBG, struct pppConformBGNormalUnkC* param2);
void pppFrameConformBGNormal(struct pppConformBGNormal* conformBG, struct pppConformBGNormalUnkB* param2, struct pppConformBGNormalUnkC* param3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONFORMBGNORMAL_H_

