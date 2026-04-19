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

struct GraphValueState {
    float value;
    float velocity;
    float acceleration;
    s32 graphId;
};

struct Vec2d {
    float x;
    float y;
};

struct PartMngEditRaw {
    u8 m_pad00[0x23554];
    void* m_recvBuff;
};

struct CAnimRaw {
    u8 m_pad00[0x10];
    u16 m_frameCount;
};

struct CModelRaw {
    u8 m_pad00[0xA8];
    u8* m_nodes;
    u8 m_padAC[0x24];
    CAnimRaw* m_anim;
    float m_time;
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

    CChara::CModel* model = handle->m_model;
    if (model == 0) {
        return 0;
    }

    return model;
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
    void* nodeNameBase;
    CModelRaw* modelRaw;
    CChara::CModel* model;
    int skNodeIndex;
    int animFrameMax;
    int frameInt;
    float frame;
    Vec local88;
    Vec local94;
    Vec localA0;
    Vec localAC;
    Vec localB8;
    Vec localC4;
    Vec localD0;
    Vec localDC;
    Vec localE8;
    Vec localF4;
    Vec local100;
    Vec local10C;
    Vec local118;
    pppFMATRIX localMatrix;

    if (Game.m_currentSceneId == 7) {
        nodeNameBase = (u8*)(reinterpret_cast<PartMngEditRaw*>(&PartMng)->m_recvBuff) + mngSt->m_nodeIndex * 0x60;
    } else {
        nodeNameBase = (u8*)(*(u32*)mngSt->m_pppResSet) + mngSt->m_nodeIndex * 0x60 + 0x20;
    }

    if (mngSt->m_owner == 0) {
        return 0;
    }

    CCharaPcs::CHandle* handle = ((CGObject*)mngSt->m_owner)->m_charaModelHandle;
    if (handle == 0) {
        return 0;
    }

    model = handle->m_model;
    if (model == 0) {
        return 0;
    }

    skNodeIndex = SearchNodeSk__Q26CChara6CModelFPc(model, (char*)nodeNameBase + 0x50);
    if (skNodeIndex == -1) {
        return 0;
    }

    modelRaw = (CModelRaw*)model;
    if (modelRaw->m_anim == 0) {
        animFrameMax = 0;
    } else {
        animFrameMax = modelRaw->m_anim->m_frameCount;
    }

    frameInt = (int)modelRaw->m_time;
    frame = (float)(frameInt - (frameInt / animFrameMax) * animFrameMax);
    if (frame < 0.0f) {
        return 0;
    }

    if (frame != 0.0f) {
        frame -= 1.0f;
    }

    CalcFrameMatrix__Q26CChara6CModelFfPQ26CChara5CNodePA4_f(model, frame + frameAdd,
                                                              (CChara::CNode*)(modelRaw->m_nodes + skNodeIndex * 0xC0),
                                                              outMatrix);

    u8 rotationOrder = mngSt->m_rotationOrder;
    if (rotationOrder == 3) {
        pppGetRotMatrixYZX(localMatrix, &mngSt->m_rotation);
    } else if (rotationOrder < 3) {
        if (rotationOrder == 1) {
            pppGetRotMatrixXZY(localMatrix, &mngSt->m_rotation);
        } else if (rotationOrder == 0) {
            pppGetRotMatrixXYZ(localMatrix, &mngSt->m_rotation);
        } else {
            pppGetRotMatrixYXZ(localMatrix, &mngSt->m_rotation);
        }
    } else if (rotationOrder == 5) {
        pppGetRotMatrixZYX(localMatrix, &mngSt->m_rotation);
    } else if (rotationOrder < 5) {
        pppGetRotMatrixZXY(localMatrix, &mngSt->m_rotation);
    }

