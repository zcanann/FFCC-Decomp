#ifndef _PPP_MATRIXSCL_H_
#define _PPP_MATRIXSCL_H_


#include "dolphin/types.h"
#include "dolphin/mtx.h"

struct _pppCtrlTable;
struct _pppPObject;
struct pppNoStep;

struct MatrixSclDataOffsets {
    s32 m_translationOffset;
    s32 m_scaleOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppMatrixScl(_pppPObject* target, pppNoStep* stepData, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MATRIXSCL_H_
