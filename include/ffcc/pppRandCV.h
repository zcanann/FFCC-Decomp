#ifndef _PPP_RANDCV_H_
#define _PPP_RANDCV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct RandCVParams;
#ifdef __cplusplus

extern "C" {
#endif

void pppRandCV(struct _pppPObject* basePtr, struct RandCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDCV_H_
