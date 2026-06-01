#ifndef _PPP_MATRIXZXY_H_
#define _PPP_MATRIXZXY_H_


#include "dolphin/types.h"
#include "ffcc/partMng.h"

struct _pppCtrlTable;
struct _pppPObject;

#ifdef __cplusplus
extern "C" {
#endif

void pppMatrixZXY(_pppPObject* target, void* unused, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MATRIXZXY_H_
