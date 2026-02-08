#include "ffcc/pppLocationTitle.h"
#include "ffcc/pppPart.h"

extern void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char);
extern void pppSetBlendMode__FUc(unsigned char);
extern void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);

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
    float fVar1 = 0.0f; // TODO: Find correct constant FLOAT_80330ee0
    u32* puVar2 = (u32*)((int)(&pppLocationTitle->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
    
    *puVar2 = 0;
    *(u16*)(puVar2 + 1) = 0;
    puVar2[4] = *(u32*)&fVar1;
    puVar2[3] = *(u32*)&fVar1;
    puVar2[2] = *(u32*)&fVar1;
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
    int iVar1 = *param_2->m_serializedDataOffsets;
    
    if (*(void**)((int)(&pppLocationTitle->field0_0x0 + 2) + iVar1) != NULL) {
        pppHeapUseRate(*(CMemory::CStage**)((int)(&pppLocationTitle->field0_0x0 + 2) + iVar1));
        *(u32*)((int)(&pppLocationTitle->field0_0x0 + 2) + iVar1) = 0;
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
    int serializedOffset = *param_3->m_serializedDataOffsets;

    if ((u16)param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    u32 graphId = *(u32*)((u8*)&pppLocationTitle->field0_0x0 + 0);
    int frameStep = (int)(graphId >> 12);
    if (((int)graphId < 0) && ((graphId & 0xFFF) != 0)) {
        frameStep++;
    }

    u8* state = (u8*)&pppLocationTitle->field0_0x0 + 8 + serializedOffset;
    Vec* source = *(Vec**)state;
    u16 sourceCount = *(u16*)(state + 4);
    u8* payload = (u8*)param_2->m_payload;
    int fadeDivisor = -1;
    if (*(u16*)(payload + 10) <= frameStep) {
        fadeDivisor = *(u16*)(payload + 12) + frameStep - *(u16*)(payload + 10);
    }

    long** shapeTable = *(long***)((u8*)pppEnvStPtr + 0x0C);
    long* shape = shapeTable[param_2->m_dataValIndex];
    u8 blend = *((u8*)&param_2->m_stepValue + 1);

    for (int i = 0; i < sourceCount; i++) {
        Mtx modelMtx;
        Vec transformedPos;
        u32 packedColor;

        PSMTXIdentity(modelMtx);
        modelMtx[2][2] = ((float*)source)[4];
        modelMtx[0][0] = pppMngStPtr->m_scale.x * modelMtx[2][2];
        modelMtx[1][1] = pppMngStPtr->m_scale.y * modelMtx[2][2];
        modelMtx[2][2] = pppMngStPtr->m_scale.z * modelMtx[2][2];

        PSMTXMultVec(ppvCameraMatrix0, source, &transformedPos);
        modelMtx[0][3] = transformedPos.x;
        modelMtx[1][3] = transformedPos.y;
        modelMtx[2][3] = transformedPos.z;

        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
            (u8*)source + 0x0C, NULL, 0.0f, 0, 0, 0, 0, 0, 1, 0);

        if (fadeDivisor >= 0) {
            u8 alpha = *((u8*)source + 0x0F);
            *((u8*)source + 0x0F) = alpha - (u8)(alpha / fadeDivisor);
        }

        packedColor = *(u32*)((u8*)source + 0x0C);
        GXColor chanColor;
        *(u32*)&chanColor = packedColor;
        GXSetChanMatColor(GX_COLOR0A0, chanColor);
        GXLoadPosMtxImm(modelMtx, 0);
        pppSetBlendMode__FUc(blend);
        pppDrawShp__FPlsP12CMaterialSetUc(shape, *(short*)((u8*)source + 0x18),
                                          pppEnvStPtr->m_materialSetPtr, blend);
        source = (Vec*)((u8*)source + 0x1C);
    }
}
