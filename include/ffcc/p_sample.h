#ifndef _FFCC_P_SAMPLE_H_
#define _FFCC_P_SAMPLE_H_

#include "ffcc/system.h"

class CSamplePcs : public CProcess
{
public:
    static CProcessTable m_table;

    CSamplePcs();
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void func0();
    void func1();
};

extern "C" void create__10CSamplePcsFv(CSamplePcs*);
extern "C" void destroy__10CSamplePcsFv(CSamplePcs*);
extern "C" void func0__10CSamplePcsFv(CSamplePcs*);
extern "C" void func1__10CSamplePcsFv(CSamplePcs*);

extern CSamplePcs SamplePcs;

#endif
