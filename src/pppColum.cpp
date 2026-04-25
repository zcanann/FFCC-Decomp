#include "ffcc/pppColum.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/util.h"
#include "ffcc/pppShape.h"

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

union ColumFloatBits {
    float value;
    u32 bits;
};

static const char s_pppColum_cpp_801DB638[] = "pppColum.cpp";

extern unsigned long __float_nan[];
extern float FLOAT_80331078;
extern float FLOAT_8033107C;
extern float FLOAT_80331080;
extern float FLOAT_80331084;
extern double DOUBLE_80331088;
extern double DOUBLE_80331090;
extern double DOUBLE_80331098;
extern float FLOAT_803310A0;
extern float FLOAT_803310A4;
extern float FLOAT_803310A8;
extern double DOUBLE_803310B0;
extern double DOUBLE_803310B8;

extern "C" {
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
}

static inline int ColumFpClassify(float value)
{
    ColumFloatBits bits;

    bits.value = value;
    switch (bits.bits & 0x7F800000) {
    case 0x7F800000:
        if ((bits.bits & 0x007FFFFF) != 0) {
            return 1;
        }
        return 2;

    case 0:
        if ((bits.bits & 0x007FFFFF) != 0) {
            return 5;
        }
        return 3;
    }

    return 4;
}

