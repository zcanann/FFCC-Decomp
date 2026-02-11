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
    unsigned int* table = reinterpret_cast<unsigned int*>(lbl_801E9F2C);
    unsigned int* desc0 = lbl_801E9EC0;
    unsigned int* desc1 = lbl_801E9ECC;
    unsigned int* desc2 = lbl_801E9ED8;
    unsigned int* desc3 = lbl_801E9EE4;
    unsigned int* desc4 = lbl_801E9EF0;
    unsigned int* desc5 = lbl_801E9EFC;
    unsigned int* desc6 = lbl_801E9F08;
    unsigned int* desc7 = lbl_801E9F14;
    unsigned int* desc8 = lbl_801E9F20;

    GamePcs = reinterpret_cast<unsigned int>(lbl_801EA0A8);

    table[1] = desc0[0];
    table[2] = desc0[1];
    table[3] = desc0[2];
    table[4] = desc1[0];
    table[5] = desc1[1];
    table[6] = desc1[2];
    table[7] = desc2[0];
    table[8] = desc2[1];
    table[9] = desc2[2];
    table[10] = desc3[0];
    table[11] = desc3[1];
    table[12] = desc3[2];
    table[13] = desc4[0];
    table[14] = desc4[1];
    table[15] = desc4[2];
    table[16] = desc5[0];
    table[17] = desc5[1];
    table[18] = desc5[2];
    table[19] = desc6[0];
    table[20] = desc6[1];
    table[21] = desc6[2];
    table[22] = desc7[0];
    table[23] = desc7[1];
    table[24] = desc7[2];
    table[25] = desc8[0];
    table[26] = desc8[1];
    table[27] = desc8[2];
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
    Game.game.Create();
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
    Game.game.Destroy();
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
 * PAL Address: 0x80047a98
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGamePcs::calc0()
{
    Game.game.Calc();
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
    Game.game.Calc2();
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
    Game.game.Calc3();
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
    Game.game.Draw();
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
