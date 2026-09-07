#ifndef _FFCC_GOBJWORK_H_
#define _FFCC_GOBJWORK_H_

#include "global.h"
#include "dolphin/mtx.h"

struct CRomWork
{
    enum
    {
        DataHalfwordCount = (0x1D0 - 0x10) / sizeof(unsigned short),
        ElementResistanceOffset = 0x6F,
        MonsterParams0Offset = 0x4E,
        MonsterParams1Offset = 0x52,
    };

    unsigned short m_id;
    unsigned short m_param1;
    unsigned short m_param2;
    unsigned short m_maxHp;
    unsigned short m_strength;
    unsigned short m_magic;
    unsigned short m_defense;
    unsigned short m_reserved0E;
    unsigned short m_data[DataHalfwordCount];

    unsigned short* Data() { return m_data; }
    const unsigned short* Data() const { return m_data; }
    unsigned short* ElementResistances() { return m_data + ElementResistanceOffset; }
    const unsigned short* ElementResistances() const { return m_data + ElementResistanceOffset; }
    unsigned short* MonsterParams0() { return m_data + MonsterParams0Offset; }
    unsigned short* MonsterParams1() { return m_data + MonsterParams1Offset; }
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
    unsigned short* m_romWork;              // 0x0024
    unsigned short* RomStatusBlock() { return m_elementResistances; }
    unsigned short m_elementResistances[8]; // 0x0028 physical, fire, freeze, stun, slow, stop, gravity, holy
    unsigned short m_statusTimers[42];      // 0x0038
    unsigned short m_statusValues[16];      // 0x008C-0xAB
}; // Size: 0xAC

STATIC_ASSERT(sizeof(CGObjWork) == 0xAC);
STATIC_ASSERT(offsetof(CGObjWork, m_statusTimers) == 0x38);

class CMonWork : public CGObjWork
{
public:
    CMonWork();
    virtual ~CMonWork();

    virtual void Init(int, CRomWork*, int);
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
        struct Halfwords {
            unsigned short m_header;
            unsigned short m_attachment;
            unsigned short m_tempVars[4];
        };
        struct Words {
            unsigned int m_word0;
            unsigned int m_word1;
            unsigned int m_word2;
        };
        struct WordPair {
            unsigned int m_word1;
            unsigned int m_word2;
        };
        struct SplitWords {
            unsigned int m_word0;
            WordPair m_pair;
        };
        struct FlagBits {
            unsigned char m_opened : 1;
            unsigned char m_attachmentClaimed : 1;
            unsigned char m_replySent : 1;
            unsigned char m_hasReply : 1;
            unsigned char m_attachmentIsGil : 1;
            unsigned char m_rest : 3;
        };
        struct HeaderBits {
            unsigned short m_opened : 1;
            unsigned short m_attachmentClaimed : 1;
            unsigned short m_replySent : 1;
            unsigned short m_hasReply : 1;
            unsigned short m_attachmentIsGil : 1;
            unsigned short m_messageType : 9;
            unsigned short m_pad : 2;
        };
        struct AttachmentBits {
            unsigned short m_pad : 7;
            unsigned short m_value : 9;
        };
        struct WordBits {
            unsigned int m_pad : 14;
            unsigned int m_senderId : 9;
            unsigned int m_attachValue : 9;
        };

        unsigned int Word0() const { return m_words.m_word0; }
        void SetWord0(unsigned int word)
        {
            m_words.m_word0 = word;
        }
        unsigned int Word1() const { return m_words.m_word1; }
        void SetWord1(unsigned int word) { m_words.m_word1 = word; }
        unsigned int Word2() const { return m_words.m_word2; }
        void SetWord2(unsigned int word) { m_words.m_word2 = word; }
        unsigned char Flags() const { return reinterpret_cast<const unsigned char*>(&m_half.m_header)[0]; }
        const FlagBits& FlagsBits() const { return *reinterpret_cast<const FlagBits*>(&m_half.m_header); }
        FlagBits& FlagsBits() { return *reinterpret_cast<FlagBits*>(&m_half.m_header); }
        void SetFlags(unsigned char flags)
        {
            reinterpret_cast<unsigned char*>(&m_half.m_header)[0] = flags;
        }
        bool IsOpened() const { return FlagsBits().m_opened != 0; }
        void SetOpened()
        {
            FlagsBits().m_opened = 1;
        }
        bool IsAttachmentClaimed() const { return FlagsBits().m_attachmentClaimed != 0; }
        void SetAttachmentClaimed() { FlagsBits().m_attachmentClaimed = 1; }
        bool IsReplySent() const { return FlagsBits().m_replySent != 0; }
        void SetReplySent()
        {
            FlagsBits().m_replySent = 1;
        }
        bool HasReply() const { return FlagsBits().m_hasReply != 0; }
        bool AttachmentIsGil() const { return FlagsBits().m_attachmentIsGil != 0; }
        unsigned short HeaderWord() const { return m_half.m_header; }
        HeaderBits& HeaderBitsRef() { return *reinterpret_cast<HeaderBits*>(&m_half.m_header); }
        void SetMessageType(unsigned short type) { HeaderBitsRef().m_messageType = type; }
        unsigned short MessageType() const { return (HeaderWord() >> 2) & 0x1FF; }
        unsigned int SenderId() const { return (Word0() >> 9) & 0x1FF; }
        unsigned short AttachmentWord() const { return m_half.m_attachment; }
        unsigned int AttachmentValue() const { return AttachmentWord() & 0x1FF; }
        AttachmentBits& AttachmentBitsRef() { return *reinterpret_cast<AttachmentBits*>(&m_half.m_attachment); }
        WordBits& WordBitsRef() { return *reinterpret_cast<WordBits*>(&m_words.m_word0); }
        void SetAttachmentValue(unsigned short value) { AttachmentBitsRef().m_value = value; }
        unsigned short TempVar(int index) const { return m_half.m_tempVars[index]; }

