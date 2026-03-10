#include "ffcc/pppVertexApLc.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"

struct VertexApLcEntry
{
    s16 vertexSetIndex;
    s16 maxValue;
    u16* vertexIndices;
};

struct VertexApLcEnv
{
    u8 unk0[0x8];
    void* unk8;
    u8 unkC[0x4];
    VertexApLcEntry* entries;
};

struct VertexApLcData
{
    u8 unk0[0x4];
    s16 entryIndex;
    u8 spawnCount;
    u8 spawnDelay;
    u8 mode;
    u8 unk9;
    u16 unkA;
    u32 childId;
    u32 childPosOffset;
};

struct VertexApLcState
{
    u16 index;
    u16 countdown;
};

struct VertexApLcCtrl
{
    u8 unk0[0xC];
    s32* stateOffset;
};

struct VertexApLcSource
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
 * PAL Address: 0x80064f4c
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApLcCon(_pppPObject* obj, PVertexApLc* apLc)
{
    s32 offset = **(s32**)((u8*)apLc + 0xC);
    u16* state = (u16*)((u8*)obj + offset + 0x80);

    state[0] = 0;
    state[1] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80064ce8  
 * PAL Size: 612b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApLc(_pppPObject* parent, PVertexApLc* dataRaw, void* ctrlRaw)
{
    VertexApLcData* data = (VertexApLcData*)dataRaw;
    VertexApLcCtrl* ctrl = (VertexApLcCtrl*)ctrlRaw;
    s32 stateOffset = *ctrl->stateOffset;
    VertexApLcState* state = (VertexApLcState*)((u8*)parent + stateOffset + 0x80);

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (data->entryIndex < 0) {
        return;
    }

    if (state->countdown == 0) {
        VertexApLcEnv* env = (VertexApLcEnv*)pppEnvStPtr;
        VertexApLcEntry* entry = &env->entries[data->entryIndex];
        u16* vertexIndices = entry->vertexIndices;
        Vec* points = *(Vec**)((u8*)parent + 0x70);

        if (points == 0) {
            u32* srcTable = *(u32**)((u8*)env + 0x8);
            VertexApLcSource* src = *(VertexApLcSource**)((u8*)srcTable + (entry->vertexSetIndex * 4));
            points = src->points;
        }

        s32 count = data->spawnCount;
        switch (data->mode) {
        case 0: {
            do {
                if ((s16)state->index >= entry->maxValue) {
                    state->index = 0;
                }

                u16 index = state->index++;
                u16 vertexIndex = vertexIndices[index];
                Vec* vertex = &points[vertexIndex];
                f32 x = vertex->x;
                f32 y = vertex->y;
                f32 z = vertex->z;

                if ((data->childId + 0x10000) != 0xFFFF) {
                    s32 childId = data->childId;
                    _pppPDataVal* childData =
                        (_pppPDataVal*)((u8*)*(u32*)((u8*)pppMngStPtr + 0xD4) + (childId << 4));
                    _pppPObject* child;
                    Vec* outPos;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)pppMngStPtr, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    outPos = (Vec*)((u8*)child + data->childPosOffset + 0x80);
                    outPos->x = x;
                    outPos->y = y;
                    outPos->z = z;
                }
            } while (count-- != 0);
            break;
        }
        case 1: {
            do {
                u16 vertexIndex = vertexIndices[(s32)((f32)entry->maxValue * RandF__5CMathFv(&Math))];
                Vec* vertex = &points[vertexIndex];
                f32 x = vertex->x;
                f32 y = vertex->y;
                f32 z = vertex->z;

                if ((data->childId + 0x10000) != 0xFFFF) {
                    s32 childId = data->childId;
                    _pppPDataVal* childData =
                        (_pppPDataVal*)((u8*)*(u32*)((u8*)pppMngStPtr + 0xD4) + (childId << 4));
                    _pppPObject* child;
                    Vec* outPos;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject((_pppMngSt*)pppMngStPtr, childData);
                        *(void**)((u8*)child + 0x4) = parent;
                    }

                    outPos = (Vec*)((u8*)child + data->childPosOffset + 0x80);
                    outPos->x = x;
                    outPos->y = y;
                    outPos->z = z;
                }
            } while (count-- != 0);
            break;
        }
        }

        state->countdown = data->spawnDelay;
    }

    state->countdown--;
}
