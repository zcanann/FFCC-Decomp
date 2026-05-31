#ifndef _FFCC_PPP_YMMIASMA_H_
#define _FFCC_PPP_YMMIASMA_H_

#include "ffcc/partMng.h"

struct pppYmMiasma {
    _pppPObject m_object;
};
struct pppYmMiasmaUnkB;
struct pppYmMiasmaUnkC {
    u8 m_pad_0x0[0xc];
    s32* m_serializedDataOffsets;
};
struct YmMiasmaRenderStep;
struct YmMiasmaFrameStep;
struct VYmMiasma;
struct PYmMiasma;
struct _pppPObject;
struct _pppCtrlTable;
#if defined(PPP_YMMIASMA_CUSTOM_PARTICLE_TYPES)
struct PARTICLE_DATA;
#else
struct _PARTICLE_DATA;
typedef _PARTICLE_DATA PARTICLE_DATA;
#endif

void InitParticleData(VYmMiasma*, _pppPObject*, PYmMiasma*, PARTICLE_DATA*);
void UpdateParticleData(_pppPObject*, _pppCtrlTable*, PYmMiasma*, PARTICLE_DATA*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMiasma(pppYmMiasma*, pppYmMiasmaUnkC*);
void pppConstruct2YmMiasma(pppYmMiasma*, pppYmMiasmaUnkC*);
void pppDestructYmMiasma(pppYmMiasma*, pppYmMiasmaUnkC*);
void pppFrameYmMiasma(pppYmMiasma*, YmMiasmaFrameStep*, pppYmMiasmaUnkC*);
void pppRenderYmMiasma(pppYmMiasma*, YmMiasmaRenderStep*, pppYmMiasmaUnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMIASMA_H_
