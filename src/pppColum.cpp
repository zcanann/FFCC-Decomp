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

struct pppColumStepData {
    float m_scaleBase;
    float m_scaleRandom;
    float m_positionBase;
    float m_positionRandom;
    float m_fadeDistance;
    u8 m_drawArg0;
    u8 m_drawArg1;
    u8 m_noiseR;
    u8 m_noiseG;
    u8 m_noiseB;
};

struct pppColumStep {
    u32 m_unk0;
    s32 m_dataValIndex;
    s16 m_initWOrk;
    u16 m_unkA;
    u32 m_stepValue;
    u8 m_blendMode;
    u8 m_count;
    u8 m_unk12;
    u8 m_unk13;
    pppColumStepData m_data;
};

static inline int* GetColumSerializedDataOffsets(void* param) {
    return *(int**)((char*)param + 0xc);
}

static char s_pppColum_cpp_801DB638[] = "pppColum.cpp";

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
unsigned char GetNoise__5CUtilFUc(void*, unsigned int);
void pppCalcFrameShape__FPlRsRsRss(long*, short&, short&, short&, short);

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
void pppRenderColum(pppColum *column, pppColumUnkB *param_2, pppColumUnkC *param_3)
{
    pppColumStep* step = (pppColumStep*)param_2;
    int* serializedDataOffsets = GetColumSerializedDataOffsets(param_3);
    pppColumFrameWork* frameWork = (pppColumFrameWork*)((u8*)column + serializedDataOffsets[3] + 0x80);
    pppColumPositionWork* positionWork = (pppColumPositionWork*)((u8*)column + serializedDataOffsets[2] + 0x80);
    int textureIndex = 0;

    if (step->m_dataValIndex != 0xFFFF) {
        pppShapeSt* shapeSt =
            *(pppShapeSt**)(*(int*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
        void* texture;
        pppCVector color;
        GXColor quadColor;

        texture = shapeSt->GetTexture((long*)shapeSt->m_animData, pppEnvStPtr->m_materialSetPtr, textureIndex);
        if (positionWork->m_alpha != 0) {
            pppColumValue* values = frameWork->m_values;
            Mtx identityMtx;
            Vec cameraDelta;
            Vec center;
            Vec offset;
            Vec shapePosA;
            Vec shapePosB;
            Vec2d uvA;
            Vec2d uvB;
            short shapeFrame;
            u8 alpha = positionWork->m_alpha;
            u8* stepColor = (u8*)&step->m_stepValue;
            float lengthXY;
            float segmentStep;
            float dist;
            float drawScale = 0.0f;

            PSMTXIdentity(identityMtx);
            cameraDelta.x = ppvCameraMatrix0[0][3] - positionWork->m_position.x;
            cameraDelta.y = ppvCameraMatrix0[1][3] - positionWork->m_position.y;
            cameraDelta.z = ppvCameraMatrix0[2][3] + positionWork->m_position.z;

            lengthXY = sqrtf(cameraDelta.x * cameraDelta.x + cameraDelta.y * cameraDelta.y);
            if (lengthXY > 0.0f) {
                PSVECScale(&cameraDelta, &cameraDelta, 1.0f / lengthXY);
            }
            segmentStep = (150.0f * lengthXY) / ((float)step->m_count - 1.0f);

            pppInitBlendMode();
            for (int i = 0; i < step->m_count; i++) {
                center.x =
                    positionWork->m_position.x +
                    (segmentStep * values->m_positionScale) * (cameraDelta.x * (float)(i + 1));
                center.y =
                    positionWork->m_position.y +
                    (segmentStep * values->m_positionScale) * (cameraDelta.y * (float)(i + 1));
                center.z = 0.0f;

                PSVECSubtract(&center, &positionWork->m_position, &offset);
                dist = PSVECMag(&offset);

                color.m_rgba[3] = alpha;
                if (dist < step->m_data.m_fadeDistance) {
                    float alphaScale = dist / step->m_data.m_fadeDistance;

                    if (alphaScale > 0.0f) {
                        color.m_rgba[3] = (u8)((float)color.m_rgba[3] * alphaScale);
                    }
                }
                color.m_rgba[0] = stepColor[0] + values->m_colorR;
                color.m_rgba[1] = stepColor[1] + values->m_colorG;
                color.m_rgba[2] = stepColor[2] + values->m_colorB;

                pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
                    &color, NULL, 0.0f, step->m_data.m_drawArg1, step->m_data.m_drawArg0,
                    step->m_blendMode, 0, 0, 1, 0);

                BeginQuadEnv__5CUtilFv(&gUtil);
                SetVtxFmt_POS_CLR_TEX__5CUtilFv(&gUtil);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
                _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                GXLoadTexObj((GXTexObj*)((char*)texture + 0x28), GX_TEXMAP0);
                pppSetBlendMode(step->m_blendMode);

                drawScale += values->m_scaleStep;
                shapeFrame = *(short*)((u8*)shapeSt->m_animData + (frameWork->m_shapeB * 8) + 0x10);
                for (int j = 0; j < *(short*)((u8*)shapeSt->m_animData + shapeFrame + 2); j++) {
                    pppGetShapePos__FPlsR3VecR3Veci(
                        (long*)shapeSt->m_animData, frameWork->m_shapeB, shapePosA, shapePosB, j);
                    pppGetShapeUV__FPlsR5Vec2dR5Vec2di(
                        (long*)shapeSt->m_animData, frameWork->m_shapeB, uvA, uvB, j);

                    PSVECScale(&shapePosA, &shapePosA, drawScale);
                    PSVECScale(&shapePosB, &shapePosB, drawScale);
                    PSVECAdd(&shapePosA, &center, &shapePosA);
                    PSVECAdd(&shapePosB, &center, &shapePosB);

                    quadColor.r = color.m_rgba[0];
                    quadColor.g = color.m_rgba[1];
                    quadColor.b = color.m_rgba[2];
                    quadColor.a = color.m_rgba[3];

                    RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d(
                        &gUtil, &shapePosA, &shapePosB, quadColor, &uvA, &uvB);
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
    pppColumStep* step = (pppColumStep*)param_2;
    int* serializedDataOffsets;
    pppColumValue* values;
    pppColumFrameWork* work;
    int i;

    if (gPppCalcDisabled == 0) {
        serializedDataOffsets = GetColumSerializedDataOffsets(param_3);
        work = (pppColumFrameWork*)((char*)column + 0x80 + serializedDataOffsets[3]);
        if (work->m_values == 0) {
            work->m_values = (pppColumValue*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                (unsigned long)step->m_count * 0xc, pppEnvStPtr->m_stagePtr,
                s_pppColum_cpp_801DB638, 0x7d);

            values = work->m_values;
            for (i = 0; i < (int)(unsigned int)step->m_count; i++) {
                values->m_scaleStep = Math.RandF(step->m_data.m_scaleRandom);
                values->m_scaleStep = values->m_scaleStep + step->m_data.m_scaleBase;
                values->m_positionScale = Math.RandF(step->m_data.m_positionRandom);
                values->m_positionScale = values->m_positionScale + step->m_data.m_positionBase;
                values->m_colorR =
                    GetNoise__5CUtilFUc(&gUtil, step->m_data.m_noiseR);
                values->m_colorG =
                    GetNoise__5CUtilFUc(&gUtil, step->m_data.m_noiseG);
                values->m_colorB =
                    GetNoise__5CUtilFUc(&gUtil, step->m_data.m_noiseB);
                values++;
            }
        }

        if (step->m_dataValIndex != 0xFFFF) {
            long* animData =
                **(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
            pppCalcFrameShape__FPlRsRsRss(
                animData,
                work->m_shapeA, work->m_shapeB, work->m_shapeC, step->m_initWOrk);
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
void pppConstructColum(pppColum *column, pppColumUnkC *param_2)
{
    int* serializedDataOffsets = GetColumSerializedDataOffsets(param_2);
    unsigned short *puVar1 = (unsigned short *)((char*)column + 0x80 + serializedDataOffsets[3]);
    puVar1[2] = 0;
    puVar1[1] = 0;
    *puVar1 = 0;
    *(unsigned int *)(puVar1 + 4) = 0;
}
