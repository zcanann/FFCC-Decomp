#ifndef _PPP_RANDDOWNINT_H_
#define _PPP_RANDDOWNINT_H_



struct _pppPObject;
struct _pppCtrlTable;
struct RandDownIntParams;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownInt(struct _pppPObject* basePtr, struct RandDownIntParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNINT_H_
