#ifndef _FFCC_P_GAME_H_
#define _FFCC_P_GAME_H_

#include "ffcc/game.h"
#include "ffcc/system.h"

class CGamePcs;

extern "C" void create__8CGamePcsFv(CGamePcs*);
extern "C" void destroy__8CGamePcsFv(CGamePcs*);
extern "C" void calcInit__8CGamePcsFv(CGamePcs*);
extern "C" void calc0__8CGamePcsFv(CGamePcs*);
extern "C" void calc1__8CGamePcsFv(CGamePcs*);
extern "C" void calc2__8CGamePcsFv(CGamePcs*);
extern "C" void draw0__8CGamePcsFv(CGamePcs*);
extern "C" void draw1__8CGamePcsFv(CGamePcs*);
extern "C" void draw2__8CGamePcsFv(CGamePcs*);

extern unsigned int m_table__8CGamePcs[];

class CGamePcs : public CProcess
{
public:
#ifdef FFCC_DEFINE_CGAMEPCS_CTOR
    CGamePcs()
    {
        unsigned int* table = reinterpret_cast<unsigned int*>(m_table__8CGamePcs);
        static unsigned int desc0[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__8CGamePcsFv)};
        static unsigned int desc1[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__8CGamePcsFv)};
        static unsigned int desc2[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__8CGamePcsFv)};
        static unsigned int desc3[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc0__8CGamePcsFv)};
        static unsigned int desc4[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc1__8CGamePcsFv)};
        static unsigned int desc5[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw0__8CGamePcsFv)};
        static unsigned int desc6[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw1__8CGamePcsFv)};
        static unsigned int desc7[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw2__8CGamePcsFv)};
        static unsigned int desc8[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc2__8CGamePcsFv)};

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
#else
    CGamePcs();
#endif

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
