#ifndef _PPP_SCREENQUAKE_H_
#define _PPP_SCREENQUAKE_H_

#include "ffcc/partMng.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    _pppPObject m_object;
} pppScreenQuake;

typedef struct {
    int m_graphId;
    float m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    float m_arg3;
    float m_initWOrk2;
    float m_stepValue2;
    float m_arg4;
    float m_initWOrk3;
    float m_stepValue3;
    float m_quakeParam0;
    float m_quakeParam1;
    float m_quakeParam2;
} pppScreenQuakeStep;

typedef struct {
    int m_unk0;
    int m_unk4;
    int m_unk8;
    int *m_serializedDataOffsets;
} pppScreenQuakeCtrl;

void pppConScreenQuake(pppScreenQuake *quake, pppScreenQuakeCtrl *param2);
void pppCon2ScreenQuake(pppScreenQuake *quake, pppScreenQuakeCtrl *param2);
void pppDesScreenQuake(pppScreenQuake* quake, pppScreenQuakeCtrl* param2);
void pppFrameScreenQuake(pppScreenQuake *quake, pppScreenQuakeStep *param2, pppScreenQuakeCtrl *param3);
void pppRenderScreenQuake(pppScreenQuake* quake, pppScreenQuakeStep* param2, pppScreenQuakeCtrl* param3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENQUAKE_H_

