#ifndef _PPP_LOCATIONTITLE_H_
#define _PPP_LOCATIONTITLE_H_

#include <dolphin/types.h>
#include "ffcc/partMng.h"

struct pppLocationTitle {
    u32 m_unk0;
    u32 m_unk4;
    u32 m_unk8;
    s32 m_graphId;
    pppFMATRIX m_localMatrix;
    char m_pad[0x54];
    void* field_0x88;
};

struct pppLocationTitleUnkB {
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

struct pppLocationTitleUnkC {
    char pad[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkC* param_2);
void pppDestructLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkC* param_2);
void pppFrameLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkB* param_2, pppLocationTitleUnkC* param_3);
void pppRenderLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkB* param_2, pppLocationTitleUnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LOCATIONTITLE_H_
