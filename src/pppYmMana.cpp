#include "ffcc/pppYmMana.h"
#include "ffcc/graphic.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"

extern Mtx ppvCameraMatrix0;

extern float FLOAT_80330e4c;
extern float FLOAT_80330e58;
extern float FLOAT_80330e5c;
extern float FLOAT_80330e68;

extern struct {
    float _224_4_;
    float _228_4_;
    float _232_4_;
} CameraPcs;

struct Vec2d {
    float x;
    float y;
};

/*
 * --INFO--
 * PAL Address: 0x800d7ff8
 * PAL Size: 1816b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetEnvMap(PYmMana*, VYmMana* vYmMana)
{
    unsigned char* vYmManaBytes = (unsigned char*)vYmMana;
    GXTexObj* texObjA = *(GXTexObj**)(vYmManaBytes + 0x2c);
    GXTexObj* texObjB = *(GXTexObj**)(vYmManaBytes + 0x28);
    void* texObjCData = *(void**)(vYmManaBytes + 0x80);
    GXTexObj* texObjC = (GXTexObj*)((unsigned char*)texObjCData + 0x28);
    unsigned char alpha = *(unsigned char*)(vYmManaBytes + 0xe8);

    _GXColor white = {0xff, 0xff, 0xff, 0xff};
    _GXColor whiteAlpha = {0xff, 0xff, 0xff, alpha};
    _GXColor alphaOnly = {0x00, 0x00, 0x00, alpha};

    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)4, (GXBool)0, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
    GXSetBlendMode((GXBlendMode)1, (GXBlendFactor)4, (GXBlendFactor)5, (GXLogicOp)0xf);
    GXSetChanAmbColor((GXChannelID)4, white);
    GXSetChanMatColor((GXChannelID)4, white);
    GXSetTevKColor((GXTevKColorID)0, alphaOnly);
    GXSetTevKColor((GXTevKColorID)1, whiteAlpha);
    GXSetTevSwapModeTable((GXTevSwapSel)1, (GXTevColorChan)3, (GXTevColorChan)3, (GXTevColorChan)3, (GXTevColorChan)3);

    GXSetTevDirect((GXTevStageID)0);
    GXLoadTexObj(texObjC, (GXTexMapID)0);
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)0, (GXTexCoordID)0, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)0, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)0, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xc);
    GXSetTevColorOp((GXTevStageID)0, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)0, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)4);
    GXSetTevAlphaOp((GXTevStageID)0, (GXTevOp)0, (GXTevBias)0, (GXTevScale)2, (GXBool)1, (GXTevRegID)1);

    GXSetTevDirect((GXTevStageID)1);
    GXLoadTexObj(texObjC, (GXTexMapID)0);
    GXSetTexCoordGen2((GXTexCoordID)1, (GXTexGenType)1, (GXTexGenSrc)5, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)1, (GXTexCoordID)1, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)1, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)1, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xc);
    GXSetTevColorOp((GXTevStageID)1, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)1, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)4);
    GXSetTevAlphaOp((GXTevStageID)1, (GXTevOp)0, (GXTevBias)0, (GXTevScale)2, (GXBool)1, (GXTevRegID)2);

    GXSetTevDirect((GXTevStageID)2);
    GXLoadTexObj(texObjA, (GXTexMapID)1);
    GXSetTexCoordGen2((GXTexCoordID)2, (GXTexGenType)1, (GXTexGenSrc)4, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)2, (GXTexCoordID)2, (GXTexMapID)1, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)2, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevKColor((GXTevKColorID)0, alphaOnly);
    GXSetTevKColorSel((GXTevStageID)2, (GXTevKColorSel)0xc);
    GXSetTevKAlphaSel((GXTevStageID)2, (GXTevKAlphaSel)0x1c);
    GXSetTevColorIn((GXTevStageID)2, (GXTevColorArg)10, (GXTevColorArg)0xe, (GXTevColorArg)8, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)2, (GXTevOp)8, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)3);
    GXSetTevAlphaIn((GXTevStageID)2, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)1);
    GXSetTevAlphaOp((GXTevStageID)2, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)3);
    GXLoadTexObj(texObjA, (GXTexMapID)1);
    GXSetTexCoordGen2((GXTexCoordID)3, (GXTexGenType)1, (GXTexGenSrc)4, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)3, (GXTexCoordID)3, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)3, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)3, (GXTevColorArg)0xf, (GXTevColorArg)6, (GXTevColorArg)9, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)3, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)3);
    GXSetTevAlphaIn((GXTevStageID)3, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)1);
    GXSetTevAlphaOp((GXTevStageID)3, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)4);
    GXLoadTexObj(texObjB, (GXTexMapID)2);
    GXSetTexCoordGen2((GXTexCoordID)4, (GXTexGenType)1, (GXTexGenSrc)5, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)4, (GXTexCoordID)4, (GXTexMapID)2, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)4, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevKColor((GXTevKColorID)1, whiteAlpha);
    GXSetTevKColorSel((GXTevStageID)4, (GXTevKColorSel)0xd);
    GXSetTevKAlphaSel((GXTevStageID)4, (GXTevKAlphaSel)0x1d);
    GXSetTevColorIn((GXTevStageID)4, (GXTevColorArg)0xe, (GXTevColorArg)0xb, (GXTevColorArg)8, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)4, (GXTevOp)8, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)4, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)2);
    GXSetTevAlphaOp((GXTevStageID)4, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)5);
    GXLoadTexObj(texObjB, (GXTexMapID)2);
    GXSetTexCoordGen2((GXTexCoordID)5, (GXTexGenType)1, (GXTexGenSrc)5, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)5, (GXTexCoordID)5, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)5, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)5, (GXTevColorArg)0xf, (GXTevColorArg)0, (GXTevColorArg)9, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)5, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)5, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)2);
    GXSetTevAlphaOp((GXTevStageID)5, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)6);
    GXSetTevOrder((GXTevStageID)6, (GXTexCoordID)0xff, (GXTexMapID)0xff, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)6, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)6, (GXTevColorArg)0xf, (GXTevColorArg)6, (GXTevColorArg)0xc, (GXTevColorArg)0);
    GXSetTevColorOp((GXTevStageID)6, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)6, (GXTevAlphaArg)7, (GXTevAlphaArg)1, (GXTevAlphaArg)6, (GXTevAlphaArg)2);
    GXSetTevAlphaOp((GXTevStageID)6, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)7);
    GXSetTevOrder((GXTevStageID)7, (GXTexCoordID)0xff, (GXTexMapID)0xff, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)7, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevKAlphaSel((GXTevStageID)7, (GXTevKAlphaSel)0x1c);
    GXSetTevColorIn((GXTevStageID)7, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0);
    GXSetTevColorOp((GXTevStageID)7, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)7, (GXTevAlphaArg)7, (GXTevAlphaArg)0, (GXTevAlphaArg)6, (GXTevAlphaArg)7);
    GXSetTevAlphaOp((GXTevStageID)7, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetNumTevStages(8);
    GXSetNumTexGens(6);
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
 * Address:	TODO
 * Size:	TODO
 */
