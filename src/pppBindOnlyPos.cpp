#include "ffcc/pppBindOnlyPos.h"

extern int lbl_8032ED70;
extern int* lbl_8032ED50;

/*
 * --INFO--
 * PAL Address: 0x80127b70
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructBindOnlyPos(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80127b54
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameBindOnlyPos(void)
{
	if (lbl_8032ED70 != 0) {
		return;
	}

	*(volatile unsigned int*)((char*)lbl_8032ED50 + 0xd8);
}
