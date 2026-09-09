#ifndef _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
#define _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_

#include "ffcc/partMng.h"

struct _pppPObject;

typedef _pppPObject pppYmMegaBirthShpTail3;

struct PYmMegaBirthShpTail3
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
    u8 m_disableDepthTest;            // 0x69
    s16 m_pathIndex;                  // 0x6A
    u8 m_blendMode;                   // 0x6C
    u8 m_pad6D[3];
    float m_drawScaleStart;           // 0x70
    float m_drawScaleEnd;             // 0x74
    s16 m_colorStart[4]; // 0x78
    s16 m_colorEnd[4]; // 0x80
    s16 m_colorStartStep[4]; // 0x88
    s16 m_colorStartAcceleration[4]; // 0x90
    s16 m_colorEndStep[4]; // 0x98
    s16 m_colorEndAcceleration[4]; // 0xA0
    u16 m_rotationEnabled;            // 0xA8
    u8 m_padAA[2];
    float m_segmentLength;            // 0xAC
    u16 m_drawCount;                  // 0xB0
    u8 m_drawHead;                    // 0xB2
    u8 m_padB3;
    float m_depth;                    // 0xB4
    u8 m_lightTarget;                 // 0xB8
    u8 m_matrixMode;                  // 0xB9
    u8 m_padBA[2];
};

struct YmMegaBirthShpTail3DataOffsets
{
    s32 m_unusedOffset;
    s32 m_colorOffset;
    s32 m_workOffset;
};


#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, _pppCtrlTable*);
void pppDestructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, _pppCtrlTable*);
void pppFrameYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, _pppCtrlTable*);
void pppRenderYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
