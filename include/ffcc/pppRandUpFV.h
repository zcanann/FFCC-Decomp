#ifndef _PPP_RANDUPFV_H_
#define _PPP_RANDUPFV_H_


struct _pppPObject;
struct _pppCtrlTable;
struct PppRandUpFVParam2;

#ifdef __cplusplus
extern "C" {
#endif

void randf(float, float);
void pppRandUpFV(struct _pppPObject* basePtr, struct PppRandUpFVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPFV_H_
