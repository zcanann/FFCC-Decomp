#ifndef _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
#define _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_

#include "ffcc/partMng.h"

struct _pppPObject;
struct pppYmMegaBirthShpTail3RenderStep;

typedef _pppPObject pppYmMegaBirthShpTail3;

struct PYmMegaBirthShpTail3
{
    Mtx m_matrix;
    Vec m_directionTail;
    float m_colorDeltaAdd[4];
    float m_sizeStart;
    float m_sizeVal;
    float m_speedRandRange;
    float m_speedScaleX;
    Vec m_speedScaleYZ;
    unsigned char m_randType;
    unsigned char m_enableParticleColor;
    unsigned char m_pad0x6a[0x6C - 0x6A];
    short m_pathIndex;
    unsigned char m_pad0x6e[0xB9 - 0x6E];
    unsigned char m_wmatCopyMode;
};

struct YmMegaBirthShpTail3DataOffsets
{
    s32 m_unusedOffset;
    s32 m_colorOffset;
    s32 m_workOffset;
};

struct pppYmMegaBirthShpTail3Offsets
{
    u8 m_pad_0x0[0xc];
    YmMegaBirthShpTail3DataOffsets* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3Offsets*);
void pppDestructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3Offsets*);
void pppFrameYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3Offsets*);
void pppRenderYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3RenderStep*, pppYmMegaBirthShpTail3Offsets*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
