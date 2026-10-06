#include "ffcc/p_game.h"

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CGamePcs::CGamePcs()
{
}

CGamePcs GamePcs;

CProcessCallbackTable CGamePcs::m_table = {
    "CGamePcs",
    static_cast<CProcessCallback>(&CGamePcs::create),
    static_cast<CProcessCallback>(&CGamePcs::destroy),
    {
        {static_cast<CProcessCallback>(&CGamePcs::calcInit), 0x13, 0},
        {static_cast<CProcessCallback>(&CGamePcs::calc0), 0x17, 0},
        {static_cast<CProcessCallback>(&CGamePcs::calc1), 0x19, 0},
        {static_cast<CProcessCallback>(&CGamePcs::draw0), 0x3a, 1},
        {static_cast<CProcessCallback>(&CGamePcs::draw1), 0x3c, 1},
        {static_cast<CProcessCallback>(&CGamePcs::draw2), 0x47, 1},
        {static_cast<CProcessCallback>(&CGamePcs::calc2), 0x4c, 0},
    },
};

/*
 * --INFO--
 * PAL Address: 80047930
 * PAL Size: 40b
 * EN Address: 0x80047724
 * EN Size: 40b
 * JP Address: 0x8004727C
 * JP Size: 40b
 */
void CGamePcs::onMapChanged(int a, int b, int c)
{
    Game.MapChanged(a, b, c);
}

/*
 * --INFO--
 * PAL Address: 80047958
 * PAL Size: 40b
 * EN Address: 0x8004774C
 * EN Size: 40b
 * JP Address: 0x800472A4
 * JP Size: 40b
 */
void CGamePcs::onMapChanging(int a, int b)
{
    Game.MapChanging(a, b);
}

/*
 * --INFO--
 * PAL Address: 80047980
 * PAL Size: 40b
 * EN Address: 0x80047774
 * EN Size: 40b
 * JP Address: 0x800472CC
 * JP Size: 40b
 */
void CGamePcs::onScriptChanged(char* script, int param)
{
    Game.ScriptChanged(script, param);
}

/*
 * --INFO--
 * PAL Address: 800479a8
 * PAL Size: 40b
 * EN Address: 0x8004779C
 * EN Size: 40b
 * JP Address: 0x800472F4
 * JP Size: 40b
 */
void CGamePcs::onScriptChanging(char* script)
{
    Game.ScriptChanging(script);
}

/*
 * --INFO--
 * PAL Address: 0x800479d0
 * PAL Size: 40b
 * EN Address: 0x800477C4
 * EN Size: 40b
 * JP Address: 0x8004731C
 * JP Size: 40b
 */
void CGamePcs::draw2()
{
    Game.Draw3();
}

/*
 * --INFO--
 * PAL Address: 0x800479f8
 * PAL Size: 40b
 * EN Address: 0x800477EC
 * EN Size: 40b
 * JP Address: 0x80047344
 * JP Size: 40b
 */
void CGamePcs::draw1()
{
    Game.Draw2();
}

/*
 * --INFO--
 * PAL Address: 0x80047a20
 * PAL Size: 40b
 * EN Address: 0x80047814
 * EN Size: 40b
 * JP Address: 0x8004736C
 * JP Size: 40b
 */
void CGamePcs::draw0()
{
    Game.Draw();
}

/*
 * --INFO--
 * PAL Address: 0x80047a48
 * PAL Size: 40b
 * EN Address: 0x8004783C
 * EN Size: 40b
 * JP Address: 0x80047394
 * JP Size: 40b
 */
void CGamePcs::calc2()
{
    Game.Calc3();
}

/*
 * --INFO--
 * PAL Address: 0x80047a70
 * PAL Size: 40b
 * EN Address: 0x80047864
 * EN Size: 40b
 * JP Address: 0x800473BC
 * JP Size: 40b
 */
void CGamePcs::calc1()
{
    Game.Calc2();
}

/*
 * --INFO--
 * PAL Address: 0x80047a98
 * PAL Size: 40b
 * EN Address: 0x8004788C
 * EN Size: 40b
 * JP Address: 0x800473E4
 * JP Size: 40b
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
 * EN Address: 0x800478DC
 * EN Size: 40b
 * JP Address: 0x80047434
 * JP Size: 40b
 */
void CGamePcs::destroy()
{
    Game.Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x80047b10
 * PAL Size: 40b
 * EN Address: 0x80047904
 * EN Size: 40b
 * JP Address: 0x8004745C
 * JP Size: 40b
 */
void CGamePcs::create()
{
    Game.Create();
}

/*
 * --INFO--
 * PAL Address: 0x80047b38
 * PAL Size: 20b
 * EN Address: 0x8004792C
 * EN Size: 20b
 * JP Address: 0x80047484
 * JP Size: 20b
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
