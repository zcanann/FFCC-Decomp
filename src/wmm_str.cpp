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
extern "C" float GetWidth__5CFontFPc(CFont*, const char*);

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
    switch (Game.game.m_gameWork.m_languageId) {
    case 2:
        return lbl_80215BE8[index];
    case 3:
        return lbl_80215BF8[index];
    case 4:
        return lbl_80215C08[index];
    case 5:
        return lbl_80215C18[index];
    default:
        return lbl_80215BD8[index];
    }
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
    switch (group) {
    case 0:
        switch (Game.game.m_gameWork.m_languageId) {
        case 2:
            return lbl_80215D14;
        case 3:
            return lbl_80215E00;
        case 4:
            return lbl_80215EEC;
        case 5:
            return lbl_80215FD8;
        default:
            return lbl_80215C28;
        }
    case 1:
        switch (Game.game.m_gameWork.m_languageId) {
        case 2:
            return lbl_8021636C;
        case 3:
            return lbl_802163A8;
        case 4:
            return lbl_802163E4;
        case 5:
            return lbl_80216420;
        default:
            return lbl_80216330;
        }
    default:
        switch (Game.game.m_gameWork.m_languageId) {
        case 2:
            return lbl_80216140;
        case 3:
            return lbl_802161BC;
        case 4:
            return lbl_80216238;
        case 5:
            return lbl_802162B4;
        default:
            return lbl_802160C4;
        }
    }
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
    int languageId = Game.game.m_gameWork.m_languageId;
    if ((languageId == 1) || (languageId < 1) || (languageId >= 6)) {
        return &lbl_8021645C[index * 0x14];
    }
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
    const unsigned int languageId = Game.game.m_gameWork.m_languageId;
    const char* yesText;
    if (languageId == 3) {
        yesText = lbl_80215E00[13];
    } else if (languageId < 3) {
        if ((languageId == 1) || (languageId == 0)) {
            yesText = lbl_80215C28[13];
        } else {
            yesText = lbl_80215D14[13];
        }
    } else if (languageId == 5) {
        yesText = lbl_80215FD8[13];
    } else if (languageId < 5) {
        yesText = lbl_80215EEC[13];
    } else {
        yesText = lbl_80215C28[13];
    }

    CFont* font = *(CFont**)((char*)this + 0xf8);
    SetMargin__5CFontFf(1.0f, font);
    SetShadow__5CFontFi(font, 0);
    SetScale__5CFontFf(1.0f, font);

    const int yesWidth = (int)GetWidth__5CFontFPc(font, yesText + 1);
    short* windowInfo = *(short**)((char*)this + 0x848);
    int x = (int)(((double)(windowInfo[2] - yesWidth) * 0.5) + (double)windowInfo[0]);
    if (right != 0) {
        const int noWidth = (int)GetWidth__5CFontFPc(font, lbl_8021672C[languageId - 1]);
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
    const unsigned int languageId = Game.game.m_gameWork.m_languageId;
    const char* slotAText;
    if (languageId == 3) {
        slotAText = lbl_80215E00[2];
    } else if (languageId < 3) {
        if ((languageId == 1) || (languageId == 0)) {
            slotAText = lbl_80215C28[2];
        } else {
            slotAText = lbl_80215D14[2];
        }
    } else if (languageId == 5) {
        slotAText = lbl_80215FD8[2];
    } else if (languageId < 5) {
        slotAText = lbl_80215EEC[2];
    } else {
        slotAText = lbl_80215C28[2];
    }

    CFont* font = *(CFont**)((char*)this + 0xf8);
    SetMargin__5CFontFf(1.0f, font);
    SetShadow__5CFontFi(font, 0);
    SetScale__5CFontFf(1.0f, font);
    SetTlut__5CFontFi(font, 0x23);

    const int slotAWidth = (int)GetWidth__5CFontFPc(font, slotAText + 1);
    short* windowInfo = *(short**)((char*)this + 0x848);
    int x = (int)(((double)(windowInfo[2] - slotAWidth) * 0.5) + (double)windowInfo[0]);
    if (right != 0) {
        const int slotBWidth = (int)GetWidth__5CFontFPc(font, lbl_80216740[languageId - 1]);
        x += slotAWidth - slotBWidth;
    }
    return x - 0x1e;
}
