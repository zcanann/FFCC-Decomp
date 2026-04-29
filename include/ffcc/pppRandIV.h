#ifndef _PPP_RANDIV_H_
#define _PPP_RANDIV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct RandIVParams;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandIV(struct _pppPObject* basePtr, struct RandIVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDIV_H_
