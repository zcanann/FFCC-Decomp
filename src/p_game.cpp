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
    unsigned int* dst;

    GamePcs = reinterpret_cast<unsigned int>(lbl_801EA0A8);
    dst = reinterpret_cast<unsigned int*>(lbl_801E9F2C);

    dst[1] = lbl_801E9EC0[0];
    dst[2] = lbl_801E9EC0[1];
    dst[3] = lbl_801E9EC0[2];
    dst[4] = lbl_801E9ECC[0];
    dst[5] = lbl_801E9ECC[1];
    dst[6] = lbl_801E9ECC[2];
    dst[7] = lbl_801E9ED8[0];
    dst[8] = lbl_801E9ED8[1];
    dst[9] = lbl_801E9ED8[2];
    dst[12] = lbl_801E9EE4[0];
    dst[13] = lbl_801E9EE4[1];
    dst[14] = lbl_801E9EE4[2];
    dst[17] = lbl_801E9EF0[0];
    dst[18] = lbl_801E9EF0[1];
    dst[19] = lbl_801E9EF0[2];
    dst[22] = lbl_801E9EFC[0];
    dst[23] = lbl_801E9EFC[1];
    dst[24] = lbl_801E9EFC[2];
    dst[27] = lbl_801E9F08[0];
    dst[28] = lbl_801E9F08[1];
    dst[29] = lbl_801E9F08[2];
    dst[32] = lbl_801E9F14[0];
    dst[33] = lbl_801E9F14[1];
    dst[34] = lbl_801E9F14[2];
    dst[37] = lbl_801E9F20[0];
    dst[38] = lbl_801E9F20[1];
    dst[39] = lbl_801E9F20[2];
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
    CGame& game = (CGame&)Game;
    game.CGame::Create();
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
    CGame& game = (CGame&)Game;
    game.CGame::Destroy();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGamePcs::calcInit()
{
    CGame& game = (CGame&)Game;
    game.CGame::CheckScriptChange();
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
    CGame& game = (CGame&)Game;
    game.CGame::Calc();
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
    CGame& game = (CGame&)Game;
    game.CGame::Calc2();
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
    CGame& game = (CGame&)Game;
    game.CGame::Calc3();
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
    CGame& game = (CGame&)Game;
    game.CGame::Draw();
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
    CGame& game = (CGame&)Game;
    game.CGame::Draw2();
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
    CGame& game = (CGame&)Game;
    game.CGame::Draw3();
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
    CGame& game = (CGame&)Game;
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
    CGame& game = (CGame&)Game;
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
    CGame& game = (CGame&)Game;
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
    CGame& game = (CGame&)Game;
    game.CGame::MapChanged(a, b, c);
}
