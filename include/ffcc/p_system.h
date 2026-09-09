#ifndef _FFCC_P_SYSTEM_H_
#define _FFCC_P_SYSTEM_H_

#include "ffcc/system.h"

class CSystemPcs : public CProcess
{
public:
    static CProcessCallbackTable m_table;

    CSystemPcs();

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

extern CSystemPcs SystemPcs;

#endif
