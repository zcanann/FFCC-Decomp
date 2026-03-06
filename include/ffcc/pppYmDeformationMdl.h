#ifndef _PPP_YMDEFORMATIONMDL_H_
#define _PPP_YMDEFORMATIONMDL_H_

#include <dolphin/types.h>

// Forward declarations
struct VYmDeformationMdl;

struct pppYmDeformationMdlUnkC {
    u8 m_pad_0x0[0xc];
    s32* m_serializedDataOffsets;
};

struct pppYmDeformationMdlUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_payload0;
    f32 m_payload1;
    f32 m_payload2;
    s16 m_payload3;
    u8 m_payloadBytes[0x1A];
};

struct pppYmDeformationMdl {
    char pad[0x80];
};

void SetUpIndWarp(VYmDeformationMdl*);
void DisableIndWarp(void);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationMdl(pppYmDeformationMdl*, struct pppYmDeformationMdlUnkC*);
void pppConstruct2YmDeformationMdl(pppYmDeformationMdl*, struct pppYmDeformationMdlUnkC*);
void pppDestructYmDeformationMdl(void);
void pppFrameYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, pppYmDeformationMdlUnkC* param_3);
void pppRenderYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, pppYmDeformationMdlUnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONMDL_H_

