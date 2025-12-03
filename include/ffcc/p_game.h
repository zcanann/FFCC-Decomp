#ifndef _FFCC_P_GAME_H_
#define _FFCC_P_GAME_H_

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
};

#endif // _FFCC_P_GAME_H_
