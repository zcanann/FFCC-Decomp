#ifndef _PPP_YMDEFORMATIONSCREEN_H_
#define _PPP_YMDEFORMATIONSCREEN_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppYmDeformationScreen;

struct VYmDeformationScreen {
    float m_depth;
    s16 m_angle;
    u8 m_direction;
    u8 m_pad;
    float m_scale;
    float m_values[5];
};

struct YmDeformationScreenStep {
    int m_graphId;
    int m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    float m_arg3;
    float m_payload0;
    float m_payload1;
    float m_payload2;
    short m_payload3;
    char m_payloadBytes[0x1a];
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
