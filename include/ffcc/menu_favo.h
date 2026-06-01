#ifndef _FFCC_MENU_FAVO_H_
#define _FFCC_MENU_FAVO_H_

#include <dolphin/gx.h>

class CFont;

class FoodRank
{
public:
    signed char place;
    unsigned char foodId;
    short score;
};

struct FavoEntry
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
    int step;
    int startFrame;
    int duration;
    unsigned int flags;
    float dx;
    float dy;
    float targetX;
    float targetY;
};

struct FavoListStorage
{
    short count;
    short selected;
    int pad_04;
    FavoEntry entries[64];
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
    enum FMT
    {
        TODO_FMT
    };

    enum TEX
    {
        TODO_TEX
    };

    void DrawInit();
    void SetAttrFmt(FMT);
    void SetTexture(TEX);
    void DrawRect(unsigned long, float, float, float, float, float, float, float, float, float);
    void DrawRect(unsigned long, float, float, float, float, float, float, _GXColor*, float, float, float);
    void DrawSingBar(int, int, int, float);
    void DrawSingleIcon(int, int, int, float, int, float);

    void FavoInit();
    void FavoInit0();
    bool FavoOpen();
    unsigned int FavoCtrl();
    bool FavoClose();
    void FavoDraw();

    char pad_00[0xF8];
    CFont* font22;
    char pad_fc[0xC];
    CFont* font16;
    char pad_10c[0x720];
    SingMenuState* singMenuState;
    char pad_830[0x18];
    short* singWindowInfo;
    char pad_84c[0x4];
    FavoListStorage* favoList;
    char pad_854[0x100];
};

extern CMenuPcs MenuPcs;

#endif // _FFCC_MENU_FAVO_H_
