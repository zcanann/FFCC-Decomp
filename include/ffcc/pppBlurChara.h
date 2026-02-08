#ifndef _FFCC_PPPBLURCHARA_H_
#define _FFCC_PPPBLURCHARA_H_

#include "ffcc/chara.h"
#include <dolphin/types.h>

struct pppBlurChara {
    int field0_0x0[2];
};

struct UnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u8 _pad0[2];
    float m_stepValue;
    u8 m_arg3;
    u8 m_payload[6];
    u8 _pad1[1];
};

struct UnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

void BlurChara_SetBeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
void BlurChara_AfterDrawModelCallback(CChara::CModel*, void*, void*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructBlurChara(pppBlurChara*, UnkC*);
void pppDestructBlurChara(pppBlurChara*, UnkC*);
void pppFrameBlurChara(pppBlurChara*, UnkB*, UnkC*);
void pppRenderBlurChara(pppBlurChara*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif
