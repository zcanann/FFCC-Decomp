#ifndef _FFCC_P_SOUND_H_
#define _FFCC_P_SOUND_H_

#include "ffcc/system.h"

extern unsigned int m_table_desc0__9CSoundPcs[];
extern unsigned int m_table_desc1__9CSoundPcs[];
extern unsigned int m_table_desc2__9CSoundPcs[];
extern unsigned int m_table_desc3__9CSoundPcs[];
extern unsigned int m_table__9CSoundPcs[];

class CSoundPcs : public CProcess
{
public:
    CSoundPcs()
    {
        unsigned int* table = &m_table__9CSoundPcs[1];

        table[0] = m_table_desc0__9CSoundPcs[0];
        table[1] = m_table_desc0__9CSoundPcs[1];
        table[2] = m_table_desc0__9CSoundPcs[2];
        table[3] = m_table_desc1__9CSoundPcs[0];
        table[4] = m_table_desc1__9CSoundPcs[1];
        table[5] = m_table_desc1__9CSoundPcs[2];
        table[6] = m_table_desc2__9CSoundPcs[0];
        table[7] = m_table_desc2__9CSoundPcs[1];
        table[8] = m_table_desc2__9CSoundPcs[2];
        table[11] = m_table_desc3__9CSoundPcs[0];
        table[12] = m_table_desc3__9CSoundPcs[1];
        table[13] = m_table_desc3__9CSoundPcs[2];
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
