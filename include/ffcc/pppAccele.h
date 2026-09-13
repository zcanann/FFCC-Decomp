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
    f32 m_x;
    f32 m_y;
    f32 m_z;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppAccele(_pppPObject* obj, pppAcceleStep* step, _pppCtrlTable* ctrl);
void pppAcceleCon(_pppPObject* obj, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif
