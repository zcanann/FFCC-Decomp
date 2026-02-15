#include "ffcc/goout.h"

static unsigned short GetGoOutInputMask()
{
    if (Pad._452_4_ != 0 || Pad._448_4_ != -1) {
        return 0;
    }

    return static_cast<unsigned short>(Pad._8_2_);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void DrawGoOutMenu()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::SetMainMode(unsigned char)
{
	// TODO
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
	field_0x18 = mode;
	switch(field_0x18) {
	case 1:
		field_0x1c = 0;
		// Menu state initialization
		break;
	case 3:
		field_0x45 = 0;
		field_0x34 = 4;
		field_0x48 = 0;
		field_0x3c = 0;
		field_0x46 = 1;
		break;
	case 4:
		field_0x45 = 0;
		field_0x34 = 5;
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
 * Address:	TODO
 * Size:	TODO
 */
void CGoOutMenu::CalcDel()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CalcGoOutMenu()
{
	// TODO
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
