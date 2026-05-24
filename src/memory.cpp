#include "ffcc/memory.h"
#include "ffcc/chara.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/RedSound/RedSound.h"
#include "ffcc/sound.h"
#include "ffcc/stopwatch.h"
#include "ffcc/system.h"
#include <PowerPC_EABI_Support/Runtime/MWCPlusLib.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "dolphin/os/OSMemory.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CMemory Memory;

static const char s_memory_cpp[] = "memory.cpp";
extern "C" const char DAT_801d669c[] =
    "===================================================================\n"
    "===================================================================\n"
    "                          GetData  TimeOut\n"
    "===================================================================\n"
    "===================================================================\n";
extern "C" const char DAT_801d67d8[40] =
    "\x83\x71\x81\x5b\x83\x76\x82\xaa\x88\xd9\x8f\xed\x82\xc8\x82\xcc"
    "\x82\xc5\x95\x60\x89\xe6\x82\xf0\x92\x86\x8e\x7e\x82\xb5\x82\xdc"
    "\x82\xb7\x81\x42\n";
static const char s_drawHeapTitleFmt[] = "%4d %4d %4d";
static const char s_heapWalkerStageNameFmt[] = "Stage Name = %s\n";
static const char s_heapWalkerHeaderFmt[] =
    "No  Flag Level Size    Total   Address  Prev     Next     Name                     Line \n";
static const char s_heapWalkerSeparator[] = {
    '-', '-', '-', ' ', '-', '-', '-', '-', ' ', '-', '-', '-',
    '-', '-', ' ', '-', '-', '-', '-', '-', '-', '-', ' ', '-',
    '-', '-', '-', '-', '-', '-', ' ', '-', '-', '-', '-', '-',
    '-', '-', '-', ' ', '-', '-', '-', '-', '-', '-', '-', '-',
    ' ', '-', '-', '-', '-', '-', '-', '-', '-', ' ', '-', '-',
    '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-',
    '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', ' ', '-'
};
extern const char s_AMEM_CACHE_DUMP_801D64F4[];
extern const char s_amemCacheEntryFmt_801D6580[];
extern const char s_refCntCompareBanner_801D65B4[];
extern const char s_heapWalkerEntryFmt_801D68D8[];
extern const char s_heapWalkerUseUnuseFmt_801D6958[];
extern const char s_heapWalkerTitle_801D6BFC[];
extern const char s_heapWalkerUseFmt_801D6C0C[];
extern const char s_heapWalkerUnuseFmt_801D6C20[];
extern const char s_heapWalkerTotalFmt_801D6C30[];
extern const char s_amemCacheSeparator_8032F7C8[];
#define s_heapWalkerTitle s_heapWalkerTitle_801D6BFC
#define s_heapWalkerUseFmt s_heapWalkerUseFmt_801D6C0C
#define s_heapWalkerUnuseFmt s_heapWalkerUnuseFmt_801D6C20
#define s_heapWalkerTotalFmt s_heapWalkerTotalFmt_801D6C30
#define s_heapWalkerBanner DAT_8032f7e8
#define s_heapWalkerEntryFmt s_heapWalkerEntryFmt_801D68D8
#define s_heapWalkerUseUnuseFmt s_heapWalkerUseUnuseFmt_801D6958
#define s_amemCacheAddRefFmt s_AMEM_CACHE_DUMP_801D64F4
#define s_amemCacheSeparator s_amemCacheSeparator_8032F7C8
#define s_refCntCompareBanner s_refCntCompareBanner_801D65B4
#define s_amemCacheEntryFmt s_amemCacheEntryFmt_801D6580
#define s_amemCacheEntryPaddedFmt s_amemCacheEntryFmt_801D6580
extern char DAT_801d6648[];
extern char DAT_801d6a24[];
extern char DAT_801d6a7c[];
extern char s_copyFromAMemorySyncTimeout_801D6ABC[];
extern char DAT_801d6b7c[];
extern char DAT_801d6bb0[];
extern char DAT_801d6c58[];
extern char DAT_801d6c88[];
extern char DAT_801d6c98[];
extern char DAT_801d6bdc[];
extern char DAT_801d6bec[];
extern char DAT_8032f7d4[4];
extern char DAT_8032f7e8[];
extern char DAT_8032f808[];
extern const char* s_amemCacheTypeNames_801E8470[];
extern const char* s_amemCacheStateNames_8032E410[];
extern const float FLOAT_8032f7d8 = 9000.0f;
extern const float FLOAT_8032f7dc = 0.0f;
extern float FLOAT_8032f7fc;
extern float FLOAT_8032f800;
extern float FLOAT_8032f804;
extern const double DOUBLE_8032F7E0 = 4503601774854144.0;
extern unsigned int s_heapBarColors_801D64A8[];
long long DAT_8032ec58;
extern char DAT_8032f7e8[];
extern char DAT_8032f808[];
static int stageGetAllocationMode(CMemory::CStage* stage)
{
    return stage->m_allocationMode;
}

static int stageGetHeapHead(CMemory::CStage* stage)
{
    return stage->m_heapHead;
}

static void stageSetHeapHead(CMemory::CStage* stage, int value)
{
    stage->m_heapHead = value;
}

static char* stageGetSourceName(CMemory::CStage* stage)
{
    return stage->m_allocationSourceStr;
}

static inline CAmemCache& cacheEntryAt(CAmemCacheSet* cacheSet, int index)
{
    return cacheSet->m_cacheTable[index];
}

static inline const CAmemCache& cacheEntryAt(const CAmemCacheSet* cacheSet, int index)
{
    return cacheSet->m_cacheTable[index];
}

static inline const char* cacheStateName(const CAmemCache& entry)
{
    return s_amemCacheStateNames_8032E410[entry.m_inUse == 0];
}

static inline const char* cacheTypeName(const CAmemCache& entry)
{
    return s_amemCacheTypeNames_801E8470[entry.m_type];
}

