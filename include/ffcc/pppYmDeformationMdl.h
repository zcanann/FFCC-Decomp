#ifndef _PPP_YMDEFORMATIONMDL_H_
#define _PPP_YMDEFORMATIONMDL_H_

#include "ffcc/partMng.h"

#include <dolphin/types.h>

// Forward declarations
struct VYmDeformationMdl;

struct pppYmDeformationMdlUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    f32 m_scaleValueAdd;
    f32 m_scaleVelocityAdd;
    f32 m_scaleAccelerationAdd;
    f32 m_angleValueAdd;
    f32 m_angleVelocityAdd;
    f32 m_angleAccelerationAdd;
    s16 m_angleLimit;
    u8 m_pad22[2];
    f32 m_envDepth;
    u8 m_blendMode;
    u8 m_cullMode;
    u8 m_fogIndex;
    u8 m_lightTarget;
    u8 m_disableZ;
    u8 m_pad2D[0xF];
};

struct pppYmDeformationMdl {
    _pppPObject m_object;
};

void SetUpIndWarp(VYmDeformationMdl*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationMdl(pppYmDeformationMdl*, _pppCtrlTable*);
void pppConstruct2YmDeformationMdl(pppYmDeformationMdl*, _pppCtrlTable*);
void pppDestructYmDeformationMdl(pppYmDeformationMdl*, _pppCtrlTable*);
void pppFrameYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, _pppCtrlTable* param_3);
void pppRenderYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONMDL_H_
