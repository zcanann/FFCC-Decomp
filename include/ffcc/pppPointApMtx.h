#ifndef _PPP_POINTAPMTX_H_
#define _PPP_POINTAPMTX_H_

struct _pppPObject;
struct _pppMngSt;
struct _pppPDataVal;
struct Vec;

void pppPointApMtxCon(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal);
void pppPointApMtx(_pppPObject* pppPObject, _pppPDataVal* pppPDataVal, _pppMngSt* pppMngSt);

#endif // _PPP_POINTAPMTX_H_
