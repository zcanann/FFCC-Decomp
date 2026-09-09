#ifndef MEMORYCARD_H
#define MEMORYCARD_H

#include <Dolphin/types.h>
#include <Dolphin/card.h>
#include "ffcc/manager.h"
#include "ffcc/gobjwork.h"
#include "ffcc/memory.h"

namespace Mc
{
struct CharaDat
{
    u16 m_id;                                      // 0x00
    u16 m_param1;                                  // 0x02
    u16 m_param2;                                  // 0x04
    u16 m_maxHp;                                   // 0x06
    u16 m_hp;                                      // 0x08
    u16 m_strength;                                // 0x0A
    u16 m_magic;                                   // 0x0C
    u16 m_defense;                                 // 0x0E
    u16 m_unknown010;                              // 0x10
    u16 m_letterMeta[8];                           // 0x12
    u16 m_unknown022;                              // 0x22
    u16 m_unknown024;                              // 0x24
    u16 m_unknown026;                              // 0x26
    u16 m_inventoryItemCount;                      // 0x28
    u16 m_unknown02A;                              // 0x2A
    u16 m_progressValue;                           // 0x2C
    u16 m_tribeId;                                 // 0x2E
    u16 m_genderFlag;                              // 0x30
    u16 m_appearanceVariant;                       // 0x32
    s16 m_equipment[4];                            // 0x34
    s16 m_inventoryItems[64];                      // 0x3C
    u32 m_artifactFlags[3];                        // 0xBC
    s16 m_commandListInventorySlotRef[8];          // 0xC8
    s16 m_commandListExtra[8];                     // 0xD8
    int m_joybusCaravanId;                         // 0xE8
    int m_gil;                                     // 0xEC
    char m_name[16];                               // 0xF0
    int m_letterCount;                             // 0x100
    CCaravanWork::CLetterWork m_letters[100];        // 0x104
    int m_exists;                                  // 0x5B4
    u8 m_evtFlags[256];                            // 0x5B8
    s16 m_evtWordArr[256];                         // 0x6B8
    int m_unknown8B8;                              // 0x8B8
    int m_jobType;                              // 0x8BC
    unsigned char m_isAway;                         // 0x8C0
    unsigned char m_isGuest;                        // 0x8C1
    unsigned char m_hasCharacterId;                 // 0x8C2
    unsigned char m_unknown8C3;
    u32 m_characterId;                              // 0x8C4
    u64 m_originSerial;                             // 0x8C8
    u32 m_originRandom;                             // 0x8D0
    int m_baseDataIndex;                            // 0x8D4
    unsigned char m_unknown8D8[0x9C0 - 0x8D8];
};

class SaveDat
{
public:
    char m_maker[4];
    char m_title[4];
    char m_machine[4];
    char m_version[4];
    char m_region;
    unsigned char m_rotateKey;
    unsigned char m_flags;
    unsigned char m_pad_13[0x18 - 0x13];
    u32 m_random;
    u32 m_crc;
    u32 m_scriptSysVal0;                           // 0x20
    int m_timerA;                                 // 0x24
    int m_scriptGlobalTime;                        // 0x28
    int m_frameCounter;                            // 0x2C
    int m_partySlots[4];                           // 0x30
    int m_bossArtifactStageTable[15];               // 0x40
    int m_unkStageTable[15];                        // 0x7C
    int m_chaliceElement;                          // 0xB8
    unsigned char m_unknown00BC[4];
    unsigned char m_linkTable[8][8][8][8];           // 0xC0
    char m_townName[16];                           // 0x10C0
    signed char m_eventFlags[256];                  // 0x10D0
    short m_eventWork[256];                        // 0x11D0
    u64 m_mcSerial;                                // 0x13D0
    u32 m_mcRandom;                                // 0x13D8
    unsigned char m_mcHasSerial;                    // 0x13DC
    signed char m_bgmVolume;                        // 0x13DD
    signed char m_seVolume;                         // 0x13DE
    unsigned char m_stereoFlag;                     // 0x13DF
    signed char m_gameInitFlag;                   // 0x13E0
    signed char m_spModeFlags[4];                 // 0x13E1
    unsigned char m_unknown13E5[0x14D0 - 0x13E5];
    CharaDat m_characters[8];                       // 0x14D0
    char m_scriptData[0x800];                      // 0x62D0
    unsigned short m_furTexels[0x1000];             // 0x6AD0
    u64 m_saveTime;                                // 0x8AD0
    unsigned char m_unknown8AD8[0x8BD0 - 0x8AD8];
};
}

class CMemoryCardMan : public CManager
{
public:
    void Init();
    void Quit();

    void DebugReadWrite(int isWrite, char* filename, void* buffer, int length);

    bool AsyncFinished();
    int GetResult();

    void McMount(int chan);
    int McUnmount(int chan);
    int McOpen(int chan);
    int McClose();
    void McCreate(int chan);
    int McGetStat(int chan);
    int McSetStat(int chan);
    void CreateMcBuff();
    void DestroyMcBuff();
    void McEnd();
    void SetMcIconImage();

    void McRead(char* buffer, int length, int offset);
    void McWrite(char* buffer, int length, int offset);
    void McFormat(int chan);
    void McCheck(int chan);
	int McFreeBlocks(int chan, int* bytesFree, int* filesFree);
    void McDelFile(int chan);

    bool IsBrokenFile();

    void MakeSaveData();
    void SetLoadData();
    unsigned int CalcCrc(::Mc::SaveDat*);
    unsigned int ChkCrc(::Mc::SaveDat*);

    int DummySave();
    int DummyLoad();

    void CnvPlayTime(unsigned int frames, int* hours, int* minutes);
    int McChkConnect(int chan);
    void Crc32(int, unsigned char*, unsigned int*);
    void EncodeData();
    void DecodeData();

    void CalcSaveDatHpMax(::Mc::SaveDat*);
    void Odekake(int, ::Mc::SaveDat&, int, ::Mc::SaveDat&, int);

    // void* vtable;           // 0x00
    int m_result;              // 0x04
    char m_opDoneFlag;         // 0x08
    CMemory::CStage* m_stage;   // 0x0C
    void* m_mountWorkArea;     // 0x10
    char* m_saveBuffer;        // 0x14
    CARDFileInfo m_fileInfo;   // 0x18 (size 0x12)
    CARDStat m_cardStat;       // 0x2C (size 0x6C)
    unsigned char m_state;     // 0x98
    char m_currentSlot;        // 0x99
};

extern CMemoryCardMan MemoryCardMan;

// Free Functions
void Detach(long, long);
void Attach(long, long);

#endif // MEMORYCARD_H
