#ifndef _PPP_LASER_H_
#define _PPP_LASER_H_

#include "dolphin/types.h"

struct pppLaser {
    u8 field_0x0[0x84];
    f32 field_0x84;     // 0x84
    f32 field_0x88;     // 0x88
    f32 field_0x8c;     // 0x8c
    f32 field_0x90;     // 0x90
    f32 field_0x94;     // 0x94
    f32 field_0x98;     // 0x98
    f32 field_0x9c;     // 0x9c
    f32 field_0xa0;     // 0xa0
    f32 field_0xa4;     // 0xa4
    f32 field_0xa8;     // 0xa8
    u8 field_0xac;      // 0xac
};

struct UnkB {
    // TODO: Define UnkB structure
    u8 placeholder[0x100];
};

struct UnkCLaserOffsets {
    int m_serializedDataOffsets[3];
};

struct UnkC {
    u8 unk_00[0xc];
    UnkCLaserOffsets* offsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLaser(struct pppLaser* pppLaser, struct UnkC* param_2);
void pppConstruct2Laser(struct pppLaser* pppLaser, struct UnkC* param_2);
void pppDestructLaser(struct pppLaser* pppLaser, struct UnkC* param_2);
void pppFrameLaser(struct pppLaser* pppLaser, struct UnkB* param_2, struct UnkC* param_3);
void pppRenderLaser(struct pppLaser* pppLaser, struct UnkB* param_2, struct UnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LASER_H_
