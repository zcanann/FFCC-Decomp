#ifndef _FFCC_P_MAP_H_
#define _FFCC_P_MAP_H_

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#include "ffcc/system.h"

struct Vec;

class CMapPcs : public CProcess
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
    static CProcessTableCallback m_table_desc19;
    static CProcessTableCallback m_table_desc20;
    static CProcessTableCallback m_table_desc21;
    static CProcessTableCallback m_table_desc22;
    static CProcessTableCallback m_table_desc23;
    static CProcessTable m_table[3];

    CMapPcs();

    void Init();
    void Quit();
    int GetTable(unsigned long);
    void create();
    void createViewer();
    void LoadMap(int, int, void*, unsigned long, unsigned char);
    unsigned long long IsLoadMapCompleted();
    void destroy();
    void calcInit();
    void calc();
    void calcViewer();
    void drawShadow();
    void drawBefore();
    void draw();
    void drawBeforeViewer();
    void drawViewer();
    void drawAfter();
    void drawAfterViewer();
    void CalcHitPosition(Vec*);
    int CheckHitCylinderNear(Vec*, Vec*, float, unsigned long);
    void IsHitDrawMode(char);

private:
    Mtx m_viewMtx;                       // 0x04
    Mtx44 m_screenMtx;                   // 0x34
    char m_mapName[0x100];               // 0x74
    s32 m_forceMapReload;                // 0x174
    s32 m_mapCalcReady;                  // 0x178
    s32 m_viewerMode;                    // 0x17C
    s32 m_drawEnabled;                   // 0x180
    u8 m_useStoredViewMtx;               // 0x184
    u8 m_pad185[3];                      // 0x185
};

extern CMapPcs MapPcs;
extern unsigned char g_hit_prof;
extern unsigned char g_map_calc_prof;
extern unsigned char g_map_draw_prof;

#endif // _FFCC_P_MAP_H_
