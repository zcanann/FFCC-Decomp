#include "ffcc/memory.h"

static char s_memory_cpp[] = "memory.cpp";
extern void* PTR_PTR_s_CMemory_801e8488;
extern CMemory Memory;

/*
 * --INFO--
 * PAL Address: 0x8001FD8C
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* operator new(unsigned long size, CMemory::CStage* stage, char* file, int line)
{
    if (file == (char*)nullptr) {
        file = s_memory_cpp;
    }
    return stage->alloc(size, file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8001FE54
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_memory_cpp(void)
{
    *reinterpret_cast<void**>(&Memory) = &PTR_PTR_s_CMemory_801e8488;
}

/*
 * --INFO--
 * PAL Address: 0x8001FD4C
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* operator new[](unsigned long size, CMemory::CStage* stage, char* file, int line)
{
    if (file == (char*)nullptr) {
        file = s_memory_cpp;
    }
    return stage->alloc(size, file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8001FC24
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void operator delete(void* ptr) throw()
{
    if (ptr != (void*)nullptr) {
        Memory.Free(ptr);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001FAFC
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void operator delete[](void* ptr) throw()
{
    if (ptr != (void*)nullptr) {
        Memory.Free(ptr);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CheckSum(void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMemory::CMemory()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::Frame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::HeapWalker()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::Draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::SetGroup(void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMemory::CStage* CMemory::CreateStage(unsigned long, char*, int)
{
	return (CMemory::CStage*)nullptr;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::DestroyStage(CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::_Alloc(unsigned long, CMemory::CStage*, char*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::Free(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::IncHeapWalkerLevel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::DecHeapWalkerLevel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CopyToAMemory(void*, void*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CopyFromAMemory(void*, void*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CopyToAMemorySync(void*, void*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CopyFromAMemorySync(void*, void*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::IsCopyCompleted(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::initBlock()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::quitBlock()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void* CMemory::CStage::alloc(unsigned long, char*, unsigned long, int)
{
	return (void*)nullptr;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::setDefaultParam(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::resDefaultParam()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::setParam(void*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::free(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::heapWalker(int, void*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::drawHeapBar(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::drawHeapTitle(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::GetHeapUnuse()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCache::Destroy(CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCache::GetData(CMemory::CStage*, char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCache::SetData(void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::Init(char*, CMemory::CStage*, CMemory::CStage*, int, unsigned char (*) (unsigned long), unsigned long, unsigned char (*) (unsigned long), unsigned long, unsigned char (*) (unsigned long), unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::SetRStage(CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::DestroyCache(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::RefCnt0Up(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::AmemSetLock()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::AmemGetLock()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::AmemAlloc(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::AmemPrev()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::GetFree()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::GetData(short, char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::SetData(void*, int, CAmemCache::TYPE, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::IsEnable(short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCache::IsEnable()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::AddRef(short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::Release(short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::AmemFreeLowPrio(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::CacheClear()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::CalcPrio()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::AmemGetFreeSize()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::RefCnt0Clear()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::RefCnt0Compare()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::AssertCache()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::DumpCache()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::heapInfo(unsigned long&, unsigned long&, unsigned long&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAmemCache::CAmemCache()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAmemCache::~CAmemCache()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCache::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::GetTail()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMemory::CStage::GetTop()
{
	// TODO
}
