#include "ffcc/p_game.h"

extern char s_CGamePcs_801D7C20[];

unsigned int m_table__8CGamePcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(s_CGamePcs_801D7C20), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x13, 0, 0, 0, 0, 0x17, 0, 0, 0,
    0, 0x19, 0, 0, 0, 0, 0x3A, 1, 0, 0, 0, 0x3C, 1, 0, 0, 0, 0x47, 1, 0, 0, 0, 0x4C
};

CGamePcs GamePcs;
extern "C" void* __vt__8CGamePcs[];

extern "C" void __sinit_p_game_cpp(void)
{
    *reinterpret_cast<void**>(&GamePcs) = __vt__8CGamePcs;

    unsigned int* dst = reinterpret_cast<unsigned int*>(m_table__8CGamePcs);

    dst[1] = m_table_desc0__8CGamePcs[0];
    dst[2] = m_table_desc0__8CGamePcs[1];
    dst[3] = m_table_desc0__8CGamePcs[2];
    dst[4] = m_table_desc1__8CGamePcs[0];
    dst[5] = m_table_desc1__8CGamePcs[1];
    dst[6] = m_table_desc1__8CGamePcs[2];
    dst[7] = m_table_desc2__8CGamePcs[0];
    dst[8] = m_table_desc2__8CGamePcs[1];
    dst[9] = m_table_desc2__8CGamePcs[2];
    dst[12] = m_table_desc3__8CGamePcs[0];
    dst[13] = m_table_desc3__8CGamePcs[1];
    dst[14] = m_table_desc3__8CGamePcs[2];
    dst[17] = m_table_desc4__8CGamePcs[0];
    dst[18] = m_table_desc4__8CGamePcs[1];
    dst[19] = m_table_desc4__8CGamePcs[2];
    dst[22] = m_table_desc5__8CGamePcs[0];
    dst[23] = m_table_desc5__8CGamePcs[1];
    dst[24] = m_table_desc5__8CGamePcs[2];
    dst[27] = m_table_desc6__8CGamePcs[0];
    dst[28] = m_table_desc6__8CGamePcs[1];
    dst[29] = m_table_desc6__8CGamePcs[2];
    dst[32] = m_table_desc7__8CGamePcs[0];
    dst[33] = m_table_desc7__8CGamePcs[1];
    dst[34] = m_table_desc7__8CGamePcs[2];
    dst[37] = m_table_desc8__8CGamePcs[0];
    dst[38] = m_table_desc8__8CGamePcs[1];
    dst[39] = m_table_desc8__8CGamePcs[2];
}

/*
 * --INFO--
 * PAL Address: 80047930
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::onMapChanged(int a, int b, int c)
{
    Game.MapChanged(a, b, c);
}

/*
 * --INFO--
 * PAL Address: 80047958
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::onMapChanging(int a, int b)
{
    Game.MapChanging(a, b);
}

/*
 * --INFO--
 * PAL Address: 80047980
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::onScriptChanged(char* script, int param)
{
    Game.ScriptChanged(script, param);
}

/*
 * --INFO--
 * PAL Address: 800479a8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::onScriptChanging(char* script)
{
    Game.ScriptChanging(script);
}

/*
 * --INFO--
 * PAL Address: 0x800479d0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::draw2()
{
    Game.Draw3();
}

/*
 * --INFO--
 * PAL Address: 0x800479f8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::draw1()
{
    Game.Draw2();
}

/*
 * --INFO--
 * PAL Address: 0x80047a20
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::draw0()
{
    Game.Draw();
}

/*
 * --INFO--
 * PAL Address: 0x80047a48
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::calc2()
{
    Game.Calc3();
}

/*
 * --INFO--
 * PAL Address: 0x80047a70
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::calc1()
{
    Game.Calc2();
}

/*
 * --INFO--
 * PAL Address: 0x80047a98
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::calc0()
{
    Game.Calc();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::calcInit()
{
    Game.CheckScriptChange();
}

/*
 * --INFO--
 * PAL Address: 0x80047ae8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::destroy()
{
    Game.Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x80047b10
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::create()
{
    Game.Create();
}

/*
 * --INFO--
 * PAL Address: 0x80047b38
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGamePcs::GetTable(unsigned long param)
{
    return (int)m_table__8CGamePcs + (int)param * 0x15C;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::Init()
{
	// TODO
}
