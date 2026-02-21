#ifndef _FFCC_PPP_YMMOVEPARABOLA_H_
#define _FFCC_PPP_YMMOVEPARABOLA_H_

#include "types.h"

struct pppYmMoveParabola {
    char m_padding[0xC];
    s32 m_graphId;
};

struct UnkB {
    u32 m_graphId;
    u32 _pad0x04;
    u32 _pad0x08;
    f32 m_stepValue;
    s32 m_arg3;
    void* m_payload;
    s32 m_dataValIndex;
    s32 m_initWOrk;
};

struct UnkC {
    u32 _pad0x00;
    u32 _pad0x04;
    u32 _pad0x08;
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
