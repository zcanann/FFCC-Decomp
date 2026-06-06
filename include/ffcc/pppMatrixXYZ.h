#ifndef _PPP_MATRIXXYZ_H_
#define _PPP_MATRIXXYZ_H_


#include "dolphin/types.h"
#include "ffcc/partMng.h"

struct _pppCtrlTable;
struct _pppPObject;
struct pppNoStep;

struct MatrixXYZDataOffsets {
    s32 m_translationOffset;
    s32 m_angleOffset;
    s32 m_scaleOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppMatrixXYZ(_pppPObject* target, pppNoStep* stepData, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MATRIXXYZ_H_
