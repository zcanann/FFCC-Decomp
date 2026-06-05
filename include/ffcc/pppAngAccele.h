#ifndef _FFCC_PPPANGACCELE_H_
#define _FFCC_PPPANGACCELE_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppAngAcceleUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppAngAccele(_pppPObject* obj, pppAngAcceleUnkB* param_2, _pppCtrlTable* param_3);
void pppAngAcceleCon(_pppPObject* obj, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif
