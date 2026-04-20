#include "ffcc/pppColum.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/util.h"
#include "ffcc/pppShape.h"

#include <math.h>

struct Vec2d {
    float x;
    float y;
};

struct pppColumValue {
    float m_scaleStep;
    float m_positionScale;
    u8 m_colorR;
    u8 m_colorG;
    u8 m_colorB;
    u8 _padB;
};

struct pppColumFrameWork {
    s16 m_shapeA;
    s16 m_shapeB;
    s16 m_shapeC;
    s16 _pad6;
    pppColumValue* m_values;
};

struct pppColumPositionWork {
    u8 _pad0[0x10];
    Vec m_position;
    u8 _pad1[0x16];
    u8 m_alpha;
};

static const char s_pppColum_cpp_801DB638[] = "pppColum.cpp";

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
unsigned char GetNoise__5CUtilFUc(void*, unsigned int);

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
void RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d(void*, Vec, Vec, GXColor, Vec2d*, Vec2d*);
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
void pppRenderColum(pppColum *column, pppColumUnkB *param_2, pppColumUnkC *param_3)
{
    s32* serializedDataOffsets = param_3->m_serializedDataOffsets;
    u8* objBytes = (u8*)column;
    u8* frameBase = objBytes + serializedDataOffsets[3] + 0x80;
    u8* positionBase = objBytes + serializedDataOffsets[2] + 0x80;
    int textureIndex = 0;

    if (param_2->m_dataValIndex != 0xFFFF) {
        pppShapeSt* shapeSt =
            *(pppShapeSt**)(*(int*)&pppEnvStPtr->m_particleColors[0] + param_2->m_dataValIndex * 4);
        pppCVector color;
        int texture;

        texture = (int)shapeSt->GetTexture((long*)shapeSt->m_animData, pppEnvStPtr->m_materialSetPtr, textureIndex);
        if (positionBase[0x32] != 0) {
            Vec shapePosA;
            Vec shapePosB;
            Vec center;
            Vec offset;
            Vec cameraDelta;
            Mtx identityMtx;
            Vec2d uvA;
            Vec2d uvB;
            float baseX;
            float baseY;
            float lengthXY;
            float segmentStep;
            float drawScale;
            pppColumValue* values;

            PSMTXIdentity(identityMtx);
            baseX = *(float*)(positionBase + 0x10);
            baseY = *(float*)(positionBase + 0x14);
            cameraDelta.x = ppvCameraMatrix0[0][3] - baseX;
            cameraDelta.y = ppvCameraMatrix0[1][3] - baseY;
            cameraDelta.z = ppvCameraMatrix0[2][3] + *(float*)(positionBase + 0x18);

            lengthXY = sqrtf(cameraDelta.x * cameraDelta.x + cameraDelta.y * cameraDelta.y);
            if (0.0f < lengthXY) {
                PSVECScale(&cameraDelta, &cameraDelta, 1.0f / lengthXY);
            }

            pppInitBlendMode();
            values = *(pppColumValue**)(frameBase + 8);
            segmentStep = (150.0f * lengthXY) / ((float)param_2->m_count - 1.0f);
            drawScale = 0.0f;

            for (int i = 0; i < param_2->m_count; i++) {
                float positionScale = segmentStep * values->m_positionScale;
                float index = (float)(i + 1);
                u8 alpha = positionBase[0x32];

                center.z = 0.0f;
                center.x = baseX + positionScale * (cameraDelta.x * index);
                center.y = baseY + positionScale * (cameraDelta.y * index);

                PSVECSubtract(&center, (Vec*)(positionBase + 0x10), &offset);
                {
                    float dist = PSVECMag(&offset);
                    float fadeAmount = dist / *(float*)(param_2->m_payload + 0x10);

                    if (dist < *(float*)(param_2->m_payload + 0x10) && 0.0f < fadeAmount) {
                        alpha = (u8)((float)alpha * fadeAmount);
                    }
                }
                color.m_rgba[0] = *((u8*)&param_2->m_stepValue + 0) + values->m_colorR;
                color.m_rgba[1] = *((u8*)&param_2->m_stepValue + 1) + values->m_colorG;
                color.m_rgba[2] = *((u8*)&param_2->m_stepValue + 2) + values->m_colorB;
                color.m_rgba[3] = alpha;

                pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
                    &color, NULL, 0.0f, (u8)param_2->m_payload[0x15], (u8)param_2->m_payload[0x14],
                    param_2->m_arg3, 0, 0, 1, 0);

                BeginQuadEnv__5CUtilFv(&gUtil);
                SetVtxFmt_POS_CLR_TEX__5CUtilFv(&gUtil);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
                _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                GXLoadTexObj((GXTexObj*)(texture + 0x28), GX_TEXMAP0);
                pppSetBlendMode(param_2->m_arg3);

                drawScale += values->m_scaleStep;
                u8* frameData = (u8*)shapeSt->m_animData + *(short*)((u8*)shapeSt->m_animData + (*(s16*)(frameBase + 2) * 8) + 0x10);
                for (int j = 0; j < *(short*)(frameData + 2); j++) {
                    pppGetShapePos__FPlsR3VecR3Veci((long*)shapeSt->m_animData, *(s16*)(frameBase + 2), shapePosA, shapePosB, j);
                    pppGetShapeUV__FPlsR5Vec2dR5Vec2di((long*)shapeSt->m_animData, *(s16*)(frameBase + 2), uvA, uvB, j);

                    PSVECScale(&shapePosA, &shapePosA, drawScale);
                    PSVECScale(&shapePosB, &shapePosB, drawScale);
                    PSVECAdd(&shapePosA, &center, &shapePosA);
                    PSVECAdd(&shapePosB, &center, &shapePosB);

                    RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d(
                        &gUtil, shapePosA, shapePosB, *(GXColor*)color.m_rgba, &uvA, &uvB);
                }

                EndQuadEnv__5CUtilFv(&gUtil);
                pppSetBlendMode(0);
                values++;
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
void pppFrameColum(pppColum *column, pppColumUnkB *param_2, pppColumUnkC *param_3)
{
    s32* serializedDataOffsets;
    pppColumValue* values;
    pppColumFrameWork* work;
    int i;

    if (gPppCalcDisabled == 0) {
        serializedDataOffsets = param_3->m_serializedDataOffsets;
        work = (pppColumFrameWork*)((char*)column + 0x80 + serializedDataOffsets[3]);
        if (work->m_values == 0) {
            work->m_values = (pppColumValue*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                (unsigned long)param_2->m_count * 0xc, pppEnvStPtr->m_stagePtr,
                const_cast<char*>(s_pppColum_cpp_801DB638), 0x7d);

            values = work->m_values;
            for (i = 0; i < (int)(unsigned int)param_2->m_count; i++) {
                values->m_scaleStep = Math.RandF(*(float*)(param_2->m_payload + 4));
                values->m_scaleStep = values->m_scaleStep + *(float*)(param_2->m_payload + 0);
                values->m_positionScale = Math.RandF(*(float*)(param_2->m_payload + 0xc));
                values->m_positionScale = values->m_positionScale + *(float*)(param_2->m_payload + 8);
                values->m_colorR =
                    GetNoise__5CUtilFUc(&gUtil, *(unsigned char*)(param_2->m_payload + 0x16));
                values->m_colorG =
                    GetNoise__5CUtilFUc(&gUtil, *(unsigned char*)(param_2->m_payload + 0x17));
                values->m_colorB =
                    GetNoise__5CUtilFUc(&gUtil, *(unsigned char*)(param_2->m_payload + 0x18));
                values++;
            }
        }

        if (param_2->m_dataValIndex != 0xFFFF) {
            long* animData =
                **(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + param_2->m_dataValIndex * 4);
            pppCalcFrameShape(
                animData,
                work->m_shapeA, work->m_shapeB, work->m_shapeC, param_2->m_initWOrk);
        }
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
void pppDestructColum(pppColum *column, pppColumUnkC *param_2)
{
    s32* serializedDataOffsets = param_2->m_serializedDataOffsets;
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
void pppConstructColum(pppColum *column, pppColumUnkC *param_2)
{
    s32* serializedDataOffsets = param_2->m_serializedDataOffsets;
    unsigned short *puVar1 = (unsigned short *)((char*)column + 0x80 + serializedDataOffsets[3]);
    puVar1[2] = 0;
    puVar1[1] = 0;
    *puVar1 = 0;
    *(unsigned int *)(puVar1 + 4) = 0;
}
