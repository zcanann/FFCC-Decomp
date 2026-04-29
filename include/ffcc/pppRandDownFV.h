#ifndef _PPP_RANDDOWNFV_H_
#define _PPP_RANDDOWNFV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct PppRandDownFVParam2;
#ifdef __cplusplus

extern "C" {
#endif

void pppRandDownFV(struct _pppPObject* basePtr, struct PppRandDownFVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNFV_H_
