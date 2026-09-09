#include "ffcc/p_mc.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/wm_menu.h"

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMcPcs::CMcPcs()
{
}

CMcPcs McPcs;

CProcessCallbackTable CMcPcs::m_table = {
    "CMcPcs",
    static_cast<CProcessCallback>(&CMcPcs::create),
    static_cast<CProcessCallback>(&CMcPcs::destroy),
    {
        {static_cast<CProcessCallback>(&CMcPcs::calc), 0x1b, 0},
    },
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

    if (MenuPcs.m_mcRequestLocked != 1)
    {
        if (MenuPcs.m_mcRequest == 0x13)
        {
            result = MenuPcs.GetMcCtrl()->Format(1);
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
                MenuPcs.m_mcRequest = 0;
            }
        }
        else if (MenuPcs.m_mcRequest == 0x12 &&
                 (result = MenuPcs.GetMcCtrl()->ChkEmpty(0), result != 0))
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
            MenuPcs.m_mcRequest = 0;
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
