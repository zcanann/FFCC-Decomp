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
