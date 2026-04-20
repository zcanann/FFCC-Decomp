#ifndef _FFCC_P_MC_H_
#define _FFCC_P_MC_H_

#include "ffcc/system.h"

class CMcPcs : public CProcess
{
public:
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

extern unsigned int m_table__6CMcPcs[];
extern unsigned char sMcPcsSingletonData[];
extern unsigned char* gMcPcsSingletonPtr;

static inline CMcPcs* GetMcPcsSingleton()
{
    if (gMcPcsSingletonPtr != 0)
    {
        return reinterpret_cast<CMcPcs*>(gMcPcsSingletonPtr);
    }

    return reinterpret_cast<CMcPcs*>(sMcPcsSingletonData);
}

#endif // _FFCC_P_MC_H_
