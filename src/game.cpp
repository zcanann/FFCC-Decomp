#include "ffcc/game.h"

#include "ffcc/ptrarray.h"
#include "ffcc/partyobj.h"
#include "ffcc/system.h"
#include "ffcc/vector.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_minigame.h"
#include "ffcc/p_system.h"
#include "ffcc/p_game.h"
#include "ffcc/p_gba.h"
#include "ffcc/map.h"
#include "ffcc/p_sound.h"
#include "ffcc/sound.h"
#include "ffcc/wind.h"
#include "ffcc/graphic.h"
#include "ffcc/file.h"
#include "ffcc/partMng.h"
#include "ffcc/maplight.h"
#include "ffcc/chara.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/gobject.h"
#include "ffcc/linkage.h"
#include "ffcc/p_chara.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_FunnyShape.h"
#include "ffcc/p_graphic.h"
#include "ffcc/p_light.h"
#include "ffcc/p_map.h"
#include "ffcc/p_MaterialEditor.h"
#include "ffcc/p_mc.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_tina.h"
#include "ffcc/p_usb.h"

#include <string.h>

#include <dolphin/os/OSMemory.h>
#include <dolphin/os/OSRtc.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

const float kGamePartyBoundsMinInit = 1.0E+10;
const float kGamePartyBoundsMaxInit = -1.0E+10;
const float kGameZero = 0.0;
const float kGameSmallDelta = 0.001;
extern "C" {
const char s_defaultScriptName[] = "ffcc_0";
const char s_gameDebugMarker[] = "*\n";
const char s_townNameTepa[] = "Tepa";
const char s_townNameTipa[] = "Tipa";
const char sGameStageName[] = "Game";
}
extern const char s_dvd_pctscft_param_cfd_801D6054[];
extern const char s_dvd_pctscft_c_system_cfd_801D6068[];
extern const char s_dvd_pctscft_mail_tbl_cfd_801D6080[];
extern const char s_dvd_pctscft_newbattle_cfd_801D6098[];
static const char s_ParticleCallbackType0Fmt_801D60D4[] = {
    0x70, 0x64, 0x74, 0x69, 0x64, 0x3D, 0x25, 0x64, 0x20, 0x66, 0x70, 0x6E, 0x6F, 0x3D, 0x25, 0x64, 0x20, 0x69,
    0x64, 0x3D, 0x25, 0x64, 0x20, 0x66, 0x72, 0x61, 0x6D, 0x65, 0x3D, 0x25, 0x64, 0x20, 0x83, 0x70, 0x81, 0x5B,
    0x83, 0x65, 0x83, 0x42, 0x83, 0x4E, 0x83, 0x8B, 0x8D, 0xED, 0x8F, 0x9C, 0x8B, 0xD6, 0x8E, 0x7E, 0x83, 0x74,
    0x83, 0x89, 0x83, 0x4F, 0x6F, 0x6E, 0x0A, 0x00};
static const char s_ParticleCallbackType1Fmt_801D6114[] = {
    0x70, 0x64, 0x74, 0x69, 0x64, 0x3D, 0x25, 0x64, 0x20, 0x66, 0x70, 0x6E, 0x6F, 0x3D, 0x25, 0x64, 0x20, 0x69,
    0x64, 0x3D, 0x25, 0x64, 0x20, 0x66, 0x72, 0x61, 0x6D, 0x65, 0x3D, 0x25, 0x64, 0x20, 0x83, 0x70, 0x81, 0x5B,
    0x83, 0x65, 0x83, 0x42, 0x83, 0x4E, 0x83, 0x8B, 0x8E, 0xA9, 0x93, 0xAE, 0x8D, 0xED, 0x8F, 0x9C, 0x83, 0x74,
    0x83, 0x89, 0x83, 0x4F, 0x6F, 0x6E, 0x0A, 0x00};
static const char s_ParticleCallbackType3Fmt_801D6154[] = {
    0x70, 0x64, 0x74, 0x69, 0x64, 0x3D, 0x25, 0x64, 0x20, 0x66, 0x70, 0x6E, 0x6F, 0x3D, 0x25, 0x64, 0x20, 0x69,
    0x64, 0x3D, 0x25, 0x64, 0x20, 0x66, 0x72, 0x61, 0x6D, 0x65, 0x3D, 0x25, 0x64, 0x83, 0x70, 0x81, 0x5B, 0x83,
    0x65, 0x83, 0x42, 0x83, 0x4E, 0x83, 0x8B, 0x83, 0x60, 0x83, 0x83, 0x81, 0x5B, 0x83, 0x57, 0x8F, 0x49, 0x97,
    0xB9, 0x6F, 0x6E, 0x0A, 0x00};
extern const char s_gameAssetNameBlock_801D5FC0[];

enum GameAssetNameBlockOffset {
	kParticleCallbackType0Fmt = 0x114,
	kParticleCallbackType1Fmt = 0x154,
	kParticleCallbackType3Fmt = 0x194,
};

enum {
	kGameWorkDataClearSize =
	    sizeof(CGame::CGameWork) - offsetof(CGame::CGameWork, m_gameDataStartMarker),
	kGameScriptSaveDataSize = 0x800,
};

STATIC_ASSERT(kGameWorkDataClearSize == 0x13E1);

extern "C" const char s_game_cpp[];
static const char s_ScriptWillChangeMsg_801D619C[] = {
    0x83, 0x58, 0x83, 0x4E, 0x83, 0x8A, 0x83, 0x76, 0x83, 0x67, 0x82, 0xAA, 0x90, 0xD8, 0x82, 0xE8, 0x91, 0xD6,
    0x82, 0xED, 0x82, 0xE8, 0x82, 0xDC, 0x82, 0xB7, 0x0A, 0x00};
static const char s_ScriptResidentLoadedMsg_801D61B8[] = {
    0x83, 0x58, 0x83, 0x4E, 0x83, 0x8A, 0x83, 0x76, 0x83, 0x67, 0x82, 0xCC, 0x8F, 0xED, 0x92, 0x93, 0x82, 0xF0,
    0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x82, 0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42, 0x0A, 0x00};
