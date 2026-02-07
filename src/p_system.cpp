#include "ffcc/p_system.h"
#include "ffcc/pad.h"
#include "ffcc/p_dbgmenu.h"

extern unsigned char lbl_801EA0F4[];

/*
 * --INFO--
 * PAL Address: 0x80047d7c
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __sinit_p_system_cpp(void)
{
	// TODO: Static initialization
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSystemPcs::CSystemPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystemPcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystemPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80047d60
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSystemPcs::GetTable(unsigned long index)
{
	unsigned char* table = lbl_801EA0F4;
	unsigned long offset = index * 0x15c;
	return (int)(table + offset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystemPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystemPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80047c9c
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSystemPcs::calc()
{
	unsigned short buttons;
	int i;

	if (Pad._452_4_ == 0) {
		i = Pad._448_4_;
		buttons = *(unsigned short*)(((unsigned char*)&Pad) +
		                             ((~((int)~(i - 4 | 4 - i) >> 0x1f) & 4U) * 0x54 + 0x36));
	} else {
		buttons = 0;
	}

	if ((buttons & 0x1000) != 0) {
		return;
	}
	if ((buttons & 0x100) != 0) {
		((CDbgMenuPcs*)0x80306708)->Add();
		return;
	}
	if (((buttons & 0x800) == 0) && ((buttons & 0x40) != 0)) {
		i = Pad._448_4_ + 1;
		if (i == 0) {
			i = Pad._448_4_ + 2;
		}
		Pad._448_4_ = i;
		if (3 < i) {
			Pad._448_4_ = -1;
		}
	}
}
