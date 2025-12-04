#ifndef _FFCC_P_GAME_H_
#define _FFCC_P_GAME_H_

#include "ffcc/game.h"

class CGamePcs
{
public:
    CGamePcs();
	
    void Init();
    void Quit();
    void GetTable(unsigned long);

    void create();
    void destroy();

    void calcInit();
    void calc0();
    void calc1();
    void calc2();
    void draw0();
    void draw1();
    void draw2();

    virtual void onScriptChanging(char *);
    virtual void onScriptChanged(char *, int);
    virtual void onMapChanging(int, int);
    virtual void onMapChanged(int, int, int);

    char unknown[0x10];
    CGame game;
};

extern CGamePcs Game;

#endif // _FFCC_P_GAME_H_
