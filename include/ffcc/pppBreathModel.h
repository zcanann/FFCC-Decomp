#ifndef _FFCC_PPBBREATHMODEL_H_
#define _FFCC_PPBBREATHMODEL_H_

#include <dolphin/mtx.h>

struct _pppPObject;
struct _pppMngSt;
struct pppBreathModel;
struct pppBreathModelUnkC;
struct VBreathModel;
struct PBreathModel;
struct VColor;
struct _PARTICLE_DATA;
struct _PARTICLE_COLOR;
typedef _PARTICLE_DATA PARTICLE_DATA;
typedef Mtx PARTICLE_WMAT;
typedef _PARTICLE_COLOR PARTICLE_COLOR;

void get_rand(void);
void BirthParticle(_pppPObject*, VBreathModel*, PBreathModel*, VColor*, PARTICLE_DATA*, PARTICLE_WMAT*, PARTICLE_COLOR*);
void SetParticleMatrix(_pppPObject*, VBreathModel*, PARTICLE_DATA*, PARTICLE_WMAT*, _pppMngSt*);
void UpdateParticle(VBreathModel*, PBreathModel*, PARTICLE_DATA*, VColor*, PARTICLE_COLOR*);
void UpdateAllParticle(_pppPObject*, VBreathModel*, PBreathModel*, VColor*);
void IsDeadGroupBreath(PBreathModel*, VBreathModel*, short);
void SearchIndex(PBreathModel*, VBreathModel*, short&, short&, short);
void IsExistGroupParticle(PBreathModel*, VBreathModel*, short);

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameBreathModel(pppBreathModel*, PBreathModel*, pppBreathModelUnkC*);
void pppRenderBreathModel(pppBreathModel*, PBreathModel*, pppBreathModelUnkC*);
void pppConstructBreathModel(pppBreathModel*, pppBreathModelUnkC*);
void pppDestructBreathModel(pppBreathModel*, pppBreathModelUnkC*);

#ifdef __cplusplus
}
#endif

#endif

