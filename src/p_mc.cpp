#include "ffcc/p_mc.h"
#include "ffcc/math.h"
#include "ffcc/p_menu.h"
#include "ffcc/wm_menu.h"

extern CMath math[];
extern "C" int Format__6McCtrlFi(McCtrl* mcCtrl, int slot);
extern "C" int Rand__5CMathFUl(CMath* instance, unsigned long max);
extern "C" void CallWorldParam__8CMenuPcsFiii(CMenuPcs* menu, int mode, int param, int unused);
extern "C" void __sinit_p_mc_cpp(void);
extern unsigned char MenuPcs[];

extern unsigned int lbl_80211D88[];
extern unsigned int lbl_80211D94[];
extern unsigned int lbl_80211DA0[];
extern unsigned char lbl_80211DAC[];
extern unsigned char lbl_80211F28[];
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
 * PAL Address: 0x80124af4
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_mc_cpp(void)
{
    unsigned int* table = (unsigned int*)lbl_80211DAC;
    unsigned int* ptr = (unsigned int*)lbl_80211F28;
    lbl_8032EE88 = (unsigned int)ptr;

    table[1] = lbl_80211D88[0];
    table[2] = lbl_80211D88[1];
    table[3] = lbl_80211D88[2];
    table[4] = lbl_80211D94[0];
    table[5] = lbl_80211D94[1];
    table[6] = lbl_80211D94[2];
    table[7] = lbl_80211DA0[0];
    table[8] = lbl_80211DA0[1];
    table[9] = lbl_80211DA0[2];
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

    Rand__5CMathFUl(math, 0x7FFFFFFF);

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
