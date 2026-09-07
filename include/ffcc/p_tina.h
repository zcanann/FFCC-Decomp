#ifndef _FFCC_P_TINA_H_
#define _FFCC_P_TINA_H_

#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/USBStreamData.h"

struct Vec;
struct pppIVECTOR3;
struct pppFVECTOR4;

unsigned char pppNotAllocAmemCacheRmem(unsigned long);
unsigned int pppFreeMngStPrioForData();
unsigned char pppAmemDeletePmng(unsigned long);
unsigned char pppAmemRefCntError(unsigned long);

class CPartPcs : public CProcess
{
public:
    static CProcessCallbackTable m_table[2];

    CUSBStreamData m_usbStreamData; // 0x04
    CUSBStreamDataState m_usbStreamState; // 0x18

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
extern "C" unsigned char g_IsDrawHeapSize;
extern char g_MsgFlashy[0x36];

#endif
