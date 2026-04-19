#ifndef _FFCC_P_SAMPLE_H_
#define _FFCC_P_SAMPLE_H_

#include "ffcc/system.h"

class CSamplePcs : public CProcess
{
public:
    CSamplePcs();
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void func0();
    void func1();
};

struct CSamplePcsTable
{
    char* m_name;
    unsigned int m_words[0x56];
};

extern CSamplePcs SamplePcs;
extern unsigned int m_table_desc0__10CSamplePcs[];
extern unsigned int m_table_desc1__10CSamplePcs[];
extern unsigned int m_table_desc2__10CSamplePcs[];
extern unsigned int m_table_desc3__10CSamplePcs[];
extern CSamplePcsTable m_table__10CSamplePcs;

#endif
