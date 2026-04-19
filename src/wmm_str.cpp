#include "ffcc/wmm_str.h"
#include "ffcc/fontman.h"
#include "ffcc/p_game.h"

extern const char* PTR_s_The_data_is_corrupt_[];
extern const char* PTR_s_Der_Spielstand_ist_fehlerhaft_[];
extern const char* PTR_s_I_dati_sono_danneggiati_[];
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

extern const char lbl_803336B4[];
extern const char lbl_803336B8[];
extern const char lbl_803336C0[];
extern const char lbl_803336C4[];
extern const char s_Steckplatz_B_801E65E4[];
extern const char s_Ranura_B_801E65F4[];

extern const float FLOAT_803336CC;
extern const double DOUBLE_803336D0;

struct WinMessEntry
{
    unsigned int words[5];
};

static char* s_NoTextByLanguage[5] = {
    (char*)lbl_803336B4,
    (char*)lbl_803336B8,
    (char*)lbl_803336B4,
    (char*)lbl_803336C0,
    (char*)lbl_803336B4,
};

static char* s_SlotBTextByLanguage[6] = {
    (char*)lbl_803336C4,
    (char*)s_Steckplatz_B_801E65E4,
    (char*)lbl_803336C4,
    (char*)lbl_803336C4,
    (char*)s_Ranura_B_801E65F4,
    0,
};

