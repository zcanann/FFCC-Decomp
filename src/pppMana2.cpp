#include "ffcc/pppMana2.h"
#include "ffcc/graphic.h"
#include "ffcc/gobject.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"
#include "ffcc/util.h"

#include <string.h>
#include <math.h>
#include <dolphin/os/OSCache.h>

struct Vec2d {
    float x;
    float y;
};

extern char lbl_801DC4D0[];
extern float FLOAT_803318fc;
extern float FLOAT_80331898;
extern float FLOAT_8033189c;
extern float FLOAT_803318a0;
extern float FLOAT_803318a4;
extern float FLOAT_803318b8;
extern float FLOAT_803318bc;
extern float FLOAT_803318c0;
extern float FLOAT_80331904;
extern Mtx ppvCameraMatrix0;
extern struct {
    float _224_4_;
    float _228_4_;
    float _232_4_;
} CameraPcs;
extern CUtil DAT_8032ec70;
extern char MaterialMan[];
extern char DAT_80331900[];
extern char DAT_803318d4[];
extern char DAT_803318dc[];
extern char DAT_803318e4[];
extern char DAT_803318ec[];
extern char DAT_803318f4[];
extern int DAT_8032ed70;

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int,
                                                                                                            int, int,
                                                                                                            int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                            int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int,
                                                                                                            int, int,
                                                                                                            int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                            int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
int GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvSt*);
void InitTexObj__8CTextureFv(void*);
void genParaboloidMap__FPvPUlUs9_GXVtxFmt(void*, unsigned long*, unsigned short, GXVtxFmt);
}

