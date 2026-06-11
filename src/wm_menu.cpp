#include "ffcc/ptrarray.h"
#include "ffcc/wm_menu.h"

#include "ffcc/baseobj.h"
#include "ffcc/goout.h"
#include "ffcc/gbaque.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/math.h"
#include "ffcc/menu.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_chara.h"
#include "ffcc/game.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/sound.h"
#include "ffcc/p_light.h"
#include "ffcc/partMng.h"
#include "ffcc/p_tina.h"
#include "ffcc/strcase.h"
#include "ffcc/THPSimple.h"
#include "ffcc/joybus.h"
#include "ffcc/color.h"
#include "ffcc/vector.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/textureman.h"
#include "ffcc/mesmenu.h"
#include "ffcc/file.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include "ffcc/fontman.h"

extern "C" char* strstr(const char*, const char*);
extern "C" char* strcat(char*, const char*);
extern "C" int DAT_801dc118[];
extern "C" int DAT_801dc140;
extern char lbl_80331208[];
extern float gWmModelYOffsetSplinePoints[];
extern float gWmModelRotationSplinePoints[];
extern float lbl_802109B4[];
extern float lbl_80210A04[];
extern float lbl_80210A34[];
extern float lbl_80210A74[];
extern float lbl_80210AB4[];
extern float lbl_80210B04[];
extern const char s_Empty_803313A4[];
extern const char s_Creating_801DC250[];
extern const char s_Frei_803313AC[];
extern const char s_Wird_kreiert_801DC25C[];
extern const char s_Vuoto_803313B4[];
extern const char s_Creazione_801DC26C[];
extern const char s_Vide_803313BC[];
extern const char s_Creation_801DC27C[];
extern const char s_Vacio_803313C4[];
extern const char s_Creando_801DC288[];
extern float gWmLifeYOffsetSplinePoints[];

char* DAT_8032E8A8 = lbl_80331208;
unsigned char lbl_8032E8AC = 1;
int gWmModelYOffsetSplineCount = 9;
float* gWmModelYOffsetSpline = gWmModelYOffsetSplinePoints;
int gWmModelRotationSplineCount = 5;
float* gWmModelRotationSpline = gWmModelRotationSplinePoints;
struct SplineTable {
	int count;
	float* data;
};
SplineTable s_YearTrns = {5, lbl_802109B4};
int DAT_8032e8c8 = 3;
float* DAT_8032e8cc = lbl_80210A04;
int DAT_8032E8D0 = 4;
float* DAT_8032E8D4 = lbl_80210A34;
int DAT_8032E8D8 = 4;
float* DAT_8032E8DC = lbl_80210A74;
int DAT_8032E8E0 = 5;
float* DAT_8032E8E4 = lbl_80210AB4;
int DAT_8032E8E8 = 7;
float* DAT_8032E8EC = lbl_80210B04;
extern int DAT_8032ef08;
extern int DAT_80238028;
extern char cRam8032ee21;
extern "C" char lbl_80331380[4];
extern "C" char lbl_80331400[3];
extern "C" unsigned char lbl_801DC294[];
extern "C" const char* lbl_80210D10[];
extern "C" const char* lbl_80210D54[];
extern "C" const char* lbl_80210D68[];
extern "C" char* lbl_80210750[];
extern "C" char* lbl_80210B74[];
extern "C" CMenuPcs::CTmp lbl_80210B98[];

inline CGBaseObj::CGBaseObj()
{
}

inline CGObject::CGObject()
{
}

extern float FLOAT_8032ee18;
unsigned char lbl_8032EE1C;
char gWmMenuCursorX[2];
char gWmMenuCursorY[2];
int gWmMenuWorkA;
int gWmMenuWorkB;
unsigned char gWmMenuScriptValueCache;
unsigned char s_wmMenuLastMountState;
unsigned char s_wmMenuMountStateInitialized;
extern char* DAT_8032EE34;
extern unsigned char lbl_8032EE38[8];

// wm_menu.o owns this .sdata2 constant pool (0x80331134-0x803311BC). These
// named float/int constants are emitted into wm_menu's .sdata2 in address
// order; defining them in-unit makes wm_menu.o's .sdata2 match the target.
extern const float kCharaFurScreenCenterY = 224.0f;
extern const float kCharaFurDepthScaleBase = 1.0f;
extern const float kCharaFurScreenCenterX = 320.0f;
extern const float kCharaFurTriangleVertexCount = 3.0f;
extern const float kCharaFurPickRayFarZ = -100.0f;
extern const float kCharaFurWeightScale = 0.5f;
extern const float kCharaFurViewDepthThreshold = -1.0f;
extern const float kCharaFurShadeScale = 255.0f;
extern const float kCharaFurShadowRange = 100.0f;
extern const float kCharaFurShadowFade = 20.0f;
extern const float FLOAT_8033115C = 0.125f;
extern const float FLOAT_80331160 = 4.0f;
extern const float FLOAT_80331164 = 6.103701889514923e-05f;
extern const float FLOAT_80331168 = 128.0f;
extern const float FLOAT_8033116C = 8.0f;
extern const int sYmEnvXAxisIdsWord = 0x79797979;
extern const short sYmEnvXAxisIdsTail = 0x7878;
extern const float sYmEnvYAxisAngle0 = 0.0f;
extern const float sYmEnvYAxisAngle180 = 180.0f;
extern const float kYmEnvRenderZero = 0.0f;
extern const float kYmEnvRenderOne = 1.0f;
extern const float kYmEnvNegativeOne = -1.0f;
extern const float kYmEnvOrthoFarZ = 100.0f;
extern const float kYmEnvTwo = 2.0f;
extern const float kYmEnvFrustumExtent = 1.0199999809265137f;
extern const float kYmEnvFrustumNegExtent = -1.0199999809265137f;
extern const float kYmEnvFrustumScale = 0.5f;
extern const float kYmEnvDegToRadF = 0.01745329238474369f;
extern const float kYmEnvPi = 3.1415927410125732f;
extern const float kYmEnvParaboloidNormalScale = -2.0f;
extern const float kYmEnvNegativeTwoPi = -6.2831854820251465f;

extern float FLOAT_803313dc;
extern float FLOAT_803313e0;
extern float FLOAT_803313e4;
extern float FLOAT_803313e8;
extern float FLOAT_80331470;
extern float FLOAT_80331474;
extern float FLOAT_80331478;
extern float FLOAT_8033147c;
extern float FLOAT_80331480;
extern float FLOAT_803314A0;
extern float FLOAT_803314B0;
extern float FLOAT_803314B4;
extern float FLOAT_803314B8;
extern float FLOAT_803314bc;
extern float FLOAT_803314c0;
extern float FLOAT_803314c4;
extern float FLOAT_803314c8;
extern float FLOAT_803314cc;
extern float FLOAT_80331430;
extern float FLOAT_8033151c;
extern float FLOAT_80331518;
extern float FLOAT_80331520;
extern float FLOAT_80331528;
extern double DOUBLE_80331530;
extern float FLOAT_803315cc;
extern float FLOAT_803315d0;
extern float FLOAT_80331598;
extern float FLOAT_803317FC;
extern double DOUBLE_803313F0;
extern char lbl_80331800[7];
extern char lbl_80331808[7];
extern char lbl_80331810[7];
extern char lbl_80331818[7];
extern char lbl_80331820[7];
extern char lbl_80331828[7];
extern char lbl_80331830[8];
extern char lbl_80331838[7];
extern char lbl_801DB7F8[];
extern float FLOAT_80331588;
extern float FLOAT_80331590;
extern float FLOAT_803315d4;
extern float FLOAT_80331698;
extern float FLOAT_8033169C;
extern float FLOAT_803316A0;
extern float FLOAT_803316A4;
extern float FLOAT_803316A8;
extern float FLOAT_803316AC;
extern float FLOAT_803316B0;
extern float FLOAT_803316B4;
extern float FLOAT_803316B8;
extern float FLOAT_803316BC;
extern float FLOAT_80331748;
extern float FLOAT_8033174c;
extern float FLOAT_80331750;
extern float FLOAT_80331754;
extern float FLOAT_80331610;
extern float FLOAT_80331614;
extern float FLOAT_80331618;
extern float FLOAT_8033161C;
extern float FLOAT_80331620;
extern float FLOAT_8033168C;
extern float FLOAT_80331690;
extern float FLOAT_80331694;
extern float FLOAT_80331410;
extern float FLOAT_80331458;
extern float FLOAT_803316d4;
extern float FLOAT_803316F0;
extern float FLOAT_803316F4;
extern float FLOAT_803316F8;
extern float FLOAT_80331760;
extern float FLOAT_80331764;
extern float FLOAT_803315b0;
extern float FLOAT_80331440;
extern float FLOAT_80331444;
extern float FLOAT_8033146c;
extern float FLOAT_80331664;
extern float FLOAT_80331434;
extern float FLOAT_80331524;
extern float FLOAT_80331704;
extern float FLOAT_80331708;
extern float FLOAT_8033170c;
extern float FLOAT_80331710;
extern float FLOAT_80331714;
extern float FLOAT_80331718;
extern float FLOAT_80331728;
extern float FLOAT_8033172c;
extern float FLOAT_80331668;
extern float FLOAT_80331740;
extern float FLOAT_80331744;
extern float FLOAT_80331768;
extern float FLOAT_80331414;
extern float FLOAT_80331468;
extern float FLOAT_80331404;
extern float FLOAT_80331490;
extern float FLOAT_80331498;
extern float FLOAT_803314d8;
extern float FLOAT_803314dc;
extern float FLOAT_803314e0;
extern float FLOAT_803314e8;
extern float FLOAT_803314f0;
extern float FLOAT_803314f8;
extern float FLOAT_803314fc;
extern float FLOAT_80331500;
extern float FLOAT_80331554;
extern float FLOAT_80331548;
extern float FLOAT_8033154C;
extern float FLOAT_80331550;
extern float FLOAT_80331558;
extern float FLOAT_8033155C;
extern float FLOAT_80331560;
extern float FLOAT_80331564;
extern float FLOAT_80331568;
extern float FLOAT_80331578;
extern float FLOAT_80331594;
extern float FLOAT_803315b4;
extern float FLOAT_803315B8;
extern float FLOAT_803315BC;
extern float FLOAT_803315C8;
extern float FLOAT_8033158C;
extern float FLOAT_803315E0;
extern float FLOAT_803315E4;
extern float FLOAT_803315E8;
extern float FLOAT_80331778;
extern float FLOAT_8033177c;
extern float FLOAT_80331780;
extern float FLOAT_803317b8;
extern float FLOAT_803317bc;
extern float FLOAT_803317c0;
extern float FLOAT_803317c4;
extern float FLOAT_803317c8;
extern float FLOAT_803317cc;
extern float FLOAT_803317D0;
extern float FLOAT_803314a4;
extern float FLOAT_8033166C;
extern float FLOAT_80331680;
extern float FLOAT_80331684;
extern float FLOAT_80331688;
extern double DOUBLE_803316C0;
extern float FLOAT_803316C8;
extern float FLOAT_803316CC;
extern float FLOAT_803316d0;
extern double DOUBLE_80331418;
extern double DOUBLE_80331488;
extern double DOUBLE_80331438;
extern double DOUBLE_80331448;
extern double DOUBLE_80331450;
extern double DOUBLE_80331460;
extern double DOUBLE_803314E8;
extern double DOUBLE_80331498;
extern double DOUBLE_80331510;
extern double DOUBLE_80331580;
extern double DOUBLE_803315A0;
extern double DOUBLE_803315A8;
extern double DOUBLE_803315C0;
extern double DOUBLE_803315D8;
extern double DOUBLE_803315F0;
extern double DOUBLE_803315F8;
extern double DOUBLE_80331600;
extern double DOUBLE_80331608;
extern double DOUBLE_80331628;
extern double DOUBLE_80331630;
extern double DOUBLE_80331670;
extern double DOUBLE_80331678;
extern double DOUBLE_80331420;
extern double DOUBLE_80331428;
extern double DOUBLE_803314a8;
extern double DOUBLE_803314A8;
extern double DOUBLE_803314d0;
extern double DOUBLE_803314f0;
extern double DOUBLE_80331490;
extern double DOUBLE_80331508;
extern double DOUBLE_80331538;
extern double DOUBLE_80331540;
extern double DOUBLE_80331570;
extern double DOUBLE_803316d8;
extern double DOUBLE_803316e0;
extern double DOUBLE_803316e8;
extern double DOUBLE_80331720;
extern double DOUBLE_80331730;
extern double DOUBLE_80331738;
extern double DOUBLE_80331770;
extern double DOUBLE_80331788;
extern double DOUBLE_80331790;
extern double DOUBLE_80331798;
extern double DOUBLE_803317A0;
extern double DOUBLE_803317A8;
extern double DOUBLE_803317B0;
extern float FLOAT_803317e0;
extern float FLOAT_803317e4;
extern float FLOAT_803317e8;
extern double DOUBLE_803313f8;
extern double DOUBLE_803313F8;
extern double DOUBLE_80331408;
extern double DOUBLE_803314e8;
extern unsigned int s_wmWorldParamPrimaryDirtyMask;
extern unsigned int s_wmWorldParamSecondaryDirtyMask;
extern char s_wmCharaAnimStand[6];
extern char s_wmCharaAnimWalk[5];
extern char s_wmCharaAnimRun[4];
extern char s_wmCharaAnimGlad[5];
extern char s_wmCharaAnimSleep[6];
extern char s_wmCharaAnimAngry[6];
const char* s_wmEmptyCreatingTextEn_8032E8F0[] = {s_Empty_803313A4, s_Creating_801DC250};
const char* s_wmEmptyCreatingTextDe_8032E8F8[] = {s_Frei_803313AC, s_Wird_kreiert_801DC25C};
const char* s_wmEmptyCreatingTextIt_8032E900[] = {s_Vuoto_803313B4, s_Creazione_801DC26C};
const char* s_wmEmptyCreatingTextFr_8032E908[] = {s_Vide_803313BC, s_Creation_801DC27C};
const char* s_wmEmptyCreatingTextEs_8032E910[] = {s_Vacio_803313C4, s_Creando_801DC288};
int gWmLifeYOffsetSplineCount = 3;
float* gWmLifeYOffsetSpline = gWmLifeYOffsetSplinePoints;
extern "C" const char s_wm_menu_cpp[] = "wm_menu.cpp";
static const char s_SetCMakeEnd_chan_pctd_cur_pctd_801DC3B4[] = "SetCMakeEnd : chan = %d  cur = %d\n";
static const char s_chan_pctd_cur_pctd_801DC3D8[] = "chan = %d  cur = %d\n";
static const char s_ClrCMakeFlg_chan_pctd_cur_pctd_801DC390[] = "ClrCMakeFlg : chan = %d  cur = %d\n";
static const char s__s__d___Error_WM_menu_no_error___801dc424[] = "%s(%d): Error:WM menu no error(%d)\n";
static const char s__s__d___Error_function_code_not_f_801dc3ec[] = "%s(%d): Error:function code not found(%d)\n";
static const char s_dvd_movie_ffcc_op_thp_801dc448[] = "dvd_movie/ffcc_op.thp";
static const char s_mount____s_801dc460[] = "mount : %s";
static const char s_TRUE_803317EC[] = "TRUE";
static const char s_FALSE_803317F4[] = "FALSE";

static const int kMcListEntrySize = 0x48;
static const int kMcListCount = 4;
static const unsigned short s_wmLoadCharaModels[] = {
    0x006E, 0x0034, 0x007F, 0x0043, 0x0042, 0x0049, 0x002A, 0x0025,
    0x0055, 0x0057, 0x0056, 0x0058, 0x0059, 0x0024, 0x005A, 0x005C,
    0x005D, 0x0064, 0x0064, 0x0064, 0x0064, 0x0043, 0x0012, 0x0013,
    0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x0064,
};
static const float s_MainMenuSubFrameWidths[5] = {264.0f, 264.0f, 264.0f, 264.0f, 264.0f};
static Vec s_RingOrgPos;
static Vec s_MMenuPos[5];

struct WmMenuLightTable
{
	int m_diffuseCount;
	_GXColor m_ambient;
	_GXColor m_diffuseColors[3];
	Vec m_diffuseDirs[3];
};

extern "C" WmMenuLightTable gWmMenuLightTables[];

#define WM_MENU_EVAL_SPLINE(result, wmTblArg, wmCntArg, wmTimeArg)                                      \
	do {                                                                                       \
		SplineTable wmSpline;                                                                  \
		SplineTable* wmSplinePtr = &wmSpline;                                                  \
		wmSpline.count = (wmCntArg);                                                              \
		wmSpline.data = (wmTblArg);                                                               \
		result = FLOAT_803313dc;                                                               \
		if ((wmTimeArg) >= wmSplinePtr->data[wmSplinePtr->count * 4 - 4]) {                                 \
			result = wmSplinePtr->data[wmSplinePtr->count * 4 - 3];                                     \
		} else {                                                                               \
			float* wmSplineTable = wmSplinePtr->data;                                              \
			int wmSplineIndex;                                                                 \
			for (wmSplineIndex = 0; wmSplineIndex < wmSplinePtr->count;                            \
			     wmSplineTable += 4, wmSplineIndex++) {                                        \
				if ((wmTimeArg) <= *wmSplineTable) {                                                \
					if (wmSplineIndex == 0) {                                                  \
						result = wmSplinePtr->data[wmSplineIndex * 4 + 1];                          \
					} else {                                                                   \
						float* wmSplineCur = wmSplinePtr->data + wmSplineIndex * 4;                 \
						float* wmSplinePrev = wmSplinePtr->data + (wmSplineIndex - 1) * 4;          \
						float wmSplineDt = *wmSplineCur - *wmSplinePrev;                       \
						float wmSplineU = ((wmTimeArg) - *wmSplinePrev) / wmSplineDt;               \
						float wmSplineU2 = wmSplineU * wmSplineU;                              \
						float wmSplineU3 = wmSplineU2 * wmSplineU;                             \
						result = wmSplineDt *                                                   \
						             (wmSplinePrev[3] *                                       \
						                  (wmSplineU + (wmSplineU3 -                           \
						                                FLOAT_803314c8 * wmSplineU2)) +        \
						              wmSplineCur[2] * (wmSplineU3 - wmSplineU2)) +            \
						         (wmSplinePrev[1] *                                            \
						              (FLOAT_803313e8 +                                       \
						               (FLOAT_803314c8 * wmSplineU3 - FLOAT_803314c4 *         \
						                                                 wmSplineU2)) +         \
						          wmSplineCur[1] *                                             \
						              (FLOAT_803314cc * wmSplineU3 + FLOAT_803314c4 *          \
						                                                 wmSplineU2));          \
					}                                                                          \
					break;                                                                     \
				}                                                                              \
			}                                                                                  \
		}                                                                                      \
	} while (0)

struct WmCharaSelectEntry
{
	int m_padType;                   // 0x00
	short m_currentSlot;             // 0x04
	short m_displaySlot;             // 0x06
	unsigned short m_disconnectTime; // 0x08
	unsigned char m_confirmed;       // 0x0A
	unsigned char m_cmakePending;    // 0x0B
	unsigned char m_cmakeReady;      // 0x0C
	unsigned char m_connected;       // 0x0D
	unsigned short _pad0E;           // 0x0E
};

STATIC_ASSERT(sizeof(WmCharaSelectEntry) == 0x10);

static const int kWmMenuPlayerCount = 8;
static const int kWmMenuControllerCount = 4;
static const int kWmCharaSelectCount = kWmMenuPlayerCount;
static const int kWmCharaSelectBytes = sizeof(WmCharaSelectEntry) * kWmCharaSelectCount;
static const int kWmFrameInfoBytes = 0x3C;
static const int kWmMenuCharaStateBytes = 0x120;

struct GbaCMakeInfoRaw
{
	unsigned char m_active;        // 0x00
	unsigned char m_commandType;   // 0x01
	unsigned short m_packetCount;  // 0x02
	short m_crc;                   // 0x04
	signed char m_channelSlot;     // 0x06
	char m_name[17];               // 0x07
	unsigned char m_charaType;     // 0x18
	unsigned char m_birthMonth;    // 0x19
	unsigned char m_birthDay;      // 0x1A
	unsigned char m_favoriteBits[4]; // 0x1B
	unsigned char m_jobType;       // 0x1F
};

STATIC_ASSERT(sizeof(GbaCMakeInfoRaw) == 0x20);

static inline WmCharaSelectEntry* GetWmCharaSelectEntries(CMenuPcs* menu)
{
	return reinterpret_cast<WmCharaSelectEntry*>(menu->m_wm.m_charaSelectData);
}

static inline unsigned char* GetWmMenuCharaState(CMenuPcs* menu)
{
	return menu->m_wmCharaState;
}

static inline unsigned char* GetWmCharaModelData(CMenuPcs* menu)
{
	return menu->m_wm.m_charaModelData;
}

static inline CCharaPcs::CHandle** GetWmCharaHandles(CMenuPcs* menu)
{
	return menu->m_wm.m_handles + 0x20;
}

static inline CCharaPcs::CHandle** GetWmWorldHandles(CMenuPcs* menu)
{
	return menu->m_wm.m_handles;
}

static inline int* GetWmCharaAnimState(CMenuPcs* menu)
{
	return menu->m_wmCharaAnimState;
}

static inline WmWorldState* GetWmWorldState(CMenuPcs* menu)
{
	return menu->m_wmWorldState;
}

static inline unsigned char* GetWmCmakeWork(CMenuPcs* menu)
{
	return menu->m_cmakeWorkActive == 1 ? menu->m_cmakeWork : 0;
}

static inline int GetWmMenuFade(short state, short frame)
{
	if (state == 1) {
		return static_cast<int>(FLOAT_80331458 * static_cast<float>(DOUBLE_803314E8 * (static_cast<double>(frame) - DOUBLE_80331408)));
	}
	if (state == 2) {
		return static_cast<int>(FLOAT_80331458);
	}
	return static_cast<int>(FLOAT_80331458 * static_cast<float>(-(DOUBLE_803314E8 * (static_cast<double>(frame) - DOUBLE_80331408) - DOUBLE_80331420)));
}

static inline CFont* GetWmFont(CMenuPcs* menu)
{
	return *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(menu) + 0xF8);
}

static inline void CalcWmFrame0Inline(CMenuPcs* menu, int param)
{
#define frame (menu->m_wm.m_frameInfo)

	*reinterpret_cast<short*>(frame + 4) = 0x10;
	int frameAddr = reinterpret_cast<int>(frame);
	*reinterpret_cast<short*>(frameAddr + 0x20) =
	    static_cast<short>(static_cast<int>(FLOAT_803313e0 - static_cast<float>(
	                                            static_cast<int>(*reinterpret_cast<short*>(frameAddr + 8)) +
	                                            static_cast<int>(*reinterpret_cast<short*>(frameAddr + 4)))));

	if (param < 0) {
		float offset = static_cast<float>(static_cast<int>(*reinterpret_cast<short*>(frame + 8)) +
		                                  static_cast<int>(*reinterpret_cast<short*>(frame + 4)));
		if (param >= -10) {
			int sign = param >> 31;
			unsigned int absParam = static_cast<unsigned int>((param ^ sign) - sign);
			float scaledOffset = offset * static_cast<float>(DOUBLE_803314E8 * static_cast<double>(static_cast<int>(absParam)));
			if (static_cast<int>(absParam) < 0) {
				absParam = 0;
			}
			if (static_cast<int>(absParam) > 10) {
				absParam = 10;
			}
			float tClamped = static_cast<float>(static_cast<int>(absParam));
			offset = scaledOffset * static_cast<float>(sin(static_cast<double>(FLOAT_803314bc * tClamped * FLOAT_803316d4)));
		}
		*reinterpret_cast<short*>(frame + 4) =
		    static_cast<short>(static_cast<int>(static_cast<float>(static_cast<int>(*reinterpret_cast<short*>(frame + 4))) - offset));
		*reinterpret_cast<short*>(frame + 0x20) =
		    static_cast<short>(static_cast<int>(static_cast<float>(static_cast<int>(*reinterpret_cast<short*>(frame + 0x20))) + offset));
	}
#undef frame
}

static inline void QueueWmCharaAnimState(CMenuPcs* menu, int slot, int state)
{
	if (slot < 0 || slot >= kWmMenuPlayerCount) {
		return;
	}
	GetWmCharaAnimState(menu)[slot * 5 + 1] = state;
}

static void releaseRefCounted(void** refObj)
{
	if (refObj == 0 || *refObj == 0) {
		return;
	}
	CRef* const obj = reinterpret_cast<CRef*>(*refObj);
	if (obj->DecRef() == 0) {
		delete obj;
	}
	*refObj = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80102e9c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMenuPcs::EffectInfo::EffectInfo()
{
}

/*
 * --INFO--
 * PAL Address: 0x80102ed8
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::WmInit()
{
	float initValue = FLOAT_803313dc;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	m_wm.m_worldObjData = 0;
	m_wm.m_bubbleData = 0;
	m_wm.m_frameData = 0;
	m_wm.m_frameInfo = 0;
	m_wm.m_charaModelData = 0;
	m_wm.m_charaSelectData = 0;
	m_wmWorldState = 0;
	m_wmCharaState = 0;
	m_wmWorldParams = 0;
	m_effectWork = 0;
	m_wmWorkBuffer = 0;
	FLOAT_8032ee18 = initValue;
	m_wmThpActive = 0;
	m_textureLocIndex = 0;
	memset(bytes + 4, 0, 0x1C);
	bytes[0xD] = 0;
	bytes[0x10] = 0;
	bytes[0x12] = 0;
	bytes[0x13] = 0;
	bytes[0xD] = 1;
	bytes[0x16] = 0;
	gWmMenuCursorX[0] = 0xFF;
	gWmMenuCursorX[1] = 0xFF;
	gWmMenuCursorY[0] = 0xFF;
	gWmMenuCursorY[1] = 0xFF;
	gWmMenuWorkB = -1;
	gWmMenuWorkA = -1;
	int scriptValue = *reinterpret_cast<int*>(&Game.m_gameWork.m_scriptSysVal0);
	gWmMenuScriptValueCache = scriptValue;
	if (scriptValue > 99) {
		gWmMenuScriptValueCache = 100;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80102ed4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::createWorld()
{
	return;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChkNumItemAll()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int total = 0;

	unsigned char* const list = m_wmWorkBuffer;
	if (list != 0) {
		for (int i = 0; i < kMcListCount; i++) {
			unsigned char* const entry = list + i * kMcListEntrySize;
			if (entry[0x43] == 0 && entry[0x41] != 0 && entry[0x42] == 0) {
				total++;
			}
		}
	}

	int selected = 0;
	unsigned char* const modelData = m_wm.m_charaModelData;
	if (modelData != 0) {
		for (int i = 0; i < kWmMenuPlayerCount; i++) {
			if (modelData[i * 0x34 + 0xC] != 0) {
				selected++;
			}
		}
	}

	bytes[0x10] = static_cast<unsigned char>(selected != 0);
	gWmMenuWorkA = total + selected;
}

/*
 * --INFO--
 * PAL Address: 0x8010172c
 * PAL Size: 6000b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::loadData()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	char* const rodataBase = lbl_801DB7F8;
#define srcFile (rodataBase + 0xC20)
	m_menuResultCode = 0;
	GbaQue.SetControllerMode(1);
	loadTexture(lbl_80210B74, 2, 3, lbl_80210B98, 0x16, 0x2F, 0);

	m_wm.m_handles[0x00] = 0;
	m_wm.m_handles[0x01] = 0;
	m_wm.m_handles[0x02] = 0;
	m_wm.m_handles[0x03] = 0;
	m_wm.m_handles[0x04] = 0;
	m_wm.m_handles[0x05] = 0;
	m_wm.m_handles[0x06] = 0;
	m_wm.m_handles[0x07] = 0;
	m_wm.m_handles[0x08] = 0;
	m_wm.m_handles[0x09] = 0;
	m_wm.m_handles[0x0A] = 0;
	m_wm.m_handles[0x0B] = 0;
	m_wm.m_handles[0x0C] = 0;
	m_wm.m_handles[0x0D] = 0;
	m_wm.m_handles[0x0E] = 0;
	m_wm.m_handles[0x0F] = 0;
	m_wm.m_handles[0x10] = 0;
	m_wm.m_handles[0x11] = 0;
	m_wm.m_handles[0x12] = 0;
	m_wm.m_handles[0x13] = 0;
	m_wm.m_handles[0x14] = 0;
	m_wm.m_handles[0x15] = 0;
	m_wm.m_handles[0x16] = 0;
	m_wm.m_handles[0x17] = 0;
	m_wm.m_handles[0x18] = 0;
	m_wm.m_handles[0x19] = 0;
	m_wm.m_handles[0x1A] = 0;
	m_wm.m_handles[0x1B] = 0;
	m_wm.m_handles[0x1C] = 0;
	m_wm.m_handles[0x1D] = 0;
	m_wm.m_handles[0x1E] = 0;
	m_wm.m_handles[0x1F] = 0;
	m_wm.m_handles[0x20] = 0;
	m_wm.m_handles[0x21] = 0;
	m_wm.m_handles[0x22] = 0;
	m_wm.m_handles[0x23] = 0;
	m_wm.m_handles[0x24] = 0;
	m_wm.m_handles[0x25] = 0;
	m_wm.m_handles[0x26] = 0;
	m_wm.m_handles[0x27] = 0;

	const short* charaNoTable = reinterpret_cast<const short*>(rodataBase + 0x970);
	const short* const charaNoDefault = charaNoTable + 21;
	for (int i = 0; i < 0x28; i++, charaNoTable++) {
		m_wm.m_handles[i] = new (MenuPcs.m_menuStage, srcFile, 0x1F4) CCharaPcs::CHandle;
		m_wm.m_handles[i]->Add();

		int charaKind;
		unsigned long charaNo;
		if (i < 0x20) {
			CharaPcs.m_charaAllocStage = 1;
			charaKind = 3;
			charaNo = *charaNoTable;
		} else {
			CCaravanWork& caravan = Game.m_caravanWorkArr[i - 0x20];
			CharaPcs.m_charaAllocStage = 0;
			if (caravan.m_shopState != 0) {
				charaKind = 0;
				charaNo = caravan.m_tribeId * 200 + 100;
				unsigned short variant = caravan.m_appearanceVariant;
				int gender = caravan.m_genderFlag;
				if (gender != 0) {
					charaNo += 100;
				}
				charaNo += variant;
			} else {
				charaKind = 3;
				charaNo = *charaNoDefault;
			}
		}

		m_wm.m_handles[i]->LoadModel(charaKind, charaNo, 0, 0, -1, 0, 0);
		m_wm.m_handles[i]->m_flags |= 0x141;
	}
	CharaPcs.m_charaAllocStage = 0;
	*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(m_wm.m_handles[6]->m_model) + 0x9C) =
	    FLOAT_803314B0;

	m_wm.m_worldObjData = static_cast<unsigned char*>(operator new[](0xC80, MenuPcs.m_menuStage, srcFile, 0x214));
	{
		const float bigF = FLOAT_80331598;
		const float oneF = FLOAT_803313e8;
		const float zeroF = FLOAT_803313dc;
		for (int i = 0; i < 0x28; i++) {
			unsigned char* const entry = m_wm.m_worldObjData + i * 0x50 + 0x1C;
			*reinterpret_cast<float*>(entry + 0x08) = zeroF;
			*reinterpret_cast<float*>(entry + 0x04) = zeroF;
			*reinterpret_cast<float*>(entry + 0x00) = zeroF;
			*reinterpret_cast<float*>(entry + 0x14) = zeroF;
			*reinterpret_cast<float*>(entry + 0x10) = zeroF;
			*reinterpret_cast<float*>(entry + 0x0C) = zeroF;
			*reinterpret_cast<float*>(entry + 0x20) = oneF;
			*reinterpret_cast<float*>(entry + 0x1C) = oneF;
			*reinterpret_cast<float*>(entry + 0x18) = oneF;
			*reinterpret_cast<int*>(m_wm.m_worldObjData + i * 0x50 + 0x00) = 0;
			*reinterpret_cast<int*>(m_wm.m_worldObjData + i * 0x50 + 0x04) = 0;
			*reinterpret_cast<short*>(m_wm.m_worldObjData + i * 0x50 + 0x08) = 0;
			*reinterpret_cast<short*>(m_wm.m_worldObjData + i * 0x50 + 0x0A) = 0;
			*reinterpret_cast<short*>(m_wm.m_worldObjData + i * 0x50 + 0x0C) = 0x280;
			*reinterpret_cast<short*>(m_wm.m_worldObjData + i * 0x50 + 0x0E) = 0x1C0;
			*reinterpret_cast<float*>(m_wm.m_worldObjData + i * 0x50 + 0x10) = zeroF;
			*reinterpret_cast<float*>(m_wm.m_worldObjData + i * 0x50 + 0x14) = zeroF;
			*reinterpret_cast<float*>(m_wm.m_worldObjData + i * 0x50 + 0x18) = bigF;
			*reinterpret_cast<int*>(m_wm.m_worldObjData + i * 0x50 + 0x40) = 0;
			*reinterpret_cast<int*>(m_wm.m_worldObjData + i * 0x50 + 0x44) = 0;
			*reinterpret_cast<int*>(m_wm.m_worldObjData + i * 0x50 + 0x48) = 0x280;
			*reinterpret_cast<int*>(m_wm.m_worldObjData + i * 0x50 + 0x4C) = 0x1C0;
		}
	}

	m_wm.m_bubbleData =
	    static_cast<unsigned char*>(operator new(0x8C, MenuPcs.m_menuStage, srcFile, 0x227));
	memset(m_wm.m_bubbleData, 0, 0x8C);

	m_wm.m_frameData =
	    static_cast<unsigned char*>(operator new(0xEC, MenuPcs.m_menuStage, srcFile, 0x22B));
	memset(m_wm.m_frameData, 0, 0xEC);
	{
		int frameSrc[20];
		unsigned int* dst = reinterpret_cast<unsigned int*>(frameSrc) - 1;
		unsigned int* src = reinterpret_cast<unsigned int*>(rodataBase + 0x9BC);
		unsigned int* const srcEnd = src + 20;
		while (src != srcEnd) {
			unsigned int lo = src[1];
			src += 2;
			unsigned int hi = *src;
			dst[1] = lo;
			dst += 2;
			*dst = hi;
		}
		const float oneF = FLOAT_803313e8;

		int wordSrc[10];
		wordSrc[0] = *reinterpret_cast<int*>(rodataBase + 0xA10);
		wordSrc[1] = *reinterpret_cast<int*>(rodataBase + 0xA14);
		wordSrc[2] = *reinterpret_cast<int*>(rodataBase + 0xA18);
		wordSrc[3] = *reinterpret_cast<int*>(rodataBase + 0xA1C);
		wordSrc[4] = *reinterpret_cast<int*>(rodataBase + 0xA20);
		wordSrc[5] = *reinterpret_cast<int*>(rodataBase + 0xA24);
		wordSrc[6] = *reinterpret_cast<int*>(rodataBase + 0xA28);
		wordSrc[7] = *reinterpret_cast<int*>(rodataBase + 0xA2C);
		wordSrc[8] = *reinterpret_cast<int*>(rodataBase + 0xA30);
		wordSrc[9] = *reinterpret_cast<int*>(rodataBase + 0xA34);

		int* tbl = frameSrc;
		float* wsrc = reinterpret_cast<float*>(wordSrc);
		for (int i = 0, count = 5; count != 0; count--, i += 0x1C) {
			*reinterpret_cast<short*>(m_wm.m_frameData + i + 0xC) = static_cast<short>(tbl[0]);
			*reinterpret_cast<short*>(m_wm.m_frameData + i + 0xE) = static_cast<short>(tbl[1]);
			*reinterpret_cast<short*>(m_wm.m_frameData + i + 0x10) = static_cast<short>(tbl[2]);
			*reinterpret_cast<short*>(m_wm.m_frameData + i + 0x12) = static_cast<short>(tbl[3]);
			*reinterpret_cast<float*>(m_wm.m_frameData + i + 0x14) = wsrc[0];
			*reinterpret_cast<float*>(m_wm.m_frameData + i + 0x18) = wsrc[1];
			*reinterpret_cast<float*>(m_wm.m_frameData + i + 0x1C) = oneF;
			*reinterpret_cast<float*>(m_wm.m_frameData + i + 0x20) = oneF;
			*reinterpret_cast<int*>(m_wm.m_frameData + i + 0x24) = 0;
			tbl += 4;
			wsrc += 2;
		}
	}

	m_wm.m_frameInfo =
	    static_cast<unsigned char*>(operator new(kWmFrameInfoBytes, MenuPcs.m_menuStage, srcFile, 0x231));
	memset(m_wm.m_frameInfo, 0, kWmFrameInfoBytes);
	*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x4) = 0x10;
	{
		const float oneF = FLOAT_803313e8;
		const float zeroF = FLOAT_803313dc;
		*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x6) = 0x10;
		*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x8) = 0xE8;
		*reinterpret_cast<short*>(m_wm.m_frameInfo + 0xA) = 0x168;
		*reinterpret_cast<float*>(m_wm.m_frameInfo + 0xC) = zeroF;
		*reinterpret_cast<float*>(m_wm.m_frameInfo + 0x10) = zeroF;
		*reinterpret_cast<float*>(m_wm.m_frameInfo + 0x14) = oneF;
		*reinterpret_cast<float*>(m_wm.m_frameInfo + 0x18) = oneF;
		*reinterpret_cast<int*>(m_wm.m_frameInfo + 0x1C) = 0;
	}
	{
		unsigned char* const frame = m_wm.m_frameInfo;
		*reinterpret_cast<short*>(frame + 0x20) = *reinterpret_cast<short*>(frame + 0x4);
		*reinterpret_cast<short*>(frame + 0x22) = *reinterpret_cast<short*>(frame + 0x6);
		*reinterpret_cast<short*>(frame + 0x24) = *reinterpret_cast<short*>(frame + 0x8);
		*reinterpret_cast<short*>(frame + 0x26) = *reinterpret_cast<short*>(frame + 0xA);
		*reinterpret_cast<float*>(frame + 0x28) = *reinterpret_cast<float*>(frame + 0xC);
		*reinterpret_cast<float*>(frame + 0x2C) = *reinterpret_cast<float*>(frame + 0x10);
		*reinterpret_cast<float*>(frame + 0x30) = *reinterpret_cast<float*>(frame + 0x14);
		*reinterpret_cast<float*>(frame + 0x34) = *reinterpret_cast<float*>(frame + 0x18);
		*reinterpret_cast<int*>(frame + 0x38) = *reinterpret_cast<int*>(frame + 0x1C);
	}
	{
		unsigned char* const frame = m_wm.m_frameInfo;
		*reinterpret_cast<short*>(frame + 0x20) = static_cast<short>(
		    0x280 - (*reinterpret_cast<short*>(frame + 0x8) + *reinterpret_cast<short*>(frame + 0x4)));
	}
	*reinterpret_cast<int*>(m_wm.m_frameInfo + 0x38) = 8;

	m_wm.m_charaModelData =
	    static_cast<unsigned char*>(operator new[](0x1A0, MenuPcs.m_menuStage, srcFile, 0x237));
	{
		const float zeroF = FLOAT_803313dc;
		const float oneF = FLOAT_803313e8;
		for (int i = 0, count = 8; count != 0; count--, i += 0x34) {
			*reinterpret_cast<int*>(m_wm.m_charaModelData + i + 0x00) = 0;
			*reinterpret_cast<int*>(m_wm.m_charaModelData + i + 0x04) = 0;
			*reinterpret_cast<int*>(m_wm.m_charaModelData + i + 0x08) = 0;
			*reinterpret_cast<unsigned char*>(m_wm.m_charaModelData + i + 0x0C) = 0;
			float* const a = reinterpret_cast<float*>(m_wm.m_charaModelData + i + 0x10);
			a[2] = zeroF;
			a[1] = zeroF;
			a[0] = zeroF;
			a[5] = zeroF;
			a[4] = zeroF;
			a[3] = zeroF;
			a[8] = oneF;
			a[7] = oneF;
			a[6] = oneF;
		}
	}

	InitCharaInfo();

	m_wm.m_charaSelectData =
	    static_cast<unsigned char*>(operator new[](kWmCharaSelectBytes, MenuPcs.m_menuStage, srcFile, 0x243));

	m_wmWorldState =
	    static_cast<WmWorldState*>(operator new(sizeof(WmWorldState), MenuPcs.m_menuStage, srcFile, 0x246));
	memset(m_wmWorldState, 0, sizeof(WmWorldState));

	m_wmCharaState =
	    static_cast<unsigned char*>(operator new[](kWmMenuCharaStateBytes, MenuPcs.m_menuStage, srcFile, 0x24A));
	memset(m_wmCharaState, 0, kWmMenuCharaStateBytes);

	m_wmWorldParams =
	    static_cast<unsigned char*>(operator new(0x10, MenuPcs.m_menuStage, srcFile, 0x24E));
	memset(m_wmWorldParams, 0, 0x10);

	m_effectWork = new (MenuPcs.m_menuStage, srcFile, 0x252) EffectInfo[0x28];
	{
		for (int i = 0, count = 5; count != 0; count--, i += 0x2920) {
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 4) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 8) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x524) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x528) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x52C) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xA48) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xA4C) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xA50) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xF6C) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xF70) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xF74) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1490) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1494) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1498) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x19B4) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x19B8) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x19BC) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1ED8) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1EDC) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1EE0) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x23FC) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x2400) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x2404) = -1;
		}
	}

	m_wmCharaAnimState =
	    static_cast<int*>(operator new[](0xA0, MenuPcs.m_menuStage, srcFile, 0x25A));
	memset(m_wmCharaAnimState, 0, 0xA0);

	m_menuWindowInfo = new (MenuPcs.m_menuStage, srcFile, 0x25E) MenuWindowInfo;
	memset(m_menuWindowInfo, 0, sizeof(MenuWindowInfo));

	// Re-initialize the effect work entries.
	{
		for (int i = 0, count = 5; count != 0; count--, i += 0x2920) {
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 4) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 8) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x528) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x52C) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x524) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xA4C) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xA50) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xA48) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xF70) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xF74) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0xF6C) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1494) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1498) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1490) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x19B8) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x19BC) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x19B4) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1EDC) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1EE0) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x1ED8) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x2400) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x2404) = -1;
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_effectWork) + i + 0x23FC) = -1;
		}
	}

	bytes[0x86E] = 0;
	bytes[0x858] = 0;
	*reinterpret_cast<int*>(bytes + 0x854) = 0;
	memset(m_wm.m_charaSelectData, 0, 0x80);

	// Assign chara-select party slots from the backed-up world state.
	{
		signed char usedMask = 0;
		for (int i = 0, j = 0, count = 2; count != 0; count--, i += 0x20, j += 4) {
			m_wm.m_charaSelectData[i + 0x0C] = 0;
			m_wm.m_charaSelectData[i + 0x0B] = 0;
			m_wm.m_charaSelectData[i + 0x0A] = 0;
			int slotA = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_wmWorldState) + j + 0x3E);
			if (slotA < 0) {
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + i + 4) = -1;
			} else {
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + i + 4) = static_cast<short>(slotA);
				usedMask = static_cast<signed char>(usedMask | (1 << slotA));
			}
			m_wm.m_charaSelectData[i + 0x1C] = 0;
			m_wm.m_charaSelectData[i + 0x1B] = 0;
			m_wm.m_charaSelectData[i + 0x1A] = 0;
			int slotB = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_wmWorldState) + j + 0x40);
			if (slotB < 0) {
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + i + 0x14) = -1;
			} else {
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + i + 0x14) = static_cast<short>(slotB);
				usedMask = static_cast<signed char>(usedMask | (1 << slotB));
			}
		}
		for (int i = 0, count = 4; count != 0; count--, i += 0x10) {
			if (*reinterpret_cast<short*>(m_wm.m_charaSelectData + i + 4) < 0) {
				int freeSlot;
				for (freeSlot = 0; freeSlot < 8; freeSlot++) {
					if ((usedMask & (1 << freeSlot)) == 0) {
						break;
					}
				}
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + i + 4) = static_cast<short>(freeSlot);
				usedMask = static_cast<signed char>(usedMask | (1 << freeSlot));
			}
			unsigned char* const entry = m_wm.m_charaSelectData + i;
			*reinterpret_cast<short*>(entry + 6) = *reinterpret_cast<short*>(entry + 4);
		}
	}

	SetManaWaterEffect();
	m_crystalPart = -1;
	m_crystalAttr = -1;
	SetCrystalCageAttr();

	// Crystal cage effect (effect slot 7, effect no 9).
	{
		PPPCREATEPARAM titleParam;
		unsigned char* const effectBase = reinterpret_cast<unsigned char*>(m_effectWork);
		*reinterpret_cast<int*>(effectBase + 0x23FC) = 9;
		CGObject* const titleObject = reinterpret_cast<CGObject*>(effectBase + 0x2408);
		*reinterpret_cast<int*>(effectBase + 0x2404) = 7;
		titleObject->Create();
		titleObject->m_charaModelHandle =
		    *reinterpret_cast<CCharaPcs::CHandle**>(bytes + 0x790);
		titleParam.m_paramB = reinterpret_cast<unsigned int>(titleObject);
		titleParam.m_lookTargetPtr = titleObject;
		*reinterpret_cast<unsigned int*>(effectBase + 0x2400) =
		    PartMng.pppCreate(0, 9, &titleParam, 1);
	}

	for (int i = 0; i < 4; i++) {
		PPPCREATEPARAM param;
		const int slot = i + 8;
		unsigned int* effect =
		    reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(m_effectWork) + slot * 0x524);
		if (slot == 5 && i + 5 < 0x13) {
			effect += 0x149;
		} else if (i + 8 >= 0x11 && i + 8 <= 0x14 && i + 5 > 0x19) {
			effect += 0x149 * 4;
		}
		const int group = static_cast<int>(effect[0] = i + 5) > 100;
		CGObject* const object = reinterpret_cast<CGObject*>(effect + 3);
		effect[2] = i + 8;
		object->Create();
		object->m_charaModelHandle = m_wm.m_handles[slot];
		param.m_paramB = reinterpret_cast<unsigned int>(object);
		param.m_lookTargetPtr = object;
		effect[1] = PartMng.pppCreate(group, i + 5, &param, 1);
	}

	for (int i = 0; i < 5; i++) {
		PPPCREATEPARAM param;
		const int slot = i + 0xC;
		unsigned int* effect =
		    reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(m_effectWork) + slot * 0x524);
		if (slot == 5 && i < 0x13) {
			effect += 0x149;
		} else if (i + 0xC >= 0x11 && i + 0xC <= 0x14 && i > 0x19) {
			effect += 0x149 * 4;
		}
		const int group = static_cast<int>(effect[0] = i) > 100;
		CGObject* const object = reinterpret_cast<CGObject*>(effect + 3);
		effect[2] = i + 0xC;
		object->Create();
		object->m_charaModelHandle = m_wm.m_handles[slot];
		param.m_paramB = reinterpret_cast<unsigned int>(object);
		param.m_lookTargetPtr = object;
		effect[1] = PartMng.pppCreate(group, i, &param, 1);
	}

	for (int i = 0; i < 4; i++) {
		PPPCREATEPARAM param;
		const int slot =  (int)(unsigned int)(i + 0x20);
		unsigned int* effect =
		    reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(m_effectWork) + slot * 0x524);
		if (slot == 5 && i + 0xA < 0x13) {
			effect += 0x149;
		} else if (i + 0x20 >= 0x11 && i + 0x20 <= 0x14 && i + 0xA > 0x19) {
			effect += 0x149 * 4;
		}
		const int group = static_cast<int>(effect[0] = i + 0xA) > 100;
		CGObject* const object = reinterpret_cast<CGObject*>(effect + 3);
		effect[2] = i + 0x20;
		object->Create();
		object->m_charaModelHandle = m_wm.m_handles[slot];
		param.m_paramB = reinterpret_cast<unsigned int>(object);
		param.m_lookTargetPtr = object;
		effect[1] = PartMng.pppCreate(group, i + 0xA, &param, 1);
		if (i == 0) {
			PartPcs.GetParLocIdx(effect[1], s_RingOrgPos);
		}
	}

	FLOAT_8032ee18 = FLOAT_803317FC;
	for (int i = 0; i < 8; i++) {
		const int modelNo = (i + 1) * 100;
		CharaPcs.LoadAnim(0, modelNo, s_wmCharaAnimStand, 1, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, s_wmCharaAnimWalk, 1, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, s_wmCharaAnimRun, 1, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, s_wmCharaAnimGlad, 3, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, s_wmCharaAnimSleep, 1, 0, 0);
	}

	{
		for (int i = 0; i < 8; i++) {
			if ((*reinterpret_cast<CCharaPcs::CHandle**>(
			        reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->m_charaKind != 3) {
				const unsigned int charaBase =
				    static_cast<unsigned int>((*reinterpret_cast<CCharaPcs::CHandle**>(
				        reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->m_charaNo) /
				    100;
				const int modelNo = charaBase * 100;
				int anim = (charaBase - 1) * 6;
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))
				    ->LoadAnim(s_wmCharaAnimStand, anim++, 1, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))
				    ->LoadAnim(s_wmCharaAnimWalk, anim++, 1, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))
				    ->LoadAnim(s_wmCharaAnimRun, anim++, 1, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))
				    ->LoadAnim(s_wmCharaAnimGlad, anim++, 3, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))
				    ->LoadAnim(s_wmCharaAnimSleep, anim++, 1, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))
				    ->LoadAnim(s_wmCharaAnimAngry, anim++, 1, 0, modelNo, -1, 0);
				(m_wmCharaAnimState + i * 5)[0] = 0;
				(m_wmCharaAnimState + i * 5)[1] = -1;
				(m_wmCharaAnimState + i * 5)[2] = rand() % 250;
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))
				    ->SetAnim(anim - 6, -1, -1, 0, 0);
				reinterpret_cast<float*>(m_wmCharaAnimState)[i * 5 + 3] = *reinterpret_cast<float*>(
				    reinterpret_cast<unsigned char*>(
				        (*reinterpret_cast<CCharaPcs::CHandle**>(
				             reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))
				            ->m_model) +
				    0xB4);
				reinterpret_cast<float*>(m_wmCharaAnimState)[i * 5 + 4] = *reinterpret_cast<float*>(
				    reinterpret_cast<unsigned char*>(
				        (*reinterpret_cast<CCharaPcs::CHandle**>(
				             reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))
				            ->m_model) +
				    0xC0);
				float maxWait = static_cast<float>(*reinterpret_cast<unsigned short*>(
				    *reinterpret_cast<int*>(
				        *reinterpret_cast<int*>(
				            reinterpret_cast<unsigned char*>(
				                *reinterpret_cast<CCharaPcs::CHandle**>(
				                    reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774)) +
				            anim * 4 + 0xC) +
				        0x28) +
				    0x10));
				if (FLOAT_8032ee18 < maxWait) {
					FLOAT_8032ee18 = maxWait;
				}
			}
		}
	}

	CCharaPcs::CHandle* const windowHandle = m_wm.m_handles[1];
	windowHandle->LoadAnim(lbl_80331800, 0, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(lbl_80331808, 1, 0, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(lbl_80331810, 2, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(lbl_80331818, 3, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(lbl_80331820, 4, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(lbl_80331828, 5, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(lbl_80331830, 6, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(lbl_80331838, 7, 0, -1, -1, -1, 0);
	m_wm.m_handles[1]->SetAnim(0, -1, -1, -1, 0);

	{
#define worldState (reinterpret_cast<unsigned char*>(m_wmWorldState))
		*reinterpret_cast<short*>(worldState + 0x1C) = 0;
		*reinterpret_cast<short*>(worldState + 0x36) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[0]);
		*reinterpret_cast<short*>(worldState + 0x3E) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[0]);
		*reinterpret_cast<short*>(worldState + 0x38) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[1]);
		*reinterpret_cast<short*>(worldState + 0x40) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[1]);
		*reinterpret_cast<short*>(worldState + 0x3A) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[2]);
		*reinterpret_cast<short*>(worldState + 0x42) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[2]);
		*reinterpret_cast<short*>(worldState + 0x3C) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[3]);
		*reinterpret_cast<short*>(worldState + 0x44) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[3]);
#undef worldState
	}

	char fontPath[128];
	sprintf(fontPath, rodataBase + 0xC74, Game.GetLangString());
	loadFont(0, fontPath, 1, -1);

	bytes[0xD] = 0;
	{
		unsigned char* const worldState = reinterpret_cast<unsigned char*>(m_wmWorldState);
		bytes[0x10] = 0;
		bytes[0x12] = 0;
		bytes[0x13] = 0;
		*reinterpret_cast<short*>(worldState + 0x20) = 0;
		*reinterpret_cast<short*>(worldState + 0x1E) = 0;
		*reinterpret_cast<short*>(worldState + 0x18) = 0;
	}
	lbl_8032EE1C = 1;
	lbl_8032E8AC = 1;

	CMesMenu** const mesMenus = reinterpret_cast<CMesMenu**>(bytes + 0x11C);
	for (int i = 4; i < 6; i++) {
		mesMenus[i - 4] = new (MenuPcs.m_menuStage, srcFile, 0x2EA) CMesMenu;
		CMesMenu* const cur = mesMenus[i - 4];
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(cur) + 0x18) = i;
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(cur) + 0x1C) = i;
		(*reinterpret_cast<void (***)(CMesMenu*)>(cur))[3](cur);
	}

	char optionPath[256];
	sprintf(optionPath, rodataBase + 0xC8C, Game.GetLangString());
	CFile::CHandle* const fileHandle = File.Open(optionPath, 0, CFile::PRI_LOW);
	if (fileHandle != 0) {
		File.Read(fileHandle);
		File.SyncCompleted(fileHandle);
		CTextureSet* texSet =
		    new (MenuPcs.m_menuStage, srcFile, 0x300) CTextureSet;
		*reinterpret_cast<CTextureSet**>(bytes + 0xBC) = texSet;
		(*reinterpret_cast<CTextureSet**>(bytes + 0xBC))
		    ->Create(File.m_readBuffer, m_menuStage, 0, 0, 0, 0);
		File.Close(fileHandle);
	}

	{
		unsigned char* dst = bytes;
		for (unsigned int i = 0;
		     i < static_cast<unsigned int>(
		             reinterpret_cast<CTextureSet*>(*reinterpret_cast<CTextureSet**>(bytes + 0xBC))
		                 ->m_textureArray.GetSize());
		     i++, dst += 4) {
			*reinterpret_cast<CTexture**>(dst + 0xC0) =
			    reinterpret_cast<CTextureSet*>(*reinterpret_cast<CTextureSet**>(bytes + 0xBC))
			        ->m_textureArray[i];
		}
	}

	GetOptionData();
	bytes[0x80] = 0;
	float zeroF = FLOAT_803313dc;
	*reinterpret_cast<float*>(bytes + 0x7C) = FLOAT_803313dc;
	*reinterpret_cast<float*>(bytes + 0x78) = zeroF;
	*reinterpret_cast<short*>(bytes + 0x74) = 0;
	g_pGoOutMenu = &g_GoOutMenu;
#undef srcFile
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitFrameInfo()
{
	unsigned char* const frame = m_wm.m_frameInfo;
	if (frame != 0) {
		memset(frame, 0, 0x3C);
	}
	InitFrame0Info();
}

/*
 * --INFO--
 * PAL Address: 0x80101658
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitFrame0Info()
{
	*reinterpret_cast<unsigned short*>(m_wm.m_frameInfo + 4) = 0x10;
	float one = FLOAT_803313e8;
	float zero = FLOAT_803313dc;
	*reinterpret_cast<unsigned short*>(m_wm.m_frameInfo + 6) = 0x10;
	*reinterpret_cast<unsigned short*>(m_wm.m_frameInfo + 8) = 0xE8;
	*reinterpret_cast<unsigned short*>(m_wm.m_frameInfo + 0xA) = 0x168;
	*reinterpret_cast<float*>(m_wm.m_frameInfo + 0xC) = zero;
	*reinterpret_cast<float*>(m_wm.m_frameInfo + 0x10) = zero;
	*reinterpret_cast<float*>(m_wm.m_frameInfo + 0x14) = one;
	*reinterpret_cast<float*>(m_wm.m_frameInfo + 0x18) = one;
	*reinterpret_cast<unsigned int*>(m_wm.m_frameInfo + 0x1C) = 0;

	unsigned char* frame = m_wm.m_frameInfo;
	*reinterpret_cast<short*>(frame + 0x20) = *reinterpret_cast<short*>(frame + 4);
	*reinterpret_cast<short*>(frame + 0x22) = *reinterpret_cast<short*>(frame + 6);
	*reinterpret_cast<short*>(frame + 0x24) = *reinterpret_cast<short*>(frame + 8);
	*reinterpret_cast<short*>(frame + 0x26) = *reinterpret_cast<short*>(frame + 0xA);
	*reinterpret_cast<float*>(frame + 0x28) = *reinterpret_cast<float*>(frame + 0xC);
	*reinterpret_cast<float*>(frame + 0x2C) = *reinterpret_cast<float*>(frame + 0x10);
	*reinterpret_cast<float*>(frame + 0x30) = *reinterpret_cast<float*>(frame + 0x14);
	*reinterpret_cast<float*>(frame + 0x34) = *reinterpret_cast<float*>(frame + 0x18);
	*reinterpret_cast<unsigned int*>(frame + 0x38) = *reinterpret_cast<unsigned int*>(frame + 0x1C);

	frame = m_wm.m_frameInfo;
	*reinterpret_cast<short*>(frame + 0x20) = 0x280 - (*reinterpret_cast<short*>(frame + 8) + *reinterpret_cast<short*>(frame + 4));
	*reinterpret_cast<unsigned int*>(m_wm.m_frameInfo + 0x38) = 8;
}

/*
 * --INFO--
 * PAL Address: 0x80101444
 * PAL Size: 532b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::Sprt::operator= (const CMenuPcs::Sprt& src)
{
	memcpy(this, &src, sizeof(CMenuPcs::Sprt));
}

/*
 * --INFO--
 * PAL Address: 0x80101444
 * PAL Size: 532b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_propagation off
void CMenuPcs::InitCharaInfo()
{
	float z;
	float zero;
	int slot;
	int baseX;
	int baseSlot;
	int baseY;
	int row;
	int col;
	int y;

	zero = FLOAT_803313dc;
	z = FLOAT_803314a4;
	row = 0;
	baseSlot = 0x20;
	baseY = 0x66;
	while (row < 2) {
		slot = (baseSlot + 0);
		col = 0;
		baseX = 0x68;
		for (; col < 4; col++) {
			int __p15 = slot;
			int slotOffset = __p15 * 0x50;
			y = baseY;
			if (row != 0) {
				y = baseY + 8;
			}

			*reinterpret_cast<short*>(m_wm.m_worldObjData + slotOffset + 8) = static_cast<short>(baseX - 0xA0);
			*reinterpret_cast<short*>(m_wm.m_worldObjData + slotOffset + 0xA) = static_cast<short>(y - 0x70);
			*reinterpret_cast<unsigned short*>(m_wm.m_worldObjData + slotOffset + 0xC) = 0x140;
			*reinterpret_cast<unsigned short*>(m_wm.m_worldObjData + slotOffset + 0xE) = 0xE0;
			*reinterpret_cast<float*>(m_wm.m_worldObjData + slotOffset + 0x10) = zero;
			*reinterpret_cast<float*>(m_wm.m_worldObjData + slotOffset + 0x14) = zero;
			*reinterpret_cast<float*>(m_wm.m_worldObjData + slotOffset + 0x18) = z;

			slot += 1;
			baseX = baseX + 0x90;
		}
		row++;
		baseSlot += 4;
		baseY = baseY + 0xB8;
	}

	unsigned char* gameData = reinterpret_cast<unsigned char*>(&Game);
	int i = 0;
	int modelOffset = 0;
	unsigned int invalidModel = 0xFFFFFFFF;
	for (; i < 8; i++) {
		unsigned char* src0 = gameData + 0x13F0;
		unsigned char* entry0 = m_wm.m_charaModelData + modelOffset;
		if (*reinterpret_cast<int*>(gameData + 0x1794) != 0) {
			int modelNo = *reinterpret_cast<unsigned short*>(src0 + 0x3E0) * 200 + 100;
			int flag0 = *reinterpret_cast<unsigned short*>(src0 + 0x3E2);
			unsigned short add0  = *reinterpret_cast<unsigned short*>(src0 + 0x3E4);
			if (flag0 != 0) {
				modelNo += 100;
			}
			*reinterpret_cast<unsigned int*>(entry0 + 8) = modelNo + add0;
		} else {
			*reinterpret_cast<unsigned int*>(entry0 + 8) = invalidModel;
		}

		gameData += 0xC30;
		modelOffset += 0x34;
	}
}
#pragma opt_propagation on

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 576b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitCharaSelectInfo()
{
	unsigned char* const selectData = m_wm.m_charaSelectData;
	if (selectData != 0) {
		memset(selectData, 0, kWmCharaSelectBytes);
		for (int i = 0; i < kWmCharaSelectCount; i++) {
			unsigned char* const entry = selectData + i * 0x10;
			*reinterpret_cast<short*>(entry + 4) = static_cast<short>(i);
			*reinterpret_cast<short*>(entry + 6) = static_cast<short>(i);
			*reinterpret_cast<short*>(entry + 8) = 0;
			entry[0xA] = 0;
			entry[0xB] = 0;
			entry[0xC] = 0;
			entry[0xD] = 0;
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitCSelCurPos()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x16] = 0;
	bytes[0x17] = 0;
	bytes[0x0E] = 0;
	bytes[0x0F] = 0;
	*reinterpret_cast<short*>(bytes + 0x1A) = 0;
	gWmMenuWorkA = 0;
	gWmMenuWorkB = 0;
	gWmMenuCursorX[0] = static_cast<char>(0xFF);
	gWmMenuCursorX[1] = static_cast<char>(0xFF);
	gWmMenuCursorY[0] = static_cast<char>(0xFF);
	gWmMenuCursorY[1] = static_cast<char>(0xFF);

	WmWorldState* const worldState = m_wmWorldState;
	if (worldState != 0) {
		worldState->m_cardChannel = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80101150
 * PAL Size: 756b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::destroyWorld()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	unsigned char* puVar5 = bytes + 0x10;
	int iVar4 = 4;
	do {
		void** piVar2 = reinterpret_cast<void**>(puVar5 + 0x10C);
		CRef* const obj = reinterpret_cast<CRef*>(*piVar2);
		if (obj != 0) {
			if (obj->DecRef() == 0) {
				delete obj;
			}
			*piVar2 = 0;
		}
		iVar4 = iVar4 + 1;
		puVar5 = puVar5 + 4;
	} while (iVar4 < 6);

	{
		void** piVar2 = reinterpret_cast<void**>(&m_fonts[1]);
		CRef* const obj = reinterpret_cast<CRef*>(*piVar2);
		if (obj != 0) {
			if (obj->DecRef() == 0) {
				delete obj;
			}
			*piVar2 = 0;
		}
	}

	if (m_wm.m_frameData != 0) {
		delete m_wm.m_frameData;
		m_wm.m_frameData = 0;
	}

	freeTexture(2, 3, 0x16, 0x2F);

	{
		CMenu** menu = reinterpret_cast<CMenu**>(bytes + 0xBC);
		if (*menu != 0) {
			delete *menu;
			*menu = 0;
		}
	}

	if (m_wm.m_worldObjData != 0) {
		delete[] m_wm.m_worldObjData;
		m_wm.m_worldObjData = 0;
	}
	if (m_wm.m_bubbleData != 0) {
		delete m_wm.m_bubbleData;
		m_wm.m_bubbleData = 0;
	}
	if (m_wm.m_frameData != 0) {
		delete m_wm.m_frameData;
		m_wm.m_frameData = 0;
	}
	if (m_wm.m_frameInfo != 0) {
		delete m_wm.m_frameInfo;
		m_wm.m_frameInfo = 0;
	}
	if (m_wm.m_charaModelData != 0) {
		delete[] m_wm.m_charaModelData;
		m_wm.m_charaModelData = 0;
	}
	if (m_wm.m_charaSelectData != 0) {
		delete[] m_wm.m_charaSelectData;
		m_wm.m_charaSelectData = 0;
	}
	if (m_wmCharaAnimState != 0) {
		delete[] m_wmCharaAnimState;
		m_wmCharaAnimState = 0;
	}
	if (m_wmWorldState != 0) {
		delete m_wmWorldState;
		m_wmWorldState = 0;
	}
	if (m_wmCharaState != 0) {
		delete[] m_wmCharaState;
		m_wmCharaState = 0;
	}
	if (m_wmWorldParams != 0) {
		delete m_wmWorldParams;
		m_wmWorldParams = 0;
	}
	{
		EffectInfo* const effectWork = m_effectWork;
		if (effectWork != 0) {
			operator delete[](reinterpret_cast<unsigned char*>(effectWork) - 0x10);
			m_effectWork = 0;
		}
	}
	if (m_menuWindowInfo != 0) {
		delete m_menuWindowInfo;
		m_menuWindowInfo = 0;
	}

	if (static_cast<signed char>(m_wmThpActive) != 0) {
		THPSimpleAudioStop();
		THPSimpleLoadStop();
		THPSimpleClose();
		THPSimpleQuit();
		if (m_wmWorkBuffer != 0) {
			if (m_wmWorkBuffer != 0) {
				Memory.Free(m_wmWorkBuffer);
				m_wmWorkBuffer = 0;
			}
			m_wmWorkBuffer = 0;
		}
		m_wmThpActive = 0;
	}

	PartMng.pppDestroyAll();
	MemoryCardMan.McEnd();

	GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0x00FFFFFF);
	GbaQue.SetControllerMode(0);
}

/*
 * --INFO--
 * PAL Address: 0x801005d8
 * PAL Size: 1320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::calcWorld()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
#define worldParams m_wmWorldParams

	reinterpret_cast<unsigned int*>(worldParams + 4)[0] = reinterpret_cast<unsigned int*>(worldParams + 8)[0];

	if (m_wmWorldState->m_worldReady == 0) {
		Sound.PlaySe(0x138B, 0x40, 0x7F, 0);
		GetWmWorldHandles(this)[1]->SetAnim(0, -1, -1, -1, 0);
		reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 0;
		m_wmWorldState->m_worldReady = 1;
		m_wmWorldState->m_mainState = 1;
	}

#define handle GetWmWorldHandles(this)[1]
#define model handle->m_model
	const int animState = m_wmWorldState->m_mainState;
	const float animTime = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(model) + 0xB4)[0];
	const float animEnd = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(model) + 0xC0)[0];

	if (animState == 1) {
		if (animTime < animEnd) {
			model->AddFrame(FLOAT_80331698);
			m_wmWorldState->m_frameCounter = 0;
		} else {
			if (m_wmWorldState->m_frameCounter >= 10) {
				CFlatRuntime::CStack stackData[3];

				handle->SetAnim(1, -1, -1, -1, 0);
				reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 1;
				stackData[0].m_word = 2;
				stackData[1].m_word = 0;
				stackData[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 4, 3, stackData, 0);
				m_wmWorldState->m_mainState = 2;
				m_wmWorldState->m_frameCounter = 0;
			}
		}
	} else if (animState == 2) {
		int nextAnim = static_cast<signed char>(bytes[0xE]);

		if (nextAnim != 0) {
			if (nextAnim == 1) {
				Sound.PlaySe(0x138C, 0x40, 0x7F, 0);
				nextAnim = 2;
			} else if (nextAnim == 2) {
				Sound.PlaySe(0x138C, 0x40, 0x7F, 0);
				nextAnim = 3;
			} else if (nextAnim == 3) {
				Sound.PlaySe(0x138C, 0x40, 0x7F, 0);
				nextAnim = 4;
			} else if (nextAnim == 4) {
				Sound.PlaySe(0x138C, 0x40, 0x7F, 0);
				nextAnim++;
			} else if (nextAnim == 5) {
				Sound.PlaySe(0x138D, 0x40, 0x7F, 0);
				nextAnim = 6;
				m_wmWorldState->m_mainState = 3;
				m_wmWorldState->m_frameCounter = 0;
			}

			if (nextAnim != reinterpret_cast<int*>(worldParams + 8)[0]) {
				handle->SetAnim(nextAnim, -1, -1, -1, 0);
				reinterpret_cast<int*>(worldParams + 8)[0] = nextAnim;

				if (nextAnim == 0) {
					model->SetFrame(animEnd);
				}
			}
			bytes[0xE] = 0;
		} else {
			if (animTime < animEnd) {
				model->AddFrame(FLOAT_80331698);
			} else {
				handle->SetAnim(1, -1, -1, -1, 0);
				reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 1;
			}
		}
	} else if (animState == 3 && m_wmWorldState->m_frameCounter >= 10) {
		if (animTime < animEnd) {
			model->AddFrame(FLOAT_80331698);
		} else {
			handle->SetAnim(0, -1, -1, -1, 0);
			reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 0;
			m_wmWorldState->m_delay = 10;
			m_wmWorldState->m_nextMenuMode = -1;
			m_wmWorldState->m_mainState = 4;
			Sound.PlaySe(0x32, 0x40, 0x7F, 0);
		}
	} else if (animState == 4) {
		if (m_wmWorldState->m_delay != 0) {
			m_wmWorldState->m_delay--;
		} else {
			m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
			m_wmWorldState->m_nextMenuMode = 0;
		}
	}

	unsigned char* const worldObj = m_wm.m_worldObjData;
	reinterpret_cast<short*>(worldObj + 0x58)[0] = 0;
	const float fVar1 = FLOAT_803313dc;
	reinterpret_cast<short*>(worldObj + 0x5A)[0] = 0;
	float fVar3 = FLOAT_80331598;
	reinterpret_cast<short*>(worldObj + 0x5C)[0] = 0x280;
	const float fVar4 = FLOAT_803315d4;
	reinterpret_cast<short*>(worldObj + 0x5E)[0] = 0x1C0;
	const float fVar5 = FLOAT_803317e0;
	reinterpret_cast<float*>(worldObj + 0x60)[0] = fVar1;
	const float fVar6 = FLOAT_803317e4;
	reinterpret_cast<float*>(worldObj + 0x64)[0] = fVar1;
	const float fVar7 = FLOAT_803317e8;
	reinterpret_cast<float*>(worldObj + 0x68)[0] = fVar3;
	fVar3 = FLOAT_803314bc;
	worldObj[0x50] = 1;
	reinterpret_cast<float*>(worldObj + 0x84)[0] = fVar4;
	reinterpret_cast<float*>(worldObj + 0x88)[0] = fVar4;
	reinterpret_cast<float*>(worldObj + 0x8C)[0] = fVar4;
	reinterpret_cast<float*>(worldObj + 0x6C)[0] = fVar1;
	reinterpret_cast<float*>(worldObj + 0x70)[0] = fVar5;
	reinterpret_cast<float*>(worldObj + 0x74)[0] = fVar6;
	reinterpret_cast<float*>(worldObj + 0x78)[0] = fVar7;
	reinterpret_cast<float*>(worldObj + 0x7C)[0] = fVar1;
	reinterpret_cast<float*>(worldObj + 0x80)[0] = fVar1;

	Mtx matrix;
	PSMTXRotRad(matrix, 'x', fVar3 * reinterpret_cast<float*>(worldObj + 0x78)[0]);
	matrix[0][3] = reinterpret_cast<float*>(worldObj + 0x6C)[0];
	matrix[1][3] = reinterpret_cast<float*>(worldObj + 0x70)[0];
	matrix[2][3] = reinterpret_cast<float*>(worldObj + 0x74)[0];
	PSMTXScaleApply(matrix, matrix, reinterpret_cast<float*>(worldObj + 0x84)[0], reinterpret_cast<float*>(worldObj + 0x88)[0],
	                reinterpret_cast<float*>(worldObj + 0x8C)[0]);

	model->SetMatrix(matrix);
	model->CalcMatrix();
	model->CalcSkin();

	const short updatedAnimState = m_wmWorldState->m_mainState;

	if (updatedAnimState == 1 && animTime >= animEnd) {
		if (m_wmWorldState->m_frameCounter < 10) {
			m_wmWorldState->m_frameCounter++;
		}
	} else if (updatedAnimState == 3 && m_wmWorldState->m_frameCounter < 10) {
		m_wmWorldState->m_frameCounter++;
	}
#undef worldParams
#undef model
#undef handle
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 504b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMainMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	WmWorldState* const worldState = m_wmWorldState;
	if (worldState == 0) {
		return;
	}

	CalcMainMenuSub();
	CalcWMFrame();

	const short state = worldState->m_mainState;
	const short subState = worldState->m_subState;
	if (state > 0 && state < 4) {
		CalcChara();
		CalcPitcher();
	}
	if (subState == 0 || subState == 1 || subState == 4 || state >= 3) {
		CalcFukidashi();
	}
	if (worldState->m_changeRequest != 0) {
		WMChgMenu();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80100b00
 * PAL Size: 1616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcDiaryMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	if (static_cast<signed char>(s_wmMenuMountStateInitialized) == 0) {
		s_wmMenuLastMountState = 0;
		s_wmMenuMountStateInitialized = 1;
	}

	const unsigned int slotState =
	    static_cast<unsigned int>(-static_cast<int>(MemoryCardMan.m_currentSlot) - 1) |
	    static_cast<unsigned int>(static_cast<int>(MemoryCardMan.m_currentSlot) + 1);
	const unsigned int mounted = slotState >> 31;
	if (mounted != s_wmMenuLastMountState) {
		if (static_cast<unsigned int>(System.m_execParam) >= 3) {
			const char* text = s_FALSE_803317F4;
			if (mounted != 0) {
				text = s_TRUE_803317EC;
			}
			System.Printf(const_cast<char*>(s_mount____s_801dc460), text);
		}
		s_wmMenuLastMountState = static_cast<unsigned char>(mounted);
	}

	WMChgMenu();
	if (static_cast<char>(bytes[0xD]) == 0) {
		int menuIndex = 4;
		unsigned char* menuPtr = bytes + 0x10;
		do {
			CMenu* const menu = *reinterpret_cast<CMenu**>(menuPtr + 0x10C);
			menu->Calc();
			menuIndex++;
			menuPtr += 4;
		} while (menuIndex < 6);
		return;
	}

	switch (m_wmWorldState->m_menuMode) {
	case 0:
		if (m_wmWorldState->m_mainState <= 4) {
			const short state = m_wmWorldState->m_mainState;
			int frameStep;
			if (state == 0) {
				frameStep = m_wmWorldState->m_frameCounter - 10;
			} else if (state > 0 && state < 4) {
				frameStep = 0;
			} else {
				frameStep = -m_wmWorldState->m_frameCounter;
			}
			CalcWmFrame0Inline(this, frameStep);
		}
		CalcMainMenuSub();
		break;
	case 1:
		calcWorld();
		break;
	case 2:
		CalcMCardMenu();
		break;
	case 3:
		if (m_singleCmakeMode == 0) {
			if (m_wmWorldState->m_modelFlagsInitialized == 0) {
				m_wm.m_charaModelData[0x0C] = 1;
				m_wm.m_charaModelData[0x40] = 1;
				m_wm.m_charaModelData[0x74] = 1;
				m_wm.m_charaModelData[0xA8] = 1;
				m_wm.m_charaModelData[0xDC] = 1;
				m_wm.m_charaModelData[0x110] = 1;
				m_wm.m_charaModelData[0x144] = 1;
				m_wm.m_charaModelData[0x178] = 1;
				m_wmWorldState->m_modelFlagsInitialized = 1;
			}
			if (m_wmWorldState->m_mainState <= 4) {
				CalcCharaSelect();
				const short state = m_wmWorldState->m_mainState;
				int frameStep;
				if (state == 0) {
					frameStep = m_wmWorldState->m_frameCounter - 10;
				} else if (state > 0 && state < 4) {
					frameStep = 0;
				} else {
					frameStep = -m_wmWorldState->m_frameCounter;
				}
				CalcWmFrame0Inline(this, frameStep);
				const short animState = m_wmWorldState->m_mainState;
				if (animState > 0 && animState < 4) {
					CalcChara();
				}
			}
		} else {
			CalcSingCMake();
		}
		break;
	case 4:
		if (((m_wmWorldState->m_mainState != 0) || bytes[0x12] != 0) &&
		    m_wmWorldState->m_mainState <= 3) {
			if (Game.m_gameWork.m_chaliceElement != m_crystalElem) {
				SetCrystalCageAttr();
			}
			if (Game.m_gameWork.m_timerA != m_manaWaterTimerA) {
				SetManaWaterEffect();
			}
			CalcFukidashi();
			CalcPitcher();
			CalcWMFrame();
		}
		break;
	case 5:
		CalcLoadMenu();
		break;
	case 6:
		CalcTitleMenu();
		break;
	case 7:
		CalcOptionMenu();
		break;
	case 8:
		CalcGoOutMenu();
		break;
	default:
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
			System.Printf(const_cast<char*>(s__s__d___Error_WM_menu_no_error___801dc424), s_wm_menu_cpp, 0x4c0);
		}
		break;
	}

	int menuIndex = 4;
	unsigned char* menuPtr = bytes + 0x10;
	do {
		CMenu* const menu = *reinterpret_cast<CMenu**>(menuPtr + 0x10C);
		menu->Calc();
		menuIndex++;
		menuPtr += 4;
	} while (menuIndex < 6);
}

/*
 * --INFO--
 * PAL Address: 0x800fec40
 * PAL Size: 6552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMCardMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	bool bVar1 = false;
	if (Pad.m_debugPadLock != 0 || Pad.m_debugPadPort != -1) {
		bVar1 = true;
	}
	unsigned short uVar3;
	if (bVar1) {
		uVar3 = 0;
	} else {
		unsigned int padIndex = 0;
		padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
		int __p11 =  (0 + padIndex);
		uVar3 = Pad.GetPadInputs()[__p11].buttonDown[0];
	}
	unsigned short uVar6 = GetButtonRepeat(0);

	if ((unsigned char)m_wmWorldState->m_worldReady == 0) {
		m_mcCtrl.m_previousState = 0;
		m_mcCtrl.m_state = 0;
		m_mcCtrl.m_lastResult = 0;
		m_mcCtrl.m_iteration = 0;
		m_mcCtrl.m_userBuffer = 0;
		m_mcCtrl.m_createFlag = 0;
		if (gWmMenuCursorX[0] >= 0 && gWmMenuCursorX[0] < 2) {
			m_mcCtrl.m_cardChannel = (int)gWmMenuCursorX[0];
		} else {
			m_mcCtrl.m_cardChannel = 0;
		}
		if (gWmMenuCursorX[1] >= 0 && gWmMenuCursorX[1] < 4) {
			m_mcCtrl.m_saveIndex = (int)gWmMenuCursorX[1];
		} else {
			m_mcCtrl.m_saveIndex = 0;
		}
		memset(GetWmMenuCharaState(this), 0, kWmMenuCharaStateBytes);
		Game.m_gameWork.m_wmBackupParams[0] = m_wmWorldState->m_originalBackupParams[0];
		Game.m_gameWork.m_wmBackupParams[1] = m_wmWorldState->m_originalBackupParams[1];
		Game.m_gameWork.m_wmBackupParams[2] = m_wmWorldState->m_originalBackupParams[2];
		Game.m_gameWork.m_wmBackupParams[3] = m_wmWorldState->m_originalBackupParams[3];
		m_wmWorldState->m_flag0A = 0;
		m_wmWorldState->m_worldReady = 1;
	}

	int iVar14;
	int iVar12;
	short sVar7 = m_wmWorldState->m_mainState;
	unsigned int uVar15;
	if (sVar7 == 0) {
		uVar15 = static_cast<int>(m_wmWorldState->m_frameCounter) - 10;
	} else if (sVar7 > 0 && sVar7 < 4) {
		uVar15 = 0;
	} else {
		uVar15 = -static_cast<int>(m_wmWorldState->m_frameCounter);
	}

	*reinterpret_cast<short*>(m_wm.m_frameInfo + 4) = 0x10;
	int frameSum = (int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 8) + (int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 4);
	iVar14 = (int)(FLOAT_803313e0 - (float)frameSum);
	*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20) = (short)iVar14;

	if ((int)uVar15 < 0) {
		double dVar22;
		float baseWidth = (float)((int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 8) + (int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 4));
		if ((int)uVar15 >= -10) {
			int absSign = (int)uVar15 >> 0x1F;
			int __p10 = absSign;
			int absRaw = ((int)uVar15 ^ absSign) - __p10;
			float dVar23 = (float)(baseWidth * (DOUBLE_803314E8 * (double)absRaw));
			int __p15 = absRaw;
			unsigned int absOff = (unsigned int)__p15;
			if ((int)absOff < 0) absOff = 0;
			if ((int)absOff > 10) absOff = 10;
			float dVar28 = (float)sin((double)(FLOAT_803314bc * (float)(int)absOff * FLOAT_803316d4));
			dVar22 = (double)(dVar23 * dVar28);
		} else {
			dVar22 = (double)baseWidth;
		}

		iVar14 = (int)((float)(int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 4) - (float)dVar22);
		*reinterpret_cast<short*>(m_wm.m_frameInfo + 4) = (short)iVar14;
		iVar14 = (int)((float)(int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20) + (float)dVar22);
		*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20) = (short)iVar14;
	}

	float fVar2 = FLOAT_803313e8;
	if (m_wmWorldState->m_mainState != 2) {
		return;
	}

	iVar14 = reinterpret_cast<int>(m_wmWorldState);
	iVar12 = m_wmWorldState->m_subState;
	switch (iVar12) {
	case 0:
	case 2:
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_cardChannel = static_cast<short>(m_mcCtrl.m_cardChannel);
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(fVar2);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(0);
			iVar14 = 0;
			int* piVar4 = reinterpret_cast<int*>(GetWinMess(0));
			int* piVar18 = piVar4;
			for (int iVar21 = 0; iVar21 < *piVar4; iVar21++) {
				const char* pcVar10 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar18) + 4)];
				if (pcVar10 != 0) {
					if (*pcVar10 == '$') pcVar10 = pcVar10 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar10);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar18 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar18) + 2);
			}
			int iLines = iVar14 / 0x16;
			if (iVar14 - iLines * 0x16 != 0) iLines = iLines + 1;
			sVar7 = (iLines + 2) * 0x16 + 0x40;
			short sVar16 = (short)*piVar4 * 0x1E + 0x40;
			iVar14 = (int)(float)((float)(0x280 - sVar7) * DOUBLE_803313f8);
			iVar12 = (int)(float)((double)(FLOAT_80331430 - (float)sVar16) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar12;
			m_menuWindowInfo->width = sVar7;
			m_menuWindowInfo->height = sVar16;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			memset(GetWmMenuCharaState(this), 0, kWmMenuCharaStateBytes);
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_flag0A = 0;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A == 0) {
				if ((uVar6 & 3) != 0) {
					m_wmWorldState->m_cardChannel ^= 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					if ((uVar3 & 0x100) != 0) {
						m_wmWorldState->m_state0E = 1;
						m_mcCtrl.m_cardChannel = m_wmWorldState->m_cardChannel;
						if (m_wmWorldState->m_cardChannel == static_cast<signed char>(gWmMenuCursorX[0])) {
							m_mcCtrl.m_saveIndex = (int)gWmMenuCursorX[1];
						}
						m_wmWorldState->m_counter1A = 10;
						Sound.PlaySe(2, 0x40, 0x7F, 0);
					} else {
						if ((uVar3 & 0x200) != 0) {
							m_wmWorldState->m_state0E = -1;
							m_wmWorldState->m_counter1A = 1;
							Sound.PlaySe(3, 0x40, 0x7F, 0);
						}
					}
				}
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	case 3:
		m_wmWorldState->m_mcResult = static_cast<short>(MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel));
		break;
	case 5:
	case 6:
	case 7:
	case 9:
	case 10:
	case 0xE:
	case 0xF:
	case 0x14:
	case 0x15:
	case 0x1B:
	case 0x1C: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			bVar1 = true;
			int uVar17;
			int uVar20 = 0;
			if (iVar12 == 5) { uVar17 = 1; }
			else if (iVar12 == 6) { uVar17 = 2; }
			else if (iVar12 == 7) { uVar17 = 3; }
			else if (iVar12 == 9) { uVar17 = 10; }
			else if (iVar12 == 10) { uVar17 = 0xB; }
			else if (iVar12 == 0xE) { uVar17 = 0xC; }
			else if (iVar12 == 0xF) { uVar17 = 0xD; }
			else if (iVar12 == 0x1C) { uVar20 = 1; uVar17 = 0x1B; }
			else if (iVar12 == 0x1B) { uVar20 = 1; uVar17 = 0x1C; }
			else if (iVar12 == 0x15) { bVar1 = false; uVar17 = 0xE; }
			else { uVar17 = 0xF; }
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(FLOAT_803313e8);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(uVar20);
			iVar14 = 0;
			int* piVar4 = reinterpret_cast<int*>(GetWinMess(uVar17));
			int* piVar18 = piVar4;
			for (int iVar21 = 0; iVar21 < *piVar4; iVar21++) {
				const char* pcVar10 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar18) + 4)];
				if (pcVar10 != 0) {
					if (*pcVar10 == '$') pcVar10 = pcVar10 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar10);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar18 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar18) + 2);
			}
			int iLines = iVar14 / 0x16;
			int __p28 = iLines;
			if (iVar14 - iLines * 0x16 != 0) iLines = __p28 + 1;
			sVar7 = (iLines + 2) * 0x16 + 0x40;
			iVar14 = (int)(float)((float)(0x280 - sVar7) * DOUBLE_803313f8);
			short sVar16 = (short)*piVar4 * 0x1E + 0x40;
			iVar12 = (int)(float)((double)(FLOAT_80331430 - (float)sVar16) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar12;
			m_menuWindowInfo->width = sVar7;
			m_menuWindowInfo->height = sVar16;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_counter1A = 0;
			if (bVar1) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			sVar7 = m_wmWorldState->m_subState;
			if (sVar7 == 0xE || sVar7 == 0x15) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
				if (m_wmWorldState->m_mcResult < 0) goto LAB_chk;
			} else if (sVar7 == 5) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
			LAB_chk:
				sVar7 = m_wmWorldState->m_subState;
				short sVar16;
				if (sVar7 == 5) { sVar16 = -1; }
				else if (sVar7 == 6) { sVar16 = -3; }
				else if (sVar7 == 7) { sVar16 = -4; }
				else { sVar16 = 0; }
				if (sVar7 != 7) {
					if (sVar16 != m_wmWorldState->m_mcResult && m_wmWorldState->m_mcResult != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				} else {
					short chk = m_wmWorldState->m_mcResult;
					if (chk != 0 && chk != sVar16 && chk != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				}
			}
			if ((uVar3 & 0x300) != 0) {
				m_wmWorldState->m_state0E = 1;
				m_wmWorldState->m_counter1A = 10;
				if (m_wmWorldState->m_subState == 0x15) {
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				} else {
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 4:
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(FLOAT_803313e8);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(0);
			iVar14 = 0;
			int* piVar4 = reinterpret_cast<int*>(GetWinMess(6));
			int* piVar18 = piVar4;
			for (int iVar21 = 0; iVar21 < *piVar4; iVar21++) {
				const char* pcVar10 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar18) + 4)];
				if (pcVar10 != 0) {
					if (*pcVar10 == '$') pcVar10 = pcVar10 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar10);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar18 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar18) + 2);
			}
			int iLines = iVar14 / 0x16;
			if (iVar14 - iLines * 0x16 != 0) iLines = iLines + 1;
			sVar7 = (iLines + 2) * 0x16 + 0x40;
			short sVar16 = (short)*piVar4 * 0x1E + 0x40;
			iVar14 = (int)(float)((float)(0x280 - sVar7) * DOUBLE_803313f8);
			iVar12 = (int)(float)((double)(FLOAT_80331430 - (float)sVar16) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar12;
			m_menuWindowInfo->width = sVar7;
			m_menuWindowInfo->height = sVar16;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			short chkResult = (short)GetMcCtrl()->ChkEmpty(0);
			int __p12 = chkResult;
			m_wmWorldState->m_mcResult = __p12;
			if (m_wmWorldState->m_mcResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
				m_wmWorldState->m_state0E = -1;
				m_wmWorldState->m_counter1A = 10;
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	case 8:
	case 0xB:
	case 0x12:
	case 0x19: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			int uVar20 =  (int)(long)(0);
			int uVar17;
			if (iVar12 == 8) {
				m_wmWorldState->m_cardChannel = 0;
				uVar17 = 4;
			} else if (iVar12 == 0xB) {
				uVar17 = 5;
				m_wmWorldState->m_cardChannel = 1;
			} else if (iVar12 == 0x19) {
				uVar17 = 0x19;
				uVar20 = 1;
				m_wmWorldState->m_cardChannel = 1;
			} else {
				uVar17 = 0x12;
				m_wmWorldState->m_cardChannel = 1;
			}
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(FLOAT_803313e8);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(uVar20);
			iVar14 = 0;
			int* piVar4 = reinterpret_cast<int*>(GetWinMess(uVar17));
			int* piVar18 = piVar4;
			for (int iVar21 = 0; iVar21 < *piVar4; iVar21++) {
				const char* pcVar10 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar18) + 4)];
				if (pcVar10 != 0) {
					if (*pcVar10 == '$') pcVar10 = pcVar10 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar10);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar18 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar18) + 2);
			}
			int iLines = iVar14 / 0x16;
			if (iVar14 - iLines * 0x16 != 0) iLines = iLines + 1;
			sVar7 = (iLines + 2) * 0x16 + 0x40;
			short sVar16 = (short)*piVar4 * 0x1E + 0x40;
			iVar14 = (int)(float)((float)(0x280 - sVar7) * DOUBLE_803313f8);
			iVar12 = (int)(float)((double)(FLOAT_80331430 - (float)sVar16) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar12;
			m_menuWindowInfo->width = sVar7;
			m_menuWindowInfo->height = sVar16;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A == 0) {
				if (m_wmWorldState->m_subState == 0x19) {
					m_wmWorldState->m_state0E = 1;
					m_wmWorldState->m_counter1A = 0x5A;
					break;
				}
				int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
				m_wmWorldState->m_mcResult = (short)chkRes;
				if (m_wmWorldState->m_mcResult != 0) {
					m_wmWorldState->m_state0E = -1;
					m_wmWorldState->m_counter1A = 10;
				} else {
					if ((uVar6 & 3) != 0) {
						m_wmWorldState->m_cardChannel ^= 1;
						Sound.PlaySe(1, 0x40, 0x7F, 0);
					} else {
						if ((uVar3 & 0x100) != 0) {
							if (m_wmWorldState->m_cardChannel == 0) {
								m_wmWorldState->m_state0E = 1;
							} else {
								m_wmWorldState->m_state0E = -1;
							}
							m_wmWorldState->m_counter1A = 10;
							Sound.PlaySe(2, 0x40, 0x7F, 0);
						} else {
							if ((uVar3 & 0x200) != 0) {
								m_wmWorldState->m_cardChannel = 1;
								m_wmWorldState->m_state0E = -1;
								m_wmWorldState->m_counter1A = 10;
								Sound.PlaySe(3, 0x40, 0x7F, 0);
							}
						}
					}
				}
			}
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A != 0) {
			if (m_wmWorldState->m_subState == 0x19) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
			}
			m_wmWorldState->m_counter1A--;
			if (m_wmWorldState->m_counter1A == 0) {
				m_menuWindowInfo->state = 2;
			}
		}
		break;
	}
	case 0xD:
	case 0x13:
	case 0x1A: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			int uVar20;
			uVar20 = 0;
			int uVar17;
			if (iVar12 == 0xD) { uVar17 = 7; }
			else if (iVar12 == 0x1A) { uVar17 = 0x1A; uVar20 = 1; }
			else { uVar17 = 8; }
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(FLOAT_803313e8);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(uVar20);
			iVar14 = 0;
			int* piVar4 = reinterpret_cast<int*>(GetWinMess(uVar17));
			int* piVar18 = piVar4;
			for (int iVar21 = 0; iVar21 < *piVar4; iVar21++) {
				const char* pcVar10 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar18) + 4)];
				if (pcVar10 != 0) {
					if (*pcVar10 == '$') pcVar10 = pcVar10 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar10);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar18 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar18) + 2);
			}
			int iLines = iVar14 / 0x16;
			if (iVar14 - iLines * 0x16 != 0) iLines = iLines + 1;
			sVar7 = (iLines + 2) * 0x16 + 0x40;
			short sVar16 = (short)*piVar4 * 0x1E + 0x40;
			iVar14 = (int)(float)((float)(0x280 - sVar7) * DOUBLE_803313f8);
			iVar12 = (int)(float)((double)(FLOAT_80331430 - (float)sVar16) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar12;
			m_menuWindowInfo->width = sVar7;
			m_menuWindowInfo->height = sVar16;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
			if (m_wmWorldState->m_menuMode == 8
			    && m_cmakeWork != 0) {
				m_mcCtrl.m_userBuffer = m_cmakeWork;
			} else {
				m_mcCtrl.m_userBuffer = 0;
			}
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			if (iVar12 == 0xD) {
				GetMcCtrl()->Format(1);
				m_wmWorldState->m_mcResult = (short)m_mcCtrl.m_lastResult;
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			} else if (iVar12 == 0x1A) {
				m_wmWorldState->m_mcResult = (short)GetMcCtrl()->EraseDat();
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			} else {
				m_wmWorldState->m_mcResult = (short)GetMcCtrl()->SaveDat();
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			}
			if (m_wmWorldState->m_mcResult == 0) break;
			if (m_wmWorldState->m_subState == 0x13) {
				if (m_wmWorldState->m_menuMode != 8) {
					gWmMenuWorkA = m_mcCtrl.m_serialLo;
					gWmMenuWorkB = m_mcCtrl.m_serialHi;
					gWmMenuCursorX[0] = (unsigned char)m_mcCtrl.m_cardChannel;
					gWmMenuCursorX[1] = (unsigned char)m_mcCtrl.m_saveIndex;
				}
				int unk838 = reinterpret_cast<int>(m_wmCharaState);
				*reinterpret_cast<int*>(unk838 + m_mcCtrl.m_saveIndex * 0x48 + 8) = *reinterpret_cast<int*>(reinterpret_cast<char*>(&Game.m_gameWork) + 8);
			}
			m_wmWorldState->m_state0E = 1;
			m_wmWorldState->m_counter1A = 10;
		}
		if (m_menuWindowInfo->state == 1) {
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 0xC: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_flag09 = 1;
			memset(GetWmMenuCharaState(this), 0, kWmMenuCharaStateBytes);
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			short listRes = (short)GetMcCtrl()->LoadMcList();
			int __p9 = listRes;
			m_wmWorldState->m_mcResult = __p9;
			if (m_wmWorldState->m_mcResult == 0) {
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
				break;
			}
			if (m_wmWorldState->m_menuMode == 8) {
				int iVar21 = 0;
				int cnt = 4;
				int iVar13 = 0;
				do {
					if (*reinterpret_cast<char*>(m_wmCharaState + iVar13 + 0x42) == 0
					    && *reinterpret_cast<int*>(m_wmCharaState + iVar13 + 8) > 0) {
						iVar21++;
					}
					iVar13 += 0x48;
					cnt--;
				} while (cnt != 0);
				if (iVar21 == 0) {
					m_wmWorldState->m_mcResult = (short)0xFC19;
				}
			}
			if (!(gWmMenuCursorX[1] >= 0 && (int)gWmMenuCursorX[0] == m_mcCtrl.m_cardChannel)) {
			LAB_saveIdx:
				int unk838 = reinterpret_cast<int>(m_wmCharaState);
				int sel = 0;
				int __p11 =  (unk838 | 0);
				if (!(*reinterpret_cast<char*>(unk838 + 0x42) == 0 && *reinterpret_cast<int*>(__p11 + 8) > 0)) {
					m_mcCtrl.m_saveIndex = sel;
				} else {
					sel = 1;
					if (!(*reinterpret_cast<char*>(unk838 + 0x8A) == 0 && *reinterpret_cast<int*>(unk838 + 0x50) > 0)) {
						m_mcCtrl.m_saveIndex = sel;
					} else {
						sel = 2;
						if (!(*reinterpret_cast<char*>(unk838 + 0xD2) == 0 && *reinterpret_cast<int*>(unk838 + 0x98) > 0)) {
							m_mcCtrl.m_saveIndex = sel;
						} else {
							sel = 3;
							if (!(*reinterpret_cast<char*>(unk838 + 0x11A) == 0 && *reinterpret_cast<int*>(unk838 + 0xE0) > 0)) {
								m_mcCtrl.m_saveIndex = sel;
							} else {
								sel = 4;
							}
						}
					}
				}
				if (sel >= 4) {
					m_mcCtrl.m_saveIndex = 0;
				}
				m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
			} else {
				if ((gWmMenuWorkA ^ (int)m_mcCtrl.m_serialLo) | (gWmMenuWorkB ^ (int)m_mcCtrl.m_serialHi)) goto LAB_saveIdx;
				m_mcCtrl.m_saveIndex = (int)gWmMenuCursorX[1];
				m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
			}
			iVar12 = 0;
			iVar14 = 0;
			for (int iVar21 = 4; iVar21 != 0; iVar21--) {
				if (*reinterpret_cast<char*>(reinterpret_cast<int>(m_wmCharaState) + iVar14 + 0x42) != 0) {
					m_mcCtrl.m_saveIndex = iVar12;
					m_wmWorldState->m_cardChannel = (short)iVar12;
					break;
				}
				iVar14 += 0x48;
				iVar12++;
			}
			m_wmWorldState->m_state0E = 1;
			m_wmWorldState->m_counter1A = 10;
		}
		if (m_menuWindowInfo->state == 1) {
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 0x11:
		m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
		if (m_wmWorldState->m_mcResult == 0 && uVar6 != 0) {
			if ((uVar6 & 8) != 0) {
				if (m_wmWorldState->m_cardChannel < 1) {
					m_wmWorldState->m_cardChannel = 3;
				} else {
					m_wmWorldState->m_cardChannel--;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				if ((uVar6 & 4) != 0) {
					if (!(m_wmWorldState->m_cardChannel < 3)) {
						m_wmWorldState->m_cardChannel = 0;
					} else {
						m_wmWorldState->m_cardChannel++;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			if ((uVar6 & 0xC) == 0) {
				if ((uVar3 & 0x100) != 0) {
					sVar7 = m_wmWorldState->m_state0E;
					if (sVar7 != -1 && sVar7 != 1) {
						m_mcCtrl.m_saveIndex = (int)m_wmWorldState->m_cardChannel;
						m_wmWorldState->m_state0E = 1;
						Sound.PlaySe(2, 0x40, 0x7F, 0);
					}
				}
				if ((uVar3 & 0x200) != 0) {
					sVar7 = m_wmWorldState->m_state0E;
					if (sVar7 != -1 && sVar7 != 1) {
						m_wmWorldState->m_state0E = -1;
						Sound.PlaySe(3, 0x40, 0x7F, 0);
					}
				}
			}
		}
		break;
	}

	if (m_wmWorldState->m_subState != 0) {
		CalcMcObj();
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 636b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcCMakeMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	WmWorldState* const worldState = m_wmWorldState;
	if (worldState == 0) {
		return;
	}

	CalcCharaBase();
	CalcCharaSelect();
	if (worldState->m_mainState > 0 && worldState->m_mainState < 4) {
		CalcChara();
	}
	CalcWMFrame();
	CalcFukidashi();
	IsAsyncCharaLoadFinish();
	if (gWmMenuWorkA != 0) {
		ChkSelectParty();
	}
	if (static_cast<signed char>(bytes[0x17]) != 0 || worldState->m_cardChannel != 0) {
		CalcMainMenuSub();
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMoveMenu()
{
	WmWorldState* const worldState = m_wmWorldState;
	if (worldState == 0) {
		return;
	}

	CalcMainMenuSub();
	CalcWMFrame();
	CalcFukidashi();
	CalcCharaBase();
	if (worldState->m_mainState > 0 && worldState->m_mainState < 4) {
		CalcPitcher();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800feba0
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitSaveLoadMenu()
{
	float posX = FLOAT_803313dc;
	float posY = FLOAT_803313e8;
	int zero = 0;

	MenuPcs.m_wmWorldState->m_frameCounter = zero;
	MenuPcs.m_wmWorldState->m_titleState = zero;
	MenuPcs.m_wmWorldState->m_worldReady = static_cast<unsigned char>(zero);
	MenuPcs.m_wmWorldState->m_flag09 = static_cast<unsigned char>(zero);
	MenuPcs.m_wmWorldState->m_flag0A = static_cast<unsigned char>(zero);
	MenuPcs.m_wmWorldState->m_state0E = zero;
	MenuPcs.m_wmWorldState->m_mainState = zero;
	MenuPcs.m_wmWorldState->m_state12 = zero;
	MenuPcs.m_wmWorldState->m_subState = zero;
	MenuPcs.m_wmWorldState->m_delay = zero;
	MenuPcs.m_wmWorldState->m_counter1A = zero;
	MenuPcs.m_wmWorldState->m_posY = posY;
	MenuPcs.m_wmWorldState->m_posX = posX;
	MenuPcs.m_wmWorldState->m_mcResult = zero;
	MenuPcs.m_wmWorldState->m_flag0B = static_cast<unsigned char>(zero);
	MenuPcs.m_wmWorldState->m_cardChannel = zero;
	MenuPcs.m_wmTransitionCode = zero;
	MenuPcs.m_textureLocIndex = static_cast<unsigned char>(zero);
}

/*
 * --INFO--
 * PAL Address: 0x800fcfb4
 * PAL Size: 7148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcLoadMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	WmWorldState* const worldState = m_wmWorldState;
	m_textureLocIndex = 0;

	int bVar1 = 0;
	if (Pad.m_debugPadLock != 0 || Pad.m_debugPadPort != -1) {
		bVar1 = true;
	}
	unsigned int uVar4;
	if (bVar1) {
		uVar4 = 0;
	} else {
		unsigned int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
		unsigned short down = Pad.GetPadInputs()[padIndex].buttonDown[0];
		uVar4 = down;
	}
	unsigned short uVar7 = GetButtonRepeat(0);

	if (m_wmWorldState->m_worldReady == 0) {
		*reinterpret_cast<unsigned short*>(m_wm.m_frameInfo + 4) = 0x10;
		float one = FLOAT_803313e8;
		float zero = FLOAT_803313dc;
		*reinterpret_cast<unsigned short*>(m_wm.m_frameInfo + 6) = 0x10;
		*reinterpret_cast<unsigned short*>(m_wm.m_frameInfo + 8) = 0xE8;
		*reinterpret_cast<unsigned short*>(m_wm.m_frameInfo + 0xA) = 0x168;
		*reinterpret_cast<float*>(m_wm.m_frameInfo + 0xC) = zero;
		*reinterpret_cast<float*>(m_wm.m_frameInfo + 0x10) = zero;
		*reinterpret_cast<float*>(m_wm.m_frameInfo + 0x14) = one;
		*reinterpret_cast<float*>(m_wm.m_frameInfo + 0x18) = one;
		*reinterpret_cast<unsigned int*>(m_wm.m_frameInfo + 0x1C) = 0;

		unsigned char* frame0 = m_wm.m_frameInfo;
		*reinterpret_cast<short*>(frame0 + 0x20) = *reinterpret_cast<short*>(frame0 + 4);
		*reinterpret_cast<short*>(frame0 + 0x22) = *reinterpret_cast<short*>(frame0 + 6);
		*reinterpret_cast<short*>(frame0 + 0x24) = *reinterpret_cast<short*>(frame0 + 8);
		*reinterpret_cast<short*>(frame0 + 0x26) = *reinterpret_cast<short*>(frame0 + 0xA);
		*reinterpret_cast<float*>(frame0 + 0x28) = *reinterpret_cast<float*>(frame0 + 0xC);
		*reinterpret_cast<float*>(frame0 + 0x2C) = *reinterpret_cast<float*>(frame0 + 0x10);
		*reinterpret_cast<float*>(frame0 + 0x30) = *reinterpret_cast<float*>(frame0 + 0x14);
		*reinterpret_cast<float*>(frame0 + 0x34) = *reinterpret_cast<float*>(frame0 + 0x18);
		*reinterpret_cast<unsigned int*>(frame0 + 0x38) = *reinterpret_cast<unsigned int*>(frame0 + 0x1C);

		frame0 = m_wm.m_frameInfo;
		*reinterpret_cast<short*>(frame0 + 0x20) = 0x280 - (*reinterpret_cast<short*>(frame0 + 8) + *reinterpret_cast<short*>(frame0 + 4));
		*reinterpret_cast<unsigned int*>(m_wm.m_frameInfo + 0x38) = 8;

		m_mcCtrl.m_previousState = 0;
		m_mcCtrl.m_state = 0;
		m_mcCtrl.m_lastResult = 0;
		m_mcCtrl.m_iteration = 0;
		m_mcCtrl.m_userBuffer = 0;
		m_mcCtrl.m_createFlag = 0;
		m_mcCtrl.m_cardChannel = 0;
		m_mcCtrl.m_saveIndex = 0;
		memset(GetWmMenuCharaState(this), 0, kWmMenuCharaStateBytes);

		Game.m_gameWork.m_wmBackupParams[0] = m_wmWorldState->m_originalBackupParams[0];
		Game.m_gameWork.m_wmBackupParams[1] = m_wmWorldState->m_originalBackupParams[1];
		Game.m_gameWork.m_wmBackupParams[2] = m_wmWorldState->m_originalBackupParams[2];
		Game.m_gameWork.m_wmBackupParams[3] = m_wmWorldState->m_originalBackupParams[3];
		if (m_wmWorldState->m_menuMode == 8 && m_cmakeWorkCardChannel != 0) {
			m_mcCtrl.m_cardChannel = (int)m_cmakeWorkCardChannel - 1;
			m_wmWorldState->m_subState = 3;
			m_wmWorldState->m_flag09 = 1;
		}
		m_wmWorldState->m_flag0A = 0;
		m_wmWorldState->m_worldReady = 1;
	}

	int iVar14;
	short sVar8 = m_wmWorldState->m_mainState;
	unsigned int uVar15;
	if (sVar8 == 0) {
		uVar15 = static_cast<int>(m_wmWorldState->m_frameCounter) - 10;
	} else if (sVar8 > 0 && sVar8 < 4) {
		uVar15 = 0;
	} else {
		uVar15 = -static_cast<int>(m_wmWorldState->m_frameCounter);
	}

	*reinterpret_cast<short*>(m_wm.m_frameInfo + 4) = 0x10;
	int iVar10 = reinterpret_cast<int>(m_wm.m_frameInfo);
	int frameSum = (int)*reinterpret_cast<short*>(iVar10 + 8) + (int)*reinterpret_cast<short*>(iVar10 + 4);
	iVar14 = (int)(FLOAT_803313e0 - (float)frameSum);
	*reinterpret_cast<short*>(iVar10 + 0x20) = (short)iVar14;

	if ((int)uVar15 < 0) {
		float wave = (float)((int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 8) + (int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 4));
		if ((int)uVar15 >= -10) {
			int s15 = (int)uVar15 >> 31;
			int absRaw = ((int)uVar15 ^ s15) - s15;
			wave = (float)(wave * (DOUBLE_803314E8 * (double)absRaw));
			int s16 = (int)uVar15 >> 31;
			int absOff = ((int)uVar15 ^ s16) - s16;
			if (absOff < 0) absOff = 0;
			if (absOff > 10) absOff = 10;
			wave = wave * (float)sin((double)(FLOAT_803314bc * ((float)absOff * FLOAT_803316d4)));
		}

		iVar14 = (int)((float)(int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 4) - wave);
		*reinterpret_cast<short*>(m_wm.m_frameInfo + 4) = (short)iVar14;
		iVar14 = (int)((float)(int)*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20) + wave);
		*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20) = (short)iVar14;
	}

	float fVar2 = FLOAT_803313e8;
	if (m_wmWorldState->m_mainState != 2) {
		return;
	}

	iVar14 = reinterpret_cast<int>(worldState);
	iVar10 = m_wmWorldState->m_subState;
	switch (iVar10) {
	case 0:
	case 2:
		if ((unsigned char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_cardChannel;
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(fVar2);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(0);
			iVar14 = 0;
			int* piVar5 = reinterpret_cast<int*>(GetWinMess(0));
			int* piVar20 = piVar5;
			for (int iVar23 = 0; iVar23 < *piVar5; iVar23++) {
				const char* pcVar12 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar20) + 4)];
				if (pcVar12 != 0) {
					if (*pcVar12 == '$') pcVar12 = pcVar12 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar12);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar20 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar20) + 2);
			}
			iVar10 = iVar14 / 0x16;
			if (iVar14 % 0x16 != 0) iVar10 = iVar10 + 1;
			sVar8 = (iVar10 + 2) * 0x16 + 0x40;
			short sVar18 = *piVar5 * 0x1E + 0x40;
			iVar14 = (int)(float)((double)(0x280 - sVar8) * DOUBLE_803313f8);
			iVar10 = (int)(float)((double)(FLOAT_80331430 - (float)sVar18) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar10;
			m_menuWindowInfo->width = sVar8;
			m_menuWindowInfo->height = sVar18;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			memset(GetWmMenuCharaState(this), 0, kWmMenuCharaStateBytes);
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_flag0A = 0;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A == 0) {
				if ((uVar7 & 3) != 0) {
					m_wmWorldState->m_cardChannel ^= 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					if ((uVar4 & 0x100) != 0) {
						m_wmWorldState->m_state0E = 1;
						m_mcCtrl.m_cardChannel = (int)m_wmWorldState->m_cardChannel;
						m_wmWorldState->m_counter1A = 10;
						Sound.PlaySe(2, 0x40, 0x7F, 0);
					} else {
						if ((uVar4 & 0x200) != 0) {
							m_wmWorldState->m_state0E = -1;
							m_wmWorldState->m_counter1A = 1;
							Sound.PlaySe(3, 0x40, 0x7F, 0);
						}
					}
				}
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar8 = m_wmWorldState->m_counter1A;
			if (sVar8 != 0) {
				m_wmWorldState->m_counter1A = sVar8 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	case 3:
		m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
		break;
	case 5:
	case 6:
	case 7:
	case 10:
	case 0xE:
	case 0xF:
	case 0x10:
	case 0x17:
	case 0x18:
	case 0x1B:
	case 0x1C: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			bVar1 = true;
			int uVar22 = 0;
			int uVar19;
			if (iVar10 == 5) { uVar19 = 1; }
			else if (iVar10 == 6) { uVar19 = 2; }
			else if (iVar10 == 7) { uVar19 = 3; }
			else if (iVar10 == 10) { uVar19 = 0xB; }
			else if (iVar10 == 0xE) { uVar19 = 0xC; }
			else if (iVar10 == 0xF) { uVar19 = 0xD; }
			else if (iVar10 == 0x1C) { uVar19 = 0x1B; uVar22 = 1; }
			else if (iVar10 == 0x1B) { uVar19 = 0x1C; uVar22 = 1; }
			else if (iVar10 == 0x18) { bVar1 = false; uVar19 = 0x10; }
			else if (iVar10 == 0x17) { uVar19 = 0x11; }
			else { uVar19 = 0x13; }
			if (bVar1) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(FLOAT_803313e8);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(uVar22);
			iVar14 = 0;
			int* piVar5 = reinterpret_cast<int*>(GetWinMess(uVar19));
			int* piVar20 = piVar5;
			for (int iVar23 = 0; iVar23 < *piVar5; iVar23++) {
				const char* pcVar12 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar20) + 4)];
				if (pcVar12 != 0) {
					if (*pcVar12 == '$') pcVar12 = pcVar12 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar12);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar20 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar20) + 2);
			}
			iVar10 = iVar14 / 0x16;
			if (iVar14 % 0x16 != 0) iVar10 = iVar10 + 1;
			sVar8 = (iVar10 + 2) * 0x16 + 0x40;
			short sVar18 = *piVar5 * 0x1E + 0x40;
			iVar14 = (int)(float)((double)(0x280 - sVar8) * DOUBLE_803313f8);
			iVar10 = (int)(float)((double)(FLOAT_80331430 - (float)sVar18) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar10;
			int __p14 =  (sVar8 - 0);
			m_menuWindowInfo->width = __p14;
			m_menuWindowInfo->height = sVar18;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_counter1A = 0;
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			if (m_wmWorldState->m_subState == 0xE) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
				if (m_wmWorldState->m_mcResult < 0) goto LAB_chkLoad;
			} else if (m_wmWorldState->m_subState == 5) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
			LAB_chkLoad:
				sVar8 = m_wmWorldState->m_subState;
				short sVar18;
				if (sVar8 == 5) { sVar18 = -1; }
				else if (sVar8 == 6) { sVar18 = -3; }
				else if (sVar8 == 7) { sVar18 = -4; }
				else { sVar18 = 0; }
				if (sVar8 == 7) {
					short chk = m_wmWorldState->m_mcResult;
					if (chk != 0 && chk != sVar18 && chk != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				} else if (m_wmWorldState->m_mcResult != sVar18 && m_wmWorldState->m_mcResult != 1) {
					m_wmWorldState->m_state0E = -1;
					m_wmWorldState->m_counter1A = 1;
					break;
				}
			}
			if ((uVar4 & 0x300) != 0) {
				m_wmWorldState->m_state0E = 1;
				m_wmWorldState->m_counter1A = 10;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar8 = m_wmWorldState->m_counter1A;
			if (sVar8 != 0) {
				m_wmWorldState->m_counter1A = sVar8 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 4:
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(FLOAT_803313e8);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(0);
			iVar14 = 0;
			int* piVar5 = reinterpret_cast<int*>(GetWinMess(6));
			int* piVar20 = piVar5;
			for (int iVar23 = 0; iVar23 < *piVar5; iVar23++) {
				const char* pcVar12 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar20) + 4)];
				if (pcVar12 != 0) {
					if (*pcVar12 == '$') pcVar12 = pcVar12 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar12);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar20 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar20) + 2);
			}
			iVar10 = iVar14 / 0x16;
			if (iVar14 % 0x16 != 0) iVar10 = iVar10 + 1;
			sVar8 = (iVar10 + 2) * 0x16 + 0x40;
			short sVar18 = *piVar5 * 0x1E + 0x40;
			iVar14 = (int)(float)((double)(0x280 - sVar8) * DOUBLE_803313f8);
			iVar10 = (int)(float)((double)(FLOAT_80331430 - (float)sVar18) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar10;
			int __p13 = sVar8;
			m_menuWindowInfo->width = __p13;
			m_menuWindowInfo->height = sVar18;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			short chkResult = (short)GetMcCtrl()->ChkEmpty(1);
			m_wmWorldState->m_mcResult = chkResult;
			if (m_wmWorldState->m_mcResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
				m_wmWorldState->m_state0E = -1;
				m_wmWorldState->m_counter1A = 10;
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar8 = m_wmWorldState->m_counter1A;
			if (sVar8 != 0) {
				m_wmWorldState->m_counter1A = sVar8 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	case 8:
	case 0xB:
	case 0x19: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			int uVar22 = 0;
			int uVar19;
			if (iVar10 == 8) {
				m_wmWorldState->m_cardChannel = 0;
				uVar19 = 4;
			} else if (iVar10 == 0x19) {
				uVar22 = 1;
				uVar19 = 0x19;
				m_wmWorldState->m_cardChannel = 1;
			} else {
				uVar19 = 5;
				m_wmWorldState->m_cardChannel = 1;
			}
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(FLOAT_803313e8);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(uVar22);
			iVar14 = 0;
			int* piVar5 = reinterpret_cast<int*>(GetWinMess(uVar19));
			int* piVar20 = piVar5;
			for (int iVar23 = 0; iVar23 < *piVar5; iVar23++) {
				const char* pcVar12 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar20) + 4)];
				if (pcVar12 != 0) {
					if (*pcVar12 == '$') pcVar12 = pcVar12 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar12);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar20 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar20) + 2);
			}
			iVar10 = iVar14 / 0x16;
			if (iVar14 % 0x16 != 0) iVar10 = iVar10 + 1;
			sVar8 = (iVar10 + 2) * 0x16 + 0x40;
			short sVar18 = *piVar5 * 0x1E + 0x40;
			iVar14 = (int)(float)((double)(0x280 - sVar8) * DOUBLE_803313f8);
			iVar10 = (int)(float)((double)(FLOAT_80331430 - (float)sVar18) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar10;
			m_menuWindowInfo->width = sVar8;
			m_menuWindowInfo->height = sVar18;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A == 0) {
				if (m_wmWorldState->m_subState == 0x19) {
					m_wmWorldState->m_state0E = 1;
					m_wmWorldState->m_counter1A = 0x5A;
					break;
				}
				int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
				m_wmWorldState->m_mcResult = (short)chkRes;
				if (m_wmWorldState->m_mcResult != 0) {
					m_wmWorldState->m_state0E = -1;
					m_wmWorldState->m_counter1A = 10;
				} else {
					if ((uVar7 & 3) != 0) {
						m_wmWorldState->m_cardChannel ^= 1;
						Sound.PlaySe(1, 0x40, 0x7F, 0);
					} else {
						if ((uVar4 & 0x100) != 0) {
							if (m_wmWorldState->m_cardChannel == 0) {
								m_wmWorldState->m_state0E = 1;
							} else {
								m_wmWorldState->m_state0E = -1;
							}
							m_wmWorldState->m_counter1A = 10;
							Sound.PlaySe(2, 0x40, 0x7F, 0);
						} else {
							if ((uVar4 & 0x200) != 0) {
								m_wmWorldState->m_cardChannel = 1;
								m_wmWorldState->m_state0E = -1;
								m_wmWorldState->m_counter1A = 10;
								Sound.PlaySe(3, 0x40, 0x7F, 0);
							}
						}
					}
				}
			}
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A != 0) {
			if (m_wmWorldState->m_subState == 0x19) {
				int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
				m_wmWorldState->m_mcResult = (short)chkRes;
			}
			m_wmWorldState->m_counter1A--;
			if (m_wmWorldState->m_counter1A == 0) {
				m_menuWindowInfo->state = 2;
			}
		}
		break;
	}
	case 0xD:
	case 0x16:
	case 0x1A: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			int uVar22 = 0;
			int uVar19;
			if (iVar10 == 0xD) { uVar19 = 7; }
			else if (iVar10 == 0x1A) { uVar19 = 0x1A; uVar22 = 1; }
			else { uVar19 = 9; }
			CFont* pFont = m_fonts[0];
			pFont->SetMargin(FLOAT_803313e8);
			pFont->SetShadow(0);
			pFont->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(uVar22);
			iVar14 = 0;
			int* piVar5 = reinterpret_cast<int*>(GetWinMess(uVar19));
			int* piVar20 = piVar5;
			for (int iVar23 = 0; iVar23 < *piVar5; iVar23++) {
				const char* pcVar12 = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(piVar20) + 4)];
				if (pcVar12 != 0) {
					if (*pcVar12 == '$') pcVar12 = pcVar12 + 1;
					int iVar25 = (int)(double)pFont->GetWidth(pcVar12);
					if (iVar25 > iVar14) iVar14 = iVar25;
				}
				piVar20 = reinterpret_cast<int*>(reinterpret_cast<int>(piVar20) + 2);
			}
			iVar10 = iVar14 / 0x16;
			if (iVar14 % 0x16 != 0) iVar10 = iVar10 + 1;
			sVar8 = (iVar10 + 2) * 0x16 + 0x40;
			short sVar18 = *piVar5 * 0x1E + 0x40;
			iVar14 = (int)(float)((double)(0x280 - sVar8) * DOUBLE_803313f8);
			iVar10 = (int)(float)((double)(FLOAT_80331430 - (float)sVar18) * DOUBLE_803313f8);
			m_menuWindowInfo->x = (short)iVar14;
			m_menuWindowInfo->y = (short)iVar10;
			m_menuWindowInfo->width = sVar8;
			m_menuWindowInfo->height = sVar18;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
			if (m_wmWorldState->m_menuMode == 8
			    && m_cmakeWork != 0) {
				m_mcCtrl.m_userBuffer = m_cmakeWork;
			} else {
				m_mcCtrl.m_userBuffer = 0;
			}
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			iVar10 = (int)m_wmWorldState->m_subState;
			if (iVar10 == 0xD) {
				GetMcCtrl()->Format(1);
				m_wmWorldState->m_mcResult = (short)m_mcCtrl.m_lastResult;
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			} else if (iVar10 == 0x1A) {
				short erRes = (short)GetMcCtrl()->EraseDat();
				m_wmWorldState->m_mcResult = erRes;
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			} else {
				short ldRes = (short)GetMcCtrl()->LoadDat();
				m_wmWorldState->m_mcResult = ldRes;
			}

			if (m_wmWorldState->m_mcResult != 0) {
				if (m_wmWorldState->m_subState == 0x16) {
					if (m_wmWorldState->m_menuMode != 8 && m_wmWorldState->m_mcResult == 1) {
						gWmMenuWorkB = m_mcCtrl.m_serialHi;
						gWmMenuWorkA = m_mcCtrl.m_serialLo;
						gWmMenuCursorX[0] = (unsigned char)m_mcCtrl.m_cardChannel;
						gWmMenuCursorX[1] = (unsigned char)m_mcCtrl.m_saveIndex;
					} else {
						gWmMenuCursorY[0] = (unsigned char)m_mcCtrl.m_cardChannel;
						gWmMenuCursorY[1] = (unsigned char)m_mcCtrl.m_saveIndex;
					}
					iVar10 = 0;
					int iVar25 = reinterpret_cast<int>(m_wm.m_worldObjData) + 0x7930;
					int iVar23 = 0;
					iVar14 = 0;
					int pOff = 0;
					do {
						int iVar17 = reinterpret_cast<int>(m_wm.m_charaModelData) + iVar10;
						if (m_wmWorldState->m_menuMode == 8
						    && m_cmakeWork != 0) {
							int iVar6 = reinterpret_cast<int>(m_cmakeWork) + iVar23 + 0x14D0;
							if (*reinterpret_cast<int*>(iVar6 + 0x5B4) != 0) {
								unsigned int uVar15b = (unsigned int)*reinterpret_cast<unsigned short*>(iVar6 + 0x2E);
								unsigned int uVar11 = (unsigned int)*reinterpret_cast<unsigned short*>(iVar6 + 0x30);
								unsigned int uVar16 = (unsigned int)*reinterpret_cast<unsigned short*>(iVar6 + 0x32);
								int cost = uVar15b * 200 + 100;
								if (uVar11 != 0) cost = uVar15b * 200 + 200;
								*reinterpret_cast<int*>(iVar17 + 8) = cost + uVar16;
							} else {
								*reinterpret_cast<int*>(iVar17 + 8) = -1;
							}
						} else if (*reinterpret_cast<int*>(iVar25 + 0x1794) != 0) {
							unsigned int uVar15b = (unsigned int)*reinterpret_cast<unsigned short*>(iVar25 + 0x17D0);
							unsigned int uVar11 = (unsigned int)*reinterpret_cast<unsigned short*>(iVar25 + 0x17D2);
							unsigned int uVar16 = (unsigned int)*reinterpret_cast<unsigned short*>(iVar25 + 0x17D4);
							int cost = uVar15b * 200 + 100;
							if (uVar11 != 0) cost = uVar15b * 200 + 200;
							*reinterpret_cast<int*>(iVar17 + 8) = cost + uVar16;
						} else {
							*reinterpret_cast<int*>(iVar17 + 8) = -1;
						}
						iVar17 = reinterpret_cast<int>(m_wm.m_charaModelData) + iVar10;
						int charaId = *reinterpret_cast<int*>(iVar17 + 8);
						int uVar22;
						if (charaId < 0) {
							uVar22 = 3;
							*reinterpret_cast<unsigned char*>(iVar17 + 0xC) = 0;
							charaId = 0x43;
						} else {
							uVar22 = 0;
							*reinterpret_cast<unsigned char*>(iVar17 + 0xC) = 1;
						}
						GetWmCharaHandles(this)[iVar14]->LoadModelASync(uVar22, charaId, 0);
						iVar14++;
						iVar23 += 0x9C0;
						iVar25 += 0xC30;
						pOff += 4;
						iVar10 += 0x34;
					} while (iVar14 < 8);
					if (m_wmWorldState->m_menuMode != 8) {
						m_wmWorldState->m_originalBackupParams[0] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[0]);
						m_wmWorldState->m_backupParams[0] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[0]);
						m_wmWorldState->m_originalBackupParams[1] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[1]);
						m_wmWorldState->m_backupParams[1] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[1]);
						m_wmWorldState->m_originalBackupParams[2] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[2]);
						m_wmWorldState->m_backupParams[2] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[2]);
						m_wmWorldState->m_originalBackupParams[3] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[3]);
						m_wmWorldState->m_backupParams[3] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[3]);
					}
				}
				m_wmWorldState->m_state0E = 1;
				m_wmWorldState->m_counter1A = 10;
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar8 = m_wmWorldState->m_counter1A;
			if (sVar8 != 0) {
				m_wmWorldState->m_counter1A = sVar8 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 0xC: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_flag09 = 1;
			memset(GetWmMenuCharaState(this), 0, kWmMenuCharaStateBytes);
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			short listRes = (short)GetMcCtrl()->LoadMcList();
			m_wmWorldState->m_mcResult = listRes;
			if (m_wmWorldState->m_mcResult != 0) {
				if (m_wmWorldState->m_menuMode == 8) {
					int unk838 = reinterpret_cast<int>(m_wmCharaState);
					int iVar23 = 0;
					int off = 0;
					for (int i = 0; i < 4; i++) {
						if (*reinterpret_cast<char*>(unk838 + off + 0x42) == 0
						    && *reinterpret_cast<int*>(unk838 + off + 8) > 0) {
							iVar23++;
						}
						off += 0x48;
					}
					if (iVar23 == 0) {
						m_wmWorldState->m_mcResult = (short)0xFC19;
					}
				}
				int calTimes[40];
				int unk838 = reinterpret_cast<int>(m_wmCharaState);
				iVar10 = 0;
				iVar14 = 0;
				int* piVar20 = calTimes;
				do {
					int* pSrc = reinterpret_cast<int*>(unk838 + iVar14);
					OSTicksToCalendarTime(*reinterpret_cast<long long*>(pSrc), reinterpret_cast<OSCalendarTime*>(piVar20));
					iVar10++;
					piVar20 += 10;
					iVar14 += 0x48;
				} while (iVar10 < 4);

				int iVar23 = 0;
				iVar10 = 0;
				int bestIdx = -1;
				int* piVar5 = calTimes;
				for (; iVar23 < 4; iVar23++) {
					int iVar17 = bestIdx;
					if (*reinterpret_cast<char*>(unk838 + iVar10 + 0x42) == 0
					    && *reinterpret_cast<int*>(unk838 + iVar10 + 8) > 0) {
						iVar17 = iVar23;
						if (bestIdx >= 0) {
							iVar17 = bestIdx;
							if (calTimes[bestIdx * 10 + 5] <= piVar5[5]
							    && (calTimes[bestIdx * 10 + 5] < piVar5[5]
							        || (calTimes[bestIdx * 10 + 7] <= piVar5[7]
							            && (calTimes[bestIdx * 10 + 7] < piVar5[7]
							                || (calTimes[bestIdx * 10 + 2] <= piVar5[2]
							                    && (calTimes[bestIdx * 10 + 2] < piVar5[2]
							                        || (calTimes[bestIdx * 10 + 1] <= piVar5[1]
							                            && (calTimes[bestIdx * 10 + 1] < piVar5[1]
							                                || (calTimes[bestIdx * 10] <= *piVar5
							                                    && (calTimes[bestIdx * 10] < *piVar5
							                                        || (calTimes[bestIdx * 10 + 8] <= piVar5[8]
							                                            && (calTimes[bestIdx * 10 + 8] < piVar5[8]
							                                                || calTimes[bestIdx * 10 + 9] < piVar5[9])))))))))))) {
								iVar17 = iVar23;
							}
						}
					}
					iVar10 += 0x48;
					piVar5 += 10;
					bestIdx = iVar17;
				}
				if (bestIdx < 0) bestIdx = 0;

				m_wmWorldState->m_cardChannel = (short)bestIdx;
				iVar10 = 0;
				iVar14 = 0;
				for (; iVar10 < 4; iVar10++) {
					if (*reinterpret_cast<char*>(unk838 + iVar14 + 0x42) != 0) {
						m_mcCtrl.m_saveIndex = iVar10;
						m_wmWorldState->m_cardChannel = (short)iVar10;
						break;
					}
					iVar14 += 0x48;
				}
				m_wmWorldState->m_state0E = 1;
				m_wmWorldState->m_counter1A = 10;
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar8 = m_wmWorldState->m_counter1A;
			if (sVar8 != 0) {
				m_wmWorldState->m_counter1A = sVar8 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 0x11: {
		int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.m_cardChannel);
		m_wmWorldState->m_mcResult = (short)chkRes;
		if (m_wmWorldState->m_mcResult == 0 && uVar7 != 0) {
			if ((uVar7 & 8) != 0) {
				if (m_wmWorldState->m_cardChannel <= 0) {
					m_wmWorldState->m_cardChannel = 3;
				} else {
					m_wmWorldState->m_cardChannel--;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				if ((uVar7 & 4) != 0) {
					if (m_wmWorldState->m_cardChannel >= 3) {
						m_wmWorldState->m_cardChannel = 0;
					} else {
						m_wmWorldState->m_cardChannel++;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			if ((uVar7 & 0xC) == 0) {
				if ((uVar4 & 0x100) != 0) {
					sVar8 = m_wmWorldState->m_state0E;
					if (sVar8 != -1 && sVar8 != 1) {
						int unk838 = reinterpret_cast<int>(m_wmCharaState);
						iVar14 = (int)m_wmWorldState->m_cardChannel;
						if (*reinterpret_cast<char*>(unk838 + iVar14 * 0x48 + 0x41) == 0
						    || *reinterpret_cast<char*>(unk838 + iVar14 * 0x48 + 0x42) != 0) {
							Sound.PlaySe(4, 0x40, 0x7F, 0);
						} else {
							m_mcCtrl.m_saveIndex = iVar14;
							m_wmWorldState->m_state0E = 1;
							Sound.PlaySe(2, 0x40, 0x7F, 0);
						}
					}
				}
				if ((uVar4 & 0x200) != 0) {
					sVar8 = m_wmWorldState->m_state0E;
					if (sVar8 != -1 && sVar8 != 1) {
						m_wmWorldState->m_state0E = -1;
						Sound.PlaySe(3, 0x40, 0x7F, 0);
					}
				}
			}
		}
		break;
	}
	}

	if (m_wmWorldState->m_subState != 0) {
		CalcMcObj();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800fca2c
 * PAL Size: 1416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcTitleMenu()
{

	if (static_cast<signed char>(lbl_8032EE38[0]) == 0) {
		DAT_8032EE34 = const_cast<char*>(s_dvd_movie_ffcc_op_thp_801dc448);
		lbl_8032EE38[0] = 1;
	}

	bool bVar1 = false;
	if (Pad.m_debugPadLock != 0 || Pad.m_debugPadPort != -1) {
		bVar1 = true;
	}
	int down;
	if (bVar1) {
		down = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
		down = Pad.GetPadInputs()[padIndex].buttonDown[0];
	}
	down = static_cast<unsigned short>(down);
	const unsigned short repeat = GetButtonRepeat(0);

	{
		if (static_cast<signed char>(m_wmWorldState->m_worldReady) == 0) {
			if (static_cast<signed char>(lbl_8032EE1C) == 1) {
				PPPCREATEPARAM param;
				EffectInfo* titleEffect = &m_effectWork[23];
				titleEffect->m_effectNo = 0x1F;
				CGObject* titleObject = &titleEffect->m_object;
				titleEffect->m_slotNo = 0x17;
				titleObject->Create();
				titleObject->m_charaModelHandle = m_wm.m_handles[23];
				param.m_lookTargetPtr = titleObject;
				param.m_paramB = reinterpret_cast<unsigned int>(titleObject);
				titleEffect->m_partNo = PartMng.pppCreate(0, 0x1F, &param, 1);
				m_wmWorldState->m_delay = 0;
				m_wmWorldState->m_worldReady = 1;
				m_wmWorldState->m_flag09 = 1;
				m_wmThpActive = 0;
				m_wmWorldState->m_titleState = 0;
				m_wmWorldState->m_state0E = -1;
				m_wmWorldState->m_state12 = 0;
				CFlatRuntime::CStack flatArgs[3];
				flatArgs[0].m_word = 9;
				flatArgs[1].m_word = 0;
				flatArgs[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs, 0);
				m_wmWorldState->m_cardChannel = 0;
				lbl_8032EE1C = 0;
				return;
			}
			lbl_8032E8AC = 0;
			THPSimpleInit(1);
			THPSimpleOpen(DAT_8032EE34);
			int thpMemory = THPSimpleCalcNeedMemory();
			m_wmWorkBuffer =
			    static_cast<unsigned char*>(Memory._Alloc(thpMemory, CharaPcs.m_viewerAnimStage, const_cast<char*>(s_wm_menu_cpp), 0xABA, 0));
			THPSimpleSetBuffer(m_wmWorkBuffer);
			THPSimplePreLoad(0);
			THPSimpleAudioStart();
			PPPCREATEPARAM param;
			EffectInfo* titleEffect = &m_effectWork[23];
			titleEffect->m_effectNo = 0x1F;
			CGObject* titleObject = &titleEffect->m_object;
			titleEffect->m_slotNo = 0x17;
			titleObject->Create();
			titleObject->m_charaModelHandle = m_wm.m_handles[23];
			param.m_lookTargetPtr = titleObject;
			param.m_paramB = reinterpret_cast<unsigned int>(titleObject);
			titleEffect->m_partNo = PartMng.pppCreate(0, 0x1F, &param, 1);
			m_wmThpActive = 1;
			m_wmWorldState->m_cardChannel = 0;
			m_wmWorldState->m_delay = 0;
			m_wmWorldState->m_worldReady = 1;
			m_wmWorldState->m_flag09 = 1;
		}

		if (m_wmWorldState->m_mainState == 0) {
			if ((down & 0x1000) != 0) {
				THPSimpleAudioStop();
				THPSimpleLoadStop();
				THPSimpleClose();
				THPSimpleQuit();
				if (m_wmWorkBuffer != 0) {
					Memory.Free(m_wmWorkBuffer);
					m_wmWorkBuffer = 0;
				}
				m_wmThpActive = 0;
				m_wmWorldState->m_titleState = 0;
				m_wmWorldState->m_state0E = -1;
			} else if (THPSimpleDecode(0) == 0) {
				m_wmWorldState->m_frameCounter = static_cast<short>(m_wmWorldState->m_frameCounter + 1);
			}
		}

		if (m_wmWorldState->m_mainState != 2) {
			if (m_wmWorldState->m_mainState < 2) {
				if (MemoryCardMan.McChkConnect(0) == 0) {
					m_wmWorldState->m_cardChannel = 1;
				} else if (MemoryCardMan.McChkConnect(1) == 0) {
					m_wmWorldState->m_cardChannel = 1;
				} else {
					m_wmWorldState->m_cardChannel = 0;
				}
			}
		} else {
			if (m_wmWorldState->m_delay == 0) {
			if ((repeat & 0xC) != 0) {
				m_wmWorldState->m_cardChannel ^= 1;
				m_wmWorldState->m_titleState = 0;
				m_wmWorldState->m_state12 = 0;
				m_wmWorldState->m_flag09 = 0;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else if ((down & 0x100) != 0) {
				if (m_wmWorldState->m_cardChannel == 0) {
					gWmMenuWorkB = -1;
					gWmMenuWorkA = -1;
					gWmMenuCursorX[0] = -1;
					gWmMenuCursorX[1] = -1;
					Game.InitNewGame();
				}
				m_wmWorldState->m_delay = 0x14;
				m_wmWorldState->m_state0E = 1;
				Sound.PlaySe(0x0B, 0x40, 0x7F, 0);
			} else if ((down & 0x200) != 0) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}

			if (repeat == 0) {
				m_wmWorldState->m_frameCounter = static_cast<short>(m_wmWorldState->m_frameCounter + 1);
			} else {
				m_wmWorldState->m_frameCounter = 0;
			}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800fc4bc
 * PAL Size: 1392b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcGoOutCharaSelect(unsigned char state)
{
	if (m_wmWorldState->m_mainState != 2) {
		return;
	}

	int validCount = 0;
	if (m_cmakeWorkActive == 1) {
		for (int ci = 0; ci < 8; ci++) {
			if (*reinterpret_cast<int*>(m_cmakeWork + 0x1A84 + ci * 0x9C0) != 0) {
				validCount++;
			}
		}
	} else {
		unsigned char* caravan = reinterpret_cast<unsigned char*>(&Game);
		if (*reinterpret_cast<int*>(caravan + 0x1794) != 0) {
			validCount = 1;
		}
		for (int ci = 0; ci < 7; ci++) {
			caravan += 0xC30;
			if (*reinterpret_cast<int*>(caravan + 0x1794) != 0) {
				validCount++;
			}
		}
	}

	int loadedCount = 0;
	for (int i = loadedCount; i < 8; i++) {
		const int handleIdx = i + 0x20;
		CCharaPcs::CHandle* const handle = m_wm.m_handles[handleIdx];
		if (handle->m_charaKind != 3 && handle->IsLoadModelASyncCompleted() != 0) {
			loadedCount++;
		}
	}

	if (loadedCount != validCount) {
		return;
	}
	WmCharaSelectEntry& entry = *reinterpret_cast<WmCharaSelectEntry*>(m_wm.m_charaSelectData);
	if (entry.m_confirmed != 0) {
		return;
	}

	entry.m_padType = Joybus.GetPadType(0);
	if (entry.m_padType == 0x09000000 || entry.m_padType == -0x74F00000 || entry.m_padType == -0x78000000) {
		entry.m_connected = 1;
	} else if (Game.m_gameWork.m_menuStageMode == 0) {
		entry.m_connected = Joybus.GetGBAConnect(0);
	} else {
		entry.m_connected = 0;
	}

	unsigned short repeat;
	unsigned short down;
	if (entry.m_connected == 1 && entry.m_cmakePending == 0) {
		const int port = 0;
		bool noRepeatInput = true;
		if (Pad.m_debugPadLock == 0) {
			bool hasPort = false;
			if (port == 0 && Pad.m_debugPadPort != -1) {
				hasPort = noRepeatInput;
			}
			if (!hasPort) {
				noRepeatInput = false;
			}
		}
		int repeatTmp;
		if (noRepeatInput) {
			repeatTmp = 0;
		} else {
			u32 clamped = (Pad.m_debugPadPort == port) ? 0 : port;
			repeatTmp = Pad.GetPadInputs()[clamped].repeatButton;
		}
		repeat = static_cast<unsigned short>(repeatTmp);

		bool noDownInput = true;
		if (Pad.m_debugPadLock == 0) {
			bool hasPort = false;
			if (port == 0 && Pad.m_debugPadPort != -1) {
				hasPort = noDownInput;
			}
			if (!hasPort) {
				noDownInput = false;
			}
		}
		int downTmp;
		if (noDownInput) {
			downTmp = 0;
		} else {
			u32 clamped = (Pad.m_debugPadPort == port) ? 0 : port;
			downTmp = Pad.GetPadInputs()[clamped].buttonDown[0];
		}
		down = static_cast<unsigned short>(downTmp);
	} else {
		repeat = 0;
		down = repeat;
	}

	if (m_wmWorldState->m_mainState != 2 || m_wmWorldState->m_nextMenuMode != 0) {
		return;
	}

	WmCharaSelectEntry& curEntry = *reinterpret_cast<WmCharaSelectEntry*>(m_wm.m_charaSelectData);
	int cursor = static_cast<int>(curEntry.m_currentSlot);
	if ((repeat & 0x0C) != 0) {
		if (cursor < 4) {
			cursor += 4;
		} else {
			cursor -= 4;
		}
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	}

	if ((repeat & 1) != 0) {
		const int row = static_cast<int>(cursor) >> 2;
		if (cursor > ((row != 0) ? 4 : 0)) {
			cursor--;
		} else {
			cursor += 3;
		}
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	} else if ((repeat & 2) != 0) {
		int rowEnd = 3;
		if ((cursor >> 2) != 0) {
			rowEnd = 7;
		}
		if (cursor < rowEnd) {
			cursor++;
		} else {
			cursor -= 3;
		}
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	}

	curEntry.m_currentSlot = static_cast<short>(cursor);
	if ((repeat & 0x6F) != 0) {
		return;
	}

	if ((down & 0x100) != 0) {
		if (m_cmakeWorkActive == 1 && m_cmakeWork != 0) {
				unsigned char* cmakeSlot = m_cmakeWork;
			cmakeSlot += curEntry.m_currentSlot * 0x9C0;
			if (*reinterpret_cast<int*>(cmakeSlot + 0x1A84) == 0) {
				goto se_empty;
			}
			goto se_full;
		}

		if (Game.m_caravanWorkArr[curEntry.m_currentSlot].m_shopState == 0) {
		se_empty:
			Sound.PlaySe(4, 0x40, 0x7F, 0);
		} else {
		se_full:
			curEntry.m_confirmed = 1;
			Sound.PlaySe(0x33, 0x40, 0x7F, 0);
			if (state != 0) {
				GetWmCharaAnimState(this)[cursor * 5 + 1] = 3;
			}
		}
	} else if ((down & 0x200) != 0) {
		*reinterpret_cast<unsigned char*>(&curEntry._pad0E) = 1;
		Sound.PlaySe(0x34, 0x40, 0x7F, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800fc234
 * PAL Size: 648b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CalcGoOutSelChar(unsigned char state, unsigned char slot)
{
	if (m_wmWorldState->m_mainState > 4) {
		return -1;
	}

	if (state != 0) {
		CalcGoOutCharaSelect(slot);
	}

	const short menuAnim = m_wmWorldState->m_mainState;
	int offset;
	if (menuAnim == 0) {
		offset = static_cast<int>(m_wmWorldState->m_frameCounter) - 10;
	} else if (menuAnim > 0 && menuAnim < 4) {
		offset = 0;
	} else {
		offset = -static_cast<int>(m_wmWorldState->m_frameCounter);
	}

	*reinterpret_cast<short*>(m_wm.m_frameInfo + 4) = 0x10;
	*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20) =
	    static_cast<short>(static_cast<int>(FLOAT_803313e0 - static_cast<float>(static_cast<double>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 8) + *reinterpret_cast<short*>(m_wm.m_frameInfo + 4)))));

	if (offset < 0) {
		float shift = static_cast<float>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 8) + *reinterpret_cast<short*>(m_wm.m_frameInfo + 4));
		if (offset >= -10) {
			shift = static_cast<float>(static_cast<double>(shift) * (DOUBLE_803314e8 * static_cast<double>(offset < 0 ? -offset : offset)));
			int absOffset =  (s32)(offset < 0 ? -offset : offset);
			if (absOffset < 0) {
				absOffset = 0;
			}
			if (absOffset > 10) {
				absOffset = 10;
			}
			int __p1 = absOffset;
			const float t = static_cast<float>(__p1);
			shift *= static_cast<float>(sin(FLOAT_803314bc * (t * FLOAT_803316d4)));
		}

		*reinterpret_cast<short*>(m_wm.m_frameInfo + 4) =
		    static_cast<short>(static_cast<float>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 4)) - shift);
		*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20) =
		    static_cast<short>(static_cast<float>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20)) + shift);
	}

	if (m_wmWorldState->m_mainState > 0 && m_wmWorldState->m_mainState < 4) {
		CalcChara();
	}

	if (m_wm.m_charaSelectData[0x0E] != 0) {
		return -2;
	}

	if (m_wm.m_charaSelectData[0x0A] != 0 &&
	    (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_wmCharaAnimState) + *reinterpret_cast<short*>(m_wm.m_charaSelectData + 4) * 0x14) != 3 || slot == 0)) {
		return static_cast<int>(*reinterpret_cast<short*>(m_wm.m_charaSelectData + 4));
	}

	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x800fc220
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcGoOutSelCharInit()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x16] = 0;
	bytes[0x17] = 0;
	bytes[0xE] = 0;
	bytes[0xF] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800fc20c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMenuCharaAnim(int charaIndex, int animIndex)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int* const menuCharaAnims = m_wmCharaAnimState;

	menuCharaAnims[charaIndex * 5 + 1] = animIndex;
}

/*
 * --INFO--
 * PAL Address: 0x800fc220
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetMenuCharaAnim__8CMenuPcsFii2(CMenuPcs* menuPcs)
{
	unsigned char* const data = menuPcs->m_wm.m_charaSelectData;

	data[0xA] = 0;
	data[0xE] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800fc1f4
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::IsMenuCharaAnimIdle(int charaIndex)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const menuCharaAnims = reinterpret_cast<unsigned char*>(m_wmCharaAnimState);

	return static_cast<unsigned int>(__cntlzw(reinterpret_cast<unsigned int*>(menuCharaAnims + charaIndex * 0x14)[0])) >> 5 & 0xff;
}

/*
 * --INFO--
 * PAL Address: 0x800fc0b0
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawWorld()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	if (static_cast<signed char>(bytes[0xD]) == 0) {
		unsigned char* menuSlot = bytes + 0x10;
		for (int i = 4; i < 6; i++) {
			CMenu* const menu = *reinterpret_cast<CMenu**>(menuSlot + 0x10C);
			menu->Draw();
			menuSlot += 4;
		}
	} else {
		const short menuMode = m_wmWorldState->m_menuMode;

		switch (menuMode) {
		case 0:
			DrawMainMenu();
			break;
		case 1:
			DrawDiaryMenu();
			break;
		case 2:
			DrawMCardMenu();
			break;
		case 3:
			if (m_singleCmakeMode == 0) {
				DrawCMakeMenu();
			} else {
				DrawSingCMake();
			}
			break;
		case 4:
			DrawMoveMenu();
			break;
		case 5:
			DrawLoadMenu();
			break;
		case 6:
			DrawTitleMenu();
			break;
		case 7:
			DrawOptionMenu();
			break;
		case 8:
			DrawGoOutMenu();
			break;
		default:
			if (static_cast<unsigned int>(System.m_execParam) >= 1) {
				System.Printf(const_cast<char*>(s__s__d___Error_WM_menu_no_error___801dc424), s_wm_menu_cpp, 0xC59);
			}
			break;
		}

		unsigned char* menuSlot = bytes + 0x10;
		for (int i = 4; i < 6; i++) {
			CMenu* const menu = *reinterpret_cast<CMenu**>(menuSlot + 0x10C);
			menu->Draw();
			menuSlot += 4;
		}
		DrawInit();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800fb910
 * PAL Size: 1952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_propagation off
#pragma opt_lifetimes off
void CMenuPcs::DrawMainMenu()
{
	extern double DOUBLE_803314E8;
	extern double DOUBLE_803313F8;
	extern double DOUBLE_803314F0;
	extern double DOUBLE_803314D0;
	extern float FLOAT_803316D0;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	short state = m_wmWorldState->m_mainState;
	float frameAlpha;
	if (state == 0) {
		frameAlpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
	} else if (state > 0 && state < 4) {
		frameAlpha = FLOAT_803313e8;
	} else {
		frameAlpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) - DOUBLE_80331420));
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor matColor;
	matColor.r = 0xFF;
	matColor.g = 0xFF;
	matColor.b = 0xFF;
	matColor.a = static_cast<unsigned char>(static_cast<int>(DOUBLE_80331508 * static_cast<double>(frameAlpha)));
	GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
	int bit = 0;
	int offset = 0;
	do {
		if (((1 << bit) & 1) != 0) {
			short* const entry = reinterpret_cast<short*>(m_wm.m_frameInfo + offset + 4);
			MenuPcs.DrawRect(*reinterpret_cast<unsigned int*>(entry + 0xC), static_cast<float>(entry[0]),
			                 static_cast<float>(entry[1]), static_cast<float>(entry[2]), static_cast<float>(entry[3]),
			                 *reinterpret_cast<float*>(entry + 4), *reinterpret_cast<float*>(entry + 6),
			                 FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
		bit++;
		offset += 0x1C;
	} while (bit < 2);

	if (m_wmWorldState->m_mainState >= 1 && m_wmWorldState->m_mainState <= 3) {
		const short tileState = m_wmWorldState->m_mainState;
		float tileAlpha;
		if (tileState == 1) {
			tileAlpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else if (tileState == 2) {
			tileAlpha = FLOAT_803313e8;
		} else {
			tileAlpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) - DOUBLE_80331420));
		}
		tileAlpha = static_cast<float>(static_cast<double>(tileAlpha) * DOUBLE_803313F8);
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		GXColor tileColor;
		tileColor.r = 0xFF;
		tileColor.g = 0xFF;
		tileColor.b = 0xFF;
		tileColor.a = static_cast<unsigned char>(static_cast<int>(DOUBLE_80331508 * static_cast<double>(tileAlpha)));
		GXSetChanMatColor(static_cast<GXChannelID>(4), tileColor);
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x33));
		float x = FLOAT_80331410;
		float y = FLOAT_80331440;
		y = y - x;
		MenuPcs.DrawRect(0, x, y, FLOAT_803316D0, FLOAT_80331500, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8,
		                 FLOAT_803313e8, FLOAT_803313dc);
		MenuPcs.DrawRect(8, x + FLOAT_803316D0, y,
		                 FLOAT_803316D0, FLOAT_80331500, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		y = y + FLOAT_80331500;
		MenuPcs.DrawRect(4, x, y, FLOAT_803316D0, FLOAT_80331500, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8,
		                 FLOAT_803313e8, FLOAT_803313dc);
		MenuPcs.DrawRect(0xC, x + FLOAT_803316D0, y,
		                 FLOAT_803316D0, FLOAT_80331500, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
	}

	DrawMainMenuSub();
	PSMTXCopy(reinterpret_cast<float(*)[4]>(bytes + 0x744), CameraPcs.m_cameraMatrix);
	GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0xFFFFFF);
	Mtx44 projectionMtx;
	PSMTX44Copy(CameraPcs.m_screenMatrix, projectionMtx);
	GXSetProjection(projectionMtx, GX_PERSPECTIVE);
	Graphic.SetViewport();
	GXSetScissor(0, 0, 0x280, 0x1C0);
	DrawInit();

	if (m_wmWorldState->m_mainState > 0 && m_wmWorldState->m_mainState < 4) {
		const int helpState = m_wmWorldState->m_mainState;
		float helpAlpha;
		if (helpState == 1) {
			helpAlpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else if (helpState == 2) {
			helpAlpha = FLOAT_803313e8;
		} else {
			helpAlpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) - DOUBLE_80331420));
		}
		if (static_cast<double>(helpAlpha) > DOUBLE_803314F0) {
			MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			const double helpColorAlpha = static_cast<double>(FLOAT_80331458 * helpAlpha);
			GXColor helpColor;
			helpColor.r = 0xFF;
			helpColor.g = 0xFF;
			helpColor.b = 0xFF;
			helpColor.a = static_cast<unsigned char>(static_cast<int>(helpColorAlpha));
			GXSetChanMatColor(static_cast<GXChannelID>(4), helpColor);
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1F));
			MenuPcs.DrawRect(0, FLOAT_803313dc, static_cast<float>(DOUBLE_803314D0 - static_cast<double>(FLOAT_80331440)),
			                 FLOAT_803313e0, FLOAT_80331440, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

			char* textList[5] = { 0, 0, 0, 0, 0 };
			const int languageIndex = Game.m_gameWork.m_languageId - 1;
			unsigned int ti;
			char** const langText = &lbl_80210750[languageIndex * 0x0B];
			ti = 0;
			textList[0] = langText[ti];
			ti = 1;
			textList[1] = langText[ti];
			ti = 2;
			textList[2] = langText[ti];
			ti = 3;
			textList[3] = langText[ti];
			ti = 4;
			textList[4] = langText[ti];
			unsigned int textAlpha;
			if (helpAlpha > FLOAT_803313e8) {
				textAlpha = 0xFF;
			} else {
				textAlpha = static_cast<unsigned int>(static_cast<int>(helpColorAlpha));
			}
			CColor textColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF));
			char* const text = textList[m_wmWorldState->m_cardChannel];
			const int x = static_cast<int>(CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8));
			DrawFont2(x, static_cast<int>(FLOAT_803317D0), textColor.color, 7, text,
			          FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
		}
	}

	if (m_wmWorldState->m_mainState != 2) {
		m_wmWorldState->m_frameCounter++;
		if (m_wmWorldState->m_frameCounter >= 10) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			if (m_wmWorldState->m_mainState >= 5) {
				m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
				m_wmWorldState->m_nextMenuMode = 0;
			}
		}
	} else {
		if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_delay != 0) {
			m_wmWorldState->m_delay--;
			if (m_wmWorldState->m_delay <= 0) {
				m_wmWorldState->m_mainState++;
				m_wmWorldState->m_frameCounter = 0;
				Sound.PlaySe(0x31, 0x40, 0x7F, 0);
			}
		}
	}
}
#pragma opt_lifetimes on
#pragma opt_propagation on

/*
 * --INFO--
 * PAL Address: 0x800fb440
 * PAL Size: 1232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawDiaryMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	GetWmWorldHandles(this)[1]->m_model->m_lightAlpha = FLOAT_803313e8;
	{
		unsigned char* const worldObj = m_wm.m_worldObjData;
		Mtx44 projectionMtx;
		C_MTXPerspective(projectionMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
		GXSetProjection(projectionMtx, GX_PERSPECTIVE);
		PSMTX44Copy(projectionMtx, CameraPcs.m_screenMatrix);
		Mtx lookAtMtx;
		C_MTXLookAt(lookAtMtx, reinterpret_cast<Vec*>(worldObj + 0x60),
		            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc)),
		            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc)));
		PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(m_wm.m_pad744));
		PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
		CharaPcs.InitEnv(5);
		GXSetColorUpdate(0);
		GXSetAlphaUpdate(0);
		GXSetCopyClear(CColor(0, 0, 0, 0).color, 0xFFFFFF);
		GXSetColorUpdate(1);
		GXSetAlphaUpdate(1);
		GXSetViewport(static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x58)),
		              static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x5A)),
		              static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x5C)),
		              static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x5E)), FLOAT_803313dc, FLOAT_803313e8);
		GXSetScissor(*reinterpret_cast<unsigned int*>(worldObj + 0x90), *reinterpret_cast<unsigned int*>(worldObj + 0x94),
		             *reinterpret_cast<unsigned int*>(worldObj + 0x98), *reinterpret_cast<unsigned int*>(worldObj + 0x9C));
		GetWmWorldHandles(this)[1]->Draw(5);
		PSMTXCopy(reinterpret_cast<MtxPtr>(m_wm.m_pad744), CameraPcs.m_cameraMatrix);
		GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0xFFFFFF);
		PSMTX44Copy(CameraPcs.m_screenMatrix, projectionMtx);
		GXSetProjection(projectionMtx, GX_PERSPECTIVE);
		Graphic.SetViewport();
		GXSetScissor(0, 0, 0x280, 0x1C0);
		DrawInit();
	}

	const int state = m_wmWorldState->m_mainState;
	if (state >= 1 && state <= 3) {
		float alpha;
		if (state == 1) {
			alpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else if (state == 2) {
			alpha = FLOAT_803313e8;
		} else {
			alpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) -
			                             DOUBLE_80331420));
		}
		DrawDiaryBase(0, alpha);
	}

	DrawInit();

	const int frame = static_cast<int>(System.m_frameCounter);
	const int rem = (frame - frame / 0x14 * 0x14) - 10;
	const int remSign = rem >> 31;
	const int phase = (rem ^ remSign) - remSign;
	const float scale = static_cast<float>(DOUBLE_80331450 * static_cast<double>(phase) + DOUBLE_80331448);
	float x = static_cast<float>(DOUBLE_80331438 - static_cast<double>(FLOAT_80331440));
	float y = FLOAT_80331444;
	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(
	    FLOAT_80331458 * static_cast<float>(DOUBLE_80331460 * static_cast<double>(phase) + DOUBLE_803313F8)));
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	SetTexture(static_cast<CMenuPcs::TEX>(0x2B));
	x = static_cast<float>((FLOAT_80331468 - FLOAT_80331468 * scale) * DOUBLE_803313F8 + static_cast<double>(x));
	y = static_cast<float>((FLOAT_80331440 - FLOAT_80331440 * scale) * DOUBLE_803313F8 + static_cast<double>(y));
	if ((bytes[0xF] & 2) != 0) {
		DrawRect(8, x, y, FLOAT_80331468, FLOAT_80331440, FLOAT_803313dc, FLOAT_803313dc, scale, scale, FLOAT_803313dc);
	}
	x = x + FLOAT_8033146c;
	if ((bytes[0xF] & 1) != 0) {
		DrawRect(0, x, y, FLOAT_80331468, FLOAT_80331440, FLOAT_803313dc, FLOAT_803313dc, scale, scale, FLOAT_803313dc);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800fa1cc
 * PAL Size: 4724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMCardMenu()
{
	extern double DOUBLE_803317d8;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	Mtx savedCamera;
	Mtx44 projMtx;
	Mtx44 screenMtx;

	short state = m_wmWorldState->m_mainState;
	if (state > 0 && state < 4) {
		double alpha;
		if (state == 1) {
			double raw;
			reinterpret_cast<int*>(&raw)[0] = 0x43300000;
			reinterpret_cast<int*>(&raw)[1] = (int)m_wmWorldState->m_frameCounter ^ 0x80000000;
			alpha = (double)(float)(DOUBLE_803314e8 * (raw - DOUBLE_80331408));
		} else if (state == 2) {
			alpha = (double)FLOAT_803313e8;
		} else {
			double raw;
			reinterpret_cast<int*>(&raw)[0] = 0x43300000;
			reinterpret_cast<int*>(&raw)[1] = (int)m_wmWorldState->m_frameCounter ^ 0x80000000;
			alpha = (double)(float)-(DOUBLE_803314e8 * (raw - DOUBLE_80331408) - DOUBLE_80331420);
		}
		if (alpha > DOUBLE_803314f0) {
			MenuPcs.SetAttrFmt((FMT)0);
			_GXColor bgColor;
			bgColor.r = 0xFF;
			bgColor.g = 0xFF;
			bgColor.b = 0xFF;
			bgColor.a = (unsigned char)(int)((double)FLOAT_80331458 * alpha);
			GXSetChanMatColor(GX_COLOR0A0, bgColor);
			MenuPcs.SetTexture((TEX)0x1F);
			MenuPcs.DrawRect(0, FLOAT_803313dc,
			         (float)(DOUBLE_803314d0 - (double)FLOAT_80331440),
			         FLOAT_803313e0, FLOAT_80331440,
			         FLOAT_803313dc, FLOAT_803313dc,
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
	}

	DrawMCList();

	if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_subState >= 0x11) {
		float cursorY = (float)((double)FLOAT_803314d8 - DOUBLE_803317d8);
		float cursorXbase = FLOAT_803314d8 + FLOAT_80331410;
		unsigned int saveIdx;
		if (m_wmWorldState->m_subState == 0x11) {
			saveIdx = (unsigned int)m_wmWorldState->m_cardChannel;
		} else {
			saveIdx = (unsigned int)m_mcCtrl.m_saveIndex;
		}
		double rawIdx;
		reinterpret_cast<int*>(&rawIdx)[0] = 0x43300000;
		reinterpret_cast<int*>(&rawIdx)[1] = saveIdx ^ 0x80000000;
		float cursorX = (float)(DOUBLE_80331498 * (rawIdx - DOUBLE_80331408) + (double)cursorXbase);
		MenuPcs.SetAttrFmt((FMT)0);
		_GXColor cursorColor;
		cursorColor.r = 0xFF;
		cursorColor.g = 0xFF;
		cursorColor.b = 0xFF;
		cursorColor.a = 0xFF;
		GXSetChanMatColor(GX_COLOR0A0, cursorColor);
		MenuPcs.SetTexture((TEX)0);
		MenuPcs.DrawRect(0, (float)(int)cursorY, (float)(int)cursorX,
		         FLOAT_80331410, FLOAT_80331410,
		         FLOAT_803313dc, FLOAT_803313dc,
		         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

		// 3D character viewports (4 slots)
		int* piVar12 = reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_worldObjData) + 0x550);
		int charaOff = 0;
		unsigned int* serial = &m_mcCtrl.m_serialHi;
		int viewBase = 0x550;
		int i =  (int)(unsigned int)(0);
		do {
			if (*piVar12 != 0) {
				int slot = reinterpret_cast<int>(m_wm.m_worldObjData) + viewBase;
				C_MTXPerspective(projMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
				GXSetProjection(projMtx, GX_PERSPECTIVE);
				PSMTX44Copy(projMtx, CameraPcs.m_screenMatrix);
				CVector target(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc);
				CVector up(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc);
				C_MTXLookAt(savedCamera, (Vec*)(slot + 0x10), (Vec*)&up, (Vec*)&target);
				PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(bytes + 0x744));
				PSMTXCopy(savedCamera, CameraPcs.m_cameraMatrix);
				CharaPcs.InitEnv(5);
				GXSetColorUpdate(0);
				GXSetAlphaUpdate(0);
				CColor clear(0, 0, 0, 0);
				GXColor clearColor = *(_GXColor*)&clear;
				GXSetCopyClear(clearColor, 0xFFFFFF);
				GXSetColorUpdate(1);
				GXSetAlphaUpdate(1);
				GXSetViewport(
					(float)*reinterpret_cast<short*>(slot + 8),
					(float)*reinterpret_cast<short*>(slot + 0xa),
					(float)*reinterpret_cast<short*>(slot + 0xc),
					(float)*reinterpret_cast<short*>(slot + 0xe),
					FLOAT_803313dc, FLOAT_803313e8);
				GXSetScissor(*reinterpret_cast<int*>(slot + 0x40), *reinterpret_cast<int*>(slot + 0x44),
				             *reinterpret_cast<int*>(slot + 0x48), *reinterpret_cast<int*>(slot + 0x4c));
				Graphic.SetFog(1, 0);
				LightPcs.SetAmbient(gWmMenuLightTables[0].m_ambient);
				LightPcs.SetNumDiffuse(gWmMenuLightTables[0].m_diffuseCount);
				for (int j = 0; j < gWmMenuLightTables[0].m_diffuseCount; j++) {
					LightPcs.SetDiffuse(
						j, gWmMenuLightTables[0].m_diffuseColors[j],
						&gWmMenuLightTables[0].m_diffuseDirs[j], 0);
				}
				LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
				reinterpret_cast<CCharaPcs::CHandle*>(serial[0x1dd])->Draw(5);
				int partA = *reinterpret_cast<int*>(m_bonusListPtr + charaOff + 0x5768);
				if (partA >= 0) {
					PartPcs.DrawMenuIdx(partA);
				}
				int partB = *reinterpret_cast<int*>(m_bonusListPtr + charaOff + 0x6bf8);
				if (partB >= 0) {
					PartPcs.DrawMenuIdx(partB);
				}
			}
			i++;
			viewBase += 0x50;
			serial++;
			piVar12 += 0x14;
			charaOff += 0x524;
		} while (i < 4);
		DrawInit();
		PSMTXCopy(reinterpret_cast<MtxPtr>(bytes + 0x744), CameraPcs.m_cameraMatrix);
		GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0xFFFFFF);
		PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
		GXSetProjection(screenMtx, GX_PERSPECTIVE);
		Graphic.SetViewport();
		GXSetScissor(0, 0, 0x280, 0x1C0);
		DrawInit();
	}

	// State machine for MC operations
	state = m_wmWorldState->m_mainState;
	if (state == 2 && m_wmWorldState->m_delay == 0) {
		short winState;
		short subState = m_wmWorldState->m_subState;
		switch ((int)subState) {
		case 0:
		case 2:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(0, 0);
				float rectY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float rectX = (float)GetSlotABXPos((int)m_wmWorldState->m_cardChannel);
				MenuPcs.SetAttrFmt((FMT)0);
				_GXColor curColor;
				curColor.r = 0xFF;
				curColor.g = 0xFF;
				curColor.b = 0xFF;
				curColor.a = 0xFF;
				GXSetChanMatColor(GX_COLOR0A0, curColor);
				MenuPcs.SetTexture((TEX)0);
				MenuPcs.DrawRect(0, (float)(int)rectX,
				         (float)(int)rectY,
				         FLOAT_80331410, FLOAT_80331410,
				         FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				if (m_wmWorldState->m_state0E < 0) {
					m_wmWorldState->m_nextMenuMode = -1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 1;
				} else if (m_wmWorldState->m_subState == 2) {
					m_wmWorldState->m_subState = 3;
				} else {
					m_wmWorldState->m_subState = 1;
				}
			}
			break;
		case 1:
			if (m_wmWorldState->m_frameCounter >= 0x13) {
				m_wmWorldState->m_subState = 3;
			}
			m_wmWorldState->m_frameCounter++;
			break;
		case 3:
			if (m_wmWorldState->m_mcResult != 1) {
				memset(m_wmCharaState, 0, kWmMenuCharaStateBytes);
				short mcResult = m_wmWorldState->m_mcResult;
				if (mcResult == -1) m_wmWorldState->m_subState = 5;
				else if (mcResult == -2) m_wmWorldState->m_subState = 8;
				else if (mcResult == -3) m_wmWorldState->m_subState = 6;
				else if (mcResult == -4) m_wmWorldState->m_subState = 7;
				else if (mcResult == 0) m_wmWorldState->m_subState = 4;
			}
			break;
		case 5:
		case 6:
		case 7:
		case 9:
		case 10:
		case 0x0E:
		case 0x0F:
		case 0x14:
		case 0x15:
		case 0x1B:
		case 0x1C:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int msgParam = 0;
				int msgId;
				short ss = m_wmWorldState->m_subState;
				if (ss == 5) msgId = 1;
				else if (ss == 6) msgId = 2;
				else if (ss == 7) msgId = 3;
				else if (ss == 9) msgId = 10;
				else if (ss == 10) msgId = 0xb;
				else if (ss == 0x0E) msgId = 0xc;
				else if (ss == 0x0F) msgId = 0xd;
				else if (ss == 0x1C) { msgId = 0x1b; msgParam = 1; }
				else if (ss == 0x1B) { msgId = 0x1c; msgParam = 1; }
				else if (ss == 0x15) msgId = 0xe;
				else msgId = 0xf;
				DrawMcWinMess(msgId, msgParam);
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				short ss = m_wmWorldState->m_subState;
				if (m_wmWorldState->m_state0E < 0 || ss == 0x14 || ss == 0x1c || ss == 0x1b) {
					m_wmWorldState->m_subState = 3;
				} else if (ss == 0x0E) {
					memset(m_wmCharaState, 0, kWmMenuCharaStateBytes);
					m_wmWorldState->m_subState = 0x11;
					m_wmWorldState->m_cardChannel = 0;
				} else if (ss == 0x15) {
					m_wmWorldState->m_subState = 0x11;
					m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
					if (m_wmWorldState->m_menuMode == 8) {
						m_wmWorldState->m_nextMenuMode = -1;
						m_wmWorldState->m_delay = 0xb;
						m_wmTransitionCode = 3;
					}
				} else {
					m_wmWorldState->m_subState = 2;
				}
			}
			break;
		case 4:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(6, 0);
				short r = m_wmWorldState->m_mcResult;
				if (r != 0 && r == 1) {
					m_wmWorldState->m_subState = 0xc;
				}
			} else if (winState == 2 && m_menuWindowInfo->state == 3) {
				short mcRes = m_wmWorldState->m_mcResult;
				if (mcRes == -2) m_wmWorldState->m_subState = 9;
				else if (mcRes == -3) m_wmWorldState->m_subState = 8;
				else if (mcRes == -4) m_wmWorldState->m_subState = 8;
				else if (mcRes == -5) m_wmWorldState->m_subState = 7;
				else m_wmWorldState->m_subState = 10;
			}
			break;
		case 8:
		case 0x0B:
		case 0x12:
		case 0x19:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int msgParam = 0;
				int msgId;
				short ss = m_wmWorldState->m_subState;
				if (ss == 8) msgId = 4;
				else if (ss == 0x0B) msgId = 5;
				else if (ss == 0x19) { msgId = 0x19; msgParam = 1; }
				else msgId = 0x12;
				DrawMcWinMess(msgId, msgParam);
				float rectY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float rectX = (float)GetYesNoXPos((int)m_wmWorldState->m_cardChannel);
				if (m_wmWorldState->m_subState != 0x19) {
					MenuPcs.SetAttrFmt((FMT)0);
					_GXColor ynColor;
					ynColor.r = 0xFF;
					ynColor.g = 0xFF;
					ynColor.b = 0xFF;
					ynColor.a = 0xFF;
					GXSetChanMatColor(GX_COLOR0A0, ynColor);
					MenuPcs.SetTexture((TEX)0);
					MenuPcs.DrawRect(0, (float)(int)rectX,
					         (float)(int)rectY,
					         FLOAT_80331410, FLOAT_80331410,
					         FLOAT_803313dc, FLOAT_803313dc,
					         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				} else {
					short ss2 = m_wmWorldState->m_mcResult;
					if (ss2 < 0) {
						if (ss2 == -1) m_wmWorldState->m_subState = 5;
						else if (ss2 == -2) m_wmWorldState->m_subState = 8;
						else if (ss2 == -3) m_wmWorldState->m_subState = 6;
						else m_wmWorldState->m_subState = 7;
					}
				}
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				short ss = m_wmWorldState->m_subState;
				if (ss == 0x12) {
					if (m_wmWorldState->m_state0E < 0) {
						m_wmWorldState->m_subState = 0x11;
						m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
					} else {
						m_wmWorldState->m_subState = 0x13;
					}
				} else {
					short ss2 = m_wmWorldState->m_mcResult;
					if (ss2 < 0) {
						if (ss2 == -1) m_wmWorldState->m_subState = 5;
						else if (ss2 == -2) m_wmWorldState->m_subState = 8;
						else if (ss2 == -3) m_wmWorldState->m_subState = 6;
						else m_wmWorldState->m_subState = 7;
					} else if (m_wmWorldState->m_state0E < 0) {
						if (ss == 0x19) {
							m_wmWorldState->m_subState = 0x11;
							m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
						} else {
							m_wmWorldState->m_subState = 2;
						}
					} else if (ss == 8) {
						m_wmWorldState->m_subState = 0xb;
					} else if (ss == 0x19) {
						m_wmWorldState->m_subState = 0x1a;
					} else {
						m_wmWorldState->m_subState = 0xd;
					}
				}
			}
			break;
		case 0x0D:
		case 0x13:
		case 0x1A:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int msgParam = 0;
				int msgId;
				short ss = m_wmWorldState->m_subState;
				if (ss == 0xd) msgId = 7;
				else if (ss == 0x1A) { msgId = 0x1a; msgParam = 1; }
				else msgId = 8;
				DrawMcWinMess(msgId, msgParam);
			} else if (winState == 2 && m_menuWindowInfo->state == 3) {
				short ss = m_wmWorldState->m_subState;
				if (ss == 0xd) {
					if (m_wmWorldState->m_mcResult == 1) {
						m_wmWorldState->m_subState = 0xe;
					} else if (m_wmWorldState->m_mcResult == -2) {
						m_wmWorldState->m_subState = 7;
					} else {
						m_wmWorldState->m_subState = 0xf;
					}
				} else if (ss == 0x1a) {
					if (m_wmWorldState->m_mcResult == 1) {
						m_wmWorldState->m_subState = 0x1c;
					} else if (m_wmWorldState->m_mcResult == -2) {
						m_wmWorldState->m_subState = 7;
					} else {
						m_wmWorldState->m_subState = 0x1b;
					}
				} else if (m_wmWorldState->m_mcResult == 1) {
					m_wmWorldState->m_flag0A = 1;
					m_wmWorldState->m_subState = 0x15;
					Sound.PlaySe(0x41, 0x40, 0x7F, 0);
				} else if (m_wmWorldState->m_mcResult == -4) {
					m_wmWorldState->m_subState = 7;
				} else {
					m_wmWorldState->m_subState = 0x14;
				}
			}
			break;
		case 0x0C:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (((winState != 1 ||
			      (DrawMcWinMess(6, 0), m_wmWorldState->m_mcResult != 0)) && winState == 2) &&
			    m_menuWindowInfo->state == 3) {
				short cRes = m_wmWorldState->m_mcResult;
				if (cRes == -1) m_wmWorldState->m_subState = 10;
				else if (cRes == -2) m_wmWorldState->m_subState = 8;
				else if (cRes == -3) m_wmWorldState->m_subState = 8;
				else if (cRes == -4) m_wmWorldState->m_subState = 7;
				else if (cRes == -999) {
					m_wmWorldState->m_nextMenuMode = -1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 2;
				} else {
					BindMcObj();
					char* cs = reinterpret_cast<char*>(m_wmCharaState);
					unsigned int idx = 0;
					if (cs[0x42] == 0 && (idx = 1, cs[0x8a] == 0) &&
					    (idx = 2, cs[0xd2] == 0) && (idx = 3, cs[0x11a] == 0)) {
						idx = 4;
					}
					int __p7 = idx;
					if (__p7 < 4) {
						m_wmWorldState->m_subState = 0x19;
					} else {
						m_wmWorldState->m_subState = 0x11;
					}
					m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
				}
			}
			break;
		case 0x11:
			if (m_wmWorldState->m_mcResult < 0) {
				m_wmWorldState->m_subState = 3;
			} else if (m_wmWorldState->m_state0E != 0) {
				if (m_wmWorldState->m_state0E < 0) {
					if (m_wmWorldState->m_flag0A == 0) {
						m_wmWorldState->m_subState = 2;
					} else {
						m_wmWorldState->m_nextMenuMode = -1;
						m_wmWorldState->m_delay = 10;
					}
				} else if (m_wmCharaState[m_mcCtrl.m_saveIndex * 0x48 + 0x41] == 0) {
					m_wmWorldState->m_subState = 0x13;
				} else {
					m_wmWorldState->m_subState = 0x12;
				}
			}
			break;
		}
		if ((int)subState != (int)m_wmWorldState->m_subState) {
			m_wmWorldState->m_flag09 = 0;
			m_wmWorldState->m_counter1A = 0;
			m_wmWorldState->m_state0E = 0;
		}
	} else if (state != 2) {
		m_wmWorldState->m_frameCounter++;
		int threshold;
		if (m_wmWorldState->m_mainState == 3 && m_wmWorldState->m_subState != 0) {
			threshold = 0x13;
		} else {
			threshold = 10;
		}
		if (m_wmWorldState->m_frameCounter >= threshold) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			if (m_wmWorldState->m_mainState >= 5) {
				m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
				m_wmWorldState->m_nextMenuMode = 0;
			}
		}
	} else if (m_wmWorldState->m_delay != 0) {
		m_wmWorldState->m_delay--;
		if (m_wmWorldState->m_delay <= 0) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			Sound.PlaySe(0x32, 0x40, 0x7F, 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f98bc
 * PAL Size: 2320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_propagation off
#pragma opt_lifetimes off
void CMenuPcs::DrawCMakeMenu()
{
	extern double DOUBLE_803314E8;
	extern double DOUBLE_803313F8;
	extern double DOUBLE_803314D0;
	unsigned int ti;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	short state = m_wmWorldState->m_mainState;
	float frameAlpha;
	if (state == 0) {
		frameAlpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
	} else if (state == 1) {
		frameAlpha = static_cast<float>(-(DOUBLE_80331460 * static_cast<double>(m_wmWorldState->m_frameCounter) - DOUBLE_80331420));
	} else if (state == 2) {
		frameAlpha = FLOAT_80331434;
	} else if (state == 3) {
		frameAlpha = static_cast<float>(DOUBLE_80331460 * static_cast<double>(m_wmWorldState->m_frameCounter) + DOUBLE_803313F8);
	} else {
		frameAlpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) - DOUBLE_80331420));
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor frameColor;
	frameColor.r = 0xFF;
	frameColor.g = 0xFF;
	frameColor.b = 0xFF;
	frameColor.a = static_cast<unsigned char>(static_cast<int>(DOUBLE_80331508 * static_cast<double>(frameAlpha)));
	GXSetChanMatColor(static_cast<GXChannelID>(4), frameColor);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
	int bit = 0;
	int byteOffset = bit;
	do {
		if (((1 << bit) & 3) != 0) {
			short* const entry = reinterpret_cast<short*>(m_wm.m_frameInfo + byteOffset + 4);
			MenuPcs.DrawRect(*reinterpret_cast<unsigned int*>(entry + 0xC), static_cast<float>(entry[0]),
			                 static_cast<float>(entry[1]), static_cast<float>(entry[2]), static_cast<float>(entry[3]),
			                 *reinterpret_cast<float*>(entry + 4), *reinterpret_cast<float*>(entry + 6),
			                 FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
		bit++;
		byteOffset += 0x1C;
	} while (bit < 2);

	short contentState = m_wmWorldState->m_mainState;
	if (contentState > 0 && contentState < 4) {
		float contentAlpha;
		if (contentState == 1) {
			contentAlpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else if (contentState == 2) {
			contentAlpha = FLOAT_803313e8;
		} else {
			contentAlpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) - DOUBLE_80331420));
		}

		DrawCharaBase();
		DrawChara();
		PSMTXCopy(reinterpret_cast<MtxPtr>(bytes + 0x744), CameraPcs.m_cameraMatrix);
		GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0xFFFFFF);
		Mtx44 projectionMtx;
		PSMTX44Copy(CameraPcs.m_screenMatrix, projectionMtx);
		GXSetProjection(projectionMtx, GX_PERSPECTIVE);
		Graphic.SetViewport();
		GXSetScissor(0, 0, 0x280, 0x1C0);
		DrawInit();
		DrawCharaName();
		DrawCMLife();

		if (m_wmWorldState->m_menuMode == 3) {
			short winState = m_menuWindowInfo->state;
			if (winState != 3) {
				DrawMcWin(-1, 0);
				if (winState == 0 && m_menuWindowInfo->state == 1) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				}
				if (m_menuWindowInfo->state == 1) {
					DrawMcWinMess(0x17, 1);
				}
			}
		}

		int textAlpha;
		if (contentAlpha > FLOAT_803313e8) {
			textAlpha = 0xFF;
		} else {
			textAlpha = static_cast<int>(FLOAT_80331458 * contentAlpha);
		}
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		GXColor helpColor;
		helpColor.r = 0xFF;
		helpColor.g = 0xFF;
		helpColor.b = 0xFF;
		helpColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * contentAlpha));
		GXSetChanMatColor(static_cast<GXChannelID>(4), helpColor);
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1F));
		MenuPcs.DrawRect(0, FLOAT_803313dc, static_cast<float>(DOUBLE_803314D0 - static_cast<double>(FLOAT_80331440)),
		         FLOAT_803313e0, FLOAT_80331440, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		if (m_wmWorldState->m_menuMode == 3) {
			if (m_wmWorldState->m_menuMode == 3) {
			const int textIndex = static_cast<int>(*reinterpret_cast<short*>(bytes + 0x74) / 0x4B);
			char* textList[3] = { 0, 0, 0 };
			char** const langText = &lbl_80210750[(Game.m_gameWork.m_languageId - 1) * 0x0B];
			ti = 5;
			textList[0] = langText[ti];
			ti = 6;
			textList[1] = langText[ti];
			ti = 7;
			textList[2] = langText[ti];
			const _GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF)).color;
			char* const text = textList[textIndex];
			const int x = static_cast<int>(CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8));
			DrawFont2(x, static_cast<int>(FLOAT_803317D0), textColor, 7, text,
			          FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
			}
		} else if (m_wmWorldState->m_menuMode == 8) {
			const int mainMode = *(reinterpret_cast<char*>(g_pGoOutMenu) + 0x2C);
			switch (mainMode) {
			case 2:
				switch (*(reinterpret_cast<char*>(g_pGoOutMenu) + 0x18)) {
				case 0x0E: {
					char** const caseText = &lbl_80210750[(Game.m_gameWork.m_languageId - 1) * 0x0B];
				unsigned int ci = 8;
				char* const text = caseText[ci];
					const _GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF)).color;
					const int x = static_cast<int>(MenuPcs.CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8));
					MenuPcs.DrawFont2(x, static_cast<int>(FLOAT_803317D0), textColor, 7, text,
					                  FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
					break;
				}
				case 0x0F: {
					char** const caseText = &lbl_80210750[(Game.m_gameWork.m_languageId - 1) * 0x0B];
				unsigned int ci = 9;
				char* const text = caseText[ci];
					const _GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF)).color;
					const int x = static_cast<int>(MenuPcs.CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8));
					MenuPcs.DrawFont2(x, static_cast<int>(FLOAT_803317D0), textColor, 7, text,
					                  FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
					break;
				}
				}
				break;
			case 3:
				switch (*(reinterpret_cast<char*>(g_pGoOutMenu) + 0x24)) {
				case 2: {
					char** const caseText = &lbl_80210750[(Game.m_gameWork.m_languageId - 1) * 0x0B];
				unsigned int ci = 10;
				char* const text = caseText[ci];
					const _GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF)).color;
					const int x = static_cast<int>(MenuPcs.CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8));
					MenuPcs.DrawFont2(x, static_cast<int>(FLOAT_803317D0), textColor, 7, text,
					                  FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
					break;
				}
				}
				break;
			}
		}
	}

	if (m_wmWorldState->m_mainState != 2) {
		m_wmWorldState->m_frameCounter++;
		if (m_wmWorldState->m_frameCounter >= 10) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			if (m_wmWorldState->m_mainState >= 5) {
				m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
				m_wmWorldState->m_nextMenuMode = 0;
			}
		}
	} else if (m_wmWorldState->m_mainState == 2) {
		if (m_wmWorldState->m_delay != 0) {
			m_wmWorldState->m_delay--;
			if (m_wmWorldState->m_delay <= 0) {
				m_wmWorldState->m_mainState++;
				m_wmWorldState->m_frameCounter = 0;
				Sound.PlaySe(0x31 + static_cast<int>(static_cast<unsigned int>(static_cast<int>(m_wmWorldState->m_nextMenuMode)) >> 31), 0x40, 0x7F, 0);
			}
		}
	}
}

#pragma opt_lifetimes on
#pragma opt_propagation on
/*
 * --INFO--
 * PAL Address: 0x800f9248
 * PAL Size: 1652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMoveMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
#define worldState m_wmWorldState

	{
		short state = worldState->m_mainState;
		if ((state == 0) && bytes[0x12] == 0) {
			return;
		}
		if (state > 3) {
			return;
		}
	}

	DrawFukidashi();
	short state = worldState->m_mainState;
	float moveAlpha;
	int __p16 = state;
	if (__p16 == 1) {
		moveAlpha = static_cast<float>(static_cast<double>(worldState->m_frameCounter) / DOUBLE_803316e8);
	int __p16 = state;
	} else if (__p16 == 2 && bytes[0x13] != 0) {
		moveAlpha = static_cast<float>(DOUBLE_80331420 - static_cast<double>(worldState->m_frameCounter) / DOUBLE_803316e8);
	} else {
		moveAlpha = FLOAT_803313e8;
	}
	int __p17 = state;
	if (state > 0 && __p17 < 3) {
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		GXColor helpColor;
		helpColor.r = 0xFF;
		helpColor.g = 0xFF;
		helpColor.b = 0xFF;
		helpColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * moveAlpha));
		GXSetChanMatColor(static_cast<GXChannelID>(4), helpColor);
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x23));
		MenuPcs.DrawRect(0, FLOAT_803313dc, static_cast<float>(DOUBLE_803314d0 - static_cast<double>(FLOAT_80331440)),
		         FLOAT_803313e0, FLOAT_80331440, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
	}
	DrawWMFrame();

	if (worldState->m_mainState > 0 && worldState->m_mainState < 3) {
		unsigned char* const worldObj = m_wm.m_worldObjData;
#define handle (reinterpret_cast<CCharaPcs::CHandle*>(reinterpret_cast<unsigned int*>(bytes + 0x788)[0]))
		Mtx lookAtMtx;
		Mtx44 projectionMtx;

		C_MTXPerspective(projectionMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
		GXSetProjection(projectionMtx, GX_PERSPECTIVE);
		PSMTX44Copy(projectionMtx, CameraPcs.m_screenMatrix);
		C_MTXLookAt(lookAtMtx, reinterpret_cast<Point3d*>(worldObj + 0x1A0),
		            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc)),
		            reinterpret_cast<Point3d*>(&CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc)));
		PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(bytes + 0x744));
		PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
		CharaPcs.InitEnv(5);
		GXSetColorUpdate(0);
		GXSetAlphaUpdate(0);
		GXSetCopyClear(CColor(0, 0, 0, 0).color, 0x00FFFFFF);
		GXSetColorUpdate(1);
		GXSetAlphaUpdate(1);
		GXSetViewport(static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x198)),
		              static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x19A)),
		              static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x19C)),
		              static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x19E)),
		              FLOAT_803313dc, FLOAT_803313e8);
		GXSetScissor(*reinterpret_cast<unsigned int*>(worldObj + 0x1D0),
		             *reinterpret_cast<unsigned int*>(worldObj + 0x1D4),
		             *reinterpret_cast<unsigned int*>(worldObj + 0x1D8),
		             *reinterpret_cast<unsigned int*>(worldObj + 0x1DC));
		Graphic.SetFog(1, 0);
		WmMenuLightTable& lightTable = gWmMenuLightTables[0];
		LightPcs.SetAmbient(lightTable.m_ambient);
		LightPcs.SetNumDiffuse(lightTable.m_diffuseCount);
		for (int lightIndex = 0; lightIndex < lightTable.m_diffuseCount; lightIndex++) {
			LightPcs.SetDiffuse(
				lightIndex, lightTable.m_diffuseColors[lightIndex],
				&lightTable.m_diffuseDirs[lightIndex], 0);
		}
		LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);

		{
			*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(m_effectWork) + 0x1E70) = handle->m_model->m_lightAlpha;
			handle->Draw(5);
			pppFVECTOR4 color;
			const short partColorIndex = m_crystalPart;
			PartPcs.GetParColIdx(partColorIndex, color);
			color.w = handle->m_model->m_lightAlpha;
			PartPcs.SetParColIdx(partColorIndex, color);
			if (*reinterpret_cast<char*>(bytes + 0x80) == 0) {
				*reinterpret_cast<char*>(bytes + 0x80) = 1;
			} else {
				PartPcs.DrawMenu(m_crystalAttr);
			}
		}

		PSMTXCopy(reinterpret_cast<MtxPtr>(bytes + 0x744), CameraPcs.m_cameraMatrix);
		GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0x00FFFFFF);
		Mtx44 restoreMtx;
		PSMTX44Copy(CameraPcs.m_screenMatrix, restoreMtx);
		GXSetProjection(restoreMtx, GX_PERSPECTIVE);
		Graphic.SetViewport();
		GXSetScissor(0, 0, 0x280, 0x1C0);
		DrawInit();
#undef handle
	}

	if (worldState->m_mainState != 2 || bytes[0x13] != 0) {
		worldState->m_frameCounter++;
	}

	if (worldState->m_mainState == 0 ||
	    (worldState->m_mainState == 2 && bytes[0x13] != 0)) {
		if (static_cast<double>(worldState->m_posX) <= DOUBLE_803314f0) {
			worldState->m_mainState++;
			*reinterpret_cast<int*>(m_wm.m_frameData + 4) = 0;
			*reinterpret_cast<int*>(m_wm.m_frameData + 8) = 0;
			worldState->m_frameCounter = 0;
		}
	} else if (worldState->m_mainState == 1 && worldState->m_frameCounter >= 10) {
		worldState->m_mainState++;
		worldState->m_frameCounter = 0;
		CFlatRuntime::CStack stackData[3];
		stackData[0].m_word = 3;
		stackData[1].m_word = 0;
		stackData[2].m_word = 0;
		gCFlatRuntime().SystemCall(0, 1, 4, 3, stackData, 0);
	} else if (worldState->m_mainState == 2 && worldState->m_frameCounter >= 10) {
		worldState->m_mainState++;
		worldState->m_frameCounter = 0;
	} else if (worldState->m_mainState == 3 && worldState->m_frameCounter >= 10) {
		worldState->m_mainState++;
		worldState->m_frameCounter = 0;
		CFlatRuntime::CStack stackData[3];
		stackData[0].m_word = 4;
		stackData[1].m_word = 0;
		stackData[2].m_word = 0;
		gCFlatRuntime().SystemCall(0, 1, 4, 3, stackData, 0);
	}
#undef worldState
}

/*
 * --INFO--
 * PAL Address: 0x800f7efc
 * PAL Size: 4940b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawLoadMenu()
{
	extern double DOUBLE_803317D8;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	McCtrl& mcCtrl = *GetMcCtrl();
	if ((signed char)m_wmWorldState->m_worldReady == 0) {
		return;
	}

	short state = m_wmWorldState->m_mainState;
	float cursorXbase;
	float alpha;
	if (state > 0 && state < 4) {
		double raw;
		if (state == 1) {
			reinterpret_cast<int*>(&raw)[0] = 0x43300000;
			reinterpret_cast<int*>(&raw)[1] = static_cast<int>(m_wmWorldState->m_frameCounter) ^ 0x80000000;
			alpha = static_cast<float>(DOUBLE_803314E8 * (raw - DOUBLE_80331408));
		} else if (state == 2) {
			alpha = FLOAT_803313e8;
		} else {
			reinterpret_cast<int*>(&raw)[0] = 0x43300000;
			reinterpret_cast<int*>(&raw)[1] = static_cast<int>(m_wmWorldState->m_frameCounter) ^ 0x80000000;
			alpha = static_cast<float>(-(DOUBLE_803314E8 * (raw - DOUBLE_80331408) - DOUBLE_80331420));
		}
		if (static_cast<double>(alpha) > DOUBLE_803314f0) {
			MenuPcs.SetAttrFmt((FMT)0);
			_GXColor bgColor;
			bgColor.r = 0xFF;
			bgColor.g = 0xFF;
			bgColor.b = 0xFF;
			bgColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * alpha));
			GXSetChanMatColor(GX_COLOR0A0, bgColor);
			MenuPcs.SetTexture((TEX)0x1F);
			MenuPcs.DrawRect(0, FLOAT_803313dc, static_cast<float>(DOUBLE_803314d0 - static_cast<double>(FLOAT_80331440)),
			         FLOAT_803313e0, FLOAT_80331440,
			         FLOAT_803313dc, FLOAT_803313dc,
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
	}
	if (alpha < FLOAT_803313dc) alpha = FLOAT_803313dc;

	unsigned int uAlpha;
	if (alpha > FLOAT_803313e8) {
		uAlpha = 0xFF;
	} else {
		uAlpha = static_cast<int>(FLOAT_80331458 * alpha);
	}

	// Header text
	if (*reinterpret_cast<char*>(reinterpret_cast<int>(g_pGoOutMenu) + 0x18) == 0x0E) {
		const int languageIndex = (Game.m_gameWork.m_languageId - 1) * 0x0B;
		char* text = lbl_80210750[languageIndex + 8];
		_GXColor color = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(uAlpha)).color;
		const int x = static_cast<int>(MenuPcs.CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8));
		MenuPcs.DrawFont2(x, static_cast<int>(FLOAT_803317D0), color, 7, text,
		                  FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
	}

	DrawMCList();

	// Cursor / selection rendering
	state = m_wmWorldState->m_mainState;
	if (state == 2 && m_wmWorldState->m_subState >= 0x11) {
		float cursorY0;
		cursorY0 = FLOAT_803314d8;
		cursorXbase = cursorY0;
		cursorY0 = static_cast<float>(static_cast<double>(cursorY0) - DOUBLE_803317D8);
		cursorXbase = cursorXbase + FLOAT_80331410;
		unsigned int saveIdx;
		if (m_wmWorldState->m_subState == 0x11) {
			saveIdx = static_cast<unsigned int>(m_wmWorldState->m_cardChannel);
		} else {
			saveIdx = static_cast<unsigned int>(mcCtrl.m_saveIndex);
		}
		double rawIdx;
		reinterpret_cast<int*>(&rawIdx)[0] = 0x43300000;
		reinterpret_cast<int*>(&rawIdx)[1] = saveIdx ^ 0x80000000;
		cursorXbase = static_cast<float>(DOUBLE_80331498 * (rawIdx - DOUBLE_80331408) + static_cast<double>(cursorXbase));
		MenuPcs.SetAttrFmt((FMT)0);
		_GXColor cursorColor;
		cursorColor.r = 0xFF;
		cursorColor.g = 0xFF;
		cursorColor.b = 0xFF;
		cursorColor.a = 0xFF;
		GXSetChanMatColor(GX_COLOR0A0, cursorColor);
		MenuPcs.SetTexture((TEX)0);
		MenuPcs.DrawRect(0, (float)(int)cursorY0, (float)(int)cursorXbase,
		         FLOAT_80331410, FLOAT_80331410,
		         FLOAT_803313dc, FLOAT_803313dc,
		         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

		// 3D character model viewports
		int* piVar13 = reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_worldObjData) + 0x550);
		int viewBase = 0x550;
		int i = 0;
		do {
			if (*piVar13 != 0) {
				int slot = reinterpret_cast<int>(m_wm.m_worldObjData) + viewBase;
				Mtx44 projMtx;
				C_MTXPerspective(projMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
				GXSetProjection(projMtx, GX_PERSPECTIVE);
				PSMTX44Copy(projMtx, CameraPcs.m_screenMatrix);

				Mtx lookAtMtx;
				C_MTXLookAt(lookAtMtx, (Vec*)(slot + 0x10),
				            (Vec*)&CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc),
				            (Vec*)&CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc));
				PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(m_wm.m_pad744));
				PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
				CharaPcs.InitEnv(5);
				GXSetColorUpdate(0);
				GXSetAlphaUpdate(0);
				GXSetCopyClear(CColor(0, 0, 0, 0).color, 0xFFFFFF);
				GXSetColorUpdate(1);
				GXSetAlphaUpdate(1);
				GXSetViewport(
					(float)*reinterpret_cast<short*>(slot + 8),
					(float)*reinterpret_cast<short*>(slot + 0xa),
					(float)*reinterpret_cast<short*>(slot + 0xc),
					(float)*reinterpret_cast<short*>(slot + 0xe),
					FLOAT_803313dc, FLOAT_803313e8);
				GXSetScissor(*reinterpret_cast<int*>(slot + 0x40), *reinterpret_cast<int*>(slot + 0x44),
				             *reinterpret_cast<int*>(slot + 0x48), *reinterpret_cast<int*>(slot + 0x4c));
				Graphic.SetFog(1, 0);
				WmMenuLightTable& lightTable = gWmMenuLightTables[0];
				LightPcs.SetAmbient(lightTable.m_ambient);
				LightPcs.SetNumDiffuse(lightTable.m_diffuseCount);
				for (int j = 0; j < lightTable.m_diffuseCount; j++) {
					LightPcs.SetDiffuse(
						j, lightTable.m_diffuseColors[j],
						&lightTable.m_diffuseDirs[j], 0);
				}
				LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
				m_wm.m_handles[17 + i]->Draw(5);
				if (m_effectWork[17 + i].m_partNo >= 0) {
					PartPcs.DrawMenuIdx(m_effectWork[17 + i].m_partNo);
				}
				if (m_effectWork[21 + i].m_partNo >= 0) {
					PartPcs.DrawMenuIdx(m_effectWork[21 + i].m_partNo);
				}
			}
			piVar13 += 0x14;
			viewBase += 0x50;
			i++;
		} while (i < 4);
		DrawInit();
		PSMTXCopy(reinterpret_cast<MtxPtr>(m_wm.m_pad744), CameraPcs.m_cameraMatrix);
		GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0xFFFFFF);
		Mtx44 projMtx2;
		PSMTX44Copy(CameraPcs.m_screenMatrix, projMtx2);
		GXSetProjection(projMtx2, GX_PERSPECTIVE);
		Graphic.SetViewport();
		GXSetScissor(0, 0, 0x280, 0x1C0);
		DrawInit();
	}

	// State machine for MC operations
	state = m_wmWorldState->m_mainState;
	if (state == 2 && m_wmWorldState->m_delay == 0) {
		short subState = m_wmWorldState->m_subState;
		short winState;
		switch ((int)subState) {
		case 0:
		case 2:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(0, 0);
				float slotY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float slotX = (float)GetSlotABXPos(m_wmWorldState->m_cardChannel);
				MenuPcs.SetAttrFmt((FMT)0);
				_GXColor slotColor;
				slotColor.r = 0xFF;
				slotColor.g = 0xFF;
				slotColor.b = 0xFF;
				slotColor.a = 0xFF;
				GXSetChanMatColor(GX_COLOR0A0, slotColor);
				MenuPcs.SetTexture((TEX)0);
				MenuPcs.DrawRect(0, (float)(int)slotX, (float)(int)slotY,
				         FLOAT_80331410, FLOAT_80331410,
				         FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				if (m_wmWorldState->m_state0E < 0) {
					m_wmWorldState->m_nextMenuMode = -1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 1;
				} else if (m_wmWorldState->m_subState == 2) {
					m_wmWorldState->m_subState = 3;
				} else {
					m_wmWorldState->m_subState = 1;
				}
			}
			break;
		case 1:
			if (m_wmWorldState->m_frameCounter >= 0x13) {
				m_wmWorldState->m_subState = 3;
			}
			m_wmWorldState->m_frameCounter++;
			break;
		case 3:
			if (m_wmWorldState->m_mcResult != 1) {
				memset(GetWmMenuCharaState(this), 0, kWmMenuCharaStateBytes);
				short mcResult = m_wmWorldState->m_mcResult;
				if (mcResult == -1) {
					m_wmWorldState->m_subState = 5;
				} else if (mcResult == -2) {
					m_wmWorldState->m_subState = 8;
				} else if (mcResult == -3) {
					m_wmWorldState->m_subState = 6;
				} else if (mcResult == -4) {
					m_wmWorldState->m_subState = 7;
				} else if (mcResult == 0) {
					m_wmWorldState->m_subState = 4;
				}
			}
			break;
		case 5:
		case 6:
		case 7:
		case 10:
		case 0x0E:
		case 0x0F:
		case 0x10:
		case 0x17:
		case 0x18:
		case 0x1B:
		case 0x1C:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int msgId = 0;
				int msgParam = 0;
				short ss = m_wmWorldState->m_subState;
				if (ss == 5) msgId = 1;
				else if (ss == 6) msgId = 2;
				else if (ss == 7) msgId = 3;
				else if (ss == 10) msgId = 0xB;
				else if (ss == 0x0E) msgId = 0xC;
				else if (ss == 0x0F) msgId = 0xD;
				else if (ss == 0x1C) { msgId = 0x1B; msgParam = 1; }
				else if (ss == 0x1B) { msgId = 0x1C; msgParam = 1; }
				else if (ss == 0x18) msgId = 0x10;
				else if (ss == 0x17) msgId = 0x11;
				else msgId = 0x13;
				DrawMcWinMess(msgId, msgParam);
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				if (m_wmWorldState->m_state0E < 0 ||
				    m_wmWorldState->m_subState == 0x1C || m_wmWorldState->m_subState == 0x1B ||
				    m_wmWorldState->m_subState == 0x17) {
					m_wmWorldState->m_subState = 3;
				} else if (subState == 0x18) {
					m_wmWorldState->m_nextMenuMode = 1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 4;
				} else if (m_wmWorldState->m_menuMode == 8 && m_goOutSaveLoadMode != 0) {
					m_wmWorldState->m_nextMenuMode = 1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 2;
				} else {
					m_wmWorldState->m_subState = 2;
				}
			}
			break;
		case 4:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(6, 0);
				short cRes4 = m_wmWorldState->m_mcResult;
				if (cRes4 != 0 && cRes4 == 1) {
					m_wmWorldState->m_subState = 0xC;
				}
			} else if (winState == 2 && m_menuWindowInfo->state == 3) {
				short mcRes2 = m_wmWorldState->m_mcResult;
				if (mcRes2 == -3) {
					m_wmWorldState->m_subState = 8;
				} else if (mcRes2 == -4) {
					m_wmWorldState->m_subState = 8;
				} else if (mcRes2 == -5) {
					m_wmWorldState->m_subState = 7;
				} else if (mcRes2 == -6) {
					m_wmWorldState->m_subState = 0x10;
				} else {
					m_wmWorldState->m_subState = 10;
				}
			}
			break;
		case 8:
		case 0x0B:
		case 0x19:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int ymsgId = 0;
				int ymsgParam = 0;
				short ys = m_wmWorldState->m_subState;
				if (ys == 8) ymsgId = 4;
				else if (ys == 0x19) { ymsgId = 0x19; ymsgParam = 1; }
				else ymsgId = 5;
				DrawMcWinMess(ymsgId, ymsgParam);

				// Yes/No cursor
				float ynY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float ynX = (float)GetYesNoXPos(m_wmWorldState->m_cardChannel);
				if (m_wmWorldState->m_subState != 0x19) {
					MenuPcs.SetAttrFmt((FMT)0);
					_GXColor ynColor;
					ynColor.r = 0xFF;
					ynColor.g = 0xFF;
					ynColor.b = 0xFF;
					ynColor.a = 0xFF;
					GXSetChanMatColor(GX_COLOR0A0, ynColor);
					MenuPcs.SetTexture((TEX)0);
					MenuPcs.DrawRect(0, (float)(int)ynX, (float)(int)ynY,
					         FLOAT_80331410, FLOAT_80331410,
					         FLOAT_803313dc, FLOAT_803313dc,
					         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				} else {
					short ynResult0 = m_wmWorldState->m_mcResult;
					if (ynResult0 < 0) {
						if (ynResult0 == -1) m_wmWorldState->m_subState = 5;
						else if (ynResult0 == -2) m_wmWorldState->m_subState = 8;
						else if (ynResult0 == -3) m_wmWorldState->m_subState = 6;
						else m_wmWorldState->m_subState = 7;
					}
				}
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				short ynResult = m_wmWorldState->m_mcResult;
				if (ynResult < 0) {
					if (ynResult == -1) m_wmWorldState->m_subState = 5;
					else if (ynResult == -2) m_wmWorldState->m_subState = 8;
					else if (ynResult == -3) m_wmWorldState->m_subState = 6;
					else m_wmWorldState->m_subState = 7;
				} else if (m_wmWorldState->m_state0E < 0) {
					if (m_wmWorldState->m_subState == 0x19) {
						m_wmWorldState->m_subState = 0x11;
						m_wmWorldState->m_cardChannel = (short)mcCtrl.m_saveIndex;
					} else if (m_wmWorldState->m_menuMode == 8 && m_goOutSaveLoadMode != 0) {
						m_wmWorldState->m_nextMenuMode = 1;
						m_wmWorldState->m_delay = 1;
						memset(m_wmCharaState, 0, kWmMenuCharaStateBytes);
						m_wmTransitionCode = 1;
					} else {
						m_wmWorldState->m_subState = 2;
					}
				} else if (m_wmWorldState->m_subState == 8) {
					m_wmWorldState->m_subState = 0x0B;
				} else if (m_wmWorldState->m_subState == 0x19) {
					m_wmWorldState->m_subState = 0x1A;
				} else {
					m_wmWorldState->m_subState = 0x0D;
				}
			}
			break;
		case 0x0D:
		case 0x16:
		case 0x1A:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int dmsgId = 7;
				int dmsgParam = 0;
				short ds = m_wmWorldState->m_subState;
				if (ds == 0x0D) dmsgId = 7;
				else if (ds == 0x1A) { dmsgId = 0x1A; dmsgParam = 1; }
				else dmsgId = 9;
				DrawMcWinMess(dmsgId, dmsgParam);
			} else if (winState == 2 && m_menuWindowInfo->state == 3) {
				if (m_wmWorldState->m_subState == 0x0D) {
					short dRes = m_wmWorldState->m_mcResult;
					if (dRes == 1) m_wmWorldState->m_subState = 0x0E;
					else if (dRes == -2) m_wmWorldState->m_subState = 7;
					else m_wmWorldState->m_subState = 0x0F;
				} else if (subState == 0x1A) {
					short dRes = m_wmWorldState->m_mcResult;
					if (dRes == 1) m_wmWorldState->m_subState = 0x1C;
					else if (dRes == -2) m_wmWorldState->m_subState = 7;
					else m_wmWorldState->m_subState = 0x1B;
				} else {
					short dRes = m_wmWorldState->m_mcResult;
					if (dRes == 1) {
						m_wmWorldState->m_subState = 0x18;
						Sound.PlaySe(0x42, 0x40, 0x7F, 0);
					} else if (dRes == -4) m_wmWorldState->m_subState = 7;
					else m_wmWorldState->m_subState = 0x17;
				}
			}
			break;
		case 0x0C:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(6, 0);
				if (m_wmWorldState->m_mcResult == 0) {
					break;
				}
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				short cRes = m_wmWorldState->m_mcResult;
				if (cRes == -1) m_wmWorldState->m_subState = 10;
				else if (cRes == -2) m_wmWorldState->m_subState = 8;
				else if (cRes == -3) m_wmWorldState->m_subState = 8;
				else if (cRes == -4) m_wmWorldState->m_subState = 7;
				else if (cRes == -999) {
					m_wmWorldState->m_nextMenuMode = -1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 2;
				} else {
					BindMcObj();
					char* cs = reinterpret_cast<char*>(m_wmCharaState);
					int idx = 0;
					if (cs[0x42] == 0 && (idx = 1, cs[0x8a] == 0) &&
					    (idx = 2, cs[0xd2] == 0) && (idx = 3, cs[0x11a] == 0)) {
						idx = 4;
					}
					if (idx < 4) {
						m_wmWorldState->m_subState = 0x19;
					} else {
						m_wmWorldState->m_subState = 0x11;
					}
				}
			}
			break;
		case 0x11:
			if (m_wmWorldState->m_mcResult < 0) {
				m_wmWorldState->m_subState = 3;
			} else if (m_wmWorldState->m_state0E != 0) {
				if (m_wmWorldState->m_state0E < 0) {
					if (m_wmWorldState->m_menuMode == 8 && m_goOutSaveLoadMode != 0) {
						m_wmWorldState->m_nextMenuMode = 1;
						m_wmWorldState->m_delay = 1;
						memset(m_wmCharaState, 0, kWmMenuCharaStateBytes);
						m_wmTransitionCode = 1;
					} else {
						m_wmWorldState->m_subState = 2;
					}
				} else {
					m_wmWorldState->m_subState = 0x16;
				}
			}
			break;
		}
		if ((int)subState != (int)m_wmWorldState->m_subState) {
			m_wmWorldState->m_flag09 = 0;
			m_wmWorldState->m_counter1A = 0;
			m_wmWorldState->m_state0E = 0;
		}
	} else if (state != 2) {
		m_wmWorldState->m_frameCounter++;
		int threshold;
		if (m_wmWorldState->m_mainState == 3 && m_wmWorldState->m_subState != 0) {
			threshold = 0x13;
		} else {
			threshold = 10;
		}
		if (m_wmWorldState->m_frameCounter >= threshold) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			if (m_wmWorldState->m_mainState >= 5) {
				if (m_wmWorldState->m_menuMode != 8) {
					m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
				}
				m_textureLocIndex = 1;
				m_wmWorldState->m_nextMenuMode = 0;
			}
		}
	} else if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_delay != 0) {
		m_wmWorldState->m_delay--;
		if (m_wmWorldState->m_delay <= 0) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			Sound.PlaySe(0x31 + (int)((unsigned int)(int)m_wmWorldState->m_nextMenuMode >> 31), 0x40, 0x7F, 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f7044
 * PAL Size: 3768b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawTitleMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int state = m_wmWorldState->m_mainState;

		if (state == 0 && static_cast<signed char>(m_wmWorldState->m_worldReady) != 0) {
			if (static_cast<signed char>(m_wmThpActive) != 0) {
				THPSimpleDrawCurrentFrame((_GXRenderModeObj*)Graphic.m_renderMode, 0, 0, 0x280, 0x1C0);
				Graphic._WaitDrawDone(const_cast<char*>(s_wm_menu_cpp), 0x12A2);
			}
		short sVarE = m_wmWorldState->m_state0E;
		if (sVarE != 0 || m_wmWorldState->m_frameCounter >= 0xB43) {
			if (sVarE != -1) {
				THPSimpleAudioStop();
				THPSimpleLoadStop();
				THPSimpleClose();
				THPSimpleQuit();
				if (m_wmWorkBuffer != 0) {
					Memory.Free(m_wmWorkBuffer);
					m_wmWorkBuffer = 0;
				}
				m_wmThpActive = 0;
			}
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			m_wmWorldState->m_titleState = 0;
			m_wmWorldState->m_state0E = 0;
			m_wmWorldState->m_state12 = 0;
			CFlatRuntime::CStack flatArgs[3];
			flatArgs[0].m_word = 9;
			flatArgs[1].m_word = 0;
			flatArgs[2].m_word = 0;
			gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs, 0);
		}
	} else {
		// 3D viewport setup
		GXColor matColor;
		Mtx44 projMtx;
		C_MTXPerspective(projMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
		GXSetProjection(projMtx, GX_PERSPECTIVE);
		PSMTX44Copy(projMtx, CameraPcs.m_screenMatrix);

		Vec eye;
		eye.x = FLOAT_803313dc;
		eye.y = FLOAT_803313dc;
		eye.z = FLOAT_80331768;
		Mtx lookAtMtx;
		C_MTXLookAt(lookAtMtx, &eye,
		            (Vec*)&CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc),
		            (Vec*)&CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc));
		PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(m_wm.m_pad744));
		PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
		CharaPcs.InitEnv(5);
		GXSetColorUpdate(0);
		GXSetAlphaUpdate(0);
		_GXColor clearGxColor = CColor(0, 0, 0, 0).color;
		GXSetCopyClear(clearGxColor, 0xFFFFFF);
		GXSetColorUpdate(1);
		GXSetAlphaUpdate(1);
		GXSetViewport(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e0, FLOAT_803313e4,
		              FLOAT_803313dc, FLOAT_803313e8);

		PartPcs.DrawMenuIdx(m_effectWork[23].m_partNo);
		PSMTXCopy(reinterpret_cast<MtxPtr>(m_wm.m_pad744), CameraPcs.m_cameraMatrix);
		GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0xFFFFFF);

		Mtx44 projMtx2;
		PSMTX44Copy(CameraPcs.m_screenMatrix, projMtx2);
		GXSetProjection(projMtx2, GX_PERSPECTIVE);
		Graphic.SetViewport();
		GXSetScissor(0, 0, 0x280, 0x1C0);
		DrawInit();

		// Fade-in overlay (state 1)
			state = m_wmWorldState->m_mainState;
			if (state == 1 && static_cast<signed char>(lbl_8032E8AC) == 0) {
				float fadeAlpha = static_cast<float>(-(DOUBLE_80331770 *
				                                        static_cast<double>(m_wmWorldState->m_frameCounter) -
				                                        DOUBLE_80331420));
				SetAttrFmt((FMT)2);
			matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * fadeAlpha));
			GXSetChanMatColor(GX_COLOR0A0, matColor);
			MenuPcs.SetTexture((TEX)0xFFFFFFFF);
			_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(5), static_cast<_GXLogicOp>(1));
			GXBegin(GX_QUADS, GX_VTXFMT0, 4);
			GXPosition3f32(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313e0, FLOAT_803313dc, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313e0, FLOAT_803313e4, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313dc, FLOAT_803313e4, FLOAT_803313dc);
		}

		// Menu items
		MenuPcs.SetAttrFmt((FMT)0);
		MenuPcs.SetTexture((TEX)0x43);

		state = m_wmWorldState->m_mainState;
		if (state >= 2) {
			float fX = FLOAT_80331778 - FLOAT_80331414;
			float fY = FLOAT_8033177c;
			if (m_wmWorldState->m_cardChannel != 0) {
				fY = FLOAT_8033177c + (float)(m_wmWorldState->m_cardChannel * 0x28 - 8);
			}
			float fYRect = fY - FLOAT_80331780;
			float alpha;
			if (state == 2 && m_wmWorldState->m_state12 == 0) {
				int timer = (int)m_wmWorldState->m_titleState;
				fX = static_cast<float>(-(DOUBLE_80331790 *
				                           (static_cast<double>(5 - timer) / DOUBLE_80331798) -
				                           static_cast<double>(fX)));
				alpha = static_cast<float>(DOUBLE_80331788 * static_cast<double>(timer) + DOUBLE_803314e8);
			} else {
				alpha = FLOAT_803313e8;
			}
			matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * alpha));
			GXSetChanMatColor(GX_COLOR0A0, matColor);
			MenuPcs.DrawRect(0, fX, fYRect,
			         FLOAT_80331568, FLOAT_80331554,
			         FLOAT_803313dc, FLOAT_803313dc,
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(1), static_cast<_GXLogicOp>(5));
			state = m_wmWorldState->m_mainState;
			float secondAlpha = alpha;
			fX = FLOAT_80331778 - FLOAT_80331414;
			if (state == 2 && m_wmWorldState->m_state12 == 0) {
				int timer = (int)m_wmWorldState->m_titleState;
				fX = static_cast<float>(DOUBLE_80331790 *
				                         (static_cast<double>(5 - timer) / DOUBLE_80331798) +
				                         static_cast<double>(fX));
			} else if ((state == 2 && m_wmWorldState->m_delay == 0) ||
			           (state == 3 && m_wmWorldState->m_state0E == 0)) {
				int pulse = (int)m_wmWorldState->m_titleState % 0x28 - 0x14;
				if (pulse < 0) {
					pulse = -pulse;
				}
				secondAlpha = static_cast<float>(-(DOUBLE_803317A0 * static_cast<double>(pulse) -
				                                  DOUBLE_80331420));
			} else {
				secondAlpha = FLOAT_803313e8;
			}
			matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * secondAlpha));
			GXSetChanMatColor(GX_COLOR0A0, matColor);
			MenuPcs.DrawRect(0, fX, fYRect,
			         FLOAT_80331568, FLOAT_80331554,
			         FLOAT_803313dc, FLOAT_80331554,
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(5), static_cast<_GXLogicOp>(1));
		}

		// Menu item labels (2 items: New Game, Continue)
		MenuPcs.SetAttrFmt((FMT)0);
		const float kColorScale = FLOAT_80331458;
		const float kZero = FLOAT_803313dc;
		unsigned int uVar7 = 0xFFFFFFF8;
		unsigned int uVar6 = 0x70;
		for (int i = 0; i < 2; i++) {
			float labelAlpha;
			if (m_wmWorldState->m_mainState == 1) {
				labelAlpha = static_cast<float>(DOUBLE_80331770 * static_cast<double>(m_wmWorldState->m_frameCounter));
			} else {
				labelAlpha = FLOAT_803313e8;
			}
			matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = static_cast<unsigned char>(static_cast<int>(kColorScale * labelAlpha));
			GXSetChanMatColor(GX_COLOR0A0, matColor);

			float yPos = FLOAT_8033177c;
			if (i != 0) {
				yPos = yPos + (float)((int)uVar7);
			}
			MenuPcs.DrawRect(0, FLOAT_80331778, yPos,
			         FLOAT_80331568, FLOAT_80331440,
			         kZero, (float)((int)uVar6),
			         FLOAT_803313e8, FLOAT_803313e8, kZero);

			// Cursor on selected item
			if (m_wmWorldState->m_flag09 == 0 &&
			    i == m_wmWorldState->m_cardChannel) {
				int timer = (int)m_wmWorldState->m_titleState;
				float cursorScale = static_cast<float>(DOUBLE_803317A8 * static_cast<double>(timer) +
				                                        static_cast<double>(FLOAT_803313e8));
				int cursorAlpha = static_cast<int>(kColorScale *
				                                   static_cast<float>(-(DOUBLE_803317B0 * static_cast<double>(timer) -
				                                                        DOUBLE_80331420)));
				matColor.r = 0xFF;
				matColor.g = 0xFF;
				matColor.b = 0xFF;
				matColor.a = static_cast<unsigned char>(cursorAlpha);
				GXSetChanMatColor(GX_COLOR0A0, matColor);
				float cursorX = static_cast<float>((FLOAT_803313e0 - FLOAT_80331568 * cursorScale) * DOUBLE_803313f8);
				float cursorY = FLOAT_8033177c - (FLOAT_80331440 * cursorScale - FLOAT_80331440);
				if (i != 0) {
					cursorY = cursorY + (float)((int)uVar7);
				}
				MenuPcs.DrawRect(0,
				         cursorX,
				         cursorY,
				         FLOAT_80331568, FLOAT_80331440,
				         kZero, (float)((int)uVar6),
				         cursorScale, cursorScale, kZero);
			}
			uVar7 += 0x28;
			uVar6 += 0x28;
		}

		// Logo and copyright textures
		MenuPcs.SetAttrFmt((FMT)0);
		matColor.r = 0xFF;
		matColor.g = 0xFF;
		matColor.b = 0xFF;
		matColor.a = 0xFF;
		GXSetChanMatColor(GX_COLOR0A0, matColor);
		MenuPcs.SetTexture((TEX)0x42);
		MenuPcs.DrawRect(0, FLOAT_803317b8, FLOAT_803317bc, FLOAT_803317c0, FLOAT_803315b4,
		         FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

		MenuPcs.SetTexture((TEX)0x44);
		float copyrightAlpha;
		if (m_wmWorldState->m_mainState == 1) {
			copyrightAlpha = static_cast<float>(DOUBLE_80331770 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else {
			copyrightAlpha = FLOAT_803313e8;
		}
		matColor.r = 0xFF;
		matColor.g = 0xFF;
		matColor.b = 0xFF;
		matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * copyrightAlpha));
		GXSetChanMatColor(GX_COLOR0A0, matColor);
		MenuPcs.DrawRect(0, FLOAT_803317c4, FLOAT_803317c8, FLOAT_803317cc, FLOAT_80331440,
		         FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

		// Timer / state transitions
		state = m_wmWorldState->m_mainState;
		if (state >= 2) {
			m_wmWorldState->m_titleState++;
			if (m_wmWorldState->m_state12 == 0 &&
			    m_wmWorldState->m_titleState >= 5) {
				m_wmWorldState->m_flag09 = 1;
				m_wmWorldState->m_state12++;
				m_wmWorldState->m_titleState = 0x14;
			}
		}

		// Fade out / transition to next state
		state = m_wmWorldState->m_mainState;
		if (state == 3 || (state == 1 && static_cast<signed char>(lbl_8032E8AC) != 0)) {
			float fadeAlpha2;
			if (state == 3) {
				fadeAlpha2 = static_cast<float>(DOUBLE_803314e8 * static_cast<double>(m_wmWorldState->m_frameCounter + 1));
			} else {
				fadeAlpha2 = static_cast<float>(-(DOUBLE_80331770 * static_cast<double>(m_wmWorldState->m_frameCounter) -
				                                 DOUBLE_80331420));
			}
			if (fadeAlpha2 >= FLOAT_803313e8) fadeAlpha2 = FLOAT_803313e8;
			SetAttrFmt((FMT)2);
			matColor.r = 0;
			matColor.g = 0;
			matColor.b = 0;
			matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * fadeAlpha2));
			GXSetChanMatColor(GX_COLOR0A0, matColor);
			MenuPcs.SetTexture((TEX)0xFFFFFFFF);
			_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(5), static_cast<_GXLogicOp>(1));
			GXBegin(GX_QUADS, GX_VTXFMT0, 4);
			GXPosition3f32(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313e0, FLOAT_803313dc, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313e0, FLOAT_803313e4, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313dc, FLOAT_803313e4, FLOAT_803313dc);
		}

		// End state handling
		state = m_wmWorldState->m_mainState;
		if (state == 3 && m_wmWorldState->m_frameCounter >= 0xA) {
			PartMng.pppDeletePart(m_effectWork[23].m_partNo);
			if (m_wmWorldState->m_state0E != 0) {
				lbl_8032E8AC = 1;
				m_wmWorldState->m_changeRequest = 1;
				CFlatRuntime::CStack flatArgs2[3];
				flatArgs2[0].m_word = 7;
				flatArgs2[1].m_word = static_cast<int>(m_wmWorldState->m_cardChannel);
				flatArgs2[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs2, 0);
				bytes[0x0D] = 0;
			} else {
				lbl_8032E8AC = 0;
			}
			m_wmWorldState->m_mainState = 0;
			m_wmWorldState->m_frameCounter = 0;
			m_wmWorldState->m_worldReady = 0;
		} else if (state != 2) {
			unsigned int threshold = 10;
			m_wmWorldState->m_frameCounter++;
			if (m_wmWorldState->m_mainState == 1) {
				threshold = 0x28;
			}
			if (m_wmWorldState->m_frameCounter > threshold) {
				m_wmWorldState->m_frameCounter = 0;
				m_wmWorldState->m_titleState = 0;
				m_wmWorldState->m_mainState++;
			}
		} else {
			if (state == 2 && m_wmWorldState->m_delay != 0) {
				m_wmWorldState->m_delay--;
				if (m_wmWorldState->m_delay <= 0) {
					m_wmWorldState->m_mainState++;
					m_wmWorldState->m_frameCounter = 0;
					m_wmWorldState->m_titleState = 0;
					CFlatRuntime::CStack flatArgs3[3];
					flatArgs3[0].m_word = 9;
					flatArgs3[1].m_word = 1;
					flatArgs3[2].m_word = 0;
					gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs3, 0);
				}
			} else if (m_wmWorldState->m_delay == 0 && m_wmWorldState->m_frameCounter >= 0x992) {
				m_wmWorldState->m_state0E = 0;
				m_wmWorldState->m_mainState++;
				m_wmWorldState->m_frameCounter = 0;
				m_wmWorldState->m_titleState = 0;
				CFlatRuntime::CStack flatArgs4[3];
				flatArgs4[0].m_word = 9;
				flatArgs4[1].m_word = 1;
				flatArgs4[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs4, 0);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f6d70
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetWorldParam(int code, int value)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	switch (code) {
	case 0: {
		const unsigned char primaryMask = s_wmWorldParamPrimaryDirtyMask;
		bytes[5] = bytes[4];
		bytes[4] = static_cast<unsigned char>(value);
		bytes[0xA] = primaryMask | bytes[0xA];
		break;
	}
	case 1:
		bytes[6] = static_cast<unsigned char>(value);
		break;
	case 2:
		*reinterpret_cast<unsigned short*>(bytes + 0x1A) = static_cast<unsigned short>(value) & 0x3FF;
		break;
	case 3:
		bytes[7] = static_cast<unsigned char>(value);
		break;
	case 4:
		bytes[8] = static_cast<unsigned char>(value);
		break;
	case 5:
		*reinterpret_cast<unsigned short*>(bytes + 0x1C) = static_cast<unsigned short>(value);
		break;
	case 6:
		*reinterpret_cast<unsigned short*>(bytes + 0x1E) = static_cast<unsigned short>(value);
		break;
	case 7:
		bytes[9] = static_cast<unsigned char>(value);
		break;
	case 8: {
		const unsigned char secondaryMask = s_wmWorldParamSecondaryDirtyMask;
		bytes[0xB] = bytes[0xC];
		bytes[0xC] = static_cast<unsigned char>(value);
		bytes[0xA] = secondaryMask | bytes[0xA];
		break;
	}
	case 9:
		if (static_cast<int>(static_cast<signed char>(bytes[0xD])) != value) {
			bytes[0xD] = static_cast<unsigned char>(value);
		}
		m_wmWorldState->m_changeRequest = 2;
		break;
	case 10:
		bytes[0x10] = static_cast<unsigned char>((static_cast<unsigned int>(-value) | static_cast<unsigned int>(value)) >> 31);
		break;
	case 11:
		bytes[0x11] = static_cast<unsigned char>((static_cast<unsigned int>(-value) | static_cast<unsigned int>(value)) >> 31);
		break;
	case 12:
		bytes[0xE] = static_cast<unsigned char>(value);
		break;
	case 13:
		bytes[0xF] = static_cast<unsigned char>(value) & 3;
		break;
	case 14:
		bytes[0x12] = static_cast<unsigned char>((static_cast<unsigned int>(-value) | static_cast<unsigned int>(value)) >> 31);
		break;
	case 15:
		bytes[0x13] = static_cast<unsigned char>((static_cast<unsigned int>(-value) | static_cast<unsigned int>(value)) >> 31);
		break;
	case 16:
		bytes[0x17] = static_cast<unsigned char>(value);
		break;
	case 0x12: {
		McCtrl* mc = GetMcCtrl();
		mc->m_previousState = 0;
		mc->m_state = 0;
		mc->m_lastResult = 0;
		mc->m_iteration = 0;
		mc->m_userBuffer = 0;
		mc->m_createFlag = 0;
		mc->m_cardChannel = static_cast<int>(static_cast<signed char>(bytes[0x17]));
		bytes[0x18] = 0x12;
		break;
	}
	case 0x13: {
		McCtrl* mc = GetMcCtrl();
		mc->m_previousState = 0;
		mc->m_state = 0;
		mc->m_lastResult = 0;
		mc->m_iteration = 0;
		mc->m_userBuffer = 0;
		mc->m_createFlag = 0;
		mc->m_cardChannel = static_cast<int>(static_cast<signed char>(bytes[0x17]));
		bytes[0x18] = 0x13;
		break;
	}
	case 0x14:
		MemoryCardMan.McEnd();
		bytes[0x14] = 1;
		break;
	case 0x16:
		bytes[0x15] = 1;
		changeMode(static_cast<MENUMODE>(2));
		bytes[0x15] = 1;
		break;
	case 0x17: {
		unsigned int clz = __cntlzw(static_cast<unsigned int>(value));
		CameraPcs.m_worldMapEffect.m_flags =
		    static_cast<unsigned char>(static_cast<int>(static_cast<unsigned char>(clz >> 5)) << 7) |
		    (CameraPcs.m_worldMapEffect.m_flags & 0x7F);
		CameraPcs.m_worldMapEffect.m_timer = 0x4B;
		CameraPcs.m_worldMapEffect.m_duration = 0x4B;
		CameraPcs.m_worldMapEffect.m_rotX = FLOAT_80331618;
		CameraPcs.m_worldMapEffect.m_rotY = FLOAT_80331760;
		CameraPcs.m_worldMapEffect.m_scale = FLOAT_80331764;
		break;
	}
	case 0x18:
		loadData();
		break;
	case 0x19:
		bytes[0x16] = 1;
		break;
	case 0x1a: {
		int i = 0;
		do {
			GbaQue.SetRadarMode(i, 0);
			i = i + 1;
		} while (i < 4);
		break;
	}
	case 0x1b:
		GbaQue.SetControllerMode(static_cast<int>((static_cast<unsigned int>(-value) | static_cast<unsigned int>(value)) >> 31));
		break;
	default:
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
			System.Printf(const_cast<char*>(s__s__d___Error_function_code_not_f_801dc3ec), s_wm_menu_cpp, 0x1482, code);
		}
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f6afc
 * PAL Size: 628b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::GetWorldParam(int code)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned int result = 0;

	switch (code) {
	case 0:
		result = *reinterpret_cast<signed char*>(bytes + 4);
		break;
	case 1:
		result = *reinterpret_cast<signed char*>(bytes + 6);
		break;
	case 2:
		result = static_cast<unsigned int>(*reinterpret_cast<short*>(bytes + 0x1A));
		break;
	case 3:
		result = *reinterpret_cast<signed char*>(bytes + 7);
		break;
	case 4:
		result = *reinterpret_cast<signed char*>(bytes + 8);
		break;
	case 5:
		result = static_cast<unsigned int>(*reinterpret_cast<short*>(bytes + 0x1C));
		break;
	case 6:
		result = static_cast<unsigned int>(*reinterpret_cast<short*>(bytes + 0x1E));
		break;
	case 7:
		result = *reinterpret_cast<signed char*>(bytes + 9);
		break;
	case 8:
		result = *reinterpret_cast<signed char*>(bytes + 0xC);
		break;
	case 9:
		result = *reinterpret_cast<signed char*>(bytes + 0xD);
		break;
	case 10:
		result = (-static_cast<unsigned int>(bytes[0x10]) | static_cast<unsigned int>(bytes[0x10])) >> 31;
		break;
	case 11:
		result = (-static_cast<unsigned int>(bytes[0x11]) | static_cast<unsigned int>(bytes[0x11])) >> 31;
		break;
	case 12:
		result = *reinterpret_cast<signed char*>(bytes + 0xE);
		break;
	case 13:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[0xF]));
		break;
	case 14:
		result = (-static_cast<unsigned int>(bytes[0x12]) | static_cast<unsigned int>(bytes[0x12])) >> 31;
		break;
	case 15:
		result = (-static_cast<unsigned int>(bytes[0x13]) | static_cast<unsigned int>(bytes[0x13])) >> 31;
		break;
	case 16:
		result = *reinterpret_cast<signed char*>(bytes + 0x17);
		break;
	case 0x11: {
		int iVar1;
		int iVar3 = 0;
		do {
			iVar1 = MemoryCardMan.McChkConnect(0);
			if (iVar1 != 1) break;
			iVar3 = iVar3 + 1;
		} while (iVar3 < 10);
		if (iVar1 == 0) {
			result = result | 1;
		} else if (iVar1 == 1) {
			result = result | 7;
		} else if (iVar1 != -1) {
			if (iVar1 == -2) {
				result = result | 2;
			} else if (iVar1 == -3) {
				result = result | 3;
			} else {
				result = result | 6;
			}
		}
		iVar3 = 0;
		do {
			iVar1 = MemoryCardMan.McChkConnect(1);
			if (iVar1 != 1) break;
			iVar3 = iVar3 + 1;
		} while (iVar3 < 10);
		if (iVar1 == 0) {
			result = result | 0x10;
		} else if (iVar1 == 1) {
			result = result | 0x70;
		} else if (iVar1 != -1) {
			if (iVar1 == -2) {
				result = result | 0x20;
			} else if (iVar1 == -3) {
				result = result | 0x30;
			} else {
				result = result | 0x60;
			}
		}
		break;
	}
	case 0x15:
		result = 0x16;
		break;
	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1a:
	case 0x1b:
	default:
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
			System.Printf(const_cast<char*>(s__s__d___Error_function_code_not_f_801dc3ec), s_wm_menu_cpp, 0x1521, code);
		}
		break;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800f6ab0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CallWorldParam(int p0, int p1, int p2)
{
	CFlatRuntime::CStack stackData[3];
	stackData[0].m_word = p0;
	stackData[1].m_word = p1;
	stackData[2].m_word = p2;

	gCFlatRuntime().SystemCall(0, 1, 4, 3, stackData, 0);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcSpl(CMenuPcs::SPL* out, CMenuPcs::SPL* in, float t)
{
	if (out == 0 || in == 0) {
		return;
	}
	if (t < 0.0f) {
		t = 0.0f;
	}
	if (t > 1.0f) {
		t = 1.0f;
	}
	memcpy(out, in, sizeof(CMenuPcs::SPL));
}

/*
 * --INFO--
 * PAL Address: 0x800f69a8
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
double CMenuPcs::GetFcvValue(CMenuPcs::FCV fcv, float value)
{
	int keyCount = fcv.keyCount;
	float t = value / FLOAT_803314c0;
	float* keys = fcv.keys;
	float result = FLOAT_803313dc;

	if (t >= keys[keyCount * 4 - 4]) {
		return static_cast<double>(keys[keyCount * 4 - 3]);
	}

	float* cur = keys;
	int idx;
	for (idx = 0; idx < keyCount; cur += 4, idx++) {
		if (t <= *cur) {
			if (idx == 0) {
				result = (keys + idx * 4)[1];
			} else {
				float* next = keys + idx * 4;
				float* prev = keys + (idx - 1) * 4;
				float span = *next - *prev;
				float u = (t - *prev) / span;
				float u2 = u * u;
				float u3 = u2 * u;
				float c4u2 = FLOAT_803314c4 * u2;
				float negTerm = -(FLOAT_803314c8 * u2 - u3);

				result = span * (prev[3] * (u + negTerm) + next[2] * (u3 - u2)) +
				         (prev[1] * (FLOAT_803313e8 + (FLOAT_803314c8 * u3 - c4u2)) +
				             next[1] * (FLOAT_803314cc * u3 + c4u2));
			}
			break;
		}
	}
	return static_cast<double>(result);
}

/*
 * --INFO--
 * PAL Address: 0x800f67e0
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetProjection(int mode)
{
	unsigned char* const slot = m_wm.m_worldObjData + mode * 0x50;
	Mtx44 projectionMtx;
	C_MTXPerspective(projectionMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
	GXSetProjection(projectionMtx, GX_PERSPECTIVE);
	PSMTX44Copy(projectionMtx, CameraPcs.m_screenMatrix);

	CVector target(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc);
	CVector up(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc);

	Mtx lookAtMtx;
	C_MTXLookAt(lookAtMtx, reinterpret_cast<Point3d*>(slot + 0x10), reinterpret_cast<Vec*>(&up),
	    reinterpret_cast<Point3d*>(&target));
	PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(this) + 0x744));
	PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);

	CharaPcs.InitEnv(5);
	GXSetColorUpdate(0);
	GXSetAlphaUpdate(0);
	GXSetCopyClear(CColor(0, 0, 0, 0).color, 0x00FFFFFF);
	GXSetColorUpdate(1);
	GXSetAlphaUpdate(1);

	GXSetViewport(
	    static_cast<float>(*reinterpret_cast<short*>(slot + 8)),
	    static_cast<float>(*reinterpret_cast<short*>(slot + 0xA)),
	    static_cast<float>(*reinterpret_cast<short*>(slot + 0xC)),
	    static_cast<float>(*reinterpret_cast<short*>(slot + 0xE)),
	    FLOAT_803313dc,
	    FLOAT_803313e8);
	GXSetScissor(
	    *reinterpret_cast<unsigned int*>(slot + 0x40),
	    *reinterpret_cast<unsigned int*>(slot + 0x44),
	    *reinterpret_cast<unsigned int*>(slot + 0x48),
	    *reinterpret_cast<unsigned int*>(slot + 0x4C));
}

/*
 * --INFO--
 * PAL Address: 0x800f673c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::RestoreProjection()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	PSMTXCopy(reinterpret_cast<float(*)[4]>(bytes + 0x744), CameraPcs.m_cameraMatrix);
	GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0x00FFFFFF);
	Mtx44 projectionMtx;
	PSMTX44Copy(CameraPcs.m_screenMatrix, projectionMtx);
	GXSetProjection(projectionMtx, GX_PERSPECTIVE);
	Graphic.SetViewport();
	GXSetScissor(0, 0, 0x280, 0x1C0);
	DrawInit();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawObj(int kind)
{
	if (kind == 0) {
		DrawChara();
	} else if (kind == 1) {
		DrawMcObj();
	} else {
		DrawWMFrame();
		DrawFukidashi();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f653c
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcPitcher()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	short state = m_wmWorldState->m_mainState;
	if (state == 0 || state > 2) {
		return;
	}

	unsigned char* worldObj = m_wm.m_worldObjData;

	const float one = FLOAT_803313e8;
	const float pb8 = FLOAT_803315d0;
	const float pb4 = FLOAT_80331750;
	const float pb0 = FLOAT_8033174c;
	const float pac = FLOAT_80331748;
	const float pa8 = FLOAT_803314a4;
	reinterpret_cast<unsigned int*>(worldObj + 0x190)[0] = 1;
	reinterpret_cast<short*>(worldObj + 0x198)[0] = 0x140;
	reinterpret_cast<short*>(worldObj + 0x19A)[0] = 0xE0;
	reinterpret_cast<short*>(worldObj + 0x19C)[0] = 0x140;
	reinterpret_cast<short*>(worldObj + 0x19E)[0] = 0xE0;
	reinterpret_cast<float*>(worldObj + 0x1A0)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(worldObj + 0x1A4)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(worldObj + 0x1A8)[0] = pa8;
	reinterpret_cast<float*>(worldObj + 0x1AC)[0] = pac;
	reinterpret_cast<float*>(worldObj + 0x1B0)[0] = pb0;
	reinterpret_cast<float*>(worldObj + 0x1B4)[0] = pb4;
	reinterpret_cast<float*>(worldObj + 0x1B8)[0] = pb8;
	reinterpret_cast<float*>(worldObj + 0x1BC)[0] += FLOAT_80331754;

	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	PSMTXScale(scaleMtx, one, one, one);
	PSMTXRotRad(rotXMtx, 'x', reinterpret_cast<float*>(worldObj + 0x1B8)[0]);
	PSMTXRotRad(rotYMtx, 'y', reinterpret_cast<float*>(worldObj + 0x1BC)[0]);
	PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
	rotXMtx[0][3] = reinterpret_cast<float*>(worldObj + 0x1AC)[0];
	rotXMtx[1][3] = reinterpret_cast<float*>(worldObj + 0x1B0)[0];
	rotXMtx[2][3] = reinterpret_cast<float*>(worldObj + 0x1B4)[0];
	PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);

	short step = m_wmWorldState->m_frameCounter;
	float blendStep = static_cast<float>(DOUBLE_803314e8 * static_cast<double>(step));
	if (m_wmWorldState->m_mainState == 1 && step < 10) {
		reinterpret_cast<float*>(
			reinterpret_cast<unsigned char*>(reinterpret_cast<CCharaPcs::CHandle**>(bytes + 0x788)[0]->m_model) + 0x9C)[0] = blendStep;
	} else if (m_wmWorldState->m_mainState == 2 && bytes[0x13] != 0) {
		reinterpret_cast<float*>(
			reinterpret_cast<unsigned char*>(reinterpret_cast<CCharaPcs::CHandle**>(bytes + 0x788)[0]->m_model) + 0x9C)[0] =
			static_cast<float>(DOUBLE_80331420 - static_cast<double>(blendStep));
	} else {
		reinterpret_cast<float*>(
			reinterpret_cast<unsigned char*>(reinterpret_cast<CCharaPcs::CHandle**>(bytes + 0x788)[0]->m_model) + 0x9C)[0] =
			FLOAT_803313e8;
	}

	reinterpret_cast<CCharaPcs::CHandle**>(bytes + 0x788)[0]->m_model->SetMatrix(scaleMtx);
	reinterpret_cast<int*>(
		reinterpret_cast<unsigned char*>(reinterpret_cast<CCharaPcs::CHandle**>(bytes + 0x788)[0]->m_model) + 0x98)[0] =
		static_cast<char>(lbl_80331380[Game.m_gameWork.m_timerA]);
	reinterpret_cast<CCharaPcs::CHandle**>(bytes + 0x788)[0]->m_model->CalcMatrix();
	reinterpret_cast<CCharaPcs::CHandle**>(bytes + 0x788)[0]->m_model->CalcSkin();
}

/*
 * --INFO--
 * PAL Address: 0x800f554c
 * PAL Size: 4080b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimize_for_size on
void CMenuPcs::CalcFukidashi()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if ((char)bytes[0x09] != 1) {
		return;
	}
	float fVar1 = FLOAT_803313dc;
#define WOBJ() reinterpret_cast<int>(m_wm.m_worldObjData)

#define BUB() reinterpret_cast<int>(m_wm.m_bubbleData)
	*reinterpret_cast<unsigned short*>(BUB()) = *reinterpret_cast<short*>(bytes + 0x1C);
	*reinterpret_cast<short*>(BUB() + 2) = *reinterpret_cast<short*>(bytes + 0x1E);
	*reinterpret_cast<short*>(BUB() + 4) = 0xF0;
	*reinterpret_cast<short*>(BUB() + 6) = 0xC4;
	*reinterpret_cast<float*>(BUB() + 0x0C) = fVar1;
	if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
		*reinterpret_cast<float*>(BUB() + 8) = FLOAT_803313dc;
	} else {
		*reinterpret_cast<float*>(BUB() + 8) = FLOAT_80331704;
	}

	fVar1 = FLOAT_80331708;
	if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x3F0) != 0) {
		*reinterpret_cast<short*>(BUB() + 0x20) = 0x50;
		float fVar2 = FLOAT_803313dc;
		*reinterpret_cast<short*>(BUB() + 0x22) = 0x48;
		*reinterpret_cast<float*>(BUB() + 0x24) = fVar1;
		*reinterpret_cast<float*>(BUB() + 0x28) = fVar2;
		*reinterpret_cast<short*>(BUB() + 0x1E) = *reinterpret_cast<short*>(BUB() + 2) + 0x1C;
		if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
			*reinterpret_cast<short*>(BUB() + 0x1E) = *reinterpret_cast<short*>(BUB() + 0x1E) + 0x10;
		}
		*reinterpret_cast<short*>(BUB() + 0x1C) = *reinterpret_cast<short*>(BUB());
		if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0xF) != 0) {
			*reinterpret_cast<short*>(BUB() + 0x1C) = *reinterpret_cast<short*>(BUB() + 0x1C) + 0x20;
		} else if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x200) != 0) {
			*reinterpret_cast<short*>(BUB() + 0x1C) = *reinterpret_cast<short*>(BUB() + 0x1C) + 0x50;
		} else {
			*reinterpret_cast<short*>(BUB() + 0x1C) = *reinterpret_cast<short*>(BUB() + 0x1C) + 0x38;
		}
	}

	fVar1 = FLOAT_803313dc;
	if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x1FF) != 0) {
		*reinterpret_cast<short*>(BUB() + 0x3C) = 0x20;
		*reinterpret_cast<short*>(BUB() + 0x3E) = 0x20;
		*reinterpret_cast<float*>(BUB() + 0x40) = fVar1;
		*reinterpret_cast<float*>(BUB() + 0x44) = fVar1;

		// Copy first icon rect to second
		int iVar9 = BUB();
		*reinterpret_cast<short*>(iVar9 + 0x54) = *reinterpret_cast<short*>(iVar9 + 0x38);
		*reinterpret_cast<short*>(iVar9 + 0x56) = *reinterpret_cast<short*>(iVar9 + 0x3A);
		*reinterpret_cast<short*>(iVar9 + 0x58) = *reinterpret_cast<short*>(iVar9 + 0x3C);
		*reinterpret_cast<short*>(iVar9 + 0x5A) = *reinterpret_cast<short*>(iVar9 + 0x3E);
		*reinterpret_cast<float*>(iVar9 + 0x5C) = *reinterpret_cast<float*>(iVar9 + 0x40);
		*reinterpret_cast<float*>(iVar9 + 0x60) = *reinterpret_cast<float*>(iVar9 + 0x44);
		*reinterpret_cast<float*>(iVar9 + 0x64) = *reinterpret_cast<float*>(iVar9 + 0x48);
		*reinterpret_cast<float*>(iVar9 + 0x68) = *reinterpret_cast<float*>(iVar9 + 0x4C);
		*reinterpret_cast<int*>(iVar9 + 0x6C) = *reinterpret_cast<int*>(iVar9 + 0x50);

		short flagsF = *reinterpret_cast<short*>(bytes + 0x1A);
		int bitIdx = 0;
		int cnt = 0;
		iVar9 = BUB();
		int sVar15 = *reinterpret_cast<short*>(iVar9 + 0x1C) + *reinterpret_cast<short*>(iVar9 + 0x20);
		if ((flagsF & 0xF) != 0) {
			*reinterpret_cast<short*>(iVar9 + 0x54) = sVar15;
			*reinterpret_cast<short*>(BUB() + 0x38) = sVar15;
			for (; bitIdx < 4; bitIdx++) {
				if (((int)*reinterpret_cast<short*>(bytes + 0x1A) & (1 << bitIdx)) != 0) {
					cnt++;
				}
			}
			if (cnt == 1) {
				*reinterpret_cast<short*>(BUB() + 0x3A) =
				    *reinterpret_cast<short*>(BUB() + 0x1E);
				*reinterpret_cast<short*>(BUB() + 0x3A) =
				    *reinterpret_cast<short*>(BUB() + 0x3A) + 0x14;
			} else {
				*reinterpret_cast<short*>(BUB() + 0x3A) =
				    *reinterpret_cast<short*>(BUB() + 0x1E);
				iVar9 = BUB();
				*reinterpret_cast<short*>(iVar9 + 0x56) =
				    *reinterpret_cast<short*>(iVar9 + 0x1E) + *reinterpret_cast<short*>(iVar9 + 0x22) - 0x20;
			}
		} else {
			*reinterpret_cast<short*>(iVar9 + 0x54) = sVar15 + 8;
			*reinterpret_cast<short*>(BUB() + 0x38) = sVar15 + 8;
			*reinterpret_cast<short*>(BUB() + 0x3A) =
			    *reinterpret_cast<short*>(BUB() + 0x1E);
			*reinterpret_cast<short*>(BUB() + 0x3A) =
			    *reinterpret_cast<short*>(BUB() + 0x3A) + 0x14;
		}
	}

	// Font name text processing
	CFont* fontFC = m_fonts[1];
	fontFC->SetMargin(FLOAT_803313e8);
	fontFC->SetShadow(0);
	fontFC->SetScale(FLOAT_803313e8);

	char nameBuffer[64];
	char tempBuf[64];
	char secondLine[64];
	int fieldVal = (int)(char)bytes[0x07];
	if (fieldVal == 0x0F) {
		strcpy(nameBuffer, Game.m_gameWork.m_townName);
	} else if (fieldVal == 0x16) {
		int languageId = Game.m_gameWork.m_languageId;
		if (languageId == 2) {
			strcpy(nameBuffer, Game.m_gameWork.m_townName);
			strcat(nameBuffer, lbl_80210D10[languageId - 1]);
		} else {
			strcpy(nameBuffer, lbl_80210D10[languageId - 1]);
			strcat(nameBuffer, Game.m_gameWork.m_townName);
		}
	} else {
		strcpy(nameBuffer, Game.m_cFlatDataArr[1].TableStrings(3)[fieldVal]);
	}
	if (nameBuffer[0] != '\0') {
		nameBuffer[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(nameBuffer[0])));
	}

	unsigned int textWidth = 0xD8;
	CFont* font = m_fonts[1];
	if (*reinterpret_cast<short*>(bytes + 0x1A) != 0) {
		textWidth = 0xA2;
	}
	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_803313e8);
	double dVar23 = (double)font->GetWidth(nameBuffer);
	if (dVar23 > static_cast<double>(static_cast<float>(static_cast<int>(textWidth)))) {
		strcpy(tempBuf, nameBuffer);
		char* spacePos = strrchr(tempBuf, 0x20);
		if (spacePos != NULL) {
			*spacePos = 0;
			strcpy(secondLine, spacePos + 1);
		} else {
			secondLine[0] = 0;
		}
		strcpy(nameBuffer, tempBuf);
	}
	float nameWidthF = fontFC->GetWidth(nameBuffer);

	int sVar15 = 0x4C;
	*reinterpret_cast<short*>(BUB() + 0x70) =
	    static_cast<short>(static_cast<int>(
	        (FLOAT_80331704 - nameWidthF) * FLOAT_80331434 +
	        static_cast<float>(static_cast<int>(*reinterpret_cast<short*>(BUB())))));
	float fVar2 = FLOAT_803314a4;
	fVar1 = FLOAT_803313dc;
	unsigned short uVar3 = *reinterpret_cast<short*>(bytes + 0x1A);
	if ((uVar3 & 0x3F0) != 0) {
		sVar15 = 0x6C;
	}
	if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
		sVar15 = sVar15 + 0x10;
	}

	// Set text position
	int iVar11 = 6;
	int iVar9 = 0x1E0;
	*reinterpret_cast<short*>(BUB() + 0x72) =
	    *reinterpret_cast<short*>(BUB() + 2) + sVar15;
	*reinterpret_cast<short*>(BUB() + 0x72) =
	    *reinterpret_cast<short*>(BUB() + 0x72) - 4;

	// Setup model viewport slots
	int sVar15b = *reinterpret_cast<short*>(BUB()) - 0x28;
	int sVar22 = *reinterpret_cast<short*>(BUB() + 2) - 0x0E;
	int iVar13;
	for (iVar13 = 2; iVar13 > 0; iVar13--) {
		int* puVar20 = reinterpret_cast<int*>(WOBJ() + iVar9);
		int iVar19 = iVar9 + 0x50;
		puVar20[0] = 0;
		int iVar18 = iVar9 + 0xA0;
		int iVar17 = iVar9 + 0xF0;
		int iVar16 = iVar9 + 0x140;
		*reinterpret_cast<short*>(puVar20 + 2) = sVar15b;
		iVar9 = iVar9 + 400;
		iVar11 = iVar11 + 5;
		*reinterpret_cast<short*>((int)(puVar20 + 2) + 2) = sVar22;
		*reinterpret_cast<short*>(puVar20 + 3) = 0x140;
		*reinterpret_cast<short*>((int)(puVar20 + 3) + 2) = 0xE0;
		*reinterpret_cast<float*>(puVar20 + 4) = fVar1;
		*reinterpret_cast<float*>(puVar20 + 5) = fVar1;
		*reinterpret_cast<float*>(puVar20 + 6) = fVar2;
		iVar19 = WOBJ() + iVar19;
		*reinterpret_cast<int*>(iVar19) = 0;
		*reinterpret_cast<short*>(iVar19 + 8) = sVar15b;
		*reinterpret_cast<short*>(iVar19 + 0xA) = sVar22;
		*reinterpret_cast<short*>(iVar19 + 0xC) = 0x140;
		*reinterpret_cast<short*>(iVar19 + 0xE) = 0xE0;
		*reinterpret_cast<float*>(iVar19 + 0x10) = fVar1;
		*reinterpret_cast<float*>(iVar19 + 0x14) = fVar1;
		*reinterpret_cast<float*>(iVar19 + 0x18) = fVar2;
		iVar18 = WOBJ() + iVar18;
		*reinterpret_cast<int*>(iVar18) = 0;
		*reinterpret_cast<short*>(iVar18 + 8) = sVar15b;
		*reinterpret_cast<short*>(iVar18 + 0xA) = sVar22;
		*reinterpret_cast<short*>(iVar18 + 0xC) = 0x140;
		*reinterpret_cast<short*>(iVar18 + 0xE) = 0xE0;
		*reinterpret_cast<float*>(iVar18 + 0x10) = fVar1;
		*reinterpret_cast<float*>(iVar18 + 0x14) = fVar1;
		*reinterpret_cast<float*>(iVar18 + 0x18) = fVar2;
		iVar17 = WOBJ() + iVar17;
		*reinterpret_cast<int*>(iVar17) = 0;
		*reinterpret_cast<short*>(iVar17 + 8) = sVar15b;
		*reinterpret_cast<short*>(iVar17 + 0xA) = sVar22;
		*reinterpret_cast<short*>(iVar17 + 0xC) = 0x140;
		*reinterpret_cast<short*>(iVar17 + 0xE) = 0xE0;
		*reinterpret_cast<float*>(iVar17 + 0x10) = fVar1;
		*reinterpret_cast<float*>(iVar17 + 0x14) = fVar1;
		*reinterpret_cast<float*>(iVar17 + 0x18) = fVar2;
		iVar16 = WOBJ() + iVar16;
		*reinterpret_cast<int*>(iVar16) = 0;
		*reinterpret_cast<short*>(iVar16 + 8) = sVar15b;
		*reinterpret_cast<short*>(iVar16 + 0xA) = sVar22;
		*reinterpret_cast<short*>(iVar16 + 0xC) = 0x140;
		*reinterpret_cast<short*>(iVar16 + 0xE) = 0xE0;
		*reinterpret_cast<float*>(iVar16 + 0x10) = fVar1;
		*reinterpret_cast<float*>(iVar16 + 0x14) = fVar1;
		*reinterpret_cast<float*>(iVar16 + 0x18) = fVar2;
		fVar2 = FLOAT_803314a4;
		fVar1 = FLOAT_803313dc;
	}

	// Fill remaining viewport slots
	for (; iVar11 <= 0x10; iVar11++) {
		int* puVar20 = reinterpret_cast<int*>(WOBJ() + iVar11 * 0x50);
		puVar20[0] = 0;
		*reinterpret_cast<short*>(puVar20 + 2) = sVar15b;
		*reinterpret_cast<short*>((int)(puVar20 + 2) + 2) = sVar22;
		*reinterpret_cast<short*>(puVar20 + 3) = 0x140;
		*reinterpret_cast<short*>((int)(puVar20 + 3) + 2) = 0xE0;
		*reinterpret_cast<float*>(puVar20 + 4) = fVar1;
		*reinterpret_cast<float*>(puVar20 + 5) = fVar1;
		*reinterpret_cast<float*>(puVar20 + 6) = fVar2;
	}

	// Setup tribe/character model slot
	fVar2 = FLOAT_8033170c;
	fVar1 = FLOAT_803313dc;
	short sFlags = *reinterpret_cast<short*>(bytes + 0x1A);
	if ((sFlags & 0x3F0) != 0) {
		int modelIdx;
		if ((sFlags & 0x200) != 0) {
			if ((char)bytes[0x06] == 1) {
				modelIdx = 7;
			} else {
				modelIdx = 6;
			}
		} else {
			modelIdx = 0;
			if ((sFlags & 0x10) == 0) { modelIdx = 1;
			if ((sFlags & 0x20) == 0) { modelIdx = 2;
			if ((sFlags & 0x40) == 0) { modelIdx = 3;
			if ((sFlags & 0x80) == 0) { modelIdx = 4;
			if ((sFlags & 0x100) == 0) { modelIdx = 5; }}}}}
			modelIdx = modelIdx + 0x0C;
		}

		int* puVar20 = reinterpret_cast<int*>(WOBJ() + modelIdx * 0x50);
		puVar20[0] = 1;
		*reinterpret_cast<float*>(puVar20 + 7) = fVar1;
		*reinterpret_cast<float*>(puVar20 + 8) = fVar1;
		*reinterpret_cast<float*>(puVar20 + 9) = fVar1;
		*reinterpret_cast<float*>(puVar20 + 0xD) = fVar2;
		*reinterpret_cast<float*>(puVar20 + 0xE) = fVar2;
		*reinterpret_cast<float*>(puVar20 + 0xF) = fVar2;
		if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
			*reinterpret_cast<float*>(puVar20 + 8) = FLOAT_80331710;
		}
		if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0xF) != 0) {
			*reinterpret_cast<float*>(puVar20 + 7) = FLOAT_80331714;
			*reinterpret_cast<float*>(puVar20 + 8) = static_cast<float>(
			    static_cast<double>(*reinterpret_cast<float*>(puVar20 + 8)) + DOUBLE_80331420);
		} else if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x200) != 0) {
			*reinterpret_cast<float*>(puVar20 + 7) = FLOAT_803313dc;
			*reinterpret_cast<float*>(puVar20 + 8) = static_cast<float>(
			    static_cast<double>(*reinterpret_cast<float*>(puVar20 + 8)) + DOUBLE_80331420);
		} else {
			*reinterpret_cast<float*>(puVar20 + 7) = FLOAT_80331718;
			*reinterpret_cast<float*>(puVar20 + 8) = static_cast<float>(
			    static_cast<double>(*reinterpret_cast<float*>(puVar20 + 8)) + DOUBLE_80331720);
		}

		// Spline evaluation for Y position
		float t = static_cast<float>(puVar20[1]) / FLOAT_803314c0;
		float yResult;
		WM_MENU_EVAL_SPLINE(yResult, gWmModelYOffsetSpline, gWmModelYOffsetSplineCount, t);
		*reinterpret_cast<float*>(puVar20 + 8) = *reinterpret_cast<float*>(puVar20 + 8) + yResult;

		// Spline evaluation for rotation
		float rotResult;
		t = static_cast<float>(puVar20[1]) / FLOAT_803314c0;
		WM_MENU_EVAL_SPLINE(rotResult, gWmModelRotationSpline, gWmModelRotationSplineCount, t);
		*reinterpret_cast<float*>(puVar20 + 0xB) = FLOAT_803314bc * rotResult;
		*reinterpret_cast<float*>(puVar20 + 0xA) = FLOAT_803315d0;

		// Matrix setup
		Mtx scaleMtx, rotXMtx, rotYMtx;
		PSMTXScale(scaleMtx, *reinterpret_cast<float*>(puVar20 + 0xD), *reinterpret_cast<float*>(puVar20 + 0xE), *reinterpret_cast<float*>(puVar20 + 0xF));
		PSMTXRotRad(rotXMtx, 'x', *reinterpret_cast<float*>(puVar20 + 0xA));
		PSMTXRotRad(rotYMtx, 'y', *reinterpret_cast<float*>(puVar20 + 0xB));
		PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
		rotXMtx[0][3] = *reinterpret_cast<float*>(puVar20 + 7);
		rotXMtx[1][3] = *reinterpret_cast<float*>(puVar20 + 8);
		rotXMtx[2][3] = *reinterpret_cast<float*>(puVar20 + 9);
		PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);

#define modelPtr (*reinterpret_cast<CChara::CModel**>(*reinterpret_cast<int*>(bytes + 0x7F4 + modelIdx * 4) + 0x168))
		modelPtr->SetMatrix(scaleMtx);
		modelPtr->CalcMatrix();
		modelPtr->CalcSkin();
#undef modelPtr

		puVar20[1] = puVar20[1] + 1;
		if (static_cast<double>(static_cast<float>(static_cast<double>(puVar20[1]))) >=
		    DOUBLE_803314A8 * static_cast<double>(gWmModelYOffsetSpline[gWmModelYOffsetSplineCount * 4 - 4])) {
			puVar20[1] = 0;
		}
	}

	// Player character model slots
	unsigned int field1a = (unsigned int)*reinterpret_cast<short*>(bytes + 0x1A);
	if ((field1a & 0x200) != 0 && (field1a & 0xF) != 0) {
		int playerCount = 0;
		int iter = 4;
		int idx = 0;
		do {
			if ((field1a & (1 << idx)) != 0) playerCount++;
			idx++;
			iter--;
		} while (iter != 0);

		int slotIdx = 0;
		for (int padIdx = 0; padIdx < 4; padIdx++) {
			if (((int)*reinterpret_cast<short*>(bytes + 0x1A) & (1 << padIdx)) != 0) {
				int* puVar20 = reinterpret_cast<int*>(WOBJ() + (padIdx + 8) * 0x50);
				puVar20[0] = 1;
				*reinterpret_cast<float*>(puVar20 + 7) = FLOAT_80331728;
				if (slotIdx == 0) {
					if (playerCount == 2) {
						*reinterpret_cast<float*>(puVar20 + 8) = FLOAT_8033172c;
					} else {
						*reinterpret_cast<float*>(puVar20 + 8) = FLOAT_80331668;
					}
				} else {
					*reinterpret_cast<float*>(puVar20 + 8) = FLOAT_80331710;
				}
				if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
					if (padIdx == 0 && playerCount == 1) {
						*reinterpret_cast<float*>(puVar20 + 8) = static_cast<float>(
						    static_cast<double>(*reinterpret_cast<float*>(puVar20 + 8)) - DOUBLE_80331730);
					} else {
						*reinterpret_cast<float*>(puVar20 + 8) = static_cast<float>(
						    static_cast<double>(*reinterpret_cast<float*>(puVar20 + 8)) - DOUBLE_80331738);
					}
				}
				*reinterpret_cast<float*>(puVar20 + 9) = FLOAT_803313dc;
				float f740 = FLOAT_80331740;
				*reinterpret_cast<float*>(puVar20 + 0xD) = f740;
				*reinterpret_cast<float*>(puVar20 + 0xE) = f740;
				*reinterpret_cast<float*>(puVar20 + 0xF) = f740;

				// Spline Y for player models
				float t2 = static_cast<float>(puVar20[1]) / FLOAT_803314c0;
				float yRes2;
				WM_MENU_EVAL_SPLINE(yRes2, gWmModelYOffsetSpline, gWmModelYOffsetSplineCount, t2);
				*reinterpret_cast<float*>(puVar20 + 8) = *reinterpret_cast<float*>(puVar20 + 8) + yRes2;

				// Spline rotation for player models
				float rotRes2;
				t2 = static_cast<float>(puVar20[1]) / FLOAT_803314c0;
				WM_MENU_EVAL_SPLINE(rotRes2, gWmModelRotationSpline, gWmModelRotationSplineCount, t2);
				*reinterpret_cast<float*>(puVar20 + 0xB) = FLOAT_803314bc * rotRes2;
				if (playerCount == 1) {
					*reinterpret_cast<float*>(puVar20 + 0xA) = FLOAT_80331744;
				} else {
					*reinterpret_cast<float*>(puVar20 + 0xA) = FLOAT_803315d0;
				}

				Mtx sMtx, rxMtx, ryMtx;
				PSMTXScale(sMtx, *reinterpret_cast<float*>(puVar20 + 0xD), *reinterpret_cast<float*>(puVar20 + 0xE), *reinterpret_cast<float*>(puVar20 + 0xF));
				PSMTXRotRad(rxMtx, 'x', *reinterpret_cast<float*>(puVar20 + 0xA));
				PSMTXRotRad(ryMtx, 'y', *reinterpret_cast<float*>(puVar20 + 0xB));
				PSMTXConcat(rxMtx, ryMtx, rxMtx);
				rxMtx[0][3] = *reinterpret_cast<float*>(puVar20 + 7);
				rxMtx[1][3] = *reinterpret_cast<float*>(puVar20 + 8);
				rxMtx[2][3] = *reinterpret_cast<float*>(puVar20 + 9);
				PSMTXConcat(rxMtx, sMtx, sMtx);

#define mdl (*reinterpret_cast<CChara::CModel**>(*reinterpret_cast<int*>(bytes + 0x7F4 + (padIdx + 8) * 4) + 0x168))
				mdl->SetMatrix(sMtx);
				mdl->CalcMatrix();
				mdl->CalcSkin();
#undef mdl

				puVar20[1] = puVar20[1] + 1;
				if (static_cast<double>(static_cast<float>(static_cast<double>(puVar20[1]))) >=
				    DOUBLE_803314A8 * static_cast<double>(gWmModelYOffsetSpline[gWmModelYOffsetSplineCount * 4 - 4])) {
					puVar20[1] = 0;
				}
				slotIdx++;
			}
		}
	}
#undef BUB
#undef WOBJ
}

#pragma optimize_for_size off

/*
 * --INFO--
 * PAL Address: 0x800f4b24
 * PAL Size: 2600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawFukidashi()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	Mtx& cameraBackup = *reinterpret_cast<Mtx*>(bytes + 0x744);
	CFont* const fontFC = m_fonts[1];
	if (static_cast<signed char>(bytes[0x09]) != 1) {
		return;
	}

	int texMode;
	if (static_cast<signed char>(bytes[0x08]) == 0 || static_cast<signed char>(bytes[0x08]) == 2) {
		texMode = 0;
	} else {
		texMode = 8;
	}

	MenuPcs.SetAttrFmt((FMT)0);
	GXColor matColor;
	matColor.r = 0xFF;
	matColor.g = 0xFF;
	matColor.b = 0xFF;
	matColor.a = 0xFF;
	GXSetChanMatColor(GX_COLOR0A0, matColor);
	MenuPcs.SetTexture((TEX)0x18);

	short* bubData = reinterpret_cast<short*>(m_wm.m_bubbleData);
	MenuPcs.DrawRect(texMode,
		(float)(int)bubData[0], (float)(int)bubData[1],
		(float)(int)bubData[2], (float)(int)bubData[3],
		*reinterpret_cast<float*>(bubData + 4), *reinterpret_cast<float*>(bubData + 6),
		FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

	if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x3F0) != 0) {
		int bd = reinterpret_cast<int>(m_wm.m_bubbleData);
		MenuPcs.DrawRect(0,
			(float)*reinterpret_cast<unsigned short*>(bd + 0x1C), (float)*reinterpret_cast<short*>(bd + 0x1E),
			(float)*reinterpret_cast<short*>(bd + 0x20), (float)*reinterpret_cast<short*>(bd + 0x22),
			*reinterpret_cast<float*>(bd + 0x24), *reinterpret_cast<float*>(bd + 0x28),
			FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
	}

	unsigned int uVar3 = (unsigned int)*reinterpret_cast<short*>(bytes + 0x1A);
	if ((uVar3 & 0x3F0) != 0 && (uVar3 & 0x1FF) != 0) {
		if ((uVar3 & 0xF) != 0) {
			int iVar5 = 0;
			int iVar9 = 0;
			while (iVar5 < 4 && iVar9 < 2) {
				if (((int)*reinterpret_cast<short*>(bytes + 0x1A) & (1 << iVar5)) != 0) {
					MenuPcs.SetTexture((TEX)(iVar5 + 0x19));
					short* psVar4;
					if (iVar9 == 0) {
						psVar4 = reinterpret_cast<short*>(*reinterpret_cast<int*>(bytes + 0x818) + 0x38);
					} else {
						psVar4 = reinterpret_cast<short*>(*reinterpret_cast<int*>(bytes + 0x818) + 0x54);
					}
					MenuPcs.DrawRect(0,
						(float)(int)psVar4[0], (float)(int)psVar4[1],
						(float)(int)psVar4[2], (float)(int)psVar4[3],
						*reinterpret_cast<float*>(psVar4 + 4), *reinterpret_cast<float*>(psVar4 + 6),
						FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
					iVar9++;
				}
				iVar5++;
			}
		} else {
			int idx = 0;
			int cnt = 5;
			do {
				if ((uVar3 & (0x10 << idx)) != 0) {
					MenuPcs.SetTexture((TEX)(idx + 0x19));
					int bd = *reinterpret_cast<int*>(bytes + 0x818);
					MenuPcs.DrawRect(0,
						(float)*reinterpret_cast<short*>(bd + 0x38), (float)*reinterpret_cast<short*>(bd + 0x3A),
						(float)*reinterpret_cast<short*>(bd + 0x3C), (float)*reinterpret_cast<short*>(bd + 0x3E),
						*reinterpret_cast<float*>(bd + 0x40), *reinterpret_cast<float*>(bd + 0x44),
						FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
					break;
				}
				idx++;
				cnt--;
			} while (cnt != 0);
		}
	}

	// Name text
	char nameBuffer[68];
	int fieldVal = (int)(char)bytes[0x07];
	if (fieldVal == 0x0F) {
		strcpy(nameBuffer, Game.m_gameWork.m_townName);
	} else if (fieldVal == 0x16) {
		strcpy(nameBuffer, Game.m_gameWork.m_townName);
		const int language = Game.m_gameWork.m_languageId;
		if (language == 2) {
			strcpy(nameBuffer, Game.m_gameWork.m_townName);
			strcat(nameBuffer, lbl_80210D10[language - 1], sizeof(nameBuffer));
		} else {
			strcpy(nameBuffer, lbl_80210D10[language - 1]);
			strcat(nameBuffer, Game.m_gameWork.m_townName, sizeof(nameBuffer));
		}
	} else {
		strcpy(nameBuffer, Game.m_cFlatDataArr[1].TableStrings(3)[fieldVal]);
	}
	if (nameBuffer[0] != 0) {
		nameBuffer[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(nameBuffer[0])));
	}

	int textW = 0xD8;
	char tempBuf[64];
	char secondLine[64];
	secondLine[0] = 0;
	CFont* const font = m_fonts[1];
	if (*reinterpret_cast<short*>(bytes + 0x1A) != 0) {
		textW = 0xA2;
	}
	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_803313e8);
	double nameWidth = (double)font->GetWidth(nameBuffer);
	int twoLines;
	if (nameWidth > (double)(float)textW) {
		twoLines = 1;
	} else {
		twoLines = 0;
	}
	if (twoLines != 0) {
		strcpy(tempBuf, nameBuffer);
		char* spacePos = strrchr(tempBuf, 0x20);
		if (spacePos != NULL) {
			*spacePos = 0;
			strcpy(secondLine, spacePos + 1);
		} else {
			secondLine[0] = 0;
		}
		strcpy(nameBuffer, tempBuf);
	}

	fontFC->SetMargin(FLOAT_803313e8);
	fontFC->SetShadow(0);
	fontFC->SetScale(FLOAT_803313e8);
	fontFC->DrawInit();
	fontFC->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
	fontFC->SetPosX((float)*reinterpret_cast<short*>(*reinterpret_cast<int*>(bytes + 0x818) + 0x70));
	fontFC->SetPosY((float)*reinterpret_cast<short*>(*reinterpret_cast<int*>(bytes + 0x818) + 0x72));
	fontFC->Draw(nameBuffer);

	if (twoLines != 0) {
		strcpy(nameBuffer, "");
		float w2 = fontFC->GetWidth(secondLine);
		fontFC->SetPosX((FLOAT_80331704 - w2) * FLOAT_80331434 +
		                (float)*reinterpret_cast<short*>(*reinterpret_cast<int*>(bytes + 0x818)));
		fontFC->SetPosY((float)(*reinterpret_cast<short*>(*reinterpret_cast<int*>(bytes + 0x818) + 0x72) + 0x16));
		fontFC->Draw(secondLine);
	}

	DrawInit();

	// 3D viewport rendering
	int viewportSetup = 0;
	if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x3F0) != 0) {
		int viewOff = 0x1E0;
		int effOff = 0x1ED8;
		for (int slot = 6; slot <= 0x10; slot++) {
			int* piVar10 = reinterpret_cast<int*>(*reinterpret_cast<int*>(bytes + 0x814) + viewOff);
			if (*piVar10 != 0) {
				if (viewportSetup == 0) {
					Mtx44 projMtx;
					C_MTXPerspective(projMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
					GXSetProjection(projMtx, GX_PERSPECTIVE);
					PSMTX44Copy(projMtx, CameraPcs.m_screenMatrix);

					CVector eye(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc);
					CVector up(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc);
					Mtx lookAtMtx;
					C_MTXLookAt(lookAtMtx, (Vec*)(piVar10 + 4), (Vec*)&up, (Vec*)&eye);
					PSMTXCopy(CameraPcs.m_cameraMatrix, cameraBackup);
					PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
					CharaPcs.InitEnv(5);
					GXSetColorUpdate(0);
					GXSetAlphaUpdate(0);
					GXSetCopyClear(CColor(0, 0, 0, 0).color, 0xFFFFFF);
					GXSetColorUpdate(1);
					GXSetAlphaUpdate(1);

					GXSetViewport(
						(float)*reinterpret_cast<short*>(piVar10 + 2),
						(float)*reinterpret_cast<short*>((int)(piVar10 + 2) + 2),
						(float)*reinterpret_cast<short*>(piVar10 + 3),
						(float)*reinterpret_cast<short*>((int)(piVar10 + 3) + 2),
						FLOAT_803313dc, FLOAT_803313e8);
					GXSetScissor(piVar10[0x10], piVar10[0x11], piVar10[0x12], piVar10[0x13]);
					viewportSetup = 1;
				}
				Graphic.SetFog(1, 0);
				LightPcs.SetAmbient(gWmMenuLightTables[0].m_ambient);
				LightPcs.SetNumDiffuse(gWmMenuLightTables[0].m_diffuseCount);
				for (int j = 0; j < gWmMenuLightTables[0].m_diffuseCount; j++) {
					LightPcs.SetDiffuse(
						j, gWmMenuLightTables[0].m_diffuseColors[j],
						&gWmMenuLightTables[0].m_diffuseDirs[j], 0);
				}
				LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
				m_wm.m_handles[slot]->Draw(5);
				if (slot != 6) {
					int* effData = reinterpret_cast<int*>(*reinterpret_cast<int*>(bytes + 0x840) + effOff);
					int a = effData[0];
					int b = effData[2];
					if (a >= 0 && b >= 0) {
						PartPcs.DrawMenu(a);
					}
				}
			}
			viewOff += 0x50;
			effOff += 0x524;
		}
	}

	if (viewportSetup != 0) {
		PSMTXCopy(cameraBackup, CameraPcs.m_cameraMatrix);
		GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0xFFFFFF);
		Mtx44 screenCopy;
		PSMTX44Copy(CameraPcs.m_screenMatrix, screenCopy);
		GXSetProjection(screenCopy, GX_PERSPECTIVE);
		Graphic.SetViewport();
		GXSetScissor(0, 0, 0x280, 0x1C0);
		DrawInit();
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChkPlaceLength(char* text)
{
	if (text == 0) {
		gWmMenuWorkA = 0;
		return;
	}

	int len = static_cast<int>(strlen(text));
	while (len > 0) {
		const char c = text[len - 1];
		if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
			break;
		}
		len--;
	}
	gWmMenuWorkA = len;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SplitPlace(const char* text, char* left, char* right)
{
	if (left != 0) {
		left[0] = '\0';
	}
	if (right != 0) {
		right[0] = '\0';
	}
	if (text == 0 || left == 0 || right == 0) {
		return;
	}
	const char* const sep = strchr(text, ',');
	if (sep == 0) {
		strcpy(left, text);
		return;
	}
	const int len = static_cast<int>(sep - text);
	strncpy(left, text, len);
	left[len] = '\0';
	const char* rhs = sep + 1;
	while (*rhs == ' ' || *rhs == '\t') {
		rhs++;
	}
	strcpy(right, rhs);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SplitPlace2(const char* text, char* left, char* right, CFont*, int)
{
	SplitPlace(text, left, right);
	if (left != 0) {
		for (char* p = left; *p != '\0'; p++) {
			if (*p == '\t') {
				*p = ' ';
			}
		}
	}
	if (right != 0) {
		for (char* p = right; *p != '\0'; p++) {
			if (*p == '\t') {
				*p = ' ';
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f3f60
 * PAL Size: 3012b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcWMFrame()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
#define worldState m_wmWorldState
	short sVar3 = worldState->m_mainState;
	if (sVar3 == 0) {
		return;
	}
	if (sVar3 > 2) {
		return;
	}

	int wmFrame;
	if (sVar3 == 2 && bytes[0x13] != 0) {
		wmFrame = reinterpret_cast<int>(m_wm.m_frameData);
		*reinterpret_cast<int*>(wmFrame + 4) = *reinterpret_cast<int*>(wmFrame + 4) - 1;
		wmFrame = reinterpret_cast<int>(m_wm.m_frameData);
		if (*reinterpret_cast<int*>(wmFrame + 4) < 0) {
			*reinterpret_cast<int*>(wmFrame + 4) = 0;
		}
	} else {
		if ((bytes[0x0A] & 1) != 0) {
			wmFrame = reinterpret_cast<int>(m_wm.m_frameData);
			int iVar16 = *reinterpret_cast<int*>(wmFrame + 4);
			if (iVar16 != 0) {
				*reinterpret_cast<int*>(wmFrame + 4) = iVar16 - 1;
				wmFrame = reinterpret_cast<int>(m_wm.m_frameData);
				if (*reinterpret_cast<int*>(wmFrame + 4) < 0) {
					*reinterpret_cast<int*>(wmFrame + 4) = 0;
				}
				wmFrame = reinterpret_cast<int>(m_wm.m_frameData);
				if (*reinterpret_cast<int*>(wmFrame + 4) == 0) {
					int flagTmp = bytes[0x0A];
					bytes[0x0A] = flagTmp & ~1;
				}
				goto LAB_calc;
			}
		}
		wmFrame = reinterpret_cast<int>(m_wm.m_frameData);
		int iVar16 = *reinterpret_cast<int*>(wmFrame + 4);
		if (iVar16 < 10) {
			*reinterpret_cast<int*>(wmFrame + 4) = iVar16 + 1;
		}
	}
LAB_calc:
	*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0x98) = 0x68;
	float fVar1 = FLOAT_803313dc;
	*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0x9A) = 0x14;
	*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0x9C) = 200;
	*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0x9E) = 0x28;
	*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xA0) = fVar1;

	if ((bytes[0x0A] & 1) != 0) {
		int frameA = reinterpret_cast<int>(m_wm.m_frameData);
		int yOff = (int)*reinterpret_cast<short*>(frameA + 0x9E) * (int)(char)bytes[0x05];
		*reinterpret_cast<float*>(frameA + 0xA4) = (float)yOff;
	} else {
		int frameA = reinterpret_cast<int>(m_wm.m_frameData);
		int yOff = (int)*reinterpret_cast<short*>(frameA + 0x9E) * (int)(char)bytes[0x04];
		*reinterpret_cast<float*>(frameA + 0xA4) = (float)yOff;
	}

	wmFrame = reinterpret_cast<int>(m_wm.m_frameData);
	*reinterpret_cast<short*>(wmFrame + 0x98) =
	    (10 - *reinterpret_cast<int*>(wmFrame + 4)) * 2 + 0x68;

	if (((bytes[0x0A] & 2) != 0 ||
	     (m_wmWorldState->m_mainState == 2 && bytes[0x13] != 0))
	    && *reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_frameData) + 8) >= 10) {
		*reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_frameData) + 8) = 0;
		bytes[0x0A] = bytes[0x0A] & ~2;
	}

	unsigned int uVar13;
	if ((bytes[0x0A] & 2) != 0) {
		uVar13 = *reinterpret_cast<int*>(reinterpret_cast<char*>(&Game.m_gameWork) + 8) + (int)(char)bytes[0x0B];
	} else {
		uVar13 = *reinterpret_cast<int*>(reinterpret_cast<char*>(&Game.m_gameWork) + 8) + (int)(char)bytes[0x0C];
	}
	gWmMenuScriptValueCache = (unsigned char)uVar13;
	if ((int)uVar13 > 99) {
		gWmMenuScriptValueCache = 100;
	}

	int uVar14 = ((int)uVar13 > 9) + 1;
	if ((int)uVar13 > 99) {
		uVar14 = 3;
	}

	float fE8 = FLOAT_803313e8;
	*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 200) = fE8;
	*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xE4) = fE8;

	if (uVar14 == 3) {
		int iVar16 = DAT_801dc118[10];
		const float fV1 = FLOAT_80331524;
		const float fV4 = FLOAT_80331528;
		*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xB4) = (0x2B - iVar16) / 2 + 0x2C;
		*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xB6) = 0x43;
		*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xB8) = (short)iVar16;
		*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xBA) = 0x20;
		*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xBC) = fV1;
		*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xC0) = fV4;
	} else {
		int digits[2];
		digits[0] = (int)uVar13 % 10;
		if (1 < uVar14) {
			digits[1] = (int)uVar13 / 10;
		}
		int iVar16 = DAT_801dc118[(int)uVar13 % 10];
		if (1 < uVar14) {
			iVar16 = iVar16 + DAT_801dc118[(int)uVar13 / 10];
		}
		int iVar19 = uVar14 - 1;
		int iVar15 = (0x2B - iVar16) / 2 + 0x2C;
		int off = iVar19 * 0x1C;
		int* piVar17 = digits + iVar19;
		const double dV10 = DOUBLE_80331490;
		const double dV12 = DOUBLE_80331540;
		const double dV11 = DOUBLE_80331538;
		int wmDigitIdx;
		for (wmDigitIdx = iVar19; wmDigitIdx >= 0; wmDigitIdx--) {
				int digit = *piVar17;
				*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + off + 0xB4) = (short)iVar15;
				int digitW = DAT_801dc118[digit];
				piVar17--;
				*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + off + 0xB6) = 0x43;
				*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + off + 0xB8) = (short)digitW;
				*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + off + 0xBA) = 0x20;
				int col = digit % 5;
				int row = digit / 5;
				*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + off + 0xBC) = (float)(dV10 * (double)(float)col);
				*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + off + 0xC0) = (float)(dV12 * (double)(float)row + dV11);
				iVar15 = iVar15 + digitW;
				off = off - 0x1C;
		}
	}

	if ((bytes[0x0A] & 2) != 0 ||
	    (worldState->m_mainState == 2 && bytes[0x13] != 0)) {
		int i = 0;
		int off = i;
		int cnt = uVar14;
		const double dE8 = DOUBLE_803316e8;
		const double dF8 = DOUBLE_803313f8;
		for (; cnt > 0; cnt--, off += 0x1C, i++) {
			if (i != 0 && uVar14 != 2) {
				break;
			}
			float fVar1 = static_cast<float>(
			    static_cast<double>(static_cast<float>(10 - *reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_frameData) + 8))) / dE8);
			*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + off + 0xC4) = fVar1;
			*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + off + 200) =
			    static_cast<float>(dF8 * static_cast<double>(fVar1) + dF8);

			int entry = reinterpret_cast<int>(m_wm.m_frameData) + off;
			float prodBA = static_cast<float>(*reinterpret_cast<short*>(entry + 0xBA)) *
			               *reinterpret_cast<float*>(entry + 200);
			*reinterpret_cast<short*>(entry + 0xB6) =
			    static_cast<short>(*reinterpret_cast<short*>(entry + 0xB6) +
			                       static_cast<int>(
			                           static_cast<float>(*reinterpret_cast<short*>(entry + 0xBA)) -
			                           prodBA));

			if (i == 0 && (uVar14 == 1 || uVar14 == 3)) {
				entry = reinterpret_cast<int>(m_wm.m_frameData) + off;
				float prodB8a = static_cast<float>(*reinterpret_cast<short*>(entry + 0xB8)) *
				               *reinterpret_cast<float*>(entry + 200);
				*reinterpret_cast<short*>(entry + 0xB4) =
				    static_cast<short>(*reinterpret_cast<short*>(entry + 0xB4) +
				                       static_cast<int>(
				                           (DOUBLE_80331420 +
				                            static_cast<double>(
				                                static_cast<float>(*reinterpret_cast<short*>(entry + 0xB8)) -
				                                prodB8a)) *
				                           DOUBLE_803313f8));
			} else if (i != 0) {
				entry = reinterpret_cast<int>(m_wm.m_frameData) + off;
				float prodB8b = static_cast<float>(*reinterpret_cast<short*>(entry + 0xB8)) *
				               *reinterpret_cast<float*>(entry + 200);
				*reinterpret_cast<short*>(entry + 0xB4) =
				    static_cast<short>(*reinterpret_cast<short*>(entry + 0xB4) +
				                       static_cast<int>(
				                           static_cast<float>(*reinterpret_cast<short*>(entry + 0xB8)) -
				                           prodB8b));
			}
		}
		int wmEnd = reinterpret_cast<int>(m_wm.m_frameData);
		*reinterpret_cast<int*>(wmEnd + 8) = *reinterpret_cast<int*>(wmEnd + 8) + 1;
	} else {
		int base = reinterpret_cast<int>(m_wm.m_frameData);
		unsigned int uVar = (unsigned int)*reinterpret_cast<int*>(base + 8);
		if (static_cast<float>(static_cast<int>(uVar - 5)) <
		    static_cast<float>(DOUBLE_803314a8 * static_cast<double>(s_YearTrns.data[s_YearTrns.count * 4 - 4]))) {
			float t = (float)(int)(uVar) / FLOAT_803314c0;
			float fVar5;
			WM_MENU_EVAL_SPLINE(fVar5, s_YearTrns.data, s_YearTrns.count, t);
			*reinterpret_cast<short*>(base + 0xD2) =
			    static_cast<short>(static_cast<int>(static_cast<float>(*reinterpret_cast<short*>(base + 0xD2)) + fVar5));

			float fVar1;
			WM_MENU_EVAL_SPLINE(fVar1, DAT_8032e8cc, DAT_8032e8c8, t);
			*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xE0) = fVar1;

			if (uVar14 == 2) {
				uVar -= 5;
			}
			t = (float)(int)(uVar) / FLOAT_803314c0;
			WM_MENU_EVAL_SPLINE(fVar5, s_YearTrns.data, s_YearTrns.count, t);
			*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xB6) =
			    static_cast<short>(static_cast<int>(
			        static_cast<float>(*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xB6)) + fVar5));

			WM_MENU_EVAL_SPLINE(fVar1, DAT_8032e8cc, DAT_8032e8c8, t);
			*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xC4) = fVar1;
			*reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_frameData) + 8) =
			    *reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_frameData) + 8) + 1;
		}
	}
#undef worldState
}

/*
 * --INFO--
 * PAL Address: 0x800f36ac
 * PAL Size: 2228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawWMFrame()
{
	extern double DOUBLE_803316D8;
	extern double DOUBLE_803316E0;
	extern double DOUBLE_803314F0;
	extern double DOUBLE_803316E8;
	extern float FLOAT_803315B0;
	extern float FLOAT_803315B4;
	extern float FLOAT_803314D8;

	GXColor matColor;
	short sVar = m_wmWorldState->m_mainState;
	float alpha;
	if (sVar == 0) {
		const double dMin = DOUBLE_803314F0;
		m_wmWorldState->m_posX -= FLOAT_80331550;
		if (static_cast<double>(m_wmWorldState->m_posX) <= dMin) {
			m_wmWorldState->m_posX = FLOAT_803313dc;
		}
		alpha = static_cast<float>(DOUBLE_803316D8 * static_cast<double>(m_wmWorldState->m_frameCounter));
	} else if (sVar == 3) {
		const double dMax = DOUBLE_803316E0;
		m_wmWorldState->m_posX += FLOAT_80331550;
		if (static_cast<double>(m_wmWorldState->m_posX) >= dMax) {
			m_wmWorldState->m_posX = FLOAT_80331440;
		}
		alpha = static_cast<float>(-(DOUBLE_803316D8 * static_cast<double>(m_wmWorldState->m_frameCounter) -
		                             DOUBLE_80331508));
	} else {
		alpha = FLOAT_80331458;
	}

	Mtx rotMtx;
	PSMTXRotRad(rotMtx, 'z', m_wmWorldState->m_posX * FLOAT_803314bc);
	rotMtx[0][3] = FLOAT_803315B0;
	rotMtx[1][3] = FLOAT_803315B4;
	rotMtx[2][3] = FLOAT_803313dc;

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor frameColor;
	matColor.r = 0xFF;
	matColor.g = 0xFF;
	matColor.b = 0xFF;
	matColor.a = static_cast<unsigned char>(static_cast<int>(alpha));
	GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x16));

	const float baseX = FLOAT_803315B0;
	const float baseY = FLOAT_803315B4;
	for (int i = 0; i < 5; i++) {
		short* const entry = reinterpret_cast<short*>(m_wm.m_frameData + (i * 0x1C + 0xC));
		MenuPcs.DrawRect2(
			0,
			static_cast<float>(entry[0]) - baseX,
			static_cast<float>(entry[1]) - baseY,
			(float)entry[2],
			(float)entry[3],
			*reinterpret_cast<float*>(entry + 4),
			*reinterpret_cast<float*>(entry + 6),
			FLOAT_803313e8,
			FLOAT_803313e8,
			rotMtx);
	}

	short sVar2 = m_wmWorldState->m_mainState;
	if (sVar2 != 0 && sVar2 <= 3) {
		MenuPcs.SetTexture((TEX)0x17);
		unsigned char gaugeAlpha = static_cast<unsigned char>(static_cast<int>(
		    DOUBLE_80331508 *
		    (static_cast<float>(*reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_frameData) + 4)) /
		     DOUBLE_803316E8)));
		matColor.r = 0xFF;
		matColor.g = 0xFF;
		matColor.b = 0xFF;
		matColor.a = gaugeAlpha;
		GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
		const float kZeroG = FLOAT_803313dc;
		MenuPcs.DrawRect(0,
			(float)*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0x98),
			(float)*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0x9A),
			(float)*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0x9C),
			(float)*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0x9E),
			*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xA0),
			*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xA4),
			FLOAT_803313e8,
			FLOAT_803313e8,
			kZeroG);

		if (m_wmWorldState->m_mainState <= 2) {
			const int language = Game.m_gameWork.m_languageId;
			MenuPcs.SetAttrFmt((FMT)0);
				matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = 0xFF;
			GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
			MenuPcs.SetTexture((TEX)0x21);
			const float kZeroYear = FLOAT_803313dc;
			float yearY = language != 5 ? FLOAT_803316F4 : FLOAT_803316F8;
			MenuPcs.DrawRect(0,
				FLOAT_803316F0, yearY,
				FLOAT_80331440, FLOAT_80331558,
				FLOAT_803313dc, FLOAT_803313dc,
				FLOAT_803313e8, FLOAT_803313e8,
				kZeroYear);

			MenuPcs.SetAttrFmt((FMT)0);
			MenuPcs.SetTexture((TEX)0x17);

			unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
			int dispValue =
			    bytes[0xA] & 2
			        ? *reinterpret_cast<int*>(&Game.m_gameWork.m_scriptSysVal0) + static_cast<signed char>(bytes[0xB])
			        : *reinterpret_cast<int*>(&Game.m_gameWork.m_scriptSysVal0) + static_cast<signed char>(bytes[0xC]);
			int digitCnt;
			digitCnt = (dispValue > 9) + 1;
			if (dispValue > 99) {
				digitCnt = 3;
			}
			const int languageYOffset = language != 5 ? 0 : 0xE;

			if (digitCnt == 3) {
				int alphaInt =
				    static_cast<int>(DOUBLE_80331508 * static_cast<double>(*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xC4)));
				matColor.r = 0xFF;
				matColor.g = 0xFF;
				matColor.b = 0xFF;
				matColor.a = alphaInt;
				GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
				const float kZero3 = FLOAT_803313dc;
				MenuPcs.DrawRect(0,
					(float)*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xB4),
					(float)(*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xB6) + languageYOffset),
					(float)*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xB8),
					(float)*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xBA),
					*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xBC),
					*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xC0),
					*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xC8),
					*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + 0xC8),
					kZero3);
			} else {
				const double k255 = DOUBLE_80331508;
				const float kZero = FLOAT_803313dc;
				for (int i = 0, off2 = 0; i < digitCnt; i++, off2 += 0x1C) {
					int alphaInt =
					    static_cast<int>(k255 * static_cast<double>(*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameData) + off2 + 0xC4)));
						matColor.r = 0xFF;
					matColor.g = 0xFF;
					matColor.b = 0xFF;
					matColor.a = alphaInt;
					GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
					int off = reinterpret_cast<int>(m_wm.m_frameData) + off2;
					MenuPcs.DrawRect(0,
						(float)*reinterpret_cast<short*>(off + 0xB4),
						(float)(*reinterpret_cast<short*>(off + 0xB6) + languageYOffset),
						(float)*reinterpret_cast<short*>(off + 0xB8),
						(float)*reinterpret_cast<short*>(off + 0xBA),
						*reinterpret_cast<float*>(off + 0xBC),
						*reinterpret_cast<float*>(off + 0xC0),
						*reinterpret_cast<float*>(off + 0xC8),
						*reinterpret_cast<float*>(off + 0xC8),
						kZero);
				}
			}

			if (digitCnt != 3 && language != 5) {
				int off = reinterpret_cast<int>(m_wm.m_frameData);
				float suffixU = FLOAT_803313dc;
				float suffixX = static_cast<float>(*reinterpret_cast<short*>(off + 0xB8)) * *reinterpret_cast<float*>(off + 0xC8) +
				                static_cast<float>(*reinterpret_cast<short*>(off + 0xB4));
				float suffixY = static_cast<float>(*reinterpret_cast<short*>(off + 0xB6));
				float suffixScale = *reinterpret_cast<float*>(off + 0xC8);
				if (language == 1) {
					if (gWmMenuScriptValueCache / 10 == 1) {
						suffixU = FLOAT_8033151c;
					} else {
						int digit = gWmMenuScriptValueCache % 10;
						if (digit >= 1 && digit <= 3) {
							suffixU = FLOAT_803314D8 * static_cast<float>(digit - 1);
						} else {
							suffixU = FLOAT_8033151c;
						}
					}
				} else if (language == 4) {
					if (gWmMenuScriptValueCache != 1) {
						suffixU = FLOAT_803314D8;
					}
				} else if (language == 2) {
					suffixY += FLOAT_80331550;
				}
				int alphaInt =
				    static_cast<int>(DOUBLE_80331508 * static_cast<double>(*reinterpret_cast<float*>(off + 0xC4)));
				MenuPcs.SetAttrFmt((FMT)0);
				matColor.r = 0xFF;
				matColor.g = 0xFF;
				matColor.b = 0xFF;
				matColor.a = alphaInt;
				GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
				MenuPcs.SetTexture((TEX)0x34);
				MenuPcs.DrawRect(0,
				         suffixX,
				         suffixY,
				         FLOAT_80331410, FLOAT_803314D8,
				         FLOAT_803313dc, suffixU,
				         suffixScale, suffixScale,
				         FLOAT_803313dc);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f3500
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcWMFrame0(int param)
{
	reinterpret_cast<short*>(m_wm.m_frameInfo + 4)[0] = 0x10;
	reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20)[0] = static_cast<short>(static_cast<int>(FLOAT_803313e0 - static_cast<float>(static_cast<int>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 8)) + static_cast<int>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 4)))));

	if (param < 0) {
		float offset = static_cast<float>(static_cast<int>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 8)) + static_cast<int>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 4)));
		if (param >= -10) {
			int sign = param >> 31;
			int absParam = (sign ^ param) - sign;
			float t_unclamped = static_cast<float>(absParam);
			float dVar4 = offset * (DOUBLE_803314E8 * t_unclamped);
			if (absParam < 0) {
				absParam = 0;
			}
			if (absParam > 10) {
				absParam = 10;
			}
			float t_clamped = static_cast<float>(absParam);
			offset = dVar4 * static_cast<float>(sin(static_cast<double>(FLOAT_803314bc * t_clamped * FLOAT_803316d4)));
		}
		reinterpret_cast<short*>(m_wm.m_frameInfo + 4)[0] = static_cast<short>(static_cast<int>(static_cast<float>(static_cast<int>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 4))) - offset));
		reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20)[0] = static_cast<short>(static_cast<int>(static_cast<float>(static_cast<int>(*reinterpret_cast<short*>(m_wm.m_frameInfo + 0x20))) + offset));
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f3384
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawWMFrame0(int mask, float alpha)
{
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(DOUBLE_80331508 * static_cast<double>(alpha)));
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));

	int offset;
	int i;
	i = 0;
	offset = 0;
	do {
		if ((static_cast<unsigned int>(mask) & (1 << i)) != 0) {
			short* psVar1 = reinterpret_cast<short*>(m_wm.m_frameInfo + offset + 4);
			MenuPcs.DrawRect(*reinterpret_cast<unsigned int*>(psVar1 + 0xC), static_cast<float>(static_cast<int>(psVar1[0])), static_cast<float>(static_cast<int>(psVar1[1])),
			         static_cast<float>(static_cast<int>(psVar1[2])), static_cast<float>(static_cast<int>(psVar1[3])),
			         *reinterpret_cast<float*>(psVar1 + 4), *reinterpret_cast<float*>(psVar1 + 6),
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
		i = i + 1;
		offset = offset + 0x1C;
	} while (i < 2);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 388b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMainMenuBase(float baseAlpha)
{
	WmWorldState* const worldState = m_wmWorldState;
	unsigned char* const frame = m_wm.m_frameInfo;
	float alpha = baseAlpha;

	if (alpha <= 0.0f) {
		alpha = 1.0f;
	}

	if (worldState != 0) {
		const short state = worldState->m_mainState;
		const short step = worldState->m_frameCounter;
		if (state == 0) {
			alpha *= static_cast<float>(step) * 0.1f;
		} else if (state >= 3) {
			alpha *= 1.0f - static_cast<float>(step) * 0.1f;
		}
	}
	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)};
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));

	if (frame != 0) {
		for (int i = 0; i < 2; i++) {
			unsigned char* const entry = frame + 4 + i * 0x1C;
			MenuPcs.DrawRect(0xFFFFFFFF, static_cast<float>(*reinterpret_cast<short*>(entry + 0)),
			         static_cast<float>(*reinterpret_cast<short*>(entry + 2)), static_cast<float>(*reinterpret_cast<short*>(entry + 4)),
			         static_cast<float>(*reinterpret_cast<short*>(entry + 6)), *reinterpret_cast<float*>(entry + 8),
			         *reinterpret_cast<float*>(entry + 0x0C), 1.0f, 1.0f, static_cast<float>(*reinterpret_cast<unsigned int*>(entry + 0x18)));
		}
	}

	if (alpha > 0.0f) {
		DrawMainMenuSub();
		DrawPageMark();
		DrawHelpBase(0, alpha);
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcCharaBase()
{
	WmWorldState* const worldState = m_wmWorldState;
	unsigned char* const worldObj = m_wm.m_worldObjData;
	if (worldState == 0 || worldObj == 0) {
		return;
	}

	const short state = worldState->m_mainState;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 4; col++) {
			unsigned char* const slot = worldObj + 0x1E0 + (row * 4 + col) * 0x50;
			*reinterpret_cast<unsigned int*>(slot + 0x00) = (state > 0 && state < 4) ? 1u : 0u;
			*reinterpret_cast<short*>(slot + 0x08) = static_cast<short>(0x1C + col * 0x90);
			*reinterpret_cast<short*>(slot + 0x0A) = static_cast<short>((row == 0 ? 0x22 : 0xCA) + (row != 0 ? 8 : 0));
			*reinterpret_cast<unsigned short*>(slot + 0x0C) = 0x140;
			*reinterpret_cast<unsigned short*>(slot + 0x0E) = 0xE0;
			*reinterpret_cast<float*>(slot + 0x10) = FLOAT_803313dc;
			*reinterpret_cast<float*>(slot + 0x14) = FLOAT_803313dc;
			*reinterpret_cast<float*>(slot + 0x18) = FLOAT_80331598;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f31b8
 * PAL Size: 460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCharaBase()
{
	WmWorldState* const worldState = m_wmWorldState;

	const short state = worldState->m_mainState;
	if (state == 0) {
		return;
	}

	float alpha;
	if (state == 1) {
		alpha = static_cast<float>(DOUBLE_803316C0 * static_cast<double>(worldState->m_frameCounter));
	} else if (state == 2) {
		alpha = FLOAT_80331668;
	} else {
		alpha = static_cast<float>(DOUBLE_80331448 - DOUBLE_803316C0 * static_cast<double>(worldState->m_frameCounter));
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(DOUBLE_80331508 * static_cast<double>(alpha)));
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x29));

	const float kZero = FLOAT_803313dc;
	int yBase = 0x22;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 4; col++) {
			const float x = static_cast<float>(0x1C + col * 0x90);
			int yInt = yBase;
			if (row != 0) {
				yInt = yBase + 8;
			}
			const float y = static_cast<float>(yInt);
			MenuPcs.DrawRect(0, x, y, FLOAT_803316C8, FLOAT_803316CC, kZero, kZero, FLOAT_803313e8, FLOAT_803313e8, kZero);
		}
		yBase += 0xB8;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f2b00
 * PAL Size: 1720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcChara()
{
	int* charaWork = reinterpret_cast<int*>(m_wm.m_worldObjData + 0xA00);
	unsigned int selectedMask = 0;

	if (m_wm.m_charaSelectData[0x0D] == 1) {
		selectedMask = 1u << static_cast<unsigned int>(*reinterpret_cast<short*>(m_wm.m_charaSelectData + 0x04));
	}
	if (m_wm.m_charaSelectData[0x1D] == 1) {
		selectedMask |= 1u << static_cast<unsigned int>(*reinterpret_cast<short*>(m_wm.m_charaSelectData + 0x14));
	}
	if (m_wm.m_charaSelectData[0x2D] == 1) {
		selectedMask |= 1u << static_cast<unsigned int>(*reinterpret_cast<short*>(m_wm.m_charaSelectData + 0x24));
	}
	if (m_wm.m_charaSelectData[0x3D] == 1) {
		selectedMask |= 1u << static_cast<unsigned int>(*reinterpret_cast<short*>(m_wm.m_charaSelectData + 0x34));
	}

	for (int slot = 0; slot < 8; slot++) {
		unsigned int effectMask = 0;
		int effectCount = 0;

		for (int player = 0; player < 4; player++) {
			unsigned char* const entry = m_wm.m_charaSelectData + player * 0x10;
			const int currentSlot = *reinterpret_cast<short*>(entry + 0x04);
			if ((entry[0x0D] == 1) && (currentSlot >= 0) && (slot == currentSlot)) {
				effectCount++;
				effectMask |= 1u << player;
			}
		}

		if (effectCount != 0) {
			float offset;
			if (effectCount == 1) {
				offset = FLOAT_803313dc;
			} else if (effectCount == 2) {
				offset = FLOAT_80331588;
			} else if (effectCount == 3) {
				offset = FLOAT_8033169C;
			} else {
				offset = FLOAT_803316A0;
			}

			for (int player = 0; player < 4; player++) {
				if ((effectMask & (1u << player)) != 0) {
					Vec loc;
					const int partNo = m_effectWork[player + 32].m_partNo;
					loc.x = s_RingOrgPos.x;
					loc.y = s_RingOrgPos.y;
					loc.z = s_RingOrgPos.z;
					loc.y = static_cast<float>((double)s_RingOrgPos.y + (DOUBLE_80331420 + (double)offset));
					PartPcs.SetParLocIdx(partNo, loc);
					offset = offset - FLOAT_8033169C;
				}
			}
		}
	}

	int modelIndex = 0;
	for (int i = 0; i < kWmMenuPlayerCount; i++, charaWork += 0x14, modelIndex += 0x34) {
		CCharaPcs::CHandle* const handle = GetWmCharaHandles(this)[i];
		if (!handle->IsModelLoaded(1)) {
			charaWork[0] = 0;
			continue;
		}

		unsigned char* const modelData = m_wm.m_charaModelData + modelIndex;
		if (modelData[0x0C] == 1) {
			reinterpret_cast<float*>(charaWork)[0x0B] = FLOAT_80331664;
			if ((*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->m_charaKind != 3) {
				const unsigned int charaBase = static_cast<unsigned int>((*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->m_charaNo) / 100;
				const int modelNo = charaBase * 100;
				int anim = (charaBase - 1) * 6;
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->LoadAnim(s_wmCharaAnimStand, anim++, 1, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->LoadAnim(s_wmCharaAnimWalk, anim++, 1, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->LoadAnim(s_wmCharaAnimRun, anim++, 1, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->LoadAnim(s_wmCharaAnimGlad, anim++, 3, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->LoadAnim(s_wmCharaAnimSleep, anim++, 1, 0, modelNo, -1, 0);
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->LoadAnim(s_wmCharaAnimAngry, anim, 1, 0, modelNo, -1, 0);
				GetWmCharaAnimState(this)[i * 5 + 0] = 0;
				GetWmCharaAnimState(this)[i * 5 + 1] = -1;
				GetWmCharaAnimState(this)[i * 5 + 2] = rand() % 250;
				(*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->SetAnim(anim - 5, -1, -1,
				    static_cast<int>(static_cast<unsigned int>((*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->m_currentAnimIndex) >> 31) - 1, 1);
				reinterpret_cast<float*>(GetWmCharaAnimState(this))[i * 5 + 3] =
				    reinterpret_cast<float*>(reinterpret_cast<unsigned char*>((*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->m_model) + 0xB4)[0];
				reinterpret_cast<float*>(GetWmCharaAnimState(this))[i * 5 + 4] =
				    reinterpret_cast<float*>(reinterpret_cast<unsigned char*>((*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(this) + (i + 0x20) * 4 + 0x774))->m_model) + 0xC0)[0];
			}
			modelData[0x0C] = 0;
		}

		charaWork[0] = 1;
		CCharaPcs::CHandle* const charaHandle = GetWmCharaHandles(this)[i];
		if (charaHandle->m_charaKind == 3) {
			if ((selectedMask & (1u << i)) != 0) {
				const float zero = FLOAT_803313dc;
				float normalX = FLOAT_803316A4;
				reinterpret_cast<float*>(charaWork)[7] = zero;
				const float scale = FLOAT_803316A8;
				reinterpret_cast<float*>(charaWork)[8] = normalX;
				normalX = FLOAT_803316AC;
				reinterpret_cast<float*>(charaWork)[9] = zero;
				reinterpret_cast<float*>(charaWork)[0x0D] = scale;
				reinterpret_cast<float*>(charaWork)[0x0E] = scale;
				reinterpret_cast<float*>(charaWork)[0x0F] = scale;
				reinterpret_cast<float*>(charaWork)[10] = normalX;
				reinterpret_cast<float*>(charaWork)[0x0B] = zero;
			} else {
				const float zero = FLOAT_803313dc;
				const float scale = FLOAT_803313e8;
				reinterpret_cast<float*>(charaWork)[7] = zero;
				reinterpret_cast<float*>(charaWork)[8] = zero;
				reinterpret_cast<float*>(charaWork)[9] = zero;
				reinterpret_cast<float*>(charaWork)[0x0D] = scale;
				reinterpret_cast<float*>(charaWork)[0x0E] = scale;
				reinterpret_cast<float*>(charaWork)[0x0F] = scale;
				reinterpret_cast<float*>(charaWork)[10] = zero;
				reinterpret_cast<float*>(charaWork)[0x0B] = zero;
			}
		} else if ((selectedMask & (1u << i)) != 0) {
			const float zero = FLOAT_803313dc;
			float normalX = FLOAT_803316B0;
			reinterpret_cast<float*>(charaWork)[7] = zero;
			const float scale = FLOAT_803316B4;
			reinterpret_cast<float*>(charaWork)[8] = normalX;
			normalX = FLOAT_803316B8;
			reinterpret_cast<float*>(charaWork)[9] = zero;
			reinterpret_cast<float*>(charaWork)[0x0D] = scale;
			reinterpret_cast<float*>(charaWork)[0x0E] = scale;
			reinterpret_cast<float*>(charaWork)[0x0F] = scale;
			reinterpret_cast<float*>(charaWork)[10] = normalX;
		} else {
			const float zero = FLOAT_803313dc;
			float normalX = FLOAT_803316BC;
			reinterpret_cast<float*>(charaWork)[7] = zero;
			const float scale = FLOAT_80331434;
			reinterpret_cast<float*>(charaWork)[8] = normalX;
			normalX = FLOAT_803315d0;
			reinterpret_cast<float*>(charaWork)[9] = zero;
			reinterpret_cast<float*>(charaWork)[0x0D] = scale;
			reinterpret_cast<float*>(charaWork)[0x0E] = scale;
			reinterpret_cast<float*>(charaWork)[0x0F] = scale;
			reinterpret_cast<float*>(charaWork)[10] = normalX;
		}

		WmWorldState* const ws = m_wmWorldState;
		union {
			double d;
			struct {
				unsigned int hi;
				unsigned int lo;
			} u;
		} frameConv;
		frameConv.u.hi = 0x43300000;
		frameConv.u.lo = static_cast<unsigned int>(static_cast<int>(ws->m_frameCounter)) ^ 0x80000000;
		float alpha = static_cast<float>(DOUBLE_803314e8 * (frameConv.d - DOUBLE_80331408));
		if (alpha > DOUBLE_80331420) {
			alpha = FLOAT_803313e8;
		}

		const int state = ws->m_mainState;
		if (state == 1) {
			GetWmCharaHandles(this)[i]->m_model->m_lightAlpha = alpha;
		} else if (state == 2) {
			GetWmCharaHandles(this)[i]->m_model->m_lightAlpha = FLOAT_803313e8;
		} else {
			GetWmCharaHandles(this)[i]->m_model->m_lightAlpha = static_cast<float>(DOUBLE_80331420 - alpha);
		}

		Mtx scaleMtx;
		Mtx rotXMtx;
		Mtx rotYMtx;
		PSMTXScale(scaleMtx, reinterpret_cast<float*>(charaWork)[0x0D], reinterpret_cast<float*>(charaWork)[0x0E],
		           reinterpret_cast<float*>(charaWork)[0x0F]);
		PSMTXRotRad(rotXMtx, 'x', reinterpret_cast<float*>(charaWork)[10]);
		PSMTXRotRad(rotYMtx, 'y', reinterpret_cast<float*>(charaWork)[0x0B]);
		PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
		rotXMtx[0][3] = reinterpret_cast<float*>(charaWork)[7];
		rotXMtx[1][3] = reinterpret_cast<float*>(charaWork)[8];
		rotXMtx[2][3] = reinterpret_cast<float*>(charaWork)[9];
		PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);
		GetWmCharaHandles(this)[i]->m_model->SetMatrix(scaleMtx);
		GetWmCharaHandles(this)[i]->m_model->CalcMatrix();
		GetWmCharaHandles(this)[i]->m_model->CalcSkin();
	}

	PCAnimCtrl();
}

/*
 * --INFO--
 * PAL Address: 0x800f26f4
 * PAL Size: 1036b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::PCAnimCtrl()
{
	unsigned char* const charaSelect = m_wm.m_charaSelectData;
	unsigned int selectedMask = 0;

	if (charaSelect[0x0D] != 0 && charaSelect[0x0A] != 0) {
		selectedMask |= 1 << reinterpret_cast<short*>(charaSelect + 4)[0];
	}
	if (charaSelect[0x1D] != 0 && charaSelect[0x1A] != 0) {
		selectedMask |= 1 << reinterpret_cast<short*>(charaSelect + 0x14)[0];
	}
	if (charaSelect[0x2D] != 0 && charaSelect[0x2A] != 0) {
		selectedMask |= 1 << reinterpret_cast<short*>(charaSelect + 0x24)[0];
	}
	if (charaSelect[0x3D] != 0 && charaSelect[0x3A] != 0) {
		selectedMask |= 1 << reinterpret_cast<short*>(charaSelect + 0x34)[0];
	}

	int* animState = m_wmCharaAnimState;
	for (int i = 0; i < kWmMenuPlayerCount; i++, animState += 5) {
		CCharaPcs::CHandle* const handle = GetWmCharaHandles(this)[i];
		const int blendMode = (static_cast<unsigned int>(handle->m_currentAnimIndex) >> 31) - 1;

		unsigned char* const model = reinterpret_cast<unsigned char*>(handle->m_model);
		if (model == 0 || reinterpret_cast<unsigned int*>(model + 0xB0)[0] == 0 || handle->m_charaKind == 3) {
			continue;
		}

		reinterpret_cast<float*>(animState)[3] = reinterpret_cast<float*>(model + 0xB4)[0];

		if (animState[1] >= 0) {
			animState[0] = animState[1];
			animState[1] = -1;
			handle->SetAnim((static_cast<int>(static_cast<unsigned int>(GetWmCharaHandles(this)[i]->m_charaNo) / 100) - 1) * 6 + animState[0], -1, -1, blendMode, 0);
			reinterpret_cast<float*>(animState)[3] = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0xB4)[0];
			reinterpret_cast<float*>(animState)[4] = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0xC0)[0];
			animState[2] = 0;
			continue;
		}

		const int isSelected = selectedMask & (1u << static_cast<unsigned int>(i));
		const float frame = reinterpret_cast<float*>(animState)[3];
		const float frameEnd = reinterpret_cast<float*>(animState)[4];
		if (isSelected == 0 &&
		    m_wmWorldState->m_menuMode != 8 &&
		    animState[0] == 0 && animState[2] >= 3000) {
			animState[0] = 4;
			handle->SetAnim((static_cast<int>(static_cast<unsigned int>(GetWmCharaHandles(this)[i]->m_charaNo) / 100) - 1) * 6 + animState[0], -1, -1, blendMode, 0);
			reinterpret_cast<float*>(animState)[3] = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0xB4)[0];
			reinterpret_cast<float*>(animState)[4] = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0xC0)[0];
			animState[2] = 0;
		} else if (isSelected != 0 &&
		           m_wmWorldState->m_menuMode != 8) {
			if (animState[0] == 1 && animState[2] >= 12000) {
				animState[0] = 0;
				animState[2] = 0;
			} else if (animState[0] == 2 && animState[2] >= 9000) {
				animState[0] = 1;
			} else if (animState[0] == 1 && animState[2] >= 6000 && animState[2] < 9000) {
				animState[0] = 2;
			} else if (animState[0] == 0 && animState[2] >= 3000) {
				animState[0] = 1;
			} else {
				goto frameStep;
			}

			handle->SetAnim((static_cast<int>(static_cast<unsigned int>(GetWmCharaHandles(this)[i]->m_charaNo) / 100) - 1) * 6 + animState[0], -1, -1, blendMode, 0);
			reinterpret_cast<float*>(animState)[3] = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0xB4)[0];
			reinterpret_cast<float*>(animState)[4] = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0xC0)[0];
		} else {
		frameStep:
			if (frame < frameEnd) {
				handle->m_model->AddFrame(FLOAT_80331698);
			} else {
				if (animState[0] == 3 || animState[0] == 4 || animState[0] == 5) {
					animState[0] = 0;
					handle->SetAnim((static_cast<int>(static_cast<unsigned int>(GetWmCharaHandles(this)[i]->m_charaNo) / 100) - 1) * 6 + animState[0], -1, -1, blendMode, 0);
					reinterpret_cast<float*>(animState)[3] = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0xB4)[0];
					reinterpret_cast<float*>(animState)[4] = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0xC0)[0];
					if (isSelected != 0) {
						animState[2] = 0x834;
					} else {
						animState[2] = 0;
					}
				}
				handle->m_model->SetFrame(FLOAT_803313dc);
			}
			animState[2]++;
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetAnimNo(int animNo, int)
{
	if (animNo < 0) {
		animNo = 0;
	}
	gWmMenuWorkA = animNo;
}

/*
 * --INFO--
 * PAL Address: 0x800f2034
 * PAL Size: 1728b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawChara()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldObj = m_wm.m_worldObjData;
	WmWorldState* const worldState = GetWmWorldState(this);

	for (int i = 0; i < kWmMenuPlayerCount; i++) {
		unsigned char* const view = worldObj + 0xA00 + i * 0x50;
		if (*reinterpret_cast<int*>(view) == 0) {
			continue;
		}

		int selectedMask = 0;
		for (int chan = 0; chan < 4; chan++) {
			WmCharaSelectEntry& entry = GetWmCharaSelectEntries(this)[chan];
			const int slot = entry.m_currentSlot;
			if (entry.m_connected == 1 && slot >= 0 && i == slot) {
				selectedMask |= 1 << chan;
			}
		}

		CCharaPcs::CHandle* const handle = GetWmCharaHandles(this)[i];
		if (handle->m_charaKind != 3 && handle->m_currentAnimIndex < 0) {
			continue;
		}

		{
			Mtx44 projectionMtx;
			C_MTXPerspective(projectionMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
			GXSetProjection(projectionMtx, GX_PERSPECTIVE);
			PSMTX44Copy(projectionMtx, CameraPcs.m_screenMatrix);
			Mtx lookAtMtx;
			C_MTXLookAt(lookAtMtx, reinterpret_cast<Point3d*>(view + 0x10),
			            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc)),
			            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc)));
			PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(bytes + 0x744));
			PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
			CharaPcs.InitEnv(5);
			GXSetColorUpdate(0);
			GXSetAlphaUpdate(0);
			GXSetCopyClear(CColor(0, 0, 0, 0).color, 0x00FFFFFF);
			GXSetColorUpdate(1);
			GXSetAlphaUpdate(1);
			GXSetViewport(static_cast<float>(*reinterpret_cast<short*>(view + 8)),
			              static_cast<float>(*reinterpret_cast<short*>(view + 0xA)),
			              static_cast<float>(*reinterpret_cast<short*>(view + 0xC)),
			              static_cast<float>(*reinterpret_cast<short*>(view + 0xE)),
			              FLOAT_803313dc, FLOAT_803313e8);
			GXSetScissor(*reinterpret_cast<unsigned int*>(view + 0x40),
			             *reinterpret_cast<unsigned int*>(view + 0x44),
			             *reinterpret_cast<unsigned int*>(view + 0x48),
			             *reinterpret_cast<unsigned int*>(view + 0x4C));
			Graphic.SetFog(1, 0);
			WmMenuLightTable& lightTable = gWmMenuLightTables[0];
			LightPcs.SetAmbient(lightTable.m_ambient);
			LightPcs.SetNumDiffuse(lightTable.m_diffuseCount);
			for (int lightIndex = 0; lightIndex < lightTable.m_diffuseCount; lightIndex++) {
				LightPcs.SetDiffuse(lightIndex, lightTable.m_diffuseColors[lightIndex],
				                    &lightTable.m_diffuseDirs[lightIndex], 0);
			}
			LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
		}
		if (GetWmCharaHandles(this)[i]->m_charaKind != 3) {
			GetWmCharaHandles(this)[i]->Draw(5);
		} else {
			DrawInit();
			GXSetZMode(GX_TRUE, static_cast<GXCompare>(7), GX_TRUE);
			{
				Mtx44 projectionMtx;
				C_MTXPerspective(projectionMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
				GXSetProjection(projectionMtx, GX_PERSPECTIVE);
				PSMTX44Copy(projectionMtx, CameraPcs.m_screenMatrix);
				Mtx lookAtMtx;
				C_MTXLookAt(lookAtMtx, reinterpret_cast<Point3d*>(view + 0x10),
				            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc)),
				            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc)));
				PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(bytes + 0x744));
				PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
				CharaPcs.InitEnv(5);
				GXSetColorUpdate(0);
				GXSetAlphaUpdate(0);
				GXSetCopyClear(CColor(0, 0, 0, 0).color, 0x00FFFFFF);
				GXSetColorUpdate(1);
				GXSetAlphaUpdate(1);
				GXSetViewport(static_cast<float>(*reinterpret_cast<short*>(view + 8)),
				              static_cast<float>(*reinterpret_cast<short*>(view + 0xA)),
				              static_cast<float>(*reinterpret_cast<short*>(view + 0xC)),
				              static_cast<float>(*reinterpret_cast<short*>(view + 0xE)),
				              FLOAT_803313dc, FLOAT_803313e8);
				GXSetScissor(*reinterpret_cast<unsigned int*>(view + 0x40),
				             *reinterpret_cast<unsigned int*>(view + 0x44),
				             *reinterpret_cast<unsigned int*>(view + 0x48),
				             *reinterpret_cast<unsigned int*>(view + 0x4C));
			}
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x32));
			MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			float alpha;
			if (worldState->m_mainState == 2) {
				alpha = FLOAT_803313e8;
			} else {
				alpha = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0x9C);
			}
			const float rgbMul = FLOAT_80331458;
			const float colorScale = static_cast<float>(selectedMask != 0 ? DOUBLE_80331420 : DOUBLE_80331448);
			const unsigned char rgb = static_cast<unsigned char>(static_cast<int>(rgbMul * colorScale));
			GXColor color = {
			    rgb,
			    rgb,
			    rgb,
			    static_cast<unsigned char>(static_cast<int>(DOUBLE_80331508 * static_cast<double>(alpha)))};
			GXSetChanMatColor(static_cast<GXChannelID>(4), color);
			float x = FLOAT_8033161C - FLOAT_8033168C;
			float y = FLOAT_803314cc;
			float scale = FLOAT_80331690;
			if (selectedMask != 0) {
				x *= FLOAT_803315d4;
				y *= FLOAT_803315d4;
				scale *= FLOAT_803315d4;
			}
			MenuPcs.DrawRect3d(0, x, y, FLOAT_80331694, FLOAT_80331578, FLOAT_80331520,
			                   FLOAT_803313dc, FLOAT_803313dc, scale, scale);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
		}
		if (worldState->m_mainState == 2 && selectedMask != 0) {
			for (int chan = 3; chan >= 0; chan--) {
				if ((selectedMask & (1 << chan)) != 0) {
					PartPcs.DrawMenuIdx(m_effectWork[chan + 32].m_partNo);
				}
			}
		}
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x800f2018
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetModelNo(int modelNo, int offset, int baseType)
{
	int result = modelNo * 200 + 100;
	if (baseType != 0) {
		result += 100;
	}
	return result + offset;
}

/*
 * --INFO--
 * PAL Address: 0x800f0a70
 * PAL Size: 5544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
void CMenuPcs::CalcCharaSelect()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	unsigned short padRepeat[4];
	unsigned short padTrig[4];
	int requestCancel = 0;
	int requestFinalize = 0;

	*reinterpret_cast<short*>(bytes + 0x74) = static_cast<short>(*reinterpret_cast<short*>(bytes + 0x74) + 1);
	const unsigned int clz = __cntlzw(static_cast<unsigned int>(Game.m_gameWork.m_menuStageMode));
	if (static_cast<int>(*reinterpret_cast<short*>(bytes + 0x74)) >= static_cast<int>(((clz >> 5) + 2) * 0x4B)) {
		*reinterpret_cast<short*>(bytes + 0x74) = 0;
	}

	for (int i = 0; i < 4; i++) {
		WmCharaSelectEntry& entry = GetWmCharaSelectEntries(this)[i];

		if ((i != 0) && (Game.m_gameWork.m_menuStageMode != 0)) {
			padRepeat[i] = 0;
			padTrig[i] = 0;
			entry.m_connected = 0;
			continue;
		}

		entry.m_padType = Joybus.GetPadType(i);
		if ((entry.m_padType == 0x09000000) || (entry.m_padType == -0x74F00000) ||
		    (entry.m_padType == -0x78000000)) {
			if (Game.m_gameWork.m_menuStageMode == 0) {
				entry.m_connected = 0;
			} else {
				entry.m_connected = 1;
			}
		} else {
			entry.m_connected = static_cast<unsigned char>(Joybus.GetGBAConnect(i));
		}

		if (entry.m_connected == 1 && entry.m_cmakePending == 0) {
			const bool lockedRepeat = Pad.m_debugPadLock != 0 || (i == 0 && Pad.m_debugPadPort != -1);
			padRepeat[i] = lockedRepeat
			                   ? 0
			                   : Pad.GetPadInputs()[(Pad.m_debugPadPort == i) ? 0 : static_cast<unsigned int>(i)].repeatButton;
			const bool lockedTrig = Pad.m_debugPadLock != 0 || (i == 0 && Pad.m_debugPadPort != -1);
			padTrig[i] = lockedTrig
			                 ? 0
			                 : Pad.GetPadInputs()[(Pad.m_debugPadPort == i) ? 0 : static_cast<unsigned int>(i)].buttonDown[0];
		} else {
			padRepeat[i] = 0;
			padTrig[i] = 0;
		}
	}

	if (GetWmWorldState(this)->m_mainState != 2 || GetWmWorldState(this)->m_nextMenuMode != 0) {
		return;
	}

	const short winState = m_menuWindowInfo->state;
	if (winState != 3) {
		unsigned short anyTrig = 0;
		for (int i = anyTrig; i < 4; i++) {
			anyTrig |= padTrig[i];
		}
		if (winState == 1 && (anyTrig & 0x0300) != 0) {
			m_menuWindowInfo->state = 2;
			for (int i = 0; i < 4; i++) {
				WmCharaSelectEntry& entry = GetWmCharaSelectEntries(this)[i];
				if (entry.m_confirmed != 0) {
					GetWmCharaAnimState(this)[entry.m_currentSlot * 5 + 1] = 0;
				}
				entry.m_confirmed = 0;
				entry.m_cmakePending = 0;
				entry.m_cmakeReady = 0;
			}
			Sound.PlaySe(2, 0x40, 0x7F, 0);
		}
		return;
	}
	{
		unsigned int pendingMask = 0;
		for (int i = 0; i < 4; i++) {
			if (Game.m_gameWork.m_menuStageMode != 0) {
				break;
			}
			if (GetWmCharaSelectEntries(this)[i].m_cmakePending != 0) {
				pendingMask |= 1u << static_cast<unsigned int>(GetWmCharaSelectEntries(this)[i].m_currentSlot);
			}
		}

		for (int i = 0; i < 4; i++) {
			if (Game.m_gameWork.m_menuStageMode != 0) {
				break;
			}
			WmCharaSelectEntry& entry = GetWmCharaSelectEntries(this)[i];

			if (entry.m_connected == 0) {
				GbaQue.ClrCmakeInfo(i);
				if (entry.m_cmakeReady == 1) {
					entry.m_cmakeReady = 0;
				} else if ((pendingMask & (1u << static_cast<unsigned int>(entry.m_currentSlot))) != 0) {
					continue;
				}

				const int slot = entry.m_currentSlot;
				const int hOff = (slot + 0x20) * 4 + 0x774;
				if (Game.m_caravanWorkArr[slot].m_shopState == 0 &&
				    (*reinterpret_cast<CCharaPcs::CHandle**>(bytes + hOff))->IsModelLoaded(1) &&
				    (*reinterpret_cast<CCharaPcs::CHandle**>(bytes + hOff))->m_charaKind != 3 &&
				    entry.m_cmakeReady != 1) {
					if (static_cast<unsigned int>(System.m_execParam) >= 3) {
						System.Printf(const_cast<char*>(s_chan_pctd_cur_pctd_801DC3D8), i,
						              static_cast<int>(entry.m_currentSlot));
					}
					const int loadSlot =  (s32)(static_cast<int>(entry.m_currentSlot));
					GetWmCharaModelData(this)[loadSlot * 0x34 + 0x0C] = 0;
					GetWmCharaHandles(this)[loadSlot]->LoadModelASync(3, 0x43, 0);
				}
			} else if (entry.m_cmakePending == 0 && Joybus.GetMType(i) == 1) {
				Joybus.SetMType(i, 4);
			}
		}

		unsigned int confirmedSlotMask = 0;
		for (int i = 0; i < 4; i++) {
			if (GetWmCharaSelectEntries(this)[i].m_confirmed != 0) {
				confirmedSlotMask |= 1u << static_cast<unsigned int>(GetWmCharaSelectEntries(this)[i].m_currentSlot);
			}
		}

		for (int slot = 0; slot < 8; slot++) {
			if (((confirmedSlotMask & (1u << static_cast<unsigned int>(slot))) == 0) &&
			    ((pendingMask & (1u << static_cast<unsigned int>(slot))) == 0) &&
			    Game.m_caravanWorkArr[slot].m_shopState == 0 &&
			    GetWmCharaHandles(this)[slot]->IsModelLoaded(1) &&
			    GetWmCharaHandles(this)[slot]->m_charaKind != 3) {
				GetWmCharaModelData(this)[slot * 0x34 + 0x0C] = 0;
				GetWmCharaHandles(this)[slot]->LoadModelASync(3, 0x43, 0);
			}
		}

		int connectedCount = 0;
		int locallyConfirmedCount = 0;
		int readyMask = 0;
		for (int i = readyMask; i < 4; i++) {
			WmCharaSelectEntry& entry = GetWmCharaSelectEntries(this)[i];
			if (entry.m_connected != 0) {
				CCaravanWork& work = Game.m_caravanWorkArr[entry.m_currentSlot];
				readyMask |= 1 << i;
				connectedCount++;
				if (entry.m_confirmed != 0 && work.m_caravanLocalFlags != 0) {
					locallyConfirmedCount++;
				}
			}
		}

		if (connectedCount != 0 && connectedCount == locallyConfirmedCount) {
			CFont* const font = GetWmFont(this);
			font->SetMargin(FLOAT_803313e8);
			font->SetShadow(0);
			font->SetScale(FLOAT_803313e8);
			const char* const* msgBuf = GetMcWinMessBuff(1);
			int maxWidth = 0;
			int* winMess = reinterpret_cast<int*>(GetWinMess(0x17));
			int* msgIter = winMess;
			for (int i = 0; i < *winMess; i++) {
				const char* text = msgBuf[*reinterpret_cast<short*>(reinterpret_cast<int>(msgIter) + 4)];
				if (text != 0) {
					if (*text == '$') {
						text++;
					}
					const int width = static_cast<int>(static_cast<double>(font->GetWidth(text)));
					if (width > maxWidth) {
						maxWidth = width;
					}
				}
				msgIter = reinterpret_cast<int*>(reinterpret_cast<int>(msgIter) + 2);
			}

			int widthCells = maxWidth / 0x16;
			if ((maxWidth % 0x16) != 0) {
				widthCells++;
			}
			const double dF8 = DOUBLE_803313F8;
			const float f430 = FLOAT_80331430;
			const short winWidth = (widthCells + 2) * 0x16 + 0x40;
			const short winHeight = *winMess * 0x1E + 0x40;
			m_menuWindowInfo->x = static_cast<short>(static_cast<int>(static_cast<float>(
			    static_cast<float>(0x280 - winWidth) * dF8)));
			m_menuWindowInfo->y = static_cast<short>(static_cast<int>(static_cast<float>(
			    (f430 - static_cast<float>(winHeight)) * dF8)));
			m_menuWindowInfo->width = winWidth;
			m_menuWindowInfo->height = winHeight;
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
			m_menuWindowInfo->state = 0;
			return;
		}

		unsigned short* pRep = padRepeat + 3;
		unsigned short* pTrig = padTrig + 3;
		int i = 3;
		int entOff = 0x30;
		for (; i >= 0; i--, pRep--, pTrig--, entOff -= 0x10) {
			WmCharaSelectEntry& entry = (*reinterpret_cast<WmCharaSelectEntry*>(reinterpret_cast<char*>(GetWmCharaSelectEntries(this)) + entOff));
			if (entry.m_cmakeReady == 1) {
				GbaCMakeInfoRaw info;
				entry.m_confirmed = 1;
				entry.m_cmakePending = 0;
				entry.m_cmakeReady = 0;
				GbaQue.GetCMakeInfo(i, reinterpret_cast<GbaCMakeInfo*>(&info));

				const int caravanSlot = static_cast<int>(info.m_channelSlot);
				const int gender = (info.m_charaType >> 7) != 0;
				int modelNo = static_cast<int>(info.m_charaType & 3) * 200 + 100;
				if (gender) {
					modelNo += 100;
				}
				modelNo += (info.m_charaType >> 2) & 3;

				*reinterpret_cast<int*>(GetWmCharaModelData(this) + caravanSlot * 0x34 + 8) = modelNo;

				CCaravanWork& caravanWork = Game.m_caravanWorkArr[caravanSlot];
				caravanWork.LoadInit();
				caravanWork.m_shopState = 1;
				caravanWork.unk_0x3a8 =
				    (static_cast<unsigned int>(info.m_birthMonth) << 8) | static_cast<unsigned int>(info.m_birthDay);
				caravanWork.unk_0x3ac = static_cast<int>(info.m_jobType);
				memset(caravanWork.m_name, 0, 0x11);
				strcpy(reinterpret_cast<char*>(caravanWork.m_name), info.m_name);
				caravanWork.m_tribeId = static_cast<unsigned short>(info.m_charaType & 3);
				caravanWork.m_appearanceVariant = static_cast<unsigned short>((info.m_charaType >> 2) & 3);
				caravanWork.m_genderFlag = static_cast<unsigned short>((info.m_charaType >> 7) != 0);
				{
					int modelNo2 = static_cast<int>(info.m_charaType & 3) * 200 + 100;
					if ((info.m_charaType >> 7) != 0) {
						modelNo2 += 100;
					}
					caravanWork.m_id = static_cast<unsigned short>(modelNo2 + ((info.m_charaType >> 2) & 3));
				}
				for (int favorite = 0; favorite < 8; favorite++) {
					unsigned char nibble = info.m_favoriteBits[favorite >> 1];
					int v;
					if ((favorite & 1) != 0) {
						v = (nibble >> 4) & 0x0F;
					} else {
						v = nibble & 0x0F;
					}
					caravanWork.m_letterMeta[favorite] = static_cast<unsigned short>((10 - v) * 10 - 5);
				}

				const int baseDataIndex =
				    static_cast<int>(caravanWork.m_genderFlag) + static_cast<int>(caravanWork.m_tribeId) * 2;
				int __p20 = baseDataIndex;
				caravanWork.Init(__p20,
				                 reinterpret_cast<CRomWork*>(Game.unkCFlatData0[0] + baseDataIndex * 0x1D0),
				                 static_cast<int>(caravanWork.m_appearanceVariant));
				caravanWork.LoadFinished();

				CFlatRuntime::CStack stackArgs[3];
				stackArgs[0].m_word = 0;
				stackArgs[1].m_word = caravanSlot;
				stackArgs[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 4, 3, stackArgs, 0);
				Sound.PlaySe(0x33, 0x40, 0x7F, 0);
				GetWmCharaAnimState(this)[entry.m_currentSlot * 5 + 1] = 3;
			}

			if (entry.m_connected == 0) {
				if (entry.m_confirmed != 0) {
					GetWmCharaAnimState(this)[entry.m_currentSlot * 5 + 1] = 0;
				}
				entry.m_confirmed = 0;
				entry.m_cmakePending = 0;
				entry.m_cmakeReady = 0;
				if (entry.m_disconnectTime < 0x3C) {
					entry.m_disconnectTime++;
				}
				(*pRep) = 0;
				(*pTrig) = 0;
				continue;
			}

			entry.m_disconnectTime = 0;
			int currentSlot = static_cast<int>(entry.m_currentSlot);
			if (((*pRep) & 0x000C) != 0) {
				if (entry.m_confirmed != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (currentSlot < 4) {
						currentSlot += 4;
					} else {
						currentSlot -= 4;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			if (((*pRep) & 0x0001) != 0) {
				if (entry.m_confirmed != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (currentSlot > ((currentSlot >> 2) != 0 ? 4 : 0)) {
						currentSlot -= 1;
					} else {
						currentSlot += 3;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			} else if (((*pRep) & 0x0002) != 0) {
				if (entry.m_confirmed != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					const int maxSlot = (currentSlot >> 2) != 0 ? 7 : 3;
					if (currentSlot < maxSlot) {
						currentSlot += 1;
					} else {
						currentSlot -= 3;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			entry.m_currentSlot = static_cast<short>(currentSlot);

			if (((*pRep) & 0x006F) == 0) {
				const unsigned short trig = (*pTrig);
				CCaravanWork& work = Game.m_caravanWorkArr[entry.m_currentSlot];
				if ((trig & 0x0100) != 0 && work.m_shopBusyFlag != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else if ((trig & 0x0100) != 0 && entry.m_confirmed == 0) {
					const int charaId = *reinterpret_cast<int*>(GetWmCharaModelData(this) + currentSlot * 0x34 + 8);
					if (charaId < 0) {
						if (Game.m_gameWork.m_menuStageMode == 0 &&
						    (entry.m_padType == 0x09000000 || entry.m_padType == -0x74F00000)) {
							Sound.PlaySe(4, 0x40, 0x7F, 0);
						} else {
							int other;
							for (other = 0; other < 4; other++) {
								if (i != other && GetWmCharaSelectEntries(this)[other].m_cmakePending != 0 &&
								    GetWmCharaSelectEntries(this)[other].m_currentSlot == currentSlot) {
									Sound.PlaySe(4, 0x40, 0x7F, 0);
									break;
								}
							}
							if (other >= 4) {
								if (Game.m_gameWork.m_menuStageMode != 0) {
									m_singleCmakeSlot = entry.m_currentSlot;
								} else {
									GbaQue.InitCmakeInfo(i, entry.m_currentSlot);
									entry.m_cmakePending = 1;
								}
								Sound.PlaySe(2, 0x40, 0x7F, 0);
							}
						}
					} else {
						int other;
						for (other = 0; other < 4; other++) {
							if (i != other && GetWmCharaSelectEntries(this)[other].m_confirmed != 0 &&
							    GetWmCharaSelectEntries(this)[other].m_currentSlot == currentSlot) {
								Sound.PlaySe(4, 0x40, 0x7F, 0);
								break;
							}
						}
						if (other >= 4) {
							if (work.m_caravanLocalFlags != 0) {
								if (Game.m_gameWork.m_menuStageMode != 0) {
									Sound.PlaySe(4, 0x40, 0x7F, 0);
								} else if (connectedCount == locallyConfirmedCount + 1) {
									Sound.PlaySe(4, 0x40, 0x7F, 0);
								} else {
									entry.m_confirmed = 1;
									locallyConfirmedCount++;
									Sound.PlaySe(0x33, 0x40, 0x7F, 0);
									GetWmCharaAnimState(this)[currentSlot * 5 + 1] = 3;
								}
							} else {
								entry.m_confirmed = 1;
								Sound.PlaySe(0x33, 0x40, 0x7F, 0);
								GetWmCharaAnimState(this)[currentSlot * 5 + 1] = 3;
							}
						}
					}
				} else if ((trig & 0x0100) != 0 && entry.m_confirmed != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else if ((trig & 0x0200) != 0) {
					if (entry.m_confirmed != 0) {
						entry.m_confirmed = 0;
						GetWmCharaAnimState(this)[currentSlot * 5 + 1] = 0;
						Sound.PlaySe(0x34, 0x40, 0x7F, 0);
					} else {
						requestCancel = 1;
					}
				} else if ((trig & 0x1000) != 0) {
					requestFinalize = 1;
				}
			}
		}

		if (requestCancel) {
			int anySelected = 0;
			for (int i = 0; i < 4; i++) {
				if ((GetWmCharaSelectEntries(this)[i].m_confirmed != 0) || (GetWmCharaSelectEntries(this)[i].m_cmakePending != 0)) {
					anySelected = 1;
					break;
				}
			}
			if (anySelected == 0) {
				GetWmWorldState(this)->m_nextMenuMode = -1;
				GetWmWorldState(this)->m_delay = 10;
				Sound.PlaySe(3, 0x40, 0x7F, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		}

		if (requestFinalize) {
			int activeCount = 0;
			for (int i = 0; i < 4; i++) {
				if (GetWmCharaSelectEntries(this)[i].m_confirmed != 0) {
					activeCount++;
				}
			}
			for (int i = 0; i < 4; i++) {
				if (GetWmCharaSelectEntries(this)[i].m_cmakePending != 0) {
					activeCount = 0;
					break;
				}
			}
			if (locallyConfirmedCount >= activeCount) {
				activeCount = 0;
			}
			if (activeCount != 0) {
				Sound.PlaySe(2, 0x40, 0x7F, 0);
				GetWmWorldState(this)->m_nextMenuMode = 1;
				GetWmWorldState(this)->m_delay = 10;
			} else {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		}

		int finishedMask = 0;
		for (int i = 0; i < 4; i++) {
			if (GetWmCharaSelectEntries(this)[i].m_confirmed != 0) {
				finishedMask |= 1 << i;
			}
		}
		if (Game.m_gameWork.m_menuStageMode != 0 && m_singleCmakeSlot >= 0) {
			GetWmWorldState(this)->m_nextMenuMode = 1;
			GetWmWorldState(this)->m_delay = 10;
		} else {
			for (int i = 0; i < 4; i++) {
				if (GetWmCharaSelectEntries(this)[i].m_connected == 0 && GetWmCharaSelectEntries(this)[i].m_disconnectTime < 0x1E) {
					readyMask |= 1 << i;
				}
			}
			if (finishedMask != 0 && finishedMask == readyMask) {
				GetWmWorldState(this)->m_nextMenuMode = 1;
				GetWmWorldState(this)->m_delay = static_cast<short>(FLOAT_8032ee18);
			}
		}

		if (GetWmWorldState(this)->m_nextMenuMode != 0) {
			GbaQue.SetControllerMode(1);
			{
				WmCharaSelectEntry& e0 = GetWmCharaSelectEntries(this)[0];
				if (e0.m_cmakePending != 0) {
					e0.m_confirmed = 0;
					e0.m_cmakePending = 0;
					e0.m_cmakeReady = 0;
				}
			}
			{
				WmCharaSelectEntry& e1 = GetWmCharaSelectEntries(this)[1];
				if (e1.m_cmakePending != 0) {
					e1.m_confirmed = 0;
					e1.m_cmakePending = 0;
					e1.m_cmakeReady = 0;
				}
			}
			{
				WmCharaSelectEntry& e2 = GetWmCharaSelectEntries(this)[2];
				if (e2.m_cmakePending != 0) {
					e2.m_confirmed = 0;
					e2.m_cmakePending = 0;
					e2.m_cmakeReady = 0;
				}
			}
			{
				WmCharaSelectEntry& e3 = GetWmCharaSelectEntries(this)[3];
				if (e3.m_cmakePending != 0) {
					e3.m_confirmed = 0;
					e3.m_cmakePending = 0;
					e3.m_cmakeReady = 0;
				}
			}
		}
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x800f0274
 * PAL Size: 2044b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_loop_invariants off
#pragma opt_strength_reduction off
void CMenuPcs::DrawCharaName()
{
	extern double DOUBLE_803314E8;
	extern double DOUBLE_803313F8;
	CFont* const font = GetWmFont(this);
	WmCharaSelectEntry* const selectEntries = GetWmCharaSelectEntries(this);
	unsigned char nameBuf[0x20];

	const char** emptyText;
	switch (Game.m_gameWork.m_languageId) {
	case 2:
		emptyText = s_wmEmptyCreatingTextDe_8032E8F8;
		break;
	case 3:
		emptyText = s_wmEmptyCreatingTextIt_8032E900;
		break;
	case 4:
		emptyText = s_wmEmptyCreatingTextFr_8032E908;
		break;
	case 5:
		emptyText = s_wmEmptyCreatingTextEs_8032E910;
		break;
	case 1:
	default:
		emptyText = s_wmEmptyCreatingTextEn_8032E8F0;
		break;
	}

	float fade;
	if (m_wmWorldState->m_mainState == 1) {
		fade = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
	} else if (m_wmWorldState->m_mainState == 2) {
		fade = FLOAT_803313e8;
	} else {
		fade = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) - DOUBLE_80331420));
	}
	unsigned int activeMask =  (int)(long)(0);
	unsigned int confirmedMask = 0;
	unsigned int pendingMask = 0;
	const WmCharaSelectEntry* entry = selectEntries;
	for (int i = 0; i < 4; i++) {
		if (entry->m_connected != 0) {
			const unsigned int bit = 1u << entry->m_currentSlot;
			activeMask |= bit;
			if (entry->m_confirmed != 0) {
				confirmedMask |= bit;
			}
			if (entry->m_cmakePending != 0 || entry->m_cmakeReady != 0) {
				pendingMask |= bit;
			}
		}
		entry++;
	}

	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_8033158C);
	font->DrawInit();
	DrawInit();

	const float alphaF = FLOAT_80331458 * fade;
	GXColor shade;
	shade.r = 0xFF;
	shade.g = 0xFF;
	shade.b = 0xFF;
	shade.a = static_cast<unsigned char>(static_cast<int>(alphaF));
	GXSetChanMatColor(GX_COLOR0A0, shade);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x28));
	const float yBase1 = FLOAT_80331478;
	const double xOffsetDefault =
	    -(DOUBLE_80331418 * static_cast<double>(FLOAT_80331680) - DOUBLE_80331678);
	const float yExtra1 = FLOAT_80331684;
	int row = 0;
	int yCounter = row;
	int slotBase = row;
	for (; row < 2; row++) {
		float y = yBase1 + static_cast<float>(yCounter);
		y += yExtra1;
		int __p2 = row;
		if (__p2 != 0) {
			y += FLOAT_80331548;
		}
		int caravanOffset = slotBase * 0xC30;
		int xCounter = 0;
		int slot = slotBase;
		for (int col = 0; col < 4; col++) {
			if ((confirmedMask & (1u << slot)) != 0) {
				const char* const text = reinterpret_cast<const char*>(
				    Game.m_caravanWorkArr[0].m_name + caravanOffset);
				float xBase = FLOAT_80331410 + static_cast<float>(xCounter);
				const float width = font->GetWidth(text);
				float scale = FLOAT_803313e8;
				if (static_cast<double>(width) * DOUBLE_803313f8 > static_cast<double>(FLOAT_80331680)) {
					const float widthPlus = static_cast<float>(static_cast<double>(width) + DOUBLE_80331510);
					scale = static_cast<float>(widthPlus * DOUBLE_803313f8 / static_cast<double>(FLOAT_80331680));
					const double xOffsetW = FLOAT_8033155C - widthPlus;
					xBase = static_cast<float>(xOffsetW * DOUBLE_803313f8 + xBase);
				} else {
					xBase = static_cast<float>(xOffsetDefault * DOUBLE_803313f8 + xBase);
				}
				MenuPcs.DrawRect(
				    0, xBase, y, FLOAT_80331680, FLOAT_80331410,
				                                FLOAT_803313dc, FLOAT_803313dc, scale, FLOAT_803313e8, FLOAT_803313dc);
				MenuPcs.DrawRect(
				    8, FLOAT_80331680 * scale + xBase, y,
				                                FLOAT_80331680, FLOAT_80331410, FLOAT_803313dc, FLOAT_803313dc,
				                                scale, FLOAT_803313e8, FLOAT_803313dc);
			}
			caravanOffset += 0xC30;
			xCounter += 0x90;
			slot++;
		}
		yCounter += 0xB8;
		slotBase += 4;
	}

	DrawInit();
	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(1);
	font->SetScale(FLOAT_8033158C);
	font->DrawInit();
	font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<long>(alphaF)).color);

	CSystem* const sys = &System;
	const float xBase2 = FLOAT_80331410;
	const float xMax2 = FLOAT_8033155C;
	const float yBase2 = FLOAT_80331478;
	const float yExtra2 = FLOAT_80331688;
	const float ySub2 = FLOAT_80331550;
	const double k3f8_2 = DOUBLE_803313F8;
	int row2 = 0;
	int slotBase2;
	int yCounter2 = row2;
	slotBase2 = row2;
	for (; row2 < 2; row2++) {
		float y = yBase2 + static_cast<float>(yCounter2);
		y += yExtra2;
		if (row2 != 0) {
			y += FLOAT_80331548;
		}
		y = static_cast<float>(y - ySub2);
		int cmakeOffset = slotBase2 * 0x9C0;
		int col = 0;
		int slot = slotBase2;
		int caravanOffset = slotBase2 * 0xC30;
		int xCounter2 = col;
		for (; col < 4; col++) {
			int restoreColor;
			restoreColor = 0;
			const char* text;

			float xBase = xBase2 + static_cast<float>(xCounter2);

			const int menuMode = this->m_wmWorldState->m_menuMode;
			bool hasName;
			if (menuMode == 8 && this->m_cmakeWork != 0) {
				hasName = *reinterpret_cast<unsigned int*>(this->m_cmakeWork + cmakeOffset + 0x1A84) != 0;
			} else {
				hasName = *reinterpret_cast<unsigned int*>(
				              reinterpret_cast<unsigned char*>(&Game) + caravanOffset + 0x1794) != 0;
			}

			if (hasName) {
				if (menuMode == 8 && this->m_cmakeWorkActive == 1 && this->m_cmakeWork != 0) {
					memset(nameBuf, 0, 0x20);
					memcpy(nameBuf, this->m_cmakeWork + cmakeOffset + 0x15C0, 0x10);
					text = reinterpret_cast<const char*>(nameBuf);
				} else {
					text = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(&Game) + caravanOffset + 0x17BA);
				}
				if ((activeMask & (1u << slot)) != 0) {
					font->SetTlut(6);
				} else {
					font->SetTlut(8);
				}
			} else if ((pendingMask & (1u << slot)) != 0) {
				font->SetTlut(0x10);
				text = emptyText[1];
				const int phase = static_cast<int>(sys->m_frameCounter) % 20 - 10;
				if (this->m_wmWorldState->m_mainState == 2) {
					const int absPhase = phase < 0 ? -phase : phase;
					fade = static_cast<float>(-(DOUBLE_80331460 * static_cast<double>(absPhase) - DOUBLE_80331420));
					restoreColor = 1;
				}
				font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<int>(FLOAT_80331458 * fade)).color);
			} else {
				if ((activeMask & (1u << slot)) != 0) {
					font->SetTlut(7);
				} else {
					font->SetTlut(8);
				}
				text = emptyText[0];
			}

			const float widthDiff = xMax2 - font->GetWidth(text);
			xBase = static_cast<float>(widthDiff * k3f8_2 + xBase);
			font->SetPosX(xBase);
			font->SetPosY(y);
			font->Draw(text);
			if (restoreColor) {
				font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
			}
			caravanOffset += 0xC30;
			cmakeOffset += 0x9C0;
			xCounter2 += 0x90;
			slot++;
		}
		slotBase2 += 4;
		yCounter2 += 0xB8;
	}

	DrawInit();
}

#pragma opt_strength_reduction on
#pragma opt_loop_invariants on
/*
 * --INFO--
 * PAL Address: 0x800efc38
 * PAL Size: 1596b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCMLife()
{
#define worldState GetWmWorldState(this)
#define selectEntries GetWmCharaSelectEntries(this)

	float fade;
	if (worldState->m_mainState == 1) {
		fade = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(worldState->m_frameCounter));
	} else if (worldState->m_mainState == 2) {
		fade = FLOAT_803313e8;
	} else {
		fade = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(worldState->m_frameCounter) -
		                            DOUBLE_80331420));
	}
	unsigned int readyMask = 0;
	for (int i = 0; i < 4; i++) {
		const WmCharaSelectEntry& entry = selectEntries[i];
		if (entry.m_connected != 0 && entry.m_cmakePending == 0 && entry.m_cmakeReady == 0) {
			readyMask |= 1u << entry.m_currentSlot;
		}
	}
	const double alphaF = FLOAT_80331458 * fade;

	for (int slot = 0; slot < 8; slot++) {
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x27));

		int count;
		if (worldState->m_menuMode == 8 && m_cmakeWorkActive == 1 && m_cmakeWork != 0 &&
		    *reinterpret_cast<int*>(m_cmakeWork + slot * 0x9C0 + 0x1A84) != 0) {
			count = static_cast<int>(*reinterpret_cast<unsigned short*>(m_cmakeWork + slot * 0x9C0 + 0x14D6)) >> 1;
		} else if (Game.m_caravanWorkArr[slot].m_shopState != 0) {
			count = static_cast<int>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Game.m_caravanWorkArr[slot]) + 0x1A)) >> 1;
		} else {
			continue;
		}
		float red;
		float green;
		float blue;
		if ((readyMask & (1u << slot)) != 0) {
			red = FLOAT_803313e8;
			green = red;
			blue = red;
		} else {
			red = FLOAT_80331434;
			green = FLOAT_80331668;
			blue = green;
		}

		GXColor color;
		color.r = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * red));
		color.g = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * green));
		color.b = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * blue));
		color.a = static_cast<unsigned char>(static_cast<int>(alphaF));
		GXSetChanMatColor(GX_COLOR0A0, color);

		const int row = slot / 4;
		const int col = slot % 4;
		float y = FLOAT_80331478 + static_cast<float>(row * 0xB8);
		const float xBase = FLOAT_80331410 + static_cast<float>(col * 0x90);
		float yTmp = y;
		if (row != 0) {
			yTmp = y + FLOAT_80331548;
		}
		const float yBase = yTmp + FLOAT_8033166C;
		float x = static_cast<float>(static_cast<double>(0x90 - count * 0x10) * DOUBLE_803313F8 + static_cast<double>(xBase));
		float step = static_cast<float>(static_cast<double>(8 - count) * DOUBLE_803313F8);

		const float kSplineDiv = FLOAT_803314c0;
		const float kZero = FLOAT_803313dc;
		const float kRectSize = FLOAT_80331558;
		const double kStepDelta = DOUBLE_80331420;

		for (int i = 0; i < count; i++) {
			float yAdd = FLOAT_803313dc;
			const float t = step / kSplineDiv;
			if (t >= gWmLifeYOffsetSpline[gWmLifeYOffsetSplineCount * 4 - 4]) {
				yAdd = gWmLifeYOffsetSpline[gWmLifeYOffsetSplineCount * 4 - 3];
			} else {
				for (int j = 0; j < gWmLifeYOffsetSplineCount; j++) {
					if (t <= gWmLifeYOffsetSpline[j * 4]) {
						if (j == 0) {
							yAdd = gWmLifeYOffsetSpline[j * 4 + 1];
						} else {
							float* const cur = gWmLifeYOffsetSpline + j * 4;
							float* const prev = gWmLifeYOffsetSpline + (j - 1) * 4;
							const float width = cur[0] - prev[0];
							const float u = (t - prev[0]) / width;
							const float u2 = u * u;
							const float u3 = u2 * u;
							yAdd = width * (prev[3] * (u + (u3 - FLOAT_803314c8 * u2)) +
							                cur[2] * (u3 - u2)) +
							       (prev[1] * (FLOAT_803313e8 + (FLOAT_803314c8 * u3 - FLOAT_803314c4 * u2)) +
							        cur[1] * (FLOAT_803314cc * u3 + FLOAT_803314c4 * u2));
						}
						break;
					}
				}
			}

			MenuPcs.DrawRect(
			    0, x, yBase + yAdd, FLOAT_80331558, FLOAT_80331558,
			                                kZero, kZero, FLOAT_803313e8, FLOAT_803313e8, kZero);
			step = static_cast<float>(step + kStepDelta);
			x += kRectSize;
		}

		unsigned char flagA;
		unsigned char flagB;
		if (m_cmakeWorkActive == 1 && m_cmakeWork != 0) {
			const unsigned char* const work = m_cmakeWork + slot * 0x9C0;
			flagB = work[0x1D91];
			flagA = work[0x1D90];
		} else {
			const CCaravanWork& caravanWork = Game.m_caravanWorkArr[slot];
			flagB = caravanWork.m_caravanLocalFlags;
			flagA = caravanWork.m_shopBusyFlag;
		}
		if (flagA != 0 || flagB != 0) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x38));
			MenuPcs.DrawRect(
			    0, static_cast<float>(xBase + DOUBLE_80331670),
			                                static_cast<float>((row != 0 ? y + FLOAT_80331548 : y) + DOUBLE_803315C0), FLOAT_80331524,
			                                FLOAT_80331440, FLOAT_803313dc,
			                                flagA != 0 ? FLOAT_803313dc : FLOAT_80331440,
			                                FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
	}
#undef worldState
#undef selectEntries
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::WMSubMenuInit()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x14] = 0;
	bytes[0x15] = 0;
	bytes[0x16] = 0;
	bytes[0x17] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800eeea0
 * PAL Size: 3480b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::WMChgMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	if (m_wmWorldState->m_changeRequest == 0) {
		return;
	}

	int iVar14 = m_wmWorldState->m_menuMode;
	lbl_8032EE1C = 1;

	short sVar2 = m_wmWorldState->m_changeRequest;

	if (sVar2 == 2) {
		char cVar1 = bytes[0xD];
		if (cVar1 == 1) {
			m_wmWorldState->m_menuMode = 0;
		} else if (cVar1 == 2) {
			m_wmWorldState->m_menuMode = 5;
		} else if (cVar1 == 3) {
			lbl_8032EE1C = 1;
			if (iVar14 == 6) {
				m_wmWorldState->m_changeRequest = 0;
				return;
			}
			m_wmWorldState->m_menuMode = 6;
		} else if (cVar1 == 4) {
			m_wmWorldState->m_menuMode = 4;
		} else {
			m_wmWorldState->m_menuMode = 1;
		}
	} else if (iVar14 == 0) {
		if (sVar2 == 1) {
			short sVar2b = m_wmWorldState->m_cardChannel;
			if (sVar2b == 0) {
				m_wmWorldState->m_menuMode = 3;
			} else if (sVar2b == 1) {
				m_wmWorldState->m_menuMode = 1;
				memset(m_wmWorldParams, 0, 0x10);
			} else if (sVar2b == 2) {
				m_wmWorldState->m_menuMode = 8;
			} else if (sVar2b == 3) {
				m_wmWorldState->m_menuMode = 7;
			} else {
				m_wmWorldState->m_menuMode = 2;
			}
		} else {
			m_wmWorldState->m_menuMode = 4;
		}
	} else if (iVar14 == 1) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 1;
	} else if (iVar14 == 8) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 2;
	} else if (iVar14 == 7) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 3;
	} else if (iVar14 == 2) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 4;
	} else if (iVar14 == 5) {
		if (sVar2 == 1) {
			m_wmWorldState->m_menuMode = 0;
			bytes[0xD] = 0;
			m_wmWorldState->m_cardChannel = 0;
			CFlatRuntime::CStack stackA[3];
			stackA[0].m_word = 1;
			stackA[1].m_word = 1;
			stackA[2].m_word = 0;
			gCFlatRuntime().SystemCall(0, 1, 4, 3, stackA, 0);
		} else if (sVar2 == -1) {
			lbl_8032EE1C = 1;
			m_wmWorldState->m_menuMode = 6;
			CFlatRuntime::CStack stackB[3];
			stackB[0].m_word = 1;
			stackB[1].m_word = 0;
			stackB[2].m_word = 0;
			gCFlatRuntime().SystemCall(0, 1, 4, 3, stackB, 0);
		}
	} else if (iVar14 == 6) {
		m_wmWorldState->m_menuMode = 0;
	} else if (sVar2 == 1) {
		if (m_wmWorldState->m_menuMode >= 8) {
			bytes[0xD] = 0;
		} else {
			m_wmWorldState->m_menuMode++;
		}
	} else if (sVar2 == -1) {
		short sVar2c = m_wmWorldState->m_menuMode;
		if (sVar2c <= 0) {
			bytes[0xD] = 0;
		} else if (sVar2c == 3) {
			m_wmWorldState->m_menuMode = 0;
			m_wmWorldState->m_cardChannel = 0;
		} else {
			m_wmWorldState->m_menuMode = sVar2c - 1;
		}
	}

	if (m_wmWorldState->m_menuMode != 0) {
		m_wmWorldState->m_cardChannel = 0;
	}

	float fVar6 = FLOAT_803315b0;
	m_wmWorldState->m_frameCounter = 0;
	double dVar15 = (double)FLOAT_80331430;
	int xInt = (int)fVar6;
	m_wmWorldState->m_titleState = 0;
	float fVar4 = FLOAT_803313dc;
	float fVar5 = FLOAT_803313e8;
	double dVar16 = DOUBLE_803313f8;
	m_wmWorldState->m_worldReady = 0;
	m_wmWorldState->m_flag09 = 0;
	int yInt = (int)(float)(dVar15 * dVar16);
	m_wmWorldState->m_flag0A = 0;
	m_wmWorldState->m_state0E = 0;
	m_wmWorldState->m_mainState = 0;
	m_wmWorldState->m_state12 = 0;
	m_wmWorldState->m_subState = 0;
	m_wmWorldState->m_delay = 0;
	m_wmWorldState->m_counter1A = 0;
	m_wmWorldState->m_posY = fVar5;
	m_wmWorldState->m_posX = fVar4;
	m_wmWorldState->m_mcResult = 0;
	m_wmWorldState->m_flag0B = 0;
	m_wmWorldState->m_modelFlagsInitialized = 0;

	m_menuWindowInfo->x = (short)xInt;
	m_menuWindowInfo->y = (short)yInt;
	m_menuWindowInfo->width = 0;
	m_menuWindowInfo->height = 0;
	m_menuWindowInfo->frame = 0;
	m_menuWindowInfo->state = 3;
	m_textureLocIndex = 0;

	*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 4) = 0x10;
	*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 6) = 0x10;
	*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 8) = 0xE8;
	*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 10) = 0x168;
	*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 0xC) = fVar4;
	*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 0x10) = fVar4;
	*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 0x14) = fVar5;
	*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 0x18) = fVar5;
	*reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 0x1C) = 0;

	int frameInfo = reinterpret_cast<int>(m_wm.m_frameInfo);
	*reinterpret_cast<short*>(frameInfo + 0x20) = *reinterpret_cast<short*>(frameInfo + 4);
	*reinterpret_cast<short*>(frameInfo + 0x22) = *reinterpret_cast<short*>(frameInfo + 6);
	*reinterpret_cast<short*>(frameInfo + 0x24) = *reinterpret_cast<short*>(frameInfo + 8);
	*reinterpret_cast<short*>(frameInfo + 0x26) = *reinterpret_cast<short*>(frameInfo + 10);
	*reinterpret_cast<float*>(frameInfo + 0x28) = *reinterpret_cast<float*>(frameInfo + 0xC);
	*reinterpret_cast<float*>(frameInfo + 0x2C) = *reinterpret_cast<float*>(frameInfo + 0x10);
	*reinterpret_cast<float*>(frameInfo + 0x30) = *reinterpret_cast<float*>(frameInfo + 0x14);
	*reinterpret_cast<float*>(frameInfo + 0x34) = *reinterpret_cast<float*>(frameInfo + 0x18);
	*reinterpret_cast<int*>(frameInfo + 0x38) = *reinterpret_cast<int*>(frameInfo + 0x1C);

	*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 0x20) = 0x280 - (*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 8) + *reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 4));
	*reinterpret_cast<int*>(reinterpret_cast<int>(m_wm.m_frameInfo) + 0x38) = 8;

	if (iVar14 == 3 && Game.m_gameWork.m_menuStageMode != 0
	    && m_singleCmakeSlot >= 0
	    && m_singleCmakeSlot < 8) {
		m_singleCmakeMode = 1;
		m_wmWorldState->m_menuMode = 3;
	} else if (iVar14 == 3 && Game.m_gameWork.m_menuStageMode != 0
	           && m_singleCmakeSlot >= 8) {
		m_singleCmakeMode = 0;
		m_singleCmakeSlot = (short)0xFFFF;
		m_wmWorldState->m_menuMode = 3;
	} else {
		m_singleCmakeMode = 0;
		m_singleCmakeSlot = (short)0xFFFF;
	}

	int iVar8 = 0;
	m_wmTransitionCode = 0;

	sVar2 = m_wmWorldState->m_menuMode;
	switch (sVar2) {
	case 0: {
			unsigned char* gameBytes = reinterpret_cast<unsigned char*>(&Game);
			for (int count = 0; count < 4; count++) {
				const int paramIndex = iVar8 / 2;
				if (Game.m_caravanWorkArr[m_wmWorldState->m_originalBackupParams[paramIndex]].m_shopState == 0) {
					m_wmWorldState->m_originalBackupParams[paramIndex] = (short)0xFFFF;
				}
				if (Game.m_caravanWorkArr[m_wmWorldState->m_backupParams[paramIndex]].m_shopState == 0) {
					m_wmWorldState->m_backupParams[paramIndex] = (short)0xFFFF;
				}
				int iVar13 = *reinterpret_cast<int*>(gameBytes + 0x20);
				if (Game.m_caravanWorkArr[iVar13].m_shopState == 0) {
					*reinterpret_cast<int*>(gameBytes + 0x20) = -1;
				}
				if (Game.m_caravanWorkArr[iVar13].m_shopBusyFlag != 0) {
					*reinterpret_cast<int*>(gameBytes + 0x20) = -1;
				}
				iVar8 = iVar8 + 2;
				gameBytes += 4;
			}

			const float scrollStep = FLOAT_8033151c;
			*reinterpret_cast<float*>(bytes + 0x78) = -(scrollStep * (float)(int)m_wmWorldState->m_cardChannel);
			*reinterpret_cast<float*>(bytes + 0x7C) = -(scrollStep * (float)(int)m_wmWorldState->m_cardChannel);
			m_effectTimer = 0;
		break;
	}
	case 3: {
			int iVar11 = iVar8;
			double dVar16b = (double)FLOAT_80331664;
			int iVar12 = 0;
			int iVar13 = reinterpret_cast<int>(m_wm.m_worldObjData) + 0xA00;
			do {
				const int handleIdx = iVar12 + 0x20;
				*reinterpret_cast<unsigned char*>(m_wm.m_charaModelData + iVar8 + 0xC) = 1;
				*reinterpret_cast<float*>(iVar13 + 0x2C) = (float)dVar16b;
				int selectData = reinterpret_cast<int>(m_wm.m_charaSelectData) + iVar11;
				*reinterpret_cast<short*>(selectData + 6) = *reinterpret_cast<short*>(selectData + 4);
				if (m_wm.m_handles[handleIdx]->IsModelLoaded(1)) {
					Mtx mtx;
					PSMTXIdentity(mtx);
					m_wm.m_handles[handleIdx]->m_model->SetMatrix(mtx);
					m_wm.m_handles[handleIdx]->m_model->CalcMatrix();
					m_wm.m_handles[handleIdx]->m_model->CalcSkin();
				}
				iVar12 = iVar12 + 1;
				iVar11 = iVar11 + 0x10;
				iVar13 = iVar13 + 0x50;
				iVar8 = iVar8 + 0x34;
			} while (iVar12 < 8);

			iVar8 = 0;
			do {
				GbaQue.ClrCmakeInfo(iVar8);
				iVar8 = iVar8 + 1;
			} while (iVar8 < 4);
		break;
	}
	case 4:
		m_wmWorldState->m_posX = FLOAT_80331440;
		break;
	case 7:
		GetOptionData();
		break;
	}

	switch (iVar14) {
	case 0: {
		if (m_wmWorldState->m_menuMode == 4) {
			Game.m_gameWork.m_wmBackupParams[0] = (int)m_wmWorldState->m_backupParams[0];
			Game.m_gameWork.m_wmBackupParams[1] = (int)m_wmWorldState->m_backupParams[1];
			Game.m_gameWork.m_wmBackupParams[2] = (int)m_wmWorldState->m_backupParams[2];
			Game.m_gameWork.m_wmBackupParams[3] = (int)m_wmWorldState->m_backupParams[3];
			bytes[0x10] = 1;
			bytes[0x12] = 0;
			bytes[0x13] = 0;
		} else {
			memset(GetWmCharaSelectEntries(this), 0, kWmCharaSelectBytes);
			char bVar7 = 0;
			iVar8 = bVar7;
			int iVar11 = iVar8;
			for (int iVar12 = 0; iVar12 < 2; iVar12++) {
				*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0xC) = 0;
				*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0xB) = 0;
				*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 10) = 0;
				int sv = m_wmWorldState->m_backupParams[iVar11 / 2];
				if (sv < 0) {
					*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 4) = (short)0xFFFF;
				} else {
					*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 4) = (short)sv;
					bVar7 = bVar7 | (1 << (int)sv);
				}
				*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0x1C) = 0;
				*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0x1B) = 0;
				*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0x1A) = 0;
				sv = m_wmWorldState->m_backupParams[iVar11 / 2 + 1];
				if (sv < 0) {
					*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 0x14) = (short)0xFFFF;
				} else {
					*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 0x14) = (short)sv;
					bVar7 = bVar7 | (1 << (int)sv);
				}
				iVar8 = iVar8 + 0x20;
				iVar11 = iVar11 + 4;
			}

			iVar8 = 0;
			iVar11 = 4;
			do {
				if (*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 4) < 0) {
					int iVar12b;
					unsigned int uVar10 = (unsigned int)(char)bVar7;
					for (iVar12b = 0; iVar12b < 8; iVar12b++) {
						if ((uVar10 & (1 << iVar12b)) == 0) {
							break;
						}
					}
					*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 4) = (short)iVar12b;
					bVar7 = bVar7 | (1 << iVar12b);
				}
				int iVar12c = reinterpret_cast<int>(m_wm.m_charaSelectData) + iVar8;
				iVar8 = iVar8 + 0x10;
				*reinterpret_cast<short*>(iVar12c + 6) = *reinterpret_cast<short*>(iVar12c + 4);
				iVar11 = iVar11 - 1;
			} while (iVar11 != 0);
		}
		break;
	}
	case 1:
		memset(m_wmWorldParams, 0, 0x10);
		bytes[0x11] = 0;
		break;
	case 3: {
		if (m_wmWorldState->m_menuMode == 4) {
			int selectBase = reinterpret_cast<int>(m_wm.m_charaSelectData);
			int* bp = Game.m_gameWork.m_wmBackupParams;
			int v0 = (*reinterpret_cast<unsigned char*>(selectBase + 10) != 0)
			    ? (int)*reinterpret_cast<short*>(selectBase + 4) : -1;
			*bp++ = v0;
			m_wmWorldState->m_backupParams[0] = (short)v0;

			int v1 = (*reinterpret_cast<unsigned char*>(selectBase + 0x1A) != 0)
			    ? (int)*reinterpret_cast<short*>(selectBase + 0x14) : -1;
			*bp++ = v1;
			m_wmWorldState->m_backupParams[1] = (short)v1;

			int v2 = (*reinterpret_cast<unsigned char*>(selectBase + 0x2A) != 0)
			    ? (int)*reinterpret_cast<short*>(selectBase + 0x24) : -1;
			*bp++ = v2;
			m_wmWorldState->m_backupParams[2] = (short)v2;

			int v3 = (*reinterpret_cast<unsigned char*>(selectBase + 0x3A) != 0)
			    ? (int)*reinterpret_cast<short*>(selectBase + 0x34) : -1;
			*bp++ = v3;
			m_wmWorldState->m_backupParams[3] = (short)v3;

			bytes[0x10] = 1;
			bytes[0x12] = 0;
			bytes[0x13] = 0;
		}
		break;
	}
	case 4: {
		Sound.PlaySe(0x31, 0x40, 0x7F, 0);
		bytes[0x10] = 0;
		memset(GetWmCharaSelectEntries(this), 0, kWmCharaSelectBytes);
		char bVar7 = 0;
		iVar8 = bVar7;
		int iVar11 = iVar8;
		int iVar12 = 2;
		do {
			*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0xC) = 0;
			*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0xB) = 0;
			*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 10) = 0;
			int sv = m_wmWorldState->m_backupParams[iVar11 / 2];
			if (sv < 0) {
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 4) = (short)0xFFFF;
			} else {
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 4) = (short)sv;
				bVar7 = bVar7 | (1 << (int)sv);
			}
			*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0x1C) = 0;
			*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0x1B) = 0;
			*reinterpret_cast<unsigned char*>(m_wm.m_charaSelectData + iVar8 + 0x1A) = 0;
			sv = m_wmWorldState->m_backupParams[iVar11 / 2 + 1];
			if (sv < 0) {
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 0x14) = (short)0xFFFF;
			} else {
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 0x14) = (short)sv;
				bVar7 = bVar7 | (1 << (int)sv);
			}
			iVar8 = iVar8 + 0x20;
			iVar11 = iVar11 + 4;
			iVar12 = iVar12 - 1;
		} while (iVar12 != 0);

		iVar8 = 0;
		iVar11 = 4;
		do {
			if (*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 4) < 0) {
				int iVar12b;
				unsigned int uVar10 = (unsigned int)(char)bVar7;
				for (iVar12b = 0; iVar12b < 8; iVar12b++) {
					if ((uVar10 & (1 << iVar12b)) == 0) {
						break;
					}
				}
				*reinterpret_cast<short*>(m_wm.m_charaSelectData + iVar8 + 4) = (short)iVar12b;
				bVar7 = bVar7 | (1 << iVar12b);
			}
			int iVar12c = reinterpret_cast<int>(m_wm.m_charaSelectData) + iVar8;
			iVar8 = iVar8 + 0x10;
			*reinterpret_cast<short*>(iVar12c + 6) = *reinterpret_cast<short*>(iVar12c + 4);
			iVar11 = iVar11 - 1;
		} while (iVar11 != 0);
		break;
	}
	case 7:
		break;
	}

	if (m_wmWorldState->m_changeRequest == 2
	    && m_wmWorldState->m_menuMode == 4) {
		bytes[0x10] = 1;
		bytes[0x12] = 0;
		bytes[0x13] = 0;
	}

	m_wmWorldState->m_changeRequest = 0;
	m_wmWorldState->m_nextMenuMode = 0;
	m_wmWorldState->m_delay = 0;

	sVar2 = m_wmWorldState->m_menuMode;
	if (sVar2 == 6) {
		MapMng.GetMapIdGrpArray()[0xF7].m_primaryColor.a = 0;
	} else if (iVar14 == 6 && sVar2 != 6) {
		MapMng.GetMapIdGrpArray()[0xF7].m_primaryColor.a = 1;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetParty()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const modelData = m_wm.m_charaModelData;
	unsigned char* const mcList = m_wmWorkBuffer;
	int partyCount = 0;

	if (modelData != 0) {
		for (int i = 0; i < kWmCharaSelectCount; i++) {
			if (modelData[i * 0x34 + 0x0C] != 0) {
				partyCount++;
			}
		}
	}
	if (partyCount == 0 && mcList != 0) {
		for (int i = 0; i < kMcListCount; i++) {
			unsigned char* const entry = mcList + i * kMcListEntrySize;
			if (entry[0x41] != 0 && entry[0x42] == 0 && entry[0x43] == 0) {
				partyCount++;
			}
		}
	}
	gWmMenuWorkA = partyCount;
	bytes[0x10] = static_cast<unsigned char>(partyCount > 0);
}

/*
 * --INFO--
 * PAL Address: 0x800eee34
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetCMakeEnd(int channel)
{
	m_wm.m_charaSelectData[channel * 0x10 + 0xC] = 1;
	if ((unsigned int)System.m_execParam >= 3) {
		System.Printf(const_cast<char*>(s_SetCMakeEnd_chan_pctd_cur_pctd_801DC3B4), channel,
		               (int)*reinterpret_cast<short*>(&m_wm.m_charaSelectData[channel * 0x10 + 4]));
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eed84
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ClrCMakeFlg(int channel)
{
	m_wm.m_charaSelectData[channel * 0x10 + 0xB] = 0;
	const int current = *reinterpret_cast<short*>(&m_wm.m_charaSelectData[channel * 0x10 + 4]);
	if ((unsigned int)System.m_execParam >= 3) {
		System.Printf(const_cast<char*>(s_ClrCMakeFlg_chan_pctd_cur_pctd_801DC390), channel, current);
	}
	m_wm.m_charaModelData[current * 0x34 + 0xC] = 0;
	GetWmCharaHandles(this)[current]->LoadModelASync(3, 0x43, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800eeb9c
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgAllModel2()
{
	unsigned char* bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* handleData = bytes;
	int modelOffset = 0;
	int pdtOffset = 0;

	for (int i = 0; i < kWmMenuPlayerCount; i++) {
		unsigned char* pdtData =
		    m_cmakeWork + pdtOffset + 0x14D0;
		unsigned char* modelData = m_wm.m_charaModelData + modelOffset;
		unsigned int race;
		int variant;
		unsigned int index;
		int modelId;
		int loadMode;

		if (*reinterpret_cast<int*>(pdtData + 0x5B4) != 0) {
			race = *reinterpret_cast<unsigned short*>(pdtData + 0x2E);
			index = *reinterpret_cast<unsigned short*>(pdtData + 0x32);
			variant = *reinterpret_cast<unsigned short*>(pdtData + 0x30);
		} else {
			race = 0xFFFFFFFF;
			*reinterpret_cast<unsigned int*>(modelData + 8) = 0xFFFFFFFF;
			index = 0xFFFFFFFF;
			variant = 0xFFFFFFFF;
		}

		modelData = m_wm.m_charaModelData + modelOffset;
		if ((int)race >= 0) {
			modelId = race * 200 + 100;
			if (variant != 0) {
				modelId += 100;
			}
			modelData[0xC] = 1;
			loadMode = 0;
			modelId += index;
		} else {
			modelData[0xC] = 0;
			loadMode = 3;
			modelId = 0x43;
		}

		reinterpret_cast<CCharaPcs::CHandle**>(handleData + 0x7F4)[0]->LoadModelASync(loadMode, modelId, 0);
		handleData += 4;
		modelOffset += 0x34;
		pdtOffset += 0x9C0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eec84
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgAllModel()
{
	unsigned char* bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* gameData = reinterpret_cast<unsigned char*>(&Game);
	unsigned char* handleData = bytes;
	int modelOffset = 0;

	for (int i = 0; i < kWmMenuPlayerCount; i++) {
		unsigned char* caravanData = gameData + 0x13F0;
		unsigned char* modelData = m_wm.m_charaModelData + modelOffset;
		unsigned int race;
		int variant;
		unsigned int index;
		int modelId;

		if (*reinterpret_cast<int*>(gameData + 0x1794) != 0) {
			race = *reinterpret_cast<unsigned short*>(caravanData + 0x3E0);
			variant = *reinterpret_cast<short*>(caravanData + 0x3E2);
			index = *reinterpret_cast<unsigned short*>(caravanData + 0x3E4);
			modelId = race * 200 + 100;
			if (variant != 0) {
				modelId += 100;
			}
			*reinterpret_cast<unsigned int*>(modelData + 8) = modelId + index;
		} else {
			race = 0xFFFFFFFF;
			*reinterpret_cast<unsigned int*>(modelData + 8) = 0xFFFFFFFF;
			variant = 0xFFFFFFFF;
			index = 0xFFFFFFFF;
		}

		modelData = m_wm.m_charaModelData + modelOffset;
		int loadMode;
		if ((int)race >= 0) {
			modelId = race * 200 + 100;
			if (variant != 0) {
				modelId += 100;
			}
			modelData[0xC] = 1;
			loadMode = 0;
			modelId += index;
		} else {
			modelData[0xC] = 0;
			loadMode = 3;
			modelId = 0x43;
		}
		reinterpret_cast<CCharaPcs::CHandle**>(handleData + 0x7F4)[0]->LoadModelASync(loadMode, modelId, 0);

		gameData += 0xC30;
		handleData += 4;
		modelOffset += 0x34;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 660b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMakeChara(int slot)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const selectData = m_wm.m_charaSelectData;
	unsigned char* const modelData = m_wm.m_charaModelData;
	WmWorldState* const worldState = m_wmWorldState;

	if (slot < 0) {
		slot = 0;
	}
	if (slot > 3) {
		slot = 3;
	}

	if (selectData != 0) {
		unsigned char* const entry = selectData + slot * 0x10;
		*reinterpret_cast<short*>(entry + 6) = *reinterpret_cast<short*>(entry + 4);
		if (entry[0x0D] == 0) {
			entry[0x0A] = 0;
			entry[0x0B] = 0;
		} else if (entry[0x0B] == 0) {
			entry[0x0B] = 1;
		}
		bytes[0x17] = entry[0x0A];
		gWmMenuWorkB = *reinterpret_cast<short*>(entry + 4);
	}

	if (modelData != 0 && modelData[slot * 0x34 + 0x0C] != 0) {
		SetMenuCharaAnim(slot, 1);
	} else {
		SetMenuCharaAnim(slot, 0);
	}

	if (worldState != 0) {
		worldState->m_cardChannel = static_cast<short>(slot);
	}

	gWmMenuWorkA = slot;
	ChkSelectParty();
	bytes[0x16] = static_cast<unsigned char>(slot);
}

/*
 * --INFO--
 * PAL Address: 0x800eeb1c
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgModel(int slot, int tribe, int job, int isFemale)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* modelData = m_wm.m_charaModelData;
	modelData += slot * 0x34;
	int modelNo;
	int charaKind;

	if (tribe >= 0) {
		charaKind = 0;
		modelNo = tribe * 200 + 100;
		if (isFemale != 0) {
			modelNo += 100;
		}
		modelNo += job;
		modelData[0xC] = 1;
	} else {
		charaKind = 3;
		modelData[0xC] = 0;
		modelNo = 0x43;
	}

	GetWmCharaHandles(this)[slot]->LoadModelASync(charaKind, static_cast<unsigned long>(modelNo), 0);
}

/*
 * --INFO--
 * PAL Address: 0x800ee928
 * PAL Size: 500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetAnim(int anim)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	const int handleIdx = anim + 0x20;
	if (m_wm.m_handles[handleIdx]->m_charaKind == 3) {
		return;
	}

	const unsigned int charaNo = m_wm.m_handles[handleIdx]->m_charaNo;
	const int modelBase =  (s32)(static_cast<int>(charaNo / 100) * 100);
	int animBase = (static_cast<int>(charaNo / 100) - 1) * 6;

	m_wm.m_handles[handleIdx]->LoadAnim(s_wmCharaAnimStand, animBase++, 1, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(s_wmCharaAnimWalk, animBase++, 1, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(s_wmCharaAnimRun, animBase++, 1, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(s_wmCharaAnimGlad, animBase++, 3, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(s_wmCharaAnimSleep, animBase++, 1, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(s_wmCharaAnimAngry, animBase, 1, 0, modelBase, -1, 0);

#define animState (m_wmCharaAnimState + anim * 5)
	animState[0] = 0;
	animState[1] = -1;
	animState[2] = rand() % 250;

	int __p22 = handleIdx;
	const int currentAnimIndex = m_wm.m_handles[__p22]->m_currentAnimIndex;
	int __p23 =  (currentAnimIndex + 0);
	const int blendMode = (static_cast<unsigned int>(__p23) >> 31) - 1;
	int __p26 = handleIdx;
	m_wm.m_handles[__p26]->SetAnim((animBase - 5) + animState[0], -1, -1, blendMode, 1);

	reinterpret_cast<float*>(animState)[3] =
	    reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(m_wm.m_handles[handleIdx]->m_model) + 0xB4)[0];
	reinterpret_cast<float*>(animState)[4] =
	    reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(m_wm.m_handles[handleIdx]->m_model) + 0xC0)[0];
#undef animState
}

/*
 * --INFO--
 * PAL Address: 0x800ee828
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCursor(int x, int y, float scale)
{
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	unsigned char alpha = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * scale));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = alpha;
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0));
	MenuPcs.DrawRect(0, static_cast<float>(x), static_cast<float>(y), FLOAT_80331410, FLOAT_80331410, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x800ed94c
 * PAL Size: 3804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMainMenuSub()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int port = 0;
	bool noInput = false;
	u32 btnRaw;
	if (Pad.m_debugPadLock == 0) {
		if (port != 0) {
			goto input_check_done;
		}
		if (Pad.m_debugPadPort == -1) {
			goto input_check_done;
		}
	}
	noInput = true;
input_check_done:
	if (noInput) {
		btnRaw = 0;
	} else {
		u32 clamped = (Pad.m_debugPadPort == port) ? 0 : port;
		btnRaw = Pad.GetPadInputs()[clamped].buttonDown[0];
	}
	const unsigned short btn = static_cast<unsigned short>(btnRaw);
	const short state = m_wmWorldState->m_mainState;

	if (((state > 0) && (state < 4)) || m_wmWorldState->m_cardChannel == 1) {
		if (state == 2 && m_wmWorldState->m_delay == 0) {
			if ((btn & 1) != 0) {
				*reinterpret_cast<float*>(bytes + 0x78) -= FLOAT_8033151c;
				if (*reinterpret_cast<float*>(bytes + 0x78) < FLOAT_803313dc) {
					*reinterpret_cast<float*>(bytes + 0x78) += FLOAT_80331528;
					*reinterpret_cast<float*>(bytes + 0x7C) += FLOAT_80331528;
				}
				m_wmWorldState->m_frameCounter = 0xE;
				if (m_wmWorldState->m_cardChannel >= 4) {
					m_wmWorldState->m_cardChannel = 0;
				} else {
					m_wmWorldState->m_cardChannel++;
				}
				Sound.PlaySe(0x37, 0x40, 0x7F, 0);
			} else if ((btn & 2) != 0) {
				*reinterpret_cast<float*>(bytes + 0x78) += FLOAT_8033151c;
				if (*reinterpret_cast<float*>(bytes + 0x78) > FLOAT_80331528) {
					*reinterpret_cast<float*>(bytes + 0x78) -= FLOAT_80331528;
					*reinterpret_cast<float*>(bytes + 0x7C) -= FLOAT_80331528;
				}
				m_wmWorldState->m_frameCounter = 0xE;
				if (m_wmWorldState->m_cardChannel <= 0) {
					m_wmWorldState->m_cardChannel = 4;
				} else {
					m_wmWorldState->m_cardChannel--;
				}
				Sound.PlaySe(0x37, 0x40, 0x7F, 0);
			}

			const float selA = *reinterpret_cast<float*>(bytes + 0x78);
			const float selB = *reinterpret_cast<float*>(bytes + 0x7C);
			const float hi = (selB < selA) ? selA : selB;
			const float lo = (selB < selA) ? selB : selA;
			const float delta = FLOAT_803315cc * (hi - lo);
			if (selB <= selA) {
				*reinterpret_cast<float*>(bytes + 0x7C) += delta;
			} else {
				*reinterpret_cast<float*>(bytes + 0x7C) -= delta;
			}

			if (m_wmWorldState->m_frameCounter > 0) {
				m_wmWorldState->m_frameCounter--;
			}

			if (m_wmWorldState->m_frameCounter == 0 && (btn & 3) == 0) {
				if ((btn & 0x100) != 0) {
					*reinterpret_cast<float*>(bytes + 0x7C) = *reinterpret_cast<float*>(bytes + 0x78);
					m_wmWorldState->m_delay = 0x14;
					m_wmWorldState->m_nextMenuMode = 1;
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				} else if ((btn & 0x200) != 0) {
					int valid = 0;
					*reinterpret_cast<float*>(bytes + 0x7C) = *reinterpret_cast<float*>(bytes + 0x78);
					const unsigned char stageMode = Game.m_gameWork.m_menuStageMode;
					int i = 0;
					do {
						if (stageMode != 0 && i != 0) {
							break;
						}
						if (m_wmWorldState->m_backupParams[i] >= 0) {
							valid++;
						}
						i++;
					} while (i < 4);
					if (valid == 0) {
						Sound.PlaySe(4, 0x40, 0x7F, 0);
					} else {
						m_wmWorldState->m_delay = 1;
						m_wmWorldState->m_nextMenuMode = -1;
						Sound.PlaySe(3, 0x40, 0x7F, 0);
					}
				}
			}
		}

		unsigned char* const worldObj = m_wm.m_worldObjData;
		Mtx baseMtx;
		Mtx workMtx;
		Mtx modelMtx;
		Mtx rotMtx;
		Mtx scaleMtx;
		Mtx selScaleMtx;
		Vec modelPos;

		PSMTXRotRad(baseMtx, 'x', FLOAT_803315d0);
		PSMTXRotRad(rotMtx, 'y', FLOAT_803314bc * -*reinterpret_cast<float*>(bytes + 0x7C));
		PSMTXConcat(baseMtx, rotMtx, baseMtx);

		float t = static_cast<float>(m_wmWorldState->m_titleState) / FLOAT_803314c0;
		float selectedRotY;
		float selectedRotZ;
		float selectedYOffset;
		WM_MENU_EVAL_SPLINE(selectedRotY, DAT_8032E8D4, DAT_8032E8D0, t);
		WM_MENU_EVAL_SPLINE(selectedRotZ, DAT_8032E8DC, DAT_8032E8D8, t);
		WM_MENU_EVAL_SPLINE(selectedYOffset, DAT_8032E8E4, DAT_8032E8E0, t);

		float openScale = FLOAT_803313dc;
		if (m_wmWorldState->m_nextMenuMode != -1) {
			t = static_cast<float>(0x14 - m_wmWorldState->m_delay) / FLOAT_803314c0;
			WM_MENU_EVAL_SPLINE(openScale, DAT_8032E8EC, DAT_8032E8E8, t);
		}

		if (state == 2 && m_wmWorldState->m_delay == 0) {
			m_wmWorldState->m_titleState++;
			if (m_wmWorldState->m_titleState >= 100) {
				m_wmWorldState->m_titleState = 0;
			}
		} else {
			m_wmWorldState->m_titleState = 0;
		}

		const float rotZSel = FLOAT_803314bc * selectedRotZ;
		const float rotYSel = FLOAT_803314bc * selectedRotY;
		for (int i = 0; i < 5; i++) {
			const short curState = m_wmWorldState->m_mainState;
			if (!(((curState > 0) && (curState < 4)) || i == 1)) {
				continue;
			}

			unsigned char* const panel = worldObj + i * 0x50;
			*reinterpret_cast<int*>(panel) = 1;
			int frame = 0;
			float modelScale = FLOAT_803315d4;
			if (i == 0) {
				modelScale = static_cast<float>(static_cast<double>(modelScale) * DOUBLE_803315D8);
			}

			*reinterpret_cast<float*>(panel + 0x34) = modelScale;
			*reinterpret_cast<float*>(panel + 0x38) = modelScale;
			*reinterpret_cast<float*>(panel + 0x3C) = modelScale;
			*reinterpret_cast<float*>(panel + 0x1C) = FLOAT_803313dc;
			*reinterpret_cast<float*>(panel + 0x20) = FLOAT_803313dc;
			*reinterpret_cast<float*>(panel + 0x24) = FLOAT_803315E0;
			*reinterpret_cast<float*>(panel + 0x28) = FLOAT_803313dc;
			*reinterpret_cast<float*>(panel + 0x2C) = FLOAT_803315E4 * static_cast<float>(i);
			*reinterpret_cast<float*>(panel + 0x30) = FLOAT_803313dc;

			PSMTXRotRad(workMtx, 'y', FLOAT_803314bc * *reinterpret_cast<float*>(panel + 0x2C));
			PSMTXMultVecSR(workMtx, reinterpret_cast<Vec*>(panel + 0x1C), &modelPos);
			PSMTXTransApply(workMtx, modelMtx, modelPos.x, modelPos.y, modelPos.z);
			PSMTXConcat(baseMtx, modelMtx, workMtx);
			{
				Vec* const mpp = &modelPos;
				mpp->x = workMtx[0][3];
				mpp->y = workMtx[1][3];
				mpp->z = workMtx[2][3];
			}
			PSMTXIdentity(modelMtx);

			if (i == 1) {
				const int ms = m_wmWorldState->m_mainState;
				if (ms != 2) {
					if (ms < 2) {
						frame = 0x13 - (ms * 10 + m_wmWorldState->m_frameCounter);
						if (static_cast<int>(frame) < 0) {
							frame = 0;
						}
					} else {
						frame = m_wmWorldState->m_frameCounter + (ms - 3) * 10;
					}
				}
			}

			if (i == 0) {
				PSMTXRotRad(rotMtx, 'y', FLOAT_803315E8);
				PSMTXRotRad(scaleMtx, 'x', FLOAT_803315d0);
				PSMTXConcat(rotMtx, scaleMtx, modelMtx);
			} else if (i == 1) {
				if (m_wmWorldState->m_nextMenuMode != -1 && m_wmWorldState->m_cardChannel == 1 &&
				    m_wmWorldState->m_mainState != 2) {
					float inner = static_cast<float>(DOUBLE_80331600 *
					    (static_cast<double>(static_cast<float>(frame)) / DOUBLE_80331608));
					float rot = static_cast<float>(
					    DOUBLE_803315F0 * (DOUBLE_803315F8 + inner));
					PSMTXRotRad(modelMtx, 'x', rot);
				} else {
					PSMTXRotRad(modelMtx, 'x', FLOAT_80331610);
				}
			} else if (i == 2 || i == 3 || i == 4) {
				PSMTXRotRad(modelMtx, 'x', FLOAT_80331614);
			}

			if (m_wmWorldState->m_cardChannel == i) {
				PSMTXRotRad(rotMtx, 'z', rotZSel);
				PSMTXRotRad(selScaleMtx, 'y', rotYSel);
				PSMTXConcat(rotMtx, selScaleMtx, rotMtx);
				PSMTXConcat(rotMtx, modelMtx, modelMtx);
			}

			s_MMenuPos[i].x = modelPos.x;
			s_MMenuPos[i].y = static_cast<float>(static_cast<double>(modelPos.y) + DOUBLE_80331418);
			s_MMenuPos[i].z = modelPos.z;
			PSMTXTransApply(modelMtx, workMtx, FLOAT_803313dc, FLOAT_803313dc, modelPos.z);
			PSMTXScaleApply(workMtx, modelMtx, *reinterpret_cast<float*>(panel + 0x34),
			                *reinterpret_cast<float*>(panel + 0x38), *reinterpret_cast<float*>(panel + 0x3C));
			if (i == 0) {
				PSMTXTransApply(modelMtx, modelMtx, FLOAT_80331618, FLOAT_8033161C, FLOAT_803313dc);
			} else if (i == 1) {
				PSMTXTransApply(modelMtx, modelMtx, FLOAT_80331620, FLOAT_803313dc, FLOAT_803313dc);
			}
			if (m_wmWorldState->m_cardChannel == i) {
				modelMtx[1][3] = modelMtx[1][3] + selectedYOffset;
			}

			if (m_wmWorldState->m_nextMenuMode != -1 && i == 1 &&
			    m_wmWorldState->m_cardChannel == 1 && m_wmWorldState->m_mainState != 2) {
				double u = static_cast<double>(frame) / DOUBLE_80331608;
				float m00 = modelMtx[0][3];
				float m10 = modelMtx[1][3];
				float m20 = modelMtx[2][3];
				modelMtx[0][3] = m00 + static_cast<float>(static_cast<float>(-m00 * u) * u);
				modelMtx[1][3] = m10 + static_cast<float>(static_cast<float>(DOUBLE_80331628 - m10 * u) * u);
				modelMtx[2][3] = m20 + static_cast<float>(static_cast<float>(DOUBLE_80331630 - m20) * u);
			}

			if (m_wmWorldState->m_nextMenuMode != -1 && m_wmWorldState->m_cardChannel == i &&
			    m_wmWorldState->m_delay != 0) {
				PSMTXScale(scaleMtx, openScale, openScale, openScale);
				PSMTXConcat(scaleMtx, modelMtx, modelMtx);
			}

			if (m_wmWorldState->m_nextMenuMode != -1 && i == 1 &&
			    m_wmWorldState->m_cardChannel == 1 && m_wmWorldState->m_mainState != 2) {
				float openScale2 = static_cast<float>(
				    static_cast<float>(DOUBLE_803313f8 * (static_cast<double>(frame) / DOUBLE_80331608)) +
				    DOUBLE_80331420);
				PSMTXScale(scaleMtx, openScale2, openScale2, openScale2);
				PSMTXConcat(scaleMtx, modelMtx, modelMtx);
			}

			if (GetWmWorldHandles(this)[i] != 0 && GetWmWorldHandles(this)[i]->m_model != 0) {
				if (m_wmWorldState->m_mainState == 1) {
					*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(GetWmWorldHandles(this)[i]->m_model) + 0x9C) =
					    static_cast<float>(DOUBLE_803314e8 * static_cast<double>(m_wmWorldState->m_frameCounter));
				} else if (m_wmWorldState->m_mainState == 2) {
					*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(GetWmWorldHandles(this)[i]->m_model) + 0x9C) = FLOAT_803313e8;
				} else if (m_wmWorldState->m_mainState == 3) {
					*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(GetWmWorldHandles(this)[i]->m_model) + 0x9C) =
					    static_cast<float>(-(DOUBLE_803314e8 * static_cast<double>(m_wmWorldState->m_frameCounter) -
					                         DOUBLE_80331420));
				} else {
					*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(GetWmWorldHandles(this)[i]->m_model) + 0x9C) = FLOAT_803313dc;
				}
				if (m_wmWorldState->m_nextMenuMode != -1 && m_wmWorldState->m_cardChannel == 1 &&
				    i == 1) {
					*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(GetWmWorldHandles(this)[i]->m_model) + 0x9C) = FLOAT_803313e8;
				}
				GetWmWorldHandles(this)[i]->m_model->SetMatrix(modelMtx);
				GetWmWorldHandles(this)[i]->m_model->CalcMatrix();
				GetWmWorldHandles(this)[i]->m_model->CalcSkin();
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChkSelectParty()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const modelData = m_wm.m_charaModelData;
	int selected = 0;

	if (modelData == 0) {
		gWmMenuWorkA = 0;
		return;
	}

	for (int i = 0; i < kWmMenuPlayerCount; i++) {
		if (modelData[i * 0x34 + 0xC] != 0) {
			selected++;
		}
	}

	gWmMenuWorkA = selected;
	reinterpret_cast<unsigned char*>(this)[0x10] = static_cast<unsigned char>(selected != 0);
}

/*
 * --INFO--
 * PAL Address: 0x800ecff0
 * PAL Size: 2396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMainMenuSub()
{
	int worldObj = reinterpret_cast<int>(m_wm.m_worldObjData);

	Mtx modelMtx;
	Mtx44 screenMtx;
	GXColor white;
	float depthValues[5];
	unsigned int drawOrder[5];

	Mtx lookAtMtx;
	Mtx44 projectionMtx;
	C_MTXPerspective(projectionMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
	GXSetProjection(projectionMtx, GX_PERSPECTIVE);
	PSMTX44Copy(projectionMtx, CameraPcs.m_screenMatrix);
	C_MTXLookAt(lookAtMtx, reinterpret_cast<Point3d*>(worldObj + 0x740),
	            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc)),
	            reinterpret_cast<Point3d*>(&CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc)));
	PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(&m_wm));
	PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
	CharaPcs.InitEnv(5);
	GXSetColorUpdate(0);
	GXSetAlphaUpdate(0);
	GXSetCopyClear(CColor(0, 0, 0, 0).color, 0x00FFFFFF);
	GXSetColorUpdate(1);
	GXSetAlphaUpdate(1);
	GXSetViewport(static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x738)),
	              static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x73A)),
	              static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x73C)),
	              static_cast<float>(*reinterpret_cast<short*>(worldObj + 0x73E)), FLOAT_803313dc, FLOAT_803313e8);
	GXSetScissor(*reinterpret_cast<unsigned int*>(worldObj + 0x770), *reinterpret_cast<unsigned int*>(worldObj + 0x774),
	             *reinterpret_cast<unsigned int*>(worldObj + 0x778), *reinterpret_cast<unsigned int*>(worldObj + 0x77C));
	PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

	const float zSub = FLOAT_80331598;
	const Vec* posPtr = s_MMenuPos;
	const double scaleX = DOUBLE_803315A0;
	const double one = DOUBLE_80331420;
	const double scaleY = DOUBLE_803315A8;
	const float subX = FLOAT_803315b0;
	const float subY = FLOAT_803315b4;
	const float zero = FLOAT_803313dc;
	int viewOff = 0;
	for (int i = 0; i < 5; i++) {
		Vec viewPos;
		Vec4d clipPos;
		viewPos.x = posPtr->x;
		viewPos.z = posPtr->z;
		viewPos.y = posPtr->y;
		viewPos.z = viewPos.z - zSub;
		Math.MTX44MultVec4(screenMtx, &viewPos, &clipPos);
		posPtr++;

		clipPos.x = clipPos.x / clipPos.w;
		clipPos.y = clipPos.y / clipPos.w;
		double negY = -static_cast<double>(clipPos.y);
		clipPos.x = static_cast<float>(scaleX * (one + static_cast<double>(clipPos.x)));
		clipPos.y = static_cast<float>(scaleY * (one + negY));
		*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_worldObjData) + viewOff + 8) =
		    static_cast<short>(static_cast<int>(clipPos.x - subX));
		*reinterpret_cast<short*>(reinterpret_cast<int>(m_wm.m_worldObjData) + viewOff + 0xA) =
		    static_cast<short>(static_cast<int>(clipPos.y - subY));
		*reinterpret_cast<unsigned short*>(reinterpret_cast<int>(m_wm.m_worldObjData) + viewOff + 0xC) = 0x280;
		*reinterpret_cast<unsigned short*>(reinterpret_cast<int>(m_wm.m_worldObjData) + viewOff + 0xE) = 0x1C0;
		*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_worldObjData) + viewOff + 0x10) = zero;
		*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_worldObjData) + viewOff + 0x14) = zero;
		*reinterpret_cast<float*>(reinterpret_cast<int>(m_wm.m_worldObjData) + viewOff + 0x18) = zSub;
		viewOff += 0x50;
	}

	float* depthPtr = depthValues;
	unsigned int* orderPtr = drawOrder;
	unsigned char* handlePtr = reinterpret_cast<unsigned char*>(this);
	for (unsigned int i = 0; static_cast<int>(i) < 5; i++) {
		PSMTXCopy(reinterpret_cast<MtxPtr>(*reinterpret_cast<int*>(*reinterpret_cast<int*>(handlePtr + 0x774) + 0x168) + 8),
		          modelMtx);
		*orderPtr = i;
		handlePtr += 4;
		orderPtr++;
		*depthPtr = modelMtx[2][3];
		depthPtr++;
	}

	{
		float* fp = depthValues;
		unsigned int* op = drawOrder;
		for (int i = 0; i < 5; i++) {
			int next = i + 1;
			float* fpInner = depthValues + next;
			unsigned int* opInner = drawOrder + next;
			for (int j = next; j < 5; j++) {
				float depth = *fp;
				if (*fp > *fpInner) {
					unsigned int idx = *op;
					unsigned int idxInner = *opInner;
					*fp = *fpInner;
					*op = idxInner;
					*fpInner = depth;
					*opInner = idx;
				}
				fpInner++;
				opInner++;
			}
			op++;
			fp++;
		}
	}

	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	white.a = 0xFF;
	for (int orderIndex = 0; orderIndex < 5; orderIndex++) {
		short state = *reinterpret_cast<short*>(reinterpret_cast<int>(m_wmWorldState) + 0x10);
		if (state < 1 || state > 3) {
			if (*reinterpret_cast<short*>(reinterpret_cast<int>(m_wmWorldState) + 0x26) != 1 || orderIndex != 1) {
				continue;
			}
			drawOrder[orderIndex] = 1;
		}

		int view = reinterpret_cast<int>(m_wm.m_worldObjData) + drawOrder[orderIndex] * 0x50;
		Mtx lookAtMtx0;
		Mtx44 projectionMtx0;
		C_MTXPerspective(projectionMtx0, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
		GXSetProjection(projectionMtx0, GX_PERSPECTIVE);
		PSMTX44Copy(projectionMtx0, CameraPcs.m_screenMatrix);
		C_MTXLookAt(lookAtMtx0, reinterpret_cast<Point3d*>(view + 0x10),
		            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc)),
		            reinterpret_cast<Point3d*>(&CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc)));
		PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(&m_wm));
		PSMTXCopy(lookAtMtx0, CameraPcs.m_cameraMatrix);
		CharaPcs.InitEnv(5);
		GXSetColorUpdate(0);
		GXSetAlphaUpdate(0);
		GXSetCopyClear(CColor(0, 0, 0, 0).color, 0x00FFFFFF);
		GXSetColorUpdate(1);
		GXSetAlphaUpdate(1);
		GXSetViewport(static_cast<float>(*reinterpret_cast<short*>(view + 8)), static_cast<float>(*reinterpret_cast<short*>(view + 0xA)),
		              static_cast<float>(*reinterpret_cast<short*>(view + 0xC)), static_cast<float>(*reinterpret_cast<short*>(view + 0xE)),
		              FLOAT_803313dc, FLOAT_803313e8);
		GXSetScissor(*reinterpret_cast<unsigned int*>(view + 0x40), *reinterpret_cast<unsigned int*>(view + 0x44),
		             *reinterpret_cast<unsigned int*>(view + 0x48), *reinterpret_cast<unsigned int*>(view + 0x4C));
		Graphic.SetFog(1, 0);
		WmMenuLightTable& lightTable = gWmMenuLightTables[0];
		LightPcs.SetAmbient(lightTable.m_ambient);
		LightPcs.SetNumDiffuse(lightTable.m_diffuseCount);
		for (int lightIndex = 0; lightIndex < lightTable.m_diffuseCount; lightIndex++) {
			LightPcs.SetDiffuse(
				lightIndex, lightTable.m_diffuseColors[lightIndex],
				&lightTable.m_diffuseDirs[lightIndex], 0);
		}
		LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
		reinterpret_cast<CCharaPcs::CHandle*>(
		    *reinterpret_cast<int*>(reinterpret_cast<int>(this) + drawOrder[orderIndex] * 4 + 0x774))
		    ->Draw(5);
		DrawInit();

		GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
		view = reinterpret_cast<int>(m_wm.m_worldObjData) + drawOrder[orderIndex] * 0x50;
		Mtx lookAtMtx1;
		Mtx44 projectionMtx1;
		C_MTXPerspective(projectionMtx1, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
		GXSetProjection(projectionMtx1, GX_PERSPECTIVE);
		PSMTX44Copy(projectionMtx1, CameraPcs.m_screenMatrix);
		C_MTXLookAt(lookAtMtx1, reinterpret_cast<Point3d*>(view + 0x10),
		            reinterpret_cast<Vec*>(&CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc)),
		            reinterpret_cast<Point3d*>(&CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc)));
		PSMTXCopy(CameraPcs.m_cameraMatrix, reinterpret_cast<MtxPtr>(&m_wm));
		PSMTXCopy(lookAtMtx1, CameraPcs.m_cameraMatrix);
		CharaPcs.InitEnv(5);
		GXSetColorUpdate(0);
		GXSetAlphaUpdate(0);
		GXSetCopyClear(CColor(0, 0, 0, 0).color, 0x00FFFFFF);
		GXSetColorUpdate(1);
		GXSetAlphaUpdate(1);
		GXSetViewport(static_cast<float>(*reinterpret_cast<short*>(view + 8)), static_cast<float>(*reinterpret_cast<short*>(view + 0xA)),
		              static_cast<float>(*reinterpret_cast<short*>(view + 0xC)), static_cast<float>(*reinterpret_cast<short*>(view + 0xE)),
		              FLOAT_803313dc, FLOAT_803313e8);
		GXSetScissor(*reinterpret_cast<unsigned int*>(view + 0x40), *reinterpret_cast<unsigned int*>(view + 0x44),
		             *reinterpret_cast<unsigned int*>(view + 0x48), *reinterpret_cast<unsigned int*>(view + 0x4C));

		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<int>(m_wmWorldState) + 0x10) == 2) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
			MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			GXSetChanMatColor(static_cast<GXChannelID>(4), white);
			unsigned int idx = drawOrder[orderIndex];
			float frameWidth = reinterpret_cast<float*>(lbl_801DC294)[idx];
			MenuPcs.DrawRect3d(0, -(FLOAT_80331414 * (frameWidth / FLOAT_803315B8) - FLOAT_803313dc), FLOAT_803315BC,
			           static_cast<float>(DOUBLE_80331418 + static_cast<double>(s_MMenuPos[idx].z) - DOUBLE_803315C0),
			           frameWidth, FLOAT_80331554, FLOAT_803313dc,
			           FLOAT_80331554 * static_cast<float>(static_cast<int>(idx)) + FLOAT_80331528,
			           FLOAT_803315C8, FLOAT_803315C8);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800ecfd0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetMcAccessPos(int* x, int* y)
{
	*x = gWmMenuCursorX[0];
	*y = gWmMenuCursorX[1];
}

/*
 * --INFO--
 * PAL Address: 0x800ecfb0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetMcOdekakePos(int* x, int* y)
{
	*x = gWmMenuCursorY[0];
	*y = gWmMenuCursorY[1];
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChkMcDataCnt()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const list = m_wmWorkBuffer;
	int count = 0;

	if (list == 0) {
		gWmMenuWorkA = 0;
		return;
	}

	for (int i = 0; i < kMcListCount; i++) {
		unsigned char* const entry = list + i * kMcListEntrySize;
		if (entry[0x43] == 0 && entry[0x41] != 0 && entry[0x42] == 0) {
			count++;
		}
	}

	gWmMenuWorkA = count;
}

/*
 * --INFO--
 * PAL Address: 0x800eb6f8
 * PAL Size: 6328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMCList()
{
	extern float FLOAT_803314D8;
	extern float FLOAT_803314DC;
	extern float FLOAT_803314E0;
	extern float FLOAT_803314F8;
	extern float FLOAT_803314FC;
	extern double DOUBLE_803314F0;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	CFont* fontF8 = m_fonts[0];
#define worldState GetWmWorldState(this)
	short state = worldState->m_mainState;

	if ((state == 2 || state == 3) && worldState->m_subState != 0) {
		int slotIdx = 0;
		int iVar16 = 0;
		do {
			float yPos;
			float alpha;
			short sub = worldState->m_subState;
			if (sub == 1 || worldState->m_mainState == 3) {
				int animFrames;
				if (worldState->m_mainState == 2) {
					animFrames = (int)worldState->m_frameCounter - iVar16;
				} else {
					animFrames = 10 - ((int)worldState->m_frameCounter - (3 - slotIdx) * 3);
				}
				if (animFrames < 0) {
					goto LAB_next;
				}
				if (animFrames > 10) {
					yPos = FLOAT_803314D8;
					alpha = FLOAT_803313e8;
				} else {
					alpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(animFrames));
					yPos = static_cast<float>(animFrames) * FLOAT_803314E0 + FLOAT_803314DC;
				}
			} else {
				yPos = FLOAT_803314D8;
				alpha = FLOAT_803313e8;
			}
			if (!(alpha <= DOUBLE_803314F0)) {
				float slotY = (float)(DOUBLE_80331498 * static_cast<double>(slotIdx) + DOUBLE_80331490);
				MenuPcs.SetAttrFmt((FMT)0);
				alpha = FLOAT_80331458 * alpha;
				GXColor slotColor;
				slotColor.r = 0xFF;
				slotColor.g = 0xFF;
				slotColor.b = 0xFF;
				slotColor.a = static_cast<unsigned char>(static_cast<int>(alpha));
				GXSetChanMatColor(GX_COLOR0A0, slotColor);

				// Draw slot background
				MenuPcs.SetTexture((TEX)0x24);
				MenuPcs.DrawRect(0, yPos, slotY, FLOAT_80331468, FLOAT_803314F8,
				         FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				yPos += FLOAT_80331468;
				MenuPcs.SetTexture((TEX)0x25);
				MenuPcs.DrawRect(0, yPos, slotY, FLOAT_803314FC, FLOAT_803314F8,
				         FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				yPos += FLOAT_803314FC;

				// Draw slot content area
				MenuPcs.SetAttrFmt((FMT)1);
				GXColor contentColors[4];
				contentColors[0].r = 0xFF;
				contentColors[0].g = 0xFF;
				contentColors[0].b = 0xFF;
				contentColors[0].a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(alpha)));
				contentColors[1].r = 0xFF;
				contentColors[1].g = 0xFF;
				contentColors[1].b = 0xFF;
				contentColors[1].a = 0;
				contentColors[2].r = 0xFF;
				contentColors[2].g = 0xFF;
				contentColors[2].b = 0xFF;
				contentColors[2].a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(alpha)));
				contentColors[3].r = 0xFF;
				contentColors[3].g = 0xFF;
				contentColors[3].b = 0xFF;
				contentColors[3].a = 0;
				MenuPcs.DrawRect(0, yPos, slotY, FLOAT_80331500, FLOAT_803314F8,
				         FLOAT_803313dc, FLOAT_803313dc, contentColors,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			}
LAB_next:
			slotIdx++;
			iVar16 += 3;
		} while (slotIdx < 4);
	}

	float frameAlpha;
	state = worldState->m_mainState;
	if (state == 0) {
		frameAlpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(worldState->m_frameCounter));
	} else if (state > 0 && state < 4) {
		frameAlpha = FLOAT_803313e8;
	} else {
		frameAlpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(worldState->m_frameCounter) - DOUBLE_80331420));
	}
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor frameColor;
	frameColor.r = 0xFF;
	frameColor.g = 0xFF;
	frameColor.b = 0xFF;
	frameColor.a = static_cast<unsigned char>(static_cast<int>(DOUBLE_80331508 * static_cast<double>(frameAlpha)));
	GXSetChanMatColor(static_cast<GXChannelID>(4), frameColor);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
	for (int i = 0, offset = i; i < 2; i++, offset += 0x1C) {
		if (((1 << i) & 2) != 0) {
			unsigned char* const frameEntry = m_wm.m_frameInfo + offset + 4;
			MenuPcs.DrawRect(*reinterpret_cast<unsigned int*>(frameEntry + 0x18),
			         static_cast<float>(*reinterpret_cast<short*>(frameEntry)),
			         static_cast<float>(*reinterpret_cast<short*>(frameEntry + 2)),
			         static_cast<float>(*reinterpret_cast<short*>(frameEntry + 4)),
			         static_cast<float>(*reinterpret_cast<short*>(frameEntry + 6)),
			         *reinterpret_cast<float*>(frameEntry + 8), *reinterpret_cast<float*>(frameEntry + 0x0C),
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor white;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	white.a = 0xFF;
	GXSetChanMatColor(static_cast<GXChannelID>(4), white);
	short separatorSub = worldState->m_subState;
	if (separatorSub != 0 && separatorSub > 1 &&
	    worldState->m_mainState == 2) {
		const float sepZero = FLOAT_803313dc;
		const double sepSlope = DOUBLE_80331498;
		const double sepBase = DOUBLE_80331490;
		const double sepOff = DOUBLE_80331510;
		for (int slot = 0; slot < kMcListCount; slot++) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
			MenuPcs.DrawRect(0, FLOAT_803314D8,
			         static_cast<float>(static_cast<float>(sepSlope * static_cast<double>(slot) + sepBase) -
			                            sepOff),
			         FLOAT_803314D8, FLOAT_803314D8,
			         static_cast<float>(sepBase * static_cast<double>(slot)), FLOAT_803313e0,
			         FLOAT_803313e8, FLOAT_803313e8, sepZero);
		}
	}

	if (worldState->m_subState >= 0x11 &&
	    worldState->m_mainState < 3) {
		const double mapX = DOUBLE_80331510 + static_cast<double>(FLOAT_80331518);
		const int language = Game.m_gameWork.m_languageId;
		int* const digitWidths = reinterpret_cast<int*>(lbl_801DB7F8 + 0x920);
		int* const playWidths = reinterpret_cast<int*>(lbl_801DB7F8 + 0xab0);
		const double rowSlopeD = DOUBLE_80331498;
		const double rowBaseD = DOUBLE_80331490;
		for (int slot = 0, slotOff = slot; slot < kMcListCount; slot++, slotOff += kMcListEntrySize) {
			unsigned char* const slotData = m_wmCharaState + slotOff;
			const float slotY = (float)(rowSlopeD * static_cast<double>(slot) + rowBaseD);
			if (*reinterpret_cast<char*>(slotData + 0x42) == 0 && *reinterpret_cast<char*>(slotData + 0x41) != 0) {
				float rowY = FLOAT_80331440 + slotY;
				float capX = FLOAT_80331468;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x26));
				MenuPcs.DrawRect(0, FLOAT_80331468, rowY, FLOAT_803314D8, FLOAT_80331440,
				         FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

				int memberCount = 0;
				if (*reinterpret_cast<int*>(slotData + 0x18) >= 0) {
					memberCount = 1;
				}
				if (*reinterpret_cast<int*>(slotData + 0x1C) >= 0) {
					memberCount++;
				}
				if (*reinterpret_cast<int*>(slotData + 0x20) >= 0) {
					memberCount++;
				}
				if (*reinterpret_cast<int*>(slotData + 0x24) >= 0) {
					memberCount++;
				}
				const int panelWidth = memberCount * 0x30 + 0x40;
				capX += FLOAT_803314D8 + static_cast<float>(panelWidth);
				MenuPcs.DrawRect(8, capX, rowY, FLOAT_803314D8, FLOAT_80331440,
				         FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x2A));
				MenuPcs.DrawRect(0, FLOAT_8033151c, rowY, static_cast<float>(panelWidth), FLOAT_80331440,
				         FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

				float digitX = FLOAT_80331520;
				if (language != 5) {
					rowY = FLOAT_803314D8 + slotY;
				}
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x17));
				int digitCount = (*reinterpret_cast<int*>(slotData + 8) > 9) + 1;
				if (*reinterpret_cast<int*>(slotData + 8) > 99) {
					digitCount = 3;
				}
				if (digitCount == 3) {
					MenuPcs.DrawRect(0, FLOAT_80331520, rowY, static_cast<float>(digitWidths[10]), FLOAT_80331410,
					         FLOAT_80331524, FLOAT_80331528, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				} else {
					int totalWidth;
					for (int di = 0; di < digitCount; di++) {
						if (digitCount == 1) {
							totalWidth = reinterpret_cast<int*>(lbl_801DB7F8 + 0x920)[*reinterpret_cast<int*>(slotData + 8) % 10];
						} else if (di == 0) {
							totalWidth = reinterpret_cast<int*>(lbl_801DB7F8 + 0x920)[*reinterpret_cast<int*>(slotData + 8) / 10];
						} else {
							totalWidth += reinterpret_cast<int*>(lbl_801DB7F8 + 0x920)[*reinterpret_cast<int*>(slotData + 8) % 10];
						}
					}
					float digitScale = static_cast<float>((language != 5) ? DOUBLE_80331530 : DOUBLE_80331420);
					if (language == 2) {
						totalWidth += 8;
					} else if (language == 3) {
						totalWidth += 0xB;
					} else if (language != 5) {
						totalWidth += 0x20;
					}
					digitX += static_cast<float>((0x20 - static_cast<int>(static_cast<float>(totalWidth) * digitScale)) / 2);
					const float zeroF = FLOAT_803313dc;
					const double colSlope = DOUBLE_80331490;
					const double rowSlope = DOUBLE_80331540;
					const double rowBase = DOUBLE_80331538;
					for (int digitIdx = 0; digitIdx < digitCount; digitIdx++) {
						int digit;
						if (digitCount == 1) {
							digit = *reinterpret_cast<int*>(slotData + 8) % 10;
						} else if (digitIdx == 0) {
							digit = *reinterpret_cast<int*>(slotData + 8) / 10;
						} else {
							digit = *reinterpret_cast<int*>(slotData + 8) % 10;
						}
						const int digitWidth = reinterpret_cast<int*>(lbl_801DB7F8 + 0x920)[digit];
						const float digitWidthF = static_cast<float>(digitWidth);
						MenuPcs.DrawRect(0, digitX, rowY, digitWidthF, FLOAT_80331410,
						         static_cast<float>(colSlope * static_cast<float>(digit % 5)),
						         static_cast<float>(rowSlope * static_cast<float>(digit / 5) + rowBase),
						         digitScale, FLOAT_803313e8, zeroF);
						digitX += digitWidthF * digitScale;
					}
					float suffixWidth;
					if (language == 2) {
						suffixWidth = FLOAT_80331548;
					} else if (language == 3) {
						suffixWidth = FLOAT_8033154C;
					} else {
						suffixWidth = FLOAT_80331410;
					}
					float suffixU = FLOAT_803313dc;
					unsigned char wideLang = (language == 1 || language == 4);
					float suffixScale = static_cast<float>(wideLang ? DOUBLE_80331530 : DOUBLE_80331420);
					if (language == 1) {
						if (*reinterpret_cast<int*>(slotData + 8) / 10 == 1) {
							suffixU = FLOAT_8033151c;
						} else {
							const int ones = *reinterpret_cast<int*>(slotData + 8) % 10;
							if (ones >= 1 && ones <= 3) {
								suffixU = FLOAT_803314D8 * static_cast<float>(ones - 1);
							} else {
								suffixU = FLOAT_8033151c;
							}
						}
					} else if (language == 4) {
						if (*reinterpret_cast<int*>(slotData + 8) != 1) {
							suffixU = FLOAT_803314D8;
						}
					} else if (language == 2) {
						rowY += FLOAT_80331550;
					}
					if (language != 5) {
						MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x34));
						MenuPcs.DrawRect(0, digitX, rowY, suffixWidth, FLOAT_803314D8,
						         suffixU, FLOAT_803313dc, suffixScale, FLOAT_803313e8, FLOAT_803313dc);
					}
				}

				float labelX = FLOAT_80331520;
				float dateLabelY;
				if (language != 5) {
					dateLabelY = FLOAT_80331554 + slotY;
				} else {
					dateLabelY = FLOAT_803314c8 + (FLOAT_803314D8 + slotY);
				}
				labelX -= FLOAT_80331550;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x21));
				MenuPcs.DrawRect(0, labelX, dateLabelY,
				         FLOAT_80331440, FLOAT_80331558, FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x37));
				float iconX = FLOAT_8033155C;
				const float iconY = FLOAT_803314D8 + slotY;
				unsigned char* memberPtr = slotData;
				for (int member = 0; member < 4; member++, memberPtr += 4) {
					const int modelNo = *reinterpret_cast<int*>(memberPtr + 0x18);
					if (modelNo >= 0) {
						const int faceNo = modelNo - 100;
						float texU = ((faceNo / 100 & 1) != 0) ? FLOAT_80331560 : DOUBLE_803314F0;
						const float du = static_cast<float>(faceNo % 100) * FLOAT_80331468;
						texU += du;
						MenuPcs.DrawRect(0, iconX, iconY, FLOAT_80331468, FLOAT_80331468,
						         texU,
						         static_cast<float>(faceNo / 100 / 2) * FLOAT_80331468,
						         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
						iconX += FLOAT_80331468;
					}
				}
				rowY = FLOAT_80331468 + slotY;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x20));
				MenuPcs.DrawRect(0, FLOAT_80331564, rowY,
				         FLOAT_80331554, FLOAT_803314D8, FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

				int playHours;
				int playMinutes;
				MemoryCardMan.CnvPlayTime(*reinterpret_cast<unsigned int*>(slotData + 0x14), &playHours, &playMinutes);
				int playDigits[5];
				float playWidth = FLOAT_803313dc;
				const int hundreds = playHours / 100;
				if (hundreds != 0) {
					playDigits[0] = hundreds;
					playWidth += static_cast<float>(reinterpret_cast<int*>(lbl_801DB7F8 + 0xab0)[hundreds]);
				} else {
					playDigits[0] = -1;
				}
				const int hourRemainder = playHours % 100;
				const int tens = hourRemainder / 10;
				if (tens != 0 || playDigits[0] > 0) {
					playDigits[1] = tens;
					playWidth += static_cast<float>(reinterpret_cast<int*>(lbl_801DB7F8 + 0xab0)[tens]);
				} else {
					playDigits[1] = -1;
				}
				playDigits[2] = hourRemainder % 10;
				playDigits[3] = playMinutes / 10;
				playDigits[4] = playMinutes % 10;
				playWidth += static_cast<float>(reinterpret_cast<int*>(lbl_801DB7F8 + 0xab0)[playDigits[2]]);
				playWidth += static_cast<float>(playWidths[10]);
				playWidth += static_cast<float>(reinterpret_cast<int*>(lbl_801DB7F8 + 0xab0)[playDigits[3]]);
				playWidth += static_cast<float>(reinterpret_cast<int*>(lbl_801DB7F8 + 0xab0)[playDigits[4]]);
				float playX = FLOAT_80331518 - playWidth;
				for (int digitIdx = 0; digitIdx < 5; digitIdx++) {
					if (playDigits[digitIdx] >= 0) {
						if (digitIdx == 3) {
							const float colonW = static_cast<float>(playWidths[10]);
							MenuPcs.DrawRect(0, playX, rowY, colonW, FLOAT_803314D8,
							         FLOAT_80331568, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
							playX += colonW;
						}
						const float digitW = static_cast<float>(reinterpret_cast<int*>(lbl_801DB7F8 + 0xab0)[playDigits[digitIdx]]);
						MenuPcs.DrawRect(0, playX, rowY, digitW, FLOAT_803314D8,
						         static_cast<float>(DOUBLE_80331490 * static_cast<double>(playDigits[digitIdx]) + DOUBLE_80331570),
						         FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
						playX += digitW;
					}
				}

				unsigned char* const mapInfo = reinterpret_cast<unsigned char*>(lbl_801DB7F8 + 0xadc) +
				                               *reinterpret_cast<int*>(slotData + 0x10) * 4;
				CMaterial* material = MapMng.GetMaterialID(mapInfo[0]);
				CTexture* texture = *reinterpret_cast<CTexture**>(reinterpret_cast<unsigned char*>(material) + 0x3C);
				TextureMan.SetTexture(static_cast<_GXTexMapID>(0), texture);
				Mtx texMtx;
				PSMTXScale(texMtx, FLOAT_803313e8 / static_cast<float>(texture->m_width),
				           FLOAT_803313e8 / static_cast<float>(texture->m_height), FLOAT_803313e8);
				GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX2x4);
				GXSetNumTexGens(1);
				GXSetTexCoordGen2(static_cast<GXTexCoordID>(0), static_cast<GXTexGenType>(1),
				                  static_cast<GXTexGenSrc>(4), 0x1E, GX_FALSE, 0x7D);
				TextureMan.SetTextureTev(texture);
				MenuPcs.DrawRect(0,
				         static_cast<float>(mapX),
				         static_cast<float>(DOUBLE_80331510 + static_cast<double>(slotY)),
				         FLOAT_80331578, FLOAT_80331578,
				         static_cast<float>(static_cast<int>(static_cast<char>(mapInfo[1])) << 7),
				         static_cast<float>(static_cast<int>(static_cast<char>(mapInfo[2])) << 7),
				         FLOAT_80331434, FLOAT_80331434, FLOAT_803313dc);
			}
		}

		// Draw text info for each save slot
		const double tSlope = DOUBLE_80331498;
		const double tBase = DOUBLE_80331490;
		for (int slot = 0, slotOff = slot; slot < 4; slot++, slotOff += 0x48) {
			char part[64];
			char locationStr[64];
			char line1[64];
			char line2[64];
			unsigned char* const slotData = m_wmCharaState + slotOff;
			const float slotY = (float)(tSlope * static_cast<double>(slot) + tBase);
			if (*reinterpret_cast<char*>(slotData + 0x42) != 0 || *reinterpret_cast<int*>(slotData + 8) <= 0) {
				fontF8->SetMargin(FLOAT_803313e8);
				fontF8->SetShadow(1);
				fontF8->SetScale(FLOAT_803313e8);
				fontF8->DrawInit();
				fontF8->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
				fontF8->SetTlut(0x19);
				const unsigned int msgId =
					__cntlzw(static_cast<unsigned int>(static_cast<int>(*reinterpret_cast<char*>(slotData + 0x42)))) >> 5;
				const int width = static_cast<int>(fontF8->GetWidth(const_cast<char*>(GetMcStr(msgId))));
				fontF8->SetPosX(static_cast<float>(static_cast<float>(0x238 - width) * DOUBLE_803313F8 + FLOAT_803314D8));
				fontF8->SetPosY(static_cast<float>(DOUBLE_80331580 + static_cast<double>(slotY)));
				fontF8->Draw(const_cast<char*>(GetMcStr(msgId)));
			} else {
				fontF8->SetMargin(FLOAT_803313e8);
				fontF8->SetShadow(0);
				fontF8->SetScale(FLOAT_80331588);
				fontF8->DrawInit();
				fontF8->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
				fontF8->SetTlut(0x2C);
				fontF8->SetPosX(FLOAT_80331520);
				fontF8->SetPosY(static_cast<float>(static_cast<double>(slotY) - DOUBLE_80331510));
				strcpy(locationStr, reinterpret_cast<char*>(slotData + 0x2C));
				if (locationStr[0] != 0) {
					locationStr[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(locationStr[0])));
				}
				fontF8->Draw(locationStr);

				fontF8->SetMargin(FLOAT_803313e8);
				fontF8->SetShadow(1);
				fontF8->SetScale(FLOAT_8033158C);
				fontF8->DrawInit();
				fontF8->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
				fontF8->SetTlut(7);
				const int locationIndex = *reinterpret_cast<int*>(slotData + 0x10);
				if (locationIndex == 0x0F) {
					strcpy(locationStr, reinterpret_cast<char*>(slotData + 0x2C));
				} else if (locationIndex == 0x16) {
					const int lang2 = Game.m_gameWork.m_languageId;
					if (lang2 == 2) {
						strcpy(locationStr, reinterpret_cast<char*>(slotData + 0x2C));
						strcat(locationStr, lbl_80210D10[lang2 - 1]);
					} else {
						strcpy(locationStr, lbl_80210D10[lang2 - 1]);
						strcat(locationStr, reinterpret_cast<char*>(slotData + 0x2C));
					}
				} else {
					strcpy(locationStr, Game.m_cFlatDataArr[1].TableStrings(3)[locationIndex]);
				}
				if (locationStr[0] != 0) {
					locationStr[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(locationStr[0])));
				}
				const float locationWidth = fontF8->GetWidth(locationStr);
				float locationY = FLOAT_80331558 + slotY;
				if (locationWidth <= FLOAT_8033155C) {
					fontF8->SetPosX(FLOAT_80331518 - locationWidth);
					fontF8->SetPosY(locationY);
					fontF8->Draw(locationStr);
				} else {
					locationY = locationY + FLOAT_80331550;
					strcpy(line1, locationStr);
					line2[0] = 0;
					char* searchPos = locationStr;
					for (;;) {
						char* space = strchr(searchPos, ' ');
						if (space == 0) {
							break;
						}
						const int firstLen = space - locationStr;
						memcpy(part, locationStr, firstLen);
						part[firstLen] = 0;
						if (static_cast<int>(fontF8->GetWidth(part)) > 0x90) {
							break;
						}
						strcpy(line1, part);
						strcpy(line2, space + 1);
						searchPos = space + 1;
					}
					fontF8->SetPosX(FLOAT_80331518 - fontF8->GetWidth(line1));
					fontF8->SetPosY(locationY - FLOAT_80331590);
					fontF8->Draw(line1);
					fontF8->SetPosX(FLOAT_80331518 - fontF8->GetWidth(line2));
					fontF8->SetPosY(locationY);
					fontF8->Draw(line2);
				}
			}
		}
	}
	if (worldState->m_subState == 0x11) {
		short mode = worldState->m_menuMode;
		if (mode == 5) {
			GXColor color = CColor(0xFF, 0xFF, 0xFF, 0xFF).color;
			char* text = const_cast<char*>(GetMcStr(2));
			const int x = static_cast<int>(CalcCenteringPos2(const_cast<char*>(GetMcStr(2)), FLOAT_80331594, FLOAT_803313e8));
			DrawFont2(x, 0x187, color, 7, text, FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
		} else if (mode == 2) {
			GXColor color = CColor(0xFF, 0xFF, 0xFF, 0xFF).color;
			char* text = const_cast<char*>(GetMcStr(3));
			const int x = static_cast<int>(CalcCenteringPos2(const_cast<char*>(GetMcStr(3)), FLOAT_80331594, FLOAT_803313e8));
			DrawFont2(x, 0x187, color, 7, text, FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
		}
	}
	DrawInit();
#undef worldState
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawHelpBase(int kind, float baseAlpha)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	WmWorldState* const worldState = m_wmWorldState;
	float alpha = baseAlpha;

	if (alpha <= 0.0f) {
		alpha = 1.0f;
	}

	if (worldState != 0) {
		const short state = worldState->m_mainState;
		if (state == 0) {
			alpha *= static_cast<float>(worldState->m_frameCounter) * 0.1f;
		} else if (state >= 3) {
			alpha *= 1.0f - static_cast<float>(worldState->m_frameCounter) * 0.1f;
		}
	}
	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)};
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kind == 0 ? 0x1F : 0x20));
	MenuPcs.DrawRect(0xFFFFFFFF, 0.0f, 0x1A8, 0x280, 0x18, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x800eb1d8
 * PAL Size: 1312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMcObj()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const charaBase = bytes + 0x44;
	unsigned char* const worldObj = m_wm.m_worldObjData;

	const float panelStateFloat = FLOAT_80331480;
	const double yBase = DOUBLE_80331488;
	const double ySlope = DOUBLE_80331498;
	const double bias = DOUBLE_80331408;
	const double yOffset = DOUBLE_80331490;
	const float yScale = FLOAT_803314A0;
	const float zero = FLOAT_803313dc;
	const float six = FLOAT_803314a4;
	const double doubleD = DOUBLE_803314a8;

	SplineTable* const yTbl = reinterpret_cast<SplineTable*>(&gWmModelYOffsetSplineCount);

	union I2D {
		double d;
		struct {
			unsigned int hi;
			unsigned int lo;
		} u;
	};

	unsigned int* panelState = reinterpret_cast<unsigned int*>(worldObj + 0x550);
	for (int i = 0; i < 4; i++, panelState = reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(panelState) + 0x50)) {
		*reinterpret_cast<short*>(panelState + 2) = static_cast<short>(panelStateFloat);

		I2D iConv;
		iConv.u.hi = 0x43300000;
		iConv.u.lo = static_cast<unsigned int>(i) ^ 0x80000000;
		const int y = static_cast<int>(
		    static_cast<float>(yBase + ySlope * (iConv.d - bias) + yOffset) -
		    yScale);
		*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(panelState) + 0xA) = static_cast<short>(y);
		*reinterpret_cast<unsigned short*>(panelState + 3) = 0x140;
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(panelState) + 0xE) = 0xE0;
		reinterpret_cast<float*>(panelState)[4] = zero;
		reinterpret_cast<float*>(panelState)[5] = zero;
		reinterpret_cast<float*>(panelState)[6] = six;

		panelState[1]++;
		if (static_cast<float>(static_cast<int>(panelState[1])) >=
		    doubleD * static_cast<double>(yTbl->data[gWmModelYOffsetSplineCount * 4 - 4])) {
			panelState[1] = 0;
		}

		unsigned char* const charaState = m_wmCharaState + i * 0x48;
		if (*reinterpret_cast<int*>(charaState + 8) <= 0) {
			panelState[0] = 0;
		} else {
			panelState[0] = 1;
			reinterpret_cast<float*>(panelState)[7] = FLOAT_803314B0;
			reinterpret_cast<float*>(panelState)[8] = FLOAT_803314B4;
			reinterpret_cast<float*>(panelState)[9] = FLOAT_803313dc;
			reinterpret_cast<float*>(panelState)[0xD] = FLOAT_80331434;
			reinterpret_cast<float*>(panelState)[0xE] = FLOAT_80331434;
			reinterpret_cast<float*>(panelState)[0xF] = FLOAT_80331434;
			reinterpret_cast<float*>(panelState)[10] = FLOAT_803314B8;
			reinterpret_cast<float*>(panelState)[0xB] = reinterpret_cast<float*>(panelState)[0xB] + FLOAT_803314bc;

			float t = static_cast<float>(static_cast<int>(panelState[1])) / FLOAT_803314c0;
			float yResult = FLOAT_803313dc;
			if (t >= gWmModelYOffsetSpline[gWmModelYOffsetSplineCount * 4 - 4]) {
				yResult = gWmModelYOffsetSpline[gWmModelYOffsetSplineCount * 4 - 3];
			} else {
				int idx = 0;
				float* spline = gWmModelYOffsetSpline;
				for (int n = gWmModelYOffsetSplineCount; n > 0; n--) {
					if (t <= *spline) {
						if (idx == 0) {
							yResult = gWmModelYOffsetSpline[idx * 4 + 1];
						} else {
							float* cur = gWmModelYOffsetSpline + idx * 4;
							float* prev = gWmModelYOffsetSpline + (idx - 1) * 4;
							float width = *cur - *prev;
							float u = (t - *prev) / width;
							float u2 = u * u;
							float u3 = u2 * u;
							yResult =
							    width * (prev[3] * (u + (u3 - FLOAT_803314c8 * u2)) + cur[2] * (u3 - u2)) +
							    (prev[1] * (FLOAT_803313e8 + (FLOAT_803314c8 * u3 - FLOAT_803314c4 * u2)) +
							    cur[1] * (FLOAT_803314cc * u3 + FLOAT_803314c4 * u2));
						}
						break;
					}
					spline += 4;
					idx++;
				}
			}
			reinterpret_cast<float*>(panelState)[8] = reinterpret_cast<float*>(panelState)[8] + yResult;

			float rotResult = FLOAT_803313dc;
			t = static_cast<float>(static_cast<int>(panelState[1])) / FLOAT_803314c0;
			if (t >= gWmModelRotationSpline[gWmModelRotationSplineCount * 4 - 4]) {
				rotResult = gWmModelRotationSpline[gWmModelRotationSplineCount * 4 - 3];
			} else {
				int idx = 0;
				float* spline = gWmModelRotationSpline;
				for (int n = gWmModelRotationSplineCount; n > 0; n--) {
					if (t <= *spline) {
						if (idx == 0) {
							rotResult = gWmModelRotationSpline[idx * 4 + 1];
						} else {
							float* cur = gWmModelRotationSpline + idx * 4;
							float* prev = gWmModelRotationSpline + (idx - 1) * 4;
							float width = *cur - *prev;
							float u = (t - *prev) / width;
							float u2 = u * u;
							float u3 = u2 * u;
							rotResult =
							    width * (prev[3] * (u + (u3 - FLOAT_803314c8 * u2)) + cur[2] * (u3 - u2)) +
							    (prev[1] * (FLOAT_803313e8 + (FLOAT_803314c8 * u3 - FLOAT_803314c4 * u2)) +
							    cur[1] * (FLOAT_803314cc * u3 + FLOAT_803314c4 * u2));
						}
						break;
					}
					spline += 4;
					idx++;
				}
			}
			reinterpret_cast<float*>(panelState)[0xB] = FLOAT_803314bc * rotResult;

			Mtx scaleMtx;
			Mtx rotXMtx;
			Mtx rotYMtx;
			PSMTXScale(scaleMtx, reinterpret_cast<float*>(panelState)[0xD], reinterpret_cast<float*>(panelState)[0xE],
			           reinterpret_cast<float*>(panelState)[0xF]);
			PSMTXRotRad(rotXMtx, 'x', reinterpret_cast<float*>(panelState)[10]);
			PSMTXRotRad(rotYMtx, 'y', reinterpret_cast<float*>(panelState)[0xB]);
			PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
			rotXMtx[0][3] = reinterpret_cast<float*>(panelState)[7];
			rotXMtx[1][3] = reinterpret_cast<float*>(panelState)[8];
			rotXMtx[2][3] = reinterpret_cast<float*>(panelState)[9];
			PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);

			reinterpret_cast<CChara::CModel*>(
			    *reinterpret_cast<int*>(*reinterpret_cast<int*>(charaBase + 0x774 + i * 4) + 0x168))
			    ->SetMatrix(scaleMtx);
			reinterpret_cast<CChara::CModel*>(
			    *reinterpret_cast<int*>(*reinterpret_cast<int*>(charaBase + 0x774 + i * 4) + 0x168))
			    ->CalcMatrix();
			reinterpret_cast<CChara::CModel*>(
			    *reinterpret_cast<int*>(*reinterpret_cast<int*>(charaBase + 0x774 + i * 4) + 0x168))
			    ->CalcSkin();
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMcObj()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldObj = m_wm.m_worldObjData;
	WmWorldState* const worldState = m_wmWorldState;
	float alpha = FLOAT_803313e8;

	if (worldState != 0) {
		const short state = worldState->m_mainState;
		if (state == 1) {
			alpha = static_cast<float>(worldState->m_frameCounter) * 0.1f;
		} else if (state >= 3) {
			alpha = 1.0f - static_cast<float>(worldState->m_frameCounter) * 0.1f;
		}
	}
	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	CalcMcObj();
	if (worldObj != 0 && worldState != 0 && worldState->m_subState != 0) {
		const GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)};
		for (int i = 0; i < 4; i++) {
			unsigned char* const panel = worldObj + 0x550 + i * 0x50;
			if (*reinterpret_cast<unsigned int*>(panel) == 0) {
				continue;
			}

			SetProjection(i + 0x11);
			MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			GXSetChanMatColor(static_cast<GXChannelID>(4), color);
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x24));
			DrawRect3d(0xFFFFFFFF, FLOAT_803313dc, FLOAT_803313dc, *reinterpret_cast<float*>(panel + 0x1C), FLOAT_80331554,
			           FLOAT_80331554, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc);
		}
		RestoreProjection();
	}
	DrawMCList();
	DrawMcWin(m_menuWindowInfo->state, 0);
	DrawPageMark();
	DrawHelpBase(0, alpha);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMcList(int index, McListInfo* info)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const list = m_wmWorkBuffer;
	if (list == 0 || info == 0 || index < 0 || index >= kMcListCount) {
		return;
	}
	unsigned char* const dst = list + index * kMcListEntrySize;
	memcpy(dst, info, kMcListEntrySize);
	dst[0x43] = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McListInfo::operator= (const McListInfo& src)
{
	memcpy(this, &src, kMcListEntrySize);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ClrMcList()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const list = m_wmWorkBuffer;
	if (list != 0) {
		memset(list, 0, kMcListEntrySize * kMcListCount);
	}
	gWmMenuCursorX[0] = 0xFF;
	gWmMenuCursorX[1] = 0xFF;
	gWmMenuCursorY[0] = 0xFF;
	gWmMenuCursorY[1] = 0xFF;
	gWmMenuWorkA = 0;
	gWmMenuWorkB = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800eb088
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_propagation off
unsigned int CMenuPcs::BindEffect(int slot, int effectNo, int cameraSlot)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	PPPCREATEPARAM createParam;

	if (cameraSlot < 0) {
		cameraSlot = slot;
	}

	EffectInfo* effect = &m_effectWork[slot];
	if (slot == 5 && effectNo < 0x13) {
		effect++;
	} else if (slot >= 0x11 && slot <= 0x14 && effectNo > 0x19) {
		effect += 4;
	}

	effect->m_effectNo = effectNo;
	const int group = (((effectNo ^ 100) >> 1) - ((effectNo ^ 100) & effectNo)) >> 31;
	CGObject* const object = &effect->m_object;
	effect->m_slotNo = slot;
	object->Create();
	object->m_charaModelHandle = reinterpret_cast<CCharaPcs::CHandle**>(bytes + 0x4A8)[cameraSlot];

	createParam.m_paramB = reinterpret_cast<unsigned int>(object);
	createParam.m_lookTargetPtr = object;

	const unsigned int partId = PartMng.pppCreate(group, effectNo, &createParam, 1);
	effect->m_partNo = partId;
	return effect->m_partNo;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x800eafa0
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetLight(int mode)
{
	Graphic.SetFog(1, 0);

	LightPcs.SetAmbient(gWmMenuLightTables[mode].m_ambient);
	LightPcs.SetNumDiffuse(static_cast<unsigned long>(gWmMenuLightTables[mode].m_diffuseCount));

	for (int i = 0; i < gWmMenuLightTables[mode].m_diffuseCount; i++) {
		LightPcs.SetDiffuse(
			static_cast<unsigned long>(i), gWmMenuLightTables[mode].m_diffuseColors[i],
			&gWmMenuLightTables[mode].m_diffuseDirs[i], 0);
	}

	LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawPageMark()
{
	int x;
	int y;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	WmWorldState* const worldState = m_wmWorldState;
	float alpha = FLOAT_803313e8;
	float cursorScale = FLOAT_803313e8;

	if (worldState != 0) {
		const short state = worldState->m_mainState;
		const short step = worldState->m_frameCounter;
		if (state == 0) {
			alpha = static_cast<float>(step) * 0.1f;
		} else if (state >= 3) {
			alpha = 1.0f - static_cast<float>(step) * 0.1f;
		}
		if (state == 2) {
			cursorScale += static_cast<float>(step & 3) * 0.1f;
		}
	}
	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)};
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x2B));

	const unsigned char cur = bytes[0x14];
	unsigned char max = bytes[0x15];
	if (max > 5) {
		max = 5;
	}
	for (unsigned int i = 0; i < max; i++) {
		const float px = 0x20 + static_cast<float>(i * 0x14);
		const float py = 0x1A0;
		const float tx = (i == cur) ? 0.0f : 16.0f;
		const float scale = (i == cur) ? cursorScale : 1.0f;
		MenuPcs.DrawRect(0xFFFFFFFF, px, py, 16.0f, 16.0f, tx, 0.0f, scale, scale, 0.0f);
	}

	GetMcAccessPos(&x, &y);
	if (x != static_cast<signed char>(0xFF) && y != static_cast<signed char>(0xFF) && x >= 0 && x < 0x280 && y >= 0 && y < 0x1C0) {
		DrawCursor(x, y, cursorScale);
	}
	GetMcOdekakePos(&x, &y);
	if (x != static_cast<signed char>(0xFF) && y != static_cast<signed char>(0xFF) && x >= 0 && x < 0x280 && y >= 0 && y < 0x1C0) {
		DrawCursor(x, y, cursorScale);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800ead94
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawRect2(unsigned long flags, float x, float y, float w, float h, float tx, float ty, float scaleX, float scaleY, float (*mtx)[4])
{
	if (w <= 0.0f || h <= 0.0f) {
		return;
	}

#define halfTexel FLOAT_80331434
	float u0;
	float u1;
	float v0;
	float v1;

	if ((flags & 8) != 0) {
		u1 = tx + halfTexel;
		u0 = (tx + w) - halfTexel;
	} else {
		u0 = tx + halfTexel;
		u1 = (tx + w) - halfTexel;
	}

	if ((flags & 4) != 0) {
		v1 = ty + halfTexel;
		v0 = (ty + h) - halfTexel;
	} else {
		v0 = ty + halfTexel;
		v1 = (ty + h) - halfTexel;
	}

	if ((flags & 1) != 0) {
		x = x - halfTexel * (w * scaleX);
	}
	if ((flags & 2) != 0) {
		y = y - halfTexel * (h * scaleY);
	}
#undef halfTexel

	Vec in[4];
	Vec out[4];

	in[0].x = x;
	in[0].y = y;
	in[0].z = 0.0f;

	in[1].x = x + (w * scaleX);
	in[1].y = y;
	in[1].z = 0.0f;

	in[2].x = x;
	in[2].y = y + (h * scaleY);
	in[2].z = 0.0f;

	in[3].x = x + (w * scaleX);
	in[3].y = y + (h * scaleY);
	in[3].z = 0.0f;

	PSMTXMultVecArray(reinterpret_cast<MtxPtr>(mtx), in, out, 4);

	GXBegin(static_cast<GXPrimitive>(0x98), static_cast<GXVtxFmt>(0), 4);

	for (int i = 0; i < 4; i++) {
		GXPosition3f32(out[i].x, out[i].y, out[i].z);
		float uu;
		if ((i & 1) != 0) {
			uu = u1;
		} else {
			uu = u0;
		}
		float vv;
		if (i < 2) {
			vv = v0;
		} else {
			vv = v1;
		}
		GXTexCoord2f32(uu, vv);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eab98
 * PAL Size: 508b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawRect3d(unsigned long flags, float x, float y, float z, float w, float h, float tx, float ty, float scaleX, float scaleY)
{
	if (w <= 0.0f || h <= 0.0f) {
		return;
	}

#define halfTexel FLOAT_80331434
	float u0;
	float u1;
	float v0;
	float v1;

	if ((flags & 8) != 0) {
		u1 = tx + halfTexel;
		u0 = (tx + w) - halfTexel;
	} else {
		u0 = tx + halfTexel;
		u1 = (tx + w) - halfTexel;
	}

	if ((flags & 4) != 0) {
		v1 = ty + halfTexel;
		v0 = (ty + h) - halfTexel;
	} else {
		v0 = ty + halfTexel;
		v1 = (ty + h) - halfTexel;
	}

	if ((flags & 1) != 0) {
		x = x - halfTexel * (w * scaleX);
	}
	if ((flags & 2) != 0) {
		y = y - halfTexel * (h * scaleY);
	}
#undef halfTexel

	Vec out[4];

	out[0].x = x;
	out[0].y = y;
	out[0].z = z;

	out[1].x = x + (w * scaleX);
	out[1].y = y;
	out[1].z = z;

	out[2].x = x;
	out[2].y = y + (h * scaleY);
	out[2].z = z;

	out[3].x = x + (w * scaleX);
	out[3].y = y + (h * scaleY);
	out[3].z = z;

	GXBegin(static_cast<GXPrimitive>(0x98), static_cast<GXVtxFmt>(0), 4);

	for (int i = 0; i < 4; i++) {
		GXPosition3f32(out[i].x, out[i].y, out[i].z);
		float uu;
		if ((i & 1) != 0) {
			uu = u1;
		} else {
			uu = u0;
		}
		float vv;
		if (i < 2) {
			vv = v0;
		} else {
			vv = v1;
		}
		GXTexCoord2f32(uu, vv);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eaaec
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMcWinInfo(int x, int y)
{
    const short newX = static_cast<short>(static_cast<int>(static_cast<float>(static_cast<float>(0x280 - x) * DOUBLE_803313F8)));
    const short newY = static_cast<short>(static_cast<int>(static_cast<float>((FLOAT_80331430 - static_cast<float>(y)) * DOUBLE_803313F8)));
    m_menuWindowInfo->x = newX;
    m_menuWindowInfo->y = newY;
    m_menuWindowInfo->width = static_cast<short>(x);
    m_menuWindowInfo->height = static_cast<short>(y);
    m_menuWindowInfo->frame = 0;
    m_menuWindowInfo->state = 3;
}

/*
 * --INFO--
 * PAL Address: 0x800ea4f4
 * PAL Size: 1528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMcWin(short state, short kind)
{
	if (state >= 0 && m_menuWindowInfo->state != state) {
		m_menuWindowInfo->state = state;
	}

	if (m_menuWindowInfo->state == 3) {
		return;
	}

	const float centerX = static_cast<float>(m_menuWindowInfo->x) + static_cast<float>(static_cast<double>(m_menuWindowInfo->width) * DOUBLE_803313f8);
	const float centerY = static_cast<float>(m_menuWindowInfo->y) + static_cast<float>(static_cast<double>(m_menuWindowInfo->height) * DOUBLE_803313f8);

	float sx;
	float sy;
	float sw;
	float sh;
	if (m_menuWindowInfo->state != 1) {
		const float xAdd = (((centerX - static_cast<float>(m_menuWindowInfo->x)) - FLOAT_80331410) / FLOAT_80331414) * static_cast<float>(m_menuWindowInfo->frame);
		const float yAdd = (((centerY - static_cast<float>(m_menuWindowInfo->y)) - FLOAT_80331410) / FLOAT_80331414) * static_cast<float>(m_menuWindowInfo->frame);
		sx = (centerX - FLOAT_80331410) - xAdd;
		sy = (centerY - FLOAT_80331410) - yAdd;
		sw = static_cast<float>(DOUBLE_80331418 * static_cast<double>(FLOAT_80331410 + xAdd));
		sh = static_cast<float>(DOUBLE_80331418 * static_cast<double>(FLOAT_80331410 + yAdd));
	} else {
		sx = static_cast<float>(m_menuWindowInfo->x);
		sy = static_cast<float>(m_menuWindowInfo->y);
		sw = static_cast<float>(m_menuWindowInfo->width);
		sh = static_cast<float>(m_menuWindowInfo->height);
	}

	sx = static_cast<float>(static_cast<int>(static_cast<double>(sx) - DOUBLE_803313f8));
	sy = static_cast<float>(static_cast<int>(static_cast<double>(sy) - DOUBLE_803313f8));
	sw = static_cast<float>(static_cast<int>(static_cast<double>(sw) - DOUBLE_80331420));
	sh = static_cast<float>(static_cast<int>(static_cast<double>(sh) - DOUBLE_80331420));

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = 0xFF;
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);

	int rectIdx;
	unsigned long flags;

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? 0x24 : 0x2C));
	const float right = (sx + sw) - FLOAT_80331410;
	const float bottom = (sy + sh) - FLOAT_80331410;
	const float uv0 = FLOAT_803313dc;
	for (rectIdx = 0; rectIdx < 4; rectIdx++) {
		float x;
		float y;
		flags = 0;
		if (rectIdx & 1) {
			x = right;
			flags |= 8;
		} else {
			x = sx;
		}
		if (rectIdx & 2) {
			y = bottom;
			flags |= 4;
		} else {
			y = sy;
		}
		MenuPcs.DrawRect(flags, x, y, FLOAT_80331410, FLOAT_80331410, uv0, uv0, FLOAT_803313e8, FLOAT_803313e8, uv0);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? 0x26 : 0x2D));
	const double innerWidthD = static_cast<double>(sw) - DOUBLE_80331428;
	const float innerX = FLOAT_80331410 + sx;
	const float uv1 = FLOAT_803313dc;
	const float innerWidthF = static_cast<float>(innerWidthD);
	float y = sy;
	for (rectIdx = 0; rectIdx < 2; rectIdx++) {
		flags = 0;
		if (rectIdx != 0) {
			y = bottom;
			flags |= 4;
		}
		MenuPcs.DrawRect(flags, innerX, y, innerWidthF, FLOAT_80331410, uv1, uv1, FLOAT_803313e8, FLOAT_803313e8, uv1);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? 0x25 : 0x2E));
	const double innerHeightD = static_cast<double>(sh) - DOUBLE_80331428;
	const float innerY = FLOAT_80331410 + sy;
	const float uv2 = FLOAT_803313dc;
	const float innerHeightF = static_cast<float>(innerHeightD);
	float x = sx;
	for (rectIdx = 0; rectIdx < 2; rectIdx++) {
		flags = 0;
		if (rectIdx != 0) {
			x = right;
			flags |= 8;
		}
		MenuPcs.DrawRect(flags, x, innerY, FLOAT_80331410, innerHeightF, uv2, uv2, FLOAT_803313e8, FLOAT_803313e8, uv2);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? 0x27 : 0x2F));
	const float uv3 = FLOAT_803313dc;
	MenuPcs.DrawRect(flags, innerX, innerY, static_cast<float>(innerWidthD), static_cast<float>(innerHeightD), uv3, uv3, FLOAT_803313e8, FLOAT_803313e8, uv3);

	if (m_menuWindowInfo->state == 0) {
		m_menuWindowInfo->frame++;
		if (m_menuWindowInfo->frame >= 6) {
			m_menuWindowInfo->frame = 6;
			m_menuWindowInfo->state = 1;
		}
	} else if (m_menuWindowInfo->state == 1) {
		if (m_menuWindowInfo->frame != 6) {
			m_menuWindowInfo->frame = 6;
		}
	} else if (m_menuWindowInfo->state == 2) {
		m_menuWindowInfo->frame--;
		if (m_menuWindowInfo->frame <= 0) {
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800ea150
 * PAL Size: 932b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMcWinMess(int winType, int messType)
{
	CFont* const font = m_fonts[0];

	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_803313e8);
	font->DrawInit();

	font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
	font->SetTlut(0x23);

	const char* const* msgTable = GetMcWinMessBuff(messType);
	const int languageIndex = Game.m_gameWork.m_languageId - 1;
	const unsigned char* const winMess = reinterpret_cast<unsigned char*>(GetWinMess(winType));

	float posX;
	if (winType != 0) {
		int maxWidth = 0;
		const unsigned char* entry = winMess;
		for (int i = 0; i < *reinterpret_cast<const int*>(winMess); i++) {
			const short msgId = *reinterpret_cast<const short*>(entry + 4);
			const char* text = msgTable[msgId];
			if (text != 0) {
				if (text[0] == '$') {
					text++;
				}
				const int width = font->GetWidth(const_cast<char*>(text));
				if (width > maxWidth) {
					maxWidth = width;
				}
			}
			entry += 2;
		}
		posX = static_cast<float>(static_cast<double>(m_menuWindowInfo->x) + static_cast<double>(m_menuWindowInfo->width - maxWidth) * DOUBLE_803313f8);
	}

	float y = static_cast<float>(m_menuWindowInfo->y + 0x20);
	const float lineHeight = FLOAT_80331404;

	char textBuf[128];
	const unsigned char* entry = winMess + 4;
	for (int i = 0; i < *reinterpret_cast<const int*>(winMess); i++) {
		const short msgId = *reinterpret_cast<const short*>(entry);
		const char* text = msgTable[msgId];
		if (strlen(text) != 0) {
			int isDollar;
			if (text[0] == '$') {
				strcpy(textBuf, text + 1);
				isDollar = 1;
			} else {
				strcpy(textBuf, text);
				isDollar = 0;
			}

			if (winType == 0 || isDollar != 0) {
				const int textWidth = font->GetWidth(textBuf);
				posX = static_cast<float>(static_cast<double>(m_menuWindowInfo->x) + static_cast<double>(m_menuWindowInfo->width - textWidth) * DOUBLE_803313f8);
			}
			font->SetPosX(posX);
			font->SetPosY(y);
			if (messType == 0) {
				char* slotText = 0;
				if (winType != 0) {
					slotText = strstr(textBuf, lbl_80210D54[languageIndex]);
				}
				if (!(winType == 0 || slotText == 0)) {
					int len = strlen(lbl_80210D54[languageIndex]);
					slotText[len - 1] += GetMcCtrl()->m_cardChannel;
				} else {
					char* marker = strstr(textBuf, lbl_80331400);
					if (marker != 0) {
						marker[0] += 2;
						marker[1] += 2;
					}
				}
			} else {
				char* dataText = strstr(textBuf, lbl_80210D68[languageIndex]);
				if (dataText != 0) {
					int len = strlen(lbl_80210D68[languageIndex]);
					dataText[len - 1] += GetMcCtrl()->m_saveIndex;
				}
			}
			font->Draw(textBuf);
		}
		y += lineHeight;
		entry += 2;
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x800ea014
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetWinSize(int winType, short* w, short* h, int messType)
{
	CFont* const font = m_fonts[0];

	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_803313e8);

	const char* const* msgTable = GetMcWinMessBuff(messType);
	const unsigned char* const winMess = reinterpret_cast<unsigned char*>(GetWinMess(winType));
#define count (*reinterpret_cast<const int*>(winMess))
	int maxWidth = 0;

	const unsigned char* entry = winMess;
	for (int i = 0; i < count; i++) {
		const short msgId = *reinterpret_cast<const short*>(entry + 4);
		const char* text = msgTable[msgId];
		if (text != 0) {
			if (text[0] == '$') {
				text++;
			}
			const int textWidth = font->GetWidth(text);
			if (textWidth > maxWidth) {
				maxWidth = textWidth;
			}
		}
		entry += 2;
	}

	int cols = maxWidth / 0x16;
	if ((maxWidth % 0x16) != 0) {
		cols++;
	}

	*w = static_cast<short>((cols + 2) * 0x16 + 0x40);
	*h = static_cast<short>(count * 0x1E + 0x40);
#undef count
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetTextureLoc(int index)
{
	if (index < 0) {
		index = 0;
	}
	if (index > 0xFF) {
		index = 0xFF;
	}
	m_textureLocIndex = static_cast<unsigned char>(index);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(index));
	gWmMenuWorkA = index;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GXSetTexCoordGen(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800ea00c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMenuPcs::GetMaxAnimWait()
{
	return FLOAT_8032ee18;
}

/*
 * --INFO--
 * PAL Address: 0x800e9c8c
 * PAL Size: 896b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::BindMcObj()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	for (int i = 0; i < 4; i++) {
		EffectInfo* const effectA = &m_effectWork[i + 0x11];
		if (effectA->m_partNo >= 0) {
			PartMng.pppDeletePart(effectA->m_partNo);
			effectA->m_partNo = -1;
			effectA->m_slotNo = -1;
			effectA->m_effectNo = -1;
		}

		EffectInfo* const effectB = effectA + 4;
		if (effectB->m_partNo >= 0) {
			PartMng.pppDeletePart(effectB->m_partNo);
			effectB->m_partNo = -1;
			effectB->m_slotNo = -1;
			effectB->m_effectNo = -1;
		}
	}

	const float kOne = FLOAT_803313e8;
	for (int i = 0; i < 4; i++) {
		unsigned int* charaState = reinterpret_cast<unsigned int*>(m_wmCharaState) + i * 0x12;
		const int modelNo = static_cast<int>(charaState[3]);

		if (modelNo != 0) {
			unsigned char createParam[0x6C];
			*reinterpret_cast<int*>(createParam + 0x40) = -1;
			*reinterpret_cast<int*>(createParam + 0x30) = -1;
			createParam[0x34] = 0;
			createParam[0x35] = 1;
			*reinterpret_cast<int*>(createParam + 0x38) = 0;
			createParam[0x36] = 0;
			*reinterpret_cast<int*>(createParam + 0x3C) = 30;
			*reinterpret_cast<int*>(createParam + 0x44) = 0;
			*reinterpret_cast<short*>(createParam + 0x48) = 0;
			createParam[0x4A] = 0;
			createParam[0x4B] = 0;
			*reinterpret_cast<unsigned int*>(createParam + 0x00) = 0;
			*reinterpret_cast<unsigned int*>(createParam + 0x04) = 0;
			*reinterpret_cast<unsigned int*>(createParam + 0x08) = 0;
			*reinterpret_cast<unsigned int*>(createParam + 0x0C) = 0;
			*reinterpret_cast<unsigned int*>(createParam + 0x10) = 0;
			*reinterpret_cast<unsigned int*>(createParam + 0x14) = 0;
			*reinterpret_cast<unsigned int*>(createParam + 0x18) = 0;
			*reinterpret_cast<unsigned int*>(createParam + 0x1C) = 0;
			*reinterpret_cast<unsigned int*>(createParam + 0x20) = 0;
			*reinterpret_cast<float*>(createParam + 0x24) = FLOAT_803313e8;
			*reinterpret_cast<float*>(createParam + 0x28) = FLOAT_803313e8;
			createParam[0x2C] = 0;

			const int slot = i + 0x11;
			EffectInfo* effect = &m_effectWork[slot];
			if (slot == 5 && modelNo + 0x16 < 0x13) {
				effect++;
			} else if (i + 0x11 >= 0x11 && i + 0x11 <= 0x14 && modelNo + 0x16 > 0x19) {
				effect += 4;
			}

			const int group = (effect->m_effectNo = modelNo + 0x16) > 100;
			CGObject* const object = &effect->m_object;
			effect->m_slotNo = i + 0x11;
			object->Create();
			object->m_charaModelHandle = m_wm.m_handles[slot];
			*reinterpret_cast<void**>(createParam + 0x18) = object;
			*reinterpret_cast<void**>(createParam + 0x14) = object;
			effect->m_partNo =
			    PartMng.pppCreate(group, modelNo + 0x16, reinterpret_cast<PPPCREATEPARAM*>(createParam), 1);
		}

		const unsigned int flags = charaState[0xA];
		int weaponModel;
		if ((flags & 1) != 0) {
			weaponModel = 0;
		} else if ((flags & 2) != 0) {
			weaponModel = 1;
		} else if ((flags & 4) != 0) {
			weaponModel = 2;
		} else if ((flags & 8) != 0) {
			weaponModel = 3;
		} else if ((flags & 0x10) != 0) {
			weaponModel = 4;
		}

		unsigned char createParam[0x6C];
		*reinterpret_cast<int*>(createParam + 0x40) = -1;
		*reinterpret_cast<int*>(createParam + 0x30) = -1;
		createParam[0x34] = 0;
		createParam[0x35] = 1;
		*reinterpret_cast<int*>(createParam + 0x38) = 0;
		createParam[0x36] = 0;
		*reinterpret_cast<int*>(createParam + 0x3C) = 30;
		*reinterpret_cast<int*>(createParam + 0x44) = 0;
		*reinterpret_cast<short*>(createParam + 0x48) = 0;
		createParam[0x4A] = 0;
		createParam[0x4B] = 0;
		*reinterpret_cast<unsigned int*>(createParam + 0x00) = 0;
		*reinterpret_cast<unsigned int*>(createParam + 0x04) = 0;
		*reinterpret_cast<unsigned int*>(createParam + 0x08) = 0;
		*reinterpret_cast<unsigned int*>(createParam + 0x0C) = 0;
		*reinterpret_cast<unsigned int*>(createParam + 0x10) = 0;
		*reinterpret_cast<unsigned int*>(createParam + 0x14) = 0;
		*reinterpret_cast<unsigned int*>(createParam + 0x18) = 0;
		*reinterpret_cast<unsigned int*>(createParam + 0x1C) = 0;
		*reinterpret_cast<unsigned int*>(createParam + 0x20) = 0;
		*reinterpret_cast<float*>(createParam + 0x24) = kOne;
		*reinterpret_cast<float*>(createParam + 0x28) = kOne;
		createParam[0x2C] = 0;

		const int slot = i + 0x11;
		EffectInfo* effect = &m_effectWork[slot];
		if (slot == 5 && weaponModel + 0x1A < 0x13) {
			effect++;
		} else if (i + 0x11 >= 0x11 && i + 0x11 <= 0x14 && weaponModel + 0x1A > 0x19) {
			effect += 4;
		}

		const int group = (effect->m_effectNo = weaponModel + 0x1A) > 100;
		CGObject* const object = &effect->m_object;
		effect->m_slotNo = i + 0x11;
		object->Create();
		object->m_charaModelHandle = m_wm.m_handles[slot];
		*reinterpret_cast<void**>(createParam + 0x18) = object;
		*reinterpret_cast<void**>(createParam + 0x14) = object;
		effect->m_partNo =
		    PartMng.pppCreate(group, weaponModel + 0x1A, reinterpret_cast<PPPCREATEPARAM*>(createParam), 1);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e9ba0
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawFilter(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SetAttrFmt(static_cast<CMenuPcs::FMT>(2));

	GXColor color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(-1));
	_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(5), static_cast<_GXLogicOp>(1));

	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc);
	GXPosition3f32(FLOAT_803313e0, FLOAT_803313dc, FLOAT_803313dc);
	GXPosition3f32(FLOAT_803313e0, FLOAT_803313e4, FLOAT_803313dc);
	GXPosition3f32(FLOAT_803313dc, FLOAT_803313e4, FLOAT_803313dc);
}

/*
 * --INFO--
 * PAL Address: 0x800e9b2c
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CopyNowCaravanDat(Mc::SaveDat* outSave)
{
	MemoryCardMan.CreateMcBuff();
	MemoryCardMan.MakeSaveData();
	MemoryCardMan.DecodeData();
	memcpy(outSave, MemoryCardMan.m_saveBuffer, 0x8BD0);
	MemoryCardMan.DestroyMcBuff();
}

/*
 * --INFO--
 * PAL Address: 0x800e9aac
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetCaravanWork(Mc::SaveDat* saveDat)
{
	MemoryCardMan.CreateMcBuff();
	memcpy(MemoryCardMan.m_saveBuffer, saveDat, 0x8BD0);
	Game.LoadInit();
	MemoryCardMan.SetLoadData();
	Game.LoadFinished();
	MemoryCardMan.DestroyMcBuff();
}

/*
 * --INFO--
 * PAL Address: 0x800e9904
 * PAL Size: 424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetSameCharaData(Mc::SaveDat* source, Mc::SaveDat* target, int memberIndex, int strictMode)
{
	unsigned char* src = reinterpret_cast<unsigned char*>(source);
	unsigned char* const dst = reinterpret_cast<unsigned char*>(target);

	if (strictMode == 0) {
		unsigned char* const targetHeader = dst + memberIndex * 0x9C0;
		unsigned int s0 = *reinterpret_cast<unsigned int*>(src + 0x13D0);
		unsigned int t0 = *reinterpret_cast<unsigned int*>(targetHeader + 0x1D98);
		unsigned int s1 = *reinterpret_cast<unsigned int*>(src + 0x13D4);
		unsigned int t1 = *reinterpret_cast<unsigned int*>(targetHeader + 0x1D9C);
		unsigned int diff = (s0 ^ t0) | (s1 ^ t1);
		if (diff != 0 ||
		    *reinterpret_cast<unsigned int*>(src + 0x13D8) != *reinterpret_cast<unsigned int*>(targetHeader + 0x1DA0)) {
			return -2;
		}
	}

	unsigned int result = 0;
	const int cmpOffset = memberIndex * 0x9C0 + 0x1D94;
	for (int count = 4; count != 0; count--) {
		if (*reinterpret_cast<int*>(src + 0x1A84) != 0) {
			if (strictMode == 0) {
				if (src[0x1D90] != 0 &&
				    *reinterpret_cast<unsigned int*>(src + 0x1D94) == *reinterpret_cast<unsigned int*>(dst + cmpOffset)) {
					break;
				}
			} else if (src[0x1D91] != 0 &&
			           *reinterpret_cast<unsigned int*>(src + 0x1D94) == *reinterpret_cast<unsigned int*>(dst + cmpOffset)) {
				unsigned int e0 = *reinterpret_cast<unsigned int*>(src + 0x1D98) ^ *reinterpret_cast<unsigned int*>(dst + 0x13D0);
				unsigned int e1 = *reinterpret_cast<unsigned int*>(src + 0x1D9C) ^ *reinterpret_cast<unsigned int*>(dst + 0x13D4);
				if ((e0 | e1) == 0 &&
				    *reinterpret_cast<unsigned int*>(src + 0x1DA0) == *reinterpret_cast<unsigned int*>(dst + 0x13D8)) {
					break;
				}
			}
		}
		result++;

		if (*reinterpret_cast<int*>(src + 0x2444) != 0) {
			if (strictMode == 0) {
				if (src[0x2750] != 0 &&
				    *reinterpret_cast<unsigned int*>(src + 0x2754) == *reinterpret_cast<unsigned int*>(dst + cmpOffset)) {
					break;
				}
			} else if (src[0x2751] != 0 &&
			           *reinterpret_cast<unsigned int*>(src + 0x2754) == *reinterpret_cast<unsigned int*>(dst + cmpOffset)) {
				unsigned int e0 = *reinterpret_cast<unsigned int*>(src + 0x2758) ^ *reinterpret_cast<unsigned int*>(dst + 0x13D0);
				unsigned int e1 = *reinterpret_cast<unsigned int*>(src + 0x275C) ^ *reinterpret_cast<unsigned int*>(dst + 0x13D4);
				if ((e0 | e1) == 0 &&
				    *reinterpret_cast<unsigned int*>(src + 0x2760) == *reinterpret_cast<unsigned int*>(dst + 0x13D8)) {
					break;
				}
			}
		}
		result++;

		src += 0x1380;
	}

	if (strictMode == 0) {
		if (static_cast<int>(result) < 8) {
			return result;
		}
		return -1;
	}

	return (static_cast<int>(result) < 8) - 4;
}

/*
 * --INFO--
 * PAL Address: 0x800e98c4
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CheckSameMcFormatID(Mc::SaveDat* lhs, Mc::SaveDat* rhs)
{
	unsigned char* const a = reinterpret_cast<unsigned char*>(lhs);
	unsigned char* const b = reinterpret_cast<unsigned char*>(rhs);
	unsigned int lhs0 = *reinterpret_cast<unsigned int*>(a + 0x13D0);
	unsigned int rhs0 = *reinterpret_cast<unsigned int*>(b + 0x13D0);
	unsigned int lhs1 = *reinterpret_cast<unsigned int*>(a + 0x13D4);
	unsigned int rhs1 = *reinterpret_cast<unsigned int*>(b + 0x13D4);
	unsigned int diff = (lhs0 ^ rhs0) | (lhs1 ^ rhs1);
	if (diff == 0 && *reinterpret_cast<unsigned int*>(a + 0x13D8) == *reinterpret_cast<unsigned int*>(b + 0x13D8)) {
		return 1;
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 520b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::IsAsyncCharaLoadFinish()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int ready = 1;
	int loadedCount = 0;
	for (int i = 0; i < 4; i++) {
		CCharaPcs::CHandle* const handle = GetWmCharaHandles(this)[i];
		if (handle == 0 || !handle->IsModelLoaded(1)) {
			ready = 0;
			break;
		}
		loadedCount++;
	}
	if (ready != 0) {
		const unsigned char* const selectData = m_wm.m_charaSelectData;
		if (selectData != 0) {
			for (int i = 0; i < 4; i++) {
				if (selectData[i * 0x10 + 0xB] != 0 && selectData[i * 0x10 + 0xC] == 0) {
					ready = 0;
					break;
				}
			}
		}
	}
	gWmMenuWorkB = loadedCount;
	gWmMenuWorkA = ready;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
McCtrl::McCtrl()
{
	Init();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
McCtrl::~McCtrl()
{
	return;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::Init()
{
	m_previousState = 0;
	m_state = 0;
	m_cardChannel = 0;
	m_lastResult = 0;
	m_saveIndex = 0;
	m_iteration = 0;
	m_createFlag = 0;
	m_userBuffer = 0;
	m_serialLo = 0;
	m_serialHi = 0;
}


/*
 * --INFO--
 * PAL Address: 0x800e9348
 * PAL Size: 1404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::LoadMcList()
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		memset(MenuPcs.m_wmCharaState, 0, kMcListEntrySize * kMcListCount);
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 4;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				return (m_lastResult == -5) ? -4 : -3;
			}
			m_state = 4;
		}
		break;

	case 4:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult < 0) {
			if (m_lastResult == -4) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;
			} else {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
			}
			if (m_lastResult == -5) {
				return -4;
			}
		} else if (MemoryCardMan.IsBrokenFile()) {
			const int closeResult = MemoryCardMan.McClose();
			if (closeResult != 0) {
				m_lastResult = closeResult;
				m_state = -1;
			} else {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				struct McListEntry {
					int m_words[11];
					char m_name[0x15];
					char m_byte41;
					char m_byte42;
					char m_byte43;
				};
				McListEntry entry;
				memset(&entry, 0, 0x48);
				entry.m_byte42 = 1;
				for (int i = 0; i < kMcListCount; i++) {
					*reinterpret_cast<McListEntry*>(MenuPcs.m_wmCharaState + i * kMcListEntrySize) = entry;
				}
				m_state = 7;
			}
		} else {
			m_state = 5;
		}
		break;

	case 5: {
		unsigned long long serial;
		if (CARDGetSerialNo(m_cardChannel, &serial) != 0) {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -1;
		}
		m_serialHi = static_cast<unsigned int>(serial);
		m_serialLo = static_cast<unsigned int>(serial >> 32);
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McRead(0, 0xA000, m_iteration * 0xA000 + 0x4000);
		m_state = 6;
		break;
	}

	case 6:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				MemoryCardMan.DecodeData();
				const int iteration = m_iteration;
				m_iteration = iteration + 1;
				SetListDat(iteration, 0);
				if (m_iteration < 4) {
					m_state = 5;
				} else {
					const int closeResult = MemoryCardMan.McClose();
					if (closeResult != 0) {
						m_lastResult = closeResult;
						m_state = -1;
					} else {
						MemoryCardMan.McUnmount(m_cardChannel);
						MemoryCardMan.DestroyMcBuff();
						m_state = 7;
					}
				}
			}
		}
		break;

	case 7:
		break;
	}

	if (m_state == -1) {
		return -1;
	}
	int result = 0;
	if (m_state == 7) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800e902c
 * PAL Size: 796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetListDat(int slot, int clearPlayTime)
{
	unsigned char entry[kMcListEntrySize];
	unsigned char* const save = reinterpret_cast<unsigned char*>(MemoryCardMan.m_saveBuffer);
	memset(entry, 0, sizeof(entry));

	if (*reinterpret_cast<signed char*>(save + 0x10C0) != 0) {
		const int formatMatch = memcmp(save + 0x0C, DAT_8032E8A8, 4);
		const unsigned char crcOk = MemoryCardMan.ChkCrc(0);
		if (crcOk == 1 && formatMatch == 0) {
			if (clearPlayTime == 0) {
				*reinterpret_cast<unsigned int*>(entry + 0x08) = *reinterpret_cast<unsigned int*>(save + 0x20);
			} else {
				*reinterpret_cast<unsigned int*>(entry + 0x08) = 0;
			}
			memcpy(entry + 0x00, save + 0x8AD0, 8);
			*reinterpret_cast<unsigned int*>(entry + 0x0C) = *reinterpret_cast<unsigned int*>(save + 0x24);
			*reinterpret_cast<unsigned int*>(entry + 0x10) = *reinterpret_cast<unsigned int*>(save + 0x28);
			*reinterpret_cast<unsigned int*>(entry + 0x14) = *reinterpret_cast<unsigned int*>(save + 0x2C);

			unsigned char* base = save;
			for (int i = 0; i < 4; i++) {
				unsigned char* party = base + reinterpret_cast<int*>(save + 0x30)[i] * 0x9C0;
				if (*reinterpret_cast<int*>(party + 0x1A84) == 0) {
					reinterpret_cast<int*>(save + 0x30)[i] = -1;
				}
				if (party[0x1D90] != 0) {
					reinterpret_cast<int*>(save + 0x30)[i] = -1;
				}
			}

			*reinterpret_cast<unsigned int*>(base + 0x1C) = MemoryCardMan.CalcCrc(reinterpret_cast<Mc::SaveDat*>(base));

			for (int i = 0; i < 4; i++) {
				if (reinterpret_cast<int*>(save + 0x30)[i] >= 0) {
					reinterpret_cast<unsigned int*>(entry + 0x18)[i] = *reinterpret_cast<unsigned short*>(save + reinterpret_cast<int*>(save + 0x30)[i] * 0x9C0 + 0x14D0);
				} else {
					reinterpret_cast<unsigned int*>(entry + 0x18)[i] = -1;
				}
			}
			*reinterpret_cast<unsigned int*>(entry + 0x28) = *reinterpret_cast<unsigned int*>(save + 0xB8);
			memcpy(entry + 0x2C, save + 0x10C0, 0x10);
			entry[0x41] = 1;
		} else {
			entry[0x42] = 1;
		}
	} else {
		entry[0x42] = 0;
		entry[0x41] = 0;
	}

	unsigned char* const dst = MenuPcs.m_wmCharaState + slot * kMcListEntrySize;
	unsigned int* const dstWords = reinterpret_cast<unsigned int*>(dst);
	unsigned int* const entryWords = reinterpret_cast<unsigned int*>(entry);
	struct Quad16 { unsigned int w[4]; };
	*reinterpret_cast<unsigned long long*>(dst) = *reinterpret_cast<unsigned long long*>(entry);
	dstWords[2] = entryWords[2];
	dstWords[3] = entryWords[3];
	dstWords[4] = entryWords[4];
	dstWords[5] = entryWords[5];
	*reinterpret_cast<Quad16*>(dst + 0x18) = *reinterpret_cast<Quad16*>(entry + 0x18);
	dstWords[10] = entryWords[10];
	struct Tail15 { unsigned char b[0x15]; };
	*reinterpret_cast<Tail15*>(dst + 0x2C) = *reinterpret_cast<Tail15*>(entry + 0x2C);
	dst[0x41] = entry[0x41];
	dst[0x42] = entry[0x42];
	dst[0x43] = entry[0x43];
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetBrokenFile(int isBroken)
{
	m_createFlag = isBroken;
	if (isBroken != 0) {
		m_lastResult = -1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e8738
 * PAL Size: 2292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::SaveDat()
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 7;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
				return -3;
			}
			m_state = 7;
		}
		break;

	case 7:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult == -4) {
			m_state = 10;
		} else if (m_lastResult == -5) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			return -4;
		} else if (MemoryCardMan.IsBrokenFile()) {
			m_state = 8;
		} else {
			MemoryCardMan.CreateMcBuff();
			m_state = 0x0C;
		}
		break;

	case 8:
		MemoryCardMan.McDelFile(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 9;
		break;

	case 9:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				struct McListEntry {
					int m_words[11];
					char m_name[0x15];
					char m_byte41;
					char m_byte42;
					char m_byte43;
				};
				McListEntry entry;
				memset(&entry, 0, 0x48);
				for (int i = 0; i < kMcListCount; i++) {
					*reinterpret_cast<McListEntry*>(MenuPcs.m_wmCharaState + i * kMcListEntrySize) = entry;
				}
				m_state = 10;
			}
		}
		break;

	case 10:
		m_createFlag = 1;
		MemoryCardMan.McCreate(m_cardChannel);
		m_state = 0x0B;
		break;

	case 0x0B:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				m_state = 0x10;
			}
		}
		break;

	case 0x0C:
		m_lastResult = MemoryCardMan.McGetStat(m_cardChannel);
		if (m_lastResult != 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = -1;
			if (m_lastResult == -5) {
				return -4;
			}
		} else {
			m_state = 0x0D;
		}
		break;

	case 0x0D:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.SetMcIconImage();
		MemoryCardMan.McWrite(0, 0x4000, 0);
		m_state = 0x0E;
		break;

	case 0x0E:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				m_state = 0x0F;
			}
		}
		break;

	case 0x0F:
		m_lastResult = MemoryCardMan.McSetStat(m_cardChannel);
		if (m_lastResult != 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			if (m_lastResult == -5) {
				return -4;
			}
		} else {
			m_state = 0x12;
		}
		break;

	case 0x10:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McWrite(0, 0xA000, m_iteration * 0xA000 + 0x4000);
		m_state = 0x11;
		break;

	case 0x11:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_iteration = m_iteration + 1;
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else if (m_iteration < 4) {
				m_state = 0x10;
			} else {
				m_state = 0x0C;
			}
		}
		break;

	case 0x12: {
		unsigned long long serial;
		if (CARDGetSerialNo(m_cardChannel, &serial) == 0) {
			if (static_cast<unsigned char>(Game.m_gameWork.m_mcHasSerial) == 0) {
				Game.m_gameWork.m_mcSerial1 = static_cast<unsigned int>(serial);
				Game.m_gameWork.m_mcSerial0 = static_cast<unsigned int>(serial >> 32);
				Game.m_gameWork.m_mcRandom = Math.Rand(0x7FFFFFFF);
				Game.m_gameWork.m_mcHasSerial = 1;
			}
			m_serialLo = static_cast<unsigned int>(serial);
			m_serialHi = static_cast<unsigned int>(serial >> 32);
			MemoryCardMan.CreateMcBuff();
			if (m_userBuffer == 0) {
				MemoryCardMan.MakeSaveData();
			} else {
				memcpy(MemoryCardMan.m_saveBuffer, m_userBuffer, 0x8BD0);
			}
			MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
			m_state = 0x13;
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -1;
		}
		break;
	}

	case 0x13:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				m_state = -1;
				if (m_lastResult == -5) {
					MemoryCardMan.McClose();
					MemoryCardMan.McUnmount(m_cardChannel);
					MemoryCardMan.DestroyMcBuff();
					return -4;
				}
			} else {
				MemoryCardMan.DecodeData();
				SetListDat(m_saveIndex, 1);
				MenuPcs.BindMcObj(m_saveIndex);
				m_state = 0x14;
			}

			const int closeResult = MemoryCardMan.McClose();
			if (closeResult != 0) {
				m_lastResult = closeResult;
				m_state = -1;
			} else {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
			}
		}
		break;

	case 0x14:
		break;
	}

	if (m_state == -1) {
		return -1;
	}
	int result = 0;
	if (m_state == 0x14) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800e8300
 * PAL Size: 1080b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::LoadDat()
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 4;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;
				if (m_lastResult == -5) {
					return -4;
				}
				return -3;
			}
			m_state = 4;
		}
		break;

	case 4:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult < 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			if (m_lastResult == -4) {
				m_state = 7;
			} else if (m_lastResult == -5) {
				m_state = -1;
				return -4;
			} else {
				m_state = -1;
			}
		} else {
			m_state = 5;
		}
		break;

	case 5: {
		unsigned int serialLo = 0;
		unsigned int serialHi = 0;
		int __p9 = serialLo;
		if (CARDGetSerialNo(m_cardChannel, reinterpret_cast<unsigned long long*>(&__p9)) != 0) {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -1;
		}
		m_serialHi = serialHi;
		m_serialLo = serialLo;
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McRead(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 6;
		break;
	}

	case 6:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				MemoryCardMan.DecodeData();
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				if (!(m_userBuffer == 0)) {
					memcpy(m_userBuffer, MemoryCardMan.m_saveBuffer, 0x8BD0);
					MemoryCardMan.CalcSaveDatHpMax(reinterpret_cast<Mc::SaveDat*>(m_userBuffer));
				} else {
					Game.LoadInit();
					MemoryCardMan.SetLoadData();
					Game.LoadFinished();
				}
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;
			}
		}
		break;

	case 7:
		break;
	}

	int result;
	if (m_state == -1) {
		result = -1;
	} else if (m_state == 7) {
		result = 1;
	} else {
		result = 0;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800e80f0
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::Format(int unmountAfter)
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;
	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult == -6 || m_lastResult == -0xD || m_lastResult == 0) {
				m_state = 2;
			} else {
				if (m_lastResult == -5) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
					m_state = -1;
					return -2;
				}
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				m_state = -1;
			}
		}
		break;
	case 2:
		MemoryCardMan.McFormat(m_cardChannel);
		m_state = 3;
		break;
	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -2;
				}
			} else {
				if (unmountAfter != 0) {
					MemoryCardMan.McUnmount(m_cardChannel);
				}
				m_state = 4;
			}
		}
		break;
	case 4:
		break;
	}

	int result;
	if (m_state == -1) {
		result = -1;
	} else if (m_state == 4) {
		result = 1;
	} else {
		result = 0;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800e7dc8
 * PAL Size: 808b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::ChkEmpty(int param_2)
{
	int filesFree;
	int bytesFree[3];

	if (m_state < 0)
	{
		return -1;
	}

	m_previousState = m_state;

	int state = m_state;

	switch (state)
	{
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;
	case 1:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult == 0)
			{
				m_state = 2;
			}
			else
			{
				if (m_lastResult == -0x0D)
				{
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
					m_state = -1;
					return -3;
				}

				if (m_lastResult == -6)
				{
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
					m_state = -1;
					return -4;
				}

				if (m_lastResult == -5)
				{
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
					m_state = -1;
					return -5;
				}

				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
				m_state = -1;
			}
		}
		break;
	case 2:
	{
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);

		if (m_lastResult < 0)
		{
			if (m_lastResult == -4)
			{
				if (param_2 == 0)
				{
					m_state = 3;
				}
				else
				{
					MemoryCardMan.McUnmount(m_cardChannel);
					m_state = -1;
					return -6;
				}
			}
			else
			{
				if (m_lastResult == -5)
				{
					MemoryCardMan.McUnmount(m_cardChannel);
					m_state = -1;
					return -5;
				}

				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
			}
		}
		else
		{
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = 4;
		}
		break;
	}
	case 3:
		{
			m_lastResult = MemoryCardMan.McFreeBlocks(m_cardChannel, bytesFree, &filesFree);
			MemoryCardMan.McUnmount(m_cardChannel);

			if (m_lastResult < 0)
			{
				if (m_lastResult == -5)
				{
					m_state = -1;
					return -5;
				}

				m_state = -1;
			}
			else
			{
				if (filesFree == 0)
				{
					m_state = -1;
					return -2;
				}

				if (bytesFree[0] < 0x2C000)
				{
					m_state = -1;
					return -2;
				}

				m_state = 4;
			}
		}
		break;
	case 4:
		break;
	}

	int result;
	if (m_state == -1)
	{
		result = -1;
	}
	else if (m_state == 4)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800e7d4c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::ChkConnect(int chan)
{
	int result = MemoryCardMan.McChkConnect(chan);

	if (result == 0)
	{
		result = 1;
	}
	else if (result == -1)
	{
		result = -3;
	}
	else if (result == -2)
	{
		result = -6;
	}
	else if (result == -3)
	{
		result = -2;
	}
	else if (result == -4)
	{
		result = -5;
	}
	else
	{
		result = -1;
	}

	return result;
}


/*
 * --INFO--
 * PAL Address: 0x800e78f8
 * PAL Size: 1108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::ChkNowData()
{
	unsigned int serialLo;
	unsigned int serialHi;

	if (m_state < 0)
	{
		return -999;
	}

	m_previousState = m_state;

	switch (m_state)
	{
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();
			int iVar3 = m_lastResult;

			if (iVar3 < 0)
			{
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;

				if (iVar3 == -6)
				{
					m_state = 2;
				}
				else
				{
					if (iVar3 == -0x0D)
					{
						m_state = -1;
						return -0x0D;
					}

					if (iVar3 == -5)
					{
						m_state = -1;
						return -5;
					}

					m_state = -1;
				}
			}
			else
			{
				m_state = 4;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult != 0)
			{
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;

				unsigned int uVar1 = __cntlzw(static_cast<unsigned int>(-5 - m_lastResult));
				return static_cast<int>(uVar1 >> 5) - 6;
			}

			m_state = 4;
		}
		break;

	case 4:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);

		if (m_lastResult < 0)
		{
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();

			if (m_lastResult == -4)
			{
				m_state = -1;
				return -4;
			}

			if (m_lastResult == -5)
			{
				m_state = -1;
				return -5;
			}

			m_state = -1;
		}
		else
		{
			m_state = 5;
		}
		break;

	case 5:
		if (CARDGetSerialNo(m_cardChannel, (unsigned long long*)&serialLo) != 0)
		{
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -999;
		}

		m_serialHi = serialHi;
		m_serialLo = serialLo;

		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McRead(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 6;
		break;

	case 6:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult < 0)
			{
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;

				if (m_lastResult == -5)
				{
					return -5;
				}
			}
			else
			{
				MemoryCardMan.DecodeData();

				int r = MemoryCardMan.McClose();
				if (r == 0)
				{
					MemoryCardMan.McUnmount(m_cardChannel);

					if ((*(unsigned int*)(MemoryCardMan.m_saveBuffer + 0x13D4) == Game.m_gameWork.m_mcSerial1 &&
						 *(unsigned int*)(MemoryCardMan.m_saveBuffer + 0x13D0) == Game.m_gameWork.m_mcSerial0) &&
						(*(unsigned int*)(MemoryCardMan.m_saveBuffer + 0x13D8) == Game.m_gameWork.m_mcRandom))
					{
						r = 1;
					}
					else
					{
						r = -1000;
					}

					MemoryCardMan.DestroyMcBuff();
					m_state = 7;
					return r;
				}

				m_lastResult = r;
				m_state = -1;
			}
		}
		break;

	case 7:
		break;
	}

	if (m_state == -1)
	{
		return -999;
	}
	int result = 0;
	if (m_state == 7)
	{
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800e7430
 * PAL Size: 1224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::SaveDataBuffer(char* buffer)
{
	if (m_state < 0) {
		return -1000;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0xD) {
					m_state = -1;
					return -13;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -5;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 7;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				return (m_lastResult == -5) ? -5 : -6;
			}
			m_state = 7;
		}
		break;

	case 7:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult == -4) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			return -4;
		} else if (m_lastResult == -5) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			return -5;
		} else {
			MemoryCardMan.CreateMcBuff();
			m_state = 0x10;
		}
		break;

	case 0x10: {
		unsigned long long serial;
		if (CARDGetSerialNo(m_cardChannel, &serial) == 0) {
			m_serialHi = static_cast<unsigned int>(serial);
			m_serialLo = static_cast<unsigned int>(serial >> 32);
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -999;
		}

		unsigned char* const save = reinterpret_cast<unsigned char*>(MemoryCardMan.m_saveBuffer);
		memcpy(save, buffer, 0x8BD0);

		unsigned char* entry = save + *reinterpret_cast<int*>(save + 0x30) * 0x9C0;
		if (*reinterpret_cast<int*>(entry + 0x1A84) == 0) {
			*reinterpret_cast<int*>(save + 0x30) = -1;
		}
		if (entry[0x1D90] != 0) {
			*reinterpret_cast<int*>(save + 0x30) = -1;
		}
		entry = save + *reinterpret_cast<int*>(save + 0x34) * 0x9C0;
		if (*reinterpret_cast<int*>(entry + 0x1A84) == 0) {
			*reinterpret_cast<int*>(save + 0x34) = -1;
		}
		if (entry[0x1D90] != 0) {
			*reinterpret_cast<int*>(save + 0x34) = -1;
		}
		entry = save + *reinterpret_cast<int*>(save + 0x38) * 0x9C0;
		if (*reinterpret_cast<int*>(entry + 0x1A84) == 0) {
			*reinterpret_cast<int*>(save + 0x38) = -1;
		}
		if (entry[0x1D90] != 0) {
			*reinterpret_cast<int*>(save + 0x38) = -1;
		}
		entry = save + *reinterpret_cast<int*>(save + 0x3C) * 0x9C0;
		if (*reinterpret_cast<int*>(entry + 0x1A84) == 0) {
			*reinterpret_cast<int*>(save + 0x3C) = -1;
		}
		if (entry[0x1D90] != 0) {
			*reinterpret_cast<int*>(save + 0x3C) = -1;
		}

		*reinterpret_cast<unsigned int*>(save + 0x1C) = MemoryCardMan.CalcCrc(reinterpret_cast<Mc::SaveDat*>(save));
		MemoryCardMan.EncodeData();
		MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 0x11;
		break;
	}

	case 0x11:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				m_state = -1;
				if (m_lastResult == -5) {
					MemoryCardMan.McClose();
					MemoryCardMan.McUnmount(m_cardChannel);
					MemoryCardMan.DestroyMcBuff();
					return -5;
				}
			} else {
				m_state = 0x12;
			}

			const int closeResult = MemoryCardMan.McClose();
			if (!(closeResult == 0)) {
				m_lastResult = closeResult;
				m_state = -1;
			} else {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
			}
		}
		break;

	case 0x12:
		break;
	}

	if (m_state == -1) {
		return -999;
	}
	int result;
	result = 0;
	if (m_state == 0x12) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::ChkParty(char*)
{
	m_lastResult = 0;
	if (m_userBuffer == 0) {
		return;
	}

	unsigned char* const save = reinterpret_cast<unsigned char*>(m_userBuffer);
	for (int i = 0; i < 4; i++) {
		const int party = *reinterpret_cast<int*>(save + 0x30 + i * 4);
		if (party >= 0 && party < 8 && *reinterpret_cast<int*>(save + party * 0x9C0 + 0x1A84) != 0 && save[party * 0x9C0 + 0x1D90] == 0) {
			m_lastResult++;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e6b98
 * PAL Size: 2200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::EraseDat()
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 7;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
				return -3;
			}
			m_state = 7;
		}
		break;

	case 7:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult == -4) {
			m_state = 10;
		} else if (m_lastResult == -5) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			return -4;
		} else if (MemoryCardMan.IsBrokenFile()) {
			m_state = 8;
		} else {
			MemoryCardMan.CreateMcBuff();
			m_state = 0x0C;
		}
		break;

	case 8:
		MemoryCardMan.McDelFile(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 9;
		break;

	case 9:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				struct McListEntry {
					int m_words[11];
					char m_name[0x15];
					char m_byte41;
					char m_byte42;
					char m_byte43;
				};
				McListEntry entry;
				memset(&entry, 0, 0x48);
				entry.m_byte42 = 0;
				for (int i = 0; i < kMcListCount; i++) {
					int __p8 =   (int)(unsigned int)((0 + i));
					*reinterpret_cast<McListEntry*>(MenuPcs.m_wmCharaState + __p8 * kMcListEntrySize) = entry;
				}
				m_state = 10;
			}
		}
		break;

	case 10:
		m_createFlag = 1;
		MemoryCardMan.McCreate(m_cardChannel);
		m_state = 0x0B;
		break;

	case 0x0B:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				m_state = 0x10;
			}
		}
		break;

	case 0x0C:
		m_lastResult = MemoryCardMan.McGetStat(m_cardChannel);
		if (m_lastResult != 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = -1;
			if (m_lastResult == -5) {
				return -4;
			}
		} else {
			m_state = 0x0D;
		}
		break;

	case 0x0D:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.SetMcIconImage();
		MemoryCardMan.McWrite(0, 0x4000, 0);
		m_state = 0x0E;
		break;

	case 0x0E:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				m_state = 0x0F;
			}
		}
		break;

	case 0x0F:
		m_lastResult = MemoryCardMan.McSetStat(m_cardChannel);
		if (m_lastResult != 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			if (m_lastResult == -5) {
				return -4;
			}
		} else {
			m_state = 0x12;
		}
		break;

	case 0x10:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McWrite(0, 0xA000, m_iteration * 0xA000 + 0x4000);
		m_state = 0x11;
		break;

	case 0x11:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_iteration = m_iteration + 1;
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				const int finishedSlot = m_iteration - 1;
				SetListDat(finishedSlot, 1);
				MenuPcs.BindMcObj(m_iteration - 1);
				if (m_iteration < 4) {
					m_state = 0x10;
				} else {
					m_state = 0x0C;
				}
			}
		}
		break;

	case 0x12: {
		unsigned long long serial;
		if (CARDGetSerialNo(m_cardChannel, &serial) == 0) {
			m_serialHi = static_cast<unsigned int>(serial);
			m_serialLo = static_cast<unsigned int>(serial >> 32);
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -1;
		}
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 0x13;
		break;
	}

	case 0x13:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				m_state = -1;
				if (m_lastResult == -5) {
					MemoryCardMan.McClose();
					MemoryCardMan.McUnmount(m_cardChannel);
					MemoryCardMan.DestroyMcBuff();
					return -4;
				}
			} else {
				MemoryCardMan.DecodeData();
				SetListDat(m_saveIndex, 1);
				MenuPcs.BindMcObj(m_saveIndex);
				m_state = 0x14;
			}

			const int closeResult = MemoryCardMan.McClose();
			if (closeResult != 0) {
				m_lastResult = closeResult;
				m_state = -1;
			} else {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
			}
		}
		break;

		case 0x14:
		break;
	}

	if (m_state == -1) {
		return -1;
	}
	int result = 0;
	if (m_state == 0x14) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::GetDno()
{
	gWmMenuWorkA = m_cardChannel;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::GetSerial()
{
	gWmMenuWorkA = static_cast<int>(m_serialLo);
	gWmMenuWorkB = static_cast<int>(m_serialHi);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetDataBuff(char* buffer)
{
	m_userBuffer = buffer;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::GetSlot()
{
	gWmMenuWorkA = m_saveIndex;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetDno(int channel)
{
	m_cardChannel = channel;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetSlot(int slot)
{
	m_saveIndex = slot;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::AlphaNormal()
{
	FLOAT_8032ee18 = FLOAT_803313dc;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::AlphaAdd()
{
	FLOAT_8032ee18 = FLOAT_803315d4;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetFontWorld()
{
	gWmMenuWorkA = static_cast<int>(reinterpret_cast<unsigned int>(m_fonts[1]));
}
