#ifndef _PPP_MATRIXYXZ_H_
#define _PPP_MATRIXYXZ_H_


#include "dolphin/types.h"
#include "ffcc/partMng.h"

struct _pppCtrlTable;
struct _pppPObject;
struct pppNoStep;

struct MatrixYXZDataOffsets {
    s32 m_translationOffset;
    s32 m_angleOffset;
    s32 m_scaleOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppMatrixYXZ(_pppPObject* target, pppNoStep* stepData, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MATRIXYXZ_H_
