#ifndef _PPP_RAIN_H_
#define _PPP_RAIN_H_

#include <dolphin/types.h>

struct pppRain {
    s32 m_graphId;
    u8 field_0x4[0x7C];
};

struct VRain;

struct PRain {
    s32 m_graphId;
    u16 m_dataValIndex;
    u8 _pad0[2];
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    u8 m_payload[0x4C];
};

struct RAIN_DATA {
    u8 padding[0xc];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructRain(struct pppRain*, struct RAIN_DATA*);
void pppDestructRain(struct pppRain*, struct RAIN_DATA*);
void pppFrameRain(struct pppRain*, struct PRain*, struct RAIN_DATA*);
void pppRenderRain(struct pppRain*, struct PRain*, struct RAIN_DATA*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RAIN_H_
