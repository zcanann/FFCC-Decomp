#ifndef _FFCC_MENU_CMD_H_
#define _FFCC_MENU_CMD_H_

#include "ffcc/p_menu.h"

struct CmdListEntry {
	short x;
	short y;
	short width;
	short height;
	float u;
	float v;
	float alpha;
	float scale;
	int unk_18;
	int tex;
	int timer;
	int startFrame;
	int duration;
	unsigned int flags;
	float dx;
	float dy;
	float targetX;
	float targetY;
};

struct CmdListStorage {
	short count;
	short listEnd;
	unsigned char pad_0004[4];
	CmdListEntry entries[64];
};

struct CmdState {
	unsigned char pad_0000[0x06];
	unsigned char submenuFlag;
	unsigned char pad_0007;
	signed char commandResult;
	unsigned char pad_0009[0x0B - 0x09];
	signed char initialized;
	unsigned char unitePanelInitialized;
	unsigned char uniteOpenFlag;
	unsigned char pad_000E[0x10 - 0x0E];
	short animState;
	short phase;
	short uniteState;
	unsigned char pad_0016[0x1E - 0x16];
	short action;
	unsigned char pad_0020[0x22 - 0x20];
	short transitionTimer;
	unsigned char pad_0024[0x26 - 0x24];
	short selected[4];
	unsigned char pad_002E[0x30 - 0x2E];
	short mode;
	short prevMode;
	short scrollTop;
};

bool IsMagicArti(int);

#endif // _FFCC_MENU_CMD_H_
