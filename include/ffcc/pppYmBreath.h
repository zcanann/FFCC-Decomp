#ifndef _PPP_YMBREATH_H_
#define _PPP_YMBREATH_H_

struct _pppPObject;
struct pppYmBreath;
struct UnkC;
struct VYmBreath;
struct PYmBreath;
struct VColor;
struct PARTICLE_DATA;
struct PARTICLE_WMAT;
struct PARTICLE_COLOR;

void get_rand(void);
void BirthParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*, PARTICLE_DATA*, PARTICLE_WMAT*, PARTICLE_COLOR*);
void UpdateParticle(VYmBreath*, PYmBreath*, PARTICLE_DATA*, VColor*, PARTICLE_COLOR*);
void UpdateAllParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*);
void SetParticleMatrix(_pppPObject*, VYmBreath*, PARTICLE_DATA*, PARTICLE_WMAT*);

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameYmBreath(pppYmBreath*, PYmBreath*, UnkC*);
void pppRenderYmBreath(pppYmBreath*, PYmBreath*, UnkC*);
void pppConstructYmBreath(pppYmBreath*, UnkC*);
void pppConstruct2YmBreath(void);
void pppDestructYmBreath(pppYmBreath*, UnkC*);

#ifdef __cplusplus
}
#endif

void IsDeadGroupBreath(PYmBreath*, VYmBreath*, short);
void SearchIndex(PYmBreath*, VYmBreath*, short&, short&, short);
void IsExistGroupParticle(PYmBreath*, VYmBreath*, short);

#endif // _PPP_YMBREATH_H_
