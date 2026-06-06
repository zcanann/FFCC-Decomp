#ifndef _FFCC_MENU_COMPA_H_
#define _FFCC_MENU_COMPA_H_

#include "ffcc/p_menu.h"

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

#endif // _FFCC_MENU_COMPA_H_
