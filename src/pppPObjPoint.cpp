#include "ffcc/pppPObjPoint.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

struct PObjPointDataVal {
    void* m_programSetDef;
    s32 m_sourceOffset;
    u8 _pad8[0x8];
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
    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 objOffset = ctrlTable->m_serializedDataOffsets[0];
    pppPObjPointWork* objPtr = (pppPObjPointWork*)(pObject->m_workArea + objOffset);

    if (step->m_graphId == pObject->m_graphId) {
        u8* vecPtr;

        if (step->m_createProgramIndex == -1) {
            vecPtr = gPppDefaultValueBuffer;
        } else {
            u8* data = step->m_sourceObject;
            PObjPointDataVal* pDataVal = (PObjPointDataVal*)pppMngStPtr->m_pppPDataVals;
            pDataVal = &pDataVal[step->m_createProgramIndex];
            s32 vecOffset = pDataVal->m_sourceOffset;
            vecPtr = data + 0x80;
            vecPtr += vecOffset;
        }

        objPtr->m_source = (Vec*)vecPtr;
    }

    objPtr->m_x = objPtr->m_source->x;
    objPtr->m_y = objPtr->m_source->y;
    objPtr->m_z = objPtr->m_source->z;
}
