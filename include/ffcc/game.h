#ifndef _FFCC_GAME_H_
#define _FFCC_GAME_H_

#include "global.h"

#include "ffcc/cflat_data.h"
#include "ffcc/mapocttree.h"
#include "ffcc/gobjwork.h"
#include "ffcc/manager.h"
#include "ffcc/memory.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern "C" int toupperLatin1(unsigned char character);

class CGObject;
class CGPrgObj;
class CGPartyObj;
class CCombi2;
class CGObjWork;
class CMapLightHolder;
class PPPIFPARAM;

class CGame : public CManager
{
public:
    class CNextScript
    {
    public:
        char m_name[256];
    };

    class CGameWork
    {
    public:
        CGameWork();

        void Init();
        void InitNewGame();
        void ClearScriptChange();
        void ClearEvtWork();

        int GetNumPlayer()
        {
            int numPlayer = 0;
            for (int i = 0; i < 4; i++) {
                if (m_wmBackupParams[i] >= 0) {
                    numPlayer++;
                }
            }
            return numPlayer;
        }
        bool IsBattleStage() { return m_bossArtifactStageIndex < 0xF; }
        bool IsMogStage() { return m_bossArtifactStageIndex == 0x19; }
        bool IsBonusStage() { return m_bossArtifactStageIndex < 0xE; }
        unsigned char GetLanguage() { return m_languageId; }

        unsigned char m_menuStageMode;                   // 0x00
        unsigned char m_gameInitFlag;                    // 0x01
        unsigned char m_spModeFlags[4];                  // 0x02
        unsigned char m_languageId;                      // 0x06
        unsigned char m_gameDataStartMarker;             // 0x07
        unsigned int m_scriptSysVal0;                    // 0x08
        int m_timerA;                                    // 0x0C
        int m_scriptGlobalTime;                          // 0x10
        int m_frameCounter;                              // 0x14
        int m_wmBackupParams[4];                         // 0x18
        int m_bossArtifactStageTable[15];                // 0x28
        int m_unkStageTable[15];                         // 0x64
        unsigned char m_linkTable[8][8][8][8];           // 0xA0
        char m_townName[20];                             // 0x10A0
        int m_chaliceElement;                            // 0x10B4 // 1=fire,2=water,4=wind,8=earth,16=holy
        int m_eventHeader[5];                            // 0x10B8
        signed char m_eventFlags[256];                   // 0x10CC
        short m_eventWork[256];                          // 0x11CC
        short m_bossArtifactStageIndex;                  // 0x13CC
        unsigned short m_optionValue;                    // 0x13CE
        unsigned char m_soundOptionFlag;                 // 0x13D0
        unsigned char m_radarType;                       // 0x13D1
        unsigned char m_gameOverFlag;                    // 0x13D2
        unsigned char m_singleShopOrSmithMenuActiveFlag; // 0x13D3
        unsigned char m_gamePaused;                      // 0x13D4
        unsigned char m_mogScoreRadarType;               // 0x13D5
        unsigned char m_mcHasSerial;                     // 0x13D6
        unsigned char unk_0x13D7;                        // 0x13D7
        unsigned int m_mcRandom;                         // 0x13D8
        unsigned char m_mcId;                            // 0x13DC
        unsigned char m_bgmVolume;                       // 0x13DD
        unsigned char m_seVolume;                        // 0x13DE
        unsigned char m_stereoFlag;                      // 0x13DF
        u64 m_mcSerial;                                  // 0x13E0
    }; // Size 0x13E8

    struct CBossArtifactEntry
    {
        unsigned short m_values[4]; // 0x00
    }; // Size 0x08

    struct CBossArtifactStage
    {
        unsigned short m_bonusConditions[16];    // 0x00
        union {
            CBossArtifactEntry m_entries[40];    // 0x20
            struct {
                CBossArtifactEntry m_prefixEntries[8]; // 0x20
                CBossArtifactEntry m_bonusEntries[32]; // 0x60
            } m_entryView;
        };
        unsigned short m_rankThresholds[4];      // 0x160
    }; // Size 0x168

public:
    CGame();

