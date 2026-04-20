#ifndef _FFCC_MENU_LST_H_
#define _FFCC_MENU_LST_H_

class CFont;

struct MenuLstState
{
    char pad_00[0x0B];
    char initialized;
    char pad_0c;
    char closeRequested;
    char pad_0e[0x02];
    short mode;
    char pad_12[0x10];
    short frame;
    char pad_24[0x02];
    short cursor;
};

struct MenuLstEntry
{
    short x;
    short y;
    short width;
    short height;
    float s;
    float t;
    float alpha;
    float z;
    int unk_18;
    int tex;
    int timer;
    int startFrame;
    int duration;
    int unk_2C;
    char pad_30[0x10];
};

struct MenuLstList
{
    short count;
    short pad_02;
    int pad_04;
    MenuLstEntry entries[64];
};

class CMenuPcs
{
public:
    void MLstInit();
    void MLstInit1();
    int MLstOpen();
    void MLstCtrl();
    int MLstClose();
    void MLstDraw();
    void MLstCtrlCur();

    char pad_00[0x108];
    CFont* listFont;
    char pad_10c[0x720];
    MenuLstState* lstState;
    char pad_830[0x20];
    MenuLstList* lstData;
};

#endif // _FFCC_MENU_LST_H_
