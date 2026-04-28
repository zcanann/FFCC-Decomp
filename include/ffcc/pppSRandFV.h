#ifndef _PPP_SRANDFV_H_
#define _PPP_SRANDFV_H_



struct _pppPObject;
struct _pppCtrlTable;
struct PppSRandFVParam2;
#ifdef __cplusplus
extern "C" {
#endif

void randfloat(float, float);
void randf(unsigned char);
void pppSRandFV(struct _pppPObject* basePtr, struct PppSRandFVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDFV_H_
