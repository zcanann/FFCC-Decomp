#include "ffcc/pppColum.h"
#include "global.h"
#include "ffcc/gxfunc.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppVec.h"
#include "ffcc/util.h"
#include "ffcc/pppShape.h"
#include "ffcc/textureman.h"

#include <math.h>
#include <stddef.h>

STATIC_ASSERT(sizeof(pppColumValue) == 0x0C);
STATIC_ASSERT(offsetof(pppColumFrameWork, m_values) == 0x08);
STATIC_ASSERT(sizeof(pppColumFrameWork) == 0x0C);
STATIC_ASSERT(offsetof(pppColumPositionWork, m_position) == 0x10);
STATIC_ASSERT(offsetof(pppColumPositionWork, m_alpha) == 0x32);
STATIC_ASSERT(sizeof(pppColumDataOffsets) == 0x10);
STATIC_ASSERT(offsetof(pppColumDataOffsets, m_positionWorkOffset) == 0x08);
STATIC_ASSERT(offsetof(pppColumDataOffsets, m_frameWorkOffset) == 0x0C);

static const char s_pppColum_cpp[] = "pppColum.cpp";

static inline pppColumDataOffsets* GetColumDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppColumDataOffsets*>(ctrl->m_serializedDataOffsets);
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
void pppRenderColum(pppColum *column, pppColumStep *param_2, _pppCtrlTable *param_3)
{
    pppColumDataOffsets* serializedDataOffsets = GetColumDataOffsets(param_3);
    pppColumValue* values;
    pppColumFrameWork* frameWork = (pppColumFrameWork*)(column->m_workArea + serializedDataOffsets->m_frameWorkOffset);
    pppColumPositionWork* positionWork =
        (pppColumPositionWork*)(column->m_workArea + serializedDataOffsets->m_positionWorkOffset);
    int textureIndex = 0;
    pppCVECTOR color;

    if (param_2->m_dataValIndex != 0xFFFF) {
        pppShapeSt* shapeSt = ppvEnv->m_shapeTablePtr[param_2->m_dataValIndex];
        CTexture* texture;

        texture = shapeSt->GetTexture((long*)shapeSt->m_animData, ppvEnv->m_materialSetPtr, textureIndex);
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
            float baseZ;
            float lengthXY;
            float segmentStep;
            float drawScale;
            float deltaY;
            float deltaX;
            float deltaX2;
            float deltaY2;

            PSMTXIdentity(identityMtx);
            baseX = positionWork->m_position.x;
            baseY = positionWork->m_position.y;
            baseZ = positionWork->m_position.z;
            deltaX = 320.0f - baseX;
            deltaY = 224.0f - baseY;
            cameraDelta.x = deltaX;
            cameraDelta.y = deltaY;
            cameraDelta.z = -0.5f + baseZ;

            deltaX2 = deltaX * deltaX;
            deltaY2 = deltaY * deltaY;
            lengthXY = sqrtf(deltaX2 + deltaY2);
            drawScale = 0.0f;
            if (lengthXY > 0.000001f) {
                PSVECScale(&cameraDelta, &cameraDelta, 1.0f / lengthXY);
            }

            pppInitBlendMode();
            values = frameWork->m_values;
            segmentStep =
                (2.0f * lengthXY) / (float)param_2->m_count;

            for (int i = 0; i < param_2->m_count; i++) {
                float positionScale = segmentStep * values->m_positionScale;
                float offsetX;
                float offsetY;
                u8 alpha;

                center.z = 0.0f;
                offsetX = cameraDelta.x * (float)(i + 1);
                center.x = baseX + positionScale * offsetX;
                offsetY = cameraDelta.y * (float)(i + 1);
                center.y = baseY + positionScale * offsetY;

                PSVECSubtract(&center, &positionWork->m_position, &offset);
                {
                    float dist = PSVECMag(&offset);
                    float fadeAmount = dist / param_2->m_colum.m_fadeDistance;
                    u32 baseAlpha = positionWork->m_alpha;

                    alpha = (u8)baseAlpha;
                    if (dist < param_2->m_colum.m_fadeDistance && fadeAmount > 0.0f) {
                        alpha = (u8)((float)baseAlpha * fadeAmount);
                    }
                }
                color.rgba[0] = param_2->m_baseColor[0] + values->m_colorR;
                color.rgba[1] = param_2->m_baseColor[1] + values->m_colorG;
                color.rgba[2] = param_2->m_baseColor[2] + values->m_colorB;
                color.rgba[3] = alpha;

                pppSetDrawEnv(
                    &color, (pppFMATRIX*)0, 0.0f, param_2->m_colum.m_drawEnvColor1,
                    param_2->m_colum.m_drawEnvColor0,
                    param_2->m_arg3, 0, 0, 1, 0);

                gUtil.BeginQuadEnv();
                gUtil.SetVtxFmt_POS_CLR_TEX();
                _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                GXLoadTexObj(&texture->m_texObj, GX_TEXMAP0);
                pppSetBlendMode(param_2->m_arg3);

                drawScale += values->m_scaleStep;
                pppShapeAnimData* shapeAnim = static_cast<pppShapeAnimData*>(shapeSt->m_animData);
                tagOAN3_SHAPE* frameData =
                    (tagOAN3_SHAPE*)((u8*)shapeAnim + shapeAnim->m_frames[frameWork->m_shapeB].m_shapeOffset);
                for (int j = 0; j < frameData->m_shapeCount; j++) {
                    pppGetShapePos((long*)shapeSt->m_animData, frameWork->m_shapeB, shapePosA,
                                   shapePosB, j);
                    pppGetShapeUV((long*)shapeSt->m_animData, frameWork->m_shapeB, uvA, uvB, j);

                    PSVECScale(&shapePosA, &shapePosA, (float)drawScale);
                    PSVECScale(&shapePosB, &shapePosB, (float)drawScale);
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
void pppFrameColum(pppColum *column, pppColumStep *param_2, _pppCtrlTable *param_3)
{
        pppColumDataOffsets* serializedDataOffsets;
    pppColumValue* values;
    pppColumFrameWork* work;
    int i;

    if (ppvUserStopPartF == 0) {
        serializedDataOffsets = GetColumDataOffsets(param_3);
        work = (pppColumFrameWork*)(column->m_workArea + serializedDataOffsets->m_frameWorkOffset);
        if (work->m_values == 0) {
            work->m_values = (pppColumValue*)pppMemAlloc(
                (unsigned long)param_2->m_count * 0xc, ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppColum_cpp), 0x7d);

            values = work->m_values;
            for (i = 0; i < (int)(unsigned int)param_2->m_count; i++) {
                values->m_scaleStep = Math.RandF(param_2->m_colum.m_scaleStepRange);
                values->m_scaleStep = values->m_scaleStep + param_2->m_colum.m_scaleStepBase;
                values->m_positionScale = Math.RandF(param_2->m_colum.m_positionRange);
                values->m_positionScale = values->m_positionScale + param_2->m_colum.m_positionBase;
                values->m_colorR = gUtil.GetNoise(param_2->m_colum.m_noiseR);
                values->m_colorG = gUtil.GetNoise(param_2->m_colum.m_noiseG);
                values->m_colorB = gUtil.GetNoise(param_2->m_colum.m_noiseB);
                values++;
            }
        }

        if (param_2->m_dataValIndex != 0xFFFF) {
            pppShapeSt* shapeSt = ppvEnv->m_shapeTablePtr[param_2->m_dataValIndex];
            long* animData = static_cast<long*>(shapeSt->m_animData);
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
void pppDestructColum(pppColum *column, _pppCtrlTable *param_2)
{
    pppColumDataOffsets* serializedDataOffsets = GetColumDataOffsets(param_2);
    pppColumFrameWork* work = (pppColumFrameWork*)(column->m_workArea + serializedDataOffsets->m_frameWorkOffset);

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
void pppConstructColum(pppColum *column, _pppCtrlTable *param_2)
{
    pppColumDataOffsets* serializedDataOffsets = GetColumDataOffsets(param_2);
    pppColumFrameWork* work = (pppColumFrameWork*)(column->m_workArea + serializedDataOffsets->m_frameWorkOffset);
    work->m_shapeC = 0;
    work->m_shapeB = 0;
    work->m_shapeA = 0;
    work->m_values = 0;
}
