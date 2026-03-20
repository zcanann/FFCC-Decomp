#ifndef _FFCC_PPP_YMMELT_H_
#define _FFCC_PPP_YMMELT_H_

#include <dolphin/gx.h>
#include <dolphin/types.h>

struct PYmMelt
{
    u8 _pad0[0xC];
    s32 m_graphId;
};

struct VERTEX_DATA
{
    s16 m_shapeFrame;
    u16 m_gridSize;
    u8 _padC[0x14];
    float m_heightBias;
    float m_collisionYOffset;
    float m_maxDropDistance;
    s16 _pad2C;
    u8 m_hideWhenNoGround;
};

struct PYmMeltDataOffsets {
    u8 _pad[0xC];
    s32* m_serializedDataOffsets;
};

struct YmMeltCtrl {
    s32 m_graphId;
    s32 m_dataValIndex;
    s16 m_shapeFrame;
    u16 m_gridSize;
    f32 m_stepValue;
    u8 m_blendMode;
    u8 _pad11;
    s16 m_phaseDivisor;
    u8 m_payload[0x20];
};

void InitPolygonData(PYmMelt*, VERTEX_DATA*, short);
void CalcPolygonHeight(PYmMelt*, VERTEX_DATA*, _GXColor*, float);

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
