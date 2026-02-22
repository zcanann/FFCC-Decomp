#ifndef _FFCC_PPP_YMMOVECIRCLE_H_
#define _FFCC_PPP_YMMOVECIRCLE_H_

struct pppYmMoveCircle {
    char m_padding[0xC];
    int m_graphId;
};

struct pppYmMoveCircleStep {
    int m_graphId;
    float m_angleStep;
    float m_angleStepStep;
    float m_angleStepStepStep;
    float m_radius;
    float m_radiusStep;
    float m_radiusStepStep;
};

struct pppYmMoveCircleOffsets {
    int m_pad0;
    int m_pad1;
    int m_pad2;
    int* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMoveCircle(struct pppYmMoveCircle* basePtr, struct pppYmMoveCircleOffsets* offsetData);
void pppFrameYmMoveCircle(struct pppYmMoveCircle* basePtr, struct pppYmMoveCircleStep* stepData, struct pppYmMoveCircleOffsets* offsetData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMOVECIRCLE_H_
