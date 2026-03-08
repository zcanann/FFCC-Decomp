#include "ffcc/p_game.h"

extern unsigned int PTR_PTR_s_CGamePcs_801ea0a8[];
extern void* GamePcs;
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
extern "C" char s_CGamePcs_801D7C20[];

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
    unsigned int* dst = reinterpret_cast<unsigned int*>(m_table__8CGamePcs);

    GamePcs = PTR_PTR_s_CGamePcs_801ea0a8;

    dst[1] = m_table_desc0__8CGamePcs[0];
    dst[2] = m_table_desc0__8CGamePcs[1];
    dst[3] = m_table_desc0__8CGamePcs[2];
    dst[4] = m_table_desc1__8CGamePcs[0];
    dst[5] = m_table_desc1__8CGamePcs[1];
    dst[6] = m_table_desc1__8CGamePcs[2];
    dst[7] = m_table_desc2__8CGamePcs[0];
    dst[8] = m_table_desc2__8CGamePcs[1];
    dst[9] = m_table_desc2__8CGamePcs[2];
    dst[12] = m_table_desc3__8CGamePcs[0];
    dst[13] = m_table_desc3__8CGamePcs[1];
    dst[14] = m_table_desc3__8CGamePcs[2];
    dst[17] = m_table_desc4__8CGamePcs[0];
    dst[18] = m_table_desc4__8CGamePcs[1];
    dst[19] = m_table_desc4__8CGamePcs[2];
    dst[22] = m_table_desc5__8CGamePcs[0];
    dst[23] = m_table_desc5__8CGamePcs[1];
    dst[24] = m_table_desc5__8CGamePcs[2];
    dst[27] = m_table_desc6__8CGamePcs[0];
    dst[28] = m_table_desc6__8CGamePcs[1];
    dst[29] = m_table_desc6__8CGamePcs[2];
    dst[32] = m_table_desc7__8CGamePcs[0];
    dst[33] = m_table_desc7__8CGamePcs[1];
    dst[34] = m_table_desc7__8CGamePcs[2];
    dst[37] = m_table_desc8__8CGamePcs[0];
    dst[38] = m_table_desc8__8CGamePcs[1];
    dst[39] = m_table_desc8__8CGamePcs[2];
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
