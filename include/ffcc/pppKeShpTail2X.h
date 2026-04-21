#ifndef _PPP_KESHPTAIL2X_H_
#define _PPP_KESHPTAIL2X_H_

struct _pppPObject;
struct pppKeShpTail2XUnkB;
struct pppKeShpTail2XUnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail2X(struct _pppPObject*, struct pppKeShpTail2XUnkB*, struct pppKeShpTail2XUnkC*);
void pppKeShpTail2XDraw(struct _pppPObject*, struct pppKeShpTail2XUnkB*, struct pppKeShpTail2XUnkC*);
void pppKeShpTail2XCon(void*, void*);
void pppKeShpTail2XDes(void*, void*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL2X_H_
