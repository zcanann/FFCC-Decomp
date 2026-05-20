#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "global.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include <dolphin/os.h>

STATIC_ASSERT(offsetof(RedMemoryBlock, m_address) == REDSOUND_MEMORY_BLOCK_ADDRESS_OFFSET);
STATIC_ASSERT(offsetof(RedMemoryBlock, m_size) == REDSOUND_MEMORY_BLOCK_SIZE_OFFSET);
STATIC_ASSERT(sizeof(RedMemoryBlock) == REDSOUND_MEMORY_BLOCK_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_BLOCK_SIZE == (1 << REDSOUND_MEMORY_BLOCK_INDEX_SHIFT));
STATIC_ASSERT(offsetof(RedMemoryBankTable, m_mainBank) == REDSOUND_MEMORY_MAIN_BANK_OFFSET);
STATIC_ASSERT(offsetof(RedMemoryBankTable, m_auxBank) == REDSOUND_MEMORY_AUX_BANK_OFFSET);
STATIC_ASSERT(sizeof(((RedMemoryBankTable*)0)->m_mainBank) == REDSOUND_MEMORY_BANK_SIZE);
STATIC_ASSERT(sizeof(((RedMemoryBankTable*)0)->m_auxBank) == REDSOUND_MEMORY_BANK_SIZE);
STATIC_ASSERT(sizeof(RedMemoryBankTable) == REDSOUND_MEMORY_BANK_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_BANK_SIZE == REDSOUND_MEMORY_BANK_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_BANK_SIZE == REDSOUND_MEMORY_BLOCK_SIZE * REDSOUND_MEMORY_BANK_BLOCK_COUNT);
STATIC_ASSERT(REDSOUND_MEMORY_AUX_BANK_OFFSET == REDSOUND_MEMORY_BANK_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_AUX_BANK_OFFSET == REDSOUND_MEMORY_MAIN_BANK_OFFSET + REDSOUND_MEMORY_BANK_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_BANK_TABLE_SIZE == REDSOUND_MEMORY_BANK_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_BANK_TABLE_SIZE == REDSOUND_MEMORY_BANK_SIZE * REDSOUND_MEMORY_BANK_TABLE_COUNT);
STATIC_ASSERT(REDSOUND_MEMORY_DATA_BUFFER_OFFSET == REDSOUND_MEMORY_BANK_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_AUX_BANK_OFFSET + REDSOUND_MEMORY_BANK_SIZE == REDSOUND_MEMORY_DATA_BUFFER_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_DATA_BUFFER_OFFSET == REDSOUND_MEMORY_BANK_TABLE_SIZE);

static int m_DataBuffer;
static int m_ADataBuffer;
static int m_DataBufferSize;
static int m_ADataBufferSize;

static RedMemoryBlock* volatile m_MemoryBank;
static RedMemoryBlock* volatile m_AMemoryBank;

const char sRedMemoryMainBankFullFmt[] = "%s%sMemory Bank Full !!%s\n";
const char sRedMemoryLogPrefix[] = "\x1b[7;34mSound\x1b[0m:";
const char sRedMemoryAuxBankFullFmt[] = "%s%sA-Memory Bank Full !!%s\n";
const char sRedMemoryLogErrorColor[] = "\x1b[7;31m";
const char sRedMemoryLogReset[] = "\x1b[0m";

enum RedMemoryStringLayout {
	REDSOUND_MEMORY_MAIN_BANK_FULL_FMT_SIZE = 0x1b,
	REDSOUND_MEMORY_LOG_PREFIX_SIZE = 0x12,
	REDSOUND_MEMORY_AUX_BANK_FULL_FMT_SIZE = 0x1d,
	REDSOUND_MEMORY_LOG_ERROR_COLOR_SIZE = 0x08,
	REDSOUND_MEMORY_LOG_RESET_SIZE = 0x05,
	REDSOUND_MEMORY_RODATA_STRING_SIZE = 0x4a,
	REDSOUND_MEMORY_SDATA2_STRING_SIZE = 0x0d,
};

