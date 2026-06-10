#include "ffcc/ptrarray.h"
#include "ffcc/p_camera.h"

#include "ffcc/cflat_runtime2.h"
#include "ffcc/color.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/map.h"
#include "ffcc/mapocttree.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/p_map.h"
#include "ffcc/pad.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/p_graphic.h"
#include "ffcc/game.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "ffcc/vector.h"

#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

#include <dolphin/mtx.h>
#include <dolphin/os/OSCache.h>

CCameraPcs CameraPcs;

static const char sCameraPcsGameTableName[] = "CCameraPcs(GAME)";
static const char sCameraPcsCharaTableName[] = "CCameraPcs(CHARA)";
static const char sCameraPcsMapTableName[] = "CCameraPcs(MAP)";
static const char sCameraPcsMaterialEditorTableName[] = "CCameraPcs(MATERIALEDITOR)";
static const char sCameraPcsFunnyShapeTableName[] = "CCameraPcs(FUNNYSHAPE)";
static const char sCameraPcsPartTableName[] = "CCameraPcs(PART)";
static const char sCameraPcsShadowTableName[] = "CCameraPcs(SHADOW)";

extern const float kCameraPi;
extern const float kCameraOneF;
extern const float kCameraHalfF;
extern const double kCameraS16ToDoubleBias;
extern const float kCameraDebugFov;
extern const float kCameraZeroF;
extern const float kCameraNegativeOneF;
extern const float kCameraAspectRatio;
extern const float kCameraOneEighthF;
extern const float kCameraFarZ3000;
extern const float kCameraDebugRotateStep;
extern const float kCameraTwoF;
extern const float kCameraNegativeThirtyF;
extern const float kCameraViewerFarZ;
extern const float kCameraOnePointFiveF;
extern const float kCameraHalfScreenHeight;
extern const float kCameraShadowRectLeft;
extern const float kCameraShadowRectRight;
extern const float kCameraShadowRectBottom;
extern const float kCameraShadowDepthScaleY;
extern const float kCameraDegToRad;
extern const float kCameraDebugMoveStep;
extern const float kCameraBoundsMinInitial;
extern const float kCameraBoundsMaxInitial;
extern const float kCameraShadowSpanScale;
extern const float kCameraShadowDepthBlend;
extern const float kCameraHundredF;
extern const float kCameraDefaultNearZ;
extern const float kCameraShadowViewportSize;
extern const float kCameraScreenProjectScaleX;
extern const float kCameraScreenProjectScaleY;
extern const float kCameraLookAtRadiusLimit;
extern const float kCameraClipMinZ;
extern const float kCameraQuarterPi;
extern const float kCameraOneThirdApprox;
extern const float kCameraNegativeDebugMoveStep;
extern const float kCameraDefaultPitch;
extern const float kCameraDefaultFov;
extern const float kCameraDefaultFarZ;
extern const float kCameraDebugZoomStep;
extern const float kCameraNegativeTenF;
extern const float kCameraFiftyF;
extern const float kCameraMinFov;
extern const char s_p_camera_cpp[];
extern const char sCameraInvalidFovFmt[0x40];
unsigned char g_IsDbgDrawShadowPos;

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

static inline CPad::PadInput& CameraDebugPadInput()
{
    return Pad.GetPadInputs()[(Pad.m_debugPadPort == 4) ? 0 : 4];
}

static inline CPad::PadInput& CameraShadowPadInput()
{
    return Pad.GetPadInputs()[(Pad.m_debugPadPort == 1) ? 0 : 1];
}

static inline CPad::PadInput& CameraRawPadInput()
{
    return reinterpret_cast<CPad::PadInput*>(&Pad)[(Pad.m_debugPadPort == 0) ? 0 : 0];
}

extern "C" {
void create__10CCameraPcsFv(CCameraPcs*);
void destroy__10CCameraPcsFv(CCameraPcs*);
void calc__10CCameraPcsFv(CCameraPcs*);
void draw__10CCameraPcsFv(CCameraPcs*);
void createChara__10CCameraPcsFv(CCameraPcs*);
void destroyChara__10CCameraPcsFv(CCameraPcs*);
void calcChara__10CCameraPcsFv(CCameraPcs*);
void createMap__10CCameraPcsFv(CCameraPcs*);
void destroyMap__10CCameraPcsFv(CCameraPcs*);
void calcMap__10CCameraPcsFv(CCameraPcs*);
void createMaterialEditor__10CCameraPcsFv(CCameraPcs*);
void destroyMaterialEditor__10CCameraPcsFv(CCameraPcs*);
void calcMaterialEditor__10CCameraPcsFv(CCameraPcs*);
void createFunnyShape__10CCameraPcsFv(CCameraPcs*);
void destroyFunnyShape__10CCameraPcsFv(CCameraPcs*);
void calcFunnyShape__10CCameraPcsFv(CCameraPcs*);
void createPart__10CCameraPcsFv(CCameraPcs*);
void destroyPart__10CCameraPcsFv(CCameraPcs*);
void calcPart__10CCameraPcsFv(CCameraPcs*);
void createFullShadow__10CCameraPcsFv(CCameraPcs*);
void destroyFullShadow__10CCameraPcsFv(CCameraPcs*);
void drawShadowBegin__10CCameraPcsFv(CCameraPcs*);
void drawShadowEnd__10CCameraPcsFv(CCameraPcs*);
void drawShadowChrBegin__10CCameraPcsFv(CCameraPcs*);
void drawShadowEndAll__10CCameraPcsFv(CCameraPcs*);
}

