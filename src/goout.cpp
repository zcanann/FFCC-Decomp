#include "ffcc/goout.h"
#include "ffcc/wm_menu.h"
#include <stdarg.h>
#include <string.h>

CGoOutMenu g_GoOutMenu;
CGoOutMenu* g_pGoOutMenu;

extern "C" int GetYesNoXPos__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int CalcGoOutSelChar__8CMenuPcsFUcUc(CMenuPcs*, unsigned char, unsigned char);
extern "C" void Calc__10CGoOutMenuFv(CGoOutMenu*);
extern "C" void __dl__FPv(void*);
extern "C" int GetWinMess__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* const* GetMcWinMessBuff__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* lbl_80214FE0[];

struct CMenuPcsGoOutLayout
{
    unsigned char unk0[0x20];
    McCtrl m_mcCtrl;
    unsigned char unkAfterMcCtrl[0x7E4];
    int m_goOutStatePtr;
    unsigned char unk830[0x18];
    int m_mcWinStatePtr;
    unsigned char unk84C[0x30];
    unsigned char m_resetGoOutFlag;
    unsigned char m_unknown_87D;
    unsigned char m_unknown_87E;
    unsigned char m_unknown_87F;
    Mc::SaveDat* m_transferSaveData;
    void* m_transferWork;
    unsigned char m_unknown_888;
    unsigned char m_saveLoadMode;
    unsigned char m_unknown_88A;
    unsigned char m_unknown_88B;
    void* m_transferWorkActive;
};

struct CMenuGoOutState
{
    unsigned char unk0[0x18];
    signed short m_waitFrames;
    signed short unk1A;
    signed short m_closeMode;
    signed short m_resultDir;
    signed short m_resultSelect;
    signed short m_animFrame;
};

struct CMenuMcWinState
{
    signed short m_x;
    signed short m_y;
    signed short m_width;
    signed short m_height;
    signed short unk8;
    signed short m_mode;
};

static inline unsigned char ReadGoOutU8(CGoOutMenu& menu, int offset) { return *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(&menu) + offset); }
static inline signed short ReadGoOutS16(CGoOutMenu& menu, int offset) { return *reinterpret_cast<signed short*>(reinterpret_cast<unsigned char*>(&menu) + offset); }
static inline signed char ReadGoOutS8(CGoOutMenu& menu, int offset) { return *reinterpret_cast<signed char*>(reinterpret_cast<unsigned char*>(&menu) + offset); }

static inline CMenuGoOutState& MenuGoOutState(CMenuPcsGoOutLayout& layout)
{
    return *reinterpret_cast<CMenuGoOutState*>(layout.m_goOutStatePtr);
}

static inline CMenuMcWinState& MenuMcWinState(CMenuPcsGoOutLayout& layout)
{
    return *reinterpret_cast<CMenuMcWinState*>(layout.m_mcWinStatePtr);
}

static unsigned short GetGoOutInputMask()
{
    bool hasPendingInput = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        hasPendingInput = true;
    }
    if (hasPendingInput) {
        return 0;
    }

    __cntlzw(Pad._448_4_);
    return static_cast<unsigned short>(Pad._8_2_);
}

static inline const char* GetGoOutMessageLine(int languageId, int line)
{
    return lbl_80214FE0[(languageId * 0x6E) + line];
}

