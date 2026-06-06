#ifndef _FFCC_MENU_FAVO_H_
#define _FFCC_MENU_FAVO_H_

#include "ffcc/p_menu.h"

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

#endif // _FFCC_MENU_FAVO_H_
