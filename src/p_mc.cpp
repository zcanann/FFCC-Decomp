#include "ffcc/p_mc.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMcPcs::CMcPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMcPcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMcPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void* CMcPcs::GetTable(unsigned long index)
{
	// Based on assembly: mulli r4, r4, 0x15c; add to base address
	// 0x15c = 348 bytes per entry
	extern char lbl_80211DAC[];
	return lbl_80211DAC + (index * 0x15c);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMcPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMcPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMcPcs::calc()
{
	// TODO
}
