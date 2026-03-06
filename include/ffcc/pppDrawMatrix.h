#ifndef _FFCC_PPPDRAWMATRIX_H_
#define _FFCC_PPPDRAWMATRIX_H_

struct _pppPObject;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawMatrix(struct _pppPObject* object, void* stepData, struct _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWMATRIX_H_
