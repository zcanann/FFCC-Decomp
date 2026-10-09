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
inline void* operator new[](unsigned long size, CMemory::CStage* stage, const char* file, int line)
{
    return stage->alloc(size, const_cast<char*>(file), line, 0);
}

#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CMemory Memory;

static const char* amem_typeName[] = {
    "TEXTURE",
    "MODEL  ",
    "PDT    ",
};
static const char* amem_stateName[2] = {
    "USE  ",
    "NOUSE",
};

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
            System.Printf(const_cast<char*>("CMemory.CStage.free: \211\363\202\352\202\304\202\242\202\334\202\267\201Baddress = %08x file = %s line = %d\n"), ptr, block->m_source, block->m_line);
        }

        block->m_flags = static_cast<unsigned char>(block->m_flags & ~kMemoryBlockUsedFlag);

        if ((block->m_next->m_flags & kMemoryBlockUsedFlag) == 0) {
            block->m_size += block->m_next->m_size + sizeof(CMemory::CStage::CBlock);
            block->m_next->m_next->m_prev = block;
            block->m_next = block->m_next->m_next;
        }

        CMemory::CStage::CBlock* prevBlock = block->m_prev;
        if ((prevBlock->m_flags & kMemoryBlockUsedFlag) == 0) {
            prevBlock->m_size += block->m_size + sizeof(CMemory::CStage::CBlock);
            block->m_prev->m_next = block->m_next;
            block->m_next->m_prev = block->m_prev;
        }

        block->m_stage->m_allocCount -= 1;
    }
}

