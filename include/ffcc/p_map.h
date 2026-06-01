#ifndef _FFCC_P_MAP_H_
#define _FFCC_P_MAP_H_

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#include "ffcc/system.h"

struct Vec;

extern const float kMapBoundsCenterScale;
extern const float kMapCameraCenterYOffset;

class CMapPcs : public CProcess
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
    static unsigned int m_table_desc19[3];
    static unsigned int m_table_desc20[3];
    static unsigned int m_table_desc21[3];
    static unsigned int m_table_desc22[3];
    static unsigned int m_table_desc23[3];
    static unsigned int m_table[3][0x15C / sizeof(unsigned int)];

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

extern "C" void create__7CMapPcsFv(CMapPcs*);
extern "C" void destroy__7CMapPcsFv(CMapPcs*);
extern "C" void calcInit__7CMapPcsFv(CMapPcs*);
extern "C" void calc__7CMapPcsFv(CMapPcs*);
extern "C" void drawShadow__7CMapPcsFv(CMapPcs*);
extern "C" void drawBefore__7CMapPcsFv(CMapPcs*);
extern "C" void draw__7CMapPcsFv(CMapPcs*);
extern "C" void drawAfter__7CMapPcsFv(CMapPcs*);
extern "C" void createViewer__7CMapPcsFv(CMapPcs*);
extern "C" void calcViewer__7CMapPcsFv(CMapPcs*);
extern "C" void drawBeforeViewer__7CMapPcsFv(CMapPcs*);
extern "C" void drawViewer__7CMapPcsFv(CMapPcs*);
extern "C" void drawAfterViewer__7CMapPcsFv(CMapPcs*);

extern CMapPcs MapPcs;

#endif // _FFCC_P_MAP_H_
