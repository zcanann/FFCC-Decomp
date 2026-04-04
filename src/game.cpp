#include "ffcc/game.h"

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
#include "ffcc/p_camera.h"
#include "ffcc/p_FunnyShape.h"
#include "ffcc/p_graphic.h"
#include "ffcc/p_light.h"
#include "ffcc/p_map.h"
#include "ffcc/p_mc.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_usb.h"

#include <string.h>

#include <dolphin/os/OSMemory.h>
#include <dolphin/os/OSRtc.h>
#include <string.h>

typedef void* ConstructorDestructor;

extern "C" {
void Printf__7CSystemFPce(CSystem*, const char*, ...);
unsigned int AddScenegraph__7CSystemFP8CProcessi(CSystem*, void*, int);
void RemoveScenegraph__7CSystemFP8CProcessi(CSystem*, void*, int);
void ExecScenegraph__7CSystemFv(CSystem*);
void Quit__11CDbgMenuPcsFv(void*);
void Quit__7CGbaPcsFv(void*);
void Quit__7CUSBPcsFv(void*);
void Quit__9CLightPcsFv(void*);
void Quit__7CMapPcsFv(void*);
void Quit__18CMaterialEditorPcsFv(void*);
void Quit__14CFunnyShapePcsFv(void*);
void Quit__11CGraphicPcsFv(void*);
void createLoad__8CPartPcsFv(void*);
void pppDeleteAll__8CPartMngFv(void*);
void pppDestroyAll__8CPartMngFv(void*);
int pppGetIfDt__8CPartMngFs(void*, short);
void pppEndPart__8CPartMngFi(void*, int);
void Init__11CGraphicPcsFv(void*);
void Init__9CLightPcsFv(void*);
void Init__7CMapPcsFv(void*);
void Init__18CMaterialEditorPcsFv(void*);
void Init__14CFunnyShapePcsFv(void*);
void Init__7CUSBPcsFv(void*);
void Init__7CGbaPcsFv(void*);
void Init__11CDbgMenuPcsFv(void*);
int sprintf(char*, const char*, ...);
int GetMapObjIdx__7CMapMngFUs(void*, unsigned short);
void SetMapObjLMtx__7CMapMngFiPA4_f(void*, int, Mtx);
void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, int, int, int, int, void*, void*);
void Draw__5CWindFv(void*);
void CheckMenu__10CGPartyObjFv();
void LoadMap__7CMapPcsFiiPvUlUc(void*, int, int, void*, unsigned long, unsigned char);
void LoadFieldPdt__8CPartPcsFiiPvUlUc(void*, int, int, void*, unsigned long, unsigned char);
void CheckMenu__10CGPartyObjFv(void);
void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, int, int, int, int, void*, void*);
unsigned char PartPcs[];
extern const char DAT_801d61dc[];
extern const char DAT_801d60d4[];
extern const char DAT_801d6114[];
extern const char DAT_801d6154[];
extern const char s_game_cpp_801d6190[];
extern const char DAT_801d619c[];
extern const char DAT_801d61b8[];
extern const char DAT_801d6214[];
extern const char DAT_801d6234[];
extern const char DAT_8032f698[];
extern const char DAT_8032f6a0;
extern const char DAT_8032f6a4;
extern const char DAT_8032f6ac;
extern const s16 DAT_8032e3d0[];
const char* s_localLangDirs[] = {
    "jp/",
    "uk/",
    "gr/",
    "it/",
    "fr/",
    "sp/",
};
const char* PTR_s_dvd__scft_param_cfd_801e8344[] = {
    "dvd/%scft/param.cfd",
    "dvd/%scft/c_system.cfd",
    "dvd/%scft/mail_tbl.cfd",
    "dvd/%scft/newbattle.cfd",
};
int sprintf(char*, const char*, ...);
int rand(void);
void __construct_array(void*, ConstructorDestructor, ConstructorDestructor, unsigned long, unsigned long);
void* __register_global_object(void*, void*, void*);
void __ct__12CCaravanWorkFv(void*);
void __dt__12CCaravanWorkFv(void*, int);
void __ct__8CMonWorkFv(void*);
void __dt__8CMonWorkFv(void*, int);
void __ct__9CFlatDataFv(void*);
void __dt__9CFlatDataFv(void*, int);
void ResetNewGame__13CFlatRuntime2Fv(void*);
void InitFurTexBuffer__6CCharaFv(void*);
void* __vt__8CManager[];
CCaravanWork* dtor_800A2B9C(CCaravanWork*, short);
CMonWork* dtor_8009E9B4(CMonWork*, short);
CFlatData* dtor_800980B4(CFlatData*, short);
void __dt__5CGameFv(void*, int);
void* __vt__5CGame[];
}

