#ifndef _PPPEMISSION_H_
#define _PPPEMISSION_H_

#include "ffcc/chara.h"

#include <dolphin/types.h>

class CMaterialMan;

struct pppEmission {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;

    u8 _pad0[0x84];
    u8 field_0x88;
    u8 field_0x89;
    u8 field_0x8a;
    u8 field_0x8b;
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

struct pppEmissionUnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

void SetTexGenMode(PEmission*);
void Emission_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void Emission_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEmission(pppEmission*, pppEmissionUnkC*);
void pppConstruct2Emission(pppEmission*, pppEmissionUnkC*);
void pppDestructEmission(pppEmission*, pppEmissionUnkC*);
void pppFrameEmission(pppEmission*, pppEmissionUnkB*, pppEmissionUnkC*);
void pppRenderEmission(pppEmission*, pppEmissionUnkB*, pppEmissionUnkC*);

#ifdef __cplusplus
}
#endif

#endif // _PPPEMISSION_H_
