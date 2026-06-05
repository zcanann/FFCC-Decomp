#ifndef _PPP_SRANDUPHCV_H_
#define _PPP_SRANDUPHCV_H_


struct _pppPObject;
struct _pppCtrlTable;
struct SRandUpHCVParams;
#ifdef __cplusplus
extern "C" {
#endif

void pppSRandUpHCV(struct _pppPObject* basePtr, struct SRandUpHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDUPHCV_H_
