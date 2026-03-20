#ifndef _FFCC_P_GAME_H_
#define _FFCC_P_GAME_H_

#include "ffcc/game.h"
#include "ffcc/system.h"

class CGamePcs : public CProcess
{
public:
    CGamePcs();
	
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

#endif // _FFCC_P_GAME_H_
