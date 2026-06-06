#ifndef _FFCC_PPPANGACCELE_H_
#define _FFCC_PPPANGACCELE_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct PppAngAcceleDataOffsets {
    s32 m_velocityOffset;
    s32 m_accelOffset;
};

struct pppAngAcceleStep {
    s32 m_graphId;
    s32 m_field_04;
    s32 m_x;
    s32 m_y;
    s32 m_z;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppAngAccele(_pppPObject* obj, pppAngAcceleStep* param_2, _pppCtrlTable* param_3);
void pppAngAcceleCon(_pppPObject* obj, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif
