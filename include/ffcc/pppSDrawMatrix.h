#ifndef _PPP_SDRAWMATRIX_H_
#define _PPP_SDRAWMATRIX_H_

struct _pppPObject;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppSDrawMatrix(struct _pppPObject* object, void* stepData, struct _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SDRAWMATRIX_H_
