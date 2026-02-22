#ifndef _FFCC_PPP_YMMELT_H_
#define _FFCC_PPP_YMMELT_H_

#include <dolphin/gx.h>
#include <dolphin/types.h>

struct PYmMelt
{

};

struct VERTEX_DATA
{
    u8 _pad0[0xA];
    u16 m_gridSize;
    u8 _padC[0x14];
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
    s32 m_initWOrk;
    f32 m_stepValue;
    s32 m_arg3;
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
