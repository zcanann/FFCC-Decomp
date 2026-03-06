#include "ffcc/pppPointAp.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct _pppPointApOffsets {
    u32 srcOffset;
    u32 targetOffset;
};

struct _pppPointApStep {
    u32 m_unknown0;
    u32 m_createProgramIndex;
    u32 m_childDstOffset;
    u8 m_cooldown;
    u8 m_useWorldMatrix;
};

extern int lbl_8032ED70;
extern u8* lbl_8032ED50;

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
    _pppPointApOffsets* data = (_pppPointApOffsets*)ctrlTable->m_serializedDef;
    u8* target = (u8*)pObject + data->targetOffset;
    target[0x81] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80060c04
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointAp(_pppPObject* pObject, void* step, _pppCtrlTable* ctrlTable)
{
    u32* offsets = (u32*)ctrlTable->m_serializedDef;
    _pppPointApStep* payload = (_pppPointApStep*)step;
    Vec* source = (Vec*)((u8*)pObject + offsets[0] + 0x80);
    u8* target = (u8*)pObject + offsets[1] + 0x80;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (target[1] == 0) {
        u32 objId = payload->m_createProgramIndex;
        if ((objId + 0x10000) != 0xFFFF) {
            _pppPDataVal* objData = (_pppPDataVal*)(*(u32*)((u8*)lbl_8032ED50 + 0xD4) + (objId << 4));
            _pppPObject* obj;

            if (objData == 0) {
                obj = 0;
            } else {
                obj = pppCreatePObject((_pppMngSt*)lbl_8032ED50, objData);
            }

            *(_pppPObject**)((u8*)obj + 4) = pObject;

            Vec* dst = (Vec*)((u8*)obj + payload->m_childDstOffset + 0x80);
            if (payload->m_useWorldMatrix == 0) {
                dst->x = source->x;
                dst->y = source->y;
                dst->z = source->z;
            } else {
                PSMTXMultVec((MtxPtr)((u8*)lbl_8032ED50 + 0x78), source, dst);
            }

            target[1] = payload->m_cooldown;
        }
    }

    target[1]--;
}
