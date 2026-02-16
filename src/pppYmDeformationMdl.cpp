#include "ffcc/pppYmDeformationMdl.h"
#include "ffcc/graphic.h"
#include "ffcc/mapmesh.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern int DAT_8032ed70;
extern u8 DAT_8032ed78;

extern void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
extern float FLOAT_80330dac;

struct pppCVECTOR {
    u8 rgba[4];
};

struct pppFMATRIX {
    Mtx value;
};

struct pppModelSt;

struct _pppEnvStYmDeformationMdl {
    void* m_stagePtr;
    CMaterialSet* m_materialSetPtr;
    CMapMesh** m_mapMeshPtr;
};

extern _pppEnvStYmDeformationMdl* pppEnvStPtr;
extern struct {
    float _212_4_;
    float _216_4_;
    float _220_4_;
    float _224_4_;
    float _228_4_;
    float _232_4_;
    Mtx m_cameraMatrix;
    Mtx44 m_screenMatrix;
} CameraPcs;
extern CGraphic Graphic;

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
void pppInitBlendMode__Fv(void);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    pppCVECTOR*, pppFMATRIX*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
void pppSetBlendMode__FUc(unsigned char);
void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt*, Vec*, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(int, int,
                                                                                                                      int, int,
                                                                                                                      int);
