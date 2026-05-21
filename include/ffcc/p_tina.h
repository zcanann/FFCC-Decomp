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
unsigned char pppNotAllocAmemCacheRmem(unsigned long);
unsigned int pppFreeMngStPrioForData();
unsigned char pppAmemDeletePmng(unsigned long);
unsigned char pppAmemRefCntError(unsigned long);

class CPartPcs : public CProcess
{
public:
    static unsigned int m_table_desc0[3];
    static unsigned int m_table_desc1[3];
    static unsigned int m_table_desc2[3];
    static unsigned int m_table_desc3[3];
    static unsigned int m_table_desc4[3];
    static unsigned int m_table_desc5[3];
    static unsigned int m_table_desc6[3];
    static unsigned int m_table_desc7[3];
    static unsigned int m_table_desc8[3];
    static unsigned int m_table_desc9[3];
    static unsigned int m_table_desc10[3];
    static unsigned int m_table_desc11[3];
    static unsigned int m_table_desc12[3];
    static unsigned int m_table_desc13[3];
    static unsigned int m_table_desc14[3];
    static unsigned int m_table_desc15[3];
    static unsigned int m_table_desc16[3];
    static unsigned int m_table_desc17[3];
    static unsigned int m_table_desc18[3];
    static unsigned int m_table[2][0x15C / sizeof(unsigned int)];

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
