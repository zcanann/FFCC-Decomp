#include "ffcc/p_camera.h"

#include "ffcc/materialman.h"
#include "ffcc/memory.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSCache.h>

extern Mtx ppvCameraMatrix0;
extern float FLOAT_8032fa30;
extern float FLOAT_8032fa34;
extern float FLOAT_8032fa38;
extern float FLOAT_8032fa5c;
extern float FLOAT_8032fa58;
extern float FLOAT_8032fa8c;
extern float FLOAT_8032fa3c;
extern float FLOAT_8032fac8;
extern float FLOAT_8032faa4;
extern float FLOAT_8032faa8;
extern float FLOAT_8032fab0;
extern float FLOAT_8032fab4;
extern float FLOAT_8032fab8;
extern CMaterialMan MaterialMan;
extern char DAT_801d7928[];
extern unsigned char MapMng[];
extern "C" void Printf__7CSystemFPce(CSystem* system, char* format, ...);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long size, CMemory::CStage* stage, char* file, int line);

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
 * PAL Address: 0x80039450
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetStdProjectionMatrix()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    float fov = *reinterpret_cast<float*>(self + 0xFC);

    if (fov < FLOAT_8032fac8 && System.m_execParam != 0) {
        Printf__7CSystemFPce(&System, DAT_801d7928);
        fov = FLOAT_8032fab4;
    }

    C_MTXPerspective(reinterpret_cast<Mtx44Ptr>(self + 0x94), fov, FLOAT_8032fa3c,
                     *reinterpret_cast<float*>(self + 0x100),
                     *reinterpret_cast<float*>(self + 0x104));
    GXSetProjection(reinterpret_cast<Mtx44Ptr>(self + 0x94), GX_PERSPECTIVE);
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
 * PAL Address: 0x80038358
 * PAL Size: 624b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::createFullShadow()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned int rampTexSize;
    unsigned int i;
    unsigned char* rampTex;
    CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(MapMng);

    *reinterpret_cast<void**>(self + 0x31C) = 0;
    rampTexSize = GXGetTexBufferSize(0x1E0, 0x1E0, GX_TF_I8, GX_FALSE, 0);
    *reinterpret_cast<void**>(self + 0x31C) =
        __nwa__FUlPQ27CMemory6CStagePci(rampTexSize, stage, const_cast<char*>("p_camera.cpp"), 0x3A5);

    rampTexSize = GXGetTexBufferSize(0x10, 0x10, GX_TF_I8, GX_FALSE, 0);
    rampTex = static_cast<unsigned char*>(
        __nwa__FUlPQ27CMemory6CStagePci(rampTexSize, stage, const_cast<char*>("p_camera.cpp"), 0x361));
    *reinterpret_cast<unsigned char**>(self + 0x320) = rampTex;

    for (i = 0; i < 0x100; i += 8) {
        unsigned int i1 = i + 1;
        unsigned int i2 = i + 2;
        unsigned int i3 = i + 3;
        unsigned int i4 = i + 4;
        unsigned int i5 = i + 5;
        unsigned int i6 = i + 6;
        unsigned int i7 = i + 7;

        rampTex[(i & 0xC) * 0x10 + ((i >> 2) & 0x20) + ((i >> 4) & 7)] = static_cast<unsigned char>(i);
        rampTex[((i1 * 8) & 0x18) + ((i1 * 0x10) & 0xC0) + ((i1 >> 2) & 0x20) + ((i1 >> 4) & 7)] =
            static_cast<unsigned char>(i1);
        rampTex[((i2 * 8) & 0x18) + ((i2 * 0x10) & 0xC0) + ((i2 >> 2) & 0x20) + ((i2 >> 4) & 7)] =
            static_cast<unsigned char>(i2);
        rampTex[((i3 * 8) & 0x18) + ((i3 * 0x10) & 0xC0) + ((i3 >> 2) & 0x20) + ((i3 >> 4) & 7)] =
            static_cast<unsigned char>(i3);
        rampTex[((i4 * 0x10) & 0xC0) + ((i4 >> 2) & 0x20) + ((i4 >> 4) & 7)] = static_cast<unsigned char>(i4);
        rampTex[((i5 * 8) & 0x18) + ((i5 * 0x10) & 0xC0) + ((i5 >> 2) & 0x20) + ((i5 >> 4) & 7)] =
            static_cast<unsigned char>(i5);
        rampTex[((i6 * 8) & 0x18) + ((i6 * 0x10) & 0xC0) + ((i6 >> 2) & 0x20) + ((i6 >> 4) & 7)] =
            static_cast<unsigned char>(i6);
        rampTex[((i7 * 8) & 0x18) + ((i7 * 0x10) & 0xC0) + ((i7 >> 2) & 0x20) + ((i7 >> 4) & 7)] =
            static_cast<unsigned char>(i7);
    }

    GXInitTexObj(reinterpret_cast<GXTexObj*>(self + 0x344), rampTex, 0x10, 0x10, GX_TF_I8,
                 GX_CLAMP, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(reinterpret_cast<GXTexObj*>(self + 0x344), GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f,
                    GX_FALSE, GX_FALSE, GX_ANISO_1);
    DCFlushRange(rampTex, rampTexSize);

    self[0x404] = 1;
    *reinterpret_cast<float*>(self + 0x364) = FLOAT_8032faa4;
    *reinterpret_cast<float*>(self + 0x368) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x370) = FLOAT_8032faa8;
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