enum RedMemoryMapLayout {
	REDSOUND_MEMORY_MAP_RODATA_STRING_OFFSET = 0x00,
	REDSOUND_MEMORY_MAP_RODATA_STRING_SIZE = 0x4A,
	REDSOUND_MEMORY_MAP_SBSS_DATA_BUFFER_OFFSET = 0x00,
	REDSOUND_MEMORY_MAP_SBSS_A_DATA_BUFFER_OFFSET = 0x04,
	REDSOUND_MEMORY_MAP_SBSS_DATA_BUFFER_SIZE_OFFSET = 0x08,
	REDSOUND_MEMORY_MAP_SBSS_A_DATA_BUFFER_SIZE_OFFSET = 0x0C,
	REDSOUND_MEMORY_MAP_SBSS_BANK_TABLE_OFFSET = 0x10,
	REDSOUND_MEMORY_MAP_SBSS_A_BANK_TABLE_OFFSET = 0x14,
	REDSOUND_MEMORY_MAP_SBSS_SIZE = 0x18,
	REDSOUND_MEMORY_MAP_SDATA2_STRING_OFFSET = 0x00,
	REDSOUND_MEMORY_MAP_SDATA2_STRING_SIZE = 0x0D,
};

struct RedMemorySmallDataState {
	int m_DataBuffer;
	int m_ADataBuffer;
	int m_DataBufferSize;
	int m_ADataBufferSize;
	RedMemoryBlock* m_MemoryBank;
	RedMemoryBlock* m_AMemoryBank;
};

enum RedMemorySmallDataLayout {
	REDSOUND_MEMORY_SBSS_DATA_BUFFER_OFFSET = (unsigned int)&(((RedMemorySmallDataState*)0)->m_DataBuffer),
	REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_OFFSET = (unsigned int)&(((RedMemorySmallDataState*)0)->m_ADataBuffer),
	REDSOUND_MEMORY_SBSS_DATA_BUFFER_SIZE_OFFSET = (unsigned int)&(((RedMemorySmallDataState*)0)->m_DataBufferSize),
	REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_SIZE_OFFSET =
	    (unsigned int)&(((RedMemorySmallDataState*)0)->m_ADataBufferSize),
	REDSOUND_MEMORY_SBSS_BANK_TABLE_OFFSET = (unsigned int)&(((RedMemorySmallDataState*)0)->m_MemoryBank),
	REDSOUND_MEMORY_SBSS_A_BANK_TABLE_OFFSET = (unsigned int)&(((RedMemorySmallDataState*)0)->m_AMemoryBank),
	REDSOUND_MEMORY_SBSS_SIZE = sizeof(RedMemorySmallDataState),
};

STATIC_ASSERT(sizeof(sRedMemoryMainBankFullFmt) == REDSOUND_MEMORY_MAIN_BANK_FULL_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedMemoryLogPrefix) == REDSOUND_MEMORY_LOG_PREFIX_SIZE);
STATIC_ASSERT(sizeof(sRedMemoryAuxBankFullFmt) == REDSOUND_MEMORY_AUX_BANK_FULL_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedMemoryLogErrorColor) == REDSOUND_MEMORY_LOG_ERROR_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedMemoryLogReset) == REDSOUND_MEMORY_LOG_RESET_SIZE);
STATIC_ASSERT(sizeof(sRedMemoryMainBankFullFmt) + sizeof(sRedMemoryLogPrefix) +
                  sizeof(sRedMemoryAuxBankFullFmt) ==
                  REDSOUND_MEMORY_RODATA_STRING_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_MAP_RODATA_STRING_OFFSET == 0);
STATIC_ASSERT(REDSOUND_MEMORY_RODATA_STRING_SIZE == REDSOUND_MEMORY_MAP_RODATA_STRING_SIZE);
STATIC_ASSERT(sizeof(sRedMemoryLogErrorColor) + sizeof(sRedMemoryLogReset) == REDSOUND_MEMORY_SDATA2_STRING_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_MAP_SDATA2_STRING_OFFSET == 0);
STATIC_ASSERT(REDSOUND_MEMORY_SDATA2_STRING_SIZE == REDSOUND_MEMORY_MAP_SDATA2_STRING_SIZE);
STATIC_ASSERT(offsetof(RedMemorySmallDataState, m_DataBuffer) == REDSOUND_MEMORY_SBSS_DATA_BUFFER_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_DATA_BUFFER_OFFSET == 0);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_DATA_BUFFER_OFFSET == REDSOUND_MEMORY_MAP_SBSS_DATA_BUFFER_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_DATA_BUFFER_OFFSET + sizeof(m_DataBuffer) ==
              REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_OFFSET);
