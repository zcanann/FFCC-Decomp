#ifndef _FFCC_PPPACCELE_H_
#define _FFCC_PPPACCELE_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct PppAcceleDataOffsets {
    s32 m_valueOffset;
    s32 m_accelOffset;
};

struct pppAcceleStep {
    s32 m_graphId;
    s32 m_field_04;
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppAccele(_pppPObject* obj, pppAcceleStep* param_2, _pppCtrlTable* param_3);
void pppAcceleCon(_pppPObject* obj, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif
