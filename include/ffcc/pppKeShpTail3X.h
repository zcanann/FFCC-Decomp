#ifndef _PPP_KESHPTAIL3X_H_
#define _PPP_KESHPTAIL3X_H_

struct pppFVECTOR4;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail3X(void);
void pppKeShpTail3XDraw(void);
void pppKeShpTail3XCon(void);
void pppKeShpTail3XDes(void);
void S4ToF32(pppFVECTOR4*, short*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL3X_H_
