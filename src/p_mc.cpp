#include "ffcc/p_mc.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
extern "C" {
extern unsigned char* gMcPcsSingletonPtr;
}
extern "C" void create__6CMcPcsFv(CMcPcs*);
extern "C" void destroy__6CMcPcsFv(CMcPcs*);
extern "C" void calc__6CMcPcsFv(CMcPcs*);
extern char lbl_80331B10[];
extern char lbl_8032E9D0[];
extern char lbl_8032E9D8[];

unsigned int m_table_desc0__6CMcPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__6CMcPcsFv)};
unsigned int m_table_desc1__6CMcPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__6CMcPcsFv)};
unsigned int m_table_desc2__6CMcPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__6CMcPcsFv)};
unsigned int m_table__6CMcPcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(lbl_80331B10), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1B
};
unsigned int lbl_80211F08[3] = {reinterpret_cast<unsigned int>(lbl_8032E9D0), 0, 0};
unsigned int lbl_80211F14[5] = {
    reinterpret_cast<unsigned int>(lbl_8032E9D0), 0, reinterpret_cast<unsigned int>(lbl_8032E9D8), 0, 0
};

unsigned char* gMcPcsSingletonPtr = 0;

class McCtrl;

extern "C" int Format__6McCtrlFi(McCtrl* mcCtrl, int slot);
extern "C" int Rand__5CMathFUl(CMath* instance, unsigned long max);
extern "C" void CallWorldParam__8CMenuPcsFiii(void* menu, int mode, int param, int unused);

class McCtrl
{
public:
    int ChkEmpty(int);

    int m_previousState;
    int m_state;
    int m_cardChannel;
    int m_lastResult;
    int m_saveIndex;
    int m_iteration;
    int m_createFlag;
    void* m_userBuffer;
    unsigned int m_serialLo;
    unsigned int m_serialHi;
};

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
int CMcPcs::GetTable(unsigned long index)
{
	return (int)(reinterpret_cast<unsigned char*>(m_table__6CMcPcs) + (index * 0x15c));
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

    if (reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).field14 != 1)
    {
        if (reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).field18 == 0x13)
        {
            result = Format__6McCtrlFi(&reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).m_mcCtrl, 1);
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

            CallWorldParam__8CMenuPcsFiii(&MenuPcs, 5, worldParam, 0);
            reinterpret_cast<MenuPcsMcLayout&>(MenuPcs).field18 = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80124AF4
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

    table = m_table__6CMcPcs;
    table0 = m_table_desc0__6CMcPcs;
    table1 = m_table_desc1__6CMcPcs;
    table2 = m_table_desc2__6CMcPcs;
    gMcPcsSingletonPtr = sMcPcsSingletonData;
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
