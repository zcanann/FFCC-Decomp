#ifndef _FFCC_PPP_YMMELT_H_
#define _FFCC_PPP_YMMELT_H_

#include <dolphin/gx.h>
#include <dolphin/types.h>

#include "ffcc/pppPart.h"

struct PYmMelt
{
    _pppPObject m_object;
};

struct YmMeltVertex
{
    Vec m_position;
    union {
        _GXColor m_gxColor;
        u32 m_rawColor;
        float m_colorValue;
        u8 m_bytes[4];
    } m_color;
};

struct YmMeltWork {
    YmMeltVertex* m_vertexData;
    s16 m_phaseOffset;
    s16 m_shapeCurrentFrame;
    s16 m_shapeDrawFrame;
    s16 m_shapeFrameTime;
    f32 m_phase;
    f32 m_phaseVelocity;
    f32 m_phaseAccel;
};

struct YmMeltColorWork {
    u8 _pad0[8];
    union {
        pppCVECTOR m_color;
        float m_colorValue;
    };
};

struct VERTEX_DATA
{
    u8 _pad0[0xA];
    u16 m_gridSize;
    f32 m_stepValue;
    u8 _pad10[0x10];
    float m_heightBias;
    float m_collisionYOffset;
    float m_maxDropDistance;
    u8 _pad2C[2];
    u8 m_hideWhenNoGround;
};

struct PYmMeltDataOffsets {
    u8 _pad[0xC];
    s32* m_serializedDataOffsets;
};

struct YmMeltCtrl {
    s32 m_graphId;
    s32 m_dataValIndex;
    s16 m_shapeFrameStep;
    u16 m_gridSize;
    f32 m_stepValue;
    u8 m_blendMode;
    u8 _pad11;
    s16 m_phasePeriod;
    union {
        u8 m_payload[0x20];
        struct Payload {
            f32 m_phaseDelta;
            f32 m_phaseVelocityDelta;
            f32 m_phaseAccelDelta;
            u8 m_pad0C[0x0C];
            u8 m_drawEnvColor0;
            u8 m_drawEnvColor1;
            u8 m_pad1A[0x06];
        } m_melt;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMelt(PYmMelt*, PYmMeltDataOffsets*);
void pppDestructYmMelt(PYmMelt*, PYmMeltDataOffsets*);
void pppFrameYmMelt(PYmMelt*, YmMeltCtrl*, PYmMeltDataOffsets*);
void pppRenderYmMelt(PYmMelt*, YmMeltCtrl*, PYmMeltDataOffsets*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMELT_H_
