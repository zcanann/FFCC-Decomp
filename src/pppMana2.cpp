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
    u32* work;

    gObject = *(CGObject**)((char*)pppMngStPtr + 0x8);
    work = (u32*)((char*)pppMana2 + 2 + param_2->m_serializedDataOffsets[2]);
    gObject->m_stepSlopeLimit = FLOAT_803318fc;

    handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

    work[0] = 0;
    work[1] = 0;
    work[8] = 0;
    work[9] = 0;
    work[10] = 0;
    work[11] = 0;
    work[12] = 0;
    work[13] = 0;
    work[15] = 0;
    work[16] = 0;
    work[17] = 0;
    work[18] = 0;
    work[20] = 0;
    work[21] = 0;
    work[22] = 0;
    work[23] = 0;
    work[24] = 0;
    work[25] = 0;
    work[26] = 0;
    work[27] = 0;
    work[28] = 0;
    work[29] = 0;
    work[30] = 0;
    work[31] = 0;
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
 * Address:	TODO
 * Size:	TODO
 */
void CreateWaterMesh(Vec* param_1, Vec* param_2, Vec2d* param_3, unsigned short* param_4, float param_5)
{
    float* pos;
    float* normal;
    float* uv;
    unsigned short* idx;
    float x;
    float z;
    short start;
    int row;
    int pair;
    const float zero = 0.0f;
    const float one = 1.0f;
    const float stepScale = 0.125f;
    float radius = 0.0f;
    float step = 0.0f;

    pos = (float*)param_1;
    normal = (float*)param_2;
    uv = (float*)param_3;
    idx = param_4;

    radius = param_5 * one;
    step = param_5 * stepScale;
    z = radius;

    for (row = 0; row <= 16; row++) {
        x = -radius;
        for (pair = 0; pair <= 16; pair++) {
            pos[0] = x;
            pos[1] = zero;
            pos[2] = z;
            pos += 3;

            normal[0] = zero;
            normal[1] = one;
            normal[2] = zero;
            normal += 3;

            uv[0] = (float)pair * stepScale;
            uv[1] = (float)row * stepScale;
            uv += 2;

            x += step;
        }
        z -= step;
    }

    start = 0;
    for (row = 0; row < 16; row++) {
        short v = start;
        for (pair = 0; pair < 8; pair++) {
            idx[0] = v;
            idx[1] = v + 1;
            idx[2] = v + 0x12;
            idx[3] = v + 0x12;
            idx[4] = v + 0x11;
            idx[5] = v;
            idx[6] = v + 1;
            idx[7] = v + 2;
            idx[8] = v + 0x13;
            idx[9] = v + 0x13;
            idx[10] = v + 0x12;
            idx[11] = v + 1;
            idx += 12;
            v += 2;
        }
        start += 0x11;
    }
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
void CalcWaterReflectionVector(Vec*, Vec*, Vec*, long, Vec*, float (*) [4], _GXColor*, Vec2d*)
{
	// TODO
}
