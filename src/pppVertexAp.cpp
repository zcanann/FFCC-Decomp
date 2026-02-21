#include "ffcc/pppVertexAp.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct VertexApEntry
{
    s16 vertexSetIndex;
    s16 maxValue;
    u16* vertexIndices;
};

struct VertexApEnv
{
    u8 unk0[0x8];
    void* unk8;
    u8 unkC[0x4];
    VertexApEntry* entries;
};

struct VertexApData
{
    u8 unk0[0x4];
    s16 entryIndex;
    u8 spawnCount;
    u8 spawnDelay;
    u8 mode;
    u8 useWorldMtx;
    u8 unkA[0x2];
    u32 childId;
    u32 childPosOffset;
};

struct VertexApState
{
    u16 index;
    u16 countdown;
};

struct VertexApCtrl
{
    u8 unk0[0xC];
    s32* stateOffset;
};

struct VertexApSource
{
    u8 unk0[0x2C];
    Vec* points;
};

struct _pppPDataVal;

extern CMath math;
extern int lbl_8032ED70;
extern u8* lbl_8032ED50;
extern VertexApEnv* lbl_8032ED54;

extern "C" {
f32 RandF__5CMathFv(CMath*);
_pppPObject* pppCreatePObject(_pppMngSt*, _pppPDataVal*);
}

/*
 * --INFO--
 * PAL Address: 0x80064ae8
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApCon(_pppPObject* pobj, PVertexAp* vtxAp)
{
    s32 offset = **(s32**)((u8*)vtxAp + 0xC);
    u16* state = (u16*)((u8*)pobj + offset + 0x80);
    state[0] = 0;
    state[1] = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
/*
 * --INFO--
 * PAL Address: 0x800647e0
 * PAL Size: 776b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexAp(_pppPObject* parent, PVertexAp* dataRaw, void* ctrlRaw)
{
    VertexApData* data = (VertexApData*)dataRaw;
    VertexApCtrl* ctrl = (VertexApCtrl*)ctrlRaw;
    s32 stateOffset = *ctrl->stateOffset;
    VertexApState* state = (VertexApState*)((u8*)parent + stateOffset + 0x80);

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (data->entryIndex < 0) {
        return;
    }

    if (state->countdown == 0) {
        VertexApEntry* entry = &lbl_8032ED54->entries[data->entryIndex];
        Vec* points = *(Vec**)((u8*)parent + 0x70);

        if (points == 0) {
            u32* srcTable = *(u32**)((u8*)lbl_8032ED54 + 0x8);
            VertexApSource* src = *(VertexApSource**)((u8*)srcTable + (entry->vertexSetIndex * 4));
            points = src->points;
        }

        u8 count = data->spawnCount;

        switch (data->mode) {
        case 0:
            do {
                if (state->index >= (u16)entry->maxValue) {
                    state->index = 0;
                }

                u16 vertexIndex = entry->vertexIndices[state->index];
                state->index++;
                Vec* vertex = &points[vertexIndex];
                f32 x = vertex->x;
                f32 y = vertex->y;
                f32 z = vertex->z;

                s32 childId = data->childId;
                if ((u16)childId != 0xFFFF) {
                    _pppPObject* child;
                    _pppPDataVal* childData = (_pppPDataVal*)((u8*)*(u32*)((u8*)lbl_8032ED50 + 0xD4) + (childId << 4));
                    Vec pos;
                    Vec worldPos;
                    Vec* outPos;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)lbl_8032ED50, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    pos.x = x;
                    pos.y = y;
                    pos.z = z;
                    PSMTXMultVec(*(Mtx*)((u8*)parent + 0x10), &pos, &pos);
                    outPos = (Vec*)((u8*)child + data->childPosOffset + 0x80);

                    if (data->useWorldMtx == 0) {
                        *outPos = pos;
                    } else {
                        PSMTXMultVec(*(Mtx*)((u8*)lbl_8032ED50 + 0x78), &pos, &worldPos);
                        *outPos = worldPos;
                    }
                }
            } while (count-- != 0);
            break;
        case 1:
            do {
                u16 vertexIndex = entry->vertexIndices[(s32)(RandF__5CMathFv(&math) * (f32)entry->maxValue)];
                Vec* vertex = &points[vertexIndex];
                f32 x = vertex->x;
                f32 y = vertex->y;
                f32 z = vertex->z;

                s32 childId = data->childId;
                if ((u16)childId != 0xFFFF) {
                    _pppPObject* child;
                    _pppPDataVal* childData = (_pppPDataVal*)((u8*)*(u32*)((u8*)lbl_8032ED50 + 0xD4) + (childId << 4));
                    Vec pos;
                    Vec worldPos;
                    Vec* outPos;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)lbl_8032ED50, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    pos.x = x;
                    pos.y = y;
                    pos.z = z;
                    PSMTXMultVec(*(Mtx*)((u8*)parent + 0x10), &pos, &pos);
                    outPos = (Vec*)((u8*)child + data->childPosOffset + 0x80);

                    if (data->useWorldMtx == 0) {
                        *outPos = pos;
                    } else {
                        PSMTXMultVec(*(Mtx*)((u8*)lbl_8032ED50 + 0x78), &pos, &worldPos);
                        *outPos = worldPos;
                    }
                }
            } while (count-- != 0);
            break;
        }

        state->countdown = data->spawnDelay;
    }

    state->countdown--;
}