STATIC_ASSERT(offsetof(RedMemorySmallDataState, m_ADataBuffer) == REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_OFFSET == REDSOUND_MEMORY_MAP_SBSS_A_DATA_BUFFER_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_OFFSET + sizeof(m_ADataBuffer) ==
              REDSOUND_MEMORY_SBSS_DATA_BUFFER_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedMemorySmallDataState, m_DataBufferSize) == REDSOUND_MEMORY_SBSS_DATA_BUFFER_SIZE_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_DATA_BUFFER_SIZE_OFFSET == REDSOUND_MEMORY_MAP_SBSS_DATA_BUFFER_SIZE_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_DATA_BUFFER_SIZE_OFFSET + sizeof(m_DataBufferSize) ==
              REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedMemorySmallDataState, m_ADataBufferSize) ==
              REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_SIZE_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_SIZE_OFFSET == REDSOUND_MEMORY_MAP_SBSS_A_DATA_BUFFER_SIZE_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_A_DATA_BUFFER_SIZE_OFFSET + sizeof(m_ADataBufferSize) ==
              REDSOUND_MEMORY_SBSS_BANK_TABLE_OFFSET);
STATIC_ASSERT(offsetof(RedMemorySmallDataState, m_MemoryBank) == REDSOUND_MEMORY_SBSS_BANK_TABLE_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_BANK_TABLE_OFFSET == REDSOUND_MEMORY_MAP_SBSS_BANK_TABLE_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_BANK_TABLE_OFFSET + sizeof(m_MemoryBank) ==
              REDSOUND_MEMORY_SBSS_A_BANK_TABLE_OFFSET);
STATIC_ASSERT(offsetof(RedMemorySmallDataState, m_AMemoryBank) == REDSOUND_MEMORY_SBSS_A_BANK_TABLE_OFFSET);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_A_BANK_TABLE_OFFSET == REDSOUND_MEMORY_MAP_SBSS_A_BANK_TABLE_OFFSET);
STATIC_ASSERT(sizeof(RedMemorySmallDataState) == REDSOUND_MEMORY_SBSS_SIZE);
STATIC_ASSERT(REDSOUND_MEMORY_SBSS_SIZE == REDSOUND_MEMORY_MAP_SBSS_SIZE);
STATIC_ASSERT(sizeof(m_DataBuffer) + sizeof(m_ADataBuffer) + sizeof(m_DataBufferSize) + sizeof(m_ADataBufferSize) +
                  sizeof(m_MemoryBank) + sizeof(m_AMemoryBank) ==
              REDSOUND_MEMORY_SBSS_SIZE);

/*
 * --INFO--
 * PAL Address: 0x801bff34
 * PAL Size: 4b
 * EN Address: 0x80201e58
 * EN Size: 4b
 * JP Address: TODO
 * JP Size: TODO
 */
CRedMemory::CRedMemory()
{
}

/*
 * --INFO--
 * PAL Address: 0x801bff38
 * PAL Size: 72b
 * EN Address: 0x80201e5c
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
CRedMemory::~CRedMemory()
{
}

/*
 * --INFO--
 * PAL Address: 0x801bff80
 * PAL Size: 360b
 * EN Address: 0x80201ea4
 * EN Size: 360b
 * JP Address: TODO
 * JP Size: TODO
 */
int RedNew(int size)
{
	int entryCount;
	unsigned int interrupts;
	RedMemoryBlock* slot;
	int address;

	if ((size < REDSOUND_MEMORY_ALLOC_MIN_SIZE) || (m_MemoryBank == 0) ||
	    ((unsigned int)m_DataBuffer == REDSOUND_MEMORY_ADDRESS_NONE)) {
		return REDSOUND_MEMORY_ADDRESS_NONE;
	}

	interrupts = OSDisableInterrupts();
	size += REDSOUND_MEMORY_BANK_ALIGN_MASK;
	size &= ~REDSOUND_MEMORY_BANK_ALIGN_MASK;
	slot = m_MemoryBank;
	address = m_DataBuffer;

	do {
		if ((slot->m_size == REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) || ((address + size) <= slot->m_address)) {
			if (RedMemoryBankGetLast(m_MemoryBank)->m_size > REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) {
				if (RedReportPrintIsEnabled()) {
					OSReport(sRedMemoryMainBankFullFmt, sRedMemoryLogPrefix, sRedMemoryLogErrorColor,
					         sRedMemoryLogReset);
					fflush(__files + 1);
				}
				break;
			}

			if ((u32)(address + size) <= (u32)(m_DataBuffer + m_DataBufferSize)) {
				if (slot->m_size > REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) {
					entryCount = RedMemoryBankGetTailCount(m_MemoryBank, slot);
					if (entryCount > REDSOUND_MEMORY_BLOCK_COUNT_NONE) {
						memmove(slot + 1, slot, entryCount * REDSOUND_MEMORY_BLOCK_SIZE);
					}
				}

				slot->m_address = address;
				slot->m_size = size;
				OSRestoreInterrupts(interrupts);
				return address;
			}

			break;
		}

		address = slot->m_address + slot->m_size;
		slot++;
	} while (slot < RedMemoryBankGetEnd(m_MemoryBank));

	OSRestoreInterrupts(interrupts);
	return REDSOUND_MEMORY_ADDRESS_NONE;
}
/*
 * --INFO--
 * PAL Address: 0x801c00e8
 * PAL Size: 216b
 * EN Address: 0x8020200c
 * EN Size: 216b
 * JP Address: TODO
 * JP Size: TODO
 */
