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

extern int gPppCalcDisabled;

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
    _pppPointApOffsets* data = (_pppPointApOffsets*)ctrlTable->m_serializedDef;
    u8* target = (u8*)pObject + data->targetOffset + 0x80;
    Vec* src = (Vec*)((u8*)pObject + data->srcOffset + 0x80);
    _pppPointApStep* payload = (_pppPointApStep*)step;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (target[1] == 0) {
        if ((payload->m_createProgramIndex + 0x10000) == 0xFFFF) {
            return;
        }

        _pppPObject* obj;
        _pppPDataVal* objData = (_pppPDataVal*)((u8*)(*(u32*)((u8*)pppMngStPtr + 0xD4)) + (payload->m_createProgramIndex << 4));

        if (objData == 0) {
            obj = 0;
        } else {
            obj = pppCreatePObject(pppMngStPtr, objData);
            *(_pppPObject**)((u8*)obj + 4) = pObject;
        }

        Vec* dst = (Vec*)((u8*)obj + payload->m_childDstOffset + 0x80);
        if (payload->m_useWorldMatrix == 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            PSMTXMultVec((MtxPtr)((u8*)pppMngStPtr + 0x78), src, dst);
        }

        target[1] = payload->m_cooldown;
    }

    target[1]--;
}
