#ifndef _FFCC_GOBJWORK_H_
#define _FFCC_GOBJWORK_H_

#include "global.h"

class CRomWork;
class CRomLetterWork;

class CGObjWork
{
public:
    CGObjWork();
    virtual ~CGObjWork();

    void Init(int, CRomWork*, int);
    void CalcStatus();

    // void* vtable;                        // 0x0000
    int m_objType;                          // 0x0004
    unsigned char m_saveSlot;               // 0x0008
    unsigned char m_partyIndex;             // 0x0009
    unsigned char m_isLoadingFlag;          // 0x000A
    unsigned char m_miscFlags;              // 0x000B
    void* m_ownerObj;                       // 0x000C
    int m_baseDataIndex;                    // 0x0010
    unsigned short m_id;                    // 0x0014
    unsigned short m_param1;                // 0x0016
    unsigned short m_param2;                // 0x0018
    unsigned short m_maxHp;                 // 0x001A
    unsigned short m_hp;                    // 0x001C
    unsigned short m_strength;              // 0x001E
    unsigned short m_magic;                 // 0x0020
    unsigned short m_defense;               // 0x0022
    unsigned short* m_romWorkPtr;           // 0x0024
    unsigned short m_elementResistances[8]; // 0x0028 physical, fire, freeze, stun, slow, stop, gravity, holy
    unsigned short m_statusTimers[42];      // 0x0038
    unsigned short m_statusValues[16];      // 0x008C-0xAB
}; // Size: 0xAC

STATIC_ASSERT(sizeof(CGObjWork) == 0xAC);

class CMonWork : public CGObjWork
{
public:
    CMonWork();

    void Init(int, CRomWork*, int);
    void CalcStatus();
    
    unsigned short unk_0xac[4];  // 0x00AC
    unsigned short unk_0xb4[14]; // 0x00B4
    unsigned short unk_0xd0[16]; // 0x00D0
    unsigned short unk_0xf0[16]; // 0x00F0
}; // Size 0x110

STATIC_ASSERT(sizeof(CMonWork) == 0x110);

class CCaravanWork : public CGObjWork
{
public:
    class CLetterWork
    {
    public:
        void operator=(const CLetterWork&);
    };

    CCaravanWork();
    virtual ~CCaravanWork();
    
    void clearCaravanWork();
    void LoadInit();
    void ClearEvtWork();
    void LoadFinished();
    void Init(int, CRomWork*, int);
    void SetBonusCondition(int);
    void IsOutOfShouki();
    void AddLetter(int, int, int, int, int, int, int, int, int);
    void FGLetterOpen(int);
    void FGLetterReply(int, int, int, int);
    void FGUseItem(int, int);
    void FGPutItem(int, int);
    void FGPutGil(int);
    void ChgCmdLst(int, int);
    void ChgEquipPos(int, int);
    int CanAddComList(int);
    void AddComList(int, int*);
    void DeleteCmdList(int, int);
    void AddItem(int, int*);
    void SetArtifact(int, int);
    void FGAddItemIdx(int, int);
    void ChkNumItem(char*, int);
    void CanAddTmpArtifact(int);
    void FindItem(int);
    void DeleteItemIdx(int, int);
    void DeleteItem(int, int);
    void AddTmpArtifact(int, int*);
    void CanAddGil(int);
    void AddGil(int);
    void GetFoodRank(int);
    void SearchRomLetterWork(CRomLetterWork**, int);
    void ShopRequest(int, int, int, int, int, int, int);
    void CallShop(int, int, int, int, int);
    void SafeDeleteTempItem();
    void ClampStatus(short&, unsigned short&);
    void CalcArtifactStatus(int, int, int&, int&, int&, int&, int&);
    void CalcStatus();
    void CanPlayerUseItem();
    void ValidCmdList(int);
    void GetIdxCmdList();
    void SetIdxCmdList(int);
    void IsUseCmdList(int);
    void IsSelectedCmdList(int);
    void GetMagicCharge(int, int&, int&);
    void GetCmdListItemName(int);
    void GetWeaponAttrib(int);
    void GetCmdListItem(int);
    void DelCmdListAndItem(int, int);
    void SearchCombiTop(int);
    void GetNumCombi(int);
    void GetNextCmdListIdx(int, int);
    void CanPlayerPutItem();
    void GetCurrentWeaponItem(int&, int&);
    void SetCurrentWeaponIdx(int);
    void CheckAndResetCurrentWeaponIdx(int);
    void SortBeforeReturnWorldMap();
    void BackupTutorialItem(int);
    void UniteComList(int, int, int);
    void UnuniteComList(int, int);
    void GetEvtFlag(int);
    int GetArtifactIncludeHpMax();

