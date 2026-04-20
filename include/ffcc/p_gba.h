#ifndef _FFCC_P_GBA_H_
#define _FFCC_P_GBA_H_

#include "ffcc/system.h"
#include "ffcc/memory.h"

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

private:
    CMemory::CStage* m_stage;
};

struct CGbaPcsTable
{
    char* m_name;
    unsigned int m_words[0x56];
};

extern CGbaPcs GbaPcs;
extern unsigned int m_table_desc0__7CGbaPcs[];
extern unsigned int m_table_desc1__7CGbaPcs[];
extern unsigned int m_table_desc2__7CGbaPcs[];
extern unsigned int m_table_desc3__7CGbaPcs[];
extern CGbaPcsTable gGbaStatusWordTable;

#endif // _FFCC_P_GBA_H_
