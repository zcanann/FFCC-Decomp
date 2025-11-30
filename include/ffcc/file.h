#ifndef CFILE_H
#define CFILE_H

#include <Dolphin/dvd.h>

class CFile {
public:
	enum PRI {
		PRI_LOW    = 0,
		PRI_NORMAL = 1,
		PRI_HIGH   = 2,
		PRI_CRITICAL   = 3,
	};

	class CHandle {
	public:
		CHandle();
		void Reset();
		
		CHandle* mNext;
		CHandle* mPrev;
		unsigned int mFlags;
		DVDFileInfo mDvdFileInfo;
		unsigned int mFileOffset;
		int mPriority;
		int mLength;
		unsigned int mUserParam;
		int mCompletionStatus;
		int mClosedFlag;
		char mName[64];
		unsigned int mChunkSize;
		unsigned int mCurrentOffset;
		unsigned int mNextOffset;
	};

	CFile();

	void Init();
	void Quit();
	void Frame();
	DVDDiskID* GetCurrentDiskID();
	CHandle* Open(const char* path, unsigned long userParam, PRI pri);
	int GetLength(CHandle* handle);
	void BackAllFilesToQueue(CHandle* handle);
	void Read(CHandle* handle);
	void LockBuffer();
	void UnlockBuffer();
	void ReadASync(CHandle* handle);
	void Close(CHandle* handle);
	bool IsCompleted(CHandle* handle);
	void SyncCompleted(CHandle* handle);

	void kick();
	CHandle* CheckQueue();

	void DrawError(DVDFileInfo& info, int errorCode);
	
    void* mStage;
    void* mReadBuffer;
    struct CHandle* mQueueSentinel;
    struct CHandle* mQueueHead;
    char mUnknown1[68];
    unsigned int mMaxPriority;
    char mUnknown2[92];
    void* mFreeListSentinelDummy;
    struct CHandle *mFreeList;
    char mUnknown3[164];
    struct CHandle *mHandlePool;
    int mFatalDiskErrorFlag;
    int mIsDiskError;
	
private:
	void readASync(CHandle* handle);   // Lowercase-a variant (likely used internally)
};

static CFile* g_file;

#endif // CFILE_H
