#ifndef _FFCC_P_MC_H_
#define _FFCC_P_MC_H_

#include "ffcc/system.h"

class CMcPcs;

extern "C" void create__6CMcPcsFv(CMcPcs*);
extern "C" void destroy__6CMcPcsFv(CMcPcs*);
extern "C" void calc__6CMcPcsFv(CMcPcs*);
extern unsigned int m_table__6CMcPcs[];

class CMcPcs : public CProcess
{
public:
    CMcPcs()
    {
        unsigned int* table = &m_table__6CMcPcs[1];

        table[0] = 0;
        table[1] = 0xFFFFFFFF;
        table[2] = reinterpret_cast<unsigned int>(create__6CMcPcsFv);
        table[3] = 0;
        table[4] = 0xFFFFFFFF;
        table[5] = reinterpret_cast<unsigned int>(destroy__6CMcPcsFv);
        table[6] = 0;
        table[7] = 0xFFFFFFFF;
        table[8] = reinterpret_cast<unsigned int>(calc__6CMcPcsFv);
    }

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
