#ifndef _PPP_KESHPTAIL_H_
#define _PPP_KESHPTAIL_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppKeShpTailUnkB;
struct pppKeShpTailUnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeShpTail(struct _pppPObject*, struct pppKeShpTailUnkB*, struct pppKeShpTailUnkC*);
void pppKeShpTailCon(_pppPObject* obj, _pppCtrlTable* ctrlTable);
void pppKeShpTailDraw(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KESHPTAIL_H_