static WinMessEntry s_WinMessTable[36] = {
    {{ 0x00000003, 0x00010000, 0x00020000, 0x00000000, 0x00000000 }},
    {{ 0x00000002, 0x00030004, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000002, 0x00050006, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000002, 0x00070008, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000005, 0x0009000A, 0x000B000C, 0x000D0000, 0x00000000 }},
    {{ 0x00000004, 0x000E000F, 0x0010000D, 0x00000000, 0x00000000 }},
    {{ 0x00000004, 0x00110012, 0x00130014, 0x00000000, 0x00000000 }},
    {{ 0x00000004, 0x00150016, 0x00170018, 0x00000000, 0x00000000 }},
    {{ 0x00000004, 0x0019001A, 0x001B001C, 0x00000000, 0x00000000 }},
    {{ 0x00000004, 0x001D001E, 0x001F0020, 0x00000000, 0x00000000 }},
    {{ 0x00000005, 0x00210022, 0x00230024, 0x00250000, 0x00000000 }},
    {{ 0x00000002, 0x00260027, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000002, 0x00280029, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000002, 0x002A002B, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x002C0000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x002D0000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x002E0000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x002F0000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000004, 0x00300031, 0x0032000D, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x00330000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x00340000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x00350000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x00360000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000003, 0x00010002, 0x00030000, 0x00000000, 0x00000000 }},
    {{ 0x00000003, 0x00040005, 0x00060000, 0x00000000, 0x00000000 }},
    {{ 0x00000003, 0x00070008, 0x00090000, 0x00000000, 0x00000000 }},
    {{ 0x00000003, 0x000A000B, 0x000C0000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x000D0000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x000E0000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000003, 0x00140015, 0x00160000, 0x00000000, 0x00000000 }},
    {{ 0x00000006, 0x00170018, 0x0019001A, 0x001B001C, 0x00000000 }},
    {{ 0x00000001, 0x001D0000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x001E0000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x00320000, 0x00000000, 0x00000000, 0x00000000 }},
    {{ 0x00000001, 0x00320000, 0x00000000, 0x00000000, 0x00000000 }},
};

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
    unsigned char languageId = Game.m_gameWork.m_languageId;
    CFont* font;
    const char* slotAText;

    switch (languageId) {
    case 2:
        slotAText = s_McWinMessGroup0_de[2];
        break;
    case 3:
        slotAText = s_McWinMessGroup0_it[2];
        break;
    case 4:
        slotAText = s_McWinMessGroup0_es[2];
        break;
    case 5:
        slotAText = s_McWinMessGroup0_fr[2];
        break;
    case 1:
    default:
        slotAText = s_McWinMessGroup0_en[2];
        break;
    }

    font = menuFont;
    font->SetMargin(FLOAT_803336CC);
    font->SetShadow(0);
    font->SetScale(FLOAT_803336CC);
    font->SetTlut(0x23);

    const int slotAWidth = (int)font->GetWidth((char*)(slotAText + 1));
    short* windowInfo = singWindowInfo;
    double centeredWidth = (double)(windowInfo[2] - slotAWidth);
    double windowLeft = (double)windowInfo[0];
    int x = (int)(centeredWidth * DOUBLE_803336D0 + windowLeft);
    if (right != 0) {
        const int slotBWidth = (int)font->GetWidth((char*)s_SlotBTextByLanguage[languageId - 1]);
        x += slotAWidth - slotBWidth;
    }
    return x - 0x1e;
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
    unsigned char languageId = Game.m_gameWork.m_languageId;
    CFont* font;
    const char* yesText;

    switch (languageId) {
    case 2:
        yesText = s_McWinMessGroup0_de[13];
        break;
    case 3:
        yesText = s_McWinMessGroup0_it[13];
        break;
    case 4:
        yesText = s_McWinMessGroup0_es[13];
        break;
    case 5:
        yesText = s_McWinMessGroup0_fr[13];
        break;
    case 1:
    default:
        yesText = s_McWinMessGroup0_en[13];
        break;
    }

    font = menuFont;
    font->SetMargin(FLOAT_803336CC);
    font->SetShadow(0);
    font->SetScale(FLOAT_803336CC);

    const int yesWidth = (int)font->GetWidth((char*)(yesText + 1));
    short* windowInfo = singWindowInfo;
    double centeredWidth = (double)(windowInfo[2] - yesWidth);
    double windowLeft = (double)windowInfo[0];
    int x = (int)(centeredWidth * DOUBLE_803336D0 + windowLeft);
    if (right != 0) {
        const int noWidth = (int)font->GetWidth((char*)s_NoTextByLanguage[languageId - 1]);
        x += yesWidth - noWidth;
    }
    return x - 0x1e;
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
int CMenuPcs::GetWinMess(int index)
{
    int languageId = Game.m_gameWork.m_languageId;

    if ((languageId != 1) && (languageId >= 1) && (languageId < 6)) {
        return reinterpret_cast<int>(&s_WinMessTable[index]);
    }
    return reinterpret_cast<int>(&s_WinMessTable[index]);
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
    unsigned char languageId = Game.m_gameWork.m_languageId;
    const char* const* result;

    if (group == 0) {
        switch (languageId) {
        case 2:
            result = s_McWinMessGroup0_de;
            break;
        case 3:
            result = s_McWinMessGroup0_it;
            break;
        case 4:
            result = s_McWinMessGroup0_es;
            break;
        case 5:
            result = s_McWinMessGroup0_fr;
            break;
        case 1:
        default:
            result = s_McWinMessGroup0_en;
            break;
        }
    } else if (group == 1) {
        switch (languageId) {
        case 2:
            result = s_McWinMessGroup1_de;
            break;
        case 3:
            result = s_McWinMessGroup1_it;
            break;
        case 4:
            result = s_McWinMessGroup1_es;
            break;
        case 5:
            result = s_McWinMessGroup1_fr;
            break;
        case 1:
        default:
            result = s_McWinMessGroup1_en;
            break;
        }
    } else {
        switch (languageId) {
        case 2:
            result = s_McWinMessGroup2_de;
            break;
        case 3:
            result = s_McWinMessGroup2_it;
            break;
        case 4:
            result = s_McWinMessGroup2_es;
            break;
        case 5:
            result = s_McWinMessGroup2_fr;
            break;
        case 1:
        default:
            result = s_McWinMessGroup2_en;
            break;
        }
    }
    return result;
}

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
    unsigned char languageId = Game.m_gameWork.m_languageId;

    switch (languageId) {
    case 2:
        return PTR_s_Der_Spielstand_ist_fehlerhaft_[index];
    case 3:
        return PTR_s_I_dati_sono_danneggiati_[index];
    case 4:
        return s_McStr_es[index];
    case 5:
        return s_McStr_fr[index];
    case 1:
    default:
        return PTR_s_The_data_is_corrupt_[index];
    }
}
