#include "ffcc/p_game.h"

extern "C" void __sinit_p_game_cpp();
extern unsigned int lbl_801E9EC0[];
extern unsigned int lbl_801E9ECC[];
extern unsigned int lbl_801E9ED8[];
extern unsigned int lbl_801E9EE4[];
extern unsigned int lbl_801E9EF0[];
extern unsigned int lbl_801E9EFC[];
extern unsigned int lbl_801E9F08[];
extern unsigned int lbl_801E9F14[];
extern unsigned int lbl_801E9F20[];
extern unsigned int lbl_801EA0A8[];
extern unsigned int GamePcs;
extern "C" char lbl_801E9F2C[];

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
    GamePcs = reinterpret_cast<unsigned int>(lbl_801EA0A8);

    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[1] = lbl_801E9EC0[0];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[2] = lbl_801E9EC0[1];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[3] = lbl_801E9EC0[2];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[4] = lbl_801E9ECC[0];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[5] = lbl_801E9ECC[1];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[6] = lbl_801E9ECC[2];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[7] = lbl_801E9ED8[0];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[8] = lbl_801E9ED8[1];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[9] = lbl_801E9ED8[2];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[10] = lbl_801E9EE4[0];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[11] = lbl_801E9EE4[1];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[12] = lbl_801E9EE4[2];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[13] = lbl_801E9EF0[0];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[14] = lbl_801E9EF0[1];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[15] = lbl_801E9EF0[2];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[16] = lbl_801E9EFC[0];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[17] = lbl_801E9EFC[1];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[18] = lbl_801E9EFC[2];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[19] = lbl_801E9F08[0];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[20] = lbl_801E9F08[1];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[21] = lbl_801E9F08[2];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[22] = lbl_801E9F14[0];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[23] = lbl_801E9F14[1];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[24] = lbl_801E9F14[2];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[25] = lbl_801E9F20[0];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[26] = lbl_801E9F20[1];
    reinterpret_cast<unsigned int*>(lbl_801E9F2C)[27] = lbl_801E9F20[2];
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
 * PAL Address: 0x80047b38
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGamePcs::GetTable(unsigned long param)
{
    return (int)(lbl_801E9F2C + param * 0x15c);
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
    game.Create();
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
    game.Destroy();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::calcInit()
{
	game.CheckScriptChange();
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
    game.Calc();
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
    game.Calc2();
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
    game.Calc3();
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
    game.Draw();
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
    game.Draw2();
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
    game.Draw3();
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
    CGame& game = Game.game;
    game.CGame::ScriptChanging(script);
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
    CGame& game = Game.game;
    game.CGame::ScriptChanged(script, param);
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
    CGame& game = Game.game;
    game.CGame::MapChanging(a, b);
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
    CGame& game = Game.game;
    game.CGame::MapChanged(a, b, c);
}
