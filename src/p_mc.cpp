#include "ffcc/p_mc.h"
#include "ffcc/math.h"
#include "ffcc/p_menu.h"
#include "ffcc/wm_menu.h"

extern CMath Math;
extern "C" int Format__6McCtrlFi(McCtrl* mcCtrl, int slot);
extern "C" int Rand__5CMathFUl(CMath* instance, unsigned long max);
extern "C" void CallWorldParam__8CMenuPcsFiii(CMenuPcs* menu, int mode, int param, int unused);
extern "C" void __sinit_p_mc_cpp(void);
extern unsigned char MenuPcs[];
extern unsigned char PTR_PTR_s_CMcPcs_80211f28[];
extern unsigned int lbl_8032EE88;

struct MenuPcsMcLayout
{
    unsigned char unk14[0x14];
    unsigned char field14;
    unsigned char unk15[3];
    signed char field18;
    unsigned char unk19[7];
    McCtrl m_mcCtrl;
};

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
	return m_table__6CMcPcs + (index * 0x15c);
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
 * PAL Address: 0x80124998
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMcPcs::calc()
{
    int result;
    int worldParam;

    Rand__5CMathFUl(&Math, 0x7FFFFFFF);

    if (reinterpret_cast<MenuPcsMcLayout*>(MenuPcs)->field14 != 1)
    {
        if (reinterpret_cast<MenuPcsMcLayout*>(MenuPcs)->field18 == 0x13)
        {
            result = Format__6McCtrlFi(&reinterpret_cast<MenuPcsMcLayout*>(MenuPcs)->m_mcCtrl, 1);
            if (result != 0)
            {
                if (result == 1)
                {
                    worldParam = 1;
                }
                else if (result == -1)
                {
                    worldParam = 4;
                }
                else
                {
                    worldParam = 6;
                }

                CallWorldParam__8CMenuPcsFiii(reinterpret_cast<CMenuPcs*>(MenuPcs), 6, worldParam, 0);
                reinterpret_cast<MenuPcsMcLayout*>(MenuPcs)->field18 = 0;
            }
        }
        else if (reinterpret_cast<MenuPcsMcLayout*>(MenuPcs)->field18 == 0x12 &&
                 (result = reinterpret_cast<MenuPcsMcLayout*>(MenuPcs)->m_mcCtrl.ChkEmpty(0), result != 0))
        {
            if (result == 1)
            {
                worldParam = 1;
            }
            else if (result == -1)
            {
                worldParam = 4;
            }
            else if (result == -2)
            {
                worldParam = 5;
            }
            else if (result == -3 || result == -4)
            {
                worldParam = 2;
            }
            else
            {
                worldParam = 6;
            }

            CallWorldParam__8CMenuPcsFiii(reinterpret_cast<CMenuPcs*>(MenuPcs), 5, worldParam, 0);
            reinterpret_cast<MenuPcsMcLayout*>(MenuPcs)->field18 = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80124af4
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_mc_cpp(void)
{
    unsigned int* table;
    unsigned int* table0;
    unsigned int* table1;
    unsigned int* table2;

    lbl_8032EE88 = (unsigned int)PTR_PTR_s_CMcPcs_80211f28;
    table = (unsigned int*)m_table__6CMcPcs;
    table0 = m_table_desc0__6CMcPcs;
    table1 = m_table_desc1__6CMcPcs;
    table2 = m_table_desc2__6CMcPcs;

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
