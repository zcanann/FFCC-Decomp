#ifndef _FFCC_GBAQUEUE_H_
#define _FFCC_GBAQUEUE_H_

#include <Dolphin/os.h>

struct GbaPInfo;
struct GbaCMakeInfo;
class HitEInfo;

struct GbaCMakeInfo
{
    unsigned char m_active;
    unsigned char m_resultCode;
    short m_packetCount;
    unsigned short m_crc;
    unsigned char m_playerSlot;
    char m_name[0x11];
    unsigned char m_charaType;
    unsigned char m_birthDate[2]; // month, day
    unsigned char m_favorite[4];
    unsigned char m_jobType;
};

struct GbaQueueHitInfo
{
    short m_enemyId;
    short m_enemyType;
};

struct GbaQueueMapObjEntry
{
    unsigned char m_type;
    unsigned char _pad01[3];
    short m_x;
    short m_y;
    short m_z;
    short m_radius;
};

struct GbaQueueMapObjWork
{
    unsigned char m_count;
    unsigned char _pad01[3];
    unsigned int m_drawFlags;
    GbaQueueMapObjEntry m_entries[32];
};

struct GbaQueuePlayerDataView
{
    signed char m_saveSlot;
    unsigned char m_hasPartyObj;
    unsigned char m_appearance;
    char m_active;
    unsigned char m_compatibility[16];
    unsigned short m_progress;
    signed char m_maxHp;
    signed char m_hp;
    unsigned char m_letterMeta[8];
    unsigned char m_strength[3];
    unsigned char m_useItem;
    unsigned int m_gil;
    unsigned int m_artifacts[3];
    unsigned short _pad34;
    short m_mapPosition[2];
    short m_items[0x40];
    unsigned short m_tmpArtifacts[4];
    unsigned short m_commandSlots[8];
    unsigned char m_bonusCondition;
    char m_commandSlotCount;
    unsigned char m_radarVisible;
    unsigned char _padD5;
    char m_itemFlags;
    unsigned char m_equipment[4];
};

struct GbaPInfo
{
    GbaQueuePlayerDataView m_players[4];
};

struct GbaQueueMapEntity
{
    char m_visible;
    char m_kind;
    char m_radarEnabled;
    unsigned char m_baseDataIndex;
    unsigned short m_hp;
    unsigned short m_maxHp;
    short m_posX;
    short m_posZ;
    short m_dropItemCodes[4];
};

class GbaQueue
{
public:
    GbaQueue();
    ~GbaQueue();

