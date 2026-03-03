#ifndef _FFCC_MENU_COMPA_H_
#define _FFCC_MENU_COMPA_H_

class CFont;

struct CompaMenuState
{
    char pad_00[0x0B];
    char initialized;
    char pad_0c;
    char closeRequested;
    char pad_0e[0x10];
    short cursorMove;
    char pad_20[0x2];
    short frame;
    char pad_24[0x2];
    short selectedIndex;
};

class CMenuPcs
{
public:
    void CompaInit();
    void CompaInit0();
    bool CompaOpen();
    void CompaCtrl();
    void CompaClose();
    void CompaDraw();
    void CompaCtrlCur();

    char pad_00[0x108];
    CFont* listFont;
    char pad_10c[0x720];
    CompaMenuState* compaMenuState;
    char pad_830[0x20];
    short* compaList;
};

#endif // _FFCC_MENU_COMPA_H_
