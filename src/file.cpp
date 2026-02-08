#include "ffcc/file.h"

#include "ffcc/p_game.h"
#include "ffcc/system.h"

/*
 * --INFO--
 * PAL Address: 0x80013968
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

    const int kHandleCount = 0x80;

    m_stage = 0; // TODO: hook up real stage creation once CStage is decomped.
    m_fatalDiskErrorFlag = 0;
    m_isDiskError = 0;
    m_readBuffer = new unsigned char[0x100000]; // TODO: replace with stage allocator
	m_handlePoolHead.m_nextOffset = (u32)(new unsigned char[kHandleCount * sizeof(CHandle)]); // TODO: replace with stage-aware array allocation

    CHandle* pool = (CHandle*)m_handlePoolHead.m_nextOffset;

    m_fileHandle.m_next = &m_fileHandle;
    m_fileHandle.m_previous = &m_fileHandle;
    m_fileHandle.m_priority = PRI_SENTINEL;
    m_freeList = pool;

    CHandle* freeSentinel = (CHandle*)&m_freeListSentinelDummy;

    for (int i = 0; i < kHandleCount; i++)
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
	if (m_readBuffer != 0)
	{
		delete[] m_readBuffer;
		m_readBuffer = 0;
	}

	if (m_handlePoolHead.m_nextOffset != 0)
	{
		CHandle* pool = (CHandle*)m_handlePoolHead.m_nextOffset;
		delete[] pool;
		m_handlePoolHead.m_nextOffset = 0;
		m_handlePoolHead.m_next = 0;
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
 * PAL Address: 0x80013968
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

CFile::CHandle* CFile::Open(char* path, unsigned long userParam, CFile::PRI pri)
{
    if (1) // g_Game.game.gameWork._5076_1_ != 0
    {
        pri = CFile::PRI_CRITICAL;
    }

    CHandle* handle = 0;

    s32 entry = DVDConvertPathToEntrynum(path);
	
    if (entry == -1)
	{
        return 0;
	}

    DVDFileInfo fi;
	
    if (!DVDFastOpen(entry, &fi))
	{
        return 0;
	}

    handle = m_freeList;
	
    if (!handle)
	{
        return 0;
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

    while ((inFlight = CheckQueue()) != 0)
	{
        SyncCompleted(inFlight);

        if (fileHandle == 0 || inFlight != fileHandle)
		{
            if (fileHandle == 0)
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
            // This is the specific handle we're targeting: mark as idle.
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

	u32 readSize = fileHandle->m_chunkSize;

	// align to 0x20
	readSize = (readSize + 0x1FU) & ~0x1FU;

	if (readSize > 0x100000U) // && System._4700_4_ != 0
	{
		// Printf(&System, &DAT_801d5dcc, fileHandle->path, readSize);
	}

	DVDReadAsyncPrio(
		&fileHandle->m_dvdFileInfo,
		m_readBuffer,
		(s32)readSize,
		(s32)fileHandle->m_currentOffset,
		0,
		2
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

		if (fileHandle == 0)
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
 * PAL Address: 0x800134f4
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFile::kick()
{
	while (CheckQueue() == 0)
	{
		CHandle* sentinel = &m_fileHandle;
		CHandle* cur = sentinel->m_previous;

		while (cur != sentinel)
		{
			if ((Game.game.m_gameWork.m_gamePaused == 0 || cur->m_priority == PRI_CRITICAL)
			    && (cur->m_completionStatus == 1 || cur->m_completionStatus == 4))
			{
				u32 readSize;

				cur->m_completionStatus = 2;
				readSize = (cur->m_chunkSize + 0x1F) & ~0x1F;

				if (readSize > 0x100000U && System.m_execParam != 0)
				{
					System.Printf("", cur->m_name, readSize);
				}

				DVDReadAsyncPrio(&cur->m_dvdFileInfo, m_readBuffer, readSize, cur->m_currentOffset, 0, 2);
				cur->m_nextOffset = cur->m_currentOffset + readSize;
				if (cur->m_completionStatus != 3)
				{
					return;
				}
				break;
			}
			cur = cur->m_previous;
		}

		if (cur == sentinel)
		{
			return;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFile::CHandle* CFile::CheckQueue()
{
    CHandle* sentinel = &m_fileHandle;
    CHandle* handle = sentinel->m_previous;

    while (handle != sentinel)
    {
        int completionStatus = handle->m_completionStatus;

        if (completionStatus == 2)
        {
            int dvdStatus = DVDGetCommandBlockStatus(&handle->m_dvdFileInfo.cb);

            if (dvdStatus == 0x0B || (dvdStatus >= 4 && dvdStatus <= 6) || dvdStatus == -1)
            {
                DrawError(handle->m_dvdFileInfo, dvdStatus);
            }
            else if (dvdStatus == 0)
            {
                handle->m_completionStatus = 3;
                CHandle* next = CheckQueue();

                if (next != 0)
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

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::DrawError(DVDFileInfo&, int)
{
	// TODO
}
