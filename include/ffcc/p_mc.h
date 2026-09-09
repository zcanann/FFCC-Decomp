#ifndef _FFCC_P_MC_H_
#define _FFCC_P_MC_H_

#include "ffcc/system.h"

class CMcPcs : public CProcess
{
public:
    static CProcessCallbackTable m_table;

    CMcPcs();

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

extern CMcPcs McPcs;

static inline CMcPcs* GetMcPcsSingleton()
{
    return &McPcs;
}

#endif // _FFCC_P_MC_H_
