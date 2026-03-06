#ifndef _FFCC_P_SOUND_H_
#define _FFCC_P_SOUND_H_

#include "ffcc/system.h"

class CSoundPcs : public CProcess
{
public:
    CSoundPcs();

    void Init();
    void Quit();
    void* GetTable(unsigned long);

    void create();
    void createLoad();
    void destroy();

    void calc();
    void draw();
};

extern CSoundPcs SoundPcs;
extern unsigned int m_table_desc0__9CSoundPcs[];
extern unsigned int m_table_desc1__9CSoundPcs[];
extern unsigned int m_table_desc2__9CSoundPcs[];
extern unsigned int m_table_desc3__9CSoundPcs[];
extern unsigned char m_table__9CSoundPcs[];

#endif