const float FLOAT_8032f688 = 1.0E+10;
const float FLOAT_8032f68c = -1.0E+10;
const float FLOAT_8032f690 = 0.0;
const float FLOAT_8032f694 = 0.001;
static const s16 s_bossArtifactStartTable[] = {0, 4, 8};
float s_ratio[] = {0.4f, 0.55f, 0.7f, 0.85f};
static const char s_numNameFmt[] = "%d%s";
static const char s_nameJoinFmt[] = "%s%s%s";
static const char s_nameSep[] = " ";
static const char s_nameNoSep[] = "";
static const char s_mainStageName[] = "game_main";
static const char s_debugStageName[] = "game_debug";

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

// Uninitialized
unsigned char GameDtorChain[0x10];
static float FLOAT_8032ec40;
static bool BOOL_8032ec44;

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
 * PAL Address: 0x80016220
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_game_cpp(void)
{
    CGame* game = &Game;
    const char* townName;

    *reinterpret_cast<void**>(game) = __vt__8CManager;
    *reinterpret_cast<void**>(game) = __vt__5CGame;
    memset(reinterpret_cast<unsigned char*>(game) + 0xF, 0, 0x13E1);
    memset(reinterpret_cast<unsigned char*>(game) + 0x20, 0xFF, 0x10);

    *reinterpret_cast<unsigned int*>(&game->m_gameWork.m_scriptSysVal0) = 1;
    game->m_gameWork.m_chaliceElement = 1;

    townName = &DAT_8032f6ac;
    if (game->m_gameWork.m_languageId == 3) {
        townName = &DAT_8032f6a4;
    }
    strcpy(game->m_gameWork.m_townName, townName);
    game->m_gameWork.m_gameInitFlag = 1;

    __construct_array(
        game->m_caravanWorkArr,
        reinterpret_cast<ConstructorDestructor>(__ct__12CCaravanWorkFv),
        reinterpret_cast<ConstructorDestructor>(dtor_800A2B9C),
        0xC30,
        9
    );
    __construct_array(
        game->m_monWorkArr,
        reinterpret_cast<ConstructorDestructor>(__ct__8CMonWorkFv),
        reinterpret_cast<ConstructorDestructor>(dtor_8009E9B4),
        0x110,
        0x40
    );

    game->m_partyMinZ = FLOAT_8032f688;
    game->m_partyMinY = FLOAT_8032f688;
    game->m_partyMinX = FLOAT_8032f688;
    game->m_partyMaxZ = FLOAT_8032f68c;
    game->m_partyMaxY = FLOAT_8032f68c;
    game->m_partyMaxX = FLOAT_8032f68c;

    __construct_array(
        game->m_cFlatDataArr,
        reinterpret_cast<ConstructorDestructor>(__ct__9CFlatDataFv),
        reinterpret_cast<ConstructorDestructor>(dtor_800980B4),
        0x14D4,
        4
    );

    __register_global_object(&Game, reinterpret_cast<void*>(__dt__5CGameFv), GameDtorChain);
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
CGame::CGame()
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
    Init__11CGraphicPcsFv(&GraphicsPcs);
    gChara.Init();
    Init__9CLightPcsFv(&LightPcs);
    CharaPcs.Init();
    Init__7CMapPcsFv(&MapPcs);
    Init__18CMaterialEditorPcsFv(&MaterialEditorPcs);
    Init__14CFunnyShapePcsFv(&FunnyShapePcs);
    Init__7CUSBPcsFv(&USBPcs);
    MenuPcs.Init();
    Init__7CGbaPcsFv(&GbaPcs);
    GetMcPcsSingleton()->Init();
    Init__11CDbgMenuPcsFv(&DbgMenuPcs);

    m_mainStage = Memory.CreateStage(0x106000, const_cast<char*>(s_mainStageName), 0);
    if (OSGetConsoleSimulatedMemSize() == 0x3000000) {
        m_debugStage = Memory.CreateStage(0x220000, const_cast<char*>(s_debugStageName), 1);
    }

    m_sceneId = 4;
    m_mapId = 3;
    m_mapVariant = 0;
    memset(m_currentScriptName, 0, sizeof(m_currentScriptName));
    memset(m_startScriptName, 0, sizeof(m_startScriptName));
    m_frameCounterEnable = 1;
    reinterpret_cast<CFlatRuntime*>(CFlat)->Init();
    unkFloat_0xca10 = FLOAT_8032f694;
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
	reinterpret_cast<CFlatRuntime*>(CFlat)->Quit();

	if (m_debugStage != 0) {
		Memory.DestroyStage(m_debugStage);
	}

	Memory.DestroyStage(m_mainStage);
	Quit__11CDbgMenuPcsFv(&DbgMenuPcs);
	GetMcPcsSingleton()->Quit();
	Quit__7CGbaPcsFv(&GbaPcs);
	MenuPcs.Quit();
	Quit__7CUSBPcsFv(&USBPcs);
	gChara.Quit();
	CharaPcs.Quit();
	Quit__9CLightPcsFv(&LightPcs);
	Quit__7CMapPcsFv(&MapPcs);
	Quit__18CMaterialEditorPcsFv(&MaterialEditorPcs);
	Quit__14CFunnyShapePcsFv(&FunnyShapePcs);
	Quit__11CGraphicPcsFv(&GraphicsPcs);
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
		createLoad__8CPartPcsFv(&PartPcs);
		m_assetsLoadedFlag = 1;
		if ((u32)System.m_execParam < 3) {
			return;
		}

		System.Printf(const_cast<char*>(DAT_801d61dc));
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
	AddScenegraph__7CSystemFP8CProcessi(&System, &SystemPcs, 0);
	AddScenegraph__7CSystemFP8CProcessi(&System, &GraphicsPcs, 0);
	AddScenegraph__7CSystemFP8CProcessi(&System, &LightPcs, 0);
	AddScenegraph__7CSystemFP8CProcessi(&System, &MiniGamePcs, 0);

	do {
		m_cfdLoadedFlag = 0;
		m_assetsLoadedFlag = 0;

		Memory.IncHeapWalkerLevel();

		m_currentSceneId = m_sceneId;
		m_currentMapId = m_mapId;
		m_currentMapVariantId = m_mapVariant;
		strcpy(m_currentScriptName, m_sceneScript + 4);

		switch (m_currentSceneId) {
		case 2:
			AddScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 1);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 1);
			break;
		case 3:
			AddScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 2);
			AddScenegraph__7CSystemFP8CProcessi(&System, &MapPcs, 1);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 6);
			break;
		case 4:
			AddScenegraph__7CSystemFP8CProcessi(&System, &MenuPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &MapPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 6);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &Game, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &PartPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &GbaPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &DbgMenuPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, GetMcPcsSingleton(), 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &SoundPcs, 0);
			break;
		case 5:
			AddScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 3);
			AddScenegraph__7CSystemFP8CProcessi(&System, &MaterialEditorPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &LightPcs, 0);
			break;
		case 6:
			AddScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 4);
			AddScenegraph__7CSystemFP8CProcessi(&System, &FunnyShapePcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &LightPcs, 0);
			break;
		case 7:
			AddScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 5);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 2);
			AddScenegraph__7CSystemFP8CProcessi(&System, &MapPcs, 1);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 6);
			AddScenegraph__7CSystemFP8CProcessi(&System, &PartPcs, 1);
			break;
		}

		ExecScenegraph__7CSystemFv(&System);

		switch (m_currentSceneId) {
		case 2:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 1);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 1);
			break;
		case 3:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 2);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 6);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &MapPcs, 1);
			break;
		case 4:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &SoundPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, GetMcPcsSingleton(), 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 6);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &MapPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &PartPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &GbaPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &Game, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &MenuPcs, 0);
			break;
		case 5:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 3);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &MaterialEditorPcs, 0);
			break;
		case 6:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 4);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &FunnyShapePcs, 0);
			break;
		case 7:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 5);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CameraPcs, 6);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 2);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &MapPcs, 1);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &PartPcs, 1);
			break;
		}

		Memory.HeapWalker();
		Memory.DecHeapWalkerLevel();
	} while (m_sceneId != 0);

	RemoveScenegraph__7CSystemFP8CProcessi(&System, &MiniGamePcs, 0);
	RemoveScenegraph__7CSystemFP8CProcessi(&System, &LightPcs, 0);
	RemoveScenegraph__7CSystemFP8CProcessi(&System, &GraphicsPcs, 0);
	RemoveScenegraph__7CSystemFP8CProcessi(&System, &SystemPcs, 0);
}

