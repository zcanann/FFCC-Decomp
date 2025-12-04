#include "ffcc/file.h"

#include "ffcc/system.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFile::CFile()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::CHandle::Reset()
{ 
	m_completionStatus = 0;
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

    m_stage = (void*)nullptr; // TODO: hook up real stage creation once CStage is decomped.
    m_fatalDiskErrorFlag = 0;
    m_isDiskError = 0;
    m_readBuffer = static_cast<void*>(new unsigned char[0x100000]); // TODO: replace with stage allocator
	m_handlePoolHead.m_nextOffset = reinterpret_cast<u32>(new unsigned char[kHandleCount * sizeof(CHandle)]); // TODO: replace with stage-aware array allocation

    CHandle* pool = reinterpret_cast<CHandle*>(m_handlePoolHead.m_nextOffset);
	
    m_fileHandle.m_next = &m_fileHandle;
    m_fileHandle.m_previous = &m_fileHandle;
    m_fileHandle.m_priority = PRI_SENTINEL;
    m_freeList = pool;

    CHandle* const freeSentinel = reinterpret_cast<CHandle*>(&m_freeListSentinelDummy);

    for (int i = 0; i < kHandleCount; ++i)
	{
        CHandle* handle = &pool[i];
        CHandle* next;
		
        if (i == kHandleCount - 1)
		{
            next = freeSentinel;
        }
		else
		{
            next = &pool[i + 1];
        }

        handle->m_next = next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Quit()
{
	if (m_readBuffer != nullptr)
	{
		delete[] m_readBuffer;
		m_readBuffer = nullptr;
	}

	if (m_handlePoolHead.m_nextOffset != 0)
	{
		CHandle* pool = reinterpret_cast<CHandle*>(m_handlePoolHead.m_nextOffset);
		delete[] pool;
		m_handlePoolHead.m_nextOffset = 0;
		m_handlePoolHead.m_next = (CHandle*)nullptr;
	}

	// DestroyStage(&Memory, stage);
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
	{
        return (CHandle*)nullptr;
	}

    DVDFileInfo fi;
	
    if (!DVDFastOpen(entry, &fi))
	{
        return (CHandle*)nullptr;
	}

    handle = m_freeList;
	
    if (!handle)
	{
        return (CHandle*)nullptr;
	}

    m_freeList = handle->m_previous;
    CHandle* sentinel = &m_fileHandle;
    CHandle* it = sentinel->m_previous;

    while (it != sentinel && it->m_priority <= pri)
    {
        it = it->m_previous;
    }

    CHandle* next = it->m_next;
    handle->m_previous = it;
    handle->m_next = next;
    next->m_previous = handle;
    it->m_next = handle;
    handle->m_priority = pri;
    handle->m_userParam = userParam;
    handle->m_length = fi.length;
    handle->m_completionStatus = 0;
    handle->m_closedFlag = 0;
    handle->m_flags = 0;
    // strncpy(handle->m_name, path, sizeof(handle->m_name));
    handle->m_chunkSize = fi.length;
    handle->m_currentOffset = 0;
    handle->m_nextOffset = 0;
    handle->m_dvdFileInfo = fi;
    handle->m_dvdFileInfo.cb.userData = handle;
	
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
	return fileHandle->m_length;
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

        if (fileHandle == (CHandle*)nullptr || inFlight != fileHandle)
		{
            if (fileHandle == (CHandle*)nullptr)
			{
                // if (System._4700_4_ > 2)
				{
                    // System.Printf(DAT_801D5EFC, inFlight->m_name);
                }
            }
			else
			{
                // if (System._4700_4_ > 1)
				{
                    // System.Printf(DAT_801D5E28, inFlight->m_name, fileHandle->m_name);
                }
            }

            // Put it back into the ready state.
            inFlight->m_completionStatus = 1;
        }
		else
		{
            // This is the specific handle we’re targeting: mark as idle.
            inFlight->m_completionStatus = 0;
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

	fileHandle->m_completionStatus = 2;

	int readSize = fileHandle->m_chunkSize;
	
	// align to 0x20
	readSize = (readSize + 0x1F) & ~0x1F;

	if (readSize > 0x100000) // && System._4700_4_ != 0
	{
		// Printf(&System, &DAT_801d5dcc, fileHandle->path, readSize);
	}

	DVDReadAsyncPrio(
		&fileHandle->m_dvdFileInfo,
		m_readBuffer,
		readSize,
		fileHandle->m_currentOffset,
		/* callback */ (DVDCallback)nullptr,
		/* priority */ 2
	);

	fileHandle->m_nextOffset = fileHandle->m_currentOffset + readSize;
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
		
		fileHandle->m_completionStatus = 1;
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
	fileHandle->m_completionStatus = 1;
	kick();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Close(CFile::CHandle* fileHandle)
{ 
	if (fileHandle->m_completionStatus == 2) //  && (1 < (uint)System._4700_4_)
	{
		// Printf(&System,&DAT_801d5e04,fileHandle->name);
	}

	DVDClose(&fileHandle->m_dvdFileInfo);
	
	fileHandle->m_closedFlag = 1;
	fileHandle->m_next->m_previous = fileHandle->m_previous;
	fileHandle->m_previous->m_next = fileHandle->m_next;
	fileHandle->m_previous = m_freeList;
	m_freeList = fileHandle;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CFile::IsCompleted(CFile::CHandle* fileHandle)
{
	if (fileHandle->m_completionStatus == 3)
	{
		return true;
	}
	
	return false;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::SyncCompleted(CFile::CHandle* fileHandle)
{ 
	while (fileHandle->m_completionStatus != 3)
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
	
    CHandle* sentinel = &m_fileHandle;
    CHandle* cur = sentinel->m_previous;

    unsigned char gameFlag = true; // g_Game.game.gameWork._5076_1_;

    while (cur != sentinel)
	{
        if (gameFlag == 0 || cur->m_priority == PRI_CRITICAL)
		{
            int status = cur->m_completionStatus;

            if (status == 1 || status == 4)
			{
                cur->m_completionStatus = 2;

                unsigned int readSize = cur->m_chunkSize + 0x1FU;
                readSize &= ~0x1FU; // align to 0x20

                if (readSize > 0x100000U)
				{
					//  && System._4700_4_ >= 1) {
                    System.Printf("" /* &DAT_801D5DCC */, cur->m_name, readSize);
                }

                DVDReadAsyncPrio(
                    &cur->m_dvdFileInfo,
                    m_readBuffer,
                    (s32)readSize,
                    (s32)cur->m_currentOffset,
                    (DVDCallback)nullptr,
                    2
                );

                cur->m_nextOffset = cur->m_currentOffset + readSize;

                kick();
                return;
            }
        }

        cur = cur->m_previous;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFile::CHandle* CFile::CheckQueue()
{
    CHandle* const sentinel = (CHandle*)&m_fileHandle;
    CHandle* handle = sentinel->m_previous;

    while (handle != sentinel)
    {
        const int completionStatus = handle->m_completionStatus;

        if (completionStatus == 2)
        {
            const int dvdStatus = DVDGetCommandBlockStatus(&handle->m_dvdFileInfo.cb);

            if (dvdStatus == 0x0B || (dvdStatus >= 4 && dvdStatus <= 6) || dvdStatus == -1)
            {
                DrawError(handle->m_dvdFileInfo, dvdStatus);
            }
            else if (dvdStatus == 0)
            {
                handle->m_completionStatus = 3;
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
                handle->m_completionStatus = 4;
            }
        }
        else if (completionStatus == 3)
        {
            return handle;
        }

        handle = handle->m_previous;
    }

    return (CHandle*)nullptr;
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
