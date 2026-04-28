#ifndef _PPP_RANDUPHCV_H_
#define _PPP_RANDUPHCV_H_


struct _pppCtrlTable;
struct PppRandUpHCVParam2;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpHCV(void* basePtr, struct PppRandUpHCVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPHCV_H_
