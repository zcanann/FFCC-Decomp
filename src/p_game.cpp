#include "ffcc/p_game.h"

extern unsigned int PTR_PTR_s_CGamePcs_801ea0a8[];
void* GamePcs;
CGamePcs Game;
extern "C" void create__8CGamePcsFv(CGamePcs*);
extern "C" void destroy__8CGamePcsFv(CGamePcs*);
extern "C" void calcInit__8CGamePcsFv(CGamePcs*);
extern "C" void calc0__8CGamePcsFv(CGamePcs*);
extern "C" void calc1__8CGamePcsFv(CGamePcs*);
extern "C" void calc2__8CGamePcsFv(CGamePcs*);
extern "C" void draw0__8CGamePcsFv(CGamePcs*);
extern "C" void draw1__8CGamePcsFv(CGamePcs*);
extern "C" void draw2__8CGamePcsFv(CGamePcs*);
char s_CGamePcs_801D7C20[] = "CGamePcs";

unsigned int m_table_desc0__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__8CGamePcsFv)};
unsigned int m_table_desc1__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__8CGamePcsFv)};
unsigned int m_table_desc2__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__8CGamePcsFv)};
unsigned int m_table_desc3__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc0__8CGamePcsFv)};
unsigned int m_table_desc4__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc1__8CGamePcsFv)};
unsigned int m_table_desc5__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc2__8CGamePcsFv)};
unsigned int m_table_desc6__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw0__8CGamePcsFv)};
unsigned int m_table_desc7__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw1__8CGamePcsFv)};
unsigned int m_table_desc8__8CGamePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw2__8CGamePcsFv)};
unsigned int m_table__8CGamePcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(s_CGamePcs_801D7C20), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x13, 0, 0, 0, 0, 0x17, 0, 0, 0, 0, 0x19, 0, 0, 0, 0,
    0x3A, 1, 0, 0, 0, 0x3C, 1, 0, 0, 0, 0x47, 1, 0, 0, 0, 0x4C
};

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
    unsigned int* desc0 = m_table_desc0__8CGamePcs;
    unsigned int* desc1 = desc0 + 3;
    unsigned int* desc2 = desc1 + 3;
    unsigned int* desc3 = desc2 + 3;
    unsigned int* desc4 = desc3 + 3;
    unsigned int* desc5 = desc4 + 3;
    unsigned int* desc6 = desc5 + 3;
    unsigned int* desc7 = desc6 + 3;
    unsigned int* desc8 = desc7 + 3;
    unsigned int* table = desc0 + 30;

    GamePcs = PTR_PTR_s_CGamePcs_801ea0a8;

    table[1] = desc0[0];
    table[2] = desc0[1];
    table[3] = desc0[2];
    table[4] = desc1[0];
    table[5] = desc1[1];
    table[6] = desc1[2];
    table[7] = desc2[0];
    table[8] = desc2[1];
    table[9] = desc2[2];
    table[12] = desc3[0];
    table[13] = desc3[1];
    table[14] = desc3[2];
    table[17] = desc4[0];
    table[18] = desc4[1];
    table[19] = desc4[2];
    table[22] = desc5[0];
    table[23] = desc5[1];
    table[24] = desc5[2];
    table[27] = desc6[0];
    table[28] = desc6[1];
    table[29] = desc6[2];
    table[32] = desc7[0];
    table[33] = desc7[1];
    table[34] = desc7[2];
    table[37] = desc8[0];
    table[38] = desc8[1];
    table[39] = desc8[2];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGamePcs::CGamePcs() : CProcess(), game() {}

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
    return reinterpret_cast<int>(reinterpret_cast<unsigned char*>(m_table__8CGamePcs) + param * 0x15c);
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
