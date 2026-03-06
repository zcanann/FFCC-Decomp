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
    void* GetTable(unsigned long);
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
};

extern CMapPcs MapPcs;

#endif // _FFCC_P_MAP_H_