static CProcessTableCallback s_cameraTableDescCreate = {0, 0xFFFFFFFF,
                                                         reinterpret_cast<unsigned int>(create__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDestroy = {0, 0xFFFFFFFF,
                                                          reinterpret_cast<unsigned int>(destroy__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCalc = {0, 0xFFFFFFFF,
                                                       reinterpret_cast<unsigned int>(calc__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDraw = {0, 0xFFFFFFFF,
                                                       reinterpret_cast<unsigned int>(draw__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCreateChara = {0, 0xFFFFFFFF,
                                                             reinterpret_cast<unsigned int>(createChara__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDestroyChara = {0, 0xFFFFFFFF,
                                                              reinterpret_cast<unsigned int>(destroyChara__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCalcChara = {0, 0xFFFFFFFF,
                                                           reinterpret_cast<unsigned int>(calcChara__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCreateMap = {0, 0xFFFFFFFF,
                                                           reinterpret_cast<unsigned int>(createMap__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDestroyMap = {0, 0xFFFFFFFF,
                                                            reinterpret_cast<unsigned int>(destroyMap__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCalcMap = {0, 0xFFFFFFFF,
                                                         reinterpret_cast<unsigned int>(calcMap__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCreateMaterialEditor = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createMaterialEditor__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDestroyMaterialEditor = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyMaterialEditor__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCalcMaterialEditor = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcMaterialEditor__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCreateFunnyShape = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createFunnyShape__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDestroyFunnyShape = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyFunnyShape__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCalcFunnyShape = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcFunnyShape__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCreatePart = {0, 0xFFFFFFFF,
                                                            reinterpret_cast<unsigned int>(createPart__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDestroyPart = {0, 0xFFFFFFFF,
                                                             reinterpret_cast<unsigned int>(destroyPart__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCalcPart = {0, 0xFFFFFFFF,
                                                          reinterpret_cast<unsigned int>(calcPart__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescCreateFullShadow = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createFullShadow__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDestroyFullShadow = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyFullShadow__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDrawShadowBegin = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadowBegin__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDrawShadowEnd = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadowEnd__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDrawShadowChrBegin = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadowChrBegin__10CCameraPcsFv)};
static CProcessTableCallback s_cameraTableDescDrawShadowEndAll = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadowEndAll__10CCameraPcsFv)};
CProcessTable CCameraPcs::m_table[7] = {
    {
        const_cast<char*>(sCameraPcsGameTableName),
        s_cameraTableDescCreate.m_thisOffset,
        s_cameraTableDescCreate.m_virtualOffset,
        s_cameraTableDescCreate.m_function,
        s_cameraTableDescDestroy.m_thisOffset,
        s_cameraTableDescDestroy.m_virtualOffset,
        s_cameraTableDescDestroy.m_function,
        s_cameraTableDescCalc.m_thisOffset,
        s_cameraTableDescCalc.m_virtualOffset,
        s_cameraTableDescCalc.m_function,
        0x18,
        0x4,
        s_cameraTableDescDraw.m_thisOffset,
        s_cameraTableDescDraw.m_virtualOffset,
        s_cameraTableDescDraw.m_function,
        0x3D,
        0x1,
        s_cameraTableDescCreateChara.m_thisOffset,
        s_cameraTableDescCreateChara.m_virtualOffset,
        s_cameraTableDescCreateChara.m_function,
    },
    {
        const_cast<char*>(sCameraPcsCharaTableName),
        s_cameraTableDescDestroyChara.m_thisOffset,
        s_cameraTableDescDestroyChara.m_virtualOffset,
        s_cameraTableDescDestroyChara.m_function,
        s_cameraTableDescCalcChara.m_thisOffset,
        s_cameraTableDescCalcChara.m_virtualOffset,
        s_cameraTableDescCalcChara.m_function,
        s_cameraTableDescCreateMap.m_thisOffset,
        s_cameraTableDescCreateMap.m_virtualOffset,
        s_cameraTableDescCreateMap.m_function,
        0x18,
        0x4,
    },
    {
        const_cast<char*>(sCameraPcsMapTableName),
        s_cameraTableDescDestroyMap.m_thisOffset,
        s_cameraTableDescDestroyMap.m_virtualOffset,
        s_cameraTableDescDestroyMap.m_function,
        s_cameraTableDescCalcMap.m_thisOffset,
        s_cameraTableDescCalcMap.m_virtualOffset,
        s_cameraTableDescCalcMap.m_function,
        s_cameraTableDescCreateMaterialEditor.m_thisOffset,
        s_cameraTableDescCreateMaterialEditor.m_virtualOffset,
        s_cameraTableDescCreateMaterialEditor.m_function,
        0x18,
        0x4,
    },
    {
        const_cast<char*>(sCameraPcsMaterialEditorTableName),
        s_cameraTableDescDestroyMaterialEditor.m_thisOffset,
        s_cameraTableDescDestroyMaterialEditor.m_virtualOffset,
        s_cameraTableDescDestroyMaterialEditor.m_function,
        s_cameraTableDescCalcMaterialEditor.m_thisOffset,
        s_cameraTableDescCalcMaterialEditor.m_virtualOffset,
        s_cameraTableDescCalcMaterialEditor.m_function,
        s_cameraTableDescCreateFunnyShape.m_thisOffset,
        s_cameraTableDescCreateFunnyShape.m_virtualOffset,
        s_cameraTableDescCreateFunnyShape.m_function,
        0x18,
        0x4,
    },
    {
        const_cast<char*>(sCameraPcsFunnyShapeTableName),
        s_cameraTableDescDestroyFunnyShape.m_thisOffset,
        s_cameraTableDescDestroyFunnyShape.m_virtualOffset,
        s_cameraTableDescDestroyFunnyShape.m_function,
        s_cameraTableDescCalcFunnyShape.m_thisOffset,
        s_cameraTableDescCalcFunnyShape.m_virtualOffset,
        s_cameraTableDescCalcFunnyShape.m_function,
        s_cameraTableDescCreatePart.m_thisOffset,
        s_cameraTableDescCreatePart.m_virtualOffset,
        s_cameraTableDescCreatePart.m_function,
        0x18,
        0x4,
    },
    {
        const_cast<char*>(sCameraPcsPartTableName),
        s_cameraTableDescDestroyPart.m_thisOffset,
        s_cameraTableDescDestroyPart.m_virtualOffset,
        s_cameraTableDescDestroyPart.m_function,
        s_cameraTableDescCalcPart.m_thisOffset,
        s_cameraTableDescCalcPart.m_virtualOffset,
        s_cameraTableDescCalcPart.m_function,
        s_cameraTableDescCreateFullShadow.m_thisOffset,
        s_cameraTableDescCreateFullShadow.m_virtualOffset,
        s_cameraTableDescCreateFullShadow.m_function,
        0x18,
        0x4,
    },
    {
        const_cast<char*>(sCameraPcsShadowTableName),
        s_cameraTableDescDestroyFullShadow.m_thisOffset,
        s_cameraTableDescDestroyFullShadow.m_virtualOffset,
        s_cameraTableDescDestroyFullShadow.m_function,
        s_cameraTableDescDrawShadowBegin.m_thisOffset,
        s_cameraTableDescDrawShadowBegin.m_virtualOffset,
        s_cameraTableDescDrawShadowBegin.m_function,
        s_cameraTableDescDrawShadowEnd.m_thisOffset,
        s_cameraTableDescDrawShadowEnd.m_virtualOffset,
        s_cameraTableDescDrawShadowEnd.m_function,
        0x2E,
        0x1,
        s_cameraTableDescDrawShadowChrBegin.m_thisOffset,
        s_cameraTableDescDrawShadowChrBegin.m_virtualOffset,
        s_cameraTableDescDrawShadowChrBegin.m_function,
        0x32,
        0x1,
        0,
        0,
        0,
        0x39,
        0x1,
        s_cameraTableDescDrawShadowEndAll.m_thisOffset,
        s_cameraTableDescDrawShadowEndAll.m_virtualOffset,
        s_cameraTableDescDrawShadowEndAll.m_function,
        0x43,
        0x1,
    }
};
Vec g_shadow_pos;
Vec g_shadow_refpos;

extern "C" {
void pppEditGetViewPos__FP3Vec(Vec*);
void pppEditGetViewMatrix__FPA4_f(float (*)[4]);
void pppEditGetProjectionMatrix__FPA4_f(float (*)[4]);
}

namespace {

STATIC_ASSERT(offsetof(CCameraPcs, m_cameraMatrix) == 0x04);
STATIC_ASSERT(offsetof(CCameraPcs, m_worldMapMatrix) == 0x34);
STATIC_ASSERT(offsetof(CCameraPcs, m_zRotate) == 0x108);
STATIC_ASSERT(sizeof(CCameraPcs::CameraState) == 0x108);
STATIC_ASSERT(offsetof(CCameraPcs::CameraState, m_screenMatrix) == 0x90);
STATIC_ASSERT(offsetof(CCameraPcs::CameraState, m_position) == 0xDC);
STATIC_ASSERT(offsetof(CCameraPcs::CameraState, m_nearZ) == 0xFC);
STATIC_ASSERT(offsetof(CCameraPcs, m_savedCamera) == 0x10C);
STATIC_ASSERT(offsetof(CCameraPcs, m_shadowCamera) == 0x214);
STATIC_ASSERT(sizeof(CFullScreenShadow) == 0xE8);
STATIC_ASSERT(offsetof(CFullScreenShadow, m_texObjs) == 0x08);
STATIC_ASSERT(offsetof(CFullScreenShadow, m_rotX) == 0x48);
STATIC_ASSERT(offsetof(CFullScreenShadow, m_shadowTexMtx) == 0x58);
STATIC_ASSERT(offsetof(CFullScreenShadow, m_depthMtx) == 0x88);
STATIC_ASSERT(offsetof(CFullScreenShadow, m_depthScaleMtx) == 0xB8);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadow) == 0x31C);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowEnabled) == 0x404);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowPosition) == 0x408);
STATIC_ASSERT(offsetof(CCameraPcs, m_shadowRectBound) == 0x414);
STATIC_ASSERT(offsetof(CCameraPcs, m_fullScreenShadowDepth) == 0x42C);
STATIC_ASSERT(offsetof(CCameraPcs, m_isAbsolute) == 0x444);
STATIC_ASSERT(offsetof(CCameraPcs, m_viewer) == 0x448);
STATIC_ASSERT(sizeof(CCameraPcs::ViewerState) == 0x24);
STATIC_ASSERT(offsetof(CCameraPcs, m_viewerOverride) == 0x46C);
STATIC_ASSERT(offsetof(CCameraPcs, m_mapRotX) == 0x470);
STATIC_ASSERT(offsetof(CCameraPcs, m_worldMapEffect) == 0x47C);
STATIC_ASSERT(offsetof(CCameraPcs::WorldMapEffectState, m_duration) == 0x02);
STATIC_ASSERT(offsetof(CCameraPcs::WorldMapEffectState, m_timer) == 0x04);
STATIC_ASSERT(offsetof(CCameraPcs::WorldMapEffectState, m_rotX) == 0x08);
STATIC_ASSERT(offsetof(CCameraPcs::WorldMapEffectState, m_rotY) == 0x0C);
STATIC_ASSERT(offsetof(CCameraPcs::WorldMapEffectState, m_scale) == 0x10);
STATIC_ASSERT(sizeof(CCameraPcs::WorldMapEffectState) == 0x14);
STATIC_ASSERT(offsetof(CCameraPcs, m_quake) == 0x490);
STATIC_ASSERT(offsetof(CCameraPcs::QuakeState, m_state) == 0x04);
STATIC_ASSERT(offsetof(CCameraPcs::QuakeState, m_positionAmplitude) == 0x14);
STATIC_ASSERT(offsetof(CCameraPcs::QuakeState, m_jitterAmplitude) == 0x20);
STATIC_ASSERT(offsetof(CCameraPcs::QuakeState, m_startTimer) == 0x2C);
STATIC_ASSERT(sizeof(CCameraPcs::QuakeState) == 0x34);
STATIC_ASSERT(sizeof(CCameraPcs) == 0x4C4);

static inline void CopyCameraState(CCameraPcs::CameraState& dst, const CCameraPcs::CameraState& src)
{
    dst = src;
}

static inline Vec* AsVec(CVector& vec)
{
    return reinterpret_cast<Vec*>(&vec);
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
    float value5c = kCameraHalfScreenHeight;
    float value18 = kCameraPi;
    float zero = kCameraZeroF;
    float valueb0 = kCameraDefaultPitch;

    m_targetZ = zero;
    m_targetY = zero;
    m_targetX = zero;

    float valueb4 = kCameraDefaultFov;
    m_yaw = value18;

    float value8c = kCameraDefaultNearZ;
    m_distance = value5c;

    float valueb8 = kCameraDefaultFarZ;
    m_pitch = valueb0;
    m_fov = valueb4;
    m_nearZ = value8c;
    m_farZ = valueb8;
    m_isAbsolute = 0;

    PSMTXIdentity(m_worldMapMatrix);

    valueb4 = kCameraDefaultFarZ;
    m_fullScreenShadowDepth = kCameraNegativeOneF;
    value18 = kCameraZeroF;
    m_fullScreenShadowCamLen = valueb4;
    m_shadowAuto = 1;
    m_fromScript = 0;
    m_quake.m_state = 0;
    m_quake.m_keepMoving = 0;
    m_quake.m_positionAmplitude.z = value18;
    m_quake.m_positionAmplitude.y = value18;
    m_quake.m_positionAmplitude.x = value18;
    m_quake.m_jitterAmplitude.z = value18;
    m_quake.m_jitterAmplitude.y = value18;
    m_quake.m_jitterAmplitude.x = value18;
    m_quake.m_startTimer = 0;
    m_quake.m_startDuration = 0;
    m_quake.m_endTimer = 0;
    m_quake.m_endDuration = 0;
    m_quake.m_signZ = 0;
    m_quake.m_signY = 0;
    m_quake.m_signX = 0;
    m_quake.m_mode = 0;
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
    MtxPtr mathMtx = reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&Math) + 4);

    PSMTXCopy(mathMtx, m_worldMapMatrix);
    PSMTXInverse(mathMtx, m_cameraWorldMtx);

    float refValue = kCameraHundredF;
    float zero;
    m_targetZ = zero = kCameraZeroF;
    m_targetY = zero;
    m_targetX = zero;
    m_positionX = zero;
    m_positionY = refValue;
    m_positionZ = refValue;

    if (fromScript != 0) {
        m_isAbsolute = 1;
    }

    memset(&m_worldMapEffect, 0, sizeof(m_worldMapEffect));
    m_worldMapEffect.m_scale = kCameraOneF;
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
    if (immediate != 0) {
        m_quake.m_state = quakeState;
        if (quakeState != 0) {
            m_quake.m_mode = 2;
            m_quake.m_positionAmplitude.x = posAmpX;
            m_quake.m_positionAmplitude.y = posAmpY;
            m_quake.m_positionAmplitude.z = posAmpZ;
            m_quake.m_jitterAmplitude.x = jitterAmpX;
            m_quake.m_jitterAmplitude.y = jitterAmpY;
            m_quake.m_jitterAmplitude.z = jitterAmpZ;
            return;
        }

        m_quake.m_mode = 0;
        m_quake.m_positionAmplitude.z = kCameraZeroF;
        m_quake.m_positionAmplitude.y = kCameraZeroF;
        m_quake.m_positionAmplitude.x = kCameraZeroF;
        m_quake.m_jitterAmplitude.z = kCameraZeroF;
        m_quake.m_jitterAmplitude.y = kCameraZeroF;
        m_quake.m_jitterAmplitude.x = kCameraZeroF;
        return;
    }

    if ((m_quake.m_state == 0) && (quakeState != 0)) {
        m_quake.m_state = 1;
        m_quake.m_mode = 1;
        m_quake.m_keepMoving = keepMoving;
        m_quake.m_startTimer = startTime;
        m_quake.m_startDuration = startTime;
        m_quake.m_endTimer = endTime;
        m_quake.m_endDuration = endTime;
        m_quake.m_positionAmplitude.x = posAmpX;
        m_quake.m_positionAmplitude.y = posAmpY;
        m_quake.m_positionAmplitude.z = posAmpZ;
        m_quake.m_jitterAmplitude.x = jitterAmpX;
        m_quake.m_jitterAmplitude.y = jitterAmpY;
        m_quake.m_jitterAmplitude.z = jitterAmpZ;
        return;
    }

    if ((m_quake.m_state == 1) && (quakeState == 0)) {
        m_quake.m_state = 0;
        m_quake.m_mode = 1;
        m_quake.m_keepMoving = keepMoving;
        m_quake.m_startTimer = 0;
        m_quake.m_startDuration = 0;
        m_quake.m_endTimer = endTime;
        m_quake.m_endDuration = endTime;
        m_quake.m_positionAmplitude.x = posAmpX;
        m_quake.m_positionAmplitude.y = posAmpY;
        m_quake.m_positionAmplitude.z = posAmpZ;
        m_quake.m_jitterAmplitude.x = jitterAmpX;
        m_quake.m_jitterAmplitude.y = jitterAmpY;
        m_quake.m_jitterAmplitude.z = jitterAmpZ;
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
    Vec offset;
    Vec jitter;

    if (System.m_scenegraphStepMode == 2) {
        return;
    }
    if (m_quake.m_mode == 2) {
        if (m_quake.m_state == 0) {
            return;
        }
        if (m_quake.m_mode == 1 && m_quake.m_state == 0 && m_quake.m_endTimer <= 0) {
            return;
        }
    }

    u32 randomValue = static_cast<u32>(rand());
    u32 randomSign = randomValue >> 0x1F;
    m_quake.m_signX = ((randomValue & 1) ^ randomSign) - randomSign;

    m_quake.m_signY = 1 - m_quake.m_signY;

    randomValue = static_cast<u32>(rand());
    randomSign = randomValue >> 0x1F;
    m_quake.m_signZ = ((randomValue & 1) ^ randomSign) - randomSign;

    offset.z = kCameraZeroF;
    offset.y = kCameraZeroF;
    offset.x = kCameraZeroF;

    offset.x = (m_quake.m_signX == 0) ? -m_quake.m_positionAmplitude.x : m_quake.m_positionAmplitude.x;
    offset.y = (m_quake.m_signY == 0) ? -m_quake.m_positionAmplitude.y : m_quake.m_positionAmplitude.y;
    offset.z = (m_quake.m_signZ == 0) ? -m_quake.m_positionAmplitude.z : m_quake.m_positionAmplitude.z;

    jitter.z = kCameraZeroF;
    jitter.y = kCameraZeroF;
    jitter.x = kCameraZeroF;

    randomValue = static_cast<u32>(rand());
    randomSign = randomValue >> 0x1F;
    short jitterSignX = static_cast<short>(((randomValue & 1) ^ randomSign) - randomSign);

    randomValue = static_cast<u32>(rand());
    randomSign = randomValue >> 0x1F;
    short jitterSignY = static_cast<short>(((randomValue & 1) ^ randomSign) - randomSign);

    randomValue = static_cast<u32>(rand());
    randomSign = randomValue >> 0x1F;
    short jitterSignZ = static_cast<short>(((randomValue & 1) ^ randomSign) - randomSign);

    float jitterAmount;
    if (jitterSignX == 0) {
        jitterAmount = Math.RandF(m_quake.m_jitterAmplitude.x);
    } else {
        jitterAmount = -Math.RandF(m_quake.m_jitterAmplitude.x);
    }
    jitter.x = jitterAmount;

    if (jitterSignY == 0) {
        jitterAmount = Math.RandF(m_quake.m_jitterAmplitude.y);
    } else {
        jitterAmount = -Math.RandF(m_quake.m_jitterAmplitude.y);
    }
    jitter.y = jitterAmount;

    if (jitterSignZ == 0) {
        jitterAmount = Math.RandF(m_quake.m_jitterAmplitude.z);
    } else {
        jitterAmount = -Math.RandF(m_quake.m_jitterAmplitude.z);
    }
    jitter.z = jitterAmount;

    if (m_quake.m_mode == 2) {
        PSVECAdd(&offset, &jitter, &offset);
        PSVECAdd(&offset, &PositionVec(), &PositionVec());
        offset.z = kCameraZeroF;
        PSVECAdd(&offset, &TargetVec(), &TargetVec());
        return;
    }

    if (m_quake.m_mode != 1) {
        return;
    }

    if (m_quake.m_startTimer > 0) {
        float ratio = static_cast<float>(m_quake.m_startTimer) /
                      static_cast<float>(m_quake.m_startDuration);
        PSVECScale(&offset, &offset, ratio);
        PSVECAdd(&offset, &jitter, &offset);
        PSVECAdd(&offset, &PositionVec(), &PositionVec());
        PSVECAdd(&offset, &TargetVec(), &TargetVec());
        m_quake.m_startTimer = m_quake.m_startTimer - 1;

        if ((m_quake.m_startTimer == 0) && (m_quake.m_keepMoving == 0)) {
            m_quake.m_state = 0;
        }
    } else {
        if (m_quake.m_state != 0) {
            PSVECAdd(&offset, &jitter, &offset);
            PSVECAdd(&offset, &PositionVec(), &PositionVec());
            PSVECAdd(&offset, &TargetVec(), &TargetVec());
        } else if (m_quake.m_endTimer > 0) {
            float ratio = static_cast<float>(m_quake.m_endTimer) /
                          static_cast<float>(m_quake.m_endDuration);
            PSVECScale(&offset, &offset, ratio);
            PSVECSubtract(&offset, &jitter, &offset);
            PSVECAdd(&offset, &PositionVec(), &PositionVec());
            PSVECAdd(&offset, &TargetVec(), &TargetVec());
            m_quake.m_endTimer = m_quake.m_endTimer - 1;
        } else {
            m_quake.m_state = 0;
            m_quake.m_startTimer = 0;
            m_quake.m_startDuration = 0;
            m_quake.m_endTimer = 0;
            m_quake.m_endDuration = 0;
            m_quake.m_positionAmplitude.z = kCameraZeroF;
            m_quake.m_positionAmplitude.y = kCameraZeroF;
            m_quake.m_positionAmplitude.x = kCameraZeroF;
            m_quake.m_jitterAmplitude.z = kCameraZeroF;
            m_quake.m_jitterAmplitude.y = kCameraZeroF;
            m_quake.m_jitterAmplitude.x = kCameraZeroF;
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
    Mtx zRotMtx;
    Mtx invMtx;
    Mtx tempMtx;
    Mtx worldMapMtx;
    Vec up;

    bool useDebugPad = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
    unsigned short buttons;
    if (useDebugPad) {
        buttons = 0;
    } else {
        buttons = CameraRawPadInput()._pad36;
    }

    if ((buttons & 0x20) != 0) {
        m_isAbsolute = (static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(m_isAbsolute))) >> 5) & 0xFF;
    }

    if (m_isAbsolute == 0) {
        float stickH = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1))
                           ? kCameraZeroF
                           : CameraRawPadInput().substickYF;
        m_yaw += kCameraDegToRad * (kCameraDefaultNearZ * stickH);

        float stickV = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1))
                           ? kCameraZeroF
                           : *reinterpret_cast<float*>(&CameraRawPadInput().lockedButton[0]);
        m_pitch += kCameraDegToRad * (kCameraDebugZoomStep * stickV);

        float triggerL = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1))
                             ? kCameraZeroF
                             : CameraRawPadInput().stickYF;
        m_distance += kCameraDebugZoomStep * triggerL;

        float triggerR = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1))
                             ? kCameraZeroF
                             : CameraRawPadInput().triggerRightF;
        float lateral = kCameraDebugZoomStep * triggerR;

        float moveInOut = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1))
                              ? kCameraZeroF
                              : CameraRawPadInput().stickXF;
        lateral -= kCameraDebugZoomStep * moveInOut;

        float sinY;
        float yaw = m_yaw;
        float pitch = m_pitch;
        sinY = static_cast<float>(cos(pitch));
        const float sinXCosY = sinY * static_cast<float>(sin(yaw));
        sinY = static_cast<float>(sin(pitch));
        const float cosXCosY = static_cast<float>(cos(yaw)) * static_cast<float>(cos(pitch));

        float panStick = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1))
                             ? kCameraZeroF
                             : CameraRawPadInput().substickXF;
        const float camMove = kCameraDefaultNearZ * panStick;

        m_targetX = sinXCosY * camMove + m_targetX;
        m_targetY = m_targetY + (sinY * camMove + lateral);
        m_targetZ = m_targetZ - cosXCosY * camMove;

        m_positionX = m_distance * sinXCosY + m_targetX;
        m_positionY = m_distance * sinY + m_targetY;
        m_positionZ = m_targetZ - m_distance * cosXCosY;
    } else {
        m_yaw = static_cast<float>(atan2(static_cast<double>(m_positionX - m_targetX),
                                         static_cast<double>(m_targetZ - m_positionZ)));
    }

    CalcQuake();

    float fov = m_fov;
    if (fov < kCameraMinFov) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(sCameraInvalidFovFmt), fov);
        }
        fov = kCameraDefaultFov;
    }
    C_MTXPerspective(m_screenMatrix, fov, kCameraAspectRatio, m_nearZ, m_farZ);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);

    up.x = kCameraZeroF;
    up.y = kCameraOneF;
    up.z = kCameraZeroF;
    PSVECDistance(&PositionVec(), &TargetVec());
    C_MTXLookAt(m_cameraMatrix, &PositionVec(), &up, &TargetVec());

    if (Game.m_currentMapId == 0x21) {
        PSMTXCopy(m_worldMapMatrix, worldMapMtx);
        if (m_worldMapEffect.m_duration != 0 && m_worldMapEffect.m_timer != 0) {
            const double t = static_cast<double>(kCameraPi *
                (kCameraOneF - static_cast<float>(m_worldMapEffect.m_timer) /
                static_cast<float>(m_worldMapEffect.m_duration)));
            const float f = kCameraHalfF * (kCameraOneF + static_cast<float>(cos(t)));

            PSMTXRotRad(tempMtx, 'x', m_worldMapEffect.m_rotX * f);
            PSMTXConcat(tempMtx, worldMapMtx, worldMapMtx);
            PSMTXRotRad(tempMtx, 'y', m_worldMapEffect.m_rotY * f);
            PSMTXConcat(tempMtx, worldMapMtx, worldMapMtx);

            const float scale = (kCameraOneF + m_worldMapEffect.m_scale) -
                m_worldMapEffect.m_scale * (kCameraOneF - f);
            PSMTXScale(tempMtx, scale, scale, scale);
            PSMTXConcat(tempMtx, worldMapMtx, worldMapMtx);

            if (static_cast<int>(static_cast<unsigned int>(m_worldMapEffect.m_flags) << 0x18) >= 0) {
                m_worldMapEffect.m_timer -= 1;
            }
        }
        PSMTXConcat(m_cameraMatrix, worldMapMtx, m_cameraMatrix);
    }

    PSMTXRotRad(zRotMtx, 'z', m_zRotate);
    PSMTXConcat(zRotMtx, m_cameraMatrix, m_cameraMatrix);
    PSMTXInverse(m_cameraMatrix, invMtx);

    DirectionVec().x = kCameraZeroF;
    DirectionVec().y = kCameraZeroF;
    DirectionVec().z = kCameraNegativeOneF;
    PSMTXMultVecSR(invMtx, &DirectionVec(), &DirectionVec());
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

    if (fov < kCameraMinFov) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(sCameraInvalidFovFmt), fov);
        }
        fov = kCameraDefaultFov;
    }

    C_MTXPerspective(m_screenMatrix, fov, kCameraAspectRatio, m_nearZ, m_farZ);
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
    Vec* shadowPos = &g_shadow_pos;

    if ((m_isAbsolute == 0) ||
        ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_Camera) != 0)) {
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        _GXColor* drawColor = &CColor(0xFF, 0xFF, 0xFF, 0xFF).color;
        Graphic.DrawSphere(m_cameraMatrix, reinterpret_cast<Vec*>(&m_targetX), kCameraDebugZoomStep, drawColor);
    }

    if (g_map_draw_prof != 0) {
        {
        Mtx cameraMtx;
        Mtx shadowMtx;
        float posX = shadowPos->x;
        float posY = shadowPos->y;
        float posZ = shadowPos->z;
        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        PSMTXScale(shadowMtx, kCameraTwoF, kCameraTwoF, kCameraTwoF);
        shadowMtx[0][3] = posX;
        shadowMtx[1][3] = posY;
        shadowMtx[2][3] = posZ;
        PSMTXConcat(cameraMtx, shadowMtx, shadowMtx);
        GXLoadPosMtxImm(shadowMtx, 0);
        _GXColor redColor;
        redColor.r = 0xFF;
        redColor.g = 0;
        redColor.b = 0;
        redColor.a = 0xFF;
        GXSetChanMatColor(GX_COLOR0A0, redColor);
        Graphic.DrawSphere();
        }

        {
        Mtx cameraMtx;
        Mtx shadowMtx;
        Vec* shadowRefPos = &g_shadow_refpos;
        float refPosX = shadowRefPos->x;
        float refPosY = shadowRefPos->y;
        float refPosZ = shadowRefPos->z;
        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        PSMTXScale(shadowMtx, kCameraTwoF, kCameraTwoF, kCameraTwoF);
        shadowMtx[0][3] = refPosX;
        shadowMtx[1][3] = refPosY;
        shadowMtx[2][3] = refPosZ;
        PSMTXConcat(cameraMtx, shadowMtx, shadowMtx);
        GXLoadPosMtxImm(shadowMtx, 0);
        _GXColor magentaColor;
        magentaColor.r = 0;
        magentaColor.g = 0xFF;
        magentaColor.b = 0;
        magentaColor.a = 0xFF;
        GXSetChanMatColor(GX_COLOR0A0, magentaColor);
        Graphic.DrawSphere();
        }
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
    float farZ = kCameraDefaultFarZ;
    float nearZ = kCameraDefaultNearZ;
    float fov = kCameraDefaultFov;
    float fifty = kCameraFiftyF;
    float negTen = kCameraNegativeTenF;
    float one = kCameraOneF;
    float zero = kCameraZeroF;
    m_viewerOverride = 0;
    m_viewer.m_position.z = zero;
    m_viewer.m_position.y = zero;
    m_viewer.m_position.x = zero;
    m_viewer.m_distance = zero;
    m_viewer.m_rotY = zero;
    m_viewer.m_rotX = zero;
    m_viewer.m_scale.z = one;
    m_viewer.m_scale.y = one;
    m_viewer.m_scale.x = one;
    m_viewer.m_position.y = negTen;
    m_viewer.m_distance = fifty;
    m_fov = fov;
    m_nearZ = nearZ;
    m_farZ = farZ;
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
    unsigned short padButtons;
    Mtx mtxInv;
    Mtx mtxB;
    Mtx mtxA;
    Vec targetPos;
    float stick;

    C_MTXPerspective(m_screenMatrix, m_fov, kCameraAspectRatio, m_nearZ, m_farZ);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);

    if (m_viewerOverride != 0) {
        m_viewerOverride = 0;
    } else {
        if (Pad.m_debugPadLock != 0) {
            padButtons = 0;
        } else {
            padButtons = CameraDebugPadInput().button[0];
        }

        stick = ((padButtons & 4) != 0) ? kCameraHalfF : kCameraZeroF;
        m_viewer.m_position.y += stick;

        stick = ((padButtons & 8) != 0) ? kCameraHalfF : kCameraZeroF;
        m_viewer.m_position.y -= stick;

        stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().stickXF;
        m_viewer.m_rotY = kCameraDebugRotateStep * stick + m_viewer.m_rotY;

        stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().stickYF;
        m_viewer.m_rotX = -((kCameraDebugRotateStep * stick) - m_viewer.m_rotX);

        stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().triggerLeftF;
        m_viewer.m_distance = -((kCameraDebugZoomStep * stick) - m_viewer.m_distance);

        stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().triggerRightF;
        m_viewer.m_distance = kCameraDebugZoomStep * stick + m_viewer.m_distance;
    }

    PSMTXTrans(mtxA, m_viewer.m_position.x, m_viewer.m_position.y, m_viewer.m_position.z);
    PSMTXRotRad(mtxB, 'y', m_viewer.m_rotY);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXRotRad(mtxB, 'x', m_viewer.m_rotX);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXTrans(mtxB, kCameraZeroF, kCameraZeroF, -m_viewer.m_distance);
    PSMTXConcat(mtxB, mtxA, m_cameraMatrix);
    PSMTXInverse(m_cameraMatrix, mtxInv);

    DirectionVec().x = kCameraZeroF;
    DirectionVec().y = kCameraZeroF;
    DirectionVec().z = kCameraNegativeOneF;
    PSMTXMultVecSR(mtxInv, &DirectionVec(), &DirectionVec());

    m_targetX = m_viewer.m_position.x;
    m_targetY = m_viewer.m_position.y;
    m_targetZ = m_viewer.m_position.z;

    Vec* eyePtr = CVector(DirectionVec());
    CVector scaledVec;
    PSVECScale(eyePtr, AsVec(scaledVec), kCameraHundredF);
    Vec scaledDir;
    scaledDir.x = scaledVec.x;
    scaledDir.y = scaledVec.y;
    scaledDir.z = scaledVec.z;

    Vec* targetBasePtr = CVector(TargetVec());
    CVector targetVec;
    PSVECAdd(targetBasePtr, &scaledDir, AsVec(targetVec));
    Vec* tp = &targetPos;
    tp->x = targetVec.x;
    tp->y = targetVec.y;
    tp->z = targetVec.z;

    m_positionX = tp->x;
    m_positionY = tp->y;
    m_positionZ = tp->z;
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

    fVar1 = kCameraZeroF;
    fVar2 = kCameraHalfScreenHeight;
    m_mapRotZ = fVar1;
    fVar3 = kCameraDefaultPitch;
    m_mapRotY = fVar1;
    fVar4 = kCameraDefaultFov;
    m_mapRotX = fVar1;
    fVar5 = kCameraDefaultNearZ;
    m_positionZ = fVar1;
    fVar6 = kCameraDefaultFarZ;
    m_positionY = fVar1;
    m_positionX = fVar1;
    m_yaw = fVar1;
    m_distance = fVar2;
    m_pitch = fVar3;
    m_fov = fVar4;
    m_nearZ = fVar5;
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
    u16 buttons;
    float stickH;
    float stickV;
    float triggerL;
    Mtx rotYMtx;
    Mtx rotXMtx;
    Mtx rotMtx;
    Mtx invViewMtx;
    Vec dir;
    Vec moveDelta;
    Vec sideVec;
    Vec upVec;
    int i;

    struct HitCylinder {
        Vec m_bottom;  // 0x00
        Vec m_top;     // 0x0c
        Vec m_axis;    // 0x18
        float m_radius; // 0x24
        Vec m_min;     // 0x28
        Vec m_max;     // 0x34
    };
    HitCylinder hitCylinder;

    buttons = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) ? 0 : CameraRawPadInput().buttonDown[0];

    stickH = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) ? kCameraZeroF : CameraRawPadInput().substickYF;
    stickH = kCameraDegToRad * (stickH / kCameraOneEighthF);

    stickV = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) ? kCameraZeroF : *reinterpret_cast<float*>(&CameraRawPadInput().lockedButton[0]);
    stickV = -(kCameraDegToRad * (stickV / kCameraOneEighthF));

    triggerL = ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) ? kCameraZeroF : CameraRawPadInput().stickYF;

    m_fov += triggerL;
    m_mapRotX += stickV;
    m_mapRotY -= stickH;

    PSMTXRotRad(rotXMtx, 'x', m_mapRotX);
    PSMTXRotRad(rotYMtx, 'y', m_mapRotY);
    PSMTXConcat(rotYMtx, rotXMtx, rotMtx);

    DirectionVec().z = kCameraZeroF;
    DirectionVec().y = kCameraZeroF;
    DirectionVec().x = kCameraZeroF;
    DirectionVec().z = kCameraOneF;
    PSMTXMultVecSR(rotMtx, &DirectionVec(), &DirectionVec());

    moveDelta.z = kCameraZeroF;
    moveDelta.y = kCameraZeroF;
    moveDelta.x = kCameraZeroF;

    if ((buttons & 0x100) != 0) {
        PSVECScale(&DirectionVec(), &moveDelta, kCameraDebugMoveStep);
    }

    moveDelta.y = kCameraZeroF;
    if ((buttons & 0x800) != 0) {
        PSVECScale(&DirectionVec(), &moveDelta, kCameraNegativeDebugMoveStep);
        moveDelta.y = kCameraZeroF;
    }

    if ((buttons & 0x8) != 0) {
        moveDelta.y += kCameraDebugMoveStep;
    } else if ((buttons & 0x4) != 0) {
        moveDelta.y -= kCameraDebugMoveStep;
    }

    if ((buttons & 0x1) != 0) {
        sideVec.x = kCameraZeroF;
        sideVec.z = kCameraZeroF;
        sideVec.y = kCameraZeroF;
        sideVec.x = kCameraDebugMoveStep;
        PSMTXMultVecSR(rotMtx, &sideVec, &sideVec);
        sideVec.y = kCameraZeroF;
        PSVECAdd(&sideVec, &moveDelta, &moveDelta);
    } else if ((buttons & 0x2) != 0) {
        sideVec.x = kCameraZeroF;
        sideVec.z = kCameraZeroF;
        sideVec.y = kCameraZeroF;
        sideVec.x = kCameraNegativeDebugMoveStep;
        PSMTXMultVecSR(rotMtx, &sideVec, &sideVec);
        sideVec.y = kCameraZeroF;
        PSVECAdd(&sideVec, &moveDelta, &moveDelta);
    }

    if ((kCameraZeroF != moveDelta.x) || (kCameraZeroF != moveDelta.y) || (kCameraZeroF != moveDelta.z)) {
        i = 4;
        while (i-- != 0) {
            double radius = kCameraDefaultNearZ;
            double boundsMax = kCameraBoundsMaxInitial;
            double boundsMin = kCameraBoundsMinInitial;
            hitCylinder.m_min.z = boundsMin;
            hitCylinder.m_min.y = boundsMin;
            hitCylinder.m_min.x = boundsMin;
            hitCylinder.m_max.z = boundsMax;
            hitCylinder.m_max.y = boundsMax;
            hitCylinder.m_max.x = boundsMax;
            hitCylinder.m_bottom.x = PositionVec().x;
            hitCylinder.m_bottom.y = PositionVec().y;
            hitCylinder.m_bottom.z = PositionVec().z;
            hitCylinder.m_axis.x = moveDelta.x;
            hitCylinder.m_axis.y = moveDelta.y;
            hitCylinder.m_axis.z = moveDelta.z;
            hitCylinder.m_radius = radius;
            if (MapMng.CheckHitCylinder(reinterpret_cast<CMapCylinder*>(&hitCylinder), &moveDelta, 0xFFFFFFFF) != 0) {
                MapMng.m_hitMapObj->CalcHitSlide(&moveDelta, kCameraTwoF);
            } else {
                PositionVec().x += moveDelta.x;
                PositionVec().y += moveDelta.y;
                PositionVec().z += moveDelta.z;
                break;
            }
        }
    }

    C_MTXPerspective(m_screenMatrix, m_fov, kCameraAspectRatio, m_nearZ, m_farZ);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);

    PSVECAdd(&PositionVec(), &DirectionVec(), &TargetVec());

    upVec.x = kCameraZeroF;
    upVec.y = kCameraOneF;
    upVec.z = kCameraZeroF;
    PSMTXMultVecSR(rotMtx, &upVec, &upVec);
    C_MTXLookAt(m_cameraMatrix, &PositionVec(), &upVec, &TargetVec());
    PSMTXInverse(m_cameraMatrix, invViewMtx);

    dir.x = kCameraZeroF;
    dir.y = kCameraZeroF;
    dir.z = kCameraNegativeOneF;
    DirectionVec() = dir;
    PSMTXMultVecSR(invViewMtx, &DirectionVec(), &DirectionVec());
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
#pragma opt_propagation off
void CCameraPcs::createFullShadow()
{
    unsigned int rampTexSize;
    unsigned int i;
    unsigned char* rampTex;
    CMapMng* map;
    char* fileName;

    fileName = const_cast<char*>(s_p_camera_cpp);
    map = &MapMng;
    m_fullScreenShadow.m_shadowTexture = 0;
    m_fullScreenShadow.m_shadowTexture =
        new (map->m_stage, fileName, 0x3A5)
            u8[GXGetTexBufferSize(0x1E0, 0x1E0, GX_TF_I8, GX_FALSE, 0)];
    fileName = const_cast<char*>(s_p_camera_cpp);
    map = &MapMng;
    m_fullScreenShadow.m_rampTexture = 0;
    rampTex = new (map->m_stage, fileName, 0x361)
        u8[rampTexSize = GXGetTexBufferSize(0x10, 0x10, GX_TF_I8, GX_FALSE, 0)];
    m_fullScreenShadow.m_rampTexture = rampTex;

    for (i = 0; i < 0x100; i += 8) {
        u32 v6 = i + 6;
        u32 v7 = i + 7;
        u32 v3 = i + 3;
        u32 v4 = i + 4;
        u32 v5 = i + 5;
        u32 v2 = i + 2;
        u32 v1 = i + 1;
        rampTex[((i & 0x80) >> 2) + ((i >> 4) & 7) + ((i & 0xC) << 4) + ((i & 3) << 3)] =
            static_cast<unsigned char>(i);
        rampTex[((v1 & 0x80) >> 2) + ((v1 >> 4) & 7) + ((v1 & 0xC) << 4) + ((v1 & 3) << 3)] =
            static_cast<unsigned char>(v1);
        rampTex[((v2 & 0x80) >> 2) + ((v2 >> 4) & 7) + ((v2 & 0xC) << 4) + ((v2 & 3) << 3)] =
            static_cast<unsigned char>(v2);
        rampTex[((v3 & 0x80) >> 2) + ((v3 >> 4) & 7) + ((v3 & 0xC) << 4) + ((v3 & 3) << 3)] =
            static_cast<unsigned char>(v3);
        rampTex[((v4 & 0x80) >> 2) + ((v4 >> 4) & 7) + ((v4 & 0xC) << 4) + ((v4 & 3) << 3)] =
            static_cast<unsigned char>(v4);
        rampTex[((v5 & 0x80) >> 2) + ((v5 >> 4) & 7) + ((v5 & 0xC) << 4) + ((v5 & 3) << 3)] =
            static_cast<unsigned char>(v5);
        rampTex[((v6 & 0x80) >> 2) + ((v6 >> 4) & 7) + ((v6 & 0xC) << 4) + ((v6 & 3) << 3)] =
            static_cast<unsigned char>(v6);
        rampTex[((v7 & 0x80) >> 2) + ((v7 >> 4) & 7) + ((v7 & 0xC) << 4) + ((v7 & 3) << 3)] =
            static_cast<unsigned char>(v7);
    }

    GXInitTexObj(&m_fullScreenShadow.m_texObjs[1], rampTex, 0x10, 0x10, GX_TF_I8,
                 GX_CLAMP, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&m_fullScreenShadow.m_texObjs[1], GX_NEAR, GX_NEAR,
                    kCameraZeroF, kCameraZeroF, kCameraZeroF,
                    GX_FALSE, GX_FALSE, GX_ANISO_1);
    DCFlushRange(rampTex, rampTexSize);

    f32 shadowAlpha = kCameraQuarterPi;
    m_fullScreenShadowEnabled = 1;
    f32 zero = kCameraZeroF;
    m_fullScreenShadow.m_rotX = shadowAlpha;
    shadowAlpha = kCameraOneThirdApprox;
    m_fullScreenShadow.m_rotY = zero;
    m_fullScreenShadow.m_scale = shadowAlpha;
}
#pragma opt_propagation on