void RedDelete(int address)
{
	if (address == REDSOUND_MEMORY_ADDRESS_NONE) {
		return;
	}

	unsigned int interrupts = OSDisableInterrupts();

	if (m_MemoryBank != 0) {
		RedMemoryBlock* blockPtr = m_MemoryBank;

		while ((blockPtr->m_size != REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) &&
		       (blockPtr < RedMemoryBankGetEnd(m_MemoryBank))) {
			if (blockPtr->m_address == address) {
				int entryCount = RedMemoryBankGetTailCount(m_MemoryBank, blockPtr);

				if (entryCount > REDSOUND_MEMORY_BLOCK_COUNT_NONE) {
					memcpy(blockPtr, blockPtr + 1, entryCount * REDSOUND_MEMORY_BLOCK_SIZE);
					memset(RedMemoryBankGetLast(m_MemoryBank), REDSOUND_MEMORY_BLOCK_SIZE_EMPTY,
					       REDSOUND_MEMORY_BLOCK_SIZE);
				}
				break;
			}

			blockPtr++;
		}
	}

	OSRestoreInterrupts(interrupts);
}

/*
 * --INFO--
 * PAL Address: 0x801c01c0
 * PAL Size: 40b
 * EN Address: 0x802020e4
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
void RedDelete(void* address)
{
	RedDelete(RedMemoryAddress(address));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 176b
 * EN Address: UNUSED
 * EN Size: 176b
 * JP Address: TODO
 * JP Size: TODO
 */
