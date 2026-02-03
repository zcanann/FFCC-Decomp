#include "ffcc/p_game.h"

extern "C" void __sinit_p_game_cpp();

/*
 * --INFO--
 * PAL Address: 80047b54
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __sinit_p_game_cpp() {
    // Static initialization for p_game module
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGamePcs::CGamePcs()
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
void CGamePcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::calcInit()
{
	Game.game.CheckScriptChange();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::calc0()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::calc1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::calc2()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::draw0()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::draw1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::draw2()
{
	// TODO
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
	Game.game.ScriptChanging(script);
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
	Game.game.ScriptChanged(script, param);
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
	Game.game.MapChanging(a, b);
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
	Game.game.MapChanged(a, b, c);
}
