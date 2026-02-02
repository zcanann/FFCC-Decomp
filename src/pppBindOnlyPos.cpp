#include "ffcc/pppBindOnlyPos.h"

extern int DAT_8032ed70;

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
	if (DAT_8032ed70 != 0) {
		return;
	}
	return;
}