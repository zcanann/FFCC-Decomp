#include "global.h"
#include "ffcc/pppVertexApLc.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

struct VertexApLcEntry
{
    s16 vertexSetIndex;
    s16 maxValue;
    u16* vertexIndices;
};

struct VertexApLcSource;

struct VertexApLcEnv
{
    u8 unk0[0x8];
    VertexApLcSource** sourceTable;
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

struct VertexApLcSource
{
    u8 unk0[0x2C];
    Vec* points;
};


static inline void apea(_pppPObject* parent, PVertexApLc* dataRaw, Vec* pos)
{
    VertexApLcData* data = (VertexApLcData*)dataRaw;
    u32 childId = data->childId;
    if ((childId + 0x10000) != 0xFFFF) {
        _pppPDataVal* childData = ppvMng->m_pppPDataVals + childId;
        _pppPObject* child;
        if (childData == 0) { child = 0; } else { child = pppCreatePObject(ppvMng, childData); child->m_link.m_previous = &parent->m_link; }
        *(Vec*)(child->m_workArea + data->childPosOffset) = *pos;
    }
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
void pppVertexApLc(_pppPObject* parent, PVertexApLc* dataRaw, _pppCtrlTable* ctrl)
{
    VertexApLcData* data = (VertexApLcData*)dataRaw;
    s32 stateOffset = ctrl->m_serializedDataOffsets[0];
    VertexApLcState* state = (VertexApLcState*)(parent->m_workArea + stateOffset);
    Vec pos;
    u32 cid;
    Vec* vertex;
    _pppPDataVal* childData;
    _pppPObject* child;

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (data->entryIndex < 0) {
        return;
    }

    if (state->countdown == 0) {
        int count;
        VertexApLcEnv* env = (VertexApLcEnv*)ppvEnv;
        VertexApLcEntry* entry;
        Vec* points = parent->m_drawMatrixPtr;
        entry = &env->entries[data->entryIndex];

        if (points == 0) {
            VertexApLcSource* src = env->sourceTable[entry->vertexSetIndex];
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
                vertex = &points[vertexIndex];
                pos.x = vertex->x;
                pos.y = vertex->y;
                pos.z = vertex->z;
                apea(parent, dataRaw, &pos);
            }
            break;
        case 1:
            while (count-- != 0) {
                f32 randValue = Math.RandF();
                f32 maxValue = (f32)entry->maxValue;
                int outValue = (int)(randValue * maxValue);
                u16* vertexIndices = entry->vertexIndices;
                u16 vertexIndex = vertexIndices[outValue];
                vertex = &points[vertexIndex];
                pos.x = vertex->x;
                pos.y = vertex->y;
                pos.z = vertex->z;
                apea(parent, dataRaw, &pos);
            }
            break;
        }

        state->countdown = data->spawnDelay;
    }

    state->countdown--;
}


/*
 * --INFO--
 * PAL Address: 0x80064f4c
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApLcCon(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    s32 offset = ctrl->m_serializedDataOffsets[0];
    u16* state = (u16*)(obj->m_workArea + offset);

    state[0] = 0;
    state[1] = 0;
}
