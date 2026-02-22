#ifndef _FFCC_P_TINA_H_
#define _FFCC_P_TINA_H_

#include "ffcc/memory.h"
#include "ffcc/system.h"

struct Vec;
struct pppIVECTOR3;
struct pppFVECTOR4;

void loadPdtPtx(char*, void*, int, void*, int, int);
void LoadFieldPdt0(int, int);
void pppNotAllocAmemCacheRmem(unsigned long);
unsigned int pppFreeMngStPrioForData();
void pppAmemDeletePmng(unsigned long);
void pppAmemRefCntError(unsigned long);

class CPartPcs : public CProcess
{
public:
    CPartPcs();
    ~CPartPcs();

    void Init();
    void Quit();

    void onScriptChanging(char*);
    void GetTable(unsigned long);

    void create0();
    void create();
    void createLoad();
    void createViewer();
    void destroy();

    void ChangeDataStage(CMemory::CStage*);
    void ResetDataStage();

    void calcInit();
    void calc();
    void calcViewer();
    void calcDead();

    void ClearOt();

    void drawShadow();
    void drawCharaBefore();
    void draw();
    void drawShadowViewer();
    void drawViewer();
    void drawAfter();
    void drawAfterViewer();

    void DrawMenu(int);
    void DrawShoki();
    void DrawMenuIdx(int);

    void SetParLocIdx(int, Vec&);
    void GetParLocIdx(int, Vec&);

    void SetParColIdx(int, pppFVECTOR4&);
    void GetParColIdx(int, pppFVECTOR4&);

    unsigned int IsLoadPartCompleted();

    void LoadFieldPdt(int, int, void*, unsigned long, unsigned char);
    void LoadMonsterPdt(int, int, void*, int, void*, int);
    int LoadMenuPdt(char*);
    void ReleasePdt(int);

    void StartLocationTitle();
    void EndLocationTitle();

    void StartMiruraEvent();
    void EndMiruraEvent();

    void pppSetDebugHide(unsigned char);
    void SetUSBData();
};

#endif