static inline float ColumSqrtPositive(float value)
{
    double guess = __frsqrte((double)value);

    guess = DOUBLE_80331088 * guess * (DOUBLE_80331090 - guess * guess * value);
    guess = DOUBLE_80331088 * guess * (DOUBLE_80331090 - guess * guess * value);
    guess = DOUBLE_80331088 * guess * (DOUBLE_80331090 - guess * guess * value);

    return (float)(value * guess);
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
    pppColumFrameWork* frameWork = (pppColumFrameWork*)(objBytes + serializedDataOffsets[3] + 0x80);
    pppColumPositionWork* positionWork =
        (pppColumPositionWork*)(objBytes + serializedDataOffsets[2] + 0x80);
    pppCVECTOR color;
    int textureIndex = 0;

    if (param_2->m_dataValIndex != 0xFFFF) {
        pppShapeSt* shapeSt =
            *(pppShapeSt**)(*(int*)&pppEnvStPtr->m_particleColors[0] + param_2->m_dataValIndex * 4);
        int texture;

        texture = (int)shapeSt->GetTexture((long*)shapeSt->m_animData, pppEnvStPtr->m_materialSetPtr, textureIndex);
        if (positionWork->m_alpha != 0) {
            Vec cameraDelta;
            Vec center;
            Vec offset;
            Vec shapePosA;
            Vec shapePosB;
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
            baseX = positionWork->m_position.x;
            baseY = positionWork->m_position.y;
            cameraDelta.x = FLOAT_80331078 - baseX;
            cameraDelta.y = FLOAT_8033107C - baseY;
            cameraDelta.z = FLOAT_80331080 + positionWork->m_position.z;

            lengthXY = cameraDelta.x * cameraDelta.x + cameraDelta.y * cameraDelta.y;
            if (lengthXY > FLOAT_80331084) {
                lengthXY = ColumSqrtPositive(lengthXY);
            } else if ((double)lengthXY < DOUBLE_80331098) {
                lengthXY = *(float*)__float_nan;
            } else if (ColumFpClassify(lengthXY) == 1) {
                lengthXY = *(float*)__float_nan;
            }
            if (FLOAT_803310A0 < lengthXY) {
                PSVECScale(&cameraDelta, &cameraDelta, FLOAT_803310A4 / lengthXY);
            }

            pppInitBlendMode();
            values = frameWork->m_values;
            segmentStep =
                (FLOAT_803310A8 * lengthXY) / (float)((double)param_2->m_count - DOUBLE_803310B0);
            drawScale = (float)DOUBLE_803310B8;

            for (int i = 0; i < param_2->m_count; i++) {
                float positionScale = segmentStep * values->m_positionScale;
                float index = (float)(i + 1);
                u8 alpha = positionWork->m_alpha;

                center.z = FLOAT_80331084;
                center.x = baseX + positionScale * (cameraDelta.x * index);
                center.y = baseY + positionScale * (cameraDelta.y * index);

                PSVECSubtract(&center, &positionWork->m_position, &offset);
                {
                    float dist = PSVECMag(&offset);
                    float fadeAmount = dist / *(float*)(param_2->m_payload + 0x10);

                    if (dist < *(float*)(param_2->m_payload + 0x10) && fadeAmount > FLOAT_80331084) {
                        alpha = (u8)((float)alpha * fadeAmount);
                    }
                }
                color.rgba[0] = *((u8*)&param_2->m_stepValue + 0) + values->m_colorR;
                color.rgba[1] = *((u8*)&param_2->m_stepValue + 1) + values->m_colorG;
                color.rgba[2] = *((u8*)&param_2->m_stepValue + 2) + values->m_colorB;
                color.rgba[3] = alpha;

                pppSetDrawEnv(
                    &color, (pppFMATRIX*)0, 0.0f, (u8)param_2->m_payload[0x15],
                    (u8)param_2->m_payload[0x14],
                    param_2->m_arg3, 0, 0, 1, 0);

                gUtil.BeginQuadEnv();
                gUtil.SetVtxFmt_POS_CLR_TEX();
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
                _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                GXLoadTexObj((GXTexObj*)(texture + 0x28), GX_TEXMAP0);
                pppSetBlendMode(param_2->m_arg3);

                drawScale += values->m_scaleStep;
                u8* frameData =
                    (u8*)shapeSt->m_animData +
                    *(short*)((u8*)shapeSt->m_animData + (frameWork->m_shapeB * 8) + 0x10);
                for (int j = 0; j < *(short*)(frameData + 2); j++) {
                    pppGetShapePos((long*)shapeSt->m_animData, frameWork->m_shapeB, shapePosA,
                                   shapePosB, j);
                    pppGetShapeUV((long*)shapeSt->m_animData, frameWork->m_shapeB, uvA, uvB, j);

                    PSVECScale(&shapePosA, &shapePosA, drawScale);
                    PSVECScale(&shapePosB, &shapePosB, drawScale);
                    PSVECAdd(&shapePosA, &center, &shapePosA);
                    PSVECAdd(&shapePosB, &center, &shapePosB);

                    gUtil.RenderQuad(shapePosA, shapePosB, *(GXColor*)color.rgba, &uvA, &uvB);
                }

                gUtil.EndQuadEnv();
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
            work->m_values = (pppColumValue*)pppMemAlloc(
                (unsigned long)param_2->m_count * 0xc, pppEnvStPtr->m_stagePtr,
                const_cast<char*>(s_pppColum_cpp_801DB638), 0x7d);

            values = work->m_values;
            for (i = 0; i < (int)(unsigned int)param_2->m_count; i++) {
                values->m_scaleStep = Math.RandF(*(float*)(param_2->m_payload + 4));
                values->m_scaleStep = values->m_scaleStep + *(float*)(param_2->m_payload + 0);
                values->m_positionScale = Math.RandF(*(float*)(param_2->m_payload + 0xc));
                values->m_positionScale = values->m_positionScale + *(float*)(param_2->m_payload + 8);
                values->m_colorR = gUtil.GetNoise(*(unsigned char*)(param_2->m_payload + 0x16));
                values->m_colorG = gUtil.GetNoise(*(unsigned char*)(param_2->m_payload + 0x17));
                values->m_colorB = gUtil.GetNoise(*(unsigned char*)(param_2->m_payload + 0x18));
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
    pppColumFrameWork* work = (pppColumFrameWork*)((char*)column + 0x80 + serializedDataOffsets[3]);

    if (work->m_values != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_values);
        work->m_values = 0;
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
    pppColumFrameWork* work = (pppColumFrameWork*)((char*)column + 0x80 + serializedDataOffsets[3]);
    work->m_shapeC = 0;
    work->m_shapeB = 0;
    work->m_shapeA = 0;
    work->m_values = 0;
}
