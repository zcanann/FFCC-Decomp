#ifndef _PPP_SRANDCV_H_
#define _PPP_SRANDCV_H_


struct _pppPObject;
#ifdef __cplusplus
void randchar(char, float);
void randf(unsigned char);

extern "C" {
#endif

void pppSRandCV(struct _pppPObject* basePtr, struct SRandCVParam* in, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDCV_H_
