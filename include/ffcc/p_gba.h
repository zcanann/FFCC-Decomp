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

    CMemory::CStage* m_stage;

    static CProcessTable m_table;
};

extern "C" void create__7CGbaPcsFv(CGbaPcs*);
extern "C" void destroy__7CGbaPcsFv(CGbaPcs*);
extern "C" void calc__7CGbaPcsFv(CGbaPcs*);
extern "C" void draw__7CGbaPcsFv(CGbaPcs*);

extern CGbaPcs GbaPcs;

#endif // _FFCC_P_GBA_H_
