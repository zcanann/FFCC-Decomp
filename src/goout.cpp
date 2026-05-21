#include "ffcc/goout.h"
#include "ffcc/memory.h"
#include "ffcc/wm_menu.h"
#include <stdarg.h>
#include <string.h>

CGoOutMenu g_GoOutMenu;
CGoOutMenu* g_pGoOutMenu;
int g_freeCaravanIdx;

extern "C" int GetYesNoXPos__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int CalcGoOutSelChar__8CMenuPcsFUcUc(CMenuPcs*, unsigned char, unsigned char);
extern "C" void Calc__10CGoOutMenuFv(CGoOutMenu*);
extern "C" int GetWinMess__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* const* GetMcWinMessBuff__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* g_strGooutMes[];

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

struct CGoOutSaveCaravan
{
    int m_dataPresent;
    unsigned char unk4[0x309];
    char m_odekakeReturnFlag;
    unsigned char unk30E[0x6B2];
};

struct CGoOutSaveDatLayout
{
    unsigned char unk0[0x1A84];
    CGoOutSaveCaravan m_caravan[8];
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

static inline unsigned short GetGoOutInputMask()
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
    return g_strGooutMes[(languageId * 0x6E) + line];
}

static const char s_gooutCpp[] = "goout.cpp";

static inline CGoOutSaveDatLayout& GoOutSaveDat(Mc::SaveDat* saveData)
{
    return *reinterpret_cast<CGoOutSaveDatLayout*>(saveData);
}

