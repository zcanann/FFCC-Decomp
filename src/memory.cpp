#include "ffcc/memory.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/stopwatch.h"
#include "ffcc/system.h"
#include "dolphin/os/OSMemory.h"
#include <string.h>

static char s_memory_cpp[] = "memory.cpp";
extern void* PTR_PTR_s_CMemory_801e8488;
extern CMemory Memory;
extern char DAT_801d6648[];
extern char DAT_801d6a7c[];
extern char DAT_801d6c58[];
extern char DAT_801d6c88[];
extern char DAT_801d6c98[];
extern "C" void Printf__7CSystemFPce(CSystem* system, char* format, ...);
extern "C" int DMAEntry__9CRedSoundFiiiiiPFPv_vPv(
    void*, int, int, int, int, int, void (*)(void*), void*);
extern "C" int DMACheck__9CRedSoundFi(void*, int);
extern "C" int __cntlzw(unsigned int);

static int calcCacheChecksum(const unsigned char* data, unsigned int size)
{
    int checksum = 0x12345678;
    unsigned int blockCount = size >> 3;
    while (blockCount != 0) {
        checksum += data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7];
        data += 8;
        blockCount--;
    }

    unsigned int remain = size & 7;
    while (remain != 0) {
        checksum += *data;
        data++;
        remain--;
    }

    return checksum;
}

static int stageGetAllocationMode(CMemory::CStage* stage)
{
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 0x10C);
}

static int stageGetHeapHead(CMemory::CStage* stage)
{
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 0x110);
}

static void stageSetHeapHead(CMemory::CStage* stage, int value)
{
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 0x110) = value;
}

static char* stageGetSourceName(CMemory::CStage* stage)
{
    return reinterpret_cast<char*>(reinterpret_cast<unsigned char*>(stage) + 0x10);
}

static bool stageHasUnfreedBlocks(CMemory::CStage* stage)
{
    int heapHead = stageGetHeapHead(stage);
    int node = *reinterpret_cast<int*>(heapHead + 8);
    while ((*reinterpret_cast<unsigned char*>(node + 2) & 2) == 0) {
        if ((*reinterpret_cast<unsigned char*>(node + 2) & 4) != 0) {
            return true;
        }
        node = *reinterpret_cast<int*>(node + 8);
    }
    return false;
}

static void stageReleaseMode2Buffer(CMemory::CStage* stage)
{
    int ptr = stageGetHeapHead(stage);
    if (ptr != 0) {
        if (ptr != 0x10) {
            operator delete(reinterpret_cast<void*>(ptr));
        }
        stageSetHeapHead(stage, 0);
    }
}

static void stageMoveToPoolList(CMemory* memory, CMemory::CStage* stage)
{
    unsigned char* stageBytes = reinterpret_cast<unsigned char*>(stage);
    int mode = stageGetAllocationMode(stage);
    int modeListBase = reinterpret_cast<int>(memory) + mode * 0x27D8 + 4;

    *reinterpret_cast<int*>(*reinterpret_cast<int*>(stageBytes) + 4) = *reinterpret_cast<int*>(stageBytes + 4);
    **reinterpret_cast<int**>(stageBytes + 4) = *reinterpret_cast<int*>(stageBytes);
    *reinterpret_cast<int*>(stageBytes + 4) = *reinterpret_cast<int*>(modeListBase + 0x130);
    *reinterpret_cast<int*>(modeListBase + 0x130) = reinterpret_cast<int>(stage);
}

