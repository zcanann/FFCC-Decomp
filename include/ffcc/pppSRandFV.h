#ifndef _PPP_SRANDFV_H_
#define _PPP_SRANDFV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct SRandFVParams;
#ifdef __cplusplus
extern "C" {
#endif

void pppSRandFV(struct _pppPObject* basePtr, struct SRandFVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDFV_H_
