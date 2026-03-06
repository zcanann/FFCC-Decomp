#ifndef _FFCC_P_SAMPLE_H_
#define _FFCC_P_SAMPLE_H_

#include "ffcc/system.h"

class CSamplePcs : public CProcess
{
public:
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void func0();
    void func1();
};

extern CSamplePcs SamplePcs;
extern unsigned int m_table_desc0__10CSamplePcs[];
extern unsigned int m_table_desc1__10CSamplePcs[];
extern unsigned int m_table_desc2__10CSamplePcs[];
extern unsigned int m_table_desc3__10CSamplePcs[];
extern unsigned char m_table__10CSamplePcs[];

#endif
