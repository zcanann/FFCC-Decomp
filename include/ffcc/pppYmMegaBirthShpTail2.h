#ifndef _PPP_YMMEGABIRTHSHPTAIL2_H_
#define _PPP_YMMEGABIRTHSHPTAIL2_H_

#include "ffcc/partMng.h"

typedef _PARTICLE_DATA PYmMegaBirthShpTail2; // Size 0x140

struct pppYmMegaBirthShpTail2
{
    _pppPObject field0_0x0;    // 0x0
    pppFMATRIX field_0x40;     // 0x40
    char field_0x70[0x4c];     // 0x70 - padding/other fields
    unsigned int field_0xbc;   // 0xbc
    unsigned int field_0xc0;   // 0xc0
    unsigned int field_0xc4;   // 0xc4
    unsigned int field_0xc8;   // 0xc8
    char m_data[0x500];        // 0xcc - additional data
};

struct VYmMegaBirthShpTail2
{
    pppFMATRIX m_emitterMatrix;         // 0x0
    _PARTICLE_DATA* m_particles;        // 0x30
    _PARTICLE_WMAT* m_wmats;            // 0x34
    _PARTICLE_COLOR* m_colors;          // 0x38
    unsigned int m_maxParticles;        // 0x3c
    unsigned int m_lifeLimit;           // 0x40
    Vec m_tailScaleDirection;           // 0x44
};

struct UnkB;
struct UnkC {
    u8 m_pad_0x0[0xc];
    s32* m_serializedDataOffsets;
};

void get_rand(void);
void U8ToF32(pppFVECTOR4*, unsigned char*);
void alloc_check(VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*);
void birth(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void calc_particle(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, UnkC*);
void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, UnkC*);
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, UnkC*);
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMMEGABIRTHSHPTAIL2_H_
