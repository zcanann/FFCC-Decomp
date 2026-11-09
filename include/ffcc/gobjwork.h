#ifndef _FFCC_GOBJWORK_H_
#define _FFCC_GOBJWORK_H_

#include "global.h"
#include "dolphin/mtx.h"

struct CMonAiAction
{
    unsigned short m_flags;
    unsigned short m_minDist;
    unsigned short m_maxDist;
    unsigned short m_chance;
    unsigned short m_type;
    unsigned short m_group;
    unsigned short m_range;
    unsigned short m_changeStat;
};

STATIC_ASSERT(sizeof(CMonAiAction) == 0x10);

struct CRomData
{
    unsigned short m_unk000[0x4E];
    unsigned short m_monsterParams0[4];      // 0x09C
    unsigned short m_monsterParams1[14];     // 0x0A4
    unsigned short m_unk0C0[4];
    unsigned short m_colRange;               // 0x0C8
    unsigned short m_viewAngle;              // 0x0CA
    unsigned short m_territoryRange;         // 0x0CC
    unsigned short m_attackRange;            // 0x0CE
    unsigned short m_unk0D0[2];
    unsigned short m_moveSpeed;              // 0x0D4
    unsigned short m_approachRange;          // 0x0D6
    unsigned short m_unk0D8[3];
    unsigned short m_elementResistances[11]; // 0x0DE
    unsigned short m_shoukiDamageInterval;   // 0x0F4
    unsigned short m_unk0F6[3];
    unsigned short m_kind;                   // 0x0FC
    unsigned short m_flags;                  // 0x0FE
    unsigned short m_aiRomBase;              // 0x100
    unsigned short m_aiFlags;                // 0x102
    unsigned short m_alertMode;              // 0x104
    unsigned short m_targetMode;             // 0x106
    unsigned short m_actionSelect;           // 0x108
    unsigned short m_actionKind;             // 0x10A
    unsigned short m_aiType;                 // 0x10C
    unsigned short m_unk10E;
    CMonAiAction m_actions[8];               // 0x110
    unsigned short m_seBank;                 // 0x190
    unsigned short m_seBase;                 // 0x192
    unsigned short m_magicCastBonus;         // 0x194
    unsigned short m_chargeCastBonus;        // 0x196
    unsigned short m_power;                  // 0x198
    unsigned short m_combatParam0;           // 0x19A
    unsigned short m_combatParam1;           // 0x19C
    unsigned short m_dieParticle;            // 0x19E
    unsigned short m_animPoint0;             // 0x1A0
    unsigned short m_animPoint1;             // 0x1A2
    unsigned short m_hitParticle;            // 0x1A4
    unsigned short m_hitSe;                  // 0x1A6
    unsigned short m_repopParticleCount;     // 0x1A8
    unsigned short m_iceParticleCount;       // 0x1AA
    unsigned short m_undeadWeaponCount;      // 0x1AC
    unsigned short m_undeadParticleCount;    // 0x1AE
    unsigned short m_turnFactor;             // 0x1B0
    unsigned short m_hitMask;                // 0x1B2
    unsigned short m_scale;                  // 0x1B4
    unsigned short m_moveLimitFrame;         // 0x1B6
    unsigned short m_escapeFrame;            // 0x1B8
    unsigned short m_chaseFrame;             // 0x1BA
    unsigned short m_attackMoveFrame;        // 0x1BC
    unsigned short m_stepSe;                 // 0x1BE
};

STATIC_ASSERT(sizeof(CRomData) == 0x1C0);
STATIC_ASSERT(offsetof(CRomData, m_monsterParams0) == 0x9C);
STATIC_ASSERT(offsetof(CRomData, m_colRange) == 0xC8);
STATIC_ASSERT(offsetof(CRomData, m_elementResistances) == 0xDE);
STATIC_ASSERT(offsetof(CRomData, m_kind) == 0xFC);
STATIC_ASSERT(offsetof(CRomData, m_actions) == 0x110);
STATIC_ASSERT(offsetof(CRomData, m_seBank) == 0x190);
STATIC_ASSERT(offsetof(CRomData, m_stepSe) == 0x1BE);

struct CRomWork
{
    unsigned short m_id;
    unsigned short m_param1;
    unsigned short m_param2;
    unsigned short m_maxHp;
    unsigned short m_strength;
    unsigned short m_magic;
    unsigned short m_defense;
    unsigned short m_reserved0E;
    CRomData m_data;
};

STATIC_ASSERT(sizeof(CRomWork) == 0x1D0);
STATIC_ASSERT(offsetof(CRomWork, m_data) == 0x10);

