#ifndef _FFCC_P_MC_H_
#define _FFCC_P_MC_H_

#include "ffcc/system.h"

class CMcPcs : public CProcess
{
public:
    CMcPcs();
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

extern unsigned int m_table__6CMcPcs[];
extern CMcPcs McPcs;

static inline CMcPcs* GetMcPcsSingleton()
{
    return &McPcs;
}

#endif // _FFCC_P_MC_H_