    void Init();
    void BlockSem(int);
    void ReleaseSem(int);
    void LoadAll();
    void ClrShopMode();
    void LoadMask();
    int SetQueue(int, unsigned int);
    void ResetQueue();
    void ExecutQueue();
    void ChgItemData(int, unsigned int);
    void ChgMoneyData(int, unsigned int);
    void ChgEquipPosData(int, unsigned int);
    void ChgCmdLstData(int, unsigned int);
    void SetSellData(int, unsigned int);
    void SetBuyData(int, unsigned int);
    void SetSmithData(int, unsigned int);
    void SetStageNo(int, int);
    void GetStageNo(int, int*, int*);
    unsigned int GetStageFlg(int);
    void ClrStageFlg(int);
    void SetRadarType();
    void GetMBasePos(int, short*, short*);
    void LoadAllStat();
    void LoadPlayerStat();
    void LoadEnemyStat();
    void LoadMapItemStat();
    void GetPlayerPos(int, unsigned int*);
    void GetEnemyPos(int, unsigned int*, int*);
    void GetTreasurePos(int, unsigned int*, int*);
    int GetMapObjInfo(int, unsigned char*);
    void GetPlayerStat(int, GbaPInfo*);
    void GetCaravanName(char*);
    int GetItemAll(int, unsigned char*);
    unsigned int GetScrFlg();
    int GetPlayerHP(int, unsigned char*);
    int MakeLetterList(int, char*);
    int MakeLetterData(int, char*, int);
    unsigned int GetLetterLstFlg(int);
    void ClrLetterLstFlg(int);
    unsigned int GetLetterDatFlg(int);
    void ClrLetterDatFlg(int);
    void MoveLetterItem(int, unsigned int);
    void ReplyLetter(int);
    void LoadMapObj();
    int GetMapObj(unsigned char*);
    void GetMapObjDrawFlg(unsigned int*);
    void SetAddLetter(int);
    unsigned int GetFavoriteFlg(int);
    void ClrFavoriteFlg(int);
    int GetFavorite(int, char*);
    unsigned int GetMoneyFlg(int);
    void ClrMoneyFlg(int);
    int GetMoney(int);
    void ClrScrInitEnd();
    void InitCmakeInfo(int, int);
    void ClrCmakeInfo(int);
    void ChkCMakeName(int, unsigned int);
    void ChkCMakeCharaType(int, unsigned int);
    void ChkCMakeJob(int, unsigned int);
    void CMakeEnd(int, unsigned int);
    void CMakeBarthday(int, unsigned int);
    void CMakeFavorite(int, unsigned int);
    unsigned int GetCompatibilityFlg(int);
    void ClrCompatibilityFlg(int);
    int GetCompatibility(int, unsigned char*);
    void GetCMakeInfo(int, GbaCMakeInfo*);
    int GetCmdData(int, unsigned char*);
    int GetEquipData(int, unsigned char*);
    void SetShopFlg(int);
    void ClrShopFlg(int);
    void SetSmithFlg(int);
    void ClrSmithFlg(int);
    void ShopEnd(int);
    void SmithEnd(int);
    int MakeBuyData(int, char*);
    int MakeSellData(int, char*);
    int MakeSmithData(int, char*);
    unsigned int GetSellFlg(int);
    void ClrSellFlg(int);
    unsigned int GetBuyFlg(int);
    void ClrBuyFlg(int);
    unsigned int GetMkSmithFlg(int);
    void ClrMkSmithFlg(int);
    void SetResetFlg(int);
    int GetBonus(int);
    unsigned int GetArtifactFlg(int);
    void ClrArtifactFlg(int);
    int GetArtifactData(int, unsigned char*);
    int GetUseItemFlg(int);
    unsigned int GetChgUseItemFlg(int);
    void ClrChgUseItemFlg(int);
    void SetChgUseItemFlg(int);
    unsigned int GetStrengthFlg(int);
    void ClrStrengthFlg(int);
    void GetStrengthData(int, unsigned char*);
    unsigned int GetArtiDatFlg(int);
    void ClrArtiDatFlg(int);
    int MakeArtiData(int, char*);
    int GetTmpArtifactData(int, unsigned char*);
    int GetRadarType(int);
    void ClrRadarTypeFlg();
    unsigned int GetRadarMode(int);
    void SetRadarMode(int, int);
    unsigned int GetChgRadarMode(int);
    void ClrChgRadarMode(int);
    int GetScouterInfo(int, unsigned char*);
    unsigned int GetChgHitFlg(int);
    void ClrChgHitFlg(int);
    unsigned int GetChgScouFlg(int);
    void ClrChgScouFlg(int);
    void SetHitEnemy(int, int);
    int GetHitEInfo(int);
    bool IsSingleMode(int);
    void SetControllerMode(int);
    unsigned int GetControllerMode();
    void OpenMenu(int, int, int);
    void SetPauseMode(int);
    unsigned int GetPauseMode();
    int GetItemUse(int);
    unsigned int GetSPModeFlg(int);
    void ClrSPModeFlg(int);
    unsigned int GetSPMode(int);
    unsigned int GetMemorysFlg(int);
    void ClrMemorysFlg(int);
    unsigned int GetMemorys(int);
    unsigned int GetCmdNumFlg(int);
    void ClrCmdNumFlg(int);
    int GetCmdNum(int);
    unsigned int GetPlayModeFlg(int);
    void ClrPlayModeFlg(int);
    void SetStartBonusFlg();
    unsigned int GetStartBonusFlg(int);
    void ClrStartBonusFlg(int);

private:
    OSSemaphore accessSemaphores[4];  // 0x0000
    unsigned int m_queue[4][0x40];    // 0x0030
    int m_queueCount[4];              // 0x0430
    char m_queueFull[4];              // 0x0440
    int m_stageNo;                    // 0x0444
    int m_mapNo;                      // 0x0448
    unsigned char m_stageFlags;       // 0x044C
    unsigned char _pad44D[0x7];       // 0x044D
    GbaQueuePlayerDataView m_playerData[4]; // 0x0454
    GbaQueuePlayerDataView m_playerHistory[4]; // 0x07C4
    GbaQueueMapEntity m_enemies[64];            // 0x0B34
    GbaQueueMapEntity m_enemyHistory[4][64];    // 0x1034
    GbaQueueMapEntity m_mapItems[16];           // 0x2434
    GbaQueueMapEntity m_mapItemHistory[4][16];  // 0x2574
    char m_caravanName[0x80];                  // 0x2A74
    char m_mapItemCount;              // 0x2AF4
    unsigned char _pad2AF5[0x3];      // 0x2AF5
    int m_scrInitEnd;                 // 0x2AF8
    unsigned char m_letterDatFlg;     // 0x2AFC
    unsigned char _pad2AFD[0x3];      // 0x2AFD
    GbaQueueMapObjWork m_mapObjWork;  // 0x2B00
    unsigned char m_makeMapObjFlg;    // 0x2C88
    signed char m_letterFlags;        // 0x2C89
    unsigned char m_compatibilityFlg[4]; // 0x2C8A
    unsigned short m_sendMask[4];     // 0x2C8E
    signed char m_maskSendState[4];   // 0x2C96
    unsigned char _pad2C9A[0x2];      // 0x2C9A
    unsigned int m_pendingMoney[4];   // 0x2C9C
    signed char m_moneyState[4];      // 0x2CAC
    unsigned char m_moneyFlags;       // 0x2CB0
    unsigned char m_favoriteFlags;    // 0x2CB1
    GbaCMakeInfo cmakeInfo[4];        // 0x2CB2
    char m_radarType[4];              // 0x2D32
    unsigned char m_artifactFlags;    // 0x2D36
    unsigned char m_chgUseItemFlags;  // 0x2D37
    unsigned char m_shopFlags;        // 0x2D38
    unsigned char m_shopStatusFlags;  // 0x2D39
    unsigned char m_sellFlg;          // 0x2D3A
    unsigned char m_buyFlg;           // 0x2D3B
    unsigned char m_mkSmithFlg;       // 0x2D3C
    unsigned char m_resetFlags;       // 0x2D3D
    unsigned char m_strengthFlags;    // 0x2D3E
    unsigned char m_artiDatFlags;     // 0x2D3F
    unsigned char m_radarTypeFlags;   // 0x2D40
    char m_radarMode;                 // 0x2D41
    char m_chgRadarMode;              // 0x2D42
    unsigned char _pad2D43;           // 0x2D43
    GbaQueueHitInfo m_hitInfo[4];      // 0x2D44
    unsigned char m_chgHitFlags;      // 0x2D54
    unsigned char m_chgScouFlags;     // 0x2D55
    char m_singleMode;                // 0x2D56
    char m_controllerMode;            // 0x2D57
    unsigned char _pad2D58;           // 0x2D58
    unsigned char m_prevOutOfShoukiFlags; // 0x2D59
    unsigned char m_outOfShoukiFlags;     // 0x2D5A
    char m_pauseMode;                 // 0x2D5B
    unsigned char m_spModeBits;       // 0x2D5C
    unsigned char m_spModeFlags;      // 0x2D5D
    unsigned char m_memorysFlags;     // 0x2D5E
    char m_cmdNumFlags;               // 0x2D5F
    unsigned char m_playModeFlags;    // 0x2D60
    unsigned char m_startBonusFlags;  // 0x2D61
    unsigned char _pad2D62[0x2];      // 0x2D62
};

extern GbaQueue GbaQue;

#endif // _FFCC_GBAQUEUE_H_
