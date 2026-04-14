#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedGlobals.h"
#include <dolphin/os.h>

static int m_DataBuffer;
static int m_ADataBuffer;
static int m_DataBufferSize;
static int m_ADataBufferSize;
static int* m_MemoryBank;
static int* m_AMemoryBank;

const char sRedMemoryLogPrefix[] = "\x1b[7;34mSound\x1b[0m:";
const char sRedMemoryLogSuffixA[] = "\x1b[7;31m";
const char sRedMemoryLogSuffixB[8] = "\x1b[0m";
const char s_redMemoryMainBankFullFmt[] = "%s%sMemory Bank Full !!%s\n";
const char s_redMemoryAuxBankFullFmt[] = "%s%sA-Memory Bank Full !!%s\n";

// Memory functions
extern "C" {
	void* memmove(void* dest, const void* src, unsigned int n);
	void* memcpy(void* dest, const void* src, unsigned int n);
	void* memset(void* s, int c, unsigned int n);
}

// Function declarations
extern "C" {
	void __dl__FPv(void*);
}

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
#pragma optimization_level 0
extern "C" CRedMemory* __dt__10CRedMemoryFv(CRedMemory* redMemory, short shouldDelete)
{
	if ((redMemory != 0) && (0 < shouldDelete)) {
		__dl__FPv(redMemory);
	}
	return redMemory;
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801bff80
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RedNew(int param_1)
{
	unsigned int interrupts;
	unsigned int alignedSize;
	int address;
	int entryCount;
	unsigned int moveCount;
	int* blockList;
	int* blockEnd;
	int* slot;

	if (param_1 < 1) {
		return 0;
	}

	blockList = m_MemoryBank;
	if (blockList == 0) {
		return 0;
	}

	address = m_DataBuffer;
	if (address == 0) {
		return 0;
	}

	interrupts = OSDisableInterrupts();
	alignedSize = (param_1 + 0x1F) & 0xFFFFFFE0;
	blockEnd = blockList + 0x800;
	slot = blockList;

	do {
		if ((slot[1] == 0) || ((address + alignedSize) <= *slot)) {
			if (blockList[0x7FF] > 0) {
				if (gRedMemoryDebugEnabled != 0) {
					OSReport(s_redMemoryMainBankFullFmt, sRedMemoryLogPrefix, sRedMemoryLogSuffixA, sRedMemoryLogSuffixB);
					fflush(__files + 1);
				}
				break;
			}

			if ((unsigned int)(address + alignedSize) <= (unsigned int)(m_DataBuffer + m_DataBufferSize)) {
				if (slot[1] > 0) {
					moveCount = (int)blockList + (0x2000 - (int)(slot + 2));
					entryCount = ((int)moveCount >> 3) + (unsigned int)((int)moveCount < 0 && (moveCount & 7) != 0);
					if (entryCount > 0) {
						memmove(slot + 2, slot, entryCount * 8);
					}
				}

				*slot = address;
				slot[1] = alignedSize;
				OSRestoreInterrupts(interrupts);
				return address;
			}

			break;
		}

		address = *slot + slot[1];
		slot += 2;
	} while (slot < blockEnd);

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
	int* blockList = m_MemoryBank;

	if (blockList != 0) {
		int* blockEnd = blockList + 0x800;
		int* blockPtr = blockList;

		do {
			if (*blockPtr == address) {
				int entryCount = ((int)(blockList + 0x800) - (int)(blockPtr + 2)) / 8;

				if (entryCount > 0) {
					memcpy(blockPtr, blockPtr + 2, entryCount * 8);
					memset(blockList + 0x7FE, 0, 8);
				}
				break;
			}
			blockPtr += 2;
		} while (blockPtr[1] != 0 && blockPtr < blockEnd);
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
#pragma dont_inline on
#pragma optimization_level 0
void RedDelete(void* param_1)
{
	RedDelete((int)param_1);
}
#pragma optimization_level 4
#pragma dont_inline reset

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
	unsigned int alignedSize;
	unsigned int moveCount;
	int result;
	unsigned int interrupts;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int* bestBlock;
	int* blockPtr;
	int* scanPtr;

	if (size < 1 || m_AMemoryBank == (int*)0 || m_ADataBuffer == 0) {
		return 0;
	}
	if (m_AMemoryBank[0x7FF] >= 1) {
		if (gRedMemoryDebugEnabled != 0) {
			OSReport(s_redMemoryAuxBankFullFmt, sRedMemoryLogPrefix, sRedMemoryLogSuffixA, sRedMemoryLogSuffixB);
			fflush(__files + 1);
		}
		return 0;
	}

	interrupts = OSDisableInterrupts();
	iVar6 = m_ADataBuffer + offset;
	if (maxSize == 0) {
		maxSize = m_ADataBufferSize;
	}
	maxSize = maxSize - offset;
	alignedSize = size + 0x1FU & 0xFFFFFFE0;
	iVar7 = -1;
	bestBlock = (int*)0;
	for (blockPtr = m_AMemoryBank; (blockPtr[1] != 0 && *blockPtr < iVar6); blockPtr = blockPtr + 2) {
	}
	iVar5 = maxSize;
	result = iVar6;
	iVar8 = iVar6;
	scanPtr = blockPtr;
	if (blockPtr[1] != 0) {
		for (; scanPtr[1] != 0 && scanPtr < m_AMemoryBank + 0x800; scanPtr = scanPtr + 2) {
			if (iVar8 < iVar6 + maxSize) {
				if ((int)(iVar8 + alignedSize) <= *scanPtr) {
					iVar7 = iVar8;
					bestBlock = scanPtr;
					if (*scanPtr - iVar8 < iVar5) {
						iVar5 = *scanPtr - iVar8;
					}
				}
			} else {
				scanPtr = m_AMemoryBank + 0x800;
			}
			iVar8 = *scanPtr + scanPtr[1];
		}
		result = iVar7;
		blockPtr = bestBlock;
		if (((scanPtr[1] == 0 && scanPtr < m_AMemoryBank + 0x800) &&
		     (iVar7 = (iVar6 + maxSize) - iVar8, (int)alignedSize <= iVar7)) &&
		    iVar7 < iVar5) {
			result = iVar8;
			blockPtr = scanPtr;
		}
	}
	if (blockPtr == (int*)0 || (unsigned int)(iVar6 + maxSize) < result + alignedSize) {
		OSRestoreInterrupts(interrupts);
		return 0;
	}
	if (0 < blockPtr[1]) {
		moveCount = (int)m_AMemoryBank + (0x2000 - (int)(blockPtr + 2));
		iVar6 = ((int)moveCount >> 3) + (unsigned int)((int)moveCount < 0 && (moveCount & 7) != 0);
		if (0 < iVar6) {
			memmove(blockPtr + 2, blockPtr, iVar6 * 8);
		}
	}
	*blockPtr = result;
	blockPtr[1] = alignedSize;
	OSRestoreInterrupts(interrupts);
	return result;
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
	int* blockList = m_AMemoryBank;

	if (blockList != 0) {
		int* blockEnd = blockList + 0x800;
		int* blockPtr = blockList;

		do {
			if (*blockPtr == address) {
				int entryCount = ((int)(blockList + 0x800) - (int)(blockPtr + 2)) / 8;

				if (entryCount > 0) {
					memcpy(blockPtr, blockPtr + 2, entryCount * 8);
					memset(blockList + 0x7FE, 0, 8);
				}
				break;
			}
			blockPtr += 2;
		} while (blockPtr[1] != 0 && blockPtr < blockEnd);
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
#pragma dont_inline on
#pragma optimization_level 0
void RedDeleteA(void* param_1)
{
	RedDeleteA((int)param_1);
}
#pragma optimization_level 4
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x801c0528
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedMemory::Init(int param1, int param2, int param3, int param4)
{
	unsigned int bankSize = 0x2000U;
	bankSize += 0x1FU;
	bankSize &= 0xFFFFFFE0;

	m_MemoryBank = (int*)param1;
	m_DataBufferSize = param2 - (bankSize * 2);
	m_AMemoryBank = (int*)((int)m_MemoryBank + bankSize);
	m_DataBuffer = (int)m_AMemoryBank + bankSize;
	memset(m_MemoryBank, 0, bankSize);
	memset(m_AMemoryBank, 0, bankSize);
	m_ADataBuffer = param3;
	m_ADataBufferSize = param4;
}
#pragma optimization_level 4

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
int* CRedMemory::GetMainBankAddress()
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
int* CRedMemory::GetABankAddress()
{
	return m_AMemoryBank;
}
