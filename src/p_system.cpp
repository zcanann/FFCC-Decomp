#include "ffcc/p_system.h"
#include "ffcc/pad.h"
#include "ffcc/p_dbgmenu.h"

CSystemPcs SystemPcs;
extern "C" unsigned int __vt__10CSystemPcs[];
unsigned int m_table_desc0__10CSystemPcs[3];
unsigned int m_table_desc1__10CSystemPcs[3];
unsigned int m_table_desc2__10CSystemPcs[3];
unsigned char m_table__10CSystemPcs[0x15C];

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
    *reinterpret_cast<unsigned int*>(&SystemPcs) = reinterpret_cast<unsigned int>(__vt__10CSystemPcs);
    reinterpret_cast<unsigned int*>(m_table__10CSystemPcs)[1] = m_table_desc0__10CSystemPcs[0];
    reinterpret_cast<unsigned int*>(m_table__10CSystemPcs)[2] = m_table_desc0__10CSystemPcs[1];
    reinterpret_cast<unsigned int*>(m_table__10CSystemPcs)[3] = m_table_desc0__10CSystemPcs[2];
    reinterpret_cast<unsigned int*>(m_table__10CSystemPcs)[4] = m_table_desc1__10CSystemPcs[0];
    reinterpret_cast<unsigned int*>(m_table__10CSystemPcs)[5] = m_table_desc1__10CSystemPcs[1];
    reinterpret_cast<unsigned int*>(m_table__10CSystemPcs)[6] = m_table_desc1__10CSystemPcs[2];
    reinterpret_cast<unsigned int*>(m_table__10CSystemPcs)[7] = m_table_desc2__10CSystemPcs[0];
    reinterpret_cast<unsigned int*>(m_table__10CSystemPcs)[8] = m_table_desc2__10CSystemPcs[1];
    reinterpret_cast<unsigned int*>(m_table__10CSystemPcs)[9] = m_table_desc2__10CSystemPcs[2];
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
	unsigned char* table = m_table__10CSystemPcs;
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
