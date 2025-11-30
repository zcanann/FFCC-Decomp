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
    DVDInit();
	
    static const int kHandleCount = 0x80;

    mStage = (void*)nullptr; // TODO: hook up real stage creation once CStage is decomped.
    mFatalDiskErrorFlag = 0;
    mIsDiskError = 0;
    mReadBuffer = static_cast<void*>(new unsigned char[0x100000]); // TODO: replace with stage allocator
    mHandlePool = new CHandle[0x80]; // TODO: replace with stage-aware array allocation
    mFileHandle.mNext = &mFileHandle;
    mFileHandle.mPrev = &mFileHandle;
    mFileHandle.mPriority = PRI_SENTINEL;
    mFreeList = mHandlePool;

    CHandle* const freeSentinel = reinterpret_cast<CHandle*>(&mFreeListSentinelDummy);

    for (int i = 0; i < kHandleCount; ++i)
	{
        CHandle* h = &mHandlePool[i];
        CHandle* next;
		
        if (i == kHandleCount - 1)
		{
            next = freeSentinel;
        }
		else
		{
            next = &mHandlePool[i + 1];
        }

        h->mNext = next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Quit()
{
	if (mReadBuffer != nullptr)
	{
		delete[] mReadBuffer;
		mReadBuffer = nullptr;
	}

	CHandle* pool = mHandlePool;
	
	if (pool != nullptr)
	{
		// Wtf is this?
		delete[](pool[-1].mName + 0x3C);
		mHandlePool = (CHandle*)nullptr;
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
    if (true) // g_Game.game.gameWork._5076_1_ != 0
    {
        pri = CFile::PRI_CRITICAL;
    }

    CHandle* handle = (CHandle*)nullptr;

    int entry = DVDConvertPathToEntrynum(path);
    if (entry == -1)
        return (CHandle*)nullptr;

    DVDFileInfo fi;
    if (!DVDFastOpen(entry, &fi))
        return (CHandle*)nullptr;

    handle = mFreeList;
    if (!handle)
        return (CHandle*)nullptr;

    mFreeList = handle->mPrev;
    CHandle* sentinel = &mFileHandle;
    CHandle* it = sentinel->mPrev;

    while (it != sentinel && it->mPriority <= pri)
    {
        it = it->mPrev;
    }

    CHandle* next = it->mNext;
    handle->mPrev = it;
    handle->mNext = next;
    next->mPrev   = handle;
    it->mNext     = handle;
    handle->mPriority          = pri;
    handle->mUserParam         = userParam;
    handle->mLength            = fi.length;
    handle->mCompletionStatus  = 0;
    handle->mClosedFlag        = 0;
    handle->mFlags             = 0;
    // strncpy(handle->mName, path, sizeof(handle->mName));
    handle->mChunkSize     = fi.length;
    handle->mCurrentOffset = 0;
    handle->mNextOffset    = 0;
    handle->mDvdFileInfo   = fi;
    handle->mDvdFileInfo.cb.userData = handle;
	
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
void CFile::BackAllFilesToQueue(CHandle* fileHandle)
{
    CHandle* inFlight;

    while ((inFlight = CheckQueue()) != (CHandle*)nullptr)
	{
        SyncCompleted(inFlight);

        if (fileHandle == (CHandle*)nullptr || inFlight != fileHandle) {
            if (fileHandle == (CHandle*)nullptr) {
                // if (System._4700_4_ > 2)
				{
                    // System.Printf(DAT_801D5EFC, inFlight->mName);
                }
            }
			else
			{
                // if (System._4700_4_ > 1)
				{
                    // System.Printf(DAT_801D5E28, inFlight->mName, fileHandle->mName);
                }
            }

            // Put it back into the ready state.
            inFlight->mCompletionStatus = 1;
        } else {
            // This is the specific handle we’re targeting: mark as idle.
            inFlight->mCompletionStatus = 0;
        }
    }
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
    CHandle* handle = CheckQueue();
	
    if (handle != (CHandle*)nullptr)
	{
        return;
    }
	
    CHandle* sentinel = &mFileHandle;
    CHandle* cur = sentinel->mPrev;

    unsigned char gameFlag = true; // g_Game.game.gameWork._5076_1_;

    while (cur != sentinel)
	{
        if (gameFlag == 0 || cur->mPriority == PRI_CRITICAL)
		{
            int status = cur->mCompletionStatus;

            if (status == 1 || status == 4)
			{
                cur->mCompletionStatus = 2;

                unsigned int readSize = cur->mChunkSize + 0x1FU;
                readSize &= ~0x1FU; // align to 0x20

                if (readSize > 0x100000U)
				{
					//  && System._4700_4_ >= 1) {
                    // System.Printf(&DAT_801D5DCC, cur->mName, readSize);
                }

                DVDReadAsyncPrio(
                    &cur->mDvdFileInfo,
                    mReadBuffer,
                    (s32)readSize,
                    (s32)cur->mCurrentOffset,
                    (DVDCallback)nullptr,
                    2
                );

                cur->mNextOffset = cur->mCurrentOffset + readSize;

                if (cur->mCompletionStatus != 3)
				{
                    return;
                }

                kick();
                return;
            }
        }

        cur = cur->mPrev;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFile::CHandle* CFile::CheckQueue()
{
    CHandle* const sentinel = (CHandle*)&mFileHandle;
    CHandle* handle = sentinel->mPrev;

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
