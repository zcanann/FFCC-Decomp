#ifndef _FFCC_PPP_YMTRACEMOVE_H_
#define _FFCC_PPP_YMTRACEMOVE_H_

#include "ffcc/partMng.h"

#include <dolphin/types.h>

struct pppYmTraceMove {
    _pppPObject m_object;
};

struct pppYmTraceMoveStep {
    s32 m_graphId;
    f32 m_dataValIndex;
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_payload;
};

struct pppYmTraceMoveCtrl {
    char pad[0x0c];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveCtrl* param_2);
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveStep* param_2, pppYmTraceMoveCtrl* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACEMOVE_H_

