#ifndef _FFCC_FILE_H
#define _FFCC_FILE_H

#include "ffcc/manager.h"
#include "ffcc/memory.h"
#include <Dolphin/dvd.h>

class CFile : public CManager
{
public:
	enum PRI
	{
		PRI_LOW = 0,
		PRI_NORMAL = 1,
		PRI_HIGH = 2,
		PRI_CRITICAL = 3,
		PRI_SENTINEL = 4,
	};

	class CHandle
	{
	public:
		void Reset();
		void SetReadSize(int size, int offset)
		{
			m_chunkSize = size;
			m_currentOffset = offset;
		}
		int GetReadSize() { return m_chunkSize; }
		
	private:
		friend class CFile;
		CHandle* m_next;
		CHandle* m_previous;
		unsigned int m_flags;
		DVDFileInfo m_dvdFileInfo;
		unsigned int m_fileOffset;
		int m_priority;
		int m_length;
		unsigned int m_userParam;
		int m_completionStatus;
		int m_closedFlag;
		char m_name[64];
		unsigned int m_chunkSize;
		unsigned int m_currentOffset;
		unsigned int m_nextOffset;

	public:
		int GetLength();
		void ReadASync();
		int IsCompleted();
		void SyncCompleted();
		void Read();
		void Close();
	};

	virtual void Init();
	virtual void Quit();
	void Frame();
	DVDDiskID* GetCurrentDiskID();
	CHandle* Open(char* path, unsigned long userParam, PRI pri);
	int GetLength(CHandle* handle);
	void BackAllFilesToQueue(CHandle* handle);
	void Read(CHandle* handle);
	void* GetBuffer() { return m_readBuffer; }
	void LockBuffer();
	void UnlockBuffer();
	void ReadASync(CHandle* handle);
	void Close(CHandle* handle);
	int IsCompleted(CHandle* handle);
#ifndef VERSION_GCCJGC
	int IsDiskError() { return m_isDiskError; }
#endif
	int IsFatalError() { return m_fatalDiskErrorFlag; }
	void SyncCompleted(CHandle* handle);

	void kick();
	void readASync(CHandle*);
	CHandle* CheckQueue();

	void DrawError(DVDFileInfo& info, int errorCode);
	
    CMemory::CStage* m_allocStage;  // 0x4
    unsigned char* m_readBuffer;   // 0x8
    CHandle m_fileHandle;          // 0x0c-0xb7
    CHandle m_freeHandle;          // 0xb8-0x163
    CHandle* m_handlePool;          // 0x164
    int m_fatalDiskErrorFlag;      // 0x168
#ifndef VERSION_GCCJGC
    int m_isDiskError;             // 0x16c
#endif
};

extern CFile File;

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: 0x8002cd80
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CFile::CHandle::GetLength()
{
	return File.GetLength(this);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: 0x8003e424
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CFile::CHandle::ReadASync()
{
	File.ReadASync(this);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: 0x8003e454
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CFile::CHandle::IsCompleted()
{
	return File.IsCompleted(this);
}

/*
 * --INFO--
 * PAL Address: 0x800B93EC
 * PAL Size: 44b
 * EN Address: 0x8001DA3C
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CFile::CHandle::Close()
{
	File.Close(this);
}

/*
 * --INFO--
 * PAL Address: 0x800B9420
 * PAL Size: 44b
 * EN Address: 0x8001DA74
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CFile::CHandle::SyncCompleted()
{
	File.SyncCompleted(this);
}

/*
 * --INFO--
 * PAL Address: 0x800B944C
 * PAL Size: 44b
 * EN Address: 0x8001DAA4
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CFile::CHandle::Read()
{
	File.Read(this);
}

#endif // _FFCC_FILE_H