void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int, int, int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int, int, int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
int GetBackBufferRect__8CGraphicFRiRiRiRii(CGraphic*, int&, int&, int&, int&, int);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetUpIndWarp(VYmDeformationMdl*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void DisableIndWarp()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800d20c0
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl_, struct UnkC* param_2)
{
    float fVar1 = 1.0f; // FLOAT_80330dac equivalent 
    u16* puVar2 = (u16*)((u8*)pppYmDeformationMdl_ + 0x80 + param_2->m_serializedDataOffsets[2]);
    
    *puVar2 = 0;
    *(u8*)(puVar2 + 1) = 1;
    *(float*)(puVar2 + 6) = fVar1;
    *(float*)(puVar2 + 4) = fVar1;
    *(float*)(puVar2 + 2) = fVar1;
    *(float*)(puVar2 + 0xc) = fVar1;
    *(float*)(puVar2 + 10) = fVar1;
    *(float*)(puVar2 + 8) = fVar1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstruct2YmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl_, UnkC* param_2)
{
    float fVar1 = FLOAT_80330dac;
    u8* state = (u8*)pppYmDeformationMdl_ + param_2->m_serializedDataOffsets[2];

    *(float*)(state + 0x8C) = fVar1;
    *(float*)(state + 0x88) = fVar1;
    *(float*)(state + 0x84) = fVar1;
    *(float*)(state + 0x98) = fVar1;
    *(float*)(state + 0x94) = fVar1;
    *(float*)(state + 0x90) = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x800d208c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmDeformationMdl(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800d1f58
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, UnkB* param_2, UnkC* param_3)
{
    s16* psVar1;

    if ((DAT_8032ed70 == 0) &&
        ((psVar1 = (s16*)((u8*)pppYmDeformationMdl + 0x80 + param_3->m_serializedDataOffsets[2])),
         (param_2->m_dataValIndex != 0xFFFF))) {
        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
            (float)param_2->m_initWOrk, pppYmDeformationMdl, param_2->m_graphId, (float*)(psVar1 + 2),
            (float*)(psVar1 + 4), (float*)(psVar1 + 6), &param_2->m_stepValue, &param_2->m_arg3);
        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
            (float)param_2->m_payload0, pppYmDeformationMdl, param_2->m_graphId, (float*)(psVar1 + 8),
            (float*)(psVar1 + 10), (float*)(psVar1 + 0xC), &param_2->m_payload1, &param_2->m_payload2);

        if (DAT_8032ed78 == 0) {
            if (*(u8*)(psVar1 + 1) != 0) {
                *psVar1 = *psVar1 + (s16)(int)*(float*)(psVar1 + 8);
                if (param_2->m_payload3 < *psVar1) {
                    *(u8*)(psVar1 + 1) = 0;
                }
            } else {
                *psVar1 = *psVar1 - (s16)(int)*(float*)(psVar1 + 8);
                if ((int)*psVar1 < -(int)param_2->m_payload3) {
                    *(u8*)(psVar1 + 1) = 1;
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d19f0
 * PAL Size: 1384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, UnkB* param_2, UnkC* param_3)
{
    short* state = (short*)((u8*)pppYmDeformationMdl + 0x80 + param_3->m_serializedDataOffsets[2]);
    u8* control = (u8*)&param_2->m_payload0;
    int textureIndex = 0;

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    pppModelSt* model = (pppModelSt*)pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
    int textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi((CMapMesh*)model, pppEnvStPtr->m_materialSetPtr, textureIndex);
    Mtx cameraMtx;
    Mtx texMtx;
    Mtx rotMtx;
    Mtx44 screenMtx;
    int left = 0;
    int top = 0;
    int width = 0x280;
    int height = 0x1c0;
    int backTexture = 0;

    pppInitBlendMode__Fv();
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);

    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (pppCVECTOR*)((u8*)pppYmDeformationMdl + 0x88 + param_3->m_serializedDataOffsets[1]),
        (pppFMATRIX*)((u8*)pppYmDeformationMdl + 0x40), *(float*)(control + 0x10), control[0x17], control[0x16], control[0x14],
        control[0x15], (u8)(control[0x18] == 0), 1, 0);

    GXSetNumTevStages(1);
    GXSetNumTexGens(2);
    GXSetNumChans(1);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 1, 7, 0);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(1, 0, 1, 2, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 0xFF);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 8, 9, 0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 7, 7, 4);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);

    pppSetBlendMode__FUc(control[0x14]);
    if (control[0x14] == 0) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 1, 5, 1);
    }
    if (control[0x14] == 3) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 1, 5, 1);
        GXSetTevOp((GXTevStageID)0, GX_MODULATE);
    }

    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 1, 0xFF);
    GXSetTevOp((GXTevStageID)1, GX_MODULATE);
    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_DIRECT);
    GXSetVtxDesc((GXAttr)10, GX_DIRECT);
    GXSetVtxDesc((GXAttr)11, GX_DIRECT);
    GXSetVtxDesc((GXAttr)13, GX_DIRECT);

    backTexture = GetBackBufferRect__8CGraphicFRiRiRiRii(&Graphic, left, top, width, height, 0);
    if (backTexture != 0) {
        PSMTXIdentity(texMtx);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

        texMtx[0][0] = screenMtx[0][0] * (2.0f / (float)width);
        texMtx[1][1] = screenMtx[1][1] * -(2.0f / (float)height);
        texMtx[1][0] = screenMtx[1][0];
        texMtx[2][0] = screenMtx[2][0];
        texMtx[0][1] = screenMtx[0][1];
        texMtx[2][1] = screenMtx[2][1];
        texMtx[0][2] = 0.0f;
        texMtx[1][2] = 0.0f;
        texMtx[2][2] = 1.0f;
        Mtx* objectMtx = (Mtx*)((u8*)pppYmDeformationMdl + 0x40);
        PSMTXConcat(texMtx, *objectMtx, texMtx);
        GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX3x4);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, 0x1E, GX_FALSE, GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumIndStages(1);
        GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
        GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_ITW_0, GX_ITM_1);
        GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

        if ((*state == 0) || (*state == 0x168)) {
            *state = 1;
        }

        PSMTXRotRad(rotMtx, 'z', 0.017453292f * (float)*state);
        float indMtx[2][3];
        indMtx[0][0] = rotMtx[0][0] * *(float*)(state + 2);
        indMtx[0][1] = rotMtx[0][1] * *(float*)(state + 2);
        indMtx[1][0] = rotMtx[1][0] * *(float*)(state + 2);
        indMtx[1][1] = rotMtx[1][1] * *(float*)(state + 2);
        indMtx[0][2] = FLOAT_80330dac;
        indMtx[1][2] = FLOAT_80330dac;
        GXSetIndTexMtx(GX_ITM_1, indMtx, 1);

        GXLoadTexObj((_GXTexObj*)backTexture, GX_TEXMAP0);
        GXLoadTexObj((_GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
        pppDrawMesh__FP10pppModelStP3Veci(model, *(Vec**)((u8*)pppYmDeformationMdl + 0x70), 0);

        GXSetTevDirect((GXTevStageID)1);
        GXSetNumIndStages(0);
        GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

        PSMTXRotRad(rotMtx, 'z', FLOAT_80330dac);
        indMtx[0][0] = FLOAT_80330dac;
        indMtx[0][1] = FLOAT_80330dac;
        indMtx[0][2] = FLOAT_80330dac;
        indMtx[1][0] = FLOAT_80330dac;
        indMtx[1][1] = FLOAT_80330dac;
        indMtx[1][2] = FLOAT_80330dac;
        GXSetIndTexMtx(GX_ITM_1, indMtx, 1);

        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
        pppInitBlendMode__Fv();
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
