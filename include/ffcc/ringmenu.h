#ifndef _FFCC_PPP_RINGMENU_H_
#define _FFCC_PPP_RINGMENU_H_

class CFont;
class CCaravanWork;
class CGame;
class CMenuPcs;

void drawCommand(int, CFont*, float, float, CCaravanWork*, int, float, float);

class CRingMenu
{
public:
    CRingMenu();
    ~CRingMenu();

    void Create();
    void Destroy();
    void GetDispCounter();
    void onCalc();
    void onDraw();
    void drawGBA();
    void onScriptChanging(char*);
    void onScriptChanged(char*, int);
    void SetFade(int);
    void SetBattleButton(int, int);
    void SetBattleCommand(int, int, int);
    void DrawIcon();
};

#endif // _FFCC_PPP_RINGMENU_H_
