#ifndef MEMORYCARD_H
#define MEMORYCARD_H

#include <Dolphin/types.h>
#include <Dolphin/card.h>

class CStage;

namespace Mc
{
    struct SaveDat;
}

class CMemoryCardMan
{
public:
    CMemoryCardMan();

    void Init();
    void Quit();

    void DebugReadWrite(int, char*, void*, int);

    void AsyncFinished();
    void GetResult();

    void McMount(int);
    void McUnmount(int);
    void McOpen(int);
    void McClose();
    void McCreate(int);
    void McGetStat(int);
    void McSetStat(int);
    void CreateMcBuff();
    void DestroyMcBuff();
    void McEnd();
    void SetMcIconImage();

    void McRead(char*, int, int);
    void McWrite(char*, int, int);
    void McFormat(int);
    void McCheck(int);
    void McFreeBlocks(int, int*, int*);
    void McDelFile(int);

    void IsBrokenFile();

    void MakeSaveData();
    void SetLoadData();
    void CalcCrc(Mc::SaveDat*);
    void ChkCrc(Mc::SaveDat*);

    void DummySave();
    void DummyLoad();

    void CnvPlayTime(unsigned int, int*, int*);
    void McChkConnect(int);
    void Crc32(int, unsigned char*, unsigned int*);
    void EncodeData();
    void DecodeData();

    void CalcSaveDatHpMax(Mc::SaveDat*);
    void Odekake(int, Mc::SaveDat&, int, Mc::SaveDat&, int);

    void rotlwi(int, int);
    void rotrwi(int, int);

    // void* vtable;                 // 0x00
    int mResult;                  // 0x04
    char mOpDoneFlag;             // 0x08
    char mPadding1[3];            // 0x09
    CStage* mStage;               // 0x0C
    void* mMountWorkArea;         // 0x10
    u8* mSaveBuffer;              // 0x14
    CARDFileInfo mFileInfo;       // 0x18 (size 0x12)
    char mPadding2[2];            // 0x2A
    CARDStat mCardStat;           // 0x2C (size 0x6C)
    u8 mState;                    // 0x98
    u8 mCurrentSlot;              // 0x99
    char mPadding3[2];            // 0x9A
};

// Free Functions
void Detach(long, long);
void Attach(long, long);

#endif // MEMORYCARD_H
