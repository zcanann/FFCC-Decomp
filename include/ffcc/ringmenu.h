#ifndef _FFCC_PPP_RINGMENU_H_
#define _FFCC_PPP_RINGMENU_H_

#include "ffcc/menu.h"

class CFont;
class CCaravanWork;
class CGame;
class CMenuPcs;

void drawCommand(int, CFont*, float, float, CCaravanWork*, int, float, float);

class CRingMenu : public CMenu
{
public:
    CRingMenu();
    ~CRingMenu();

    void Create();
    void Destroy();
    double GetDispCounter();
    void onCalc();
    void onDraw();
    void drawGBA();
    void onScriptChanging(char*);
    void onScriptChanged(char*, int);
    void SetFade(int);
    void SetBattleButton(int, int);
    void SetBattleCommand(int, int, int);
    void DrawIcon();

    int m_menuIndex;
    int m_stateFlag;
    int m_animDirection;
    int m_transitionCounter;
    int m_battleButtons[8];
    int m_buttonTimers[9];
    int m_ringRotation;
    int m_rotationPhase;
    float m_spinPhase;
    char m_unk68[0x418];
    float m_animFloat[9][3];
    int m_gbaConnectedFlag;
    int m_gbaAnimCounter;
    int m_commonFrameCounter;
    int m_unk4f8;
    int m_timerB;
    int m_displayCounter;
    int m_displayDirection;
    int m_currentCommandIndex;
    float m_spinAccumulator;
    char m_unk510[0x10];
};

#endif // _FFCC_PPP_RINGMENU_H_
