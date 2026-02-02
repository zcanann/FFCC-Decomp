#ifndef _PPP_SRANDHCV_H_
#define _PPP_SRANDHCV_H_

#ifdef __cplusplus
extern "C" {
#endif

void randshort(short, float);
void randf(unsigned char);
void pppSRandHCV(void* data1, void* data2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDHCV_H_
