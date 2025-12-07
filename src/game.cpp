#include "ffcc/game.h"

#include "ffcc/partyobj.h"
#include "ffcc/system.h"
#include "ffcc/vector.h"

static const float FLOAT_8032f688 = 1.0E+10;
static const float FLOAT_8032f68c = -1.0E+10;
static const float FLOAT_8032f690 = 0.0;    
static const float FLOAT_8032f694 = 0.001;

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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::LoadLogoWaitingData()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::ScriptChanging(char*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::LoadInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::LoadFinished()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetFoodLevel(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::GetTargetCursor(int, Vec&, Vec&)
{
	// TODO
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
void CGame::GetPartyObj(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
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

    // Safety in case languageId is out of range.
    if (m_gameWork.m_languageId >= sizeof(sLangDirs) / sizeof(sLangDirs[0]))
	{
        return sLangDirs[0];
    }

    return sLangDirs[m_gameWork.m_languageId];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGame::SetNextScript(CGame::CNextScript* nextScript)
{ 
	nextScript->m_flags = 1;
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
