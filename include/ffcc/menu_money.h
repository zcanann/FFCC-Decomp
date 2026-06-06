#ifndef _FFCC_MENU_MONEY_H_
#define _FFCC_MENU_MONEY_H_

#include "ffcc/p_menu.h"

struct MoneyMenuAnim
{
    short x;
    short y;
    short w;
    short h;
    float u;
    float v;
    float alpha;
    float uvScale;
    int unk18;
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

struct MoneyMenuAnimList
{
    short count;
    char pad_02[6];
    MoneyMenuAnim anims[64];
};

struct MoneyMenuState
{
    char pad_00[0x09];
    signed char messageMask;
    char pad_0a;
    char initialized;
    char pad_0c;
    char closeRequested;
    char pad_0e[0x2];
    short listState;
    short optionState;
    short optionIndex;
    char pad_16[0x8];
    short moveDirection;
    char pad_20[0x2];
    short frame;
    char pad_24[0x2];
    short selections[2];
    char pad_2a[0x6];
    short mode;
    short prevMode;
};

#endif // _FFCC_MENU_MONEY_H_
