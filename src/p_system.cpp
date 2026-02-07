#include "ffcc/p_system.h"
#include "ffcc/pad.h"
#include "ffcc/p_dbgmenu.h"
extern int lbl_801EA0F4[];

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
	return (int)lbl_801EA0F4 + index * 0x15c;
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
	extern CDbgMenuPcs MiniGamePcs;
	unsigned short buttons;
	CPad* pad = &Pad;

	if (pad->_452_4_ == 0) {
		int controller = pad->_448_4_;
		int port = (~((int)~(controller - 4 | 4 - controller) >> 0x1f) & 4);
		buttons = *(unsigned short*)((unsigned char*)pad + 0x36 + port * 0x54);
	} else {
		buttons = 0;
	}

	if ((buttons & 0x1000) != 0) {
		return;
	}

	if ((buttons & 0x100) != 0) {
		MiniGamePcs.Add();
		return;
	}

	if ((buttons & 0x800) != 0) {
		return;
	}

	if ((buttons & 0x40) == 0) {
		return;
	}

	int next = pad->_448_4_ + 1;
	if (next == 0) {
		next = pad->_448_4_ + 2;
	}
	if (next > 3) {
		next = -1;
	}
	pad->_448_4_ = next;
}
