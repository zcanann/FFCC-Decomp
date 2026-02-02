#ifndef _FFCC_PPP_YMMOVEPARABOLA_H_
#define _FFCC_PPP_YMMOVEPARABOLA_H_

#include "types.h"

struct pppYmMoveParabola {
    struct {
        s32 m_graphId;
    } field0_0x0;
};

struct UnkB {
    u32 m_graphId;
    f32 m_stepValue;
    u32 m_arg3;
    u8* m_payload;
    u32 m_dataValIndex;
    u16 m_initWOrk;
};

struct UnkC {
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMoveParabola(struct pppYmMoveParabola* basePtr, struct UnkC* dataPtr);
void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct UnkB* stepData, struct UnkC* offsetData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMOVEPARABOLA_H_
