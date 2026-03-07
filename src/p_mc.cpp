#include "ffcc/p_mc.h"
#include "ffcc/math.h"
#include "ffcc/symbols_shared.h"

extern CMath Math;
struct McCtrl;
extern "C" unsigned char MenuPcs[];
extern "C" int Format__6McCtrlFi(McCtrl* mcCtrl, int slot);
extern "C" int ChkEmpty__6McCtrlFi(McCtrl* mcCtrl, int param_2);
extern "C" int Rand__5CMathFUl(CMath* instance, unsigned long max);
extern "C" void CallWorldParam__8CMenuPcsFiii(void* menu, int mode, int param, int unused);
extern "C" void __sinit_p_mc_cpp(void);

struct MenuPcsMcLayout
{
    unsigned char unk14[0x14];
    unsigned char field14;
    unsigned char unk15[3];
    signed char field18;
    unsigned char unk19[7 + 0x30];
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
    MenuPcsMcLayout* menu;

    Rand__5CMathFUl(&Math, 0x7FFFFFFF);
    menu = reinterpret_cast<MenuPcsMcLayout*>(&MenuPcs);

    if (menu->field14 != 1)
    {
        if (menu->field18 == 0x13)
        {
            result = Format__6McCtrlFi((McCtrl*)(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x20), 1);
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

                CallWorldParam__8CMenuPcsFiii(&MenuPcs, 6, worldParam, 0);
                menu->field18 = 0;
            }
        }
        else if (reinterpret_cast<MenuPcsMcLayout*>(&MenuPcs)->field18 == 0x12 &&
                 (result = ChkEmpty__6McCtrlFi((McCtrl*)(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x20), 0),
                  result != 0))
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

            CallWorldParam__8CMenuPcsFiii(&MenuPcs, 5, worldParam, 0);
            menu->field18 = 0;
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

    gMcPcsSingletonPtr = (unsigned int)sMcPcsSingletonData;
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