void Mana_BeforeDrawShadowLockEnvCallback(CChara::CModel*, void*, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Chara_DrawShadowMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Mana_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructYmMana(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructYmMana(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameYmMana(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800d6908
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMana(void)
{
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
void Mana_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*) [4], int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetViewportv(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeWave(Vec*, unsigned short*, float*, Vec&, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CreateWaterMesh(Vec*, Vec*, Vec2d*, unsigned short*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateWaterMesh(VYmMana*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RenderWaterMesh(VYmMana*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalculateNormal(VYmMana*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800d50dc
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CalcWaterReflectionVector__FP3VecP3VecP3Vecl3VecPA4_fP8_GXColorP5Vec2d(
    Vec* reflectionVec, Vec* positions, Vec* normals, long count, Vec waterOrigin, float (*matrix)[4], _GXColor* color, Vec2d* texCoord)
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

    transformedCameraPos.x = FLOAT_80330e4c;
    transformedCameraPos.y = FLOAT_80330e4c;
    transformedCameraPos.z = FLOAT_80330e4c;

    PSMTXCopy(matrix, matrixNoTranslate);
    objPos.x = matrixNoTranslate[0][3];
    objPos.y = matrixNoTranslate[1][3];
    objPos.z = matrixNoTranslate[2][3];
    matrixNoTranslate[0][3] = transformedCameraPos.x;
    matrixNoTranslate[1][3] = transformedCameraPos.y;
    matrixNoTranslate[2][3] = transformedCameraPos.z;
    PSMTXInverse(matrixNoTranslate, inverseMtx);

    PSVECSubtract(&objPos, &cameraPos, &cameraPos);
    PSVECScale(&cameraPos, &cameraPos, FLOAT_80330e68);
    PSMTXMultVec(inverseMtx, &cameraPos, &transformedCameraPos);

    texCoordFloat = (float*)texCoord;
    colorBytes = (unsigned char*)color;
    zero = (double)FLOAT_80330e4c;
    half = (double)FLOAT_80330e5c;

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
            *texCoordFloat = -reflectionVec->x / (FLOAT_80330e58 - reflectionVec->z);
            texCoordFloat[1] = -reflectionVec->y / (FLOAT_80330e58 - reflectionVec->z);
        } else {
            colorBytes[0] = 0x80;
            colorBytes[1] = 0x80;
            colorBytes[2] = 0xff;
            colorBytes[3] = 0xbc;
            *texCoordFloat = -reflectionVec->x / (FLOAT_80330e58 + reflectionVec->z);
            texCoordFloat[1] = -reflectionVec->y / (FLOAT_80330e58 + reflectionVec->z);
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
    DCFlushRange(texCoord, count * sizeof(Vec2d));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalcReflectionVector2(Vec*, S16Vec*, S16Vec*, long, unsigned long, unsigned long, float (*) [4], void*, unsigned long, _GXColor*, S16Vec2d*, S16Vec2d*, CChara::CNode*, PYmMana*, VYmMana*)
{
	// TODO
}
