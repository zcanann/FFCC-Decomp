#ifndef _FFCC_P_MC_H_
#define _FFCC_P_MC_H_

#include "ffcc/system.h"

extern unsigned int initData__6CMcPcs[];
extern unsigned int m_table__6CMcPcs[];
extern void* __vt__6CMcPcs[];

class CMcPcs : public CProcess
{
public:
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

extern void* McPcs;

static inline CMcPcs* GetMcPcsSingleton()
{
    return reinterpret_cast<CMcPcs*>(&McPcs);
}

#endif // _FFCC_P_MC_H_