static void stageDestroyInternal(CMemory::CStage* stage)
{
    if (stageGetAllocationMode(stage) == 2) {
        stageReleaseMode2Buffer(stage);
        return;
    }

    if (stageHasUnfreedBlocks(stage)) {
        Printf__7CSystemFPce(&System, DAT_801d6a7c, stageGetSourceName(stage));
        stage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
    }
}

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
void operator delete(void* ptr)
{
    if (ptr != (void*)nullptr) {
        unsigned char* mem = reinterpret_cast<unsigned char*>(ptr);
        if ((*reinterpret_cast<short*>(mem - 0x40) != 0x4b41) ||
            (*reinterpret_cast<short*>(mem - 2) != 0x4d49)) {
            Printf__7CSystemFPce(&System, DAT_801d6648, ptr, mem - 0x26, *reinterpret_cast<unsigned short*>(mem - 0x28));
        }

        mem[-0x3e] &= 0xfb;

        int blockPrev = *reinterpret_cast<int*>(mem - 0x38);
        if ((*(reinterpret_cast<unsigned char*>(blockPrev) + 2) & 4) == 0) {
            *reinterpret_cast<int*>(mem - 0x30) =
                *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockPrev) + 0x10) +
                *reinterpret_cast<int*>(mem - 0x30) + 0x40;
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockPrev) + 8) + 4) =
                reinterpret_cast<int>(mem) - 0x40;
            *reinterpret_cast<int*>(mem - 0x38) =
                *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockPrev) + 8);
        }

        int blockNext = *reinterpret_cast<int*>(mem - 0x3c);
        if ((*(reinterpret_cast<unsigned char*>(blockNext) + 2) & 4) == 0) {
            *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockNext) + 0x10) =
                *reinterpret_cast<int*>(mem - 0x30) +
                *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockNext) + 0x10) + 0x40;
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x3c) + 8) = *reinterpret_cast<int*>(mem - 0x38);
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 4) = *reinterpret_cast<int*>(mem - 0x3c);
        }

        *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x34) + 0x124) -= 1;
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
void operator delete[](void* ptr)
{
    if (ptr != (void*)nullptr) {
        unsigned char* mem = reinterpret_cast<unsigned char*>(ptr);
        if ((*reinterpret_cast<short*>(mem - 0x40) != 0x4b41) ||
            (*reinterpret_cast<short*>(mem - 2) != 0x4d49)) {
            Printf__7CSystemFPce(&System, DAT_801d6648, ptr, mem - 0x26, *reinterpret_cast<unsigned short*>(mem - 0x28));
        }

        mem[-0x3e] &= 0xfb;

        int blockPrev = *reinterpret_cast<int*>(mem - 0x38);
        if ((*(reinterpret_cast<unsigned char*>(blockPrev) + 2) & 4) == 0) {
            *reinterpret_cast<int*>(mem - 0x30) =
                *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockPrev) + 0x10) +
                *reinterpret_cast<int*>(mem - 0x30) + 0x40;
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockPrev) + 8) + 4) =
                reinterpret_cast<int>(mem) - 0x40;
            *reinterpret_cast<int*>(mem - 0x38) =
                *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockPrev) + 8);
        }

        int blockNext = *reinterpret_cast<int*>(mem - 0x3c);
        if ((*(reinterpret_cast<unsigned char*>(blockNext) + 2) & 4) == 0) {
            *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockNext) + 0x10) =
                *reinterpret_cast<int*>(mem - 0x30) +
                *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockNext) + 0x10) + 0x40;
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x3c) + 8) = *reinterpret_cast<int*>(mem - 0x38);
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 4) = *reinterpret_cast<int*>(mem - 0x3c);
        }

        *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x34) + 0x124) -= 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001FDCC
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CheckSum(void* data, int size)
{
    unsigned int checksum = 0x12345678;
    unsigned char* bytes = reinterpret_cast<unsigned char*>(data);

    if (size != 0) {
        unsigned int blockCount = static_cast<unsigned int>(size) >> 3;
        if (blockCount != 0) {
            do {
                checksum += bytes[0] + bytes[1] + bytes[2] + bytes[3] + bytes[4] + bytes[5] + bytes[6] + bytes[7];
                bytes += 8;
                blockCount--;
            } while (blockCount != 0);

            size &= 7;
            if (size == 0) {
                return checksum;
            }
        }

        do {
            checksum += *bytes;
            bytes++;
            size--;
        } while (size != 0);
    }

    return checksum;
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
 * PAL Address: 0x8001F8F0
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::Init()
{
    int arenaLo = reinterpret_cast<int>(OSGetArenaLo());
    OSInitAlloc(OSGetArenaLo(), reinterpret_cast<void*>(arenaLo + 0x14000), 1);

    unsigned char* modeBase = reinterpret_cast<unsigned char*>(this) + 4;
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x7794) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x7798) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x779C) = 0;

    for (int pass = 0; pass < 3; pass++) {
        if ((pass != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) {
            if ((pass == 0) || (pass == 1)) {
                unsigned int arenaHi = reinterpret_cast<unsigned int>(OSGetArenaHi());
                if (pass == 0) {
                    *reinterpret_cast<unsigned int*>(modeBase + 8) = 0x81780000;
                    unsigned int lo = reinterpret_cast<unsigned int>(OSGetArenaLo());
                    *reinterpret_cast<unsigned int*>(modeBase + 0xC) = (lo + 0x1403F) & ~0x3FU;
                } else {
                    *reinterpret_cast<unsigned int*>(modeBase + 8) = arenaHi & ~0x3FU;
                    *reinterpret_cast<unsigned int*>(modeBase + 0xC) = 0x81800000;
                }

                int top = *reinterpret_cast<int*>(modeBase + 8);
                int bottom = *reinterpret_cast<int*>(modeBase + 0xC);
                if (0 < (top - bottom)) {
                    memset(reinterpret_cast<void*>(bottom), 0xAB, top - bottom);
                }
            } else {
                *reinterpret_cast<int*>(modeBase + 8) = 0x7FC000;
                *reinterpret_cast<int*>(modeBase + 0xC) = 0x4000;
            }

            *reinterpret_cast<unsigned char**>(modeBase) = modeBase;
            *reinterpret_cast<unsigned char**>(modeBase + 4) = modeBase;
            *reinterpret_cast<unsigned char**>(modeBase + 0x130) = modeBase + 600;

            unsigned char* stageBase = modeBase;
            for (int index = 0; index < 32; index += 4) {
                unsigned char* next;

                if (index == 0x1F) {
                    next = modeBase + 300;
                } else {
                    next = modeBase + (index + 1) * 300 + 600;
                }
                *reinterpret_cast<unsigned char**>(stageBase + 0x25C) = next;

                if (index == 0x1E) {
                    next = modeBase + 300;
                } else {
                    next = modeBase + (index + 2) * 300 + 600;
                }
                *reinterpret_cast<unsigned char**>(stageBase + 0x388) = next;

                if (index == 0x1D) {
                    next = modeBase + 300;
                } else {
                    next = modeBase + (index + 3) * 300 + 600;
                }
                *reinterpret_cast<unsigned char**>(stageBase + 0x4B4) = next;

                if (index == 0x1C) {
                    next = modeBase + 300;
                } else {
                    next = modeBase + (index + 4) * 300 + 600;
                }
                *reinterpret_cast<unsigned char**>(stageBase + 0x5E0) = next;

                stageBase += 0x4B0;
            }
        }

        modeBase += 0x27D8;
    }

    CStage* stage = CreateStage(0x2000, DAT_801d6c88, 0);
    *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(this) + 0x778C) = stage;

    stage = CreateStage(0x4000, DAT_801d6c98, 0);
    *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(this) + 0x7790) = stage;
}

