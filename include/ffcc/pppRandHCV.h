#ifndef _PPP_RANDHCV_H_
#define _PPP_RANDHCV_H_


struct _pppCtrlTable;
struct RandHCVParams;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandHCV(void* basePtr, struct RandHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDHCV_H_
