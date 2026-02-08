#include "ffcc/pppLocationTitle.h"
#include "ffcc/pppPart.h"

/*
 * --INFO--
 * PAL Address: 0x800d92cc
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructLocationTitle(pppLocationTitle* pppLocationTitle, UnkC* param_2)
{
    s32* serializedOffsets = *(s32**)((u8*)param_2 + 0xC);
    u8* base = (u8*)pppLocationTitle + *serializedOffsets + 0x80;
    float value = 0.0f;

    *(u32*)(base + 0x0) = 0;
    *(u16*)(base + 0x4) = 0;
    *(float*)(base + 0x10) = value;
    *(float*)(base + 0xC) = value;
    *(float*)(base + 0x8) = value;
}

/*
 * --INFO--
 * PAL Address: 0x800d9278
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructLocationTitle(pppLocationTitle* pppLocationTitle, UnkC* param_2)
{
    s32* serializedOffsets = *(s32**)((u8*)param_2 + 0xC);
    s32 fieldOffset = *serializedOffsets + 0x80;

    if (*(CMemory::CStage**)((u8*)pppLocationTitle + fieldOffset) != NULL) {
        pppHeapUseRate(*(CMemory::CStage**)((u8*)pppLocationTitle + fieldOffset));
        *(u32*)((u8*)pppLocationTitle + fieldOffset) = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d8dac
 * PAL Size: 1228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameLocationTitle(pppLocationTitle* pppLocationTitle, UnkB* param_2, UnkC* param_3)
{
    // TODO: Complex implementation with matrix operations
    // This is a very large function that needs careful implementation
    // Based on Ghidra decompilation with matrix math, memory allocation, etc.
}

/*
 * --INFO--
 * PAL Address: 0x800d8c1c
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderLocationTitle(pppLocationTitle* pppLocationTitle, UnkB* param_2, UnkC* param_3)
{
    // TODO: Implementation with rendering operations
    // Based on Ghidra decompilation with GX calls and matrix operations
}
