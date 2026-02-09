#ifndef _FFCC_PPP_YMMIASMA_H_
#define _FFCC_PPP_YMMIASMA_H_

#include <dolphin/types.h>

struct pppYmMiasma {
    u32 field0_0x0;
};
struct UnkB;
struct UnkC {
    u8 m_pad_0x0[0xc];
    s32* m_serializedDataOffsets;
};
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

void pppConstructYmMiasma(pppYmMiasma*, UnkC*);
void pppConstruct2YmMiasma(pppYmMiasma*, UnkC*);
void pppDestructYmMiasma(pppYmMiasma*, UnkC*);
void pppFrameYmMiasma(pppYmMiasma*, UnkB*, UnkC*);
void pppRenderYmMiasma(pppYmMiasma*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMIASMA_H_
