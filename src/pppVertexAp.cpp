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

struct VertexApObject
{
    u8 unk0[0x10];
    Mtx localMatrix;
};

struct _pppPDataVal;


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
    VertexApObject* parentObj = (VertexApObject*)parent;
    s32 stateOffset = *ctrl->stateOffset;
    VertexApState* state = (VertexApState*)((u8*)parent + stateOffset + 0x80);

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (data->entryIndex < 0) {
        return;
    }

    if (state->countdown == 0) {
        int count;
        VertexApEnv* env = (VertexApEnv*)pppEnvStPtr;
        VertexApEntry* entry;
        Vec* points = *(Vec**)((u8*)parent + 0x70);
        entry = &env->entries[data->entryIndex];

        if (points == 0) {
            u32* srcTable = *(u32**)((u8*)env + 0x8);
            VertexApSource* src = *(VertexApSource**)((u8*)srcTable + (entry->vertexSetIndex * 4));
            points = src->points;
        }

        count = data->spawnCount;

        switch (data->mode) {
        case 0:
            while (count-- != 0) {
                if (state->index >= entry->maxValue) {
                    state->index = 0;
                }

                u16 outValue = state->index;
                u16* vertexIndices = entry->vertexIndices;
                state->index++;
                u16 vertexIndex = vertexIndices[outValue];
                Vec* vertex = &points[vertexIndex];
                f32 x = vertex->x;
                f32 y = vertex->y;
                f32 z = vertex->z;

                if ((data->childId + 0x10000) != 0xFFFF) {
                    s32 childId = data->childId;
                    _pppPDataVal* childData =
                        (_pppPDataVal*)((u8*)*(u32*)((u8*)pppMngStPtr + 0xD4) + (childId << 4));
                    Vec pos;
                    Vec* outPos;
                    _pppPObject* child;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)pppMngStPtr, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    pos.x = x;
                    pos.y = y;
                    pos.z = z;
                    PSMTXMultVec(parentObj->localMatrix, &pos, &pos);
                    outPos = (Vec*)((u8*)child + data->childPosOffset + 0x80);

                    if (data->useWorldMtx == 0) {
                        outPos->x = pos.x;
                        outPos->y = pos.y;
                        outPos->z = pos.z;
                    } else {
                        PSMTXMultVec(pppMngStPtr->m_matrix.value, &pos, outPos);
                    }
                }
            }
            break;
        case 1:
            while (count-- != 0) {
                f32 randValue = Math.RandF();
                f32 maxValue = (f32)entry->maxValue;
                int outValue = (int)(randValue * maxValue);
                u16* vertexIndices = entry->vertexIndices;
                u16 vertexIndex = vertexIndices[outValue];
                Vec* vertex = &points[vertexIndex];
                f32 x = vertex->x;
                f32 y = vertex->y;
                f32 z = vertex->z;

                if ((data->childId + 0x10000) != 0xFFFF) {
                    s32 childId = data->childId;
                    _pppPDataVal* childData =
                        (_pppPDataVal*)((u8*)*(u32*)((u8*)pppMngStPtr + 0xD4) + (childId << 4));
                    Vec pos;
                    Vec* outPos;
                    _pppPObject* child;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)pppMngStPtr, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    pos.x = x;
                    pos.y = y;
                    pos.z = z;
                    PSMTXMultVec(parentObj->localMatrix, &pos, &pos);
                    outPos = (Vec*)((u8*)child + data->childPosOffset + 0x80);

                    if (data->useWorldMtx == 0) {
                        outPos->x = pos.x;
                        outPos->y = pos.y;
                        outPos->z = pos.z;
                    } else {
                        PSMTXMultVec(pppMngStPtr->m_matrix.value, &pos, outPos);
                    }
                }
            }
            break;
        }

        state->countdown = data->spawnDelay;
    }

    state->countdown--;
}
