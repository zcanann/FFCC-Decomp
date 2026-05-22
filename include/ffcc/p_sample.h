#ifndef _FFCC_P_SAMPLE_H_
#define _FFCC_P_SAMPLE_H_

#include "ffcc/system.h"

struct CSamplePcsTable
{
    char* m_name;
    unsigned int m_words[0x56];
};

class CSamplePcs : public CProcess
{
public:
    static CSamplePcsTable m_table;

    CSamplePcs();
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void func0();
    void func1();
};

extern CSamplePcs SamplePcs;

#endif
