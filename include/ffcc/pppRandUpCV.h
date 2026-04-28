#ifndef _PPP_RANDUPCV_H_
#define _PPP_RANDUPCV_H_


struct _pppPObject;
#ifdef __cplusplus
char randchar(char, float);

extern "C" {
#endif

void pppRandUpCV(struct _pppPObject* basePtr, struct RandUpCVParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDUPCV_H_
