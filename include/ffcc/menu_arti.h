#ifndef _FFCC_MENU_ARTI_H_
#define _FFCC_MENU_ARTI_H_

#include "ffcc/p_menu.h"

struct ArtiState
{
    unsigned char pad_0000[0xB];
    char initialized;
    unsigned char pad_000C;
    unsigned char closeRequested;
    unsigned char pad_000E[2];
    short state;
    unsigned char pad_0012[0x0C];
    short moveDirection;
    unsigned short optionCloseReady;
    short frame;
    unsigned char pad_0024[2];
    short selections[5];
    short currentSelection;
    short prevSelection;
    short scrollOffset;
};

struct ArtiOpenAnim
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

struct ArtiOpenAnimList
{
    short count;
    unsigned char pad_0002[6];
    ArtiOpenAnim entries[64];
};

#endif // _FFCC_MENU_ARTI_H_
