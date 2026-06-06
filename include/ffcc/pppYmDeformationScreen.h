#ifndef _PPP_YMDEFORMATIONSCREEN_H_
#define _PPP_YMDEFORMATIONSCREEN_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppYmDeformationScreen;

struct VYmDeformationScreen {
    f32 m_depth;
    s16 m_angle;
    u8 m_direction;
    u8 m_pad;
    f32 m_scale;
    f32 m_values[5];
};

struct YmDeformationScreenDataOffsets {
    s32 _unused0;
    s32 _unused1;
    s32 m_workOffset;
};

struct YmDeformationScreenStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_payload0;
    f32 m_payload1;
    f32 m_payload2;
    s16 m_payload3;
    s8 m_payloadBytes[0x1a];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationScreen(pppYmDeformationScreen*, _pppCtrlTable*);
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen*, _pppCtrlTable*);
void pppDestructYmDeformationScreen(pppYmDeformationScreen*, _pppCtrlTable*);
void pppFrameYmDeformationScreen(pppYmDeformationScreen*, YmDeformationScreenStep*, _pppCtrlTable*);
void pppRenderYmDeformationScreen(pppYmDeformationScreen*, YmDeformationScreenStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONSCREEN_H_