static const char s_defaultTownName[] = "Tipa";
static const char s_italianTownName[] = "TipaItalia";

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
    int mapVariant;
    int mapId;

    m_nextScript.m_flags = 1;
    clearWork();

    memset(&m_gameWork.m_gameDataStartMarker, 0, 0x13E1);
    memset(m_gameWork.m_wmBackupParams, 0xFF, sizeof(m_gameWork.m_wmBackupParams));

    m_gameWork.m_scriptSysVal0 = 0;
    m_gameWork.m_scriptSysVal1 = 0;
    m_gameWork.m_scriptSysVal2 = 0;
    m_gameWork.m_scriptSysVal3 = 1;
    m_gameWork.m_chaliceElement = 1;

    if (m_gameWork.m_languageId == 3) {
        strcpy(m_gameWork.m_townName, s_italianTownName);
    } else {
        strcpy(m_gameWork.m_townName, s_defaultTownName);
    }

    m_gameWork.m_gameInitFlag = 1;

    if (strlen(m_startScriptName) != 0) {
        strcpy(m_nextScript.m_name, m_startScriptName);
        m_newGameFlag = 1;
    }

    if (m_newGameFlag == 0) {
        mapVariant = m_currentMapVariantId;
        mapId = m_currentMapId;

        Graphic._WaitDrawDone(const_cast<char*>(s_game_cpp_801d6190), 0x24E);
        System.MapChanging(mapId, mapVariant);

        m_currentMapId = mapId;
        m_currentMapVariantId = mapVariant;

        LoadMap__7CMapPcsFiiPvUlUc(&MapPcs, mapId, mapVariant, 0, 0, 0);
        LoadFieldPdt__8CPartPcsFiiPvUlUc(&PartPcs, mapId, mapVariant, 0, 0, 0);

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
    Printf__7CSystemFPce(&System, &DAT_8032f6a0);
    Printf__7CSystemFPce(&System, DAT_801d6214);
    Printf__7CSystemFPce(&System, &DAT_8032f6a0);

    CGame* game = &Game;

    memset(&game->m_gameWork.m_gameDataStartMarker, 0, 0x13E1);
    memset(game->m_gameWork.m_wmBackupParams, 0xFF, sizeof(game->m_gameWork.m_wmBackupParams));

    *reinterpret_cast<unsigned int*>(&game->m_gameWork.m_scriptSysVal0) = 1;
    game->m_gameWork.m_chaliceElement = 1;
    strcpy(game->m_gameWork.m_townName, game->m_gameWork.m_languageId == 3 ? &DAT_8032f6a4 : &DAT_8032f6ac);
    ResetNewGame__13CFlatRuntime2Fv(CFlat);
    InitFurTexBuffer__6CCharaFv(&Chara);
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

    *((u8*)&Sound + 0x8892) = 0x7F;

    CPtrArray<CMapLightHolder*>* mapLightHolderArr =
        reinterpret_cast<CPtrArray<CMapLightHolder*>*>(reinterpret_cast<u8*>(&MapMng) + 0x21450);

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
void CGame::clearWorkMap()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::clearWorkScript()
{
	// TODO
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
    Graphic._WaitDrawDone(const_cast<char*>(s_game_cpp_801d6190), 0x205);

    if ((u32)System.m_execParam > 2) {
        System.Printf(const_cast<char*>(DAT_801d619c));
    }

    System.ScriptChanging(m_nextScript.m_name);

    if (strcmp(m_nextScript.m_name, DAT_8032f698) != 0) {
        if (m_cfdLoadedFlag == 0) {
            gCFlatRuntime2.Destroy();
            loadCfd();
            m_cfdLoadedFlag = 1;

            if ((u32)System.m_execParam > 2) {
                System.Printf(const_cast<char*>(DAT_801d61b8));
            }
        }

        if (m_assetsLoadedFlag == 0) {
            SoundPcs.createLoad();
            CharaPcs.createLoad();
            createLoad__8CPartPcsFv(&PartPcs);
            m_assetsLoadedFlag = 1;

            if ((u32)System.m_execParam > 2) {
                System.Printf(const_cast<char*>(DAT_801d61dc));
            }
        }
    }

    int scriptResult = gCFlatRuntime2.Load(m_nextScript.m_name);
    strcpy(m_currentScriptName, m_nextScript.m_name);

    if (m_nextScript.m_flags != 0) {
        CGame::CGameWork* gameWork;
        const char* townName = &DAT_8032f6ac;

        gameWork = &Game.m_gameWork;

        Printf__7CSystemFPce(&System, &DAT_8032f6a0);
        System.Printf(const_cast<char*>(DAT_801d6214));
        Printf__7CSystemFPce(&System, &DAT_8032f6a0);

        memset(&gameWork->m_gameDataStartMarker, 0, 0x13E1);
        memset(gameWork->m_wmBackupParams, 0xFF, sizeof(gameWork->m_wmBackupParams));

        *reinterpret_cast<unsigned int*>(&gameWork->m_scriptSysVal0) = 1;
        gameWork->m_chaliceElement = 1;

        if (gameWork->m_languageId == 3) {
            townName = &DAT_8032f6a4;
        }

        strcpy(gameWork->m_townName, townName);
        ResetNewGame__13CFlatRuntime2Fv(CFlat);
        InitFurTexBuffer__6CCharaFv(&Chara);
        m_nextScript.m_flags = 0;
    }

    System.ScriptChanged(m_nextScript.m_name, scriptResult);

    if ((u32)System.m_execParam > 2) {
        System.Printf(const_cast<char*>(DAT_801d6234));
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
    u32 hasParamMask;

    if (param5 != 0) {
        Graphic._WaitDrawDone(const_cast<char*>(s_game_cpp_801d6190), 0x24E);
        System.MapChanging(mapId, mapVariant);

        m_currentMapId = mapId;
        m_currentMapVariantId = mapVariant;
        hasParamMask = (u32)((-param4 | param4) >> 31);

        LoadMap__7CMapPcsFiiPvUlUc(
            &MapPcs, mapId, mapVariant, (void*)(hasParamMask & 0x800000), hasParamMask & 0x580000, 0);

        hasParamMask = (u32)((-param4 | param4) >> 31);
        LoadFieldPdt__8CPartPcsFiiPvUlUc(
            &PartPcs, mapId, mapVariant, (void*)(hasParamMask & 0xD80000), hasParamMask & 0x80000, 0);

        System.MapChanged(mapId, mapVariant, 1);
    } else {
        hasParamMask = (u32)((-param4 | param4) >> 31);
        LoadMap__7CMapPcsFiiPvUlUc(
            &MapPcs, mapId, mapVariant, (void*)(hasParamMask & 0x800000), hasParamMask & 0x580000, param4 & 0xFF);

        hasParamMask = (u32)((-param4 | param4) >> 31);
        LoadFieldPdt__8CPartPcsFiiPvUlUc(
            &PartPcs, mapId, mapVariant, (void*)(hasParamMask & 0xD80000), hasParamMask & 0x80000, (u8)param4);
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
	pppDeleteAll__8CPartMngFv(&PartMng);
	pppDestroyAll__8CPartMngFv(&PartMng);
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

    *((u8*)&Sound + 0x8892) = 0x7F;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MapChanging(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MapChanged(int, int, int)
{
	// TODO
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
    };

    char path[0x10C];

    for (int i = 0; i < 4; i++)
    {
        const char* localLangDirs[6];
        localLangDirs[0] = s_localLangDirs[0];
        localLangDirs[1] = s_localLangDirs[1];
        localLangDirs[2] = s_localLangDirs[2];
        localLangDirs[3] = s_localLangDirs[3];
        localLangDirs[4] = s_localLangDirs[4];
        localLangDirs[5] = s_localLangDirs[5];

        sprintf(path, PTR_s_dvd__scft_param_cfd_801e8344[i], localLangDirs[m_gameWork.m_languageId]);
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
    m_scriptFoodBase[0] = (unsigned int)flatData[2].m_data[0].m_data;
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

    m_partyMinZ = FLOAT_8032f688;
    m_partyMinY = FLOAT_8032f688;
    m_partyMinX = FLOAT_8032f688;
    m_partyMaxZ = FLOAT_8032f68c;
    m_partyMaxY = FLOAT_8032f68c;
    m_partyMaxX = FLOAT_8032f68c;

    for (int i = 0; i < 4; i++) {
        CGPartyObj* partyObj = m_partyObjArr[i];

        if (partyObj != 0) {
            position = partyObj->m_worldPosition.x;
            if (m_partyMinX < position) {
                position = m_partyMinX;
            }
            m_partyMinX = position;

            position = partyObj->m_worldPosition.y;
            if (m_partyMinY < position) {
                position = m_partyMinY;
            }
            m_partyMinY = position;

            position = partyObj->m_worldPosition.z;
            if (m_partyMinZ < position) {
                position = m_partyMinZ;
            }
            m_partyMinZ = position;

            position = partyObj->m_worldPosition.x;
            if (position < m_partyMaxX) {
                position = m_partyMaxX;
            }
            m_partyMaxX = position;

            position = partyObj->m_worldPosition.y;
            if (position < m_partyMaxY) {
                position = m_partyMaxY;
            }
            m_partyMaxY = position;

            position = partyObj->m_worldPosition.z;
            if (position < m_partyMaxZ) {
                position = m_partyMaxZ;
            }
            m_partyMaxZ = position;
        }
    }

    Wind.Frame();
    gCFlatRuntime2.Calc();
    reinterpret_cast<CFlatRuntime*>(CFlat)->ResetPerformance();
    gCFlatRuntime2.Frame(1, 0);

    if ((m_currentMapId == 0x21) && ((mapObjIdx = GetMapObjIdx__7CMapMngFUs(&MapMng, 0)) >= 0)) {
            if (!BOOL_8032ec44) {
                BOOL_8032ec44 = true;
                FLOAT_8032ec40 = FLOAT_8032f690;
            }

            FLOAT_8032ec40 += FLOAT_8032f694;
            PSMTXRotRad(rotMtx, 'y', FLOAT_8032ec40);
            SetMapObjLMtx__7CMapMngFiPA4_f(&MapMng, mapObjIdx, rotMtx);
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
	reinterpret_cast<CFlatRuntime2*>(CFlat)->Frame(0, 1);
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
	CheckMenu__10CGPartyObjFv();
	reinterpret_cast<CFlatRuntime*>(CFlat)->AfterFrame(0);
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
	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	    CFlat, 0, 1, 6, 0, 0, 0);
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
	reinterpret_cast<CFlatRuntime2*>(CFlat)->Draw();
	Wind.Draw();
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
	gCFlatRuntime2.Frame(0, 2);
	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	    CFlat, 0, 1, 5, 0, 0, 0);
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
	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	    &CFlat, 0, 1, 1, 8, stack, 0);
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
void CGame::ParticleFrameCallback(int effectIndex, int scriptLine, int scriptStep, int, int callbackType, Vec* pos)
{
	int ifData = pppGetIfDt__8CPartMngFs(&PartMng, (short)effectIndex);
	*(u8*)(ifData + 7) |= 1 << callbackType;

	if (callbackType == 0) {
		if (System.m_execParam > 2) {
			System.Printf(const_cast<char*>(DAT_801d60d4), scriptLine, scriptStep, effectIndex, pos);
		}
	} else if (callbackType == 1) {
		*(u8*)(ifData + 7) &= ~2;
		pppEndPart__8CPartMngFi(&PartMng, effectIndex);

		if (System.m_execParam > 2) {
			System.Printf(const_cast<char*>(DAT_801d6114), scriptLine, scriptStep, effectIndex, pos);
		}
	} else if (callbackType == 3) {
		pppEndPart__8CPartMngFi(&PartMng, effectIndex);

		if (System.m_execParam > 2) {
			System.Printf(const_cast<char*>(DAT_801d6154), scriptLine, scriptStep, effectIndex, pos);
		}
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
    memset(scriptData, 0, 0x800);

    int scriptOffset = 0;
    int entryOffset = 0;
    int i = 0;

    while (i < *(int*)(CFlat + 4)) {
        if ((*(u8*)(*(int*)(CFlat + 8) + entryOffset + 1) & 0x20) != 0) {
            *(u32*)(scriptData + scriptOffset) = *(u32*)(*(int*)(CFlat + 12) + entryOffset);
            scriptOffset += 4;
        }

        entryOffset += 4;
        i++;
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
    int scriptOffset = 0;
    int entryOffset = 0;
    int i = 0;

    while (i < *(int*)(CFlat + 4)) {
        if ((*(u8*)(*(int*)(CFlat + 8) + entryOffset + 1) & 0x20) != 0) {
            *(u32*)(*(int*)(CFlat + 12) + entryOffset) = *(u32*)(scriptData + scriptOffset);
            scriptOffset += 4;
        }
        entryOffset += 4;
        i++;
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
 * PAL Address: 0x8001440c
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGame::GetBossArtifact(int ratioIndex, int amount)
{
    int iVar5 =
        Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
    if (2 < iVar5) {
        iVar5 = 2;
    }

    s16 stageBase = s_bossArtifactStartTable[iVar5];
    iVar5 = (int)((float)(u32)amount * s_ratio[ratioIndex]);

    s16 local_38[4];
    memset(local_38, 0, 8);

    u32 uVar2 = Game.m_bossArtifactBase;
    int stageIndex = (int)Game.m_gameWork.m_bossArtifactStageIndex;
    int iVar6 = 3;
    int iVar4 = Game.m_bossArtifactBase + stageIndex * 0x168;

    local_38[1] = *(s16*)(iVar4 + 0x162);
    local_38[2] = *(s16*)(iVar4 + 0x164);
    local_38[3] = *(s16*)(iVar4 + 0x166);

    if (((iVar5 < local_38[3]) && (iVar6 = 2, iVar5 < local_38[2])) && (iVar6 = 1, iVar5 < local_38[1])) {
        iVar6 = 0;
    }

    iVar5 = rand();
    return uVar2 + stageIndex * 0x168 + 0x20 +
           ((int)stageBase + (iVar5 - (iVar5 / (iVar6 + 1)) * (iVar6 + 1))) * 8;
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

    runtime = reinterpret_cast<CFlatRuntime2*>(CFlat);
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
        char* itemName = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings[itemIndex * 5 + 3];

        sprintf(out, s_numNameFmt, count, itemName);
    } else {
        char** itemTable = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings;
        unsigned char hasSeparator = 0;
        char* prefix = itemTable[itemIndex * 5];
        char* itemName = itemTable[itemIndex * 5 + 1];

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
        char* monName = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings[monIndex * 5 + 3];

        sprintf(out, s_numNameFmt, count, monName);
    } else {
        char** monTable = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings;
        unsigned char hasSeparator = 0;
        char* prefix = monTable[monIndex * 5];
        char* monName = monTable[monIndex * 5 + 1];

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
void CGame::CGameWork::ClearEvtWork()
{
    memset(m_eventFlags, 0, sizeof(m_eventFlags));
    memset(m_eventWork, 0, sizeof(m_eventWork));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::CGameWork::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::CGameWork::InitNewGame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::CGameWork::ClearScriptChange()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::IsWorldMap()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::IsPartyExist(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetItemName(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetItemArt(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetItemNames(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetItemArts(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetItemName(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetMonName(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetMonArt(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetMonNames(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetMonArts(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetMonName(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGame::CGameWork::CGameWork()
{
	// TODO
}

template class CPtrArray<CMapLightHolder*>;
