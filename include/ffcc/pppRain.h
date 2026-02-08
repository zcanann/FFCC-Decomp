#ifndef _PPP_RAIN_H_
#define _PPP_RAIN_H_

#include <dolphin/types.h>

struct pppRain {
    u8 field_0x0[0x80];
};

struct VRain;

struct PRain {
    u8 payload[0x60];
};

struct RAIN_DATA {
    u8 padding[0xc];
    s32* m_serializedDataOffsets;
};

void InitRainData(VRain*, PRain*, RAIN_DATA*);
void UpdateRain(VRain*, PRain*, RAIN_DATA*);

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
