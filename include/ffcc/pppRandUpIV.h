#ifndef _PPP_RANDUPIV_H_
#define _PPP_RANDUPIV_H_


struct _pppCtrlTable;
struct PppRandUpIVParam2;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpIV(void* basePtr, struct PppRandUpIVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPIV_H_
