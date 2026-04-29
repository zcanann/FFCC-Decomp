#ifndef _PPP_SRANDHCV_H_
#define _PPP_SRANDHCV_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppSRandHCV(struct _pppPObject* basePtr, struct SRandHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDHCV_H_
