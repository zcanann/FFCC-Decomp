#include "ffcc/pppFilter.h"

extern volatile int lbl_8032ED70;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructFilter(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructFilter(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8015a8c8
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameFilter(void)
{
	(void)(lbl_8032ED70 == 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderFilter(void)
{
	// TODO
}
