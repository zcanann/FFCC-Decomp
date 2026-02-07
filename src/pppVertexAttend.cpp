#include "ffcc/pppVertexAttend.h"
#include "dolphin/mtx.h"

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
    s16 count = *(s16*)((u8*)r4 + 0xc);
    if (count < 0) {
        return;
    }

    void* streamData = *(void**)((u8*)r5 + 0xc);
    u32 sourceOffset = *(u32*)streamData + 0x80;
    u32 destOffset = *(u32*)((u8*)streamData + 4) + 0x80;
    u8* output = (u8*)r3 + destOffset;

    extern void* lbl_8032ED54;
    u8* tableA = *(u8**)((u8*)lbl_8032ED54 + 0x10);
    u8* entry = tableA + (count << 3);
    s16 modelIndex = *(s16*)entry;

    u8* tableB = *(u8**)((u8*)lbl_8032ED54 + 8);
    u8* model = *(u8**)(tableB + (modelIndex << 2));
    u8* vertexData = *(u8**)(model + 0x2c);

    u16 sourceIndex = *(u16*)((u8*)r3 + sourceOffset);
    u8* indexTable = *(u8**)((u8*)streamData + 4);
    u16 vertexIndex = *(u16*)(indexTable + (sourceIndex << 1));
    u8* vertex = vertexData + (vertexIndex * 12);

    Vec transformed;
    transformed.x = *(f32*)(vertex + 0);
    transformed.y = *(f32*)(vertex + 4);
    transformed.z = *(f32*)(vertex + 8);

    Mtx* mtx = (Mtx*)((u8*)*(void**)((u8*)r3 + 4) + 0x10);
    PSMTXMultVec(*mtx, &transformed, &transformed);

    *(f32*)(output + 0) = transformed.x;
    *(f32*)(output + 4) = transformed.y;
    *(f32*)(output + 8) = transformed.z;
}
