#include "ffcc/p_system.h"
#include "ffcc/pad.h"
#include "ffcc/p_dbgmenu.h"

extern unsigned int lbl_801EA0D0[];
extern unsigned int lbl_801EA0DC[];
extern unsigned int lbl_801EA0E8[];
extern unsigned int lbl_801EA270[];
extern unsigned char lbl_801EA0F4[];
extern unsigned int lbl_8032ED08;

/*
 * --INFO--
 * PAL Address: 0x80047d7c
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_system_cpp(void)
{
    unsigned int* table;
    unsigned int* table0;
    unsigned int* table1;
    unsigned int* table2;

    lbl_8032ED08 = reinterpret_cast<unsigned int>(lbl_801EA270);
    table = reinterpret_cast<unsigned int*>(lbl_801EA0F4);
    table0 = lbl_801EA0D0;
    table1 = lbl_801EA0DC;
    table2 = lbl_801EA0E8;

    table[1] = table0[0];
    table[2] = table0[1];
    table[3] = table0[2];
    table[4] = table1[0];
    table[5] = table1[1];
    table[6] = table1[2];
    table[7] = table2[0];
    table[8] = table2[1];
    table[9] = table2[2];
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
    int debugPad;
    int stepPad;
    unsigned short buttons;

    if ((int)Pad._1c4_4_ != 0) {
        buttons = 0;
    } else {
        debugPad = (int)Pad._1c0_4_;
        stepPad = (debugPad == 4) ? 0 : 4;
        buttons = *(unsigned short*)(((unsigned char*)&Pad) + stepPad * 0x54 + 0x36);
    }

    if ((buttons & 0x1000) != 0) {
        return;
    }
    if ((buttons & 0x100) != 0) {
        DbgMenuPcs.Add();
        return;
    }
    if (((buttons & 0x800) == 0) && ((buttons & 0x40) != 0)) {
        int nextPad = (int)Pad._1c0_4_ + 1;
        if (nextPad == 0) {
            nextPad++;
        }
        if (nextPad > 3) {
            nextPad = -1;
        }
        Pad._1c0_4_ = (unsigned int)nextPad;
    }
}
