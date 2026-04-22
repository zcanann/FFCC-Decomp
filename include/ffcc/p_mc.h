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
        static unsigned int desc0[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__6CMcPcsFv)};
        static unsigned int desc1[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__6CMcPcsFv)};
        static unsigned int desc2[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__6CMcPcsFv)};
        unsigned int* table = &m_table__6CMcPcs[1];

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

extern CMcPcs McPcs;

static inline CMcPcs* GetMcPcsSingleton()
{
    return &McPcs;
}

#endif // _FFCC_P_MC_H_
