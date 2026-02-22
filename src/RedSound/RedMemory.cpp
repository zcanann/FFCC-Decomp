#include "ffcc/RedSound/RedMemory.h"
#include <dolphin/os.h>

// Memory functions
extern "C" {
	void* memmove(void* dest, const void* src, unsigned int n);
	void* memcpy(void* dest, const void* src, unsigned int n);
	void* memset(void* s, int c, unsigned int n);
}

// Global memory management data
extern int* DAT_8032f4a0;  // Main memory block list
extern int* DAT_8032f4a4;  // A memory block list  
extern int DAT_8032f490;   // Main memory base
extern int DAT_8032f494;   // A memory base
extern int DAT_8032f498;   // Main memory size
extern int DAT_8032f49c;   // A memory size
extern int DAT_8032f408;   // Debug output flag
extern char s__s_sMemory_Bank_Full____s_801e7888[];
extern char s__s_sA_Memory_Bank_Full____s_801e78b5[];
extern char DAT_801e78a3;
extern char DAT_80333d20;
extern char DAT_80333d28;
extern char DAT_8021d1a8;

// Function declarations
extern "C" {
	void fflush(void*);
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
extern "C" CRedMemory* __dt__10CRedMemoryFv(CRedMemory* redMemory, int shouldDelete)
{
	if ((redMemory != 0) && (0 < shouldDelete)) {
		__dl__FPv(redMemory);
	}
	return redMemory;
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
	int* entry;
	unsigned int alignedSize;
	unsigned int moveCount;
	BOOL interrupts;
	int address;
	int entryCount;
	int* slot;

	if (((param_1 < 1) || (DAT_8032f4a0 == (int*)0)) || (DAT_8032f490 == 0)) {
		return 0;
	}

	interrupts = OSDisableInterrupts();
	alignedSize = param_1 + 0x1FU & 0xFFFFFFE0;
	address = DAT_8032f490;
	slot = DAT_8032f4a0;
	do {
		if ((slot[1] == 0) || (address + (int)alignedSize <= *slot)) {
			if (DAT_8032f4a0[0x7FF] < 1) {
				if (address + (int)alignedSize <= DAT_8032f490 + DAT_8032f498) {
					if (0 < slot[1]) {
						moveCount = (int)DAT_8032f4a0 + (0x2000 - (int)(slot + 2));
						entryCount = ((int)moveCount >> 3) + (unsigned int)((int)moveCount < 0 && (moveCount & 7) != 0);
						if (0 < entryCount) {
							memmove(slot + 2, slot, entryCount * 8);
						}
					}
					*slot = address;
					slot[1] = alignedSize;
					OSRestoreInterrupts(interrupts);
					return address;
				}
			} else if (DAT_8032f408 != 0) {
				OSReport(s__s_sMemory_Bank_Full____s_801e7888, &DAT_801e78a3, &DAT_80333d20, &DAT_80333d28);
				fflush(&DAT_8021d1a8);
			}
			break;
		}
		address = *slot;
		entry = slot + 1;
		slot = slot + 2;
		address = address + *entry;
	} while (slot < DAT_8032f4a0 + 0x800);
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
	int* blockPtr = DAT_8032f4a0;
	
	if (blockPtr) {
		while (blockPtr[1] != 0 && blockPtr < DAT_8032f4a0 + 0x800) {
			if (blockPtr[0] == address) {
				unsigned int moveCount = (int)DAT_8032f4a0 + (0x2000 - (int)(blockPtr + 2));
				int entryCount = (int)moveCount / 8;
				if (entryCount > 0) {
					memcpy(blockPtr, blockPtr + 2, entryCount * 8);
					memset(DAT_8032f4a0 + 0x7FE, 0, 8);
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
#pragma dont_inline on
void RedDelete(void* param_1)
{
	RedDelete((int)param_1);
}
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

	if (size < 1 || DAT_8032f4a4 == (int*)0 || DAT_8032f494 == 0) {
		return 0;
	}
	if (DAT_8032f4a4[0x7FF] >= 1) {
		if (DAT_8032f408 != 0) {
			OSReport(s__s_sA_Memory_Bank_Full____s_801e78b5, &DAT_801e78a3, &DAT_80333d20, &DAT_80333d28);
			fflush(&DAT_8021d1a8);
		}
		return 0;
	}

	interrupts = OSDisableInterrupts();
	iVar6 = DAT_8032f494 + offset;
	if (maxSize == 0) {
		maxSize = DAT_8032f49c;
	}
	maxSize = maxSize - offset;
	alignedSize = size + 0x1FU & 0xFFFFFFE0;
	iVar7 = -1;
	bestBlock = (int*)0;
	for (blockPtr = DAT_8032f4a4; (blockPtr[1] != 0 && *blockPtr < iVar6); blockPtr = blockPtr + 2) {
	}
	iVar5 = maxSize;
	result = iVar6;
	iVar8 = iVar6;
	scanPtr = blockPtr;
	if (blockPtr[1] != 0) {
		for (; scanPtr[1] != 0 && scanPtr < DAT_8032f4a4 + 0x800; scanPtr = scanPtr + 2) {
			if (iVar8 < iVar6 + maxSize) {
				if ((int)(iVar8 + alignedSize) <= *scanPtr) {
					iVar7 = iVar8;
					bestBlock = scanPtr;
					if (*scanPtr - iVar8 < iVar5) {
						iVar5 = *scanPtr - iVar8;
					}
				}
			} else {
				scanPtr = DAT_8032f4a4 + 0x800;
			}
			iVar8 = *scanPtr + scanPtr[1];
		}
		result = iVar7;
		blockPtr = bestBlock;
		if (((scanPtr[1] == 0 && scanPtr < DAT_8032f4a4 + 0x800) &&
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
		moveCount = (int)DAT_8032f4a4 + (0x2000 - (int)(blockPtr + 2));
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
	int* blockPtr = DAT_8032f4a4;
	
	if (blockPtr) {
		while (blockPtr[1] != 0 && blockPtr < DAT_8032f4a4 + 0x800) {
			if (blockPtr[0] == address) {
				unsigned int moveCount = (int)DAT_8032f4a4 + (0x2000 - (int)(blockPtr + 2));
				int entryCount = (int)moveCount / 8;
				if (entryCount > 0) {
					memcpy(blockPtr, blockPtr + 2, entryCount * 8);
					memset(DAT_8032f4a4 + 0x7FE, 0, 8);
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
#pragma dont_inline on
void RedDeleteA(void* param_1)
{
	RedDeleteA((int)param_1);
}
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
void CRedMemory::Init(int param1, int param2, int param3, int param4)
{
	int* bankA = (int*)(param1 + 0x2000);

	DAT_8032f498 = param2 - 0x4000;
	DAT_8032f4a4 = bankA;
	DAT_8032f490 = param1 + 0x4000;
	DAT_8032f4a0 = (int*)param1;
	memset((void*)param1, 0, 0x2000);
	memset(bankA, 0, 0x2000);
	DAT_8032f494 = param3;
	DAT_8032f49c = param4;
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
	return DAT_8032f490;
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
	return DAT_8032f498;
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
	return DAT_8032f4a0;
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
	return DAT_8032f494;
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
	return DAT_8032f49c;
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
	return DAT_8032f4a4;
}
