#include "ffcc/wmm_str.h"
#include "ffcc/p_game.h"

extern const char* lbl_80215BD8[];
extern const char* lbl_80215BE8[];
extern const char* lbl_80215BF8[];
extern const char* lbl_80215C08[];
extern const char* lbl_80215C18[];

extern const char* lbl_80215C28[];
extern const char* lbl_80215D14[];
extern const char* lbl_80215E00[];
extern const char* lbl_80215EEC[];
extern const char* lbl_80215FD8[];

extern const char* lbl_802160C4[];
extern const char* lbl_80216140[];
extern const char* lbl_802161BC[];
extern const char* lbl_80216238[];
extern const char* lbl_802162B4[];

extern const char* lbl_80216330[];
extern const char* lbl_8021636C[];
extern const char* lbl_802163A8[];
extern const char* lbl_802163E4[];
extern const char* lbl_80216420[];

extern const char lbl_8021645C[];

/*
 * --INFO--
 * PAL Address: 0x8017b3f8
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
const char* CMenuPcs::GetMcStr(int index)
{
    const unsigned int languageId = Game.game.m_gameWork.m_languageId;
    if (languageId == 3) {
        return lbl_80215BF8[index];
    }
    if (languageId < 3) {
        if ((languageId != 1) && (languageId != 0)) {
            return lbl_80215BE8[index];
        }
    } else {
        if (languageId == 5) {
            return lbl_80215C18[index];
        }
        if (languageId < 5) {
            return lbl_80215C08[index];
        }
    }
    return lbl_80215BD8[index];
}

/*
 * --INFO--
 * PAL Address: 0x8017b268
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
const char* const* CMenuPcs::GetMcWinMessBuff(int group)
{
    const unsigned int languageId = Game.game.m_gameWork.m_languageId;
    if (group != 0) {
        if (group != 1) {
            if (languageId == 3) {
                return lbl_802161BC;
            }
            if (languageId < 3) {
                if ((languageId != 1) && (languageId != 0)) {
                    return lbl_80216140;
                }
            } else {
                if (languageId == 5) {
                    return lbl_802162B4;
                }
                if (languageId < 5) {
                    return lbl_80216238;
                }
            }
            return lbl_802160C4;
        }
        if (languageId == 3) {
            return lbl_802163A8;
        }
        if (languageId < 3) {
            if ((languageId != 1) && (languageId != 0)) {
                return lbl_8021636C;
            }
        } else {
            if (languageId == 5) {
                return lbl_80216420;
            }
            if (languageId < 5) {
                return lbl_802163E4;
            }
        }
        return lbl_80216330;
    }
    if (languageId == 3) {
        return lbl_80215E00;
    }
    if (languageId < 3) {
        if ((languageId != 1) && (languageId != 0)) {
            return lbl_80215D14;
        }
    } else {
        if (languageId == 5) {
            return lbl_80215FD8;
        }
        if (languageId < 5) {
            return lbl_80215EEC;
        }
    }
    return lbl_80215C28;
}

/*
 * --INFO--
 * PAL Address: 0x8017b220
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
const char* CMenuPcs::GetWinMess(int index)
{
    return &lbl_8021645C[index * 0x14];
}

/*
 * --INFO--
 * PAL Address: 0x8017b0a0
 * PAL Size: 384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetYesNoXPos(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8017af14
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetSlotABXPos(int)
{
	// TODO
}