        union {
            Halfwords m_half;
            Words m_words;
            SplitWords m_split;
        };
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
    int GetFoodRank(int);
    void SearchRomLetterWork(CRomLetterWork**, int);
    int ShopRequest(int, int, int, int, int, int, int);
    void CallShop(int, int, int, int, int);
    void SafeDeleteTempItem();
    void CalcStatus();
    int CanPlayerUseItem();
    void ValidCmdList(int);
    int GetIdxCmdList();
    void SetIdxCmdList(int);
    int IsUseCmdList(int);
    unsigned int IsSelectedCmdList(int);
    int GetMagicCharge(int, int&, int&);
    const char* GetCmdListItemName(int);
    int GetWeaponAttrib(int);
    int GetCmdListItem(int);
    void SearchCombiTop(int);
    void DelCmdListAndItem(int, int);
    int GetNumCombi(int);
    int GetNextCmdListIdx(int, int);
    int CanPlayerPutItem();
    void GetCurrentWeaponItem(int&, int&);
    void SetCurrentWeaponIdx(int);
    void CheckAndResetCurrentWeaponIdx(int);
    void SortBeforeReturnWorldMap();
    void BackupTutorialItem(int);
    void UniteComList(int, int, int);
    void UnuniteComList(int, int);
    void SetEvtWord(int, short);
    int GetEvtWord(int);
    void SetEvtFlag(int, int);
    int GetEvtFlag(int);
    int GetArtifactIncludeHpMax();

    short m_equipment[4];                       // 0x00AC weapon[0], armor[1], tribal[2], accessory[3]
    unsigned short m_inventoryItemCount;        // 0x00B4
    short m_inventoryItems[64];                 // 0x00B6
    enum { kPermanentArtifactCount = 96, kTemporaryArtifactCount = 4,
           kArtifactCount = kPermanentArtifactCount + kTemporaryArtifactCount };
    short m_artifacts[kArtifactCount];          // 0x0136, temporary artifacts start at 0x01F6
    unsigned char m_treasureFlags;              // 0x01FE
    unsigned char m_moneyFlags;                 // 0x01FF
    int m_gil;                                  // 0x0200
    short m_commandListInventorySlotRef[8];     // 0x0204
    short m_commandListExtra[8];                // 0x0214
    short m_currentCmdListIndex;                // 0x0224
    short m_weaponIdx;                          // 0x0226
    short m_backupEquipment[4];                 // 0x0228
    unsigned short m_backupInventoryItemCount;  // 0x0230
    unsigned char m_backupInventoryBlock[328];  // 0x0232
    unsigned char m_backupTreasureFlags;        // 0x037A
    unsigned char m_backupMoneyFlags;           // 0x037B
    int m_backupGil;                            // 0x037C
    short m_backupCommandListInventorySlotRef[8]; // 0x0380
    short m_backupCmdlistExtra[8];              // 0x0390
    short m_backupCurrentCmdListIndex;          // 0x03A0
    short m_backupWeaponIdx;                    // 0x03A2
    int m_shopState;                            // 0x03A4
    int unk_0x3a8;                              // 0x03A8
    int unk_0x3ac;                              // 0x03AC
    unsigned int m_equipEffectFlags;            // 0x03B0
    int m_joybusCaravanId;                      // 0x03B4
    unsigned short m_letterMeta[8];             // 0x03B8
    unsigned short unk_0x3c8;                   // 0x03C8
    unsigned char m_name[18];                   // 0x03CA
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
    unsigned short m_evtWorkArr[128];           // 0x08A4
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

STATIC_ASSERT(sizeof(CCaravanWork) == 0xC30);
STATIC_ASSERT(offsetof(CCaravanWork, m_artifacts) == 0x136);
STATIC_ASSERT(offsetof(CCaravanWork, m_artifacts) + CCaravanWork::kPermanentArtifactCount * sizeof(short) == 0x1F6);
STATIC_ASSERT(offsetof(CCaravanWork, m_treasureFlags) == 0x1FE);
STATIC_ASSERT(sizeof(CCaravanWork::CLetterWork) == 0x0C);
STATIC_ASSERT(sizeof(CRomLetterWork) == 0x3E);
STATIC_ASSERT(offsetof(CCaravanWork, m_targetCursorPosA) == 0x0BAC);
STATIC_ASSERT(offsetof(CCaravanWork, m_targetCursorPosB) == 0x0BB8);

CMonWork* SAFE_CAST_MON_WORK(CGObjWork*);
CCaravanWork* SAFE_CAST_CARAVAN_WORK(CGObjWork*);

#endif // _FFCC_GOBJWORK_H_
