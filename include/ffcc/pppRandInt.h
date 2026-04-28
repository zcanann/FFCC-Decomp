#ifndef _PPP_RANDINT_H_
#define _PPP_RANDINT_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandInt(struct _pppPObject* basePtr, struct PppRandIntParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDINT_H_
