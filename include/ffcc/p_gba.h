#ifndef _FFCC_P_GBA_H_
#define _FFCC_P_GBA_H_

#include "ffcc/system.h"
#include "ffcc/memory.h"

struct CGbaPcsTable
{
    char* m_name;
    unsigned int m_words[0x56];
};

class CGbaPcs : public CProcess
{
public:
    CGbaPcs();
	
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void SetFirstZone();

    void create();
    void destroy();
    void calc();
    void draw();

    virtual void onMapChanging(int, int);
    virtual void onMapChanged(int, int, int);
    virtual void onScriptChanging(char*);

    CMemory::CStage* m_stage;

    static CGbaPcsTable m_table;
};

extern CGbaPcs GbaPcs;

#endif // _FFCC_P_GBA_H_
