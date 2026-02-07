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

#endif
