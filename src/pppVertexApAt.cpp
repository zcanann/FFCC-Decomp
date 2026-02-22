#include "ffcc/pppVertexApAt.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"

#include <dolphin/types.h>

struct VertexApAtEntry
{
    u16 unk0;
    s16 maxValue;
    u32 unk4;
};

struct VertexApAtEnv
{
    u8 unk0[0x10];
    VertexApAtEntry* entries;
};

struct VertexApAtCtrl
{
    u8 unk0[0xC];
    s32* stateOffset;
};

struct VertexApAtData
{
    u8 unk0[0x4];
    s16 entryIndex;
    u8 spawnCount;
    u8 waitFrames;
    u8 mode;
    u8 unk9[0x2];
    s32 childId;
    s32 childValueOffset;
};

struct VertexApAtState
{
    u16 index;
    u16 countdown;
};

struct _pppPDataVal;

extern CMath math[];
extern int lbl_8032ED70;
extern unsigned char* lbl_8032ED50;
extern VertexApAtEnv* lbl_8032ED54;
extern "C" f32 RandF__5CMathFv(CMath*);
extern _pppPObject* pppCreatePObject(_pppMngSt*, _pppPDataVal*);

/*
 * --INFO--
 * PAL Address: 0x80064cc8
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApAtCon(_pppPObject* obj, PVertexApAt* data)
{
    s32 offset = **(s32**)((u8*)data + 0xC);
    u16* state = (u16*)((u8*)obj + offset + 0x80);
    state[0] = 0;
    state[1] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80064ce8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void apea(_pppPObject*, PVertexApAt*, unsigned short)
{
    // Intentionally empty.
}

/*
 * --INFO--
 * PAL Address: 0x80064b08
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApAt(_pppPObject* parent, PVertexApAt* data, void* ctrl)
{
    VertexApAtData* vtxData = (VertexApAtData*)data;
    VertexApAtCtrl* vtxCtrl = (VertexApAtCtrl*)ctrl;
    s32 stateOffset = *vtxCtrl->stateOffset;
    VertexApAtState* state = (VertexApAtState*)((u8*)parent + stateOffset + 0x80);

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (vtxData->entryIndex < 0) {
        return;
    }

    if (state->countdown == 0) {
        VertexApAtEntry* entry = &lbl_8032ED54->entries[vtxData->entryIndex];
        u8 count = vtxData->spawnCount;

        switch (vtxData->mode) {
        case 0:
            do {
                if (state->index >= (u16)entry->maxValue) {
                    state->index = 0;
                }

                u16 outValue = state->index;
                state->index++;

                u16 childId = (u16)vtxData->childId;
                if (childId != 0xFFFF) {
                    _pppPDataVal* childData = (_pppPDataVal*)((u8*)*(u32*)((u8*)lbl_8032ED50 + 0xD4) + (childId << 4));
                    _pppPObject* child;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)lbl_8032ED50, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    *(u16*)((u8*)child + vtxData->childValueOffset + 0x80) = outValue;
                }
            } while (count-- != 0);
            break;
        case 1:
            do {
                u16 outValue = (u16)(RandF__5CMathFv(math) * (f32)entry->maxValue);
                u16 childId = (u16)vtxData->childId;

                if (childId != 0xFFFF) {
                    _pppPDataVal* childData = (_pppPDataVal*)((u8*)*(u32*)((u8*)lbl_8032ED50 + 0xD4) + (childId << 4));
                    _pppPObject* child;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)lbl_8032ED50, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    *(u16*)((u8*)child + vtxData->childValueOffset + 0x80) = outValue;
                }
            } while (count-- != 0);
            break;
        }

        state->countdown = vtxData->waitFrames;
    }

    state->countdown--;
}
