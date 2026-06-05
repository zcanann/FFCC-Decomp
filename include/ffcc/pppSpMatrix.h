#ifndef _PPP_SPMATRIX_H_
#define _PPP_SPMATRIX_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppSpMatrix(_pppPObject* mtx, pppNoStep* stepData, _pppCtrlTable* data);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SPMATRIX_H_
