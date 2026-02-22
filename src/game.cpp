#include "ffcc/game.h"

#include "ffcc/partyobj.h"
#include "ffcc/system.h"
#include "ffcc/vector.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_minigame.h"
#include "ffcc/p_game.h"
#include "ffcc/map.h"
#include "ffcc/sound.h"
#include "ffcc/graphic.h"
#include "ffcc/file.h"
#include "ffcc/partMng.h"

#include <string.h>

extern CMiniGamePcs MiniGamePcs;

#include <dolphin/os/OSMemory.h>
#include <dolphin/os/OSRtc.h>
#include <string.h>

typedef void* ConstructorDestructor;

extern "C" {
unsigned int AddScenegraph__7CSystemFP8CProcessi(CSystem*, void*, int);
void RemoveScenegraph__7CSystemFP8CProcessi(CSystem*, void*, int);
void ExecScenegraph__7CSystemFv(CSystem*);
void Quit__12CFlatRuntimeFv(void*);
void Destroy__13CFlatRuntime2Fv(void*);
void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
void DestroyMap__7CMapMngFv(void*);
void Quit__11CDbgMenuPcsFv(void*);
void Quit__6CMcPcsFv(void*);
void Quit__7CGbaPcsFv(void*);
void Quit__8CMenuPcsFv(void*);
void Quit__7CUSBPcsFv(void*);
void Quit__6CCharaFv(void*);
void Quit__9CCharaPcsFv(void*);
void Quit__9CLightPcsFv(void*);
void Quit__7CMapPcsFv(void*);
void Quit__18CMaterialEditorPcsFv(void*);
void Quit__14CFunnyShapePcsFv(void*);
void Quit__11CGraphicPcsFv(void*);
void Quit__10CCameraPcsFv(void*);
void createLoad__9CSoundPcsFv(void*);
void createLoad__9CCharaPcsFv(void*);
void createLoad__8CPartPcsFv(void*);
void pppDeleteAll__8CPartMngFv(void*);
void pppDestroyAll__8CPartMngFv(void*);
int pppGetIfDt__8CPartMngFs(void*, short);
void pppEndPart__8CPartMngFi(void*, int);
void Init__10CCameraPcsFv(void*);
void Init__11CGraphicPcsFv(void*);
void Init__6CCharaFv(void*);
void Init__9CLightPcsFv(void*);
void Init__9CCharaPcsFv(void*);
void Init__7CMapPcsFv(void*);
void Init__18CMaterialEditorPcsFv(void*);
void Init__14CFunnyShapePcsFv(void*);
void Init__7CUSBPcsFv(void*);
void Init__8CMenuPcsFv(void*);
void Init__7CGbaPcsFv(void*);
void Init__6CMcPcsFv(void*);
void Init__11CDbgMenuPcsFv(void*);
void Reset__9CCharaPcsFQ29CCharaPcs5RESET(void*, int);
void StopAndFreeAllSe__6CSoundFi(void*, int);
void ClearAll__5CWindFv(void*);
void* CreateStage__7CMemoryFUlPci(void*, unsigned long, const char*, int);
void Init__12CFlatRuntimeFv(void*);
int Load__13CFlatRuntime2FPc(void*, char*);
void ResetNewGame__13CFlatRuntime2Fv(void*);
void InitFurTexBuffer__6CCharaFv(void*);
void Printf__7CSystemFPce(CSystem* system, const char* format, ...);
void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
int intToClass__13CFlatRuntime2Fi(void*, int);
int sprintf(char*, const char*, ...);
void ScriptChanging__7CSystemFPc(CSystem*, char*);
void ScriptChanged__7CSystemFPci(CSystem*, char*, int);
void MapChanging__7CSystemFii(CSystem*, int, int);
void MapChanged__7CSystemFiii(CSystem*, int, int, int);
void Draw__13CFlatRuntime2Fv(void*);
void Frame__13CFlatRuntime2Fii(void*, int, int);
void AfterFrame__12CFlatRuntimeFi(void*, int);
void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, int, int, int, int, void*, void*);
void Draw__5CWindFv(void*);
void CheckMenu__10CGPartyObjFv();
void LoadMap__7CMapPcsFiiPvUlUc(void*, int, int, void*, unsigned long, unsigned char);
void LoadFieldPdt__8CPartPcsFiiPvUlUc(void*, int, int, void*, unsigned long, unsigned char);
void Draw__13CFlatRuntime2Fv(void*);
void Draw__5CWindFv(void*);
void Frame__13CFlatRuntime2Fii(void*, int, int);
void CheckMenu__10CGPartyObjFv(void);
void AfterFrame__12CFlatRuntimeFi(void*, int);
void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, int, int, int, int, void*, void*);
unsigned char CFlat[];
unsigned char PartMng[];
unsigned char McPcs[];
unsigned char GbaPcs[];
unsigned char MenuPcs[];
unsigned char USBPcs[];
unsigned char SoundPcs[];
unsigned char PartPcs[];
unsigned char Chara[];
unsigned char LightPcs[];
unsigned char MapPcs[];
unsigned char MaterialEditorPcs[];
unsigned char FunnyShapePcs[];
unsigned char GraphicsPcs[];
unsigned char CameraPcs[];
unsigned char DAT_8032ed00[];
unsigned char DAT_8032ed08[];
unsigned char Wind[];
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
extern const char DAT_8032f6a0[];
extern const char DAT_8032f6a4[];
extern const char DAT_8032f6ac[];
extern const s16 DAT_8032e3d0[];
extern const char* lbl_801D60B0[];
extern const char* lbl_801E8344[];
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
void __dt__5CGameFv(void*, int);
void* __vt__5CGame[];
}

