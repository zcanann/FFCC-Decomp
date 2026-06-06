#ifndef _PPP_PARHITSPHMAT_H_
#define _PPP_PARHITSPHMAT_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct ParHitSphMatDataOffsets {
    s32 m_unusedOffset;
    s32 m_positionOffset;
};

struct pppParHitSphMatStep {
    s32 m_unused0;
    f32 m_height;
    f32 m_radiusScale;
    u8 m_useWorkPosition;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppParHitSphMat(_pppPObject* pObject, pppParHitSphMatStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_PARHITSPHMAT_H_
