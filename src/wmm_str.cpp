#include "ffcc/wmm_str.h"
#include "ffcc/fontman.h"
#include "ffcc/p_game.h"

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

extern const float FLOAT_803336CC;
extern const double DOUBLE_803336D0;

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
const char* CMenuPcs::GetWinMess(int index)
{
    int languageId = Game.m_gameWork.m_languageId;
    if ((languageId != 1) && (languageId >= 1) && (languageId < 6)) {
        return &s_WinMessTable[index * 0x14];
    }
    return &s_WinMessTable[index * 0x14];
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
        return PTR_s_Der_Spielstand_ist_fehlerhaft__80215be8[index];
    case 3:
        return PTR_s_I_dati_sono_danneggiati__80215bf8[index];
    case 4:
        return s_McStr_es[index];
    case 5:
        return s_McStr_fr[index];
    case 1:
    default:
        return PTR_s_The_data_is_corrupt__80215bd8[index];
    }
}
