#ifndef _FFCC_MENU_EQUIP_H_
#define _FFCC_MENU_EQUIP_H_

#include "ffcc/p_menu.h"

struct EquipMenuState
{
    unsigned char pad_00[0x0B];
    unsigned char initialized;
    unsigned char pad_0C;
    unsigned char closeRequested;
    unsigned char pad_0E[2];
    short listState;
    short step;
    unsigned char pad_14[0x0A];
    short cursorMove;
    unsigned char pad_20[2];
    short frame;
    unsigned char pad_24[2];
    short selected[2];
    unsigned char pad_2A[2];
    short emptySlotHelpState;
    unsigned char pad_2E[2];
    short mode;
    short prevMode;
    short scroll;
};

struct EquipOpenAnim
{
    short x;
    short y;
    short w;
    short h;
    float u;
    float v;
    float alpha;
    float scale;
    int unk;
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

struct EquipOpenAnimList
{
    short count;
    short listEnd;
    unsigned char pad_04[4];
    EquipOpenAnim entries[64];
};

#endif // _FFCC_MENU_EQUIP_H_
