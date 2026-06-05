#ifndef _PPP_RANDUPSHORT_H_
#define _PPP_RANDUPSHORT_H_


struct _pppPObject;
struct _pppCtrlTable;
struct RandUpShortParam;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpShort(struct _pppPObject* basePtr, struct RandUpShortParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPSHORT_H_