/*
 * --INFO--
 * PAL Address: 0x80108db0
 * PAL Size: 1060b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Mana2_DrawMeshDLCallback(CChara::CModel* model, void* work, void* step, int partIndex, int dlIndex, float (*mtx)[4])
{
    u8 type = *(u8*)((char*)step + 0x1C);
    int shape = *(int*)(*(int*)((char*)model + 0xAC) + partIndex * 0x14 + 8);
    u32* dlEntry = (u32*)(*(int*)(shape + 0x50) + dlIndex * 0xC);
    bool draw = false;

    if (type == 2) {
        if (strcmp((char*)shape, DAT_80331900) == 0 || strcmp((char*)shape, DAT_803318dc) == 0) {
            draw = true;
        }
    } else if (type < 2) {
        if (type == 0) {
            if (strcmp((char*)shape, DAT_80331900) == 0) {
                draw = true;
            }
        } else if (strcmp((char*)shape, DAT_80331900) == 0 || strcmp((char*)shape, DAT_803318d4) == 0) {
            draw = true;
        }
    } else if (type < 4 && (strcmp((char*)shape, DAT_80331900) == 0 || strcmp((char*)shape, DAT_803318e4) == 0)) {
        draw = true;
    }

    int waterCmp = strcmp((char*)shape, DAT_803318ec);
    if ((waterCmp == 0 && *(char*)((char*)step + 0x1C) == 1) ||
        (strcmp((char*)shape, DAT_803318f4) == 0 && *(char*)((char*)step + 0x1C) == 2)) {
        Mtx cameraMtx;
        Mtx rotMtx;
        Mtx posMtx;
        Vec offset;
        double x = (double)mtx[0][3];
        double y = (double)mtx[1][3];
        double z = (double)mtx[2][3];

        PSMTXCopy(ppvCameraMatrix0, cameraMtx);
        PSMTXRotRad(rotMtx, 'z', FLOAT_80331904);
        mtx[0][3] = FLOAT_80331898;
        mtx[1][3] = FLOAT_80331898;
        mtx[2][3] = FLOAT_80331898;
        PSMTXConcat(mtx, rotMtx, mtx);

        offset.x = FLOAT_80331898;
        offset.y = *(float*)((char*)step + 0x30);
        offset.z = FLOAT_80331898;
        PSMTXMultVec(mtx, &offset, &offset);

        mtx[0][3] = (float)x;
        mtx[1][3] = (float)(y - (double)offset.y);
        mtx[2][3] = (float)z;

        PSMTXConcat(cameraMtx, mtx, posMtx);
        GXLoadPosMtxImm(posMtx, 0);
        PSMTXCopy(mtx, (float(*)[4])((char*)work + 0x80));
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        RenderWaterMesh((VMana2*)work);
        GXSetCullMode((GXCullMode)1);
    }

    if (draw) {
        if (strcmp((char*)shape, DAT_80331900) != 0) {
            PSMTXCopy(mtx, (float(*)[4])((char*)work + 0xB0));
            if (*(char*)((char*)work + 0xEC) != 0) {
                *(u8*)((char*)work + 0x38) = **(u8**)(shape + 0x28);
                *(u8*)((char*)work + 0x39) = *((u8*)(*(int*)(shape + 0x28)) + 1);
                *(u8*)((char*)work + 0x3A) = *((u8*)(*(int*)(shape + 0x28)) + 2);
                *(u8*)((char*)work + 0x3B) = 0x80;
                DCFlushRange((u8*)work + 0x38, 4);
                GXSetArray((GXAttr)0xB, *(void**)((char*)work + 0x68), 4);
                GXSetArray((GXAttr)0xD, *(void**)((char*)work + 0x6C), 4);
                *(u32*)(MaterialMan + 0x08) = *(u32*)((char*)work + 0x64);
                *(u32*)(MaterialMan + 0x44) = 0xFFFFFFFF;
                *(u8*)(MaterialMan + 0x4C) = 0xFF;
                *(u32*)(MaterialMan + 0x11C) = 0;
                *(u32*)(MaterialMan + 0x120) = 0x1E;
                *(u32*)(MaterialMan + 0x124) = 0;
                *(u8*)(MaterialMan + 0x205) = 0xFF;
                *(u8*)(MaterialMan + 0x206) = 0xFF;
                *(u32*)(MaterialMan + 0x58) = 0;
                *(u32*)(MaterialMan + 0x5C) = 0;
                *(u8*)(MaterialMan + 0x208) = 0;
                *(u32*)(MaterialMan + 0x48) = 0x2ACE0F;
                *(u32*)(MaterialMan + 0x128) = 0;
                *(u32*)(MaterialMan + 0x12C) = 0x1E;
                *(u32*)(MaterialMan + 0x130) = 0;
                *(u32*)(MaterialMan + 0x40) = 0x2ACE0F;
                *(u32*)(MaterialMan + 0xD0) = *(u32*)((char*)work + 0x20);
                GXSetCullMode((GXCullMode)1);
                GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
                SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                    MaterialMan, *(void**)(*(int*)((char*)model + 0xA4) + 0x24), *(u16*)((char*)dlEntry + 8), 0, 0);
                GXCallDisplayList(*(void**)(*(int*)((char*)work + 0x60) + dlIndex * 4), *dlEntry);
            }
        } else {
            GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                MaterialMan, *(void**)(*(int*)((char*)model + 0xA4) + 0x24), *(u16*)((char*)dlEntry + 8), 0, 0);
            GXCallDisplayList((void*)dlEntry[1], dlEntry[0]);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructMana2(pppMana2* pppMana2, UnkC* param_2)
{
    CGObject* gObject;
    void* handle;
    u32 model;
    u32* work;
    s32 workOffset;

    gObject = *(CGObject**)((char*)pppMngStPtr + 0xDC);
    workOffset = *(s32*)((char*)param_2 + 0xC);
    work = (u32*)((char*)pppMana2 + 0x80 + workOffset);
    gObject->m_stepSlopeLimit = FLOAT_803318fc;

    handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    model = *(u32*)((char*)handle + 0x168);
    *(u32*)(model + 0x98) = 0x3F;
    work[1] = (u32)pppMngStPtr;

    work[0] = 0;
    work[1] = 0;
    work[8] = 0;
    work[9] = 0;
    work[15] = 0;
    work[16] = 0;
    work[18] = 0;
    work[19] = 0;
    work[20] = 0;
    work[21] = 0;
    work[22] = 0;
    work[24] = 0;
    work[17] = 0;
    work[23] = 0;
    work[29] = 0;
    work[28] = 0;
    work[30] = 0;
    work[31] = 0;
    work[25] = 0;
    work[26] = 0;
    work[27] = 0;
    work[10] = 0;
    work[11] = 0;
    work[12] = 0;
    work[13] = 0;
    *(u8*)(work + 0x38) = 0xFF;
    PSMTXIdentity((float (*)[4])(work + 0x20));
    PSMTXIdentity((float (*)[4])(work + 0x2C));
    *(u8*)(work + 0xE) = 0xFF;
    *((u8*)work + 0x39) = 0xFF;
    *((u8*)work + 0x3A) = 0xFF;
    *((u8*)work + 0x3B) = 0xFF;
    work[2] = 0;
    work[3] = 0;
    work[4] = 0;
    work[5] = 0;
    work[6] = 0;
    work[7] = 0;
    work[0x39] = 0;
    work[0x3A] = 0;
    *(u8*)(work + 0x3B) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructMana2(pppMana2*, UnkC*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80107ea4
 * PAL Size: 2556b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameMana2(pppMana2* pppMana2, UnkB* param_2, UnkC* param_3)
{
    u32 texBufferSize;
    u32* work;
    void* dstBuffer;
    u32* texList;
    void* handle;
    s32 model;
    CGObject* gObject;
    s32 i;
    s32 setupOffset;

    if (DAT_8032ed70 != 0) {
        return;
    }

    gObject = *(CGObject**)((char*)pppMngStPtr + 0xDC);
    setupOffset = *(s32*)((char*)param_3 + 8);
    work = (u32*)((char*)pppMana2 + 0x80 + *(s32*)((char*)param_3 + 0xC));
    if (gObject == NULL) {
        return;
    }

    handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *((u8*)param_2 + 0x24) = 0;
    work[0x1C] = (u32)param_2;
    if (Game.game.m_currentMapId == 0x21) {
        *((u8*)param_2 + 0x24) = 0;
    }

    *(u32*)(model + 0xE4) = (u32)work;
    *(u32*)(model + 0xE8) = (u32)param_2;
    *(u32*)(model + 0xF0) = (u32)Mana2_BeforeDrawCallback;
    *(u32*)(model + 0xFC) = (u32)Mana2_DrawMeshDLCallback;

    MaterialMan[0x228] = *((u8*)pppMana2 + 0x8B + setupOffset);
    *((u8*)(work + 0x38)) = MaterialMan[0x228];

    if (*(s32*)pppMana2 != 0) {
        return;
    }

    work[0] = (u32)gObject;
    *(u32*)(model + 0xE4) = (u32)work;
    *(u32*)(model + 0xE8) = (u32)param_2;
    *(u32*)(model + 0xF0) = (u32)Mana2_BeforeDrawCallback;
    *(u32*)(model + 0xFC) = (u32)Mana2_DrawMeshDLCallback;
    work[2] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((char*)param_2 + 0x8), pppEnvStPtr);
    work[3] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((char*)param_2 + 0xC), pppEnvStPtr);
    work[4] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((char*)param_2 + 0x10), pppEnvStPtr);
    work[5] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((char*)param_2 + 0x14), pppEnvStPtr);
    work[6] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((char*)param_2 + 0x18), pppEnvStPtr);
    work[7] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((char*)param_2 + 0x1C), pppEnvStPtr);
    work[0x1E] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((char*)param_2 + 0x28), pppEnvStPtr);
    work[0x1F] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((char*)param_2 + 0x2C), pppEnvStPtr);

    if (work[0x1D] == 0) {
        work[0x1D] = (u32)pppMemAlloc(0xC0, pppEnvStPtr->m_stagePtr, (char*)"pppMana2.cpp", 0x1D7);
    }
    if (work[10] == 0) {
        work[10] = (u32)pppMemAlloc(0x20, pppEnvStPtr->m_stagePtr, (char*)"pppMana2.cpp", 0x1DD);
    }
    if (work[11] == 0) {
        work[11] = (u32)pppMemAlloc(0x20, pppEnvStPtr->m_stagePtr, (char*)"pppMana2.cpp", 0x1E1);
    }

    texBufferSize = GXGetTexBufferSize(0x80, 0x80, GX_TF_RGBA8, GX_FALSE, 0);
    if (work[12] == 0) {
        work[12] = (u32)pppMemAlloc(texBufferSize, pppEnvStPtr->m_stagePtr, (char*)"pppMana2.cpp", 0x1E9);
    }
    if (work[13] == 0) {
        work[13] = (u32)pppMemAlloc(texBufferSize, pppEnvStPtr->m_stagePtr, (char*)"pppMana2.cpp", 0x1EB);
    }

    GXInitTexObj((GXTexObj*)work[10], (void*)work[12], 0x80, 0x80, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObj((GXTexObj*)work[11], (void*)work[13], 0x80, 0x80, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

    if (work[8] == 0) {
        work[8] = (u32)pppMemAlloc(0xC0, pppEnvStPtr->m_stagePtr, (char*)"pppMana2.cpp", 0x1F6);
    }
    dstBuffer = (void*)work[8];
    texList = &work[2];
    for (i = 0; i < 6; i++) {
        memcpy(dstBuffer, (void*)(texList[0] + 0x28), 0x20);
        dstBuffer = (void*)((char*)dstBuffer + 0x20);
        texList++;
    }

    *(u32*)(work[0x1E] + 0x6C) = 0;
    InitTexObj__8CTextureFv((void*)work[0x1E]);
    *(u32*)(work[0x1F] + 0x6C) = 0;
    InitTexObj__8CTextureFv((void*)work[0x1F]);

    if (work[9] == 0) {
        work[9] = (u32)pppMemAlloc(0xA5E8, pppEnvStPtr->m_stagePtr, (char*)"pppMana2.cpp", 0x211);
        genParaboloidMap__FPvPUlUs9_GXVtxFmt((void*)work[9], &work[0x39], 0x1E, GX_VTXFMT7);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80107e48
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderMana2(pppMana2*, UnkB*, UnkC*)
{
    Graphic.Printf(lbl_801DC4D0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    Graphic.SetViewport();
    pppInitBlendMode();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Mana2_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*) [4], int)
{
	// TODO
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
 * PAL Address: 0x801071b0
 * PAL Size: 1428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CalcReflectionVector2(
    Vec* reflectionVec,
    S16Vec* positions,
    S16Vec* normals,
    long count,
    unsigned long posScale,
    unsigned long normalScale,
    float (*matrix)[4],
    void* displayList,
    unsigned long displayListSize,
    _GXColor* color,
    S16Vec2d* texCoord,
    CChara::CNode* node)
{
    Vec cameraPos;
    Vec nodeOffset;
    Vec worldPos;
    Vec cameraVector;
    Vec objSpacePos;
    Vec objSpaceNormal;
    Vec reflectOut;
    Vec2d uv;
    Mtx nodeMtx;
    Mtx nodeRotMtx;
    Mtx cameraMtx;
    u8* dl = (u8*)displayList;
    u8* dlEnd;
    const double half = (double)FLOAT_803318a4;

    cameraPos.x = CameraPcs._224_4_;
    cameraPos.y = CameraPcs._228_4_;
    cameraPos.z = CameraPcs._232_4_;

    PSMTXCopy(matrix, nodeMtx);
    nodeOffset.x = *(float*)((char*)node + 0x78);
    nodeOffset.y = *(float*)((char*)node + 0x88);
    nodeOffset.z = *(float*)((char*)node + 0x98);

    worldPos.x = nodeMtx[0][3];
    worldPos.y = nodeMtx[1][3];
    worldPos.z = nodeMtx[2][3];
    PSVECAdd(&nodeOffset, &worldPos, &worldPos);

    PSMTXCopy((float(*)[4])((char*)node + 0x6C), matrix);
    matrix[0][3] = worldPos.x;
    matrix[1][3] = worldPos.y;
    matrix[2][3] = worldPos.z;

    PSMTXCopy(matrix, nodeRotMtx);
    nodeRotMtx[0][3] = FLOAT_80331898;
    nodeRotMtx[1][3] = FLOAT_80331898;
    nodeRotMtx[2][3] = FLOAT_80331898;

    PSMTXCopy(ppvCameraMatrix0, cameraMtx);
    PSMTXConcat(cameraMtx, matrix, cameraMtx);

    dlEnd = dl + displayListSize;
    while (dl < dlEnd) {
        u8 drawFmt = dl[0];
        u16 itemCount = *(u16*)(dl + 1);
        int i;

        if (DAT_8032ec70.IsHasDrawFmtDL(drawFmt) == 0) {
            break;
        }

        dl += 3;
        for (i = 0; i < itemCount; i++) {
            u16 posIndex = *(u16*)(dl + 0);
            u16 normalIndex = *(u16*)(dl + 2);
            u8* next = dl + 8;
            int axis = 0;
            float maxAxis;
            float invAxis;
            u8* clr;

            if ((drawFmt & 7) == 2) {
                next = dl + 10;
            }

            DAT_8032ec70.ConvI2FVector(objSpacePos, positions[posIndex], posScale);
            DAT_8032ec70.ConvI2FVector(objSpaceNormal, normals[normalIndex], normalScale);
            PSMTXMultVec(matrix, &objSpacePos, &objSpacePos);
            PSMTXMultVec(nodeRotMtx, &objSpaceNormal, &objSpaceNormal);

            PSVECSubtract(&objSpacePos, &cameraPos, &cameraVector);
            PSVECNormalize(&cameraVector, &cameraVector);
            C_VECReflect(&cameraVector, &objSpaceNormal, &reflectOut);

            maxAxis = fabsf(reflectOut.x);
            if (maxAxis < fabsf(reflectOut.y)) {
                axis = 1;
                maxAxis = fabsf(reflectOut.y);
            }
            if (maxAxis < fabsf(reflectOut.z)) {
                axis = 2;
            }

            clr = (u8*)&color[posIndex];
            clr[0] = 0x80;
            clr[1] = 0x80;
            clr[2] = 0x80;
            clr[3] = 0xFF;

            uv.x = (float)half;
            uv.y = (float)half;

            if (axis == 1) {
                invAxis = FLOAT_803318b8 * reflectOut.y;
                if (reflectOut.y < FLOAT_80331898) {
                    clr[1] = (u8)(clr[1] - 0x7F);
                    uv.x = (float)((half - (double)(reflectOut.x / invAxis)) * (double)FLOAT_803318bc +
                                   (double)FLOAT_803318bc);
                    uv.y = (float)((double)((float)(half + (double)(reflectOut.z / invAxis)) * FLOAT_803318bc) + half);
                } else {
                    clr[1] = (u8)(clr[1] + 0x7F);
                    uv.y = (float)((half + (double)(reflectOut.z / invAxis)) * (double)FLOAT_803318bc);
                    uv.x = (float)((double)((float)(half + (double)(reflectOut.x / invAxis)) * FLOAT_803318bc) + half);
                }
            } else if (axis == 0) {
                invAxis = FLOAT_803318b8 * reflectOut.x;
                if (reflectOut.x < FLOAT_80331898) {
                    clr[0] = (u8)(clr[0] - 0x7F);
                    uv.x = (float)((half - (double)(reflectOut.z / invAxis)) * (double)FLOAT_803318bc +
                                   (double)FLOAT_803318c0);
                    uv.y = (float)((half + (double)(reflectOut.y / invAxis)) * (double)FLOAT_803318bc +
                                   (double)FLOAT_803318bc);
                } else {
                    clr[0] = (u8)(clr[0] + 0x7F);
                    uv.x = (float)((half - (double)(reflectOut.z / invAxis)) * (double)FLOAT_803318bc +
                                   (double)FLOAT_803318bc);
                    uv.y = (float)((half - (double)(reflectOut.y / invAxis)) * (double)FLOAT_803318bc +
                                   (double)FLOAT_803318bc);
                }
            } else {
                invAxis = FLOAT_803318b8 * reflectOut.z;
                if (reflectOut.z < FLOAT_80331898) {
                    clr[2] = (u8)(clr[2] - 0x7F);
                    uv.x = (float)((double)((float)(half + (double)(reflectOut.x / invAxis)) * FLOAT_803318bc) + half);
                    uv.y = (float)((half + (double)(reflectOut.y / invAxis)) * (double)FLOAT_803318bc +
                                   (double)FLOAT_803318bc);
                } else {
                    clr[2] = (u8)(clr[2] + 0x7F);
                    uv.x = (float)((half + (double)(reflectOut.x / invAxis)) * (double)FLOAT_803318bc);
                    uv.y = (float)((half - (double)(reflectOut.y / invAxis)) * (double)FLOAT_803318bc +
                                   (double)FLOAT_803318bc);
                }
            }

            DAT_8032ec70.ConvF2IVector2d(texCoord[normalIndex], uv, 12);
            dl = next;
        }
    }

    DCFlushRange(reflectionVec, count * sizeof(Vec));
    DCFlushRange(texCoord, count << 3);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeWave(Vec*, unsigned short*, float*, Vec*, float, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010701c
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int CreateWaterMesh__FP3VecP3VecP5Vec2dPUsf2(
    Vec* param_1, Vec* param_2, Vec2d* param_3, unsigned short* param_4, float param_5, float)
{
    float* pPos;
    float* pNormal;
    float* pUv;
    unsigned short* pIdx;
    float xPos;
    float zPos;
    int idxOffset;
    int row;
    int pair;
    int rowCounter;
    int colCounter;
    const float fZero = 0.0f;
    const float fOne = 1.0f;
    const float fStepScale = 0.125f;
    float radius = 0.0f;
    float step = 0.0f;

    pPos = (float*)param_1;
    pNormal = (float*)param_2;
    pUv = (float*)param_3;
    pIdx = param_4;

    radius = param_5 * fOne;
    rowCounter = 0;
    step = param_5 * fStepScale;
    for (zPos = radius; -radius <= zPos; zPos -= step) {
        colCounter = 0;
        for (xPos = -radius; xPos <= radius; xPos += step) {
            pPos[0] = xPos;
            pPos[1] = fZero;
            pPos[2] = zPos;
            pPos += 3;

            pNormal[0] = fZero;
            pNormal[1] = fOne;
            pNormal[2] = fZero;
            pNormal += 3;

            pUv[0] = (float)((double)colCounter * (double)fStepScale);
            pUv[1] = (float)((double)rowCounter * (double)fStepScale);
            pUv += 2;
            colCounter++;
        }
        rowCounter++;
    }

    idxOffset = 0;
    row = 0;
    colCounter = 0;
    do {
        pair = 8;
        rowCounter = colCounter;
        do {
            *(short*)((char*)pIdx + idxOffset) = rowCounter;
            *(short*)((char*)pIdx + idxOffset + 2) = rowCounter + 1;
            *(short*)((char*)pIdx + idxOffset + 4) = rowCounter + 0x12;
            *(short*)((char*)pIdx + idxOffset + 6) = rowCounter + 0x12;
            *(short*)((char*)pIdx + idxOffset + 8) = rowCounter + 0x11;
            *(short*)((char*)pIdx + idxOffset + 10) = rowCounter;
            *(short*)((char*)pIdx + idxOffset + 12) = rowCounter + 1;
            *(short*)((char*)pIdx + idxOffset + 14) = rowCounter + 2;
            *(short*)((char*)pIdx + idxOffset + 16) = rowCounter + 0x13;
            *(short*)((char*)pIdx + idxOffset + 18) = rowCounter + 0x13;
            *(short*)((char*)pIdx + idxOffset + 20) = rowCounter + 0x12;
            *(short*)((char*)pIdx + idxOffset + 22) = rowCounter + 1;
            idxOffset += 0x18;
            pair--;
            rowCounter += 2;
        } while (pair != 0);
        row++;
        colCounter += 0x11;
    } while (row < 0x10);

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80106c54
 * PAL Size: 968b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdateWaterMesh(VMana2* mana2)
{
    u8* work;
    float* waterHeightA;
    float* waterHeightB;
    Vec* positions;
    Vec origin;

    work = (u8*)mana2;
    waterHeightA = *(float**)(work + 0x48);
    positions = *(Vec**)(work + 0x3C);
    waterHeightB = *(float**)(work + 0x4C);
    if (waterHeightA == NULL) {
        return;
    }

    for (int row = 1; row < 0x10; row++) {
        int rowBase = row * 0x11;
        for (int colBlock = 0; colBlock < 3; colBlock++) {
            int col = colBlock * 5 + 1;
            int idx = rowBase + col;

            waterHeightB[idx + 0] =
                FLOAT_80331898 * waterHeightA[idx + 0] +
                FLOAT_803318a4 *
                    (waterHeightA[idx + 1] + waterHeightA[idx - 1] + waterHeightA[idx - 0x11] + waterHeightA[idx + 0x11]) -
                waterHeightB[idx + 0];

            waterHeightB[idx + 1] =
                FLOAT_80331898 * waterHeightA[idx + 1] +
                FLOAT_803318a4 *
                    (waterHeightA[idx + 2] + waterHeightA[idx + 0] + waterHeightA[idx - 0x10] + waterHeightA[idx + 0x12]) -
                waterHeightB[idx + 1];

            waterHeightB[idx + 2] =
                FLOAT_80331898 * waterHeightA[idx + 2] +
                FLOAT_803318a4 *
                    (waterHeightA[idx + 3] + waterHeightA[idx + 1] + waterHeightA[idx - 0x0F] + waterHeightA[idx + 0x13]) -
                waterHeightB[idx + 2];

            waterHeightB[idx + 3] =
                FLOAT_80331898 * waterHeightA[idx + 3] +
                FLOAT_803318a4 *
                    (waterHeightA[idx + 4] + waterHeightA[idx + 2] + waterHeightA[idx - 0x0E] + waterHeightA[idx + 0x14]) -
                waterHeightB[idx + 3];

            waterHeightB[idx + 4] =
                FLOAT_80331898 * waterHeightA[idx + 4] +
                FLOAT_803318a4 *
                    (waterHeightA[idx + 5] + waterHeightA[idx + 3] + waterHeightA[idx - 0x0D] + waterHeightA[idx + 0x15]) -
                waterHeightB[idx + 4];
        }
    }

    for (int i = 0; i < 0x121; i++) {
        float tmp = waterHeightA[i];
        waterHeightA[i] = waterHeightB[i];
        waterHeightB[i] = tmp;
        positions[i].y = waterHeightA[i];
    }

    DCFlushRange(positions, 0xD8C);
    CalculateNormal(mana2);

    origin.x = *(float*)(work + 0x8C);
    origin.y = *(float*)(work + 0x9C);
    origin.z = *(float*)(work + 0xAC);
    CalcWaterReflectionVector(*(Vec**)(work + 0x44), *(Vec**)(work + 0x3C), *(Vec**)(work + 0x40), 0x121, &origin,
                              (float(*)[4])(work + 0x80), *(_GXColor**)(work + 0x5C), *(Vec2d**)(work + 0x58));
}

/*
 * --INFO--
 * PAL Address: 0x80106694
 * PAL Size: 1472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RenderWaterMesh(VMana2* mana2)
{
    u8* work = (u8*)mana2;
    u16* indices = *(u16**)(work + 0x50);
    void* texObj0 = *(void**)(work + 0x28);
    void* texObj1 = *(void**)(work + 0x2C);
    void* texObj2 = (u8*)*(void**)(work + 0x7C) + 0x28;
    _GXColor modulateColor;
    _GXColor blendColor = {0x80, 0x80, 0x80, 0x80};

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_INDEX16);
    GXSetVtxDesc((GXAttr)10, GX_INDEX16);
    GXSetVtxDesc((GXAttr)0xB, GX_INDEX16);
    GXSetVtxDesc((GXAttr)0xD, GX_INDEX16);
    GXSetVtxDesc((GXAttr)0xE, GX_INDEX16);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)10, (GXCompCnt)0, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xB, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xD, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xE, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetNumTexGens(2);
    GXSetCullMode((GXCullMode)0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 0xF);
    GXSetChanCtrl((GXChannelID)4, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPOT);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetNumChans(1);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
    GXSetArray((GXAttr)9, *(void**)(work + 0x3C), 0xC);
    GXSetArray((GXAttr)10, *(void**)(work + 0x40), 0xC);
    GXSetArray((GXAttr)0xB, *(void**)(work + 0x5C), 4);
    GXSetArray((GXAttr)0xD, *(void**)(work + 0x54), 8);
    GXSetArray((GXAttr)0xE, *(void**)(work + 0x58), 8);
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)1, (GXTexGenType)1, (GXTexGenSrc)5, 0x3C, GX_FALSE, 0x7D);
    modulateColor.r = *(u8*)(work + 0xE0);
    modulateColor.g = modulateColor.r;
    modulateColor.b = modulateColor.r;
    modulateColor.a = modulateColor.r;

    GXSetTevDirect((GXTevStageID)0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    GXLoadTexObj((GXTexObj*)texObj2, GX_TEXMAP0);
    GXSetTevKColor((GXTevKColorID)1, modulateColor);
    GXSetTevKColorSel((GXTevStageID)0, (GXTevKColorSel)0xD);
    GXSetTevKAlphaSel((GXTevStageID)0, (GXTevKAlphaSel)0x1D);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 0xF,
                                                                                                           0xF, 8);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 6, 4, 7);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);

    GXSetTevDirect((GXTevStageID)1);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 1, 1, 4);
    GXLoadTexObj((GXTexObj*)texObj0, GX_TEXMAP1);
    GXSetTevKColor((GXTevKColorID)0, blendColor);
    GXSetTevKColorSel((GXTevStageID)1, (GXTevKColorSel)0xC);
    GXSetTevKAlphaSel((GXTevStageID)1, (GXTevKAlphaSel)0x1C);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xB, 0xE,
                                                                                                           8, 0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 8, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 7, 7, 0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 1, 1, 0);

    GXSetTevDirect((GXTevStageID)2);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 1, 2, 4);
    GXLoadTexObj((GXTexObj*)texObj1, GX_TEXMAP2);
    GXSetTevKColor((GXTevKColorID)0, blendColor);
    GXSetTevKColorSel((GXTevStageID)2, (GXTevKColorSel)0xC);
    GXSetTevKAlphaSel((GXTevStageID)2, (GXTevKAlphaSel)0x1C);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xE, 0xB,
                                                                                                           8, 0);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 8, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 7, 7, 0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);

    GXSetNumTevStages(3);
    GXBegin((GXPrimitive)0x90, GX_VTXFMT7, 0x600);
    for (int i = 0; i < 0x180; i++) {
        GXPosition1x16(indices[0]);
        GXNormal1x16(indices[0]);
        GXColor1x16(indices[0]);
        GXTexCoord1x16(indices[0]);
        GXTexCoord1x16(indices[0]);
        GXPosition1x16(indices[1]);
        GXNormal1x16(indices[1]);
        GXColor1x16(indices[1]);
        GXTexCoord1x16(indices[1]);
        GXTexCoord1x16(indices[1]);
        GXPosition1x16(indices[2]);
        GXNormal1x16(indices[2]);
        GXColor1x16(indices[2]);
        GXTexCoord1x16(indices[2]);
        GXTexCoord1x16(indices[2]);
        GXPosition1x16(indices[3]);
        GXNormal1x16(indices[3]);
        GXColor1x16(indices[3]);
        GXTexCoord1x16(indices[3]);
        GXTexCoord1x16(indices[3]);
        indices += 4;
    }

    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0xFF, 4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 4, 5, 0xF);
    GXSetNumTevStages(1);
    GXLoadTexObj((GXTexObj*)texObj0, GX_TEXMAP0);
}

/*
 * --INFO--
 * PAL Address: 0x80106438
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CalculateNormal(VMana2* mana2)
{
    Vec* positions;
    Vec* normals;
    u16* indices;
    Vec edgeA;
    Vec edgeB;
    Vec faceNormal;

    positions = *(Vec**)((u8*)mana2 + 0x3C);
    normals = *(Vec**)((u8*)mana2 + 0x40);
    indices = *(u16**)((u8*)mana2 + 0x50);

    for (s32 i = 0; i < 0x121; i++) {
        normals[i].x = 0.0f;
        normals[i].y = 0.0f;
        normals[i].z = 0.0f;
    }

    for (s32 i = 0; i < 0x200; i++) {
        u16 i0 = indices[0];
        u16 i1 = indices[1];
        u16 i2 = indices[2];
        indices += 3;

        edgeA.x = positions[i1].x - positions[i0].x;
        edgeA.y = positions[i1].y - positions[i0].y;
        edgeA.z = positions[i1].z - positions[i0].z;

        edgeB.x = positions[i2].x - positions[i0].x;
        edgeB.y = positions[i2].y - positions[i0].y;
        edgeB.z = positions[i2].z - positions[i0].z;

        PSVECCrossProduct(&edgeA, &edgeB, &faceNormal);
        PSVECNormalize(&faceNormal, &faceNormal);

        PSVECAdd(&normals[i0], &faceNormal, &normals[i0]);
        PSVECAdd(&normals[i1], &faceNormal, &normals[i1]);
        PSVECAdd(&normals[i2], &faceNormal, &normals[i2]);
    }

    for (s32 i = 0; i < 0x121; i++) {
        PSVECNormalize(&normals[i], &normals[i]);
    }

    DCFlushRange(normals, 0xD8C);
}

/*
 * --INFO--
 * PAL Address: 0x8010617c
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CalcWaterReflectionVector__FP3VecP3VecP3Vecl3VecPA4_fP8_GXColorP5Vec2d2(
    Vec* reflectionVec,
    Vec* positions,
    Vec* normals,
    long count,
    Vec waterOrigin,
    float (*matrix)[4],
    _GXColor* color,
    Vec2d* texCoord,
    Vec2d*)
{
    Vec cameraPos;
    Vec objPos;
    Vec transformedCameraPos;
    Vec reflected;
    Mtx inverseMtx;
    Mtx matrixNoTranslate;
    float* texCoordFloat;
    unsigned char* colorBytes;
    double zero;
    double half;
    long i;

    (void)waterOrigin;

    if (Game.game.m_currentSceneId == 7) {
        cameraPos.x = ppvCameraMatrix0[0][3];
        cameraPos.y = ppvCameraMatrix0[1][3];
        cameraPos.z = ppvCameraMatrix0[2][3];
    } else {
        cameraPos.x = CameraPcs._224_4_;
        cameraPos.y = CameraPcs._228_4_;
        cameraPos.z = CameraPcs._232_4_;
    }

    transformedCameraPos.x = FLOAT_80331898;
    transformedCameraPos.y = FLOAT_80331898;
    transformedCameraPos.z = FLOAT_80331898;

    PSMTXCopy(matrix, matrixNoTranslate);
    objPos.x = matrixNoTranslate[0][3];
    objPos.y = matrixNoTranslate[1][3];
    objPos.z = matrixNoTranslate[2][3];
    matrixNoTranslate[0][3] = transformedCameraPos.x;
    matrixNoTranslate[1][3] = transformedCameraPos.y;
    matrixNoTranslate[2][3] = transformedCameraPos.z;
    PSMTXInverse(matrixNoTranslate, inverseMtx);

    PSVECSubtract(&objPos, &cameraPos, &cameraPos);
    PSVECScale(&cameraPos, &cameraPos, FLOAT_8033189c);
    PSMTXMultVec(inverseMtx, &cameraPos, &transformedCameraPos);

    texCoordFloat = (float*)texCoord;
    colorBytes = (unsigned char*)color;
    zero = (double)FLOAT_80331898;
    half = (double)FLOAT_803318a4;

    for (i = 0; i < count; i++) {
        PSVECSubtract(positions, &transformedCameraPos, &reflected);
        C_VECReflect(&reflected, normals, reflectionVec);
        PSMTXMultVec(matrixNoTranslate, reflectionVec, reflectionVec);
        PSVECNormalize(reflectionVec, reflectionVec);

        if ((double)reflectionVec->z < zero) {
            colorBytes[0] = 0x80;
            colorBytes[1] = 0xff;
            colorBytes[2] = 0x80;
            colorBytes[3] = 0x7f;
            *texCoordFloat = -reflectionVec->x / (FLOAT_803318a0 - reflectionVec->z);
            texCoordFloat[1] = -reflectionVec->y / (FLOAT_803318a0 - reflectionVec->z);
        } else {
            colorBytes[0] = 0x80;
            colorBytes[1] = 0x80;
            colorBytes[2] = 0xff;
            colorBytes[3] = 0xbc;
            *texCoordFloat = -reflectionVec->x / (FLOAT_803318a0 + reflectionVec->z);
            texCoordFloat[1] = -reflectionVec->y / (FLOAT_803318a0 + reflectionVec->z);
        }

        positions++;
        reflectionVec++;
        normals++;
        colorBytes += 4;
        *texCoordFloat = (float)((double)*texCoordFloat * half);
        *texCoordFloat = (float)((double)*texCoordFloat + half);
        texCoordFloat[1] = (float)((double)texCoordFloat[1] * half);
        texCoordFloat[1] = (float)((double)texCoordFloat[1] + half);
        texCoordFloat += 2;
    }

    DCFlushRange(reflectionVec - count, count * sizeof(Vec));
    DCFlushRange(texCoord, count << 3);
}
