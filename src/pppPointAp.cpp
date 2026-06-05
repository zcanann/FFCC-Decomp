#include "ffcc/pppPointAp.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>
#include <dolphin/types.h>

/*
 * --INFO--
 * PAL Address: 0x80060c04
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointAp(_pppPObject* pObject, pppPointApStep* step, _pppCtrlTable* ctrlTable)
{
    pppPointApOffsets* data = (pppPointApOffsets*)ctrlTable->m_serializedDataOffsets;
    u32 srcOffset = data->m_srcOffset;
    u32 targetOffset = data->m_targetOffset;
    Vec* src = (Vec*)(pObject->m_workArea + srcOffset);
    u8* target = pObject->m_workArea + targetOffset;

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (target[1] == 0) {
        if ((step->m_createProgramIndex + 0x10000) == 0xFFFF) {
            return;
        }

        _pppPObject* obj;
        _pppPDataVal* objData = ppvMng->m_pppPDataVals + step->m_createProgramIndex;

        if (objData == 0) {
            obj = 0;
        } else {
            obj = pppCreatePObject(ppvMng, objData);
            obj->m_link.m_previous = &pObject->m_link;
        }

        Vec* dst = (Vec*)(obj->m_workArea + step->m_childDstOffset);
        if (step->m_useWorldMatrix == 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            PSMTXMultVec(ppvMng->m_matrix.value, src, dst);
        }

        target[1] = step->m_cooldown;
    }

    target[1]--;
}

/*
 * --INFO--
 * PAL Address: 0x80060d08
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointApCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable)
{
    pppPointApOffsets* data = (pppPointApOffsets*)ctrlTable->m_serializedDataOffsets;
    u8* target = pObject->m_workArea + data->m_targetOffset;
    target[1] = 0;
}
