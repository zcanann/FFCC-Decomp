#include "ffcc/pppYmEnv.h"
#include "ffcc/gobject.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/graphic.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppGetRotMatrixXZY.h"
#include "ffcc/pppGetRotMatrixYXZ.h"
#include "ffcc/pppGetRotMatrixYZX.h"
#include "ffcc/pppGetRotMatrixZXY.h"
#include "ffcc/pppGetRotMatrixZYX.h"
#include "ffcc/util.h"

#include <math.h>

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
int SearchNodeSk__Q26CChara6CModelFPc(CChara::CModel*, char*);
void CalcFrameMatrix__Q26CChara6CModelFfPQ26CChara5CNodePA4_f(CChara::CModel*, float, void*, float (*)[4]);
void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
    int tevSwapSel, int red, int green, int blue, int alpha);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int stage, int a, int b, int c, int d);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int stage, int op, int bias,
                                                                                           int scale, int clamp,
                                                                                           int reg);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int stage, int texCoord, int texMap,
                                                                                 int colorChannel);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int stage, int a, int b, int c, int d);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int stage, int op, int bias,
                                                                                           int scale, int clamp,
                                                                                           int reg);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int type, int src, int dst, int op);
}

extern CUtil DAT_8032ec70;

struct _pppEnvStYmEnv {
    void* m_stagePtr;
    CMaterialSet* m_materialSetPtr;
    CMapMesh** m_mapMeshPtr;
};

struct CTextureLite {
    char pad_0x0[0x28];
    GXTexObj m_texObj;
    GXTlutObj m_tlutObj0;
    GXTlutObj m_tlutObj1;
};

