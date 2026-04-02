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
extern unsigned char m_table__8CPartPcs[];

class CPartPcs : public CProcess
{
public:
    CUSBStreamData m_usbStreamData; // 0x04

    CPartPcs()
    {
        unsigned int* table = reinterpret_cast<unsigned int*>(m_table__8CPartPcs);
        table[1] = m_table_desc0__8CPartPcs[0];
        table[2] = m_table_desc0__8CPartPcs[1];
        table[3] = m_table_desc0__8CPartPcs[2];
        table[4] = m_table_desc1__8CPartPcs[0];
        table[5] = m_table_desc1__8CPartPcs[1];
        table[6] = m_table_desc1__8CPartPcs[2];
        table[7] = m_table_desc2__8CPartPcs[0];
        table[8] = m_table_desc2__8CPartPcs[1];
        table[9] = m_table_desc2__8CPartPcs[2];
        table[12] = m_table_desc3__8CPartPcs[0];
        table[13] = m_table_desc3__8CPartPcs[1];
        table[14] = m_table_desc3__8CPartPcs[2];
        table[17] = m_table_desc4__8CPartPcs[0];
        table[18] = m_table_desc4__8CPartPcs[1];
        table[19] = m_table_desc4__8CPartPcs[2];
        table[22] = m_table_desc5__8CPartPcs[0];
        table[23] = m_table_desc5__8CPartPcs[1];
        table[24] = m_table_desc5__8CPartPcs[2];
        table[27] = m_table_desc6__8CPartPcs[0];
        table[28] = m_table_desc6__8CPartPcs[1];
        table[29] = m_table_desc6__8CPartPcs[2];
        table[32] = m_table_desc7__8CPartPcs[0];
        table[33] = m_table_desc7__8CPartPcs[1];
        table[37] = m_table_desc8__8CPartPcs[1];
        table[38] = m_table_desc8__8CPartPcs[2];
        table[35] = m_table_desc7__8CPartPcs[2];
        table[39] = m_table_desc8__8CPartPcs[0];
        table[44] = m_table_desc9__8CPartPcs[1];
        table[45] = m_table_desc9__8CPartPcs[2];
        table[46] = m_table_desc9__8CPartPcs[0];

        table[88] = m_table_desc10__8CPartPcs[0];
        table[89] = m_table_desc10__8CPartPcs[1];
        table[90] = m_table_desc10__8CPartPcs[2];
        table[93] = m_table_desc11__8CPartPcs[0];
        table[94] = m_table_desc11__8CPartPcs[1];
        table[95] = m_table_desc11__8CPartPcs[2];
        table[96] = m_table_desc12__8CPartPcs[0];
        table[97] = m_table_desc12__8CPartPcs[1];
        table[98] = m_table_desc12__8CPartPcs[2];
        table[101] = m_table_desc13__8CPartPcs[0];
        table[102] = m_table_desc13__8CPartPcs[1];
        table[103] = m_table_desc13__8CPartPcs[2];
        table[106] = m_table_desc14__8CPartPcs[0];
        table[107] = m_table_desc14__8CPartPcs[1];
        table[108] = m_table_desc14__8CPartPcs[2];
        table[111] = m_table_desc15__8CPartPcs[0];
        table[112] = m_table_desc15__8CPartPcs[1];
        table[113] = m_table_desc15__8CPartPcs[2];
        table[114] = m_table_desc16__8CPartPcs[0];
        table[117] = m_table_desc17__8CPartPcs[0];
        table[118] = m_table_desc17__8CPartPcs[1];
        table[119] = m_table_desc17__8CPartPcs[2];
        table[120] = m_table_desc16__8CPartPcs[1];
        table[121] = m_table_desc16__8CPartPcs[2];
        table[124] = m_table_desc18__8CPartPcs[0];
        table[125] = m_table_desc18__8CPartPcs[1];
        table[126] = m_table_desc18__8CPartPcs[2];
    }
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
