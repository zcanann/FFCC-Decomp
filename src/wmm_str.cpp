#include "ffcc/wmm_str.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"

extern const char sWmmEmptyEn[] = "Empty.";
extern const char sWmmEmptyIt[] = "Vuoto.";
extern const char sWmmEmptyFr[] = "Vide";
extern const char sWmmEmptyEs[8] = {'V', 'a', 'c', (char)0xED, 'o', '.', '\0', '\0'};
extern const char sWmmBlankText[4] = {0, 0, 0, 0};
extern const char sWmmWerdenText[] = "werden.";
extern const char sWmmAuswahlText[] = "Auswahl";
extern const char sWmmNo[] = "No";
extern const char sWmmNein[] = "Nein";
extern const char sWmmNon[] = "Non";
extern const char sWmmSlotB[] = "Slot B";
extern const char sWmmSteckplatzB[];
extern const char sWmmRanuraB[];

extern const float kWmmWindowTextScale = 1.0f;
extern const double kWmmCenteringHalf = 0.5;
extern const double kWmmUnsignedToDoubleBias = 4503601774854144.0;

extern const char* s_McStr_en[];
extern const char* s_McStr_de[];
extern const char* s_McStr_it[];
extern const char* s_McStr_es[];
extern const char* s_McStr_fr[];
extern const char* s_McWinMessGroup0_en[];
extern const char* s_McWinMessGroup0_de[];
extern const char* s_McWinMessGroup0_it[];
extern const char* s_McWinMessGroup0_es[];
extern const char* s_McWinMessGroup0_fr[];
extern const char* s_McWinMessGroup1_en[];
extern const char* s_McWinMessGroup1_de[];
extern const char* s_McWinMessGroup1_it[];
extern const char* s_McWinMessGroup1_es[];
extern const char* s_McWinMessGroup1_fr[];
extern const char* s_McWinMessGroup2_en[];
extern const char* s_McWinMessGroup2_de[];
extern const char* s_McWinMessGroup2_it[];
extern const char* s_McWinMessGroup2_es[];
extern const char* s_McWinMessGroup2_fr[];

struct WinMessEntry
{
    unsigned int words[5];
};

extern WinMessEntry s_WinMessTable[];
extern char* s_NoTextByLanguage[];
extern char* s_SlotBTextByLanguage[];

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

    font = m_fonts[0];
    font->SetMargin(kWmmWindowTextScale);
    font->SetShadow(0);
    font->SetScale(kWmmWindowTextScale);
    font->SetTlut(0x23);

    const int slotAWidth = (int)font->GetWidth((char*)(slotAText + 1));
    MenuWindowInfo* windowInfo = m_menuWindowInfo;
    double centeredWidth = (double)(windowInfo->width - slotAWidth);
    double windowLeft = (double)windowInfo->x;
    int x = (int)(centeredWidth * kWmmCenteringHalf + windowLeft);
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

    font = m_fonts[0];
    font->SetMargin(kWmmWindowTextScale);
    font->SetShadow(0);
    font->SetScale(kWmmWindowTextScale);

    const int yesWidth = (int)font->GetWidth((char*)(yesText + 1));
    MenuWindowInfo* windowInfo = m_menuWindowInfo;
    double centeredWidth = (double)(windowInfo->width - yesWidth);
    double windowLeft = (double)windowInfo->x;
    int x = (int)(centeredWidth * kWmmCenteringHalf + windowLeft);
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
        return s_McStr_de[index];
    case 3:
        return s_McStr_it[index];
    case 4:
        return s_McStr_es[index];
    case 5:
        return s_McStr_fr[index];
    case 1:
    default:
        return s_McStr_en[index];
    }
}

#include "src/wmm_str_data.inc"

WinMessEntry s_WinMessTable[36] = {
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

char* s_NoTextByLanguage[5] = {
    (char*)sWmmNo,
    (char*)sWmmNein,
    (char*)sWmmNo,
    (char*)sWmmNon,
    (char*)sWmmNo,
};

char* s_SlotBTextByLanguage[6] = {
    (char*)sWmmSlotB,
    (char*)sWmmSteckplatzB,
    (char*)sWmmSlotB,
    (char*)sWmmSlotB,
    (char*)sWmmRanuraB,
    0,
};
