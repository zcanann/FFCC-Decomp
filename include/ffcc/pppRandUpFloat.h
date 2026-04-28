#ifndef _PPP_RANDUPFLOAT_H_
#define _PPP_RANDUPFLOAT_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandUpFloat(struct _pppPObject* basePtr, struct RandUpFloatParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPFLOAT_H_
