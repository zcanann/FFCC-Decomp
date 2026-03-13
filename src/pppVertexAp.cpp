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
    u16 unkA;
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

extern "C" {
f32 RandF__5CMathFv(CMath*);
}

_pppPObject* pppCreatePObject(_pppMngSt*, _pppPDataVal*);

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

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (data->entryIndex < 0) {
        return;
    }

    if (state->countdown == 0) {
        VertexApEnv* env = (VertexApEnv*)pppEnvStPtr;
        VertexApEntry* entry = &env->entries[data->entryIndex];
        u16* vertexIndices = entry->vertexIndices;
        Vec* points = *(Vec**)((u8*)parent + 0x70);

        if (points == 0) {
            u32* srcTable = *(u32**)((u8*)env + 0x8);
            VertexApSource* src = *(VertexApSource**)((u8*)srcTable + (entry->vertexSetIndex * 4));
            points = src->points;
        }

        s32 count = data->spawnCount;

        switch (data->mode) {
        case 0: {
            MtxPtr parentMtx = (MtxPtr)((u8*)parent + 0x10);
            do {
                if (state->index >= entry->maxValue) {
                    state->index = 0;
                }

                u16 outValue = state->index;
                state->index++;
                u16 vertexIndex = vertexIndices[outValue];
                Vec* vertex = &points[vertexIndex];
                f32 x = vertex->x;
                f32 y = vertex->y;
                f32 z = vertex->z;

                if ((data->childId + 0x10000) != 0xFFFF) {
                    _pppPObject* child;
                    s32 childId = data->childId;
                    _pppPDataVal* childData =
                        (_pppPDataVal*)((u8*)*(u32*)((u8*)pppMngStPtr + 0xD4) + (childId << 4));
                    Vec pos;
                    Vec* dst;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)pppMngStPtr, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    pos.x = x;
                    pos.y = y;
                    pos.z = z;
                    PSMTXMultVec(parentMtx, &pos, &pos);
                    dst = (Vec*)((u8*)child + data->childPosOffset + 0x80);

                    if (data->useWorldMtx == 0) {
                        dst->x = pos.x;
                        dst->y = pos.y;
                        dst->z = pos.z;
                    } else {
                        PSMTXMultVec(*(Mtx*)((u8*)pppMngStPtr + 0x78), &pos, dst);
                    }
                }
            } while (count-- != 0);
            break;
        }
        case 1: {
            MtxPtr parentMtx = (MtxPtr)((u8*)parent + 0x10);
            do {
                f32 randValue = RandF__5CMathFv(&Math);
                f32 maxValue = (f32)entry->maxValue;
                int outValue = (int)(randValue * maxValue);
                u16 vertexIndex = vertexIndices[outValue];
                Vec* vertex = &points[vertexIndex];
                f32 x = vertex->x;
                f32 y = vertex->y;
                f32 z = vertex->z;

                if ((data->childId + 0x10000) != 0xFFFF) {
                    _pppPObject* child;
                    s32 childId = data->childId;
                    _pppPDataVal* childData =
                        (_pppPDataVal*)((u8*)*(u32*)((u8*)pppMngStPtr + 0xD4) + (childId << 4));
                    Vec pos;
                    Vec* dst;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)pppMngStPtr, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    pos.x = x;
                    pos.y = y;
                    pos.z = z;
                    PSMTXMultVec(parentMtx, &pos, &pos);
                    dst = (Vec*)((u8*)child + data->childPosOffset + 0x80);

                    if (data->useWorldMtx == 0) {
                        dst->x = pos.x;
                        dst->y = pos.y;
                        dst->z = pos.z;
                    } else {
                        PSMTXMultVec(*(Mtx*)((u8*)pppMngStPtr + 0x78), &pos, dst);
                    }
                }
            } while (count-- != 0);
            break;
        }
        default:
            break;
        }

        state->countdown = data->spawnDelay;
    }

    state->countdown--;
}
