#ifndef _PPP_RANDHCV_H_
#define _PPP_RANDHCV_H_

#ifdef __cplusplus
short randshort(short, float);

extern "C" {
#endif

void pppRandHCV(void*, void*, void*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDHCV_H_
