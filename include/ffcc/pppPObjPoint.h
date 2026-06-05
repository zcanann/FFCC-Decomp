#ifndef _PPP_POBJPOINT_H_
#define _PPP_POBJPOINT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;
struct Vec;

struct pppPObjPointStep {
    s32 m_graphId;              // 0x0
    u32 m_createProgramIndex;   // 0x4
    u32 m_sourceOffset;         // 0x8
    u32 m_objectId;             // 0xc
};

#ifdef __cplusplus
extern "C" {
#endif

void pppPObjPoint(_pppPObject* pObject, pppPObjPointStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POBJPOINT_H_