static const char sCoreResidentLoadedMsg[] = {
    0x83, 0x54, 0x83, 0x45, 0x83, 0x93, 0x83, 0x68, 0x81, 0x45, 0x83, 0x4C, 0x83, 0x83, 0x83, 0x89, 0x81, 0x45,
    0x83, 0x70, 0x81, 0x5B, 0x83, 0x65, 0x83, 0x42, 0x83, 0x4E, 0x83, 0x8B, 0x82, 0xCC, 0x8F, 0xED, 0x92, 0x93,
    0x82, 0xF0, 0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x82, 0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42,
    0x0A, 0x00};
static const char sNewGameInitMsg[] = {
    0x2A, 0x83, 0x6A, 0x83, 0x85, 0x81, 0x5B, 0x83, 0x51, 0x81, 0x5B, 0x83, 0x80, 0x8F, 0x89, 0x8A, 0xFA, 0x89,
    0xBB, 0x82, 0xB5, 0x82, 0xDC, 0x82, 0xB7, 0x81, 0x42, 0x0A, 0x00};
static const char s_ScriptChangedMsg_801D6234[] = {
    0x83, 0x58, 0x83, 0x4E, 0x83, 0x8A, 0x83, 0x76, 0x83, 0x67, 0x82, 0xAA, 0x90, 0xD8, 0x82, 0xE8, 0x91, 0xD6,
    0x82, 0xED, 0x82, 0xE8, 0x82, 0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x0A, 0x00};
static const char sGameExecSceneFmt[] = "CGame.Exec: scene = %s\n";
static const char sGameInvalidSceneFmt[] = {
    0x83, 0x56, 0x81, 0x5B, 0x83, 0x93, 0x82, 0xAA, 0x88, 0xD9, 0x8F, 0xED, 0x82, 0xC5, 0x82, 0xB7,
    0x81, 0x42, 0x25, 0x64, 0x0A, 0x00, 0x00, 0x00};
static const char sGameDebugStageName[] = "GameDebug";
extern const char s_SN_EXIT_8032F630[];
extern const char s_SN_DUMMY_801D600C[];
extern const char s_SN_CHARA_801D6018[];
extern const char s_SN_MAP_8032F638[];
extern const char s_SN_GAME_8032F640[];
extern const char s_SN_MATERIALEDITOR_801D6024[];
extern const char s_SN_FUNNYSHAPE_801D6038[];
extern const char s_SN_PARTVIEW_801D6048[];
extern const char* s_localLangDirs[];
static const char* m_tStatus[] = {
    s_SN_EXIT_8032F630,
    s_SN_DUMMY_801D600C,
    s_SN_CHARA_801D6018,
    s_SN_MAP_8032F638,
    s_SN_GAME_8032F640,
    s_SN_MATERIALEDITOR_801D6024,
    s_SN_FUNNYSHAPE_801D6038,
    s_SN_PARTVIEW_801D6048,
    0,
};
const char* PTR_s_dvd__scft_param_cfd[] = {
    s_dvd_pctscft_param_cfd_801D6054,
    s_dvd_pctscft_c_system_cfd_801D6068,
    s_dvd_pctscft_mail_tbl_cfd_801D6080,
    s_dvd_pctscft_newbattle_cfd_801D6098,
};
float s_ratio[] = {1.35f, 1.25f, 1.1f, 1.0f};
static const char s_numNameFmt[] = "%d %s";
static const char s_nameJoinFmt[] = "%s%s%s";
static const char s_nameSep[] = " ";
static const char s_nameNoSep[4] = "";

struct CFlatDataTableEntryView
{
    int m_numEntries;
    char** m_strings;
    char* m_stringBuf;
};

struct CFlatDataView
{
    int m_dataCount;
    unsigned char _pad[0x68 - 4];
    int m_tableCount;
    CFlatDataTableEntryView m_tabl[8];
};

struct GameSoundLayout
{
    u8 m_pad[0x22BC];
    int m_seMaxVolume;
};

static inline GameSoundLayout& GameSoundData(CSound& sound)
{
    return *reinterpret_cast<GameSoundLayout*>(&sound);
}

CGame Game;

// Uninitialized
static float sMapObjRotationAngle;
static s8 sMapObjRotationInitialized;

