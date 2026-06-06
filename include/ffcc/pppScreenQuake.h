#ifndef _PPP_SCREENQUAKE_H_
#define _PPP_SCREENQUAKE_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct pppScreenQuakeStep {
    s32 m_graphId;
    f32 m_dataValIndex;
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_initWOrk2;
    f32 m_stepValue2;
    f32 m_arg4;
    f32 m_initWOrk3;
    f32 m_stepValue3;
    f32 m_quakeParam0;
    f32 m_quakeParam1;
    f32 m_quakeParam2;
};

typedef _pppPObject pppScreenQuake;

struct ScreenQuakeDataOffsets {
    s32 m_workOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenQuake(pppScreenQuake *quake, _pppCtrlTable *param2);
void pppCon2ScreenQuake(pppScreenQuake *quake, _pppCtrlTable *param2);
void pppDesScreenQuake(pppScreenQuake* quake, _pppCtrlTable* param2);
void pppFrameScreenQuake(pppScreenQuake *quake, pppScreenQuakeStep *param2, _pppCtrlTable *param3);
void pppRenderScreenQuake(pppScreenQuake* quake, pppScreenQuakeStep* param2, _pppCtrlTable* param3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENQUAKE_H_
