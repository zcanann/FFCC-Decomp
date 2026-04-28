#ifndef _PPP_RANDDOWNCHAR_H_
#define _PPP_RANDDOWNCHAR_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownChar(struct _pppPObject* basePtr, struct PppRandDownCharParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNCHAR_H_
