#ifndef _FFCC_PPP_YMMOVEPARABOLA_H_
#define _FFCC_PPP_YMMOVEPARABOLA_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct pppYmMoveParabolaStep {
    s32 m_graphId;
    f32 m_dataValIndex;
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_payload;
};

typedef _pppPObject pppYmMoveParabola;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMoveParabola(pppYmMoveParabola* basePtr, _pppCtrlTable* dataPtr);
void pppFrameYmMoveParabola(pppYmMoveParabola* basePtr, pppYmMoveParabolaStep* stepData, _pppCtrlTable* offsetData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMOVEPARABOLA_H_
