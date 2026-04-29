#ifndef _PPP_SRANDDOWNHCV_H_
#define _PPP_SRANDDOWNHCV_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppSRandDownHCV(struct _pppPObject* basePtr, struct SRandDownHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDDOWNHCV_H_
