#ifndef _PPP_SRANDUPFV_H_
#define _PPP_SRANDUPFV_H_


struct _pppCtrlTable;
struct PppSRandUpFVParam2;
#ifdef __cplusplus
extern "C" {
#endif

void randfloat(float, float);
void randf(unsigned char);
void pppSRandUpFV(void* basePtr, struct PppSRandUpFVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDUPFV_H_
