#ifndef _PPP_MATRIXLOC_H_
#define _PPP_MATRIXLOC_H_

#include <dolphin/mtx.h>

struct _pppCtrlTable;
struct _pppPObject;

#ifdef __cplusplus
extern "C" {
#endif

void pppMatrixLoc(_pppPObject* target, void* unused, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MATRIXLOC_H_