static inline CRedSound* RedSound(CSound* sound)
{
    return reinterpret_cast<CRedSound*>(reinterpret_cast<unsigned char*>(sound) + 8);
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
            operator delete[](reinterpret_cast<void*>(ptr - 0x10));
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
        System.Printf(const_cast<char*>(DAT_801d6a7c), stageGetSourceName(stage));
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
    return stage->alloc(size, file != (char*)nullptr ? file : DAT_8032f7d4, line, 0);
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
    return stage->alloc(size, file != (char*)nullptr ? file : DAT_8032f7d4, line, 0);
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
        int mem = reinterpret_cast<int>(ptr);
        if ((*reinterpret_cast<short*>(mem - 0x40) != 0x4b41) ||
            (*reinterpret_cast<short*>(mem - 2) != 0x4d49)) {
            System.Printf(const_cast<char*>(DAT_801d6648), ptr, mem - 0x26, *reinterpret_cast<unsigned short*>(mem - 0x28));
        }

        *reinterpret_cast<unsigned char*>(mem - 0x3e) &= 0xfb;

        if ((*reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(mem - 0x38) + 2) & 4) == 0) {
            *reinterpret_cast<int*>(mem - 0x30) =
                *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 0x10) +
                *reinterpret_cast<int*>(mem - 0x30) + 0x40;
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 8) + 4) =
                mem - 0x40;
            *reinterpret_cast<int*>(mem - 0x38) =
                *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 8);
        }

        int blockNext = *reinterpret_cast<int*>(mem - 0x3c);
        if ((*reinterpret_cast<unsigned char*>(blockNext + 2) & 4) == 0) {
            *reinterpret_cast<int*>(blockNext + 0x10) =
                *reinterpret_cast<int*>(mem - 0x30) +
                *reinterpret_cast<int*>(blockNext + 0x10) + 0x40;
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
        int mem = reinterpret_cast<int>(ptr);
        if ((*reinterpret_cast<short*>(mem - 0x40) != 0x4b41) ||
            (*reinterpret_cast<short*>(mem - 2) != 0x4d49)) {
            System.Printf(const_cast<char*>(DAT_801d6648), ptr, mem - 0x26, *reinterpret_cast<unsigned short*>(mem - 0x28));
        }

        *reinterpret_cast<unsigned char*>(mem - 0x3e) &= 0xfb;

        if ((*reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(mem - 0x38) + 2) & 4) == 0) {
            *reinterpret_cast<int*>(mem - 0x30) =
                *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 0x10) +
                *reinterpret_cast<int*>(mem - 0x30) + 0x40;
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 8) + 4) =
                mem - 0x40;
            *reinterpret_cast<int*>(mem - 0x38) =
                *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 8);
        }

        int blockNext = *reinterpret_cast<int*>(mem - 0x3c);
        if ((*reinterpret_cast<unsigned char*>(blockNext + 2) & 4) == 0) {
            *reinterpret_cast<int*>(blockNext + 0x10) =
                *reinterpret_cast<int*>(mem - 0x30) +
                *reinterpret_cast<int*>(blockNext + 0x10) + 0x40;
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
                checksum += bytes[0];
                checksum += bytes[1];
                checksum += bytes[2];
                checksum += bytes[3];
                checksum += bytes[4];
                checksum += bytes[5];
                checksum += bytes[6];
                checksum += bytes[7];
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
    m_heapWalkerLevel = 0;
    m_heapWalkerVisible = 0;
    m_defaultGroup = 0;

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

            CStage* stageBase = reinterpret_cast<CStage*>(modeBase + 0x258);
            for (int index = 0; index < 32; index++) {
                unsigned char* next;

                if (index == 0x1F) {
                    next = modeBase + 300;
                } else {
                    next = modeBase + (index + 1) * 300 + 600;
                }

                stageBase->m_next = reinterpret_cast<CStage*>(next);
                stageBase++;
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
            unsigned char* listHeadBytes = reinterpret_cast<unsigned char*>(this) + 4 + pass * 0x27D8;
            CStage* listHead = reinterpret_cast<CStage*>(listHeadBytes);
            CStage* stage = *reinterpret_cast<CStage**>(listHeadBytes + 4);

            while (stage != listHead) {
                CStage* next = *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(stage) + 4);
                if ((pass != 0) ||
                    (stage != *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(this) + 0x778C))) {
                    System.Printf(const_cast<char*>(DAT_801d6c58), stageGetSourceName(stage));
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
    bool activeInput;
    unsigned short trigger;

    activeInput = false;
    if (Pad._452_4_ == 0) {
        if (Pad._448_4_ == -1) {
            goto frame_input_done;
        }
    }
    activeInput = true;

frame_input_done:

    if (activeInput) {
        trigger = 0;
    } else {
        int port = 0;
        unsigned int clamped = (unsigned int)port & ~-((int)(__cntlzw(static_cast<unsigned int>(Pad._448_4_)) >> 5));
        trigger = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 0x36 + clamped * 0x54);
    }

    if ((trigger & 0x200) != 0) {
        unsigned int showHeap = static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(m_heapWalkerVisible)));
        m_heapWalkerVisible = static_cast<int>((showHeap >> 5) & 0xFF);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001EF90
 * PAL Size: 392b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::HeapWalker()
{
    System.Printf(const_cast<char*>(DAT_8032f7e8));
    System.Printf(const_cast<char*>(DAT_8032f808));
    System.Printf(const_cast<char*>(s_heapWalkerTitle));
    System.Printf(const_cast<char*>(DAT_8032f808));

    CStage* listHead = reinterpret_cast<CStage*>(reinterpret_cast<unsigned char*>(this) + 4);
    for (int mode = 0; mode < 3; mode++) {
        if ((mode != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) {
            CStage* stage = *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(listHead) + 4);
            while (stage != listHead) {
                stage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
                stage = *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(stage) + 4);
            }

            System.Printf(const_cast<char*>(DAT_8032f7e8));

            stage = *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(listHead) + 4);
            int useTotal = 0;
            int unuseTotal = 0;
            while (stage != listHead) {
                unsigned int useKB = static_cast<unsigned int>(
                    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 0xC) -
                    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 8))
                    >> 10;
                System.Printf(const_cast<char*>(s_heapWalkerUseFmt), useKB, stageGetSourceName(stage));
                useTotal += useKB;

                unsigned int unuseKB = static_cast<unsigned int>(
                    *reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 4) + 8) -
                    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 0xC))
                    >> 10;
                System.Printf(const_cast<char*>(s_heapWalkerUnuseFmt), unuseKB);
                stage = *reinterpret_cast<CStage**>(reinterpret_cast<unsigned char*>(stage) + 4);
                unuseTotal += unuseKB;
            }

            System.Printf(
                const_cast<char*>(s_heapWalkerTotalFmt), useTotal + unuseTotal, useTotal, unuseTotal);
        }

        listHead = reinterpret_cast<CStage*>(reinterpret_cast<unsigned char*>(listHead) + 0x27D8);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001EC94
 * PAL Size: 764b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::Draw()
{
    if (m_heapWalkerVisible == 0) {
        return;
    }

    Mtx orthoMtx;
    Mtx modelMtx;
    char line[0x104];

    C_MTXOrtho(orthoMtx, FLOAT_8032f7dc, FLOAT_8032f7fc, FLOAT_8032f7dc, FLOAT_8032f800, FLOAT_8032f7dc,
               FLOAT_8032f804);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXSetZCompLoc(GX_FALSE);
    _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, GX_PNMTX0);
    GXLoadTexMtxImm(modelMtx, GX_TEXMTX0, GX_MTX2x4);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    for (int pass = 0; pass < 2; pass++) {
        if (pass == 1) {
            Graphic.InitDebugString();
        }

        unsigned char* listHead = reinterpret_cast<unsigned char*>(this) + 4;
        int y = 0x20;
        int useTotalKB = 0;
        int unuseTotalKB = 0;

        for (int mode = 0; mode < 3; mode++) {
            if (((mode != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) && (mode != 2)) {
                CMemory::CStage* head = reinterpret_cast<CMemory::CStage*>(listHead);
                CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(listHead + 4);
                while (stage != head) {
                    if (pass == 0) {
                        stage->drawHeapBar(y);
                    } else {
                        stage->drawHeapTitle(y);
                        if (mode == 0) {
                            useTotalKB +=
                                static_cast<unsigned int>(
                                    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 0xC) -
                                    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 8)) >>
                                10;
                            unuseTotalKB +=
                                static_cast<unsigned int>(
                                    *reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) +
                                                                                  4) +
                                                           8) -
                                    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(stage) + 0xC)) >>
                                10;
                        }
                    }
                    y += 0xC;
                    stage = *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(stage) + 4);
                }
            }

            listHead += 0x27D8;
        }

        if (pass == 1) {
            sprintf(line, DAT_801d6bdc, useTotalKB, unuseTotalKB);
            Graphic.DrawDebugStringDirect(0x10, y, line, 8);

            int amemAnim = static_cast<int>(Chara.GetAmemAnimSize());
            int amemAnimKB = amemAnim / 1024;
            sprintf(line, DAT_801d6bec, amemAnimKB);
            Graphic.DrawDebugStringDirect(0x10, y + 0xC, line, 8);
        }
    }
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
    *header = (*header & 0x0F) | (group << 4);
}

