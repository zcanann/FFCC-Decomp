#include "ffcc/pppCharaBreak.h"

#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/system.h"
#include "ffcc/util.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
#include "ffcc/ppp_linkage.h"

static const float kPppCharaBreakZero = 0.0f;
static const float kPppCharaBreakOne = 1.0f;
static const float kPppCharaBreakInitialMiscValue = -10000.0f;
static const float kPppCharaBreakTriangleCenterScale = 0.3333333f;
static const float kPppCharaBreakDegToRad = 0.017453292f;
static const float kPppCharaBreakHalfTurnDegrees = 180.0f;
static const float kPppCharaBreakWobbleRange = 0.8f;
static const float kPppCharaBreakRandomSign = -1.0f;
static const s32 kPppCharaBreakFullTurnDegrees = 0x168;
static const s32 kPppCharaBreakMaxQuantizedCenter = 0x7530;
static const s32 kPppCharaBreakSinTableQuarterTurn = 0x4000;

STATIC_ASSERT(sizeof(POLYGON_DATA) == 0x34);
STATIC_ASSERT(sizeof(CharaBreakStep) == 0x44);
STATIC_ASSERT(sizeof(CharaBreakWork) == 0x48);
STATIC_ASSERT(sizeof(CharaBreakDisplayListPair) == 0x10);

typedef CChara::CMesh::CDisplayList CharaBreakDisplayList;
typedef CChara::CMesh CharaBreakMeshRef;
typedef CChara::CMesh::CRefData CharaBreakMeshData;

STATIC_ASSERT(offsetof(CharaBreakMeshRef, m_data) == 0x8);
STATIC_ASSERT(offsetof(CharaBreakMeshRef, m_workPositions) == 0xC);
STATIC_ASSERT(offsetof(CharaBreakMeshRef, m_workNormals) == 0x10);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_meshCount) == 0xC);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_posQuant) == 0x34);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_normQuant) == 0x38);
STATIC_ASSERT(offsetof(CharaBreakStep, m_worldSpaceMode) == 0x42);

static inline MtxPtr ModelDrawMtx(CChara::CModel* model)
{
    return model->m_matrix;
}

static void CharaBreak_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);
static void CharaBreak_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
static void CharaBreak_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
static int CharaBreak_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);

STATIC_ASSERT(sizeof(CharaBreakDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(CharaBreakDataOffsets, m_colorWorkOffset) == 0x0);
STATIC_ASSERT(offsetof(CharaBreakDataOffsets, m_workOffset) == 0x8);

static inline CharaBreakDataOffsets* GetCharaBreakDataOffsets(_pppCtrlTable* data)
{
    return reinterpret_cast<CharaBreakDataOffsets*>(data->m_serializedDataOffsets);
}

static inline CharaBreakWork* GetCharaBreakWork(pppCharaBreak* charaBreak, _pppCtrlTable* data)
{
    return reinterpret_cast<CharaBreakWork*>(
        charaBreak->m_workArea + GetCharaBreakDataOffsets(data)->m_workOffset);
}

static inline void SetCharaBreakModelCallbacks(CChara::CModel* model, CharaBreakWork* work, CharaBreakStep* step)
{
    model->SetCallbackContext(work, step);
    model->SetBeforeMeshLockEnvCallback(CharaBreak_BeforeMeshLockEnvCallback);
    model->SetDrawMeshDLCallback(CharaBreak_DrawMeshDLCallback);
    model->SetAfterDrawMeshCallback(CharaBreak_AfterDrawMeshCallback);
    model->SetBeforeCalcMatrixCallback(CharaBreak_BeforeCalcMatrixCallback);
}

static inline void ClearCharaBreakModelCallbacks(CChara::CModel* model)
{
    model->SetCallbackContext(0, 0);
    model->SetBeforeMeshLockEnvCallback(0);
    model->SetDrawMeshDLCallback(0);
    model->SetAfterDrawMeshCallback(0);
    model->SetBeforeCalcMatrixCallback(0);
}

/*
 * --INFO--
 * PAL Address: 0x801411E4
 * PAL Size: 32b
 * EN Address: 0x80140360
 * EN Size: 20b
 * JP Address: 0x8013CF88
 * JP Size: 20b
 */
static int CharaBreak_BeforeCalcMatrixCallback(CChara::CModel* model, void* modelData, void* meshData)
{
    CharaBreakStep* stepData = reinterpret_cast<CharaBreakStep*>(meshData);

#if defined(VERSION_GCCP01)
    CharaBreakWork* work = reinterpret_cast<CharaBreakWork*>(modelData);
    if (work->m_enabled == 0) {
        return reinterpret_cast<int>(model);
    }
#endif

    return (u32)__cntlzw(1 - (u32)stepData->m_worldSpaceMode) >> 5;
}

/*
 * --INFO--
 * PAL Address: 0x801411E0
 * PAL Size: 4b
 * EN Address: 0x8014035C
 * EN Size: 4b
 * JP Address: 0x8013CF84
 * JP Size: 4b
 */
static void CharaBreak_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int)
{
}

/*
 * --INFO--
 * PAL Address: 0x801411DC
 * PAL Size: 4b
 * EN Address: 0x80140358
 * EN Size: 4b
 * JP Address: 0x8013CF80
 * JP Size: 4b
 */
static void CharaBreak_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4])
{
}

/*
 * --INFO--
 * PAL Address: 0x80140F18
 * PAL Size: 708b
 * EN Address: 0x801400A0
 * EN Size: 696b
 * JP Address: 0x8013CCC8
 * JP Size: 696b
 */
static void CharaBreak_AfterDrawMeshCallback(
    CChara::CModel* model, void* modelData, void*, int meshIndex, float (*meshMtx)[4])
{
    Mtx cameraMtx;
    Mtx drawMtx;

    CharaBreakWork* work = reinterpret_cast<CharaBreakWork*>(modelData);
    CChara::CMesh* meshRef = model->GetMesh();

#if defined(VERSION_GCCP01)
    if (work->m_enabled != 0)
#endif
    {
        meshRef += meshIndex;
        CharaBreakMeshData* meshData = meshRef->GetRefData();
        CharaBreakDisplayList* materialData = meshData->m_displayLists;
        CameraPcs.GetViewMatrix(cameraMtx);

        s32 materialIndex = meshData->m_displayListCount - 1;

        for (; materialIndex >= 0; materialIndex--, materialData++) {
            CharaBreakDisplayListPair** meshTable =
                work->m_meshBuffers[meshIndex];
            CharaBreakDisplayListPair** displayListEntry = &meshTable[materialIndex];
            POLYGON_DATA* vertexData = (*displayListEntry)->m_polygonData;

            MaterialMan.SetMaterial(
                (CMaterialSet*)model->GetRefData()->m_materialSet, materialData->m_material, 0, GX_CS_SCALE_1);

            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            GXSetCullMode(GX_CULL_NONE);
            GXClearVtxDesc();
            GXSetVtxDesc((GXAttr)9, GX_DIRECT);
            GXSetVtxDesc((GXAttr)10, GX_INDEX16);
            GXSetVtxDesc((GXAttr)11, GX_INDEX16);
            GXSetVtxDesc((GXAttr)13, GX_INDEX16);
            GXSetVtxDesc((GXAttr)14, GX_INDEX16);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, GX_POS_XYZ, GX_S16, model->GetRefData()->m_posQuant & 0xFF);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)10, GX_NRM_XYZ, GX_S16, model->GetRefData()->m_normQuant & 0xFF);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)11, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)13, GX_TEX_ST, GX_S16, 0xC);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)14, GX_TEX_ST, GX_S16, 0xC);

            if (meshRef->GetRefData()->m_skinCount == 0) {
                GXLoadPosMtxImm(cameraMtx, 0);
            } else {
                PSMTXConcat(cameraMtx, meshMtx, drawMtx);
                GXLoadPosMtxImm(drawMtx, 0);
            }

            GXBegin((GXPrimitive)0x90, (GXVtxFmt)7, (*displayListEntry)->m_polygonCount * 3);
            POLYGON_DATA* polygon = vertexData;
            s32 faceIndex = 0;
            while (faceIndex < (s32)(u32)(*displayListEntry)->m_polygonCount) {
                faceIndex++;
                GXPosition3s16(polygon->m_pos[0].x, polygon->m_pos[0].y, polygon->m_pos[0].z);
                GXNormal1x16(polygon->m_nrmIndices[0]);
                GXColor1x16(0);
                GXTexCoord1x16(polygon->m_texIndices[0]);
                GXTexCoord1x16(polygon->m_texIndices[0]);
                GXPosition3s16(polygon->m_pos[1].x, polygon->m_pos[1].y, polygon->m_pos[1].z);
                GXNormal1x16(polygon->m_nrmIndices[1]);
                GXColor1x16(0);
                GXTexCoord1x16(polygon->m_texIndices[1]);
                GXTexCoord1x16(polygon->m_texIndices[1]);
                GXPosition3s16(polygon->m_pos[2].x, polygon->m_pos[2].y, polygon->m_pos[2].z);
                GXNormal1x16(polygon->m_nrmIndices[2]);
                GXColor1x16(0);
                GXTexCoord1x16(polygon->m_texIndices[2]);
                GXTexCoord1x16(polygon->m_texIndices[2]);
                polygon++;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80140CC8
 * PAL Size: 592b
 * EN Address: 0x8013FE50
 * EN Size: 592b
 * JP Address: 0x8013CA78
 * JP Size: 592b
 */
static void CreatePolygon(POLYGON_DATA* polygonData, void* displayList, unsigned long, CChara::CModel* model, CChara::CMesh* mesh)
{
    CharaBreakMeshData* meshData = mesh->GetRefData();
    S16Vec* workPositions;
    s32 isRigid = 0;
    Mtx meshMtx;

    if (meshData->m_skinCount == 0) {
        isRigid = 1;
        PSMTXConcat(ModelDrawMtx(model), model->GetNode(meshData->m_nodeIndex)->GetWorldMatrix(), meshMtx);
    }
    workPositions = mesh->GetVertex();
    u16* stream = (u16*)displayList;

    s32 keepReading = 1;
    while (keepReading != 0) {
        u8 drawCmd = *(u8*)stream;
        u16 drawCount = *(u16*)((u8*)stream + 1);
        u8 drawMode = drawCmd & 7;
        u8 primitive = drawCmd & 0xF8;
        s32 keepTri;
        s32 outVertex;
        u16* stripRestart;
        s16 triCount;

        stream = (u16*)((u8*)stream + 3);
        if (gUtil.IsHasDrawFmtDL(drawCmd) == 0) {
            keepReading = 0;
        } else {
            triCount = (s16)(drawCount - 2);
            keepTri = 1;
            outVertex = 0;
            stripRestart = 0;

            if (primitive == 0x90) {
                triCount = (s16)((s32)drawCount / 3);
            }

            while (keepTri != 0) {
                u16* previousRestart = stripRestart;
                u16 posIndex = stream[0];
                u16 nrmIndex = stream[1];
                u16 texIndex = stream[3];

                stream += 4;
                if (drawMode == 2) {
                    stream++;
                }

                if (isRigid != 0) {
                    S16Vec* sourcePos = workPositions + posIndex;
                    S16Vec posQuantized = *sourcePos;
                    Vec posFloat;

                    gUtil.ConvI2FVector(posFloat, posQuantized, model->GetRefData()->m_posQuant);
                    PSMTXMultVec(meshMtx, &posFloat, &posFloat);
                    gUtil.ConvF2IVector(polygonData->m_pos[outVertex], posFloat,
                        model->GetRefData()->m_posQuant);
                } else {
                    polygonData->m_pos[outVertex] = workPositions[posIndex];
                }

                polygonData->m_posIndices[outVertex] = posIndex;
                polygonData->m_texIndices[outVertex] = texIndex;
                polygonData->m_nrmIndices[outVertex] = nrmIndex;
                outVertex++;
                stripRestart = previousRestart;

                if (primitive == 0x90) {
                    if (outVertex == 3) {
                        triCount--;
                        if (triCount <= 0) {
                            keepTri = 0;
                        }
                        outVertex = 0;
                        polygonData++;
                    }
                } else if (primitive == 0x98) {
                    if (outVertex == 1) {
                        stripRestart = stream;
                    } else if (outVertex == 3) {
                        triCount--;
                        if (triCount <= 0) {
                            keepTri = 0;
                        }
                        if ((__rlwnm(1, (u32)__cntlzw((s32)triCount), 31, 31) & 0xFF) == 0) {
                            stream = previousRestart;
                        }
                        outVertex = 0;
                        polygonData++;
                    }
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8014099C
 * PAL Size: 812b
 * EN Address: 0x8013FB24
 * EN Size: 812b
 * JP Address: 0x8013C758
 * JP Size: 800b
 */
static void InitPolygonParameter(PCharaBreak* charaBreak, VCharaBreak*, POLYGON_DATA* polygonData, unsigned long polygonCount,
                          CChara::CModel* model, CChara::CMesh* mesh)
{
    CharaBreakStep* stepData = (CharaBreakStep*)charaBreak;
    S16Vec* workNormals = mesh->GetNormal();
    POLYGON_DATA* polygon = polygonData;
    f32 zero = kPppCharaBreakZero;

    for (u32 i = 0; i < polygonCount; i++) {
        Vec normal;
        Vec up = {0.0f, 1.0f, 0.0f};
        Vec tangent;

        int rotationDeg = (int)stepData->m_rotationBaseDeg + rand() % stepData->m_rotationRangeDeg;
        if (rotationDeg > 0xFF) {
            rotationDeg = 0xFF;
        }

        polygon->m_rotationDeg = (u8)rotationDeg;
        polygon->m_enabled = 0;
        polygon->m_fallFrames = 0;

        if (stepData->m_clipMode == 2) {
            polygon->m_enabled = 1;
        }

        if (mesh->GetRefData()->m_skinCount == 0) {
            normal.x = Math.RandF(kPppCharaBreakOne);
            normal.y = Math.RandF(kPppCharaBreakOne);
            normal.z = Math.RandF(kPppCharaBreakOne);
            normal.x *= (rand() % 2) ? kPppCharaBreakOne : kPppCharaBreakRandomSign;
            normal.y *= (rand() % 2) ? kPppCharaBreakOne : kPppCharaBreakRandomSign;
            normal.z *= (rand() % 2) ? kPppCharaBreakOne : kPppCharaBreakRandomSign;
            PSVECNormalize(&normal, &normal);
            gUtil.ConvF2IVector(polygon->m_normalA, normal, model->GetRefData()->m_normQuant);
        } else {
            polygon->m_normalA = workNormals[polygon->m_nrmIndices[0]];
            gUtil.ConvI2FVector(normal, workNormals[polygon->m_nrmIndices[0]], model->GetRefData()->m_normQuant);
        }

        PSVECCrossProduct(&up, &normal, &tangent);
        VECNormalizeZero(&tangent, &tangent);

        if (zero == tangent.x && zero == tangent.y && zero == tangent.z) {
            tangent.x = kPppCharaBreakOne;
            tangent.y = zero;
            tangent.z = zero;
        }

        if (stepData->m_spinMode != 0 && stepData->m_spinMode == 1) {
            polygon->m_normalA.z = 0;
            polygon->m_normalA.y = 0;
            polygon->m_normalA.x = 0;
            polygon->m_normalA.y = rand() % 2;
        }

        gUtil.ConvF2IVector(polygon->m_normalB, tangent, model->GetRefData()->m_normQuant);
        polygon++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801400f0
 * PAL Size: 2220b
 * EN Address: 0x8013F278
 * EN Size: 2220b
 * JP Address: 0x8013BEAC
 * JP Size: 2220b
 */
static void UpdatePolygonData(PCharaBreak* step, VCharaBreak* work, CChara::CModel* model)
{
    POLYGON_DATA* polygon;
    CharaBreakStep* stepData = (CharaBreakStep*)step;
    CChara::CMesh* mesh = model->GetMesh();
    u32 meshIndex;
    s16 threshold;

    threshold = (s32)((work->m_graphValue0 * (work->m_bboxMax.y - work->m_bboxMin.y)) *
                      (float)(1 << model->GetRefData()->m_posQuant));

    for (meshIndex = 0; meshIndex < model->GetRefData()->m_meshCount; meshIndex++, mesh++) {
        s32 needsMtxUpdate = 0;
        Mtx meshToWorld;

        if (mesh->GetRefData()->m_skinCount == 0 && stepData->m_worldSpaceMode == 1) {
            needsMtxUpdate = 1;
            PSMTXConcat(model->m_matrix, model->GetNode(mesh->GetRefData()->m_nodeIndex)->GetWorldMatrix(), meshToWorld);
        }

        for (int dl = mesh->GetRefData()->m_displayListCount - 1; dl >= 0; dl--) {
            CharaBreakDisplayListPair** displayListPairs =
                work->m_meshBuffers[meshIndex];
            polygon = displayListPairs[dl]->m_polygonData;

            for (int polyIndex = 0; polyIndex < displayListPairs[dl]->m_polygonCount; polyIndex++) {
                S16Vec transformed[3];

                if (polygon->m_enabled == 0) {
                    int flags[3] = {0, 0, 0};

                    for (int i = 0; i < 3; i++) {
                        if (needsMtxUpdate) {
                            S16Vec* srcPos = mesh->GetVertex() + polygon->m_posIndices[i];
                            Vec transformedPos;
                            gUtil.ConvI2FVector(transformedPos, *srcPos, model->GetRefData()->m_posQuant);
                            PSMTXMultVec(meshToWorld, &transformedPos, &transformedPos);
                            gUtil.ConvF2IVector(transformed[i], transformedPos, model->GetRefData()->m_posQuant);
                        } else {
                            transformed[i] = mesh->GetVertex()[polygon->m_posIndices[i]];
                        }

                        if (stepData->m_clipMode == 0) {
                            if (stepData->m_worldSpaceMode == 1) {
                                if (transformed[i].y < threshold) {
                                    flags[i] = 1;
                                }
                            } else if (polygon->m_pos[i].y < threshold) {
                                flags[i] = 1;
                            }
                        } else if (stepData->m_clipMode == 1) {
                            if (stepData->m_worldSpaceMode == 1) {
                                if (transformed[i].y > threshold) {
                                    flags[i] = 1;
                                }
                            } else if (polygon->m_pos[i].y > threshold) {
                                flags[i] = 1;
                            }
                        }
                    }

                    for (int i = 0; i < 3; i++) {
                        if (flags[i] == 0) {
                            polygon->m_enabled = 0;
                            break;
                        }
                        polygon->m_enabled = 1;
                    }

                    if (stepData->m_worldSpaceMode == 1 && polygon->m_enabled != 0) {
                        polygon->m_pos[0] = transformed[0];
                        polygon->m_pos[1] = transformed[1];
                        polygon->m_pos[2] = transformed[2];
                    }
                }

                if (polygon->m_enabled == 0) {
                    if (stepData->m_worldSpaceMode == 1) {
                        polygon->m_pos[0] = transformed[0];
                        polygon->m_pos[1] = transformed[1];
                        polygon->m_pos[2] = transformed[2];
                    }
                } else {
                    Vec center;
                    center.z = kPppCharaBreakZero;
                    center.y = kPppCharaBreakZero;
                    center.x = kPppCharaBreakZero;

                    int sumX = (int)polygon->m_pos[0].x + (int)polygon->m_pos[1].x + (int)polygon->m_pos[2].x;
                    int sumY = (int)polygon->m_pos[0].y + (int)polygon->m_pos[1].y + (int)polygon->m_pos[2].y;
                    int sumZ = (int)polygon->m_pos[0].z + (int)polygon->m_pos[1].z + (int)polygon->m_pos[2].z;
                    short avgX = (short)(sumX / 3);
                    short avgY = (short)(sumY / 3);
                    short avgZ = (short)(sumZ / 3);

                    if (avgX >= -kPppCharaBreakMaxQuantizedCenter && avgX <= kPppCharaBreakMaxQuantizedCenter &&
                        avgY >= -kPppCharaBreakMaxQuantizedCenter && avgY <= kPppCharaBreakMaxQuantizedCenter &&
                        avgZ >= -kPppCharaBreakMaxQuantizedCenter && avgZ <= kPppCharaBreakMaxQuantizedCenter) {
                        Vec verts[3];
                        Vec axis;
                        Vec velocity;
                        Quaternion rotQuat;
                        Mtx rotMtx;
                        float cosValue;
                        float sinValue;

                        for (int i = 0; i < 3; i++) {
                            S16Vec pos = polygon->m_pos[i];
                            gUtil.ConvI2FVector(verts[i], pos, model->GetRefData()->m_posQuant);
                            PSVECAdd(&center, &verts[i], &center);
                        }

                        PSVECScale(&center, &center, kPppCharaBreakTriangleCenterScale);

                        gUtil.ConvI2FVector(axis, polygon->m_normalB, model->GetRefData()->m_normQuant);
                        gUtil.ConvI2FVector(velocity, polygon->m_normalA, model->GetRefData()->m_normQuant);
                        PSVECScale(&velocity, &velocity, stepData->m_velocityBase + Math.RandF(stepData->m_velocityRange));

                        C_QUATRotAxisRad(&rotQuat, &axis, kPppCharaBreakDegToRad * (float)polygon->m_rotationDeg);
                        PSMTXQuat(rotMtx, &rotQuat);
                        cosValue = kPppCharaBreakZero;
                        sinValue = cosValue;

                        if (stepData->m_spinMode == 1) {
                            short* angleState = &polygon->m_normalA.x;
                            if (polygon->m_normalA.y == 0) {
                                *angleState += (rand() % 10) + 10;
                            } else {
                                *angleState -= (rand() % 10) + 10;
                            }

                            s32 angle = *angleState;
                            if (angle > kPppCharaBreakFullTurnDegrees) {
                                angle -= kPppCharaBreakFullTurnDegrees;
                                *angleState = angle;
                            }
                            angle = *angleState;
                            if (angle < 0) {
                                angle += kPppCharaBreakFullTurnDegrees;
                                *angleState = angle;
                            }

                            s32 sinIndex = (s32)(((float)((int)(*angleState << 15))) / kPppCharaBreakHalfTurnDegrees);
                            sinValue = ppvSinTbl[(sinIndex & 0xFFFC) >> 2];
                            cosValue = ppvSinTbl[((sinIndex + kPppCharaBreakSinTableQuarterTurn) & 0xFFFC) >> 2];
                        }

                        for (int i = 0; i < 3; i++) {
                            float wobbleScale;

                            PSVECSubtract(&verts[i], &center, &verts[i]);
                            PSMTXMultVec(rotMtx, &verts[i], &verts[i]);
                            PSVECAdd(&verts[i], &center, &verts[i]);

                            if (stepData->m_spinMode == 0) {
                                verts[i].x += velocity.x;
                                verts[i].y += velocity.y - stepData->m_gravity * (float)polygon->m_fallFrames;
                                verts[i].z += velocity.z;
                            } else if (stepData->m_spinMode == 1) {
                                wobbleScale = kPppCharaBreakOne + Math.RandF(kPppCharaBreakWobbleRange);
                                verts[i].x += cosValue * wobbleScale;
                                verts[i].y += velocity.y - stepData->m_gravity * (float)polygon->m_fallFrames;
                                wobbleScale = kPppCharaBreakOne + Math.RandF(kPppCharaBreakWobbleRange);
                                verts[i].z += sinValue * wobbleScale;
                            }

                            verts[i].x += stepData->m_direction.x * work->m_payloadGraphValue0;
                            verts[i].y += stepData->m_direction.y * work->m_payloadGraphValue0;
                            verts[i].z += stepData->m_direction.z * work->m_payloadGraphValue0;

                            gUtil.ConvF2IVector(polygon->m_pos[i], verts[i], model->GetRefData()->m_posQuant);
                        }
                        polygon->m_fallFrames++;
                    }
                }

                polygon++;
            }
        }

    }
}

/*
 * --INFO--
 * PAL Address: 0x801400B0
 * PAL Size: 64b
 * EN Address: 0x8013F240
 * EN Size: 56b
 * JP Address: 0x8013BE70
 * JP Size: 60b
 */
void pppConstructCharaBreak(pppCharaBreak* charaBreak, _pppCtrlTable* data)
{
    CharaBreakWork* work = GetCharaBreakWork(charaBreak, data);

    work->m_meshBuffers = 0;
    work->m_graphValue0 = work->m_graphValue1 = work->m_graphValue2 = kPppCharaBreakZero;
    work->m_payloadGraphValue0 = work->m_payloadGraphValue1 = work->m_payloadGraphValue2 = kPppCharaBreakZero;
#if defined(VERSION_GCCP01)
    work->m_enabled = 1;
#endif
}

/*
 * --INFO--
 * PAL Address: 0x80140080
 * PAL Size: 48b
 * EN Address: 0x8013F210
 * EN Size: 48b
 * JP Address: 0x8013BE3C
 * JP Size: 52b
 */
void pppConstruct2CharaBreak(pppCharaBreak* charaBreak, _pppCtrlTable* data)
{
    CharaBreakWork* work = GetCharaBreakWork(charaBreak, data);

    work->m_graphValue0 = work->m_graphValue1 = work->m_graphValue2 = kPppCharaBreakZero;
    work->m_payloadGraphValue0 = work->m_payloadGraphValue1 = work->m_payloadGraphValue2 = kPppCharaBreakZero;
}

/*
 * --INFO--
 * PAL Address: 0x8013FF14
 * PAL Size: 364b
 * EN Address: 0x8013F0C0
 * EN Size: 336b
 * JP Address: 0x8013BCEC
 * JP Size: 336b
 */
void pppDestructCharaBreak(pppCharaBreak* charaBreak, _pppCtrlTable* data)
{
    CharaBreakDisplayListPair*** perMeshBuffers;
    CharaBreakDisplayListPair** dlEntries;
    CharaBreakMeshData* meshData;
    CharaBreakDisplayListPair*** meshBufferSlot;
    CChara::CModel* model;
    CChara::CMesh* mesh;
    u32 dlIndex;
    u32 meshIndex;
    CharaBreakWork* work;
    CharaBreakDisplayListPair** dlEntryBase;

#if defined(VERSION_GCCP01)
    Graphic._WaitDrawDone("pppCharaBreak.cpp", 0x319);
#else
    Graphic._WaitDrawDone("pppCharaBreak.cpp", 0x30D);
#endif

    work = GetCharaBreakWork(charaBreak, data);
    model = work->m_model;

    ClearCharaBreakModelCallbacks(model);

    meshBufferSlot = work->m_meshBuffers;
    perMeshBuffers = meshBufferSlot;
    mesh = model->GetMesh();

#if defined(VERSION_GCCP01)
    if (perMeshBuffers != NULL)
#endif
    {
        for (meshIndex = 0; meshIndex < model->GetRefData()->m_meshCount; meshIndex++, mesh++) {
            dlEntryBase = *meshBufferSlot;
            meshData = mesh->GetRefData();
#if defined(VERSION_GCCP01)
            if (dlEntryBase != NULL)
#endif
            {
                dlEntries = dlEntryBase;
                for (dlIndex = 0; dlIndex < meshData->m_displayListCount; dlIndex++) {
#if defined(VERSION_GCCP01)
                    if (*dlEntries != NULL)
#endif
                    {
                        if ((*dlEntries)->m_rewrittenDisplayList != NULL) {
                            pppMemFree((*dlEntries)->m_rewrittenDisplayList);
                            (*dlEntries)->m_rewrittenDisplayList = 0;
                        }
                        if ((*dlEntries)->m_polygonData != NULL) {
                            pppMemFree((*dlEntries)->m_polygonData);
                            (*dlEntries)->m_polygonData = 0;
                        }
                    }
                    if (*dlEntries != NULL) {
                        pppMemFree(*dlEntries);
                        *dlEntries = 0;
                    }
                    dlEntries++;
                }
            }

            if (*meshBufferSlot != NULL) {
                pppMemFree(*meshBufferSlot);
                *meshBufferSlot = 0;
            }
            meshBufferSlot++;
        }
    }

    if (perMeshBuffers != NULL) {
        pppMemFree(perMeshBuffers);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8013FAA0
 * PAL Size: 1140b
 * EN Address: 0x8013ED28
 * EN Size: 920b
 * JP Address: 0x8013B94C
 * JP Size: 928b
 */
void pppFrameCharaBreak(pppCharaBreak* charaBreak, CharaBreakStep* step, _pppCtrlTable* data)
{
    CharaBreakWork* work;
    CChara::CMesh* mesh;
    CChara::CModel* model;
    CGObject* handle;
    u32 i;
    CharaBreakDisplayList* displayList;
    CharaBreakDisplayListPair** dlEntries;
    int dl;

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetCharaBreakWork(charaBreak, data);
    handle = ppvMng->m_owner;
#if defined(VERSION_GCCP01)
    if (work->m_enabled == 0) {
        return;
    }
#endif

    CCharaPcs::CHandle* charaHandle = GetCharaHandlePtr(handle, 0);
    model = GetCharaModelPtr(charaHandle);
    work->m_model = model;

    CalcGraphValue(charaBreak,
                   step->m_graphId,
                   work->m_graphValue0,
                   work->m_graphValue1,
                   work->m_graphValue2,
                   step->m_dataValIndex,
                   step->m_graphInit,
                   step->m_graphStep);

    CalcGraphValue(charaBreak,
                   step->m_graphId,
                   work->m_payloadGraphValue0,
                   work->m_payloadGraphValue1,
                   work->m_payloadGraphValue2,
                   step->m_payloadGraphInit,
                   step->m_payloadGraphStep,
                   step->m_payloadGraphStepStep);

    SetCharaBreakModelCallbacks(model, work, step);

    if (step->m_graphId == charaBreak->m_graphId) {
        f32 zero = kPppCharaBreakZero;
        if (zero == step->m_direction.x && zero == step->m_direction.y &&
            zero == step->m_direction.z) {
            step->m_direction.x = kPppCharaBreakOne;
            step->m_direction.y = kPppCharaBreakZero;
            step->m_direction.z = kPppCharaBreakZero;
        } else {
            PSVECNormalize(&step->m_direction, &step->m_direction);
        }
    }

    mesh = model->GetMesh();

    if (work->m_meshBuffers == NULL) {
#if !defined(VERSION_GCCP01)
        u32 totalPolygonCount = 0;
#endif
        work->m_miscValue = kPppCharaBreakInitialMiscValue;
#if defined(VERSION_GCCP01)
        work->m_meshBuffers = static_cast<CharaBreakDisplayListPair***>(pppMemAllocNoReport(
            model->GetRefData()->m_meshCount << 2, ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x3D0));
#else
        work->m_meshBuffers = static_cast<CharaBreakDisplayListPair***>(pppMemAlloc(
            model->GetRefData()->m_meshCount << 2, ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x3B5));
#endif
#if defined(VERSION_GCCP01)
        if (work->m_meshBuffers == NULL) {
            goto fail;
        }
#endif

#if defined(VERSION_GCCP01)
        for (u32 i = 0; i < model->GetRefData()->m_meshCount; i++) {
            work->m_meshBuffers[i] = 0;
        }
#endif

        for (i = 0; i < model->GetRefData()->m_meshCount; i++, mesh++) {
            {
                CharaBreakMeshData* meshData = mesh->GetRefData();

                if (strcmp(meshData->m_name, "obj") == 0) {
                    gUtil.CalcBoundaryBoxQuantized(&work->m_bboxMin, &work->m_bboxMax,
                        mesh->GetVertex(), meshData->m_vertexCount,
                        model->GetRefData()->m_posQuant);
                }
            }

#if defined(VERSION_GCCP01)
            work->m_meshBuffers[i] = static_cast<CharaBreakDisplayListPair**>(pppMemAllocNoReport(
                mesh->GetRefData()->m_displayListCount << 2, ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x3E9));
#else
            work->m_meshBuffers[i] = static_cast<CharaBreakDisplayListPair**>(pppMemAlloc(
                mesh->GetRefData()->m_displayListCount << 2, ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x3C4));
#endif
            CharaBreakDisplayListPair** meshBuffer = work->m_meshBuffers[i];
#if defined(VERSION_GCCP01)
            if (meshBuffer == 0) {
                goto fail;
            }
#endif

#if defined(VERSION_GCCP01)
            {
                int displayListCount = mesh->GetRefData()->m_displayListCount;
                CharaBreakDisplayListPair** dlEntries = meshBuffer;
                for (int dl = displayListCount - 1; dl >= 0; dl--) {
                    dlEntries[dl] = 0;
                }
            }
#endif

            {
                int displayListCount = mesh->GetRefData()->m_displayListCount;
                displayList = mesh->GetRefData()->m_displayLists;
                dl = displayListCount - 1;
                dlEntries = meshBuffer + dl;
                for (; dl >= 0; dl--, displayList++) {
#if defined(VERSION_GCCP01)
                    *dlEntries = (CharaBreakDisplayListPair*)pppMemAllocNoReport(
                        0x10, ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x3FC);
#else
                    *dlEntries = (CharaBreakDisplayListPair*)pppMemAlloc(
                        0x10, ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x3CE);
#endif
#if defined(VERSION_GCCP01)
                    if (*dlEntries == NULL) {
                        goto fail;
                    }
#endif

#if defined(VERSION_GCCP01)
                    (*dlEntries)->m_rewrittenDisplayList = NULL;
                    (*dlEntries)->m_displayListSize = 0;
                    (*dlEntries)->m_polygonData = 0;
#endif
                    (*dlEntries)->m_displayListSize = displayList->m_size;
#if defined(VERSION_GCCP01)
                    (*dlEntries)->m_rewrittenDisplayList = pppMemAllocNoReport(
                        displayList->m_size, ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x40B);
#else
                    (*dlEntries)->m_rewrittenDisplayList = pppMemAlloc(
                        displayList->m_size, ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x3D0);
#endif
#if defined(VERSION_GCCP01)
                    if ((*dlEntries)->m_rewrittenDisplayList == NULL) {
                        goto fail;
                    }
#endif

                    memcpy((*dlEntries)->m_rewrittenDisplayList, displayList->m_data, displayList->m_size);
                    gUtil.ReWriteDisplayList((*dlEntries)->m_rewrittenDisplayList, displayList->m_size, 1);

                    u32 polygonCount = gUtil.GetNumPolygonFromDL((*dlEntries)->m_rewrittenDisplayList, displayList->m_size);
#if !defined(VERSION_GCCP01)
                    totalPolygonCount += polygonCount;
#endif
#if defined(VERSION_GCCP01)
                    (*dlEntries)->m_polygonData = (POLYGON_DATA*)pppMemAllocNoReport(
                        polygonCount * sizeof(POLYGON_DATA), ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x423);
#else
                    (*dlEntries)->m_polygonData = (POLYGON_DATA*)pppMemAlloc(
                        polygonCount * sizeof(POLYGON_DATA), ppvEnv->m_stagePtr, "pppCharaBreak.cpp", 0x3DF);
#endif
#if defined(VERSION_GCCP01)
                    if ((*dlEntries)->m_polygonData == NULL) {
                        goto fail;
                    }
#endif
                    (*dlEntries)->m_polygonCount = (u16)polygonCount;

                    CreatePolygon((*dlEntries)->m_polygonData, displayList->m_data, displayList->m_size,
                                  model, mesh);
                    InitPolygonParameter((PCharaBreak*)step, work, (*dlEntries)->m_polygonData,
                                         (*dlEntries)->m_polygonCount, model, mesh);

                    dlEntries--;
                }
            }

        }
#if !defined(VERSION_GCCP01)
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf("ポリゴン数: %d ポリゴンデータサイズ: %d メモリサイズ: %d KB\n",
                totalPolygonCount, sizeof(POLYGON_DATA), totalPolygonCount * sizeof(POLYGON_DATA) >> 10);
        }
#endif
    }

    if (ppvIsLoopCalc == 0) {
        UpdatePolygonData((PCharaBreak*)step, work, model);
    }
    return;

#if defined(VERSION_GCCP01)
fail:
    work->m_enabled = 0;
    ClearCharaBreakModelCallbacks(model);
#endif
}

/*
 * --INFO--
 * PAL Address: 0x8013F9D0
 * PAL Size: 208b
 * EN Address: 0x8013EC64
 * EN Size: 196b
 * JP Address: 0x8013B888
 * JP Size: 196b
 */
void pppRenderCharaBreak(pppCharaBreak* charaBreak, CharaBreakStep*, _pppCtrlTable* data)
{
    int colorOffset = GetCharaBreakDataOffsets(data)->m_colorWorkOffset;
    CharaBreakWork* work = GetCharaBreakWork(charaBreak, data);
    VColor* colorWork = reinterpret_cast<VColor*>(charaBreak->m_workArea + colorOffset);

#if defined(VERSION_GCCP01)
    if (work->m_enabled != 0)
#endif
    {
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        pppInitBlendMode();
        pppSetDrawEnv(
            &colorWork->m_color,
            &charaBreak->m_drawMatrix,
            kPppCharaBreakZero,
            0,
            0,
            0,
            0,
            1,
            1,
            0);
        _GXSetBlendMode(GX_BM_NONE, GX_BL_SRCCLR, GX_BL_SRCCLR, GX_LO_COPY);
        work->m_color.r = 0xFF;
        work->m_color.g = 0xFF;
        work->m_color.b = 0xFF;
        work->m_color.a = colorWork->m_color.rgba[3];
    }
}
