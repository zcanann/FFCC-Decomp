#include "ffcc/pppScreenBreak.h"

#include "ffcc/graphic.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
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

struct UnkB {
    float m_dataValIndex;
    u16 m_initWOrk;
    u16 _pad6;
    float m_stepValue;
    s32 m_graphId;
    float m_arg3;
    u8* m_payload;
};

struct UnkC {
    s32* m_serializedDataOffsets;
};

extern int DAT_8032ed70;
extern int DAT_802381a0;
extern void* DAT_80238034;
extern float FLOAT_80331cc0;
extern float FLOAT_80331cc4;
extern float FLOAT_80331cc8;
extern float FLOAT_80331ccc;
extern float FLOAT_80331cd0;
extern float FLOAT_80331cd4;
extern float FLOAT_80331cd8;
extern float FLOAT_80331ce8;
extern float FLOAT_80331cec;
extern float FLOAT_80331cf0;
extern CUtil DAT_8032ec70;
extern CMath Math;
extern float DAT_801dd4bc;
extern float DAT_801dd4c0;
extern float DAT_801dd4c4;
extern float DAT_801dd4b0;
extern float DAT_801dd4b4;
extern float DAT_801dd4b8;
extern char MaterialMan[];
extern char s_f999_root_801dd4c8[];
extern char s_pppScreenBreak_cpp_801dd4d4[];
extern CGraphic GraphicsPcs;
extern _pppMngSt* pppMngStPtr;
extern _pppEnvSt* pppEnvStPtr;
extern float FLOAT_80331cf4;

struct ScreenBreakCameraPcs {
    u8 _pad0[4];
    Mtx m_cameraMatrix;
    u8 _pad34[0x14];
    Mtx44 m_screenMatrix;
    u8 _pad88[0x58];
    float _224_4_;
    float _228_4_;
    float _232_4_;
    float _236_4_;
    float _240_4_;
    float _244_4_;
};

extern ScreenBreakCameraPcs CameraPcs;

