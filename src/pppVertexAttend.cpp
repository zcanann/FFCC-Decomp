#include "ffcc/pppVertexAttend.h"
#include "dolphin/mtx.h"

struct VertexAttendStream
{
    s32 sourceOffset;
    s32 destOffset;
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
    s16* vertexSetTable;
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

    if (entryIndex < 0) {
        return;
    }

    VertexAttendStream* stream = *(VertexAttendStream**)((u8*)r5 + 0xC);
    Vec transformed;
    Vec* transformedPtr = &transformed;
    u8* output = (u8*)r3 + stream->destOffset;
    u16 sourceIndex = *(u16*)((u8*)r3 + stream->sourceOffset + 0x80);
    s16 modelIndex = ((s16*)lbl_8032ED54->vertexSetTable)[(u32)entryIndex * 4];
    u16 vertexIndex = *(u16*)(output + ((u32)sourceIndex << 1));
    Vec* sourceVertex =
        (Vec*)((u8*)lbl_8032ED54->modelTable[modelIndex]->vertexData + (vertexIndex * sizeof(Vec)));

    transformed.x = sourceVertex->x;
    transformed.y = sourceVertex->y;
    transformed.z = sourceVertex->z;

    PSMTXMultVec(*(Mtx*)((u8*)*(void**)((u8*)r3 + 4) + 0x10), transformedPtr, transformedPtr);

    *(f32*)((u8*)output + 0x80) = transformed.x;
    *(f32*)((u8*)output + 0x84) = transformed.y;
    *(f32*)((u8*)output + 0x88) = transformed.z;
}
