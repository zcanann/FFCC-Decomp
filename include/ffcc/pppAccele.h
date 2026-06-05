#ifndef _FFCC_PPPACCELE_H_
#define _FFCC_PPPACCELE_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppAcceleUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppAccele(_pppPObject* obj, pppAcceleUnkB* param_2, _pppCtrlTable* param_3);
void pppAcceleCon(_pppPObject* obj, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif
