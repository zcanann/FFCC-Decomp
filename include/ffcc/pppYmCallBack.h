#ifndef _PPP_YMCALLBACK_H_
#define _PPP_YMCALLBACK_H_

struct pppYmCallBack;
struct pppYmCallBackUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmCallBack(pppYmCallBack* pppYmCallBack, void* param_2);
void pppDestructYmCallBack(pppYmCallBack* pppYmCallBack, void* param_2);
void pppFrameYmCallBack(pppYmCallBack* pppYmCallBack, pppYmCallBackUnkB* param_2, void* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMCALLBACK_H_
