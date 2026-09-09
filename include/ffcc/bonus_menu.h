#ifndef _FFCC_BONUS_MENU_H_
#define _FFCC_BONUS_MENU_H_

#include "ffcc/p_menu.h"

struct BonusAnimHeader {
	short count;
	short unk02;
	short unk04;
	short finished;
};

struct BonusAnimList {
	BonusAnimHeader header;
	CMenuPcs::Sprt2 sprites[64];
};

STATIC_ASSERT(sizeof(BonusAnimHeader) == 8);
STATIC_ASSERT(offsetof(BonusAnimHeader, count) == 0);
STATIC_ASSERT(offsetof(BonusAnimHeader, finished) == 6);
STATIC_ASSERT(offsetof(BonusAnimList, sprites) == 8);
STATIC_ASSERT(sizeof(CMenuPcs::Sprt2) == 0x40);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, x) == 0x00);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, y) == 0x02);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, w) == 0x04);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, h) == 0x06);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, mulX) == 0x08);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, mulY) == 0x0C);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, alpha) == 0x10);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, depth) == 0x14);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, tex) == 0x18);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, kind) == 0x1C);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, timer) == 0x20);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, startFrame) == 0x24);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, duration) == 0x28);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, flags) == 0x2C);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, motionX) == 0x30);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, motionY) == 0x34);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, targetX) == 0x38);
STATIC_ASSERT(offsetof(CMenuPcs::Sprt2, targetY) == 0x3C);
STATIC_ASSERT(sizeof(BonusAnimList) == 0x1008);

struct BonusMenuState
{
    float m_modelRotation;
    unsigned char m_pad04[4];
    signed char m_selectionResult;
    unsigned char m_pad09[2];
    signed char m_initialized;
    unsigned char m_pad0C[2];
    short m_currentRank;
    short m_countFinished;
    unsigned char m_pad12[6];
    short m_finishDelay;
    short m_selectionDelay;
    short m_phase;
    unsigned char m_pad1E[4];
    short m_frame;
    unsigned char m_pad24[2];
    short m_selection;
    short m_confirmSelection;
    unsigned char m_pad2A[0x1E];
};

STATIC_ASSERT(sizeof(BonusMenuState) == 0x48);
STATIC_ASSERT(offsetof(BonusMenuState, m_modelRotation) == 0x00);
STATIC_ASSERT(offsetof(BonusMenuState, m_selectionResult) == 0x08);
STATIC_ASSERT(offsetof(BonusMenuState, m_initialized) == 0x0B);
STATIC_ASSERT(offsetof(BonusMenuState, m_currentRank) == 0x0E);
STATIC_ASSERT(offsetof(BonusMenuState, m_countFinished) == 0x10);
STATIC_ASSERT(offsetof(BonusMenuState, m_finishDelay) == 0x18);
STATIC_ASSERT(offsetof(BonusMenuState, m_selectionDelay) == 0x1A);
STATIC_ASSERT(offsetof(BonusMenuState, m_phase) == 0x1C);
STATIC_ASSERT(offsetof(BonusMenuState, m_frame) == 0x22);
STATIC_ASSERT(offsetof(BonusMenuState, m_selection) == 0x26);
STATIC_ASSERT(offsetof(BonusMenuState, m_confirmSelection) == 0x28);

#endif // _FFCC_BONUS_MENU_H_
