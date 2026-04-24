#ifndef _FFCC_P_SOUND_H_
#define _FFCC_P_SOUND_H_

#include "ffcc/system.h"

class CSoundPcs;

extern "C" void create__9CSoundPcsFv(CSoundPcs*);
extern "C" void destroy__9CSoundPcsFv(CSoundPcs*);
extern "C" void calc__9CSoundPcsFv(CSoundPcs*);
extern "C" void draw__9CSoundPcsFv(CSoundPcs*);
extern unsigned int m_table__9CSoundPcs[];
extern unsigned int m_table_desc0__9CSoundPcs[];
extern unsigned int m_table_desc1__9CSoundPcs[];
extern unsigned int m_table_desc2__9CSoundPcs[];
extern unsigned int m_table_desc3__9CSoundPcs[];

class CSoundPcs : public CProcess
{
public:
    CSoundPcs();

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
