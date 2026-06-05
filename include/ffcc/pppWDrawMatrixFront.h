#ifndef _PPP_WDRAWMATRIXFRONT_H_
#define _PPP_WDRAWMATRIXFRONT_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppWDrawMatrixFront(struct _pppPObject* object, pppNoStep* stepData, struct _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_WDRAWMATRIXFRONT_H_
