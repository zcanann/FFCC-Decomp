#ifndef _FFCC_PPP_YMMOVEPARABOLA_H_
#define _FFCC_PPP_YMMOVEPARABOLA_H_

#include "ffcc/partMng.h"

struct pppYmMoveParabola {
    _pppPObject m_object;
};

struct pppYmMoveParabolaWork {
    f32 m_distance;
    f32 m_velocity;
    f32 m_acceleration;
    u16 m_frame;
    u16 _pad0x0E;
    Vec m_basePosition;
};

struct pppYmMoveParabolaUnkB {
    s32 m_graphId;
    f32 m_dataValIndex;
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_payload;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMoveParabola(struct pppYmMoveParabola* basePtr, _pppCtrlTable* dataPtr);
void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkB* stepData, _pppCtrlTable* offsetData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMOVEPARABOLA_H_
