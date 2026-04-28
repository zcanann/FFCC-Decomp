#ifndef _PPP_RANDDOWNINT_H_
#define _PPP_RANDDOWNINT_H_



struct _pppPObject;
struct _pppCtrlTable;
struct PppRandDownIntParam2;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownInt(struct _pppPObject* basePtr, struct PppRandDownIntParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNINT_H_
