#ifndef _FFCC_P_SOUND_H_
#define _FFCC_P_SOUND_H_

#include "ffcc/system.h"

extern unsigned int m_table__9CSoundPcs[];

class CSoundPcs : public CProcess
{
public:
    CSoundPcs() {}

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
