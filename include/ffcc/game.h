#ifndef _FFCC_GAME_H_
#define _FFCC_GAME_H_

#include "global.h"

#include "ffcc/cflat_data.h"
#include "ffcc/gobjwork.h"
#include "ffcc/manager.h"
#include "ffcc/memory.h"
#include "ffcc/ptrarray.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class CGObject;
class CGPrgObj;
class CGPartyObj;
class CCombi2Set;
class CGObjWork;
class CMapLightHolder;
class CBound;
class PPPIFPARAM;

class CGame : public CManager
{
public:
    class CNextScript
    {
    public:
        unsigned int m_flags;
        char m_name[256];

        CNextScript& operator=(const CNextScript&);
    };

    class CGameWork
    {
    public:
        CGameWork();

        void Init();
        void InitNewGame();
        void ClearScriptChange();

        unsigned char m_menuStageMode;                   // 0x00
        unsigned char m_gameInitFlag;                    // 0x01
        unsigned char m_spModeFlags[4];                  // 0x02
        unsigned char m_languageId;                      // 0x06
        unsigned char m_gameDataStartMarker;             // 0x07
        unsigned char m_scriptSysVal0;                   // 0x08
        unsigned char m_scriptSysVal1;                   // 0x09
        unsigned char m_scriptSysVal2;                   // 0x0A
        unsigned char m_scriptSysVal3;                   // 0x0B
        int m_timerA;                                    // 0x0C
        int m_scriptGlobalTime;                          // 0x10
        int m_frameCounter;                              // 0x14
        int m_wmBackupParams[4];                         // 0x18
        int m_bossArtifactStageTable[15];                // 0x28
        int m_unkStageTable[15];                         // 0x64
        unsigned char m_linkTable[8][8][8][8];           // 0xA0
        char m_townName[20];                             // 0x10A0
        int m_chaliceElement;                            // 0x10B4 // 1=fire,2=water,4=wind,8=earth,16=holy
        int m_eventHeader[3];                            // 0x10B8
        signed char m_eventFlags[256];                   // 0x10C4
        short m_eventWork[256];                          // 0x11C4
        int m_eventFooter[2];                            // 0x13C4
        short m_bossArtifactStageIndex;                  // 0x13CC
        unsigned short m_optionValue;                    // 0x13CE
        unsigned char m_soundOptionFlag;                 // 0x13D0
        unsigned char m_radarType;                       // 0x13D1
        unsigned char m_gameOverFlag;                    // 0x13D2
        unsigned char m_singleShopOrSmithMenuActiveFlag; // 0x13D3
        unsigned char m_gamePaused;                      // 0x13D4
        unsigned char m_mogScoreRadarType;               // 0x13D5
        unsigned short m_mcHasSerial;                    // 0x13D6
        unsigned int m_mcRandom;                         // 0x13D8
        unsigned char m_mcId;                            // 0x13DC
        unsigned char m_bgmVolume;                       // 0x13DD
        unsigned char m_seVolume;                        // 0x13DE
        unsigned char m_stereoFlag;                      // 0x13DF
        unsigned int m_mcSerial0;                        // 0x13E0
        unsigned int m_mcSerial1;                        // 0x13E4
    }; // Size 0x13E8

public:
    CGame();
    ~CGame();

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
    virtual void ScriptChanging(char*);
    virtual void ScriptChanged(char*, int);
    virtual void MapChanging(int, int);
    virtual void MapChanged(int, int, int);
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
    void GetBossArtifact(int, int);
    void GetFoodLevel(int, int);
    void GetTargetCursor(int, Vec&, Vec&);
    void GetParticleSpecialInfo(PPPIFPARAM&, int&, int&);
    void GetPartyObj(int);
    void MakeArtItemName(char*, int, int);
    void MakeArtsItemNames(char*, int);
    void MakeNumItemName(char*, int, int);
    void MakeArtMonName(char*, int, int);
    void MakeArtsMonNames(char*, int);
    void MakeNumMonName(char*, int, int);
    const char* GetLangString();
    void SetNextScript(CGame::CNextScript* nextScript);
    void SetNextScriptNewGame();
    void IsWorldMap();
    void IsPartyExist(int);
    void GetItemName(int);
    void GetItemArt(int);
    void GetItemNames(int);
    void GetItemArts(int);
    void GetItemName(int, int);
    void GetMonName(int);
    void GetMonArt(int);
    void GetMonNames(int);
    void GetMonArts(int);
    void GetMonName(int, int);

    // void* vtable;                        // 0x00
    int unk_0x4;                            // 0x04
    CGameWork m_gameWork;                   // 0x08 size 0x13E8
    CCaravanWork m_caravanWorkArr[9];       // 0x13F0 size 0x6DB0
    CMonWork m_monWorkArr[64];              // 0x81A0 size 0x4400
    unsigned int unkCFlatData0[4];          // 0xC5A0
    CGPartyObj* m_partyObjArr[4];           // 0xC5B0
    unsigned int m_scriptFoodBase[4];       // 0xC5C0
    unsigned int m_scriptWork[4][16][2];    // 0xC5D0
    unsigned int unk_flat3_0xc7d0;          // 0xC7D0
    unsigned int unk_flat3_count_0xc7d4;    // 0xC7D4
    unsigned int unk_flat3_field_1C_0xc7d8; // 0xC7D8
    unsigned int unk_flat3_field_8_0xc7dc;  // 0xC7DC
    unsigned int unk_flat3_field_30_0xc7e0; // 0xC7E0
    unsigned int m_bossArtifactBase;        // 0xC7E4
    unsigned int m_currentMapId;            // 0xC7E8
    unsigned int m_currentMapVariantId;     // 0xC7EC
    unsigned int m_currentSceneId;          // 0xC7F0
    char m_currentScriptName[256];          // 0xC7F4
    char m_startScriptName[256];            // 0xC8F4
    float m_partyMinX;                      // 0xC9F4
    float m_partyMinY;                      // 0xC9F8
    float m_partyMinZ;                      // 0xC9FC
    float m_partyMaxX;                      // 0xCA00
    float m_partyMaxY;                      // 0xCA04
    float m_partyMaxZ;                      // 0xCA08
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
    CNextScript m_nextScript;               // 0xCB2C
    CMemory::CStage* m_mainStage;           // 0xCC30
    CMemory::CStage* m_debugStage;          // 0xCC34
    CFlatData m_cFlatDataArr[4];            // 0xCC38 stride 0x14D4, total 0x5350
}; // Size 0x11F88

STATIC_ASSERT(sizeof(CGame::CGameWork) == 0x13E8);
STATIC_ASSERT(sizeof(CGame) == 0x11F88);

#endif // _FFCC_GAME_H_
