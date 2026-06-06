#ifndef _PPP_POBJPOINT_H_
#define _PPP_POBJPOINT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct PObjPointDataOffsets {
    s32 m_workOffset;
};

struct pppPObjPointStep {
    s32 m_graphId;
    u32 m_createProgramIndex;
    u32 m_sourceOffset;
    u32 m_objectId;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppPObjPoint(_pppPObject* pObject, pppPObjPointStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POBJPOINT_H_
