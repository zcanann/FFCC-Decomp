#ifndef _FFCC_P_SOUND_H_
#define _FFCC_P_SOUND_H_

#include "ffcc/system.h"

class CSoundPcs : public CProcess
{
public:
    static CProcessCallbackTable m_table;

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
