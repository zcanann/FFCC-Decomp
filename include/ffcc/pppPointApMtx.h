#ifndef _PPP_POINTAPMTX_H_
#define _PPP_POINTAPMTX_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct pppPointApMtxStep {
    u32 m_unknown0;
    u32 m_createProgramIndex;
    u32 m_childMatrixOffset;
    u8 m_cooldown;
    u8 m_useWorldMatrix;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppPointApMtx(_pppPObject* pObject, pppPointApMtxStep* step, _pppCtrlTable* ctrlTable);
void pppPointApMtxCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINTAPMTX_H_
