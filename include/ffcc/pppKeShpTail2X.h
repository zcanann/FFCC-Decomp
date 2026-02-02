#ifndef _PPP_KESHPTAIL2X_H_
#define _PPP_KESHPTAIL2X_H_

struct pppFVECTOR4;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail2X(void);
void pppKeShpTail2XDraw(void);
void pppKeShpTail2XCon(void);
void pppKeShpTail2XDes(void);
void U8ToF32(pppFVECTOR4*, unsigned char*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL2X_H_
