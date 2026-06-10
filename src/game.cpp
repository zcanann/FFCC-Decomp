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

extern const char sGameStatusExit[] = "SN_EXIT";
extern const char sGameStatusMap[] = "SN_MAP";
extern const char sGameStatusGame[] = "SN_GAME";
extern const char s_localLangDirJp[] = "jp/";
extern const char s_localLangDirUk[] = "uk/";
extern const char s_localLangDirGr[] = "gr/";
extern const char s_localLangDirIt[] = "it/";
extern const char s_localLangDirFr[] = "fr/";
extern const char s_localLangDirSp[] = "sp/";
extern const char sGameClassName[] = "CGame";
static const char s_numNameFmt[] = "%d %s";
static const char s_nameSep[] = " ";
static const char s_nameNoSep[4] = "";
static const char s_nameJoinFmt[] = "%s%s%s";
extern const double kGameIntToDoubleBias = 4503601774854144.0;
extern const float kGamePartyBoundsMinInit = 1.0E+10;
extern const float kGamePartyBoundsMaxInit = -1.0E+10;
extern const float kGameZero = 0.0;
extern const float kGameSmallDelta = 0.001;
extern "C" {
const char s_defaultScriptName[] = "ffcc_0";
const char s_gameDebugMarker[] = "*\n";
const char s_townNameTepa[] = "Tepa";
const char s_townNameTipa[] = "Tipa";
const char sGameStageName[] = "Game";
}
extern const char sGameParamCfdPathFmt[];
extern const char sGameSystemCfdPathFmt[];
extern const char sGameMailTableCfdPathFmt[];
extern const char sGameNewBattleCfdPathFmt[];
extern const char sGameAssetNameBlock[];

enum GameAssetNameBlockOffset {
	kParticleCallbackType0Fmt = 0x114,
	kParticleCallbackType1Fmt = 0x154,
	kParticleCallbackType3Fmt = 0x194,
	kGameCpp = 0x1D0,
	kScriptWillChangeMsg = 0x1DC,
	kScriptResidentLoadedMsg = 0x1F8,
	kCoreResidentLoadedMsg = 0x21C,
	kNewGameInitMsg = 0x254,
	kScriptChangedMsg = 0x274,
};

enum {
	kGameWorkDataClearSize =
	    sizeof(CGame::CGameWork) - offsetof(CGame::CGameWork, m_gameDataStartMarker),
	kGameScriptSaveDataSize = 0x800,
};

STATIC_ASSERT(kGameWorkDataClearSize == 0x13E1);

extern "C" const char s_game_cpp[];
extern const char sCoreResidentLoadedMsg[];
extern const char sNewGameInitMsg[];
extern const char sGameExecSceneFmt[];
extern const char sGameInvalidSceneFmt[];
extern const char sGameDebugStageName[];
extern const char sGameStatusExit[];
extern const char sGameStatusDummy[];
extern const char sGameStatusChara[];
extern const char sGameStatusMap[];
extern const char sGameStatusGame[];
extern const char sGameStatusMaterialEditor[];
extern const char sGameStatusFunnyShape[];
extern const char sGameStatusPartView[];
extern const char* s_localLangDirs[];
static const char* m_tStatus[] = {
    sGameStatusExit,
    sGameStatusDummy,
    sGameStatusChara,
    sGameStatusMap,
    sGameStatusGame,
    sGameStatusMaterialEditor,
    sGameStatusFunnyShape,
    sGameStatusPartView,
    0,
};
const char* sGameCfdPathFmts[] = {
    sGameParamCfdPathFmt,
    sGameSystemCfdPathFmt,
    sGameMailTableCfdPathFmt,
    sGameNewBattleCfdPathFmt,
};
float s_ratio[] = {1.35f, 1.25f, 1.1f, 1.0f};

struct GameNameRow
{
    char* m_prefix;
    char* m_name;
    char* m_artPrefix;
    char* m_artName;
    char* m_namePlural;
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
inline int CGBaseObj::GetCID()
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
    int languageId;

