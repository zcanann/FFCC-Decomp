#ifndef _FFCC_PPP_YMTRACEMOVE_H_
#define _FFCC_PPP_YMTRACEMOVE_H_

#include <dolphin/types.h>

struct pppYmTraceMove {
    union {
        void* ptr;
        s32 m_graphId;
    } field0_0x0;
};

struct UnkB {
    s32 m_graphId;
    f32 m_dataValIndex;
    s16 m_initWOrk;
    f32 m_stepValue;
    s16 m_arg3;
    u16 pad;
    f32* m_payload;
};

struct UnkC {
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, UnkC* param_2);
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, UnkB* param_2, UnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACEMOVE_H_
