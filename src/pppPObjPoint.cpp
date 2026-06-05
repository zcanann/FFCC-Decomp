#include "global.h"
#include "ffcc/pppPObjPoint.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

struct pppPObjPointWork {
    float m_x;         // 0x0
    float m_y;         // 0x4
    float m_z;         // 0x8
    u8 m_pad[4];       // 0xc
    Vec* m_source;     // 0x10
};

struct PObjPointDataOffsets {
    s32 m_workOffset;
};

STATIC_ASSERT(offsetof(PObjPointDataOffsets, m_workOffset) == 0x0);

static inline PObjPointDataOffsets* GetPObjPointDataOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<PObjPointDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline pppPObjPointWork* GetPObjPointWork(_pppPObject* pObject, _pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<pppPObjPointWork*>(
        pObject->m_workArea + GetPObjPointDataOffsets(ctrlTable)->m_workOffset);
}

/*
 * --INFO--
 * PAL Address: 0x80060AEC
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPObjPoint(_pppPObject* pObject, pppPObjPointStep* step, _pppCtrlTable* ctrlTable)
{
    if (ppvUserStopPartF != 0) {
        return;
    }

    pppPObjPointWork* objPtr = GetPObjPointWork(pObject, ctrlTable);

    if (step->m_graphId == pObject->m_graphId) {
        Vec* source = (step->m_createProgramIndex == -1)
                          ? (Vec*)gPppDefaultValueBuffer
                          : (Vec*)(((_pppPObject*)ppvMng->m_pppPDataVals[step->m_createProgramIndex].m_pppPObjLink)->m_workArea
                                  + step->m_sourceOffset);

        objPtr->m_source = source;
    }

    objPtr->m_x = objPtr->m_source->x;
    objPtr->m_y = objPtr->m_source->y;
    objPtr->m_z = objPtr->m_source->z;
}
