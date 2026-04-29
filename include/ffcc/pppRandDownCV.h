#ifndef _PPP_RANDDOWNCV_H_
#define _PPP_RANDDOWNCV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct RandDownCVParams;
#ifdef __cplusplus

extern "C" {
#endif

void pppRandDownCV(struct _pppPObject* basePtr, struct RandDownCVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNCV_H_
