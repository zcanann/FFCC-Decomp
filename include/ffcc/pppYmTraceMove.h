#ifndef _FFCC_PPP_YMTRACEMOVE_H_
#define _FFCC_PPP_YMTRACEMOVE_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct YmTraceMoveDataOffsets {
    s32 m_workOffset;
};

struct pppYmTraceMoveStep {
    s32 m_graphId;
    f32 m_dataValIndex;
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_payload;
};

typedef _pppPObject pppYmTraceMove;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, _pppCtrlTable* ctrl);
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveStep* step, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACEMOVE_H_
