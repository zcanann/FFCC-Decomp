#include "ffcc/p_game.h"

extern "C" void create__8CGamePcsFv(CGamePcs*);
extern "C" void destroy__8CGamePcsFv(CGamePcs*);
extern "C" void calcInit__8CGamePcsFv(CGamePcs*);
extern "C" void calc0__8CGamePcsFv(CGamePcs*);
extern "C" void calc1__8CGamePcsFv(CGamePcs*);
extern "C" void calc2__8CGamePcsFv(CGamePcs*);
extern "C" void draw0__8CGamePcsFv(CGamePcs*);
extern "C" void draw1__8CGamePcsFv(CGamePcs*);
extern "C" void draw2__8CGamePcsFv(CGamePcs*);

extern char s_CGamePcs_801D7C20[];
unsigned int m_table_desc0__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__8CGamePcsFv)};
unsigned int m_table_desc1__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__8CGamePcsFv)};
unsigned int m_table_desc2__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__8CGamePcsFv)};
unsigned int m_table_desc3__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc0__8CGamePcsFv)};
unsigned int m_table_desc4__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc1__8CGamePcsFv)};
unsigned int m_table_desc5__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw0__8CGamePcsFv)};
unsigned int m_table_desc6__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw1__8CGamePcsFv)};
unsigned int m_table_desc7__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw2__8CGamePcsFv)};
unsigned int m_table_desc8__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc2__8CGamePcsFv)};

unsigned int m_table__8CGamePcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(s_CGamePcs_801D7C20), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x13, 0, 0, 0, 0, 0x17, 0, 0, 0,
    0, 0x19, 0, 0, 0, 0, 0x3A, 1, 0, 0, 0, 0x3C, 1, 0, 0, 0, 0x47, 1, 0, 0, 0, 0x4C
};

CGamePcs GamePcs;

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
