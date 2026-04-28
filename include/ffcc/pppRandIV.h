#ifndef _PPP_RANDIV_H_
#define _PPP_RANDIV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct PppRandIVParam2;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandIV(struct _pppPObject* basePtr, struct PppRandIVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDIV_H_
