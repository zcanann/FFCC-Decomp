#include "ffcc/wmm_str.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"

extern const char sWmmEmptyEn[] = "Empty.";
extern const char sWmmEmptyIt[] = "Vuoto.";
extern const char sWmmEmptyFr[] = "Vide";
extern const char sWmmEmptyEs[8] = "Vac\xedo.";
extern const char sWmmBlankText[4] = "";
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

static inline float LoadFloat(const float& value)
{
    return value;
}

static inline double LoadDouble(const double& value)
{
    return value;
}

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
    font->SetMargin(LoadFloat(kWmmWindowTextScale));
    font->SetShadow(0);
    font->SetScale(LoadFloat(kWmmWindowTextScale));
    font->SetTlut(0x23);

    const int slotAWidth = (int)font->GetWidth((char*)(slotAText + 1));
    MenuWindowInfo* windowInfo = m_menuWindowInfo;
    double centeredWidth = (double)(windowInfo->width - slotAWidth);
    double windowLeft = (double)windowInfo->x;
    double half = LoadDouble(kWmmCenteringHalf);
    int x = (int)(centeredWidth * half + windowLeft);
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
    font->SetMargin(LoadFloat(kWmmWindowTextScale));
    font->SetShadow(0);
    font->SetScale(LoadFloat(kWmmWindowTextScale));

    const int yesWidth = (int)font->GetWidth((char*)(yesText + 1));
    MenuWindowInfo* windowInfo = m_menuWindowInfo;
    double centeredWidth = (double)(windowInfo->width - yesWidth);
    double windowLeft = (double)windowInfo->x;
    double half = LoadDouble(kWmmCenteringHalf);
    int x = (int)(centeredWidth * half + windowLeft);
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
WinMessEntry* CMenuPcs::GetWinMess(int index)
{
    int languageId = Game.m_gameWork.m_languageId;

    if ((languageId != 1) && (languageId >= 1) && (languageId < 6)) {
        return &s_WinMessTable[index];
    }
    return &s_WinMessTable[index];
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
    { 3, { 1, 0, 2, 0, 0, 0, 0, 0 } },
    { 2, { 3, 4, 0, 0, 0, 0, 0, 0 } },
    { 2, { 5, 6, 0, 0, 0, 0, 0, 0 } },
    { 2, { 7, 8, 0, 0, 0, 0, 0, 0 } },
    { 5, { 9, 10, 11, 12, 13, 0, 0, 0 } },
    { 4, { 14, 15, 16, 13, 0, 0, 0, 0 } },
    { 4, { 17, 18, 19, 20, 0, 0, 0, 0 } },
    { 4, { 21, 22, 23, 24, 0, 0, 0, 0 } },
    { 4, { 25, 26, 27, 28, 0, 0, 0, 0 } },
    { 4, { 29, 30, 31, 32, 0, 0, 0, 0 } },
    { 5, { 33, 34, 35, 36, 37, 0, 0, 0 } },
    { 2, { 38, 39, 0, 0, 0, 0, 0, 0 } },
    { 2, { 40, 41, 0, 0, 0, 0, 0, 0 } },
    { 2, { 42, 43, 0, 0, 0, 0, 0, 0 } },
    { 1, { 44, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 45, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 46, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 47, 0, 0, 0, 0, 0, 0, 0 } },
    { 4, { 48, 49, 50, 13, 0, 0, 0, 0 } },
    { 1, { 51, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 52, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 53, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 54, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, { 1, 2, 3, 0, 0, 0, 0, 0 } },
    { 3, { 4, 5, 6, 0, 0, 0, 0, 0 } },
    { 3, { 7, 8, 9, 0, 0, 0, 0, 0 } },
    { 3, { 10, 11, 12, 0, 0, 0, 0, 0 } },
    { 1, { 13, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 14, 0, 0, 0, 0, 0, 0, 0 } },
    { 0, { 0, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, { 20, 21, 22, 0, 0, 0, 0, 0 } },
    { 6, { 23, 24, 25, 26, 27, 28, 0, 0 } },
    { 1, { 29, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 30, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 50, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, { 50, 0, 0, 0, 0, 0, 0, 0 } },
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
