#include "ffcc/goout.h"
#include "ffcc/wm_menu.h"
#include <string.h>

extern CGoOutMenu g_GoOutMenu;
extern CGoOutMenu* g_pGoOutMenu;
extern "C" int GetYesNoXPos__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int CalcGoOutSelChar__8CMenuPcsFUcUc(CMenuPcs*, unsigned char, unsigned char);
extern "C" void Calc__10CGoOutMenuFv(CGoOutMenu*);

struct CMenuPcsGoOutLayout
{
    unsigned char unk0[2092];
    int field_2092;
    unsigned char unk2096[24];
    int field_2120;
};

static inline signed short ReadMenuShort(int base, int offset)
{
    return *reinterpret_cast<signed short*>(base + offset);
}

static inline void WriteMenuShort(int base, int offset, signed short value)
{
    *reinterpret_cast<signed short*>(base + offset) = value;
}

static inline unsigned char ReadGoOutU8(CGoOutMenu& menu, int offset)
{
    return *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(&menu) + offset);
}

static inline signed short ReadGoOutS16(CGoOutMenu& menu, int offset)
{
    return *reinterpret_cast<signed short*>(reinterpret_cast<unsigned char*>(&menu) + offset);
}

static inline signed char ReadGoOutS8(CGoOutMenu& menu, int offset)
{
    return *reinterpret_cast<signed char*>(reinterpret_cast<unsigned char*>(&menu) + offset);
}

static inline void WriteMenuU8(int offset, unsigned char value)
{
    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(&MenuPcs) + offset) = value;
}

