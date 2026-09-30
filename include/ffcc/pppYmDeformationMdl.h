#ifndef _PPP_YMDEFORMATIONMDL_H_
#define _PPP_YMDEFORMATIONMDL_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppYmDeformationMdl;

struct VYmDeformationMdl {
    s16 m_angle;
    u8 m_direction;
    u8 m_pad;
    float m_scale;
    float m_values[5];
};

struct pppYmDeformationMdlStep {
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

struct YmDeformationMdlDataOffsets {
    s32 _unused0;
    s32 m_colorInfoOffset;
    s32 m_stateOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationMdl(pppYmDeformationMdl*, _pppCtrlTable*);
void pppConstruct2YmDeformationMdl(pppYmDeformationMdl*, _pppCtrlTable*);
void pppDestructYmDeformationMdl(pppYmDeformationMdl*, _pppCtrlTable*);
void pppFrameYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlStep* step, _pppCtrlTable* ctrl);
void pppRenderYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlStep* step, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONMDL_H_
