#ifndef _PPP_YMMEGABIRTHSHPTAIL2_H_
#define _PPP_YMMEGABIRTHSHPTAIL2_H_

#include "ffcc/partMng.h"

struct _pppPObject;

typedef _pppPObject pppYmMegaBirthShpTail2;

struct YmMegaBirthShpTail2DataOffsets {
    s32 m_unusedOffset;
    s32 m_colorOffset;
    s32 m_workOffset;
};

struct PYmMegaBirthShpTail2
{
    s32 m_graphId;                    // 0x00
    s32 m_shapeIndex;                 // 0x04
    s32 m_frameStep;                  // 0x08
    u8 m_fogIndex;                    // 0x0C
    u8 m_pad0D;
    u16 m_maxParticles;               // 0x0E
    u16 m_emitCount;                  // 0x10
    u16 m_emitInterval;               // 0x12
    u16 m_life;                       // 0x14
    u8 m_fadeInFrames;                // 0x16
    u8 m_fadeOutFrames;               // 0x17
    u8 m_spawnMode;                   // 0x18
    u8 m_spread;                      // 0x19
    u8 m_pad1A[6];
    Vec m_baseDirection;              // 0x20
    u8 m_pad2C[4];
    Vec m_tailDirection;              // 0x30
    float m_unk3C;
    float m_speed;                    // 0x40
    float m_speedStep;                // 0x44
    float m_speedRandom;              // 0x48
    float m_tailSpeed;                // 0x4C
    float m_tailSpeedStep;            // 0x50
    float m_spawnRange;               // 0x54
    Vec m_spawnScale;                 // 0x58
    u8 m_pad64[4];
    u8 m_randType;                    // 0x68
    u8 m_enableParticleColor;         // 0x69
    u8 m_pad6A;
    u8 m_disableDepthTest;            // 0x6B
    s16 m_pathIndex;                  // 0x6C
    u8 m_blendMode;                   // 0x6E
    u8 m_pad6F;
    float m_drawScaleStart;           // 0x70
    float m_drawScaleEnd;             // 0x74
    GXColor m_colorStart;             // 0x78
    GXColor m_colorEnd;               // 0x7C
    float m_segmentLength;            // 0x80
    u16 m_drawCount;                  // 0x84
    u8 m_drawHead;                    // 0x86
    u8 m_pad87;
    float m_depth;                    // 0x88
    u8 m_lightTarget;                 // 0x8C
    u8 m_matrixMode;                  // 0x8D
    u8 m_pad8E[2];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, _pppCtrlTable*);
void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, _pppCtrlTable*);
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _pppCtrlTable*);
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMMEGABIRTHSHPTAIL2_H_
