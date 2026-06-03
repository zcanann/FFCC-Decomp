#ifndef _FFCC_PPPBLURCHARA_H_
#define _FFCC_PPPBLURCHARA_H_

#include "ffcc/chara.h"
#include "ffcc/pppPart.h"

#include <dolphin/gx.h>
#include <dolphin/types.h>

class CGObject;

struct pppBlurChara {
    _pppPObject m_object;
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

struct pppBlurCharaWork {
    void* m_captureBuffer;
    CGObject* m_ownerObj;
    GXTexObj* m_smallTexObj;
    float m_savedModelField;
};

struct BlurCharaColorData {
    u8 _pad0[8];
    pppCVECTOR m_color;
};

struct BlurCharaTexData {
    u8 _pad0[4];
    CGObject* m_objPosBase;
    GXTexObj* m_texObj;
};

void BlurChara_SetBeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
void BlurChara_AfterDrawModelCallback(CChara::CModel*, void*, void*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructBlurChara(pppBlurChara*, _pppCtrlTable*);
void pppDestructBlurChara(pppBlurChara*, _pppCtrlTable*);
void pppFrameBlurChara(pppBlurChara*, pppBlurCharaUnkB*, _pppCtrlTable*);
void pppRenderBlurChara(pppBlurChara*, pppBlurCharaUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif
