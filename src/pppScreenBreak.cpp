#include "ffcc/pppScreenBreak.h"

#include "ffcc/graphic.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/ptrarray.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/linkage.h"
#include "ffcc/p_graphic.h"
#include "ffcc/pppPart.h"
#include "ffcc/render_buffers.h"
#include "ffcc/util.h"

#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"

#include <string.h>

struct PScreenBreak {
    float field0_0x0;
    u8 _pad0[0x84];
    u8 field_0x88;
    u8 field_0x89;
    u8 field_0x8a;
    u8 field_0x8b;
};

struct VScreenBreak {
    u8 _pad0[0x100];
};

struct Vec4d {
    float x;
    float y;
    float z;
    float w;
};

struct ScreenBreakDisplayList {
    u32 m_size;
    void* m_data;
    u16 m_material;
};

struct ScreenBreakMeshData {
    u8 _pad0[0x50];
    ScreenBreakDisplayList* m_displayLists;
    u8 _pad54[0x8];
    s32 m_nodeIndex;
};

struct ScreenBreakMeshRef {
    u8 _pad0[0x8];
    ScreenBreakMeshData* m_data;
    u8 _padC[0x8];
};

struct ScreenBreakModelData {
    u8 _pad0[0xC];
    u32 m_meshCount;
    u8 _pad10[0x14];
    CMaterialSet* m_materialSet;
};

struct ScreenBreakModelView {
    u8 _pad0[0x68];
    Mtx m_drawMtx;
    u8 _pad98[0xC];
    ScreenBreakModelData* m_data;
    u8* m_nodes;
    ScreenBreakMeshRef* m_meshes;
};

struct pppScreenBreakUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_initWOrk;
    u8 _pad9[3];
    float m_stepValue;
    float m_arg3;
    u8 m_payload[0x20];
};

struct pppScreenBreakUnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

extern float FLOAT_80331cc0;
static const float kPppScreenBreakDoubleScale = 2.0f;
static const float kPppScreenBreakZero = 0.0f;
static const float kPppScreenBreakRandRange = 0.3f;
static const float kPppScreenBreakVelocityScale = -0.5f;
static const float kPppScreenBreakOne = 1.0f;
static const float kPppScreenBreakNegOne = -1.0f;
static const float kPppScreenBreakDegreesToRadians = 0.017453292f;
static const float kPppScreenBreakCameraOffset = 30.0f;
static const float kPppScreenBreakLightAttn = 4.0f;
static const float kPppScreenBreakLightBias = -3.0f;
static const float DAT_801dd4b0 = 0.0f;
static const float DAT_801dd4b4 = 1.0f;
static const float DAT_801dd4b8 = 0.0f;
static const char s_f999_root_801dd4c8[] = "f999_root";
static const char s_pppScreenBreak_cpp_801dd4d4[] = "pppScreenBreak.cpp";
static inline float CameraPosX() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE0); }
static inline float CameraPosY() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE4); }
static inline float CameraPosZ() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE8); }
static inline float CameraDirX() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xEC); }
static inline float CameraDirY() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xF0); }
static inline float CameraDirZ() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xF4); }
static inline MtxPtr CameraMatrix() { return reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4); }
static inline Mtx44Ptr CameraScreenMatrix() { return reinterpret_cast<Mtx44Ptr>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x48); }

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }
static inline int GraphicScreenBreakBlurEnabled() { return *reinterpret_cast<int*>(reinterpret_cast<u8*>(&Graphic) + 0x7358); }

extern "C" {
int GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti(
    CGraphic*, void*, _GXTexObj*, int, int, int, int, int, int, int, int);
void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int stage, int texCoord, int texMap,
                                                                                 int colorChannel);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int stage, int a, int b, int c, int d);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int stage, int op, int bias,
                                                                                           int scale, int clamp,
                                                                                           int reg);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int stage, int a, int b, int c, int d);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int stage, int op, int bias,
                                                                                           int scale, int clamp,
                                                                                           int reg);
