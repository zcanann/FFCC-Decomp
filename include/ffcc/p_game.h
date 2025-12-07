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

    virtual void onScriptChanging(char*);
    virtual void onScriptChanged(char*, int);
    virtual void onMapChanging(int, int);
    virtual void onMapChanged(int, int, int);

    // void* vtable; // 0x00
    int unknown[3];  // 0x4-0xC
    CGame game;      // 0xC
};

CGamePcs Game;

#endif // _FFCC_P_GAME_H_
