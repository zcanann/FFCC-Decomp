#ifndef _FFCC_PPPBLURCHARA_H_
#define _FFCC_PPPBLURCHARA_H_

#include "ffcc/chara.h"
#include <dolphin/types.h>

struct pppBlurChara {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;
};

struct pppBlurCharaUnkB {
    s32 m_graphId;
    u8 m_afterDrawPass;
    u8 m_textureMode;
    u8 m_smallTextureDiv;
    u8 _pad7;
    s32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_afterDrawOffsetY;
    u8 _pad18;
    u8 m_alpha;
    u8 _pad1A[2];
};

struct pppBlurCharaUnkC {
    u8 _pad0[0x0C];
    s32* m_serializedDataOffsets;
};

void BlurChara_SetBeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
void BlurChara_AfterDrawModelCallback(CChara::CModel*, void*, void*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructBlurChara(pppBlurChara*, pppBlurCharaUnkC*);
void pppDestructBlurChara(pppBlurChara*, pppBlurCharaUnkC*);
void pppFrameBlurChara(pppBlurChara*, pppBlurCharaUnkB*, pppBlurCharaUnkC*);
void pppRenderBlurChara(pppBlurChara*, pppBlurCharaUnkB*, pppBlurCharaUnkC*);

#ifdef __cplusplus
}
#endif

#endif
