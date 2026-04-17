#include "ffcc/p_camera.h"

#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/map.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/pad.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/p_graphic.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"

#include <math.h>
#include <string.h>

#include <dolphin/mtx.h>
#include <dolphin/os/OSCache.h>

CCameraPcs CameraPcs;

extern float FLOAT_8032fa30;
extern float FLOAT_8032fa34;
extern float FLOAT_8032fa38;
extern float FLOAT_8032fa18;
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
extern float FLOAT_8032fabc;
extern float FLOAT_8032fa60;
extern float FLOAT_8032fa64;
extern float FLOAT_8032fa68;
extern float FLOAT_8032fa6c;
extern float FLOAT_8032fa70;
extern float FLOAT_8032fa74;
extern float FLOAT_8032fa80;
extern float FLOAT_8032fa84;
extern float FLOAT_8032fa88;
extern float FLOAT_8032fa90;
extern float FLOAT_8032fa8c;
extern float FLOAT_8032fa78;
extern float FLOAT_8032fa7c;
extern float FLOAT_8032fa94;
extern float FLOAT_8032fa98;
extern float FLOAT_8032fa9c;
extern float FLOAT_8032faa0;
extern float FLOAT_8032fa3c;
extern float FLOAT_8032fac8;
extern float FLOAT_8032fac0;
extern float FLOAT_8032fac4;
extern float FLOAT_8032faa4;
extern float FLOAT_8032faa8;
extern float FLOAT_8032faac;
extern float FLOAT_8032fab0;
extern float FLOAT_8032fab4;
extern float FLOAT_8032fab8;
extern double DOUBLE_8032fa28;
extern char DAT_801d7928[];
extern double DOUBLE_8032fa28;
unsigned char DAT_8032ecd8;
unsigned int PTR_s_CCameraPcs_GAME__801e915c[(0x15C / sizeof(unsigned int)) * 25];
unsigned int m_table_desc0__10CCameraPcs[3];
unsigned int m_table_desc1__10CCameraPcs[3];
unsigned int m_table_desc2__10CCameraPcs[3];
unsigned int m_table_desc3__10CCameraPcs[3];
unsigned int m_table_desc4__10CCameraPcs[3];
unsigned int m_table_desc5__10CCameraPcs[3];
unsigned int m_table_desc6__10CCameraPcs[3];
unsigned int m_table_desc7__10CCameraPcs[3];
unsigned int m_table_desc8__10CCameraPcs[3];
unsigned int m_table_desc9__10CCameraPcs[3];
unsigned int m_table_desc10__10CCameraPcs[3];
unsigned int m_table_desc11__10CCameraPcs[3];
unsigned int m_table_desc12__10CCameraPcs[3];
unsigned int m_table_desc13__10CCameraPcs[3];
unsigned int m_table_desc14__10CCameraPcs[3];
unsigned int m_table_desc15__10CCameraPcs[3];
unsigned int m_table_desc16__10CCameraPcs[3];
unsigned int m_table_desc17__10CCameraPcs[3];
unsigned int m_table_desc18__10CCameraPcs[3];
unsigned int m_table_desc19__10CCameraPcs[3];
unsigned int m_table_desc20__10CCameraPcs[3];
unsigned int m_table_desc21__10CCameraPcs[3];
unsigned int m_table_desc22__10CCameraPcs[3];
unsigned int m_table_desc23__10CCameraPcs[3];
unsigned int m_table_desc24__10CCameraPcs[3];
Vec g_shadow_pos;
Vec g_shadow_refpos;
extern "C" void Printf__7CSystemFPce(CSystem* system, char* format, ...);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long size, CMemory::CStage* stage, char* file, int line);
extern "C" void __dl__FPv(void*);
extern "C" CGObject* FindGObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" void SetFrustum__6CBoundFR3VecPA4_f(float* bound, Vec* point, Mtx matrix);
extern "C" int CheckFrustum0__6CBoundFR6CBound(float* lhs, float* rhs);
extern "C" void DrawMapShadow__7CMapMngFv(void*);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void setViewport__11CGraphicPcsFv(void*);
extern "C" int CheckHitCylinder__7CMapMngFP12CMapCylinderP3VecUl(void*, void*, Vec*, unsigned long);
extern "C" void CalcHitSlide__7CMapObjFP3Vecf(void*, Vec*);
extern "C" int rand(void);
extern "C" float RandF__5CMathFf(float, CMath*);

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
 * PAL Address: 0x8003A234
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCameraPcs::GetTable(unsigned long tableIndex)
{
	return (int)(PTR_s_CCameraPcs_GAME__801e915c + tableIndex * 0x57);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::create()
{
    float value5c = FLOAT_8032fa5c;
    float zero = FLOAT_8032fa34;
    float value18 = FLOAT_8032fa18;
    float valueb0 = FLOAT_8032fab0;

    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0xDC) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0xD8) = zero;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0xD4) = zero;

    float valueb4 = FLOAT_8032fab4;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0xF8) = value18;

    float value8c = FLOAT_8032fa8c;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x43C) = value5c;

    float valueb8 = FLOAT_8032fab8;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x440) = valueb0;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0xFC) = valueb4;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x100) = value8c;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x104) = valueb8;
    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x444) = 0;

    PSMTXIdentity(reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(this) + 0x34));

    valueb4 = FLOAT_8032fab8;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x42C) = FLOAT_8032fa38;
    value18 = FLOAT_8032fa34;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x430) = valueb4;
    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x434) = 1;
    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x438) = 0;
    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x494) = 0;
    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x498) = 0;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x4AC) = value18;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x4A8) = value18;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x4A4) = value18;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x4B8) = value18;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x4B4) = value18;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x4B0) = value18;
    *reinterpret_cast<s16*>(reinterpret_cast<u8*>(this) + 0x4BC) = 0;
    *reinterpret_cast<s16*>(reinterpret_cast<u8*>(this) + 0x4BE) = 0;
    *reinterpret_cast<s16*>(reinterpret_cast<u8*>(this) + 0x4C0) = 0;
    *reinterpret_cast<s16*>(reinterpret_cast<u8*>(this) + 0x4C2) = 0;
    *reinterpret_cast<s16*>(reinterpret_cast<u8*>(this) + 0x4A0) = 0;
    *reinterpret_cast<s16*>(reinterpret_cast<u8*>(this) + 0x49E) = 0;
    *reinterpret_cast<s16*>(reinterpret_cast<u8*>(this) + 0x49C) = 0;
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(this) + 0x490) = 0;
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
 * PAL Address: 0x8003A148
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::onScriptChanging(char*)
{
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x444) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003A0A0
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::onScriptChanged(char*, int fromScript)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    float zero = FLOAT_8032fa34;
    MtxPtr mathMtx = reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&Math) + 4);

    PSMTXCopy(mathMtx, reinterpret_cast<MtxPtr>(self + 0x34));
    PSMTXInverse(mathMtx, reinterpret_cast<MtxPtr>(self + 0x64));

    *reinterpret_cast<float*>(self + 0xDC) = zero;
    *reinterpret_cast<float*>(self + 0xD8) = zero;
    *reinterpret_cast<float*>(self + 0xD4) = zero;
    *reinterpret_cast<float*>(self + 0xE0) = zero;
    *reinterpret_cast<float*>(self + 0xE4) = FLOAT_8032fa88;
    *reinterpret_cast<float*>(self + 0xE8) = FLOAT_8032fa88;

    if (fromScript != 0) {
        *reinterpret_cast<int*>(self + 0x444) = 1;
    }

    memset(self + 0x47C, 0, 0x14);
    *reinterpret_cast<float*>(self + 0x48C) = FLOAT_8032fa1c;
}

