#ifndef _PPP_KEDMAT_H_
#define _PPP_KEDMAT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;
struct pppNoStep;

struct KeDMatDataOffsets {
    s32 _unused0;
    s32 m_targetMatrixOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppKeDMatDraw(_pppPObject* pObject, pppNoStep* data, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KEDMAT_H_
