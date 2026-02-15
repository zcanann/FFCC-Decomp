#ifndef _FFCC_PPBBREATHMODEL_H_
#define _FFCC_PPBBREATHMODEL_H_

struct _pppPObject;
struct _pppMngSt;
struct pppBreathModel;
struct UnkC;
struct VBreathModel;
struct PBreathModel;
struct VColor;
struct PARTICLE_DATA;
struct PARTICLE_WMAT;
struct PARTICLE_COLOR;

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

void pppFrameBreathModel(pppBreathModel*, PBreathModel*, UnkC*);
void pppRenderBreathModel(pppBreathModel*, PBreathModel*, UnkC*);
void pppConstructBreathModel(pppBreathModel*, UnkC*);
void pppDestructBreathModel(pppBreathModel*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif
