#ifndef _PPP_POINTRAP_H_
#define _PPP_POINTRAP_H_

struct _pppPObject;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppPointRApCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable);
void pppPointRAp(_pppPObject* pObject, void* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINTRAP_H_
