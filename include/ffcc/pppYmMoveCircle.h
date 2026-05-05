#ifndef _FFCC_PPP_YMMOVECIRCLE_H_
#define _FFCC_PPP_YMMOVECIRCLE_H_

struct _pppCtrlTable;
struct _pppPObject;

struct pppYmMoveCircleStep {
    int m_graphId;
    float m_angleStep;
    float m_angleStepStep;
    float m_angleStepStepStep;
    float m_radius;
    float m_radiusStep;
    float m_radiusStepStep;
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
