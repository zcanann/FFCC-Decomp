#include "ffcc/game.h"

#include "ffcc/partyobj.h"
#include "ffcc/system.h"
#include "ffcc/vector.h"
#include "ffcc/p_dbgmenu.h"

#include <dolphin/os/OSMemory.h>
#include <dolphin/os/OSRtc.h>
#include <string.h>

extern "C" {
void Quit__12CFlatRuntimeFv(void*);
void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
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
void* CreateStage__7CMemoryFUlPci(void*, unsigned long, const char*, int);
void Init__12CFlatRuntimeFv(void*);
void Printf__7CSystemFPce(CSystem* system, const char* format, ...);
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
extern const char DAT_801d61dc[];
}

static const float FLOAT_8032f688 = 1.0E+10;
static const float FLOAT_8032f68c = -1.0E+10;
static const float FLOAT_8032f690 = 0.0;    
static const float FLOAT_8032f694 = 0.001;
static const char s_mainStageName[] = "game_main";
static const char s_debugStageName[] = "game_debug";

// Uninitialized
static float FLOAT_8032ec40;
static bool BOOL_8032ec44;

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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Exec()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Create()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::InitNewGame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::clearWork()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::CheckScriptChange()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::ChangeMap(int mapId, int mapVariant, int param4, int param5)
{
    bool hasParam = (param4 != 0);

    if (param5 == 0)
    {
        // LoadMap(&MapPcs, mapId, mapVariant, hasParam ? 0x800000 : 0, hasParam ? 0x580000 : 0, param4 & 0xFF);
        // LoadFieldPdt(&PartPcs, mapId, mapVariant, hasParam ? 0xD80000 : 0, hasParam ? 0x80000 : 0, param4 & 0xFF);
    }
    else
    {
        // Graphic._WaitDrawDone(s_game_cpp_801d6190, 0x24e);
        System.MapChanging(mapId, mapVariant);

        m_currentMapId = mapId;
        m_currentMapVariantId = mapVariant;

        // LoadMap(&MapPcs, mapId, mapVariant, hasParam ? 0x800000 : 0, hasParam ? 0x580000 : 0, 0);
        // LoadFieldPdt(&PartPcs, mapId, mapVariant, hasParam ? 0xD80000 : 0, hasParam ? 0x80000 : 0, 0);

        System.MapChanged(mapId, mapVariant, 1);
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::ScriptChanged(char*, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::loadCfd()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Calc2()
{
	// CFlat.Frame(0, 1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Calc3()
{ 
	// CheckMenu__10CGPartyObjFv();
	// AfterFrame__12CFlatRuntimeFi(&CFlat,0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Draw2()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Draw3()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::HitParticleBG(int, int, int, Vec*, PPPIFPARAM*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::ParticleFrameCallback(int, int, int, int, int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::SaveScript(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::LoadScript(char*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetBossArtifact(int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetParticleSpecialInfo(PPPIFPARAM&, int&, int&)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MakeArtItemName(char*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MakeArtsItemNames(char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MakeNumItemName(char*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MakeArtMonName(char*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MakeArtsMonNames(char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::MakeNumMonName(char*, int, int)
{
	// TODO
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
    static const char* const sLangDirs[] =
    {
        "jp/",
        "uk/",
        "gr/",
        "it/",
        "fr/",
        "sp/"
    };
    const char* localLangDirs[6];

    localLangDirs[0] = sLangDirs[0];
    localLangDirs[1] = sLangDirs[1];
    localLangDirs[2] = sLangDirs[2];
    localLangDirs[3] = sLangDirs[3];
    localLangDirs[4] = sLangDirs[4];
    localLangDirs[5] = sLangDirs[5];

    return localLangDirs[m_gameWork.m_languageId];
}

/*
 * --INFO--
 * PAL Address: 0x800b9928
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGame::SetNextScript(CGame::CNextScript* nextScript)
{ 
    memcpy(&m_nextScript, nextScript, sizeof(CNextScript));
    m_newGameFlag = 1;
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
