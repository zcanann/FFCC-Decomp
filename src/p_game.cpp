#include "ffcc/p_game.h"

extern "C" {
void create__8CGamePcsFv(CGamePcs*);
void destroy__8CGamePcsFv(CGamePcs*);
void calcInit__8CGamePcsFv(CGamePcs*);
void calc0__8CGamePcsFv(CGamePcs*);
void calc1__8CGamePcsFv(CGamePcs*);
void calc2__8CGamePcsFv(CGamePcs*);
void draw0__8CGamePcsFv(CGamePcs*);
void draw1__8CGamePcsFv(CGamePcs*);
void draw2__8CGamePcsFv(CGamePcs*);
}

inline CGamePcs::CGamePcs()
{
    static CProcessTableCallback desc0 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__8CGamePcsFv)};
    static CProcessTableCallback desc1 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__8CGamePcsFv)};
    static CProcessTableCallback desc2 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__8CGamePcsFv)};
    static CProcessTableCallback desc3 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc0__8CGamePcsFv)};
    static CProcessTableCallback desc4 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc1__8CGamePcsFv)};
    static CProcessTableCallback desc5 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw0__8CGamePcsFv)};
    static CProcessTableCallback desc6 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw1__8CGamePcsFv)};
    static CProcessTableCallback desc7 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw2__8CGamePcsFv)};
    static CProcessTableCallback desc8 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc2__8CGamePcsFv)};

    CProcessTable* table = &m_table;

    table->m_fields.m_create = desc0;
    table->m_fields.m_destroy = desc1;
    table->m_fields.m_entries[0].m_callback = desc2;
    table->m_fields.m_entries[1].m_callback = desc3;
    table->m_fields.m_entries[2].m_callback = desc4;
    table->m_fields.m_entries[3].m_callback = desc5;
    table->m_fields.m_entries[4].m_callback = desc6;
    table->m_fields.m_entries[5].m_callback = desc7;
    table->m_fields.m_entries[6].m_callback = desc8;
}

CProcessTable CGamePcs::m_table = {
    "CGamePcs",
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0x13, 0, 0, 0, 0, 0x17, 0, 0, 0,
        0, 0x19, 0, 0, 0, 0, 0x3A, 1, 0, 0, 0, 0x3C, 1, 0, 0, 0, 0x47, 1, 0, 0, 0, 0x4C,
    },
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
    return reinterpret_cast<int>(&m_table + param);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::Quit()
{
    return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::Init()
{
    return;
}
