#include "ffcc/pppPObjPoint.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

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
            u32 sourceOffset = step->m_sourceOffset;
            _pppPDataVal* pDataVal = pppMngStPtr->m_pppPDataVals;
            pDataVal = &pDataVal[step->m_createProgramIndex];
            vecPtr = (u8*)pDataVal->m_pppPObjLink + sourceOffset + 0x80;
        }

        objPtr->m_source = (Vec*)vecPtr;
    }

    objPtr->m_x = objPtr->m_source->x;
    objPtr->m_y = objPtr->m_source->y;
    objPtr->m_z = objPtr->m_source->z;
}
