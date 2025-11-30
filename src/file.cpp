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
	this->completionStatus = 0;
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
	// TODO
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
void CFile::Open(char *, unsigned long, CFile::PRI)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CFile::GetLength(CFile::CHandle* fileHandle)
{
	return fileHandle->length;
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
		
		fileHandle->completionStatus = 1;
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
	fileHandle->completionStatus = 1;
	kick();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFile::Close(CFile::CHandle* fileHandle)
{ 
	if (fileHandle->completionStatus == 2) //  && (1 < (uint)System._4700_4_)
	{
		// Printf(&System,&DAT_801d5e04,fileHandle->name);
	}

	DVDClose(&fileHandle->dvdFileInfo);
	
	fileHandle->closedFlag = 1;
	fileHandle->next->prev = fileHandle->prev;
	fileHandle->prev->next = fileHandle->next;
	fileHandle->prev = this->freeList;
	this->freeList = fileHandle;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CFile::IsCompleted(CFile::CHandle* fileHandle)
{
	if (fileHandle->completionStatus == 3)
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
	while (fileHandle->completionStatus != 3)
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
	return (CFile::CHandle*)nullptr;
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
