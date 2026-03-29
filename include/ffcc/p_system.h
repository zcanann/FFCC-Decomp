#ifndef _FFCC_P_SYSTEM_H_
#define _FFCC_P_SYSTEM_H_

#include "ffcc/system.h"

extern unsigned int m_table_desc0__10CSystemPcs[];
extern unsigned int m_table_desc1__10CSystemPcs[];
extern unsigned int m_table_desc2__10CSystemPcs[];
extern unsigned int m_table__10CSystemPcs[];

class CSystemPcs : public CProcess
{
public:
    CSystemPcs()
    {
        unsigned int* table = &m_table__10CSystemPcs[1];
        const unsigned int* desc0 = m_table_desc0__10CSystemPcs;
        const unsigned int* desc1 = m_table_desc1__10CSystemPcs;
        const unsigned int* desc2 = m_table_desc2__10CSystemPcs;

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