static inline int FindFreeCaravanIdx(Mc::SaveDat* saveData)
{
    for (int i = 0; i < 8; i++) {
        if (GoOutSaveDat(saveData).m_caravan[i].m_dataPresent == 0) {
            return i;
        }
    }

    return -1;
}

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
    CGoOutMenu& goOutMenu = g_GoOutMenu;
    g_pGoOutMenu = &goOutMenu;
    signed char mode = ReadGoOutS8(goOutMenu, 0x2C);

    if (mode != 3) {
        if (mode < 3 && mode > 1) {
            if (ReadGoOutU8(goOutMenu, 0x1D) != 0) {
                MenuPcs.DrawInit();
                MenuPcs.DrawCMakeMenu();
            }
            if (ReadGoOutS8(goOutMenu, 0x18) > 0xD && ReadGoOutS8(goOutMenu, 0x18) < 0xF) {
                MenuPcs.DrawLoadMenu();
            }
            if (ReadGoOutU8(goOutMenu, 0x18) == 1 &&
                MenuGoOutState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_resultSelect != 0) {
                MenuGoOutState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_closeMode = 8;
                goOutMenu.SetMainMode(1);
                MenuGoOutState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_resultSelect = 0;
            }
        }
    } else {
        MenuPcs.DrawInit();
        MenuPcs.DrawCMakeMenu();
        if (ReadGoOutU8(goOutMenu, 0x24) == 1 &&
            MenuGoOutState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_resultSelect != 0) {
            MenuGoOutState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_closeMode = 8;
            goOutMenu.SetMainMode(1);
            MenuGoOutState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_resultSelect = 0;
        }
    }

    if (ReadGoOutS16(goOutMenu, 0x36) != -1) {
        MenuPcs.DrawMcWin(-1, 0);
        if (MenuMcWinState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_mode == 1) {
            const int message = static_cast<int>(ReadGoOutS16(goOutMenu, 0x36));
            MenuPcs.DrawMcWinMess(message, (message >= 0x1E) ? 2 : 0);
        }
    }

    if (MenuMcWinState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_mode == 1 && ReadGoOutU8(goOutMenu, 0x47) != 0) {
        const float cursorY = (float)(MenuMcWinState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_y +
            MenuMcWinState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_height - 0x3E);
        const float cursorX = (float)(MenuMcWinState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_x + 0x20);
        const unsigned char cursorMode = ReadGoOutU8(goOutMenu, 0x49);

        if (cursorMode == 0) {
            const int cursorX = GetYesNoXPos__8CMenuPcsFi(&MenuPcs, ReadGoOutU8(goOutMenu, 0x46));
            MenuPcs.DrawCursor(cursorX, (int)cursorY, 1.0f);
        } else {
            const int localY = ReadGoOutS16(goOutMenu, 0x4C) + ReadGoOutU8(goOutMenu, 0x46) * 0x1E;
            MenuPcs.DrawCursor((int)cursorX, localY, 1.0f);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int getFreeCaravanIdx(Mc::SaveDat* saveData)
{
    g_freeCaravanIdx = FindFreeCaravanIdx(saveData);
    return g_freeCaravanIdx;
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
                       GetGoOutMessageLine(languageId, 0),
                       GetGoOutMessageLine(languageId, 1),
                       GetGoOutMessageLine(languageId, 2),
                       GetGoOutMessageLine(languageId, 3),
                       GetGoOutMessageLine(languageId, 4));
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
                       GetGoOutMessageLine(languageId, 0),
                       GetGoOutMessageLine(languageId, 1),
                       GetGoOutMessageLine(languageId, 2),
                       GetGoOutMessageLine(languageId, 3),
                       GetGoOutMessageLine(languageId, 4));
        }
    } else if (field_0x4 == 1) {
        return 0;
    }

    field_0x18 = 2;
    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenu(short message, long timer)
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    if (field_0x36 >= 0) {
        MenuMcWinState(menuPcsLayout).m_mode = 2;
        MenuGoOutState(menuPcsLayout).m_animFrame = 0;
    }

    field_0x44 = 1;
    field_0x45 = 0;
    field_0x34 = message;
    field_0x48 = 0;
    field_0x3c = static_cast<int>(timer);
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
    int i;
    int indexBase;
    int mask;
    int* winMessage;
    const char** winMessageBuffer;
    short messageIndex;

    field_0x38 ^= 1;
    winMessage = (int*)GetWinMess__8CMenuPcsFi(&MenuPcs, field_0x38 + 0x22);
    *winMessage = lineCount;

    leadingZeros = (unsigned int)__cntlzw((unsigned int)field_0x38);
    mask = -static_cast<int>(leadingZeros >> 5 & 1U);
    indexBase = 10;
    indexBase &= ~mask;
    va_start(args, lineCount);
    winMessageBuffer = (const char**)GetMcWinMessBuff__8CMenuPcsFi(&MenuPcs, 2);
    for (i = 0; i < lineCount; i++) {
        winMessageBuffer[indexBase + i] = va_arg(args, const char*);
    }
    va_end(args);

    messageIndex = field_0x38 + 0x22;
    if (field_0x36 >= 0) {
        MenuMcWinState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_mode = 2;
        MenuGoOutState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_animFrame = 0;
    }

    field_0x45 = 0;
    field_0x34 = messageIndex;
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
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
        field_0x44 = 1;
        field_0x45 = 1;
    }

    if (field_0x44 != 0 && MenuMcWinState(menuPcsLayout).m_mode == 3) {
        short x;
        short y;

        field_0x36 = field_0x34;
        if (field_0x34 != -1) {
            MenuPcs.GetWinSize(static_cast<unsigned short>(field_0x36), &x, &y,
                               (field_0x36 >= 0x1E) ? 2 : 0);
            MenuPcs.SetMcWinInfo(x, y);
            MenuMcWinState(menuPcsLayout).m_mode = 0;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            field_0x40 = field_0x3c;
            field_0x44 = 0;
        }
    }

    if (field_0x40 != 0) {
        field_0x40--;
        if (field_0x40 == 0) {
            SetMenuForceClose();
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawMenu()
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    if (ReadGoOutS16(*this, 0x36) != -1) {
        MenuPcs.DrawMcWin(-1, 0);
        if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
            const int message = static_cast<int>(ReadGoOutS16(*this, 0x36));
            MenuPcs.DrawMcWinMess(message, (message >= 0x1E) ? 2 : 0);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMenuForceClose()
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    if (field_0x36 >= 0) {
        MenuMcWinState(menuPcsLayout).m_mode = 2;
        MenuGoOutState(menuPcsLayout).m_animFrame = 0;
    }

    field_0x45 = 0;
    field_0x34 = -1;
    field_0x48 = 0;
    field_0x3c = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CalcLoadMenu()
{
    CalcMenu();
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
        if (prevMainMode != 3U) {
            field_0x46 = 0;
        }
        MenuPcs.ChgAllModel();
        if (field_0x36 >= 0) {
            MenuMcWinState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_mode = 2;
            MenuGoOutState(*reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs)).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = 0x1e;
        field_0x48 = 0;
        field_0x3c = 0;
        field_0x14 = 0;
        break;
    }
    case 2:
        if (static_cast<signed char>(Game.m_gameWork.m_mcHasSerial) != 1) {
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
                static_cast<signed char>(Game.m_caravanWorkArr[i].unk_0xc1e) != 1) {
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
    memset(this, 0, sizeof(*this));
    field_0x4 = -1;
    field_0x19 = -1;
    field_0x34 = -1;
    field_0x36 = -1;
    field_0x38 = 0;
    field_0x44 = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::Destroy()
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    if (menuPcsLayout.m_transferSaveData != 0) {
        delete[] reinterpret_cast<unsigned char*>(menuPcsLayout.m_transferSaveData);
        menuPcsLayout.m_transferSaveData = 0;
    }
    if (menuPcsLayout.m_transferWork != 0) {
        delete[] static_cast<unsigned char*>(menuPcsLayout.m_transferWork);
        menuPcsLayout.m_transferWork = 0;
    }

    menuPcsLayout.m_transferWorkActive = 0;
    menuPcsLayout.m_unknown_888 = 0;
    menuPcsLayout.m_saveLoadMode = 0;
    menuPcsLayout.m_unknown_88A = 0;

    if (field_0x2c == 2) {
        MemoryCardMan.McEnd();
    }
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
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 7,
                       GetGoOutMessageLine(languageId, 14),
                       GetGoOutMessageLine(languageId, 15),
                       GetGoOutMessageLine(languageId, 16),
                       GetGoOutMessageLine(languageId, 17),
                       GetGoOutMessageLine(languageId, 18),
                       GetGoOutMessageLine(languageId, 19),
                       GetGoOutMessageLine(languageId, 20));
        }
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
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 21),
                       GetGoOutMessageLine(languageId, 22),
                       GetGoOutMessageLine(languageId, 23),
                       GetGoOutMessageLine(languageId, 24),
                       GetGoOutMessageLine(languageId, 25));
        } else {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 26),
                       GetGoOutMessageLine(languageId, 27),
                       GetGoOutMessageLine(languageId, 28),
                       GetGoOutMessageLine(languageId, 29),
                       GetGoOutMessageLine(languageId, 30));
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
    case 0x12: {
        field_0x1c = 0;
        Mc::SaveDat* const transferWork = static_cast<Mc::SaveDat*>(menuPcsLayout.m_transferWork);
        Mc::SaveDat* const transferSaveData = menuPcsLayout.m_transferSaveData;
        int freeCaravanIdx;

        if (GoOutSaveDat(transferWork).m_caravan[field_0x20].m_odekakeReturnFlag == 0) {
            freeCaravanIdx = FindFreeCaravanIdx(transferSaveData);
            MemoryCardMan.Odekake(1, *transferWork, field_0x20, *transferSaveData, freeCaravanIdx);
        } else {
            freeCaravanIdx = MenuPcs.GetSameCharaData(transferSaveData, transferWork, field_0x20, 0);
            MemoryCardMan.Odekake(0, *transferWork, field_0x20, *transferSaveData, freeCaravanIdx);
        }

        mcCtrl.m_cardChannel = field_0xc;
        field_0x2 = static_cast<char>(mcCtrl.m_cardChannel);
        field_0x3 = static_cast<char>(field_0x10);
        field_0x8 = reinterpret_cast<int>(transferSaveData);
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
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 31),
                       GetGoOutMessageLine(languageId, 32),
                       GetGoOutMessageLine(languageId, 33),
                       GetGoOutMessageLine(languageId, 34));
        }
        break;
    }
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
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 35),
                       GetGoOutMessageLine(languageId, 36),
                       GetGoOutMessageLine(languageId, 37),
                       GetGoOutMessageLine(languageId, 38));
        }
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
            {
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 5,
                           GetGoOutMessageLine(languageId, 39),
                           GetGoOutMessageLine(languageId, 40),
                           GetGoOutMessageLine(languageId, 41),
                           GetGoOutMessageLine(languageId, 42),
                           GetGoOutMessageLine(languageId, 43));
            }
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
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 2,
                       GetGoOutMessageLine(languageId, 44),
                       GetGoOutMessageLine(languageId, 45));
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
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 2,
                       GetGoOutMessageLine(languageId, 46),
                       GetGoOutMessageLine(languageId, 47));
            field_0x19 = -1;
            SetGoOutMode(0);
            return;
        }
        SetGoOutMode(0xE);
        break;
    case 0xC:
        if (field_0x4 != 0) {
            if (SetMemCardError() != 0) {
                return;
            }

            MenuPcs.GetMcAccessPos(&field_0xc, &field_0x10);
            if (field_0xc == -1) {
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 5,
                           GetGoOutMessageLine(languageId, 0),
                           GetGoOutMessageLine(languageId, 1),
                           GetGoOutMessageLine(languageId, 2),
                           GetGoOutMessageLine(languageId, 3),
                           GetGoOutMessageLine(languageId, 4));
                field_0x19 = -1;
                SetGoOutMode(0);
            } else {
                field_0xc = 0;
                mcCtrl.m_cardChannel = field_0xc;
                field_0x2 = static_cast<char>(mcCtrl.m_cardChannel);
                field_0x3 = static_cast<char>(field_0x10);
                SetGoOutMode(10);
            }
        }
        break;
    case 0x10:
        if (field_0x45 == 0) {
            break;
        }

        input = GetGoOutInputMask();
        if ((input & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7f, 0);
            SetGoOutMode(0xf);
            break;
        }

        field_0x47 = 1;
        if (field_0x1e == 0) {
            field74_0x4a = 0xb1;
        } else {
            field74_0x4a = 0x8b;
        }
        field75_0x4c = 0xdc;
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
            SetGoOutMode(0xf);
        } else if (next == 1) {
            SetGoOutMode(0x11);
        }
        break;
    case 0x11:
        if (field_0x45 == 0) {
            break;
        }

        input = GetGoOutInputMask();
        if ((input & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7f, 0);
            SetGoOutMode(0xf);
            break;
        }

        field_0x47 = 1;
        field74_0x4a = 0xd3;
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
            SetGoOutMode(0xf);
        } else if (next == 1) {
            SetGoOutMode(0x12);
        }
        break;
    case 0x12:
        if (field_0x45 != 0 && field_0x4 != 0) {
            if (SetMemCardError() != 0) {
                return;
            }
            SetGoOutMode(0x13);
        }
        break;
    case 0x13:
        if (field_0x45 != 0 && field_0x4 != 0) {
            if (SetMemCardError() != 0) {
                return;
            }
            SetGoOutMode(0x14);
        }
        break;
    case 0x14:
        if (field_0x45 != 0) {
            input = GetGoOutInputMask();
            if ((input & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7f, 0);
                MenuPcs.SetCaravanWork(menuPcsLayout.m_transferSaveData);
                MenuPcs.ChgAllModel();
                SetGoOutMode(1);
            }
        }
        break;
    default:
        break;
    }

    if (field_0x1 == 2) {
        mcCtrl.SaveDataBuffer(reinterpret_cast<char*>(field_0x8));
        field_0x4 = mcCtrl.m_lastResult;
        if (field_0x4 != 0) {
            field_0x0 = field_0x1;
            field_0x1 = 0;
        }
    } else if (field_0x1 < 2) {
        if (field_0x1 != 0) {
            field_0x4 = mcCtrl.ChkNowData();
            if (field_0x4 != 0) {
                field_0x0 = field_0x1;
                field_0x1 = 0;
            }
        }
    } else if (field_0x1 < 4) {
        mcCtrl.Format(1);
        int formatResult = mcCtrl.m_lastResult;
        if (formatResult < 0) {
            MemoryCardMan.m_opDoneFlag = 1;
            MemoryCardMan.m_currentSlot = static_cast<char>(0xff);
        }

        if (formatResult == 0) {
            field_0x4 = 0;
        } else if (formatResult == 1) {
            field_0x4 = 1;
        } else if (formatResult == -2) {
            field_0x4 = -5;
        } else {
            field_0x4 = -999;
        }

        if (field_0x4 != 0) {
            field_0x0 = field_0x1;
            field_0x1 = 0;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::DrawGoOut()
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    if (ReadGoOutU8(*this, 0x29) != 0) {
        MenuPcs.DrawInit();
        MenuPcs.DrawCMakeMenu();
    }

    if (ReadGoOutS8(*this, 0x24) > 0xD && ReadGoOutS8(*this, 0x24) < 0xF) {
        MenuPcs.DrawLoadMenu();
    }

    if (ReadGoOutS8(*this, 0x24) == 1 && MenuGoOutState(menuPcsLayout).m_resultSelect != 0) {
        MenuGoOutState(menuPcsLayout).m_closeMode = 8;
        SetMainMode(1);
        MenuGoOutState(menuPcsLayout).m_resultSelect = 0;
    }
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
    unsigned char& initSelChar = reinterpret_cast<unsigned char&>(field_0x24[2]);
    int& selectedChara = *reinterpret_cast<int*>(&field_0x24[4]);

    delMode = mode;
    switch (delMode) {
    case 2:
        if (field_0x36 >= 0) {
            MenuMcWinState(menuPcsLayout).m_mode = 2;
            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
        }
        field_0x45 = 0;
        field_0x34 = -1;
        field_0x48 = 0;
        field_0x3c = 0;
        if (initSelChar == 0) {
            MenuPcs.InitSaveLoadMenu();
        }
        MenuPcs.SetMenuCharaAnim(selectedChara, 0);
        initSelChar = 1;
        break;
    case 1:
        MenuGoOutState(menuPcsLayout).m_resultDir = -1;
        MenuGoOutState(menuPcsLayout).m_waitFrames = 10;
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
                int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                SetMenuStr(0, 4,
                           GetGoOutMessageLine(languageId, 70),
                           GetGoOutMessageLine(languageId, 71),
                           GetGoOutMessageLine(languageId, 72),
                           GetGoOutMessageLine(languageId, 73));
                reinterpret_cast<signed char&>(field_0x24[1]) = 2;
                SetDelMode(0);
                return;
            }
        }

        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 2,
                       GetGoOutMessageLine(languageId, 74),
                       GetGoOutMessageLine(languageId, 75));
        }
        field_0x46 = 1;
        break;
    }
    case 4:
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 4,
                       GetGoOutMessageLine(languageId, 76),
                       GetGoOutMessageLine(languageId, 77),
                       GetGoOutMessageLine(languageId, 78),
                       GetGoOutMessageLine(languageId, 79));
        }
        field_0x46 = 1;
        break;
    case 5:
        if (Game.m_caravanWorkArr[selectedChara].m_caravanLocalFlags == 0) {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 1, GetGoOutMessageLine(languageId, 88));
        } else {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 8,
                       GetGoOutMessageLine(languageId, 80),
                       GetGoOutMessageLine(languageId, 81),
                       GetGoOutMessageLine(languageId, 82),
                       GetGoOutMessageLine(languageId, 83),
                       GetGoOutMessageLine(languageId, 84),
                       GetGoOutMessageLine(languageId, 85),
                       GetGoOutMessageLine(languageId, 86),
                       GetGoOutMessageLine(languageId, 87));
        }
        field_0x46 = 1;
        MenuPcs.SetMenuCharaAnim(selectedChara, 5);
        break;
    case 6:
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 6,
                       GetGoOutMessageLine(languageId, 89),
                       GetGoOutMessageLine(languageId, 90),
                       GetGoOutMessageLine(languageId, 91),
                       GetGoOutMessageLine(languageId, 92),
                       GetGoOutMessageLine(languageId, 93),
                       GetGoOutMessageLine(languageId, 94));
        }
        field_0x46 = 1;
        break;
    case 7:
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 5,
                       GetGoOutMessageLine(languageId, 95),
                       GetGoOutMessageLine(languageId, 96),
                       GetGoOutMessageLine(languageId, 97),
                       GetGoOutMessageLine(languageId, 98),
                       GetGoOutMessageLine(languageId, 99));
        }
        field_0x46 = 1;
        break;
    case 8:
        MenuPcs.SetMenuCharaAnim(selectedChara, 3);
        {
            int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
            SetMenuStr(0, 1, GetGoOutMessageLine(languageId, 100));
        }
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
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    MenuPcs.DrawInit();
    MenuPcs.DrawCMakeMenu();
    if (ReadGoOutS16(*this, 0x36) == 1 && MenuGoOutState(menuPcsLayout).m_resultSelect != 0) {
        MenuGoOutState(menuPcsLayout).m_closeMode = 8;
        SetMainMode(1);
        MenuGoOutState(menuPcsLayout).m_resultSelect = 0;
    }
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
        menuPcsLayout.m_transferSaveData =
            reinterpret_cast<Mc::SaveDat*>(new (MenuPcs.m_menuStage, const_cast<char*>(s_gooutCpp), 0x32B) unsigned char[0x8BD0]);
        menuPcsLayout.m_transferWork = new (MenuPcs.m_menuStage, const_cast<char*>(s_gooutCpp), 0x32D) unsigned char[0x8BD0];
        menuPcsLayout.m_transferWorkActive = 0;
        menuPcsLayout.m_unknown_888 = 0;
        menuPcsLayout.m_saveLoadMode = 0;
        menuPcsLayout.m_unknown_88A = 0;
        short* winMessage = reinterpret_cast<short*>(GetWinMess__8CMenuPcsFi(&MenuPcs, 0x22));
        winMessage[0] = 0;
        winMessage[1] = 0;
        winMessage[2] = 0;
        winMessage[3] = 1;
        winMessage[4] = 2;
        winMessage[5] = 3;
        winMessage[6] = 4;
        winMessage[7] = 5;
        winMessage[8] = 6;
        winMessage[9] = 7;
        winMessage = reinterpret_cast<short*>(GetWinMess__8CMenuPcsFi(&MenuPcs, 0x23));
        winMessage[0] = 0;
        winMessage[1] = 0;
        winMessage[2] = 10;
        winMessage[3] = 11;
        winMessage[4] = 12;
        winMessage[5] = 13;
        winMessage[6] = 14;
        winMessage[7] = 15;
        winMessage[8] = 16;
        winMessage[9] = 17;
        MenuMcWinState(menuPcsLayout).m_mode = 3;
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
            } else if (mode >= 0 && field_0x45 != 0) {
                input = GetGoOutInputMask();
                if ((input & 0x200) != 0) {
                    Sound.PlaySe(3, 0x40, 0x7f, 0);
                    MenuPcs.InitSaveLoadMenu();
                    MenuPcs.SetMenuCharaAnim(0, 0);
                    MenuGoOutState(menuPcsLayout).m_resultSelect = -1;

                    if (menuPcsLayout.m_transferSaveData != 0) {
                        delete[] reinterpret_cast<unsigned char*>(menuPcsLayout.m_transferSaveData);
                        menuPcsLayout.m_transferSaveData = 0;
                    }
                    if (menuPcsLayout.m_transferWork != 0) {
                        delete[] static_cast<unsigned char*>(menuPcsLayout.m_transferWork);
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

                unsigned char nextMode = 0;
                if (MenuMcWinState(menuPcsLayout).m_mode == 1) {
                    input = GetGoOutInputMask();
                    if ((input & 0xC) == 0) {
                        input = GetGoOutInputMask();
                        if ((input & 0x100) != 0) {
                            Sound.PlaySe(2, 0x40, 0x7f, 0);
                            nextMode = static_cast<unsigned char>(field_0x46 + 1);
                        }
                    } else {
                        field_0x46 ^= 1;
                        Sound.PlaySe(1, 0x40, 0x7f, 0);
                    }
                }

                if (nextMode == 2) {
                    int activeCount = 0;
                    for (int i = 0; i < 8; i++) {
                        CCaravanWork& caravanWork = Game.m_caravanWorkArr[i];
                        if (caravanWork.m_shopState != 0) {
                            activeCount++;
                            if (caravanWork.m_caravanLocalFlags != 0) {
                                activeCount++;
                            }
                        }
                    }

                    if (activeCount < 2) {
                        int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                        SetMenuStr(0, 2,
                                   GetGoOutMessageLine(languageId, 108),
                                   GetGoOutMessageLine(languageId, 109));
                        field_0x2d = 1;
                        SetMainMode(0);
                    } else {
                        SetMainMode(3);
                        if (field_0x36 >= 0) {
                            MenuMcWinState(menuPcsLayout).m_mode = 2;
                            MenuGoOutState(menuPcsLayout).m_animFrame = 0;
                        }
                        field_0x45 = 0;
                        field_0x34 = -1;
                        field_0x48 = 0;
                        field_0x3c = 0;
                    }
                } else if (nextMode == 1) {
                    int characterCount = 0;
                    int transferableCount = 0;
                    for (int i = 0; i < 8; i++) {
                        CCaravanWork& caravanWork = Game.m_caravanWorkArr[i];
                        if (caravanWork.m_shopState != 0) {
                            characterCount++;
                            if (caravanWork.m_caravanLocalFlags == 0) {
                                transferableCount++;
                            }
                        }
                    }

                    if (characterCount == 0) {
                        int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                        SetMenuStr(0, 7,
                                   GetGoOutMessageLine(languageId, 101),
                                   GetGoOutMessageLine(languageId, 102),
                                   GetGoOutMessageLine(languageId, 103),
                                   GetGoOutMessageLine(languageId, 104),
                                   GetGoOutMessageLine(languageId, 105),
                                   GetGoOutMessageLine(languageId, 106),
                                   GetGoOutMessageLine(languageId, 107));
                        field_0x2d = 1;
                        SetMainMode(0);
                    } else if (transferableCount < 8) {
                        SetMainMode(2);
                    } else {
                        int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
                        SetMenuStr(0, 6,
                                   GetGoOutMessageLine(languageId, 62),
                                   GetGoOutMessageLine(languageId, 63),
                                   GetGoOutMessageLine(languageId, 64),
                                   GetGoOutMessageLine(languageId, 65),
                                   GetGoOutMessageLine(languageId, 66),
                                   GetGoOutMessageLine(languageId, 67));
                        field_0x2d = 1;
                        SetMainMode(0);
                    }
                }
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

    if (field_0x40 != 0) {
        field_0x40--;
        if (field_0x40 == 0) {
            if (field_0x36 >= 0) {
                MenuMcWinState(menuPcsLayout).m_mode = 2;
                MenuGoOutState(menuPcsLayout).m_animFrame = 0;
            }
            field_0x45 = 0;
            field_0x34 = -1;
            field_0x48 = 0;
            field_0x3c = 0;
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
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    if (MenuMcWinState(menuPcsLayout).m_mode == 1 && ReadGoOutU8(*this, 0x47) != 0) {
        const int cursorY = MenuMcWinState(menuPcsLayout).m_y + MenuMcWinState(menuPcsLayout).m_height - 0x3E;

        if (ReadGoOutU8(*this, 0x49) == 0) {
            const int cursorX = GetYesNoXPos__8CMenuPcsFi(&MenuPcs, ReadGoOutU8(*this, 0x46));
            MenuPcs.DrawCursor(cursorX, cursorY, 1.0f);
        } else {
            const int cursorX = MenuMcWinState(menuPcsLayout).m_x + 0x20;
            const int localY =
                ReadGoOutS16(*this, 0x4A) + ReadGoOutU8(*this, 0x46) * 0x1E;
            MenuPcs.DrawCursor(cursorX, localY, 1.0f);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::Draw()
{
    if (ReadGoOutU8(*this, 0x44) == 3) {
        DrawDel();
    } else if (ReadGoOutU8(*this, 0x44) == 2) {
        DrawGoOut();
    }

    DrawMenu();
    DrawSelectYesNo();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::InitMemCardProc()
{
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
    McCtrl& mcCtrl = menuPcsLayout.m_mcCtrl;

    mcCtrl.m_saveIndex = static_cast<unsigned char>(field_0x3);
    mcCtrl.m_cardChannel = static_cast<unsigned char>(field_0x2);
    mcCtrl.m_previousState = 0;
    mcCtrl.m_state = 0;
    mcCtrl.m_lastResult = 0;
    mcCtrl.m_iteration = 0;
    mcCtrl.m_userBuffer = reinterpret_cast<void*>(field_0x8);
    mcCtrl.m_createFlag = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::EndMemCardProc()
{
    field_0x1 = 0;
    field_0x4 = -1;
    MemoryCardMan.McEnd();
}
