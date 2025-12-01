#include "ffcc/memorycard.h"

#include "dolphin/card.h"

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
void CMemoryCardMan::DebugReadWrite(int, char*, void*, int)
{
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
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::DestroyMcBuff()
{ 
  if (mSaveBuffer != (unsigned char*)nullptr)
  {
    delete[] mSaveBuffer;
	mSaveBuffer = (unsigned char*)nullptr;
  }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McEnd()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::SetMcIconImage()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McRead(char* buffer, int length, int offset)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McWrite(char* buffer, int length, int offset)
{
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
void CMemoryCardMan::McCheck(int)
{
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
        (const char*)nullptr, // PTR_DAT_8032e854,   // file name
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
void CMemoryCardMan::IsBrokenFile()
{
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
void CMemoryCardMan::DummySave()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::DummyLoad()
{
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
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::DecodeData()
{
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
void Detach(long, long)
{
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

