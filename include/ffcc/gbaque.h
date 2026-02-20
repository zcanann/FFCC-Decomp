#ifndef _FFCC_GBAQUEUE_H_
#define _FFCC_GBAQUEUE_H_

#include <Dolphin/os.h>

class GbaPInfo;
class GbaCMakeInfo;
class HitEInfo;

struct GbaPInfo
{
    GbaPInfo &operator=(const GbaPInfo&);
};

struct GbaCMakeInfo
{
    GbaCMakeInfo &operator=(const GbaCMakeInfo&);
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
    void GetStageFlg(int);
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
    void GetScrFlg();
    int GetPlayerHP(int, unsigned char*);
    void MakeLetterList(int, char*);
    void MakeLetterData(int, char*, int);
    void GetLetterLstFlg(int);
    void ClrLetterLstFlg(int);
    void GetLetterDatFlg(int);
    void ClrLetterDatFlg(int);
    void MoveLetterItem(int, unsigned int);
    void ReplyLetter(int);
    void LoadMapObj();
    int GetMapObj(unsigned char*);
    void GetMapObjDrawFlg(unsigned int*);
    void SetAddLetter(int);
    void GetFavoriteFlg(int);
    void ClrFavoriteFlg(int);
    int GetFavorite(int, char*);
    void GetMoneyFlg(int);
    void ClrMoneyFlg(int);
    void GetMoney(int);
    void ClrScrInitEnd();
    void InitCmakeInfo(int, int);
    void ClrCmakeInfo(int);
    void ChkCMakeName(int, unsigned int);
    void ChkCMakeCharaType(int, unsigned int);
    void ChkCMakeJob(int, unsigned int);
    void CMakeEnd(int, unsigned int);
    void CMakeBarthday(int, unsigned int);
    void CMakeFavorite(int, unsigned int);
    void GetCompatibilityFlg(int);
    void ClrCompatibilityFlg(int);
    int GetCompatibility(int, unsigned char*);
    void GetCMakeInfo(int, GbaCMakeInfo*);
    void GetCmdData(int, unsigned char*);
    int GetEquipData(int, unsigned char*);
    void SetShopFlg(int);
    void ClrShopFlg(int);
    void SetSmithFlg(int);
    void ClrSmithFlg(int);
    void ShopEnd(int);
    void SmithEnd(int);
    void MakeBuyData(int, char*);
    void MakeSellData(int, char*);
    void MakeSmithData(int, char*);
    void GetSellFlg(int);
    void ClrSellFlg(int);
    void GetBuyFlg(int);
    void ClrBuyFlg(int);
    void GetMkSmithFlg(int);
    void ClrMkSmithFlg(int);
    void SetResetFlg(int);
    void GetBonus(int);
    void GetArtifactFlg(int);
    void ClrArtifactFlg(int);
    int GetArtifactData(int, unsigned char*);
    void GetUseItemFlg(int);
    void GetChgUseItemFlg(int);
    void ClrChgUseItemFlg(int);
    void SetChgUseItemFlg(int);
    void GetStrengthFlg(int);
    void ClrStrengthFlg(int);
    int GetStrengthData(int, unsigned char*);
    void GetArtiDatFlg(int);
    void ClrArtiDatFlg(int);
    void MakeArtiData(int, char*);
    int GetTmpArtifactData(int, unsigned char*);
    unsigned char GetRadarType(int);
    void ClrRadarTypeFlg();
    void GetRadarMode(int);
    void SetRadarMode(int, int);
    void GetChgRadarMode(int);
    void ClrChgRadarMode(int);
    int GetScouterInfo(int, unsigned char*);
    void GetChgHitFlg(int);
    void ClrChgHitFlg(int);
    void GetChgScouFlg(int);
    void ClrChgScouFlg(int);
    void SetHitEnemy(int, int);
    void GetHitEInfo(int);
    bool IsSingleMode(int);
    void SetControllerMode(int);
    char GetControllerMode();
    void OpenMenu(int, int, int);
    void SetPauseMode(int);
    void GetPauseMode();
    unsigned char GetItemUse(int);
    void GetSPModeFlg(int);
    void ClrSPModeFlg(int);
    unsigned int GetSPMode(int);
    unsigned int GetMemorysFlg(int);
    void ClrMemorysFlg(int);
    unsigned char GetMemorys(int);
    unsigned int GetCmdNumFlg(int);
    void ClrCmdNumFlg(int);
    unsigned char GetCmdNum(int);
    unsigned int GetPlayModeFlg(int);
    void ClrPlayModeFlg(int);
    void SetStartBonusFlg();
    unsigned int GetStartBonusFlg(int);
    void ClrStartBonusFlg(int);

private:
    char cmakeInfo[4][0x20];
    OSSemaphore accessSemaphores[4];
};

extern GbaQueue GbaQue;

#endif // _FFCC_GBAQUEUE_H_
