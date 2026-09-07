#ifndef _FFCC_BONUS_MENU_H_
#define _FFCC_BONUS_MENU_H_

#include "ffcc/p_menu.h"

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
