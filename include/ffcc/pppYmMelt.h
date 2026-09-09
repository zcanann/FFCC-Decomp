#ifndef _FFCC_PPP_YMMELT_H_
#define _FFCC_PPP_YMMELT_H_

#include "ffcc/pppPart.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;
struct PYmMelt;

typedef _pppCtrlTable PYmMeltDataOffsets;
typedef _pppPObject pppYmMelt;

struct YmMeltDataOffsets {
    s32 m_workOffset;
    s32 m_colorWorkOffset;
};

struct VERTEX_DATA
{
    Vec m_position;
    union {
        _GXColor m_gxColor;
        u32 m_rawColor;
        u8 m_bytes[4];
    } m_color;
};

struct YmMeltWork {
    VERTEX_DATA* m_vertexData;
    s16 m_phaseOffset;
    s16 m_shapeCurrentFrame;
    s16 m_shapeDrawFrame;
    s16 m_shapeFrameTime;
    f32 m_phase;
    f32 m_phaseVelocity;
    f32 m_phaseAccel;
};

struct PYmMelt {
    s32 m_graphId;
    s32 m_dataValIndex;
    s16 m_shapeFrameStep;
    u16 m_gridSize;
    f32 m_stepValue;
    u8 m_blendMode;
    u8 _pad11;
    s16 m_phasePeriod;
    f32 m_phaseDelta;
    f32 m_phaseVelocityDelta;
    f32 m_phaseAccelDelta;
    f32 m_heightBias;
    f32 m_collisionYOffset;
    f32 m_maxDropDistance;
    u8 _pad2C[2];
    u8 m_hideWhenNoGround;
    u8 _pad2F;
    u8 m_drawEnvColor0;
    u8 m_drawEnvColor1;
    u8 _pad32[2];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMelt(pppYmMelt*, PYmMeltDataOffsets*);
void pppDestructYmMelt(pppYmMelt*, PYmMeltDataOffsets*);
void pppFrameYmMelt(pppYmMelt*, PYmMelt*, PYmMeltDataOffsets*);
void pppRenderYmMelt(pppYmMelt*, PYmMelt*, PYmMeltDataOffsets*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMELT_H_
