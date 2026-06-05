#ifndef _PPP_PARHITSPHMAT_H_
#define _PPP_PARHITSPHMAT_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppParHitSphMatStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppParHitSphMat(_pppPObject* pObject, pppParHitSphMatStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_PARHITSPHMAT_H_
