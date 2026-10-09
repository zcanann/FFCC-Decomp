#include "ffcc/combi.h"
#include "ffcc/game.h"
#include "ffcc/joybusconst.h"
#include "ffcc/cardconst.h"

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

enum {
#ifdef VERSION_GCCJGC
	kGameStageSize = 0xE6000,
#else
	kGameStageSize = 0x106000,
#endif
	kGameWorkDataClearSize =
	    sizeof(CGame::CGameWork) - offsetof(CGame::CGameWork, m_gameDataStartMarker),
	kGameScriptSaveDataSize = 0x800,
};

STATIC_ASSERT(kGameWorkDataClearSize == 0x13E1);

struct GameNameRow
{
    char* m_prefix;
    char* m_name;
    char* m_artPrefix;
    char* m_artName;
    char* m_namePlural;
};

CGame Game;

inline void CFile::CHandle::Read()
{
    File.Read(this);
}

inline void CFile::CHandle::SyncCompleted()
{
    File.SyncCompleted(this);
}

inline void CFile::CHandle::Close()
{
    File.Close(this);
}

inline void* CFile::GetBuffer()
{
    return m_readBuffer;
}

inline int CMapPcs::GetLightHolderSize(CMapLightHolder::TYPE type)
{
    return MapMng.GetMapLightHolderArray(type).GetSize();
}

inline void CMapPcs::GetLightHolder(CMapLightHolder::TYPE type, long index, _GXColor* color, Vec* pos)
{
    CPtrArray<CMapLightHolder*>& holders = MapMng.GetMapLightHolderArray(type);

    if (static_cast<unsigned long>(index) < static_cast<unsigned long>(holders.GetSize())) {
        holders[index]->GetLightHolder(color, pos);
    }
}

inline int CMapPcs::GetCharLightHolderSize()
{
    return GetLightHolderSize(CMapLightHolder::TYPE_CHARA);
}

inline void CMapPcs::GetCharLightHolder(long index, _GXColor* color, Vec* pos)
{
    GetLightHolder(CMapLightHolder::TYPE_CHARA, index, color, pos);
}

inline void CCharaPcs::SetAmbient(int index, _GXColor* color)
{
    m_viewerAmbientColor[index] = *color;
}

