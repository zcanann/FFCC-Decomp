#ifndef _FFCC_P_SOUND_H_
#define _FFCC_P_SOUND_H_

#include "ffcc/system.h"

class CSoundPcs;

extern "C" void create__9CSoundPcsFv(CSoundPcs*);
extern "C" void destroy__9CSoundPcsFv(CSoundPcs*);
extern "C" void calc__9CSoundPcsFv(CSoundPcs*);
extern "C" void draw__9CSoundPcsFv(CSoundPcs*);
extern unsigned int m_table__9CSoundPcs[];

class CSoundPcs : public CProcess
{
public:
    CSoundPcs()
    {
        static unsigned int desc0[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CSoundPcsFv)};
        static unsigned int desc1[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CSoundPcsFv)};
        static unsigned int desc2[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CSoundPcsFv)};
        static unsigned int desc3[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CSoundPcsFv)};
        unsigned int* table = &m_table__9CSoundPcs[1];

        table[0] = desc0[0];
        table[1] = desc0[1];
        table[2] = desc0[2];
        table[3] = desc1[0];
        table[4] = desc1[1];
        table[5] = desc1[2];
        table[6] = desc2[0];
        table[7] = desc2[1];
        table[8] = desc2[2];
        table[11] = desc3[0];
        table[12] = desc3[1];
        table[13] = desc3[2];
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
