#ifndef _FFCC_LOCATIONTITLE2_H_
#define _FFCC_LOCATIONTITLE2_H_

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppLocationTitle2;
typedef _pppCtrlTable pppLocationTitle2Offsets;

struct LocationTitle2DataOffsets {
    s32 m_workOffset;
    s32 m_colorOffset;
};

struct LocationTitle2Particle {
    Vec m_pos;
    GXColor m_color;
    float m_scaleX;
    float m_scaleY;
    float m_scaleZ;
    u16 m_frame;
    s16 m_pad0;
    s16 m_pad1;
    s16 m_shape;
};

struct LocationTitle2Work {
    LocationTitle2Particle* m_particles;
    u16 m_count;
    u16 m_pad;
    float m_cur;
    float m_vel;
    float m_acc;
};

struct LocationTitle2ColorBlock {
    u8 m_pad[8];
    GXColor m_color;
};

struct pppLocationTitle2Step {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u16 m_maxCount;
    u8 m_stepCount;
    u8 m_blendMode;
    u8 _pad0x0E;
    u8 _pad0x0F;
    float m_arg3;
    float m_payload0;
    float m_payload1;
    u16 _pad0x1C;
    u16 _pad0x1E;
    u16 _pad0x20;
    u8 m_enableColorUpdate;
    u8 _pad0x23;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle2(pppLocationTitle2*, pppLocationTitle2Offsets*);
void pppDestructLocationTitle2(pppLocationTitle2*, pppLocationTitle2Offsets*);
void pppFrameLocationTitle2(pppLocationTitle2*, pppLocationTitle2Step*, pppLocationTitle2Offsets*);
void pppRenderLocationTitle2(pppLocationTitle2*, pppLocationTitle2Step*, pppLocationTitle2Offsets*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_LOCATIONTITLE2_H_
