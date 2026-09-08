#ifndef MEMORYCARD_H
#define MEMORYCARD_H

#include <Dolphin/types.h>
#include <Dolphin/card.h>
#include "ffcc/manager.h"
#include "ffcc/memory.h"

namespace Mc
{
struct CharaDat
{
    unsigned char m_unknown000[0x5B4];
    int m_exists;                                  // 0x5B4
    unsigned char m_unknown5B8[0x8C0 - 0x5B8];
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
    unsigned char m_unknown0020[0xC0 - 0x20];
    unsigned char m_linkTable[8][8][8][8];           // 0xC0
    unsigned char m_unknown10C0[0x13D0 - 0x10C0];
    u64 m_mcSerial;                                // 0x13D0
    u32 m_mcRandom;                                // 0x13D8
    unsigned char m_unknown13DC[0x14D0 - 0x13DC];
    CharaDat m_characters[8];                       // 0x14D0
    unsigned char m_unknown62D0[0x8BD0 - 0x62D0];
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
