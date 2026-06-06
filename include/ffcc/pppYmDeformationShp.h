#ifndef _PPP_YMDEFORMATIONSHP_H_
#define _PPP_YMDEFORMATIONSHP_H_

#include "ffcc/pppVec.h"

#include <dolphin/gx.h>
#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppYmDeformationShp;

struct VYmDeformationShp {
    GXTexObj* m_backBuffer;
    int m_pad0;
    int m_pad1;
    s16 m_angle;
    u8 m_direction;
    u8 m_pad2;
    float m_scale;
    float m_values[5];
};

struct pppYmDeformationShpGraphArgs {
    f32 m_valueAdd;
    f32 m_velocityAdd;
    f32 m_accelerationAdd;
};

struct pppYmDeformationShpStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_size;
    u8 m_pad09[3];
    union {
        f32 m_payload[6];
        struct Payload {
            pppYmDeformationShpGraphArgs m_scale;
            pppYmDeformationShpGraphArgs m_angle;
        } m_deformation;
    };
    s16 m_angleLimit;
    s8 m_splitMode;
    u8 m_splitSize;
    u8 m_orientation;
    u8 m_pad29[3];
    f32 m_drawZ;
    u8 m_pad30;
    u8 m_alpha;
    u8 m_pad32[0xA];
};

struct YmDeformationShpDataOffsets {
    s32 _unused0;
    s32 m_colorInfoOffset;
    s32 m_stateOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationShp(pppYmDeformationShp*, _pppCtrlTable*);
void pppConstruct2YmDeformationShp(pppYmDeformationShp*, _pppCtrlTable*);
void pppDestructYmDeformationShp(pppYmDeformationShp*, _pppCtrlTable*);
void pppFrameYmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpStep*, _pppCtrlTable*);
void pppRenderYmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONSHP_H_
