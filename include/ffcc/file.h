#ifndef _FFCC_FILE_H
#define _FFCC_FILE_H

#include "ffcc/manager.h"
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

	void Init();
	void Quit();
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
	bool IsCompleted(CHandle* handle);
	int IsDiskError();
	void SyncCompleted(CHandle* handle);

	void kick();
	CHandle* CheckQueue();

	void DrawError(DVDFileInfo& info, int errorCode);
	
	// void* m_vtable;             // 0x0
    void* m_0x08;                  // 0x4
    void* m_readBuffer;            // 0x8
    CHandle m_fileHandle;          // 0xC-0xB7
    CHandle* m_freeListSentinelDummy[2]; // 0xB8-0xBF
    CHandle* m_freeList;           // 0xC0
    CHandle m_handlePoolHead;
    int m_fatalDiskErrorFlag;
    int m_isDiskError;
};

extern CFile File;

#endif // _FFCC_FILE_H