static const char sSlotAErrorText1[] = "The Memory Card in Slot A contains";
static const char sSlotAErrorText2[] = "no save data for your current game";
static const char sSlotAErrorText3[] = "or contains corrupt data. Please";
static const char sSlotAErrorText4[] = "insert a Memory Card containing";
static const char sSlotAErrorText5[] = "valid save data into Slot A.";
static const char* const sSlotAErrorLine1[5] = {
    sSlotAErrorText1,
    sSlotAErrorText1,
    sSlotAErrorText1,
    sSlotAErrorText1,
    sSlotAErrorText1,
};
static const char* const sSlotAErrorLine2[5] = {
    sSlotAErrorText2,
    sSlotAErrorText2,
    sSlotAErrorText2,
    sSlotAErrorText2,
    sSlotAErrorText2,
};
static const char* const sSlotAErrorLine3[5] = {
    sSlotAErrorText3,
    sSlotAErrorText3,
    sSlotAErrorText3,
    sSlotAErrorText3,
    sSlotAErrorText3,
};
static const char* const sSlotAErrorLine4[5] = {
    sSlotAErrorText4,
    sSlotAErrorText4,
    sSlotAErrorText4,
    sSlotAErrorText4,
    sSlotAErrorText4,
};
static const char* const sSlotAErrorLine5[5] = {
    sSlotAErrorText5,
    sSlotAErrorText5,
    sSlotAErrorText5,
    sSlotAErrorText5,
    sSlotAErrorText5,
};
static const char sEmptyLine[] = "";
static const char sImportNeedsSaveLine1[] = "This game has not been saved.";
static const char sImportNeedsSaveLine2[] = "You must save your game before";
static const char sImportNeedsSaveLine3[] = "you can import a character.";
static const char sImportHasUnsavedLine1[] = "This game contains character data";
static const char sImportHasUnsavedLine2[] = "that has not yet been saved.";
static const char sTransferPromptLine1[] = "Please insert a Memory Card with";
static const char sTransferPromptLine2[] = "current game's data into Slot A.";
static const char sTransferPromptLine3[] = "Insert into Slot B a Memory Card";
static const char sTransferPromptLine4[] = "with the character data to be transferred.";
static const char sTransferPromptLine5[] = "Please do not remove either Memory Card";
static const char sTransferPromptLine6[] = "until the transfer is complete.";
static const char sImportConfirmLine1[] = "Are you sure you wish to import";
static const char sImportConfirmLine2[] = "the selected character into the";
static const char sImportConfirmLine3[] = "current game? The character will";
static const char sImportConfirmLine4[] = "be unavailable until returned.";
static const char sReturnConfirmLine1[] = "Are you sure you wish to return";
static const char sReturnConfirmLine2[] = "the selected character to the";
static const char sReturnConfirmLine3[] = "current game's";
static const char sReturnConfirmLine4[] = "guest data will be deleted.";
static const char sYesNoLine[] = "  Yes   No";
static const char sSavingLine1[] = "Saving data to the Memory";
static const char sSavingLine2[] = "Card in Slot B. Please do";
static const char sSavingLine3[] = "not touch the Memory Card";
static const char sSavingLine4[] = "or the POWER Button.";
static const char sCardRemovedLine1[] = "A Memory Card has been removed.";
static const char sCardRemovedLine2[] = "Cancelling character transfer.";
static const char sNoCardLine1[] = "No Memory Card found in";
static const char sNoCardSlotALine2[] = "Slot A.";
static const char sNoCardSlotBLine2[] = "Slot B.";
static const char sDeleteBlockedLine1[] = "This character cannot be deleted.";
static const char sDeleteBlockedLine2[] = "At least one non-guest character";
static const char sDeleteBlockedLine3[] = "must remain.";
static const char sDeletePromptLine1[] = "Delete this character?";
static const char sDeletedWarningLine1[] = "Deleted characters";
static const char sDeletedWarningLine2[] = "cannot be restored.";
static const char sDeletedWarningLine3[] = "Are you sure?";
static const char sDeletedMainLine1[] = "The character has been deleted.";
static const char sDeletedGuestLine1[] = "The guest character has been deleted.";
static const char sDeletedGuestLine2[] = "Please restore the character's";
static const char sDeletedGuestLine3[] = "original save data.";
static const char sDeletedGuestLine4[] = "To restore a character who is abroad,";
static const char sDeletedGuestLine5[] = "first select \"Delete Character\" and";
static const char sDeletedGuestLine6[] = "select the character you wish to restore.";
static const char sAbroadDeleteLine1[] = "This character is currently abroad";
static const char sAbroadDeleteLine2[] = "and cannot be deleted here. If you";
static const char sAbroadDeleteLine3[] = "wish to delete the character's";
static const char sAbroadDeleteLine4[] = "original data, you must first";
static const char sAbroadDeleteLine5[] = "restore it. Proceed?";
static const char sRestorePromptLine1[] = "This will restore the character";
static const char sRestorePromptLine2[] = "to the state it was in before transfer.";
static const char sRestorePromptLine3[] = "It will also prevent the transferred data";
static const char sRestorePromptLine4[] = "from returning to this save location.";
static const char sRestoredLine1[] = "The character has been restored.";

