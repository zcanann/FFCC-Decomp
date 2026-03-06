#ifndef _PPP_YMBREATH_H_
#define _PPP_YMBREATH_H_

#include <dolphin/mtx.h>

struct _pppPObject;
struct pppYmBreath;
struct pppYmBreathUnkC;
struct VYmBreath;
struct PYmBreath;
struct VColor;
struct _PARTICLE_DATA;
struct _PARTICLE_COLOR;
typedef _PARTICLE_DATA PARTICLE_DATA;
typedef Mtx PARTICLE_WMAT;
typedef _PARTICLE_COLOR PARTICLE_COLOR;

void get_rand(void);
void BirthParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*, PARTICLE_DATA*, PARTICLE_WMAT*, PARTICLE_COLOR*);
void UpdateParticle(VYmBreath*, PYmBreath*, PARTICLE_DATA*, VColor*, PARTICLE_COLOR*);
void UpdateAllParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*);
void SetParticleMatrix(_pppPObject*, VYmBreath*, PARTICLE_DATA*, PARTICLE_WMAT*);

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameYmBreath(pppYmBreath*, PYmBreath*, pppYmBreathUnkC*);
void pppRenderYmBreath(pppYmBreath*, PYmBreath*, pppYmBreathUnkC*);
void pppConstructYmBreath(pppYmBreath*, pppYmBreathUnkC*);
void pppConstruct2YmBreath(_pppPObject* obj);
void pppDestructYmBreath(pppYmBreath*, pppYmBreathUnkC*);

#ifdef __cplusplus
}
#endif

void IsDeadGroupBreath(PYmBreath*, VYmBreath*, short);
void SearchIndex(PYmBreath*, VYmBreath*, short&, short&, short);
void IsExistGroupParticle(PYmBreath*, VYmBreath*, short);

#endif // _PPP_YMBREATH_H_

