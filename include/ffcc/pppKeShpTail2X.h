#ifndef _PPP_KESHPTAIL2X_H_
#define _PPP_KESHPTAIL2X_H_

struct pppFVECTOR4;
struct _pppPObject;
struct UnkB;
struct UnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail2X(struct _pppPObject*, struct UnkB*, struct UnkC*);
void pppKeShpTail2XDraw(struct _pppPObject*, struct UnkB*, struct UnkC*);
void pppKeShpTail2XCon(void*, void*);
void pppKeShpTail2XDes(void*, void*);
void U8ToF32(pppFVECTOR4*, unsigned char*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL2X_H_
