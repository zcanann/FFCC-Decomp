#include "ffcc/pppLocationTitle.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

static int GetGraphFrameFromId(u32 graphId)
{
    return ((int)graphId >> 12) + (int)((graphId & 0x80000000) != 0 && (graphId & 0xFFF) != 0);
}

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
    int serializedOffset = *param_3->m_serializedDataOffsets;

    if (param_2->m_dataValIndex != 0xFFFF) {
        u32 graphId = *(u32*)pppLocationTitle;
        int fadeDivisor = -1;
        int graphFrame = GetGraphFrameFromId(graphId);
        Vec* particle = *(Vec**)((u8*)pppLocationTitle + 8 + serializedOffset);
        long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + param_2->m_dataValIndex * 4);

        u16* payload = (u16*)param_2->m_payload;
        if ((int)payload[5] <= graphFrame) {
            fadeDivisor = payload[6] + (graphFrame - (int)payload[5]);
        }

        u16 count = *(u16*)((u8*)pppLocationTitle + 12 + serializedOffset);
        for (int i = 0; i < (int)count; i++) {
            Mtx model;
            Vec worldPos;
            u32 colorWord;
            GXColor color;

            PSMTXIdentity(model);
            model[2][2] = particle[1].y;
            model[0][0] = pppMngStPtr->m_scale.x * model[2][2];
            model[1][1] = pppMngStPtr->m_scale.y * model[2][2];
            model[2][2] = pppMngStPtr->m_scale.z * model[2][2];

            PSMTXMultVec(ppvCameraMatrix0, particle, &worldPos);
            model[0][3] = worldPos.x;
            model[1][3] = worldPos.y;
            model[2][3] = worldPos.z;

            pppSetDrawEnv((pppCVECTOR*)(particle + 1), (pppFMATRIX*)0, 0.0f, 0, 0, 0, 0, 0, 1, 0);

            if (fadeDivisor > 0) {
                u8* alpha = (u8*)&particle[1].x + 3;
                *alpha = (u8)(*alpha - (*alpha / fadeDivisor));
            }

            colorWord = *(u32*)&particle[1].x;
            *(u32*)&color = colorWord;
            GXSetChanMatColor(GX_COLOR0A0, color);
            GXLoadPosMtxImm(model, 0);

            u8 blendMode = ((u8*)&param_2->m_stepValue)[1];
            pppSetBlendMode(blendMode);
            pppDrawShp(shapeTable, *(short*)&particle[2].x, pppEnvStPtr->m_materialSetPtr, blendMode);

            particle = (Vec*)&particle[2].y;
        }
    }
}