extern "C" {
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
void SetBlurParameter__11CGraphicPcsFiUcUcUcUcUcs(CGraphic*, int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, short);
void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppHeapUseRate__FPQ27CMemory6CStage(void*);
void SearchNode__Q26CChara6CModelFPc(CChara::CModel*, char*);
void ConvI2FVector__5CUtilFR3Vec6S16Vecl(CUtil*, Vec*, S16Vec*, unsigned long);
float RandF__5CMathFf(float, CMath*);
void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(void*, Mtx44, Vec4d*, Vec4d*);
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
    float* pieceData = *(float**)((u8*)param_2 + 0xC);
    u8* mesh = *(u8**)((u8*)model + 0xAC);
    Vec basis;
    Vec cameraForward;
    Vec cameraPos;
    Vec cameraRefPos;
    Vec cameraOffset;
    Vec screenOffset;
    Vec gravityAdd;
    Vec axis;
    Vec translation;
    Vec4d clipInput;
    Vec4d clipOutput;
    Quaternion axisQuat;
    Quaternion meshQuat;
    Quaternion resultQuat;
    Mtx cameraMtx;
    Mtx invCameraMtx;
    Mtx meshMtx;
    Mtx transMtx;
    Mtx invTransMtx;
    Mtx quatMtx;
    Mtx44 screenMtx;

    basis.x = DAT_801dd4b0;
    basis.y = DAT_801dd4b4;
    basis.z = DAT_801dd4b8;

    cameraForward.x = CameraPcs._236_4_;
    cameraForward.y = CameraPcs._240_4_;
    cameraForward.z = CameraPcs._244_4_;
    cameraRefPos.x = CameraPcs._224_4_;
    cameraRefPos.y = CameraPcs._228_4_;
    cameraRefPos.z = CameraPcs._232_4_;

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

    PSVECCrossProduct(&cameraForward, &basis, &cameraPos);
    PSVECNormalize(&cameraPos, &cameraPos);

    cameraOffset.x = *(float*)((u8*)param_2 + 0x18) * cameraPos.x + cameraRefPos.x;
    cameraOffset.y = cameraRefPos.y;
    cameraOffset.z = *(float*)((u8*)param_2 + 0x18) * cameraPos.z + cameraRefPos.z;

    PSMTXMultVec(cameraMtx, &cameraOffset, (Vec*)&clipInput);
    clipInput.w = FLOAT_80331cd0;
    MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math, screenMtx, &clipInput, &clipOutput);

    screenOffset.x = clipOutput.x * cameraForward.x;
    screenOffset.y = clipOutput.x * cameraForward.y;
    screenOffset.z = clipOutput.x * cameraForward.z;
    PSVECAdd(&cameraRefPos, &screenOffset, &screenOffset);

    PSMTXInverse(cameraMtx, invCameraMtx);
    PSMTXConcat(invCameraMtx, *(Mtx*)((u8*)model + 0x38), *(Mtx*)((u8*)model + 0x38));
    (*(Mtx*)((u8*)model + 0x38))[0][3] = screenOffset.x;
    (*(Mtx*)((u8*)model + 0x38))[1][3] = screenOffset.y;
    (*(Mtx*)((u8*)model + 0x38))[2][3] = screenOffset.z;

    if (*(float*)((u8*)param_3 + 0x30) != FLOAT_80331cc4) {
        PSVECScale((Vec*)((u8*)param_3 + 0x20), &gravityAdd, *(float*)((u8*)param_3 + 0x30));
    }

    for (u32 i = 0; i < *(u32*)(*(u8**)((u8*)model + 0xA4) + 0xC); i++) {
        if (*((char*)pieceData + 0x38) != '\0') {
            u8* node = *(u8**)((u8*)model + 0xA8) + (*(u32*)(*(u8**)(mesh + 8) + 0x5C) * 0xC0);
            u8* nodeMtx = node + 0xC;

            *(float*)(node + 0x18) = FLOAT_80331cc4;
            *(float*)(node + 0x28) = FLOAT_80331cc4;
            *(float*)(node + 0x38) = FLOAT_80331cc4;

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
            pieceData[4] = pieceData[1] * pieceData[0xC] -
                           FLOAT_80331cf4 * *(float*)((u8*)param_3 + 0x18) * pieceData[0xC] * pieceData[0xC];
            pieceData[5] -= pieceData[2];

            if (*(float*)((u8*)param_3 + 0x30) != FLOAT_80331cc4) {
                pieceData[3] += gravityAdd.x;
                pieceData[5] += gravityAdd.z;
            }

            pieceData[0xC] += FLOAT_80331cd0;

            translation.x = invTransMtx[0][3];
            translation.y = invTransMtx[1][3];
            translation.z = invTransMtx[2][3];
            PSVECAdd((Vec*)(pieceData + 3), &translation, &translation);
            invTransMtx[0][3] = translation.x;
            invTransMtx[1][3] = translation.y;
            invTransMtx[2][3] = translation.z;
            PSMTXConcat(invTransMtx, (float(*)[4])nodeMtx, (float(*)[4])nodeMtx);
        }

        mesh += 0x14;
        pieceData += 0xF;
    }

    return 1;
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
    Vec local_50;
    GXLightObj local_44;
    unsigned char colorStorage[4];
    unsigned int colorPacked;

    local_50.x = CameraPcs._236_4_ - (FLOAT_80331ce8 + CameraPcs._224_4_);
    local_50.y = CameraPcs._240_4_ - (FLOAT_80331ce8 + CameraPcs._228_4_);
    local_50.z = CameraPcs._244_4_ - (FLOAT_80331ce8 + CameraPcs._232_4_);
    PSVECNormalize(&local_50, &local_50);

    GXInitSpecularDirHA(&local_44, local_50.x, local_50.y, local_50.z, FLOAT_80331cc4, FLOAT_80331cd0, FLOAT_80331cc4);
    GXInitLightAttn(&local_44, FLOAT_80331cc4, FLOAT_80331cc4, FLOAT_80331cd0, FLOAT_80331cec, FLOAT_80331cc4,
                    FLOAT_80331cf0);

    colorPacked = *(unsigned int*)__ct__6CColorFUcUcUcUc(colorStorage, 0xFF, 0xFF, 0xFF, 0xFF);
    GXInitLightColor(&local_44, *(GXColor*)&colorPacked);
    GXLoadLightObjImm(&local_44, (GXLightID)1);
    GXSetChanCtrl((GXChannelID)0, 1, (GXColorSrc)0, (GXColorSrc)1, 1, (GXDiffuseFn)2, (GXAttnFn)0);
    GXSetChanCtrl((GXChannelID)2, 0, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
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
    u8* meshData = *(u8**)((u8*)model + 0xAC) + (meshIndex * 0x14);
    u8* refData = *(u8**)(meshData + 8);
    u8* displayList = *(u8**)(refData + 0x50) + (drawListIndex * 0xC);

    if (*(char*)((u8*)param_2 + 0x24) != '\0') {
        void* colorPtr;
        u8 colorStorage0[4];
        u32 colorPacked0;
        u8 colorStorage1[4];
        u32 colorPacked1;
        void* material;
        void* materialSet = *(void**)((u8*)*(u8**)((u8*)model + 0xA4) + 0x24);
        unsigned short materialIdx = *(unsigned short*)(displayList + 8);
        material = (*(void***)((u8*)materialSet + 0x18))[materialIdx];

        SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, materialSet, materialIdx, 1, 0);
        GXSetArray((GXAttr)0xB, (void*)((u8*)param_2 + 0x28), 4);

        if (*(short*)((u8*)material + 0x18) == 1) {
            GXSetNumChans(1);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
            colorPtr = __ct__6CColorFUcUcUcUc(colorStorage0, 0xA0, 0xA0, 0xA0, 0xA0);
            colorPacked0 = *(u32*)colorPtr;
            GXSetTevKColor((GXTevKColorID)0, *(GXColor*)&colorPacked0);
            GXSetTevKColorSel((GXTevStageID)0, (GXTevKColorSel)0xC);
            GXSetTevKAlphaSel((GXTevStageID)0, (GXTevKAlphaSel)0x1C);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 10, 0xE, 10, 0xF);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0xC, 0, 0, 1, 0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 4, 5, 7);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);

            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 0, 4);
            colorPtr = __ct__6CColorFUcUcUcUc(colorStorage1, 0x60, 0x60, 0x60, *(u8*)((u8*)param_2 + 0x2B));
            colorPacked1 = *(u32*)colorPtr;
            GXSetTevKColor((GXTevKColorID)1, *(GXColor*)&colorPacked1);
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
            GXLoadTexObj((_GXTexObj*)*(void**)((u8*)param_2 + 0x10), (GXTexMapID)0);
        }

        GXCallDisplayList(*(void**)displayList, *(unsigned int*)(displayList + 4));
    }
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

