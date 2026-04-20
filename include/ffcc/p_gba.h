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
extern unsigned int gGbaStatusWordTriplet0[];
extern unsigned int gGbaStatusWordTriplet1[];
extern unsigned int gGbaStatusWordTriplet2[];
extern unsigned int gGbaStatusWordTriplet3[];
extern CGbaPcsTable gGbaStatusWordTable;

#endif // _FFCC_P_GBA_H_
