#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include <dolphin/os.h>

static int m_DataBuffer;
static int m_ADataBuffer;
static int m_DataBufferSize;
static int m_ADataBufferSize;

static RedMemoryBlock* m_MemoryBank;
static RedMemoryBlock* m_AMemoryBank;

const char s_redMemoryMainBankFullFmt[] = "%s%sMemory Bank Full !!%s\n";
const char sRedMemoryLogPrefix[] = "\x1b[7;34mSound\x1b[0m:";
const char s_redMemoryAuxBankFullFmt[] = "%s%sA-Memory Bank Full !!%s\n";
const char sRedMemoryLogSuffixA[] = "\x1b[7;31m";
const char sRedMemoryLogSuffixB[] = "\x1b[0m";

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CRedMemory::CRedMemory()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801bff38
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RedNew(int size)
{
	int entryCount;
	unsigned int interrupts;
	RedMemoryBlock* slot;
	int address;

	if ((size < 1) || (m_MemoryBank == 0) || ((unsigned int)m_DataBuffer == 0)) {
		return 0;
	}

	interrupts = OSDisableInterrupts();
	size += REDSOUND_MEMORY_BANK_ALIGN_MASK;
	size &= ~REDSOUND_MEMORY_BANK_ALIGN_MASK;
	slot = m_MemoryBank;
	address = m_DataBuffer;

	do {
		if ((slot->m_size == 0) || ((address + size) <= slot->m_address)) {
			if (m_MemoryBank[REDSOUND_MEMORY_BANK_LAST_INDEX].m_size > 0) {
				if (m_ReportPrint != 0) {
					OSReport(s_redMemoryMainBankFullFmt, sRedMemoryLogPrefix, sRedMemoryLogSuffixA,
					         sRedMemoryLogSuffixB);
					fflush(__files + 1);
				}
				break;
			}

			if ((u32)(address + size) <= (u32)(m_DataBuffer + m_DataBufferSize)) {
				if (slot->m_size > 0) {
					entryCount = (m_MemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT) - (slot + 1);
					if (entryCount > 0) {
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
	} while (slot < m_MemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT);

	OSRestoreInterrupts(interrupts);
	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801c00e8
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RedDelete(int address)
{
	if (address == 0) {
		return;
	}

	unsigned int interrupts = OSDisableInterrupts();

	if (m_MemoryBank != 0) {
		RedMemoryBlock* blockPtr = m_MemoryBank;

		while ((blockPtr->m_size != 0) && (blockPtr < m_MemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT)) {
			if (blockPtr->m_address == address) {
				int entryCount = (m_MemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT) - (blockPtr + 1);

				if (entryCount > 0) {
					memcpy(blockPtr, blockPtr + 1, entryCount * REDSOUND_MEMORY_BLOCK_SIZE);
					memset(m_MemoryBank + REDSOUND_MEMORY_BANK_LAST_INDEX, 0, REDSOUND_MEMORY_BLOCK_SIZE);
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RedDelete(void* address)
{
	RedDelete((int)address);
}

/*
 * --INFO--
 * PAL Address: 0x801c01e8
 * PAL Size: 576b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RedNewA(int size, int offset, int maxSize)
{
	unsigned int interrupts;
	int result;
	int rangeStart;
	int currentAddress;
	int gap;
	int maxGap;
	RedMemoryBlock* bestBlock;
	RedMemoryBlock* blockPtr;

	if ((size < 1) || (m_AMemoryBank == 0) || ((unsigned int)m_ADataBuffer == 0)) {
		return 0;
	}
	if (m_AMemoryBank[REDSOUND_MEMORY_BANK_LAST_INDEX].m_size > 0) {
		if (m_ReportPrint != 0) {
			OSReport(s_redMemoryAuxBankFullFmt, sRedMemoryLogPrefix, sRedMemoryLogSuffixA, sRedMemoryLogSuffixB);
			fflush(__files + 1);
		}
		return 0;
	}

	interrupts = OSDisableInterrupts();
	rangeStart = m_ADataBuffer + offset;
	if (maxSize == 0) {
		maxSize = m_ADataBufferSize;
	}
	maxSize -= offset;
	size = (size + REDSOUND_MEMORY_BANK_ALIGN_MASK) & ~REDSOUND_MEMORY_BANK_ALIGN_MASK;
	currentAddress = rangeStart;
	result = REDSOUND_MEMORY_ALLOC_FAILED;
	maxGap = maxSize;
	bestBlock = 0;

	for (blockPtr = m_AMemoryBank; (blockPtr->m_size != 0) && (blockPtr->m_address < rangeStart); blockPtr++) {
	}

	if (blockPtr->m_size == 0) {
		result = currentAddress;
		bestBlock = blockPtr;
	} else {
		for (; (blockPtr->m_size != 0) && (blockPtr < m_AMemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT); blockPtr++) {
			if (currentAddress < rangeStart + maxSize) {
				if ((currentAddress + size) <= blockPtr->m_address) {
					gap = blockPtr->m_address - currentAddress;
					if (maxGap > gap) {
						maxGap = gap;
					}
					result = currentAddress;
					bestBlock = blockPtr;
				}
			} else {
				blockPtr = m_AMemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT;
			}
			currentAddress = blockPtr->m_address + blockPtr->m_size;
		}

		if ((blockPtr->m_size == 0) && (blockPtr < m_AMemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT)) {
			gap = (rangeStart + maxSize) - currentAddress;
			if ((size <= gap) && (maxGap > gap)) {
				result = currentAddress;
				bestBlock = blockPtr;
			}
		}
	}

	if ((bestBlock != 0) && ((u32)(result + size) <= (u32)(rangeStart + maxSize))) {
		if (bestBlock->m_size > 0) {
			int moveCount = (m_AMemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT) - (bestBlock + 1);
			if (moveCount > 0) {
				memmove(bestBlock + 1, bestBlock, moveCount * REDSOUND_MEMORY_BLOCK_SIZE);
			}
		}
		bestBlock->m_address = result;
		bestBlock->m_size = size;
		OSRestoreInterrupts(interrupts);
		return result;
	}

	OSRestoreInterrupts(interrupts);
	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801c0428
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RedDeleteA(int address)
{
	if (address == 0) {
		return;
	}

	unsigned int interrupts = OSDisableInterrupts();

	if (m_AMemoryBank != 0) {
		RedMemoryBlock* blockPtr = m_AMemoryBank;

		while ((blockPtr->m_size != 0) && (blockPtr < m_AMemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT)) {
			if (blockPtr->m_address == address) {
				int entryCount = (m_AMemoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT) - (blockPtr + 1);

				if (entryCount > 0) {
					memcpy(blockPtr, blockPtr + 1, entryCount * REDSOUND_MEMORY_BLOCK_SIZE);
					memset(m_AMemoryBank + REDSOUND_MEMORY_BANK_LAST_INDEX, 0, REDSOUND_MEMORY_BLOCK_SIZE);
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RedDeleteA(void* address)
{
	RedDeleteA((int)address);
}

/*
 * --INFO--
 * PAL Address: 0x801c0528
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedMemory::Init(int param1, int param2, int param3, int param4)
{
	int bankSize = REDSOUND_MEMORY_BANK_SIZE;
	bankSize += REDSOUND_MEMORY_BANK_ALIGN_MASK;
	bankSize &= ~REDSOUND_MEMORY_BANK_ALIGN_MASK;

	m_MemoryBank = (RedMemoryBlock*)param1;
	m_AMemoryBank = (RedMemoryBlock*)((int)m_MemoryBank + bankSize);
	m_DataBufferSize = param2 - bankSize * 2;
	m_DataBuffer = (int)m_AMemoryBank + bankSize;
	memset(m_MemoryBank, 0, bankSize);
	memset(m_AMemoryBank, 0, bankSize);
	m_ADataBuffer = param3;
	m_ADataBufferSize = param4;
}

/*
 * --INFO--
 * PAL Address: 0x801c05c8
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
RedMemoryBlock* CRedMemory::GetABankAddress()
{
	return m_AMemoryBank;
}
