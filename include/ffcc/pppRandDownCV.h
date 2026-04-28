#ifndef _PPP_RANDDOWNCV_H_
#define _PPP_RANDDOWNCV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct PppRandDownCVParam2;
#ifdef __cplusplus
char randchar(char, float);

extern "C" {
#endif

void pppRandDownCV(struct _pppPObject* basePtr, struct PppRandDownCVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNCV_H_
