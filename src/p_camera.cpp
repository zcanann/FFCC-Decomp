#include "ffcc/p_camera.h"

#include "ffcc/cflat_runtime2.h"
#include "ffcc/color.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/map.h"
#include "ffcc/mapocttree.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/pad.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/p_graphic.h"
#include "ffcc/game.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"

#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

#include <dolphin/mtx.h>
#include <dolphin/os/OSCache.h>

CCameraPcs CameraPcs;

extern "C" const char s_CCameraPcs_GAME_801D7860[] = "CCameraPcs(GAME)";
extern "C" const char s_CCameraPcs_CHARA_801D7874[] = "CCameraPcs(CHARA)";
extern "C" const char s_CCameraPcs_MAP_801D7888[] = "CCameraPcs(MAP)";
extern "C" const char s_CCameraPcs_MATERIALEDITOR_801D7898[] = "CCameraPcs(MATERIALEDITOR)";
extern "C" const char s_CCameraPcs_FUNNYSHAPE_801D78B4[] = "CCameraPcs(FUNNYSHAPE)";
extern "C" const char s_CCameraPcs_PART_801D78CC[] = "CCameraPcs(PART)";
extern "C" const char s_CCameraPcs_SHADOW_801D78E0[] = "CCameraPcs(SHADOW)";

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
extern char s_p_camera_cpp[];
extern char sCameraInvalidFovFmt[];
extern unsigned char g_map_draw_prof;

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

