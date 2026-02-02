#ifndef _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
#define _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_

#include "ffcc/partMng.h"

typedef _PARTICLE_DATA VYmMegaBirthShpTail3; // Size 0x140

struct PYmMegaBirthShpTail3
{

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

void pppConstructYmMegaBirthShpTail3(void);
void pppDestructYmMegaBirthShpTail3(void);
void pppFrameYmMegaBirthShpTail3(void);
void pppRenderYmMegaBirthShpTail3(void);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
