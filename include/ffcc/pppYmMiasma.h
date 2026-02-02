#ifndef _FFCC_PPP_YMMIASMA_H_
#define _FFCC_PPP_YMMIASMA_H_

struct VYmMiasma;
struct PYmMiasma;
struct _pppPObject;
struct _pppCtrlTable;
struct _PARTICLE_DATA;

void InitParticleData(VYmMiasma*, _pppPObject*, PYmMiasma*, _PARTICLE_DATA*);
void UpdateParticleData(_pppPObject*, _pppCtrlTable*, PYmMiasma*, _PARTICLE_DATA*);
void RenderParticle(_pppPObject*, PYmMiasma*, _PARTICLE_DATA*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMiasma(void);
void pppConstruct2YmMiasma(void);
void pppDestructYmMiasma(void);
void pppFrameYmMiasma(void);
void pppRenderYmMiasma(void);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMIASMA_H_
