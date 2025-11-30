#include "ffcc/file.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFile::CFile()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::CHandle::Reset()
{ 
	mCompletionStatus = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Quit()
{
	if (mReadBuffer != nullptr) {
		delete[] mReadBuffer;
		mReadBuffer = nullptr;
	}

	CHandle* pool = mHandlePool;
	
	if (pool != nullptr)
	{
		delete[](pool[-1].mName + 0x3C);
		mHandlePool = (CFile::CHandle*)nullptr;
	}

	// DestroyStage(&g_memory, stage);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Frame()
{
	kick();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
DVDDiskID* CFile::GetCurrentDiskID()
{
	return DVDGetCurrentDiskID();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFile::CHandle* CFile::Open(const char* path, unsigned long userParam, CFile::PRI pri)
{
    if (true) // g_Game.game.gameWork._5076_1_ != 0)
	{
        pri = CFile::PRI_CRITICAL;
    }

    CHandle* handle = (CHandle*)nullptr;

    // Resolve path to a DVD entry
    int entry = DVDConvertPathToEntrynum(path);
	
    if (entry != -1)
	{
        DVDFileInfo fi;
        DVDFastOpen(entry, &fi);

        handle = mFreeList;
        mFreeList  = handle->mPrev;

        CHandle* it = mQueueSentinel->mPrev;
		
        while (it != mQueueSentinel && it->mPriority <= pri)
		{
            it = it->mPrev;
        }
		
        CHandle* next = it->mNext;

        handle->mPrev = it;
        handle->mNext = next;
        next->mPrev   = handle;
        it->mNext     = handle;

        handle->mPriority = pri;
        handle->mUserParam = userParam;
        handle->mLength = fi.length;
        handle->mCompletionStatus = 0;
        handle->mClosedFlag = 0;
        handle->mFlags = 0;
		
        // strcpy(handle->mName, path);
		
        handle->mChunkSize  = fi.length;
        handle->mCurrentOffset  = 0;
        handle->mNextOffset = 0;
        handle->mDvdFileInfo = fi;
        handle->mDvdFileInfo.cb.userData = handle;
    }
	
    // if (!handle && System._4700_4_ != 0)
	// {
    //     System.Printf(&DAT_801d5f9c, path);
    // }

    return handle;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CFile::GetLength(CFile::CHandle* fileHandle)
{
	return fileHandle->mLength;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::BackAllFilesToQueue(CFile::CHandle* fileHandle)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Read(CFile::CHandle* fileHandle)
{
	BackAllFilesToQueue(fileHandle);

	fileHandle->mCompletionStatus = 2;

	int readSize = fileHandle->mChunkSize;
	
	// align to 0x20
	readSize = (readSize + 0x1F) & ~0x1F;

	if (readSize > 0x100000) // && System._4700_4_ != 0
	{
		// Printf(&System, &DAT_801d5dcc, fileHandle->path, readSize);
	}

	DVDReadAsyncPrio(
		&fileHandle->mDvdFileInfo,
		mReadBuffer,
		readSize,
		fileHandle->mCurrentOffset,
		/* callback */ (DVDCallback)nullptr,
		/* priority */ 2
	);

	fileHandle->mNextOffset = fileHandle->mCurrentOffset + readSize;
	SyncCompleted(fileHandle);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::LockBuffer()
{
	CFile::CHandle* fileHandle;
  
	while(true)
	{
		fileHandle = CheckQueue();
		
		if (fileHandle == nullptr)
		{
			break;
		}
		
		SyncCompleted(fileHandle);
		
		fileHandle->mCompletionStatus = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::UnlockBuffer()
{
	kick();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::ReadASync(CFile::CHandle* fileHandle)
{ 
	fileHandle->mCompletionStatus = 1;
	kick();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Close(CFile::CHandle* fileHandle)
{ 
	if (fileHandle->mCompletionStatus == 2) //  && (1 < (uint)System._4700_4_)
	{
		// Printf(&System,&DAT_801d5e04,fileHandle->name);
	}

	DVDClose(&fileHandle->mDvdFileInfo);
	
	fileHandle->mClosedFlag = 1;
	fileHandle->mNext->mPrev = fileHandle->mPrev;
	fileHandle->mPrev->mNext = fileHandle->mNext;
	fileHandle->mPrev = mFreeList;
	mFreeList = fileHandle;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CFile::IsCompleted(CFile::CHandle* fileHandle)
{
	if (fileHandle->mCompletionStatus == 3)
		return true;
	
	return false;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::SyncCompleted(CFile::CHandle* fileHandle)
{ 
	while (fileHandle->mCompletionStatus != 3)
	{
		kick();
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::kick()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFile::CHandle* CFile::CheckQueue()
{
    CHandle* const sentinel = mQueueSentinel;
    CHandle* handle = mQueueHead;

    while (handle != sentinel)
    {
        const int completionStatus = handle->mCompletionStatus;

        if (completionStatus == 2)
        {
            const int dvdStatus = DVDGetCommandBlockStatus(&handle->mDvdFileInfo.cb);

            if (dvdStatus == 0x0B || (dvdStatus >= 4 && dvdStatus <= 6) || dvdStatus == -1)
            {
                DrawError(handle->mDvdFileInfo, dvdStatus);
            }
            else if (dvdStatus == 0)
            {
                handle->mCompletionStatus = 3;
                CHandle* next = CheckQueue();
				
                if (next != (CHandle*)nullptr)
                {
                    return next;
                }
            }
            else if (dvdStatus > 0)
            {
                return handle;
            }
            else
            {
                handle->mCompletionStatus = 4;
            }
        }
        else if (completionStatus == 3)
        {
            return handle;
        }

        handle = handle->mPrev;
    }

    return (CHandle*)nullptr;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::readASync(CFile::CHandle *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::DrawError(DVDFileInfo &, int)
{
	// TODO
}
