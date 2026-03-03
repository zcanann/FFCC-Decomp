#ifndef _FFCC_MENU_ITEM_H_
#define _FFCC_MENU_ITEM_H_

class CFont;

struct ItemMenuState
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
    void ItemInit();
    void ItemInit1();
    bool ItemOpen();
    int ItemCtrl();
    bool ItemClose();
    void ItemDraw();
    int ItemCtrlCur();
    void SingLifeInit(int);

    char pad_00[0xF8];
    CFont* helpFont;
    char pad_fc[0xC];
    CFont* listFont;
    char pad_10c[0x720];
    ItemMenuState* itemMenuState;
    char pad_830[0x18];
    short* singWindowInfo;
    short* itemList;
    char pad_854[0x100];
};

#endif // _FFCC_MENU_ITEM_H_