/*
 * --INFO--
 * PAL Address: 0x8001439c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGBaseObj::GetCID()
{
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800161f0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapLightHolder* CPtrArray<CMapLightHolder*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CGame::CGame()
    : m_partyMinX(kGamePartyBoundsMinInit)
    , m_partyMinY(kGamePartyBoundsMinInit)
    , m_partyMinZ(kGamePartyBoundsMinInit)
    , m_partyMaxX(kGamePartyBoundsMaxInit)
    , m_partyMaxY(kGamePartyBoundsMaxInit)
    , m_partyMaxZ(kGamePartyBoundsMaxInit)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGame::~CGame()
{
}

/*
 * --INFO--
 * PAL Address: 0x8001600c
 * PAL Size: 476b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Init()
{
    switch (OSSetProgressiveMode()) {
    case 3:
        m_gameWork.m_languageId = 5;
        break;

    case 1:
        m_gameWork.m_languageId = 2;
        break;

    case 2:
        m_gameWork.m_languageId = 4;
        break;

    case 4:
        m_gameWork.m_languageId = 3;
        break;

    default:
        m_gameWork.m_languageId = 1;
        break;
    }

    CameraPcs.Init();
    GraphicPcs.Init();
    Chara.Init();
    LightPcs.Init();
    CharaPcs.Init();
    MapPcs.Init();
    MaterialEditorPcs.Init();
    FunnyShapePcs.Init();
    USBPcs.Init();
    MenuPcs.Init();
    GbaPcs.Init();
    McPcs.Init();
    DbgMenuPcs.Init();

    m_mainStage = Memory.CreateStage(0x106000, const_cast<char*>(sGameStageName), 0);
    if (OSGetConsoleSimulatedMemSize() == 0x3000000) {
        m_debugStage = Memory.CreateStage(0x220000, const_cast<char*>(sGameDebugStageName), 1);
    }

    m_sceneId = 4;
    m_mapId = 3;
    m_mapVariant = 0;
    memset(m_currentScriptName, 0, sizeof(m_currentScriptName));
    memset(m_startScriptName, 0, sizeof(m_startScriptName));
    m_frameCounterEnable = 1;
    gCFlatRuntime().Init();
    unkFloat_0xca10 = kGameSmallDelta;
}

/*
 * --INFO--
 * PAL Address: 0x80015f14
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Quit()
{
	gCFlatRuntime().Quit();

	if (m_debugStage != 0) {
		Memory.DestroyStage(m_debugStage);
	}

	Memory.DestroyStage(m_mainStage);
	DbgMenuPcs.Quit();
	McPcs.Quit();
	GbaPcs.Quit();
	MenuPcs.Quit();
	USBPcs.Quit();
	Chara.Quit();
	CharaPcs.Quit();
	LightPcs.Quit();
	MapPcs.Quit();
	MaterialEditorPcs.Quit();
	FunnyShapePcs.Quit();
	GraphicPcs.Quit();
	CameraPcs.Quit();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::LoadLogoWaitingData()
{
	if (m_assetsLoadedFlag == 0) {
		SoundPcs.createLoad();
		CharaPcs.createLoad();
		PartPcs.createLoad();
		m_assetsLoadedFlag = 1;
		if ((u32)System.m_execParam < 3) {
			return;
		}

		System.Printf(const_cast<char*>(sCoreResidentLoadedMsg));
	}
}

/*
 * --INFO--
 * PAL Address: 0x800157a8
 * PAL Size: 1764b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Exec()
{
	System.AddScenegraph(reinterpret_cast<CProcess*>(&SystemPcs), 0);
	System.AddScenegraph(reinterpret_cast<CProcess*>(&GraphicPcs), 0);
	System.AddScenegraph(reinterpret_cast<CProcess*>(&LightPcs), 0);
	System.AddScenegraph(reinterpret_cast<CProcess*>(&MiniGamePcs), 0);

	do {
		m_cfdLoadedFlag = 0;
		m_assetsLoadedFlag = 0;

		Memory.IncHeapWalkerLevel();

		m_currentSceneId = m_sceneId;
		m_currentMapId = m_mapId;
		m_currentMapVariantId = m_mapVariant;
		strcpy(m_currentScriptName, m_sceneScript + 4);

		int sceneId = m_currentSceneId;
		if (sceneId >= 0 && sceneId < 9) {
			System.Printf(const_cast<char*>(sGameExecSceneFmt), m_tStatus[sceneId]);
		} else {
			System.Printf(const_cast<char*>(sGameInvalidSceneFmt), sceneId);
		}

		switch (m_currentSceneId) {
		case 2:
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 1);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CharaPcs), 1);
			break;
		case 3:
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 2);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&MapPcs), 1);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 6);
			break;
		case 4:
			System.AddScenegraph(reinterpret_cast<CProcess*>(&MenuPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&MapPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 6);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CharaPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&Game), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&PartPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&GbaPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&DbgMenuPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&McPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&SoundPcs), 0);
			break;
		case 5:
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 3);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&MaterialEditorPcs), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&LightPcs), 0);
			break;
		case 6:
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 4);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&FunnyShapePcs), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&LightPcs), 0);
			break;
		case 7:
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 5);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CharaPcs), 2);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&MapPcs), 1);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 6);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&PartPcs), 1);
			break;
		}

		System.ExecScenegraph();

		switch (m_currentSceneId) {
		case 2:
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 1);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CharaPcs), 1);
			break;
		case 3:
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 2);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 6);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&MapPcs), 1);
			break;
		case 4:
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&SoundPcs), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&McPcs), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 6);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&MapPcs), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CharaPcs), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&PartPcs), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&GbaPcs), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&Game), 0);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&MenuPcs), 0);
			break;
		case 5:
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 3);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&MaterialEditorPcs), 0);
			break;
		case 6:
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 4);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&FunnyShapePcs), 0);
			break;
		case 7:
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 5);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CameraPcs), 6);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&CharaPcs), 2);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&MapPcs), 1);
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&PartPcs), 1);
			break;
		}

		Memory.HeapWalker();
		Memory.DecHeapWalkerLevel();
	} while (m_sceneId != 0);

	System.RemoveScenegraph(reinterpret_cast<CProcess*>(&MiniGamePcs), 0);
	System.RemoveScenegraph(reinterpret_cast<CProcess*>(&LightPcs), 0);
	System.RemoveScenegraph(reinterpret_cast<CProcess*>(&GraphicPcs), 0);
	System.RemoveScenegraph(reinterpret_cast<CProcess*>(&SystemPcs), 0);
}

/*
 * --INFO--
 * PAL Address: 0x80015610
 * PAL Size: 408b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Create()
{
    int mapId;
    int mapVariant;
    char scriptName[256];

    m_nextScript.m_flags = 1;
    clearWork();

    memset(&m_gameWork.m_gameDataStartMarker, 0, kGameWorkDataClearSize);
    memset(m_gameWork.m_wmBackupParams, 0xFF, sizeof(m_gameWork.m_wmBackupParams));

    *reinterpret_cast<u32*>(&m_gameWork.m_scriptSysVal0) = 1;
    m_gameWork.m_chaliceElement = 1;
    strcpy(m_gameWork.m_townName, m_gameWork.m_languageId == 3 ? s_townNameTepa : s_townNameTipa);

    m_gameWork.m_gameInitFlag = 1;

    if (strlen(m_startScriptName) != 0) {
        strcpy(scriptName, m_startScriptName);
        u32* src = reinterpret_cast<u32*>(scriptName);
        u32* dst = reinterpret_cast<u32*>(m_nextScript.m_name);
        int count = sizeof(scriptName) / (sizeof(u32) * 2);
        do {
            *dst++ = *src++;
            *dst++ = *src++;
        } while (--count != 0);
        m_newGameFlag = 1;
    }

    if (m_newGameFlag == 0) {
        mapId = m_currentMapId;
        mapVariant = m_currentMapVariantId;

        Graphic._WaitDrawDone(const_cast<char*>(s_game_cpp), 0x24E);
        System.MapChanging(mapId, mapVariant);

        m_currentMapId = mapId;
        m_currentMapVariantId = mapVariant;

        MapPcs.LoadMap(mapId, mapVariant, 0, 0, 0);
        PartPcs.LoadFieldPdt(mapId, mapVariant, 0, 0, 0);

        System.MapChanged(mapId, mapVariant, 1);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Destroy()
{
	clearWork();
}

/*
 * --INFO--
 * PAL Address: 0x8001551c
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::InitNewGame()
{
    System.Printf(const_cast<char*>(s_gameDebugMarker));
    System.Printf(const_cast<char*>(sNewGameInitMsg));
    System.Printf(const_cast<char*>(s_gameDebugMarker));

    CGame* game = &Game;

    memset(&game->m_gameWork.m_gameDataStartMarker, 0, kGameWorkDataClearSize);
    memset(game->m_gameWork.m_wmBackupParams, 0xFF, sizeof(game->m_gameWork.m_wmBackupParams));

    *reinterpret_cast<unsigned int*>(&game->m_gameWork.m_scriptSysVal0) = 1;
    game->m_gameWork.m_chaliceElement = 1;
    strcpy(game->m_gameWork.m_townName, game->m_gameWork.m_languageId == 3 ? s_townNameTepa : s_townNameTipa);
    gCFlatRuntime2.ResetNewGame();
    Chara.InitFurTexBuffer();
}

/*
 * --INFO--
 * PAL Address: 0x80015280
 * PAL Size: 668b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::clearWork()
{
    int i;
    int j;

    gCFlatRuntime2.Destroy();

    for (i = 0; i < 4; i++) {
        m_cFlatDataArr[i].Destroy();
    }

    unkCFlatData0[0] = 0;
    unkCFlatData0[1] = 0;
    unkCFlatData0[2] = 0;
    unkCFlatData0[3] = 0;
    m_partyObjArr[0] = 0;
    m_partyObjArr[1] = 0;
    m_partyObjArr[2] = 0;
    m_partyObjArr[3] = 0;
    m_scriptFoodBase[0] = 0;
    m_scriptFoodBase[1] = 0;
    m_scriptFoodBase[2] = 0;
    m_scriptFoodBase[3] = 0;

    unk_flat3_0xc7d0 = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            m_scriptWork[i][j][0] = 0;
            m_scriptWork[i][j + 8][0] = 0;
            m_scriptWork[i][j][1] = 0;
            m_scriptWork[i][j + 8][1] = 0;
        }
    }

    m_gameWork.m_soundOptionFlag = '\0';
    m_gameWork.m_gameOverFlag = '\0';

    MapMng.DestroyMap();
    CharaPcs.Reset(static_cast<CCharaPcs::RESET>(0));
    Sound.StopAndFreeAllSe(0);
    Wind.ClearAll();

    GameSoundData(Sound).m_seMaxVolume = 0x7F;

    CPtrArray<CMapLightHolder*>* mapLightHolderArr = &MapMng.GetMapLightHolderArray(0);

    if (mapLightHolderArr->GetSize() != 0) {
        _GXColor holderColor;
        Vec holderVec;

        if (mapLightHolderArr->GetSize() != 0) {
            (*mapLightHolderArr)[0]->GetLightHolder(&holderColor, 0);
        }

        u8* charaColorE8 = reinterpret_cast<u8*>(&CharaPcs) + 0xE8;
        u8* charaColorF0Base = reinterpret_cast<u8*>(&CharaPcs) + 0xF0;
        u8* charaVec108Base = reinterpret_cast<u8*>(&CharaPcs) + 0x108;

        for (int i = 0; i < 2; i++) {
            charaColorE8[0] = holderColor.r;
            charaColorE8[1] = holderColor.g;
            charaColorE8[2] = holderColor.b;
            charaColorE8[3] = holderColor.a;

            u8* charaColorF0 = charaColorF0Base;
            u8* charaVec108 = charaVec108Base;

            for (u32 j = 0; j < 3; j++) {
                if ((j + 1) < static_cast<u32>(mapLightHolderArr->GetSize())) {
                    (*mapLightHolderArr)[j + 1]->GetLightHolder(&holderColor, &holderVec);
                }

                charaColorF0[0] = holderColor.r;
                charaColorF0[1] = holderColor.g;
                charaColorF0[2] = holderColor.b;
                charaColorF0[3] = holderColor.a;

                if (i == 0) {
                    *reinterpret_cast<Vec*>(charaVec108) = holderVec;
                }

                charaColorF0 += 4;
                charaVec108 += 0xC;
            }

            charaColorE8 += 4;
            charaColorF0Base += 0xC;
            charaVec108Base += 0xC;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGame::clearWorkMap()
{
    MapMng.DestroyMap();
    CharaPcs.Reset(static_cast<CCharaPcs::RESET>(0));
    Sound.StopAndFreeAllSe(0);
    Wind.ClearAll();

    GameSoundData(Sound).m_seMaxVolume = 0x7F;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGame::clearWorkScript()
{
    for (int i = 0; i < 4; i++) {
        m_partyObjArr[i] = 0;
        m_scriptFoodBase[i] = 0;
    }

    unk_flat3_0xc7d0 = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            m_scriptWork[i][j][0] = 0;
            m_scriptWork[i][j + 8][0] = 0;
            m_scriptWork[i][j][1] = 0;
            m_scriptWork[i][j + 8][1] = 0;
        }
    }

    m_gameWork.m_soundOptionFlag = 0;
    m_gameWork.m_gameOverFlag = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80014ff8
 * PAL Size: 648b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::CheckScriptChange()
{
    if (m_newGameFlag == 0) {
        return;
    }

    m_newGameFlag = 0;
    Graphic._WaitDrawDone(const_cast<char*>(s_game_cpp), 0x205);

    if ((u32)System.m_execParam > 2) {
        System.Printf(const_cast<char*>(s_ScriptWillChangeMsg_801D619C));
    }

    System.ScriptChanging(m_nextScript.m_name);

    if (strcmp(m_nextScript.m_name, s_defaultScriptName) != 0) {
        if (m_cfdLoadedFlag == 0) {
            gCFlatRuntime2.Destroy();
            loadCfd();
            m_cfdLoadedFlag = 1;

            if ((u32)System.m_execParam > 2) {
                System.Printf(const_cast<char*>(s_ScriptResidentLoadedMsg_801D61B8));
            }
        }

        if (m_assetsLoadedFlag == 0) {
            SoundPcs.createLoad();
            CharaPcs.createLoad();
            PartPcs.createLoad();
            m_assetsLoadedFlag = 1;

            if ((u32)System.m_execParam > 2) {
                System.Printf(const_cast<char*>(sCoreResidentLoadedMsg));
            }
        }
    }

    int scriptResult = gCFlatRuntime2.Load(m_nextScript.m_name);
    strcpy(m_currentScriptName, m_nextScript.m_name);

    if (m_nextScript.m_flags != 0) {
        CGame* game = &Game;

        System.Printf(const_cast<char*>(s_gameDebugMarker));
        System.Printf(const_cast<char*>(sNewGameInitMsg));
        System.Printf(const_cast<char*>(s_gameDebugMarker));

        memset(&game->m_gameWork.m_gameDataStartMarker, 0, kGameWorkDataClearSize);
        memset(game->m_gameWork.m_wmBackupParams, 0xFF, sizeof(game->m_gameWork.m_wmBackupParams));

        *reinterpret_cast<unsigned int*>(&game->m_gameWork.m_scriptSysVal0) = 1;
        game->m_gameWork.m_chaliceElement = 1;
        strcpy(game->m_gameWork.m_townName, game->m_gameWork.m_languageId == 3 ? s_townNameTepa : s_townNameTipa);
        gCFlatRuntime2.ResetNewGame();
        Chara.InitFurTexBuffer();
        m_nextScript.m_flags = 0;
    }

    System.ScriptChanged(m_nextScript.m_name, scriptResult);

    if ((u32)System.m_execParam > 2) {
        System.Printf(const_cast<char*>(s_ScriptChangedMsg_801D6234));
    }
}

/*
 * --INFO--
 * PAL Address: 0x80014e78
 * PAL Size: 384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::ChangeMap(int mapId, int mapVariant, int param4, int param5)
{
    int hasParamMask;

    if (param5 != 0) {
        Graphic._WaitDrawDone(const_cast<char*>(s_game_cpp), 0x24E);
        System.MapChanging(mapId, mapVariant);

        m_currentMapId = mapId;
        m_currentMapVariantId = mapVariant;
        hasParamMask = (-param4 | param4) >> 31;

        MapPcs.LoadMap(
            mapId, mapVariant, (void*)(hasParamMask & 0x800000), hasParamMask & 0x580000, 0);

        PartPcs.LoadFieldPdt(
            mapId, mapVariant, (void*)(hasParamMask & 0xD80000), hasParamMask & 0x80000, 0);

        System.MapChanged(mapId, mapVariant, 1);
    } else {
        u8 loadStep = param4;
        hasParamMask = (-param4 | param4) >> 31;
        MapPcs.LoadMap(
            mapId, mapVariant, (void*)(hasParamMask & 0x800000), hasParamMask & 0x580000, loadStep);

        PartPcs.LoadFieldPdt(
            mapId, mapVariant, (void*)(hasParamMask & 0xD80000), hasParamMask & 0x80000, loadStep);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80014e44
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::ScriptChanging(char*)
{
	PartMng.pppDeleteAll();
	PartMng.pppDestroyAll();
}

/*
 * --INFO--
 * PAL Address: 0x80014d04
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::ScriptChanged(char*, int)
{
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        m_partyObjArr[i] = 0;
        m_scriptFoodBase[i] = 0;
    }

    unk_flat3_0xc7d0 = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            m_scriptWork[i][j][0] = 0;
            m_scriptWork[i][j + 8][0] = 0;
            m_scriptWork[i][j][1] = 0;
            m_scriptWork[i][j + 8][1] = 0;
        }
    }

    m_gameWork.m_soundOptionFlag = 0;
    m_gameWork.m_gameOverFlag = 0;

    MapMng.DestroyMap();
    CharaPcs.Reset(static_cast<CCharaPcs::RESET>(0));
    Sound.StopAndFreeAllSe(0);
    Wind.ClearAll();

    GameSoundData(Sound).m_seMaxVolume = 0x7F;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MapChanging(int, int)
{
    return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MapChanged(int, int, int)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80014b90
 * PAL Size: 364b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::loadCfd()
{
    struct FlatDataEntry
    {
        unsigned int m_size;
        void* m_data;
        int m_numStrings;
        char** m_strings;
        char* m_stringBuf;
    };

    struct FlatDataLayout
    {
        int m_dataCount;
        FlatDataEntry m_data[5];
        u8 m_pad[0x14D4 - 0x68];
    };

    char path[0xFC];

    for (int i = 0; i < 4; i++)
    {
        const char* localLangDirs[6];
        localLangDirs[0] = s_localLangDirs[0];
        localLangDirs[1] = s_localLangDirs[1];
        localLangDirs[2] = s_localLangDirs[2];
        localLangDirs[3] = s_localLangDirs[3];
        localLangDirs[4] = s_localLangDirs[4];
        localLangDirs[5] = s_localLangDirs[5];

        sprintf(path, PTR_s_dvd__scft_param_cfd[i], localLangDirs[Game.m_gameWork.m_languageId]);
        CFile::CHandle* handle = File.Open(path, 0, CFile::PRI_LOW);

        if (handle != nullptr)
        {
            File.Read(handle);
            File.SyncCompleted(handle);
            m_cFlatDataArr[i].Create(File.m_readBuffer);
            File.Close(handle);
        }
    }

    FlatDataLayout* flatData = reinterpret_cast<FlatDataLayout*>(m_cFlatDataArr);

    unkCFlatData0[0] = (unsigned int)flatData[0].m_data[0].m_data;
    unkCFlatData0[1] = (unsigned int)flatData[0].m_data[1].m_data;
    unkCFlatData0[2] = (unsigned int)flatData[0].m_data[2].m_data;
    unkCFlatData0[3] = (unsigned int)flatData[2].m_data[0].m_data;
    unk_flat3_field_8_0xc7dc = (unsigned int)flatData[3].m_data[0].m_data;
    unk_flat3_field_1C_0xc7d8 = (unsigned int)flatData[3].m_data[1].m_data;
    unk_flat3_count_0xc7d4 = flatData[3].m_data[1].m_size / 0x1A;
    unk_flat3_field_30_0xc7e0 = (unsigned int)flatData[3].m_data[2].m_data;
    m_bossArtifactBase = (unsigned int)flatData[3].m_data[3].m_data;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Calc()
{
	Mtx rotMtx;
    int mapObjIdx;
    float position;

    if (m_frameCounterEnable != 0) {
        m_gameWork.m_frameCounter++;
    }

    m_partyMinZ = kGamePartyBoundsMinInit;
    m_partyMinY = kGamePartyBoundsMinInit;
    m_partyMinX = kGamePartyBoundsMinInit;
    m_partyMaxZ = kGamePartyBoundsMaxInit;
    m_partyMaxY = kGamePartyBoundsMaxInit;
    m_partyMaxX = kGamePartyBoundsMaxInit;

    for (int i = 0; i < 4; i++) {
        CGPartyObj* partyObj = m_partyObjArr[i];

        if (partyObj != 0) {
            position = partyObj->m_worldPosition.x;
            m_partyMinX = (m_partyMinX < position) ? m_partyMinX : position;

            position = partyObj->m_worldPosition.y;
            m_partyMinY = (m_partyMinY < position) ? m_partyMinY : position;

            position = partyObj->m_worldPosition.z;
            m_partyMinZ = (m_partyMinZ < position) ? m_partyMinZ : position;

            position = partyObj->m_worldPosition.x;
            m_partyMaxX = (m_partyMaxX > position) ? m_partyMaxX : position;

            position = partyObj->m_worldPosition.y;
            m_partyMaxY = (m_partyMaxY > position) ? m_partyMaxY : position;

            position = partyObj->m_worldPosition.z;
            m_partyMaxZ = (m_partyMaxZ > position) ? m_partyMaxZ : position;
        }
    }

    Wind.Frame();
    CFlatRuntime2Storage().Calc();
    gCFlatRuntime().ResetPerformance();
    CFlatRuntime2Storage().Frame(1, 0);

    if ((m_currentMapId == 0x21) && ((mapObjIdx = MapMng.GetMapObjIdx(0)) >= 0)) {
            if (!sMapObjRotationInitialized) {
                sMapObjRotationInitialized = true;
                sMapObjRotationAngle = kGameZero;
            }

            sMapObjRotationAngle += kGameSmallDelta;
            PSMTXRotRad(rotMtx, 'y', sMapObjRotationAngle);
            MapMng.SetMapObjLMtx(mapObjIdx, rotMtx);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80014964
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Calc2()
{
	CFlatRuntime2Storage().Frame(0, 1);
}

/*
 * --INFO--
 * PAL Address: 0x80014934
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Calc3()
{ 
	CGPartyObj::CheckMenu();
	gCFlatRuntime().AfterFrame(0);
}

/*
 * --INFO--
 * PAL Address: 0x80014540
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::LoadFinished()
{
	for (int i = 0; i < 8; ++i) {
		m_caravanWorkArr[i].LoadFinished();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8001458c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::LoadInit()
{
	for (int i = 0; i < 8; ++i) {
		m_caravanWorkArr[i].LoadInit();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800145d8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::LoadScript(char* scriptData)
{
    u8* flat = CFlat;
    int scriptOffset = 0;
    int i = 0;
    int entryOffset = 0;

    while (i < *(int*)(flat + 4)) {
        if ((*(u8*)(*(int*)(flat + 8) + entryOffset + 1) & 0x20) != 0) {
            u32* src = reinterpret_cast<u32*>(scriptData + scriptOffset);
            scriptOffset += 4;
            *(u32*)(*(int*)(flat + 12) + entryOffset) = *src;
        }

        entryOffset += 4;
        i++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001462c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::SaveScript(char* scriptData)
{
    memset(scriptData, 0, kGameScriptSaveDataSize);

    u8* flat = CFlat;
    int scriptOffset = 0;
    int entryOffset = 0;
    int i = 0;

    while (i < *(int*)(flat + 4)) {
        if ((*(u8*)(*(int*)(flat + 8) + entryOffset + 1) & 0x20) != 0) {
            *(u32*)(scriptData + scriptOffset) = *reinterpret_cast<u32*>(*(int*)(flat + 12) + entryOffset);
            scriptOffset += 4;
        }

        entryOffset += 4;
        i++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800146b4
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::ParticleFrameCallback(int effectIndex, int scriptLine, int scriptStep, int callbackType, int graphFrame, Vec*)
{
	char* callbackFmtBase = const_cast<char*>(s_gameAssetNameBlock_801D5FC0);
	PPPIFPARAM* ifData = PartMng.pppGetIfDt(static_cast<short>(effectIndex));
	ifData->m_hitFlags |= 1 << callbackType;

	if (callbackType == 0) {
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(callbackFmtBase + kParticleCallbackType0Fmt, scriptLine, scriptStep, effectIndex, graphFrame);
		}
	} else if (callbackType == 1) {
		ifData->m_hitFlags &= ~2;
		PartMng.pppEndPart(effectIndex);

		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(callbackFmtBase + kParticleCallbackType1Fmt, scriptLine, scriptStep, effectIndex, graphFrame);
		}
	} else if (callbackType == 3) {
		PartMng.pppEndPart(effectIndex);

		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(callbackFmtBase + kParticleCallbackType3Fmt, scriptLine, scriptStep, effectIndex, graphFrame);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800147f8
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::HitParticleBG(int effectIndex, int kind, int nodeIndex, Vec* pos, PPPIFPARAM* hitParam)
{
	CFlatRuntime::CStack stack[8];
	stack[0].m_word = (u32)effectIndex;
	stack[1].m_word = (u32)kind;
	stack[2].m_word = (u32)nodeIndex;
	*(float*)&stack[3].m_word = pos->x;
	*(float*)&stack[4].m_word = pos->y;
	*(float*)&stack[5].m_word = pos->z;
	stack[6].m_word = (u32)hitParam->m_particleIndex;
	stack[7].m_word = (u32)hitParam->m_classId;
	gCFlatRuntime().SystemCall(0, 1, 1, 8, stack, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8001486c
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Draw3()
{
	CFlatRuntime2Storage().Frame(0, 2);
	gCFlatRuntime().SystemCall(0, 1, 5, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800148c0
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Draw2()
{
	CFlatRuntime2Storage().Draw();
	Wind.Draw();
}

/*
 * --INFO--
 * PAL Address: 0x800148f4
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Draw()
{
	gCFlatRuntime().SystemCall(0, 1, 6, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8001440c
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGame::GetBossArtifact(int ratioIndex, int amount)
{
    static s16 s_top[] = {0, 4, 8};

    int stage =
        Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
    if (2 < stage) {
        stage = 2;
    }

    int stageBase = s_top[stage];
    int scaledAmount = (int)((float)amount * s_ratio[ratioIndex - 1]);

    u16 thresholds[4];
    memset(thresholds, 0, 8);

    u32 bossArtifactBase = Game.m_bossArtifactBase;
    int stageIndex = (int)Game.m_gameWork.m_bossArtifactStageIndex;
    int artifactRank = 3;
    int stageOffset = Game.m_bossArtifactBase + stageIndex * 0x168;

    thresholds[1] = *(u16*)(stageOffset + 0x162);
    thresholds[2] = *(u16*)(stageOffset + 0x164);
    thresholds[3] = *(u16*)(stageOffset + 0x166);

    if (((scaledAmount < (s16)thresholds[3]) && (artifactRank = 2, scaledAmount < (s16)thresholds[2])) &&
        (artifactRank = 1, scaledAmount < (s16)thresholds[1])) {
        artifactRank = 0;
    }

    scaledAmount = rand();
    int divisor = artifactRank + 1;
    int quotient = scaledAmount / divisor;
    stageBase += scaledAmount - quotient * divisor;
    return bossArtifactBase + stageIndex * 0x168 + 0x20 + stageBase * 8;
}

/*
 * --INFO--
 * PAL Address: 0x800143ec
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGame::GetFoodLevel(int playerIndex, int foodIndex)
{
    u16 level = reinterpret_cast<u16*>(m_scriptFoodBase[playerIndex] + 0x3B8)[foodIndex];
    return level;
}

/*
 * --INFO--
 * PAL Address: 0x800143a4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::GetTargetCursor(int playerIndex, Vec& posA, Vec& posB)
{
    unsigned int* data = (unsigned int*)(m_scriptFoodBase[playerIndex] + 0xBAC);

    posA.x = *(f32*)&data[0];
    posA.y = *(f32*)&data[1];
    posA.z = *(f32*)&data[2];

    data = (unsigned int*)(m_scriptFoodBase[playerIndex] + 0xBB8);
    posB.x = *(f32*)&data[0];
    posB.y = *(f32*)&data[1];
    posB.z = *(f32*)&data[2];
}

/*
 * --INFO--
 * PAL Address: 0x800142e4
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGame::GetParticleSpecialInfo(PPPIFPARAM& ifParam, int& particleIndex, int& specialInfo)
{
    CFlatRuntime2* runtime;
    CGBaseObj* baseObj;

    if (ifParam.m_classId == 0) {
        return 0;
    }

    runtime = &CFlatRuntime2Storage();
    baseObj = reinterpret_cast<CGBaseObj*>(runtime->intToClass((int)ifParam.m_classId));
    particleIndex = ifParam.m_particleIndex;
    if (particleIndex == 0) {
        return 0;
    }

    u16 behaviorFlags = (u16)baseObj->GetCID();
    if ((behaviorFlags & 0x6D) != 0x6D) {
        return 0;
    }

    char* objWork = (char*)reinterpret_cast<CGObject*>(baseObj)->m_scriptHandle;
    specialInfo = *reinterpret_cast<int*>(objWork + 0x3B4);
    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGPartyObj* CGame::GetPartyObj(int index)
{
    return m_partyObjArr[index];
}

/*
 * --INFO--
 * PAL Address: 0x800141e0
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeArtItemName(char* out, int itemIndex, int count)
{
    if (count > 1) {
        char* name;

        if (count > 1) {
            name = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings[itemIndex * 5 + 3];
        } else {
            name = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings[itemIndex * 5 + 1];
        }

        sprintf(out, s_numNameFmt, count, name);
    } else {
        char** itemTable = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings;
        unsigned char hasSeparator = 0;
        char* prefix = itemTable[itemIndex * 5];
        char* name = itemTable[itemIndex * 5 + 1];

        if (strlen(prefix) != 0) {
            unsigned char languageId = m_gameWork.m_languageId;
            if ((languageId != 3) && (languageId != 4)) {
                hasSeparator = 1;
            }
        }

        const char* separator = s_nameNoSep;
        if (hasSeparator != 0) {
            separator = s_nameSep;
        }

        sprintf(out, s_nameJoinFmt, prefix, separator, name);
    }
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x80014144
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeArtsItemNames(char* out, int itemIndex)
{
    CFlatDataView* flatData = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1]);
    char** itemTable = flatData->m_tabl[0].m_strings;
    unsigned char hasSeparator = 0;
    char* prefix = itemTable[itemIndex * 5 + 2];
    char* itemName = itemTable[itemIndex * 5 + 3];

    if (strlen(prefix) != 0) {
        unsigned char languageId = m_gameWork.m_languageId;
        if ((languageId != 3) && (languageId != 4)) {
            hasSeparator = 1;
        }
    }

    const char* separator = s_nameNoSep;
    if (hasSeparator != 0) {
        separator = s_nameSep;
    }

    sprintf(out, s_nameJoinFmt, prefix, separator, itemName);
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x800140c8
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeNumItemName(char* out, int itemIndex, int count)
{
    char* itemName;

    if (count > 1) {
        itemName = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings[itemIndex * 5 + 3];
    } else {
        itemName = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings[itemIndex * 5 + 1];
    }

    sprintf(out, s_numNameFmt, count, itemName);
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x80013fd8
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeArtMonName(char* out, int monIndex, int count)
{
    if (count > 1) {
        char* name;

        if (count > 1) {
            name = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings[monIndex * 5 + 3];
        } else {
            name = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings[monIndex * 5 + 1];
        }

        sprintf(out, s_numNameFmt, count, name);
    } else {
        char** monTable = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings;
        unsigned char hasSeparator = 0;
        char* prefix = monTable[monIndex * 5];
        char* name = monTable[monIndex * 5 + 1];

        if (strlen(prefix) != 0) {
            unsigned char languageId = m_gameWork.m_languageId;
            if ((languageId != 3) && (languageId != 4)) {
                hasSeparator = 1;
            }
        }

        const char* separator = s_nameNoSep;
        if (hasSeparator != 0) {
            separator = s_nameSep;
        }

        sprintf(out, s_nameJoinFmt, prefix, separator, name);
    }
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x80013f3c
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeArtsMonNames(char* out, int monIndex)
{
    CFlatDataView* flatData = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1]);
    char** monTable = flatData->m_tabl[1].m_strings;
    unsigned char hasSeparator = 0;
    char* prefix = monTable[monIndex * 5 + 2];
    char* monName = monTable[monIndex * 5 + 3];

    if (strlen(prefix) != 0) {
        unsigned char languageId = m_gameWork.m_languageId;
        if ((languageId != 3) && (languageId != 4)) {
            hasSeparator = 1;
        }
    }

    const char* separator = s_nameNoSep;
    if (hasSeparator != 0) {
        separator = s_nameSep;
    }

    sprintf(out, s_nameJoinFmt, prefix, separator, monName);
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x80013ec0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeNumMonName(char* out, int monIndex, int count)
{
    char* monName;

    if (count > 1) {
        monName = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings[monIndex * 5 + 3];
    } else {
        monName = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings[monIndex * 5 + 1];
    }

    sprintf(out, s_numNameFmt, count, monName);
    return out;
}

/*
 * --INFO--
 * PAL Address: 80013e70
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
const char* CGame::GetLangString()
{
    const char* localLangDirs[6];

    localLangDirs[0] = s_localLangDirs[0];
    localLangDirs[1] = s_localLangDirs[1];
    localLangDirs[2] = s_localLangDirs[2];
    localLangDirs[3] = s_localLangDirs[3];
    localLangDirs[4] = s_localLangDirs[4];
    localLangDirs[5] = s_localLangDirs[5];

    return localLangDirs[m_gameWork.m_languageId];
}

/*
 * --INFO--
 * PAL Address: 0x800b91a4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGame::CGameWork::ClearEvtWork()
{
    memset(m_eventFlags, 0, sizeof(m_eventFlags));
    memset(m_eventWork, 0, sizeof(m_eventWork));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGame::CGameWork::Init()
{
    memset(&m_gameDataStartMarker, 0, kGameWorkDataClearSize);
    memset(m_wmBackupParams, 0xFF, sizeof(m_wmBackupParams));

    *reinterpret_cast<unsigned int*>(&m_scriptSysVal0) = 1;
    m_chaliceElement = 1;
    strcpy(m_townName, m_languageId == 3 ? s_townNameTepa : s_townNameTipa);
    m_gameInitFlag = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGame::CGameWork::InitNewGame()
{
    const unsigned short optionValue = m_optionValue;
    const unsigned char radarType = m_radarType;
    const unsigned char mogScoreRadarType = m_mogScoreRadarType;
    const unsigned char mcHasSerial = m_mcHasSerial;
    const unsigned char unk13D7 = unk_0x13D7;
    const unsigned int mcRandom = m_mcRandom;
    const unsigned char mcId = m_mcId;
    const unsigned char bgmVolume = m_bgmVolume;
    const unsigned char seVolume = m_seVolume;
    const unsigned char stereoFlag = m_stereoFlag;
    const unsigned int mcSerial0 = m_mcSerial0;
    const unsigned int mcSerial1 = m_mcSerial1;

    Init();

    m_optionValue = optionValue;
    m_radarType = radarType;
    m_mogScoreRadarType = mogScoreRadarType;
    m_mcHasSerial = mcHasSerial;
    unk_0x13D7 = unk13D7;
    m_mcRandom = mcRandom;
    m_mcId = mcId;
    m_bgmVolume = bgmVolume;
    m_seVolume = seVolume;
    m_stereoFlag = stereoFlag;
    m_mcSerial0 = mcSerial0;
    m_mcSerial1 = mcSerial1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGame::CGameWork::ClearScriptChange()
{
    *reinterpret_cast<unsigned int*>(&m_scriptSysVal0) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CGame::IsWorldMap()
{
    return m_currentMapId == 0x21;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CGame::IsPartyExist(int index)
{
    return index >= 0 && index < 4 && GetPartyObj(index) != 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetItemName(int itemIndex)
{
    return reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings[itemIndex * 5 + 1];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetItemArt(int itemIndex)
{
    return reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings[itemIndex * 5];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetItemNames(int itemIndex)
{
    return reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings[itemIndex * 5 + 3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetItemArts(int itemIndex)
{
    return reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings[itemIndex * 5 + 2];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetItemName(int itemIndex, int count)
{
    return count > 1 ? GetItemNames(itemIndex) : GetItemName(itemIndex);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetMonName(int monIndex)
{
    return reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings[monIndex * 5 + 1];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetMonArt(int monIndex)
{
    return reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings[monIndex * 5];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetMonNames(int monIndex)
{
    return reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings[monIndex * 5 + 3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetMonArts(int monIndex)
{
    return reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings[monIndex * 5 + 2];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetMonName(int monIndex, int count)
{
    return count > 1 ? GetMonNames(monIndex) : GetMonName(monIndex);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CGame::CGameWork::CGameWork()
{
    memset(&m_gameDataStartMarker, 0, kGameWorkDataClearSize);
    memset(m_wmBackupParams, 0xFF, sizeof(m_wmBackupParams));

    *reinterpret_cast<unsigned int*>(&m_scriptSysVal0) = 1;
    m_chaliceElement = 1;
    strcpy(m_townName, m_languageId == 3 ? s_townNameTepa : s_townNameTipa);
    m_gameInitFlag = 1;
}
