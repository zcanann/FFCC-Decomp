#ifndef _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
#define _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_

struct pppFVECTOR4;
struct VYmMegaBirthShpTail3;
struct PYmMegaBirthShpTail3;
struct _pppPObject;
struct VColor;
struct _PARTICLE_DATA;
struct _PARTICLE_WMAT;
struct _PARTICLE_COLOR;

void get_rand(void);
void S4ToF32(pppFVECTOR4 *, short *);
void alloc_check(VYmMegaBirthShpTail3 *, PYmMegaBirthShpTail3 *);
void pppConstructYmMegaBirthShpTail3(void);
void pppDestructYmMegaBirthShpTail3(void);
void birth(_pppPObject *, VYmMegaBirthShpTail3 *, PYmMegaBirthShpTail3 *, VColor *, _PARTICLE_DATA *, _PARTICLE_WMAT *, _PARTICLE_COLOR *);
void calc(_pppPObject *, VYmMegaBirthShpTail3 *, PYmMegaBirthShpTail3 *, _PARTICLE_DATA *, VColor *, _PARTICLE_COLOR *);
void calc_particle(_pppPObject *, VYmMegaBirthShpTail3 *, PYmMegaBirthShpTail3 *, VColor *);
void pppFrameYmMegaBirthShpTail3(void);
void pppRenderYmMegaBirthShpTail3(void);

#endif // _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