inline void CCharaPcs::SetDiffuse(int index, unsigned long light, _GXColor* color, Vec* pos)
{
    m_viewerDiffuseColor[index][light] = *color;

    if (index == 0) {
        m_viewerDiffusePos[light] = *pos;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001439C
 * PAL Size: 8b
 * EN Address: 0x8001DDBC
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CGBaseObj::GetCID()
{
    return 1;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CGame::CGame()
{
}

/*
 * --INFO--
 * PAL Address: 0x8001600C
 * PAL Size: 476b
 * EN Address: 0x80015E58
 * EN Size: 396b
 * JP Address: 0x80015A54
 * JP Size: 376b
 */
void CGame::Init()
{
#ifdef VERSION_GCCP01
    int languageId;

    switch (static_cast<unsigned char>(OSGetLanguage())) {
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
#elif defined(VERSION_GCCE01)
    Game.m_gameWork.m_languageId = 1;
#endif

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

    m_mainStage = Memory.CreateStage(kGameStageSize, "Game", 0);
    if (OSGetConsoleSimulatedMemSize() == 0x3000000) {
        m_debugStage = Memory.CreateStage(0x220000, "GameDebug", 1);
    }

    m_sceneId = 4;
    m_mapId = 3;
    m_mapVariant = 0;
    memset(m_currentScriptName, 0, sizeof(m_currentScriptName));
    memset(m_startScriptName, 0, sizeof(m_startScriptName));
    m_frameCounterEnable = 1;
    gCFlatRuntime().CFlatRuntime::Init();
    unkFloat_0xca10 = 1000.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80015F14
 * PAL Size: 248b
 * EN Address: 0x8001AC8C
 * EN Size: 256b
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
 * PAL Address: 0x80015E8C
 * PAL Size: 136b
 * EN Address: 0x80015CD8
 * EN Size: 136b
 * JP Address: TODO
 * JP Size: TODO
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

		System.Printf("サウンド・キャラ・パーティクルの常駐を読み込みました。\n");
	}
}

/*
 * --INFO--
 * PAL Address: 0x800157A8
 * PAL Size: 1764b
 * EN Address: 0x800155F4
 * EN Size: 1764b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Exec()
{
	static const char* m_tStatus[] = {
	    "SN_EXIT",
	    "SN_DUMMY",
	    "SN_CHARA",
	    "SN_MAP",
	    "SN_GAME",
	    "SN_MATERIALEDITOR",
	    "SN_FUNNYSHAPE",
	    "SN_PARTVIEW",
	    0,
	};

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
			System.Printf("CGame.Exec: scene = %s\n", m_tStatus[sceneId]);
		} else {
			System.Printf("シーンが異常です。%d\n", sceneId);
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
 * EN Address: 0x8001545C
 * EN Size: 408b
 * JP Address: 0x80015064
 * JP Size: 396b
 */
void CGame::Create()
{
    char scriptName[256];

    m_nextScriptFlags = 1;
    clearWork();
    m_gameWork.Init();

    if (strlen(m_startScriptName) != 0) {
        strcpy(scriptName, m_startScriptName);
        m_nextScript = *reinterpret_cast<CNextScript*>(scriptName);
        m_newGameFlag = 1;
    }

    if (m_newGameFlag == 0) {
        ChangeMap(m_currentMapId, m_currentMapVariantId, 0, 1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800155F0
 * PAL Size: 32b
 * EN Address: 0x8001B614
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Destroy()
{
	clearWork();
}

/*
 * --INFO--
 * PAL Address: 0x8001551C
 * PAL Size: 212b
 * EN Address: 0x80015368
 * EN Size: 212b
 * JP Address: 0x80014F7C
 * JP Size: 200b
 */
void CGame::InitNewGame()
{
    System.Printf("*\n");
    System.Printf("*ニューゲーム初期化します。\n");
    System.Printf("*\n");

    Game.m_gameWork.InitNewGame();
    CFlatRuntime2Storage().ResetNewGame();
    Chara.InitFurTexBuffer();
}

/*
 * --INFO--
 * PAL Address: 0x80015280
 * PAL Size: 668b
 * EN Address: 0x800150CC
 * EN Size: 668b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::clearWork()
{
    int i;

    CFlatRuntime2Storage().CFlatRuntime2::Destroy();

    for (i = 0; i < 4; i++) {
        m_cFlatDataArr[i].Destroy();
    }

    unkCFlatData0[0] = 0;
    unkCFlatData0[1] = 0;
    unkCFlatData0[2] = 0;
    clearWorkScript();
    clearWorkMap();
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
void CGame::clearWorkMap()
{
    if (MapPcs.GetCharLightHolderSize() != 0) {
        _GXColor color;
        Vec pos;

        MapPcs.GetCharLightHolder(0, &color, 0);

        for (int i = 0; i < 2; i++) {
            CharaPcs.SetAmbient(i, &color);

            for (unsigned long j = 0; j < 3; j++) {
                MapPcs.GetCharLightHolder(j + 1, &color, &pos);
                CharaPcs.SetDiffuse(i, j, &color, &pos);
            }
        }
    }
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
void CGame::clearWorkScript()
{
    int i;

    for (i = 0; i < 4; i++) {
        m_partyObjArr[i] = 0;
        m_scriptFoodBase[i] = 0;
    }

    unk_flat3_0xc7d0 = 0;

    for (i = 0; i < 64; i++) {
        m_monObjects[i] = 0;
        m_monWorkRefs[i] = 0;
    }

    m_gameWork.m_soundOptionFlag = 0;
    m_gameWork.m_gameOverFlag = 0;

    MapMng.DestroyMap();
    CharaPcs.Reset(static_cast<CCharaPcs::RESET>(0));
    Sound.StopAndFreeAllSe(0);
    Wind.ClearAll();

    Sound.SeMaxVolume(0x7F);
}

/*
 * --INFO--
 * PAL Address: 0x80014FF8
 * PAL Size: 648b
 * EN Address: 0x80014E44
 * EN Size: 648b
 * JP Address: 0x80014A68
 * JP Size: 632b
 */
void CGame::CheckScriptChange()
{
    if (m_newGameFlag == 0) {
        return;
    }

    m_newGameFlag = 0;
#ifdef VERSION_GCCJGC
    Graphic._WaitDrawDone("game.cpp", 0x1EA);
#else
    Graphic._WaitDrawDone("game.cpp", 0x205);
#endif

    if ((u32)System.m_execParam >= 3) {
        System.Printf("スクリプトが切り替わります\n");
    }

    System.ScriptChanging(m_nextScript.m_name);

    if (strcmp(m_nextScript.m_name, "ffcc_0") != 0) {
        if (m_cfdLoadedFlag == 0) {
            CFlatRuntime2Storage().CFlatRuntime2::Destroy();
            loadCfd();
            m_cfdLoadedFlag = 1;

            if ((u32)System.m_execParam >= 3) {
                System.Printf("スクリプトの常駐を読み込みました。\n");
            }
        }

        LoadLogoWaitingData();
    }

    int scriptResult = CFlatRuntime2Storage().Load(m_nextScript.m_name);
    strcpy(m_currentScriptName, m_nextScript.m_name);

    if ((int)m_nextScriptFlags != 0) {
        InitNewGame();
        m_nextScriptFlags = 0;
    }

    System.ScriptChanged(m_nextScript.m_name, scriptResult);

    if ((u32)System.m_execParam >= 3) {
        System.Printf("スクリプトが切り替わりました\n");
    }
}

/*
 * --INFO--
 * PAL Address: 0x80014E78
 * PAL Size: 384b
 * EN Address: 0x80014CC4
 * EN Size: 384b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::ChangeMap(int mapId, int mapVariant, int param4, int param5)
{
    if (param5 != 0) {
#ifdef VERSION_GCCJGC
        Graphic._WaitDrawDone("game.cpp", 0x22C);
#else
        Graphic._WaitDrawDone("game.cpp", 0x24E);
#endif
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
 * PAL Address: 0x80014E44
 * PAL Size: 52b
 * EN Address: 0x8001BD90
 * EN Size: 52b
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
 * PAL Address: 0x80014D04
 * PAL Size: 320b
 * EN Address: 0x80014B50
 * EN Size: 320b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::ScriptChanged(char*, int)
{
    clearWorkScript();
}

/*
 * --INFO--
 * PAL Address: 0x80014D00
 * PAL Size: 4b
 * EN Address: 0x8001BDEC
 * EN Size: 4b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::MapChanging(int, int)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80014CFC
 * PAL Size: 4b
 * EN Address: 0x8001BDF0
 * EN Size: 4b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::MapChanged(int, int, int)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80014B90
 * PAL Size: 364b
 * EN Address: 0x80014A28
 * EN Size: 288b
 * JP Address: 0x80014660
 * JP Size: 268b
 */
void CGame::loadCfd()
{
#ifdef VERSION_GCCJGC
    static const char* tName[] = {
        "dvd/cft/param.cfd",
        "dvd/cft/c_system.cfd",
        "dvd/cft/mail_tbl.cfd",
        "dvd/cft/newbattle.cfd",
    };
#else
    static const char* tName[] = {
        "dvd/%scft/param.cfd",
        "dvd/%scft/c_system.cfd",
        "dvd/%scft/mail_tbl.cfd",
        "dvd/%scft/newbattle.cfd",
    };

    char path[0xFC];
#endif

    for (int i = 0; i < 4; i++)
    {
#ifdef VERSION_GCCJGC
        char* path = const_cast<char*>(tName[i]);
#else
        sprintf(path, tName[i], Game.GetLangString());
#endif
        CFile::CHandle* handle = File.Open(path, 0, CFile::PRI_LOW);

        if (handle != nullptr)
        {
            handle->Read();
            handle->SyncCompleted();
            m_cFlatDataArr[i].Create(File.GetBuffer());
            handle->Close();
        }
    }

    unkCFlatData0[0] = (unsigned int)m_cFlatDataArr[0].GetData(0);
    ASSERT(unkCFlatData0[0]);
    unkCFlatData0[1] = (unsigned int)m_cFlatDataArr[0].GetData(1);
    ASSERT(unkCFlatData0[1]);
    unkCFlatData0[2] = (unsigned int)m_cFlatDataArr[0].GetData(2);
    ASSERT(unkCFlatData0[2]);
    m_romLetterWorkBase = (unsigned int)m_cFlatDataArr[2].GetData(0);
    ASSERT(m_romLetterWorkBase);
    unk_flat3_field_8_0xc7dc = (unsigned int)m_cFlatDataArr[3].GetData(0);
    ASSERT(unk_flat3_field_8_0xc7dc);
    m_combiTable = reinterpret_cast<CCombi2*>(m_cFlatDataArr[3].GetData(1));
    ASSERT(m_combiTable);
    ASSERT((m_cFlatDataArr[3].m_data[1].m_size % sizeof(CCombi2)) == 0);
    m_combiCount = m_cFlatDataArr[3].m_data[1].m_size / sizeof(CCombi2);
    ASSERT(m_combiCount);
    unk_flat3_field_30_0xc7e0 = (unsigned int)m_cFlatDataArr[3].GetData(2);
    ASSERT(unk_flat3_field_30_0xc7e0);
    m_bossArtifactBase = reinterpret_cast<CBossArtifactStage*>(m_cFlatDataArr[3].GetData(3));
    ASSERT(m_bossArtifactBase);
}

/*
 * --INFO--
 * PAL Address: 0x80014994
 * PAL Size: 508b
 * EN Address: 0x8001482C
 * EN Size: 508b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Calc()
{
	Mtx rotMtx;
    int mapObjIdx;

    if (m_frameCounterEnable != 0) {
        m_gameWork.m_frameCounter++;
    }

    m_partyBound.m_min.x = m_partyBound.m_min.y = m_partyBound.m_min.z = 1.0E+10f;
    m_partyBound.m_max.x = m_partyBound.m_max.y = m_partyBound.m_max.z = -1.0E+10f;

    for (int i = 0; i < 4; i++) {
        CGPartyObj* partyObj = m_partyObjArr[i];

        if (partyObj != 0) {
            m_partyBound.m_min.x = (m_partyBound.m_min.x < partyObj->m_worldPosition.x) ? m_partyBound.m_min.x : partyObj->m_worldPosition.x;
            m_partyBound.m_min.y = (m_partyBound.m_min.y < partyObj->m_worldPosition.y) ? m_partyBound.m_min.y : partyObj->m_worldPosition.y;
            m_partyBound.m_min.z = (m_partyBound.m_min.z < partyObj->m_worldPosition.z) ? m_partyBound.m_min.z : partyObj->m_worldPosition.z;
            m_partyBound.m_max.x = (m_partyBound.m_max.x > partyObj->m_worldPosition.x) ? m_partyBound.m_max.x : partyObj->m_worldPosition.x;
            m_partyBound.m_max.y = (m_partyBound.m_max.y > partyObj->m_worldPosition.y) ? m_partyBound.m_max.y : partyObj->m_worldPosition.y;
            m_partyBound.m_max.z = (m_partyBound.m_max.z > partyObj->m_worldPosition.z) ? m_partyBound.m_max.z : partyObj->m_worldPosition.z;
        }
    }

    Wind.Frame();
    CFlatRuntime2Storage().Calc();
    gCFlatRuntime().ResetPerformance();
    CFlatRuntime2Storage().CFlatRuntime2::Frame(1, 0);

    if ((m_currentMapId == 0x21) && ((mapObjIdx = MapMng.GetMapObjIdx(0)) >= 0)) {
        static float a = 0.0f;
        a += 0.001f;
        PSMTXRotRad(rotMtx, 'y', a);
        MapMng.SetMapObjLMtx(mapObjIdx, rotMtx);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80014964
 * PAL Size: 48b
 * EN Address: 0x8001C3AC
 * EN Size: 48b
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
 * EN Address: 0x8001C3DC
 * EN Size: 48b
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
 * PAL Address: 0x800148F4
 * PAL Size: 64b
 * EN Address: 0x8001C40C
 * EN Size: 64b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::Draw()
{
	gCFlatRuntime().SystemCall(0, 1, 6, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800148C0
 * PAL Size: 52b
 * EN Address: 0x8001C44C
 * EN Size: 52b
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
 * PAL Address: 0x8001486C
 * PAL Size: 84b
 * EN Address: 0x8001C480
 * EN Size: 84b
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
 * PAL Address: 0x800147F8
 * PAL Size: 116b
 * EN Address: 0x80014690
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::HitParticleBG(int effectIndex, int kind, int nodeIndex, Vec* pos, PPPIFPARAM* hitParam)
{
	CFlatRuntime::CStack stack[8];
	stack[0].m_word = (u32)effectIndex;
	stack[1].m_word = (u32)kind;
	stack[2].m_word = (u32)nodeIndex;
	stack[3].m_float = pos->x;
	stack[4].m_float = pos->y;
	stack[5].m_float = pos->z;
	stack[6].m_word = (u32)hitParam->m_particleIndex;
	stack[7].m_word = (u32)hitParam->m_classId;
	gCFlatRuntime().SystemCall(0, 1, 1, 8, stack, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800146B4
 * PAL Size: 324b
 * EN Address: 0x8001454C
 * EN Size: 324b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::ParticleFrameCallback(int effectIndex, int scriptLine, int scriptStep, int callbackType, int graphFrame, Vec*)
{
	PPPIFPARAM* ifData = PartMng.pppGetIfDt(static_cast<short>(effectIndex));
	ifData->m_hitFlags |= 1 << callbackType;

	if (callbackType == 0) {
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf("pdtid=%d fpno=%d id=%d frame=%d パーティクル削除禁止フラグon\n", scriptLine, scriptStep, effectIndex, graphFrame);
		}
	} else if (callbackType == 1) {
		ifData->m_hitFlags &= ~2;
		PartMng.pppEndPart(effectIndex);

		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf("pdtid=%d fpno=%d id=%d frame=%d パーティクル自動削除フラグon\n", scriptLine, scriptStep, effectIndex, graphFrame);
		}
	} else if (callbackType == 3) {
		PartMng.pppEndPart(effectIndex);

		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf("pdtid=%d fpno=%d id=%d frame=%dパーティクルチャージ終了on\n", scriptLine, scriptStep, effectIndex, graphFrame);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8001462C
 * PAL Size: 136b
 * EN Address: 0x800144C4
 * EN Size: 136b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::SaveScript(char* scriptData)
{
    memset(scriptData, 0, kGameScriptSaveDataSize);
    int savedCount = 0;
    for (int i = 0; i < CFlat.m_permanentVarCount; i++) {
        if ((CFlat.m_permanentVarDefs[i].m_flags & 0x20) != 0) {
            reinterpret_cast<unsigned int*>(scriptData)[savedCount++] = CFlat.m_permanentVarValues[i];
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800145D8
 * PAL Size: 84b
 * EN Address: 0x80014470
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::LoadScript(char* scriptData)
{
    int savedCount = 0;
    for (int i = 0; i < CFlat.m_permanentVarCount; i++) {
        if ((CFlat.m_permanentVarDefs[i].m_flags & 0x20) != 0) {
            CFlat.m_permanentVarValues[i] = reinterpret_cast<unsigned int*>(scriptData)[savedCount++];
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001458C
 * PAL Size: 76b
 * EN Address: 0x8001C8E8
 * EN Size: 80b
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
 * EN Address: 0x8001C938
 * EN Size: 80b
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
 * PAL Address: 0x8001440C
 * PAL Size: 308b
 * EN Address: 0x800142A4
 * EN Size: 308b
 * JP Address: TODO
 * JP Size: TODO
 */
CGame::CBossArtifactEntry* CGame::GetBossArtifact(int ratioIndex, int amount)
{
    static float s_ratio[] = {1.35f, 1.25f, 1.1f, 1.0f};
    static s16 s_top[] = {0, 2, 4};

    int scaledAmount;
    int artifactRank;

    int stage =
        Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
    if (2 < stage) {
        stage = 2;
    }

    CBossArtifactStage* artifactBase;
    int stageBase = s_top[stage];
    scaledAmount = (int)((float)amount * s_ratio[ratioIndex - 1]);

    u16 thresholds[4];
    memset(thresholds, 0, sizeof(thresholds));

    int stageIndex = (int)Game.m_gameWork.m_bossArtifactStageIndex;
    artifactBase = Game.m_bossArtifactBase;
    artifactRank = 3;

    thresholds[1] = artifactBase[stageIndex].m_rankThresholds[1];
    thresholds[2] = artifactBase[stageIndex].m_rankThresholds[2];
    thresholds[3] = artifactBase[stageIndex].m_rankThresholds[3];

    if (((scaledAmount < (s16)thresholds[3]) && (artifactRank = 2, scaledAmount < (s16)thresholds[2])) &&
        (artifactRank = 1, scaledAmount < (s16)thresholds[1])) {
        artifactRank = 0;
    }

    stageBase += rand() % (artifactRank + 1);
    CBossArtifactEntry* entries = artifactBase[stageIndex].m_entries;
    return &entries[stageBase];
}

/*
 * --INFO--
 * PAL Address: 0x800143EC
 * PAL Size: 32b
 * EN Address: 0x8001CB4C
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
int CGame::GetFoodLevel(int playerIndex, int foodIndex)
{
    CCaravanWork* caravanWork = m_scriptFoodBase[playerIndex];
    u16 level = caravanWork->m_letterMeta[foodIndex];
    return level;
}

/*
 * --INFO--
 * PAL Address: 0x800143A4
 * PAL Size: 72b
 * EN Address: 0x8001423C
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::GetTargetCursor(int playerIndex, Vec& posA, Vec& posB)
{
    posA = m_scriptFoodBase[playerIndex]->m_targetCursorPosA;
    posB = m_scriptFoodBase[playerIndex]->m_targetCursorPosB;
}

/*
 * --INFO--
 * PAL Address: 0x800142E4
 * PAL Size: 184b
 * EN Address: 0x8001CCC4
 * EN Size: 188b
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

    if (!baseObj->IsKindOf(0x6D)) {
        return 0;
    }

    specialInfo = SAFE_CAST_CARAVAN_WORK(reinterpret_cast<CGObject*>(baseObj)->m_scriptHandle)->m_joybusCaravanId;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800142D0
 * PAL Size: 20b
 * EN Address: 0x8001CD80
 * EN Size: 20b
 * JP Address: TODO
 * JP Size: TODO
 */
CGPartyObj* CGame::GetPartyObj(int index)
{
    return m_partyObjArr[index];
}

/*
 * --INFO--
 * PAL Address: 0x800141E0
 * PAL Size: 240b
 * EN Address: 0x8001CD94
 * EN Size: 180b
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeArtItemName(char* out, int itemIndex, int count)
{
    if (count > 1) {
        MakeNumItemName(out, itemIndex, count);
    } else {
        char** itemTable = m_cFlatDataArr[1].GetTable(0);
        unsigned char hasSeparator = 0;
        char* prefix = itemTable[itemIndex * 5];
        char* name = itemTable[itemIndex * 5 + 1];

        if (strlen(prefix) != 0) {
            unsigned char languageId = m_gameWork.m_languageId;
            if ((languageId != 3) && (languageId != 4)) {
                hasSeparator = 1;
            }
        }

        const char* separator = "";
        if (hasSeparator != 0) {
            separator = " ";
        }

        sprintf(out, "%s%s%s", prefix, separator, name);
    }
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x80014144
 * PAL Size: 156b
 * EN Address: 0x8001CE48
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeArtsItemNames(char* out, int itemIndex)
{
    GameNameRow* itemTable = reinterpret_cast<GameNameRow*>(m_cFlatDataArr[1].GetTable(0));
    unsigned char hasSeparator = 0;
    char* prefix = itemTable[itemIndex].m_artPrefix;
    char* itemName = itemTable[itemIndex].m_artName;

    if (strlen(prefix) != 0) {
        unsigned char languageId = m_gameWork.m_languageId;
        if ((languageId != 3) && (languageId != 4)) {
            hasSeparator = 1;
        }
    }

    const char* separator = "";
    if (hasSeparator != 0) {
        separator = " ";
    }

    sprintf(out, "%s%s%s", prefix, separator, itemName);
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x800140C8
 * PAL Size: 124b
 * EN Address: 0x8001CED8
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeNumItemName(char* out, int itemIndex, int count)
{
    sprintf(out, "%d %s", count, GetItemName(itemIndex, count));
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x80013FD8
 * PAL Size: 240b
 * EN Address: 0x8001CF40
 * EN Size: 180b
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeArtMonName(char* out, int monIndex, int count)
{
    if (count > 1) {
        MakeNumMonName(out, monIndex, count);
    } else {
        char** monTable = m_cFlatDataArr[1].GetTable(1);
        unsigned char hasSeparator = 0;
        char* prefix = monTable[monIndex * 5];
        char* name = monTable[monIndex * 5 + 1];

        if (strlen(prefix) != 0) {
            unsigned char languageId = m_gameWork.m_languageId;
            if ((languageId != 3) && (languageId != 4)) {
                hasSeparator = 1;
            }
        }

        const char* separator = "";
        if (hasSeparator != 0) {
            separator = " ";
        }

        sprintf(out, "%s%s%s", prefix, separator, name);
    }
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x80013F3C
 * PAL Size: 156b
 * EN Address: 0x8001CFF4
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeArtsMonNames(char* out, int monIndex)
{
    GameNameRow* monTable = reinterpret_cast<GameNameRow*>(m_cFlatDataArr[1].GetTable(1));
    unsigned char hasSeparator = 0;
    char* prefix = monTable[monIndex].m_artPrefix;
    char* monName = monTable[monIndex].m_artName;

    if (strlen(prefix) != 0) {
        unsigned char languageId = m_gameWork.m_languageId;
        if ((languageId != 3) && (languageId != 4)) {
            hasSeparator = 1;
        }
    }

    const char* separator = "";
    if (hasSeparator != 0) {
        separator = " ";
    }

    sprintf(out, "%s%s%s", prefix, separator, monName);
    return out;
}

/*
 * --INFO--
 * PAL Address: 0x80013EC0
 * PAL Size: 124b
 * EN Address: 0x8001D084
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
char* CGame::MakeNumMonName(char* out, int monIndex, int count)
{
    sprintf(out, "%d %s", count, GetMonName(monIndex, count));
    return out;
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
    InitNewGame();
    m_gameInitFlag = 1;
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
inline void CGame::CGameWork::InitNewGame()
{
#ifdef VERSION_GCCJGC
    memset(&m_languageId, 0, sizeof(CGameWork) - offsetof(CGameWork, m_languageId));
#else
    memset(&m_gameDataStartMarker, 0, kGameWorkDataClearSize);
#endif
    memset(m_wmBackupParams, 0xFF, sizeof(m_wmBackupParams));

    m_scriptSysVal0 = 1;
    m_chaliceElement = 1;
#ifdef VERSION_GCCJGC
    strcpy(m_townName, "（はじまり）");
#else
    strcpy(m_townName, m_languageId == 3 ? "Tepa" : "Tipa");
#endif
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGame::CGameWork::ClearScriptChange()
{
    m_scriptSysVal0 = 1;
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
inline CGame::CGameWork::CGameWork()
{
    Init();
}

/*
 * --INFO--
 * PAL Address: 0x80013E70
 * PAL Size: 80b
 * EN Address: 0x80013D50
 * EN Size: 8b
 * JP Address: UNUSED
 * JP Size: UNUSED
 */
const char* CGame::GetLangString()
{
#if defined(VERSION_GCCE01) || defined(VERSION_GCCJGC)
    return "";
#else
    const char* localLangDirs[] = {
        "jp/", "uk/", "gr/",
        "it/", "fr/", "sp/",
    };

    return localLangDirs[m_gameWork.m_languageId];
#endif
}
