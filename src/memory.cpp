#include "ffcc/memory.h"
#include "ffcc/chara.h"
#include "global.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/stopwatch.h"
#include "ffcc/system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "dolphin/os/OSMemory.h"
#include <string.h>
#include <PowerPC_EABI_Support/Runtime/MWCPlusLib.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CMemory Memory;

extern "C" const char s_memory_cpp[] = "memory.cpp";
extern "C" const char sGetDataTimeoutBanner[] =
    "===================================================================\n"
    "===================================================================\n"
    "                          GetData  TimeOut\n"
    "===================================================================\n"
    "===================================================================\n";
extern "C" const char sHeapCorruptAbortDrawMsg[40] =
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
extern const char sAmemCacheAddRefFmt[];
extern const char sAmemCacheEntryFmt[];
extern const char sRefCntCompareBanner[];
extern const char sHeapWalkerEntryFmt[];
extern const char sHeapWalkerUseUnuseFmt[];
extern const char sHeapWalkerTitle[];
extern const char sHeapWalkerUseFmt[];
extern const char sHeapWalkerUnuseFmt[];
extern const char sHeapWalkerTotalFmt[];
extern const char sAmemCacheSeparator[3];
extern char sStageFreeCorruptBlockFmt[];
extern char sStageAllocNoMemoryFmt[];
extern char sStageQuitBlockUnfreedAllocFmt[];
extern char sCopyFromAMemorySyncTimeoutMsg[];
extern char sCurrentMemoryStageName[];
extern char sMainMemoryStageName[];
extern char sDrawHeapUseUnuseFmt[];
extern char sDrawHeapAmemAnimFmt[];
extern const char sAmemCacheTypeTexture[] = "TEXTURE";
extern const char sAmemCacheTypeModel[] = "MODEL  ";
extern const char sAmemCacheTypePdt[] = "PDT    ";
extern const char sAmemCacheStateUse[] = "USE  ";
extern const char sAmemCacheStateNoUse[] = "NOUSE";
extern const char sMemoryClassName[] = "CMemory";
extern const char sAmemCacheSeparator[3] = "\n\n";
extern const char sMemoryNoNameStopwatchName[8] = "no name";
extern const char sEmptyAllocSourceName[4] = "";
extern const char* amem_typeName[] = {
    sAmemCacheTypeTexture,
    sAmemCacheTypeModel,
    sAmemCacheTypePdt,
};
extern const char* amem_stateName[2] = {
    sAmemCacheStateUse,
    sAmemCacheStateNoUse,
};
extern const float kMemoryDmaTimeout = 9000.0f;
extern const float kMemoryDrawZero = 0.0f;
extern const double kMemorySignedDoubleMagic = 4503601774854144.0;
extern const char sHeapWalkerNewline[] = "\n";
static const char sHeapWalkerFree[] = "FREE";
static const char sHeapWalkerUsed[] = "USED";
extern const float kMemoryDrawOrthoBottom = 448.0f;
extern const float kMemoryDrawOrthoRight = 640.0f;
extern const float kMemoryDrawOrthoFar = -100.0f;
extern const char sHeapWalkerSlashLine[] = "//\n";
extern unsigned int sHeapBarColors[];
int g_alloc_ct;
static int s_RefCnt0Compare;
static int s_MaxRefCnt0Compare;

STATIC_ASSERT(sizeof(CMemory::CStage) == 0x12C);
STATIC_ASSERT(sizeof(CMemory::CStage::CBlock) == 0x40);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_flags) == 0x02);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_level) == 0x03);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_prev) == 0x04);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_next) == 0x08);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_stage) == 0x0C);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_size) == 0x10);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_defaultParam) == 0x14);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_line) == 0x18);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_source) == 0x1A);
STATIC_ASSERT(offsetof(CMemory::CStage::CBlock, m_magicEnd) == 0x3E);
STATIC_ASSERT(sizeof(CMemory::CMode) == 0x27D8);
STATIC_ASSERT(sizeof(CMemory) == 0x77A0);

static const unsigned short kMemoryBlockStartMagic = 0x4B41;
static const unsigned short kMemoryBlockEndMagic = 0x4D49;
static const unsigned char kMemoryBlockUsedFlag = 0x04;

static const int kStagePoolFullMsgOffset = 0xC0;
static const int kStageAllocFailedMsgOffset = 0xF4;
static const int kStageDestroyingMsgOffset = 0x28;
static inline int stageGetAllocationMode(CMemory::CStage* stage)
{
    return stage->m_allocationMode;
}

static inline int stageGetHeapHead(CMemory::CStage* stage)
{
    return stage->m_heapHead;
}

static inline void stageSetHeapHead(CMemory::CStage* stage, int value)
{
    stage->m_heapHead = value;
}

static inline char* stageGetSourceName(CMemory::CStage* stage)
{
    return stage->m_allocationSourceStr;
}

static inline CMemory::CStage::CBlock* stageBlockAt(unsigned long address)
{
    return reinterpret_cast<CMemory::CStage::CBlock*>(address);
}

static inline CMemory::CStage::CBlock* blockFromPayload(void* payload)
{
    return reinterpret_cast<CMemory::CStage::CBlock*>(reinterpret_cast<unsigned char*>(payload) - sizeof(CMemory::CStage::CBlock));
}

static inline void* payloadFromBlock(CMemory::CStage::CBlock* block)
{
    return reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(block) + sizeof(CMemory::CStage::CBlock));
}

