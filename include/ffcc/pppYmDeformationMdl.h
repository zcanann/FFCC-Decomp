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
    u8 m_pad22[2];
    f32 m_payload4;
    u8 m_payloadByte28;
    u8 m_payloadByte29;
    u8 m_payloadByte2A;
    u8 m_payloadByte2B;
    u8 m_payloadByte2C;
    u8 m_pad2D[0xF];
};

struct pppYmDeformationMdl {
    char pad[0x80];
};

void SetUpIndWarp(VYmDeformationMdl*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationMdl(pppYmDeformationMdl*, struct pppYmDeformationMdlUnkC*);
void pppConstruct2YmDeformationMdl(pppYmDeformationMdl*, struct pppYmDeformationMdlUnkC*);
void pppDestructYmDeformationMdl(pppYmDeformationMdl*, struct pppYmDeformationMdlUnkC*);
void pppFrameYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, pppYmDeformationMdlUnkC* param_3);
void pppRenderYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, pppYmDeformationMdlUnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONMDL_H_
