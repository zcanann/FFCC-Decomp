#include "ffcc/p_mc.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/wm_menu.h"

extern const char s_CMcPcs_80331B10[];
extern const float FLOAT_80331b18 = 1.0f;
extern const float FLOAT_80331b1c = 10.0f;

CProcessTable CMcPcs::m_table = {
    const_cast<char*>(s_CMcPcs_80331B10),
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
        0x1B,
    },
};

CMcPcs McPcs;

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

    Math.Rand(0x7FFFFFFF);

    if (reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).field14 != 1)
    {
        if (reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).field18 == 0x13)
        {
            result = reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).m_mcCtrl.Format(1);
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
                reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).field18 = 0;
            }
        }
        else if (reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).field18 == 0x12 &&
                 (result = reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).m_mcCtrl.ChkEmpty(0), result != 0))
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
            reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).field18 = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80124AD0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMcPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80124AD4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMcPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80124AD8
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMcPcs::GetTable(unsigned long index)
{
	return reinterpret_cast<int>(&m_table + index);
}

/*
 * --INFO--
 * PAL Address: 0x80124AEC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMcPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80124AF0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMcPcs::Init()
{
	// TODO
}
