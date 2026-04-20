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
        m_table__8CGamePcs[1] = m_table_desc0__8CGamePcs[0];
        m_table__8CGamePcs[2] = m_table_desc0__8CGamePcs[1];
        m_table__8CGamePcs[3] = m_table_desc0__8CGamePcs[2];
        m_table__8CGamePcs[4] = m_table_desc1__8CGamePcs[0];
        m_table__8CGamePcs[5] = m_table_desc1__8CGamePcs[1];
        m_table__8CGamePcs[6] = m_table_desc1__8CGamePcs[2];
        m_table__8CGamePcs[7] = m_table_desc2__8CGamePcs[0];
        m_table__8CGamePcs[8] = m_table_desc2__8CGamePcs[1];
        m_table__8CGamePcs[9] = m_table_desc2__8CGamePcs[2];
        m_table__8CGamePcs[12] = m_table_desc3__8CGamePcs[0];
        m_table__8CGamePcs[13] = m_table_desc3__8CGamePcs[1];
        m_table__8CGamePcs[14] = m_table_desc3__8CGamePcs[2];
        m_table__8CGamePcs[17] = m_table_desc4__8CGamePcs[0];
        m_table__8CGamePcs[18] = m_table_desc4__8CGamePcs[1];
        m_table__8CGamePcs[19] = m_table_desc4__8CGamePcs[2];
        m_table__8CGamePcs[22] = m_table_desc5__8CGamePcs[0];
        m_table__8CGamePcs[23] = m_table_desc5__8CGamePcs[1];
        m_table__8CGamePcs[24] = m_table_desc5__8CGamePcs[2];
        m_table__8CGamePcs[27] = m_table_desc6__8CGamePcs[0];
        m_table__8CGamePcs[28] = m_table_desc6__8CGamePcs[1];
        m_table__8CGamePcs[29] = m_table_desc6__8CGamePcs[2];
        m_table__8CGamePcs[32] = m_table_desc7__8CGamePcs[0];
        m_table__8CGamePcs[33] = m_table_desc7__8CGamePcs[1];
        m_table__8CGamePcs[34] = m_table_desc7__8CGamePcs[2];
        m_table__8CGamePcs[37] = m_table_desc8__8CGamePcs[0];
        m_table__8CGamePcs[38] = m_table_desc8__8CGamePcs[1];
        m_table__8CGamePcs[39] = m_table_desc8__8CGamePcs[2];
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
