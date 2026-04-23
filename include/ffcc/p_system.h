#ifndef _FFCC_P_SYSTEM_H_
#define _FFCC_P_SYSTEM_H_

#include "ffcc/system.h"

class CSystemPcs;

extern "C" void create__10CSystemPcsFv(CSystemPcs*);
extern "C" void destroy__10CSystemPcsFv(CSystemPcs*);
extern "C" void calc__10CSystemPcsFv(CSystemPcs*);
extern unsigned int m_table__10CSystemPcs[];

class CSystemPcs : public CProcess
{
public:
    CSystemPcs()
    {
        static unsigned int desc0[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__10CSystemPcsFv)};
        static unsigned int desc1[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__10CSystemPcsFv)};
        static unsigned int desc2[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__10CSystemPcsFv)};
        unsigned int* table = &m_table__10CSystemPcs[1];

        table[0] = desc0[0];
        table[1] = desc0[1];
        table[2] = desc0[2];
        table[3] = desc1[0];
        table[4] = desc1[1];
        table[5] = desc1[2];
        table[6] = desc2[0];
        table[7] = desc2[1];
        table[8] = desc2[2];
    }

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

extern CSystemPcs SystemPcs;

#endif
