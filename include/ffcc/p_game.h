#ifndef _FFCC_P_GAME_H_
#define _FFCC_P_GAME_H_

#include "ffcc/game.h"
#include "ffcc/system.h"

extern unsigned int m_table_desc0__8CGamePcs[];
extern unsigned int m_table_desc1__8CGamePcs[];
extern unsigned int m_table_desc2__8CGamePcs[];
extern unsigned int m_table_desc3__8CGamePcs[];
extern unsigned int m_table_desc4__8CGamePcs[];
extern unsigned int m_table_desc5__8CGamePcs[];
extern unsigned int m_table_desc6__8CGamePcs[];
extern unsigned int m_table_desc7__8CGamePcs[];
extern unsigned int m_table_desc8__8CGamePcs[];
extern unsigned int m_table__8CGamePcs[];

class CGamePcs : public CProcess
{
public:
    CGamePcs()
    {
        unsigned int* dst = reinterpret_cast<unsigned int*>(m_table__8CGamePcs);

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

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void calcInit();
    void calc0();
    void calc1();
    void calc2();
    void draw0();
    void draw1();
    void draw2();

    virtual void onScriptChanging(char*);
    virtual void onScriptChanged(char*, int);
    virtual void onMapChanging(int, int);
    virtual void onMapChanged(int, int, int);
};

extern CGame Game;
extern CGamePcs GamePcs;

#endif // _FFCC_P_GAME_H_
