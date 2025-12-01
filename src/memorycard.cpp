#include "ffcc/memorycard.h"
#include "ffcc/file.h"
#include "ffcc/system.h"

#include "dolphin/card.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "string.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMemoryCardMan::CMemoryCardMan()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::Init()
{
    CARDInit();

    mResult = 0;
    mOpDoneFlag = 0;
    mCurrentSlot = -1;
    mState = 0;
    mSaveBuffer = (char*)nullptr;

    // mStage = g_memory.CreateStage(0x16000, s_CMemoryCardMan_801dae0c, 0);
    // mMountWorkArea = __nwa__(0xA000,  mStage, s_memorycard_cpp_801daea8, 0x88);

    mCurrentSlot = -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::Quit()
{ 
  mCurrentSlot = -1;
  
  if (mMountWorkArea != (void*)nullptr)
  {
    delete[] mMountWorkArea;
    mMountWorkArea = (void*)nullptr;
  }
  
  // DestroyStage__7CMemoryFPQ27CMemory6CStage(&g_memory,mStage);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::DebugReadWrite(int isWrite, char* filename, void* buffer, int length)
{
    bool success = false;
    bool abort   = false;
    int  result;

    // Mount card
    result = CARDMount(1, mMountWorkArea, 0);

    bool canUseCard = false;
	
    if (result != 0 && result != -6)
    {
        canUseCard = true;
    }
    else if (CARDCheckAsync(1, 0) >= 0)
    {
        canUseCard = true;
    }

    if (canUseCard)
    {
        // Wait until card is ready; optionally format if needed.
        while (true)
        {
            result = CARDGetResultCode(1);
			
            if (result == 0)
                break; // card ready

            if ((result == -6 || result == -13) && isWrite == 0)
            {
                System.Printf("%s", (char*)nullptr /* DAT_801db044 */);

                if (CARDFormat(1) < 0)
                {
                    abort = true;
                    break;
                }
            }
            else
            {
                abort = true;
                break;
            }
        }

        if (!abort)
        {
            unsigned long sectorSizeTmp;
            if (CARDGetSectorSize(1, &sectorSizeTmp) >= 0)
            {
                if (isWrite != 0)
                {
                    CARDFileInfo fileInfo;
                    result = CARDOpen(1, filename, &fileInfo);

                    if (result < 0)
                    {
                        int      fileNo;
                        CARDStat stat;

                        for (fileNo = 0; fileNo < 0x7F; ++fileNo)
                        {
                            if (CARDGetStatus(1, fileNo, &stat) >= 0 &&
                                strcmp(filename, (char*)&stat) == 0)
                            {
                                break;
                            }
                        }

                        if (fileNo >= 0x7F ||
                            CARDFastOpen(1, fileNo, &fileInfo) < 0)
                        {
                            abort = true;
                        }
                    }

                    if (!abort)
                    {
                        if (CARDRead(&fileInfo, buffer, length, 0) >= 0)
                            success = true;

                        CARDClose(&fileInfo);
                    }
                }
                else
                {
                    CARDDelete(1, filename);

                    CARDFileInfo fileInfo;
                    if (CARDCreate(1, filename, length, &fileInfo) >= 0)
                    {
                        if (CARDWrite(&fileInfo, buffer, length, 0) >= 0)
                            success = true;

                        CARDClose(&fileInfo);
                    }
                }
            }
        }
    }

    CARDUnmount(1);

    if (!success)
        System.Printf("%s", (char*)nullptr /* DAT_801db07c */);
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CMemoryCardMan::AsyncFinished()
{ 
	return mOpDoneFlag != 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::GetResult()
{
	return mResult;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McMount(int chan)
{ 
    mOpDoneFlag = 0;
    mState = 1;

    int result = CARDMountAsync(chan, mMountWorkArea, &Detach, &Attach);

    if (result < 0)
	{
        mOpDoneFlag = 1;
    }

    mResult = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McUnmount(int chan)
{
	mResult = CARDUnmount(chan);
	mOpDoneFlag = 1;
	mState = '\x02';
	mCurrentSlot = 0xff;

	return mResult;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McOpen(int chan)
{ 
	mResult = CARDOpen(chan, (const char*)nullptr /* PTR_DAT_8032e854 */, &mFileInfo);
	mOpDoneFlag = 1;
	mState = 3;

	return mResult;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McClose()
{
	int chan = mFileInfo.chan;

	if (chan < 0 || chan > 1)
	{
		mOpDoneFlag = 1;
		mState = 4;
		mResult = -3;

		return mResult;
	}

	int result = CARDClose(&mFileInfo);
	
	mResult = result;
	mOpDoneFlag = 1;
	mState = 4;

	return mResult;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McCreate(int chan)
{
    mOpDoneFlag = 0;
    mState = 5;

    int result = CARDCreateAsync(
        chan,
        (const char*)nullptr, // PTR_DAT_8032e854, // file name string
        0x2C000, // size
        &mFileInfo,
        &Attach
    );

    if (result < 0)
    {
        mOpDoneFlag = 1;
    }

    mResult = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McGetStat(int chan)
{
	int result = CARDGetStatus(
		chan,
		mFileInfo.fileNo,
		&mCardStat
	);

	mResult = result;
	mOpDoneFlag = 1;
	mState = 6;

	return mResult;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McSetStat(int chan)
{
	int result = CARDSetStatus(
		chan,
		mFileInfo.fileNo,
		&mCardStat
	);

	mResult = result;
	mOpDoneFlag = 1;
	mState = 7;

	return mResult;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::CreateMcBuff()
{
    if (mSaveBuffer == 0)
    {
        mSaveBuffer = (char*)nullptr; // (char*)__nwa__(0xA000, mStage, s_memorycard_cpp_801daea8, 0x2AB);

        if (mSaveBuffer == 0 && System.mExecParam != 0)
        {
            System.Printf("%s(%d): Error: memory allocation", "memorycard.cpp", 0x2AD);
        }
    }

    // Zero buffer every call, allocated or not
    memset(mSaveBuffer, 0, 0xA000);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::DestroyMcBuff()
{ 
  if (mSaveBuffer != (char*)nullptr)
  {
    delete[] mSaveBuffer;
	mSaveBuffer = (char*)nullptr;
  }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McEnd()
{
    int chan = 0;

    while (chan < 2)
    {
        int attempt = 0;

        while (attempt < 10)
        {
            int result = CARDUnmount(chan);

            mResult = result;
            mOpDoneFlag = 1;
            mState = 2;
            mCurrentSlot = 0xFF;

            // IMPORTANT: compare mResult, not result
            if (mResult != -1)
            {
                break;
            }

            attempt++;
        }

        chan++;
    }

    if (mSaveBuffer != 0)
    {
        delete[] mSaveBuffer;
        mSaveBuffer = 0;
    }

    mResult = 0;
    mOpDoneFlag = 0;
    mCurrentSlot = 0xFF;
    mState = 0;
    mSaveBuffer = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::SetMcIconImage()
{
    if (mSaveBuffer == (char*)nullptr)
    {
        mSaveBuffer = (char*)nullptr; // (char*)__nwa__(0xA000, mStage, s_memorycard_cpp_801daea8, 0x2AB);

        if (mSaveBuffer == (char*)nullptr && System.mExecParam != 0)
        {
            System.Printf("%s(%d): Error: memory allocation", "" /* s_memorycard_cpp_801daea8 */, 0x2AD);
        }

        memset(mSaveBuffer, 0, 0xA000);
    }
	
    char path[136];

    const char* lang = (const char*) nullptr; // Game.game.GetLangString();
    sprintf(path, "dvd/%smenu/%s", lang, "" /*PTR_s_icon_dat_8032e850*/);
    CFile::CHandle* h = File.Open(path, 0, CFile::PRI_LOW);

    if (h == nullptr && System.mExecParam != 0)
    {
        System.Printf("%s(%d): Error: %s open error", "" /* s_memorycard_cpp_801daea8 */, 0x2EF, path);
    }

    File.Read(h);
    File.SyncCompleted(h);

    int len = File.GetLength(h);

    if (len != 0x2A00 && System.mExecParam != 0)
    {
        System.Printf("%s(%d): Error: [%s] data error", "" /* s_memorycard_cpp_801daea8 */, 0x2F6, path);
    }

    memcpy(mSaveBuffer + 0x40, File.mReadBuffer, len);

    File.Close(h);

    mCardStat.commentAddr = 0;
    mCardStat.iconAddr    = 0x40;

    mCardStat.bannerFormat = (mCardStat.bannerFormat & ~0x03) | 0x02; // lower 2 bits = 2
    mCardStat.bannerFormat &= ~0x04;  // clear bit 2

    mCardStat.iconFormat = (mCardStat.iconFormat & ~0x0003) | 0x0001;
    mCardStat.iconSpeed  = (mCardStat.iconSpeed  & ~0x0003) | 0x0002;

    mCardStat.iconFormat = (mCardStat.iconFormat & ~0x000C) | 0x0004;
    mCardStat.iconSpeed  = (mCardStat.iconSpeed  & ~0x000C) | 0x0008;

    mCardStat.iconFormat = (mCardStat.iconFormat & ~0x0030) | 0x0010;
    mCardStat.iconSpeed  = (mCardStat.iconSpeed  & ~0x0030) | 0x0020;

    mCardStat.iconFormat = (mCardStat.iconFormat & ~0x00C0) | 0x0040;
    mCardStat.iconSpeed  = (mCardStat.iconSpeed  & ~0x00C0) | 0x0080;

    mCardStat.iconFormat &= ~0x0300;
    mCardStat.iconSpeed  &= ~0x0300;

    mCardStat.offsetIcon[4] = 0xFFFFFFFF;
    mCardStat.iconFormat &= ~0x0C00;
    mCardStat.iconSpeed  &= ~0x0C00;

    mCardStat.offsetIcon[5] = 0xFFFFFFFF;
    mCardStat.iconFormat &= ~0x3000;
    mCardStat.iconSpeed  &= ~0x3000;

    mCardStat.offsetIcon[6] = 0xFFFFFFFF;
    mCardStat.iconFormat &= ~0xC000;
    mCardStat.iconSpeed  &= ~0xC000;

    mCardStat.offsetIcon[7] = 0xFFFFFFFF;

    mCardStat.offsetIconTlut = 0x2840;
    mCardStat.offsetIconTlut = 0x2A40;

    size_t titleLen = strlen("" /* PTR_s_FF_Crystal_Chronicles_8032e858 */);
    memcpy(mSaveBuffer, "" /*PTR_s_FF_Crystal_Chronicles_8032e858*/, titleLen);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McRead(char* buffer, int length, int offset)
{
    if (buffer == nullptr)
    {
        buffer = mSaveBuffer;
    }

    mOpDoneFlag = 0;
    mState = 8;

    int result = CARDReadAsync(&mFileInfo, buffer, length, offset, &Attach);

    if (result < 0)
    {
        mOpDoneFlag = 1;
    }

    mResult = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McWrite(char* buffer, int length, int offset)
{
    if (buffer == nullptr)
    {
        buffer = mSaveBuffer;
    }

    mOpDoneFlag = 0;
    mState = 9;

    int result = CARDWriteAsync(
        &mFileInfo,
        buffer,
        length,
        offset,
        &Attach
    );

    if (result < 0)
    {
        mOpDoneFlag = 1;
    }

    mResult = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McFormat(int chan)
{
    mOpDoneFlag = 0;
    mState = 10;
	
    int result = CARDFormatAsync(
        chan,
        &Attach
    );

    if (result < 0)
    {
        mOpDoneFlag = 1;
    }

    mResult = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McCheck(int chan)
{
    mOpDoneFlag = 0;
    mState = 11;

    int result = CARDCheckAsync(chan, &Attach);

    if (result < 0)
    {
        mOpDoneFlag = 1;
    }

    mResult = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McFreeBlocks(int chan, int* bytesFree, int* filesFree)
{
    int result;
    long localBytes;
    long localFiles;

    result = CARDFreeBlocks(chan, &localBytes, &localFiles);

    mResult = result;
    *bytesFree = localBytes;
    *filesFree = localFiles;
    mState = 12;
    mOpDoneFlag = 1;

    return mResult;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McDelFile(int chan)
{
    mOpDoneFlag = 0;
    mState = 13;
	
    int result = CARDDeleteAsync(
        chan,
        "FFCC", // PTR_DAT_8032e854, // file name
        &Attach
    );

    if (result < 0)
    {
        mOpDoneFlag = 1;
    }

    mResult = result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CMemoryCardMan::IsBrokenFile()
{
    if (mCardStat.iconAddr == 0xFFFFFFFF || mCardStat.commentAddr == 0xFFFFFFFF)
    {
		return 1;
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::MakeSaveData()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::SetLoadData()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::CalcCrc(Mc::SaveDat*)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::ChkCrc(Mc::SaveDat*)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::DummySave()
{
    int result;

    mOpDoneFlag = 0;
    mState = 1;

    result = CARDMountAsync(0, mMountWorkArea, &Detach, &Attach);
    if (result < 0)
    {
        mOpDoneFlag = 1;
    }
    mResult = result;

    // Busy-wait for async completion
    while ((-((int)mOpDoneFlag) | (int)mOpDoneFlag) >= 0)
    {
    }

    if (mResult == -6)
    {
        mOpDoneFlag = 0;
        mState = 10;

        result = CARDFormatAsync(0, &Attach);
        if (result < 0)
        {
            mOpDoneFlag = 1;
        }
        mResult = result;

        while ((-((int)mOpDoneFlag) | (int)mOpDoneFlag) >= 0)
        {
        }

        if (mResult != 0)
        {
            if (System.mExecParam != 0)
            {
                // "%s(%d) McFormat(%d) error(%d)"
                System.Printf("%s", /* s_McFormat(%d)_error(%d)_801daef8 */ 0);
            }

            result = CARDUnmount(0);
            mResult = result;
            mOpDoneFlag = 1;
            mState = 2;
            mCurrentSlot = 0xFF;

            return mResult;
        }
    }

    // Handle general mount error
    if (mResult != 0)
    {
        if (System.mExecParam != 0)
        {
            // "%s(%d) McMount(%d) error(%d)"
            System.Printf("%s", /* s_McMount(%d)_error(%d)_801dae78 */ 0);
        }

        result = CARDUnmount(0);
        mResult = result;
        mOpDoneFlag = 1;
        mState = 2;
        mCurrentSlot = 0xFF;

        return mResult;
    }

    result = CARDOpen(0, /* PTR_DAT_8032e854 */ (const char*)0, &mFileInfo);
    mResult = result;
    mOpDoneFlag = 1;
    mState = 3;

    if (mResult == -4)
    {
        mOpDoneFlag = 0;
        mState = 5;

        result = CARDCreateAsync(
            0,
            /* PTR_DAT_8032e854 */ (const char*)0,
            0x2C000,
            &mFileInfo,
            &Attach
        );

        if (result < 0)
        {
            mOpDoneFlag = 1;
        }
        mResult = result;

        while ((-((int)mOpDoneFlag) | (int)mOpDoneFlag) >= 0)
        {
        }

        if (mResult != 0)
        {
            if (System.mExecParam != 0)
            {
                // "McCreate(%d) error(%d)"
                System.Printf("%s", /* s_McCreate(%d)_error(%d)_801daf10 */ 0);
            }

            result = CARDUnmount(0);
            mResult = result;
            mOpDoneFlag = 1;
            mState = 2;
            mCurrentSlot = 0xFF;

            return mResult;
        }

        result = CARDGetStatus(0, mFileInfo.fileNo, &mCardStat);
        mResult = result;
        mOpDoneFlag = 1;
        mState = 6;

        if (mResult != 0)
        {
            if (System.mExecParam != 0)
            {
                // "McGetStat(%d) error(%d)"
                System.Printf("%s", /* s_McGetStat(%d)_error(%d)_801daf28 */ 0);
            }

            result = CARDUnmount(0);
            mResult = result;
            mOpDoneFlag = 1;
            mState = 2;
            mCurrentSlot = 0xFF;

            return mResult;
        }

        if (mSaveBuffer == 0)
        {
            mSaveBuffer = (char*)0;  
            // __nwa__(0xA000, mStage, s_memorycard_cpp_801daea8, 0x2AB);

            if (mSaveBuffer == 0 && System.mExecParam != 0)
            {
                // "%s(%d): Error: memory allocation"
                System.Printf("%s", /* s_%s(%d):_Error:_memory_allocation_801daeb8 */ 0);
            }
        }

        memset(mSaveBuffer, 0, 0xA000);
		
        SetMcIconImage();

        mOpDoneFlag = 0;
        mState = 9;

        result = CARDWriteAsync(
            &mFileInfo,
            mSaveBuffer,
            0x4000,
            0,
            &Attach
        );

        if (result < 0)
        {
            mOpDoneFlag = 1;
        }
        mResult = result;

        while ((-((int)mOpDoneFlag) | (int)mOpDoneFlag) >= 0)
        {
        }

        if (mResult != 0)
        {
            if (System.mExecParam != 0)
            {
                System.Printf("%s", /* s_McWrite(%d)_error(%d)_801daf44 */ 0);
            }

            result = CARDUnmount(0);
            mResult = result;
            mOpDoneFlag = 1;
            mState = 2;
            mCurrentSlot = 0xFF;

            if (mSaveBuffer != 0)
            {
                delete[] mSaveBuffer;
                mSaveBuffer = 0;
            }

            return mResult;
        }

        result = CARDSetStatus(0, mFileInfo.fileNo, &mCardStat);
        mResult = result;
        mOpDoneFlag = 1;
        mState = 7;

        if (mResult != 0)
        {
            if (System.mExecParam != 0)
            {
                System.Printf("%s", /* s_McSetStat(%d)_error(%d)_801daf5c */ 0);
            }

            result = CARDUnmount(0);
            mResult = result;
            mOpDoneFlag = 1;
            mState = 2;
            mCurrentSlot = 0xFF;

            if (mSaveBuffer != 0)
            {
                delete[] mSaveBuffer;
                mSaveBuffer = 0;
            }

            return mResult;
        }
    }
    else
    {
        if (mSaveBuffer == 0)
        {
            mSaveBuffer = (char*)0;
            // __nwa__(0xA000, ...)

            if (mSaveBuffer == 0 && System.mExecParam != 0)
            {
                System.Printf("%s", /* s_%s(%d):_Error:_memory_allocation_801daeb8 */ 0);
            }
        }

        memset(mSaveBuffer, 0, 0xA000);
    }

    MakeSaveData();
	
    mOpDoneFlag = 0;
    mState = 9;

    result = CARDWriteAsync(
        &mFileInfo,
        mSaveBuffer,
        0xA000,
        0x4000,
        &Attach
    );

    if (result < 0)
    {
        mOpDoneFlag = 1;
    }
    mResult = result;

    while ((-((int)mOpDoneFlag) | (int)mOpDoneFlag) >= 0)
    {
    }

    if (mResult == 0)
    {
        if (mSaveBuffer != 0)
        {
            delete[] mSaveBuffer;
            mSaveBuffer = 0;
        }

        int chan = mFileInfo.chan;

        if (chan < 0 || chan > 1)
        {
            mOpDoneFlag = 1;
            mState = 4;
            mResult = -3;
        }
        else
        {
            result = CARDClose(&mFileInfo);
            mResult = result;
            mOpDoneFlag = 1;
            mState = 4;
        }

        result = CARDUnmount(0);
        mResult = result;
        mOpDoneFlag = 1;

        mState = 2;
        mCurrentSlot = 0xFF;

        return 0;
    }

    if (System.mExecParam != 0)
    {
        System.Printf("%s", /* s_McWrite(%d)_error(%d)_801daf44 */ 0);
    }

    int chan = mFileInfo.chan;

    if (chan < 0 || chan > 1)
    {
        mOpDoneFlag = 1;
        mState = 4;
        mResult = -3;
    }
    else
    {
        result = CARDClose(&mFileInfo);
        mResult = result;
        mOpDoneFlag = 1;
        mState = 4;
    }

    result = CARDUnmount(0);
    mResult = result;
    mOpDoneFlag = 1;
    mState = 2;
    mCurrentSlot = 0xFF;

    if (mSaveBuffer != 0)
    {
        delete[] mSaveBuffer;
        mSaveBuffer = 0;
    }

    return mResult;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::DummyLoad()
{
    int result;

    // Begin mount
    mOpDoneFlag = 0;
    mState = 1;

    result = CARDMountAsync(0, mMountWorkArea, &Detach, &Attach);
    if (result < 0)
    {
        mOpDoneFlag = 1;
    }
    mResult = result;

    // Busy wait for async completion
    while ( ((-(int)mOpDoneFlag) | (int)mOpDoneFlag) >= 0 )
    {
    }

    // If mount failed
    if (mResult != 0)
    {
        if (System.mExecParam != 0)
        {
            // "McMount(%d) error(%d)"
            System.Printf("%s", /* s_McMount(%d)_error(%d)_801dae78 */ 0);
        }

        result = CARDUnmount(0);
        mResult = result;
        mOpDoneFlag = 1;
        mState = 2;
        mCurrentSlot = 0xFF;

        return mResult;
    }

    result = CARDOpen(0, /* PTR_DAT_8032e854 */ (const char*)0, &mFileInfo);
    mResult = result;
    mOpDoneFlag = 1;
    mState = 3;

    if (mResult != 0)
    {
        // Open failed
        if (System.mExecParam != 0)
        {
            // "McOpen(%d) error(%d)"
            System.Printf("%s", /* s_McOpen(%d)_error(%d)_801dae90 */ 0);
        }

        result = CARDUnmount(0);
        mResult = result;
        mOpDoneFlag = 1;
        mState = 2;
        mCurrentSlot = 0xFF;

        return mResult;
    }

    if (mSaveBuffer == 0)
    {
        mSaveBuffer = (char*)0; 
        // __nwa__(0xA000, mStage, s_memorycard_cpp_801daea8, 0x2AB);

        if (mSaveBuffer == 0 && System.mExecParam != 0)
        {
            System.Printf("%s", /* s_%s(%d):_Error:_memory_allocation_801daeb8 */ 0);
        }
    }

    memset(mSaveBuffer, 0, 0xA000);
    mOpDoneFlag = 0;
    mState = 8;

    result = CARDReadAsync(
        &mFileInfo,
        mSaveBuffer,
        0xA000,
        0x4000,
        &Attach
    );

    if (result < 0)
    {
        mOpDoneFlag = 1;
    }

    mResult = result;

    // Wait for read to finish
    while ( ((-(int)mOpDoneFlag) | (int)mOpDoneFlag) >= 0 )
    {
    }

    if (mResult == 0)
    {
        int chan = mFileInfo.chan;

        if (chan < 0 || chan > 1)
        {
            mOpDoneFlag = 1;
            mState = 4;
            mResult = -3;
        }
        else
        {
            result = CARDClose(&mFileInfo);
            mResult = result;
            mOpDoneFlag = 1;
            mState = 4;
        }

        result = CARDUnmount(0);
        mResult = result;
        mOpDoneFlag = 1;
        mState = 2;
        mCurrentSlot = 0xFF;

        // Game.LoadInit();
        SetLoadData();
        // Game.LoadFinished();

        if (mSaveBuffer != 0)
        {
            delete[] mSaveBuffer;
            mSaveBuffer = 0;
        }

        return 0;
    }

    if (System.mExecParam != 0)
    {
        // "McRead(%d) error(%d)"
        System.Printf("%s", /* s_McRead(%d)_error(%d)_801daee0 */ 0);
    }

    int chan = mFileInfo.chan;

    if (chan < 0 || chan > 1)
    {
        mOpDoneFlag = 1;
        mState = 4;
        mResult = -3;
    }
    else
    {
        result = CARDClose(&mFileInfo);
        mResult = result;
        mOpDoneFlag = 1;
        mState = 4;
    }

    result = CARDUnmount(0);
    mResult = result;
    mOpDoneFlag = 1;
    mState = 2;
    mCurrentSlot = 0xFF;

    if (mSaveBuffer != 0)
    {
        delete[] mSaveBuffer;
        mSaveBuffer = 0;
    }

    return mResult;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::CnvPlayTime(unsigned int frames, int* hours, int* minutes)
{
    int total_minutes = frames / 1500;
	
    *minutes = total_minutes % 60;
    *hours = total_minutes / 60;
	
    if (*hours >= 999)
	{
        *hours = 999;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMemoryCardMan::McChkConnect(int chan)
{
    long type;
    long sectorSize;
	int result;

    // CARDProbeEx returns:
    //  0   = ready
    // -1   = no card
    // -2   = busy
    // -5   = broken
    int probeResult = CARDProbeEx(chan, &type, &sectorSize);

    if (probeResult == -1)
    {
        result = 1;
    }
    else if (probeResult == 0)
    {
        if (sectorSize != 0x2000)
        {
            result = -2;
        }
        else
        {
            result = 0;
        }
    }
    else if (probeResult == -2)
    {
        result = -3;
    }
    else if (probeResult == -5)
    {
        result = -4;
    }
    else
    {
        result = -1;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::EncodeData()
{
    const u8  key       = mSaveBuffer[0x11];
    const u32 rotAmount = key & 0x1F;

    u32* ptr = reinterpret_cast<u32*>(mSaveBuffer + 0x18);

    for (int i = 0; i < 0x5B6; i++)
    {
        for (int w = 0; w < 7; w++)
        {
            u32 v = ptr[w];
            v = (v << rotAmount) | (v >> (32 - rotAmount));
            ptr[w] = v;
        }

        ptr += 7;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::DecodeData()
{
    u32 shift = (mSaveBuffer[0x11] & 0x1F);
    u32 rshift = (32 - shift) & 31; 
    u32* ptr = reinterpret_cast<u32*>(mSaveBuffer + 0x18);

    for (int i = 0; i < 0x5B6; i++)
    {
        for (int w = 0; w < 7; w++)
        {
            u32 v = ptr[w];
            v = (v >> shift) | (v << rshift);
            ptr[w] = v;
        }

        ptr += 7;
    }
}

void CMemoryCardMan::CalcSaveDatHpMax(Mc::SaveDat*)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::Odekake(int, Mc::SaveDat&, int, Mc::SaveDat&, int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Detach(long currentSlot, long result)
{ 
	MemoryCardMan.mResult = result;
	MemoryCardMan.mOpDoneFlag = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Attach(long currentSlot, long result)
{
    MemoryCardMan.mResult = result;
    MemoryCardMan.mOpDoneFlag = 1;

    if (MemoryCardMan.mState == 1)
    {
        if (result == 0)
        {
            MemoryCardMan.mCurrentSlot = currentSlot;
        }
    }
}

