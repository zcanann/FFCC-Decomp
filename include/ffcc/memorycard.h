#ifndef MEMORYCARD_H
#define MEMORYCARD_H

#include <Dolphin/types.h>
#include <Dolphin/card.h>
#include "ffcc/manager.h"

class CStage;

namespace Mc
{
    struct SaveDat;
}

class CMemoryCardMan : public CManager
{
public:
    CMemoryCardMan();

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
    void CalcCrc(Mc::SaveDat*);
    void ChkCrc(Mc::SaveDat*);

    void DummySave();
    void DummyLoad();

    void CnvPlayTime(unsigned int frames, int* hours, int* minutes);
    int McChkConnect(int chan);
    void Crc32(int, unsigned char*, unsigned int*);
    void EncodeData();
    void DecodeData();

    void CalcSaveDatHpMax(Mc::SaveDat*);
    void Odekake(int, Mc::SaveDat&, int, Mc::SaveDat&, int);

    void rotlwi(int, int);
    void rotrwi(int, int);

    // void* vtable;              // 0x00
    int mResult;                  // 0x04
    char mOpDoneFlag;             // 0x08
    CStage* mStage;               // 0x0C
    void* mMountWorkArea;         // 0x10
    char* mSaveBuffer;            // 0x14
    CARDFileInfo mFileInfo;       // 0x18 (size 0x12)
    CARDStat mCardStat;           // 0x2C (size 0x6C)
    unsigned char mState;         // 0x98
    char mCurrentSlot;            // 0x99
};

extern CMemoryCardMan MemoryCardMan;

// Free Functions
void Detach(long, long);
void Attach(long, long);

#endif // MEMORYCARD_H
