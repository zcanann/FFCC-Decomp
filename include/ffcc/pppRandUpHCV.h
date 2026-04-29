#ifndef _PPP_RANDUPHCV_H_
#define _PPP_RANDUPHCV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct RandUpHCVParams;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpHCV(struct _pppPObject* basePtr, struct RandUpHCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPHCV_H_
