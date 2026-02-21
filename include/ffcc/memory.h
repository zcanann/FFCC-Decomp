#ifndef _FFCC_MEMORY_H_
#define _FFCC_MEMORY_H_

#include <dolphin/types.h>

class CMemory;
class CAmemCache;
class CAmemCacheSet;
class CChara;

unsigned int CheckSum(void*, int);

class CMemory
{
public:
    class CStage
    {
    public:
        void initBlock();
        void quitBlock();
        void* alloc(unsigned long, char*, unsigned long, int);
        void setDefaultParam(unsigned long);
        void resDefaultParam();
        void setParam(void*, unsigned long);
        void free(void*);
        int heapWalker(int, void*, unsigned long);
        void drawHeapBar(int);
        void drawHeapTitle(int);
        void GetHeapUnuse();
        void heapInfo(unsigned long&, unsigned long&, unsigned long&);
        void GetTail();
        void GetTop();
    };

    CMemory();

    void Init();
    void Quit();
    void Frame();
    void HeapWalker();
    void Draw();
    void SetGroup(void*, int);
    CStage* CreateStage(unsigned long, char*, int);
    void DestroyStage(CMemory::CStage*);
    void _Alloc(unsigned long, CMemory::CStage*, char*, int, int);
    void Free(void*);
    void IncHeapWalkerLevel();
    void DecHeapWalkerLevel();
    void CopyToAMemory(void*, void*, unsigned long);
    void CopyFromAMemory(void*, void*, unsigned long);
    void CopyToAMemorySync(void*, void*, unsigned long);
    void CopyFromAMemorySync(void*, void*, unsigned long);
    void IsCopyCompleted(int);
};

class CAmemCache
{
public:
    enum TYPE
    {
        TODO,
    };

    CAmemCache();
    ~CAmemCache();
    void Destroy(CMemory::CStage*);
    void GetData(CMemory::CStage*, char*, int);
    void SetData(void*, int);
    void IsEnable();
    void Init();
};

class CAmemCacheSet
{
public:
    void Init(char*, CMemory::CStage*, CMemory::CStage*, int,
              unsigned char (*)(unsigned long), unsigned long,
              unsigned char (*)(unsigned long), unsigned long,
              unsigned char (*)(unsigned long), unsigned long);
    void SetRStage(CMemory::CStage*);
    void Destroy();
    void DestroyCache(int);
    void RefCnt0Up(int);
    void AmemSetLock();
    void AmemGetLock();
    void AmemAlloc(int);
    void AmemPrev();
    void GetFree();
    void GetData(short, char*, int);
    int SetData(void*, int, CAmemCache::TYPE, int);
    unsigned int IsEnable(short);
    void AddRef(short);
    void Release(short);
    void AmemFreeLowPrio(int);
    void CacheClear();
    void CalcPrio();
    int AmemGetFreeSize();
    void RefCnt0Clear();
    void RefCnt0Compare();
    void AssertCache();
    void DumpCache();
};

void* operator new(unsigned long size, CMemory::CStage* stage, char* file, int line);
void* operator new[](unsigned long size, CMemory::CStage* stage, char* file, int line);

extern CMemory Memory;

#endif // _FFCC_MEMORY_H_
