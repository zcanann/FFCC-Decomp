#ifndef _FFCC_MESMENU_H_
#define _FFCC_MESMENU_H_

#include "ffcc/mes.h"
#include "ffcc/menu.h"

class _GXColor;

class CMesMenu : public CMenu
{
public:
    CMesMenu();
    ~CMesMenu();

    void Create();
    void Destroy();
    void onCalc();
    void onDraw();
    void CalcHeart();
    void DrawHeart(float, float, float, float);
    void onScriptChanging(char*);
    void onScriptChanged(char*, int);
    void Open(char*, int, int, int, int, int, int);
    void CloseRequest(int);
    void SetPos(float, float);

private:
    int m_active;              // 0x0008
    int m_state;               // 0x000C
    int m_stateTimer;          // 0x0010
    int m_stateTimerMax;       // 0x0014
    int m_menuIndex;           // 0x0018
    CMes m_mes;                // 0x001C
    float m_baseX;             // 0x3D6C
    float m_baseY;             // 0x3D70
    float m_offsetX;           // 0x3D74
    float m_offsetY;           // 0x3D78
    float m_windowWidth;       // 0x3D7C
    float m_windowHeight;      // 0x3D80
    float m_windowScale;       // 0x3D84
    int m_fromScriptPosition;  // 0x3D88
    unsigned int m_flags;      // 0x3D8C
    int m_buttonMask;          // 0x3D90
    int m_itemIndex;           // 0x3D94
    int m_nameIndex;           // 0x3D98
    float m_marginX;           // 0x3D9C
    float m_marginY;           // 0x3DA0
    int m_closeReason;         // 0x3DA4
    int m_heartValue;          // 0x3DA8
    int m_heartTarget;         // 0x3DAC
    int m_heartGrowTimers[8];  // 0x3DB0
    int m_heartDropTimers[8];  // 0x3DD0
    int m_foodShakeTimer;      // 0x3DF0
    int m_stageFadeTimer;      // 0x3DF4
    int m_stageFadeOut;        // 0x3DF8
};

#endif // _FFCC_MESMENU_H_
