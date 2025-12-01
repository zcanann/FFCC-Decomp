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
void CMemoryCardMan::McOpen(int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McClose()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McCreate(int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McGetStat(int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McSetStat(int)
{
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
void CMemoryCardMan::McRead(char*, int, int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McWrite(char*, int, int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McFormat(int)
{
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
void CMemoryCardMan::McFreeBlocks(int, int*, int*)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemoryCardMan::McDelFile(int)
{
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
void CMemoryCardMan::McChkConnect(int)
{
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
void Attach(long, long)
{
}
