#ifndef _PPP_RANDSHORT_H_
#define _PPP_RANDSHORT_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandShort(struct _pppPObject* basePtr, struct PppRandShortParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDSHORT_H_