/*
 * --INFO--
 * PAL Address: 0x8012da2c
 * PAL Size: 1020b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InitPieceData(CChara::CModel* model, PScreenBreak* pppScreenBreak, VScreenBreak* work)
{
    const u32 meshCount = *(u32*)(*(u8**)model + 0xC);
    Vec* piece = *(Vec**)((u8*)work + 0xC);
    s16 maxX = -0x7FFF;
    s16 maxY = -0x7FFF;
    s16 maxZ = -0x7FFF;
    s32 meshList = *(s32*)((u8*)model + 0xAC);
    const float maxRand = FLOAT_80331cc8;
    const float minRand = -maxRand;
    Vec basis;

    memset(piece, 0, meshCount * 0x3C);

    basis.x = DAT_801dd4bc;
    basis.y = DAT_801dd4c0;
    basis.z = DAT_801dd4c4;

    for (u32 i = 0; i < meshCount; i++) {
        s32 refData = *(s32*)(meshList + 8);
        s32 node = *(s32*)((u8*)model + 0xA8) + (*(s32*)(refData + 0x5C) * 0xC0);
        s16 minLocalX = 0x7FFF;
        s16 minLocalY = 0x7FFF;
        s16 minLocalZ = 0x7FFF;
        s16 maxLocalX = -0x7FFF;
        s16 maxLocalY = -0x7FFF;
        s16 maxLocalZ = -0x7FFF;
        s32 vertexCount = *(s32*)(refData + 0x14);
        s32 vertexOffset = 0;
        s32 vertexBase = *(s32*)(refData + 0x18);
        S16Vec centerS16;
        float randVelocity;
        float angleRand;
        float maxAngle;

        *(u8*)(node + 0xBC) &= 0x7F;
        PSMTXIdentity((float(*)[4])(node + 0x14));

        while (vertexCount > 0) {
            s16 x = *(s16*)(vertexBase + vertexOffset);
            s16 y = *(s16*)(vertexBase + vertexOffset + 2);
            s16 z = *(s16*)(vertexBase + vertexOffset + 4);

            if (x > maxX) {
                maxX = x;
            }
            if (y > maxY) {
                maxY = y;
            }
            if (z > maxZ) {
                maxZ = z;
            }

            if (x < minLocalX) {
                minLocalX = x;
            }
            if (y < minLocalY) {
                minLocalY = y;
            }
            if (z < minLocalZ) {
                minLocalZ = z;
            }

            if (x > maxLocalX) {
                maxLocalX = x;
            }
            if (y > maxLocalY) {
                maxLocalY = y;
            }
            if (z > maxLocalZ) {
                maxLocalZ = z;
            }

            vertexOffset += 6;
            vertexCount--;
        }

        centerS16.x = maxLocalX + minLocalX;
        centerS16.y = maxLocalY + minLocalY;
        centerS16.z = maxLocalZ + minLocalZ;
        ConvI2FVector__5CUtilFR3Vec6S16Vecl(&DAT_8032ec70, piece + 3, &centerS16, *(u32*)(*(u8**)model + 0x34));
        PSVECScale(piece + 3, piece + 3, FLOAT_80331ccc);

        randVelocity = piece[3].x;
        if (randVelocity > maxRand) {
            randVelocity = RandF__5CMathFf(maxRand, &Math);
        } else if (randVelocity < minRand) {
            randVelocity = -RandF__5CMathFf(maxRand, &Math);
        }

        piece->x = randVelocity;
        piece->y = FLOAT_80331cd0;
        piece->z = FLOAT_80331cd4;
        PSVECNormalize(piece, piece);

        PSVECCrossProduct(piece, &basis, piece + 2);

        randVelocity = *(float*)((u8*)pppScreenBreak + 0x38) + RandF__5CMathFf(*(float*)((u8*)pppScreenBreak + 0x3C), &Math);
        PSVECScale(piece, piece, randVelocity);

        piece[1].x = FLOAT_80331cc4;
        piece[1].y = FLOAT_80331cc4;
        piece[1].z = FLOAT_80331cc4;
        piece[4].x = FLOAT_80331cc4;

        maxAngle = (float)(u8)*(u8*)((u8*)pppScreenBreak + 0x34);
        angleRand = RandF__5CMathFf(maxAngle, &Math);
        piece[4].y = (float)(FLOAT_80331cd8 * ((double)FLOAT_80331cc0 + (double)angleRand));
        *(u8*)&piece[4].z = 0;

        meshList += 0x14;
        piece += 5;
    }

    S16Vec worldMax;
    worldMax.x = maxX;
    worldMax.y = maxY;
    worldMax.z = maxZ;
    ConvI2FVector__5CUtilFR3Vec6S16Vecl(&DAT_8032ec70, (Vec*)((u8*)work + 0x18), &worldMax, *(u32*)(*(u8**)model + 0x34));
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
 * PAL Address: 0x8012d930
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConScreenBreak(PScreenBreak* pppScreenBreak, UnkC* param_2)
{
    s32 dataOffset = param_2->m_serializedDataOffsets[2];
    float* value = (float*)((u8*)pppScreenBreak + dataOffset + 0x80);
    void* gObject = *(void**)((u8*)pppMngStPtr + 0xD8);
    void* handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    float f = FLOAT_80331cc4;
    *(u32*)((u8*)gObject + 0x60) |= 0x40;
    *(void**)(model + 0xF0) = (void*)SB_BeforeDrawCallback;
    *(void**)(model + 0xFC) = (void*)SB_DrawMeshDLCallback;
    *(void**)(model + 0xF4) = (void*)SB_BeforeMeshLockEnvCallback;
    *(void**)(model + 0xEC) = (void*)SB_BeforeCalcMatrixCallback;
    value[3] = 0.0f;
    value[4] = 0.0f;
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
 * PAL Address: 0x8012d90c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCon2ScreenBreak(PScreenBreak* pppScreenBreak, UnkC* param_2)
{
    s32 dataOffset = param_2->m_serializedDataOffsets[2];
    float* value = (float*)((u8*)pppScreenBreak + dataOffset + 0x80);
    value[2] = FLOAT_80331cc4;
    value[1] = FLOAT_80331cc4;
    value[0] = FLOAT_80331cc4;
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
void pppDesScreenBreak(PScreenBreak* pppScreenBreak, UnkC* param_2)
{
    s32* serializedDataOffsets = *(s32**)param_2;
    s32 dataOffset = serializedDataOffsets[2];
    u8* pppData = ((u8*)pppScreenBreak + dataOffset + 0x80);
    void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((u8*)pppMngStPtr + 0xD8), 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
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
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameScreenBreak(PScreenBreak* pppScreenBreak, UnkB* param_2, UnkC* param_3)
{
    if (DAT_8032ed70 != 0) {
        return;
    }

    if (DAT_802381a0 != 0) {
        SetBlurParameter__11CGraphicPcsFiUcUcUcUcUcs(&GraphicsPcs, 0, 0, 0, 0, 0, 0, 0);
    }

    s32 index = param_3->m_serializedDataOffsets[0];
    float* value = (float*)((u8*)&pppScreenBreak->field0_0x0 + 8 + param_3->m_serializedDataOffsets[2]);
    void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((u8*)pppMngStPtr + 0xD8), 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(float**)(model + 0xE4) = value;
    *(UnkB**)(model + 0xE8) = param_2;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

    u8* color = (u8*)(value + 10);
    color[0] = (&pppScreenBreak->field_0x88)[index];
    color[1] = (&pppScreenBreak->field_0x89)[index];
    color[2] = (&pppScreenBreak->field_0x8a)[index];
    color[3] = (&pppScreenBreak->field_0x8b)[index];
    DCFlushRange(value + 10, 4);

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(param_2->m_stepValue, &pppScreenBreak->field0_0x0, param_2->m_graphId,
                                                 value, value + 1, value + 2, &param_2->m_arg3, (float*)param_2->m_payload);

    u32 pieceCount = *(u32*)(*(u8**)(model + 0xA4) + 0xC);
    if (*(void**)&value[3] == NULL) {
        *(void**)&value[3] = pppMemAlloc__FUlPQ27CMemory6CStagePci(pieceCount * 0x3C, pppEnvStPtr->m_stagePtr,
                                                                    s_pppScreenBreak_cpp_801dd4d4, 0x25E);
        *(void**)&value[4] = pppMemAlloc__FUlPQ27CMemory6CStagePci(0x20, pppEnvStPtr->m_stagePtr,
                                                                    s_pppScreenBreak_cpp_801dd4d4, 0x25F);
        InitPieceData((CChara::CModel*)model, pppScreenBreak, (VScreenBreak*)param_2);
        PSVECNormalize((Vec*)(param_2->m_payload + 0xC), (Vec*)(param_2->m_payload + 0xC));
    }

    float sx = FLOAT_80331cc0 * value[6];
    float sy = FLOAT_80331cc0 * value[7];
    u8* piece = (u8*)*(void**)&value[3];
    for (u32 i = 0; i < pieceCount; i++) {
        switch ((u8)param_2->m_initWOrk) {
        case 0:
            piece[0x38] = 1;
            break;
        case 1:
            if (-*(float*)(piece + 0x28) < (*value * sy) - value[7]) {
                piece[0x38] = 1;
            }
            break;
        case 2:
            if (-((*value * sy) - value[7]) < -*(float*)(piece + 0x28)) {
                piece[0x38] = 1;
            }
            break;
        case 3:
            if (-*(float*)(piece + 0x24) < (*value * sx) - value[6]) {
                piece[0x38] = 1;
            }
            break;
        case 4:
            if (-((*value * sx) - value[6]) < -*(float*)(piece + 0x24)) {
                piece[0x38] = 1;
            }
            break;
        case 5: {
            float x = *value * value[6];
            float y = *value * value[7];
            if ((*(float*)(piece + 0x24) <= x) && (-*(float*)(piece + 0x24) <= x) &&
                (*(float*)(piece + 0x28) <= y) && (-*(float*)(piece + 0x28) <= y)) {
                piece[0x38] = 1;
            }
            break;
        }
        case 6: {
            float x = *value * value[6];
            float y = *value * value[7];
            if (((value[6] - x <= -*(float*)(piece + 0x24)) || (-*(float*)(piece + 0x24) <= -value[6] + x) ||
                 (value[7] - y <= -*(float*)(piece + 0x28)) || (-*(float*)(piece + 0x28) <= -value[7] + y))) {
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
 * PAL Address: 0x8012d458
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderScreenBreak(PScreenBreak* pppScreenBreak, UnkB*, UnkC* param_3)
{
    s32 dataOffset = param_3->m_serializedDataOffsets[2];
    u8* value = (u8*)pppScreenBreak + dataOffset + 0x80;

    if (value[0x24] == 0) {
        Graphic.GetBackBufferRect2(*(void**)((u8*)&Graphic + 0x71EC), *(_GXTexObj**)(value + 0x10), 0, 0, 0x280, 0x1C0,
                                   0, (_GXTexFilter)0, (_GXTexFmt)0, 0);
        value[0x24] = 1;
    }
}
