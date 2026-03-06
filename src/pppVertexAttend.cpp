#include "ffcc/pppVertexAttend.h"
#include "dolphin/mtx.h"

struct VertexAttendStream
{
    s32 sourceOffset;
    s32 destOffset;
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

extern VertexAttendEnv* lbl_8032ED54;

/*
 * --INFO--
 * PAL Address: 0x80064f6c
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexAttend(void* r3, void* r4, void* r5)
{
    s16 entryIndex = *(s16*)((u8*)r4 + 0xC);
    VertexAttendEnv* env;
    VertexAttendStream* stream;
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

    stream = *(VertexAttendStream**)((u8*)r5 + 0xC);
    env = lbl_8032ED54;
    setEntry = (VertexSetEntry*)((u8*)env->vertexSetTable + (entryIndex * sizeof(VertexSetEntry)));
    sourceIndex = *(u16*)((u8*)r3 + stream->sourceOffset + 0x80);
    output = (f32*)((u8*)r3 + stream->destOffset + 0x80);
    model = env->modelTable[setEntry->modelIndex];
    sourceVertex = &model->vertexData[setEntry->vertexRemap[sourceIndex]];
    matrix = (MtxPtr)((u8*)*(void**)((u8*)r3 + 4) + 0x10);

    transformed = *sourceVertex;
    PSMTXMultVec(matrix, &transformed, &transformed);

    output[0] = transformed.x;
    output[1] = transformed.y;
    output[2] = transformed.z;
}
