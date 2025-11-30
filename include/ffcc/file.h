#ifndef CFILE_H
#define CFILE_H

#include <Dolphin/dvd.h>

class CFile {
public:
	enum PRI {
		PRI_LOW    = 0,
		PRI_NORMAL = 1,
		PRI_HIGH   = 2,
	};

	class CHandle {
	public:
		CHandle();
		void Reset();
		
		CHandle* next;
		CHandle* prev;
		unsigned int flags;
		DVDFileInfo dvdFileInfo;
		unsigned int nextOffset;
		int priority;
		int length;
		unsigned int userParam;
		int completionStatus;
		int closedFlag;
		char name[76];
	};

	CFile();

	static void Init();
	static void Quit();
	static void Frame();

	static DVDDiskID* GetCurrentDiskID();

	static void Open(char* path, unsigned long length, PRI pri);
	static int GetLength(CHandle* handle);

	static void BackAllFilesToQueue(CHandle* handle);
	static void Read(CHandle* handle);

	static void LockBuffer();
	static void UnlockBuffer();

	static void ReadASync(CHandle* handle);   // Capital-A variant
	static void readASync(CHandle* handle);   // Lowercase-a variant (likely used internally)

	void Close(CHandle* handle);

	bool IsCompleted(CHandle* handle);
	static void SyncCompleted(CHandle* handle);

	static void kick();
	static CHandle* CheckQueue();

	static void DrawError(DVDFileInfo& info, int errorCode);
	
    void* mStage;
    void* mReadBuffer;
    struct CHandle* mQueueSentinel;
    struct CHandle* mQueueHead;
    char unknown1[68];
    unsigned int maxPriority;
    char unknown2[92];
    void* freeListSentinelDummy;
    struct CHandle *freeList;
    char unknown3[164];
    struct CHandle *handlePool;
    int fatalDiskErrorFlag;
    int isDiskError;
};

static CFile* g_file;

#endif // CFILE_H