/*
 * --INFO--
 * PAL Address: 0x8001F198
 * PAL Size: 1832b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::Quit()
{
    CStage* activeStage = *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(this) + 0x7790);
    stageDestroyInternal(activeStage);
    stageMoveToPoolList(this, activeStage);

    for (int pass = 0; pass < 3; pass++) {
        if ((pass != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) {
            unsigned char* listHeadBytes = reinterpret_cast<unsigned char*>(this) + 4 + pass * 0x110;
            CStage* listHead = reinterpret_cast<CStage*>(listHeadBytes);
            CStage* stage = *reinterpret_cast<CStage**>(listHeadBytes + 4);

            while (stage != listHead) {
                CStage* next = *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(stage) + 4);
                if ((pass != 0) ||
                    (stage != *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(this) + 0x778C))) {
                    Printf__7CSystemFPce(&System, DAT_801d6c58, stageGetSourceName(stage));
                    stageDestroyInternal(stage);
                    stageMoveToPoolList(this, stage);
                }
                stage = next;
            }
        }
    }

    CStage* rootStage = *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(this) + 0x778C);
    stageDestroyInternal(rootStage);
    stageMoveToPoolList(this, rootStage);
}

/*
 * --INFO--
 * PAL Address: 0x8001F118
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::Frame()
{
    bool activeInput = false;
    unsigned short trigger;

    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        activeInput = true;
    }

    if (activeInput) {
        trigger = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        trigger = Pad._8_2_;
    }

    if ((trigger & 0x200) != 0) {
        unsigned int showHeap = static_cast<unsigned int>(
            __cntlzw(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x7798)));
        *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x7798) =
            (showHeap >> 5) & 0xFF;
    }
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
 * PAL Address: 0x8001EC80
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::SetGroup(void* ptr, int group)
{
    unsigned char* header = reinterpret_cast<unsigned char*>(ptr) - 0x3e;
    *header = (*header & 0x0F) | (static_cast<unsigned char>(group) << 4);
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
 * PAL Address: 0x8001E834
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::DestroyStage(CMemory::CStage* stage)
{
    stageDestroyInternal(stage);
    stageMoveToPoolList(this, stage);
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
 * PAL Address: 0x8001E6E0
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::IncHeapWalkerLevel()
{
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x7794) += 1;
}

/*
 * --INFO--
 * PAL Address: 0x8001E6D0
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::DecHeapWalkerLevel()
{
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x7794) -= 1;
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
 * PAL Address: 0x8001E2E4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::CStage::setDefaultParam(unsigned long defaultParam)
{
    *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(this) + 0x108) =
        defaultParam;
}

/*
 * --INFO--
 * PAL Address: 0x8001E2D8
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::CStage::resDefaultParam()
{
    *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(this) + 0x108) =
        static_cast<unsigned long>(-1);
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
 * PAL Address: 0x8001DF88
 * PAL Size: 848b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMemory::CStage::heapWalker(int flag, void*, unsigned long group)
{
    int mode = stageGetAllocationMode(this);
    int node = stageGetHeapHead(this);

    if (mode != 2) {
        node = *reinterpret_cast<int*>(node + 8);
    }

    if (flag == -1) {
        Printf__7CSystemFPce(&System, "***** HEAP WALKER *****\n");
        Printf__7CSystemFPce(&System, "Stage Name : %s\n", stageGetSourceName(this));
        Printf__7CSystemFPce(&System,
                             " No Flag Level  Size  Total  Address   Top      Tail     Source\n");
        Printf__7CSystemFPce(&System,
                             "-----------------------------------------------------------------\n");
    }

    int totalSize = 0;
    int freeCount = 0;
    int usedCount = 0;
    int freeSize = 0;
    int usedSize = 0;

    if (mode == 2) {
        int top = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 8);
        int tail = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 12);
        int count = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x120);

        for (int i = 0; i <= count; i++) {
            int blockTail = (i == count) ? tail : *reinterpret_cast<int*>(node + 4);
            int size = blockTail - top;
            if (size != 0) {
                if ((flag & 1) != 0) {
                    Printf__7CSystemFPce(&System,
                                         "%3d %s %5d %7d %08x %08x %08x %-16.16s %04x\n",
                                         freeCount, "FREE", 0, size, totalSize, 0, 0, "-------", 0);
                }
                usedSize += size;
                totalSize += size;
                freeCount++;
            }

            if (i < count) {
                int used = *reinterpret_cast<int*>(node + 8) - *reinterpret_cast<int*>(node + 4);
                if ((flag & 2) != 0) {
                    Printf__7CSystemFPce(
                        &System, "%3d %s %5d %7d %08x %08x %08x %-16.16s %04x\n", usedCount, "USED",
                        *reinterpret_cast<unsigned char*>(node + 3), used, totalSize,
                        *reinterpret_cast<int*>(node + 4), 0, reinterpret_cast<char*>(node + 0x1A),
                        *reinterpret_cast<unsigned short*>(node + 0x18));
                }
                freeSize += used;
                totalSize += used;
                top = blockTail + used;
                usedCount++;
            }

            node += 0x40;
        }
    } else {
        while ((*reinterpret_cast<unsigned char*>(node + 2) & 2) == 0) {
            unsigned char nodeFlags = *reinterpret_cast<unsigned char*>(node + 2);
            int nodeGroup = *reinterpret_cast<int*>(node + 0x14);
            if ((group == static_cast<unsigned long>(-1)) || (static_cast<unsigned long>(nodeGroup) == group)) {
                bool isUsed = (nodeFlags & 4) != 0;
                if ((isUsed && ((flag & 2) != 0)) || (!isUsed && ((flag & 1) != 0))) {
                    const char* kind = isUsed ? "USED" : "FREE";
                    unsigned char level = isUsed ? *reinterpret_cast<unsigned char*>(node + 3) : 0;
                    const char* source = isUsed ? reinterpret_cast<char*>(node + 0x1A) : "-------";
                    unsigned short line = isUsed ? *reinterpret_cast<unsigned short*>(node + 0x18) : 0;
                    int index = isUsed ? usedCount : freeCount;
                    Printf__7CSystemFPce(
                        &System, "%3d %s %5d %7d %08x %08x %08x %-16.16s %04x\n", index, kind, level,
                        *reinterpret_cast<int*>(node + 0x10), totalSize, node + 0x40,
                        *reinterpret_cast<int*>(node + 4), source, line);
                }
            }

            if ((group == static_cast<unsigned long>(-1)) || (static_cast<unsigned long>(nodeGroup) == group)) {
                if ((nodeFlags & 4) == 0) {
                    freeCount++;
                    usedSize += *reinterpret_cast<int*>(node + 0x10);
                } else {
                    usedCount++;
                    freeSize += *reinterpret_cast<int*>(node + 0x10);
                }
            }

            totalSize += *reinterpret_cast<int*>(node + 8) - node;
            node = *reinterpret_cast<int*>(node + 8);
        }
    }

    if (flag == -1) {
        Printf__7CSystemFPce(&System,
                             "-----------------------------------------------------------------\n");
        Printf__7CSystemFPce(&System, "USE  : %d  UNUSE : %d\n", freeSize, usedSize);
    }

    return freeSize;
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
 * PAL Address: 0x8001D468
 * PAL Size: 576b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::DestroyCache(int index)
{
    unsigned char* bytes = reinterpret_cast<unsigned char*>(this);
    unsigned char* entry =
        reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(bytes + 0x58) + index * 0x1C);
    int cacheData = *reinterpret_cast<int*>(entry + 0x00);
    int workData = *reinterpret_cast<int*>(entry + 0x04);

    if (entry[0x1A] == 0) {
        if (workData != 0) {
            operator delete(reinterpret_cast<void*>(workData));
        }
        *reinterpret_cast<int*>(entry + 0x00) = 0;
        *reinterpret_cast<int*>(entry + 0x04) = 0;
    } else {
        if (cacheData != 0) {
            operator delete(reinterpret_cast<void*>(cacheData));
            *reinterpret_cast<int*>(entry + 0x00) = 0;
        }
        if (workData != 0) {
            *reinterpret_cast<int*>(entry + 0x04) = 0;
        }
    }

    *reinterpret_cast<unsigned short*>(entry + 0x18) = 0;
    *reinterpret_cast<unsigned short*>(entry + 0x0C) = 0;
    entry[0x0E] = 0;
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
 * PAL Address: 0x8001D45C
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::AmemSetLock()
{
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x38) =
        *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x30);
}

/*
 * --INFO--
 * PAL Address: 0x8001D44C
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::AmemGetLock()
{
    int lock = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x38);
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x34) = lock;
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x30) = lock;
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
 * PAL Address: 0x8001D440
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::AmemPrev()
{
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x30) =
        *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x34);
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
 * PAL Address: 0x8001CED0
 * PAL Size: 936b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CAmemCacheSet::SetData(void* src, int size, CAmemCache::TYPE type, int dmaCopy)
{
    unsigned char* bytes = reinterpret_cast<unsigned char*>(this);
    short index = -1;
    short i = 0;
    int cacheCount = *reinterpret_cast<int*>(bytes + 0x3C);
    int tableBase = *reinterpret_cast<int*>(bytes + 0x58);

    while (i < cacheCount) {
        unsigned char* entry = reinterpret_cast<unsigned char*>(tableBase + i * 0x1C);
        if (entry[0x0E] == 0) {
            index = i;
            break;
        }
        i++;
    }

    if (index == -1) {
        return -1;
    }

    unsigned char* entry = reinterpret_cast<unsigned char*>(tableBase + index * 0x1C);
    unsigned int allocSize = static_cast<unsigned int>(size + 0x1F) & ~0x1F;
    entry[0x0E] = 1;
    entry[0x0F] = static_cast<unsigned char>(type);
    entry[0x1A] = static_cast<char>(dmaCopy);
    *reinterpret_cast<short*>(entry + 0x0C) = 0;

    if (dmaCopy == 0) {
        CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(bytes + 0x00);
        int allocated = 0;
        do {
            allocated = reinterpret_cast<int>(stage->alloc(allocSize, s_memory_cpp, 0x807, 1));
            *reinterpret_cast<int*>(entry + 0x04) = allocated;
            if (allocated == 0) {
                AmemFreeLowPrio(allocSize);
            }
        } while (allocated == 0);
    } else {
        *reinterpret_cast<int*>(bytes + 0x34) = *reinterpret_cast<int*>(bytes + 0x30);
        *reinterpret_cast<int*>(bytes + 0x30) += allocSize;
        *reinterpret_cast<int*>(entry + 0x04) = *reinterpret_cast<int*>(bytes + 0x34);
    }

    *reinterpret_cast<int*>(entry + 0x00) = 0;
    *reinterpret_cast<unsigned int*>(entry + 0x08) = allocSize;
    *reinterpret_cast<int*>(entry + 0x14) = calcCacheChecksum(reinterpret_cast<unsigned char*>(src), allocSize);

    if (entry[0x1A] == 0) {
        memcpy(reinterpret_cast<void*>(*reinterpret_cast<int*>(entry + 0x04)), src, *reinterpret_cast<int*>(entry + 0x08));
        DCFlushRange(reinterpret_cast<void*>(*reinterpret_cast<int*>(entry + 0x04)), allocSize);
    } else {
        int dmaId = DMAEntry__9CRedSoundFiiiiiPFPv_vPv(
            &Sound, 0, 0, reinterpret_cast<int>(src), *reinterpret_cast<int*>(entry + 0x04), *reinterpret_cast<int*>(entry + 0x08), 0,
            0);

        CStopWatch watch((char*)-1);
        watch.Start();
        while (DMACheck__9CRedSoundFi(&Sound, dmaId) != 0) {
            watch.Stop();
            watch.Get();
            watch.Start();
        }
    }

    return index;
}

/*
 * --INFO--
 * PAL Address: 0x8001CEB0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CAmemCacheSet::IsEnable(short index)
{
    int table = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x58);
    unsigned int value = *reinterpret_cast<unsigned int*>(table + index * 0x1c);
    return ((0u - value) | value) >> 31;
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
 * PAL Address: 0x8001C800
 * PAL Size: 1012b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::AmemFreeLowPrio(int size)
{
    unsigned char* bytes = reinterpret_cast<unsigned char*>(this);
    unsigned int bestPriority = 0x7ffffff1;
    int currentSize = size;

    while (true) {
        int cacheCount = *reinterpret_cast<int*>(bytes + 0x3C);
        unsigned char* bestEntry = 0;

        for (int i = 0; i < cacheCount; i++) {
            unsigned char* entry = reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(bytes + 0x58) + i * 0x1C);
            if (entry[0x0E] != 0 && *reinterpret_cast<short*>(entry + 0x0C) == 0 && entry[0x1A] != 0 &&
                *reinterpret_cast<int*>(entry + 0x00) != 0 && currentSize <= *reinterpret_cast<int*>(entry + 0x08) &&
                *reinterpret_cast<unsigned int*>(entry + 0x10) < bestPriority) {
                bestEntry = entry;
                bestPriority = *reinterpret_cast<unsigned int*>(entry + 0x10);
            }
        }

        if (bestEntry != 0) {
            int cachedData = *reinterpret_cast<int*>(bestEntry + 0x00);
            if (cachedData != 0) {
                operator delete(reinterpret_cast<void*>(cachedData));
            }
            *reinterpret_cast<int*>(bestEntry + 0x00) = 0;
        }

        CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(bytes + 0x00);
        int allocated = reinterpret_cast<int>(stage->alloc(size, s_memory_cpp, 0x86D, 1));
        if (allocated != 0) {
            operator delete(reinterpret_cast<void*>(allocated));
            return;
        }

        if (currentSize != 0) {
            currentSize -= size / 2;
            if (currentSize < 0) {
                currentSize = 0;
            }
            continue;
        }

        if (bestPriority == 0xFFFFFFFF) {
            unsigned char (*releaseCheck)(unsigned long) =
                *reinterpret_cast<unsigned char (**)(unsigned long)>(bytes + 0x40);
            if (releaseCheck != 0 && releaseCheck(*reinterpret_cast<unsigned long*>(bytes + 0x44)) != 0) {
                continue;
            }
            unsigned char (*releaseAction)(unsigned long) =
                *reinterpret_cast<unsigned char (**)(unsigned long)>(bytes + 0x48);
            releaseAction(*reinterpret_cast<unsigned long*>(bytes + 0x4C));
            bestPriority = 0xFFFFFFFF;
            continue;
        }
    }
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
 * PAL Address: 0x8001C630
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CAmemCacheSet::AmemGetFreeSize()
{
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x2c) -
           *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x30);
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
