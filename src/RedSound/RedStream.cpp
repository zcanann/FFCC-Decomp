#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedExecute.h"
#include <string.h>

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SearchEmptyStreamData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _StreamStop(RedStreamDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ArrangeStreamDataNoLoop(RedStreamDATA*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	801cbc6c
 * Size:	856b
 */
void _ArrangeStreamDataLoop(RedStreamDATA* param_1, unsigned int param_2, int param_3)
{
	unsigned int* puVar1;
	unsigned int* puVar3;
	unsigned char* pbVar4;
	unsigned char* pbVar5;
	unsigned char* pbVar6;
	unsigned int* puVar7;
	int iVar8;

	param_2 = param_2 & 1;
	
	if (*(short*)((int)param_1 + 0x2a) == 2) {
		do {
			pbVar6 = (unsigned char*)(*(int*)((int)param_1 + 0xc) + param_2 * 0x1000);
			iVar8 = *(int*)((int)param_1 + 4);
			puVar7 = (unsigned int*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120));
			pbVar4 = pbVar6 + 0x2000;
			puVar3 = puVar7 + 0x400;
			pbVar5 = pbVar6;
			
			do {
				*(unsigned int*)pbVar5 = *puVar7;
				*(unsigned int*)(pbVar5 + 4) = puVar7[1];
				pbVar5 = pbVar5 + 8;
				*(unsigned int*)pbVar4 = puVar7[2];
				puVar1 = puVar7 + 3;
				puVar7 = puVar7 + 4;
				*(unsigned int*)(pbVar4 + 4) = *puVar1;
				pbVar4 = pbVar4 + 8;
			} while (puVar7 < puVar3);
			
			*(int*)((int)param_1 + 0x120) = *(int*)((int)param_1 + 0x120) + 0x1000;
			if (*(int*)((int)param_1 + 0x118) <= *(int*)((int)param_1 + 0x120)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
			
			puVar7 = (unsigned int*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120));
			puVar3 = puVar7 + 0x400;
			
			do {
				*(unsigned int*)pbVar5 = *puVar7;
				*(unsigned int*)(pbVar5 + 4) = puVar7[1];
				pbVar5 = pbVar5 + 8;
				*(unsigned int*)pbVar4 = puVar7[2];
				puVar1 = puVar7 + 3;
				puVar7 = puVar7 + 4;
				*(unsigned int*)(pbVar4 + 4) = *puVar1;
				pbVar4 = pbVar4 + 8;
			} while (puVar7 < puVar3);
			
			*(int*)((int)param_1 + 0x120) = *(int*)((int)param_1 + 0x120) + 0x1000;
			if (*(int*)((int)param_1 + 0x118) <= *(int*)((int)param_1 + 0x120)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
			
			RedDmaEntry(0x8001, 0, (int)pbVar6, *(int*)((int)param_1 + 300) + param_2 * 0x1000, 0x1000, 0, 0);
			RedDmaEntry(0x8001, 0, (int)(pbVar6 + 0x2000), *(int*)((int)param_1 + 300) + (param_2 + 2) * 0x1000, 0x1000, 0, 0);
			
			if ((param_2 == 0) && (*(int*)(iVar8 + 0x14) != 0)) {
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ec) = (unsigned short)*pbVar6;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1f0) = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ee) = 0;
				*(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) | 0x100000;
				*(unsigned short*)(*(int*)(iVar8 + 0xd4) + 0x1ec) = (unsigned short)pbVar6[0x2000];
				*(unsigned short*)(*(int*)(iVar8 + 0xd4) + 0x1f0) = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0xd4) + 0x1ee) = 0;
				*(unsigned int*)(*(int*)(iVar8 + 0xd4) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0xd4) + 0x1c) | 0x100000;
			}
			
			param_2 = param_2 ^ 1;
			param_3 = param_3 + -0x1000;
			*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + 0x200;
			
			if (*(int*)((int)param_1 + 0x1c) <= *(int*)((int)param_1 + 0x124)) {
				*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) - *(int*)((int)param_1 + 0x1c);
				*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + *(int*)((int)param_1 + 0x20);
			}
		} while (0 < param_3);
	} else {
		do {
			pbVar5 = (unsigned char*)(*(int*)((int)param_1 + 0xc) + param_2 * 0x1000);
			iVar8 = *(int*)((int)param_1 + 4);
			memcpy(pbVar5, (void*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120)), 0x1000);
			*(int*)((int)param_1 + 0x120) = *(int*)((int)param_1 + 0x120) + 0x1000;
			
			if (*(int*)((int)param_1 + 0x118) <= *(int*)((int)param_1 + 0x120)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
			
			RedDmaEntry(0x8001, 0, (int)pbVar5, *(int*)((int)param_1 + 300) + param_2 * 0x1000, 0x1000, 0, 0);
			
			if ((param_2 == 0) && (*(int*)(iVar8 + 0x14) != 0)) {
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ec) = (unsigned short)*pbVar5;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1f0) = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ee) = 0;
				*(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) | 0x100000;
			}
			
			param_2 = param_2 ^ 1;
			param_3 = param_3 + -0x1000;
			*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + 0x200;
			
			if (*(int*)((int)param_1 + 0x1c) <= *(int*)((int)param_1 + 0x124)) {
				*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) - *(int*)((int)param_1 + 0x1c);
				*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + *(int*)((int)param_1 + 0x20);
			}
		} while (0 < param_3);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void StreamStop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void StreamPlay(int, void*, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetStreamVolume(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void StreamPause(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void StreamControl()
{
	// TODO
}
