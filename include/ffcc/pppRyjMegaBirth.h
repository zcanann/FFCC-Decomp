#ifndef _PPP_RYJMEGABIRTH_H_
#define _PPP_RYJMEGABIRTH_H_

#include "ffcc/partMng.h"

typedef _PARTICLE_DATA PRyjMegaBirth; // Size 0x140

struct VRyjMegaBirth
{

};

void get_rand(void);
void get_noise(unsigned char);
void alloc_check(VRyjMegaBirth*, PRyjMegaBirth*);
void birth(_pppPObject*, VRyjMegaBirth*, PRyjMegaBirth*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(VRyjMegaBirth*, PRyjMegaBirth*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void calc_particle(_pppPObject*, VRyjMegaBirth*, PRyjMegaBirth*, VColor*);
void pppRyjMegaBirth(void);
void init_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirth*, VRyjMegaBirth*);
void set_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirth*, VRyjMegaBirth*, _PARTICLE_DATA*, _PARTICLE_WMAT*);
void pppRyjDrawMegaBirth(void);
void pppRyjMegaBirthCon(void);
void pppRyjMegaBirthDes(void);

#endif // _PPP_RYJMEGABIRTH_H_
