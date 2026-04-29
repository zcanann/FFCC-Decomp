#ifndef _PPP_SRANDUPFV_H_
#define _PPP_SRANDUPFV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct SRandUpFVParams;
#ifdef __cplusplus
extern "C" {
#endif

void pppSRandUpFV(struct _pppPObject* basePtr, struct SRandUpFVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDUPFV_H_
