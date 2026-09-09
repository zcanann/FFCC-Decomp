#include "ffcc/p_system.h"
#include "ffcc/pad.h"
#include "ffcc/p_dbgmenu.h"

extern "C" {
void create__10CSystemPcsFv(CSystemPcs*);
void destroy__10CSystemPcsFv(CSystemPcs*);
void calc__10CSystemPcsFv(CSystemPcs*);
}

inline CSystemPcs::CSystemPcs()
{
    static CProcessTableCallback desc0 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__10CSystemPcsFv)};
    static CProcessTableCallback desc1 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__10CSystemPcsFv)};
    static CProcessTableCallback desc2 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__10CSystemPcsFv)};

    CProcessTable* table = &m_table;

    table->m_fields.m_create = desc0;
    table->m_fields.m_destroy = desc1;
    table->m_fields.m_entries[0].m_callback = desc2;
}

CSystemPcs SystemPcs;
CProcessTable CSystemPcs::m_table = {
    "CSystemPcs",
    {
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
        0x8,
    },
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
    unsigned short buttons = Pad.GetDebugButtonDown(4);

    if ((buttons & 0x1000) != 0) {
        return;
    }
    if ((buttons & 0x100) != 0) {
        DbgMenuPcs.Add();
        return;
    }
    if (((buttons & 0x800) == 0) && ((buttons & 0x40) != 0)) {
        int nextPad = Pad.m_debugPadPort + 1;
        if (nextPad == 0) {
            nextPad++;
        }
        if (nextPad > 3) {
            nextPad = -1;
        }
        Pad.m_debugPadPort = nextPad;
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
	return reinterpret_cast<int>(&CSystemPcs::m_table + index);
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
