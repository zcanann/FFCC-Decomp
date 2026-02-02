#ifndef _PPP_SRANDUPCV_H_
#define _PPP_SRANDUPCV_H_

void randchar(char, float);
void randf(unsigned char);

#ifdef __cplusplus
extern "C" {
#endif
void pppSRandUpCV(void* param1, void* param2);
#ifdef __cplusplus
}
#endif

#endif // _PPP_SRANDUPCV_H_