struct CRomLetterWork
{
    unsigned short Word(int index) const { return reinterpret_cast<const unsigned short*>(this)[index]; }

    unsigned short m_from;
    unsigned short m_subject;
    unsigned short m_message;
    unsigned short m_priorityFlags;
    unsigned char m_pad08[0x18 - 0x08];
    unsigned short m_personalConditions;
    unsigned short m_linkConditions;
    unsigned short m_linkValueConditions;

    struct CompareRule
    {
        unsigned short m_rule;
        unsigned short m_value;
    };

    CompareRule m_compareRules[4];
    unsigned short m_eventRules[8];
};

class CGObjWork
{
public:
    enum
    {
        RomStatusBlockHalfwordCount = 11,
    };

    CGObjWork()
    {
        m_objType = -1;
        m_saveSlot = -1;
        m_ownerObj = 0;
    }
    virtual ~CGObjWork();

    virtual void Init(int, CRomWork*, int);
    void CalcStatus();

    // void* vtable;                        // 0x0000
    int m_objType;                          // 0x0004
    int m_saveSlot;                         // 0x0008
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
    CRomData* m_romWork;                    // 0x0024
    unsigned short* RomStatusBlock() { return m_elementResistances; }
    unsigned short m_elementResistances[RomStatusBlockHalfwordCount]; // 0x0028
    unsigned short m_statusTimers[39];      // 0x003E
    unsigned short m_statusValues[16];      // 0x008C-0xAB
}; // Size: 0xAC

STATIC_ASSERT(sizeof(CGObjWork) == 0xAC);
STATIC_ASSERT(offsetof(CGObjWork, m_elementResistances) == 0x28);
STATIC_ASSERT(offsetof(CGObjWork, m_statusTimers) == 0x3E);
STATIC_ASSERT(offsetof(CGObjWork, m_statusValues) == 0x8C);

class CMonWork : public CGObjWork
{
public:
    CMonWork();
    virtual ~CMonWork();

    virtual void Init(int, CRomWork*, int);
    void CalcStatus();
    
    unsigned short unk_0xac[4];  // 0x00AC
    unsigned short unk_0xb4[14]; // 0x00B4
    unsigned short m_actionItems[16]; // 0x00D0
    unsigned short m_actionAnimations[16]; // 0x00F0
}; // Size 0x110

STATIC_ASSERT(sizeof(CMonWork) == 0x110);
STATIC_ASSERT(offsetof(CMonWork, m_actionItems) == 0xD0);
STATIC_ASSERT(offsetof(CMonWork, m_actionAnimations) == 0xF0);

class CCaravanWork : public CGObjWork
{
public:
    class CLetterWork
    {
    public:
        unsigned int m_opened : 1;
        unsigned int m_attachmentClaimed : 1;
        unsigned int m_replySent : 1;
        unsigned int m_hasReply : 1;
        unsigned int m_attachmentIsGil : 1;
        unsigned int m_messageType : 9;
        unsigned int m_senderId : 9;
        unsigned int m_attachValue : 9;
        unsigned short m_tempVars[4];
    };

    CCaravanWork();
    virtual ~CCaravanWork();
    
