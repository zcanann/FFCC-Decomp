#include "ffcc/pppVertexAttend.h"
#include "ffcc/linkage.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"
#include <stddef.h>

struct VertexAttendStream
{
    s32 sourceOffset;
    s32 destOffset;
};

struct pppVertexAttendStep
{
    u8 pad0[0xC];
    s16 m_entryIndex;
};

struct VertexSetEntry
{
    s16 modelIndex;
    u8 pad2[2];
    u16* vertexRemap;
};

struct VertexAttendModel
{
    u8 pad0[0x2C];
    Vec* vertexData;
};

struct VertexAttendEnv
{
    u8 pad0[0x8];
    VertexAttendModel** modelTable;
    u8 padC[0x4];
    VertexSetEntry* vertexSetTable;
};

STATIC_ASSERT(offsetof(pppVertexAttendStep, m_entryIndex) == 0xC);


/*
 * --INFO--
 * PAL Address: 0x80064f6c
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexAttend(_pppPObject* object, pppVertexAttendStep* step, _pppCtrlTable* ctrl)
{
    s16 entryIndex = step->m_entryIndex;
    VertexAttendStream* stream;
    VertexAttendEnv* env;
    VertexSetEntry* setEntry;
    u16 sourceIndex;
    f32* output;
    VertexAttendModel* model;
    Vec* sourceVertex;
    MtxPtr matrix;
    Vec transformed;

    if (entryIndex < 0) {
        return;
    }

    stream = reinterpret_cast<VertexAttendStream*>(ctrl->m_serializedDataOffsets);
    env = (VertexAttendEnv*)ppvEnv;
    setEntry = (VertexSetEntry*)((u8*)env->vertexSetTable + (entryIndex * sizeof(VertexSetEntry)));
    sourceIndex = *(u16*)(object->m_workArea + stream->sourceOffset);
    output = (f32*)(object->m_workArea + stream->destOffset);
    model = env->modelTable[setEntry->modelIndex];
    sourceVertex = &model->vertexData[setEntry->vertexRemap[sourceIndex]];
    matrix = reinterpret_cast<_pppPObject*>(object->m_link.m_previous)->m_localMatrix.value;

    transformed = *sourceVertex;
    PSMTXMultVec(matrix, &transformed, &transformed);

    output[0] = transformed.x;
    output[1] = transformed.y;
    output[2] = transformed.z;
}