/*
 * --INFO--
 * PAL Address: 0x80039FA0
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::SetQuakeParameter(int quakeState, int keepMoving, short startTime, short endTime,
                                   float posAmpX, float posAmpY, float posAmpZ,
                                   float jitterAmpX, float jitterAmpY, float jitterAmpZ, int immediate)
{
    u8* self = reinterpret_cast<u8*>(this);

    if (immediate != 0) {
        *reinterpret_cast<s32*>(self + 0x494) = quakeState;
        if (quakeState != 0) {
            self[0x490] = 2;
            *reinterpret_cast<float*>(self + 0x4A4) = posAmpX;
            *reinterpret_cast<float*>(self + 0x4A8) = posAmpY;
            *reinterpret_cast<float*>(self + 0x4AC) = posAmpZ;
            *reinterpret_cast<float*>(self + 0x4B0) = jitterAmpX;
            *reinterpret_cast<float*>(self + 0x4B4) = jitterAmpY;
            *reinterpret_cast<float*>(self + 0x4B8) = jitterAmpZ;
            return;
        }

        self[0x490] = 0;
        *reinterpret_cast<float*>(self + 0x4AC) = FLOAT_8032fa34;
        *reinterpret_cast<float*>(self + 0x4A8) = FLOAT_8032fa34;
        *reinterpret_cast<float*>(self + 0x4A4) = FLOAT_8032fa34;
        *reinterpret_cast<float*>(self + 0x4B8) = FLOAT_8032fa34;
        *reinterpret_cast<float*>(self + 0x4B4) = FLOAT_8032fa34;
        *reinterpret_cast<float*>(self + 0x4B0) = FLOAT_8032fa34;
        return;
    }

    if ((*reinterpret_cast<s32*>(self + 0x494) == 0) && (quakeState != 0)) {
        *reinterpret_cast<s32*>(self + 0x494) = 1;
        self[0x490] = 1;
        *reinterpret_cast<s32*>(self + 0x498) = keepMoving;
        *reinterpret_cast<s16*>(self + 0x4BC) = startTime;
        *reinterpret_cast<s16*>(self + 0x4BE) = startTime;
        *reinterpret_cast<s16*>(self + 0x4C0) = endTime;
        *reinterpret_cast<s16*>(self + 0x4C2) = endTime;
        *reinterpret_cast<float*>(self + 0x4A4) = posAmpX;
        *reinterpret_cast<float*>(self + 0x4A8) = posAmpY;
        *reinterpret_cast<float*>(self + 0x4AC) = posAmpZ;
        *reinterpret_cast<float*>(self + 0x4B0) = jitterAmpX;
        *reinterpret_cast<float*>(self + 0x4B4) = jitterAmpY;
        *reinterpret_cast<float*>(self + 0x4B8) = jitterAmpZ;
        return;
    }

    if ((*reinterpret_cast<s32*>(self + 0x494) == 1) && (quakeState == 0)) {
        *reinterpret_cast<s32*>(self + 0x494) = 0;
        self[0x490] = 1;
        *reinterpret_cast<s32*>(self + 0x498) = keepMoving;
        *reinterpret_cast<s16*>(self + 0x4BC) = 0;
        *reinterpret_cast<s16*>(self + 0x4BE) = 0;
        *reinterpret_cast<s16*>(self + 0x4C0) = endTime;
        *reinterpret_cast<s16*>(self + 0x4C2) = endTime;
        *reinterpret_cast<float*>(self + 0x4A4) = posAmpX;
        *reinterpret_cast<float*>(self + 0x4A8) = posAmpY;
        *reinterpret_cast<float*>(self + 0x4AC) = posAmpZ;
        *reinterpret_cast<float*>(self + 0x4B0) = jitterAmpX;
        *reinterpret_cast<float*>(self + 0x4B4) = jitterAmpY;
        *reinterpret_cast<float*>(self + 0x4B8) = jitterAmpZ;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80039b7c
 * PAL Size: 1060b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::CalcQuake()
{
    u8* self = reinterpret_cast<u8*>(this);
    Vec offset;
    Vec jitter;
    float zero = FLOAT_8032fa34;

    if ((System.m_scenegraphStepMode == 2) || ((self[0x490] == 2) && (*reinterpret_cast<s32*>(self + 0x494) == 0))) {
        return;
    }

    s32 randomValue = rand();
    s16 randomSign = static_cast<s16>(randomValue >> 0x1F);
    *reinterpret_cast<u16*>(self + 0x49C) = static_cast<u16>((randomValue & 1) ^ -randomSign) + randomSign;

    *reinterpret_cast<s16*>(self + 0x49E) = 1 - *reinterpret_cast<s16*>(self + 0x49E);

    randomValue = rand();
    randomSign = static_cast<s16>(randomValue >> 0x1F);
    *reinterpret_cast<u16*>(self + 0x4A0) = static_cast<u16>((randomValue & 1) ^ -randomSign) + randomSign;

    if (*reinterpret_cast<s16*>(self + 0x49C) == 0) {
        offset.x = -*reinterpret_cast<float*>(self + 0x4A4);
    } else {
        offset.x = *reinterpret_cast<float*>(self + 0x4A4);
    }

    if (*reinterpret_cast<s16*>(self + 0x49E) == 0) {
        offset.y = -*reinterpret_cast<float*>(self + 0x4A8);
    } else {
        offset.y = *reinterpret_cast<float*>(self + 0x4A8);
    }

    if (*reinterpret_cast<s16*>(self + 0x4A0) == 0) {
        offset.z = -*reinterpret_cast<float*>(self + 0x4AC);
    } else {
        offset.z = *reinterpret_cast<float*>(self + 0x4AC);
    }

    jitter.x = FLOAT_8032fa34;
    jitter.y = FLOAT_8032fa34;
    jitter.z = FLOAT_8032fa34;

    u32 randX = static_cast<u32>(rand());
    u16 signX = static_cast<u16>(randX >> 0x1F);
    u32 randY = static_cast<u32>(rand());
    u16 signY = static_cast<u16>(randY >> 0x1F);
    u32 randZ = static_cast<u32>(rand());
    u16 signZ = static_cast<u16>(randZ >> 0x1F);

    if (((randX & 1) ^ signX) == signX) {
        jitter.x = RandF__5CMathFf(*reinterpret_cast<float*>(self + 0x4B0), &Math);
    } else {
        jitter.x = -RandF__5CMathFf(*reinterpret_cast<float*>(self + 0x4B0), &Math);
    }

    if (((randY & 1) ^ signY) == signY) {
        jitter.y = RandF__5CMathFf(*reinterpret_cast<float*>(self + 0x4B4), &Math);
    } else {
        jitter.y = -RandF__5CMathFf(*reinterpret_cast<float*>(self + 0x4B4), &Math);
    }

    if (((randZ & 1) ^ signZ) == signZ) {
        jitter.z = RandF__5CMathFf(*reinterpret_cast<float*>(self + 0x4B8), &Math);
    } else {
        jitter.z = -RandF__5CMathFf(*reinterpret_cast<float*>(self + 0x4B8), &Math);
    }

    if (self[0x490] == 2) {
        PSVECAdd(&offset, &jitter, &offset);
        PSVECAdd(&offset, reinterpret_cast<Vec*>(self + 0xE0), reinterpret_cast<Vec*>(self + 0xE0));
        offset.z = FLOAT_8032fa34;
        PSVECAdd(&offset, reinterpret_cast<Vec*>(self + 0xD4), reinterpret_cast<Vec*>(self + 0xD4));
        return;
    }

    if (self[0x490] != 1) {
        return;
    }

    if (*reinterpret_cast<s16*>(self + 0x4BC) < 1) {
        if (*reinterpret_cast<s32*>(self + 0x494) == 0) {
            if (*reinterpret_cast<s16*>(self + 0x4C0) < 1) {
                *reinterpret_cast<s32*>(self + 0x494) = 0;
                *reinterpret_cast<s16*>(self + 0x4BC) = 0;
                *reinterpret_cast<s16*>(self + 0x4BE) = 0;
                *reinterpret_cast<s16*>(self + 0x4C0) = 0;
                *reinterpret_cast<s16*>(self + 0x4C2) = 0;
                *reinterpret_cast<float*>(self + 0x4AC) = zero;
                *reinterpret_cast<float*>(self + 0x4A8) = zero;
                *reinterpret_cast<float*>(self + 0x4A4) = zero;
                *reinterpret_cast<float*>(self + 0x4B8) = zero;
                *reinterpret_cast<float*>(self + 0x4B4) = zero;
                *reinterpret_cast<float*>(self + 0x4B0) = zero;
            } else {
                float ratio = static_cast<float>(*reinterpret_cast<s16*>(self + 0x4C0)) /
                              static_cast<float>(*reinterpret_cast<s16*>(self + 0x4C2));
                PSVECScale(&offset, &offset, ratio);
                PSVECSubtract(&offset, &jitter, &offset);
                PSVECAdd(&offset, reinterpret_cast<Vec*>(self + 0xE0), reinterpret_cast<Vec*>(self + 0xE0));
                PSVECAdd(&offset, reinterpret_cast<Vec*>(self + 0xD4), reinterpret_cast<Vec*>(self + 0xD4));
                *reinterpret_cast<s16*>(self + 0x4C0) = *reinterpret_cast<s16*>(self + 0x4C0) - 1;
            }
        } else {
            PSVECAdd(&offset, &jitter, &offset);
            PSVECAdd(&offset, reinterpret_cast<Vec*>(self + 0xE0), reinterpret_cast<Vec*>(self + 0xE0));
            PSVECAdd(&offset, reinterpret_cast<Vec*>(self + 0xD4), reinterpret_cast<Vec*>(self + 0xD4));
        }
    } else {
        float ratio = static_cast<float>(*reinterpret_cast<s16*>(self + 0x4BC)) /
                      static_cast<float>(*reinterpret_cast<s16*>(self + 0x4BE));
        PSVECScale(&offset, &offset, ratio);
        PSVECAdd(&offset, &jitter, &offset);
        PSVECAdd(&offset, reinterpret_cast<Vec*>(self + 0xE0), reinterpret_cast<Vec*>(self + 0xE0));
        PSVECAdd(&offset, reinterpret_cast<Vec*>(self + 0xD4), reinterpret_cast<Vec*>(self + 0xD4));
        *reinterpret_cast<s16*>(self + 0x4BC) = *reinterpret_cast<s16*>(self + 0x4BC) - 1;

        if ((*reinterpret_cast<s16*>(self + 0x4BC) == 0) && (*reinterpret_cast<s32*>(self + 0x498) == 0)) {
            *reinterpret_cast<s32*>(self + 0x494) = 0;
        }
    }
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
    unsigned char* pad = reinterpret_cast<unsigned char*>(&Pad);
    Mtx worldMapMtx;
    Mtx tempMtx;
    Mtx invMtx;
    Mtx zRotMtx;
    Vec up;

    bool useDebugPad = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
    unsigned short buttons = 0;
    if (!useDebugPad) {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        buttons = *reinterpret_cast<unsigned short*>(pad + 0x54);
    }

    if ((buttons & 0x20) != 0) {
        *reinterpret_cast<unsigned int*>(self + 0x444) =
            (static_cast<unsigned int>(__cntlzw(*reinterpret_cast<unsigned int*>(self + 0x444))) >> 5) & 0xFF;
    }

    if (*reinterpret_cast<int*>(self + 0x444) == 0) {
        float stickH = FLOAT_8032fa34;
        float stickV = FLOAT_8032fa34;
        float triggerL = FLOAT_8032fa34;
        float triggerR = FLOAT_8032fa34;
        float moveInOut = FLOAT_8032fa34;

        if (!useDebugPad) {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            stickH = *reinterpret_cast<float*>(pad + 0x44);
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            stickV = *reinterpret_cast<float*>(pad + 0x48);
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            triggerL = *reinterpret_cast<float*>(pad + 0x36);
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            triggerR = *reinterpret_cast<float*>(pad + 0x28);
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            moveInOut = *reinterpret_cast<float*>(pad + 0x40);
        }

        *reinterpret_cast<float*>(self + 0xF8) += FLOAT_8032fa70 * FLOAT_8032fa8c * stickH;
        *reinterpret_cast<float*>(self + 0x440) += FLOAT_8032fa70 * FLOAT_8032fabc * stickV;
        *reinterpret_cast<float*>(self + 0x43C) += FLOAT_8032fabc * triggerL;

        const double rotY = static_cast<double>(*reinterpret_cast<float*>(self + 0x440));
        const double rotX = static_cast<double>(*reinterpret_cast<float*>(self + 0xF8));
        const double camMove = static_cast<double>(FLOAT_8032fa8c * moveInOut);
        const double lateral = -static_cast<double>(FLOAT_8032fabc * triggerR - FLOAT_8032fabc * triggerL);
        const double sinX = static_cast<double>(sin(rotX));
        const double cosX = static_cast<double>(cos(rotX));
        const double sinY = static_cast<double>(sin(rotY));
        const double cosY = static_cast<double>(cos(rotY));
        const double sinXCosY = static_cast<double>(static_cast<float>(sinX * cosY));
        const double cosXCosY = static_cast<double>(static_cast<float>(cosX * cosY));

        *reinterpret_cast<float*>(self + 0xD4) =
            static_cast<float>(sinXCosY * camMove + static_cast<double>(*reinterpret_cast<float*>(self + 0xD4)));
        *reinterpret_cast<float*>(self + 0xD8) = static_cast<float>(
            static_cast<double>(*reinterpret_cast<float*>(self + 0xD8)) + (sinY * camMove + lateral));
        *reinterpret_cast<float*>(self + 0xDC) =
            -static_cast<float>(cosXCosY * camMove - static_cast<double>(*reinterpret_cast<float*>(self + 0xDC)));

        const double distance = static_cast<double>(*reinterpret_cast<float*>(self + 0x43C));
        *reinterpret_cast<float*>(self + 0xE0) =
            static_cast<float>(distance * sinXCosY + static_cast<double>(*reinterpret_cast<float*>(self + 0xD4)));
        *reinterpret_cast<float*>(self + 0xE4) =
            static_cast<float>(distance * sinY + static_cast<double>(*reinterpret_cast<float*>(self + 0xD8)));
        *reinterpret_cast<float*>(self + 0xE8) =
            -static_cast<float>(distance * cosXCosY - static_cast<double>(*reinterpret_cast<float*>(self + 0xDC)));
    } else {
        *reinterpret_cast<float*>(self + 0xF8) = static_cast<float>(atan2(
            static_cast<double>(*reinterpret_cast<float*>(self + 0xE0) - *reinterpret_cast<float*>(self + 0xD4)),
            static_cast<double>(*reinterpret_cast<float*>(self + 0xDC) - *reinterpret_cast<float*>(self + 0xE8))));
    }

    CalcQuake();

    float fov = *reinterpret_cast<float*>(self + 0xFC);
    if (fov < FLOAT_8032fac8 && System.m_execParam != 0) {
        Printf__7CSystemFPce(&System, DAT_801d7928);
        fov = FLOAT_8032fab4;
    }
    C_MTXPerspective(reinterpret_cast<Mtx44Ptr>(self + 0x94), fov, FLOAT_8032fa3c,
                     *reinterpret_cast<float*>(self + 0x100),
                     *reinterpret_cast<float*>(self + 0x104));
    GXSetProjection(reinterpret_cast<Mtx44Ptr>(self + 0x94), GX_PERSPECTIVE);

    up.x = FLOAT_8032fa34;
    up.y = FLOAT_8032fa1c;
    up.z = FLOAT_8032fa34;
    PSVECDistance(reinterpret_cast<Vec*>(self + 0xE0), reinterpret_cast<Vec*>(self + 0xD4));
    C_MTXLookAt(reinterpret_cast<MtxPtr>(self + 4), reinterpret_cast<Vec*>(self + 0xE0), &up,
                reinterpret_cast<Vec*>(self + 0xD4));

    if (Game.m_currentMapId == 0x21) {
        PSMTXCopy(reinterpret_cast<MtxPtr>(self + 0x34), worldMapMtx);
        if (*reinterpret_cast<short*>(self + 0x47E) != 0 && *reinterpret_cast<short*>(self + 0x480) != 0) {
            const double t = static_cast<double>(FLOAT_8032fa18 * (
                FLOAT_8032fa1c - (static_cast<float>(static_cast<double>((0x4330000000000000ULL |
                static_cast<unsigned short>(*reinterpret_cast<short*>(self + 0x480)))) - DOUBLE_8032fa28) /
                static_cast<float>(static_cast<double>((0x4330000000000000ULL |
                static_cast<unsigned short>(*reinterpret_cast<short*>(self + 0x47E)))) - DOUBLE_8032fa28))));
            const double f = static_cast<double>(FLOAT_8032fa20 * (FLOAT_8032fa1c + static_cast<float>(cos(t))));

            PSMTXRotRad(tempMtx, 'x', static_cast<float>(static_cast<double>(*reinterpret_cast<float*>(self + 0x484)) * f));
            PSMTXConcat(tempMtx, worldMapMtx, worldMapMtx);
            PSMTXRotRad(tempMtx, 'y', static_cast<float>(static_cast<double>(*reinterpret_cast<float*>(self + 0x488)) * f));
            PSMTXConcat(tempMtx, worldMapMtx, worldMapMtx);

            const float scale = -static_cast<float>(
                static_cast<double>(*reinterpret_cast<float*>(self + 0x48C)) * (static_cast<double>(FLOAT_8032fa1c) - f) -
                static_cast<double>(FLOAT_8032fa1c + *reinterpret_cast<float*>(self + 0x48C)));
            PSMTXScale(tempMtx, scale, scale, scale);
            PSMTXConcat(tempMtx, worldMapMtx, worldMapMtx);

            if (static_cast<int>(static_cast<unsigned int>(self[0x47C]) << 0x18) >= 0) {
                *reinterpret_cast<short*>(self + 0x480) -= 1;
            }
        }
        PSMTXConcat(reinterpret_cast<MtxPtr>(self + 4), worldMapMtx, reinterpret_cast<MtxPtr>(self + 4));
    }

    PSMTXRotRad(zRotMtx, 'z', *reinterpret_cast<float*>(self + 0x108));
    PSMTXConcat(zRotMtx, reinterpret_cast<MtxPtr>(self + 4), reinterpret_cast<MtxPtr>(self + 4));
    PSMTXInverse(reinterpret_cast<MtxPtr>(self + 4), invMtx);

    *reinterpret_cast<float*>(self + 0xEC) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF4) = FLOAT_8032fa38;
    PSMTXMultVecSR(invMtx, reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xEC));
    *reinterpret_cast<int*>(self + 0x438) = 0;
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
 * PAL Address: 0x80038FB4
 * PAL Size: 1180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::draw()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    Mtx shadowMtx;
    Mtx cameraMtx;
    _GXColor drawColor;
    unsigned int redColor;
    unsigned int magentaColor;

    if ((*reinterpret_cast<int*>(self + 0x444) == 0) || ((*reinterpret_cast<unsigned int*>(CFlat + 0x129c) & 0x1000000) != 0)) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTevStages(1);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        __ct__6CColorFUcUcUcUc(&drawColor, 0xFF, 0xFF, 0xFF, 0xFF);
        Graphic.DrawSphere(reinterpret_cast<MtxPtr>(self + 4), reinterpret_cast<Vec*>(self + 0xD4), FLOAT_8032fabc,
                           &drawColor);
    }

    if (DAT_8032ecd8 != 0) {
        PSMTXCopy(reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&CameraPcs) + 4), cameraMtx);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTevStages(1);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        PSMTXScale(shadowMtx, FLOAT_8032fa4c, FLOAT_8032fa4c, FLOAT_8032fa4c);
        shadowMtx[0][3] = g_shadow_pos.x;
        shadowMtx[1][3] = g_shadow_pos.y;
        shadowMtx[2][3] = g_shadow_pos.z;
        PSMTXConcat(cameraMtx, shadowMtx, shadowMtx);
        GXLoadPosMtxImm(shadowMtx, 0);
        redColor = 0xFF0000FF;
        GXSetChanMatColor(GX_COLOR0A0, *reinterpret_cast<_GXColor*>(&redColor));
        Graphic.DrawSphere();

        PSMTXCopy(reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&CameraPcs) + 4), cameraMtx);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTevStages(1);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        PSMTXScale(shadowMtx, FLOAT_8032fa4c, FLOAT_8032fa4c, FLOAT_8032fa4c);
        shadowMtx[0][3] = g_shadow_refpos.x;
        shadowMtx[1][3] = g_shadow_refpos.y;
        shadowMtx[2][3] = g_shadow_refpos.z;
        PSMTXConcat(cameraMtx, shadowMtx, shadowMtx);
        GXLoadPosMtxImm(shadowMtx, 0);
        magentaColor = 0x00FF00FF;
        GXSetChanMatColor(GX_COLOR0A0, *reinterpret_cast<_GXColor*>(&magentaColor));
        Graphic.DrawSphere();
    }
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
void CCameraPcs::SetViewerSRT(const SRT* srt)
{
    u32* dst = reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x448);
    const u32* src = reinterpret_cast<const u32*>(srt);

    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    dst[8] = src[8];
    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x46C) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::createChara()
{
    u8* self;
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;

    self = reinterpret_cast<u8*>(this);
    fVar2 = FLOAT_8032fa34;
    *reinterpret_cast<s32*>(self + 0x46C) = 0;
    fVar1 = FLOAT_8032fa1c;
    *reinterpret_cast<float*>(self + 0x450) = fVar2;
    fVar6 = FLOAT_8032fac0;
    *reinterpret_cast<float*>(self + 0x44C) = fVar2;
    fVar7 = FLOAT_8032fac4;
    *reinterpret_cast<float*>(self + 0x448) = fVar2;
    fVar4 = FLOAT_8032fab4;
    *reinterpret_cast<float*>(self + 0x45C) = fVar2;
    fVar3 = FLOAT_8032fa8c;
    *reinterpret_cast<float*>(self + 0x458) = fVar2;
    fVar5 = FLOAT_8032fab8;
    *reinterpret_cast<float*>(self + 0x454) = fVar2;
    *reinterpret_cast<float*>(self + 0x468) = fVar1;
    *reinterpret_cast<float*>(self + 0x464) = fVar1;
    *reinterpret_cast<float*>(self + 0x460) = fVar1;
    *reinterpret_cast<float*>(self + 0x44C) = fVar6;
    *reinterpret_cast<float*>(self + 0x45C) = fVar7;
    *reinterpret_cast<float*>(self + 0xFC) = fVar4;
    *reinterpret_cast<float*>(self + 0x100) = fVar3;
    *reinterpret_cast<float*>(self + 0x104) = fVar5;
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
 * PAL Address: 0x80038b68
 * PAL Size: 916b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::calcChara()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned short padButtons;
    Mtx mtxA;
    Mtx mtxB;
    Mtx mtxInv;
    float stick;
    Vec eyeDir;
    Vec scaledDir;
    Vec targetPos;

    C_MTXPerspective(reinterpret_cast<Mtx44Ptr>(self + 0x94), *reinterpret_cast<float*>(self + 0xFC), FLOAT_8032fa3c,
                     *reinterpret_cast<float*>(self + 0x100), *reinterpret_cast<float*>(self + 0x104));
    GXSetProjection(reinterpret_cast<Mtx44Ptr>(self + 0x94), GX_PERSPECTIVE);

    if (*reinterpret_cast<int*>(self + 0x46C) == 0) {
        if (Pad._452_4_ == 0) {
            padButtons = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 4 +
                                                            ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
        } else {
            padButtons = 0;
        }

        if ((padButtons & 4) != 0) {
            *reinterpret_cast<float*>(self + 0x44C) += FLOAT_8032fa20;
        }
        if ((padButtons & 8) != 0) {
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
            -((FLOAT_8032fabc * stick) - *reinterpret_cast<float*>(self + 0x45C));

        stick = FLOAT_8032fa34;
        if (Pad._452_4_ == 0) {
            stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20 +
                                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
        }
        *reinterpret_cast<float*>(self + 0x45C) =
            FLOAT_8032fabc * stick + *reinterpret_cast<float*>(self + 0x45C);
    } else {
        *reinterpret_cast<int*>(self + 0x46C) = 0;
    }

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

    *reinterpret_cast<float*>(self + 0xD4) = *reinterpret_cast<float*>(self + 0x448);
    *reinterpret_cast<float*>(self + 0xD8) = *reinterpret_cast<float*>(self + 0x44C);
    *reinterpret_cast<float*>(self + 0xDC) = *reinterpret_cast<float*>(self + 0x450);

    eyeDir = *reinterpret_cast<Vec*>(self + 0xEC);
    PSVECScale(&eyeDir, &scaledDir, FLOAT_8032fa88);
    PSVECAdd(reinterpret_cast<Vec*>(self + 0xD4), &scaledDir, &targetPos);

    *reinterpret_cast<float*>(self + 0xE0) = targetPos.x;
    *reinterpret_cast<float*>(self + 0xE4) = targetPos.y;
    *reinterpret_cast<float*>(self + 0xE8) = targetPos.z;
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

    fVar1 = FLOAT_8032fa34;
    fVar2 = FLOAT_8032fa5c;
    *reinterpret_cast<float*>(self + 0x478) = fVar1;
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
 * PAL Address: 0x800385c8
 * PAL Size: 1360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::calcMap()
{
    u8* self = reinterpret_cast<u8*>(this);
    bool useDebugPad = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
    u16 buttons;
    float stickH;
    float stickV;
    float triggerL;
    Mtx rotXMtx;
    Mtx rotYMtx;
    Mtx rotMtx;
    Mtx invViewMtx;
    Vec dir;
    Vec moveDelta;
    Vec sideVec;
    Vec upVec;
    int i;

    struct HitCylinder {
        Vec center;
        Vec delta;
        float radiusXZ;
        float radiusY;
        float height;
        float unk;
    };
    HitCylinder hitCylinder;

    if (useDebugPad) {
        buttons = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        buttons = *reinterpret_cast<u16*>(reinterpret_cast<u8*>(&Pad) + 0x4);
    }

    stickH = FLOAT_8032fa34;
    if (!useDebugPad) {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        stickH = *reinterpret_cast<float*>(reinterpret_cast<u8*>(&Pad) + 0x44);
    }
    stickH = FLOAT_8032fa70 * (stickH / FLOAT_8032fa40);

    stickV = FLOAT_8032fa34;
    if (!useDebugPad) {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        stickV = *reinterpret_cast<float*>(reinterpret_cast<u8*>(&Pad) + 0x48);
    }
    stickV = FLOAT_8032fa70 * (stickV / FLOAT_8032fa40);

    triggerL = FLOAT_8032fa34;
    if (!useDebugPad) {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        triggerL = *reinterpret_cast<float*>(reinterpret_cast<u8*>(&Pad) + 0x36);
    }

    *reinterpret_cast<float*>(self + 0xFC) += triggerL;
    *reinterpret_cast<float*>(self + 0x470) -= stickV;
    *reinterpret_cast<float*>(self + 0x474) -= stickH;

    PSMTXRotRad(rotXMtx, 'x', *reinterpret_cast<float*>(self + 0x470));
    PSMTXRotRad(rotYMtx, 'y', *reinterpret_cast<float*>(self + 0x474));
    PSMTXConcat(rotYMtx, rotXMtx, rotMtx);

    *reinterpret_cast<float*>(self + 0xEC) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF4) = FLOAT_8032fa1c;
    PSMTXMultVecSR(rotMtx, reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xEC));

    moveDelta.x = FLOAT_8032fa34;
    moveDelta.y = FLOAT_8032fa34;
    moveDelta.z = FLOAT_8032fa34;

    if ((buttons & 0x100) != 0) {
        PSVECScale(&moveDelta, reinterpret_cast<Vec*>(self + 0xEC), FLOAT_8032fa74);
    }

    moveDelta.y = FLOAT_8032fa34;
    if ((buttons & 0x800) != 0) {
        PSVECScale(&moveDelta, reinterpret_cast<Vec*>(self + 0xEC), FLOAT_8032faac);
        moveDelta.y = FLOAT_8032fa34;
    }

    if ((buttons & 0x8) != 0) {
        moveDelta.y += FLOAT_8032fa74;
    } else if ((buttons & 0x4) != 0) {
        moveDelta.y -= FLOAT_8032fa74;
    }

    if ((buttons & 0x1) != 0) {
        sideVec.x = FLOAT_8032fa74;
        sideVec.y = FLOAT_8032fa34;
        sideVec.z = FLOAT_8032fa34;
        PSMTXMultVecSR(rotMtx, &sideVec, &sideVec);
        sideVec.y = FLOAT_8032fa34;
        PSVECAdd(&moveDelta, &moveDelta, &sideVec);
    } else if ((buttons & 0x2) != 0) {
        sideVec.x = FLOAT_8032faac;
        sideVec.y = FLOAT_8032fa34;
        sideVec.z = FLOAT_8032fa34;
        PSMTXMultVecSR(rotMtx, &sideVec, &sideVec);
        sideVec.y = FLOAT_8032fa34;
        PSVECAdd(&moveDelta, &moveDelta, &sideVec);
    }

    if ((moveDelta.x != FLOAT_8032fa34) || (moveDelta.y != FLOAT_8032fa34) || (moveDelta.z != FLOAT_8032fa34)) {
        for (i = 0; i < 4; i++) {
            hitCylinder.radiusXZ = FLOAT_8032fa78;
            hitCylinder.radiusY = FLOAT_8032fa78;
            hitCylinder.height = FLOAT_8032fa78;
            hitCylinder.unk = FLOAT_8032fa8c;
            hitCylinder.center = *reinterpret_cast<Vec*>(self + 0xE0);
            hitCylinder.delta = moveDelta;
            if (CheckHitCylinder__7CMapMngFP12CMapCylinderP3VecUl(
                    &MapMng, &hitCylinder, &moveDelta, 0xFFFFFFFF) == 0) {
                *reinterpret_cast<float*>(self + 0xE0) += moveDelta.x;
                *reinterpret_cast<float*>(self + 0xE4) += moveDelta.y;
                *reinterpret_cast<float*>(self + 0xE8) += moveDelta.z;
                break;
            }
            CalcHitSlide__7CMapObjFP3Vecf(
                *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MapMng) + 0x22A88), &moveDelta);
        }
    }

    C_MTXPerspective(reinterpret_cast<Mtx44Ptr>(self + 0x94), *reinterpret_cast<float*>(self + 0xFC), FLOAT_8032fa3c,
                     *reinterpret_cast<float*>(self + 0x100),
                     *reinterpret_cast<float*>(self + 0x104));
    GXSetProjection(reinterpret_cast<Mtx44Ptr>(self + 0x94), GX_PERSPECTIVE);

    PSVECAdd(reinterpret_cast<Vec*>(self + 0xD4), reinterpret_cast<Vec*>(self + 0xE0), reinterpret_cast<Vec*>(self + 0xEC));

    upVec.x = FLOAT_8032fa34;
    upVec.y = FLOAT_8032fa1c;
    upVec.z = FLOAT_8032fa34;
    PSMTXMultVecSR(rotMtx, &upVec, &upVec);
    C_MTXLookAt(reinterpret_cast<MtxPtr>(self + 0x4), reinterpret_cast<Vec*>(self + 0xE0), &upVec,
                reinterpret_cast<Vec*>(self + 0xD4));
    PSMTXInverse(reinterpret_cast<MtxPtr>(self + 0x4), invViewMtx);

    dir.x = FLOAT_8032fa34;
    dir.y = FLOAT_8032fa34;
    dir.z = FLOAT_8032fa38;
    *reinterpret_cast<Vec*>(self + 0xEC) = dir;
    PSMTXMultVecSR(invViewMtx, reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xEC));
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
    CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&MapMng));

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
 * PAL Address: 0x80037554
 * PAL Size: 2812b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::drawShadowBegin()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    Mtx rotX;
    Mtx rotY;
    Mtx rotXY;
    Mtx tempMtx;
    Vec up;
    Vec delta;
    double depth;

    if (self[0x404] == 0) {
        return;
    }

    GXInvalidateTexAll();

    memcpy(self + 0x10C, self + 4, 0x108);
    memcpy(self + 0x214, self + 4, 0x108);

    if (Game.m_currentSceneId == 3) {
        float stickX = FLOAT_8032fa34;
        float stickY = FLOAT_8032fa34;

        if (Pad._452_4_ == 0) {
            stickX = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x24 +
                                               (((1 - Pad._448_4_ | Pad._448_4_ - 1) >> 0x1f) * -0x54));
            stickY = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x28 +
                                               (((1 - Pad._448_4_ | Pad._448_4_ - 1) >> 0x1f) * -0x54));
        }

        *reinterpret_cast<float*>(self + 0x368) += FLOAT_8032fa70 * FLOAT_8032fa74 * stickX;
        *reinterpret_cast<float*>(self + 0x364) += FLOAT_8032fa70 * FLOAT_8032fa4c * stickY;
    }

    PSMTXRotRad(rotX, 'x', -*reinterpret_cast<float*>(self + 0x364));
    PSMTXRotRad(rotY, 'y', *reinterpret_cast<float*>(self + 0x368));
    PSMTXConcat(rotY, rotX, rotXY);

    if (Game.m_currentSceneId == 4) {
        *reinterpret_cast<float*>(self + 0x414) = FLOAT_8032fa78;
        *reinterpret_cast<float*>(self + 0x418) = FLOAT_8032fa78;
        *reinterpret_cast<float*>(self + 0x41C) = FLOAT_8032fa78;
        *reinterpret_cast<float*>(self + 0x420) = FLOAT_8032fa7c;
        *reinterpret_cast<float*>(self + 0x424) = FLOAT_8032fa7c;
        *reinterpret_cast<float*>(self + 0x428) = FLOAT_8032fa7c;

        if (*reinterpret_cast<int*>(self + 0x434) == 1 && GetShadowRect(*reinterpret_cast<CBound*>(self + 0x414)) != 0) {
            *reinterpret_cast<float*>(self + 0xD4) = (*reinterpret_cast<float*>(self + 0x414) +
                                                      *reinterpret_cast<float*>(self + 0x420)) * FLOAT_8032fa20;
            *reinterpret_cast<float*>(self + 0xD8) = *reinterpret_cast<float*>(self + 0x40C);
            *reinterpret_cast<float*>(self + 0xDC) = (*reinterpret_cast<float*>(self + 0x41C) +
                                                      *reinterpret_cast<float*>(self + 0x428)) * FLOAT_8032fa20;

            double w = static_cast<double>(*reinterpret_cast<float*>(self + 0x420) - *reinterpret_cast<float*>(self + 0x414));
            double h = static_cast<double>(*reinterpret_cast<float*>(self + 0x428) - *reinterpret_cast<float*>(self + 0x41C));
            if (w < h) {
                w = h;
            }
            *reinterpret_cast<float*>(self + 0x36C) = static_cast<float>(static_cast<double>(FLOAT_8032fa20) * w);
            depth = w;
        } else if (*reinterpret_cast<int*>(self + 0x434) == 2) {
            *reinterpret_cast<float*>(self + 0xD4) = *reinterpret_cast<float*>(self + 0x408);
            *reinterpret_cast<float*>(self + 0xD8) = *reinterpret_cast<float*>(self + 0x40C);
            *reinterpret_cast<float*>(self + 0xDC) = *reinterpret_cast<float*>(self + 0x410);
            PSVECSubtract(reinterpret_cast<Vec*>(self + 0xD4), reinterpret_cast<Vec*>(self + 0xE0), &delta);
            depth = static_cast<double>(*reinterpret_cast<float*>(self + 0x430));
            *reinterpret_cast<float*>(self + 0x36C) = FLOAT_8032fa80 * *reinterpret_cast<float*>(self + 0x370);
        } else {
            *reinterpret_cast<float*>(self + 0xD4) = *reinterpret_cast<float*>(self + 0x408);
            *reinterpret_cast<float*>(self + 0xD8) = *reinterpret_cast<float*>(self + 0x40C);
            *reinterpret_cast<float*>(self + 0xDC) = *reinterpret_cast<float*>(self + 0x410);
            PSVECSubtract(reinterpret_cast<Vec*>(self + 0xD4), reinterpret_cast<Vec*>(self + 0xE0), &delta);
            depth = static_cast<double>(PSVECMag(&delta));
            *reinterpret_cast<float*>(self + 0x36C) = static_cast<float>(depth * static_cast<double>(*reinterpret_cast<float*>(self + 0x370)));
        }

        double currentDepth = static_cast<double>(*reinterpret_cast<float*>(self + 0x42C));
        if (static_cast<double>(FLOAT_8032fa34) <= currentDepth) {
            *reinterpret_cast<float*>(self + 0x42C) = static_cast<float>(currentDepth +
                                                   static_cast<double>((static_cast<float>(depth - currentDepth)) * FLOAT_8032fa84));
        } else {
            *reinterpret_cast<float*>(self + 0x42C) = static_cast<float>(depth);
        }
    } else {
        *reinterpret_cast<float*>(self + 0x36C) = FLOAT_8032fa88;
        *reinterpret_cast<float*>(self + 0x42C) = FLOAT_8032fa8c;
    }

    up.x = FLOAT_8032fa34;
    up.y = FLOAT_8032fa1c;
    up.z = FLOAT_8032fa34;
    PSMTXMultVecSR(rotXY, &up, &up);

    *reinterpret_cast<float*>(self + 0x2F0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x2F4) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x2F8) = *reinterpret_cast<float*>(self + 0x42C);
    PSMTXMultVecSR(rotXY, reinterpret_cast<Vec*>(self + 0x2F0), reinterpret_cast<Vec*>(self + 0x2F0));

    if (Game.m_currentMapId == 0x21) {
        PSMTXCopy(reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x64), tempMtx);
        PSMTXMultVecSR(tempMtx, reinterpret_cast<Vec*>(self + 0x2F0), reinterpret_cast<Vec*>(self + 0x2F0));
    }

    PSVECAdd(reinterpret_cast<Vec*>(self + 0x2F0), reinterpret_cast<Vec*>(self + 0xD4), reinterpret_cast<Vec*>(self + 0x2F0));
    *reinterpret_cast<float*>(self + 0x2E4) = *reinterpret_cast<float*>(self + 0xD4);
    *reinterpret_cast<float*>(self + 0x2E8) = *reinterpret_cast<float*>(self + 0xD8);
    *reinterpret_cast<float*>(self + 0x2EC) = *reinterpret_cast<float*>(self + 0xDC);
    *reinterpret_cast<float*>(self + 0x310) = FLOAT_8032fa8c;
    *reinterpret_cast<float*>(self + 0x314) = FLOAT_8032fa4c * *reinterpret_cast<float*>(self + 0x42C);

    C_MTXLookAt(reinterpret_cast<MtxPtr>(self + 0x214), reinterpret_cast<Vec*>(self + 0x2F0), &up,
                reinterpret_cast<Vec*>(self + 0x2E4));
    C_MTXOrtho(reinterpret_cast<Mtx44Ptr>(self + 0x2A4),
               *reinterpret_cast<float*>(self + 0x36C), -*reinterpret_cast<float*>(self + 0x36C),
               -*reinterpret_cast<float*>(self + 0x36C), *reinterpret_cast<float*>(self + 0x36C),
               *reinterpret_cast<float*>(self + 0x310), *reinterpret_cast<float*>(self + 0x314));

    g_shadow_pos.x = *reinterpret_cast<float*>(self + 0x2F0);
    g_shadow_pos.y = *reinterpret_cast<float*>(self + 0x2F4);
    g_shadow_pos.z = *reinterpret_cast<float*>(self + 0x2F8);
    g_shadow_refpos.x = *reinterpret_cast<float*>(self + 0x2E4);
    g_shadow_refpos.y = *reinterpret_cast<float*>(self + 0x2E8);
    g_shadow_refpos.z = *reinterpret_cast<float*>(self + 0x2EC);

    memcpy(self + 4, self + 0x214, 0x108);
    GXSetProjection(reinterpret_cast<Mtx44Ptr>(self + 0x94), GX_ORTHOGRAPHIC);
    GXSetColorUpdate(GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetViewport(FLOAT_8032fa4c, FLOAT_8032fa4c, FLOAT_8032fa90, FLOAT_8032fa90, FLOAT_8032fa34, FLOAT_8032fa1c);
    GXSetScissor(2, 2, 0x1DC, 0x1DC);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 0, 0, 5);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 0, 7, 0xFF);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    GXSetNumTexGens(0);
    DrawMapShadow__7CMapMngFv(&MapMng);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::drawShadowEnd()
{
    u8* self = reinterpret_cast<u8*>(this);
    Mtx44 proj;
    Mtx ident;
    float z;
    int x0;
    int y0;
    int x1;
    int y1;
    int x2;

    if (self[0x404] == 0) {
        return;
    }

    C_MTXOrtho(proj, FLOAT_8032fa5c, -FLOAT_8032fa5c, FLOAT_8032fa5c, -FLOAT_8032fa5c,
               *reinterpret_cast<float*>(self + 0x310), *reinterpret_cast<float*>(self + 0x314));
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    PSMTXIdentity(ident);
    GXLoadPosMtxImm(ident, 0);

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 4, 5, 1);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 1, 0, 7, 0);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_TRUE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetNumTexGens(0);

    {
        GXColor black = {0, 0, 0, 0};
        GXSetChanMatColor(GX_COLOR0A0, black);
    }

    z = *reinterpret_cast<float*>(self + 0x310) - *reinterpret_cast<float*>(self + 0x314);
    x0 = static_cast<int>(-FLOAT_8032fa5c - FLOAT_8032fa4c);
    y0 = static_cast<int>(FLOAT_8032fa64);
    x1 = static_cast<int>(FLOAT_8032fa60);
    y1 = static_cast<int>(FLOAT_8032fa68);
    x2 = static_cast<int>(FLOAT_8032fa64);

    GXBegin(GX_QUADS, GX_VTXFMT0, 16);
    GXPosition3f32(static_cast<float>(x0), static_cast<float>(y0), z);
    GXPosition3f32(static_cast<float>(x1), static_cast<float>(y0), z);
    GXPosition3f32(static_cast<float>(x1), static_cast<float>(x0), z);
    GXPosition3f32(static_cast<float>(x0), static_cast<float>(x0), z);

    GXPosition3f32(static_cast<float>(y1), static_cast<float>(y0), z);
    GXPosition3f32(static_cast<float>(x2), static_cast<float>(y0), z);
    GXPosition3f32(static_cast<float>(x2), static_cast<float>(x0), z);
    GXPosition3f32(static_cast<float>(y1), static_cast<float>(x0), z);

    GXPosition3f32(static_cast<float>(x0), static_cast<float>(y0), z);
    GXPosition3f32(static_cast<float>(x2), static_cast<float>(y0), z);
    GXPosition3f32(static_cast<float>(x2), static_cast<float>(y1), z);
    GXPosition3f32(static_cast<float>(x0), static_cast<float>(y1), z);

    GXPosition3f32(static_cast<float>(x0), static_cast<float>(x1), z);
    GXPosition3f32(static_cast<float>(x2), static_cast<float>(x1), z);
    GXPosition3f32(static_cast<float>(x2), static_cast<float>(x0), z);
    GXPosition3f32(static_cast<float>(x0), static_cast<float>(x0), z);

    GXSetTexCopySrc(0, 0, 0x1E0, 0x1E0);
    GXSetTexCopyDst(0x1E0, 0x1E0, GX_TF_I8, GX_FALSE);
    GXCopyTex(*reinterpret_cast<void**>(self + 0x31C), GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);

    {
        float span = *reinterpret_cast<float*>(self + 0x36C);
        float depthSpan = *reinterpret_cast<float*>(self + 0x314) - *reinterpret_cast<float*>(self + 0x310);
        C_MTXLightOrtho(reinterpret_cast<MtxPtr>(self + 0x374), -span, span, -span, span,
                        FLOAT_8032fa20, FLOAT_8032fa20, FLOAT_8032fa20, FLOAT_8032fa20);
        PSMTXScale(reinterpret_cast<MtxPtr>(self + 0x3D4), FLOAT_8032fa34, FLOAT_8032fa34, FLOAT_8032fa34);
        *reinterpret_cast<float*>(self + 0x3DC) = FLOAT_8032fa38 / depthSpan;
        *reinterpret_cast<float*>(self + 0x3E0) = -(*reinterpret_cast<float*>(self + 0x310) / depthSpan);
        *reinterpret_cast<float*>(self + 0x3EC) = *reinterpret_cast<float*>(self + 0x3DC) * FLOAT_8032fa6c;
        *reinterpret_cast<float*>(self + 0x3F0) = *reinterpret_cast<float*>(self + 0x3E0) * FLOAT_8032fa6c;
        *reinterpret_cast<float*>(self + 0x400) = FLOAT_8032fa1c;
        PSMTXConcat(reinterpret_cast<MtxPtr>(self + 0x374),
                    reinterpret_cast<MtxPtr>(self + 0x214),
                    reinterpret_cast<MtxPtr>(self + 0x374));
        PSMTXConcat(reinterpret_cast<MtxPtr>(self + 0x3D4),
                    reinterpret_cast<MtxPtr>(self + 0x214),
                    reinterpret_cast<MtxPtr>(self + 0x3A4));
    }

    GXSetColorUpdate(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXPixModeSync();
    GXInitTexObj(reinterpret_cast<GXTexObj*>(self + 0x324), *reinterpret_cast<void**>(self + 0x31C),
                 0x1E0, 0x1E0, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(reinterpret_cast<GXTexObj*>(self + 0x324), GX_NEAR, GX_NEAR, FLOAT_8032fa34,
                    FLOAT_8032fa34, FLOAT_8032fa34, GX_FALSE, GX_FALSE, GX_ANISO_1);

    memcpy(self + 0x4, self + 0x10C, 0x108);
    GXSetProjection(reinterpret_cast<Mtx44Ptr>(self + 0x94), GX_PERSPECTIVE);
    setViewport__11CGraphicPcsFv(&GraphicsPcs);
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
    u8* self = reinterpret_cast<u8*>(this);
    float fVar2 = FLOAT_8032fa34;
    *reinterpret_cast<int*>(self + 0x46C) = 0;
    float fVar1 = FLOAT_8032fa1c;
    *reinterpret_cast<float*>(self + 0x450) = fVar2;
    float fVar3 = FLOAT_8032fa50;
    *reinterpret_cast<float*>(self + 0x44C) = fVar2;
    *reinterpret_cast<float*>(self + 0x448) = fVar2;
    *reinterpret_cast<float*>(self + 0x45C) = fVar2;
    *reinterpret_cast<float*>(self + 0x458) = fVar2;
    *reinterpret_cast<float*>(self + 0x454) = fVar2;
    *reinterpret_cast<float*>(self + 0x468) = fVar1;
    *reinterpret_cast<float*>(self + 0x464) = fVar1;
    *reinterpret_cast<float*>(self + 0x460) = fVar1;
    *reinterpret_cast<float*>(self + 0x44C) = fVar2;
    *reinterpret_cast<float*>(self + 0x450) = fVar3;
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
    u8* self = reinterpret_cast<u8*>(this);
    float fVar2 = FLOAT_8032fa34;
    *reinterpret_cast<int*>(self + 0x46C) = 0;
    float fVar1 = FLOAT_8032fa1c;
    *reinterpret_cast<float*>(self + 0x450) = fVar2;
    float fVar3 = FLOAT_8032fa50;
    *reinterpret_cast<float*>(self + 0x44C) = fVar2;
    *reinterpret_cast<float*>(self + 0x448) = fVar2;
    *reinterpret_cast<float*>(self + 0x45C) = fVar2;
    *reinterpret_cast<float*>(self + 0x458) = fVar2;
    *reinterpret_cast<float*>(self + 0x454) = fVar2;
    *reinterpret_cast<float*>(self + 0x468) = fVar1;
    *reinterpret_cast<float*>(self + 0x464) = fVar1;
    *reinterpret_cast<float*>(self + 0x460) = fVar1;
    *reinterpret_cast<float*>(self + 0x44C) = fVar2;
    *reinterpret_cast<float*>(self + 0x450) = fVar3;
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
