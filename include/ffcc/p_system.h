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

#endif
