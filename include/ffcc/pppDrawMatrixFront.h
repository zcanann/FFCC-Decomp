#ifndef _FFCC_PPPDRAWMATRIXFRONT_H_
#define _FFCC_PPPDRAWMATRIXFRONT_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawMatrixFront(_pppPObject* object, pppNoStep* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWMATRIXFRONT_H_
