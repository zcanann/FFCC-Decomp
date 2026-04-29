#ifndef _PPP_RANDDOWNFV_H_
#define _PPP_RANDDOWNFV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct RandDownFVParams;
#ifdef __cplusplus

extern "C" {
#endif

void pppRandDownFV(struct _pppPObject* basePtr, struct RandDownFVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNFV_H_
