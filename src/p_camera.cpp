#include "ffcc/p_camera.h"

#include "ffcc/materialman.h"
#include "ffcc/memory.h"
#include "ffcc/pad.h"
#include "ffcc/gobject.h"
#include "ffcc/p_game.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSCache.h>
#include <math.h>

extern Mtx ppvCameraMatrix0;
extern float FLOAT_8032fa30;
extern float FLOAT_8032fa34;
extern float FLOAT_8032fa38;
extern float FLOAT_8032fa1c;
extern float FLOAT_8032fa20;
extern float FLOAT_8032fa40;
extern float FLOAT_8032fa44;
extern float FLOAT_8032fa48;
extern float FLOAT_8032fa4c;
extern float FLOAT_8032fa50;
extern float FLOAT_8032fa54;
extern float FLOAT_8032fa5c;
extern float FLOAT_8032fa58;
extern float FLOAT_8032fa8c;
extern float FLOAT_8032fa78;
extern float FLOAT_8032fa7c;
extern float FLOAT_8032fa94;
extern float FLOAT_8032fa98;
extern float FLOAT_8032fa9c;
extern float FLOAT_8032faa0;
extern float FLOAT_8032fa3c;
extern float FLOAT_8032fac8;
extern float FLOAT_8032faa4;
extern float FLOAT_8032faa8;
extern float FLOAT_8032fab0;
extern float FLOAT_8032fab4;
extern float FLOAT_8032fab8;
extern float FLOAT_8032fabc;
extern CMaterialMan MaterialMan;
extern char DAT_801d7928[];
extern unsigned char MapMng[];
extern unsigned char CFlat[];
extern float FLOAT_8032fa18;
extern float FLOAT_8032fa70;
extern "C" void Printf__7CSystemFPce(CSystem* system, char* format, ...);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long size, CMemory::CStage* stage, char* file, int line);
extern "C" void __dl__FPv(void*);
extern "C" CGObject* FindGObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" void SetFrustum__6CBoundFR3VecPA4_f(float* bound, Vec* point, Mtx matrix);
extern "C" int CheckFrustum0__6CBoundFR6CBound(float* lhs, float* rhs);

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
 * PAL Address: 0x800394d0
 * PAL Size: 1708b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::calc()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    bool useDebugPad = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
    unsigned short padButtons;
    unsigned int padOffset;
    float stick;
    float yaw;
    float pitch;
    float dolly;
    float move;
    double dYaw;
    double dPitch;
    Mtx rotMtx;
    Mtx invMtx;
    Mtx mapMtx;
    Vec up;
    unsigned int hiA;
    unsigned int hiB;

    if (useDebugPad) {
        padButtons = 0;
        padOffset = 0;
    } else {
        padOffset = ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54);
        padButtons = *reinterpret_cast<unsigned short*>(
            reinterpret_cast<unsigned char*>(&Pad) + 4 +
            padOffset);
    }

    if ((padButtons & 0x20) != 0) {
        *reinterpret_cast<unsigned int*>(self + 0x444) =
            (__cntlzw(*reinterpret_cast<unsigned int*>(self + 0x444)) >> 5) & 0xFF;
    }

    if (*reinterpret_cast<int*>(self + 0x444) == 0) {
        stick = FLOAT_8032fa34;
        if (!useDebugPad) {
            stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x2C + padOffset);
        }
        *reinterpret_cast<float*>(self + 0xF8) += FLOAT_8032fa70 * FLOAT_8032fa8c * stick;

        stick = FLOAT_8032fa34;
        if (!useDebugPad) {
            stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x30 + padOffset);
        }
        *reinterpret_cast<float*>(self + 0x440) += FLOAT_8032fa70 * FLOAT_8032fabc * stick;

        stick = FLOAT_8032fa34;
        if (!useDebugPad) {
            stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x1C + padOffset);
        }
        *reinterpret_cast<float*>(self + 0x43C) += FLOAT_8032fabc * stick;

        yaw = FLOAT_8032fa34;
        if (!useDebugPad) {
            yaw = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x24 + padOffset);
        }

        pitch = FLOAT_8032fa34;
        if (!useDebugPad) {
            pitch = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x28 + padOffset);
        }

        dYaw = static_cast<double>(*reinterpret_cast<float*>(self + 0x440));
        dPitch = static_cast<double>(*reinterpret_cast<float*>(self + 0xF8));
        dolly = -(FLOAT_8032fabc * pitch - FLOAT_8032fabc * yaw);

        move = FLOAT_8032fa34;
        if (!useDebugPad) {
            move = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20 + padOffset);
        }
        move *= FLOAT_8032fa8c;

        *reinterpret_cast<float*>(self + 0xD4) +=
            static_cast<float>(sin(dPitch) * cos(dYaw) * static_cast<double>(move));
        *reinterpret_cast<float*>(self + 0xD8) +=
            static_cast<float>(sin(dYaw) * static_cast<double>(move) + static_cast<double>(dolly));
        *reinterpret_cast<float*>(self + 0xDC) =
            -((cos(dPitch) * cos(dYaw) * static_cast<double>(move)) - *reinterpret_cast<float*>(self + 0xDC));

        *reinterpret_cast<float*>(self + 0xE0) =
            *reinterpret_cast<float*>(self + 0x43C) *
                static_cast<float>(sin(dPitch) * cos(dYaw)) +
            *reinterpret_cast<float*>(self + 0xD4);
        *reinterpret_cast<float*>(self + 0xE4) =
            *reinterpret_cast<float*>(self + 0x43C) * static_cast<float>(sin(dYaw)) +
            *reinterpret_cast<float*>(self + 0xD8);
        *reinterpret_cast<float*>(self + 0xE8) =
            -(*reinterpret_cast<float*>(self + 0x43C) * static_cast<float>(cos(dPitch) * cos(dYaw)) -
              *reinterpret_cast<float*>(self + 0xDC));
    } else {
        *reinterpret_cast<float*>(self + 0xF8) = static_cast<float>(atan2(
            static_cast<double>(*reinterpret_cast<float*>(self + 0xE0) - *reinterpret_cast<float*>(self + 0xD4)),
            static_cast<double>(*reinterpret_cast<float*>(self + 0xDC) - *reinterpret_cast<float*>(self + 0xE8))));
    }

    CalcQuake();

    SetStdProjectionMatrix();

    up.x = FLOAT_8032fa34;
    up.y = FLOAT_8032fa1c;
    up.z = FLOAT_8032fa34;
    PSVECDistance(reinterpret_cast<Vec*>(self + 0xE0), reinterpret_cast<Vec*>(self + 0xD4));
    C_MTXLookAt(reinterpret_cast<MtxPtr>(self + 0x4),
                reinterpret_cast<Vec*>(self + 0xE0),
                &up,
                reinterpret_cast<Vec*>(self + 0xD4));

    if (Game.game.m_currentMapId == 0x21) {
        PSMTXCopy(reinterpret_cast<MtxPtr>(self + 0x34), mapMtx);
        if ((*reinterpret_cast<short*>(self + 0x47E) != 0) && (*reinterpret_cast<short*>(self + 0x480) != 0)) {
            hiA = static_cast<unsigned int>(static_cast<int>(*reinterpret_cast<short*>(self + 0x480)) ^ 0x80000000);
            hiB = static_cast<unsigned int>(static_cast<int>(*reinterpret_cast<short*>(self + 0x47E)) ^ 0x80000000);
            yaw = FLOAT_8032fa1c -
                  static_cast<float>((static_cast<double>(static_cast<float>(static_cast<int>(hiA ^ 0x80000000))) /
                                     static_cast<double>(static_cast<float>(static_cast<int>(hiB ^ 0x80000000)))));
            move = static_cast<float>(cos(FLOAT_8032fa18 * yaw));
            move = FLOAT_8032fa20 * (FLOAT_8032fa1c + move);

            PSMTXRotRad(rotMtx, 'x', *reinterpret_cast<float*>(self + 0x484) * move);
            PSMTXConcat(rotMtx, mapMtx, mapMtx);

            PSMTXRotRad(rotMtx, 'y', *reinterpret_cast<float*>(self + 0x488) * move);
            PSMTXConcat(rotMtx, mapMtx, mapMtx);

            yaw = -(*reinterpret_cast<float*>(self + 0x48C) * (FLOAT_8032fa1c - move) -
                    (FLOAT_8032fa1c + *reinterpret_cast<float*>(self + 0x48C)));
            PSMTXScale(rotMtx, yaw, yaw, yaw);
            PSMTXConcat(rotMtx, mapMtx, mapMtx);

            if (static_cast<signed char>(self[0x47C]) >= 0) {
                *reinterpret_cast<short*>(self + 0x480) =
                    static_cast<short>(*reinterpret_cast<short*>(self + 0x480) - 1);
            }
        }
        PSMTXConcat(reinterpret_cast<MtxPtr>(self + 0x4), mapMtx, reinterpret_cast<MtxPtr>(self + 0x4));
    }

    PSMTXRotRad(rotMtx, 'z', *reinterpret_cast<float*>(self + 0x108));
    PSMTXConcat(rotMtx, reinterpret_cast<MtxPtr>(self + 0x4), reinterpret_cast<MtxPtr>(self + 0x4));

    PSMTXInverse(reinterpret_cast<MtxPtr>(self + 0x4), invMtx);
    *reinterpret_cast<float*>(self + 0xEC) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF4) = FLOAT_8032fa38;
    PSMTXMultVecSR(invMtx, reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xEC));
    *reinterpret_cast<unsigned int*>(self + 0x438) = 0;
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
 * PAL Address: 0x80038b18
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::destroyMap()
{
    return;
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
 * PAL Address: 0x800382f8
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::destroyFullShadow()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    if (*reinterpret_cast<void**>(self + 0x31C) != 0) {
        __dl__FPv(*reinterpret_cast<void**>(self + 0x31C));
        *reinterpret_cast<void**>(self + 0x31C) = 0;
    }

    if (*reinterpret_cast<void**>(self + 0x320) != 0) {
        __dl__FPv(*reinterpret_cast<void**>(self + 0x320));
        *reinterpret_cast<void**>(self + 0x320) = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80038050
 * PAL Size: 680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCameraPcs::GetShadowRect(CBound&)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    int count = 0;
    Mtx invView;
    Mtx frustumMtx;
    float cameraBound[6];
    float* shadowRect = reinterpret_cast<float*>(self + 0x414);

    PSMTXInverse(reinterpret_cast<MtxPtr>(self + 0x4), invView);
    Vec eyePos;
    eyePos.x = invView[0][3];
    eyePos.y = invView[1][3];
    eyePos.z = invView[2][3];

    PSMTXScaleApply(reinterpret_cast<MtxPtr>(self + 0x4), frustumMtx,
                    FLOAT_8032fa94 * *reinterpret_cast<float*>(self + 0x94),
                    FLOAT_8032fa98 * *reinterpret_cast<float*>(self + 0xA8),
                    FLOAT_8032fa1c);
    SetFrustum__6CBoundFR3VecPA4_f(cameraBound, &eyePos, frustumMtx);

    for (CGObject* gObject = FindGObjFirst__13CFlatRuntime2Fv(CFlat); gObject != 0;
         gObject = FindGObjNext__13CFlatRuntime2FP8CGObject(CFlat, gObject))
    {
        bool include = false;
        if (gObject->m_charaModelHandle != 0) {
            unsigned int displayFlags = gObject->m_displayFlags;
            if ((displayFlags & 1) != 0 && (displayFlags & 0x40) == 0) {
                if (static_cast<signed char>(gObject->m_weaponNodeFlags >> 8) < 0) {
                    if ((displayFlags & 0x80) != 0 || gObject->m_lookAtTimer == FLOAT_8032fa1c) {
                        include = true;
                    }
                }
            }
        }

        if (!include) {
            continue;
        }

        float radius = gObject->m_nearColRadius;
        if (FLOAT_8032fa9c < radius) {
            radius = FLOAT_8032fa9c;
        }

        float minX = gObject->m_worldPosition.x - radius;
        float minY = gObject->m_worldPosition.y;
        float minZ = gObject->m_worldPosition.z - radius;
        float maxX = gObject->m_worldPosition.x + radius;
        float maxY = gObject->m_worldPosition.y + radius;
        float maxZ = gObject->m_worldPosition.z + radius;

        float clipBound[6];
        clipBound[0] = FLOAT_8032fa78;
        clipBound[1] = FLOAT_8032fa78;
        clipBound[2] = FLOAT_8032fa78;
        clipBound[3] = FLOAT_8032fa7c;
        clipBound[4] = FLOAT_8032fa7c;
        clipBound[5] = FLOAT_8032fa7c;

        float worldBound[6];
        worldBound[0] = minX;
        worldBound[1] = minY;
        worldBound[2] = minZ;
        worldBound[3] = maxX;
        worldBound[4] = maxY;
        worldBound[5] = maxZ;

        if (CheckFrustum0__6CBoundFR6CBound(worldBound, clipBound) == 0) {
            continue;
        }
        if (FLOAT_8032faa0 >= clipBound[0]) {
            continue;
        }
        if ((FLOAT_8032fa48 >= (clipBound[5] - clipBound[2]) / -clipBound[0]) &&
            (FLOAT_8032fa48 >= (clipBound[4] - clipBound[1]) / -clipBound[0])) {
            continue;
        }

        if (shadowRect[0] < minX) {
            shadowRect[0] = minX;
        }
        if (shadowRect[1] < minY) {
            shadowRect[1] = minY;
        }
        if (shadowRect[2] < minZ) {
            shadowRect[2] = minZ;
        }
        if (maxX < shadowRect[3]) {
            shadowRect[3] = maxX;
        }
        if (maxY < shadowRect[4]) {
            shadowRect[4] = maxY;
        }
        if (maxZ < shadowRect[5]) {
            shadowRect[5] = maxZ;
        }
        count += 1;
    }

    return count;
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
 * PAL Address: 0x80036a18
 * PAL Size: 544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::drawShadowEndAll()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    if (self[0x404] == 0) {
        return;
    }

    *reinterpret_cast<unsigned int*>(self + 0x4) = *reinterpret_cast<unsigned int*>(self + 0x10C);
    *reinterpret_cast<unsigned int*>(self + 0x8) = *reinterpret_cast<unsigned int*>(self + 0x110);
    *reinterpret_cast<unsigned int*>(self + 0xC) = *reinterpret_cast<unsigned int*>(self + 0x114);
    *reinterpret_cast<unsigned int*>(self + 0x10) = *reinterpret_cast<unsigned int*>(self + 0x118);
    *reinterpret_cast<unsigned int*>(self + 0x14) = *reinterpret_cast<unsigned int*>(self + 0x11C);
    *reinterpret_cast<unsigned int*>(self + 0x18) = *reinterpret_cast<unsigned int*>(self + 0x120);
    *reinterpret_cast<unsigned int*>(self + 0x1C) = *reinterpret_cast<unsigned int*>(self + 0x124);
    *reinterpret_cast<unsigned int*>(self + 0x20) = *reinterpret_cast<unsigned int*>(self + 0x128);
    *reinterpret_cast<unsigned int*>(self + 0x24) = *reinterpret_cast<unsigned int*>(self + 0x12C);
    *reinterpret_cast<unsigned int*>(self + 0x28) = *reinterpret_cast<unsigned int*>(self + 0x130);
    *reinterpret_cast<unsigned int*>(self + 0x2C) = *reinterpret_cast<unsigned int*>(self + 0x134);
    *reinterpret_cast<unsigned int*>(self + 0x30) = *reinterpret_cast<unsigned int*>(self + 0x138);
    *reinterpret_cast<unsigned int*>(self + 0x34) = *reinterpret_cast<unsigned int*>(self + 0x13C);
    *reinterpret_cast<unsigned int*>(self + 0x38) = *reinterpret_cast<unsigned int*>(self + 0x140);
    *reinterpret_cast<unsigned int*>(self + 0x3C) = *reinterpret_cast<unsigned int*>(self + 0x144);
    *reinterpret_cast<unsigned int*>(self + 0x40) = *reinterpret_cast<unsigned int*>(self + 0x148);
    *reinterpret_cast<unsigned int*>(self + 0x44) = *reinterpret_cast<unsigned int*>(self + 0x14C);
    *reinterpret_cast<unsigned int*>(self + 0x48) = *reinterpret_cast<unsigned int*>(self + 0x150);
    *reinterpret_cast<unsigned int*>(self + 0x4C) = *reinterpret_cast<unsigned int*>(self + 0x154);
    *reinterpret_cast<unsigned int*>(self + 0x50) = *reinterpret_cast<unsigned int*>(self + 0x158);
    *reinterpret_cast<unsigned int*>(self + 0x54) = *reinterpret_cast<unsigned int*>(self + 0x15C);
    *reinterpret_cast<unsigned int*>(self + 0x58) = *reinterpret_cast<unsigned int*>(self + 0x160);
    *reinterpret_cast<unsigned int*>(self + 0x5C) = *reinterpret_cast<unsigned int*>(self + 0x164);
    *reinterpret_cast<unsigned int*>(self + 0x60) = *reinterpret_cast<unsigned int*>(self + 0x168);
    *reinterpret_cast<unsigned int*>(self + 0x64) = *reinterpret_cast<unsigned int*>(self + 0x16C);
    *reinterpret_cast<unsigned int*>(self + 0x68) = *reinterpret_cast<unsigned int*>(self + 0x170);
    *reinterpret_cast<unsigned int*>(self + 0x6C) = *reinterpret_cast<unsigned int*>(self + 0x174);
    *reinterpret_cast<unsigned int*>(self + 0x70) = *reinterpret_cast<unsigned int*>(self + 0x178);
    *reinterpret_cast<unsigned int*>(self + 0x74) = *reinterpret_cast<unsigned int*>(self + 0x17C);
    *reinterpret_cast<unsigned int*>(self + 0x78) = *reinterpret_cast<unsigned int*>(self + 0x180);
    *reinterpret_cast<unsigned int*>(self + 0x7C) = *reinterpret_cast<unsigned int*>(self + 0x184);
    *reinterpret_cast<unsigned int*>(self + 0x80) = *reinterpret_cast<unsigned int*>(self + 0x188);
    *reinterpret_cast<unsigned int*>(self + 0x84) = *reinterpret_cast<unsigned int*>(self + 0x18C);
    *reinterpret_cast<unsigned int*>(self + 0x88) = *reinterpret_cast<unsigned int*>(self + 0x190);
    *reinterpret_cast<unsigned int*>(self + 0x8C) = *reinterpret_cast<unsigned int*>(self + 0x194);
    *reinterpret_cast<unsigned int*>(self + 0x90) = *reinterpret_cast<unsigned int*>(self + 0x198);
    *reinterpret_cast<unsigned int*>(self + 0x94) = *reinterpret_cast<unsigned int*>(self + 0x19C);
    *reinterpret_cast<unsigned int*>(self + 0x98) = *reinterpret_cast<unsigned int*>(self + 0x1A0);
    *reinterpret_cast<unsigned int*>(self + 0x9C) = *reinterpret_cast<unsigned int*>(self + 0x1A4);
    *reinterpret_cast<unsigned int*>(self + 0xA0) = *reinterpret_cast<unsigned int*>(self + 0x1A8);
    *reinterpret_cast<unsigned int*>(self + 0xA4) = *reinterpret_cast<unsigned int*>(self + 0x1AC);
    *reinterpret_cast<unsigned int*>(self + 0xA8) = *reinterpret_cast<unsigned int*>(self + 0x1B0);
    *reinterpret_cast<unsigned int*>(self + 0xAC) = *reinterpret_cast<unsigned int*>(self + 0x1B4);
    *reinterpret_cast<unsigned int*>(self + 0xB0) = *reinterpret_cast<unsigned int*>(self + 0x1B8);
    *reinterpret_cast<unsigned int*>(self + 0xB4) = *reinterpret_cast<unsigned int*>(self + 0x1BC);
    *reinterpret_cast<unsigned int*>(self + 0xB8) = *reinterpret_cast<unsigned int*>(self + 0x1C0);
    *reinterpret_cast<unsigned int*>(self + 0xBC) = *reinterpret_cast<unsigned int*>(self + 0x1C4);
    *reinterpret_cast<unsigned int*>(self + 0xC0) = *reinterpret_cast<unsigned int*>(self + 0x1C8);
    *reinterpret_cast<unsigned int*>(self + 0xC4) = *reinterpret_cast<unsigned int*>(self + 0x1CC);
    *reinterpret_cast<unsigned int*>(self + 0xC8) = *reinterpret_cast<unsigned int*>(self + 0x1D0);
    *reinterpret_cast<unsigned int*>(self + 0xCC) = *reinterpret_cast<unsigned int*>(self + 0x1D4);
    *reinterpret_cast<unsigned int*>(self + 0xD0) = *reinterpret_cast<unsigned int*>(self + 0x1D8);
    *reinterpret_cast<unsigned int*>(self + 0xD4) = *reinterpret_cast<unsigned int*>(self + 0x1DC);
    *reinterpret_cast<unsigned int*>(self + 0xD8) = *reinterpret_cast<unsigned int*>(self + 0x1E0);
    *reinterpret_cast<unsigned int*>(self + 0xDC) = *reinterpret_cast<unsigned int*>(self + 0x1E4);
    *reinterpret_cast<unsigned int*>(self + 0xE0) = *reinterpret_cast<unsigned int*>(self + 0x1E8);
    *reinterpret_cast<unsigned int*>(self + 0xE4) = *reinterpret_cast<unsigned int*>(self + 0x1EC);
    *reinterpret_cast<unsigned int*>(self + 0xE8) = *reinterpret_cast<unsigned int*>(self + 0x1F0);
    *reinterpret_cast<unsigned int*>(self + 0xEC) = *reinterpret_cast<unsigned int*>(self + 0x1F4);
    *reinterpret_cast<unsigned int*>(self + 0xF0) = *reinterpret_cast<unsigned int*>(self + 0x1F8);
    *reinterpret_cast<unsigned int*>(self + 0xF4) = *reinterpret_cast<unsigned int*>(self + 0x1FC);
    *reinterpret_cast<unsigned int*>(self + 0xF8) = *reinterpret_cast<unsigned int*>(self + 0x200);
    *reinterpret_cast<unsigned int*>(self + 0xFC) = *reinterpret_cast<unsigned int*>(self + 0x204);
    *reinterpret_cast<unsigned int*>(self + 0x100) = *reinterpret_cast<unsigned int*>(self + 0x208);
    *reinterpret_cast<unsigned int*>(self + 0x104) = *reinterpret_cast<unsigned int*>(self + 0x20C);
    *reinterpret_cast<unsigned int*>(self + 0x108) = *reinterpret_cast<unsigned int*>(self + 0x210);
}

/*
 * --INFO--
 * PAL Address: 0x800369d4
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::createMaterialEditor()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    *reinterpret_cast<int*>(self + 0x46C) = 0;
    *reinterpret_cast<float*>(self + 0x450) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x44C) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x448) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x45C) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x458) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x454) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x468) = FLOAT_8032fa1c;
    *reinterpret_cast<float*>(self + 0x464) = FLOAT_8032fa1c;
    *reinterpret_cast<float*>(self + 0x460) = FLOAT_8032fa1c;
    *reinterpret_cast<float*>(self + 0x44C) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x450) = FLOAT_8032fa50;
}

/*
 * --INFO--
 * PAL Address: 0x800369d0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::destroyMaterialEditor()
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80036700
 * PAL Size: 720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::calcMaterialEditor()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned short padButtons;
    Mtx mtxA;
    Mtx mtxB;
    Mtx mtxInv;
    float stick;

    C_MTXPerspective(reinterpret_cast<Mtx44Ptr>(self + 0x94), FLOAT_8032fa30, FLOAT_8032fa3c,
                     FLOAT_8032fa40, FLOAT_8032fa54);
    GXSetProjection(reinterpret_cast<Mtx44Ptr>(self + 0x94), GX_PERSPECTIVE);

    if (Pad._452_4_ == 0) {
        padButtons = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 4 +
                                                        ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    } else {
        padButtons = 0;
    }

    if ((padButtons & 8) != 0) {
        *reinterpret_cast<float*>(self + 0x44C) += FLOAT_8032fa20;
    }
    if ((padButtons & 4) != 0) {
        *reinterpret_cast<float*>(self + 0x44C) -= FLOAT_8032fa20;
    }

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x24 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    *reinterpret_cast<float*>(self + 0x458) =
        FLOAT_8032fa48 * stick + *reinterpret_cast<float*>(self + 0x458);

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x28 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    *reinterpret_cast<float*>(self + 0x454) =
        -((FLOAT_8032fa48 * stick) - *reinterpret_cast<float*>(self + 0x454));

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x1C +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    *reinterpret_cast<float*>(self + 0x45C) =
        -((FLOAT_8032fa4c * stick) - *reinterpret_cast<float*>(self + 0x45C));

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    *reinterpret_cast<float*>(self + 0x45C) =
        FLOAT_8032fa4c * stick + *reinterpret_cast<float*>(self + 0x45C);

    PSMTXTrans(mtxA, *reinterpret_cast<float*>(self + 0x448), *reinterpret_cast<float*>(self + 0x44C),
               *reinterpret_cast<float*>(self + 0x450));
    PSMTXRotRad(mtxB, 'y', *reinterpret_cast<float*>(self + 0x458));
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXRotRad(mtxB, 'x', *reinterpret_cast<float*>(self + 0x454));
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXTrans(mtxB, FLOAT_8032fa34, FLOAT_8032fa34, -*reinterpret_cast<float*>(self + 0x45C));
    PSMTXConcat(mtxB, mtxA, reinterpret_cast<MtxPtr>(self + 4));
    PSMTXInverse(reinterpret_cast<MtxPtr>(self + 4), mtxInv);

    *reinterpret_cast<float*>(self + 0xEC) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF4) = FLOAT_8032fa38;
    PSMTXMultVecSR(mtxInv, reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xEC));
}

/*
 * --INFO--
 * PAL Address: 0x800366bc
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::createFunnyShape()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    *reinterpret_cast<int*>(self + 0x46C) = 0;
    *reinterpret_cast<float*>(self + 0x450) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x44C) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x448) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x45C) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x458) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x454) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x468) = FLOAT_8032fa1c;
    *reinterpret_cast<float*>(self + 0x464) = FLOAT_8032fa1c;
    *reinterpret_cast<float*>(self + 0x460) = FLOAT_8032fa1c;
    *reinterpret_cast<float*>(self + 0x44C) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x450) = FLOAT_8032fa50;
}

/*
 * --INFO--
 * PAL Address: 0x800366b8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::destroyFunnyShape()
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x800363e8
 * PAL Size: 720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::calcFunnyShape()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned short padButtons;
    Mtx mtxA;
    Mtx mtxB;
    Mtx mtxInv;
    float stick;

    C_MTXPerspective(reinterpret_cast<Mtx44Ptr>(self + 0x94), FLOAT_8032fa30, FLOAT_8032fa3c,
                     FLOAT_8032fa40, FLOAT_8032fa44);
    GXSetProjection(reinterpret_cast<Mtx44Ptr>(self + 0x94), GX_PERSPECTIVE);

    if (Pad._452_4_ == 0) {
        padButtons = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 4 +
                                                        ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    } else {
        padButtons = 0;
    }

    if ((padButtons & 8) != 0) {
        *reinterpret_cast<float*>(self + 0x44C) += FLOAT_8032fa20;
    }
    if ((padButtons & 4) != 0) {
        *reinterpret_cast<float*>(self + 0x44C) -= FLOAT_8032fa20;
    }

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x24 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    *reinterpret_cast<float*>(self + 0x458) =
        FLOAT_8032fa48 * stick + *reinterpret_cast<float*>(self + 0x458);

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x28 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    *reinterpret_cast<float*>(self + 0x454) =
        -((FLOAT_8032fa48 * stick) - *reinterpret_cast<float*>(self + 0x454));

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x1C +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    *reinterpret_cast<float*>(self + 0x45C) =
        -((FLOAT_8032fa4c * stick) - *reinterpret_cast<float*>(self + 0x45C));

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    *reinterpret_cast<float*>(self + 0x45C) =
        FLOAT_8032fa4c * stick + *reinterpret_cast<float*>(self + 0x45C);

    PSMTXTrans(mtxA, *reinterpret_cast<float*>(self + 0x448), *reinterpret_cast<float*>(self + 0x44C),
               *reinterpret_cast<float*>(self + 0x450));
    PSMTXRotRad(mtxB, 'y', *reinterpret_cast<float*>(self + 0x458));
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXRotRad(mtxB, 'x', *reinterpret_cast<float*>(self + 0x454));
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXTrans(mtxB, FLOAT_8032fa34, FLOAT_8032fa34, -*reinterpret_cast<float*>(self + 0x45C));
    PSMTXConcat(mtxB, mtxA, reinterpret_cast<MtxPtr>(self + 4));
    PSMTXInverse(reinterpret_cast<MtxPtr>(self + 4), mtxInv);

    *reinterpret_cast<float*>(self + 0xEC) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF4) = FLOAT_8032fa38;
    PSMTXMultVecSR(mtxInv, reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xEC));
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
