#ifndef _FFCC_MENU_COMPA_H_
#define _FFCC_MENU_COMPA_H_

class CFont;

struct CompaOpenAnim
{
    short x;
    short y;
    short w;
    short h;
    float u;
    float v;
    float alpha;
    float uvScale;
    int drawFlags;
    int tex;
    int frame;
    int startFrame;
    int duration;
    unsigned int flags;
    float dx;
    float dy;
    float targetX;
    float targetY;
};

struct CompaOpenAnimList
{
    short count;
    short pad_02;
    int pad_04;
    CompaOpenAnim entries[64];
};

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
    bool CompaOpen();
    void CompaCtrl();
    bool CompaClose();
    void CompaDraw();

    char pad_00[0x108];
    CFont* listFont;
    char pad_10c[0x720];
    CompaMenuState* compaMenuState;
    char pad_830[0x20];
    CompaOpenAnimList* compaList;
};

#endif // _FFCC_MENU_COMPA_H_
