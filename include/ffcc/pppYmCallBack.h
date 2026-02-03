#ifndef _PPP_YMCALLBACK_H_
#define _PPP_YMCALLBACK_H_

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmCallBack(void);
void pppDestructYmCallBack(void);
void pppFrameYmCallBack(void* pppYmCallBack, void* param_2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMCALLBACK_H_