/*
 * --INFO--
 * PAL Address: 0x80168130
 * PAL Size: 676b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void DrawGoOutMenu()
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
    g_pGoOutMenu = &g_GoOutMenu;

    if (ReadGoOutU8(g_GoOutMenu, 0x44) == 3) {
        MenuPcs.DrawInit();
        MenuPcs.DrawCMakeMenu();
        if (ReadGoOutS16(g_GoOutMenu, 0x36) == 1 && MenuGoOutState(menuPcsLayout).m_resultSelect != 0) {
            MenuGoOutState(menuPcsLayout).m_closeMode = 8;
            g_GoOutMenu.SetMainMode(1);
            MenuGoOutState(menuPcsLayout).m_resultSelect = 0;
        }
    } else if (ReadGoOutU8(g_GoOutMenu, 0x44) == 2) {
        if (ReadGoOutU8(g_GoOutMenu, 0x29) != 0) {
            MenuPcs.DrawInit();
            MenuPcs.DrawCMakeMenu();
        }
        if (ReadGoOutS8(g_GoOutMenu, 0x24) > 0xD && ReadGoOutS8(g_GoOutMenu, 0x24) < 0xF) {
            MenuPcs.DrawLoadMenu();
        }
        if (ReadGoOutS8(g_GoOutMenu, 0x24) == 1 && MenuGoOutState(menuPcsLayout).m_resultSelect != 0) {
            MenuGoOutState(menuPcsLayout).m_closeMode = 8;
            g_GoOutMenu.SetMainMode(1);
            MenuGoOutState(menuPcsLayout).m_resultSelect = 0;
        }
    }

    if (ReadGoOutS16(g_GoOutMenu, 0x54) != -1) {
        MenuPcs.DrawMcWin(-1, 0);
        if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
            const int message = static_cast<int>(ReadGoOutS16(g_GoOutMenu, 0x54));
            MenuPcs.DrawMcWinMess(message, (message >= 0x1E) ? 2 : 0);
        }
    }

    if (MenuMcWinState(menuPcsLayout).m_mode == 1 && ReadGoOutU8(g_GoOutMenu, 0x71) != 0) {
        const int cursorY = MenuMcWinState(menuPcsLayout).m_y + MenuMcWinState(menuPcsLayout).m_height - 0x3E;

        if (ReadGoOutU8(g_GoOutMenu, 0x73) == 0) {
            const int cursorX = GetYesNoXPos__8CMenuPcsFi(&MenuPcs, ReadGoOutU8(g_GoOutMenu, 0x70));
            MenuPcs.DrawCursor(cursorX, cursorY, 1.0f);
        } else {
            const int cursorX = MenuMcWinState(menuPcsLayout).m_x + 0x20;
            const int localY = ReadGoOutS16(g_GoOutMenu, 0x76) + ReadGoOutU8(g_GoOutMenu, 0x70) * 0x1E;
            MenuPcs.DrawCursor(cursorX, localY, 1.0f);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void getFreeCaravanIdx(Mc::SaveDat*)
{
	// TODO
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CharaSelClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMemCardSlot(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMemCardProc(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMemCardSaveBuff(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::GetMemCardResult()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CalcMemCardProc()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8016c564
 * PAL Size: 1156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGoOutMenu::SetMemCardError()
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
    int result = 1;

    if (field_0x4 == -5) {
        MenuMcWinState(menuPcsLayout).m_mode = 3;
        MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        field_0x36 = -1;
        field_0x40 = 0;
        field_0x44 = 1;
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 3;
        field_0x48 = 0;
        field_0x3c = 0;
    } else if (field_0x4 < -5) {
        if (field_0x4 == -13 || field_0x4 == -6) {
            SetGoOutMode(3);
            return 1;
        }

        if ((field_0x4 == -999 || field_0x4 == -1000) && field_0x1 == 1) {
            MenuMcWinState(menuPcsLayout).m_mode = 3;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       sSlotAErrorLine1[languageId],
                       sSlotAErrorLine2[languageId],
                       sSlotAErrorLine3[languageId],
                       sSlotAErrorLine4[languageId],
                       sSlotAErrorLine5[languageId]);
        } else if (field_0x1 == 3) {
            MenuMcWinState(menuPcsLayout).m_mode = 3;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
            if (field_0x36 >= 0) {
                MenuMcWinState(menuPcsLayout).m_mode = 2;
                MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            }
            field_0x45 = 0;
            field_0x34 = 0xd;
            field_0x48 = 0;
            field_0x3c = 0;
        } else if (field_0x1 == 2) {
            MenuMcWinState(menuPcsLayout).m_mode = 3;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
            if (field_0x36 >= 0) {
                MenuMcWinState(menuPcsLayout).m_mode = 2;
                MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            }
            field_0x45 = 0;
            field_0x34 = 0xf;
            field_0x48 = 0;
            field_0x3c = 0;
        }
    } else if (field_0x4 == -1 || field_0x4 == -3) {
        MenuMcWinState(menuPcsLayout).m_mode = 3;
        MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        field_0x36 = -1;
        field_0x40 = 0;
        field_0x44 = 1;
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 1;
        field_0x48 = 0;
        field_0x3c = 0;
    } else if (field_0x4 == -2) {
        MenuMcWinState(menuPcsLayout).m_mode = 3;
        MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        field_0x36 = -1;
        field_0x40 = 0;
        field_0x44 = 1;
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 2;
        field_0x48 = 0;
        field_0x3c = 0;
    } else if (field_0x4 == -4) {
        if (field_0x1 != 1) {
            MenuMcWinState(menuPcsLayout).m_mode = 3;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
            if (field_0x36 >= 0) {
                MenuMcWinState(menuPcsLayout).m_mode = 2;
                MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            }
            field_0x45 = 0;
            field_0x34 = 0x13;
            field_0x48 = 0;
            field_0x3c = 0;
        } else {
            MenuMcWinState(menuPcsLayout).m_mode = 3;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       sSlotAErrorLine1[languageId],
                       sSlotAErrorLine2[languageId],
                       sSlotAErrorLine3[languageId],
                       sSlotAErrorLine4[languageId],
                       sSlotAErrorLine5[languageId]);
        }
    } else if (field_0x4 == 1) {
        result = 0;
    }

    field_0x18 = 2;
    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenu(short, long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenuStr(long timer, int lineCount, ...)
{
    va_list args;
    unsigned int leadingZeros;
    int indexBase;
    int i;
    int* winMessage;
    const char** winMessageBuffer;
    short messageIndex;

    field_0x38 ^= 1;
    winMessage = (int*)GetWinMess__8CMenuPcsFi(&MenuPcs, field_0x38 + 0x22);
    *winMessage = lineCount;

    va_start(args, lineCount);
    leadingZeros = (unsigned int)__cntlzw((unsigned int)field_0x38);
    indexBase = static_cast<int>(~-(leadingZeros >> 5 & 1U) & 10U);
    winMessageBuffer = (const char**)GetMcWinMessBuff__8CMenuPcsFi(&MenuPcs, 2);
    for (i = 0; i < lineCount; i++) {
        winMessageBuffer[indexBase + i] = va_arg(args, const char*);
    }
    va_end(args);

    messageIndex = field_0x38;
    if (field_0x36 >= 0) {
        CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
        MenuMcWinState(menuPcsLayout).m_mode = 2;
        MenuGoOutState(menuPcsLayout).m_animFrame = 0;
    }

    field_0x45 = 0;
    field_0x34 = messageIndex + 0x22;
    field_0x48 = 0;
    field_0x3c = timer;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CalcMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenuForceClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CalcLoadMenu()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8016c1a4
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::SetMainMode(unsigned char mode)
{
    unsigned char prevMainMode;
    int i;

    {
        CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
        menuPcsLayout.m_saveLoadMode = 0;
        menuPcsLayout.m_unknown_88A = 0;
        menuPcsLayout.m_transferWorkActive = 0;
    }
    if (field_0x2c == '\x02') {
        MemoryCardMan.McEnd();
    }
    prevMainMode = field_0x2c;
    field_0x2c = mode;
    field_0x30 = 0;
    switch (mode) {
    case 1: {
        field_0x46 = 1;
        if (prevMainMode != '\x03') {
            field_0x46 = 0;
        }
        MenuPcs.ChgAllModel();
        CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 0x1e;
        field_0x48 = 0;
        field_0x3c = 0;
        field_0x14 = 0;
        break;
    }
    case 2:
        if (Game.m_gameWork.m_mcHasSerial != 1) {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 5),
                       GetGoOutMessageLine(languageId, 6),
                       GetGoOutMessageLine(languageId, 7),
                       GetGoOutMessageLine(languageId, 8));
            field_0x19 = (char)0xff;
            field_0x18 = 0;
        }
        i = 0;
        do {
            if (Game.m_caravanWorkArr[i].m_shopState != 0 &&
                Game.m_caravanWorkArr[i].m_caravanLocalFlags != 1) {
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 5,
                           GetGoOutMessageLine(languageId, 9),
                           GetGoOutMessageLine(languageId, 10),
                           GetGoOutMessageLine(languageId, 11),
                           GetGoOutMessageLine(languageId, 12),
                           GetGoOutMessageLine(languageId, 13));
                field_0x19 = (char)0xff;
                field_0x18 = 0;
            }
            i++;
        } while (i < 8);
        field_0x1 = 0;
        field_0x0 = 0;
        field_0x2 = 0;
        field_0x3 = 0;
        field_0x4 = -1;
        field_0x8 = 0;
        SetGoOutMode(7);
        break;
    case 3: {
        MenuPcs.ChgAllModel();
        CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
        menuPcsLayout.m_unknown_888 = 2;
        field_0x14 = 0;
        field_0x24[2] = 0;
        SetDelMode(2);
        break;
    }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SelectYesNo(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::InitSelectYesNo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::HitAnyKey()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::HitCanncel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8016b8d4
 * PAL Size: 2256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void CGoOutMenu::SetGoOutMode(unsigned char mode)
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
    McCtrl& mcCtrl = menuPcsLayout.m_mcCtrl;

	field_0x18 = mode;
	switch(field_0x18) {
	case 1:
		field_0x1c = 0;
        MenuGoOutState(menuPcsLayout).m_resultDir = -1;
        MenuGoOutState(menuPcsLayout).m_waitFrames = 10;
		break;
	case 3:
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
		field_0x45 = 0;
		field_0x34 = 4;
		field_0x48 = 0;
		field_0x3c = 0;
		field_0x46 = 1;
		break;
	case 4:
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
		field_0x45 = 0;
		field_0x34 = 5;
		field_0x48 = 0;
		field_0x3c = 0;
		field_0x46 = 1;
		break;
    case 5:
        field_0x4 = mcCtrl.ChkConnect(static_cast<unsigned char>(field_0x2));
        if (field_0x4 == 1) {
            mcCtrl.m_saveIndex = static_cast<unsigned char>(field_0x3);
            mcCtrl.m_cardChannel = static_cast<unsigned char>(field_0x2);
            mcCtrl.m_previousState = 0;
            mcCtrl.m_state = 0;
            mcCtrl.m_lastResult = 0;
            mcCtrl.m_iteration = 0;
            mcCtrl.m_userBuffer = 0;
            mcCtrl.m_createFlag = 0;
            field_0x1 = 3;
        }
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 7;
        field_0x48 = 0;
        field_0x3c = 0;
        break;
    case 6:
        if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
            MenuMcWinState(menuPcsLayout).m_mode = 3;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
        }
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 0xc;
        field_0x48 = 0;
        field_0x3c = 0;
        field_0x46 = 1;
        break;
    case 7:
        menuPcsLayout.m_unknown_888 = 1;
        field_0x14 = 0;
        field_0x18 = 7;
        field_0x1c = 0;
        field_0x1d = 0;
        SetMenuStr(0, 7, sTransferPromptLine1, sTransferPromptLine2, sTransferPromptLine3,
                   sTransferPromptLine4, sEmptyLine, sTransferPromptLine5, sTransferPromptLine6);
        break;
    case 0xC:
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 0x21;
        field_0x48 = 0;
        field_0x3c = 0;
        MenuPcs.GetMcAccessPos(&field_0xc, &field_0x10);
        field_0xc = 0;
        mcCtrl.m_cardChannel = field_0xc;
        field_0x2 = static_cast<char>(mcCtrl.m_cardChannel);
        field_0x3 = static_cast<char>(field_0x10);
        field_0x4 = mcCtrl.ChkConnect(static_cast<unsigned char>(field_0x2));
        if (field_0x4 == 1) {
            mcCtrl.m_saveIndex = static_cast<unsigned char>(field_0x3);
            mcCtrl.m_cardChannel = static_cast<unsigned char>(field_0x2);
            mcCtrl.m_previousState = 0;
            mcCtrl.m_state = 0;
            mcCtrl.m_lastResult = 0;
            mcCtrl.m_iteration = 0;
            mcCtrl.m_userBuffer = 0;
            mcCtrl.m_createFlag = 0;
            field_0x1 = 1;
        }
        break;
    case 0xE:
        MenuPcs.InitSaveLoadMenu();
        MenuPcs.SetMenuCharaAnim(0, 0);
        MenuPcs.CopyNowCaravanDat(menuPcsLayout.m_transferSaveData);
        menuPcsLayout.m_saveLoadMode = 2;
        menuPcsLayout.m_unknown_88A = 1;
        menuPcsLayout.m_transferWorkActive = menuPcsLayout.m_transferWork;
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = -1;
        field_0x48 = 0;
        field_0x3c = 0;
        break;
    case 0xF:
        MenuPcs.ChgAllModel2();
        if (field_0x1d == 0) {
            MenuPcs.InitSaveLoadMenu();
        }
        MenuPcs.SetMenuCharaAnim(0, 0);
        field_0x1d = 1;
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = -1;
        field_0x48 = 0;
        field_0x3c = 0;
        menuPcsLayout.m_saveLoadMode = 2;
        menuPcsLayout.m_unknown_88A = 1;
        menuPcsLayout.m_transferWorkActive = menuPcsLayout.m_transferWork;
        break;
    case 0x10:
        if (field_0x1e == 0) {
            SetMenuStr(0, 5, sImportConfirmLine1, sImportConfirmLine2, sImportConfirmLine3,
                       sImportConfirmLine4, sYesNoLine);
        } else {
            SetMenuStr(0, 5, sReturnConfirmLine1, sReturnConfirmLine2, sReturnConfirmLine3,
                       sReturnConfirmLine4, sYesNoLine);
        }
        field_0x46 = 1;
        break;
    case 0x11:
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 0x1F;
        field_0x48 = 0;
        field_0x3c = 0;
        field_0x46 = 1;
        break;
    case 0x13:
        mcCtrl.m_cardChannel = static_cast<unsigned char>(field_0x1a);
        field_0x2 = field_0x1a;
        field_0x3 = field_0x1b;
        field_0x8 = reinterpret_cast<int>(menuPcsLayout.m_transferWork);
        field_0x4 = mcCtrl.ChkConnect(static_cast<unsigned char>(field_0x2));
        if (field_0x4 == 1) {
            mcCtrl.m_saveIndex = static_cast<unsigned char>(field_0x3);
            mcCtrl.m_cardChannel = static_cast<unsigned char>(field_0x2);
            mcCtrl.m_previousState = 0;
            mcCtrl.m_state = 0;
            mcCtrl.m_lastResult = 0;
            mcCtrl.m_iteration = 0;
            mcCtrl.m_userBuffer = 0;
            mcCtrl.m_createFlag = 0;
            field_0x1 = 2;
        }
        SetMenuStr(0, 4, sSavingLine1, sSavingLine2, sSavingLine3, sSavingLine4);
        break;
    case 0x14:
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 0x20;
        field_0x48 = 0;
        field_0x3c = 0;
        break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8016a06c
 * PAL Size: 6248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::CalcGoOut()
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
    McCtrl& mcCtrl = menuPcsLayout.m_mcCtrl;
    unsigned short input;
    unsigned char next;

    if (field_0x1c != 0 && field_0x30 > 0x13 && (field_0x30 & 0xF) == 0) {
        const int cardStatus = ((field_0x30 & 0x10) == 0) ? mcCtrl.ChkConnect(1) : mcCtrl.ChkConnect(0);
        if (cardStatus != 1) {
            field_0x1c = 0;
            field_0x19 = -1;
            field_0x18 = 0;
            MenuMcWinState(menuPcsLayout).m_mode = 3;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
            SetMenuStr(0, 5, sCardRemovedLine1, sCardRemovedLine2, sEmptyLine, sTransferPromptLine5,
                       sTransferPromptLine6);
            return;
        }
    }

    if (field_0x1d != 0) {
        const unsigned char selInit = static_cast<unsigned char>(__cntlzw(0xF - static_cast<int>(field_0x18)) >> 5 & 0xFF);
        CalcGoOutSelChar__8CMenuPcsFUcUc(&MenuPcs, selInit, 1);
    }

    switch (field_0x18) {
    case 0:
        if (field_0x45 == 0) {
            break;
        }

        input = GetGoOutInputMask();
        if ((input & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7f, 0);
            if (field_0x19 == -1) {
                SetMainMode(1);
            } else {
                SetGoOutMode(field_0x19);
            }
        }
        break;
    case 2:
        if (field_0x45 == 0) {
            break;
        }

        input = GetGoOutInputMask();
        if ((input & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7f, 0);
            SetMainMode(1);
        }
        break;
    case 3:
        if (field_0x45 == 0) {
            break;
        }

        field_0x47 = 1;
        field74_0x4a = 0xcf;
        field75_0x4c = 0xe7;
        field_0x49 = 0;
        next = 0;

        if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
            input = GetGoOutInputMask();
            if ((input & 3) == 0) {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (field_0x46 == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (field_0x46 == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }

                    next = static_cast<unsigned char>(field_0x46 + 1);
                }
            } else {
                field_0x46 ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            }
        }

        if (next == 2) {
            SetMainMode(1);
        } else if (next == 1) {
            SetGoOutMode(4);
        }
        break;
    case 4:
        if (field_0x45 == 0) {
            break;
        }

        field_0x47 = 1;
        field74_0x4a = 0xce;
        field75_0x4c = 0xde;
        field_0x49 = 0;
        next = 0;

        if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
            input = GetGoOutInputMask();
            if ((input & 3) == 0) {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (field_0x46 == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (field_0x46 == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }

                    next = static_cast<unsigned char>(field_0x46 + 1);
                }
            } else {
                field_0x46 ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            }
        }

        if (next == 2) {
            SetMainMode(1);
        } else if (next == 1) {
            SetGoOutMode(5);
        }
        break;
    case 5:
        if (field_0x45 == 0 || field_0x4 == 0) {
            break;
        }

        if (SetMemCardError() != 0) {
            return;
        }
        SetGoOutMode(6);
        break;
    case 6:
        if (field_0x45 == 0) {
            break;
        }

        input = GetGoOutInputMask();
        if ((input & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7f, 0);
            SetMainMode(1);
        }
        break;
    case 7:
        if (field_0x45 == 0) {
            break;
        }

        input = GetGoOutInputMask();
        if ((input & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7f, 0);
            SetGoOutMode(8);
        }
        break;
    case 8:
        if (mcCtrl.ChkConnect(0) == -1) {
            return;
        }
        field_0x30 = 0;
        SetGoOutMode(9);
        break;
    case 9:
        if (field_0x30 < 0x14) {
            return;
        }
        if (mcCtrl.ChkConnect(0) == -3) {
            SetMenuStr(0, 2, sNoCardLine1, sNoCardSlotALine2);
            field_0x19 = -1;
            SetGoOutMode(0);
            return;
        }
        SetGoOutMode(0xC);
        break;
    case 10:
        if (mcCtrl.ChkConnect(1) == -1) {
            return;
        }
        field_0x30 = 0;
        SetGoOutMode(0xB);
        break;
    case 0xB:
        if (field_0x30 < 0x14) {
            return;
        }
        if (mcCtrl.ChkConnect(1) == -3) {
            SetMenuStr(0, 2, sNoCardLine1, sNoCardSlotBLine2);
            field_0x19 = -1;
            SetGoOutMode(0);
            return;
        }
        SetGoOutMode(0xE);
        break;
    default:
        break;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawGoOut()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80169c18
 * PAL Size: 1108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::SetDelMode(unsigned char mode)
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
    signed char& delMode = reinterpret_cast<signed char&>(field_0x24[0]);
    signed char& initSelChar = reinterpret_cast<signed char&>(field_0x24[2]);
    int& selectedChara = *reinterpret_cast<int*>(&field_0x24[4]);

    delMode = mode;
    switch (delMode) {
    case 1:
        MenuGoOutState(menuPcsLayout).m_resultDir = -1;
        MenuGoOutState(menuPcsLayout).m_waitFrames = 10;
        break;
    case 2:
        field_0x45 = 0;
        field_0x34 = -1;
        field_0x48 = 0;
        field_0x3c = 0;
        field_0x40 = 0;
        if (initSelChar == 0) {
            MenuPcs.InitSaveLoadMenu();
        }
        MenuPcs.SetMenuCharaAnim(selectedChara, 0);
        initSelChar = 1;
        break;
    case 3: {
        if (Game.m_caravanWorkArr[selectedChara].m_caravanLocalFlags == 0) {
            int activeMainCharacterCount = 0;
            for (int i = 0; i < 8; i++) {
                const CCaravanWork& caravanWork = Game.m_caravanWorkArr[i];
                if (caravanWork.m_objType != 0 && caravanWork.m_caravanLocalFlags == 0) {
                    activeMainCharacterCount++;
                }
            }

            if (activeMainCharacterCount < 2) {
                SetMenuStr(0, 4, sDeleteBlockedLine1, sEmptyLine, sDeleteBlockedLine2,
                           sDeleteBlockedLine3);
                reinterpret_cast<signed char&>(field_0x24[1]) = 2;
                SetDelMode(0);
                return;
            }
        }

        SetMenuStr(0, 2, sDeletePromptLine1, sYesNoLine);
        field_0x46 = 1;
        break;
    }
    case 4:
        SetMenuStr(0, 4, sDeletedWarningLine1, sDeletedWarningLine2, sDeletedWarningLine3,
                   sYesNoLine);
        field_0x46 = 1;
        break;
    case 5:
        if (Game.m_caravanWorkArr[selectedChara].m_caravanLocalFlags == 0) {
            SetMenuStr(0, 1, sDeletedMainLine1);
        } else {
            SetMenuStr(0, 8, sDeletedGuestLine1, sEmptyLine, sDeletedGuestLine2, sDeletedGuestLine3,
                       sEmptyLine, sDeletedGuestLine4, sDeletedGuestLine5, sDeletedGuestLine6);
        }
        field_0x46 = 1;
        MenuPcs.SetMenuCharaAnim(selectedChara, 5);
        break;
    case 6:
        SetMenuStr(0, 6, sAbroadDeleteLine1, sAbroadDeleteLine2, sAbroadDeleteLine3,
                   sAbroadDeleteLine4, sAbroadDeleteLine5, sYesNoLine);
        field_0x46 = 1;
        break;
    case 7:
        SetMenuStr(0, 5, sRestorePromptLine1, sRestorePromptLine2, sRestorePromptLine3,
                   sRestorePromptLine4, sYesNoLine);
        field_0x46 = 1;
        break;
    case 8:
        MenuPcs.SetMenuCharaAnim(selectedChara, 3);
        SetMenuStr(0, 1, sRestoredLine1);
        break;
    default:
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80168e3c
 * PAL Size: 3548b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::CalcDel()
{
    signed char& delMode = reinterpret_cast<signed char&>(field_0x24[0]);
    signed char& prevMode = reinterpret_cast<signed char&>(field_0x24[1]);
    int& selectedChara = *reinterpret_cast<int*>(&field_0x24[4]);
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    const unsigned char selInit = static_cast<unsigned char>(__cntlzw(2 - static_cast<int>(delMode)) >> 5 & 0xFF);
    const int selResult = CalcGoOutSelChar__8CMenuPcsFUcUc(&MenuPcs, selInit, 0);
    unsigned short input;
    unsigned char next;

    switch (delMode) {
    case 0:
        if (field_0x45 != 0) {
            input = GetGoOutInputMask();
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                if (prevMode == -1) {
                    SetMainMode(1);
                } else {
                    SetDelMode(prevMode);
                }
            }
        }
        break;
    case 2:
        selectedChara = selResult;
        if (selectedChara == -2) {
            SetDelMode(1);
        } else if (selectedChara != -1) {
            if (Game.m_caravanWorkArr[selectedChara].m_shopBusyFlag == 0) {
                SetDelMode(3);
            } else {
                SetDelMode(6);
            }
        }
        break;
    case 3:
        if (field_0x45 == 0) {
            return;
        }

        input = GetGoOutInputMask();
        if ((input & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7f, 0);
            SetDelMode(2);
        }

        field_0x47 = 1;
        field74_0x4a = 0xad;
        field75_0x4c = 0xbc;
        field_0x49 = 0;
        next = 0;

        if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
            input = GetGoOutInputMask();
            if ((input & 3) == 0) {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (field_0x46 == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (field_0x46 == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(field_0x46 + 1);
                }
            } else {
                field_0x46 ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            }
        }

        if (next == 2) {
            SetDelMode(2);
        } else if (next == 1) {
            SetDelMode(4);
        }
        break;
    case 4:
        if (field_0x45 == 0) {
            return;
        }

        input = GetGoOutInputMask();
        if ((input & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7f, 0);
            SetDelMode(2);
        }

        field_0x47 = 1;
        field74_0x4a = 0xc2;
        field75_0x4c = 0xd1;
        field_0x49 = 0;
        next = 0;

        if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
            input = GetGoOutInputMask();
            if ((input & 3) == 0) {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (field_0x46 == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (field_0x46 == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(field_0x46 + 1);
                }
            } else {
                field_0x46 ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            }
        }

        if (next == 2) {
            SetDelMode(2);
        } else if (next == 1) {
            SetDelMode(5);
        }
        break;
    case 5:
        if (field_0x45 != 0 && MenuPcs.IsMenuCharaAnimIdle(selectedChara) != 0) {
            input = GetGoOutInputMask();
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                CCaravanWork& caravanWork = Game.m_caravanWorkArr[selectedChara];
                caravanWork.m_shopState = 0;
                memset(reinterpret_cast<unsigned char*>(&caravanWork) + 0x9A4, 0, 0x100);
                memset(reinterpret_cast<unsigned char*>(&caravanWork) + 0xAA4, 0, 0x200);
                SetDelMode(1);
            }
        }
        break;
    case 6:
        if (field_0x45 == 0) {
            return;
        }

        input = GetGoOutInputMask();
        if ((input & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7f, 0);
            SetDelMode(2);
        }

        field_0x47 = 1;
        field74_0x4a = 0x97;
        field75_0x4c = 0xe9;
        field_0x49 = 0;
        next = 0;

        if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
            input = GetGoOutInputMask();
            if ((input & 3) == 0) {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (field_0x46 == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (field_0x46 == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(field_0x46 + 1);
                }
            } else {
                field_0x46 ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            }
        }

        if (next == 2) {
            SetDelMode(2);
        } else if (next == 1) {
            SetDelMode(7);
        }
        break;
    case 7:
        if (field_0x45 == 0) {
            return;
        }

        input = GetGoOutInputMask();
        if ((input & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7f, 0);
            SetDelMode(2);
        }

        field_0x47 = 1;
        field74_0x4a = 0x9f;
        field75_0x4c = 0xdb;
        field_0x49 = 0;
        next = 0;

        if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
            input = GetGoOutInputMask();
            if ((input & 3) == 0) {
                input = GetGoOutInputMask();
                if ((input & 0x100) != 0) {
                    if (field_0x46 == 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                    } else if (field_0x46 == 1) {
                        Sound.PlaySe(3, 0x40, 0x7f, 0);
                    }
                    next = static_cast<unsigned char>(field_0x46 + 1);
                }
            } else {
                field_0x46 ^= 1;
                Sound.PlaySe(1, 0x40, 0x7f, 0);
            }
        }

        if (next == 2) {
            SetDelMode(2);
        } else if (next == 1) {
            Game.m_caravanWorkArr[selectedChara].m_shopBusyFlag = 0;
            SetDelMode(8);
        }
        break;
    case 8:
        if (field_0x45 != 0 && MenuPcs.IsMenuCharaAnimIdle(selectedChara) != 0) {
            input = GetGoOutInputMask();
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                SetDelMode(1);
            }
        }
        break;
    default:
        break;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawDel()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80168400
 * PAL Size: 2620b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGoOutMenu::Calc()
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
    unsigned short input;
    char mode;

    field_0x47 = 0;

    if (menuPcsLayout.m_resetGoOutFlag != 0) {
        menuPcsLayout.m_resetGoOutFlag = 0;
        MenuMcWinState(menuPcsLayout).m_mode = 3;
        field_0x36 = -1;
        field_0x34 = -1;
        field_0x38 = 0;
        SetMainMode(1);
        field_0x44 = 1;
    }

    if (field_0x48 == 0) {
        mode = field_0x2c;
        if (mode == 2) {
            CalcGoOut();
        } else if (mode < 2) {
            if (mode == 0) {
                if (field_0x45 != 0) {
                    input = GetGoOutInputMask();
                    if ((input & 0x100) != 0) {
                        Sound.PlaySe(2, 0x40, 0x7f, 0);
                        SetMainMode(field_0x2d);
                    }
                }
            } else if (field_0x45 != 0) {
                input = GetGoOutInputMask();
                if ((input & 0x200) != 0) {
                    Sound.PlaySe(3, 0x40, 0x7f, 0);
                    MenuPcs.InitSaveLoadMenu();
                    MenuPcs.SetMenuCharaAnim(0, 0);
                    MenuGoOutState(menuPcsLayout).m_resultSelect = -1;

                    if (menuPcsLayout.m_transferSaveData != 0) {
                        __dl__FPv(menuPcsLayout.m_transferSaveData);
                        menuPcsLayout.m_transferSaveData = 0;
                    }
                    if (menuPcsLayout.m_transferWork != 0) {
                        __dl__FPv(menuPcsLayout.m_transferWork);
                        menuPcsLayout.m_transferWork = 0;
                    }

                    menuPcsLayout.m_transferWorkActive = 0;
                    menuPcsLayout.m_unknown_888 = 0;
                    menuPcsLayout.m_saveLoadMode = 0;
                    menuPcsLayout.m_unknown_88A = 0;
                    menuPcsLayout.m_resetGoOutFlag = 1;
                    MenuPcs.ChgAllModel();
                    return;
                }
                field_0x47 = 1;
                field74_0x4a = 200;
                field75_0x4c = 0xB0;
                field_0x49 = 1;
            }
        } else if (mode < 4) {
            CalcDel();
        }

        field_0x30 = field_0x30 + 1;
        if (10000 < field_0x30) {
            field_0x30 = 10000;
        }
    }

    if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
        field_0x44 = 1;
        field_0x45 = 1;
    }

    if (field_0x44 != 0 && MenuMcWinState(menuPcsLayout).m_mode == 3) {
        short x;
        short y;

        field_0x36 = field_0x34;
        if (field_0x34 == -1) {
            field_0x44 = 1;
        } else {
            MenuPcs.GetWinSize(static_cast<unsigned short>(field_0x36), &x, &y, (field_0x36 >= 0x1E) ? 2 : 0);
            MenuPcs.SetMcWinInfo(x, y);
            MenuMcWinState(menuPcsLayout).m_mode = 0;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            field_0x40 = field_0x3c;
            field_0x44 = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801683d4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CalcGoOutMenu()
{
    g_pGoOutMenu = &g_GoOutMenu;
    Calc__10CGoOutMenuFv(&g_GoOutMenu);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawSelectYesNo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::Draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::InitMemCardProc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::EndMemCardProc()
{
	// TODO
}
