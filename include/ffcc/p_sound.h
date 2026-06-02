#ifndef _FFCC_P_SOUND_H_
#define _FFCC_P_SOUND_H_

#include "ffcc/system.h"

class CSoundPcs;

extern "C" void create__9CSoundPcsFv(CSoundPcs*);
extern "C" void destroy__9CSoundPcsFv(CSoundPcs*);
extern "C" void calc__9CSoundPcsFv(CSoundPcs*);
extern "C" void draw__9CSoundPcsFv(CSoundPcs*);

class CSoundPcs : public CProcess
{
public:
    static CProcessTable m_table;

    CSoundPcs()
    {
        static CProcessTableCallback desc0 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CSoundPcsFv)};
        static CProcessTableCallback desc1 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CSoundPcsFv)};
        static CProcessTableCallback desc2 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CSoundPcsFv)};
        static CProcessTableCallback desc3 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CSoundPcsFv)};

        m_table.m_fields.m_create = desc0;
        m_table.m_fields.m_destroy = desc1;
        m_table.m_fields.m_entries[0].m_callback = desc2;
        m_table.m_fields.m_entries[1].m_callback = desc3;
    }

    void draw();
    void calc();
    void destroy();
    void createLoad();
    void create();

    int GetTable(unsigned long);
    void Quit();
    void Init();
};

extern CSoundPcs SoundPcs;

#endif
