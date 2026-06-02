#ifndef _FFCC_P_MC_H_
#define _FFCC_P_MC_H_

#include "ffcc/system.h"

class CMcPcs;

extern "C" void create__6CMcPcsFv(CMcPcs*);
extern "C" void destroy__6CMcPcsFv(CMcPcs*);
extern "C" void calc__6CMcPcsFv(CMcPcs*);

class CMcPcs : public CProcess
{
public:
    static CProcessTable m_table;

    CMcPcs()
    {
        static CProcessTableCallback desc0 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__6CMcPcsFv)};
        static CProcessTableCallback desc1 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__6CMcPcsFv)};
        static CProcessTableCallback desc2 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__6CMcPcsFv)};

        m_table.m_fields.m_create = desc0;
        m_table.m_fields.m_destroy = desc1;
        m_table.m_fields.m_entries[0].m_callback = desc2;
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