void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
void SetBlurParameter__11CGraphicPcsFiUcUcUcUcUcs(CGraphicPcs*, int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, short);
void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(void*, long, float&, float&, float&, float, float&, float&);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppHeapUseRate__FPQ27CMemory6CStage(void*);
void SearchNode__Q26CChara6CModelFPc(CChara::CModel*, char*);
void ConvI2FVector__5CUtilFR3Vec6S16Vecl(CUtil*, Vec*, S16Vec*, unsigned long);
void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(void*, Mtx44, Vec4d*, Vec4d*);
}

/*
 * --INFO--
 * PAL Address: 0x8012d458
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderScreenBreak(PScreenBreak* pppScreenBreak, pppScreenBreakUnkB*, pppScreenBreakUnkC* param_3)
{
    s32 dataOffset = param_3->m_serializedDataOffsets[2];
    u8* value = (u8*)pppScreenBreak + dataOffset + 0x80;
    void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((u8*)pppMngStPtr + 0xD8), 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    SearchNode__Q26CChara6CModelFPc((CChara::CModel*)model, const_cast<char*>(s_f999_root_801dd4c8));

    if (value[0x24] == 0) {
        Graphic.GetBackBufferRect2(
            Graphic.m_savedFrameBuffer, *(_GXTexObj**)(value + 0x10), 0, 0, 0x280, 0x1C0, 0, (_GXTexFilter)1, (_GXTexFmt)4, 0);
        value[0x24] = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012d500
 * PAL Size: 880b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameScreenBreak(PScreenBreak* pppScreenBreak, pppScreenBreakUnkB* param_2, pppScreenBreakUnkC* param_3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    if (GraphicScreenBreakBlurEnabled() != 0) {
        SetBlurParameter__11CGraphicPcsFiUcUcUcUcUcs(&GraphicsPcs, 0, 0, 0, 0, 0, 0, 0);
    }

    s32* serializedDataOffsets = param_3->m_serializedDataOffsets;
    float* value = (float*)((u8*)pppScreenBreak + serializedDataOffsets[2] + 0x80);
    u8* colorSource = (u8*)pppScreenBreak + serializedDataOffsets[0] + 0x80;
    void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((u8*)pppMngStPtr + 0xD8), 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(float**)(model + 0xE4) = value;
    *(pppScreenBreakUnkB**)(model + 0xE8) = param_2;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

    u8* color = (u8*)(value + 10);
    color[0] = colorSource[8];
    color[1] = colorSource[9];
    color[2] = colorSource[10];
    color[3] = colorSource[11];
    DCFlushRange(value + 10, 4);

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(&pppScreenBreak->field0_0x0, param_2->m_graphId, value[0], value[1], value[2],
                                                 param_2->m_stepValue, param_2->m_arg3, *(float*)param_2->m_payload);

    void* pieceStorage = *(void**)&value[3];
    if (pieceStorage == NULL) {
        pieceStorage = pppMemAlloc__FUlPQ27CMemory6CStagePci(*(u32*)(*(u8**)(model + 0xA4) + 0xC) * 0x3C, pppEnvStPtr->m_stagePtr,
                                                             const_cast<char*>(s_pppScreenBreak_cpp_801dd4d4), 0x25E);
        *(void**)&value[3] = pieceStorage;
        *(void**)&value[4] = pppMemAlloc__FUlPQ27CMemory6CStagePci(0x20, pppEnvStPtr->m_stagePtr,
                                                                    const_cast<char*>(s_pppScreenBreak_cpp_801dd4d4), 0x25F);
        InitPieceData((CChara::CModel*)model, (PScreenBreak*)param_2, (VScreenBreak*)value);
        PSVECNormalize((Vec*)(param_2->m_payload + 0xC), (Vec*)(param_2->m_payload + 0xC));
    }

    float sx = FLOAT_80331cc0 * value[6];
    float sy = FLOAT_80331cc0 * value[7];
    u8* piece = (u8*)*(void**)&value[3];
    for (u32 i = 0; i < *(u32*)(*(u8**)(model + 0xA4) + 0xC); i++) {
        switch (param_2->m_initWOrk) {
        case 0:
            piece[0x38] = 1;
            break;
        case 1:
            if (-*(float*)(piece + 0x28) < (*value * sy) - value[7]) {
                piece[0x38] = 1;
            }
            break;
        case 2:
            float pieceY = *(float*)(piece + 0x28);
            if (-pieceY > value[7] - (*value * sy)) {
                piece[0x38] = 1;
            }
            break;
        case 3:
            if (-*(float*)(piece + 0x24) < (*value * sx) + -value[6]) {
                piece[0x38] = 1;
            }
            break;
        case 4:
            float pieceX = *(float*)(piece + 0x24);
            if (-pieceX > value[6] - (*value * sx)) {
                piece[0x38] = 1;
            }
            break;
        case 5: {
            sx = value[6];
            sy = value[7];
            float x = *value * sx;
            float y = *value * sy;
            float pieceX = *(float*)(piece + 0x24);
            if ((x >= pieceX) && (-pieceX <= x) &&
                (y >= *(float*)(piece + 0x28)) && (-*(float*)(piece + 0x28) <= y)) {
                piece[0x38] = 1;
            }
            break;
        }
        case 6: {
            sx = value[6];
            float x = *value * sx;
            sy = value[7];
            float y = *value * sy;
            if ((-*(float*)(piece + 0x24) >= sx - x) || (-*(float*)(piece + 0x24) <= -sx + x) ||
                (-*(float*)(piece + 0x28) >= sy - y) || (-*(float*)(piece + 0x28) <= -sy + y)) {
                piece[0x38] = 1;
            }
            break;
        }
        default:
            break;
        }
        piece += 0x3C;
    }

    pppSetFpMatrix(pppMngStPtr);
}

/*
 * --INFO--
 * PAL Address: 0x8012d870
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDesScreenBreak(PScreenBreak* pppScreenBreak, pppScreenBreakUnkC* param_2)
{
    s32* serializedDataOffsets = *(s32**)((u8*)param_2 + 0xC);
    s32 dataOffset = serializedDataOffsets[2];
    u8* pppData = ((u8*)pppScreenBreak + dataOffset + 0x80);
    void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((u8*)pppMngStPtr + 0xD8), 0);
    u8* model = (u8*)GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    if (model != 0) {
        *(void**)(model + 0xF0) = NULL;
        *(void**)(model + 0xFC) = NULL;
        *(void**)(model + 0xF4) = NULL;
        *(void**)(model + 0xE4) = NULL;
        *(void**)(model + 0xE8) = NULL;
        *(void**)(model + 0xEC) = NULL;
    }
    if (*(void**)(pppData + 0xC) != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(pppData + 0xC));
        *(void**)(pppData + 0xC) = NULL;
    }
    if (*(void**)(pppData + 0x10) != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(pppData + 0x10));
        *(void**)(pppData + 0x10) = NULL;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012d90c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCon2ScreenBreak(PScreenBreak* pppScreenBreak, pppScreenBreakUnkC* param_2)
{
    s32 dataOffset = param_2->m_serializedDataOffsets[2];
    float* value = (float*)((u8*)pppScreenBreak + dataOffset + 0x80);
    float f = 0.0f;
    value[2] = 0.0f;
    value[1] = f;
    *value = f;
}

/*
 * --INFO--
 * PAL Address: 0x8012d930
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConScreenBreak(PScreenBreak* pppScreenBreak, pppScreenBreakUnkC* param_2)
{
    s32 dataOffset = param_2->m_serializedDataOffsets[2];
    u8* pppData = (u8*)pppScreenBreak + dataOffset + 0x80;
    float* value = (float*)pppData;
    void* gObject = *(void**)((u8*)pppMngStPtr + 0xD8);
    void* handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    float f = 0.0f;
    *(u32*)((u8*)gObject + 0x60) |= 0x40;
    *(void**)(model + 0xF0) = (void*)SB_BeforeDrawCallback;
    *(void**)(model + 0xFC) = (void*)SB_DrawMeshDLCallback;
    *(void**)(model + 0xF4) = (void*)SB_BeforeMeshLockEnvCallback;
    *(void**)(model + 0xEC) = (void*)SB_BeforeCalcMatrixCallback;
    *(void**)(pppData + 0xC) = NULL;
    *(void**)(pppData + 0x10) = NULL;
    value[8] = f;
    value[7] = f;
    value[6] = f;
    value[2] = f;
    value[1] = f;
    value[0] = f;
    *(u8*)(value + 9) = 0;
    *(u8*)(value + 10) = 0xFF;
    *((u8*)value + 0x29) = 0xFF;
    *((u8*)value + 0x2A) = 0xFF;
    *((u8*)value + 0x2B) = 0xFF;
}

/*
 * --INFO--
 * PAL Address: 0x8012da00
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SB_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int)
{
    GXSetZMode(GX_TRUE, (GXCompare)7, GX_TRUE);
}

/*
 * --INFO--
 * PAL Address: 0x8012da2c
 * PAL Size: 1020b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InitPieceData(CChara::CModel* model, PScreenBreak* step, VScreenBreak* work)
{
    s16 sVar2;
    s16 sVar3;
    s16 sVar4;
    s16 sVar7;
    s16 sVar9;
    s16* psVar11;
    s16 sVar12;
    s32 iVar5;
    s32 iVar6;
    s32 iVar14;
    u32 uVar15;
    Vec* inVec;
    s32 iVar16;
    double dVar17;
    const double dVar18 = -(double)kPppScreenBreakRandRange;
    const double dVar19 = (double)kPppScreenBreakRandRange;
    const double dVar20 = (double)kPppScreenBreakOne;
    const double dVar21 = (double)kPppScreenBreakNegOne;
    const double dVar22 = (double)kPppScreenBreakZero;
    const double dVar24 = (double)kPppScreenBreakDoubleScale;
    const double dVar25 = (double)kPppScreenBreakDegreesToRadians;
    S16Vec local_e8;
    S16Vec local_e0;
    S16Vec local_d8;
    s16 local_d0;
    s16 sStack_ce;
    s16 local_cc;
    Vec local_c8;
    u32 uStack_b4;
    s16 sVar8;
    s16 sVar10;
    s16 sVar13;
    u8* modelData = *(u8**)((u8*)model + 0xA4);

    memset(*(void**)((u8*)work + 0xC), 0, *(s32*)(modelData + 0xC) * 0x3C);
    iVar16 = *(s32*)((u8*)model + 0xAC);
    inVec = *(Vec**)((u8*)work + 0xC);
    local_d0 = -0x7FFF;
    sStack_ce = -0x7FFF;
    local_cc = -0x7FFF;

    for (uVar15 = 0; uVar15 < *(u32*)(modelData + 0xC); uVar15++) {
        iVar14 = *(s32*)(iVar16 + 8);
        iVar5 = *(s32*)((u8*)model + 0xA8) + (*(s32*)(iVar14 + 0x5C) * 0xC0);
        *(u8*)(iVar5 + 0xBC) &= 0x7F;
        PSMTXIdentity((float(*)[4])(iVar5 + 0x14));

        iVar5 = *(s32*)(iVar14 + 0x14);
        iVar6 = 0;
        local_d8.x = -0x7FFF;
        local_d8.y = -0x7FFF;
        local_d8.z = -0x7FFF;
        sVar2 = 0x7FFF;
        sVar3 = 0x7FFF;
        local_e0.z = 0x7FFF;
        sVar12 = 0x7FFF;
        sVar9 = 0x7FFF;
        sVar4 = 0x7FFF;

        for (; iVar5 != 0; iVar5--) {
            s16 sVar1 = *(s16*)(*(s32*)(iVar14 + 0x18) + iVar6);
            if (local_d0 < sVar1) {
                local_d0 = sVar1;
            }
            sVar1 = *(s16*)(*(s32*)(iVar14 + 0x18) + iVar6 + 2);
            if (sStack_ce < sVar1) {
                sStack_ce = sVar1;
            }
            sVar1 = *(s16*)(*(s32*)(iVar14 + 0x18) + iVar6 + 4);
            if (local_cc < sVar1) {
                local_cc = sVar1;
            }

            psVar11 = (s16*)(*(s32*)(iVar14 + 0x18) + iVar6);
            sVar1 = *psVar11;
            sVar7 = sVar1;
            sVar8 = sVar1;
            if (sVar12 < sVar1) {
                sVar7 = sVar2;
                sVar8 = sVar12;
            }

            sVar12 = psVar11[1];
            sVar13 = sVar12;
            if (sVar9 < sVar12) {
                sVar12 = sVar3;
                sVar13 = sVar9;
            }

            sVar9 = psVar11[2];
            sVar10 = sVar9;
            if (sVar4 < sVar9) {
                sVar9 = local_e0.z;
                sVar10 = sVar4;
            }

            if (local_d8.x < sVar1) {
                local_d8.x = sVar1;
            }
            sVar2 = *(s16*)(*(s32*)(iVar14 + 0x18) + iVar6 + 2);
            if (local_d8.y < sVar2) {
                local_d8.y = sVar2;
            }
            sVar2 = *(s16*)(*(s32*)(iVar14 + 0x18) + iVar6 + 4);
            if (local_d8.z < sVar2) {
                local_d8.z = sVar2;
            }

            iVar6 += 6;
            sVar2 = sVar7;
            sVar3 = sVar12;
            local_e0.z = sVar9;
            sVar12 = sVar8;
            sVar9 = sVar13;
            sVar4 = sVar10;
        }

        local_e0.z = local_d8.z + local_e0.z;
        local_d8.x = local_d8.x + sVar2;
        local_d8.y = local_d8.y + sVar3;
        local_e0.x = local_d8.x;
        local_e0.y = local_d8.y;
        local_d8.z = local_e0.z;
        ConvI2FVector__5CUtilFR3Vec6S16Vecl(&gUtil, inVec + 3, &local_e0, *(u32*)(modelData + 0x34));
        PSVECScale(inVec + 3, inVec + 3, kPppScreenBreakVelocityScale);

        dVar17 = (double)inVec[3].x;
        if (dVar19 < dVar17) {
            dVar17 = (double)Math.RandF(kPppScreenBreakRandRange);
        }
        if ((double)inVec[3].x < dVar18) {
            dVar17 = -(double)Math.RandF(kPppScreenBreakRandRange);
        }

        inVec->x = (float)dVar17;
        inVec->y = (float)dVar20;
        inVec->z = (float)dVar21;
        PSVECNormalize(inVec, inVec);
        local_c8.x = DAT_801dd4b0;
        local_c8.y = DAT_801dd4b4;
        local_c8.z = DAT_801dd4b8;
        PSVECCrossProduct(inVec, &local_c8, inVec + 2);

        dVar17 = (double)Math.RandF(*(float*)((u8*)step + 0x3C));
        PSVECScale(inVec, inVec, (float)((double)*(float*)((u8*)step + 0x38) + dVar17));

        inVec[1].x = (float)dVar22;
        inVec[1].y = (float)dVar22;
        inVec[1].z = (float)dVar22;
        inVec[4].x = (float)dVar22;

        uStack_b4 = (u32)*(u8*)((u8*)step + 0x34);
        dVar17 = (double)Math.RandF((float)uStack_b4);
        iVar16 += 0x14;
        inVec[4].y = (float)(dVar25 * (double)(float)(dVar24 + dVar17));
        *(u8*)&inVec[4].z = 0;
        inVec += 5;
    }

    local_e8.x = local_d0;
    local_e8.y = sStack_ce;
    local_e8.z = local_cc;
    ConvI2FVector__5CUtilFR3Vec6S16Vecl(&gUtil, (Vec*)((u8*)work + 0x18), &local_e8, *(u32*)(modelData + 0x34));
}

/*
 * --INFO--
 * PAL Address: 0x8012de28
 * PAL Size: 776b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SB_DrawMeshDLCallback(CChara::CModel* model, void* param_2, void*, int meshIndex, int drawListIndex, float (*) [4])
{
    u8* work = (u8*)param_2;
    ScreenBreakModelView* modelView = (ScreenBreakModelView*)model;
    ScreenBreakMeshData* meshData = modelView->m_meshes[meshIndex].m_data;
    ScreenBreakDisplayList* displayList = meshData->m_displayLists;

    displayList += drawListIndex;

    if (work[0x24] != 0) {
        CMaterial* material = (*reinterpret_cast<CPtrArray<CMaterial*>*>((u8*)modelView->m_data->m_materialSet + 8))[displayList->m_material];
        unsigned char colorStorage0[4];
        unsigned char colorStorage1[4];

        MaterialMan.SetMaterial(modelView->m_data->m_materialSet, displayList->m_material, 1, (_GXTevScale)0);
        GXSetArray((GXAttr)0xB, work + 0x28, 4);

        if (*(u16*)((u8*)material + 0x18) == 1) {
            GXSetNumChans(1);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
            GXSetTevKColor((GXTevKColorID)0,
                           *reinterpret_cast<GXColor*>(__ct__6CColorFUcUcUcUc(colorStorage0, 0xA0, 0xA0, 0xA0, 0xA0)));
            GXSetTevKColorSel((GXTevStageID)0, (GXTevKColorSel)0xC);
            GXSetTevKAlphaSel((GXTevStageID)0, (GXTevKAlphaSel)0x1C);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 10, 0xE, 10, 0xF);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0xC, 0, 0, 1, 0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 4, 5, 7);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);

            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 0, 4);
            GXSetTevKColor((GXTevKColorID)1,
                           *reinterpret_cast<GXColor*>(__ct__6CColorFUcUcUcUc(colorStorage1, 0x60, 0x60, 0x60, work[0x2B])));
            GXSetTevKColorSel((GXTevStageID)1, (GXTevKColorSel)0xD);
            GXSetTevKAlphaSel((GXTevStageID)1, (GXTevKAlphaSel)0x1D);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xF, 0xE, 0, 0xF);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 4, 5, 7);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);

            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0, 0, 4);
            GXSetTevKAlphaSel((GXTevStageID)2, (GXTevKAlphaSel)0x1D);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xF, 0xC, 8, 0);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 7, 7, 6);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);

            GXSetNumTevStages(3);
            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
            GXLoadTexObj((_GXTexObj*)*(void**)(work + 0x10), (GXTexMapID)0);
        }

        GXCallDisplayList(displayList->m_data, displayList->m_size);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012e130
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SB_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*) [4], int)
{
    GXColor colorStorage;
    Vec lightDir;
    GXLightObj lightObj;
    u8* camera = reinterpret_cast<u8*>(&CameraPcs);
    const float cameraOffset = kPppScreenBreakCameraOffset;
    const float zero = 0.0f;

    lightDir.x = *(float*)(camera + 0xEC) - (cameraOffset + *(float*)(camera + 0xE0));
    lightDir.y = *(float*)(camera + 0xF0) - (cameraOffset + *(float*)(camera + 0xE4));
    lightDir.z = *(float*)(camera + 0xF4) - (cameraOffset + *(float*)(camera + 0xE8));
    PSVECNormalize(&lightDir, &lightDir);

    GXInitSpecularDirHA(&lightObj, lightDir.x, lightDir.y, lightDir.z, zero, kPppScreenBreakOne, zero);
    GXInitLightAttn(&lightObj, zero, zero, kPppScreenBreakOne, kPppScreenBreakLightAttn, zero, kPppScreenBreakLightBias);

    GXInitLightColor(&lightObj,
                     *reinterpret_cast<GXColor*>(__ct__6CColorFUcUcUcUc(&colorStorage, 0xFF, 0xFF, 0xFF, 0xFF)));
    GXLoadLightObjImm(&lightObj, (GXLightID)1);
    GXSetChanCtrl((GXChannelID)0, 1, (GXColorSrc)0, (GXColorSrc)1, 1, (GXDiffuseFn)2, (GXAttnFn)0);
    GXSetChanCtrl((GXChannelID)2, 0, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
}

/*
 * --INFO--
 * PAL Address: 0x8012e258
 * PAL Size: 900b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int SB_BeforeCalcMatrixCallback(CChara::CModel* model, void* param_2, void* param_3)
{
    ScreenBreakModelView* modelView = (ScreenBreakModelView*)model;
    float* pieceData = *(float**)((u8*)param_2 + 0xC);
    float zero = 0.0f;
    Quaternion meshQuat;
    Quaternion resultQuat;
    Quaternion axisQuat;
    Vec axis;
    Vec gravityAdd;
    Vec basis = { 0.0f, 1.0f, 0.0f };
    Vec cameraOffset;
    Vec screenOffset;
    Vec invTransOffset;
    Vec4d clipOutput;
    Vec4d clipInput;
    Vec cameraPos;
    Vec cameraForward;
    Vec translation;
    Mtx invTransMtx;
    Mtx transMtx;
    Mtx quatMtx;
    Mtx meshMtx;
    Mtx44 screenMtx;
    Mtx invCameraMtx;
    Mtx cameraMtx;
    ScreenBreakMeshRef* mesh;

    cameraForward.x = CameraPcs._236_4_;
    cameraForward.y = CameraPcs._240_4_;
    cameraForward.z = CameraPcs._244_4_;
    cameraPos.x = CameraPcs._224_4_;
    cameraPos.y = CameraPcs._228_4_;
    cameraPos.z = CameraPcs._232_4_;

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

    PSVECCrossProduct(&cameraForward, &basis, &cameraOffset);
    PSVECNormalize(&cameraOffset, &cameraOffset);

    screenOffset.x = *(float*)((u8*)param_2 + 0x18) * cameraOffset.x + cameraPos.x;
    screenOffset.y = cameraPos.y;
    screenOffset.z = *(float*)((u8*)param_2 + 0x18) * cameraOffset.z + cameraPos.z;

    PSMTXMultVec(cameraMtx, &screenOffset, (Vec*)&clipInput);
    clipInput.w = 1.0f;
    MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math, screenMtx, &clipInput, &clipOutput);

    translation.x = clipOutput.x * cameraForward.x;
    translation.y = clipOutput.x * cameraForward.y;
    translation.z = clipOutput.x * cameraForward.z;
    PSVECAdd(&cameraPos, &translation, &translation);

    PSMTXInverse(cameraMtx, invCameraMtx);
    PSMTXConcat(invCameraMtx, modelView->m_drawMtx, modelView->m_drawMtx);
    modelView->m_drawMtx[0][3] = translation.x;
    modelView->m_drawMtx[1][3] = translation.y;
    modelView->m_drawMtx[2][3] = translation.z;

    mesh = modelView->m_meshes;
    if (*(float*)((u8*)param_3 + 0x30) != zero) {
        PSVECScale((Vec*)((u8*)param_3 + 0x20), &gravityAdd, *(float*)((u8*)param_3 + 0x30));
    }

    for (u32 i = 0; i < modelView->m_data->m_meshCount; i++) {
        if (*((char*)pieceData + 0x38) != '\0') {
            u8* nodeMtx = modelView->m_nodes + (mesh->m_data->m_nodeIndex * 0xC0) + 0x14;

            *(float*)(nodeMtx + 0xC) = zero;
            *(float*)(nodeMtx + 0x1C) = zero;
            *(float*)(nodeMtx + 0x2C) = zero;

            PSMTXCopy((float(*)[4])nodeMtx, meshMtx);
            PSMTXIdentity(transMtx);
            transMtx[0][3] = pieceData[9];
            transMtx[1][3] = pieceData[10];
            transMtx[2][3] = pieceData[11];
            PSMTXInverse(transMtx, invTransMtx);

            axis.x = pieceData[6];
            axis.y = pieceData[7];
            axis.z = pieceData[8];
            C_QUATRotAxisRad(&axisQuat, &axis, pieceData[0xD]);
            PSMTXQuat(quatMtx, &axisQuat);
            C_QUATMtx(&meshQuat, meshMtx);
            PSQUATMultiply(&axisQuat, &meshQuat, &resultQuat);
            PSMTXQuat(quatMtx, &resultQuat);
            PSMTXConcat(quatMtx, transMtx, (float(*)[4])nodeMtx);

            pieceData[3] -= pieceData[0];
            pieceData[4] = pieceData[1] * pieceData[0xC] - 0.5f * *(float*)((u8*)param_3 + 0x18) * pieceData[0xC] * pieceData[0xC];
            pieceData[5] -= pieceData[2];

            if (*(float*)((u8*)param_3 + 0x30) != zero) {
                pieceData[3] += gravityAdd.x;
                pieceData[5] += gravityAdd.z;
            }

            pieceData[0xC] += 1.0f;

            invTransOffset.x = invTransMtx[0][3];
            invTransOffset.y = invTransMtx[1][3];
            invTransOffset.z = invTransMtx[2][3];
            PSVECAdd((Vec*)(pieceData + 3), &invTransOffset, &invTransOffset);
            invTransMtx[0][3] = invTransOffset.x;
            invTransMtx[1][3] = invTransOffset.y;
            invTransMtx[2][3] = invTransOffset.z;
            PSMTXConcat(invTransMtx, (float(*)[4])nodeMtx, (float(*)[4])nodeMtx);
        }

        mesh++;
        pieceData += 0xF;
    }

    return 1;
}