    if (mngSt->m_matrixMode == 5) {
        if (mngSt->m_bindNode != 0) {
            outMatrix[0][3] += pppMngStPtr->m_position.x;
            outMatrix[1][3] += pppMngStPtr->m_position.y;
            outMatrix[2][3] += pppMngStPtr->m_position.z;
            PSMTXConcat(outMatrix, localMatrix.value, localMatrix.value);

            if (mngSt->m_scale.x != 1.0f) {
                localB8.x = localMatrix.value[0][0];
                localB8.y = localMatrix.value[1][0];
                localB8.z = localMatrix.value[2][0];
                PSVECScale(&localB8, &localB8, mngSt->m_scale.x);
                localMatrix.value[0][0] = localB8.x;
                localMatrix.value[1][0] = localB8.y;
                localMatrix.value[2][0] = localB8.z;
            }
            if (mngSt->m_scale.y != 1.0f) {
                localC4.x = localMatrix.value[0][1];
                localC4.y = localMatrix.value[1][1];
                localC4.z = localMatrix.value[2][1];
                PSVECScale(&localC4, &localC4, mngSt->m_scale.y);
                localMatrix.value[0][1] = localC4.x;
                localMatrix.value[1][1] = localC4.y;
                localMatrix.value[2][1] = localC4.z;
            }
            if (mngSt->m_scale.z != 1.0f) {
                localD0.x = localMatrix.value[0][2];
                localD0.y = localMatrix.value[1][2];
                localD0.z = localMatrix.value[2][2];
                PSVECScale(&localD0, &localD0, mngSt->m_scale.z);
                localMatrix.value[0][2] = localD0.x;
                localMatrix.value[1][2] = localD0.y;
                localMatrix.value[2][2] = localD0.z;
            }
            goto copy_out;
        }
    } else if (mngSt->m_matrixMode < 5) {
        if ((mngSt->m_matrixMode == 3) && (mngSt->m_bindNode != 0)) {
            PSMTXMultVecSR(outMatrix, &pppMngStPtr->m_position, &local88);
            outMatrix[0][3] += local88.x;
            outMatrix[1][3] += local88.y;
            outMatrix[2][3] += local88.z;
            PSMTXConcat(outMatrix, localMatrix.value, localMatrix.value);

            local94.x = localMatrix.value[0][0];
            local94.y = localMatrix.value[1][0];
            local94.z = localMatrix.value[2][0];
            PSVECScale(&local94, &local94, mngSt->m_scale.x);
            localMatrix.value[0][0] = local94.x;
            localMatrix.value[1][0] = local94.y;
            localMatrix.value[2][0] = local94.z;

            localA0.x = localMatrix.value[0][1];
            localA0.y = localMatrix.value[1][1];
            localA0.z = localMatrix.value[2][1];
            PSVECScale(&localA0, &localA0, mngSt->m_scale.y);
            localMatrix.value[0][1] = localA0.x;
            localMatrix.value[1][1] = localA0.y;
            localMatrix.value[2][1] = localA0.z;

            localAC.x = localMatrix.value[0][2];
            localAC.y = localMatrix.value[1][2];
            localAC.z = localMatrix.value[2][2];
            PSVECScale(&localAC, &localAC, mngSt->m_scale.z);
            localMatrix.value[0][2] = localAC.x;
            localMatrix.value[1][2] = localAC.y;
            localMatrix.value[2][2] = localAC.z;
            goto copy_out;
        }
    } else if ((mngSt->m_matrixMode < 7) && (mngSt->m_bindNode != 0)) {
        PSVECNormalize((Vec*)outMatrix, (Vec*)outMatrix);
        PSVECNormalize((Vec*)&outMatrix[0][1], (Vec*)&outMatrix[0][1]);
        PSVECNormalize((Vec*)&outMatrix[0][2], (Vec*)&outMatrix[0][2]);
        PSMTXMultVecSR(outMatrix, &pppMngStPtr->m_position, &local88);
        PSMTXConcat(outMatrix, localMatrix.value, localMatrix.value);

        if (mngSt->m_scale.x != 1.0f) {
            localDC.x = localMatrix.value[0][0];
            localDC.y = localMatrix.value[1][0];
            localDC.z = localMatrix.value[2][0];
            PSVECScale(&localDC, &localDC, mngSt->m_scale.x);
            localMatrix.value[0][0] = localDC.x;
            localMatrix.value[1][0] = localDC.y;
            localMatrix.value[2][0] = localDC.z;
        }
        if (mngSt->m_scale.y != 1.0f) {
            localE8.x = localMatrix.value[0][1];
            localE8.y = localMatrix.value[1][1];
            localE8.z = localMatrix.value[2][1];
            PSVECScale(&localE8, &localE8, mngSt->m_scale.y);
            localMatrix.value[0][1] = localE8.x;
            localMatrix.value[1][1] = localE8.y;
            localMatrix.value[2][1] = localE8.z;
        }
        if (mngSt->m_scale.z != 1.0f) {
            localF4.x = localMatrix.value[0][2];
            localF4.y = localMatrix.value[1][2];
            localF4.z = localMatrix.value[2][2];
            PSVECScale(&localF4, &localF4, mngSt->m_scale.z);
            localMatrix.value[0][2] = localF4.x;
            localMatrix.value[1][2] = localF4.y;
            localMatrix.value[2][2] = localF4.z;
        }

        localMatrix.value[0][3] += local88.x;
        localMatrix.value[1][3] += local88.y;
        localMatrix.value[2][3] += local88.z;
        goto copy_out;
    }

