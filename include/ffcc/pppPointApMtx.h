#ifndef _PPP_POINTAPMTX_H_
#define _PPP_POINTAPMTX_H_

struct _pppPObject;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppPointApMtx(_pppPObject* pObject, void* step, _pppCtrlTable* ctrlTable);
void pppPointApMtxCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINTAPMTX_H_
