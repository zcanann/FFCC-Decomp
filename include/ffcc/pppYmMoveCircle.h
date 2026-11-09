#ifndef _FFCC_PPP_YMMOVECIRCLE_H_
#define _FFCC_PPP_YMMOVECIRCLE_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct pppYmMoveCircleStep {
    s32 m_graphId;
    f32 m_angleStep;
    f32 m_angleStepStep;
    f32 m_angleStepStepStep;
    f32 m_radius;
    f32 m_radiusStep;
    f32 m_radiusStepStep;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMoveCircle(struct _pppPObject* basePtr, struct _pppCtrlTable* offsetData);
void pppFrameYmMoveCircle(struct _pppPObject* basePtr, struct pppYmMoveCircleStep* stepData, struct _pppCtrlTable* offsetData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMOVECIRCLE_H_
