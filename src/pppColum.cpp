#include "ffcc/pppColum.h"
#include "ffcc/partMng.h"

/*
 * --INFO--
 * PAL Address: 0x800df2f8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructColum(pppColum *column, UnkC *param_2)
{
    unsigned short *puVar1 = (unsigned short *)((char*)column + 0x80 + param_2->m_serializedDataOffsets[3]);
    puVar1[2] = 0;
    puVar1[1] = 0;
    *puVar1 = 0;
    *(unsigned int *)(puVar1 + 4) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800df2ac
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructColum(pppColum *column, UnkC *param_2)
{
    int iVar1 = param_2->m_serializedDataOffsets[3];
    void** memPtr = (void**)((char*)column + 0x88 + iVar1);
    if (*memPtr != 0) {
        // TODO: pppHeapUseRate__FPQ27CMemory6CStage(*memPtr);
        *memPtr = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800df168
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameColum(pppColum *column, UnkB *param_2, UnkC *param_3)
{
    // TODO: Check global pause state - if (DAT_8032ed70 == 0)
    unsigned char *puVar4 = (unsigned char *)((char*)column + 0x80 + param_3->m_serializedDataOffsets[3]);
    if (*(int *)(puVar4 + 8) == 0) {
        // TODO: Allocate memory for particle data
        // uVar1 = pppMemAlloc(...);
        // Initialize particle data arrays
    }
    if (param_2->m_dataValIndex != 0xffff) {
        // TODO: Calculate frame shape
        // pppCalcFrameShape__FPlRsRsRss(...);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800dec5c
 * PAL Size: 1292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderColum(pppColum *column, UnkB *param_2, UnkC *param_3)
{
    int iVar7 = param_3->m_serializedDataOffsets[3];
    int iVar5 = param_3->m_serializedDataOffsets[2];
    
    if (param_2->m_dataValIndex != 0xffff) {
        // TODO: Get texture and shape data
        // pppShapeSt *shapeSt = ...;
        
        // TODO: Check if column data is active
        // if (column->field_0xb2[iVar5] != 0) {
            // TODO: Complex rendering logic
            // - Matrix setup
            // - Vector calculations
            // - Blending setup
            // - Quad rendering loop
        // }
    }
}