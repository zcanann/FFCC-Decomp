#ifndef _FFCC_P_SYSTEM_H_
#define _FFCC_P_SYSTEM_H_

#include "ffcc/system.h"

class CSystemPcs;

extern "C" void create__10CSystemPcsFv(CSystemPcs*);
extern "C" void destroy__10CSystemPcsFv(CSystemPcs*);
extern "C" void calc__10CSystemPcsFv(CSystemPcs*);

class CSystemPcs : public CProcess
{
public:
    static CProcessTable m_table;

    CSystemPcs()
    {
        static CProcessTableCallback desc0 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__10CSystemPcsFv)};
        static CProcessTableCallback desc1 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__10CSystemPcsFv)};
        static CProcessTableCallback desc2 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__10CSystemPcsFv)};

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

extern CSystemPcs SystemPcs;

#endif
