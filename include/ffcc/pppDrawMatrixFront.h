#ifndef _FFCC_PPPDRAWMATRIXFRONT_H_
#define _FFCC_PPPDRAWMATRIXFRONT_H_

struct _pppPObject;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawMatrixFront(_pppPObject* object, void* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWMATRIXFRONT_H_
