#ifndef _FFCC_MENU_ITEM_H_
#define _FFCC_MENU_ITEM_H_

#include "ffcc/p_menu.h"

struct ItemMenuAnimList;

struct ItemMenuState
{
    char pad_00[0x09];
    char optionFlags;
    char pad_0a;
    char initialized;
    char pad_0c;
    char closeRequested;
    char pad_0e[0x2];
    short listState;
    short optionFrame;
    short optionIndex;
    char pad_16[0x8];
    short cursorMove;
    char pad_20[0x2];
    short frame;
    char pad_24[0x2];
    short cursorIndex[2];
    char pad_2a[0x6];
    short mode;
    short prevMode;
    short scroll;
};

#endif // _FFCC_MENU_ITEM_H_
