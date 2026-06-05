#ifndef _FFCC_PPPDRAWMATRIXNOROT_H_
#define _FFCC_PPPDRAWMATRIXNOROT_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawMatrixNoRot(struct _pppPObject* object, pppNoStep* stepData, struct _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWMATRIXNOROT_H_
