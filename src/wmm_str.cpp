#include "ffcc/wmm_str.h"
#include "ffcc/p_game.h"
#include "ffcc/fontman.h"

extern const char* PTR_s_The_data_is_corrupt__80215bd8[];
extern const char* PTR_s_Der_Spielstand_ist_fehlerhaft__80215be8[];
extern const char* PTR_s_I_dati_sono_danneggiati__80215bf8[];
extern const char* s_McStr_es[];
extern const char* s_McStr_fr[];

extern const char* s_McWinMessGroup0_en[];
extern const char* s_McWinMessGroup0_de[];
extern const char* s_McWinMessGroup0_it[];
extern const char* s_McWinMessGroup0_es[];
extern const char* s_McWinMessGroup0_fr[];

extern const char* s_McWinMessGroup2_en[];
extern const char* s_McWinMessGroup2_de[];
extern const char* s_McWinMessGroup2_it[];
extern const char* s_McWinMessGroup2_es[];
extern const char* s_McWinMessGroup2_fr[];

extern const char* s_McWinMessGroup1_en[];
extern const char* s_McWinMessGroup1_de[];
extern const char* s_McWinMessGroup1_it[];
extern const char* s_McWinMessGroup1_es[];
extern const char* s_McWinMessGroup1_fr[];

extern const char s_WinMessTable[];
extern const char* s_NoTextByLanguage[];
extern const char* s_SlotBTextByLanguage[];

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
        return PTR_s_Der_Spielstand_ist_fehlerhaft__80215be8[index];
    case 3:
        return PTR_s_I_dati_sono_danneggiati__80215bf8[index];
    case 4:
        return s_McStr_es[index];
    case 5:
        return s_McStr_fr[index];
    default:
        return PTR_s_The_data_is_corrupt__80215bd8[index];
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
    int languageId = Game.game.m_gameWork.m_languageId;
    switch (group) {
    case 0:
        switch (languageId) {
        case 2:
            return s_McWinMessGroup0_de;
        case 3:
            return s_McWinMessGroup0_it;
        case 4:
            return s_McWinMessGroup0_es;
        case 5:
            return s_McWinMessGroup0_fr;
        default:
            return s_McWinMessGroup0_en;
        }
    case 1:
        switch (languageId) {
        case 2:
            return s_McWinMessGroup1_de;
        case 3:
            return s_McWinMessGroup1_it;
        case 4:
            return s_McWinMessGroup1_es;
        case 5:
            return s_McWinMessGroup1_fr;
        default:
            return s_McWinMessGroup1_en;
        }
    default:
        switch (languageId) {
        case 2:
            return s_McWinMessGroup2_de;
        case 3:
            return s_McWinMessGroup2_it;
        case 4:
            return s_McWinMessGroup2_es;
        case 5:
            return s_McWinMessGroup2_fr;
        default:
            return s_McWinMessGroup2_en;
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
    if ((languageId != 1) && (languageId >= 1) && (languageId < 6)) {
        return &s_WinMessTable[index * 0x14];
    }
    return &s_WinMessTable[index * 0x14];
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
    const unsigned char languageId = Game.game.m_gameWork.m_languageId;
    const char* yesText;
    if (languageId == 3) {
        yesText = s_McWinMessGroup0_it[13];
    } else if (languageId < 3) {
        if ((languageId == 1) || (languageId == 0)) {
            yesText = s_McWinMessGroup0_en[13];
        } else {
            yesText = s_McWinMessGroup0_de[13];
        }
    } else if (languageId == 5) {
        yesText = s_McWinMessGroup0_fr[13];
    } else if (languageId < 5) {
        yesText = s_McWinMessGroup0_es[13];
    } else {
        yesText = s_McWinMessGroup0_en[13];
    }

    CFont* font = menuFont;
    SetMargin__5CFontFf(1.0f, font);
    SetShadow__5CFontFi(font, 0);
    SetScale__5CFontFf(1.0f, font);

    const int yesWidth = (int)GetWidth__5CFontFPc(font, yesText + 1);
    short* windowInfo = singWindowInfo;
    int x = (int)(((double)(windowInfo[2] - yesWidth) * 0.5) + (double)windowInfo[0]);
    if (right != 0) {
        const int noWidth = (int)GetWidth__5CFontFPc(font, s_NoTextByLanguage[languageId - 1]);
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
    const unsigned char languageId = Game.game.m_gameWork.m_languageId;
    const char* slotAText;
    if (languageId == 3) {
        slotAText = s_McWinMessGroup0_it[2];
    } else if (languageId < 3) {
        if ((languageId == 1) || (languageId == 0)) {
            slotAText = s_McWinMessGroup0_en[2];
        } else {
            slotAText = s_McWinMessGroup0_de[2];
        }
    } else if (languageId == 5) {
        slotAText = s_McWinMessGroup0_fr[2];
    } else if (languageId < 5) {
        slotAText = s_McWinMessGroup0_es[2];
    } else {
        slotAText = s_McWinMessGroup0_en[2];
    }

    CFont* font = menuFont;
    SetMargin__5CFontFf(1.0f, font);
    SetShadow__5CFontFi(font, 0);
    SetScale__5CFontFf(1.0f, font);
    SetTlut__5CFontFi(font, 0x23);

    const int slotAWidth = (int)GetWidth__5CFontFPc(font, slotAText + 1);
    short* windowInfo = singWindowInfo;
    int x = (int)(((double)(windowInfo[2] - slotAWidth) * 0.5) + (double)windowInfo[0]);
    if (right != 0) {
        const int slotBWidth = (int)GetWidth__5CFontFPc(font, s_SlotBTextByLanguage[languageId - 1]);
        x += slotAWidth - slotBWidth;
    }
    return x - 0x1e;
}
