#include "ffcc/wmm_str.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"

#include "src/wmm_str_data.inc"

/*
 * --INFO--
 * PAL Address: 0x8017AF14
 * PAL Size: 396b
 * EN Address: 0x80179E64
 * EN Size: 396b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetSlotABXPos(int right)
{
    static const char* s_SlotStr[] = { "Slot B", "Steckplatz B", "Slot B", "Slot B", "Ranura B" };

    unsigned char languageId = Game.m_gameWork.m_languageId;
    CFont* font;
    const char* slotAText;

    switch (languageId) {
    case 2:
        slotAText = s_McWinMessStr_ge[2];
        break;
    case 3:
        slotAText = s_McWinMessStr_it[2];
        break;
    case 4:
        slotAText = s_McWinMessStr_fr[2];
        break;
    case 5:
        slotAText = s_McWinMessStr_sp[2];
        break;
    case 1:
    default:
        slotAText = s_McWinMessStr_us[2];
        break;
    }

    font = m_fonts[0];
    font->SetMargin(1.0f);
    font->SetShadow(0);
    font->SetScale(1.0f);
    font->SetTlut(0x23);

    const int slotAWidth = (int)font->GetWidth((char*)(slotAText + 1));
    MenuWindowInfo* windowInfo = m_menuWindowInfo;
    double centeredWidth = (double)(windowInfo->width - slotAWidth);
    double windowLeft = (double)windowInfo->x;
    double half = 0.5;
    int x = (int)(centeredWidth * half + windowLeft);
    if (right != 0) {
        const int slotBWidth = (int)font->GetWidth((char*)s_SlotStr[languageId - 1]);
        x += slotAWidth - slotBWidth;
    }
    return x - 0x1e;
}

/*
 * --INFO--
 * PAL Address: 0x8017B0A0
 * PAL Size: 384b
 * EN Address: 0x80179FF0
 * EN Size: 384b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetYesNoXPos(int right)
{
    static const char* s_NoStr[] = { "No", "Nein", "No", "Non", "No" };

    unsigned char languageId = Game.m_gameWork.m_languageId;
    CFont* font;
    const char* yesText;

    switch (languageId) {
    case 2:
        yesText = s_McWinMessStr_ge[13];
        break;
    case 3:
        yesText = s_McWinMessStr_it[13];
        break;
    case 4:
        yesText = s_McWinMessStr_fr[13];
        break;
    case 5:
        yesText = s_McWinMessStr_sp[13];
        break;
    case 1:
    default:
        yesText = s_McWinMessStr_us[13];
        break;
    }

    font = m_fonts[0];
    font->SetMargin(1.0f);
    font->SetShadow(0);
    font->SetScale(1.0f);

    const int yesWidth = (int)font->GetWidth((char*)(yesText + 1));
    MenuWindowInfo* windowInfo = m_menuWindowInfo;
    double centeredWidth = (double)(windowInfo->width - yesWidth);
    double windowLeft = (double)windowInfo->x;
    double half = 0.5;
    int x = (int)(centeredWidth * half + windowLeft);
    if (right != 0) {
        const int noWidth = (int)font->GetWidth((char*)s_NoStr[languageId - 1]);
        x += yesWidth - noWidth;
    }
    return x - 0x1e;
}

/*
 * --INFO--
 * PAL Address: 0x8017B220
 * PAL Size: 72b
 * EN Address: 0x8017A170
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
WinMessEntry* CMenuPcs::GetWinMess(int index)
{
    int languageId = Game.m_gameWork.m_languageId;

    switch (languageId) {
    case 2:
    case 3:
    case 4:
    case 5:
        return &s_WinMess_us[index];
    case 1:
    default:
        return &s_WinMess_us[index];
    }
}

/*
 * --INFO--
 * PAL Address: 0x8017B268
 * PAL Size: 400b
 * EN Address: 0x8017A1B8
 * EN Size: 400b
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
            result = s_McWinMessStr_ge;
            break;
        case 3:
            result = s_McWinMessStr_it;
            break;
        case 4:
            result = s_McWinMessStr_fr;
            break;
        case 5:
            result = s_McWinMessStr_sp;
            break;
        case 1:
        default:
            result = s_McWinMessStr_us;
            break;
        }
    } else if (group == 1) {
        switch (languageId) {
        case 2:
            result = s_McWinMessStr2_ge;
            break;
        case 3:
            result = s_McWinMessStr2_it;
            break;
        case 4:
            result = s_McWinMessStr2_fr;
            break;
        case 5:
            result = s_McWinMessStr2_sp;
            break;
        case 1:
        default:
            result = s_McWinMessStr2_us;
            break;
        }
    } else {
        switch (languageId) {
        case 2:
            result = s_McWinGoOutMessStr_ge;
            break;
        case 3:
            result = s_McWinGoOutMessStr_it;
            break;
        case 4:
            result = s_McWinGoOutMessStr_fr;
            break;
        case 5:
            result = s_McWinGoOutMessStr_sp;
            break;
        case 1:
        default:
            result = s_McWinGoOutMessStr_us;
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
        return s_McStr_ge[index];
    case 3:
        return s_McStr_it[index];
    case 4:
        return s_McStr_fr[index];
    case 5:
        return s_McStr_sp[index];
    case 1:
    default:
        return s_McStr_us[index];
    }
}
