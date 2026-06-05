#ifndef _FFCC_PPP_YMTRACEMOVE_H_
#define _FFCC_PPP_YMTRACEMOVE_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppYmTraceMoveStep;

typedef _pppPObject pppYmTraceMove;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, _pppCtrlTable* param_2);
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveStep* param_2, _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMTRACEMOVE_H_
