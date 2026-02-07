#ifndef _PPP_KELNS_H_
#define _PPP_KELNS_H_

#ifdef __cplusplus
extern "C" {
#endif

void pppKeLnsLpCon(void* basePtr, void* dataPtr);
void pppKeLnsLpCon2(void* basePtr, void* dataPtr);
void pppKeLnsLpDraw(void);
void pppKeLnsFlsCon(void);
void pppKeLnsFlsDraw(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KELNS_H_
