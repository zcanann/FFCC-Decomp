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
 * Address:	TODO
 * Size:	TODO
 */
CRedMemory::~CRedMemory()
{
	// TODO
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
	int *piVar1;
	unsigned int uVar2;
	unsigned int uVar3;
	unsigned int uVar4;
	int iVar5;
	int iVar6;
	int *piVar7;
	
	if (((0 < param_1) && (DAT_8032f4a0 != (int *)0x0)) && (DAT_8032f490 != 0)) {
		uVar4 = OSDisableInterrupts();
		uVar2 = param_1 + 0x1fU & 0xffffffe0;
		iVar5 = DAT_8032f490;
		piVar7 = DAT_8032f4a0;
		do {
			if ((piVar7[1] == 0) || ((int)(iVar5 + uVar2) <= *piVar7)) {
				if (DAT_8032f4a0[0x7ff] < 1) {
					if (iVar5 + uVar2 <= (unsigned int)(DAT_8032f490 + DAT_8032f498)) {
						if (0 < piVar7[1]) {
							uVar3 = (int)DAT_8032f4a0 + (0x2000 - (int)(piVar7 + 2));
							iVar6 = ((int)uVar3 >> 3) + (unsigned int)((int)uVar3 < 0 && (uVar3 & 7) != 0);
							if (0 < iVar6) {
								memmove(piVar7 + 2, piVar7, iVar6 * 8);
							}
						}
						*piVar7 = iVar5;
						piVar7[1] = uVar2;
						OSRestoreInterrupts(uVar4);
						return iVar5;
					}
				}
				else {
					if (DAT_8032f408 != 0) {
						OSReport(s__s_sMemory_Bank_Full____s_801e7888, &DAT_801e78a3, &DAT_80333d20, &DAT_80333d28);
						fflush(&DAT_8021d1a8);
					}
				}
				break;
			}
			iVar5 = *piVar7;
			piVar1 = piVar7 + 1;
			piVar7 = piVar7 + 2;
			iVar5 = iVar5 + *piVar1;
		} while (piVar7 < DAT_8032f4a0 + 0x800);
		OSRestoreInterrupts(uVar4);
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
	int* blockPtr = DAT_8032f4a0;
	
	if (blockPtr) {
		while (blockPtr[1] != 0 && blockPtr < DAT_8032f4a0 + 0x800) {
			if (blockPtr[0] == address) {
				unsigned int moveCount = (int)DAT_8032f4a0 + (0x2000 - (int)(blockPtr + 2));
				int entryCount = ((int)moveCount >> 3) + ((int)moveCount < 0 && (moveCount & 7) != 0);
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
void RedDelete(unsigned int param_1)
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
	if (size < 1 || !DAT_8032f4a4 || !DAT_8032f494) {
		return 0;
	}
	
	if (DAT_8032f4a4[0x7FF] >= 1) {
		if (DAT_8032f408) {
			OSReport(s__s_sA_Memory_Bank_Full____s_801e78b5, &DAT_801e78a3, &DAT_80333d20, &DAT_80333d28);
		}
		return 0;
	}
	
	unsigned int interrupts = OSDisableInterrupts();
	int baseAddr = DAT_8032f494 + offset;
	
	if (maxSize == 0) {
		maxSize = DAT_8032f49c;
	}
	maxSize = maxSize - offset;
	
	unsigned int alignedSize = (size + 0x1F) & 0xFFFFFFE0;
	int bestFit = -1;
	int* bestBlock = 0;
	int* blockPtr = DAT_8032f4a4;
	
	// Find first block that comes after our base address
	while (blockPtr[1] != 0 && blockPtr[0] < baseAddr) {
		blockPtr += 2;
	}
	
	int searchSpace = maxSize;
	int resultAddr = baseAddr;
	int currentAddr = baseAddr;
	int* targetBlock = blockPtr;
	
	if (blockPtr[1] != 0) {
		// Search through existing blocks for best fit
		while (blockPtr[1] != 0 && blockPtr < DAT_8032f4a4 + 0x800) {
			if (currentAddr < baseAddr + maxSize) {
				if ((int)(currentAddr + alignedSize) <= blockPtr[0]) {
					bestFit = currentAddr;
					bestBlock = blockPtr;
					if (blockPtr[0] - currentAddr < searchSpace) {
						searchSpace = blockPtr[0] - currentAddr;
					}
				}
			} else {
				blockPtr = DAT_8032f4a4 + 0x800;
			}
			currentAddr = blockPtr[0] + blockPtr[1];
			blockPtr += 2;
		}
		
		resultAddr = bestFit;
		targetBlock = bestBlock;
		
		// Check if we can fit at the end
		if (blockPtr[1] == 0 && blockPtr < DAT_8032f4a4 + 0x800) {
			int remainingSpace = (baseAddr + maxSize) - currentAddr;
			if ((int)alignedSize <= remainingSpace && remainingSpace < searchSpace) {
				resultAddr = currentAddr;
				targetBlock = blockPtr;
			}
		}
	}
	
	if (!targetBlock || (unsigned int)(baseAddr + maxSize) < resultAddr + alignedSize) {
		OSRestoreInterrupts(interrupts);
		return 0;
	}
	
	if (targetBlock[1] > 0) {
		unsigned int moveCount = (int)DAT_8032f4a4 + (0x2000 - (int)(targetBlock + 2));
		int entryCount = ((int)moveCount >> 3) + ((int)moveCount < 0 && (moveCount & 7) != 0);
		if (entryCount > 0) {
			memmove(targetBlock + 2, targetBlock, entryCount * 8);
		}
	}
	
	targetBlock[0] = resultAddr;
	targetBlock[1] = alignedSize;
	OSRestoreInterrupts(interrupts);
	return resultAddr;
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
				int entryCount = ((int)moveCount >> 3) + ((int)moveCount < 0 && (moveCount & 7) != 0);
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
void RedDeleteA(unsigned int param_1)
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
	DAT_8032f498 = param2 + -0x4000;
	DAT_8032f4a4 = (int*)(param1 + 0x2000);
	DAT_8032f490 = param1 + 0x4000;
	DAT_8032f4a0 = (int*)param1;
	memset((void*)param1, 0, 0x2000);
	memset(DAT_8032f4a4, 0, 0x2000);
	DAT_8032f494 = param3;
	DAT_8032f49c = param4;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedMemory::GetMainBufferAddress()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedMemory::GetMainBufferSize()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedMemory::GetMainBankAddress()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedMemory::GetABufferAddress()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedMemory::GetABufferSize()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedMemory::GetABankAddress()
{
	// TODO
}
