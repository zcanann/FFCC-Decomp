#ifndef _FFCC_PPPCONFORMBGNORMAL_H_
#define _FFCC_PPPCONFORMBGNORMAL_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppConformBGNormal;

struct ConformBgNormalDataOffsets {
    s32 m_stateOffset;
};

struct pppConformBGNormalStep {
    u32 m_unk0;
    f32 m_dataValIndex;
    f32 m_initWOrk;
    u8 m_stepValue;
    u8 m_pad0D[3];
    f32 m_arg3;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructConformBGNormal(pppConformBGNormal* conformBG, struct _pppCtrlTable* ctrl);
void pppFrameConformBGNormal(pppConformBGNormal* conformBG, pppConformBGNormalStep* step, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONFORMBGNORMAL_H_
