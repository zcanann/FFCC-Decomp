#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include <dolphin/os.h>

static int m_DataBuffer;
static int m_ADataBuffer;
static int m_DataBufferSize;
static int m_ADataBufferSize;
static int* m_MemoryBank;
static int* m_AMemoryBank;

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
int RedNew(int param_1)
{
	unsigned int interrupts;
	int address;
	int entryCount;
	int* slot;

	if (param_1 >= 1) {
		if (m_MemoryBank != 0) {
			if (m_DataBuffer != 0) {
				interrupts = OSDisableInterrupts();
				param_1 = (param_1 + 0x1F) & 0xFFFFFFE0;
				address = m_DataBuffer;
				slot = m_MemoryBank;

				do {
					if ((slot[1] == 0) || ((address + param_1) <= *slot)) {
						if (m_MemoryBank[0x7FF] > 0) {
							if (m_ReportPrint != 0) {
								OSReport(s_redMemoryMainBankFullFmt, sRedMemoryLogPrefix, sRedMemoryLogSuffixA,
								         sRedMemoryLogSuffixB);
								fflush(__files + 1);
							}
							break;
						}

						if ((unsigned int)(address + param_1) <=
						    (unsigned int)(m_DataBuffer + m_DataBufferSize)) {
							if (slot[1] > 0) {
								entryCount = ((int)(m_MemoryBank + 0x800) - (int)(slot + 2)) / 8;
								if (entryCount > 0) {
									memmove(slot + 2, slot, entryCount * 8);
								}
							}

							*slot = address;
							slot[1] = param_1;
							OSRestoreInterrupts(interrupts);
							return address;
						}

						break;
					}

					address = *slot + slot[1];
					slot += 2;
				} while (slot < m_MemoryBank + 0x800);

				OSRestoreInterrupts(interrupts);
			}
		}
	}
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
		int* blockPtr = m_MemoryBank;

		while ((blockPtr[1] != 0) && (blockPtr < m_MemoryBank + 0x800)) {
			if (*blockPtr == address) {
				int entryCount = ((int)(m_MemoryBank + 0x800) - (int)(blockPtr + 2)) / 8;

				if (entryCount > 0) {
					memcpy(blockPtr, blockPtr + 2, entryCount * 8);
					memset(m_MemoryBank + 0x7FE, 0, 8);
				}
				break;
			}

			blockPtr += 2;
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
void RedDelete(void* param_1)
{
	RedDelete((int)param_1);
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
	int* bestBlock;
	int* blockPtr;

	if ((size < 1) || (m_AMemoryBank == 0) || (m_ADataBuffer == 0)) {
		return 0;
	}
	if (m_AMemoryBank[0x7FF] > 0) {
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
	size = (size + 0x1F) & 0xFFFFFFE0;
	result = rangeStart;
	maxGap = maxSize;
	bestBlock = 0;

	for (blockPtr = m_AMemoryBank; (blockPtr[1] != 0) && (*blockPtr < rangeStart); blockPtr += 2) {
	}

	if (blockPtr[1] != 0) {
		currentAddress = rangeStart;
		for (; (blockPtr[1] != 0) && (blockPtr < m_AMemoryBank + 0x800); blockPtr += 2) {
			if (currentAddress < rangeStart + maxSize) {
				if ((int)(currentAddress + size) <= *blockPtr) {
					gap = *blockPtr - currentAddress;
					if (maxGap > gap) {
						maxGap = gap;
					}
					result = currentAddress;
					bestBlock = blockPtr;
				}
			} else {
				blockPtr = m_AMemoryBank + 0x800;
			}
			currentAddress = blockPtr[0] + blockPtr[1];
		}

	if (((blockPtr[1] == 0) && (blockPtr < m_AMemoryBank + 0x800)) &&
		    (gap = (rangeStart + maxSize) - currentAddress, size <= gap) &&
		    (maxGap > gap)) {
			result = currentAddress;
			bestBlock = blockPtr;
		}
	} else {
		bestBlock = blockPtr;
	}

	if ((bestBlock == 0) || ((unsigned int)(rangeStart + maxSize) < result + size)) {
		OSRestoreInterrupts(interrupts);
		return 0;
	}

	blockPtr = bestBlock;
	if (blockPtr[1] > 0) {
		gap = ((int)(m_AMemoryBank + 0x800) - (int)(blockPtr + 2)) / 8;
		if (gap > 0) {
			memmove(blockPtr + 2, blockPtr, gap * 8);
		}
	}
	*blockPtr = result;
	blockPtr[1] = size;
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

	if (m_AMemoryBank != 0) {
		int* blockPtr = m_AMemoryBank;

		while ((blockPtr[1] != 0) && (blockPtr < m_AMemoryBank + 0x800)) {
			if (*blockPtr == address) {
				int entryCount = ((int)(m_AMemoryBank + 0x800) - (int)(blockPtr + 2)) / 8;

				if (entryCount > 0) {
					memcpy(blockPtr, blockPtr + 2, entryCount * 8);
					memset(m_AMemoryBank + 0x7FE, 0, 8);
				}
				break;
			}

			blockPtr += 2;
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
void RedDeleteA(void* param_1)
{
	RedDeleteA((int)param_1);
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
	int bankSize = 0x2000;
	bankSize += 0x1F;
	bankSize &= ~0x1F;

	m_MemoryBank = (int*)param1;
	m_AMemoryBank = (int*)((int)m_MemoryBank + bankSize);
	m_DataBuffer = (int)m_AMemoryBank + bankSize;
	m_DataBufferSize = param2 - bankSize * 2;
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