    void Init();
    void Quit();
    void LoadLogoWaitingData();
    void Exec();
    void Create();
    void Destroy();
    void InitNewGame();
    void clearWork();
    void clearWorkMap();
    void clearWorkScript();
    void CheckScriptChange();
    void ChangeMap(int, int, int, int);
    void ScriptChanging(char*);
    void ScriptChanged(char*, int);
    void MapChanging(int, int);
    void MapChanged(int, int, int);
    void loadCfd();
    void Calc();
    void Calc2();
    void Calc3();
    void Draw();
    void Draw2();
    void Draw3();
    void HitParticleBG(int, int, int, Vec*, PPPIFPARAM*);
    void ParticleFrameCallback(int, int, int, int, int, Vec*);
    void SaveScript(char*);
    void LoadScript(char*);
    void LoadInit();
    void LoadFinished();
    CBossArtifactEntry* GetBossArtifact(int, int);
    int GetFoodLevel(int, int);
    void GetTargetCursor(int, Vec&, Vec&);
    int GetParticleSpecialInfo(PPPIFPARAM&, int&, int&);
    CGPartyObj* GetPartyObj(int);
    char* MakeArtItemName(char*, int, int);
    char* MakeArtsItemNames(char*, int);
    char* MakeNumItemName(char*, int, int);
    char* MakeArtMonName(char*, int, int);
    char* MakeArtsMonNames(char*, int);
    char* MakeNumMonName(char*, int, int);
    const char* GetLangString();
    void SetNextScript(CGame::CNextScript* nextScript);
    void SetNextScriptNewGame();
    int IsWorldMap() { return m_currentMapId == 0x21; }
    int IsPartyExist(int);
    char* GetItemName(int);
    char* GetItemArt(int);
    char* GetItemNames(int);
    char* GetItemArts(int);
    char* GetItemName(int, int);
    int GetGbaSP(int idx) { return m_gameWork.m_spModeFlags[idx]; }
    void SetGbaSP(int idx, int sp) { m_gameWork.m_spModeFlags[idx] = sp; }
    int GetMark() { return m_gameWork.m_gameInitFlag; }
    void SetMark(int mark) { m_gameWork.m_gameInitFlag = mark; }
#ifdef VERSION_GCCJGC
    char* GetShortItemName(int itemIndex) { return m_cFlatDataArr[1].TableStrings(0)[itemIndex]; }
#else
    char* GetShortItemName(int itemIndex) { return m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5 + 4]; }
#endif
    char* GetRingName(int ringIndex) { return m_cFlatDataArr[1].TableStrings(4)[ringIndex]; }
    char* GetHelpName(int helpIndex) { return m_cFlatDataArr[1].TableStrings(6)[helpIndex]; }
    char* GetBonusName(int bonusIndex) { return m_cFlatDataArr[1].TableStrings(7)[bonusIndex]; }
    char* GetNPCName(int npcIndex) { return m_cFlatDataArr[1].TableStrings(2)[npcIndex]; }
    char* GetLetterSubject(int subjectIndex) { return m_cFlatDataArr[1].TableStrings(5)[subjectIndex]; }
    char* GetPlaceName(int placeIndex) { return m_cFlatDataArr[1].TableStrings(3)[placeIndex]; }
    void UpperItemName(char* name)
    {
        if (name[0] != '\0') {
            name[0] = toupperLatin1(name[0]);
        }
    }
    char* GetLetter(int letterType) { return m_cFlatDataArr[1].Message(letterType * 2 + 0x10); }
    char* GetLetterReply(int letterType) { return m_cFlatDataArr[1].Message(letterType * 2 + 0x11); }
    char* GetMonName(int);
    char* GetMonArt(int);
    char* GetMonNames(int);
    char* GetMonArts(int);
    char* GetMonName(int, int);
    char* GetSysMes(int);
    int GetEvtFlag(int);
    void SetEvtFlag(int, int);

    // void* vtable;                        // 0x00
    int unk_0x4;                            // 0x04
    CGameWork m_gameWork;                   // 0x08 size 0x13E8
    CCaravanWork m_caravanWorkArr[9];       // 0x13F0 size 0x6DB0
    CMonWork m_monWorkArr[64];              // 0x81A0 size 0x4400
    unsigned int unkCFlatData0[3];          // 0xC5A0
    unsigned int m_romLetterWorkBase;       // 0xC5AC
    CGPartyObj* m_partyObjArr[4];           // 0xC5B0
    CCaravanWork* m_scriptFoodBase[4];       // 0xC5C0
    CGObject* m_monObjects[64];             // 0xC5D0
    CMonWork* m_monWorkRefs[64];             // 0xC6D0
    unsigned int unk_flat3_0xc7d0;          // 0xC7D0
    unsigned int m_combiCount;             // 0xC7D4
    CCombi2* m_combiTable;                 // 0xC7D8
    unsigned int unk_flat3_field_8_0xc7dc;  // 0xC7DC
    unsigned int unk_flat3_field_30_0xc7e0; // 0xC7E0
    CBossArtifactStage* m_bossArtifactBase; // 0xC7E4
    unsigned int m_currentMapId;            // 0xC7E8
    unsigned int m_currentMapVariantId;     // 0xC7EC
    int m_currentSceneId;                   // 0xC7F0
    char m_currentScriptName[256];          // 0xC7F4
    char m_startScriptName[256];            // 0xC8F4
    CBound m_partyBound;                    // 0xC9F4
    int m_frameCounterEnable;               // 0xCA0C
    float unkFloat_0xca10;                  // 0xCA10
    unsigned char m_cfdLoadedFlag;          // 0xCA14
    unsigned char m_assetsLoadedFlag;       // 0xCA15
    unsigned char unk_0xca16[2];            // 0xCA16
    int m_sceneId;                          // 0xCA18
    char m_sceneScript[256];                // 0xCA1C
    int m_pendingMapId;                     // 0xCB1C
    int m_mapId;                            // 0xCB20
    int m_mapVariant;                       // 0xCB24
    int m_newGameFlag;                      // 0xCB28
    unsigned int m_nextScriptFlags;         // 0xCB2C
    CNextScript m_nextScript;               // 0xCB30
    CMemory::CStage* m_mainStage;           // 0xCC30
    CMemory::CStage* m_debugStage;          // 0xCC34
    CFlatData m_cFlatDataArr[4];            // 0xCC38 stride 0x14D4, total 0x5350
}; // Size 0x11F88

