#ifndef _FFCC_P_SYSTEM_H_
#define _FFCC_P_SYSTEM_H_

class CSystemPcs
{
public:
    CSystemPcs();

    void Init();
    void Quit();
    void GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

#endif