static const float FLOAT_8032f688 = 1.0E+10;
static const float FLOAT_8032f68c = -1.0E+10;
static const float FLOAT_8032f690 = 0.0;    
static const float FLOAT_8032f694 = 0.001;
static const s16 s_bossArtifactStartTable[] = {0, 4, 8};
static const float s_ratio[] = {0.4f, 0.55f, 0.7f, 0.85f};
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
    *reinterpret_cast<void**>(&Game.game) = __vt__5CGame;

    memset(reinterpret_cast<unsigned char*>(&Game.game) + 0xF, 0, 0x13E1);
    memset(reinterpret_cast<unsigned char*>(&Game.game) + 0x20, 0xFF, 0x10);

    Game.game.m_gameWork.m_scriptSysVal0 = 0;
    Game.game.m_gameWork.m_scriptSysVal1 = 0;
    Game.game.m_gameWork.m_scriptSysVal2 = 0;
    Game.game.m_gameWork.m_scriptSysVal3 = 1;
    Game.game.m_gameWork.m_chaliceElement = 1;

    const char* townName = DAT_8032f6ac;
    if (Game.game.m_gameWork.m_languageId == 3) {
        townName = DAT_8032f6a4;
    }
    strcpy(Game.game.m_gameWork.m_townName, townName);

    Game.game.m_gameWork.m_gameInitFlag = 1;

    __construct_array(
        Game.game.m_caravanWorkArr,
        reinterpret_cast<ConstructorDestructor>(__ct__12CCaravanWorkFv),
        reinterpret_cast<ConstructorDestructor>(__dt__12CCaravanWorkFv),
        0xC30,
        9
    );
    __construct_array(
        Game.game.m_monWorkArr,
        reinterpret_cast<ConstructorDestructor>(__ct__8CMonWorkFv),
        reinterpret_cast<ConstructorDestructor>(__dt__8CMonWorkFv),
        0x110,
        0x40
    );

    Game.game.m_partyMinZ = FLOAT_8032f688;
    Game.game.m_partyMinY = FLOAT_8032f688;
    Game.game.m_partyMinX = FLOAT_8032f688;
    Game.game.m_partyMaxZ = FLOAT_8032f68c;
    Game.game.m_partyMaxY = FLOAT_8032f68c;
    Game.game.m_partyMaxX = FLOAT_8032f68c;

    __construct_array(
        Game.game.m_cFlatDataArr,
        reinterpret_cast<ConstructorDestructor>(__ct__9CFlatDataFv),
        reinterpret_cast<ConstructorDestructor>(__dt__9CFlatDataFv),
        0x14D4,
        4
    );

    __register_global_object(&Game.game, reinterpret_cast<void*>(__dt__5CGameFv), &Game);
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
    u32 progressiveMode = OSGetProgressiveMode();

    if (progressiveMode == 3) {
        m_gameWork.m_languageId = 5;
    } else if (progressiveMode < 3) {
        if (progressiveMode == 1) {
            m_gameWork.m_languageId = 2;
        } else if (progressiveMode != 0) {
            m_gameWork.m_languageId = 4;
        } else {
            m_gameWork.m_languageId = 1;
        }
    } else if ((progressiveMode < 5) && (progressiveMode != 5)) {
        m_gameWork.m_languageId = 3;
    } else {
        m_gameWork.m_languageId = 1;
    }

    Init__10CCameraPcsFv(&CameraPcs);
    Init__11CGraphicPcsFv(GraphicsPcs);
    Init__6CCharaFv(Chara);
    Init__9CLightPcsFv(LightPcs);
    Init__9CCharaPcsFv(&CharaPcs);
    Init__7CMapPcsFv(MapPcs);
    Init__18CMaterialEditorPcsFv(MaterialEditorPcs);
    Init__14CFunnyShapePcsFv(FunnyShapePcs);
    Init__7CUSBPcsFv(USBPcs);
    Init__8CMenuPcsFv(MenuPcs);
    Init__7CGbaPcsFv(&GbaPcs);
    Init__6CMcPcsFv(McPcs);
    Init__11CDbgMenuPcsFv(&DbgMenuPcs);

    m_mainStage = (CMemory::CStage*)CreateStage__7CMemoryFUlPci(&Memory, 0x106000, s_mainStageName, 0);
    if (OSGetConsoleSimulatedMemSize() == 0x3000000) {
        m_debugStage = (CMemory::CStage*)CreateStage__7CMemoryFUlPci(&Memory, 0x220000, s_debugStageName, 1);
    }

    m_sceneId = 4;
    m_mapId = 3;
    m_mapVariant = 0;
    memset(m_currentScriptName, 0, sizeof(m_currentScriptName));
    memset(m_startScriptName, 0, sizeof(m_startScriptName));
    m_frameCounterEnable = 1;
    Init__12CFlatRuntimeFv(CFlat);
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
	Quit__12CFlatRuntimeFv(CFlat);

	if (m_debugStage != 0) {
		DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, m_debugStage);
	}

	DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, m_mainStage);
	Quit__11CDbgMenuPcsFv(&DbgMenuPcs);
	Quit__6CMcPcsFv(McPcs);
	Quit__7CGbaPcsFv(&GbaPcs);
	Quit__8CMenuPcsFv(MenuPcs);
	Quit__7CUSBPcsFv(USBPcs);
	Quit__6CCharaFv(Chara);
	Quit__9CCharaPcsFv(&CharaPcs);
	Quit__9CLightPcsFv(LightPcs);
	Quit__7CMapPcsFv(MapPcs);
	Quit__18CMaterialEditorPcsFv(MaterialEditorPcs);
	Quit__14CFunnyShapePcsFv(FunnyShapePcs);
	Quit__11CGraphicPcsFv(GraphicsPcs);
	Quit__10CCameraPcsFv(&CameraPcs);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::LoadLogoWaitingData()
{
	if (m_assetsLoadedFlag == 0) {
		createLoad__9CSoundPcsFv(SoundPcs);
		createLoad__9CCharaPcsFv(&CharaPcs);
		createLoad__8CPartPcsFv(&PartPcs);
		m_assetsLoadedFlag = 1;
		if (System.m_execParam > 2) {
			Printf__7CSystemFPce(&System, DAT_801d61dc);
		}
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
	AddScenegraph__7CSystemFP8CProcessi(&System, DAT_8032ed08, 0);
	AddScenegraph__7CSystemFP8CProcessi(&System, GraphicsPcs, 0);
	AddScenegraph__7CSystemFP8CProcessi(&System, LightPcs, 0);
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
			AddScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 1);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 1);
			break;
		case 3:
			AddScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 2);
			AddScenegraph__7CSystemFP8CProcessi(&System, MapPcs, 1);
			AddScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 6);
			break;
		case 4:
			AddScenegraph__7CSystemFP8CProcessi(&System, MenuPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, MapPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 6);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, DAT_8032ed00, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &PartPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &GbaPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, &DbgMenuPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, McPcs, 0);
			AddScenegraph__7CSystemFP8CProcessi(&System, SoundPcs, 0);
			break;
		case 5:
			AddScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 3);
			AddScenegraph__7CSystemFP8CProcessi(&System, MaterialEditorPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, LightPcs, 0);
			break;
		case 6:
			AddScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 4);
			AddScenegraph__7CSystemFP8CProcessi(&System, FunnyShapePcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, LightPcs, 0);
			break;
		case 7:
			AddScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 5);
			AddScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 2);
			AddScenegraph__7CSystemFP8CProcessi(&System, MapPcs, 1);
			AddScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 6);
			AddScenegraph__7CSystemFP8CProcessi(&System, &PartPcs, 1);
			break;
		}

		ExecScenegraph__7CSystemFv(&System);

		switch (m_currentSceneId) {
		case 2:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 1);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 1);
			break;
		case 3:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 2);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 6);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, MapPcs, 1);
			break;
		case 4:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, SoundPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, McPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 6);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, MapPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &PartPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &GbaPcs, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, DAT_8032ed00, 0);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, MenuPcs, 0);
			break;
		case 5:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 3);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, MaterialEditorPcs, 0);
			break;
		case 6:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 4);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, FunnyShapePcs, 0);
			break;
		case 7:
			RemoveScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 5);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, CameraPcs, 6);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &CharaPcs, 2);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, MapPcs, 1);
			RemoveScenegraph__7CSystemFP8CProcessi(&System, &PartPcs, 1);
			break;
		}

		Memory.HeapWalker();
		Memory.DecHeapWalkerLevel();
	} while (m_sceneId != 0);

	RemoveScenegraph__7CSystemFP8CProcessi(&System, &MiniGamePcs, 0);
	RemoveScenegraph__7CSystemFP8CProcessi(&System, LightPcs, 0);
	RemoveScenegraph__7CSystemFP8CProcessi(&System, GraphicsPcs, 0);
	RemoveScenegraph__7CSystemFP8CProcessi(&System, DAT_8032ed08, 0);
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

        _WaitDrawDone__8CGraphicFPci(&Graphic, s_game_cpp_801d6190, 0x24E);
        MapChanging__7CSystemFii(&System, mapId, mapVariant);

        m_currentMapId = mapId;
        m_currentMapVariantId = mapVariant;

        LoadMap__7CMapPcsFiiPvUlUc(MapPcs, mapId, mapVariant, 0, 0, 0);
        LoadFieldPdt__8CPartPcsFiiPvUlUc(&PartPcs, mapId, mapVariant, 0, 0, 0);

        MapChanged__7CSystemFiii(&System, mapId, mapVariant, 1);
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
    const char* townName = DAT_8032f6ac;

    Printf__7CSystemFPce(&System, DAT_8032f6a0);
    Printf__7CSystemFPce(&System, DAT_801d6214);
    Printf__7CSystemFPce(&System, DAT_8032f6a0);

    memset(&m_gameWork.m_gameDataStartMarker, 0, 0x13E1);
    memset(m_gameWork.m_wmBackupParams, 0xFF, sizeof(m_gameWork.m_wmBackupParams));

    m_gameWork.m_scriptSysVal0 = 0;
    m_gameWork.m_scriptSysVal1 = 0;
    m_gameWork.m_scriptSysVal2 = 0;
    m_gameWork.m_scriptSysVal3 = 1;
    m_gameWork.m_chaliceElement = 1;

    if (m_gameWork.m_languageId == 3) {
        townName = DAT_8032f6a4;
    }

    strcpy(m_gameWork.m_townName, townName);
    ResetNewGame__13CFlatRuntime2Fv(CFlat);
    InitFurTexBuffer__6CCharaFv(Chara);
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

    Destroy__13CFlatRuntime2Fv(CFlat);

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

    DestroyMap__7CMapMngFv(&MapMng);
    Reset__9CCharaPcsFQ29CCharaPcs5RESET(&CharaPcs, 0);
    StopAndFreeAllSe__6CSoundFi(&Sound, 0);
    ClearAll__5CWindFv(Wind);

    *((u8*)&Sound + 0x8892) = 0x7F;
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
    _WaitDrawDone__8CGraphicFPci(&Graphic, s_game_cpp_801d6190, 0x205);

    if (System.m_execParam > 2) {
        Printf__7CSystemFPce(&System, DAT_801d619c);
    }

    ScriptChanging__7CSystemFPc(&System, m_nextScript.m_name);

    if (strcmp(m_nextScript.m_name, DAT_8032f698) != 0) {
        if (m_cfdLoadedFlag == 0) {
            Destroy__13CFlatRuntime2Fv(CFlat);
            loadCfd();
            m_cfdLoadedFlag = 1;

            if (System.m_execParam > 2) {
                Printf__7CSystemFPce(&System, DAT_801d61b8);
            }
        }

        if (m_assetsLoadedFlag == 0) {
            createLoad__9CSoundPcsFv(SoundPcs);
            createLoad__9CCharaPcsFv(&CharaPcs);
            createLoad__8CPartPcsFv(&PartPcs);
            m_assetsLoadedFlag = 1;

            if (System.m_execParam > 2) {
                Printf__7CSystemFPce(&System, DAT_801d61dc);
            }
        }
    }

    int scriptResult = Load__13CFlatRuntime2FPc(CFlat, m_nextScript.m_name);
    strcpy(m_currentScriptName, m_nextScript.m_name);

    if (m_nextScript.m_flags != 0) {
        const char* townName = DAT_8032f6ac;

        Printf__7CSystemFPce(&System, DAT_8032f6a0);
        Printf__7CSystemFPce(&System, DAT_801d6214);
        Printf__7CSystemFPce(&System, DAT_8032f6a0);

        memset(&m_gameWork.m_gameDataStartMarker, 0, 0x13E1);
        memset(m_gameWork.m_wmBackupParams, 0xFF, sizeof(m_gameWork.m_wmBackupParams));

        m_gameWork.m_scriptSysVal0 = 0;
        m_gameWork.m_scriptSysVal1 = 0;
        m_gameWork.m_scriptSysVal2 = 0;
        m_gameWork.m_scriptSysVal3 = 1;
        m_gameWork.m_chaliceElement = 1;

        if (m_gameWork.m_languageId == 3) {
            townName = DAT_8032f6a4;
        }

        strcpy(m_gameWork.m_townName, townName);
        ResetNewGame__13CFlatRuntime2Fv(CFlat);
        InitFurTexBuffer__6CCharaFv(Chara);
        m_nextScript.m_flags = 0;
    }

    ScriptChanged__7CSystemFPci(&System, m_nextScript.m_name, scriptResult);

    if (System.m_execParam > 2) {
        Printf__7CSystemFPce(&System, DAT_801d6234);
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
        _WaitDrawDone__8CGraphicFPci(&Graphic, s_game_cpp_801d6190, 0x24E);
        MapChanging__7CSystemFii(&System, mapId, mapVariant);

        m_currentMapId = mapId;
        m_currentMapVariantId = mapVariant;
        hasParamMask = (u32)((-param4 | param4) >> 31);

        LoadMap__7CMapPcsFiiPvUlUc(
            MapPcs, mapId, mapVariant, (void*)(hasParamMask & 0x800000), hasParamMask & 0x580000, 0);

        hasParamMask = (u32)((-param4 | param4) >> 31);
        LoadFieldPdt__8CPartPcsFiiPvUlUc(
            &PartPcs, mapId, mapVariant, (void*)(hasParamMask & 0xD80000), hasParamMask & 0x80000, 0);

        MapChanged__7CSystemFiii(&System, mapId, mapVariant, 1);
    } else {
        hasParamMask = (u32)((-param4 | param4) >> 31);
        LoadMap__7CMapPcsFiiPvUlUc(
            MapPcs, mapId, mapVariant, (void*)(hasParamMask & 0x800000), hasParamMask & 0x580000, param4 & 0xFF);

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
	pppDeleteAll__8CPartMngFv(PartMng);
	pppDestroyAll__8CPartMngFv(PartMng);
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
    int k;

    for (i = 0; i < 4; i++) {
        m_partyObjArr[i] = 0;
        m_scriptFoodBase[i] = 0;
    }

    unk_flat3_0xc7d0 = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            for (k = 0; k < 2; k++) {
                m_scriptWork[i][j][k] = 0;
            }
        }
    }

    m_gameWork.m_soundOptionFlag = 0;
    m_gameWork.m_gameOverFlag = 0;

    DestroyMap__7CMapMngFv(&MapMng);
    Reset__9CCharaPcsFQ29CCharaPcs5RESET(&CharaPcs, 0);
    StopAndFreeAllSe__6CSoundFi(&Sound, 0);
    ClearAll__5CWindFv(Wind);

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
    };

    struct FlatDataLayout
    {
        int m_dataCount;
        FlatDataEntry m_data[5];
    };

    static const char* const sLangDirs[] =
    {
        "jp/",
        "uk/",
        "gr/",
        "it/",
        "fr/",
        "sp/"
    };

    static const char* const sCfdPathFormats[] =
    {
        "dvd/%scft/param.cfd",
        "dvd/%scft/c_system.cfd",
        "dvd/%scft/mail_tbl.cfd",
        "dvd/%scft/newbattle.cfd"
    };

    char path[0x10C];

    for (int i = 0; i < 4; i++)
    {
        const char* localLangDirs[6];
        localLangDirs[0] = sLangDirs[0];
        localLangDirs[1] = sLangDirs[1];
        localLangDirs[2] = sLangDirs[2];
        localLangDirs[3] = sLangDirs[3];
        localLangDirs[4] = sLangDirs[4];
        localLangDirs[5] = sLangDirs[5];

        sprintf(path, sCfdPathFormats[i], localLangDirs[m_gameWork.m_languageId]);
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

    if (m_frameCounterEnable != 0) {
        m_gameWork.m_frameCounter++;
    }

    const float minInit = FLOAT_8032f688;
    const float maxInit = FLOAT_8032f68c;

    m_partyMinX = minInit;
    m_partyMinY = minInit;
    m_partyMinZ = minInit;

    m_partyMaxX = maxInit;
    m_partyMaxY = maxInit;
    m_partyMaxZ = maxInit;

    for (int i = 0; i < 4; ++i)
    {
        CGPartyObj* obj = m_partyObjArr[i];

        if (!obj)
		{
            continue;
		}

        const CVector& pos = (CVector&)obj; // obj->field0_0x0.gObject.maybeRotation;

        if (pos.x < m_partyMinX)
		{
			m_partyMinX = pos.x;
		}

        if (pos.y < m_partyMinY)
		{
			m_partyMinY = pos.y;
		}

        if (pos.z < m_partyMinZ)
		{
			m_partyMinZ = pos.z;
		}

        if (pos.x > m_partyMaxX)
		{
			m_partyMaxX = pos.x;
		}

        if (pos.y > m_partyMaxY)
		{
			m_partyMaxY = pos.y;
		}

        if (pos.z > m_partyMaxZ)
		{
			m_partyMaxZ = pos.z;
		}
    }

    // Wind.Frame();

    // CFlat.Calc(); // Calc__13CFlatRuntime2Fv
    // CFlat.ResetPerformance();
    // CFlat.Frame(1, 0);

    if (m_currentMapId == 0x21)
    {
        int objIdx = (int)this; // = MapMng.GetMapObjIdx(0);

        if (objIdx >= 0)
        {
            if (!BOOL_8032ec44) {
                BOOL_8032ec44 = true;
                FLOAT_8032ec40 = FLOAT_8032f690;
            }

            FLOAT_8032ec40 += FLOAT_8032f694;

            PSMTXRotRad(rotMtx, 0, FLOAT_8032ec40);

            // MapMng.SetMapObjLMtx(objIdx, rotMtx);
        }
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
	Frame__13CFlatRuntime2Fii(CFlat, 0, 1);
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
	AfterFrame__12CFlatRuntimeFi(CFlat, 0);
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
	Draw__13CFlatRuntime2Fv(CFlat);
	Draw__5CWindFv(Wind);
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
	Frame__13CFlatRuntime2Fii(CFlat, 0, 2);
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
			Printf__7CSystemFPce(&System, DAT_801d60d4, scriptLine, scriptStep, effectIndex, pos);
		}
	} else if (callbackType == 1) {
		*(u8*)(ifData + 7) &= ~2;
		pppEndPart__8CPartMngFi(&PartMng, effectIndex);

		if (System.m_execParam > 2) {
			Printf__7CSystemFPce(&System, DAT_801d6114, scriptLine, scriptStep, effectIndex, pos);
		}
	} else if (callbackType == 3) {
		pppEndPart__8CPartMngFi(&PartMng, effectIndex);

		if (System.m_execParam > 2) {
			Printf__7CSystemFPce(&System, DAT_801d6154, scriptLine, scriptStep, effectIndex, pos);
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
    int count = *(int*)(CFlat + 4);
    u8* table = *(u8**)(CFlat + 8);
    u32* values = *(u32**)(CFlat + 12);

    while (i < count) {
        if ((table[entryOffset + 1] & 0x20) != 0) {
            *(u32*)(scriptData + scriptOffset) = values[i];
            scriptOffset += 4;
        }
        entryOffset += 4;
        ++i;
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
    s16 stageBase;
    s16 thresholdA;
    s16 thresholdB;
    s16 thresholdC;
    int stageClass;
    int baseOffset;
    int stageIndex;
    int bucketCount;
    int randomValue;

    stageClass = Game.game.m_gameWork.m_bossArtifactStageTable[Game.game.m_gameWork.m_bossArtifactStageIndex];
    if (stageClass > 2) {
        stageClass = 2;
    }

    stageBase = s_bossArtifactStartTable[stageClass];
    baseOffset = (int)((float)amount * s_ratio[ratioIndex]);

    stageIndex = (int)Game.game.m_gameWork.m_bossArtifactStageIndex;
    randomValue = (int)Game.game.m_bossArtifactBase + stageIndex * 0x168;
    thresholdA = *(s16*)(randomValue + 0x162);
    thresholdB = *(s16*)(randomValue + 0x164);
    thresholdC = *(s16*)(randomValue + 0x166);

    bucketCount = 3;
    if (baseOffset < thresholdC) {
        bucketCount = 2;
        if (baseOffset < thresholdB) {
            bucketCount = 1;
            if (baseOffset < thresholdA) {
                bucketCount = 0;
            }
        }
    }

    baseOffset = rand();
    return randomValue + 0x20 + (stageBase + (baseOffset - (baseOffset / (bucketCount + 1)) * (bucketCount + 1))) * 8;
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
    s16 level = reinterpret_cast<s16*>(m_scriptFoodBase[playerIndex] + 0x3B8)[foodIndex];
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
    f32* cursorPos = reinterpret_cast<f32*>(m_scriptFoodBase[playerIndex] + 0xBAC);

    posA.x = cursorPos[0];
    posA.y = cursorPos[1];
    posA.z = cursorPos[2];

    posB.x = cursorPos[3];
    posB.y = cursorPos[4];
    posB.z = cursorPos[5];
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
    if (ifParam.m_classId == 0) {
        return 0;
    }

    char* classObj = reinterpret_cast<char*>(intToClass__13CFlatRuntime2Fi(CFlat, (int)ifParam.m_classId));
    particleIndex = ifParam.m_particleIndex;
    if (particleIndex == 0) {
        return 0;
    }

    void* behavior = *reinterpret_cast<void**>(classObj + 0x48);
    void** behaviorVtable = *reinterpret_cast<void***>(behavior);
    u32 behaviorFlags = reinterpret_cast<u32 (*)(void*)>(behaviorVtable[3])(behavior);
    if ((behaviorFlags & 0x6D) != 0x6D) {
        return 0;
    }

    char* objWork = *reinterpret_cast<char**>(classObj + 0x58);
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
    char** itemTable = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[0].m_strings;
    if (count >= 2) {
        sprintf(out, s_numNameFmt, count, itemTable[itemIndex * 5 + 3]);
        return out;
    }

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
    char* prefix = itemTable[itemIndex * 5 + 2];
    char* itemName = itemTable[itemIndex * 5 + 3];

    const char* separator = s_nameNoSep;
    if ((strlen(prefix) != 0) && (m_gameWork.m_languageId != 3) && (m_gameWork.m_languageId != 4)) {
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
    CFlatDataView* flatData = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1]);
    char** itemTable = flatData->m_tabl[0].m_strings;
    char* itemName;

    if (count < 2) {
        itemName = itemTable[itemIndex * 5 + 1];
    } else {
        itemName = itemTable[itemIndex * 5 + 3];
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
    char** monTable = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1])->m_tabl[1].m_strings;
    if (count >= 2) {
        sprintf(out, s_numNameFmt, count, monTable[monIndex * 5 + 3]);
        return out;
    }

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
    char* prefix = monTable[monIndex * 5 + 2];
    char* monName = monTable[monIndex * 5 + 3];

    const char* separator = s_nameNoSep;
    if ((strlen(prefix) != 0) && (m_gameWork.m_languageId != 3) && (m_gameWork.m_languageId != 4)) {
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
    CFlatDataView* flatData = reinterpret_cast<CFlatDataView*>(&m_cFlatDataArr[1]);
    char** monTable = flatData->m_tabl[1].m_strings;
    char* monName;

    if (count < 2) {
        monName = monTable[monIndex * 5 + 1];
    } else {
        monName = monTable[monIndex * 5 + 3];
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

    localLangDirs[0] = lbl_801D60B0[0];
    localLangDirs[1] = lbl_801D60B0[1];
    localLangDirs[2] = lbl_801D60B0[2];
    localLangDirs[3] = lbl_801D60B0[3];
    localLangDirs[4] = lbl_801D60B0[4];
    localLangDirs[5] = lbl_801D60B0[5];

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
