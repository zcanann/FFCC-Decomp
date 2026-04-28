#ifndef _PPP_SRANDUPCV_H_
#define _PPP_SRANDUPCV_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppSRandUpCV(struct _pppPObject* basePtr, struct SRandUpCVParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDUPCV_H_
