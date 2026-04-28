#ifndef _PPP_RANDDOWNIV_H_
#define _PPP_RANDDOWNIV_H_

#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownIV(void* basePtr, struct PppRandDownIVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNIV_H_
