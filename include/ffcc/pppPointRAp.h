#ifndef _PPP_POINTRAP_H_
#define _PPP_POINTRAP_H_

struct _pppMngSt;
struct _pppPDataVal;

#ifdef __cplusplus
extern "C" {
#endif

void pppPointRApCon(_pppMngSt* mngSt, _pppPDataVal* dataVal);
void pppPointRAp(_pppMngSt* mngSt, _pppPDataVal* dataVal);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINTRAP_H_