unsigned int CCameraPcs::m_table_desc0[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc1[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc2[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc3[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc4[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createChara__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc5[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyChara__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc6[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcChara__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc7[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createMap__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc8[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyMap__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc9[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcMap__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc10[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createMaterialEditor__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc11[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyMaterialEditor__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc12[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcMaterialEditor__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc13[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createFunnyShape__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc14[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyFunnyShape__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc15[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcFunnyShape__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc16[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createPart__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc17[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyPart__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc18[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcPart__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc19[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createFullShadow__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc20[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyFullShadow__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc21[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadowBegin__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc22[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadowEnd__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc23[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadowChrBegin__10CCameraPcsFv)};
unsigned int CCameraPcs::m_table_desc24[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadowEndAll__10CCameraPcsFv)};
CProcessTable CCameraPcs::m_table[7] = {
    {
        const_cast<char*>(s_CCameraPcs_GAME_801D7860),
        m_table_desc0[0],
        m_table_desc0[1],
        m_table_desc0[2],
        m_table_desc1[0],
        m_table_desc1[1],
        m_table_desc1[2],
        m_table_desc2[0],
        m_table_desc2[1],
        m_table_desc2[2],
        0x18,
        0x4,
        m_table_desc3[0],
        m_table_desc3[1],
        m_table_desc3[2],
        m_table_desc4[0],
        m_table_desc4[1],
        m_table_desc4[2],
    },
    {
        const_cast<char*>(s_CCameraPcs_CHARA_801D7874),
        m_table_desc5[0],
        m_table_desc5[1],
        m_table_desc5[2],
        m_table_desc6[0],
        m_table_desc6[1],
        m_table_desc6[2],
        m_table_desc7[0],
        m_table_desc7[1],
        m_table_desc7[2],
        0x18,
        0x4,
    },
    {
        const_cast<char*>(s_CCameraPcs_MAP_801D7888),
        m_table_desc8[0],
        m_table_desc8[1],
        m_table_desc8[2],
        m_table_desc9[0],
        m_table_desc9[1],
        m_table_desc9[2],
        m_table_desc10[0],
        m_table_desc10[1],
        m_table_desc10[2],
        0x18,
        0x4,
    },
    {
        const_cast<char*>(s_CCameraPcs_MATERIALEDITOR_801D7898),
        m_table_desc11[0],
        m_table_desc11[1],
        m_table_desc11[2],
        m_table_desc12[0],
        m_table_desc12[1],
        m_table_desc12[2],
        m_table_desc13[0],
        m_table_desc13[1],
        m_table_desc13[2],
        0x18,
        0x4,
    },
    {
        const_cast<char*>(s_CCameraPcs_FUNNYSHAPE_801D78B4),
        m_table_desc14[0],
        m_table_desc14[1],
        m_table_desc14[2],
        m_table_desc15[0],
        m_table_desc15[1],
        m_table_desc15[2],
        m_table_desc16[0],
        m_table_desc16[1],
        m_table_desc16[2],
        0x18,
        0x4,
    },
    {
        const_cast<char*>(s_CCameraPcs_PART_801D78CC),
        m_table_desc17[0],
        m_table_desc17[1],
        m_table_desc17[2],
        m_table_desc18[0],
        m_table_desc18[1],
        m_table_desc18[2],
        m_table_desc19[0],
        m_table_desc19[1],
        m_table_desc19[2],
        0x18,
        0x4,
    },
    {
        const_cast<char*>(s_CCameraPcs_SHADOW_801D78E0),
        m_table_desc20[0],
        m_table_desc20[1],
        m_table_desc20[2],
        m_table_desc21[0],
        m_table_desc21[1],
        m_table_desc21[2],
        m_table_desc22[0],
        m_table_desc22[1],
        m_table_desc22[2],
        0x2E,
        0x1,
        m_table_desc23[0],
        m_table_desc23[1],
        m_table_desc23[2],
        0x32,
        0x1,
        0,
        0,
        0,
        0x39,
        0x1,
        m_table_desc24[0],
        m_table_desc24[1],
        m_table_desc24[2],
        0x43,
        0x1,
    }
};
Vec g_shadow_pos;
Vec g_shadow_refpos;
extern "C" int CheckHitCylinder__7CMapMngFP12CMapCylinderP3VecUl(void*, void*, Vec*, unsigned long);
extern "C" void CalcHitSlide__7CMapObjFP3Vecf(void*, Vec*);

extern "C" {
void pppEditGetViewPos__FP3Vec(Vec*);
void pppEditGetViewMatrix__FPA4_f(float (*)[4]);
void pppEditGetProjectionMatrix__FPA4_f(float (*)[4]);
}

namespace {

struct CameraStateCopy {
    u8 bytes[0x108];
};

STATIC_ASSERT(offsetof(CCameraPcs, m_cameraMatrix) == 0x04);
STATIC_ASSERT(offsetof(CCameraPcs, m_worldMapMatrix) == 0x34);
STATIC_ASSERT(offsetof(CCameraPcs, m_zRotate) == 0x108);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowRotX) == 0x364);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowRotY) == 0x368);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowSpan) == 0x36C);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowScale) == 0x370);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowEnabled) == 0x404);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowPosition) == 0x408);
STATIC_ASSERT(offsetof(CCameraPcs, m_shadowRectBound) == 0x414);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowDepth) == 0x42C);
STATIC_ASSERT(offsetof(CCameraPcs, m_isAbsolute) == 0x444);
STATIC_ASSERT(offsetof(CCameraPcs, m_viewer) == 0x448);
STATIC_ASSERT(sizeof(CCameraPcs::ViewerState) == 0x24);
STATIC_ASSERT(offsetof(CCameraPcs, m_viewerOverride) == 0x46C);
STATIC_ASSERT(offsetof(CCameraPcs, m_mapRotX) == 0x470);
STATIC_ASSERT(sizeof(CCameraPcs) == 0x4C4);

static inline void CopyCameraState(u8* dst, u8* src)
{
    *reinterpret_cast<CameraStateCopy*>(dst) = *reinterpret_cast<CameraStateCopy*>(src);
}

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
	return reinterpret_cast<int>(&CCameraPcs::m_table[tableIndex]);
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

    m_targetZ = FLOAT_8032fa34;
    m_targetY = zero;
    m_targetX = zero;

    float valueb4 = FLOAT_8032fab4;
    m_yaw = value18;

    float value8c = FLOAT_8032fa8c;
    m_distance = value5c;

    float valueb8 = FLOAT_8032fab8;
    m_pitch = valueb0;
    m_fov = valueb4;
    m_nearZ = value8c;
    m_farZ = valueb8;
    m_isAbsolute = 0;

    PSMTXIdentity(m_worldMapMatrix);

    valueb4 = FLOAT_8032fab8;
    m_fullScreenShadowDepth = FLOAT_8032fa38;
    value18 = FLOAT_8032fa34;
    m_fullScreenShadowCamLen = valueb4;
    m_shadowAuto = 1;
    m_fromScript = 0;
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
    m_isAbsolute = 0;
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
    MtxPtr mathMtx = reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&Math) + 4);

    PSMTXCopy(mathMtx, m_worldMapMatrix);
    PSMTXInverse(mathMtx, m_cameraWorldMtx);

    float refValue = FLOAT_8032fa88;
    float zero;
    m_targetZ = zero = FLOAT_8032fa34;
    m_targetY = zero;
    m_targetX = zero;
    m_positionX = zero;
    m_positionY = refValue;
    m_positionZ = refValue;

    if (fromScript != 0) {
        m_isAbsolute = 1;
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
        jitter.x = Math.RandF(*reinterpret_cast<float*>(self + 0x4B0));
    } else {
        jitter.x = -Math.RandF(*reinterpret_cast<float*>(self + 0x4B0));
    }

    if (((randY & 1) ^ signY) == signY) {
        jitter.y = Math.RandF(*reinterpret_cast<float*>(self + 0x4B4));
    } else {
        jitter.y = -Math.RandF(*reinterpret_cast<float*>(self + 0x4B4));
    }

    if (((randZ & 1) ^ signZ) == signZ) {
        jitter.z = Math.RandF(*reinterpret_cast<float*>(self + 0x4B8));
    } else {
        jitter.z = -Math.RandF(*reinterpret_cast<float*>(self + 0x4B8));
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
        m_isAbsolute = (static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(m_isAbsolute))) >> 5) & 0xFF;
    }

    if (m_isAbsolute == 0) {
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

        m_yaw += FLOAT_8032fa70 * FLOAT_8032fa8c * stickH;
        m_pitch += FLOAT_8032fa70 * FLOAT_8032fabc * stickV;
        m_distance += FLOAT_8032fabc * triggerL;

        const double rotY = static_cast<double>(m_pitch);
        const double rotX = static_cast<double>(m_yaw);
        const double camMove = static_cast<double>(FLOAT_8032fa8c * moveInOut);
        const double lateral = -static_cast<double>(FLOAT_8032fabc * triggerR - FLOAT_8032fabc * triggerL);
        const double sinX = static_cast<double>(sin(rotX));
        const double cosX = static_cast<double>(cos(rotX));
        const double sinY = static_cast<double>(sin(rotY));
        const double cosY = static_cast<double>(cos(rotY));
        const double sinXCosY = static_cast<double>(static_cast<float>(sinX * cosY));
        const double cosXCosY = static_cast<double>(static_cast<float>(cosX * cosY));

        m_targetX = static_cast<float>(sinXCosY * camMove + static_cast<double>(m_targetX));
        m_targetY = static_cast<float>(static_cast<double>(m_targetY) + (sinY * camMove + lateral));
        m_targetZ = -static_cast<float>(cosXCosY * camMove - static_cast<double>(m_targetZ));

        const double distance = static_cast<double>(m_distance);
        m_positionX = static_cast<float>(distance * sinXCosY + static_cast<double>(m_targetX));
        m_positionY = static_cast<float>(distance * sinY + static_cast<double>(m_targetY));
        m_positionZ = -static_cast<float>(distance * cosXCosY - static_cast<double>(m_targetZ));
    } else {
        m_yaw = static_cast<float>(atan2(static_cast<double>(m_positionX - m_targetX),
                                         static_cast<double>(m_targetZ - m_positionZ)));
    }

    CalcQuake();

    float fov = m_fov;
    if (fov < FLOAT_8032fac8 && System.m_execParam != 0) {
        System.Printf(sCameraInvalidFovFmt, fov);
        fov = FLOAT_8032fab4;
    }
    C_MTXPerspective(m_screenMatrix, fov, FLOAT_8032fa3c, m_nearZ, m_farZ);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);

    up.x = FLOAT_8032fa34;
    up.y = FLOAT_8032fa1c;
    up.z = FLOAT_8032fa34;
    PSVECDistance(reinterpret_cast<Vec*>(self + 0xE0), reinterpret_cast<Vec*>(self + 0xD4));
    C_MTXLookAt(m_cameraMatrix, reinterpret_cast<Vec*>(self + 0xE0), &up, reinterpret_cast<Vec*>(self + 0xD4));

    if (Game.m_currentMapId == 0x21) {
        PSMTXCopy(m_worldMapMatrix, worldMapMtx);
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
        PSMTXConcat(m_cameraMatrix, worldMapMtx, m_cameraMatrix);
    }

    PSMTXRotRad(zRotMtx, 'z', m_zRotate);
    PSMTXConcat(zRotMtx, m_cameraMatrix, m_cameraMatrix);
    PSMTXInverse(m_cameraMatrix, invMtx);

    *reinterpret_cast<float*>(self + 0xEC) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF4) = FLOAT_8032fa38;
    PSMTXMultVecSR(invMtx, reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xEC));
    m_fromScript = 0;
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
    float fov = m_fov;

    if (fov < FLOAT_8032fac8 && System.m_execParam != 0) {
        System.Printf(sCameraInvalidFovFmt, fov);
        fov = FLOAT_8032fab4;
    }

    C_MTXPerspective(m_screenMatrix, fov, FLOAT_8032fa3c, m_nearZ, m_farZ);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);
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
    unsigned int redColor;
    unsigned int magentaColor;

    if ((m_isAbsolute == 0) ||
        ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_Camera) != 0)) {
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        CColor drawColor(0xFF, 0xFF, 0xFF, 0xFF);
        Graphic.DrawSphere(m_cameraMatrix, reinterpret_cast<Vec*>(&m_targetX), FLOAT_8032fabc, &drawColor.color);
    }

    if (g_map_draw_prof != 0) {
        PSMTXCopy(m_cameraMatrix, cameraMtx);
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
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

        PSMTXCopy(m_cameraMatrix, cameraMtx);
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
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
    u32* dst = reinterpret_cast<u32*>(&m_viewer);
    const u32* src = reinterpret_cast<const u32*>(srt);
    u32 value1;
    u32 value0 = *src++;
    value1 = *src;
    dst[0] = value0;
    u32 value2 = src[1];
    dst[1] = value1;
    value1 = src[2];
    dst[2] = value2;
    value2 = src[3];
    dst[3] = value1;
    value1 = src[4];
    dst[4] = value2;
    u32 value3 = src[5];
    dst[5] = value1;
    value2 = src[6];
    dst[6] = value3;
    value1 = src[7];
    dst[7] = value2;
    dst[8] = value1;
    m_viewerOverride = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCameraPcs::createChara()
{
    u8* self;
    float fVar6;
    float fVar5;
    float fVar4;
    float fVar3;
    float fVar2;
    float fVar1;
    float fVar7;

    self = reinterpret_cast<u8*>(this);
    fVar2 = FLOAT_8032fa34;
    m_viewerOverride = 0;
    fVar1 = FLOAT_8032fa1c;
    m_viewer.m_position.z = fVar2;
    fVar6 = FLOAT_8032fac0;
    m_viewer.m_position.y = fVar2;
    fVar7 = FLOAT_8032fac4;
    m_viewer.m_position.x = fVar2;
    fVar4 = FLOAT_8032fab4;
    m_viewer.m_distance = fVar2;
    fVar3 = FLOAT_8032fa8c;
    m_viewer.m_rotY = fVar2;
    fVar5 = FLOAT_8032fab8;
    m_viewer.m_rotX = fVar2;
    m_viewer.m_scale.z = fVar1;
    m_viewer.m_scale.y = fVar1;
    m_viewer.m_scale.x = fVar1;
    m_viewer.m_position.y = fVar6;
    m_viewer.m_distance = fVar7;
    m_fov = fVar4;
    m_nearZ = fVar3;
    m_farZ = fVar5;
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

    C_MTXPerspective(m_screenMatrix, m_fov, FLOAT_8032fa3c, m_nearZ, m_farZ);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);

    if (m_viewerOverride == 0) {
        if (Pad._452_4_ == 0) {
            padButtons = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 4 +
                                                            ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
        } else {
            padButtons = 0;
        }

        if ((padButtons & 4) != 0) {
            m_viewer.m_position.y += FLOAT_8032fa20;
        }
        if ((padButtons & 8) != 0) {
            m_viewer.m_position.y -= FLOAT_8032fa20;
        }

        stick = FLOAT_8032fa34;
        if (Pad._452_4_ == 0) {
            stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x24 +
                                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
        }
        m_viewer.m_rotY = FLOAT_8032fa48 * stick + m_viewer.m_rotY;

        stick = FLOAT_8032fa34;
        if (Pad._452_4_ == 0) {
            stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x28 +
                                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
        }
        m_viewer.m_rotX = -((FLOAT_8032fa48 * stick) - m_viewer.m_rotX);

        stick = FLOAT_8032fa34;
        if (Pad._452_4_ == 0) {
            stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x1C +
                                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
        }
        m_viewer.m_distance = -((FLOAT_8032fabc * stick) - m_viewer.m_distance);

        stick = FLOAT_8032fa34;
        if (Pad._452_4_ == 0) {
            stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20 +
                                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
        }
        m_viewer.m_distance = FLOAT_8032fabc * stick + m_viewer.m_distance;
    } else {
        m_viewerOverride = 0;
    }

    PSMTXTrans(mtxA, m_viewer.m_position.x, m_viewer.m_position.y, m_viewer.m_position.z);
    PSMTXRotRad(mtxB, 'y', m_viewer.m_rotY);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXRotRad(mtxB, 'x', m_viewer.m_rotX);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXTrans(mtxB, FLOAT_8032fa34, FLOAT_8032fa34, -m_viewer.m_distance);
    PSMTXConcat(mtxB, mtxA, m_cameraMatrix);
    PSMTXInverse(m_cameraMatrix, mtxInv);

    *reinterpret_cast<float*>(self + 0xEC) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xF4) = FLOAT_8032fa38;
    PSMTXMultVecSR(mtxInv, reinterpret_cast<Vec*>(self + 0xEC), reinterpret_cast<Vec*>(self + 0xEC));

    m_targetX = m_viewer.m_position.x;
    m_targetY = m_viewer.m_position.y;
    m_targetZ = m_viewer.m_position.z;

    eyeDir = *reinterpret_cast<Vec*>(self + 0xEC);
    PSVECScale(&eyeDir, &scaledDir, FLOAT_8032fa88);
    PSVECAdd(reinterpret_cast<Vec*>(&m_targetX), &scaledDir, &targetPos);

    m_positionX = targetPos.x;
    m_positionY = targetPos.y;
    m_positionZ = targetPos.z;
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
    float fVar6;
    float fVar5;
    float fVar4;
    float fVar3;
    float fVar2;
    float fVar1;

    fVar1 = FLOAT_8032fa34;
    fVar2 = FLOAT_8032fa5c;
    m_mapRotZ = fVar1;
    fVar4 = FLOAT_8032fab0;
    m_mapRotY = fVar1;
    fVar5 = FLOAT_8032fab4;
    m_mapRotX = fVar1;
    fVar3 = FLOAT_8032fa8c;
    m_positionZ = fVar1;
    fVar6 = FLOAT_8032fab8;
    m_positionY = fVar1;
    m_positionX = fVar1;
    m_yaw = fVar1;
    m_distance = fVar2;
    m_pitch = fVar4;
    m_fov = fVar5;
    m_nearZ = fVar3;
    m_farZ = fVar6;
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

    m_fov += triggerL;
    m_mapRotX -= stickV;
    m_mapRotY -= stickH;

    PSMTXRotRad(rotXMtx, 'x', m_mapRotX);
    PSMTXRotRad(rotYMtx, 'y', m_mapRotY);
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
            hitCylinder.radiusXZ = kCameraBoundsMinInitial;
            hitCylinder.radiusY = kCameraBoundsMinInitial;
            hitCylinder.height = kCameraBoundsMinInitial;
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
            CalcHitSlide__7CMapObjFP3Vecf(MapMng.m_hitMapObj, &moveDelta);
        }
    }

    C_MTXPerspective(m_screenMatrix, m_fov, FLOAT_8032fa3c, m_nearZ, m_farZ);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);

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
    CMemory::CStage* stage = MapMng.m_stage;

    *reinterpret_cast<void**>(self + 0x31C) = 0;
    rampTexSize = GXGetTexBufferSize(0x1E0, 0x1E0, GX_TF_I8, GX_FALSE, 0);
    *reinterpret_cast<void**>(self + 0x31C) = new (stage, s_p_camera_cpp, 0x3A5) u8[rampTexSize];

    *reinterpret_cast<void**>(self + 0x320) = 0;
    rampTexSize = GXGetTexBufferSize(0x10, 0x10, GX_TF_I8, GX_FALSE, 0);
    rampTex = new (stage, s_p_camera_cpp, 0x361) u8[rampTexSize];
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

    f32 shadowAlpha = FLOAT_8032faa4;
    m_fullScreenShadowEnabled = 1;
    f32 zero = FLOAT_8032fa34;
    m_fullScreenShadowRotX = shadowAlpha;
    shadowAlpha = FLOAT_8032faa8;
    m_fullScreenShadowRotY = zero;
    m_fullScreenShadowScale = shadowAlpha;
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
        delete static_cast<u8*>(*reinterpret_cast<void**>(self + 0x31C));
        *reinterpret_cast<void**>(self + 0x31C) = 0;
    }

    if (*reinterpret_cast<void**>(self + 0x320) != 0) {
        delete static_cast<u8*>(*reinterpret_cast<void**>(self + 0x320));
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
int CCameraPcs::GetShadowRect(CBound& shadowRectBound)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    int count = 0;
    Mtx invView;
    Mtx frustumMtx;

    PSMTXInverse(reinterpret_cast<MtxPtr>(self + 0x4), invView);
    Vec eyePos;
    eyePos.x = invView[0][3];
    eyePos.y = invView[1][3];
    eyePos.z = invView[2][3];

    PSMTXScaleApply(reinterpret_cast<MtxPtr>(self + 0x4), frustumMtx,
                    FLOAT_8032fa94 * *reinterpret_cast<float*>(self + 0x94),
                    FLOAT_8032fa98 * *reinterpret_cast<float*>(self + 0xA8),
                    FLOAT_8032fa1c);
    CBound::SetFrustum(eyePos, frustumMtx);

    for (CGObject* gObject = CFlatRuntime2Storage().FindGObjFirst(); gObject != 0;
         gObject = CFlatRuntime2Storage().FindGObjNext(gObject))
    {
        bool include = false;
        if (gObject->m_charaModelHandle != 0) {
            unsigned int displayFlags = gObject->m_displayFlags;
            if ((displayFlags & 1) != 0 && (displayFlags & 0x40) == 0) {
                if (static_cast<signed char>(
                        static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(
                                             &gObject->m_weaponNodeFlags)) << 26) &
                                         0xC0000000) >>
                        31) != 0) {
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

        float clipBoundData[6];
        CBound* clipBound = reinterpret_cast<CBound*>(clipBoundData);
        clipBoundData[0] = kCameraBoundsMinInitial;
        clipBoundData[1] = kCameraBoundsMinInitial;
        clipBoundData[2] = kCameraBoundsMinInitial;
        clipBoundData[3] = kCameraBoundsMaxInitial;
        clipBoundData[4] = kCameraBoundsMaxInitial;
        clipBoundData[5] = kCameraBoundsMaxInitial;

        float worldBoundData[6];
        CBound* worldBound = reinterpret_cast<CBound*>(worldBoundData);
        worldBoundData[0] = gObject->m_worldPosition.x - radius;
        worldBoundData[1] = gObject->m_worldPosition.y;
        worldBoundData[2] = gObject->m_worldPosition.z - radius;
        worldBoundData[3] = gObject->m_worldPosition.x + radius;
        worldBoundData[4] = gObject->m_worldPosition.y + radius;
        worldBoundData[5] = gObject->m_worldPosition.z + radius;

        if (worldBound->CheckFrustum0(*clipBound) == 0) {
            continue;
        }
        if (FLOAT_8032faa0 >= clipBoundData[0]) {
            continue;
        }
        if ((FLOAT_8032fa48 >= (clipBoundData[5] - clipBoundData[2]) / -clipBoundData[0]) &&
            (FLOAT_8032fa48 >= (clipBoundData[4] - clipBoundData[1]) / -clipBoundData[0])) {
            continue;
        }

        if (worldBoundData[0] < shadowRectBound.m_min.x) {
            shadowRectBound.m_min.x = worldBoundData[0];
        }
        if (worldBoundData[1] < shadowRectBound.m_min.y) {
            shadowRectBound.m_min.y = worldBoundData[1];
        }
        if (worldBoundData[2] < shadowRectBound.m_min.z) {
            shadowRectBound.m_min.z = worldBoundData[2];
        }
        if (shadowRectBound.m_max.x < worldBoundData[3]) {
            shadowRectBound.m_max.x = worldBoundData[3];
        }
        if (shadowRectBound.m_max.y < worldBoundData[4]) {
            shadowRectBound.m_max.y = worldBoundData[4];
        }
        if (shadowRectBound.m_max.z < worldBoundData[5]) {
            shadowRectBound.m_max.z = worldBoundData[5];
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

    if (m_fullScreenShadowEnabled == 0) {
        return;
    }

    GXInvalidateTexAll();

    CopyCameraState(self + 0x10C, self + 4);
    CopyCameraState(self + 0x214, self + 4);

    if (Game.m_currentSceneId == 3) {
        float stickX = FLOAT_8032fa34;
        float stickY = FLOAT_8032fa34;

        if (Pad._452_4_ == 0) {
            stickX = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x24 +
                                               (((1 - Pad._448_4_ | Pad._448_4_ - 1) >> 0x1f) * -0x54));
            stickY = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x28 +
                                               (((1 - Pad._448_4_ | Pad._448_4_ - 1) >> 0x1f) * -0x54));
        }

        m_fullScreenShadowRotY += FLOAT_8032fa70 * FLOAT_8032fa74 * stickX;
        m_fullScreenShadowRotX += FLOAT_8032fa70 * FLOAT_8032fa4c * stickY;
    }

    PSMTXRotRad(rotX, 'x', -m_fullScreenShadowRotX);
    PSMTXRotRad(rotY, 'y', m_fullScreenShadowRotY);
    PSMTXConcat(rotY, rotX, rotXY);

    if (Game.m_currentSceneId == 4) {
        m_shadowRectBound.m_min.x = kCameraBoundsMinInitial;
        m_shadowRectBound.m_min.y = kCameraBoundsMinInitial;
        m_shadowRectBound.m_min.z = kCameraBoundsMinInitial;
        m_shadowRectBound.m_max.x = kCameraBoundsMaxInitial;
        m_shadowRectBound.m_max.y = kCameraBoundsMaxInitial;
        m_shadowRectBound.m_max.z = kCameraBoundsMaxInitial;

        if (m_shadowAuto == 1 && GetShadowRect(m_shadowRectBound) != 0) {
            m_targetX = (m_shadowRectBound.m_min.x + m_shadowRectBound.m_max.x) * FLOAT_8032fa20;
            m_targetY = m_fullScreenShadowPosition.y;
            m_targetZ = (m_shadowRectBound.m_min.z + m_shadowRectBound.m_max.z) * FLOAT_8032fa20;

            double w = static_cast<double>(m_shadowRectBound.m_max.x - m_shadowRectBound.m_min.x);
            double h = static_cast<double>(m_shadowRectBound.m_max.z - m_shadowRectBound.m_min.z);
            if (w < h) {
                w = h;
            }
            m_fullScreenShadowSpan = static_cast<float>(static_cast<double>(FLOAT_8032fa20) * w);
            depth = w;
        } else if (m_shadowAuto == 2) {
            m_targetX = m_fullScreenShadowPosition.x;
            m_targetY = m_fullScreenShadowPosition.y;
            m_targetZ = m_fullScreenShadowPosition.z;
            PSVECSubtract(reinterpret_cast<Vec*>(&m_targetX), reinterpret_cast<Vec*>(&m_positionX), &delta);
            depth = static_cast<double>(m_fullScreenShadowCamLen);
            m_fullScreenShadowSpan = FLOAT_8032fa80 * m_fullScreenShadowScale;
        } else {
            m_targetX = m_fullScreenShadowPosition.x;
            m_targetY = m_fullScreenShadowPosition.y;
            m_targetZ = m_fullScreenShadowPosition.z;
            PSVECSubtract(reinterpret_cast<Vec*>(&m_targetX), reinterpret_cast<Vec*>(&m_positionX), &delta);
            depth = static_cast<double>(PSVECMag(&delta));
            m_fullScreenShadowSpan = static_cast<float>(depth * static_cast<double>(m_fullScreenShadowScale));
        }

        double currentDepth = static_cast<double>(m_fullScreenShadowDepth);
        if (static_cast<double>(FLOAT_8032fa34) <= currentDepth) {
            m_fullScreenShadowDepth = static_cast<float>(currentDepth +
                                                         static_cast<double>((static_cast<float>(depth - currentDepth)) * FLOAT_8032fa84));
        } else {
            m_fullScreenShadowDepth = static_cast<float>(depth);
        }
    } else {
        m_fullScreenShadowSpan = FLOAT_8032fa88;
        m_fullScreenShadowDepth = FLOAT_8032fa8c;
    }

    up.x = FLOAT_8032fa34;
    up.y = FLOAT_8032fa1c;
    up.z = FLOAT_8032fa34;
    PSMTXMultVecSR(rotXY, &up, &up);

    *reinterpret_cast<float*>(self + 0x2F0) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x2F4) = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0x2F8) = m_fullScreenShadowDepth;
    PSMTXMultVecSR(rotXY, reinterpret_cast<Vec*>(self + 0x2F0), reinterpret_cast<Vec*>(self + 0x2F0));

    if (Game.m_currentMapId == 0x21) {
        PSMTXCopy(CameraPcs.m_cameraWorldMtx, tempMtx);
        PSMTXMultVecSR(tempMtx, reinterpret_cast<Vec*>(self + 0x2F0), reinterpret_cast<Vec*>(self + 0x2F0));
    }

    PSVECAdd(reinterpret_cast<Vec*>(self + 0x2F0), reinterpret_cast<Vec*>(self + 0xD4), reinterpret_cast<Vec*>(self + 0x2F0));
    *reinterpret_cast<float*>(self + 0x2E4) = *reinterpret_cast<float*>(self + 0xD4);
    *reinterpret_cast<float*>(self + 0x2E8) = *reinterpret_cast<float*>(self + 0xD8);
    *reinterpret_cast<float*>(self + 0x2EC) = *reinterpret_cast<float*>(self + 0xDC);
    *reinterpret_cast<float*>(self + 0x310) = FLOAT_8032fa8c;
    *reinterpret_cast<float*>(self + 0x314) = FLOAT_8032fa4c * m_fullScreenShadowDepth;

    C_MTXLookAt(reinterpret_cast<MtxPtr>(self + 0x214), reinterpret_cast<Vec*>(self + 0x2F0), &up,
                reinterpret_cast<Vec*>(self + 0x2E4));
    C_MTXOrtho(reinterpret_cast<Mtx44Ptr>(self + 0x2A4),
               m_fullScreenShadowSpan, -m_fullScreenShadowSpan,
               -m_fullScreenShadowSpan, m_fullScreenShadowSpan,
               *reinterpret_cast<float*>(self + 0x310), *reinterpret_cast<float*>(self + 0x314));

    g_shadow_pos.x = *reinterpret_cast<float*>(self + 0x2F0);
    g_shadow_pos.y = *reinterpret_cast<float*>(self + 0x2F4);
    g_shadow_pos.z = *reinterpret_cast<float*>(self + 0x2F8);
    g_shadow_refpos.x = *reinterpret_cast<float*>(self + 0x2E4);
    g_shadow_refpos.y = *reinterpret_cast<float*>(self + 0x2E8);
    g_shadow_refpos.z = *reinterpret_cast<float*>(self + 0x2EC);

    CopyCameraState(self + 4, self + 0x214);
    GXSetProjection(reinterpret_cast<Mtx44Ptr>(self + 0x94), GX_ORTHOGRAPHIC);
    GXSetColorUpdate(GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetViewport(FLOAT_8032fa4c, FLOAT_8032fa4c, FLOAT_8032fa90, FLOAT_8032fa90, FLOAT_8032fa34, FLOAT_8032fa1c);
    GXSetScissor(2, 2, 0x1DC, 0x1DC);
    _GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumTexGens(0);
    MapMng.DrawMapShadow();
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

    if (m_fullScreenShadowEnabled == 0) {
        return;
    }

    C_MTXOrtho(proj, FLOAT_8032fa5c, -FLOAT_8032fa5c, FLOAT_8032fa5c, -FLOAT_8032fa5c,
               *reinterpret_cast<float*>(self + 0x310), *reinterpret_cast<float*>(self + 0x314));
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    PSMTXIdentity(ident);
    GXLoadPosMtxImm(ident, 0);

    _GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    _GXSetAlphaCompare(GX_ALWAYS, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_TRUE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
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
        float span = m_fullScreenShadowSpan;
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
    GraphicPcs.setViewport();
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

    if (m_fullScreenShadowEnabled != 0) {
        float shadowX = *reinterpret_cast<float*>(self + 0x3E0);
        float scale = FLOAT_8032fa58;
        *reinterpret_cast<float*>(self + 0x3E0) = shadowX * scale;
        *reinterpret_cast<float*>(self + 0x3F0) *= scale;
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

    if (m_fullScreenShadowEnabled != 0) {
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

    if (m_fullScreenShadowEnabled == 0) {
        return;
    }

    unsigned int* dstWords = reinterpret_cast<unsigned int*>(self + 0x4);
    unsigned int* srcWords = reinterpret_cast<unsigned int*>(self + 0x10C);
    float* dstFloats = reinterpret_cast<float*>(self + 0xF8);
    float* srcFloats = reinterpret_cast<float*>(self + 0x200);

#define COPY_SHADOW_CAMERA_WORD_PAIR(index) \
    do {                                    \
        unsigned int word0 = srcWords[index]; \
        unsigned int word1 = srcWords[(index) + 1]; \
        dstWords[index] = word0;            \
        dstWords[(index) + 1] = word1;      \
    } while (0)

    COPY_SHADOW_CAMERA_WORD_PAIR(0);
    COPY_SHADOW_CAMERA_WORD_PAIR(2);
    COPY_SHADOW_CAMERA_WORD_PAIR(4);
    COPY_SHADOW_CAMERA_WORD_PAIR(6);
    COPY_SHADOW_CAMERA_WORD_PAIR(8);
    COPY_SHADOW_CAMERA_WORD_PAIR(10);
    COPY_SHADOW_CAMERA_WORD_PAIR(12);
    COPY_SHADOW_CAMERA_WORD_PAIR(14);
    COPY_SHADOW_CAMERA_WORD_PAIR(16);
    COPY_SHADOW_CAMERA_WORD_PAIR(18);
    COPY_SHADOW_CAMERA_WORD_PAIR(20);
    COPY_SHADOW_CAMERA_WORD_PAIR(22);
    COPY_SHADOW_CAMERA_WORD_PAIR(24);
    COPY_SHADOW_CAMERA_WORD_PAIR(26);
    COPY_SHADOW_CAMERA_WORD_PAIR(28);
    COPY_SHADOW_CAMERA_WORD_PAIR(30);
    COPY_SHADOW_CAMERA_WORD_PAIR(32);
    COPY_SHADOW_CAMERA_WORD_PAIR(34);
    COPY_SHADOW_CAMERA_WORD_PAIR(36);
    COPY_SHADOW_CAMERA_WORD_PAIR(38);
    COPY_SHADOW_CAMERA_WORD_PAIR(40);
    COPY_SHADOW_CAMERA_WORD_PAIR(42);
    COPY_SHADOW_CAMERA_WORD_PAIR(44);
    COPY_SHADOW_CAMERA_WORD_PAIR(46);
    COPY_SHADOW_CAMERA_WORD_PAIR(48);
    COPY_SHADOW_CAMERA_WORD_PAIR(50);
    COPY_SHADOW_CAMERA_WORD_PAIR(52);
    COPY_SHADOW_CAMERA_WORD_PAIR(54);
    COPY_SHADOW_CAMERA_WORD_PAIR(56);
    COPY_SHADOW_CAMERA_WORD_PAIR(58);

#undef COPY_SHADOW_CAMERA_WORD_PAIR

    dstWords[60] = srcWords[60];
    dstFloats[0] = srcFloats[0];
    dstFloats[1] = srcFloats[1];
    dstFloats[2] = srcFloats[2];
    dstFloats[3] = srcFloats[3];
    dstFloats[4] = srcFloats[4];
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
    float fVar3;
    float fVar1;
    float fVar2;
    fVar2 = FLOAT_8032fa34;
    m_viewerOverride = 0;
    fVar1 = FLOAT_8032fa1c;
    m_viewer.m_position.z = fVar2;
    fVar3 = FLOAT_8032fa50;
    m_viewer.m_position.y = fVar2;
    m_viewer.m_position.x = fVar2;
    m_viewer.m_distance = fVar2;
    m_viewer.m_rotY = fVar2;
    m_viewer.m_rotX = fVar2;
    m_viewer.m_scale.z = fVar1;
    m_viewer.m_scale.y = fVar1;
    m_viewer.m_scale.x = fVar1;
    m_viewer.m_position.y = fVar2;
    m_viewer.m_position.z = fVar3;
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
        m_viewer.m_position.y += FLOAT_8032fa20;
    }
    if ((padButtons & 4) != 0) {
        m_viewer.m_position.y -= FLOAT_8032fa20;
    }

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x24 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    m_viewer.m_rotY = FLOAT_8032fa48 * stick + m_viewer.m_rotY;

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x28 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    m_viewer.m_rotX = -((FLOAT_8032fa48 * stick) - m_viewer.m_rotX);

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x1C +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    m_viewer.m_distance = -((FLOAT_8032fa4c * stick) - m_viewer.m_distance);

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    m_viewer.m_distance = FLOAT_8032fa4c * stick + m_viewer.m_distance;

    PSMTXTrans(mtxA, m_viewer.m_position.x, m_viewer.m_position.y, m_viewer.m_position.z);
    PSMTXRotRad(mtxB, 'y', m_viewer.m_rotY);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXRotRad(mtxB, 'x', m_viewer.m_rotX);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXTrans(mtxB, FLOAT_8032fa34, FLOAT_8032fa34, -m_viewer.m_distance);
    PSMTXConcat(mtxB, mtxA, m_cameraMatrix);
    PSMTXInverse(m_cameraMatrix, mtxInv);

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
    float fVar3;
    float fVar1;
    float fVar2;
    fVar2 = FLOAT_8032fa34;
    m_viewerOverride = 0;
    fVar1 = FLOAT_8032fa1c;
    m_viewer.m_position.z = fVar2;
    fVar3 = FLOAT_8032fa50;
    m_viewer.m_position.y = fVar2;
    m_viewer.m_position.x = fVar2;
    m_viewer.m_distance = fVar2;
    m_viewer.m_rotY = fVar2;
    m_viewer.m_rotX = fVar2;
    m_viewer.m_scale.z = fVar1;
    m_viewer.m_scale.y = fVar1;
    m_viewer.m_scale.x = fVar1;
    m_viewer.m_position.y = fVar2;
    m_viewer.m_position.z = fVar3;
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
        m_viewer.m_position.y += FLOAT_8032fa20;
    }
    if ((padButtons & 4) != 0) {
        m_viewer.m_position.y -= FLOAT_8032fa20;
    }

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x24 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    m_viewer.m_rotY = FLOAT_8032fa48 * stick + m_viewer.m_rotY;

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x28 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    m_viewer.m_rotX = -((FLOAT_8032fa48 * stick) - m_viewer.m_rotX);

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x1C +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    m_viewer.m_distance = -((FLOAT_8032fa4c * stick) - m_viewer.m_distance);

    stick = FLOAT_8032fa34;
    if (Pad._452_4_ == 0) {
        stick = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20 +
                                          ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54));
    }
    m_viewer.m_distance = FLOAT_8032fa4c * stick + m_viewer.m_distance;

    PSMTXTrans(mtxA, m_viewer.m_position.x, m_viewer.m_position.y, m_viewer.m_position.z);
    PSMTXRotRad(mtxB, 'y', m_viewer.m_rotY);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXRotRad(mtxB, 'x', m_viewer.m_rotX);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXTrans(mtxB, FLOAT_8032fa34, FLOAT_8032fa34, -m_viewer.m_distance);
    PSMTXConcat(mtxB, mtxA, m_cameraMatrix);
    PSMTXInverse(m_cameraMatrix, mtxInv);

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
    m_fullScreenShadowEnabled = 0;
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

    float directionZ = FLOAT_8032fa38;
    float directionXY = FLOAT_8032fa34;
    *reinterpret_cast<float*>(self + 0xEC) = directionXY;
    *reinterpret_cast<float*>(self + 0xF0) = directionXY;
    *reinterpret_cast<float*>(self + 0xF4) = directionZ;

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
void CCameraPcs::SetWorldMapMatrix(float (*mtx) [4])
{
	PSMTXCopy(mtx, m_worldMapMatrix);
	PSMTXInverse(mtx, m_cameraWorldMtx);
}

/*
 * --INFO--
 * PAL Address: 0x800B95FC
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCameraPcs::GetWorldMapMatrix(float (*mtx) [4])
{
	PSMTXCopy(m_worldMapMatrix, mtx);
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
