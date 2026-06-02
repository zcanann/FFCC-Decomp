#ifndef _PPP_YMBREATH_H_
#define _PPP_YMBREATH_H_

#include <dolphin/mtx.h>

struct _pppPObject;
struct _pppCtrlTable;
struct pppYmBreath;
struct VYmBreath;
struct PYmBreath;
struct VColor;
struct _PARTICLE_DATA;
struct _PARTICLE_COLOR;

#ifdef PPP_YMBREATH_CUSTOM_PARTICLE_TYPES
struct PARTICLE_DATA;
struct PARTICLE_WMAT;
struct PARTICLE_COLOR;
#else
typedef _PARTICLE_DATA PARTICLE_DATA;
typedef Mtx PARTICLE_WMAT;
typedef _PARTICLE_COLOR PARTICLE_COLOR;
#endif

void get_rand(void);
void BirthParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*, PARTICLE_DATA*, PARTICLE_WMAT*, PARTICLE_COLOR*);
void UpdateParticle(VYmBreath*, PYmBreath*, PARTICLE_DATA*, VColor*, PARTICLE_COLOR*);
void UpdateAllParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*);
void SetParticleMatrix(_pppPObject*, VYmBreath*, PARTICLE_DATA*, PARTICLE_WMAT*);

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameYmBreath(pppYmBreath*, PYmBreath*, _pppCtrlTable*);
void pppRenderYmBreath(pppYmBreath*, PYmBreath*, _pppCtrlTable*);
void pppConstructYmBreath(pppYmBreath*, _pppCtrlTable*);
void pppConstruct2YmBreath(_pppPObject* obj);
void pppDestructYmBreath(pppYmBreath*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

void IsDeadGroupBreath(PYmBreath*, VYmBreath*, short);
void SearchIndex(PYmBreath*, VYmBreath*, short&, short&, short);
void IsExistGroupParticle(PYmBreath*, VYmBreath*, short);

#endif // _PPP_YMBREATH_H_
