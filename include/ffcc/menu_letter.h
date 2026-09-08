#ifndef _FFCC_MENU_LETTER_H_
#define _FFCC_MENU_LETTER_H_

#include "ffcc/p_menu.h"

struct LetterMenuState
{
    char pad_00[8];
    signed char action;
    signed char messageMask;
    char pad_0A;
    char initialized;
    char dialogInitialized;
    char closeRequested;
    char pad_0E[4];
    short step;
    char pad_14[10];
    short cursorMove;
    char pad_20[2];
    short frame;
    char pad_24[2];
    short listCursor;
    short choiceCursor;
    char pad_2A[6];
    short mode;
    short previousMode;
    short topIndex;
    char pad_36[0x12];
};

STATIC_ASSERT(offsetof(LetterMenuState, action) == 0x08);
STATIC_ASSERT(offsetof(LetterMenuState, messageMask) == 0x09);
STATIC_ASSERT(offsetof(LetterMenuState, initialized) == 0x0B);
STATIC_ASSERT(offsetof(LetterMenuState, dialogInitialized) == 0x0C);
STATIC_ASSERT(offsetof(LetterMenuState, closeRequested) == 0x0D);
STATIC_ASSERT(offsetof(LetterMenuState, step) == 0x12);
STATIC_ASSERT(offsetof(LetterMenuState, cursorMove) == 0x1E);
STATIC_ASSERT(offsetof(LetterMenuState, frame) == 0x22);
STATIC_ASSERT(offsetof(LetterMenuState, listCursor) == 0x26);
STATIC_ASSERT(offsetof(LetterMenuState, choiceCursor) == 0x28);
STATIC_ASSERT(offsetof(LetterMenuState, mode) == 0x30);
STATIC_ASSERT(offsetof(LetterMenuState, previousMode) == 0x32);
STATIC_ASSERT(offsetof(LetterMenuState, topIndex) == 0x34);
STATIC_ASSERT(sizeof(LetterMenuState) == sizeof(SingMenuState));
STATIC_ASSERT(offsetof(CMenuPcs, m_letterMenuState) == 0x82C);

#endif // _FFCC_MENU_LETTER_H_