/*
 * --INFO--
 * PAL Address: 0x800382f8
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_propagation off
void CCameraPcs::destroyFullShadow()
{
    u8* zero;

    zero = 0;
    if (m_fullScreenShadow.m_shadowTexture != 0) {
        delete static_cast<u8*>(m_fullScreenShadow.m_shadowTexture);
        m_fullScreenShadow.m_shadowTexture = zero;
    }

    zero = 0;
    if (m_fullScreenShadow.m_rampTexture != 0) {
        delete m_fullScreenShadow.m_rampTexture;
        m_fullScreenShadow.m_rampTexture = zero;
    }
}
#pragma opt_propagation on

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
    int count = 0;
    Mtx invView;
    Mtx frustumMtx;

    PSMTXInverse(m_cameraMatrix, invView);
    Vec eyePos;
    eyePos.x = invView[0][3];
    eyePos.y = invView[1][3];
    eyePos.z = invView[2][3];

    PSMTXScaleApply(m_cameraMatrix, frustumMtx,
                    kCameraScreenProjectScaleX * m_screenMatrix[0][0],
                    kCameraScreenProjectScaleY * m_screenMatrix[1][1],
                    kCameraOneF);
    CBound::SetFrustum(eyePos, frustumMtx);

    for (CGObject* gObject = CFlatRuntime2Storage().FindGObjFirst(); gObject != 0;
         gObject = CFlatRuntime2Storage().FindGObjNext(gObject))
    {
        unsigned int displayFlags;
        bool include = false;
        if (gObject->m_charaModelHandle != 0) {
            displayFlags = gObject->m_displayFlags;
            if ((displayFlags & 1) != 0 && (displayFlags & 0x40) == 0) {
                if (static_cast<signed char>(
                        static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<signed char*>(
                                             &gObject->m_weaponNodeFlags)) << 26) &
                                         0xC0000000) >>
                        31) != 0) {
                    if ((displayFlags & 0x80) != 0 || kCameraOneF == gObject->m_lookAtTimer) {
                        include = true;
                    }
                }
            }
        }

        if (!include) {
            continue;
        }

        float radius = gObject->m_nearColRadius;
        if (radius > kCameraLookAtRadiusLimit) {
            radius = kCameraLookAtRadiusLimit;
        }

        float worldBoundData[6];
        CBound* worldBound = reinterpret_cast<CBound*>(worldBoundData);
        float clipBoundData[6];
        CBound* clipBound = reinterpret_cast<CBound*>(clipBoundData);
        worldBoundData[0] = gObject->m_worldPosition.x - radius;
        worldBoundData[3] = gObject->m_worldPosition.x + radius;
        worldBoundData[2] = gObject->m_worldPosition.z - radius;
        worldBoundData[5] = gObject->m_worldPosition.z + radius;
        worldBoundData[1] = gObject->m_worldPosition.y;
        clipBoundData[2] = kCameraBoundsMinInitial;
        worldBoundData[4] = gObject->m_worldPosition.y + radius;
        clipBoundData[1] = kCameraBoundsMinInitial;
        clipBoundData[0] = kCameraBoundsMinInitial;
        clipBoundData[5] = kCameraBoundsMaxInitial;
        clipBoundData[4] = kCameraBoundsMaxInitial;
        clipBoundData[3] = kCameraBoundsMaxInitial;

        if (worldBound->CheckFrustum0(*clipBound) == 0) {
            continue;
        }
        if (!(clipBoundData[2] > kCameraClipMinZ)) {
            continue;
        }
        float negMinZ = -clipBoundData[2];
        float ratioX = (clipBoundData[3] - clipBoundData[0]) / negMinZ;
        float ratioY = (clipBoundData[4] - clipBoundData[1]) / negMinZ;
        if (ratioX > kCameraDebugRotateStep) {
            // proceed
        } else if (!(ratioY > kCameraDebugRotateStep)) {
            continue;
        }

        shadowRectBound.m_min.x =
            (shadowRectBound.m_min.x < worldBoundData[0]) ? shadowRectBound.m_min.x : worldBoundData[0];
        shadowRectBound.m_min.y =
            (shadowRectBound.m_min.y < worldBoundData[1]) ? shadowRectBound.m_min.y : worldBoundData[1];
        shadowRectBound.m_min.z =
            (shadowRectBound.m_min.z < worldBoundData[2]) ? shadowRectBound.m_min.z : worldBoundData[2];
        shadowRectBound.m_max.x =
            (shadowRectBound.m_max.x > worldBoundData[3]) ? shadowRectBound.m_max.x : worldBoundData[3];
        shadowRectBound.m_max.y =
            (shadowRectBound.m_max.y > worldBoundData[4]) ? shadowRectBound.m_max.y : worldBoundData[4];
        shadowRectBound.m_max.z =
            (shadowRectBound.m_max.z > worldBoundData[5]) ? shadowRectBound.m_max.z : worldBoundData[5];
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
    Mtx rotY;
    Mtx rotX;
    Mtx rotXY;
    Mtx tempMtx;
    Vec delta;
    Vec up;
    float depth;

    if (m_fullScreenShadowEnabled == 0) {
        return;
    }

    GXInvalidateTexAll();

    CopyCameraState(m_savedCamera, CurrentCameraState());
    CopyCameraState(m_shadowCamera, CurrentCameraState());

    if (Game.m_currentSceneId == 3) {
        float stickX = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraShadowPadInput().stickXF;
        m_fullScreenShadow.m_rotY += kCameraDegToRad * (kCameraDebugMoveStep * stickX);

        float stickY = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraShadowPadInput().stickYF;
        m_fullScreenShadow.m_rotX += kCameraDegToRad * (kCameraTwoF * stickY);
    }

    PSMTXRotRad(rotX, 'x', -m_fullScreenShadow.m_rotX);
    PSMTXRotRad(rotY, 'y', m_fullScreenShadow.m_rotY);
    PSMTXConcat(rotY, rotX, rotXY);

    if (Game.m_currentSceneId == 4) {
        m_shadowRectBound.m_min.z = kCameraBoundsMinInitial;
        m_shadowRectBound.m_min.y = kCameraBoundsMinInitial;
        m_shadowRectBound.m_min.x = kCameraBoundsMinInitial;
        m_shadowRectBound.m_max.z = kCameraBoundsMaxInitial;
        m_shadowRectBound.m_max.y = kCameraBoundsMaxInitial;
        m_shadowRectBound.m_max.x = kCameraBoundsMaxInitial;

        if (m_shadowAuto == 1 && GetShadowRect(m_shadowRectBound) != 0) {
            float sumX = m_shadowRectBound.m_min.x + m_shadowRectBound.m_max.x;
            float half = kCameraHalfF;
            float sumZ = m_shadowRectBound.m_min.z + m_shadowRectBound.m_max.z;
            m_targetX = sumX * half;
            m_targetZ = sumZ * half;
            m_targetY = m_fullScreenShadowPosition.y;

            depth = m_shadowRectBound.m_max.x - m_shadowRectBound.m_min.x;
            float h = m_shadowRectBound.m_max.z - m_shadowRectBound.m_min.z;
            if (depth < h) {
                depth = h;
            }
            m_fullScreenShadow.m_span = kCameraHalfF * depth;
        } else if (m_shadowAuto == 2) {
            m_targetX = m_fullScreenShadowPosition.x;
            m_targetY = m_fullScreenShadowPosition.y;
            m_targetZ = m_fullScreenShadowPosition.z;
            PSVECSubtract(reinterpret_cast<Vec*>(&m_targetX), reinterpret_cast<Vec*>(&m_positionX), &delta);
            depth = m_fullScreenShadowCamLen;
            m_fullScreenShadow.m_span = kCameraShadowSpanScale * m_fullScreenShadow.m_scale;
        } else {
            m_targetX = m_fullScreenShadowPosition.x;
            m_targetY = m_fullScreenShadowPosition.y;
            m_targetZ = m_fullScreenShadowPosition.z;
            PSVECSubtract(reinterpret_cast<Vec*>(&m_targetX), reinterpret_cast<Vec*>(&m_positionX), &delta);
            depth = PSVECMag(&delta);
            m_fullScreenShadow.m_span = depth * m_fullScreenShadow.m_scale;
        }

        float currentDepth = m_fullScreenShadowDepth;
        if (currentDepth < kCameraZeroF) {
            m_fullScreenShadowDepth = depth;
        } else {
            float blended = (depth - currentDepth) * kCameraShadowDepthBlend;
            m_fullScreenShadowDepth = currentDepth + blended;
        }
    } else {
        m_fullScreenShadow.m_span = kCameraHundredF;
        m_fullScreenShadowDepth = kCameraDefaultNearZ;
    }

    up.x = kCameraZeroF;
    up.y = kCameraOneF;
    up.z = kCameraZeroF;
    PSMTXMultVecSR(rotXY, &up, &up);

    m_shadowCamera.m_position.x = kCameraZeroF;
    m_shadowCamera.m_position.y = kCameraZeroF;
    m_shadowCamera.m_position.z = m_fullScreenShadowDepth;
    PSMTXMultVecSR(rotXY, reinterpret_cast<Vec*>(&m_shadowCamera.m_position.x), reinterpret_cast<Vec*>(&m_shadowCamera.m_position.x));

    if (Game.m_currentMapId == 0x21) {
        PSMTXCopy(CameraPcs.m_cameraWorldMtx, tempMtx);
        PSMTXMultVecSR(tempMtx, reinterpret_cast<Vec*>(&m_shadowCamera.m_position.x), reinterpret_cast<Vec*>(&m_shadowCamera.m_position.x));
    }

    PSVECAdd(reinterpret_cast<Vec*>(&m_shadowCamera.m_position.x), reinterpret_cast<Vec*>(&m_targetX), reinterpret_cast<Vec*>(&m_shadowCamera.m_position.x));
    m_shadowCamera.m_target.x = m_targetX;
    m_shadowCamera.m_target.y = m_targetY;
    m_shadowCamera.m_target.z = m_targetZ;
    m_shadowCamera.m_nearZ = kCameraDefaultNearZ;
    m_shadowCamera.m_farZ = kCameraTwoF * m_fullScreenShadowDepth;

    C_MTXLookAt(m_shadowCamera.m_cameraMatrix, reinterpret_cast<Vec*>(&m_shadowCamera.m_position.x), &up,
                reinterpret_cast<Vec*>(&m_shadowCamera.m_target.x));
    C_MTXOrtho(m_shadowCamera.m_screenMatrix,
               m_fullScreenShadow.m_span, -m_fullScreenShadow.m_span,
               -m_fullScreenShadow.m_span, m_fullScreenShadow.m_span,
               m_shadowCamera.m_nearZ, m_shadowCamera.m_farZ);

    g_shadow_pos.x = m_shadowCamera.m_position.x;
    g_shadow_pos.y = m_shadowCamera.m_position.y;
    g_shadow_pos.z = m_shadowCamera.m_position.z;
    g_shadow_refpos.x = m_shadowCamera.m_target.x;
    g_shadow_refpos.y = m_shadowCamera.m_target.y;
    g_shadow_refpos.z = m_shadowCamera.m_target.z;

    CopyCameraState(CurrentCameraState(), m_shadowCamera);
    GXSetProjection(m_screenMatrix, GX_ORTHOGRAPHIC);
    GXSetColorUpdate(GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetViewport(kCameraTwoF, kCameraTwoF, kCameraShadowViewportSize, kCameraShadowViewportSize, kCameraZeroF, kCameraOneF);
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

    float negHalf = -kCameraHalfScreenHeight;
    float nearZ = m_shadowCamera.m_nearZ;
    float farZ = m_shadowCamera.m_farZ;
    C_MTXOrtho(proj, kCameraHalfScreenHeight, negHalf, kCameraHalfScreenHeight, negHalf,
               nearZ, farZ);
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
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetNumTexGens(0);

    {
        GXColor black;
        black.r = 0;
        black.g = 0;
        black.b = 0;
        black.a = 0;
        GXSetChanMatColor(GX_COLOR0A0, black);
    }

    z = -farZ + nearZ;
    x0 = static_cast<int>(negHalf - kCameraTwoF);
    x1 = static_cast<int>(kCameraShadowRectLeft);
    y0 = static_cast<int>(kCameraShadowRectRight);
    y1 = static_cast<int>(kCameraShadowRectBottom);
    x2 = static_cast<int>(kCameraShadowRectRight);

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
    GXSetTexCopyDst(0x1E0, 0x1E0, GX_TF_Z8, GX_FALSE);
    GXCopyTex(m_fullScreenShadow.m_shadowTexture, GX_TRUE);
    GXSetCullMode(GX_CULL_FRONT);

    {
        float span = m_fullScreenShadow.m_span;
        C_MTXLightOrtho(m_fullScreenShadow.m_shadowTexMtx, -span, span, -span, span,
                        kCameraHalfF, kCameraHalfF, kCameraHalfF, kCameraHalfF);
        PSMTXScale(m_fullScreenShadow.m_depthScaleMtx, kCameraZeroF, kCameraZeroF, kCameraZeroF);
        float one = kCameraOneF;
        float depthSpan = m_shadowCamera.m_farZ - m_shadowCamera.m_nearZ;
        m_fullScreenShadow.m_depthScaleMtx[0][2] = kCameraNegativeOneF / depthSpan;
        m_fullScreenShadow.m_depthScaleMtx[0][3] = -(m_shadowCamera.m_nearZ / depthSpan);
        m_fullScreenShadow.m_depthScaleMtx[1][2] = m_fullScreenShadow.m_depthScaleMtx[0][2] * kCameraShadowDepthScaleY;
        m_fullScreenShadow.m_depthScaleMtx[1][3] = m_fullScreenShadow.m_depthScaleMtx[0][3] * kCameraShadowDepthScaleY;
        m_fullScreenShadow.m_depthScaleMtx[2][3] = one;
        PSMTXConcat(m_fullScreenShadow.m_shadowTexMtx,
                    m_shadowCamera.m_cameraMatrix,
                    m_fullScreenShadow.m_shadowTexMtx);
        PSMTXConcat(m_fullScreenShadow.m_depthScaleMtx,
                    m_shadowCamera.m_cameraMatrix,
                    m_fullScreenShadow.m_depthMtx);
    }

    GXSetColorUpdate(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXPixModeSync();
    GXInitTexObj(&m_fullScreenShadow.m_texObjs[0], m_fullScreenShadow.m_shadowTexture,
                 0x1E0, 0x1E0, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&m_fullScreenShadow.m_texObjs[0], GX_NEAR, GX_NEAR, kCameraZeroF,
                    kCameraZeroF, kCameraZeroF, GX_FALSE, GX_FALSE, GX_ANISO_1);

    CopyCameraState(CurrentCameraState(), m_savedCamera);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);
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
        float shadowX = m_fullScreenShadow.m_depthScaleMtx[0][3];
        m_fullScreenShadow.m_depthScaleMtx[0][3] = shadowX * kCameraOnePointFiveF;
        m_fullScreenShadow.m_depthScaleMtx[1][3] *= kCameraOnePointFiveF;
        PSMTXConcat(m_fullScreenShadow.m_depthScaleMtx,
                    m_shadowCamera.m_cameraMatrix,
                    m_fullScreenShadow.m_depthMtx);
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
    if (m_fullScreenShadowEnabled != 0) {
        MaterialMan.SetFullScreenShadow(m_fullScreenShadow, matrix, flags);
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
    if (m_fullScreenShadowEnabled == 0) {
        return;
    }

    CopyCameraState(CurrentCameraState(), m_savedCamera);
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
    float negThirty = kCameraNegativeThirtyF;
    float one = kCameraOneF;
    float zero = kCameraZeroF;
    m_viewerOverride = 0;
    m_viewer.m_position.z = zero;
    m_viewer.m_position.y = zero;
    m_viewer.m_position.x = zero;
    m_viewer.m_distance = zero;
    m_viewer.m_rotY = zero;
    m_viewer.m_rotX = zero;
    m_viewer.m_scale.z = one;
    m_viewer.m_scale.y = one;
    m_viewer.m_scale.x = one;
    m_viewer.m_position.y = zero;
    m_viewer.m_position.z = negThirty;
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
    unsigned short padButtons;
    Mtx mtxInv;
    Mtx mtxB;
    Mtx mtxA;
    float stick;

    C_MTXPerspective(m_screenMatrix, kCameraDebugFov, kCameraAspectRatio, kCameraOneEighthF, kCameraViewerFarZ);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);

    if (Pad.m_debugPadLock != 0) {
        padButtons = 0;
    } else {
        padButtons = CameraDebugPadInput().button[0];
    }

    stick = ((padButtons & 8) != 0) ? kCameraHalfF : kCameraZeroF;
    m_viewer.m_position.y += stick;

    stick = ((padButtons & 4) != 0) ? kCameraHalfF : kCameraZeroF;
    m_viewer.m_position.y -= stick;

    stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().stickXF;
    m_viewer.m_rotY = kCameraDebugRotateStep * stick + m_viewer.m_rotY;

    stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().stickYF;
    m_viewer.m_rotX = -((kCameraDebugRotateStep * stick) - m_viewer.m_rotX);

    stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().triggerLeftF;
    m_viewer.m_distance = -((kCameraTwoF * stick) - m_viewer.m_distance);

    stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().triggerRightF;
    m_viewer.m_distance = kCameraTwoF * stick + m_viewer.m_distance;

    PSMTXTrans(mtxA, m_viewer.m_position.x, m_viewer.m_position.y, m_viewer.m_position.z);
    PSMTXRotRad(mtxB, 'y', m_viewer.m_rotY);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXRotRad(mtxB, 'x', m_viewer.m_rotX);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXTrans(mtxB, kCameraZeroF, kCameraZeroF, -m_viewer.m_distance);
    PSMTXConcat(mtxB, mtxA, m_cameraMatrix);
    PSMTXInverse(m_cameraMatrix, mtxInv);

    DirectionVec().x = kCameraZeroF;
    DirectionVec().y = kCameraZeroF;
    DirectionVec().z = kCameraNegativeOneF;
    PSMTXMultVecSR(mtxInv, &DirectionVec(), &DirectionVec());
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
    float negThirty = kCameraNegativeThirtyF;
    float one = kCameraOneF;
    float zero = kCameraZeroF;
    m_viewerOverride = 0;
    m_viewer.m_position.z = zero;
    m_viewer.m_position.y = zero;
    m_viewer.m_position.x = zero;
    m_viewer.m_distance = zero;
    m_viewer.m_rotY = zero;
    m_viewer.m_rotX = zero;
    m_viewer.m_scale.z = one;
    m_viewer.m_scale.y = one;
    m_viewer.m_scale.x = one;
    m_viewer.m_position.y = zero;
    m_viewer.m_position.z = negThirty;
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
    unsigned short padButtons;
    Mtx mtxInv;
    Mtx mtxB;
    Mtx mtxA;
    float stick;

    C_MTXPerspective(m_screenMatrix, kCameraDebugFov, kCameraAspectRatio, kCameraOneEighthF, kCameraFarZ3000);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);

    if (Pad.m_debugPadLock != 0) {
        padButtons = 0;
    } else {
        padButtons = CameraDebugPadInput().button[0];
    }

    stick = ((padButtons & 8) != 0) ? kCameraHalfF : kCameraZeroF;
    m_viewer.m_position.y += stick;

    stick = ((padButtons & 4) != 0) ? kCameraHalfF : kCameraZeroF;
    m_viewer.m_position.y -= stick;

    stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().stickXF;
    m_viewer.m_rotY = kCameraDebugRotateStep * stick + m_viewer.m_rotY;

    stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().stickYF;
    m_viewer.m_rotX = -((kCameraDebugRotateStep * stick) - m_viewer.m_rotX);

    stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().triggerLeftF;
    m_viewer.m_distance = -((kCameraTwoF * stick) - m_viewer.m_distance);

    stick = (Pad.m_debugPadLock != 0) ? kCameraZeroF : CameraDebugPadInput().triggerRightF;
    m_viewer.m_distance = kCameraTwoF * stick + m_viewer.m_distance;

    PSMTXTrans(mtxA, m_viewer.m_position.x, m_viewer.m_position.y, m_viewer.m_position.z);
    PSMTXRotRad(mtxB, 'y', m_viewer.m_rotY);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXRotRad(mtxB, 'x', m_viewer.m_rotX);
    PSMTXConcat(mtxB, mtxA, mtxA);
    PSMTXTrans(mtxB, kCameraZeroF, kCameraZeroF, -m_viewer.m_distance);
    PSMTXConcat(mtxB, mtxA, m_cameraMatrix);
    PSMTXInverse(m_cameraMatrix, mtxInv);

    DirectionVec().x = kCameraZeroF;
    DirectionVec().y = kCameraZeroF;
    DirectionVec().z = kCameraNegativeOneF;
    PSMTXMultVecSR(mtxInv, &DirectionVec(), &DirectionVec());
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
    Mtx invCamera;
    Vec pos;

    if (m_quake.m_state != 0) {
        CalcQuake();

        pos.x = ppvCameraMatrix0[0][3];
        pos.y = ppvCameraMatrix0[1][3];
        pos.z = ppvCameraMatrix0[2][3];

        PSVECAdd(&m_quake.m_positionAmplitude, &pos, &pos);

        ppvCameraMatrix0[0][3] = pos.x;
        ppvCameraMatrix0[1][3] = pos.y;
        ppvCameraMatrix0[2][3] = pos.z;
    }

    m_fov = kCameraDebugFov;

    pppEditGetViewPos__FP3Vec(&PositionVec());
    pppEditGetViewMatrix__FPA4_f(m_cameraMatrix);
    pppEditGetProjectionMatrix__FPA4_f(m_screenMatrix);
    GXSetProjection(m_screenMatrix, GX_PERSPECTIVE);

    PSMTXInverse(m_cameraMatrix, invCamera);

    float directionZ = kCameraNegativeOneF;
    float directionXY = kCameraZeroF;
    DirectionVec().x = directionXY;
    DirectionVec().y = directionXY;
    DirectionVec().z = directionZ;

    PSMTXMultVecSR(invCamera, &DirectionVec(), &DirectionVec());
    PSVECAdd(&PositionVec(), &DirectionVec(), &TargetVec());
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
    Mtx44 projection;

    PSMTX44Copy(m_screenMatrix, projection);
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
