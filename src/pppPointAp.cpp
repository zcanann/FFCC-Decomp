#include "ffcc/pppPointAp.h"

#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct _pppMngSt;
struct _pppPDataVal;

struct _pppPObject {
    void* unk0;
    void* owner;
};

extern int lbl_8032ED70;
extern _pppMngSt* lbl_8032ED50;
extern _pppPObject* pppCreatePObject(_pppMngSt*, _pppPDataVal*);

/*
 * --INFO--
 * PAL Address: 0x80060d08
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointApCon(void* param1, void* param2)
{
    u32* data = *(u32**)((u8*)param2 + 0xC);
    param1 = (u8*)param1 + data[1];
    *((u8*)param1 + 0x81) = 0;
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
void pppPointAp(void* param1, void* param2, void* param3)
{
    Vec* src = *(Vec**)((u8*)param3 + 0xC);
    s32 index = (s32)src->y;
    u8* target = (u8*)param1 + index + 0x80;

    if (lbl_8032ED70 == 0) {
        if ((s8)target[1] == 0) {
            u32 objId = *(u32*)((u8*)param2 + 0x4);
            if ((objId + 0x10000) != 0xFFFF) {
                _pppPDataVal* objData = (_pppPDataVal*)(*(u32*)((u8*)lbl_8032ED50 + 0xD4) + (objId << 4));

                if (objData != 0) {
                    _pppPObject* obj = pppCreatePObject(lbl_8032ED50, objData);
                    obj->owner = param1;

                    Vec* dst = (Vec*)((u8*)obj + *(u32*)((u8*)param2 + 0x8) + 0x80);
                    if (*(u8*)((u8*)param2 + 0xD) == 0) {
                        dst->x = src->x;
                        dst->y = src->y;
                        dst->z = src->z;
                    } else {
                        PSMTXMultVec((MtxPtr)((u8*)lbl_8032ED50 + 0x78), src, dst);
                    }

                    target[1] = *(u8*)((u8*)param2 + 0xC);
                }
            }
        }

        if ((s8)target[1] > 0) {
            target[1]--;
        }
    }
}