    switch (static_cast<unsigned char>(OSSetProgressiveMode())) {
    case 5:
    default:
        languageId = 1;
        break;

    case 1:
        languageId = 2;
        break;

    case 2:
        languageId = 4;
        break;

    case 3:
        languageId = 5;
        break;

    case 4:
        languageId = 3;
        break;
    }
    Game.m_gameWork.m_languageId = static_cast<unsigned char>(languageId);

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
    gCFlatRuntime().CFlatRuntime::Init();
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
	gCFlatRuntime().CFlatRuntime::Quit();

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
	System.AddScenegraph(reinterpret_cast<CProcess*>(&DbgMenuPcs), 0);

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
			System.Printf(const_cast<char*>(sGameInvalidSceneFmt));
		}

		switch (m_currentSceneId) {
		case 0:
		case 1:
			break;
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
			System.AddScenegraph(reinterpret_cast<CProcess*>(&GamePcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&PartPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&GbaPcs), 0);
			System.AddScenegraph(reinterpret_cast<CProcess*>(&MiniGamePcs), 0);
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
		case 0:
		case 1:
			break;
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
			System.RemoveScenegraph(reinterpret_cast<CProcess*>(&GamePcs), 0);
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

	System.RemoveScenegraph(reinterpret_cast<CProcess*>(&DbgMenuPcs), 0);
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

    m_nextScriptFlags = 1;
    clearWork();

    memset(&m_gameWork.m_gameDataStartMarker, 0, kGameWorkDataClearSize);
    memset(m_gameWork.m_wmBackupParams, 0xFF, sizeof(m_gameWork.m_wmBackupParams));

    *reinterpret_cast<u32*>(&m_gameWork.m_scriptSysVal0) = 1;
    m_gameWork.m_chaliceElement = 1;
    strcpy(m_gameWork.m_townName, m_gameWork.m_languageId == 3 ? s_townNameTepa : s_townNameTipa);

    m_gameWork.m_gameInitFlag = 1;

    if (strlen(m_startScriptName) != 0) {
        strcpy(scriptName, m_startScriptName);
        m_nextScript = *reinterpret_cast<CNextScript*>(scriptName);
        m_newGameFlag = 1;
    }

    if (m_newGameFlag == 0) {
        mapVariant = m_currentMapVariantId;
        mapId = m_currentMapId;

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

    CGameWork* work = &game->m_gameWork;
    memset(&work->m_gameDataStartMarker, 0, kGameWorkDataClearSize);
    memset(work->m_wmBackupParams, 0xFF, sizeof(work->m_wmBackupParams));

    *reinterpret_cast<unsigned int*>(&game->m_gameWork.m_scriptSysVal0) = 1;
    game->m_gameWork.m_chaliceElement = 1;
    strcpy(game->m_gameWork.m_townName, game->m_gameWork.m_languageId == 3 ? s_townNameTepa : s_townNameTipa);
    CFlatRuntime2Storage().ResetNewGame();
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

    CFlatRuntime2Storage().CFlatRuntime2::Destroy();

    for (i = 0; i < 4; i++) {
        m_cFlatDataArr[i].Destroy();
    }

    unkCFlatData0[0] = 0;
    unkCFlatData0[1] = 0;
    unkCFlatData0[2] = 0;
    m_partyObjArr[0] = 0;
    m_scriptFoodBase[0] = 0;
    m_partyObjArr[1] = 0;
    m_scriptFoodBase[1] = 0;
    m_partyObjArr[2] = 0;
    m_scriptFoodBase[2] = 0;
    m_partyObjArr[3] = 0;
    m_scriptFoodBase[3] = 0;

    unk_flat3_0xc7d0 = 0;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            m_scriptWork[i][j][0] = 0;
            m_scriptWork[i + 8][j][0] = 0;
            m_scriptWork[i][j][1] = 0;
            m_scriptWork[i + 8][j][1] = 0;
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

        if (0U < static_cast<unsigned int>(mapLightHolderArr->GetSize())) {
            (*mapLightHolderArr)[0]->GetLightHolder(&holderColor, 0);
        }

        for (int i = 0; i < 2; i++) {
            CharaPcs.m_viewerAmbientColor[i] = holderColor;

            for (u32 j = 0; j < 3; j++) {
                if ((j + 1) < static_cast<u32>(mapLightHolderArr->GetSize())) {
                    (*mapLightHolderArr)[j + 1]->GetLightHolder(&holderColor, &holderVec);
                }

                CharaPcs.m_viewerDiffuseColor[i][j] = holderColor;

                if (i == 0) {
                    CharaPcs.m_viewerDiffusePos[j] = holderVec;
                }
            }
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

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            m_scriptWork[i][j][0] = 0;
            m_scriptWork[i + 8][j][0] = 0;
            m_scriptWork[i][j][1] = 0;
            m_scriptWork[i + 8][j][1] = 0;
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
    const char* assetNameBlock = sGameAssetNameBlock;

    if (m_newGameFlag == 0) {
        return;
    }

    m_newGameFlag = 0;
    Graphic._WaitDrawDone(const_cast<char*>(assetNameBlock + kGameCpp), 0x205);

    if ((u32)System.m_execParam >= 3) {
        System.Printf(const_cast<char*>(assetNameBlock + kScriptWillChangeMsg));
    }

    System.ScriptChanging(m_nextScript.m_name);

    if (strcmp(m_nextScript.m_name, s_defaultScriptName) != 0) {
        if (m_cfdLoadedFlag == 0) {
            CFlatRuntime2Storage().CFlatRuntime2::Destroy();
            loadCfd();
            m_cfdLoadedFlag = 1;

            if ((u32)System.m_execParam >= 3) {
                System.Printf(const_cast<char*>(assetNameBlock + kScriptResidentLoadedMsg));
            }
        }

        if (m_assetsLoadedFlag == 0) {
            SoundPcs.createLoad();
            CharaPcs.createLoad();
            PartPcs.createLoad();
            m_assetsLoadedFlag = 1;

            if ((u32)System.m_execParam >= 3) {
                System.Printf(const_cast<char*>(assetNameBlock + kCoreResidentLoadedMsg));
            }
        }
    }

    int scriptResult = CFlatRuntime2Storage().Load(m_nextScript.m_name);
    strcpy(m_currentScriptName, m_nextScript.m_name);

    if ((int)m_nextScriptFlags != 0) {
        System.Printf(const_cast<char*>(s_gameDebugMarker));
        System.Printf(const_cast<char*>(assetNameBlock + kNewGameInitMsg));
        System.Printf(const_cast<char*>(s_gameDebugMarker));

        CGame* game = &Game;

        CGameWork* work = &game->m_gameWork;
        memset(&work->m_gameDataStartMarker, 0, kGameWorkDataClearSize);
        memset(work->m_wmBackupParams, 0xFF, sizeof(work->m_wmBackupParams));

        *reinterpret_cast<unsigned int*>(&game->m_gameWork.m_scriptSysVal0) = 1;
        game->m_gameWork.m_chaliceElement = 1;
        strcpy(game->m_gameWork.m_townName, game->m_gameWork.m_languageId == 3 ? s_townNameTepa : s_townNameTipa);
        CFlatRuntime2Storage().ResetNewGame();
        Chara.InitFurTexBuffer();
        m_nextScriptFlags = 0;
    }

    System.ScriptChanged(m_nextScript.m_name, scriptResult);

    if ((u32)System.m_execParam >= 3) {
        System.Printf(const_cast<char*>(assetNameBlock + kScriptChangedMsg));
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
    if (param5 != 0) {
        Graphic._WaitDrawDone(const_cast<char*>(s_game_cpp), 0x24E);
        System.MapChanging(mapId, mapVariant);

        m_currentMapId = mapId;
        m_currentMapVariantId = mapVariant;

        MapPcs.LoadMap(
            mapId, mapVariant, param4 != 0 ? (void*)0x800000 : 0, param4 != 0 ? 0x580000 : 0, 0);

        PartPcs.LoadFieldPdt(
            mapId, mapVariant, param4 != 0 ? (void*)0xD80000 : 0, param4 != 0 ? 0x80000 : 0, 0);

        System.MapChanged(mapId, mapVariant, 1);
    } else {
        u8 loadStep = param4;
        MapPcs.LoadMap(
            mapId,
            mapVariant,
            param4 != 0 ? (void*)0x800000 : 0,
            param4 != 0 ? 0x580000 : 0,
            loadStep);

        loadStep = param4;

        PartPcs.LoadFieldPdt(
            mapId,
            mapVariant,
            param4 != 0 ? (void*)0xD80000 : 0,
            param4 != 0 ? 0x80000 : 0,
            loadStep);
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

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            m_scriptWork[i][j][0] = 0;
            m_scriptWork[i + 8][j][0] = 0;
            m_scriptWork[i][j][1] = 0;
            m_scriptWork[i + 8][j][1] = 0;
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

        sprintf(path, sGameCfdPathFmts[i], localLangDirs[Game.m_gameWork.m_languageId]);
        CFile::CHandle* handle = File.Open(path, 0, CFile::PRI_LOW);

        if (handle != nullptr)
        {
            File.Read(handle);
            File.SyncCompleted(handle);
            m_cFlatDataArr[i].Create(File.m_readBuffer);
            File.Close(handle);
        }
    }

    unkCFlatData0[0] = (unsigned int)m_cFlatDataArr[0].Data(0).m_data;
    unkCFlatData0[1] = (unsigned int)m_cFlatDataArr[0].Data(1).m_data;
    unkCFlatData0[2] = (unsigned int)m_cFlatDataArr[0].Data(2).m_data;
    m_romLetterWorkBase = (unsigned int)m_cFlatDataArr[2].Data(0).m_data;
    unk_flat3_field_8_0xc7dc = (unsigned int)m_cFlatDataArr[3].Data(0).m_data;
    unk_flat3_field_1C_0xc7d8 = (unsigned int)m_cFlatDataArr[3].Data(1).m_data;
    unk_flat3_count_0xc7d4 = m_cFlatDataArr[3].Data(1).m_size / 0x1A;
    unk_flat3_field_30_0xc7e0 = (unsigned int)m_cFlatDataArr[3].Data(2).m_data;
    m_bossArtifactBase = reinterpret_cast<CBossArtifactStage*>(m_cFlatDataArr[3].Data(3).m_data);
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
            m_partyMinX = (m_partyMinX < partyObj->m_worldPosition.x) ? m_partyMinX : partyObj->m_worldPosition.x;
            m_partyMinY = (m_partyMinY < partyObj->m_worldPosition.y) ? m_partyMinY : partyObj->m_worldPosition.y;
            m_partyMinZ = (m_partyMinZ < partyObj->m_worldPosition.z) ? m_partyMinZ : partyObj->m_worldPosition.z;
            m_partyMaxX = (m_partyMaxX > partyObj->m_worldPosition.x) ? m_partyMaxX : partyObj->m_worldPosition.x;
            m_partyMaxY = (m_partyMaxY > partyObj->m_worldPosition.y) ? m_partyMaxY : partyObj->m_worldPosition.y;
            m_partyMaxZ = (m_partyMaxZ > partyObj->m_worldPosition.z) ? m_partyMaxZ : partyObj->m_worldPosition.z;
        }
    }

    Wind.Frame();
    CFlatRuntime2Storage().Calc();
    gCFlatRuntime().ResetPerformance();
    CFlatRuntime2Storage().CFlatRuntime2::Frame(1, 0);

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
	CFlatRuntime2Storage().CFlatRuntime2::Frame(0, 1);
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
static inline void loadPermanentScriptVars(char* scriptData)
{
    int scriptOffset = 0;
    int entryOffset = 0;
    int i = 0;

    while (i < CFlatPermanentVarCount()) {
        int flagIndex = entryOffset + 1;
        if ((CFlatPermanentVarDefs()[flagIndex] & 0x20) != 0) {
            CFlatPermanentVarWord(entryOffset) = *reinterpret_cast<u32*>(scriptData + scriptOffset);
            scriptOffset += 4;
        }

        entryOffset += 4;
        i++;
    }
}

void CGame::LoadScript(char* scriptData)
{
    loadPermanentScriptVars(scriptData);
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
static inline void savePermanentScriptVars(char* scriptData)
{
    int scriptOffset = 0;
    int i = 0;
    int entryOffset = 0;

    while (i < CFlatPermanentVarCount()) {
        int flagIndex = entryOffset + 1;
        if ((CFlatPermanentVarDefs()[flagIndex] & 0x20) != 0) {
            *reinterpret_cast<u32*>(scriptData + scriptOffset) = CFlatPermanentVarWord(entryOffset);
            scriptOffset += 4;
        }

        entryOffset += 4;
        i++;
    }
}

void CGame::SaveScript(char* scriptData)
{
    memset(scriptData, 0, kGameScriptSaveDataSize);
    savePermanentScriptVars(scriptData);
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
	char* callbackFmtBase = const_cast<char*>(sGameAssetNameBlock);
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
	CFlatRuntime2Storage().CFlatRuntime2::Frame(0, 2);
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
    static s16 s_top[] = {0, 2, 4, 0};

    int stage =
        Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
    if (2 < stage) {
        stage = 2;
    }

    int scaledAmount = (int)((float)amount * s_ratio[ratioIndex - 1]);
    int stageBase = s_top[stage];

    u16 thresholds[4];
    memset(thresholds, 0, 8);

    int stageIndex = (int)Game.m_gameWork.m_bossArtifactStageIndex;
    int stageByteOffset = stageIndex * sizeof(CBossArtifactStage);
    CBossArtifactStage* artifactBase = Game.m_bossArtifactBase;
    CBossArtifactStage* stageArtifacts =
        reinterpret_cast<CBossArtifactStage*>(reinterpret_cast<char*>(artifactBase) + stageByteOffset);
    int artifactRank = 3;

    thresholds[1] = stageArtifacts->m_rankThresholds[1];
    thresholds[2] = stageArtifacts->m_rankThresholds[2];
    thresholds[3] = stageArtifacts->m_rankThresholds[3];

    if (((scaledAmount < (s16)thresholds[3]) && (artifactRank = 2, scaledAmount < (s16)thresholds[2])) &&
        (artifactRank = 1, scaledAmount < (s16)thresholds[1])) {
        artifactRank = 0;
    }

    scaledAmount = rand();
    int divisor = artifactRank + 1;
    int entriesByteOffset = stageByteOffset + offsetof(CBossArtifactStage, m_entries);
    int quotient = scaledAmount / divisor;
    stageBase += scaledAmount - quotient * divisor;
    return reinterpret_cast<int>(reinterpret_cast<char*>(artifactBase) +
        entriesByteOffset + stageBase * (int)sizeof(CBossArtifactEntry));
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
    CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(m_scriptFoodBase[playerIndex]);
    u16 level = caravanWork->m_letterMeta[foodIndex];
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
    CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(m_scriptFoodBase[playerIndex]);

    posA.x = caravanWork->m_targetCursorPosA.x;
    posA.y = caravanWork->m_targetCursorPosA.y;
    posA.z = caravanWork->m_targetCursorPosA.z;

    caravanWork = reinterpret_cast<CCaravanWork*>(m_scriptFoodBase[playerIndex]);
    posB.x = caravanWork->m_targetCursorPosB.x;
    posB.y = caravanWork->m_targetCursorPosB.y;
    posB.z = caravanWork->m_targetCursorPosB.z;
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
    baseObj = reinterpret_cast<CGBaseObj*>(runtime->CFlatRuntime2::intToClass((int)ifParam.m_classId));
    particleIndex = ifParam.m_particleIndex;
    if (particleIndex == 0) {
        return 0;
    }

    u16 behaviorFlags = (u16)baseObj->GetCID();
    if ((behaviorFlags & 0x6D) != 0x6D) {
        return 0;
    }

    CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(reinterpret_cast<CGObject*>(baseObj)->m_scriptHandle);
    specialInfo = caravanWork->m_joybusCaravanId;
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
            name = m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5 + 3];
        } else {
            name = m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5 + 1];
        }

        sprintf(out, s_numNameFmt, count, name);
    } else {
        char** itemTable = m_cFlatDataArr[1].TableStrings(0);
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
    GameNameRow* itemTable = reinterpret_cast<GameNameRow*>(m_cFlatDataArr[1].TableStrings(0));
    unsigned char hasSeparator = 0;
    char* prefix = itemTable[itemIndex].m_artPrefix;
    char* itemName = itemTable[itemIndex].m_artName;

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
        itemName = m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5 + 3];
    } else {
        itemName = m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5 + 1];
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
            name = m_cFlatDataArr[1].TableStrings(1)[monIndex * 5 + 3];
        } else {
            name = m_cFlatDataArr[1].TableStrings(1)[monIndex * 5 + 1];
        }

        sprintf(out, s_numNameFmt, count, name);
    } else {
        char** monTable = m_cFlatDataArr[1].TableStrings(1);
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
    GameNameRow* monTable = reinterpret_cast<GameNameRow*>(m_cFlatDataArr[1].TableStrings(1));
    unsigned char hasSeparator = 0;
    char* prefix = monTable[monIndex].m_artPrefix;
    char* monName = monTable[monIndex].m_artName;

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
        monName = m_cFlatDataArr[1].TableStrings(1)[monIndex * 5 + 3];
    } else {
        monName = m_cFlatDataArr[1].TableStrings(1)[monIndex * 5 + 1];
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
    return m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5 + 1];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetItemArt(int itemIndex)
{
    return m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetItemNames(int itemIndex)
{
    return m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5 + 3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetItemArts(int itemIndex)
{
    return m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5 + 2];
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
    return m_cFlatDataArr[1].TableStrings(1)[monIndex * 5 + 1];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetMonArt(int monIndex)
{
    return m_cFlatDataArr[1].TableStrings(1)[monIndex * 5];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetMonNames(int monIndex)
{
    return m_cFlatDataArr[1].TableStrings(1)[monIndex * 5 + 3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetMonArts(int monIndex)
{
    return m_cFlatDataArr[1].TableStrings(1)[monIndex * 5 + 2];
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
