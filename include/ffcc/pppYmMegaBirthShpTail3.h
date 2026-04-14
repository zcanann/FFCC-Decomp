#ifndef _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
#define _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_

#include "ffcc/partMng.h"

struct pppYmMegaBirthShpTail3
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

struct VYmMegaBirthShpTail3
{
    pppFMATRIX m_emitterMatrix;   // 0x0
    Vec m_tailScaleDirection;     // 0x30
    _PARTICLE_DATA* m_particles;  // 0x3c
    _PARTICLE_WMAT* m_wmats;      // 0x40
    _PARTICLE_COLOR* m_colors;    // 0x44
    unsigned int m_maxParticles;  // 0x48
    unsigned int m_lifeLimit;     // 0x4c
};

struct PYmMegaBirthShpTail3 : _PARTICLE_DATA
{
};

struct pppYmMegaBirthShpTail3UnkB;
struct pppYmMegaBirthShpTail3UnkC
{
    u8 m_pad_0x0[0xc];
    s32* m_serializedDataOffsets;
};

void get_rand(void);
void S4ToF32(pppFVECTOR4*, short*);
void alloc_check(VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*);
void birth(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void calc_particle(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, VColor*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3UnkC*);
void pppDestructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3UnkC*);
void pppFrameYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3UnkC*);
void pppRenderYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3UnkB*, pppYmMegaBirthShpTail3UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