static inline void freeStageBlock(void* ptr)
{
    if (ptr != (void*)nullptr) {
        CMemory::CStage::CBlock* block = blockFromPayload(ptr);
        if ((block->m_magicStart != kMemoryBlockStartMagic) ||
            (block->m_magicEnd != kMemoryBlockEndMagic)) {
            System.Printf(const_cast<char*>(sStageFreeCorruptBlockFmt), ptr, block->m_source, block->m_line);
        }

        block->m_flags = static_cast<unsigned char>(block->m_flags & ~kMemoryBlockUsedFlag);

        if ((block->m_next->m_flags & kMemoryBlockUsedFlag) == 0) {
            block->m_size =
                block->m_size + sizeof(CMemory::CStage::CBlock) + block->m_next->m_size;
            block->m_next->m_next->m_prev = block;
            block->m_next = block->m_next->m_next;
        }

        CMemory::CStage::CBlock* prevBlock = block->m_prev;
        if ((prevBlock->m_flags & kMemoryBlockUsedFlag) == 0) {
            prevBlock->m_size =
                prevBlock->m_size + sizeof(CMemory::CStage::CBlock) + block->m_size;
            block->m_prev->m_next = block->m_next;
            block->m_next->m_prev = block->m_prev;
        }

        block->m_stage->m_allocCount -= 1;
    }
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
    return amem_stateName[entry.m_inUse == 0];
}

static inline const char* cacheTypeName(const CAmemCache& entry)
{
    return amem_typeName[entry.m_type];
}

static inline int stageHasUnfreedBlocks(CMemory::CStage* stage)
{
    int found = 0;
    CMemory::CStage::CBlock* node = stageBlockAt(stageGetHeapHead(stage))->m_next;
    while ((node->m_flags & 2) == 0) {
        if ((node->m_flags & kMemoryBlockUsedFlag) != 0) {
            found = 1;
        }
        node = node->m_next;
    }
    return found;
}

static inline void stageReleaseMode2Buffer(CMemory::CStage* stage)
{
    int ptr = stageGetHeapHead(stage);
    if (ptr != 0) {
        if (ptr != 0x10) {
            operator delete[](reinterpret_cast<void*>(ptr - 0x10));
        }
        stageSetHeapHead(stage, 0);
    }
}

