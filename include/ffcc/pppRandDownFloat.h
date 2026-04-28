#ifndef _PPP_RANDDOWNFLOAT_H_
#define _PPP_RANDDOWNFLOAT_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandDownFloat(struct _pppPObject* basePtr, struct RandDownFloatParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDDOWNFLOAT_H_
