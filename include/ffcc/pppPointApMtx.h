#ifndef _PPP_POINTAPMTX_H_
#define _PPP_POINTAPMTX_H_

struct _pppPObject;
struct _pppMngSt;
struct _pppPDataVal;
struct Vec;

#ifdef __cplusplus
extern "C" {
#endif

void pppPointApMtxCon(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal);
void pppPointApMtx(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal, _pppMngSt* pppMngSt);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINTAPMTX_H_
