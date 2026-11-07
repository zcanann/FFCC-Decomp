#ifndef _PPP_SCALELOOPAUTO_H_
#define _PPP_SCALELOOPAUTO_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct pppScaleLoopAutoStep {
    s32 m_index;
    u8 _pad0x04[4];
    f32 m_addScale[3];
    u8 _pad0x14[4];
    f32 m_amplitude;
    u8 m_stepCount;
    s8 m_countA;
    s8 m_countB;
    u8 _pad0x1f;
    f32 m_scale;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppScaleLoopAuto(_pppPObject* arg1, pppScaleLoopAutoStep* arg2, _pppCtrlTable* arg3);
void pppScaleLoopAutoCon(_pppPObject* arg1, _pppCtrlTable* arg2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCALELOOPAUTO_H_
