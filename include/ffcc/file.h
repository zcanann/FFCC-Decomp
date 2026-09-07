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
		CHandle() {}
		void Reset();
		
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
	void* GetBuffer();
	void LockBuffer();
	void UnlockBuffer();
	void ReadASync(CHandle* handle);
	void Close(CHandle* handle);
	int IsCompleted(CHandle* handle);
	int IsDiskError();
	void SyncCompleted(CHandle* handle);

	void kick();
	CHandle* CheckQueue();

	void DrawError(DVDFileInfo& info, int errorCode);
	
    CMemory::CStage* m_allocStage;  // 0x4
    unsigned char* m_readBuffer;   // 0x8
    CHandle m_fileHandle;          // 0x0c-0xb7
    CHandle m_freeHandle;          // 0xb8-0x163
    CHandle* m_handlePool;          // 0x164
    int m_fatalDiskErrorFlag;      // 0x168
    int m_isDiskError;             // 0x16c
};

extern CFile File;

#endif // _FFCC_FILE_H
