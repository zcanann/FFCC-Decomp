#ifndef _PPP_POINTRAP_H_
#define _PPP_POINTRAP_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct pppPointRApStep {
    u32 m_unknown0;
    float m_radius;
    float m_speedScale;
    u32 m_createProgramIndex;
    u32 m_childPosOffset;
    u32 m_unused14;
    u32 m_childVelocityOffset;
    u8 m_cooldown;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppPointRApCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable);
void pppPointRAp(_pppPObject* pObject, pppPointRApStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINTRAP_H_