    if (mngSt->m_scale.x != 1.0f) {
        local100.x = localMatrix.value[0][0];
        local100.y = localMatrix.value[1][0];
        local100.z = localMatrix.value[2][0];
        PSVECScale(&local100, &local100, mngSt->m_scale.x);
        localMatrix.value[0][0] = local100.x;
        localMatrix.value[1][0] = local100.y;
        localMatrix.value[2][0] = local100.z;
    }
    if (mngSt->m_scale.y != 1.0f) {
        local10C.x = localMatrix.value[0][1];
        local10C.y = localMatrix.value[1][1];
        local10C.z = localMatrix.value[2][1];
        PSVECScale(&local10C, &local10C, mngSt->m_scale.y);
        localMatrix.value[0][1] = local10C.x;
        localMatrix.value[1][1] = local10C.y;
        localMatrix.value[2][1] = local10C.z;
    }
    if (mngSt->m_scale.z != 1.0f) {
        local118.x = localMatrix.value[0][2];
        local118.y = localMatrix.value[1][2];
        local118.z = localMatrix.value[2][2];
        PSVECScale(&local118, &local118, mngSt->m_scale.z);
        localMatrix.value[0][2] = local118.x;
        localMatrix.value[1][2] = local118.y;
        localMatrix.value[2][2] = local118.z;
    }

    localMatrix.value[0][3] = mngSt->m_position.x;
    localMatrix.value[1][3] = mngSt->m_position.y;
    localMatrix.value[2][3] = mngSt->m_position.z;

copy_out:
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
    GraphValueState* state = (GraphValueState*)object;

    velocity += acceleration;
    value += velocity;

    if (graphId == state->graphId) {
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

    if (modelType != 1) {
        if (modelType < 1) {
            if (modelType < 0) {
                return 0;
            }

            if (gObject->m_charaModelHandle != 0) {
                return gObject->m_charaModelHandle;
            }
        } else if (modelType < 3) {
            if (gObject->m_shieldModelHandle != 0) {
                return gObject->m_shieldModelHandle;
            }
        }
    } else {
        if (gObject->m_weaponModelHandle != 0) {
            return gObject->m_weaponModelHandle;
        }
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
    GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
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

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT7, rings + 2);
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

        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, ringVertexCount * 2);
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
    gUtil.RenderColorQuad(0.0f, 0.0f, texWidth, texHeight, clearColor);

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
        Vec2d uvMin;
        Vec2d uvMax;

        uvMin.x = 1.0f;
        uvMin.y = 0.0f;
        uvMax.x = 0.0f;
        uvMax.y = 1.0f;

        gUtil.RenderTextureQuad(0.0f, 0.0f, rtWidth, rtHeight, targetTexObj, &uvMin, &uvMax, 0, (GXBlendFactor)4,
                                (GXBlendFactor)5);
        Graphic.GetBackBufferRect2(targetData, targetTexObj, 0, 0, texWidth, texHeight, 0, GX_LINEAR, GX_TF_RGBA8, 0);
    }
}
