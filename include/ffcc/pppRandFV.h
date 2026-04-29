#ifndef _PPP_RANDFV_H_
#define _PPP_RANDFV_H_


struct _pppPObject;
#ifdef __cplusplus
extern "C" {
#endif

void pppRandFV(struct _pppPObject* basePtr, struct RandFVParams* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDFV_H_