static inline void freeStageBlockBase(void* ptr)
{
    if (ptr != (void*)nullptr) {
        CMemory::CStage::CBlock* block = blockFromPayload(ptr);
        if ((block->m_magicStart != kMemoryBlockStartMagic) ||
            (block->m_magicEnd != kMemoryBlockEndMagic)) {
            System.Printf(const_cast<char*>("CMemory.CStage.free: \211\363\202\352\202\304\202\242\202\334\202\267\201Baddress = %08x file = %s line = %d\n"), ptr, block->m_source, block->m_line);
        }

        block->m_flags = static_cast<unsigned char>(block->m_flags & ~kMemoryBlockUsedFlag);

        if ((block->m_next->m_flags & kMemoryBlockUsedFlag) == 0) {
            block->m_size += block->m_next->m_size + sizeof(CMemory::CStage::CBlock);
            block->m_next->m_next->m_prev = block;
            block->m_next = block->m_next->m_next;
        }

        CMemory::CStage::CBlock* prevBlock = block->m_prev;
        if ((prevBlock->m_flags & kMemoryBlockUsedFlag) == 0) {
            prevBlock->m_size += block->m_size + sizeof(CMemory::CStage::CBlock);
            block->m_prev->m_next = block->m_next;
            block->m_next->m_prev = block->m_prev;
        }

        blockFromPayload(ptr)->m_stage->m_allocCount -= 1;
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

static inline void releaseStageBuffer(unsigned int ptr)
{
    if (ptr != 0) {
        operator delete[](reinterpret_cast<void*>(ptr - 0x10));
    }
}

static inline void stageReleaseMode2Buffer(CMemory::CStage* stage)
{
    unsigned int ptr = static_cast<unsigned int>(stageGetHeapHead(stage));
    if (ptr != 0) {
        releaseStageBuffer(ptr);
        stageSetHeapHead(stage, 0);
    }
}

static inline void releaseStageBufferBase(unsigned int ptr) throw()
{
    if (ptr != 0) {
        freeStageBlockBase(reinterpret_cast<void*>(ptr - 0x10));
    }
}

static inline void stageReleaseMode2BufferBase(CMemory::CStage* stage)
{
    unsigned int ptr = static_cast<unsigned int>(stageGetHeapHead(stage));
    if (ptr != 0) {
        releaseStageBufferBase(ptr);
        stageSetHeapHead(stage, 0);
    }
}

static inline void stageDestroyAndPool(CMemory* memory, CMemory::CStage* stage)
{
    CMemory::CMode& modeData = memory->Mode(stage->m_allocationMode);

    if (stage->m_allocationMode != 2) {
        if (stageHasUnfreedBlocks(stage)) {
            System.Printf(const_cast<char*>("CMemory.CStage.quitBlock: \212J\225\372\202\263\202\352\202\304\202\242\202\310\202\242alloc\202\252\202\240\202\350\202\334\202\267\201B%s\n"), stageGetSourceName(stage));
            stage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
        }
    } else {
        stageReleaseMode2BufferBase(stage);
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
    return stage->alloc(size, file != (char*)nullptr ? file : const_cast<char*>(""), line, 0);
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
    return stage->alloc(size, file != (char*)nullptr ? file : const_cast<char*>(""), line, 0);
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
    unsigned char* bytes = reinterpret_cast<unsigned char*>(data);
    unsigned int checksum = 0x12345678;
    int i;

    for (i = size; i != 0; i--) {
        checksum += *bytes++;
    }

    return checksum;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 88b
 * EN Address: UNUSED
 * EN Size: 112b
 * JP Address: TODO
 * JP Size: TODO
 */
void* operator new(unsigned long size)
{
    System.Printf("operator new: \216g\227p\202\305\202\253\202\334\202\271\202\361\201B\n");
    return nullptr;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* operator new[](unsigned long size)
{
    System.Printf("operator new: \216g\227p\202\305\202\253\202\334\202\271\202\361\201B\n");
    return nullptr;
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

    CStage* stage = CreateStage(0x2000, "CMemory.current", 0);
    m_currentMemoryStage = stage;

    stage = CreateStage(0x4000, "CMemory.memory", 0);
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
                        System.Printf(const_cast<char*>("CMemory.Quit: \203X\203e\201[\203W%s\202\252\212J\225\372\202\263\202\352\202\304\202\242\202\334\202\271\202\361\201B\n"), stage->m_allocationSourceStr);
                        stageDestroyAndPool(this, stage);
                    }
                } else {
                    System.Printf(const_cast<char*>("CMemory.Quit: \203X\203e\201[\203W%s\202\252\212J\225\372\202\263\202\352\202\304\202\242\202\334\202\271\202\361\201B\n"), stage->m_allocationSourceStr);
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
    unsigned short trigger = Pad.GetDebugButtonDown(0);

    if ((trigger & 0x200) != 0) {
        m_heapWalkerVisible = !m_heapWalkerVisible;
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

    System.Printf(const_cast<char*>("\n"));
    System.Printf(const_cast<char*>("//\n"));
    System.Printf(const_cast<char*>("// Heap Walker\n"));
    System.Printf(const_cast<char*>("//\n"));

    CMode* modeData = m_modes;
    for (int mode = 0; mode < 3; mode++, modeData++) {
        if ((mode != 1) || (OSGetConsoleSimulatedMemSize() == 0x3000000)) {
            CStage* listHead = &modeData->m_activeList;
            CStage* stage = listHead->m_next;
            while (stage != listHead) {
                stage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
                stage = stage->m_next;
            }

            System.Printf(const_cast<char*>("\n"));

            stage = listHead->m_next;
            int useTotal = 0;
            int unuseTotal = 0;
            unsigned int kb;
            do {
                kb = static_cast<unsigned int>(stage->m_heapBottom - stage->m_heapTop) >> 10;
                System.Printf(const_cast<char*>("Use  : %5dKB %s\n"), kb, stage->m_allocationSourceStr);
                useTotal += kb;

                kb = static_cast<unsigned int>(stage->m_next->m_heapTop - stage->m_heapBottom) >> 10;
                System.Printf(const_cast<char*>("Unuse: %5dKB\n"), kb);
                stage = stage->m_next;
                unuseTotal += kb;
            } while (stage != listHead);

            System.Printf(
                const_cast<char*>("Total: %5dKB Use =%5dKB Unuse =%5dKB\n"), useTotal + unuseTotal, useTotal, unuseTotal);
        }

    }
}

/*
 * --INFO--
 * PAL Address: 0x8001EC94
 * PAL Size: 764b
 * EN Address: 0x80025C60
 * EN Size: 792b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::Draw()
{
    if (m_heapWalkerVisible == 0) {
        return;
    }

    Mtx44 orthoMtx;
    Mtx modelMtx;
    char line[0x100];

    C_MTXOrtho(orthoMtx, 0.0f, 448.0f, 0.0f, 640.0f,
               0.0f, -100.0f);
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

        CMode* modeData = m_modes;
        int y = 0x20;
        int unuseTotalKB = 0;
        int useTotalKB = 0;

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
            sprintf(line, "USE=%d UNUSE=%d", useTotalKB, unuseTotalKB);
            Graphic.DrawDebugStringDirect(0x10, y, line, 8);

            int amemAnim = static_cast<int>(Chara.GetAmemOffset());
            int amemAnimKB = amemAnim / 1024;
            sprintf(line, "AMEM ANIM=%d", amemAnimKB);
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
 * PAL Address: UNUSED
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMemory::CStage::initBlock()
{
    unsigned char* fill = reinterpret_cast<unsigned char*>(m_heapTop);
    while (fill < reinterpret_cast<unsigned char*>(m_heapBottom)) {
        *fill = 0xCD;
        fill++;
    }

    m_heapHead = m_heapTop;
    m_heapTail = m_heapBottom - 0x40;

    stageBlockAt(m_heapHead)->m_flags = 5;
    stageBlockAt(m_heapHead)->m_prev = 0;
    stageBlockAt(m_heapHead)->m_next = stageBlockAt(m_heapHead) + 1;

    (stageBlockAt(m_heapHead) + 1)->m_magicStart = kMemoryBlockStartMagic;
    (stageBlockAt(m_heapHead) + 1)->m_magicEnd = kMemoryBlockEndMagic;
    (stageBlockAt(m_heapHead) + 1)->m_flags = 0;
    (stageBlockAt(m_heapHead) + 1)->m_size = m_heapTail - reinterpret_cast<unsigned long>(stageBlockAt(m_heapHead) + 2);
    (stageBlockAt(m_heapHead) + 1)->m_prev = stageBlockAt(m_heapHead);
    (stageBlockAt(m_heapHead) + 1)->m_next = stageBlockAt(m_heapTail);

    stageBlockAt(m_heapTail)->m_flags = 6;
    stageBlockAt(m_heapTail)->m_prev = stageBlockAt(m_heapHead) + 1;
    stageBlockAt(m_heapTail)->m_next = 0;
    m_allocCount = 0;
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

    if ((mode == 1) && (OSGetConsoleSimulatedMemSize() != 0x3000000)) {
        return (CMemory::CStage*)nullptr;
    }

    {
        size = (size + 0x3F) & ~0x3FU;
        unsigned int alignedSize = static_cast<unsigned int>(size);
        CStage* next;
        CMode& modeData = m_modes[mode];
        CStage* stage = modeData.m_freeList.m_next;

        if (stage == &modeData.m_freeList) {
            System.Printf(const_cast<char*>("CMemory.CreateStage: \203X\203e\201[\203W\202\360\215\354\220\254\202\305\202\253\202\334\202\271\202\361\201B\n"));
            return (CMemory::CStage*)nullptr;
        } else {
            CStage* list = &modeData.m_activeList;
            do {
                next = list->m_next;
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
                           source != (char*)nullptr ? source : const_cast<char*>(""));
                    stage->m_allocationMode = mode;

                    if (mode != 2) {
                        stage->initBlock();
                    }

                    if (mode == 2) {
                        CStage* backingStage = m_mainMemoryStage;
                        void* blockPool =
                            backingStage->alloc(sizeof(CStage::CBlock) * 0x20 + 0x10, const_cast<char*>("memory.cpp"), 0x228, 0);
                        stage->m_heapHead = reinterpret_cast<unsigned long>(
                            static_cast<CStage::CBlock*>(__construct_new_array(blockPool, 0, 0, sizeof(CStage::CBlock), 0x20)));
                        stage->m_blockCount = 0;
                    }

                    stage->m_defaultParam = static_cast<unsigned int>(-1);
                    return stage;
                }
                list = next;
            } while (list != &modeData.m_activeList);

            System.Printf(const_cast<char*>("CMemory.CreateStage: \203\201\203\202\203\212\202\252\221\253\202\350\202\334\202\271\202\361\201B\n"));
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
    CMode& modeData = m_modes[stage->m_allocationMode];

    if (stage->m_allocationMode != 2) {
        stage->quitBlock();
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
 * PAL Address: 0x8001E7F4
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMemory::_Alloc(unsigned long size, CMemory::CStage* stage, char* source, int line, int noError)
{
    return stage->alloc(size, source != (char*)nullptr ? source : const_cast<char*>(""), line, noError);
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
    CStopWatch watch(const_cast<char*>("no name"));
    watch.Start();
    while (!IsCopyCompleted(dmaId)) {
        watch.Stop();
        watch.Get();
        watch.Start();
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001E4F8
 * PAL Size: 296b
 * EN Address: 0x8001E2EC
 * EN Size: 296b
 * JP Address: 0x8001DD60
 * JP Size: 280b
 */
void CMemory::CopyFromAMemorySync(void* source, void* dest, unsigned long size)
{
    int dmaId;
    dmaId = Sound.DMAEntry(0, 1, reinterpret_cast<int>(source), reinterpret_cast<int>(dest),
                           static_cast<int>(size), 0, 0);
    CStopWatch watch(const_cast<char*>("no name"));
    watch.Start();
    while (!IsCopyCompleted(dmaId)) {
        watch.Stop();
        if (watch.Get() >= 9000.0f) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>("===================================================================\n                          CopyFromAMemorySync  TimeOut\n===================================================================\n"));
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
 * PAL Address: UNUSED
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::CStage::quitBlock()
{
    if (stageHasUnfreedBlocks(this)) {
        System.Printf(const_cast<char*>("CMemory.CStage.quitBlock: \212J\225\372\202\263\202\352\202\304\202\242\202\310\202\242alloc\202\252\202\240\202\350\202\334\202\267\201B%s\n"), stageGetSourceName(this));
        heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
    }
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CMemory::IsCopyCompleted(int dmaId)
{
    return Sound.DMACheck(dmaId) == 0;
}

/*
 * --INFO--
 * PAL Address: 0x8001E2EC
 * PAL Size: 524b
 * EN Address: 0x80026B4C
 * EN Size: 956b
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
    unsigned int allocated = 0;

    for (int pass = 0; pass < 2; pass++) {
        if (pass != 0) {
            for (CBlock* node = stageBlockAt(stageGetHeapHead(this))->m_next;
                 (node->m_flags & 3) == 0;
                 node = node->m_next) {
                if (((node->m_flags & kMemoryBlockUsedFlag) == 0) &&
                    (size <= static_cast<unsigned int>(node->m_size))) {
                    if (size < static_cast<unsigned int>(node->m_size - 0x40)) {
                        CBlock* split =
                            reinterpret_cast<CBlock*>(static_cast<unsigned char*>(payloadFromBlock(node)) + size);
                        split->m_flags = 0;
                        split->m_size = (node->m_size - static_cast<int>(size)) - 0x40;
                        node->m_size = size;
                        split->m_magicStart = kMemoryBlockStartMagic;
                        split->m_magicEnd = kMemoryBlockEndMagic;
                        split->m_prev = node;
                        split->m_next = node->m_next;
                        node->m_next = split;
                        split->m_next->m_prev = split;
                    }

                    node->m_line = static_cast<unsigned short>(line);
                    node->m_level = static_cast<unsigned char>(Memory.GetHeapWalkerLevel());
                    memset(node->m_source, 0, sizeof(node->m_source));

                    strncpy(node->m_source,
                            source != (char*)nullptr ? source : const_cast<char*>(""),
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
            const_cast<char*>("CMemory.CStage.alloc: stage_name=%s \203\201\203\202\203\212\202\252\221\253\202\350\202\334\202\271\202\361\201Bsize = %d file = %s line = %d\n"), stageGetSourceName(this), size,
            source != (char*)nullptr ? source : const_cast<char*>(""), line);
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
 * PAL Address: UNUSED
 * PAL Size: 588b
 * EN Address: UNUSED
 * EN Size: 792b
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMemory::CStage::allocAMemory(unsigned long size, char* source, unsigned long line)
{
    void* allocated = alloc(size, source, line, 1);
    if (allocated == nullptr) {
        System.Printf("CMemory.CStage.allocAMemory: stage_name=%s \203\201\203\202\203\212\202\252\221\253\202\350\202\334\202\271\202\361\201Bsize = %d file = %s line = %d\n", stageGetSourceName(this), size, source, line);
    }
    return allocated;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 300b
 * EN Address: UNUSED
 * EN Size: 380b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMemory::CStage::freeAMemory(void* ptr)
{
    if (ptr == nullptr) {
        System.Printf("CMemory.CStage.freeAMemory: stage_name=%s %x \202\261\202\314\203A\203h\203\214\203X\202\315\212m\225\333\202\263\202\352\202\304\202\242\202\334\202\271\202\361\201B\n", stageGetSourceName(this), ptr);
        return;
    }
    free(ptr);
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
    CBlock* node;
    if (mode == 2) {
        node = stageBlockAt(stageGetHeapHead(this));
    } else {
        node = stageBlockAt(stageGetHeapHead(this))->m_next;
    }

    if (flag == -1) {
        System.Printf(const_cast<char*>("\n"));
        System.Printf(const_cast<char*>("Stage Name = %s\n"), stageGetSourceName(this));
        System.Printf(const_cast<char*>("No  Flag Level Size    Total   Address  Prev     Next     Name                     Line \n"));
        System.Printf(const_cast<char*>("--- ---- ----- ------- ------- -------- -------- -------- ------------------------ -----\n"));
    }

    int totalSize = 0;
    int freeSize = 0;
    int usedSize = 0;
    int usedCount = 0;
    int freeCount = 0;

    if (stageGetAllocationMode(this) == 2) {
        int showFree = flag & 1;
        int blockTail;
        int i;
        int showUsed = flag & 2;
        int size;
        int top = m_heapTop;

        for (i = 0; i <= m_blockCount; i++, node++) {
            blockTail = (m_blockCount == i) ? m_heapBottom : reinterpret_cast<int>(node->m_prev);
            size = blockTail - top;
            if (size != 0) {
                if (showFree != 0) {
                    System.Printf(
                        const_cast<char*>("%3d %s %5d %7d %7d %08x %08x %08x %-24s %d\n"), freeCount, "FREE", 0, top - blockTail, totalSize, 0, 0, 0,
                        "", 0);
                }
                usedSize += size;
                totalSize += size;
                freeCount++;
            }

            if (i < m_blockCount) {
                int used = reinterpret_cast<int>(node->m_next) - reinterpret_cast<int>(node->m_prev);
                if (showUsed != 0) {
                    System.Printf(
                        const_cast<char*>("%3d %s %5d %7d %7d %08x %08x %08x %-24s %d\n"), usedCount, "USE ",
                        node->m_level, used, totalSize, node->m_prev, 0, 0, node->m_source,
                        node->m_line);
                }
                freeSize += used;
                totalSize += used;
                top = blockTail + used;
                usedCount++;
            }
        }
    } else {
        while ((node->m_flags & 2) == 0) {
            if ((group == static_cast<unsigned long>(-1)) || (group == node->m_defaultParam)) {
                if ((((node->m_flags & 4) != 0) && ((flag & 2) != 0)) || (((node->m_flags & 4) == 0) && ((flag & 1) != 0))) {
                    int line = ((node->m_flags & 4) != 0) ? node->m_line : 0;
                    const char* source = ((node->m_flags & 4) != 0) ? node->m_source : "";
                    int level = ((node->m_flags & 4) != 0) ? node->m_level : 0;
                    const char* kind = ((node->m_flags & 4) != 0) ? "USE " : "FREE";
                    int index = ((node->m_flags & 4) != 0) ? usedCount : freeCount;
                    System.Printf(
                        const_cast<char*>("%3d %s %5d %7d %7d %08x %08x %08x %-24s %d\n"), index, kind, level, node->m_size,
                        totalSize, payloadFromBlock(node), node->m_prev, node->m_next,
                        source, line);
                }
            }

            if ((group == static_cast<unsigned long>(-1)) || (group == node->m_defaultParam)) {
                if ((node->m_flags & 4) != 0) {
                    usedCount++;
                    freeSize += node->m_size;
                } else {
                    freeCount++;
                    usedSize += node->m_size;
                }
            }

            totalSize += reinterpret_cast<int>(node->m_next) - reinterpret_cast<int>(node);
            node = node->m_next;
        }
    }

    if (flag == -1) {
        System.Printf(const_cast<char*>("--- ---- ----- ------- -------- -------- -------- ------------------------ -----\n"));
        System.Printf(const_cast<char*>("USE = %d UNUSE = %d\n"), freeSize, usedSize);
    }

    return freeSize;
}

/*
 * --INFO--
 * PAL Address: 0x8001DB48
 * PAL Size: 1088b
 * EN Address: 0x8001D93C
 * EN Size: 1088b
 * JP Address: 0x8001D388
 * JP Size: 1128b
 */
void CMemory::CStage::drawHeapBar(int y)
{
    float z = 0.0f;
    _GXColor color;
    unsigned int colors[16] = {
        0xFFFFFF80, 0xFF808080, 0x80FF8080, 0xC0C0FF80,
        0xFFFF8080, 0xFF80FF80, 0x80FFFF80, 0x80808080,
        0x80000080, 0x00800080, 0x00008080, 0x80800080,
        0x80008080, 0x00808080, 0xFF800080, 0xFF008080,
    };

    CBlock* prevNode;
    CBlock* node;
    CBlock* head;
    if (m_allocationMode == 2) {
        head = stageBlockAt(stageGetHeapHead(this));
    } else {
        head = stageBlockAt(stageGetHeapHead(this))->m_next;
    }

    prevNode = head->m_prev;
    node = head;
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

            for (int i = fillStart; i <= fillEnd; i++) {
                heapBar[i] = static_cast<unsigned char>(curNode->m_flags >> 4);
            }
        }

        if ((static_cast<unsigned int>(curNode->m_size) !=
             static_cast<unsigned int>(reinterpret_cast<int>(curNode->m_next) - reinterpret_cast<int>(payloadFromBlock(curNode)))) ||
            (static_cast<unsigned int>(reinterpret_cast<int>(curNode->m_prev)) !=
             static_cast<unsigned int>(reinterpret_cast<int>(prevNode)))) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>("\203q\201[\203v\202\252\210\331\217\355\202\310\202\314\202\305\225`\211\346\202\360\222\206\216~\202\265\202\334\202\267\201B\n"));
            }
            return;
        }

        prevNode = curNode;
        node = curNode->m_next;
    }

    int drawColor = heapBar[0];
    int segmentStart = 0;
    unsigned char* colorPtr = heapBar;
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
            GXPosition3f32(static_cast<float>(segmentStart + 0x80), static_cast<float>(y), z);
            GXColor1u32(*reinterpret_cast<u32*>(&color));
            GXPosition3f32(static_cast<float>(x + 0x80), static_cast<float>(y), z);
            GXColor1u32(*reinterpret_cast<u32*>(&color));
            GXPosition3f32(static_cast<float>(segmentStart + 0x80), static_cast<float>(y + 8), z);
            GXColor1u32(*reinterpret_cast<u32*>(&color));
            GXPosition3f32(static_cast<float>(x + 0x80), static_cast<float>(y + 8), z);
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
    CBlock* block = (m_allocationMode == 2) ? reinterpret_cast<CBlock*>(m_heapHead)
                                            : reinterpret_cast<CBlock*>(m_heapHead)->m_next;
    int unuse = 0;
    int maxUnuse = 0;
    CBlock* prev = block->m_prev;
    unsigned long top = m_heapTop;
    char buf[0x108];

    while ((block->m_flags & 2) == 0) {
        if ((block->m_flags & kMemoryBlockUsedFlag) == 0) {
            int start = reinterpret_cast<unsigned long>(block + 1) - top;
            int end = reinterpret_cast<unsigned long>(block->m_next) - top;
            int size = end - start;
            unuse += size;
            if (maxUnuse < size) {
                maxUnuse = size;
            }
        }

        unsigned long blockSize = reinterpret_cast<unsigned long>(block->m_next) - reinterpret_cast<unsigned long>(block + 1);
        if ((block->m_size != blockSize) || (block->m_prev != prev)) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>("\203q\201[\203v\202\252\210\331\217\355\202\310\202\314\202\305\225`\211\346\202\360\222\206\216~\202\265\202\334\202\267\201B\n"));
            }
            return;
        }

        CBlock* next = block->m_next;
        prev = block;
        block = next;
    }

    int len = strlen(m_allocationSourceStr);
    strcpy(buf, m_allocationSourceStr + ((len - 12) & ~((len - 12) >> 31)));
    Graphic.DrawDebugStringDirect(0x10, y, buf, 8);

    int unuseKB = unuse / 1024;
    int maxUnuseKB = maxUnuse / 1024;
    sprintf(buf, "%4d %4d %4d", m_allocCount, unuseKB, maxUnuseKB);
    Graphic.DrawDebugStringDirect(0x208, y, buf, 8);
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
    int totalSize = 0;
    int total = 0;

    while ((node->m_flags & 2) == 0) {
        if ((node->m_flags & kMemoryBlockUsedFlag) == 0) {
            total += node->m_size;
        }
        totalSize += reinterpret_cast<int>(node->m_next) - reinterpret_cast<int>(node);
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

        m_cacheTable = new (rStage, "memory.cpp", 0x787) CAmemCache[m_cacheCount];
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
            entry.m_cacheData = 0;
            entry.m_workData = 0;
        }
    }

    entry.m_refCnt0 = 0;
    entry.m_refCount = 0;
    entry.m_inUse = 0;
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
 * PAL Address: UNUSED
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline short CAmemCacheSet::GetFree()
{
    for (int i = 0; i < m_cacheCount; i++) {
        if (cacheEntryAt(this, i).m_inUse == 0) {
            return static_cast<short>(i);
        }
    }
    return -1;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CAmemCache::GetData(CMemory::CStage* rStage, char* source, int line)
{
    if (m_cacheData == 0) {
        if (m_dmaCopy != 0) {
            m_cacheData =
                rStage->alloc(static_cast<unsigned long>(m_size),
                                source != 0 ? source : const_cast<char*>(""),
                                static_cast<unsigned long>(line), 1);
            if (m_cacheData == 0) {
                return 0;
            } else {
                int dmaId = Sound.DMAEntry(0, 1, reinterpret_cast<int>(m_cacheData),
                                           reinterpret_cast<int>(m_workData), m_size, 0, 0);
                CStopWatch watch(const_cast<char*>("no name"));
                watch.Start();
                while (Sound.DMACheck(dmaId) != 0) {
                    watch.Stop();
                    if (watch.Get() >= 9000.0f) {
                        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                            System.Printf(const_cast<char*>("===================================================================\n===================================================================\n                          GetData  TimeOut\n===================================================================\n===================================================================\n"));
                        }
                        Sound.CheckDriver(1);
                        watch.Reset();
                        watch.Start();
                    } else {
                        watch.Start();
                    }
                }
                return reinterpret_cast<int>(m_cacheData);
            }
        } else {
            m_cacheData = m_workData;
            return reinterpret_cast<int>(m_cacheData);
        }
    } else {
        return 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001D278
 * PAL Size: 456b
 * EN Address: 0x8001D06C
 * EN Size: 456b
 * JP Address: 0x8001CAC8
 * JP Size: 440b
 */
int CAmemCacheSet::GetData(short index, char* source, int line)
{
    while (true) {
        unsigned int data = cacheEntryAt(this, index).GetData(m_rStage, source, line);

        if (data == 0) {
            AmemFreeLowPrio(cacheEntryAt(this, index).m_size);
            continue;
        }
        return data;
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
short CAmemCacheSet::SetData(void* src, int size, CAmemCache::TYPE type, int dmaCopy)
{
    short index = GetFree();

    if (index == -1) {
        return -1;
    }

    int allocSize = (static_cast<unsigned int>(size) + 0x1F) & ~0x1F;
    CAmemCache& entry = m_cacheTable[index];
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

        entry.m_checksum = static_cast<int>(CheckSum(src, entry.m_size));

        if (entry.m_dmaCopy == 0) {
            memcpy(entry.m_workData, src, static_cast<unsigned long>(entry.m_size));
        } else {
            int dmaId = Sound.DMAEntry(0, 0, reinterpret_cast<int>(src),
                                       reinterpret_cast<int>(entry.m_workData), entry.m_size, 0, 0);
            CStopWatch watch(const_cast<char*>("no name"));
            watch.Start();
            while (Sound.DMACheck(dmaId) != 0) {
                watch.Stop();
                watch.Get();
                watch.Start();
            }
        }
    } else {
        while (true) {
            entry.m_workData = m_rStage->alloc(allocSize, const_cast<char*>("memory.cpp"), 0x807, 1);
            if (entry.m_workData != 0) {
                break;
            }
            AmemFreeLowPrio(allocSize);
        }

        entry.m_cacheData = 0;
        entry.m_size = static_cast<int>(allocSize);

        entry.m_checksum = static_cast<int>(CheckSum(src, entry.m_size));

        if (entry.m_dmaCopy == 0) {
            memcpy(entry.m_workData, src, static_cast<unsigned long>(entry.m_size));
        } else {
            int dmaId = Sound.DMAEntry(0, 0, reinterpret_cast<int>(src),
                                       reinterpret_cast<int>(entry.m_workData), entry.m_size, 0, 0);
            CStopWatch watch(const_cast<char*>("no name"));
            watch.Start();
            while (Sound.DMACheck(dmaId) != 0) {
                watch.Stop();
                watch.Get();
                watch.Start();
            }
        }

        DCFlushRange(entry.m_workData, allocSize);
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
int CAmemCacheSet::IsEnable(short index)
{
    return cacheEntryAt(this, index).IsEnable();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CAmemCache::IsEnable()
{
    return m_cacheData != 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x800294B4
 * EN Size: 372b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CAmemCacheSet::DumpCache()
{
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>("\n\n=================================================\n                    AMEM CACHE DUMP\n=================================================\n"));
    }

    for (int i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = cacheEntryAt(this, i);
        if (((entry.m_inUse != 0) || (entry.m_cacheData != 0)) && (static_cast<unsigned int>(System.m_execParam) >= 3)) {
            System.Printf(
                const_cast<char*>("%03d %s  type=%s  RefCnt=%d  prio=%d  rmem=%08x\n"), i, amem_stateName[entry.m_inUse ? 0 : 1],
                amem_typeName[entry.m_type], entry.m_refCount, entry.m_priority, reinterpret_cast<int>(entry.m_cacheData));
        }
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>("\n\n"));
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001CD48
 * PAL Size: 360b
 * EN Address: 0x80028B98
 * EN Size: 316b
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::AddRef(short index)
{
    m_cacheTable[index].m_refCount += 1;
    if (m_cacheTable[index].m_refCount >= 0xFFFF) {
        DumpCache();

        if (m_overflowHook != 0) {
            m_overflowHook(static_cast<unsigned long>(index));
        }
    }

    m_cacheTable[index].m_priority = 0x7FFFFFF0;
}

/*
 * --INFO--
 * PAL Address: 0x8001CBF4
 * PAL Size: 340b
 * EN Address: 0x80028CD4
 * EN Size: 288b
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::Release(short index)
{
    m_cacheTable[index].m_refCount -= 1;

    if (m_cacheTable[index].m_refCount >= 0xFFFF) {
        DumpCache();

        if (m_overflowHook != 0) {
            m_overflowHook(static_cast<unsigned long>(index));
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
    int i;

    while (true) {
        CAmemCache* bestEntry = 0;

        for (i = 0; i < m_cacheCount; i++) {
            CAmemCache& entry = m_cacheTable[i];
            if (entry.m_inUse != 0 && entry.m_refCount == 0 && entry.m_dmaCopy != 0 &&
                entry.m_cacheData != 0 && entry.m_size >= currentSize &&
                static_cast<unsigned int>(entry.m_priority) < bestPriority) {
                bestEntry = &entry;
                bestPriority = static_cast<unsigned int>(entry.m_priority);
            }
        }

        if (bestEntry != 0) {
            freeStageBlockBase(bestEntry->m_cacheData);
            bestEntry->m_cacheData = 0;
        }

        unsigned int allocated = reinterpret_cast<int>(m_rStage->alloc(size, const_cast<char*>("memory.cpp"), 0x86D, 1));
        if (allocated != 0) {
            freeStageBlockBase(reinterpret_cast<void*>(allocated));
            return;
        }

        if (currentSize != 0) {
            goto shrink;
        }

        if (bestPriority != 0xFFFFFFFF) {
            goto dropPriority;
        }

        if (m_releaseAction == 0 || m_releaseAction(m_releaseActionArg) == 0) {
            m_releaseCheck(m_releaseCheckArg);
            if (static_cast<unsigned int>(System.m_execParam) >= 3) {
                System.Printf(const_cast<char*>("\n\n=================================================\n                    AMEM CACHE DUMP\n=================================================\n"));
            }

            for (i = 0; i < m_cacheCount; i++) {
                CAmemCache& entry = cacheEntryAt(this, i);
                if (((entry.m_inUse != 0) || (entry.m_cacheData != 0)) && (static_cast<unsigned int>(System.m_execParam) >= 3)) {
                    System.Printf(
                        const_cast<char*>("%03d %s  type=%s  RefCnt=%d  prio=%d  rmem=%08x\n"), i, amem_stateName[entry.m_inUse ? 0 : 1],
                        amem_typeName[entry.m_type], entry.m_refCount, entry.m_priority,
                        reinterpret_cast<int>(entry.m_cacheData));
                }
            }

            if (static_cast<unsigned int>(System.m_execParam) >= 3) {
                System.Printf(const_cast<char*>("\n\n"));
            }
            m_rStage->heapWalker(-1, nullptr, static_cast<unsigned long>(-1));
            goto dropPriority;
        }
        continue;

    dropPriority:
        bestPriority = 0xFFFFFFFF;
        continue;

    shrink:
        currentSize -= size / 2;
        if (currentSize < 0) {
            currentSize = 0;
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
        CAmemCache& entry = m_cacheTable[i];

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
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::RefCnt0Up(int index)
{
    CAmemCache& entry = cacheEntryAt(this, index);
    entry.m_refCnt0++;
    s_RefCnt0Compare++;
    if (s_MaxRefCnt0Compare < s_RefCnt0Compare) {
        s_MaxRefCnt0Compare = s_RefCnt0Compare;
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf("  CAmemCacheSet s_MaxRefCnt0Compare=%d\n", s_MaxRefCnt0Compare);
        }
    }
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

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>("\n\n\n================================================\n"));
    }

    for (int i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = m_cacheTable[i];
        if ((entry.m_inUse != 0 && entry.m_refCount != 0) &&
            static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(
                const_cast<char*>("%03d %s  type=%s  RefCnt=%d  prio=%d  rmem=%08x\n"), i, amem_stateName[entry.m_inUse ? 0 : 1], amem_typeName[entry.m_type],
                entry.m_refCount, entry.m_priority, reinterpret_cast<int>(entry.m_cacheData));
        }
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>("================================================\n\n\n"));
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001C40C
 * PAL Size: 288b
 * EN Address: 0x800292FC
 * EN Size: 440b
 * JP Address: TODO
 * JP Size: TODO
 */
void CAmemCacheSet::AssertCache()
{
    int i;

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>("\n\n=================================================\n                    AMEM CACHE DUMP\n=================================================\n"));
    }

    for (i = 0; i < m_cacheCount; i++) {
        CAmemCache& entry = cacheEntryAt(this, i);
        if (((entry.m_inUse != 0) || (entry.m_cacheData != 0)) && (static_cast<unsigned int>(System.m_execParam) >= 3)) {
            System.Printf(
                const_cast<char*>("%03d %s  type=%s  RefCnt=%d  prio=%d  rmem=%08x\n"), i, amem_stateName[entry.m_inUse ? 0 : 1],
                amem_typeName[entry.m_type], entry.m_refCount, entry.m_priority, reinterpret_cast<int>(entry.m_cacheData));
        }
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>("\n\n"));
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

