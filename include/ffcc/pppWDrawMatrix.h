#ifndef _PPP_WDRAWMATRIX_H_
#define _PPP_WDRAWMATRIX_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppWDrawMatrix(_pppPObject* object, pppNoStep* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_WDRAWMATRIX_H_
