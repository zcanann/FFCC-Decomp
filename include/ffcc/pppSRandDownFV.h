#ifndef _PPP_SRANDDOWNFV_H_
#define _PPP_SRANDDOWNFV_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void randfloat(float, float);
void randf(unsigned char);
void pppSRandDownFV(struct _pppPObject* basePtr, struct PppSRandDownFVParam2* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDDOWNFV_H_
