#ifndef _PPP_YMCALLBACK_H_
#define _PPP_YMCALLBACK_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppCtrlTable pppYmCallBackCtrl;
typedef _pppPObject pppYmCallBack;

struct pppYmCallBackStep {
    u32 m_unk0;
    s16 m_graphId;
    s16 m_initWOrk;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmCallBack(pppYmCallBack* pppYmCallBack, pppYmCallBackCtrl* param_2);
void pppDestructYmCallBack(pppYmCallBack* pppYmCallBack, pppYmCallBackCtrl* param_2);
void pppFrameYmCallBack(pppYmCallBack* pppYmCallBack, pppYmCallBackStep* param_2, pppYmCallBackCtrl* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMCALLBACK_H_
