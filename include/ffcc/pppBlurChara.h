#ifndef _FFCC_PPPBLURCHARA_H_
#define _FFCC_PPPBLURCHARA_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppBlurChara;

struct BlurCharaDataOffsets {
    s32 _unused0;
    s32 m_colorDataOffset;
    s32 m_texDataOffset;
};

struct pppBlurCharaStep {
    s32 m_graphId;
    u8 m_afterDrawPass;
    u8 m_textureMode;
    u8 m_smallTextureDiv;
    u8 m_pad07;
    s32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_afterDrawOffsetY;
    u8 m_pad18;
    u8 m_alpha;
    u8 m_pad1A[2];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructBlurChara(pppBlurChara*, _pppCtrlTable*);
void pppDestructBlurChara(pppBlurChara*, _pppCtrlTable*);
void pppFrameBlurChara(pppBlurChara*, pppBlurCharaStep*, _pppCtrlTable*);
void pppRenderBlurChara(pppBlurChara*, pppBlurCharaStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif
