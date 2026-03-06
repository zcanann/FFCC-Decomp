#ifndef _PPP_YMCALLBACK_H_
#define _PPP_YMCALLBACK_H_

#include <dolphin/types.h>

struct pppYmCallBack {
    u8 m_pad0[0xc];
    u32 m_graphId;
};

struct pppYmCallBackUnkB {
    u32 m_unk0;
    s16 m_graphId;
    s16 m_initWOrk;
};

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
