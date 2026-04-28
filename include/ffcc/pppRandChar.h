#ifndef _PPP_RANDCHAR_H_
#define _PPP_RANDCHAR_H_

#ifdef __cplusplus
extern "C" {
#endif

void pppRandChar(void* basePtr, struct RandCharParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDCHAR_H_
