#ifndef _PPP_POBJPOINT_H_
#define _PPP_POBJPOINT_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppPObjPointStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppPObjPoint(_pppPObject* pObject, pppPObjPointStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POBJPOINT_H_
