#ifndef _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
#define _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_

#include "ffcc/partMng.h"

struct VYmMegaBirthShpTail3
{
    _PARTICLE_DATA m_baseData;  // 0x0 - 0x140
    Vec m_tailScaleDirection;   // 0x140 - 0x14c
}; // Size 0x14c+

struct PYmMegaBirthShpTail3
{
    pppFMATRIX m_matrix;        // 0x0 - 0x30
    float m_colorDeltaAdd[4];   // 0x30 - 0x40
    float m_sizeVal;            // 0x40 - 0x44
}; // Size 0x44+

// Helper functions  
void pppScaleVectorXYZ(float scale, Vec* result, const Vec* input);
void pppAddVector(_PARTICLE_DATA* particle, Vec* dest, const Vec* src);

void get_rand(void);
void S4ToF32(pppFVECTOR4*, short*);
void alloc_check(VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*);
void birth(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void calc_particle(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, VColor*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMegaBirthShpTail3(void);
void pppDestructYmMegaBirthShpTail3(void);
void pppFrameYmMegaBirthShpTail3(void);
void pppRenderYmMegaBirthShpTail3(void);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