/*
 * --INFO--
 * PAL Address: 0x8001EA28
 * PAL Size: 600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMemory::CStage* CMemory::CreateStage(unsigned long size, char* source, int mode)
{
    if ((mode != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) {
        unsigned int alignedSize = (size + 0x3F) & ~0x3FU;
        unsigned char* modeBase = reinterpret_cast<unsigned char*>(this) + 4 + mode * 0x27D8;
        CStage* stage = *reinterpret_cast<CStage**>(modeBase + 0x130);
        unsigned char* list = modeBase;

        if (stage == reinterpret_cast<CStage*>(modeBase + 300)) {
            System.Printf(const_cast<char*>(DAT_801d6b7c));
        } else {
            do {
                unsigned char* next = *reinterpret_cast<unsigned char**>(list + 4);
                if (static_cast<unsigned int>(*reinterpret_cast<int*>(list + 0xC)) + alignedSize <=
                    *reinterpret_cast<unsigned int*>(next + 8)) {
                    unsigned char* stageBytes = reinterpret_cast<unsigned char*>(stage);

                    *reinterpret_cast<CStage**>(modeBase + 0x130) =
                        *reinterpret_cast<CStage**>(stageBytes + 4);
                    *reinterpret_cast<unsigned char**>(stageBytes) = list;
                    *reinterpret_cast<unsigned char**>(stageBytes + 4) =
                        *reinterpret_cast<unsigned char**>(list + 4);
                    *reinterpret_cast<CStage**>(*reinterpret_cast<unsigned char**>(list + 4)) = stage;
                    *reinterpret_cast<CStage**>(list + 4) = stage;

                    *reinterpret_cast<int*>(stageBytes + 8) = *reinterpret_cast<int*>(list + 0xC);
                    *reinterpret_cast<unsigned int*>(stageBytes + 0xC) =
                        *reinterpret_cast<unsigned int*>(stageBytes + 8) + alignedSize;

                    if (source == (char*)nullptr) {
                        source = DAT_8032f7d4;
                    }
                    strcpy(reinterpret_cast<char*>(stageBytes + 0x10), source);
                    stage->m_allocationMode = mode;

                    if (mode != 2) {
                        unsigned char* fill = reinterpret_cast<unsigned char*>(
                            *reinterpret_cast<int*>(stageBytes + 8));
                        while (fill < reinterpret_cast<unsigned char*>(
                                          *reinterpret_cast<int*>(stageBytes + 0xC))) {
                            *fill = 0xCD;
                            fill++;
                        }

                        *reinterpret_cast<int*>(stageBytes + 0x110) =
                            *reinterpret_cast<int*>(stageBytes + 8);
                        *reinterpret_cast<int*>(stageBytes + 0x114) =
                            *reinterpret_cast<int*>(stageBytes + 0xC) - 0x40;

                        *reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(stageBytes + 0x110) + 2) = 5;
                        *reinterpret_cast<int*>(*reinterpret_cast<int*>(stageBytes + 0x110) + 4) = 0;
                        *reinterpret_cast<int*>(*reinterpret_cast<int*>(stageBytes + 0x110) + 8) =
                            *reinterpret_cast<int*>(stageBytes + 0x110) + 0x40;

                        *reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(stageBytes + 0x110) + 0x40) =
                            0x4B41;
                        *reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(stageBytes + 0x110) + 0x7E) =
                            0x4D49;
                        *reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(stageBytes + 0x110) + 0x42) = 0;
                        *reinterpret_cast<int*>(*reinterpret_cast<int*>(stageBytes + 0x110) + 0x50) =
                            *reinterpret_cast<int*>(stageBytes + 0x114) -
                            (*reinterpret_cast<int*>(stageBytes + 0x110) + 0x80);
                        *reinterpret_cast<int*>(*reinterpret_cast<int*>(stageBytes + 0x110) + 0x44) =
                            *reinterpret_cast<int*>(stageBytes + 0x110);
                        *reinterpret_cast<int*>(*reinterpret_cast<int*>(stageBytes + 0x110) + 0x48) =
                            *reinterpret_cast<int*>(stageBytes + 0x114);

                        *reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(stageBytes + 0x114) + 2) = 6;
                        *reinterpret_cast<int*>(*reinterpret_cast<int*>(stageBytes + 0x114) + 4) =
                            *reinterpret_cast<int*>(stageBytes + 0x110) + 0x40;
                        *reinterpret_cast<int*>(*reinterpret_cast<int*>(stageBytes + 0x114) + 8) = 0;
                        *reinterpret_cast<int*>(stageBytes + 0x124) = 0;
                    }

                    if (mode == 2) {
                        void* block = reinterpret_cast<CStage*>(
                                          *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x778C))
                                          ->alloc(0x810, const_cast<char*>(s_memory_cpp), 0x228, 0);
                        *reinterpret_cast<int*>(stageBytes + 0x110) =
                            reinterpret_cast<int>(__construct_new_array(block, 0, 0, 0x40, 0x20));
                        *reinterpret_cast<int*>(stageBytes + 0x120) = 0;
                    }

                    stage->m_defaultParam = static_cast<unsigned int>(-1);
                    return stage;
                }
                list = next;
            } while (list != modeBase);

            System.Printf(const_cast<char*>(DAT_801d6bb0));
            HeapWalker();
        }
    }
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
    int mode = stageGetAllocationMode(stage);
    int modeListOffset = mode * 0x27D8;

    if (mode != 2) {
        if (stageHasUnfreedBlocks(stage)) {
            System.Printf(const_cast<char*>(DAT_801d6a7c), stageGetSourceName(stage));
            stage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
        }
    } else {
        int heapHead = stageGetHeapHead(stage);
        if (heapHead != 0) {
            if (heapHead != 0x10) {
                operator delete[](reinterpret_cast<void*>(heapHead - 0x10));
            }
            stageSetHeapHead(stage, 0);
        }
    }

    unsigned char* stageBytes = reinterpret_cast<unsigned char*>(stage);
    int modeListNode = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x134 + modeListOffset);

    *reinterpret_cast<int*>(*reinterpret_cast<int*>(stageBytes) + 4) = *reinterpret_cast<int*>(stageBytes + 4);
    **reinterpret_cast<int**>(stageBytes + 4) = *reinterpret_cast<int*>(stageBytes);
    *reinterpret_cast<int*>(stageBytes + 4) = modeListNode;
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x134 + modeListOffset) = reinterpret_cast<int>(stage);
}

/*
 * --INFO--
 * PAL Address: 0x8001E7F4
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMemory::_Alloc(unsigned long size, CMemory::CStage* stage, char* source, int line, int noError)
{
    return stage->alloc(size, source != (char*)nullptr ? source : DAT_8032f7d4, line, noError);
}

/*
 * --INFO--
 * PAL Address: 0x8001E6F0
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::Free(void* ptr)
{
    if (ptr != (void*)nullptr) {
        int mem = reinterpret_cast<int>(ptr);
        if ((*reinterpret_cast<short*>(mem - 0x40) != 0x4b41) ||
            (*reinterpret_cast<short*>(mem - 2) != 0x4d49)) {
            System.Printf(const_cast<char*>(DAT_801d6648), ptr, mem - 0x26, *reinterpret_cast<unsigned short*>(mem - 0x28));
        }

        *reinterpret_cast<unsigned char*>(mem - 0x3e) &= 0xfb;

        if ((*reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(mem - 0x38) + 2) & 4) == 0) {
            *reinterpret_cast<int*>(mem - 0x30) =
                *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 0x10) +
                *reinterpret_cast<int*>(mem - 0x30) + 0x40;
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 8) + 4) =
                mem - 0x40;
            *reinterpret_cast<int*>(mem - 0x38) =
                *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 8);
        }

        int blockNext = *reinterpret_cast<int*>(mem - 0x3c);
        if ((*reinterpret_cast<unsigned char*>(blockNext + 2) & 4) == 0) {
            *reinterpret_cast<int*>(blockNext + 0x10) =
                *reinterpret_cast<int*>(mem - 0x30) +
                *reinterpret_cast<int*>(blockNext + 0x10) + 0x40;
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x3c) + 8) = *reinterpret_cast<int*>(mem - 0x38);
            *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x38) + 4) = *reinterpret_cast<int*>(mem - 0x3c);
        }

        *reinterpret_cast<int*>(*reinterpret_cast<int*>(mem - 0x34) + 0x124) -= 1;
    }
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
    m_heapWalkerLevel += 1;
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
    m_heapWalkerLevel -= 1;
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
 * PAL Address: 0x8001E620
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::CopyToAMemorySync(void* source, void* dest, unsigned long size)
{
    int dmaId = RedSound(&Sound)->DMAEntry(0, 0, reinterpret_cast<int>(source), reinterpret_cast<int>(dest),
                                           static_cast<int>(size), 0, 0);
    CStopWatch watch((char*)0);
    watch.Start();
    while (RedSound(&Sound)->DMACheck(dmaId) != 0) {
        watch.Stop();
        watch.Get();
        watch.Start();
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001E4F8
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::CopyFromAMemorySync(void* source, void* dest, unsigned long size)
{
    CStopWatch watch((char*)0);
    int dmaId = RedSound(&Sound)->DMAEntry(0, 1, reinterpret_cast<int>(source), reinterpret_cast<int>(dest),
                                           static_cast<int>(size), 0, 0);
    watch.Start();
    float timeout = FLOAT_8032f7d8;
    while (RedSound(&Sound)->DMACheck(dmaId) != 0) {
        watch.Stop();
        if (watch.Get() < timeout) {
            watch.Start();
        } else {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(s_copyFromAMemorySyncTimeout_801D6ABC));
            }
            Sound.CheckDriver(1);
            watch.Reset();
            watch.Start();
        }
    }
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
 * PAL Address: 0x8001E2EC
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMemory::CStage::alloc(unsigned long size, char* source, unsigned long line, int noError)
{
    DAT_8032ec58 += 1;
    if (size == 0) {
        size = 0x40;
    }

    unsigned int allocSize = static_cast<unsigned int>(size + 0x3F) & ~0x3F;
    int allocated = 0;

    for (int pass = 0; pass < 2; pass++) {
        if (pass != 0) {
            for (int node = *reinterpret_cast<int*>(stageGetHeapHead(this) + 8);
                 (*reinterpret_cast<unsigned char*>(node + 2) & 3) == 0;
                 node = *reinterpret_cast<int*>(node + 8)) {
                if (((*reinterpret_cast<unsigned char*>(node + 2) & 4) == 0) &&
                    (allocSize <= static_cast<unsigned int>(*reinterpret_cast<int*>(node + 0x10)))) {
                    if (allocSize < static_cast<unsigned int>(*reinterpret_cast<int*>(node + 0x10) - 0x40)) {
                        int split = node + allocSize;
                        *reinterpret_cast<unsigned char*>(split + 2) = 0;
                        *reinterpret_cast<int*>(split + 0x10) =
                            (*reinterpret_cast<int*>(node + 0x10) - static_cast<int>(allocSize)) - 0x40;
                        *reinterpret_cast<int*>(node + 0x10) = allocSize;
                        *reinterpret_cast<unsigned short*>(split + 0x00) = 0x4B41;
                        *reinterpret_cast<unsigned short*>(split + 0x3E) = 0x4D49;
                        *reinterpret_cast<int*>(split + 0x04) = node;
                        *reinterpret_cast<int*>(split + 0x08) = *reinterpret_cast<int*>(node + 0x08);
                        *reinterpret_cast<int*>(node + 0x08) = split + 0x40;
                        *reinterpret_cast<int*>(*reinterpret_cast<int*>(split + 0x08) + 0x04) = split + 0x40;
                    }

                    *reinterpret_cast<unsigned short*>(node + 0x18) = static_cast<unsigned short>(line);
                    *reinterpret_cast<unsigned char*>(node + 3) =
                        static_cast<unsigned char>(Memory.GetHeapWalkerLevel());
                    memset(reinterpret_cast<void*>(node + 0x1A), 0, 0x24);

                    if (source == (char*)nullptr) {
                        source = DAT_8032f7d4;
                    }
                    strncpy(reinterpret_cast<char*>(node + 0x1A), source, 0x23);

                    allocated = node + 0x40;
                    *reinterpret_cast<unsigned char*>(node + 2) = 4;
                    *reinterpret_cast<unsigned char*>(node + 2) =
                        (*reinterpret_cast<unsigned char*>(node + 2) & 0x0F) |
                        static_cast<unsigned char>(Memory.GetDefaultGroup() << 4);
                    *reinterpret_cast<unsigned long*>(node + 0x14) =
                        m_defaultParam;
                    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x124) += 1;
                    *reinterpret_cast<CStage**>(node + 0x0C) = this;
                    break;
                }

                if ((*reinterpret_cast<int*>(node + 8) == 0) || (*reinterpret_cast<int*>(node + 4) == 0)) {
                    heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
                }
            }

            if (allocated != 0) {
                break;
            }
        }
    }

    if ((noError == 0) && (allocated == 0)) {
        if (source == (char*)nullptr) {
            source = DAT_8032f7d4;
        }
        System.Printf(
            const_cast<char*>(DAT_801d6a24), stageGetSourceName(this), allocSize, source, line);
        heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
    }

    return reinterpret_cast<void*>(allocated);
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
    *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(this) + 0x128) =
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
    *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(this) + 0x128) =
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
        System.Printf(const_cast<char*>(s_heapWalkerBanner));
        System.Printf(const_cast<char*>(s_heapWalkerStageNameFmt), stageGetSourceName(this));
        System.Printf(const_cast<char*>(s_heapWalkerHeaderFmt));
        System.Printf(const_cast<char*>(s_heapWalkerSeparator));
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
                    System.Printf(
                        const_cast<char*>(s_heapWalkerEntryFmt), freeCount, "FREE", 0, top - blockTail, totalSize, 0, 0, 0,
                        "-------", 0);
                }
                usedSize += size;
                totalSize += size;
                freeCount++;
            }

            if (i < count) {
                int used = *reinterpret_cast<int*>(node + 8) - *reinterpret_cast<int*>(node + 4);
                if ((flag & 2) != 0) {
                    System.Printf(
                        const_cast<char*>(s_heapWalkerEntryFmt), usedCount, "USED",
                        *reinterpret_cast<unsigned char*>(node + 3), used, totalSize,
                        *reinterpret_cast<int*>(node + 4), 0, 0, reinterpret_cast<char*>(node + 0x1A),
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
                    System.Printf(
                        const_cast<char*>(s_heapWalkerEntryFmt), index, kind, level, *reinterpret_cast<int*>(node + 0x10),
                        totalSize, node + 0x40, *reinterpret_cast<int*>(node + 4), *reinterpret_cast<int*>(node + 8),
                        source, line);
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
        System.Printf(const_cast<char*>(s_heapWalkerSeparator));
        System.Printf(const_cast<char*>(s_heapWalkerUseUnuseFmt), freeSize, usedSize);
    }

    return freeSize;
}

/*
 * --INFO--
 * PAL Address: 0x8001DB48
 * PAL Size: 1088b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::CStage::drawHeapBar(int y)
{
    _GXColor color;
    unsigned int colors[16];
    colors[0] = s_heapBarColors_801D64A8[0];
    colors[1] = s_heapBarColors_801D64A8[1];
    colors[2] = s_heapBarColors_801D64A8[2];
    colors[3] = s_heapBarColors_801D64A8[3];
    colors[4] = s_heapBarColors_801D64A8[4];
    colors[5] = s_heapBarColors_801D64A8[5];
    colors[6] = s_heapBarColors_801D64A8[6];
    colors[7] = s_heapBarColors_801D64A8[7];
    colors[8] = s_heapBarColors_801D64A8[8];
    colors[9] = s_heapBarColors_801D64A8[9];
    colors[10] = s_heapBarColors_801D64A8[10];
    colors[11] = s_heapBarColors_801D64A8[11];
    colors[12] = s_heapBarColors_801D64A8[12];
    colors[13] = s_heapBarColors_801D64A8[13];
    colors[14] = s_heapBarColors_801D64A8[14];
    colors[15] = s_heapBarColors_801D64A8[15];

    int prevNode;
    int node;
    if (m_allocationMode == 2) {
        node = stageGetHeapHead(this);
    } else {
        node = *reinterpret_cast<int*>(stageGetHeapHead(this) + 8);
    }

    prevNode = *reinterpret_cast<int*>(node + 4);
    unsigned char heapBar[0x17D];
    memset(heapBar, 0xFF, 0x17D);

    int heapTop = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 8);
    int heapSpan = (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0xC) - 0x40) - heapTop;

    while ((*reinterpret_cast<unsigned char*>(node + 2) & 2) == 0) {
        int curNode = node;
        unsigned char flags = *reinterpret_cast<unsigned char*>(curNode + 2);
        bool isUsed = false;
        if (((flags & 4) != 0) && ((flags & 3) == 0)) {
            isUsed = true;
        }

        if (isUsed) {
            int fillEnd = ((*reinterpret_cast<int*>(curNode + 8) - heapTop) * 0x17C) / heapSpan;
            int fillStart = (((curNode + 0x40) - heapTop) * 0x17C) / heapSpan;
            unsigned char* dst = heapBar + fillStart;
            unsigned int fillCount = static_cast<unsigned int>(fillEnd + 1) - static_cast<unsigned int>(fillStart);

            if (fillStart <= fillEnd) {
                unsigned int loop = fillCount >> 3;
                if (loop != 0) {
                    do {
                        dst[0] = static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(curNode + 2) >> 4);
                        dst[1] = static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(curNode + 2) >> 4);
                        dst[2] = static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(curNode + 2) >> 4);
                        dst[3] = static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(curNode + 2) >> 4);
                        dst[4] = static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(curNode + 2) >> 4);
                        dst[5] = static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(curNode + 2) >> 4);
                        dst[6] = static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(curNode + 2) >> 4);
                        dst[7] = static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(curNode + 2) >> 4);
                        dst += 8;
                        loop--;
                    } while (loop != 0);

                    fillCount &= 7;
                    if (fillCount == 0) {
                        goto checkHeapNode;
                    }
                }

                do {
                    *dst = static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(curNode + 2) >> 4);
                    dst++;
                    fillCount--;
                } while (fillCount != 0);
            }
        }

checkHeapNode:
        if ((static_cast<unsigned int>(*reinterpret_cast<int*>(curNode + 0x10)) !=
             static_cast<unsigned int>(*reinterpret_cast<int*>(curNode + 8) - (curNode + 0x40))) ||
            (static_cast<unsigned int>(*reinterpret_cast<int*>(curNode + 4)) != static_cast<unsigned int>(prevNode))) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(DAT_801d67d8));
            }
            return;
        }

        prevNode = curNode;
        node = *reinterpret_cast<int*>(curNode + 8);
    }

    int drawColor = heapBar[0];
    unsigned char* colorPtr = heapBar;
    int segmentStart = 0;
    int x = 0;

    do {
        if ((drawColor != *colorPtr) || (x == 0x17B)) {
            if (drawColor == 0xFF) {
                if (stageGetAllocationMode(this) == 0) {
                    color.r = 0;
                    color.g = 0;
                    color.b = 0x40;
                    color.a = 0x80;
                } else {
                    color.r = 0;
                    color.g = 0x40;
                    color.b = 0;
                    color.a = 0x80;
                }
            } else if (stageGetAllocationMode(this) == 0) {
                u8* colorSrc = reinterpret_cast<u8*>(colors) + drawColor * 4;
                color.r = colorSrc[0];
                color.g = colorSrc[1];
                color.b = colorSrc[2];
                color.a = colorSrc[3];
            } else {
                u8* colorSrc = reinterpret_cast<u8*>(colors) + drawColor * 4;
                color.r = colorSrc[0];
                color.g = colorSrc[1];
                color.b = colorSrc[2];
                color.a = colorSrc[3];
            }

            GXBegin(static_cast<GXPrimitive>(0x98), GX_VTXFMT0, 4);
            GXPosition3f32(static_cast<float>(segmentStart + 0x80), static_cast<float>(y), 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&color));
            GXPosition3f32(static_cast<float>(x + 0x80), static_cast<float>(y), 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&color));
            GXPosition3f32(static_cast<float>(segmentStart + 0x80), static_cast<float>(y + 8), 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&color));
            GXPosition3f32(static_cast<float>(x + 0x80), static_cast<float>(y + 8), 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&color));

            drawColor = *colorPtr;
            segmentStart = x;
        }

        x++;
        colorPtr++;
    } while (x < 0x17C);
}

/*
 * --INFO--
 * PAL Address: 0x8001D9BC
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::CStage::drawHeapTitle(int y)
{
    int node = (stageGetAllocationMode(this) == 2) ? stageGetHeapHead(this) : *reinterpret_cast<int*>(stageGetHeapHead(this) + 8);
    unsigned int totalUnuse = 0;
    unsigned int maxUnuse = 0;
    int prev = *reinterpret_cast<int*>(node + 4);
    int heapTop = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 8);
    char line[264];

    while ((*reinterpret_cast<unsigned char*>(node + 2) & 2) == 0) {
        if ((*reinterpret_cast<unsigned char*>(node + 2) & 4) == 0) {
            int blockStart = (node + 0x40) - heapTop;
            int blockEnd = *reinterpret_cast<int*>(node + 8) - heapTop;
            int blockSize = blockEnd - blockStart;
            totalUnuse += blockSize;
            if (static_cast<int>(maxUnuse) < blockSize) {
                maxUnuse = blockSize;
            }
        }

        if ((*reinterpret_cast<int*>(node + 0x10) != *reinterpret_cast<int*>(node + 8) - (node + 0x40)) ||
            (*reinterpret_cast<int*>(node + 4) != prev)) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(DAT_801d67d8));
            }
            return;
        }

        prev = node;
        node = *reinterpret_cast<int*>(node + 8);
    }

    int srcLen = strlen(reinterpret_cast<char*>(reinterpret_cast<unsigned char*>(this) + 0x10));
    int sourceOffset = srcLen - 12;
    sourceOffset &= ~(sourceOffset >> 31);
    strcpy(line, reinterpret_cast<char*>(reinterpret_cast<unsigned char*>(this) + sourceOffset + 0x10));
    Graphic.DrawDebugStringDirect(0x10, y, line, 8);

    sprintf(line, s_drawHeapTitleFmt, *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x124),
            static_cast<int>(totalUnuse) / 1024, static_cast<int>(maxUnuse) / 1024);
    Graphic.DrawDebugStringDirect(0x208, y, line, 8);
}

/*
 * --INFO--
 * PAL Address: 0x8001D964
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMemory::CStage::GetHeapUnuse()
{
    int node = (m_allocationMode == 2) ? stageGetHeapHead(this) : *reinterpret_cast<int*>(stageGetHeapHead(this) + 8);
    int total = 0;

    while ((*reinterpret_cast<unsigned char*>(node + 2) & 2) == 0) {
        if ((*reinterpret_cast<unsigned char*>(node + 2) & 4) == 0) {
            total += *reinterpret_cast<int*>(node + 0x10);
        }
        node = *reinterpret_cast<int*>(node + 8);
    }

    return total;
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
 * PAL Address: 0x8001D838
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::Init(char* sourceName, CMemory::CStage* rStage, CMemory::CStage* stage, int cacheCount,
                         unsigned char (*releaseCheck)(unsigned long), unsigned long releaseCheckArg,
                         unsigned char (*releaseAction)(unsigned long), unsigned long releaseActionArg,
                         unsigned char (*overflowHook)(unsigned long), unsigned long overflowHookArg)
{
    strcpy(m_name, sourceName);

    m_releaseAction = releaseAction;
    m_releaseActionArg = releaseActionArg;
    m_releaseCheck = releaseCheck;
    m_releaseCheckArg = releaseCheckArg;
    m_overflowHook = overflowHook;
    m_overflowHookArg = overflowHookArg;
    m_rStage = rStage;
    m_stage = stage;

    if (stage == nullptr) {
        m_cacheCount = 0;
        m_amemCursor = 0;
        m_amemStart = 0;
        m_amemEnd = 0;
        m_amemLock = 0;
        m_cacheTable = 0;
    } else {
        m_cacheCount = cacheCount;
        unsigned long start = stage->m_heapTop;
        m_amemStart = start;
        m_amemCursor = start;
        m_amemEnd = stage->m_heapBottom;
        m_amemLock = 0;

        m_cacheTable = new (rStage, const_cast<char*>(s_memory_cpp), 0x787) CAmemCache[m_cacheCount];
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001D830
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::SetRStage(CMemory::CStage* stage)
{
    m_rStage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x8001D6A8
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::Destroy()
{
    if (m_cacheTable != nullptr) {
        delete[] m_cacheTable;
        m_cacheTable = 0;
    }
}

static inline void freeAmemCacheBlock(unsigned long ptr)
{
    unsigned char* block = reinterpret_cast<unsigned char*>(ptr - 0x40);
    if ((*reinterpret_cast<unsigned short*>(block) != 0x4b41) ||
        (*reinterpret_cast<unsigned short*>(block + 0x3E) != 0x4d49)) {
        System.Printf(const_cast<char*>(DAT_801d6648), ptr, block + 0x1A, *reinterpret_cast<unsigned short*>(block + 0x18));
    }

    block[2] &= 0xfb;

    int blockPrev = *reinterpret_cast<int*>(block + 8);
    if ((*(reinterpret_cast<unsigned char*>(blockPrev) + 2) & 4) == 0) {
        *reinterpret_cast<int*>(block + 0x10) =
            *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockPrev) + 0x10) +
            *reinterpret_cast<int*>(block + 0x10) + 0x40;
        *reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockPrev) + 8) + 4) =
            reinterpret_cast<int>(block);
        *reinterpret_cast<int*>(block + 8) =
            *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockPrev) + 8);
    }

    int blockNext = *reinterpret_cast<int*>(block + 4);
    if ((*(reinterpret_cast<unsigned char*>(blockNext) + 2) & 4) == 0) {
        *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockNext) + 0x10) =
            *reinterpret_cast<int*>(block + 0x10) +
            *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(blockNext) + 0x10) + 0x40;
        *reinterpret_cast<int*>(*reinterpret_cast<int*>(block + 4) + 8) = *reinterpret_cast<int*>(block + 8);
        *reinterpret_cast<int*>(*reinterpret_cast<int*>(block + 8) + 4) = *reinterpret_cast<int*>(block + 4);
    }

    *reinterpret_cast<int*>(*reinterpret_cast<int*>(block + 0xC) + 0x124) -= 1;
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
    CAmemCache& entry = cacheEntryAt(this, index);

    if (entry.m_dmaCopy != 0) {
        unsigned long cacheData = reinterpret_cast<unsigned long>(entry.m_cacheData);
        if (cacheData != 0) {
            if (cacheData != 0) {
                freeAmemCacheBlock(cacheData);
            }
            entry.m_cacheData = 0;
        }
        unsigned long workData = reinterpret_cast<unsigned long>(entry.m_workData);
        if (workData != 0) {
            entry.m_workData = 0;
        }
    } else {
        unsigned long workData = reinterpret_cast<unsigned long>(entry.m_workData);
        if (workData != 0) {
            if (workData != 0) {
                freeAmemCacheBlock(workData);
            }
        }
        entry.m_cacheData = 0;
        entry.m_workData = 0;
    }

    entry.m_refCnt0 = 0;
    entry.m_refCount = 0;
    entry.m_inUse = 0;
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
    m_amemLock = m_amemCursor;
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
    unsigned long lock = m_amemLock;
    m_amemPrev = lock;
    m_amemCursor = lock;
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
    m_amemCursor = m_amemPrev;
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
 * PAL Address: 0x8001D278
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CAmemCacheSet::GetData(short index, char* source, int line)
{
    int data = 0;

    while (true) {
        CAmemCache& entry = cacheEntryAt(this, index);

        if (entry.m_cacheData == 0) {
            if (!entry.m_dmaCopy) {
                entry.m_cacheData = entry.m_workData;
                data = reinterpret_cast<int>(entry.m_cacheData);
            } else {
                char* allocSource = source;
                if (allocSource == 0) {
                    allocSource = DAT_8032f7d4;
                }

                data = reinterpret_cast<int>(
                    m_rStage->alloc(static_cast<unsigned long>(entry.m_size), allocSource, static_cast<unsigned long>(line), 1));
                entry.m_cacheData = reinterpret_cast<void*>(data);
                if (data != 0) {
                    int dmaId = RedSound(&Sound)->DMAEntry(0, 1, reinterpret_cast<int>(entry.m_cacheData),
                                                           reinterpret_cast<int>(entry.m_workData), entry.m_size, 0, 0);
                    CStopWatch watch(0);
                    watch.Start();
                    float timeout = FLOAT_8032f7d8;
                    while (RedSound(&Sound)->DMACheck(dmaId) != 0) {
                        watch.Stop();
                        if (watch.Get() >= timeout) {
                            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                                System.Printf(const_cast<char*>(DAT_801d669c));
                            }
                            Sound.CheckDriver(1);
                            watch.Reset();
                        }
                        watch.Start();
                    }
                    data = reinterpret_cast<int>(entry.m_cacheData);
                }
            }
        }

        if (data != 0) {
            return data;
        }
        AmemFreeLowPrio(entry.m_size);
    }
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
    short slot = 0;
    int remaining = m_cacheCount;
    int index = -1;

    if (remaining > 0) {
        do {
            if (cacheEntryAt(this, slot).m_inUse == 0) {
                index = slot;
                break;
            }
            slot++;
            remaining--;
        } while (remaining != 0);
    }

    if (static_cast<short>(index) == -1) {
        return -1;
    }

    CAmemCache& entry = cacheEntryAt(this, static_cast<short>(index));
    unsigned int allocSize = (static_cast<unsigned int>(size) + 0x1F) & ~0x1F;
    entry.m_inUse = 1;
    entry.m_type = static_cast<unsigned char>(type);
    entry.m_dmaCopy = static_cast<unsigned char>(dmaCopy);
    entry.m_refCount = 0;

    if (dmaCopy != 0) {
        m_amemPrev = m_amemCursor;
        m_amemCursor += allocSize;
        entry.m_workData = reinterpret_cast<void*>(m_amemPrev);
        entry.m_cacheData = 0;
        entry.m_size = static_cast<int>(allocSize);

        int checksum = 0x12345678;
        unsigned int remainingBytes = static_cast<unsigned int>(entry.m_size);
        const unsigned char* data = reinterpret_cast<const unsigned char*>(src);
        if (remainingBytes != 0) {
            unsigned int chunks = remainingBytes >> 3;
            if (chunks != 0) {
                do {
                    checksum += data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7];
                    data += 8;
                    chunks--;
                } while (chunks != 0);

                remainingBytes &= 7;
                if (remainingBytes == 0) {
                    goto checksum_done_dma;
                }
            }

            do {
                checksum += *data;
                data++;
                remainingBytes--;
            } while (remainingBytes != 0);
        }

    checksum_done_dma:
        entry.m_checksum = checksum;

        if (entry.m_dmaCopy == 0) {
            memcpy(entry.m_workData, src, static_cast<unsigned long>(entry.m_size));
        } else {
            int dmaId = RedSound(&Sound)->DMAEntry(0, 0, reinterpret_cast<int>(src),
                                                   reinterpret_cast<int>(entry.m_workData), entry.m_size, 0, 0);
            CStopWatch watch((char*)0);
            watch.Start();
            while (RedSound(&Sound)->DMACheck(dmaId) != 0) {
                watch.Stop();
                watch.Get();
                watch.Start();
            }
        }

        return index;
    }

    while (true) {
        entry.m_workData = m_rStage->alloc(allocSize, const_cast<char*>(s_memory_cpp), 0x807, 1);
        if (entry.m_workData != 0) {
            break;
        }
        AmemFreeLowPrio(allocSize);
    }

    entry.m_cacheData = 0;
    entry.m_size = static_cast<int>(allocSize);

    int checksum = 0x12345678;
    unsigned int remainingBytes = static_cast<unsigned int>(entry.m_size);
    const unsigned char* data = reinterpret_cast<const unsigned char*>(src);
    if (remainingBytes != 0) {
        unsigned int chunks = remainingBytes >> 3;
        if (chunks != 0) {
            do {
                checksum += data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7];
                data += 8;
                chunks--;
            } while (chunks != 0);

            remainingBytes &= 7;
            if (remainingBytes == 0) {
                goto checksum_done_copy;
            }
        }

        do {
            checksum += *data;
            data++;
            remainingBytes--;
        } while (remainingBytes != 0);
    }

checksum_done_copy:
    entry.m_checksum = checksum;

    if (entry.m_dmaCopy == 0) {
        memcpy(entry.m_workData, src, static_cast<unsigned long>(entry.m_size));
    } else {
        int dmaId = RedSound(&Sound)->DMAEntry(0, 0, reinterpret_cast<int>(src),
                                               reinterpret_cast<int>(entry.m_workData), entry.m_size, 0, 0);
        CStopWatch watch((char*)0);
        watch.Start();
        while (RedSound(&Sound)->DMACheck(dmaId) != 0) {
            watch.Stop();
            watch.Get();
            watch.Start();
        }
    }

    DCFlushRange(entry.m_workData, allocSize);
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
int CAmemCacheSet::IsEnable(short index)
{
    unsigned int value = reinterpret_cast<unsigned int>(cacheEntryAt(this, index).m_cacheData);
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
 * PAL Address: 0x8001CD48
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::AddRef(short index)
{
    CAmemCache& entry = cacheEntryAt(this, index);

    entry.m_refCount += 1;
    if (entry.m_refCount == 0xFFFF) {
        if (2 < (unsigned int)System.m_execParam) {
            System.Printf(const_cast<char*>(s_amemCacheAddRefFmt), static_cast<int>(index));
        }

        for (int i = 0; i < m_cacheCount; i++) {
            CAmemCache& current = cacheEntryAt(this, i);
            int data = reinterpret_cast<int>(current.m_cacheData);
            if ((current.m_inUse != 0) || (data != 0)) {
                if (2 < (unsigned int)System.m_execParam) {
                    System.Printf(
                        const_cast<char*>(s_amemCacheEntryFmt), i, cacheStateName(current),
                        cacheTypeName(current), current.m_refCount, current.m_priority, data);
                }
            }
        }

        if (2 < (unsigned int)System.m_execParam) {
            System.Printf(const_cast<char*>(s_amemCacheSeparator));
        }

        void (*overflowHook)(int) = reinterpret_cast<void (*)(int)>(m_overflowHook);
        if (overflowHook != 0) {
            overflowHook(static_cast<int>(index));
        }
    }

    entry.m_priority = 0x7FFFFFF0;
}

/*
 * --INFO--
 * PAL Address: 0x8001CBF4
 * PAL Size: 340b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::Release(short index)
{
    CAmemCache& entry = cacheEntryAt(this, index);
    entry.m_refCount -= 1;

    if (entry.m_refCount == 0xFFFF) {
        if (2 < (unsigned int)System.m_execParam) {
            System.Printf(const_cast<char*>(s_amemCacheAddRefFmt));
        }

        for (int i = 0; i < m_cacheCount; i++) {
            CAmemCache& cache = cacheEntryAt(this, i);
            if (((cache.m_inUse != 0) || (cache.m_cacheData != 0)) && (2 < (unsigned int)System.m_execParam)) {
                System.Printf(
                    const_cast<char*>(s_amemCacheEntryPaddedFmt), i, cacheStateName(cache),
                    cacheTypeName(cache), cache.m_refCount,
                    cache.m_priority, reinterpret_cast<int>(cache.m_cacheData));
            }
        }

        if (2 < (unsigned int)System.m_execParam) {
            System.Printf(const_cast<char*>(s_amemCacheSeparator));
        }

        void (*onUnderflow)(int) = reinterpret_cast<void (*)(int)>(m_overflowHook);
        if (onUnderflow != 0) {
            onUnderflow(static_cast<int>(index));
        }
    }
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
    unsigned int bestPriority = 0x7ffffff1;
    int currentSize = size;

    while (true) {
        CAmemCache* bestEntry = 0;

        for (int i = 0; i < m_cacheCount; i++) {
            CAmemCache& entry = cacheEntryAt(this, i);
            if (entry.m_inUse != 0 && entry.m_refCount == 0 && entry.m_dmaCopy != 0 &&
                entry.m_cacheData != 0 && entry.m_size >= currentSize &&
                static_cast<unsigned int>(entry.m_priority) < bestPriority) {
                bestEntry = &entry;
                bestPriority = static_cast<unsigned int>(entry.m_priority);
            }
        }

        if (bestEntry != 0) {
            freeAmemCacheBlock(reinterpret_cast<unsigned long>(bestEntry->m_cacheData));
            bestEntry->m_cacheData = 0;
        }

        int allocated = reinterpret_cast<int>(m_rStage->alloc(size, const_cast<char*>(s_memory_cpp), 0x86D, 1));
        if (allocated != 0) {
            freeAmemCacheBlock(static_cast<unsigned long>(allocated));
            return;
        }

        if (currentSize != 0) {
            currentSize -= size / 2;
            if (currentSize < 0) {
                currentSize = 0;
            }
            continue;
        }

        if (bestPriority != 0xFFFFFFFF) {
            bestPriority = 0xFFFFFFFF;
            continue;
        }

        if (m_releaseAction == 0 || m_releaseAction(m_releaseActionArg) == 0) {
            m_releaseCheck(m_releaseCheckArg);
            if (2 < (unsigned int)System.m_execParam) {
                System.Printf(const_cast<char*>(s_amemCacheAddRefFmt));
            }

            for (int i = 0; i < m_cacheCount; i++) {
                CAmemCache& entry = cacheEntryAt(this, i);
                int data = reinterpret_cast<int>(entry.m_cacheData);
                if (((entry.m_inUse != 0) || (data != 0)) && (2 < (unsigned int)System.m_execParam)) {
                    System.Printf(
                        const_cast<char*>(s_amemCacheEntryFmt), i, cacheStateName(entry),
                        cacheTypeName(entry), entry.m_refCount, entry.m_priority, data);
                }
            }

            if (2 < (unsigned int)System.m_execParam) {
                System.Printf(const_cast<char*>(s_amemCacheSeparator));
            }
            m_stage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001C6A4
 * PAL Size: 348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::CacheClear()
{
    for (int i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = cacheEntryAt(this, i);

        if ((entry.m_inUse != 0) && (entry.m_refCount == 0) && (entry.m_dmaCopy != 0)) {
            int data = reinterpret_cast<int>(entry.m_cacheData);
            if (data != 0) {
                freeAmemCacheBlock(static_cast<unsigned long>(data));
                entry.m_cacheData = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001C640
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::CalcPrio()
{
    for (int i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = cacheEntryAt(this, i);

        if ((entry.m_inUse != 0) && (entry.m_refCount == 0) &&
            (entry.m_cacheData != 0) && (static_cast<unsigned int>(entry.m_priority) != 0)) {
            entry.m_priority--;
        }
    }
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
    return static_cast<int>(m_amemEnd - m_amemCursor);
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
 * PAL Address: 0x8001C52C
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::RefCnt0Compare()
{
    const char* dumpBase = reinterpret_cast<const char*>(s_heapBarColors_801D64A8);

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(dumpBase + 0x10c));
    }

    for (int i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = cacheEntryAt(this, i);
        if ((entry.m_inUse != 0 && entry.m_refCount != 0) &&
            static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(
                const_cast<char*>(dumpBase + 0xd8), i, cacheStateName(entry), cacheTypeName(entry),
                entry.m_refCount, entry.m_priority, reinterpret_cast<int>(entry.m_cacheData));
        }
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(dumpBase + 0x144));
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001C40C
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::AssertCache()
{
    if (2 < (unsigned int)System.m_execParam) {
        System.Printf(const_cast<char*>(s_amemCacheAddRefFmt));
    }

    for (int i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = cacheEntryAt(this, i);
        int data = reinterpret_cast<int>(entry.m_cacheData);
        if ((entry.m_inUse != 0 || data != 0) && (2 < (unsigned int)System.m_execParam)) {
            System.Printf(
                const_cast<char*>(s_amemCacheEntryFmt), i, cacheStateName(entry),
                cacheTypeName(entry), entry.m_refCount, entry.m_priority, data);
        }
    }

    if (2 < (unsigned int)System.m_execParam) {
        System.Printf(const_cast<char*>(s_amemCacheSeparator));
    }
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
 * PAL Address: 0x8001C2F0
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::CStage::heapInfo(unsigned long& heapTotal, unsigned long& heapUse, unsigned long& heapUnuse)
{
    int usedSize;
    int freeSize;
    int blockTail;
    int i;
    int top;
    int node;

    if (m_allocationMode == 2) {
        node = stageGetHeapHead(this);
    } else {
        node = *reinterpret_cast<int*>(stageGetHeapHead(this) + 8);
    }

    heapTotal = 0;
    heapUse = 0;
    heapUnuse = 0;

    if (m_allocationMode == 2) {
        top = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 8);

        for (i = 0; i <= *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x120); i++, node += 0x40) {
            if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x120) == i) {
                blockTail = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x0C);
            } else {
                blockTail = *reinterpret_cast<int*>(node + 4);
            }

            freeSize = blockTail - top;
            if (freeSize != 0) {
                heapUnuse += freeSize;
                heapTotal += freeSize;
            }

            if (i < *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x120)) {
                usedSize = *reinterpret_cast<int*>(node + 8) - *reinterpret_cast<int*>(node + 4);
                heapUse += usedSize;
                top = blockTail + usedSize;
                heapTotal += usedSize;
            }

        }
        return;
    }

    while ((*reinterpret_cast<unsigned char*>(node + 2) & 2) == 0) {
        if ((*reinterpret_cast<unsigned char*>(node + 2) & 4) != 0) {
            heapUse += *reinterpret_cast<int*>(node + 0x10);
        } else {
            heapUnuse += *reinterpret_cast<int*>(node + 0x10);
        }

        heapTotal += *reinterpret_cast<int*>(node + 8) - node;
        node = *reinterpret_cast<int*>(node + 8);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001D934
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CAmemCache::CAmemCache()
{
    unsigned char* bytes = reinterpret_cast<unsigned char*>(this);

    *reinterpret_cast<int*>(bytes + 0x00) = 0;
    *reinterpret_cast<int*>(bytes + 0x04) = 0;
    *reinterpret_cast<short*>(bytes + 0x0C) = 0;
    *reinterpret_cast<int*>(bytes + 0x08) = 0;
    bytes[0x0E] = 0;
    *reinterpret_cast<int*>(bytes + 0x10) = 0;
    bytes[0x1A] = 1;
    bytes[0x0F] = 0xFF;
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
