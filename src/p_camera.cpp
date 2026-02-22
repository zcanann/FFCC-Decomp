#include "ffcc/p_camera.h"

#include "ffcc/materialman.h"

#include <dolphin/mtx.h>

extern Mtx ppvCameraMatrix0;
extern float FLOAT_8032fa30;
extern float FLOAT_8032fa34;
extern float FLOAT_8032fa38;
extern float FLOAT_8032fa5c;
extern float FLOAT_8032fa58;
extern float FLOAT_8032fa8c;
extern float FLOAT_8032fab0;
extern float FLOAT_8032fab4;
extern float FLOAT_8032fab8;
extern CMaterialMan MaterialMan;

extern "C" {
void pppEditGetViewPos__FP3Vec(Vec*);
void pppEditGetViewMatrix__FPA4_f(float (*)[4]);
void pppEditGetProjectionMatrix__FPA4_f(float (*)[4]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void dbgDrawSphere(float, float, float, float, unsigned char, unsigned char, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCameraPcs::CCameraPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::onScriptChanging(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::onScriptChanged(char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::SetQuakeParameter(int, int, short, short, float, float, float, float, float, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::CalcQuake()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::SetStdProjectionMatrix()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::calcViewerCameraMatrix(float (*) [4], const SRT*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::SetViewerSRT(const SRT*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::createChara()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::destroyChara()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::calcChara()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80038b1c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::createMap()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;

    fVar2 = FLOAT_8032fa5c;
    fVar1 = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x478) = FLOAT_8032fa34;
    fVar4 = FLOAT_8032fab0;
    *reinterpret_cast<float*>(self + 0x474) = fVar1;
    fVar5 = FLOAT_8032fab4;
    *reinterpret_cast<float*>(self + 0x470) = fVar1;
    fVar3 = FLOAT_8032fa8c;
    *reinterpret_cast<float*>(self + 0xE8) = fVar1;
    fVar6 = FLOAT_8032fab8;
    *reinterpret_cast<float*>(self + 0xE4) = fVar1;
    *reinterpret_cast<float*>(self + 0xE0) = fVar1;
    *reinterpret_cast<float*>(self + 0xF8) = fVar1;
    *reinterpret_cast<float*>(self + 0x43C) = fVar2;
    *reinterpret_cast<float*>(self + 0x440) = fVar4;
    *reinterpret_cast<float*>(self + 0xFC) = fVar5;
    *reinterpret_cast<float*>(self + 0x100) = fVar3;
    *reinterpret_cast<float*>(self + 0x104) = fVar6;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::destroyMap()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::calcMap()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::createRampTex8()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::createFullShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::destroyFullShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::GetShadowRect(CBound&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::drawShadowBegin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::drawShadowEnd()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80036c7c
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::drawShadowChrBegin()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    if (self[0x404] != 0) {
        *reinterpret_cast<float*>(self + 0x3E0) *= FLOAT_8032fa58;
        *reinterpret_cast<float*>(self + 0x3F0) *= FLOAT_8032fa58;
        PSMTXConcat(reinterpret_cast<MtxPtr>(self + 0x3D4),
                    reinterpret_cast<MtxPtr>(self + 0x214),
                    reinterpret_cast<MtxPtr>(self + 0x3A4));
    }
}

/*
 * --INFO--
 * PAL Address: 0x80036c38
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetFullScreenShadow(float (*matrix)[4], long flags)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    if (self[0x404] != 0) {
        MaterialMan.SetFullScreenShadow(*reinterpret_cast<CFullScreenShadow*>(self + 0x31C),
                                        matrix, flags);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::drawShadowEndAll()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::createMaterialEditor()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::destroyMaterialEditor()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::calcMaterialEditor()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::createFunnyShape()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::destroyFunnyShape()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::calcFunnyShape()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800363dc
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::createPart()
{
    reinterpret_cast<unsigned char*>(this)[0x404] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800363d8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::destroyPart()
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x800362e4
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::calcPart()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    Mtx invCamera;
    Vec pos;

    if (*reinterpret_cast<int*>(self + 0x494) != 0) {
        CalcQuake();

        pos.x = ppvCameraMatrix0[0][3];
        pos.y = ppvCameraMatrix0[1][3];
        pos.z = ppvCameraMatrix0[2][3];

        PSVECAdd(reinterpret_cast<Vec*>(self + 0x4A4), &pos, &pos);

        ppvCameraMatrix0[0][3] = pos.x;
        ppvCameraMatrix0[1][3] = pos.y;
        ppvCameraMatrix0[2][3] = pos.z;
    }

    *reinterpret_cast<float*>(self + 0xFC) = FLOAT_8032fa30;

    pppEditGetViewPos__FP3Vec(reinterpret_cast<Vec*>(self + 0xE0));
    pppEditGetViewMatrix__FPA4_f(reinterpret_cast<float(*)[4]>(self + 0x4));
    pppEditGetProjectionMatrix__FPA4_f(reinterpret_cast<float(*)[4]>(self + 0x94));
    GXSetProjection(reinterpret_cast<float(*)[4]>(self + 0x94), GX_PERSPECTIVE);

    PSMTXInverse(reinterpret_cast<MtxPtr>(self + 0x4), invCamera);

    *reinterpret_cast<float*>(self + 0xEC) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF4) = FLOAT_8032fa38;

    PSMTXMultVecSR(invCamera, reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xEC));
    PSVECAdd(reinterpret_cast<Vec*>(self + 0xE0), reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xD4));
}

/*
 * --INFO--
 * PAL Address: 0x80036290
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetOffsetZBuff(float offset)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    Mtx44 projection;

    PSMTX44Copy(reinterpret_cast<Mtx44Ptr>(self + 0x94), projection);
    projection[2][3] += offset;
    GXSetProjection(projection, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::addWorldMap()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::SetIsAbsolute(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::SetWorldMapMatrix(float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::GetWorldMapInverseMatrix(float (*) [4])
{
	// TODO
}