/*
 * --INFO--
 * PAL Address: 0x800e602c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CModel* GetModelPtr(CGObject* gObject)
{
    if (gObject == 0) {
        return 0;
    }

    CCharaPcs::CHandle* handle = gObject->m_charaModelHandle;
    if (handle == 0) {
        return 0;
    }

    return handle->m_model;
}
/*
 * --INFO--
 * PAL Address: 0x800e591c
 * PAL Size: 1808b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GetCharaNodeFrameMatrix(_pppMngSt* mngSt, float frameAdd, float (*outMatrix)[4])
{
    float one = 1.0f;
    s16 nodeIndex = *(s16*)((u8*)mngSt + 0x76);
    char* nodeNameBase;

    if (Game.game.m_currentSceneId == 7) {
        nodeNameBase = (char*)(*(u32*)((u8*)mngSt + 0x0) + nodeIndex * 0x60);
    } else {
        nodeNameBase = (char*)(*(u32*)((u8*)mngSt + 0x0) + nodeIndex * 0x60 + 0x20);
    }

    CGObject* owner = *(CGObject**)((u8*)mngSt + 0xD8);
    if (owner == 0) {
        return 0;
    }

    CChara::CModel* model = GetModelPtr(owner);
    if (model == 0) {
        return 0;
    }

    int skNodeIndex = SearchNodeSk__Q26CChara6CModelFPc(model, nodeNameBase + 0x50);
    if (skNodeIndex == -1) {
        return 0;
    }

    u8* modelBytes = (u8*)model;
    u16 animFrameMax = 0;
    void* anim = *(void**)(modelBytes + 0xD0);
    if (anim != 0) {
        animFrameMax = *(u16*)((u8*)anim + 0x10);
    }
    if (animFrameMax == 0) {
        return 0;
    }

    int frameInt = (int)*(float*)(modelBytes + 0xD4);
    int frameMod = frameInt % (int)animFrameMax;
    float frame = (float)frameMod;
    if (frame < 0.0f) {
        return 0;
    }
    if (frame != 0.0f) {
        frame -= 1.0f;
    }

    void* nodeList = *(void**)(modelBytes + 0xA8);
    CalcFrameMatrix__Q26CChara6CModelFfPQ26CChara5CNodePA4_f(model, frame + frameAdd, (u8*)nodeList + skNodeIndex * 0xC0,
                                                              outMatrix);

    pppFMATRIX localMatrix;
    switch (*(u8*)((u8*)mngSt + 0xEC)) {
    case 0:
        pppGetRotMatrixXYZ(localMatrix, (pppIVECTOR4*)((u8*)mngSt + 0x18));
        break;
    case 1:
        pppGetRotMatrixXZY(localMatrix, (pppIVECTOR4*)((u8*)mngSt + 0x18));
        break;
    case 2:
        pppGetRotMatrixYXZ(localMatrix, (pppIVECTOR4*)((u8*)mngSt + 0x18));
        break;
    case 3:
        pppGetRotMatrixYZX(localMatrix, (pppIVECTOR4*)((u8*)mngSt + 0x18));
        break;
    case 4:
        pppGetRotMatrixZXY(localMatrix, (pppIVECTOR4*)((u8*)mngSt + 0x18));
        break;
    case 5:
        pppGetRotMatrixZYX(localMatrix, (pppIVECTOR4*)((u8*)mngSt + 0x18));
        break;
    default:
        break;
    }

    u8 matrixMode = *(u8*)((u8*)mngSt + 0xE7);
    if (matrixMode == 5) {
        if (*(void**)((u8*)mngSt + 0xE0) != 0) {
            outMatrix[0][3] += pppMngStPtr->m_position.x;
            outMatrix[1][3] += pppMngStPtr->m_position.y;
            outMatrix[2][3] += pppMngStPtr->m_position.z;
            PSMTXConcat(outMatrix, localMatrix.value, localMatrix.value);

            if (*(float*)((u8*)mngSt + 0x28) != one) {
                Vec col;
                col.x = localMatrix.value[0][0];
                col.y = localMatrix.value[1][0];
                col.z = localMatrix.value[2][0];
                PSVECScale(&col, &col, *(float*)((u8*)mngSt + 0x28));
                localMatrix.value[0][0] = col.x;
                localMatrix.value[1][0] = col.y;
                localMatrix.value[2][0] = col.z;
            }
            if (*(float*)((u8*)mngSt + 0x2C) != one) {
                Vec col;
                col.x = localMatrix.value[0][1];
                col.y = localMatrix.value[1][1];
                col.z = localMatrix.value[2][1];
                PSVECScale(&col, &col, *(float*)((u8*)mngSt + 0x2C));
                localMatrix.value[0][1] = col.x;
                localMatrix.value[1][1] = col.y;
                localMatrix.value[2][1] = col.z;
            }
            if (*(float*)((u8*)mngSt + 0x30) != one) {
                Vec col;
                col.x = localMatrix.value[0][2];
                col.y = localMatrix.value[1][2];
                col.z = localMatrix.value[2][2];
                PSVECScale(&col, &col, *(float*)((u8*)mngSt + 0x30));
                localMatrix.value[0][2] = col.x;
                localMatrix.value[1][2] = col.y;
                localMatrix.value[2][2] = col.z;
            }
            PSMTXCopy(localMatrix.value, outMatrix);
            return 1;
        }
    } else if (matrixMode < 5) {
        if (matrixMode == 3 && *(void**)((u8*)mngSt + 0xE0) != 0) {
            Vec pos;
            PSMTXMultVecSR(outMatrix, &pppMngStPtr->m_position, &pos);
            outMatrix[0][3] += pos.x;
            outMatrix[1][3] += pos.y;
            outMatrix[2][3] += pos.z;
            PSMTXConcat(outMatrix, localMatrix.value, localMatrix.value);

            Vec col0;
            Vec col1;
            Vec col2;
            col0.x = localMatrix.value[0][0];
            col0.y = localMatrix.value[1][0];
            col0.z = localMatrix.value[2][0];
            PSVECScale(&col0, &col0, *(float*)((u8*)mngSt + 0x28));
            localMatrix.value[0][0] = col0.x;
            localMatrix.value[1][0] = col0.y;
            localMatrix.value[2][0] = col0.z;

            col1.x = localMatrix.value[0][1];
            col1.y = localMatrix.value[1][1];
            col1.z = localMatrix.value[2][1];
            PSVECScale(&col1, &col1, *(float*)((u8*)mngSt + 0x2C));
            localMatrix.value[0][1] = col1.x;
            localMatrix.value[1][1] = col1.y;
            localMatrix.value[2][1] = col1.z;

            col2.x = localMatrix.value[0][2];
            col2.y = localMatrix.value[1][2];
            col2.z = localMatrix.value[2][2];
            PSVECScale(&col2, &col2, *(float*)((u8*)mngSt + 0x30));
            localMatrix.value[0][2] = col2.x;
            localMatrix.value[1][2] = col2.y;
            localMatrix.value[2][2] = col2.z;
            PSMTXCopy(localMatrix.value, outMatrix);
            return 1;
        }
    } else if (matrixMode < 7 && *(void**)((u8*)mngSt + 0xE0) != 0) {
        Vec col0;
        Vec col1;
        Vec col2;
        Vec pos;
        col0.x = outMatrix[0][0];
        col0.y = outMatrix[1][0];
        col0.z = outMatrix[2][0];
        col1.x = outMatrix[0][1];
        col1.y = outMatrix[1][1];
        col1.z = outMatrix[2][1];
        col2.x = outMatrix[0][2];
        col2.y = outMatrix[1][2];
        col2.z = outMatrix[2][2];
        PSVECNormalize(&col0, &col0);
        PSVECNormalize(&col1, &col1);
        PSVECNormalize(&col2, &col2);
        outMatrix[0][0] = col0.x;
        outMatrix[1][0] = col0.y;
        outMatrix[2][0] = col0.z;
        outMatrix[0][1] = col1.x;
        outMatrix[1][1] = col1.y;
        outMatrix[2][1] = col1.z;
        outMatrix[0][2] = col2.x;
        outMatrix[1][2] = col2.y;
        outMatrix[2][2] = col2.z;

        PSMTXMultVecSR(outMatrix, &pppMngStPtr->m_position, &pos);
        PSMTXConcat(outMatrix, localMatrix.value, localMatrix.value);
        if (*(float*)((u8*)mngSt + 0x28) != one) {
            Vec col;
            col.x = localMatrix.value[0][0];
            col.y = localMatrix.value[1][0];
            col.z = localMatrix.value[2][0];
            PSVECScale(&col, &col, *(float*)((u8*)mngSt + 0x28));
            localMatrix.value[0][0] = col.x;
            localMatrix.value[1][0] = col.y;
            localMatrix.value[2][0] = col.z;
        }
        if (*(float*)((u8*)mngSt + 0x2C) != one) {
            Vec col;
            col.x = localMatrix.value[0][1];
            col.y = localMatrix.value[1][1];
            col.z = localMatrix.value[2][1];
            PSVECScale(&col, &col, *(float*)((u8*)mngSt + 0x2C));
            localMatrix.value[0][1] = col.x;
            localMatrix.value[1][1] = col.y;
            localMatrix.value[2][1] = col.z;
        }
        if (*(float*)((u8*)mngSt + 0x30) != one) {
            Vec col;
            col.x = localMatrix.value[0][2];
            col.y = localMatrix.value[1][2];
            col.z = localMatrix.value[2][2];
            PSVECScale(&col, &col, *(float*)((u8*)mngSt + 0x30));
            localMatrix.value[0][2] = col.x;
            localMatrix.value[1][2] = col.y;
            localMatrix.value[2][2] = col.z;
        }
        localMatrix.value[0][3] += pos.x;
        localMatrix.value[1][3] += pos.y;
        localMatrix.value[2][3] += pos.z;
        PSMTXCopy(localMatrix.value, outMatrix);
        return 1;
    }

    if (*(float*)((u8*)mngSt + 0x28) != one) {
        Vec col;
        col.x = localMatrix.value[0][0];
        col.y = localMatrix.value[1][0];
        col.z = localMatrix.value[2][0];
        PSVECScale(&col, &col, *(float*)((u8*)mngSt + 0x28));
        localMatrix.value[0][0] = col.x;
        localMatrix.value[1][0] = col.y;
        localMatrix.value[2][0] = col.z;
    }
    if (*(float*)((u8*)mngSt + 0x2C) != one) {
        Vec col;
        col.x = localMatrix.value[0][1];
        col.y = localMatrix.value[1][1];
        col.z = localMatrix.value[2][1];
        PSVECScale(&col, &col, *(float*)((u8*)mngSt + 0x2C));
        localMatrix.value[0][1] = col.x;
        localMatrix.value[1][1] = col.y;
        localMatrix.value[2][1] = col.z;
    }
    if (*(float*)((u8*)mngSt + 0x30) != one) {
        Vec col;
        col.x = localMatrix.value[0][2];
        col.y = localMatrix.value[1][2];
        col.z = localMatrix.value[2][2];
        PSVECScale(&col, &col, *(float*)((u8*)mngSt + 0x30));
        localMatrix.value[0][2] = col.x;
        localMatrix.value[1][2] = col.y;
        localMatrix.value[2][2] = col.z;
    }

    localMatrix.value[0][3] = *(float*)((u8*)mngSt + 0x8);
    localMatrix.value[1][3] = *(float*)((u8*)mngSt + 0xC);
    localMatrix.value[2][3] = *(float*)((u8*)mngSt + 0x10);
    PSMTXCopy(localMatrix.value, outMatrix);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800e58c0
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CalcGraphValue(_pppPObject* object, long graphId, float& value, float& velocity, float& acceleration, float addValue,
                    float& velocityAdd, float& accelerationAdd)
{
    velocity += acceleration;
    value += velocity;

    if (graphId == object->m_graphId) {
        value += addValue;
        velocity += velocityAdd;
        acceleration += accelerationAdd;
    }
}
/*
 * --INFO--
 * PAL Address: 0x800e5870
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GetTextureFromRSD(int mapMeshIndex, _pppEnvSt* env)
{
    _pppEnvStYmEnv* ymEnv = (_pppEnvStYmEnv*)env;
    int textureIndex;
    CMapMesh** mapMeshArray;

    if (mapMeshIndex == 0xFFFF) {
        return 0;
    }

    mapMeshArray = ymEnv->m_mapMeshPtr;
    textureIndex = 0;
    return GetTexture__8CMapMeshFP12CMaterialSetRi(mapMeshArray[mapMeshIndex], ymEnv->m_materialSetPtr, textureIndex);
}

/*
 * --INFO--
 * PAL Address: 0x800e5858
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CModel* GetCharaModelPtr(CCharaPcs::CHandle* handle)
{
    if (handle != 0) {
        return handle->m_model;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800e57f0
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CCharaPcs::CHandle* GetCharaHandlePtr(CGObject* gObject, long modelType)
{
    if (gObject == 0) {
        return 0;
    }

    if (modelType == 1) {
        if (gObject->m_weaponModelHandle != 0) {
            return gObject->m_weaponModelHandle;
        }
    } else if (modelType < 1) {
        if (modelType >= 0 && gObject->m_charaModelHandle != 0) {
            return gObject->m_charaModelHandle;
        }
    } else if (modelType < 3 && gObject->m_shieldModelHandle != 0) {
        return gObject->m_shieldModelHandle;
    }

    return 0;
}
/*
 * --INFO--
 * PAL Address: 0x800e5780
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void DisableIndWarp(_GXTevStageID tevStage, _GXIndTexStageID indStage)
{
    float indMtx[2][3];

    GXSetTevDirect((GXTevStageID)tevStage);
    GXSetNumIndStages(0);
    GXSetIndTexCoordScale((GXIndTexStageID)indStage, GX_ITS_1, GX_ITS_1);

    indMtx[0][0] = 0.0f;
    indMtx[0][1] = 0.0f;
    indMtx[0][2] = 0.0f;
    indMtx[1][0] = 0.0f;
    indMtx[1][1] = 0.0f;
    indMtx[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_1, indMtx, 1);
}

/*
 * --INFO--
 * PAL Address: 0x800e54dc
 * PAL Size: 676b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetUpPaletteEnv(CTexture* texture)
{
    GXColorS10 tevColor2;
    GXColorS10 tevColor3;
    CTextureLite* textureLite;

    GXSetNumTevStages(3);
    GXSetNumTexGens(1);

    tevColor2.r = -1;
    tevColor2.g = 0;
    tevColor2.b = 0;
    tevColor2.a = -1;
    GXSetTevColorS10((GXTevRegID)2, tevColor2);

    tevColor3.r = 0;
    tevColor3.g = 0;
    tevColor3.b = 0;
    tevColor3.a = -1;
    GXSetTevColorS10((GXTevRegID)3, tevColor3);

    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(1, 0, 3,
                                                                                                                     3, 3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(2, 2, 2,
                                                                                                                     2, 3);

    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 8, 4,
                                                                                                          0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 0, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 0xFF);

    GXSetTevDirect(GX_TEVSTAGE1);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xF, 8, 6,
                                                                                                          0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 6, 4,
                                                                                                          7);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 2);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 1, 0xFF);

    GXSetTevDirect(GX_TEVSTAGE2);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xF, 0, 10,
                                                                                                          0xF);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 0, 5,
                                                                                                          7);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 1, 1, 0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 2, 1, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0xFF, 0xFF, 4);

    textureLite = (CTextureLite*)texture;
    GXInitTexObjTlut(&textureLite->m_texObj, GX_TLUT0);
    GXLoadTexObj(&textureLite->m_texObj, GX_TEXMAP0);
    GXInitTexObjTlut(&textureLite->m_texObj, GX_TLUT1);
    GXLoadTexObj(&textureLite->m_texObj, GX_TEXMAP1);
    GXLoadTlut(&textureLite->m_tlutObj0, GX_TLUT0);
    GXLoadTlut(&textureLite->m_tlutObj1, GX_TLUT1);
}

/*
 * --INFO--
 * PAL Address: 0x800e4fb8
 * PAL Size: 1316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void genParaboloidMap(void* displayListBuffer, unsigned long* outDisplayListSize, unsigned short detail, _GXVtxFmt vtxFmt)
{
    static const char s_pppYmEnv_cpp[] = "pppYmEnv.cpp";
    static const char s_exiting[] = "Exiting";
    static const char s_display_list_alloc_error[] = "Error allocating display list. Need %u bytes\n";
    const float kZero = 0.0f;
    const float kOne = 1.0f;
    const float kPi = 3.1415927f;
    const float kHalfPi = 1.5707964f;
    const float kNormalScale = 0.5f;

    const unsigned int rings = detail;
    const int ringVertexCount = rings + 1;
    const unsigned int displayListSize = ((ringVertexCount + (rings - 2) * ringVertexCount * 2) * 0x18 + 0x1F) & ~0x1F;

    DCInvalidateRange(displayListBuffer, displayListSize);
    GXBeginDisplayList(displayListBuffer, displayListSize);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt((GXVtxFmt)vtxFmt, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt((GXVtxFmt)vtxFmt, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);

    const float latStep = kHalfPi / (float)rings;
    const float firstLat = latStep;
    const float firstRingSin = (float)sin(firstLat);
    const float firstRingCos = (float)cos(firstLat);

    GXBegin(GX_TRIANGLEFAN, (GXVtxFmt)vtxFmt, rings + 2);
    GXPosition3f32(kZero, kZero, kOne);
    GXNormal3f32(kZero, kZero, kOne);

    for (unsigned int i = 0; i <= rings; i++) {
        const float lon = (2.0f * kPi * (float)i) / (float)rings;
        const float lonSin = (float)sin(lon);
        const float lonCos = (float)cos(lon);

        const float x = firstRingSin * lonCos;
        const float y = firstRingSin * lonSin;
        const float z = firstRingCos;

        GXPosition3f32(x, y, z);
        GXNormal3f32(kNormalScale * x * z, kNormalScale * y * z, z * z);
    }

    for (unsigned int ring = 2; ring < rings; ring++) {
        const float upperLat = (kHalfPi * (float)(ring - 1)) / (float)rings;
        const float lowerLat = (kHalfPi * (float)ring) / (float)rings;

        const float upperSin = (float)sin(upperLat);
        const float upperCos = (float)cos(upperLat);
        const float lowerSin = (float)sin(lowerLat);
        const float lowerCos = (float)cos(lowerLat);

        if ((float)fabs(upperCos) < 1.0e-6f || (float)fabs(lowerCos) < 1.0e-6f) {
            break;
        }

        GXBegin(GX_TRIANGLESTRIP, (GXVtxFmt)vtxFmt, ringVertexCount * 2);
        for (unsigned int i = 0; i <= rings; i++) {
            const float lon = (2.0f * kPi * (float)i) / (float)rings;
            const float lonSin = (float)sin(lon);
            const float lonCos = (float)cos(lon);

            const float lx = lowerSin * lonCos;
            const float ly = lowerSin * lonSin;
            GXPosition3f32(lx, ly, lowerCos);
            GXNormal3f32(kNormalScale * lx * lowerCos, kNormalScale * ly * lowerCos, lowerCos * lowerCos);

            const float ux = upperSin * lonCos;
            const float uy = upperSin * lonSin;
            GXPosition3f32(ux, uy, upperCos);
            GXNormal3f32(kNormalScale * ux * upperCos, kNormalScale * uy * upperCos, upperCos * upperCos);
        }
    }

    *outDisplayListSize = GXEndDisplayList();
    if (displayListSize < *outDisplayListSize) {
        OSReport(s_display_list_alloc_error, displayListSize);
        OSPanic(s_pppYmEnv_cpp, 0x19f, s_exiting);
    }

    DCFlushRange(displayListBuffer, *outDisplayListSize);
}

/*
 * --INFO--
 * PAL Address: 0x800e46dc
 * PAL Size: 2268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void drawParaboloidMap(_GXTexObj* texObjs, _GXTexObj* targetTexObj, void* displayList, unsigned long displayListSize,
                       _GXTexObj* blendTexObj, unsigned char mode)
{
    static const unsigned char s_texObjIndices[] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
    static const unsigned char s_xAxisRotIndices[] = {0, 0, 0, 1, 1, 0, 0, 0, 1, 1};
    static const unsigned char s_yAxisRotIndices[] = {0, 1, 0, 0, 1, 0, 1, 0, 0, 1};
    static const float s_xAxisAngles[] = {0.0f, 90.0f, 180.0f, 270.0f};
    static const unsigned char s_xAxisIds[] = {'x', 'x', 'x', 'x'};
    static const float s_yAxisAngles[] = {0.0f, 1.0f};
    static const Vec s_cameraPos = {0.0f, 0.0f, 0.0f};
    static const Vec s_cameraUp = {0.0f, 1.0f, 0.0f};
    static const Vec s_cameraLook = {0.0f, 0.0f, -1.0f};

    const unsigned short texWidth = GXGetTexObjWidth(targetTexObj);
    const unsigned short texHeight = GXGetTexObjHeight(targetTexObj);
    const unsigned short modeOffset = (unsigned short)mode * 5;

    _GXColor clearColor = {0, 0, 0, 0xFF};
    _GXColor whiteColor = {0xFF, 0xFF, 0xFF, 0xFF};
    _GXColor blackColor = {0, 0, 0, 0};

    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    DAT_8032ec70.RenderColorQuad(0.0f, 0.0f, texWidth, texHeight, clearColor);

    const unsigned short rtWidth = GXGetTexObjWidth(targetTexObj);
    const unsigned short rtHeight = GXGetTexObjHeight(targetTexObj);
    const GXTexFmt targetFmt = GXGetTexObjFmt(targetTexObj);
    void* targetData = GXGetTexObjData(targetTexObj);

    Mtx44 orthoMtx;
    C_MTXOrtho(orthoMtx, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);

    Mtx cameraMtx;
    C_MTXLookAt(cameraMtx, &s_cameraPos, &s_cameraUp, &s_cameraLook);
    GXLoadPosMtxImm(cameraMtx, 0);

    GXSetCullMode(GX_CULL_BACK);
    GXSetViewport(0.0f, 0.0f, rtWidth, rtHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, rtWidth, rtHeight);
    GXSetTexCopySrc(0, 0, rtWidth, rtHeight);
    GXSetTexCopyDst(rtWidth, rtHeight, targetFmt, GX_FALSE);

    GXSetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT1, GX_DF_NONE, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, whiteColor);
    GXSetChanAmbColor(GX_COLOR0A0, blackColor);

    GXLightObj lightObj;
    GXInitLightColor(&lightObj, whiteColor);
    GXInitLightAttnA(&lightObj, 0.0f, 1.0f, 0.0f);
    GXInitLightAttnK(&lightObj, 0.0f, 0.0f, 0.0f);
    GXInitLightPos(&lightObj, 0.0f, 0.0f, 1.0f);
    GXInitLightDir(&lightObj, 0.0f, 0.0f, 1.0f);
    GXLoadLightObjImm(&lightObj, GX_LIGHT1);

    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_NRM, 0x1E, GX_FALSE, GX_PTIDENTITY);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 0xF, 0xF,
                                                                                                          8);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 4, 5, 7);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);

    Mtx lightFrustumMtx;
    C_MTXLightFrustum(lightFrustumMtx, 1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 0xF);

    if (blendTexObj != 0) {
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 0xF,
                                                                                                              0xF, 0xF);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 4, 5,
                                                                                                              7);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xF, 8, 1,
                                                                                                              0xF);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 7, 4,
                                                                                                              0);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTevDirect(GX_TEVSTAGE1);
        GXSetNumTevStages(2);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_NRM, 0x1E, GX_FALSE, GX_PTIDENTITY);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 1, 4);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
        GXSetChanMatColor(GX_COLOR0A0, whiteColor);
        GXLoadTexObj(blendTexObj, GX_TEXMAP0);
    }

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);

    const float kDegToRad = 0.017453292f;
    for (int i = 0; i < 5; i++) {
        const unsigned char texObjIdx = s_texObjIndices[modeOffset + i];
        const unsigned char xRotIdx = s_xAxisRotIndices[modeOffset + i];
        const unsigned char yRotIdx = s_yAxisRotIndices[modeOffset + i];

        if (blendTexObj == 0) {
            GXLoadTexObj(&texObjs[texObjIdx], GX_TEXMAP0);
        } else {
            GXLoadTexObj(&texObjs[texObjIdx], GX_TEXMAP1);
        }

        Mtx objectMtx;
        Mtx tempMtx;
        PSMTXIdentity(objectMtx);

        if (s_yAxisAngles[yRotIdx] != 0.0f) {
            PSMTXRotRad(tempMtx, 'y', kDegToRad * s_yAxisAngles[yRotIdx]);
            PSMTXConcat(objectMtx, tempMtx, objectMtx);
        }

        PSMTXRotRad(tempMtx, s_xAxisIds[xRotIdx], kDegToRad * s_xAxisAngles[xRotIdx]);
        PSMTXConcat(objectMtx, tempMtx, objectMtx);
        PSMTXConcat(lightFrustumMtx, objectMtx, objectMtx);

        GXLoadTexMtxImm(objectMtx, 0x1E, GX_MTX3x4);
        GXLoadNrmMtxImm(objectMtx, 0);
        GXCallDisplayList(displayList, displayListSize);
    }

    Graphic.GetBackBufferRect2(targetData, targetTexObj, 0, 0, texWidth, texHeight, 0, GX_LINEAR, GX_TF_RGBA8, 0);
    GXSetScissor(0, 0, 0x280, 0x1C0);
    Graphic.SetViewport();

    if (mode != 0) {
        DAT_8032ec70.RenderTextureQuad(0.0f, 0.0f, rtWidth, rtHeight, targetTexObj, 0, 0, 0, (GXBlendFactor)4,
                                       (GXBlendFactor)5);
        Graphic.GetBackBufferRect2(targetData, targetTexObj, 0, 0, texWidth, texHeight, 0, GX_LINEAR, GX_TF_RGBA8, 0);
    }
}
