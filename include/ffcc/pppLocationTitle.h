#ifndef _PPP_LOCATIONTITLE_H_
#define _PPP_LOCATIONTITLE_H_

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppLocationTitle;
typedef _pppCtrlTable pppLocationTitleOffsets;

struct LocationTitleDataOffsets {
    s32 m_workOffset;
    s32 m_colorOffset;
};

struct LocationTitleParticle {
    Vec m_pos;
    GXColor m_color;
    float m_frame;
    s16 m_shapeUnk;
    s16 m_shapeA;
    s16 m_shapeB;
    s16 m_pad;
};

struct LocationTitleWork {
    LocationTitleParticle* m_particles;
    u16 m_count;
    u16 m_pad;
    float m_cur;
    float m_vel;
    float m_acc;
};

struct pppLocationTitleStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u16 m_maxCount;
    u8 m_stepCount;
    u8 m_blendMode;
    u8 m_pad0E;
    u8 m_pad0F;
    float m_arg3;
    float m_payload0;
    float m_payload1;
    u16 m_spawnFrame;
    u16 m_fadeStartFrame;
    u16 m_fadeLength;
    u16 m_pad;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle(pppLocationTitle* locationTitle, pppLocationTitleOffsets* offsets);
void pppDestructLocationTitle(pppLocationTitle* locationTitle, pppLocationTitleOffsets* offsets);
void pppFrameLocationTitle(pppLocationTitle* locationTitle, pppLocationTitleStep* step, pppLocationTitleOffsets* offsets);
void pppRenderLocationTitle(pppLocationTitle* locationTitle, pppLocationTitleStep* step, pppLocationTitleOffsets* offsets);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LOCATIONTITLE_H_
