#ifndef _FFCC_P_TINA_H_
#define _FFCC_P_TINA_H_

#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/USBStreamData.h"

struct Vec;
struct pppIVECTOR3;
struct pppFVECTOR4;

void loadPdtPtx(char*, void*, int, void*, int, int);
void LoadFieldPdt0(int, int);
unsigned int pppNotAllocAmemCacheRmem(unsigned long);
unsigned int pppFreeMngStPrioForData();
unsigned char pppAmemDeletePmng(unsigned long);
unsigned int pppAmemRefCntError(unsigned long);

extern unsigned int m_table_desc0__8CPartPcs[];
extern unsigned int m_table_desc1__8CPartPcs[];
extern unsigned int m_table_desc2__8CPartPcs[];
extern unsigned int m_table_desc3__8CPartPcs[];
extern unsigned int m_table_desc4__8CPartPcs[];
extern unsigned int m_table_desc5__8CPartPcs[];
extern unsigned int m_table_desc6__8CPartPcs[];
extern unsigned int m_table_desc7__8CPartPcs[];
extern unsigned int m_table_desc8__8CPartPcs[];
extern unsigned int m_table_desc9__8CPartPcs[];
extern unsigned int m_table_desc10__8CPartPcs[];
extern unsigned int m_table_desc11__8CPartPcs[];
extern unsigned int m_table_desc12__8CPartPcs[];
extern unsigned int m_table_desc13__8CPartPcs[];
extern unsigned int m_table_desc14__8CPartPcs[];
extern unsigned int m_table_desc15__8CPartPcs[];
extern unsigned int m_table_desc16__8CPartPcs[];
extern unsigned int m_table_desc17__8CPartPcs[];
extern unsigned int m_table_desc18__8CPartPcs[];
extern unsigned int m_table__8CPartPcs[];

class CPartPcs : public CProcess
{
public:
    CUSBStreamData m_usbStreamData; // 0x04

    CPartPcs();
    ~CPartPcs();

    void Init();
    void Quit();

    void onScriptChanging(char*);
    int GetTable(unsigned long);

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
    int LoadMonsterPdt(int, int, void*, int, void*, int);
    int LoadMenuPdt(char*);
    void ReleasePdt(int);

    void StartLocationTitle();
    void EndLocationTitle();

    void StartMiruraEvent();
    void EndMiruraEvent();

    void pppSetDebugHide(unsigned char);
    void SetUSBData();
};

extern CPartPcs PartPcs;

#endif