    void clearCaravanWork();
    void LoadInit();
    void ClearEvtWork();
    void LoadFinished();
    virtual void Init(int, CRomWork*, int);
    void SetBonusCondition(int);
    int IsOutOfShouki();
    void AddLetter(int, int, int, int, int, int, int, int, int);
    void FGLetterOpen(int);
    void FGLetterReply(int, int, int, int);
    void FGUseItem(int, int);
    void FGPutItem(int, int);
    void FGPutGil(int);
    void ChgCmdLst(int, int);
    void ChgEquipPos(int, int);
    int CanAddComList(int);
    int AddComList(int, int*);
    void DeleteCmdList(int, int);
    int AddItem(int, int*);
    void SetArtifact(int, int);
    void FGAddItemIdx(int, int);
    int CanAddTmpArtifact(int);
    int FindItem(int);
    void DeleteItemIdx(int, int);
    int DeleteItem(int, int);
    int AddTmpArtifact(int, int*);
    int CanAddGil(int);
    int AddGil(int);
    const int& GetGil() { return m_gil; }
    int GetFoodRank(int);
    void SearchRomLetterWork(CRomLetterWork**, int);
    int ShopRequest(int, int, int, int, int, int, int);
    void CallShop(int, int, int, int, int);
    void CalcArtifactStatus(int, int, int&, int&, int&, int&, int&);
    void SafeDeleteTempItem();
    void ClampStatus(short&, unsigned short&);
    void CalcStatus();
    int CanPlayerUseItem();
    int IsUseItem() { return 1; }
    int CanAddItem(int count) { return m_inventoryItemCount + count <= 0x40; }
    int GetTotalBonus()
    {
        int bonus = m_artifactRelated[3] + m_artifactRelated[4];
        int total;
        if (bonus < 0) {
            total = 0;
        } else {
            total = 100;
            if (bonus <= 100) {
                total = bonus;
            }
        }
        return total;
    }
    int GetTotalBonus2()
    {
        int bonus = m_artifactRelated[0] + m_artifactRelated[1] - m_artifactRelated[2];
        return bonus;
    }
    void ValidCmdList(int);
    int GetIdxCmdList();
    int GetNumCmdList() { return m_numCmdListSlots; }
    void SetIdxCmdList(int);
    int IsUseCmdList(int);
    unsigned int IsSelectedCmdList(int);
    int GetMagicCharge(int, int&, int&);
    const char* GetCmdListItemName(int);
    int GetWeaponAttrib(int);
    int GetCmdListItem(int);
    int SearchCombiTop(int);
    void DelCmdListAndItem(int, int);
    int GetNumCombi(int);
    int GetNextCmdListIdx(int, int);
    int GetCurCmdListItem()
    {
        int idx = GetIdxCmdList();
        return GetCmdListItem(idx);
    }
    void StepIdxCmdList(int dir)
    {
        int idx = GetNextCmdListIdx(GetIdxCmdList(), dir);
        SetIdxCmdList(idx);
    }
    int CanPlayerPutItem();
    void GetCurrentWeaponItem(int&, int&);
    void SetCurrentWeaponIdx(int);
    void CheckAndResetCurrentWeaponIdx(int);
    void SortBeforeReturnWorldMap();
    void BackupTutorialItem(int);
    void UniteComList(int, int, int);
    void UnuniteComList(int, int);
    void SetEvtWord(int evtWordIndex, short evtWord) { m_evtWordArr[evtWordIndex] = evtWord; }
    int GetEvtWord(int evtWordIndex) { return m_evtWordArr[evtWordIndex]; }
    void SetEvtFlag(int, int);
    int GetEvtFlag(int);
    int GetArtifactIncludeHpMax();

