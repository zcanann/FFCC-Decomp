#ifndef _FFCC_GAME_H_
#define _FFCC_GAME_H_

#include "ffcc/cflat_data.h"
#include "ffcc/gobjwork.h"
#include "ffcc/manager.h"
#include "ffcc/memory.h"

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

        unsigned char placeholder1[0x6];
        unsigned char m_languageId;
        unsigned char placeholder2[0x14 - 0x7];
        int m_frameCounter;
        unsigned char placeholder3[0x13E8 - 0x18];
    };

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

    // void*vtable;                         // [0x00]
    int unk_0x4;                            // [0x04]
    CGameWork m_gameWork;                   // [0x08]
    CCaravanWork m_caravanWorkArr[9];       // [0x13F0] size 0x6DB0
    CMonWork m_monWorkArr[64];              // [0x81A0] size 0x4400
    unsigned int unkCFlatData0[4];          // [0xC5A0]
    CGPartyObj* m_partyObjArr[4];           // [0xC5B0]
    unsigned char* m_scriptFoodBase[4];     // [0xC5C0]
    unsigned int m_scriptWork[4][16][2];    // [0xC5D0]
    unsigned int unk_flat3_0xc7d0;          // [0xC7D0]
    unsigned int unk_flat3_count_0xc7d4;    // [0xC7D4]
    unsigned int unk_flat3_field_1C_0xc7d8; // [0xC7D8]
    unsigned int unk_flat3_field_8_0xc7dc;  // [0xC7DC]
    unsigned int unk_flat3_field_30_0xc7e0; // [0xC7E0]
    unsigned int m_bossArtifactBase;        // [0xC7E4]
    unsigned int m_currentMapId;            // [0xC7E8]
    unsigned int m_currentMapVariantId;     // [0xC7EC]
    unsigned int m_currentSceneId;          // [0xC7F0]
    char m_currentScriptName[256];          // [0xC7F4]
    char m_startScriptName[256];            // [0xC8F4]
    float m_partyMinX;                      // [0xC9F4]
    float m_partyMinY;                      // [0xC9F8]
    float m_partyMinZ;                      // [0xC9FC]
    float m_partyMaxX;                      // [0xCA00]
    float m_partyMaxY;                      // [0xCA04]
    float m_partyMaxZ;                      // [0xCA08]
    int m_frameCounterEnable;               // [0xCA0C]
    float unkFloat_0xca10;                  // [0xCA10]
    unsigned char m_cfdLoadedFlag;          // [0xCA14]
    unsigned char m_assetsLoadedFlag;       // [0xCA15]
    unsigned char unk_0xca16[2];            // [0xCA16]
    int m_sceneId;                          // [0xCA18]
    char m_sceneScript[256];                // [0xCA1C] header at +0, script at +4
    int m_mapId;                            // [0xCB1C]
    int m_mapVariant;                       // [0xCB20]
    int m_scriptChangeFlag;                 // [0xCB24]
    int m_newGameFlag;                      // [0xCB28]
    CNextScript m_nextScript;               // [0xCB2C]
    CMemory::CStage* m_mainStage;           // [0xCC30]
    CMemory::CStage* m_debugStage;          // [0xCC34]
    CFlatData m_cFlatDataArr[4];            // [0xCC38] stride 0x14D4, total 0x5350
};

#endif // _FFCC_GAME_H_
