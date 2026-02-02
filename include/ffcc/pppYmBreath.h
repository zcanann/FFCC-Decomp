#ifndef _PPP_YMBREATH_H_
#define _PPP_YMBREATH_H_

struct _pppPObject;
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

void pppFrameYmBreath(void);
void pppRenderYmBreath(void);
void pppConstructYmBreath(void);
void pppConstruct2YmBreath(void);
void pppDestructYmBreath(void);

#ifdef __cplusplus
}
#endif

void IsDeadGroupBreath(PYmBreath*, VYmBreath*, short);
void SearchIndex(PYmBreath*, VYmBreath*, short&, short&, short);
void IsExistGroupParticle(PYmBreath*, VYmBreath*, short);

#endif // _PPP_YMBREATH_H_
