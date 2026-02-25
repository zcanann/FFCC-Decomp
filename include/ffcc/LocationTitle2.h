#ifndef _FFCC_LOCATIONTITLE2_H_
#define _FFCC_LOCATIONTITLE2_H_

#include <dolphin/types.h>

struct pppLocationTitle2 {
    // Fields based on similar ppp* patterns
    char pad[0x80];  // Placeholder size, adjust based on actual usage
};

struct UnkB {
    u32 m_dataValIndex;
    u16 m_initWOrk;
    u16 m_pad;
    u32 m_graphId;
    float m_arg3;
    u8* m_payload;
    float m_stepValue;
};

struct UnkC {
    char pad[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle2(struct pppLocationTitle2*, struct UnkC*);
void pppDestructLocationTitle2(struct pppLocationTitle2*, struct UnkC*);
void pppFrameLocationTitle2(struct pppLocationTitle2*, struct UnkB*, struct UnkC*);
void pppRenderLocationTitle2(struct pppLocationTitle2*, struct UnkB*, struct UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_LOCATIONTITLE2_H_
