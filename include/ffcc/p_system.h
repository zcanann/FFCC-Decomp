#ifndef _FFCC_P_SYSTEM_H_
#define _FFCC_P_SYSTEM_H_

#include "ffcc/system.h"

class CSystemPcs : public CProcess
{
public:
    CSystemPcs();

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

extern CSystemPcs SystemPcs;
extern unsigned int m_table_desc0__10CSystemPcs[];
extern unsigned int m_table_desc1__10CSystemPcs[];
extern unsigned int m_table_desc2__10CSystemPcs[];
extern unsigned char m_table__10CSystemPcs[];

#endif
