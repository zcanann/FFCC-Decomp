#include "ffcc/p_system.h"
#include "ffcc/pad.h"
#include "ffcc/p_dbgmenu.h"

extern "C" void create__10CSystemPcsFv(CSystemPcs*);
extern "C" void destroy__10CSystemPcsFv(CSystemPcs*);
extern "C" void calc__10CSystemPcsFv(CSystemPcs*);
extern const char __RTTI__8CManager_8032E608[];
extern const char __RTTI__8CProcess_8032E610[];
CSystemPcs SystemPcs;
unsigned int m_table__10CSystemPcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>("CSystemPcs"),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x16,
    0x8
};
const char s_CManager_801D7C54[] = "CManager";
const char s_CProcess_801D7C60[] = "CProcess";
unsigned int s_CSystemPcsTablePad0_801EA250[3] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E608)), 0, 0};
unsigned int s_CSystemPcsTablePad1_801EA25C[5] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E608)),
    0,
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CProcess_8032E610)),
    0,
    0,
};

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
 * Address:	TODO
 * Size:	TODO
 */
void CSystemPcs::create()
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
	unsigned char* table = reinterpret_cast<unsigned char*>(m_table__10CSystemPcs);
	unsigned long offset = index * 0x15c;
	return (int)(table + offset);
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
 * Address:	TODO
 * Size:	TODO
 */
void CSystemPcs::Init()
{
	// TODO
}