static unsigned short GetGoOutInputMask()
{
    if (Pad._452_4_ != 0 || Pad._448_4_ != -1) {
        return 0;
    }

    return static_cast<unsigned short>(Pad._8_2_);
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
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);
    g_pGoOutMenu = &g_GoOutMenu;

    if (ReadGoOutU8(g_GoOutMenu, 0x44) == 3) {
        MenuPcs.DrawInit();
        MenuPcs.DrawCMakeMenu();
        if (ReadGoOutS16(g_GoOutMenu, 0x36) == 1 && ReadMenuShort(menuPcsLayout.field_2092, 0x20) != 0) {
            WriteMenuShort(menuPcsLayout.field_2092, 0x1C, 8);
            g_GoOutMenu.SetMainMode(1);
            WriteMenuShort(menuPcsLayout.field_2092, 0x20, 0);
        }
    } else if (ReadGoOutU8(g_GoOutMenu, 0x44) == 2) {
        if (ReadGoOutU8(g_GoOutMenu, 0x29) != 0) {
            MenuPcs.DrawInit();
            MenuPcs.DrawCMakeMenu();
        }
        if (ReadGoOutS8(g_GoOutMenu, 0x24) > 0xD && ReadGoOutS8(g_GoOutMenu, 0x24) < 0xF) {
            MenuPcs.DrawLoadMenu();
        }
        if (ReadGoOutS8(g_GoOutMenu, 0x24) == 1 && ReadMenuShort(menuPcsLayout.field_2092, 0x20) != 0) {
            WriteMenuShort(menuPcsLayout.field_2092, 0x1C, 8);
            g_GoOutMenu.SetMainMode(1);
            WriteMenuShort(menuPcsLayout.field_2092, 0x20, 0);
        }
    }

    if (ReadGoOutS16(g_GoOutMenu, 0x54) != -1) {
        MenuPcs.DrawMcWin(-1, 0);
        if (ReadMenuShort(menuPcsLayout.field_2120, 0xA) == 1) {
            const int message = static_cast<int>(ReadGoOutS16(g_GoOutMenu, 0x54));
            MenuPcs.DrawMcWinMess(message, (message >= 0x1E) ? 2 : 0);
        }
    }

    if (ReadMenuShort(menuPcsLayout.field_2120, 0xA) == 1 && ReadGoOutU8(g_GoOutMenu, 0x71) != 0) {
        const int cursorY = ReadMenuShort(menuPcsLayout.field_2120, 2) + ReadMenuShort(menuPcsLayout.field_2120, 6) - 0x3E;

        if (ReadGoOutU8(g_GoOutMenu, 0x73) == 0) {
            const int cursorX = GetYesNoXPos__8CMenuPcsFi(&MenuPcs, ReadGoOutU8(g_GoOutMenu, 0x70));
            MenuPcs.DrawCursor(cursorX, cursorY, 1.0f);
        } else {
            const int cursorX = ReadMenuShort(menuPcsLayout.field_2120, 0) + 0x20;
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
    int result = 1;
    const int memCardResult = field_0x4;

    if (memCardResult == -5) {
        field_0x36 = -1;
        field_0x40 = 0;
        field_0x44 = 1;
        field_0x45 = 0;
        field_0x34 = 3;
        field_0x48 = 0;
        field_0x3c = 0;
    } else if (memCardResult < -5) {
        if (memCardResult == -13 || memCardResult == -6) {
            SetGoOutMode(3);
            return 1;
        }

        if ((memCardResult == -999 || memCardResult == -1000) && field_0x1 == 1) {
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
        } else if (field_0x1 == 3) {
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
            field_0x45 = 0;
            field_0x34 = 0xd;
            field_0x48 = 0;
            field_0x3c = 0;
        } else if (field_0x1 == 2) {
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
            field_0x45 = 0;
            field_0x34 = 0xf;
            field_0x48 = 0;
            field_0x3c = 0;
        }
    } else if (memCardResult == -1 || memCardResult == -3) {
        field_0x36 = -1;
        field_0x40 = 0;
        field_0x44 = 1;
        field_0x45 = 0;
        field_0x34 = 1;
        field_0x48 = 0;
        field_0x3c = 0;
    } else if (memCardResult == -2) {
        field_0x36 = -1;
        field_0x40 = 0;
        field_0x44 = 1;
        field_0x45 = 0;
        field_0x34 = 2;
        field_0x48 = 0;
        field_0x3c = 0;
    } else if (memCardResult == -4) {
        if (field_0x1 != 1) {
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
            field_0x45 = 0;
            field_0x34 = 0x13;
            field_0x48 = 0;
            field_0x3c = 0;
        } else {
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
        }
    } else if (memCardResult == 1) {
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
void CGoOutMenu::SetMenuStr(long, int, ...)
{
	// TODO
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
    CMenuPcsGoOutLayout& menuPcsLayout = *reinterpret_cast<CMenuPcsGoOutLayout*>(&MenuPcs);

    WriteMenuU8(2185, 0);
    WriteMenuU8(2186, 0);
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&MenuPcs) + 2188) = 0;

    if (field_0x2c == 2) {
        MemoryCardMan.McEnd();
    }

    const signed char previousMode = field_0x2c;
    field_0x2c = mode;
    field_0x30 = 0;

    if (mode == 2) {
        if (Game.game.m_gameWork.m_mcHasSerial != 1) {
            SetMenuStr(0, 4,
                       "This game has not been saved.",
                       "",
                       "You must save your game before",
                       "you can import a character.");
            field_0x19 = -1;
            field_0x18 = 0;
        }

        for (int i = 0; i < 8; i++) {
            if (Game.game.m_caravanWorkArr[i].m_objType != 0 &&
                Game.game.m_caravanWorkArr[i].m_caravanLocalFlags != 1) {
                SetMenuStr(0, 5,
                           "This game contains character data",
                           "that has not yet been saved.",
                           "",
                           "You must save your game before",
                           "you can import a character.");
                field_0x19 = -1;
                field_0x18 = 0;
            }
        }

        field_0x1 = 0;
        reinterpret_cast<unsigned char*>(this)[0] = 0;
        field_0x2 = 0;
        field_0x3 = 0;
        field_0x4 = -1;
        field_0x8 = 0;
        SetGoOutMode(7);
    } else if (mode < 2) {
        if (mode != 0) {
            field_0x46 = 1;
            if (previousMode != 3) {
                field_0x46 = 0;
            }

            MenuPcs.ChgAllModel();

            if (field_0x36 >= 0) {
                WriteMenuShort(menuPcsLayout.field_2120, 0xA, 2);
                WriteMenuShort(menuPcsLayout.field_2092, 0x22, 0);
            }

            field_0x45 = 0;
            field_0x34 = 0x1e;
            field_0x48 = 0;
            field_0x3c = 0;
            field_0x14 = 0;
        }
    } else if (mode < 4) {
        MenuPcs.ChgAllModel();
        WriteMenuU8(2184, 2);
        field_0x14 = 0;
        reinterpret_cast<signed char&>(field_0x24[2]) = 0;
        SetDelMode(2);
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
    McCtrl& mcCtrl = *reinterpret_cast<McCtrl*>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x20);

	field_0x18 = mode;
	switch(field_0x18) {
	case 1:
		field_0x1c = 0;
        WriteMenuShort(menuPcsLayout.field_2092, 0x1E, -1);
        WriteMenuShort(menuPcsLayout.field_2092, 0x18, 10);
		break;
	case 3:
        if (field_0x36 >= 0) {
            WriteMenuShort(menuPcsLayout.field_2120, 0xA, 2);
            WriteMenuShort(menuPcsLayout.field_2092, 0x22, 0);
        }
		field_0x45 = 0;
		field_0x34 = 4;
		field_0x48 = 0;
		field_0x3c = 0;
		field_0x46 = 1;
		break;
	case 4:
        if (field_0x36 >= 0) {
            WriteMenuShort(menuPcsLayout.field_2120, 0xA, 2);
            WriteMenuShort(menuPcsLayout.field_2092, 0x22, 0);
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
            WriteMenuShort(menuPcsLayout.field_2120, 0xA, 2);
            WriteMenuShort(menuPcsLayout.field_2092, 0x22, 0);
        }
        field_0x45 = 0;
        field_0x34 = 7;
        field_0x48 = 0;
        field_0x3c = 0;
        break;
    case 6:
        if (ReadMenuShort(menuPcsLayout.field_2120, 0xA) == 1) {
            WriteMenuShort(menuPcsLayout.field_2120, 0xA, 3);
            WriteMenuShort(menuPcsLayout.field_2092, 0x22, 0);
            field_0x36 = -1;
            field_0x40 = 0;
            field_0x44 = 1;
        }
        if (field_0x36 >= 0) {
            WriteMenuShort(menuPcsLayout.field_2120, 0xA, 2);
            WriteMenuShort(menuPcsLayout.field_2092, 0x22, 0);
        }
        field_0x45 = 0;
        field_0x34 = 0xc;
        field_0x48 = 0;
        field_0x3c = 0;
        field_0x46 = 1;
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
    McCtrl& mcCtrl = *reinterpret_cast<McCtrl*>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x20);
    unsigned short input;
    unsigned char next;

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
        input = GetGoOutInputMask();

        if ((input & 3) == 0) {
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
        input = GetGoOutInputMask();

        if ((input & 3) == 0) {
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
            SetMenuStr(0, 2, "No Memory Card found in", "Slot A.");
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
            SetMenuStr(0, 2, "No Memory Card found in", "Slot B.");
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
    signed char& delMode = reinterpret_cast<signed char&>(field_0x24[0]);
    signed char& initSelChar = reinterpret_cast<signed char&>(field_0x24[2]);
    int& selectedChara = *reinterpret_cast<int*>(&field_0x24[4]);

    delMode = mode;
    switch (delMode) {
    case 1:
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
        if (Game.game.m_caravanWorkArr[selectedChara].m_caravanLocalFlags == 0) {
            int activeMainCharacterCount = 0;
            for (int i = 0; i < 8; i++) {
                const CCaravanWork& caravanWork = Game.game.m_caravanWorkArr[i];
                if (caravanWork.m_objType != 0 && caravanWork.m_caravanLocalFlags == 0) {
                    activeMainCharacterCount++;
                }
            }

            if (activeMainCharacterCount < 2) {
                SetMenuStr(0, 4,
                           "This character cannot be deleted.",
                           "",
                           "At least one non-guest character",
                           "must remain.");
                reinterpret_cast<signed char&>(field_0x24[1]) = 2;
                SetDelMode(0);
                return;
            }
        }

        SetMenuStr(0, 2, "Delete this character?", "  Yes   No");
        field_0x46 = 1;
        break;
    }
    case 4:
        SetMenuStr(0, 4,
                   "Deleted characters",
                   "cannot be restored.",
                   "Are you sure?",
                   "  Yes   No");
        field_0x46 = 1;
        break;
    case 5:
        if (Game.game.m_caravanWorkArr[selectedChara].m_caravanLocalFlags == 0) {
            SetMenuStr(0, 1, "The character has been deleted.");
        } else {
            SetMenuStr(0, 8,
                       "The guest character has been deleted.",
                       "",
                       "Please restore the character's",
                       "original save data.",
                       "",
                       "To restore a character who is abroad,",
                       "first select \"Delete Character\" and",
                       "select the character you wish to restore.");
        }
        field_0x46 = 1;
        MenuPcs.SetMenuCharaAnim(selectedChara, 5);
        break;
    case 6:
        SetMenuStr(0, 6,
                   "This character is currently abroad",
                   "and cannot be deleted here. If you",
                   "wish to delete the character's",
                   "original data, you must first",
                   "restore it. Proceed?",
                   "  Yes   No");
        field_0x46 = 1;
        break;
    case 7:
        SetMenuStr(0, 5,
                   "This will restore the character",
                   "to the state it was in before transfer.",
                   "It will also prevent the transferred data",
                   "from returning to this save location.",
                   "  Yes   No");
        field_0x46 = 1;
        break;
    case 8:
        MenuPcs.SetMenuCharaAnim(selectedChara, 3);
        SetMenuStr(0, 1, "The character has been restored.");
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
            if (Game.game.m_caravanWorkArr[selectedChara].m_shopBusyFlag == 0) {
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

        if (ReadMenuShort(menuPcsLayout.field_2120, 0xA) == 1) {
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

        if (ReadMenuShort(menuPcsLayout.field_2120, 0xA) == 1) {
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
                CCaravanWork& caravanWork = Game.game.m_caravanWorkArr[selectedChara];
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

        if (ReadMenuShort(menuPcsLayout.field_2120, 0xA) == 1) {
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

        if (ReadMenuShort(menuPcsLayout.field_2120, 0xA) == 1) {
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
            Game.game.m_caravanWorkArr[selectedChara].m_shopBusyFlag = 0;
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
    char cVar10;

    // Basic menu state management
    field_0x47 = 0;
    
    // Check main mode and handle transitions
    cVar10 = field_0x2c;
    if (cVar10 == 2) {
        CalcGoOut();
    }
    else if (cVar10 < 2) {
        if (cVar10 == 0) {
            if (field_0x45 != 0) {
                SetMainMode(field_0x2d);
            }
        }
        else if (cVar10 == 1) {
            // Handle menu operations
            field_0x47 = 1;
        }
    }
    else if (cVar10 == 3) {
        CalcDel();
    }
    
    // Update frame counter
    field_0x30 = field_0x30 + 1;
    if (10000 < field_0x30) {
        field_0x30 = 10000;
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
