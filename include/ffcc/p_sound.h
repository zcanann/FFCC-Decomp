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
        unsigned int* table = m_table__9CSoundPcs;
        const unsigned int* desc0 = m_table_desc0__9CSoundPcs;
        const unsigned int* desc1 = m_table_desc1__9CSoundPcs;
        const unsigned int* desc2 = m_table_desc2__9CSoundPcs;
        const unsigned int* desc3 = m_table_desc3__9CSoundPcs;

        table[1] = desc0[0];
        table[2] = desc0[1];
        table[3] = desc0[2];
        table[4] = desc1[0];
        table[5] = desc1[1];
        table[6] = desc1[2];
        table[7] = desc2[0];
        table[8] = desc2[1];
        table[9] = desc2[2];
        table[12] = desc3[0];
        table[13] = desc3[1];
        table[14] = desc3[2];
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
