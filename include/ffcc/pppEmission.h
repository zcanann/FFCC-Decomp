#ifndef _PPPEMISSION_H_
#define _PPPEMISSION_H_

#include "ffcc/chara.h"
#include "ffcc/partMng.h"

#include <dolphin/types.h>

class CMaterialMan;

struct pppEmission {
    _pppPObject m_object;
};

struct PEmission {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_initWOrk;
    u8 _pad8[3];
    f32 m_stepValue;
    f32 m_arg3;
    u8 m_payload[0x20];
};
typedef PEmission pppEmissionUnkB;

void Emission_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void Emission_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEmission(pppEmission*, _pppCtrlTable*);
void pppConstruct2Emission(pppEmission*, _pppCtrlTable*);
void pppDestructEmission(pppEmission*, _pppCtrlTable*);
void pppFrameEmission(pppEmission*, pppEmissionUnkB*, _pppCtrlTable*);
void pppRenderEmission(pppEmission*, pppEmissionUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPPEMISSION_H_
