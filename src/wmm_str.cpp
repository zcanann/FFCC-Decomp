#include "ffcc/wmm_str.h"
#include "ffcc/p_game.h"
#include "ffcc/fontman.h"

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
extern const char* lbl_8021672C[];
extern const char* lbl_80216740[];

extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void SetTlut__5CFontFi(CFont*, int);
extern "C" int GetWidth__5CFontFPc(CFont*, const char*);

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
int CMenuPcs::GetYesNoXPos(int right)
{
    static const char sYes[] = "\0Yes";
    static const char sJa[] = "\0Ja";
    static const char sOui[] = "\0Oui";

    const unsigned int languageId = Game.game.m_gameWork.m_languageId;
    const char* yesText = sOui;
    if (languageId != 3) {
        if (languageId < 3) {
            if ((languageId != 1) && (languageId != 0)) {
                yesText = sJa;
                goto apply_font_yes;
            }
        } else {
            yesText = sYes;
            if ((languageId == 5) || (languageId < 5)) {
                goto apply_font_yes;
            }
        }
        yesText = sYes;
    }

apply_font_yes:
    CFont* font = *(CFont**)((char*)this + 0xf8);
    SetMargin__5CFontFf(1.0f, font);
    SetShadow__5CFontFi(font, 0);
    SetScale__5CFontFf(1.0f, font);

    const int yesWidth = GetWidth__5CFontFPc(font, yesText + 1);
    short* windowInfo = *(short**)((char*)this + 0x848);
    int x = (int)((windowInfo[2] - yesWidth) * 0.5f + windowInfo[0]);
    if (right != 0) {
        const int noWidth = GetWidth__5CFontFPc(font, lbl_8021672C[languageId - 1]);
        x += yesWidth - noWidth;
    }
    return x - 0x1e;
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
int CMenuPcs::GetSlotABXPos(int right)
{
    static const char sSlotA[] = "\0Slot A";
    static const char sSteckplatzA[] = "\0Steckplatz A";
    static const char sRanuraA[] = "\0Ranura A";

    const unsigned int languageId = Game.game.m_gameWork.m_languageId;
    const char* slotAText = sSlotA;
    if (languageId != 3) {
        if (languageId < 3) {
            if ((languageId != 1) && (languageId != 0)) {
                slotAText = sSteckplatzA;
                goto apply_font_slot;
            }
        } else {
            slotAText = sRanuraA;
            if ((languageId == 5) || (languageId < 5)) {
                goto apply_font_slot;
            }
        }
        slotAText = sSlotA;
    }

apply_font_slot:
    CFont* font = *(CFont**)((char*)this + 0xf8);
    SetMargin__5CFontFf(1.0f, font);
    SetShadow__5CFontFi(font, 0);
    SetScale__5CFontFf(1.0f, font);
    SetTlut__5CFontFi(font, 0x23);

    const int slotAWidth = GetWidth__5CFontFPc(font, slotAText + 1);
    short* windowInfo = *(short**)((char*)this + 0x848);
    int x = (int)((windowInfo[2] - slotAWidth) * 0.5f + windowInfo[0]);
    if (right != 0) {
        const int slotBWidth = GetWidth__5CFontFPc(font, lbl_80216740[languageId - 1]);
        x += slotAWidth - slotBWidth;
    }
    return x - 0x1e;
}
