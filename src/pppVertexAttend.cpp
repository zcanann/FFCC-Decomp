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
    VertexAttendStream* stream;
    VertexAttendEnv* env;
    VertexSetEntry* setEntry;
    VertexAttendModel** modelTable;
    u16 sourceIndex;
    s32 modelIndex;
    u16 vertexIndex;
    u8* output;
    VertexAttendModel* model;
    Vec* sourceVertex;
    void* matrixObject;
    Vec transformed;
    Vec* transformedPtr = &transformed;

    if (entryIndex < 0) {
        return;
    }

    stream = *(VertexAttendStream**)((u8*)r5 + 0xC);
    env = lbl_8032ED54;
    setEntry = (VertexSetEntry*)((u8*)env->vertexSetTable + (entryIndex * sizeof(VertexSetEntry)));
    sourceIndex = *(u16*)((u8*)r3 + stream->sourceOffset + 0x80);
    output = (u8*)r3 + stream->destOffset + 0x80;
    modelIndex = setEntry->modelIndex;
    vertexIndex = setEntry->vertexRemap[sourceIndex];
    modelTable = env->modelTable;
    model = modelTable[modelIndex];
    sourceVertex = (Vec*)((u8*)model->vertexData + (vertexIndex * sizeof(Vec)));
    matrixObject = *(void**)((u8*)r3 + 4);

    transformed.x = sourceVertex->x;
    transformed.y = sourceVertex->y;
    transformed.z = sourceVertex->z;

    PSMTXMultVec((MtxPtr)((u8*)matrixObject + 0x10), transformedPtr, transformedPtr);

    *(f32*)(output + 0) = transformed.x;
    *(f32*)(output + 4) = transformed.y;
    *(f32*)(output + 8) = transformed.z;
}
