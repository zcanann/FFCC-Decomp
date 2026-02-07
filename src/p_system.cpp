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
	unsigned short uVar2;
	int iVar1;
	
	if (Pad._452_4_ == 0) {
		// Calculate controller index and read button data
		// Complex controller selection logic from Ghidra
		int controllerIndex = Pad._448_4_;
		int indexCalc = (~((int)~(controllerIndex - 4 | 4 - controllerIndex) >> 0x1f) & 4U);
		unsigned char* padData = (unsigned char*)&Pad;
		uVar2 = *(unsigned short*)(padData + 0x36 + indexCalc * 0x54);
	}
	else {
		uVar2 = 0;
	}
	
	if ((uVar2 & 0x1000) == 0) { // Not START/MENU button
		if ((uVar2 & 0x100) == 0) { // Not A button
			if (((uVar2 & 0x800) == 0) && ((uVar2 & 0x40) != 0)) { // Not Y button, but L trigger
				iVar1 = Pad._448_4_ + 1;
				if (iVar1 == 0) {
					iVar1 = Pad._448_4_ + 2;
				}
				Pad._448_4_ = iVar1;
				if (3 < iVar1) {
					Pad._448_4_ = -1;
				}
			}
		}
		else {
			// A button pressed - add debug menu entry  
			// TODO: Need to properly call debug menu function
			// The original assembly shows: bl Add__11CDbgMenuPcsFv
		}
	}
}