inline int CGame::GetEvtFlag(int evtFlagIndex)
{
    int byteIndex = evtFlagIndex / 8;
    unsigned char value = m_gameWork.m_eventFlags[byteIndex];
    int mask = 1 << (evtFlagIndex % 8);
    unsigned int flag = value & mask;

    return flag != 0;
}

inline void CGame::SetEvtFlag(int evtFlagIndex, int value)
{
    if (value != 0) {
        int byteIndex = evtFlagIndex / 8;
        int bit = 1 << (evtFlagIndex % 8);
        m_gameWork.m_eventFlags[byteIndex] |= bit;
        return;
    }

    {
        int byteIndex = evtFlagIndex / 8;
        int bit = 1 << (evtFlagIndex % 8);
        m_gameWork.m_eventFlags[byteIndex] &= ~bit;
    }
}

STATIC_ASSERT(sizeof(CGame::CGameWork) == 0x13E8);
STATIC_ASSERT(offsetof(CGame::CGameWork, m_mcSerial) == 0x13E0);
STATIC_ASSERT(offsetof(CGame, m_gameWork) == 0x08);
STATIC_ASSERT(sizeof(CGame::CBossArtifactEntry) == 0x08);
STATIC_ASSERT(sizeof(CGame::CBossArtifactStage) == 0x168);
STATIC_ASSERT(offsetof(CGame::CBossArtifactStage, m_entries) == 0x20);
STATIC_ASSERT(offsetof(CGame::CBossArtifactStage, m_rankThresholds) == 0x160);
STATIC_ASSERT(offsetof(CGame, m_monObjects) == 0xC5D0);
STATIC_ASSERT(offsetof(CGame, m_monWorkRefs) == 0xC6D0);
STATIC_ASSERT(offsetof(CGame, m_bossArtifactBase) == 0xC7E4);
STATIC_ASSERT(sizeof(CGame) == 0x11F88);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline char* CGame::GetItemName(int itemIndex)
{
#ifdef VERSION_GCCJGC
    return m_cFlatDataArr[1].TableStrings(0)[itemIndex];
#else
    return m_cFlatDataArr[1].TableStrings(0)[itemIndex * 5 + 1];
#endif
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
#ifdef VERSION_GCCJGC
    return m_cFlatDataArr[1].TableStrings(1)[monIndex];
#else
    return m_cFlatDataArr[1].TableStrings(1)[monIndex * 5 + 1];
#endif
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

extern CGame Game;

#endif // _FFCC_GAME_H_
