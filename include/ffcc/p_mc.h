#ifndef _FFCC_P_MC_H_
#define _FFCC_P_MC_H_

class CMcPcs
{
public:
    CMcPcs();

    void Init();
    void Quit();
    void GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

#endif // _FFCC_P_MC_H_
