#ifndef _PPP_YMMEGABIRTHSHPTAIL2_H_
#define _PPP_YMMEGABIRTHSHPTAIL2_H_

struct pppFVECTOR4;
struct VYmMegaBirthShpTail2;
struct PYmMegaBirthShpTail2;
struct _pppPObject;
struct VColor;
struct _PARTICLE_DATA;
struct _PARTICLE_WMAT;
struct _PARTICLE_COLOR;

void get_rand(void);
void U8ToF32(pppFVECTOR4*, unsigned char*);
void alloc_check(VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*);
void pppConstructYmMegaBirthShpTail2(void);
void pppDestructYmMegaBirthShpTail2(void);
void birth(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void calc_particle(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*);
void pppFrameYmMegaBirthShpTail2(void);
void pppRenderYmMegaBirthShpTail2(void);

#endif // _PPP_YMMEGABIRTHSHPTAIL2_H_
