#ifndef _FFCC_P_MC_H_
#define _FFCC_P_MC_H_

#include "ffcc/system.h"

class CMcPcs : public CProcess
{
public:
    void Init();
    void Quit();
    void* GetTable(unsigned long);

    void create();
    void destroy();

    void calc();
};

extern unsigned int m_table_desc0__6CMcPcs[];
extern unsigned int m_table_desc1__6CMcPcs[];
extern unsigned int m_table_desc2__6CMcPcs[];
extern unsigned char m_table__6CMcPcs[];
extern unsigned char sMcPcsSingletonData[];

#endif // _FFCC_P_MC_H_