    short m_equipment[4];                       // 0x00AC weapon[0], armor[1], tribal[2], accessory[3]
    short m_inventoryItemCount;                 // 0x00B4
    unsigned short m_inventoryItems[64];        // 0x00B6
    unsigned short m_artifacts[96];             // 0x0136
    unsigned short m_treasures[4];              // 0x01F6
    unsigned char m_treasureFlags;              // 0x01FE
    unsigned char m_moneyFlags;                 // 0x01FF
    int m_gil;                                  // 0x0200
    unsigned short m_commandListInventorySlotRef[8]; // 0x0204
    unsigned char m_commandListExtra[16];       // 0x0214
    unsigned short m_currentCmdListIndex;       // 0x0224
    short m_weaponIdx;                          // 0x0226
    short m_backupEquipment[4];                 // 0x0228
    short m_backupInventoryItemCount;           // 0x0230
    unsigned char m_backupInventoryBlock[328];  // 0x0232
    unsigned char m_backupTreasureFlags;        // 0x037A
    unsigned char m_backupMoneyFlags;           // 0x037B
    int m_backupGil;                            // 0x037C
    unsigned short m_backupCommandListInventorySlotRef[8]; // 0x0380
    unsigned char m_backupCmdlistExtra[16];     // 0x0390
    unsigned short m_backupCurrentCmdListIndex; // 0x03A0
    short m_backupWeaponIdx;                    // 0x03A2
    int m_shopState;                            // 0x03A4
    int unk_0x3a8;                              // 0x03A8
    int unk_0x3ac;                              // 0x03AC
    unsigned int m_equipEffectFlags;            // 0x03B0
    int m_joybusCaravanId;                      // 0x03B4
    unsigned short m_letterMeta[8];             // 0x03B8
    unsigned char unk_0x3c8;                    // 0x03C8
    unsigned char unk_0x3c9;                    // 0x03C9
    unsigned char unk_0x3ca_0x3dd[20];          // 0x03CA
    unsigned short m_progressValue;             // 0x03DE
    unsigned short m_tribeId;                   // 0x03E0
    unsigned short m_genderFlag;                // 0x03E2
    unsigned short m_appearanceVariant;         // 0x03E4
    unsigned short unk_0x3e6;                   // 0x03E6
    int m_letterCount;                          // 0x03E8
    unsigned char m_letter0[12];                // 0x03EC
    unsigned char m_letterSlots[1188];          // 0x03F8
    unsigned int m_evtState0;                   // 0x089C
    unsigned int m_evtState1;                   // 0x08A0
    unsigned short m_evtWorkArr[80];            // 0x08A4
    unsigned char m_evtWorkPadding[96];         // 0x0944
    short m_evtWordArr[256];                    // 0x09A4
    unsigned char m_bonusCondition;             // 0x0BA4
    unsigned char m_shopBusyFlag;               // 0x0BA5
    unsigned char m_caravanLocalFlags;          // 0x0BA6
    unsigned char m_cmdListFlags;               // 0x0BA7
    unsigned short m_baseCmdListSlots;          // 0x0BA8
    unsigned short m_numCmdListSlots;           // 0x0BAA
    int m_timedBuffCounter;                     // 0x0BAC
    int m_timedBuffItemId;                      // 0x0BB0
    char m_bonusFire;                           // 0x0BB4
    char m_bonusIce;                            // 0x0BB5
    char m_bonusThunder;                        // 0x0BB6
    char m_bonusHoly;                           // 0x0BB7
    char m_bonusStr;                            // 0x0BB8
    char m_bonusDef;                            // 0x0BB9
    char m_bonusMag;                            // 0x0BBA
    char m_bonusOther;                          // 0x0BBB
    unsigned char unk_0xbbc_0xbc4[8];           // 0x0BBC
    unsigned short m_artifactRelated[5];        // 0x0BC4
    unsigned char m_tempBuffFlags;              // 0x0BCE
    unsigned char m_tempBuffIndex;              // 0x0BCF
    int m_tempStatBuffTimer;                    // 0x0BD0
    int m_tempStatBuffId;                       // 0x0BD4
    char m_equipEffectParams[8];                // 0x0BD8
    unsigned char m_shopRequestState;           // 0x0BE0
    unsigned char m_shopRequestFlags;           // 0x0BE1
    short m_shopParam;                          // 0x0BE2
    short m_shopListCount;                      // 0x0BE4
    short m_shopList[16];                       // 0x0BE6
    unsigned char m_shopExtraState;             // 0x0C06
    unsigned char m_shopExtraFlags;             // 0x0C07
    int m_shopArg0;                             // 0x0C08
    int m_shopArg1;                             // 0x0C0C
    int m_shopArg2;                             // 0x0C10
    int m_shopArg3;                             // 0x0C14
    unsigned short m_baseStrength;              // 0x0C18
    unsigned short m_baseMagic;                 // 0x0C1A
    unsigned short m_baseDefense;               // 0x0C1C
    unsigned char unk_0xc1e;                    // 0x0C1E
    unsigned char unk_0xc1f;                    // 0x0C1F
    int m_shopRandSeed;                         // 0x0C20
    int m_shopData0;                            // 0x0C24
    int m_shopData1;                            // 0x0C28
    int m_shopData2;                            // 0x0C2C
}; // Size 0xC30

STATIC_ASSERT(sizeof(CCaravanWork) == 0xC30);

#endif // _FFCC_GOBJWORK_H_
