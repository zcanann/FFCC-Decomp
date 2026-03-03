#ifndef _FFCC_MENU_FAVO_H_
#define _FFCC_MENU_FAVO_H_

class CFont;

class FoodRank
{
public:
};

struct SingMenuState
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
    void FavoInit();
    void FavoInit0();
    bool FavoOpen();
    unsigned int FavoCtrl();
    bool FavoClose();
    void FavoDraw();
    void FavoCtrlCur();

    char pad_00[0xF8];
    CFont* font22;
    char pad_fc[0xC];
    CFont* font16;
    char pad_10c[0x720];
    SingMenuState* singMenuState;
    char pad_830[0x18];
    short* singWindowInfo;
    short* favoList;
    char pad_854[0x100];
};

#endif // _FFCC_MENU_FAVO_H_
