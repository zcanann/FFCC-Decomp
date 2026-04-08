#include "ffcc/pppPObjPoint.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"


typedef struct PObjPointEntry {
    u32 unk0;
    u32 vecOffset;
    u32 unk8;
    u32 unkC;
} PObjPointEntry;

/*
 * --INFO--
 * PAL Address: 0x80060AEC
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPObjPoint(PppPointData* pointData, PppObjData* objData, PppContainer* container)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 objOffset = *(s32*)container->ptrData;
    PppPointObj* objPtr = (PppPointObj*)((u8*)pointData + objOffset + 0x80);

    if (objData->id == pointData->id) {
        u32 vecIndex = objData->field_4;
        u8* vecPtr;

        if ((vecIndex + 0x10000) == 0xFFFF) {
            vecPtr = (u8*)gPppDefaultValueBuffer;
        } else {
            PObjPointEntry* table = *(PObjPointEntry**)((u8*)pppMngStPtr + 0xD4);
            vecPtr = (u8*)objData->data + 0x80;
            vecPtr += table[vecIndex].vecOffset;
        }

        objPtr->vecPtr = vecPtr;
    }

    objPtr->x = ((f32*)objPtr->vecPtr)[0];
    objPtr->y = ((f32*)objPtr->vecPtr)[1];
    objPtr->z = ((f32*)objPtr->vecPtr)[2];
}
