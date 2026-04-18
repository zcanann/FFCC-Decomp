#ifndef _FFCC_P_MAP_H_
#define _FFCC_P_MAP_H_

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#include "ffcc/system.h"

struct Vec;

void mapInitDrawEnv();
extern const float kMapBoundsCenterScale;
extern const float kMapCameraCenterYOffset;

class CMapPcs : public CProcess
{
public:
    CMapPcs();
	
    void Init();
    void Quit();
    int GetTable(unsigned long);
    void create();
    void createViewer();
    void LoadMap(char*, void*, unsigned long, unsigned char);
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
    void GetMapLightHolder(long, _GXColor*, Vec*);

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
    u8 _pad188[0x1B0 - 0x188];           // 0x188
};

extern CMapPcs MapPcs;
extern unsigned int m_table_desc0__7CMapPcs[];
extern unsigned int m_table_desc1__7CMapPcs[];
extern unsigned int m_table_desc2__7CMapPcs[];
extern unsigned int m_table_desc3__7CMapPcs[];
extern unsigned int m_table_desc4__7CMapPcs[];
extern unsigned int m_table_desc5__7CMapPcs[];
extern unsigned int m_table_desc6__7CMapPcs[];
extern unsigned int m_table_desc7__7CMapPcs[];
extern unsigned int m_table_desc8__7CMapPcs[];
extern unsigned int m_table_desc9__7CMapPcs[];
extern unsigned int m_table_desc10__7CMapPcs[];
extern unsigned int m_table_desc11__7CMapPcs[];
extern unsigned int m_table_desc12__7CMapPcs[];
extern unsigned int m_table_desc13__7CMapPcs[];
extern unsigned int m_table_desc14__7CMapPcs[];
extern unsigned int m_table_desc15__7CMapPcs[];
extern unsigned int m_table_desc16__7CMapPcs[];
extern unsigned int m_table_desc17__7CMapPcs[];
extern unsigned int m_table_desc18__7CMapPcs[];
extern unsigned int m_table_desc19__7CMapPcs[];
extern unsigned int m_table_desc20__7CMapPcs[];
extern unsigned int m_table_desc21__7CMapPcs[];
extern unsigned int m_table_desc22__7CMapPcs[];
extern unsigned int m_table_desc23__7CMapPcs[];
extern unsigned int PTR_s_CMapPcs_GAME__801e8ad8[][0x15C / sizeof(unsigned int)];

#endif // _FFCC_P_MAP_H_
