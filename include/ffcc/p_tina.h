#ifndef _FFCC_P_TINA_H_
#define _FFCC_P_TINA_H_

#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/USBStreamData.h"

struct Vec;
struct pppIVECTOR3;
struct pppFVECTOR4;

void LoadFieldPdt0(int, int);
unsigned char pppNotAllocAmemCacheRmem(unsigned long);
unsigned int pppFreeMngStPrioForData();
unsigned char pppAmemDeletePmng(unsigned long);
unsigned char pppAmemRefCntError(unsigned long);

class CPartPcs : public CProcess
{
public:
    static CProcessTableCallback m_table_desc0;
    static CProcessTableCallback m_table_desc1;
    static CProcessTableCallback m_table_desc2;
    static CProcessTableCallback m_table_desc3;
    static CProcessTableCallback m_table_desc4;
    static CProcessTableCallback m_table_desc5;
    static CProcessTableCallback m_table_desc6;
    static CProcessTableCallback m_table_desc7;
    static CProcessTableCallback m_table_desc8;
    static CProcessTableCallback m_table_desc9;
    static CProcessTableCallback m_table_desc10;
    static CProcessTableCallback m_table_desc11;
    static CProcessTableCallback m_table_desc12;
    static CProcessTableCallback m_table_desc13;
    static CProcessTableCallback m_table_desc14;
    static CProcessTableCallback m_table_desc15;
    static CProcessTableCallback m_table_desc16;
    static CProcessTableCallback m_table_desc17;
    static CProcessTableCallback m_table_desc18;
    static CProcessTable m_table[2];

    CUSBStreamData m_usbStreamData; // 0x04

    CPartPcs();
    ~CPartPcs();

    void Init();
    void Quit();

    void onScriptChanging(char*);
    int GetTable(unsigned long);

    void create();
    void createLoad();
    void createViewer();
    void destroy();

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
};

extern CPartPcs PartPcs;

#endif
