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
    pppPObjPointWork* objPtr = (pppPObjPointWork*)((u8*)pObject + objOffset + 0x80);

    if (step->m_graphId == pObject->m_graphId) {
        u8* vecPtr;

        if (step->m_createProgramIndex == -1) {
            vecPtr = gPppDefaultValueBuffer;
        } else {
            u8* data = step->m_sourceObject;
            _pppPDataVal* pDataVal = pppMngStPtr->m_pppPDataVals;
            pDataVal = &pDataVal[step->m_createProgramIndex];
            s32 vecOffset = pDataVal->m_nextSpawnTime;
            vecPtr = data + 0x80;
            vecPtr += vecOffset;
        }

        objPtr->m_source = vecPtr;
    }

    objPtr->m_x = ((f32*)objPtr->m_source)[0];
    objPtr->m_y = ((f32*)objPtr->m_source)[1];
    objPtr->m_z = ((f32*)objPtr->m_source)[2];
}
