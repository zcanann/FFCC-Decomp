#include "ffcc/pppCrystal2.h"
#include "ffcc/pppPart.h"

#include <math.h>
#include <dolphin/gx.h>

extern int DAT_8032ed70;
extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

static char s_pppCrystal2Cpp[] = "pppCrystal2.cpp";

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ImageBufferSetPixel_IA8(HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeRefractionMap(HSD_ImageBuffer*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8013ef74
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCrystal2(pppCrystal2* pppCrystal2, UnkC* param_2)
{
    s32 iVar1 = param_2->m_serializedDataOffsets[2];
    u32* data = (u32*)((char*)pppCrystal2 + iVar1 + 8);

    data[0] = 0;
    data[1] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8013eeec
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCrystal2(pppCrystal2* pppCrystal2, UnkC* param_2)
{
    u32* puVar1;
    CMemory::CStage* stage;

    puVar1 = (u32*)((u8*)pppCrystal2 + param_2->m_serializedDataOffsets[2] + 0x80);
    stage = (CMemory::CStage*)puVar1[0];
    
    if ((CMemory::CStage*)puVar1[1] != 0) {
        pppHeapUseRate((CMemory::CStage*)puVar1[1]);
        puVar1[1] = 0;
    }
    
    if ((stage != 0) && (*(CMemory::CStage**)stage != 0)) {
        pppHeapUseRate(*(CMemory::CStage**)stage);
        *(u32*)stage = 0;
    }
    
    if (stage != 0) {
        pppHeapUseRate(stage);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8013eb50
 * PAL Size: 924b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCrystal2(pppCrystal2* pppCrystal2, UnkB* param_2, UnkC* param_3)
{
    int* refractionData;
    u32 y;
    u32 x;

    if ((DAT_8032ed70 != 0) || (param_2->m_payload[0] == 0)) {
        return;
    }

    refractionData = (int*)((char*)pppCrystal2 + param_3->m_serializedDataOffsets[2] + 8);
    if (refractionData[0] != 0) {
        return;
    }

    refractionData[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(0x18, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xA8);
    if (refractionData[0] == 0) {
        return;
    }

    int* textureInfo = (int*)refractionData[0];
    const int textureSize = (int)GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
    textureInfo[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(textureSize, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xAD);
    textureInfo[1] = GX_TF_IA8;
    textureInfo[2] = 0x20;
    textureInfo[3] = 0x20;
    textureInfo[4] = 0x100;
    textureInfo[5] = textureSize;

    if (textureInfo[0] == 0) {
        return;
    }

    const float start = -1.0f;
    const float step = 2.0f / (float)(textureInfo[2] - 1);
    float yy = start;

    for (y = 0; y < (u32)textureInfo[3]; ++y) {
        float xx = start;
        const float y2 = yy * yy;

        for (x = 0; x < (u32)textureInfo[2]; ++x) {
            float magnitude = xx * xx + y2;
            if (magnitude < 0.0f) {
                magnitude = 0.0f;
            }

            float normal = 0.0f;
            if (magnitude > 1.0f) {
                normal = 1.0f / sqrtf(magnitude);
            } else if (magnitude > 0.0f) {
                normal = sqrtf(magnitude);
            }

            if (normal > 0.8f) {
                normal = 0.8f;
            }

            const u8 nx = (u8)__cvt_fp2unsigned((double)(xx * normal * 127.0f + 128.0f));
            const u8 ny = (u8)__cvt_fp2unsigned((double)(yy * normal * 127.0f + 128.0f));
            u8* pixel = (u8*)(textureInfo[0] +
                (y >> 2) * (textureInfo[2] & 0x1ffffffcU) * 8 +
                (x & 0x1ffffffc) * 8 +
                ((x & 3) + (y & 3) * 4) * 2);

            pixel[0] = nx;
            pixel[1] = ny;
            xx += step;
        }

        yy += step;
    }

    DCFlushRange((void*)textureInfo[0], textureInfo[5]);
    refractionData[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(0x20, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xB5);

    if (refractionData[1] != 0) {
        GXInitTexObj((GXTexObj*)refractionData[1], (void*)textureInfo[0], (u16)textureInfo[2], (u16)textureInfo[3],
                     GX_TF_IA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8013e694
 * PAL Size: 1212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderCrystal2(pppCrystal2* pppCrystal2, UnkB* param_2, UnkC* param_3)
{
    // TODO: Implement rendering logic
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}
