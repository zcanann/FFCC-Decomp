#ifndef _FFCC_LOCATIONTITLE2_H_
#define _FFCC_LOCATIONTITLE2_H_

#include "ffcc/partMng.h"
#include <dolphin/types.h>

struct pppLocationTitle2 {
    u32 m_unk0;
    u32 m_unk4;
    u32 m_unk8;
    u32 m_graphId;
    pppFMATRIX m_localMatrix;
    char m_pad[0x54];
    void* field_0x88;
};

struct pppLocationTitle2UnkB {
    u32 m_graphId;
    u32 m_dataValIndex;
    u16 m_initWOrk;
    u16 m_maxCount;
    float m_arg3;
    float* m_payload;
    float m_stepValue;
    u8 _pad0x18[0xA];
    u8 m_enableColorUpdate;
    u8 _pad0x23;
};

struct pppLocationTitle2UnkC {
    char pad[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle2(struct pppLocationTitle2*, struct pppLocationTitle2UnkC*);
void pppDestructLocationTitle2(struct pppLocationTitle2*, struct pppLocationTitle2UnkC*);
void pppFrameLocationTitle2(struct pppLocationTitle2*, struct pppLocationTitle2UnkB*, struct pppLocationTitle2UnkC*);
void pppRenderLocationTitle2(struct pppLocationTitle2*, struct pppLocationTitle2UnkB*, struct pppLocationTitle2UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_LOCATIONTITLE2_H_