static inline void stageDestroyAndPool(CMemory* memory, CMemory::CStage* stage)
{
    int mode = stageGetAllocationMode(stage);
    CMemory::CMode& modeData = memory->Mode(mode);

    if (mode != 2) {
        if (stageHasUnfreedBlocks(stage)) {
            System.Printf(const_cast<char*>(sStageQuitBlockUnfreedAllocFmt), stageGetSourceName(stage));
            stage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
        }
    } else {
        stageReleaseMode2Buffer(stage);
    }

    stage->m_prev->m_next = stage->m_next;
    stage->m_next->m_prev = stage->m_prev;
    stage->m_next = modeData.m_freeList.m_next;
    modeData.m_freeList.m_next = stage;
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
    return stage->alloc(size, file != (char*)nullptr ? file : const_cast<char*>(sEmptyAllocSourceName), line, 0);
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
    return stage->alloc(size, file != (char*)nullptr ? file : const_cast<char*>(sEmptyAllocSourceName), line, 0);
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
    freeStageBlock(ptr);
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
    freeStageBlock(ptr);
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
        }

        if (size != 0) {
            do {
                checksum += *bytes;
                bytes++;
                size--;
            } while (size != 0);
        }
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
    OSInitAlloc(OSGetArenaLo(), reinterpret_cast<void*>(reinterpret_cast<int>(OSGetArenaLo()) + 0x14000), 1);

    m_heapWalkerLevel = 0;
    m_heapWalkerVisible = 0;
    m_defaultGroup = 0;

    CMode* modePtr = m_modes;
    for (int pass = 0; pass < 3; pass++, modePtr++) {
        if ((pass != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) {
            CMode& modeData = *modePtr;
            if ((pass == 0) || (pass == 1)) {
                unsigned int arenaHi = reinterpret_cast<unsigned int>(OSGetArenaHi());
                if (pass == 0) {
                    modeData.m_activeList.m_heapTop = 0x81780000;
                    unsigned int lo = reinterpret_cast<unsigned int>(OSGetArenaLo());
                    modeData.m_activeList.m_heapBottom = (lo + 0x1403F) & ~0x3FU;
                } else {
                    modeData.m_activeList.m_heapTop = arenaHi & ~0x3FU;
                    modeData.m_activeList.m_heapBottom = 0x81800000;
                }

                int top = modeData.m_activeList.m_heapTop;
                int bottom = modeData.m_activeList.m_heapBottom;
                if (0 < (top - bottom)) {
                    memset(reinterpret_cast<void*>(bottom), 0xAB, top - bottom);
                }
            } else {
                modeData.m_activeList.m_heapTop = 0x7FC000;
                modeData.m_activeList.m_heapBottom = 0x4000;
            }

            modeData.m_activeList.m_prev = &modeData.m_activeList;
            modeData.m_activeList.m_next = &modeData.m_activeList;
            modeData.m_freeList.m_next = &modeData.m_stagePool[0];

            for (unsigned int index = 0; index < 32; index++) {
                CStage* next;

                if (index == 0x1F) {
                    next = &modeData.m_freeList;
                } else {
                    next = &modeData.m_stagePool[index + 1];
                }

                modeData.m_stagePool[index].m_next = next;
            }
        }
    }

    CStage* stage = CreateStage(0x2000, sCurrentMemoryStageName, 0);
    m_currentMemoryStage = stage;

    stage = CreateStage(0x4000, sMainMemoryStageName, 0);
    m_mainMemoryStage = stage;
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
    const char* strBase = reinterpret_cast<const char*>(sHeapBarColors);

    stageDestroyAndPool(this, m_mainMemoryStage);

    CMode* modeData = m_modes;
    for (int pass = 0; pass < 3; pass++, modeData++) {
        if ((pass != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) {
            CStage* listHead = &modeData->m_activeList;
            CStage* stage = listHead->m_next;

            while (stage != listHead) {
                CStage* next = stage->m_next;
                if (pass == 0) {
                    if (stage != m_currentMemoryStage) {
                        System.Printf(const_cast<char*>(strBase + 0x7b0), stage->m_allocationSourceStr);
                        stageDestroyAndPool(this, stage);
                    }
                } else {
                    System.Printf(const_cast<char*>(strBase + 0x7b0), stage->m_allocationSourceStr);
                    stageDestroyAndPool(this, stage);
                }
                stage = next;
            }
        }
    }

    stageDestroyAndPool(this, m_currentMemoryStage);
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
    if (Pad.m_debugPadLock == 0) {
        if (Pad.m_debugPadPort == -1) {
            goto frame_input_done;
        }
    }
    activeInput = true;

frame_input_done:

    if (activeInput) {
        trigger = 0;
    } else {
        int port = 0;
        unsigned int clamped = (unsigned int)port & ~-(int)((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) >> 5) & 1);
        trigger = Pad.GetPadInputs()[clamped].lockedButton[1];
    }

    if ((trigger & 0x200) != 0) {
        unsigned int showHeap = static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(m_heapWalkerVisible)));
        m_heapWalkerVisible = static_cast<int>((showHeap >> 5) & 0xFF);
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

    C_MTXOrtho(orthoMtx, kMemoryDrawZero, kMemoryDrawOrthoBottom, kMemoryDrawZero, kMemoryDrawOrthoRight,
               kMemoryDrawZero, kMemoryDrawOrthoFar);
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

        int y = 0x20;
        int useTotalKB = 0;
        int unuseTotalKB = 0;

        CMode* modeData = m_modes;
        for (int mode = 0; mode < 3; mode++, modeData++) {
            if (((mode != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) && (mode != 2)) {
                CMemory::CStage* head = &modeData->m_activeList;
                CMemory::CStage* stage = head->m_next;
                while (stage != head) {
                    if (pass == 0) {
                        stage->drawHeapBar(y);
                    } else {
                        stage->drawHeapTitle(y);
                        if (mode == 0) {
                            useTotalKB += static_cast<unsigned int>(stage->m_heapBottom - stage->m_heapTop) >> 10;
                            unuseTotalKB +=
                                static_cast<unsigned int>(stage->m_next->m_heapTop - stage->m_heapBottom) >>
                                10;
                        }
                    }
                    y += 0xC;
                    stage = stage->m_next;
                }
            }
        }

        if (pass == 1) {
            sprintf(line, sDrawHeapUseUnuseFmt, useTotalKB, unuseTotalKB);
            Graphic.DrawDebugStringDirect(0x10, y, line, 8);

            int amemAnim = static_cast<int>(Chara.GetAmemAnimSize());
            int amemAnimKB = amemAnim / 1024;
            sprintf(line, sDrawHeapAmemAnimFmt, amemAnimKB);
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
    const char* strBase = reinterpret_cast<const char*>(sHeapBarColors);

    if ((mode == 1) && (OSGetConsoleSimulatedMemSize() != 0x3000000)) {
        return (CMemory::CStage*)nullptr;
    }

    {
        unsigned int alignedSize = (size + 0x3F) & ~0x3FU;
        CMode& modeData = m_modes[mode];
        CStage* stage = modeData.m_freeList.m_next;
        CStage* list = &modeData.m_activeList;

        if (stage == &modeData.m_freeList) {
            System.Printf(const_cast<char*>(strBase + 0x6d4));
        } else {
            do {
                CStage* next = list->m_next;
                if (static_cast<unsigned int>(list->m_heapBottom) + alignedSize <=
                    static_cast<unsigned int>(next->m_heapTop)) {

                    modeData.m_freeList.m_next = stage->m_next;
                    stage->m_prev = list;
                    stage->m_next = list->m_next;
                    list->m_next->m_prev = stage;
                    list->m_next = stage;

                    stage->m_heapTop = list->m_heapBottom;
                    stage->m_heapBottom = stage->m_heapTop + alignedSize;

                    strcpy(stage->m_allocationSourceStr,
                           source != (char*)nullptr ? source : const_cast<char*>(sEmptyAllocSourceName));
                    stage->m_allocationMode = mode;

                    if (mode != 2) {
                        unsigned char* fill = reinterpret_cast<unsigned char*>(
                            stage->m_heapTop);
                        while (fill < reinterpret_cast<unsigned char*>(
                                          stage->m_heapBottom)) {
                            *fill = 0xCD;
                            fill++;
                        }

                        stage->m_heapHead = stage->m_heapTop;
                        stage->m_heapTail = stage->m_heapBottom - 0x40;

                        stageBlockAt(stage->m_heapHead)->m_flags = 5;
                        stageBlockAt(stage->m_heapHead)->m_prev = 0;
                        stageBlockAt(stage->m_heapHead)->m_next = stageBlockAt(stage->m_heapHead) + 1;

                        (stageBlockAt(stage->m_heapHead) + 1)->m_magicStart = kMemoryBlockStartMagic;
                        (stageBlockAt(stage->m_heapHead) + 1)->m_magicEnd = kMemoryBlockEndMagic;
                        (stageBlockAt(stage->m_heapHead) + 1)->m_flags = 0;
                        (stageBlockAt(stage->m_heapHead) + 1)->m_size = stage->m_heapTail - reinterpret_cast<unsigned long>(stageBlockAt(stage->m_heapHead) + 2);
                        (stageBlockAt(stage->m_heapHead) + 1)->m_prev = stageBlockAt(stage->m_heapHead);
                        (stageBlockAt(stage->m_heapHead) + 1)->m_next = stageBlockAt(stage->m_heapTail);

                        stageBlockAt(stage->m_heapTail)->m_flags = 6;
                        stageBlockAt(stage->m_heapTail)->m_prev = stageBlockAt(stage->m_heapHead) + 1;
                        stageBlockAt(stage->m_heapTail)->m_next = 0;
                        stage->m_allocCount = 0;
                    }

                    if (mode == 2) {
                        CStage* backingStage = m_mainMemoryStage;
                        void* blockPool =
                            backingStage->alloc(sizeof(CStage::CBlock) * 0x20 + 0x10, const_cast<char*>(strBase + 0x1e8), 0x228, 0);
                        stage->m_heapHead = reinterpret_cast<unsigned long>(
                            static_cast<CStage::CBlock*>(__construct_new_array(blockPool, 0, 0, sizeof(CStage::CBlock), 0x20)));
                        stage->m_blockCount = 0;
                    }

                    stage->m_defaultParam = static_cast<unsigned int>(-1);
                    return stage;
                }
                list = next;
            } while (list != &modeData.m_activeList);

            System.Printf(const_cast<char*>(strBase + 0x708));
            HeapWalker();
        }
    }
    return (CMemory::CStage*)nullptr;
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
    const char* strBase = reinterpret_cast<const char*>(sHeapBarColors);

    System.Printf(const_cast<char*>(sHeapWalkerNewline));
    System.Printf(const_cast<char*>(sHeapWalkerSlashLine));
    System.Printf(const_cast<char*>(strBase + 0x754));
    System.Printf(const_cast<char*>(sHeapWalkerSlashLine));

    CMode* modeData = m_modes;
    for (int mode = 0; mode < 3; mode++, modeData++) {
        if ((mode != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) {
            CStage* listHead = &modeData->m_activeList;
            CStage* stage = listHead->m_next;
            while (stage != listHead) {
                stage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
                stage = stage->m_next;
            }

            System.Printf(const_cast<char*>(sHeapWalkerNewline));

            stage = listHead->m_next;
            int useTotal = 0;
            int unuseTotal = 0;
            do {
                unsigned int useKB = static_cast<unsigned int>(stage->m_heapBottom - stage->m_heapTop)
                    >> 10;
                System.Printf(const_cast<char*>(strBase + 0x764), useKB, stage->m_allocationSourceStr);
                useTotal += useKB;

                unsigned int unuseKB = static_cast<unsigned int>(
                    stage->m_next->m_heapTop - stage->m_heapBottom)
                    >> 10;
                System.Printf(const_cast<char*>(strBase + 0x778), unuseKB);
                stage = stage->m_next;
                unuseTotal += unuseKB;
            } while (stage != listHead);

            System.Printf(
                const_cast<char*>(strBase + 0x788), useTotal + unuseTotal, useTotal, unuseTotal);
        }

    }
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
    CMode& modeData = Mode(mode);

    if (mode != 2) {
        if (stageHasUnfreedBlocks(stage)) {
            System.Printf(const_cast<char*>(sStageQuitBlockUnfreedAllocFmt), stageGetSourceName(stage));
            stage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
        }
    } else {
        unsigned int heapHead = stageGetHeapHead(stage);
        if (heapHead != 0) {
            if (heapHead != 0x10) {
                operator delete[](reinterpret_cast<void*>(heapHead - 0x10));
            }
            stageSetHeapHead(stage, 0);
        }
    }

    stage->m_prev->m_next = stage->m_next;
    stage->m_next->m_prev = stage->m_prev;
    stage->m_next = modeData.m_freeList.m_next;
    modeData.m_freeList.m_next = stage;
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
    return stage->alloc(size, source != (char*)nullptr ? source : const_cast<char*>(sEmptyAllocSourceName), line, noError);
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
    freeStageBlock(ptr);
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
    int dmaId;
    dmaId = Sound.DMAEntry(0, 0, reinterpret_cast<int>(source), reinterpret_cast<int>(dest),
                           static_cast<int>(size), 0, 0);
    CStopWatch watch(const_cast<char*>(sMemoryNoNameStopwatchName));
    watch.Start();
    while (Sound.DMACheck(dmaId) != 0) {
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
    int dmaId;
    dmaId = Sound.DMAEntry(0, 1, reinterpret_cast<int>(source), reinterpret_cast<int>(dest),
                           static_cast<int>(size), 0, 0);
    CStopWatch watch(const_cast<char*>(sMemoryNoNameStopwatchName));
    watch.Start();
    float timeout = kMemoryDmaTimeout;
    while (Sound.DMACheck(dmaId) != 0) {
        watch.Stop();
        if (watch.Get() >= timeout) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(sCopyFromAMemorySyncTimeoutMsg));
            }
            Sound.CheckDriver(1);
            watch.Reset();
            watch.Start();
        } else {
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
    g_alloc_ct += 1;
    if (size == 0) {
        size = 0x40;
    }

    size = (size + 0x3F) & ~0x3F;
    unsigned int allocSize = static_cast<unsigned int>(size);
    unsigned int allocated = 0;

    for (int pass = 0; pass < 2; pass++) {
        if (pass != 0) {
            for (CBlock* node = stageBlockAt(stageGetHeapHead(this))->m_next;
                 (node->m_flags & 3) == 0;
                 node = node->m_next) {
                if (((node->m_flags & kMemoryBlockUsedFlag) == 0) &&
                    (allocSize <= static_cast<unsigned int>(node->m_size))) {
                    if (allocSize < static_cast<unsigned int>(node->m_size - 0x40)) {
                        CBlock* split = stageBlockAt(reinterpret_cast<unsigned long>(node) + allocSize);
                        split[1].m_flags = 0;
                        split[1].m_size = (node->m_size - static_cast<int>(allocSize)) - 0x40;
                        node->m_size = allocSize;
                        split[1].m_magicStart = kMemoryBlockStartMagic;
                        split[1].m_magicEnd = kMemoryBlockEndMagic;
                        split[1].m_prev = node;
                        split[1].m_next = node->m_next;
                        CBlock* split1 = split + 1;
                        node->m_next = split1;
                        split1->m_next->m_prev = split1;
                    }

                    node->m_line = static_cast<unsigned short>(line);
                    node->m_level = static_cast<unsigned char>(Memory.GetHeapWalkerLevel());
                    memset(node->m_source, 0, sizeof(node->m_source));

                    strncpy(node->m_source,
                            source != (char*)nullptr ? source : const_cast<char*>(sEmptyAllocSourceName),
                            sizeof(node->m_source) - 1);

                    allocated = reinterpret_cast<int>(payloadFromBlock(node));
                    node->m_flags = kMemoryBlockUsedFlag;
                    node->m_flags =
                        (node->m_flags & 0x0F) |
                        (Memory.GetDefaultGroup() << 4);
                    node->m_defaultParam = m_defaultParam;
                    m_allocCount += 1;
                    node->m_stage = this;
                    break;
                }

                if ((node->m_next == 0) || (node->m_prev == 0)) {
                    heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
                }
            }

            if (allocated != 0) {
                break;
            }
        }
    }

    if ((noError == 0) && (allocated == 0)) {
        System.Printf(
            const_cast<char*>(sStageAllocNoMemoryFmt), stageGetSourceName(this), allocSize,
            source != (char*)nullptr ? source : const_cast<char*>(sEmptyAllocSourceName), line);
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
    m_defaultParam = defaultParam;
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
    m_defaultParam = static_cast<unsigned long>(-1);
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
    const char* strBase = reinterpret_cast<const char*>(sHeapBarColors);
    int mode = stageGetAllocationMode(this);
    CBlock* node;
    if (mode == 2) {
        node = stageBlockAt(stageGetHeapHead(this));
    } else {
        node = stageBlockAt(stageGetHeapHead(this))->m_next;
    }

    if (flag == -1) {
        System.Printf(const_cast<char*>(sHeapWalkerNewline));
        System.Printf(const_cast<char*>(strBase + 0x364), stageGetSourceName(this));
        System.Printf(const_cast<char*>(strBase + 0x378));
        System.Printf(const_cast<char*>(strBase + 0x3d4));
    }

    int totalSize = 0;
    int freeCount = 0;
    int usedCount = 0;
    int freeSize = 0;
    int usedSize = 0;

    if (stageGetAllocationMode(this) == 2) {
        int top = m_heapTop;

        for (int i = 0; i <= m_blockCount; i++) {
            int blockTail = (i == m_blockCount) ? m_heapBottom : reinterpret_cast<int>(node->m_prev);
            int size = blockTail - top;
            if (size != 0) {
                if ((flag & 1) != 0) {
                    System.Printf(
                        const_cast<char*>(strBase + 0x430), freeCount, sHeapWalkerFree, 0, top - blockTail, totalSize, 0, 0, 0,
                        sEmptyAllocSourceName, 0);
                }
                usedSize += size;
                totalSize += size;
                freeCount++;
            }

            if (i < m_blockCount) {
                int used = reinterpret_cast<int>(node->m_next) - reinterpret_cast<int>(node->m_prev);
                if ((flag & 2) != 0) {
                    System.Printf(
                        const_cast<char*>(strBase + 0x430), usedCount, sHeapWalkerUsed,
                        node->m_level, used, totalSize, node->m_prev, 0, 0, node->m_source,
                        node->m_line);
                }
                freeSize += used;
                totalSize += used;
                top = blockTail + used;
                usedCount++;
            }

            node++;
        }
    } else {
        while ((node->m_flags & 2) == 0) {
            unsigned char nodeFlags = node->m_flags;
            int nodeGroup = node->m_defaultParam;
            if ((group == static_cast<unsigned long>(-1)) || (static_cast<unsigned long>(nodeGroup) == group)) {
                bool isUsed = (nodeFlags & 4) != 0;
                if ((isUsed && ((flag & 2) != 0)) || (!isUsed && ((flag & 1) != 0))) {
                    const char* kind = isUsed ? sHeapWalkerUsed : sHeapWalkerFree;
                    unsigned char level = isUsed ? node->m_level : 0;
                    const char* source = isUsed ? node->m_source : sEmptyAllocSourceName;
                    unsigned short line = isUsed ? node->m_line : 0;
                    int index = isUsed ? usedCount : freeCount;
                    System.Printf(
                        const_cast<char*>(strBase + 0x430), index, kind, level, node->m_size,
                        totalSize, payloadFromBlock(node), node->m_prev, node->m_next,
                        source, line);
                }
            }

            if ((group == static_cast<unsigned long>(-1)) || (static_cast<unsigned long>(nodeGroup) == group)) {
                if ((nodeFlags & 4) == 0) {
                    freeCount++;
                    usedSize += node->m_size;
                } else {
                    usedCount++;
                    freeSize += node->m_size;
                }
            }

            totalSize += reinterpret_cast<int>(node->m_next) - reinterpret_cast<int>(node);
            node = node->m_next;
        }
    }

    if (flag == -1) {
        System.Printf(const_cast<char*>(strBase + 0x45c));
        System.Printf(const_cast<char*>(strBase + 0x4b0), freeSize, usedSize);
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
    colors[0] = sHeapBarColors[0];
    colors[1] = sHeapBarColors[1];
    colors[2] = sHeapBarColors[2];
    colors[3] = sHeapBarColors[3];
    colors[4] = sHeapBarColors[4];
    colors[5] = sHeapBarColors[5];
    colors[6] = sHeapBarColors[6];
    colors[7] = sHeapBarColors[7];
    colors[8] = sHeapBarColors[8];
    colors[9] = sHeapBarColors[9];
    colors[10] = sHeapBarColors[10];
    colors[11] = sHeapBarColors[11];
    colors[12] = sHeapBarColors[12];
    colors[13] = sHeapBarColors[13];
    colors[14] = sHeapBarColors[14];
    colors[15] = sHeapBarColors[15];

    CBlock* prevNode;
    CBlock* node;
    if (m_allocationMode == 2) {
        node = stageBlockAt(stageGetHeapHead(this));
    } else {
        node = stageBlockAt(stageGetHeapHead(this))->m_next;
    }

    prevNode = node->m_prev;
    unsigned char heapBar[0x17D];
    memset(heapBar, 0xFF, 0x17D);

    int heapTop = m_heapTop;
    int heapSpan = (m_heapBottom - 0x40) - heapTop;

    while ((node->m_flags & 2) == 0) {
        CBlock* curNode = node;
        unsigned char flags = curNode->m_flags;
        bool isUsed = false;
        if (((flags & 4) != 0) && ((flags & 3) == 0)) {
            isUsed = true;
        }

        if (isUsed) {
            int fillEnd = ((reinterpret_cast<int>(curNode->m_next) - heapTop) * 0x17C) / heapSpan;
            int fillStart = ((reinterpret_cast<int>(payloadFromBlock(curNode)) - heapTop) * 0x17C) / heapSpan;
            unsigned char* dst = heapBar + fillStart;
            unsigned int fillCount = static_cast<unsigned int>(fillEnd + 1) - static_cast<unsigned int>(fillStart);

            if (fillStart <= fillEnd) {
                unsigned int loop = fillCount >> 3;
                if (loop != 0) {
                    do {
                        dst[0] = static_cast<unsigned char>(curNode->m_flags >> 4);
                        dst[1] = static_cast<unsigned char>(curNode->m_flags >> 4);
                        dst[2] = static_cast<unsigned char>(curNode->m_flags >> 4);
                        dst[3] = static_cast<unsigned char>(curNode->m_flags >> 4);
                        dst[4] = static_cast<unsigned char>(curNode->m_flags >> 4);
                        dst[5] = static_cast<unsigned char>(curNode->m_flags >> 4);
                        dst[6] = static_cast<unsigned char>(curNode->m_flags >> 4);
                        dst[7] = static_cast<unsigned char>(curNode->m_flags >> 4);
                        dst += 8;
                        loop--;
                    } while (loop != 0);

                    fillCount &= 7;
                    if (fillCount == 0) {
                        goto checkHeapNode;
                    }
                }

                do {
                    *dst = static_cast<unsigned char>(curNode->m_flags >> 4);
                    dst++;
                    fillCount--;
                } while (fillCount != 0);
            }
        }

checkHeapNode:
        if ((static_cast<unsigned int>(curNode->m_size) !=
             static_cast<unsigned int>(reinterpret_cast<int>(curNode->m_next) - reinterpret_cast<int>(payloadFromBlock(curNode)))) ||
            (static_cast<unsigned int>(reinterpret_cast<int>(curNode->m_prev)) !=
             static_cast<unsigned int>(reinterpret_cast<int>(prevNode)))) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(sHeapCorruptAbortDrawMsg));
            }
            return;
        }

        prevNode = curNode;
        node = curNode->m_next;
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
    CBlock* node = (stageGetAllocationMode(this) == 2) ?
        stageBlockAt(stageGetHeapHead(this)) :
        stageBlockAt(stageGetHeapHead(this))->m_next;
    unsigned int totalUnuse = 0;
    unsigned int maxUnuse = 0;
    CBlock* prev = node->m_prev;
    unsigned int heapTop = m_heapTop;
    char line[264];

    while ((node->m_flags & 2) == 0) {
        if ((node->m_flags & kMemoryBlockUsedFlag) == 0) {
            int blockStart = reinterpret_cast<int>(payloadFromBlock(node)) - heapTop;
            int blockEnd = reinterpret_cast<int>(node->m_next) - heapTop;
            int blockSize = blockEnd - blockStart;
            totalUnuse += blockSize;
            if (static_cast<int>(maxUnuse) < blockSize) {
                maxUnuse = blockSize;
            }
        }

        if ((node->m_size != reinterpret_cast<unsigned int>(node->m_next) - reinterpret_cast<int>(payloadFromBlock(node))) ||
            (node->m_prev != prev)) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(sHeapCorruptAbortDrawMsg));
            }
            return;
        }

        prev = node;
        node = node->m_next;
    }

    int srcLen = strlen(m_allocationSourceStr);
    int sourceOffset = srcLen - 12;
    sourceOffset &= ~(sourceOffset >> 31);
    strcpy(line, m_allocationSourceStr + sourceOffset);
    Graphic.DrawDebugStringDirect(0x10, y, line, 8);

    sprintf(line, s_drawHeapTitleFmt, m_allocCount,
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
    CBlock* node;
    if (m_allocationMode == 2) {
        node = stageBlockAt(stageGetHeapHead(this));
    } else {
        node = stageBlockAt(stageGetHeapHead(this))->m_next;
    }
    int total = 0;

    while ((node->m_flags & 2) == 0) {
        if ((node->m_flags & kMemoryBlockUsedFlag) == 0) {
            total += node->m_size;
        }
        node = node->m_next;
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
            freeStageBlock(reinterpret_cast<void*>(cacheData));
            entry.m_cacheData = 0;
        }
        unsigned long workData = reinterpret_cast<unsigned long>(entry.m_workData);
        if (workData != 0) {
            entry.m_workData = 0;
        }
    } else {
        unsigned long workData = reinterpret_cast<unsigned long>(entry.m_workData);
        if (workData != 0) {
            freeStageBlock(reinterpret_cast<void*>(workData));
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
void CAmemCacheSet::RefCnt0Up(int index)
{
    CAmemCache& entry = cacheEntryAt(this, index);
    entry.m_refCnt0++;
    s_RefCnt0Compare++;
    if (s_MaxRefCnt0Compare < s_RefCnt0Compare) {
        s_MaxRefCnt0Compare = s_RefCnt0Compare;
    }
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
    while (true) {
        CAmemCache& entry = cacheEntryAt(this, index);
        unsigned int data;

        if (entry.m_cacheData == 0) {
            if (entry.m_dmaCopy != 0) {
                char* allocSource = source;
                if (allocSource == 0) {
                    allocSource = const_cast<char*>(sEmptyAllocSourceName);
                }

                entry.m_cacheData =
                    m_rStage->alloc(static_cast<unsigned long>(entry.m_size), allocSource, static_cast<unsigned long>(line), 1);
                if (entry.m_cacheData == 0) {
                    data = 0;
                } else {
                    int dmaId = Sound.DMAEntry(0, 1, reinterpret_cast<int>(entry.m_cacheData),
                                               reinterpret_cast<int>(entry.m_workData), entry.m_size, 0, 0);
                    CStopWatch watch(const_cast<char*>(sMemoryNoNameStopwatchName));
                    watch.Start();
                    float timeout = kMemoryDmaTimeout;
                    while (Sound.DMACheck(dmaId) != 0) {
                        watch.Stop();
                        if (watch.Get() >= timeout) {
                            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                                System.Printf(const_cast<char*>(sGetDataTimeoutBanner));
                            }
                            Sound.CheckDriver(1);
                            watch.Reset();
                            watch.Start();
                        } else {
                            watch.Start();
                        }
                    }
                    data = reinterpret_cast<int>(entry.m_cacheData);
                }
            } else {
                entry.m_cacheData = entry.m_workData;
                data = reinterpret_cast<int>(entry.m_cacheData);
            }
        } else {
            data = 0;
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
    short index;

    for (int i = 0; i < m_cacheCount; i++) {
        if (cacheEntryAt(this, i).m_inUse == 0) {
            index = static_cast<short>(i);
            goto found;
        }
    }
    index = -1;

found:
    if (index == -1) {
        return -1;
    }

    CAmemCache& entry = cacheEntryAt(this, index);
    int allocSize = (static_cast<unsigned int>(size) + 0x1F) & ~0x1F;
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
            int dmaId = Sound.DMAEntry(0, 0, reinterpret_cast<int>(src),
                                       reinterpret_cast<int>(entry.m_workData), entry.m_size, 0, 0);
            CStopWatch watch(const_cast<char*>(sMemoryNoNameStopwatchName));
            watch.Start();
            while (Sound.DMACheck(dmaId) != 0) {
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
        int dmaId = Sound.DMAEntry(0, 0, reinterpret_cast<int>(src),
                                   reinterpret_cast<int>(entry.m_workData), entry.m_size, 0, 0);
        CStopWatch watch(const_cast<char*>(sMemoryNoNameStopwatchName));
        watch.Start();
        while (Sound.DMACheck(dmaId) != 0) {
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
    if (entry.m_refCount >= 0xFFFF) {
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(sAmemCacheAddRefFmt), static_cast<int>(index));
        }

        for (int i = 0; i < m_cacheCount; i++) {
            CAmemCache& current = cacheEntryAt(this, i);
            unsigned int data = reinterpret_cast<int>(current.m_cacheData);
            if ((current.m_inUse != 0) || (data != 0)) {
                if (static_cast<unsigned int>(System.m_execParam) >= 3) {
                    System.Printf(
                        const_cast<char*>(sAmemCacheEntryFmt), i, cacheStateName(current),
                        cacheTypeName(current), current.m_refCount, current.m_priority, data);
                }
            }
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(sAmemCacheSeparator));
        }

        void (*overflowHook)(int) = reinterpret_cast<void (*)(int)>(m_overflowHook);
        if (overflowHook != 0) {
            overflowHook(static_cast<unsigned int>(index));
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
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(sAmemCacheAddRefFmt));
        }

        for (int i = 0; i < m_cacheCount; i++) {
            CAmemCache& cache = cacheEntryAt(this, i);
            if (((cache.m_inUse != 0) || (cache.m_cacheData != 0)) && (static_cast<unsigned int>(System.m_execParam) >= 3)) {
                System.Printf(
                    const_cast<char*>(sAmemCacheEntryFmt), i, cacheStateName(cache),
                    cacheTypeName(cache), cache.m_refCount,
                    cache.m_priority, reinterpret_cast<int>(cache.m_cacheData));
            }
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(sAmemCacheSeparator));
        }

        void (*onUnderflow)(int) = reinterpret_cast<void (*)(int)>(m_overflowHook);
        if (onUnderflow != 0) {
            onUnderflow(static_cast<unsigned int>(index));
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
    const char* strBase = reinterpret_cast<const char*>(sHeapBarColors);
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
            freeStageBlock(bestEntry->m_cacheData);
            bestEntry->m_cacheData = 0;
        }

        unsigned int allocated = reinterpret_cast<int>(m_rStage->alloc(size, const_cast<char*>(strBase + 0x1e8), 0x86D, 1));
        if (allocated != 0) {
            freeStageBlock(reinterpret_cast<void*>(allocated));
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
            if (static_cast<unsigned int>(System.m_execParam) >= 3) {
                System.Printf(const_cast<char*>(strBase + 0x4c));
            }

            for (unsigned int i = 0; i < m_cacheCount; i++) {
                CAmemCache& entry = cacheEntryAt(this, i);
                int data = reinterpret_cast<int>(entry.m_cacheData);
                if (((entry.m_inUse != 0) || (data != 0)) && (static_cast<int>(System.m_execParam) >= 3)) {
                    System.Printf(
                        const_cast<char*>(strBase + 0xd8), i, cacheStateName(entry),
                        cacheTypeName(entry), entry.m_refCount, entry.m_priority, data);
                }
            }

            if (static_cast<unsigned int>(System.m_execParam) >= 3) {
                System.Printf(const_cast<char*>(sAmemCacheSeparator));
            }
            m_rStage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
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
            void* data = entry.m_cacheData;
            if (data != 0) {
                freeStageBlock(reinterpret_cast<void*>(data));
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
        if ((m_cacheTable[i].m_inUse != 0) && (m_cacheTable[i].m_refCount == 0) &&
            (m_cacheTable[i].m_cacheData != 0) && (static_cast<unsigned int>(m_cacheTable[i].m_priority) != 0)) {
            m_cacheTable[i].m_priority--;
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
    for (int i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = cacheEntryAt(this, i);
        entry.m_refCnt0 = entry.m_refCount;
    }

    s_RefCnt0Compare = 0;
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
    const char* dumpBase = reinterpret_cast<const char*>(sHeapBarColors);

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
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(sAmemCacheAddRefFmt));
    }

    for (int i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = cacheEntryAt(this, i);
        if ((entry.m_inUse != 0 || entry.m_cacheData != 0) && (static_cast<unsigned int>(System.m_execParam) >= 3)) {
            System.Printf(
                const_cast<char*>(sAmemCacheEntryFmt), i, cacheStateName(entry),
                cacheTypeName(entry), entry.m_refCount, entry.m_priority, reinterpret_cast<int>(entry.m_cacheData));
        }
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(sAmemCacheSeparator));
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAmemCacheSet::DumpCache()
{
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(sAmemCacheAddRefFmt));
    }

    for (int i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = cacheEntryAt(this, i);
        if (((entry.m_inUse != 0) || (entry.m_cacheData != 0)) && (static_cast<unsigned int>(System.m_execParam) >= 3)) {
            System.Printf(
                const_cast<char*>(sAmemCacheEntryFmt), i, cacheStateName(entry),
                cacheTypeName(entry), entry.m_refCount, entry.m_priority, reinterpret_cast<int>(entry.m_cacheData));
        }
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(sAmemCacheSeparator));
    }
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
    CBlock* node;

    if (m_allocationMode == 2) {
        node = stageBlockAt(stageGetHeapHead(this));
    } else {
        node = stageBlockAt(stageGetHeapHead(this))->m_next;
    }

    heapTotal = 0;
    heapUse = 0;
    heapUnuse = 0;

    if (m_allocationMode == 2) {
        top = m_heapTop;

        for (i = 0; i <= m_blockCount; i++, node++) {
            if (m_blockCount == i) {
                blockTail = m_heapBottom;
            } else {
                blockTail = reinterpret_cast<int>(node->m_prev);
            }

            freeSize = blockTail - top;
            if (freeSize != 0) {
                heapUnuse += freeSize;
                heapTotal += freeSize;
            }

            if (i < m_blockCount) {
                usedSize = reinterpret_cast<int>(node->m_next) - reinterpret_cast<int>(node->m_prev);
                heapUse += usedSize;
                top = blockTail + usedSize;
                heapTotal += usedSize;
            }

        }
        return;
    }

    while ((node->m_flags & 2) == 0) {
        if ((node->m_flags & kMemoryBlockUsedFlag) != 0) {
            heapUse += node->m_size;
        } else {
            heapUnuse += node->m_size;
        }

        heapTotal += reinterpret_cast<int>(node->m_next) - reinterpret_cast<int>(node);
        node = node->m_next;
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
    m_cacheData = 0;
    m_workData = 0;
    m_refCount = 0;
    m_size = 0;
    m_inUse = 0;
    m_priority = 0;
    m_dmaCopy = 1;
    m_type = 0xFF;
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
