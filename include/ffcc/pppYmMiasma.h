#ifndef _FFCC_PPP_YMMIASMA_H_
#define _FFCC_PPP_YMMIASMA_H_

#include <dolphin/types.h>

struct pppYmMiasma {
    u8 m_pad0[0xC];
    s32 m_graphId;
};
struct pppYmMiasmaUnkB;
struct pppYmMiasmaUnkC {
    u8 m_pad_0x0[0xc];
    s32* m_serializedDataOffsets;
};
struct VYmMiasma;
struct PYmMiasma;
struct _pppPObject;
struct _pppCtrlTable;
struct _PARTICLE_DATA;
typedef _PARTICLE_DATA PARTICLE_DATA;

void InitParticleData(VYmMiasma*, _pppPObject*, PYmMiasma*, PARTICLE_DATA*);
void UpdateParticleData(_pppPObject*, _pppCtrlTable*, PYmMiasma*, PARTICLE_DATA*);
void RenderParticle(_pppPObject*, PYmMiasma*, PARTICLE_DATA*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMiasma(pppYmMiasma*, pppYmMiasmaUnkC*);
void pppConstruct2YmMiasma(pppYmMiasma*, pppYmMiasmaUnkC*);
void pppDestructYmMiasma(pppYmMiasma*, pppYmMiasmaUnkC*);
void pppFrameYmMiasma(pppYmMiasma*, pppYmMiasmaUnkB*, pppYmMiasmaUnkC*);
void pppRenderYmMiasma(pppYmMiasma*, pppYmMiasmaUnkB*, pppYmMiasmaUnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMIASMA_H_
