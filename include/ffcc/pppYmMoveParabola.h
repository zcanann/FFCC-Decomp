#ifndef _FFCC_PPP_YMMOVEPARABOLA_H_
#define _FFCC_PPP_YMMOVEPARABOLA_H_

#include "types.h"

struct pppYmMoveParabola {
    struct {
        s32 m_graphId;
    } field0_0x0;
};

struct pppYmMoveParabolaUnkB {
    u32 m_graphId;
    f32 m_dataValIndex;
    s32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_payload;
};

struct pppYmMoveParabolaUnkC {
    u32 _pad0x00;
    u32 _pad0x04;
    u32 _pad0x08;
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMoveParabola(struct pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkC* dataPtr);
void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkB* stepData, struct pppYmMoveParabolaUnkC* offsetData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMOVEPARABOLA_H_
