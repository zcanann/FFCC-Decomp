#ifndef _PPP_RANDDOWNHCV_H_
#define _PPP_RANDDOWNHCV_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownHCV(struct _pppPObject* basePtr, struct RandDownHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNHCV_H_
