#ifndef _PPP_SRANDDOWNCV_H_
#define _PPP_SRANDDOWNCV_H_

#ifdef __cplusplus
extern "C" {
#endif

struct SRandDownCVParams;
void pppSRandDownCV(struct _pppPObject* basePtr, struct SRandDownCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDDOWNCV_H_
