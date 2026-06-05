#ifndef _PPP_SDRAWMATRIX_H_
#define _PPP_SDRAWMATRIX_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppSDrawMatrix(struct _pppPObject* object, pppNoStep* stepData, struct _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SDRAWMATRIX_H_
