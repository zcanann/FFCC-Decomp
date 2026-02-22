#include "ffcc/pppColum.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/util.h"

#include <math.h>

struct Vec2d {
    float x;
    float y;
};

static inline int* GetColumSerializedDataOffsets(void* param) {
    return *(int**)((char*)param + 0xc);
}

extern int lbl_8032ED70;
extern CMath Math;
extern void* DAT_8032ec70;

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
float RandF__5CMathFf(float, CMath*);
unsigned char GetNoise__5CUtilFUc(void*, unsigned int);
void pppCalcFrameShape__FPlRsRsRss(long*, short&, short&, short&, short);
void pppInitBlendMode__Fv(void);
void pppSetBlendMode__FUc(unsigned char);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, unsigned char,
                                                                unsigned char, unsigned char, unsigned char,
                                                                unsigned char, unsigned char, unsigned char);
void BeginQuadEnv__5CUtilFv(void*);
void EndQuadEnv__5CUtilFv(void*);
void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
void pppGetShapePos__FPlsR3VecR3Veci(long*, short, Vec&, Vec&, int);
void pppGetShapeUV__FPlsR5Vec2dR5Vec2di(long*, short, Vec2d&, Vec2d&, int);
void RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d(void*, Vec*, Vec*, GXColor, Vec2d*, Vec2d*);
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
    int* serializedDataOffsets = GetColumSerializedDataOffsets(param_3);
    int iVar7 = serializedDataOffsets[3];
    int iVar5 = serializedDataOffsets[2];

    if (param_2->m_dataValIndex != 0xffff) {
        pppShapeSt* shapeSt = *(pppShapeSt**)(*(int*)&pppEnvStPtr->m_particleColors[0] + param_2->m_dataValIndex * 4);
        int textureIndex = 0;
        void* texture;
        u8 alpha = *((u8*)column + 0xb2 + iVar5);

        texture = shapeSt->GetTexture((long*)shapeSt->m_animData, pppEnvStPtr->m_materialSetPtr, textureIndex);
        if (alpha != 0) {
            float* values = *(float**)((u8*)column + 0x88 + iVar7);
            u8 count = *((u8*)&param_2->m_arg3 + 1);
            Mtx identityMtx;
            Vec basePos;
            Vec cameraDelta;
            short shapeFrame;
            float lengthXY;
            float fadeRange = *(float*)(param_2->m_payload + 0x10);
            float segmentStep;
            double drawScale = 0.0;

            PSMTXIdentity(identityMtx);
            basePos.x = *(float*)((u8*)column + 0x90 + iVar5);
            basePos.y = *(float*)((u8*)column + 0x94 + iVar5);
            basePos.z = *(float*)((u8*)column + 0x98 + iVar5);

            cameraDelta.x = ppvCameraMatrix0[0][3] - basePos.x;
            cameraDelta.y = ppvCameraMatrix0[1][3] - basePos.y;
            cameraDelta.z = ppvCameraMatrix0[2][3] + basePos.z;

            lengthXY = sqrtf(cameraDelta.x * cameraDelta.x + cameraDelta.y * cameraDelta.y);
            if (lengthXY > 0.0f) {
                PSVECScale(&cameraDelta, &cameraDelta, 1.0f / lengthXY);
            }
            segmentStep = (150.0f * lengthXY) / ((float)count - 1.0f);

            pppInitBlendMode__Fv();
            for (int i = 0; i < count; i++) {
                Vec center;
                Vec offset;
                Vec shapePosA;
                Vec shapePosB;
                Vec2d uvA;
                Vec2d uvB;
                pppCVector color;
                float dist;
                float fadeAmount;

                center.x = basePos.x + ((cameraDelta.x * (float)(i + 1)) * segmentStep) * values[1];
                center.y = basePos.y + ((cameraDelta.y * (float)(i + 1)) * segmentStep) * values[1];
                center.z = 0.0f;

                PSVECSubtract(&center, &basePos, &offset);
                dist = PSVECMag(&offset);

                color.m_rgba[3] = alpha;
                fadeAmount = dist / fadeRange;
                if (dist < fadeRange && fadeAmount > 0.0f) {
                    color.m_rgba[3] = (u8)((float)color.m_rgba[3] * fadeAmount);
                }
                color.m_rgba[0] = *((u8*)&param_2->m_stepValue + 0) + *((u8*)values + 8);
                color.m_rgba[1] = *((u8*)&param_2->m_stepValue + 1) + *((u8*)values + 9);
                color.m_rgba[2] = *((u8*)&param_2->m_stepValue + 2) + *((u8*)values + 10);

                pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
                    &color, NULL, 0.0f, (u8)param_2->m_payload[0x15], (u8)param_2->m_payload[0x14],
                    param_2->m_arg3, 0, 0, 1, 0);

                BeginQuadEnv__5CUtilFv(&DAT_8032ec70);
                SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
                _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                GXLoadTexObj((GXTexObj*)((char*)texture + 0x28), GX_TEXMAP0);
                pppSetBlendMode__FUc(param_2->m_arg3);

                drawScale += values[0];
                shapeFrame = *(short*)((u8*)shapeSt->m_animData + (*(u16*)((u8*)column + 0x82 + iVar7) * 8) + 0x10);
                for (int j = 0; j < *(short*)((u8*)shapeSt->m_animData + shapeFrame + 2); j++) {
                    pppGetShapePos__FPlsR3VecR3Veci((long*)shapeSt->m_animData,
                                                    *(short*)((u8*)column + 0x82 + iVar7), shapePosA, shapePosB, j);
                    pppGetShapeUV__FPlsR5Vec2dR5Vec2di((long*)shapeSt->m_animData,
                                                       *(short*)((u8*)column + 0x82 + iVar7), uvA, uvB, j);

                    PSVECScale(&shapePosA, &shapePosA, (float)drawScale);
                    PSVECScale(&shapePosB, &shapePosB, (float)drawScale);
                    PSVECAdd(&shapePosA, &center, &shapePosA);
                    PSVECAdd(&shapePosB, &center, &shapePosB);

                    GXColor quadColor;
                    quadColor.r = color.m_rgba[0];
                    quadColor.g = color.m_rgba[1];
                    quadColor.b = color.m_rgba[2];
                    quadColor.a = color.m_rgba[3];

                    RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d(
                        &DAT_8032ec70, &shapePosA, &shapePosB, quadColor, &uvA, &uvB);
                }

                EndQuadEnv__5CUtilFv(&DAT_8032ec70);
                pppSetBlendMode__FUc(0);
                values += 3;
            }
        }
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
    int i;
    int* serializedDataOffsets;
    unsigned char* work;

    if (lbl_8032ED70 != 0) {
        return;
    }

    serializedDataOffsets = GetColumSerializedDataOffsets(param_3);
    work = (unsigned char*)((char*)column + 0x80 + serializedDataOffsets[3]);

    if (*(void**)(work + 8) == 0) {
        unsigned char count = *((unsigned char*)&param_2->m_arg3 + 1);
        float* values = (float*)pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(count * 0xc),
                                                                       pppEnvStPtr->m_stagePtr,
                                                                       (char*)"pppColum.cpp", 0x7d);

        *(void**)(work + 8) = values;
        for (i = 0; i < (int)count; i++) {
            values[0] = RandF__5CMathFf(*(float*)(param_2->m_payload + 4), &Math);
            values[0] += *(float*)param_2->m_payload;
            values[1] = RandF__5CMathFf(*(float*)(param_2->m_payload + 0xc), &Math);
            values[1] += *(float*)(param_2->m_payload + 8);
            ((unsigned char*)values)[8] =
                GetNoise__5CUtilFUc(&DAT_8032ec70, (unsigned char)param_2->m_payload[0x16]);
            ((unsigned char*)values)[9] =
                GetNoise__5CUtilFUc(&DAT_8032ec70, (unsigned char)param_2->m_payload[0x17]);
            ((unsigned char*)values)[10] =
                GetNoise__5CUtilFUc(&DAT_8032ec70, (unsigned char)param_2->m_payload[0x18]);
            values += 3;
        }
    }

    if (param_2->m_dataValIndex != 0xffff) {
        long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + param_2->m_dataValIndex * 4);
        short& shapeA = *(short*)(work + 0);
        short& shapeB = *(short*)(work + 2);
        short& shapeC = *(short*)(work + 4);

        pppCalcFrameShape__FPlRsRsRss(shapeTable, shapeA, shapeB, shapeC, (short)param_2->m_initWOrk);
    }
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
    int* serializedDataOffsets = GetColumSerializedDataOffsets(param_2);
    char* work = (char*)column + 0x80 + serializedDataOffsets[3];

    if (*(CMemory::CStage**)(work + 8) != 0) {
        pppHeapUseRate(*(CMemory::CStage**)(work + 8));
        *(void**)(work + 8) = 0;
    }
}

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
    int* serializedDataOffsets = GetColumSerializedDataOffsets(param_2);
    unsigned short *puVar1 = (unsigned short *)((char*)column + 0x80 + serializedDataOffsets[3]);
    puVar1[2] = 0;
    puVar1[1] = 0;
    *puVar1 = 0;
    *(unsigned int *)(puVar1 + 4) = 0;
}
