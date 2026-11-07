#ifndef _PPP_MATRIXYZX_H_
#define _PPP_MATRIXYZX_H_


#include "dolphin/types.h"

struct _pppCtrlTable;
struct _pppPObject;
struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppMatrixYZX(_pppPObject* target, pppNoStep* stepData, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MATRIXYZX_H_
