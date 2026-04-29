#ifndef _PPP_RANDUPFV_H_
#define _PPP_RANDUPFV_H_


struct _pppPObject;
struct _pppCtrlTable;
struct RandUpFVParams;

#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpFV(struct _pppPObject* basePtr, struct RandUpFVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPFV_H_
