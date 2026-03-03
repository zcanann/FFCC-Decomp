#ifndef _PPP_KESHPTAIL_H_
#define _PPP_KESHPTAIL_H_

struct _pppPObject;
struct UnkB;
struct UnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail(struct _pppPObject*, struct UnkB*, struct UnkC*);
void pppKeShpTailCon(void* r3, void* r4);
void pppKeShpTailDraw(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL_H_
