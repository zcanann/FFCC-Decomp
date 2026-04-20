#ifndef _FFCC_P_GBA_H_
#define _FFCC_P_GBA_H_

#include "ffcc/system.h"
#include "ffcc/memory.h"

extern unsigned int gGbaStatusWordTriplet0[];
extern unsigned int gGbaStatusWordTriplet1[];
extern unsigned int gGbaStatusWordTriplet2[];
extern unsigned int gGbaStatusWordTriplet3[];
extern unsigned int gGbaStatusWordTable[];

class CGbaPcs : public CProcess
{
public:
    CGbaPcs()
    {
        unsigned int* table = &gGbaStatusWordTable[1];
        table[0] = gGbaStatusWordTriplet0[0];
        table[1] = gGbaStatusWordTriplet0[1];
        table[2] = gGbaStatusWordTriplet0[2];
        table[3] = gGbaStatusWordTriplet1[0];
        table[4] = gGbaStatusWordTriplet1[1];
        table[5] = gGbaStatusWordTriplet1[2];
        table[6] = gGbaStatusWordTriplet2[0];
        table[7] = gGbaStatusWordTriplet2[1];
        table[8] = gGbaStatusWordTriplet2[2];
        table[11] = gGbaStatusWordTriplet3[0];
        table[12] = gGbaStatusWordTriplet3[1];
        table[13] = gGbaStatusWordTriplet3[2];
    }
	
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

extern CGbaPcs GbaPcs;

#endif // _FFCC_P_GBA_H_
