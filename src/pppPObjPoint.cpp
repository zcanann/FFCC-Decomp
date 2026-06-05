#include "ffcc/pppPObjPoint.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

struct pppPObjPointStep {
    s32 m_graphId;              // 0x0
    u32 m_createProgramIndex;   // 0x4
    u32 m_sourceOffset;         // 0x8
    u32 m_objectId;             // 0xc
};

struct pppPObjPointWork {
    float m_x;         // 0x0
    float m_y;         // 0x4
    float m_z;         // 0x8
    u8 m_pad[4];       // 0xc
    Vec* m_source;     // 0x10
};

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

    s32 objOffset = ctrlTable->m_serializedDataOffsets[0];
    pppPObjPointWork* objPtr = (pppPObjPointWork*)(pObject->m_workArea + objOffset);

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
