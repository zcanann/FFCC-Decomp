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
int RedNew(int size)
{
	if (size <= 0 || !DAT_8032f4a0 || !DAT_8032f490) {
		return 0;
	}
	
	unsigned int alignedSize = (size + 0x1F) & 0xFFFFFFE0;
	int currentAddr = DAT_8032f490;
	int* blockPtr = DAT_8032f4a0;
	
	unsigned int interrupts = OSDisableInterrupts();
	
	while (blockPtr < DAT_8032f4a0 + 0x800) {
		if (!blockPtr[1] || (int)(currentAddr + alignedSize) <= blockPtr[0]) {
			if (DAT_8032f4a0[0x7FF] >= 1) {
				if (DAT_8032f408) {
					OSReport(s__s_sMemory_Bank_Full____s_801e7888, &DAT_801e78a3, &DAT_80333d20, &DAT_80333d28);
				}
				break;
			}
			
			if (currentAddr + alignedSize <= (unsigned int)(DAT_8032f490 + DAT_8032f498)) {
				if (blockPtr[1] > 0) {
					unsigned int moveCount = (int)DAT_8032f4a0 + (0x2000 - (int)(blockPtr + 2));
					int entryCount = ((int)moveCount >> 3) + ((int)moveCount < 0 && (moveCount & 7) != 0);
					if (entryCount > 0) {
						memmove(blockPtr + 2, blockPtr, entryCount * 8);
					}
				}
				
				blockPtr[0] = currentAddr;
				blockPtr[1] = alignedSize;
				OSRestoreInterrupts(interrupts);
				return currentAddr;
			}
		}
		
		currentAddr = blockPtr[0] + blockPtr[1];
		blockPtr += 2;
	}
	
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
 * Address:	TODO
 * Size:	TODO
 */
void RedDelete(void*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void RedDeleteA(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RedDeleteA(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedMemory::Init(int, int, int, int)
{
	// TODO
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
