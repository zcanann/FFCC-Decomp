#ifndef _FFCC_P_MAP_H_
#define _FFCC_P_MAP_H_

#include <dolphin/gx.h>

#include "ffcc/system.h"

struct Vec;

void mapInitDrawEnv();

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
    int IsLoadMapCompleted();
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
};

#endif // _FFCC_P_MAP_H_
