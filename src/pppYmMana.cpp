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
 * Address:	TODO
 * Size:	TODO
 */
void SetEnvMap(PYmMana*, VYmMana*)
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
