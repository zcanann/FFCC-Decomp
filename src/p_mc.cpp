#include "ffcc/p_mc.h"
#include "ffcc/goout.h"
#include "ffcc/math.h"
#include "ffcc/wm_menu.h"

extern CMath math;
extern "C" int Format__6McCtrlFi(McCtrl* mcCtrl, int slot);

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
CMcPcs::CMcPcs()
{
	// TODO
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
	// Based on assembly: mulli r4, r4, 0x15c; add to base address
	// 0x15c = 348 bytes per entry
	extern char lbl_80211DAC[];
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
    MenuPcsMcLayout* menuPcsLayout = reinterpret_cast<MenuPcsMcLayout*>(&MenuPcs);
    int result;
    int worldParam;

    math.Rand(0x7FFFFFFF);

    if (menuPcsLayout->field14 != 1)
    {
        if (menuPcsLayout->field18 == 0x13)
        {
            result = Format__6McCtrlFi(&menuPcsLayout->m_mcCtrl, 1);
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

                MenuPcs.CallWorldParam(6, worldParam, 0);
                menuPcsLayout->field18 = 0;
            }
        }
        else if (menuPcsLayout->field18 == 0x12)
        {
            result = menuPcsLayout->m_mcCtrl.ChkEmpty(0);
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

                MenuPcs.CallWorldParam(5, worldParam, 0);
                menuPcsLayout->field18 = 0;
            }
        }
    }
}
