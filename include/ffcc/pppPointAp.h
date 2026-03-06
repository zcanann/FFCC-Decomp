#ifndef _PPP_POINTAP_H_
#define _PPP_POINTAP_H_

struct _pppPObject;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppPointApCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable);
void pppPointAp(_pppPObject* pObject, void* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINTAP_H_