    short m_equipment[4];                       // 0x00AC weapon[0], armor[1], tribal[2], accessory[3]
    unsigned short m_inventoryItemCount;        // 0x00B4
    enum { kInventoryCapacity = 64, kPermanentArtifactCount = 96, kTemporaryArtifactCount = 4,
           kArtifactCount = kPermanentArtifactCount + kTemporaryArtifactCount,
           kPermanentArtifactStart = kInventoryCapacity,
           kTemporaryArtifactStart = kPermanentArtifactStart + kPermanentArtifactCount,
           kItemSlotCount = kInventoryCapacity + kArtifactCount };
    short m_inventoryItems[kItemSlotCount];     // 0x00B6: inventory, permanent artifacts, temporary artifacts
    unsigned char m_treasureFlags;              // 0x01FE
    unsigned char m_moneyFlags;                 // 0x01FF
    int m_gil;                                  // 0x0200
    short m_commandListInventorySlotRef[8];     // 0x0204
    short m_commandListExtra[8];                // 0x0214
    short m_currentCmdListIndex;                // 0x0224
    short m_weaponIdx;                          // 0x0226
    short m_backupEquipment[4];                 // 0x0228
    unsigned short m_backupInventoryItemCount;  // 0x0230
    short m_backupItems[kItemSlotCount];        // 0x0232
    unsigned char m_backupTreasureFlags;        // 0x037A
    unsigned char m_backupMoneyFlags;           // 0x037B
    int m_backupGil;                            // 0x037C
    short m_backupCommandListInventorySlotRef[8]; // 0x0380
    short m_backupCmdlistExtra[8];              // 0x0390
    short m_backupCurrentCmdListIndex;          // 0x03A0
    short m_backupWeaponIdx;                    // 0x03A2
    int m_shopState;                            // 0x03A4
    int unk_0x3a8;                              // 0x03A8
    int m_jobType;                              // 0x03AC
    unsigned int m_equipEffectFlags;            // 0x03B0
    int m_joybusCaravanId;                      // 0x03B4
    unsigned short m_letterMeta[8];             // 0x03B8
    unsigned short unk_0x3c8;                   // 0x03C8
    char m_name[18];                            // 0x03CA
    unsigned short unk_0x3dc;                   // 0x03DC
    unsigned short m_progressValue;             // 0x03DE
    unsigned short m_tribeId;                   // 0x03E0
    unsigned short m_genderFlag;                // 0x03E2
    unsigned short m_appearanceVariant;         // 0x03E4
    unsigned short unk_0x3e6;                   // 0x03E6
    int m_letterCount;                          // 0x03E8
    CLetterWork m_letters[100];                 // 0x03EC
    unsigned int m_evtState0;                   // 0x089C
    unsigned int m_evtState1;                   // 0x08A0
    unsigned char m_evtFlags[256];           // 0x08A4
    short m_evtWordArr[256];                    // 0x09A4
    unsigned char m_bonusCondition;             // 0x0BA4
    unsigned char m_shopBusyFlag;               // 0x0BA5
    unsigned char m_caravanLocalFlags;          // 0x0BA6
    unsigned char m_cmdListFlags;               // 0x0BA7
    short m_baseCmdListSlots;                   // 0x0BA8
    short m_numCmdListSlots;                    // 0x0BAA
    Vec m_targetCursorPosA;                     // 0x0BAC
    Vec m_targetCursorPosB;                     // 0x0BB8
    unsigned short m_artifactRelated[5];        // 0x0BC4
    unsigned char m_tempBuffFlags;              // 0x0BCE
    unsigned char m_tempBuffIndex;              // 0x0BCF
    int m_tempStatBuffTimer;                    // 0x0BD0
    int m_tempStatBuffId;                       // 0x0BD4
    char m_equipEffectParams[8];                // 0x0BD8
    signed char m_shopRequestState;             // 0x0BE0
    unsigned char m_shopRequestFlags;           // 0x0BE1
    short m_shopParam;                          // 0x0BE2
    short m_shopListCount;                      // 0x0BE4
    short m_shopList[16];                       // 0x0BE6
    unsigned char m_shopExtraState;             // 0x0C06
    unsigned char m_shopExtraFlags;             // 0x0C07
    int m_shopArgs[4];                         // 0x0C08
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

/*
 * --INFO--
 * PAL Address: 0x800B9264
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CCaravanWork::SetEvtFlag(int evtFlagIndex, int value)
{
    if (value != 0) {
        int byteIndex = evtFlagIndex / 8;
        int bit = 1 << (evtFlagIndex % 8);
        m_evtFlags[byteIndex] |= bit;
        return;
    }

    {
        int byteIndex = evtFlagIndex / 8;
        int bit = 1 << (evtFlagIndex % 8);
        m_evtFlags[byteIndex] &= ~bit;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800B92DC
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CCaravanWork::GetEvtFlag(int evtFlagIndex)
{
    int byteIndex = evtFlagIndex / 8;
    unsigned char value = m_evtFlags[byteIndex];
    int mask = 1 << (evtFlagIndex % 8);
    unsigned int flag = value & mask;

    if (flag != 0) {
        return 1;
    }
    return 0;
}

STATIC_ASSERT(sizeof(CCaravanWork) == 0xC30);
STATIC_ASSERT(offsetof(CCaravanWork, m_inventoryItems) == 0xB6);
STATIC_ASSERT(offsetof(CCaravanWork, m_inventoryItems) + CCaravanWork::kPermanentArtifactStart * sizeof(short) == 0x136);
STATIC_ASSERT(offsetof(CCaravanWork, m_inventoryItems) + CCaravanWork::kTemporaryArtifactStart * sizeof(short) == 0x1F6);
STATIC_ASSERT(offsetof(CCaravanWork, m_backupItems) == 0x232);
STATIC_ASSERT(sizeof(((CCaravanWork*)0)->m_inventoryItems) == 328);
STATIC_ASSERT(offsetof(CCaravanWork, m_evtFlags) == 0x8A4);
STATIC_ASSERT(offsetof(CCaravanWork, m_evtWordArr) == 0x9A4);
STATIC_ASSERT(offsetof(CCaravanWork, m_treasureFlags) == 0x1FE);
STATIC_ASSERT(sizeof(CCaravanWork::CLetterWork) == 0x0C);
STATIC_ASSERT(sizeof(CRomLetterWork) == 0x3E);
STATIC_ASSERT(offsetof(CCaravanWork, m_targetCursorPosA) == 0x0BAC);
STATIC_ASSERT(offsetof(CCaravanWork, m_targetCursorPosB) == 0x0BB8);

inline CGObjWork* SAFE_CAST_WORK(CGObjWork* work)
{
    return work;
}

inline CMonWork* SAFE_CAST_MON_WORK(CGObjWork* work)
{
    return static_cast<CMonWork*>(work);
}

inline CCaravanWork* SAFE_CAST_CARAVAN_WORK(CGObjWork* work)
{
    return static_cast<CCaravanWork*>(work);
}

#endif // _FFCC_GOBJWORK_H_
