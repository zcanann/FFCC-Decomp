#ifndef _PPP_POINTAP_H_
#define _PPP_POINTAP_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct pppPointApStep {
    u32 m_unknown0;
    u32 m_createProgramIndex;
    u32 m_childDstOffset;
    u8 m_cooldown;
    u8 m_useWorldMatrix;
};

struct pppPointApOffsets {
    u32 m_srcOffset;
    u32 m_targetOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppPointApCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable);
void pppPointAp(_pppPObject* pObject, pppPointApStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINTAP_H_
