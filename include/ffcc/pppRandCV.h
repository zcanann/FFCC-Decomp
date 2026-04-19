#ifndef _PPP_RANDCV_H_
#define _PPP_RANDCV_H_

#ifdef __cplusplus
char randchar(char, float);

extern "C" {
#endif

void pppRandCV(void*, void*, void*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RANDCV_H_
