#include "ffcc/p_game.h"

extern unsigned int PTR_PTR_s_CGamePcs_801ea0a8[];
CGamePcs Game;

/*
 * --INFO--
 * PAL Address: 80047b54
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_game_cpp() {
    unsigned int* srcA = m_table_desc0__8CGamePcs;
    unsigned int* srcB = m_table_desc1__8CGamePcs;
    unsigned int* srcC = m_table_desc2__8CGamePcs;
    unsigned int* srcD = m_table_desc3__8CGamePcs;
    unsigned int* srcE = m_table_desc4__8CGamePcs;
    unsigned int* srcF = m_table_desc5__8CGamePcs;
    unsigned int* srcG = m_table_desc6__8CGamePcs;
    unsigned int* srcH = m_table_desc7__8CGamePcs;
    unsigned int* srcI = m_table_desc8__8CGamePcs;
    unsigned int* dst = reinterpret_cast<unsigned int*>(m_table__8CGamePcs);

    *reinterpret_cast<void**>(&Game) = PTR_PTR_s_CGamePcs_801ea0a8;

    dst[1] = srcA[0];
    dst[2] = srcA[1];
    dst[3] = srcA[2];
    dst[4] = srcB[0];
    dst[5] = srcB[1];
    dst[6] = srcB[2];
    dst[7] = srcC[0];
    dst[8] = srcC[1];
    dst[9] = srcC[2];
    dst[12] = srcD[0];
    dst[13] = srcD[1];
    dst[14] = srcD[2];
    dst[17] = srcE[0];
    dst[18] = srcE[1];
    dst[19] = srcE[2];
    dst[22] = srcF[0];
    dst[23] = srcF[1];
    dst[24] = srcF[2];
    dst[27] = srcG[0];
    dst[28] = srcG[1];
    dst[29] = srcG[2];
    dst[32] = srcH[0];
    dst[33] = srcH[1];
    dst[34] = srcH[2];
    dst[37] = srcI[0];
    dst[38] = srcI[1];
    dst[39] = srcI[2];
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
    return (int)(m_table__8CGamePcs + param * 0x15c);
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