int RedResize(int address, int size)
{
	unsigned int interrupts;
	RedMemoryBlock* blockPtr;
	RedMemoryBlock* bankEnd;
	int resizedAddress;

	interrupts = OSDisableInterrupts();
	resizedAddress = REDSOUND_MEMORY_ADDRESS_NONE;
	if ((address == REDSOUND_MEMORY_ADDRESS_NONE) || (m_MemoryBank == 0)) {
		OSRestoreInterrupts(interrupts);
		return resizedAddress;
	}

	size += REDSOUND_MEMORY_BANK_ALIGN_MASK;
	size &= ~REDSOUND_MEMORY_BANK_ALIGN_MASK;
	blockPtr = m_MemoryBank;
	bankEnd = RedMemoryBankGetEnd(m_MemoryBank);

	while ((blockPtr->m_size != REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) &&
	       (blockPtr < bankEnd)) {
		if (blockPtr->m_address == address) {
			blockPtr->m_size = size;
			resizedAddress = address;
			break;
		}

		blockPtr++;
	}

	OSRestoreInterrupts(interrupts);
	return resizedAddress;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: UNUSED
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
void* RedResize(void* address, int size)
{
	return (void*)RedResize(RedMemoryAddress(address), size);
}

/*
 * --INFO--
 * PAL Address: 0x801c01e8
 * PAL Size: 576b
 * EN Address: 0x8020210c
 * EN Size: 576b
 * JP Address: TODO
 * JP Size: TODO
 */
int RedNewA(int size, int offset, int maxSize)
{
	unsigned int interrupts;
	int allocAddress;
	int rangeStart;
	int currentAddress;
	int gap;
	int maxGap;
	RedMemoryBlock* bestBlock;
	RedMemoryBlock* blockPtr;

	if ((size < REDSOUND_MEMORY_ALLOC_MIN_SIZE) || (m_AMemoryBank == 0) ||
	    ((unsigned int)m_ADataBuffer == REDSOUND_MEMORY_ADDRESS_NONE)) {
		return REDSOUND_MEMORY_ADDRESS_NONE;
	}
	if (RedMemoryBankGetLast(m_AMemoryBank)->m_size > REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) {
		if (RedReportPrintIsEnabled()) {
			OSReport(sRedMemoryAuxBankFullFmt, sRedMemoryLogPrefix, sRedMemoryLogErrorColor, sRedMemoryLogReset);
			fflush(__files + 1);
		}
		return REDSOUND_MEMORY_ADDRESS_NONE;
	}

	interrupts = OSDisableInterrupts();
	rangeStart = m_ADataBuffer + offset;
	if (maxSize == REDSOUND_MEMORY_MAX_SIZE_ALL) {
		maxSize = m_ADataBufferSize;
	}
	maxSize -= offset;
	size += REDSOUND_MEMORY_BANK_ALIGN_MASK;
	size &= ~REDSOUND_MEMORY_BANK_ALIGN_MASK;
	currentAddress = rangeStart;
	allocAddress = REDSOUND_MEMORY_ALLOC_FAILED;
	maxGap = maxSize;
	bestBlock = 0;

	for (blockPtr = m_AMemoryBank;
	     (blockPtr->m_size != REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) && (blockPtr->m_address < rangeStart);
	     blockPtr++) {
	}

	if (blockPtr->m_size == REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) {
		allocAddress = currentAddress;
		bestBlock = blockPtr;
	} else {
		for (; (blockPtr->m_size != REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) &&
		       (blockPtr < RedMemoryBankGetEnd(m_AMemoryBank)); blockPtr++) {
			if (currentAddress < rangeStart + maxSize) {
				if ((currentAddress + size) <= blockPtr->m_address) {
					gap = blockPtr->m_address - currentAddress;
					if (maxGap > gap) {
						maxGap = gap;
					}
					allocAddress = currentAddress;
					bestBlock = blockPtr;
				}
			} else {
				blockPtr = RedMemoryBankGetEnd(m_AMemoryBank);
			}
			currentAddress = blockPtr->m_address + blockPtr->m_size;
		}

		if ((blockPtr->m_size == REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) &&
		    (blockPtr < RedMemoryBankGetEnd(m_AMemoryBank))) {
			gap = (rangeStart + maxSize) - currentAddress;
			if ((size <= gap) && (maxGap > gap)) {
				allocAddress = currentAddress;
				bestBlock = blockPtr;
			}
		}
	}

	if ((bestBlock != 0) && ((u32)(allocAddress + size) <= (u32)(rangeStart + maxSize))) {
		if (bestBlock->m_size > REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) {
			gap = RedMemoryBankGetTailCount(m_AMemoryBank, bestBlock);
			if (gap > REDSOUND_MEMORY_BLOCK_COUNT_NONE) {
				memmove(bestBlock + 1, bestBlock, gap * REDSOUND_MEMORY_BLOCK_SIZE);
			}
		}
		bestBlock->m_address = allocAddress;
		bestBlock->m_size = size;
		OSRestoreInterrupts(interrupts);
		return allocAddress;
	}

	OSRestoreInterrupts(interrupts);
	return REDSOUND_MEMORY_ADDRESS_NONE;
}
/*
 * --INFO--
 * PAL Address: 0x801c0428
 * PAL Size: 216b
 * EN Address: 0x8020234c
 * EN Size: 216b
 * JP Address: TODO
 * JP Size: TODO
 */
void RedDeleteA(int address)
{
	if (address == REDSOUND_MEMORY_ADDRESS_NONE) {
		return;
	}

	unsigned int interrupts = OSDisableInterrupts();

	if (m_AMemoryBank != 0) {
		RedMemoryBlock* blockPtr = m_AMemoryBank;

		while ((blockPtr->m_size != REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) &&
		       (blockPtr < RedMemoryBankGetEnd(m_AMemoryBank))) {
			if (blockPtr->m_address == address) {
				int entryCount = RedMemoryBankGetTailCount(m_AMemoryBank, blockPtr);

				if (entryCount > REDSOUND_MEMORY_BLOCK_COUNT_NONE) {
					memcpy(blockPtr, blockPtr + 1, entryCount * REDSOUND_MEMORY_BLOCK_SIZE);
					memset(RedMemoryBankGetLast(m_AMemoryBank), REDSOUND_MEMORY_BLOCK_SIZE_EMPTY,
					       REDSOUND_MEMORY_BLOCK_SIZE);
				}
				break;
			}

			blockPtr++;
		}
	}

	OSRestoreInterrupts(interrupts);
}

/*
 * --INFO--
 * PAL Address: 0x801c0500
 * PAL Size: 40b
 * EN Address: 0x80202424
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
void RedDeleteA(void* address)
{
	RedDeleteA(RedMemoryAddress(address));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 176b
 * EN Address: UNUSED
 * EN Size: 176b
 * JP Address: TODO
 * JP Size: TODO
 */
int RedResizeA(int address, int size)
{
	unsigned int interrupts;
	RedMemoryBlock* blockPtr;
	RedMemoryBlock* bankEnd;
	int resizedAddress;

	interrupts = OSDisableInterrupts();
	resizedAddress = REDSOUND_MEMORY_ADDRESS_NONE;
	if ((address == REDSOUND_MEMORY_ADDRESS_NONE) || (m_AMemoryBank == 0)) {
		OSRestoreInterrupts(interrupts);
		return resizedAddress;
	}

	size += REDSOUND_MEMORY_BANK_ALIGN_MASK;
	size &= ~REDSOUND_MEMORY_BANK_ALIGN_MASK;
	blockPtr = m_AMemoryBank;
	bankEnd = RedMemoryBankGetEnd(m_AMemoryBank);

	while ((blockPtr->m_size != REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) &&
	       (blockPtr < bankEnd)) {
		if (blockPtr->m_address == address) {
			blockPtr->m_size = size;
			resizedAddress = address;
			break;
		}

		blockPtr++;
	}

	OSRestoreInterrupts(interrupts);
	return resizedAddress;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: UNUSED
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
void* RedResizeA(void* address, int size)
{
	return (void*)RedResizeA(RedMemoryAddress(address), size);
}

/*
 * --INFO--
 * PAL Address: 0x801c0528
 * PAL Size: 160b
 * EN Address: 0x8020244c
 * EN Size: 160b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedMemory::Init(int mainBuffer, int mainBufferSize, int auxBuffer, int auxBufferSize)
{
	int bankSize = REDSOUND_MEMORY_BANK_SIZE;
	bankSize += REDSOUND_MEMORY_BANK_ALIGN_MASK;
	bankSize &= ~REDSOUND_MEMORY_BANK_ALIGN_MASK;

	m_MemoryBank = (RedMemoryBlock*)mainBuffer;
	m_AMemoryBank = RedMemoryBankGetAuxBank(m_MemoryBank, bankSize);
	*(volatile int*)&m_DataBuffer = RedMemoryBankGetDataBuffer(m_AMemoryBank, bankSize);
	*(volatile int*)&m_DataBufferSize = mainBufferSize - bankSize * REDSOUND_MEMORY_BANK_TABLE_COUNT;
	memset(m_MemoryBank, 0, bankSize);
	memset(m_AMemoryBank, 0, bankSize);
	m_ADataBuffer = auxBuffer;
	m_ADataBufferSize = auxBufferSize;
}

/*
 * --INFO--
 * PAL Address: 0x801c05c8
 * PAL Size: 8b
 * EN Address: 0x802024ec
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedMemory::GetMainBufferAddress()
{
	return m_DataBuffer;
}

/*
 * --INFO--
 * PAL Address: 0x801c05d0
 * PAL Size: 8b
 * EN Address: 0x802024f4
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedMemory::GetMainBufferSize()
{
	return m_DataBufferSize;
}

/*
 * --INFO--
 * PAL Address: 0x801c05d8
 * PAL Size: 8b
 * EN Address: 0x802024fc
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
RedMemoryBlock* CRedMemory::GetMainBankAddress()
{
	return m_MemoryBank;
}

/*
 * --INFO--
 * PAL Address: 0x801c05e0
 * PAL Size: 8b
 * EN Address: 0x80202504
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedMemory::GetABufferAddress()
{
	return m_ADataBuffer;
}

/*
 * --INFO--
 * PAL Address: 0x801c05e8
 * PAL Size: 8b
 * EN Address: 0x8020250c
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedMemory::GetABufferSize()
{
	return m_ADataBufferSize;
}

/*
 * --INFO--
 * PAL Address: 0x801c05f0
 * PAL Size: 8b
 * EN Address: 0x80202514
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
RedMemoryBlock* CRedMemory::GetABankAddress()
{
	return m_AMemoryBank;
}
