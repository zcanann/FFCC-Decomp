#include "ffcc/pppMana2.h"
#include "ffcc/graphic.h"
#include "ffcc/gobject.h"
#include "ffcc/pppPart.h"

extern char lbl_801DC4D0[];
extern float FLOAT_803318fc;

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Mana2_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*) [4])
{
	// TODO
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

    gObject = *(CGObject**)((char*)pppMngStPtr + 0x8);
    work = (u32*)((char*)pppMana2 + 2 + param_2->m_serializedDataOffsets[2]);
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
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameMana2(pppMana2*, UnkB*, UnkC*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CalcReflectionVector2(Vec*, S16Vec*, S16Vec*, long, unsigned long, unsigned long, float (*) [4], void*, unsigned long, _GXColor*, S16Vec2d*, CChara::CNode*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void UpdateWaterMesh(VMana2*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RenderWaterMesh(VMana2*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalculateNormal(VMana2*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
extern "C" void CalcWaterReflectionVector__FP3VecP3VecP3Vecl3VecPA4_fP8_GXColorP5Vec2d2(
    Vec*, Vec*, Vec*, long, Vec, float (*) [4], _GXColor*, Vec2d*, Vec2d*)
{
	// TODO
}
