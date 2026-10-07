#include "ffcc/shopmenu.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/materialman.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/itemobj.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/sound.h"
#include "ffcc/linkage.h"
#include "ffcc/mes.h"
#include "ffcc/memory.h"
#include "ffcc/p_tina.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>


#pragma readonly_strings on
#ifdef VERSION_GCCJGC
#include "ffcc/joybusconst.h"
#include "ffcc/cardconst.h"
#endif
extern char s_shopmenu_cpp[];
extern char s_pcts_pctd_Error_memory_allocation_error_801DED9C[];
unsigned short gShopMenuInputLatch;
extern const unsigned int gShopMenuAmbientWhite;
extern const unsigned int gShopMenuMaterialWhiteBase;
extern const unsigned int DAT_80332D04;
extern const unsigned int DAT_80332D08;
extern const unsigned int DAT_80332D0C;
extern const float FLOAT_80332D10;
extern const char s_DecimalFormat_80332d14[];
extern const char s_TwoDigitFormat_80332d18[];
extern const double DOUBLE_80332D20;
extern const float FLOAT_80332d28;
extern const float FLOAT_80332d2c;
extern const char s_Colon_80332d30[];
extern const float FLOAT_80332d34;
extern const char s_PlusOne_80332d38[];
extern const float FLOAT_80332d3c;
extern const char s_StringFormat_80332d40[];
extern const char s_StringDecimalFormat_80332d44[];
extern const char s_Plus_80332d4c[];
extern const char s_Minus_80332d50[];
extern const float FLOAT_80332d54;
extern const float FLOAT_80332d58;
extern const float FLOAT_80332d5c;
extern const float FLOAT_80332d60;
extern const float FLOAT_80332d64;
extern const float FLOAT_80332d68;
extern const float FLOAT_80332d6c;
extern const float FLOAT_80332d70;
extern const float FLOAT_80332d74;
extern const float FLOAT_80332d78;
extern const float FLOAT_80332d7c;
extern const float FLOAT_80332d80;
extern const char s_Slash_80332d84[];
extern const float FLOAT_80332d88;
extern const float FLOAT_80332d8c;
extern const float FLOAT_80332d90;
extern const float FLOAT_80332d94;
extern const float FLOAT_80332d98;
extern const float FLOAT_80332D9C;
extern const float FLOAT_80332DC8;
extern const float FLOAT_80332DCC;
extern const float FLOAT_80332DD0;
extern const float FLOAT_80332DD4;
extern const float FLOAT_80332DD8;
extern const float FLOAT_80332DDC;
extern const float FLOAT_80332DE0;
extern const float FLOAT_80332DE4;
extern const float FLOAT_80332DE8;
extern const float FLOAT_80332DEC;
extern const float FLOAT_80332DF0;
extern const float FLOAT_80332DF4;
extern const float FLOAT_80332DF8;
extern const float FLOAT_80332DFC;
extern const float FLOAT_80332E00;
extern const float FLOAT_80332E04;
extern const float FLOAT_80332E08;
extern const float FLOAT_80332E0C;
extern const float FLOAT_80332E10;
extern const float FLOAT_80332E14;
extern const float FLOAT_80332E18;
extern const float FLOAT_80332E1C;
extern const float FLOAT_80332E20;
extern const float FLOAT_80332E24;
extern const float FLOAT_80332E28;
extern const float FLOAT_80332E2C;
extern const float FLOAT_80332E30;
extern const float FLOAT_80332E34;
extern const float FLOAT_80332E38;
extern const float FLOAT_80332E3C;
extern const char lbl_80332E40[];
extern const float FLOAT_80332E44;
extern const float FLOAT_80332e48;
extern const float FLOAT_80332e4c;
extern const float FLOAT_80332E50;
extern const char s_shop_80332e54[];
extern char s_Blacksmith_801DEB38[];
extern char s_Materials_801DEB44[];
extern char s_Cannot_buy_801DEB50[];
extern char s_Cannot_sell_801DEB5C[];
extern char s_Quantity_801DEB6C[];
extern char s_Strength_801DEB78[];
extern char s_Cannot_be_crafted_here_801DEB84[];
extern char s_Verkaufen_801DEB9C[];
extern char s_Abbrechen_801DEBA8[];
extern char s_Schmiede_801DEBB4[];
extern char s_Guthaben_801DEBC0[];
extern char lbl_801DEBCC[];
extern char s_Inventar_801DEBD8[];
extern char s_Herstellen_801DEBE4[];
extern char lbl_801DEBF0[];
extern char lbl_801DEBFC[];
extern char lbl_801DEC0C[];
extern char s_Anzahl_x_801DEC18[];
extern char s_Falsche_Schmiede_801DEC24[];
extern char s_Inventario_801DEC38[];
extern char s_Utilizza_801DEC44[];
extern char s_Non_puoi_acquistare_801DEC50[];
extern char s_Non_puoi_vendere_801DEC68[];
extern char lbl_801DEC7C[];
extern char s_Irrealizzabile_qui_801DEC88[];
extern char s_Forgeron_801DEC9C[];
extern char lbl_801DECA8[];
extern char s_En_stock_801DECB4[];
extern char s_Non_achetable_801DECC0[];
extern char s_Non_vendable_801DECD0[];
extern char lbl_801DECE0[];
extern char lbl_801DECEC[];
extern char s_Infaisable_ici_801DECF8[];
extern char s_Cancelar_801DED08[];
extern char s_Honorario_801DED14[];
extern char s_Materiales_801DED20[];
extern char s_Reservas_801DED2C[];
extern char lbl_801DED38[];
extern char s_No_puedes_comprar_801DED44[];
extern char s_No_vendible_801DED58[];
extern char s_Cantidad_801DED68[];
extern char lbl_801DED74[];
const char lbl_80332B40[] = "Buy";
const char lbl_80332B44[] = "Sell";
const char lbl_80332B4C[] = "Cancel";
const char lbl_80332B54[] = "Shop";
const char lbl_80332B5C[] = "For:";
const char lbl_80332B64[] = "gil";
const char lbl_80332B68[] = "Fee";
const char lbl_80332B6C[] = "Money";
const char lbl_80332B74[] = "Stock";
const char lbl_80332B7C[] = "Craft";
const char lbl_80332B84[] = "Equip";
const char lbl_80332B8C[] = "Price";
const char lbl_80332B94[] = "Defence";
const char lbl_80332B9C[4] = "";
const char lbl_80332BA0[] = "Kaufen";
const char lbl_80332BA8[] = "Laden";
const char lbl_80332BB0[8] = "F\374r:";
const char lbl_80332BB8[] = "Gil";
const char lbl_80332BBC[] = "Kosten";
const char lbl_80332BC4[] = "Preis";
const char lbl_80332BCC[8] = "St\344rke";
const char lbl_80332BD4[] = "Abwehr";
const char lbl_80332BDC[] = "Compra";
const char lbl_80332BE4[] = "Vendi";
const char lbl_80332BEC[] = "Annulla";
const char lbl_80332BF4[] = "Emporio";
const char lbl_80332BFC[] = "Fabbro";
const char lbl_80332C04[] = "Per:";
const char lbl_80332C0C[] = "guil";
const char lbl_80332C14[] = "Tariffa";
const char lbl_80332C1C[] = "Denaro";
const char lbl_80332C24[] = "Materie";
const char lbl_80332C2C[] = "Forgia";
const char lbl_80332C34[] = "Prezzo";
const char lbl_80332C3C[] = "Forza";
const char lbl_80332C44[] = "Difesa";
const char lbl_80332C4C[] = "Acheter";
const char lbl_80332C54[] = "Vendre";
const char lbl_80332C5C[] = "Annuler";
const char lbl_80332C64[] = "Magasin";
const char lbl_80332C6C[] = "Pour:";
const char lbl_80332C74[] = "gils";
const char lbl_80332C7C[] = "Tarif";
const char lbl_80332C84[] = "Argent";
const char lbl_80332C8C[] = "Forger";
const char lbl_80332C94[] = "Equiper";
const char lbl_80332C9C[] = "Prix";
const char lbl_80332CA4[] = "Force";
const char lbl_80332CAC[] = "Comprar";
const char lbl_80332CB4[] = "Vender";
const char lbl_80332CBC[] = "Herrero";
const char lbl_80332CC4[] = "Para:";
const char lbl_80332CCC[] = "guiles";
const char lbl_80332CD4[] = "Dinero";
const char lbl_80332CDC[] = "Equipar";
const char lbl_80332CE4[] = "Precio";
const char lbl_80332CEC[] = "Fuerza";
const char lbl_80332CF4[] = "Defensa";
extern const char s_DecimalFormat_80332d14[] = "%d";
extern const char s_TwoDigitFormat_80332d18[] = "%02d";
extern const char s_Colon_80332d30[] = ":";
extern const char s_PlusOne_80332d38[] = "+1";
extern const char s_StringFormat_80332d40[] = "%s";
extern const char s_StringDecimalFormat_80332d44[] = "%s%d";
extern const char s_Plus_80332d4c[] = "+";
extern const char s_Minus_80332d50[] = "-";
extern const char s_Slash_80332d84[] = "/";
extern const char lbl_80332E40[] = "x";
extern const char s_shop_80332e54[] = "shop";
extern "C" char* g_strShopMenuMes[105] = {
    (char*)lbl_80332B40,
    (char*)lbl_80332B44,
    (char*)lbl_80332B4C,
    (char*)lbl_80332B54,
    s_Blacksmith_801DEB38,
    (char*)lbl_80332B5C,
    (char*)lbl_80332B64,
    (char*)lbl_80332B68,
    (char*)lbl_80332B6C,
    s_Materials_801DEB44,
    (char*)lbl_80332B74,
    (char*)lbl_80332B7C,
    (char*)lbl_80332B84,
    (char*)lbl_80332B8C,
    s_Cannot_buy_801DEB50,
    s_Cannot_sell_801DEB5C,
    s_Quantity_801DEB6C,
    s_Strength_801DEB78,
    (char*)lbl_80332B94,
    (char*)lbl_80332B9C,
    s_Cannot_be_crafted_here_801DEB84,
    (char*)lbl_80332BA0,
    s_Verkaufen_801DEB9C,
    s_Abbrechen_801DEBA8,
    (char*)lbl_80332BA8,
    s_Schmiede_801DEBB4,
    (char*)lbl_80332BB0,
    (char*)lbl_80332BB8,
    (char*)lbl_80332BBC,
    s_Guthaben_801DEBC0,
    lbl_801DEBCC,
    s_Inventar_801DEBD8,
    s_Herstellen_801DEBE4,
    lbl_801DEBF0,
    (char*)lbl_80332BC4,
    lbl_801DEBFC,
    lbl_801DEC0C,
    s_Anzahl_x_801DEC18,
    (char*)lbl_80332BCC,
    (char*)lbl_80332BD4,
    (char*)lbl_80332B9C,
    s_Falsche_Schmiede_801DEC24,
    (char*)lbl_80332BDC,
    (char*)lbl_80332BE4,
    (char*)lbl_80332BEC,
    (char*)lbl_80332BF4,
    (char*)lbl_80332BFC,
    (char*)lbl_80332C04,
    (char*)lbl_80332C0C,
    (char*)lbl_80332C14,
    (char*)lbl_80332C1C,
    (char*)lbl_80332C24,
    s_Inventario_801DEC38,
    (char*)lbl_80332C2C,
    s_Utilizza_801DEC44,
    (char*)lbl_80332C34,
    s_Non_puoi_acquistare_801DEC50,
    s_Non_puoi_vendere_801DEC68,
    lbl_801DEC7C,
    (char*)lbl_80332C3C,
    (char*)lbl_80332C44,
    (char*)lbl_80332B9C,
    s_Irrealizzabile_qui_801DEC88,
    (char*)lbl_80332C4C,
    (char*)lbl_80332C54,
    (char*)lbl_80332C5C,
    (char*)lbl_80332C64,
    s_Forgeron_801DEC9C,
    (char*)lbl_80332C6C,
    (char*)lbl_80332C74,
    (char*)lbl_80332C7C,
    (char*)lbl_80332C84,
    lbl_801DECA8,
    s_En_stock_801DECB4,
    (char*)lbl_80332C8C,
    (char*)lbl_80332C94,
    (char*)lbl_80332C9C,
    s_Non_achetable_801DECC0,
    s_Non_vendable_801DECD0,
    lbl_801DECE0,
    (char*)lbl_80332CA4,
    lbl_801DECEC,
    (char*)lbl_80332B9C,
    s_Infaisable_ici_801DECF8,
    (char*)lbl_80332CAC,
    (char*)lbl_80332CB4,
    s_Cancelar_801DED08,
    (char*)lbl_80332CAC,
    (char*)lbl_80332CBC,
    (char*)lbl_80332CC4,
    (char*)lbl_80332CCC,
    s_Honorario_801DED14,
    (char*)lbl_80332CD4,
    s_Materiales_801DED20,
    s_Reservas_801DED2C,
    lbl_801DED38,
    (char*)lbl_80332CDC,
    (char*)lbl_80332CE4,
    s_No_puedes_comprar_801DED44,
    s_No_vendible_801DED58,
    s_Cantidad_801DED68,
    (char*)lbl_80332CEC,
    (char*)lbl_80332CF4,
    (char*)lbl_80332B9C,
    lbl_801DED74,
};

STATIC_ASSERT(offsetof(CShopMenu, m_mode) == 0x4);
STATIC_ASSERT(offsetof(CShopMenu, m_subMode) == 0x10);
STATIC_ASSERT(offsetof(CShopMenu, m_listType) == 0x14);
STATIC_ASSERT(offsetof(CShopMenu, m_pdtSlot) == 0x18);
STATIC_ASSERT(offsetof(CShopMenu, m_fade) == 0x1C);
STATIC_ASSERT(offsetof(CShopMenu, m_caravanWork) == 0x20);
STATIC_ASSERT(offsetof(CShopMenu, m_selectedIndex) == 0x28);
STATIC_ASSERT(offsetof(CShopMenu, m_quantity) == 0x44);
STATIC_ASSERT(offsetof(CShopMenu, m_topChoice) == 0x48);
STATIC_ASSERT(offsetof(CShopMenu, m_itemCount) == 0x4C);
STATIC_ASSERT(sizeof(CShopMenu) == 0x158);

struct ShopMenuTopMenuEntry {
    int x;
    int y;
    char* text;
};

#ifdef VERSION_GCCJGC
#define SHOP_JP_BUY "\x82\xA9\x82\xA4"
#define SHOP_JP_SELL "\x82\xA4\x82\xE9"
#define SHOP_JP_CANCEL "\x82\xC6\x82\xE8\x82\xAF\x82\xB5"

ShopMenuTopMenuEntry s_shopMenuTopMenuEntries[] = {
    {0x1AE, 0x78, SHOP_JP_BUY},
    {0x186, 0xDC, SHOP_JP_SELL},
    {0x1AE, 0x140, SHOP_JP_CANCEL},
};
ShopMenuTopMenuEntry* s_currentShopMenuTopMenuEntry;
#else
ShopMenuTopMenuEntry s_shopMenuTopMenuEntries[] = {
    {0x1AE, 0x78, 0},
    {0x186, 0xDC, 0},
    {0x1AE, 0x140, 0},
};
ShopMenuTopMenuEntry* s_currentShopMenuTopMenuEntry;
s8 s_shopMenuTopMenuTextInitialized;
#endif

enum ShopMenuTextIndex {
    SHOP_MENU_TEXT_BUY = 0,
    SHOP_MENU_TEXT_SELL = 1,
    SHOP_MENU_TEXT_CANCEL = 2,
    SHOP_MENU_TEXT_TITLE = 3,
    SHOP_MENU_TEXT_BLACKSMITH = 4,
    SHOP_MENU_TEXT_RACE = 5,
    SHOP_MENU_TEXT_GIL = 6,
    SHOP_MENU_TEXT_MAKE_PRICE = 7,
    SHOP_MENU_TEXT_MONEY = 8,
    SHOP_MENU_TEXT_MATERIALS = 9,
    SHOP_MENU_TEXT_STOCK = 10,
    SHOP_MENU_TEXT_CRAFT = 11,
    SHOP_MENU_TEXT_EQUIP = 12,
    SHOP_MENU_TEXT_PRICE = 13,
    SHOP_MENU_TEXT_CANNOT_BUY = 14,
    SHOP_MENU_TEXT_CANNOT_SELL = 15,
    SHOP_MENU_TEXT_QUANTITY = 16,
    SHOP_MENU_TEXT_STRENGTH = 17,
    SHOP_MENU_TEXT_DEFENCE = 18,
    SHOP_MENU_TEXT_CANNOT_CRAFT_HERE = 20,
};

#define ShopMenuMes(languageIndex, textIndex) (g_strShopMenuMes[(languageIndex) * 0x15 + (textIndex)])

static inline float CalcCenteredShopMenuX(CFont* font, const char* text, int centerX)
{
    centerX += (FLOAT_80332DD4 - font->GetWidth(text)) / 2;
    return static_cast<float>(centerX);
}

static inline void SetupShopMenuAmountFont(CFont* font)
{
    font->SetShadow(1);
    font->SetScaleX(FLOAT_80332d28);
    font->SetScaleY(FLOAT_80332d8c);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();
    font->SetFixed(1);
    font->SetMargin(FLOAT_80332d64);
}

static inline void SetupShopMenuMakeFont(CFont* font, float margin)
{
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();
    font->SetFixed(1);
    font->SetMargin(margin);
}

static inline void SetupShopMenuValueFont(CFont* font)
{
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();
    font->SetFixed(1);
    font->SetMargin(FLOAT_80332d34);
}

static inline void SetupShopMenuGilFont(CFont* font)
{
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();
    font->SetFixed(1);
    font->SetMargin(FLOAT_80332d64);
}

#define DrawShopMenuAmountTrunc(font, value, rightEdge, y, tlut)                                                       \
    do {                                                                                                               \
        char amountBuffer[64];                                                                                         \
        sprintf(amountBuffer, s_DecimalFormat_80332d14, (value));                                                      \
        float amountWidth = (font)->GetWidth(amountBuffer);                                                            \
        MenuPcs.DrawNoShadowFont((font), amountBuffer,                                                                 \
            static_cast<float>(static_cast<int>(static_cast<float>(rightEdge) - amountWidth)), (y), (tlut), 0x12);     \
        MenuPcs.DrawInit();                                                                                            \
    } while (0)


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void _drawNoShadowFont(CFont* font, char* text, float x, float y, int tlut, int flags)
{
	font->DrawInit();
	MenuPcs.DrawNoShadowFont(font, text, x, y, tlut, flags);
	MenuPcs.DrawInit();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void _drawShadowFont(CFont* font, char* text, float x, float y, int tlut, int flags)
{
	font->DrawInit();
	MenuPcs.DrawShadowFont(font, text, x, y, tlut, flags);
	MenuPcs.DrawInit();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 384b
 * EN Address: 0x80173D70
 * EN Size: 160b
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned short getButtonRepeat(int padIndex, unsigned short buttonMask)
{
    if (gShopMenuInputLatch == 0) {
        return Pad.GetButtonRepeat(padIndex) & buttonMask;
    }
    if ((Pad.GetButton(padIndex) & gShopMenuInputLatch) == 0) {
        gShopMenuInputLatch = 0;
    }
    return Pad.GetButtonDown(padIndex) & buttonMask;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: 0x80173E10
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void bButtonNoRepeat(unsigned short button)
{
    gShopMenuInputLatch = button;
}

/*
 * --INFO--
 * PAL Address: 0x801593f8
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::SetMode(int mode)
{
    m_mode = mode;
    m_timer = 0;

    switch (m_mode) {
    case 0:
        m_fade = FLOAT_80332D9C;
        m_topChoice = 0xFF;
        break;
    case 1:
        m_topChoice = 0;
        break;
    case 3:
        m_listType = 0;
        goto mode_3_6_common;
    case 6:
        m_listType = 1;
mode_3_6_common:
        m_subMode = 0;
        m_selectedIndex = -1;
        m_listTop = 0;
        m_visibleRows = 8;
        m_canScrollDown = 0;
        m_canScrollUp = 0;
        m_faceAlpha = 0;
        m_quantity = 1;
        m_figureMode = 0;
        m_yesNo = 0;
        break;
    case 4:
    case 7:
        m_selectedIndex = 0;
        m_listTop = 0;
        m_figureMode = 0;
        break;
    case 9: {
        m_fade = FLOAT_80332D9C;
        m_topChoice = 0xFF;
        m_listType = 2;
        m_subMode = 0;
        m_selectedIndex = 0;
        m_listTop = 0;
        m_visibleRows = 8;
        m_canScrollDown = 0;
        m_canScrollUp = 0;
        m_faceAlpha = 0;
        m_quantity = 1;
        m_figureMode = 0;
        m_yesNo = 0;
        m_resultParam = -1;
        m_itemCount = 0;

        for (int i = 0; i < 0x40; i++) {
            if (MenuPcs.GetItemType(i, 0) == 9) {
                m_itemTable[m_itemCount++] = i;
            }
        }

        if (m_itemCount == 0) {
            for (int i = 0; i < 8; i++) {
                m_itemTable[m_itemCount++] = -1;
            }
        }
        break;
    }
    case 10:
        m_topChoice = 0;
        break;
    case 12:
        m_yesNo = 0;
        break;
    case 13:
    case 14:
        break;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CShopMenu::getItemCnt()
{
    int listType = m_listType;
    if (listType == 0) {
        return m_caravanWork->m_shopListCount;
    }
    if (listType == 1) {
        return 0x40;
    }
    if (listType == 2) {
        return m_itemCount;
    }
    return -1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: 0x801740DC
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::calcGilRatio(int baseGil)
{
    return m_caravanWork->m_shopParam * baseGil / 100;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CShopMenu::getItemNo(int index)
{
    if (m_listType == 0) {
        return m_caravanWork->m_shopList[index];
    }
    if (m_listType == 1) {
        return m_caravanWork->m_inventoryItems[index];
    }
    if (m_listType == 2) {
        int mapped = m_itemTable[index];
        if (mapped == -1) {
            return -1;
        }
        return m_caravanWork->m_inventoryItems[mapped];
    }
    return -1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 84b
 * EN Address: 0x801741FC
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::getBuyGil(int itemNo)
{
    if (itemNo <= 0) {
        return 0;
    }
    return calcGilRatio(*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + 0x20 + itemNo * 0x48));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 140b
 * EN Address: 0x8017425C
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::getSellGil(int itemNo)
{
    if (itemNo <= 0) {
        return 0;
    }
    return static_cast<int>(FLOAT_80332d60 * static_cast<float>(calcGilRatio(
        *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + 0x20 + itemNo * 0x48))));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 84b
 * EN Address: 0x801742EC
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::getMakeGil(int itemNo)
{
    if (itemNo <= 0) {
        return 0;
    }
    return calcGilRatio(*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + 0x24 + itemNo * 0x48));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 296b
 * EN Address: 0x8017434C
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::getBuySellGil(int itemNo)
{
    int gil;
    if (m_listType == 0) {
        gil = getBuyGil(itemNo);
    } else if (m_listType == 1) {
        gil = getSellGil(itemNo);
    } else {
        gil = -1;
    }
    return gil;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: 0x801743F4
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
inline char* CShopMenu::GetItemName(int itemNo)
{
    if (itemNo <= 0) {
        return 0;
    }

    return Game.GetShortItemName(itemNo);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 16b
 * EN Address: 0x8017443C
 * EN Size: 16b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::GetMaxExchange()
{
    return 0x40 - m_caravanWork->m_inventoryItemCount;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 484b
 * EN Address: 0x8017444C
 * EN Size: 92b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::GetTotalGil()
{
    if (m_selectedIndex == -1) {
        return 0;
    }
    return m_quantity * getBuySellGil(getItemNo(m_selectedIndex));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 496b
 * EN Address: 0x801744A8
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::CanAddGil()
{
    int totalGil = GetTotalGil();
    return m_caravanWork->CanAddGil(-totalGil);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 380b
 * EN Address: 0x801744F0
 * EN Size: 316b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::CheckSell(int index)
{
    if (index == -1) {
        return 0;
    }

    int itemNo = getItemNo(index);
    if (itemNo <= 0) {
        return 0;
    }
    if (m_listType == 0) {
        return 1;
    }
    if (m_listType == 2) {
        int recipeNo = itemNo - 0x191;
        if ((m_caravanWork->m_shopArgs[recipeNo >> 5] & (1U << (recipeNo & 0x1F))) != 0) {
            return 1;
        }
        return 0;
    }
    if (MenuPcs.EquipChk(index)) {
        return 0;
    }
    if (itemNo > 0x9E) {
        return 1;
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 232b
 * EN Address: 0x8017462C
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CShopMenu::getItemHaveCnt(int itemNo)
{
    int count;
    int i;
    for (i = 0, count = 0; i < 0x40; i++) {
        if (m_caravanWork->m_inventoryItems[i] == itemNo) {
            count++;
        }
    }
    return count;
}

static inline void SetupShopMenuShapeDrawColor(unsigned char alpha)
{
    _GXColor drawColor = {0xFF, 0xFF, 0xFF, alpha};
    GXSetChanAmbColor(GX_COLOR0A0, drawColor);
    GXSetChanMatColor(GX_COLOR0A0, drawColor);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void setOrtho(int x, int y, float scaleX, float scaleY, float zOffset)
{
    Mtx screenMtx;
    Mtx44 projectionMtx;

    PSMTXIdentity(screenMtx);
    screenMtx[0][0] = scaleX;
    screenMtx[1][1] = scaleY;
    screenMtx[2][2] = FLOAT_80332d78;
    screenMtx[0][3] = static_cast<float>(x);
    screenMtx[1][3] = static_cast<float>(y);
    GXLoadPosMtxImm(screenMtx, 0);
    GXSetCurrentMtx(0);

    C_MTXOrtho(projectionMtx, FLOAT_80332D9C, FLOAT_80332DEC, FLOAT_80332D9C, FLOAT_80332DF0, FLOAT_80332D9C,
               FLOAT_80332d28);
    projectionMtx[2][3] += zOffset;
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 224b
 * EN Address: 0x80174768
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void drawShp(tagOAN3_SHAPE* shape, CMaterialSet* materialSet, unsigned char tlut)
{
    MaterialMan.LockEnv();
    MaterialMan.SetMaterialMenu(materialSet, shape->m_entries[0].m_textureIndex, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    for (int i = 0; i < shape->m_shapeCount; i++) {
        GXCallDisplayList(shape->m_entries[i].m_displayList, 0x60);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void drawShapeSeq0(int shapeNo, int groupNo, unsigned char alpha, unsigned char tlut)
{
    pppShapeAnimData* shapeData = reinterpret_cast<pppShapeAnimData*>(ppvEnv->m_shapeTablePtr[shapeNo]->m_animData);
    pppShapeAnimFrame* frame = &shapeData->m_frames[groupNo];
    tagOAN3_SHAPE* shape = reinterpret_cast<tagOAN3_SHAPE*>(reinterpret_cast<unsigned char*>(shapeData) + frame->m_shapeOffset);

    _GXColor mat;
    *reinterpret_cast<unsigned int*>(&mat) = gShopMenuMaterialWhiteBase;
    mat.a = alpha;

    MaterialMan.InitEnv();
    MaterialMan.LockEnv();

    GXSetChanAmbColor(GX_COLOR0A0, *reinterpret_cast<_GXColor*>(const_cast<unsigned int*>(&gShopMenuAmbientWhite)));
    GXSetChanMatColor(GX_COLOR0A0, mat);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);

    drawShp(shape, ppvEnv->m_materialSetPtr, tlut);
}

/*
 * --INFO--
 * PAL Address: 0x80159114
 * PAL Size: 740b
 * EN Address: 0x801749EC
 * EN Size: 188b
 * JP Address: TODO
 * JP Size: TODO
 */
void drawShapeSeq(int shapeNo, int groupNo, int x, int y, unsigned char alpha, unsigned char flipX, unsigned char flipY,
                  float zOffset, unsigned char tlut)
{
    setOrtho(x, y, flipX != 0 ? FLOAT_80332DD0 : FLOAT_80332d78, flipY != 0 ? FLOAT_80332d78 : FLOAT_80332DD0, zOffset);
    drawShapeSeq0(shapeNo, groupNo, alpha, tlut);
}

/*
 * --INFO--
 * PAL Address: 0x80158E44
 * PAL Size: 720b
 * EN Address: 0x80174AA8
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
void drawShapeSeqScale(int shapeNo, int groupNo, int x, int y, float scaleX, float scaleY, unsigned char alpha)
{
    setOrtho(x, y, scaleX, -scaleY, FLOAT_80332D9C);
    drawShapeSeq0(shapeNo, groupNo, alpha, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80158AF4
 * PAL Size: 848b
 * EN Address: 0x80174B10
 * EN Size: 848b
 * JP Address: TODO
 * JP Size: TODO
 */
void drawShapeSeqGrouad(int shapeNo, int groupNo, int x, int y, float scaleX, float scaleY, _GXColor colorA,
                        _GXColor colorB, _GXColor colorC, _GXColor colorD)
{
    setOrtho(x, y, scaleX, -scaleY, FLOAT_80332D9C);

    pppShapeAnimData* shapeData = reinterpret_cast<pppShapeAnimData*>(ppvEnv->m_shapeTablePtr[shapeNo]->m_animData);
    pppShapeAnimFrame* frame = &shapeData->m_frames[groupNo];
    tagOAN3_SHAPE* shape = reinterpret_cast<tagOAN3_SHAPE*>(reinterpret_cast<unsigned char*>(shapeData) + frame->m_shapeOffset);

    MaterialMan.InitEnv();
    MaterialMan.LockEnv();

    _GXColor matColor = {0, 0, 0, 0};
    GXSetChanAmbColor(GX_COLOR0A0, *reinterpret_cast<_GXColor*>(const_cast<unsigned int*>(&DAT_80332D04)));
    GXSetChanMatColor(GX_COLOR0A0, matColor);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetZCompLoc(GX_TRUE);

    MaterialMan.LockEnv();
    MaterialMan.SetMaterialMenu(
        ppvEnv->m_materialSetPtr,
        shape->m_entries[0].m_textureIndex, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    Vec minPos;
    Vec maxPos;
    unsigned char* vertexData = shape->m_entries[0].m_displayList;
    *reinterpret_cast<unsigned int*>(&minPos.x) = *reinterpret_cast<unsigned int*>(vertexData + 3);
    *reinterpret_cast<unsigned int*>(&minPos.y) = *reinterpret_cast<unsigned int*>(vertexData + 7);
    minPos.z = FLOAT_80332D9C;
    *reinterpret_cast<unsigned int*>(&maxPos.x) = *reinterpret_cast<unsigned int*>(vertexData + 0x2B);
    *reinterpret_cast<unsigned int*>(&maxPos.y) = *reinterpret_cast<unsigned int*>(vertexData + 0x2F);
    maxPos.z = FLOAT_80332D9C;

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    Graphic.RenderTexQuadGrouad(minPos, maxPos, colorA, colorB, colorC, colorD);
}

/*
 * --INFO--
 * PAL Address: 0x801589d0
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CreateShopMenu()
{
    m_shopMenu = reinterpret_cast<CShopMenu*>(
        operator new(0x158, (Game.m_gameWork.m_menuStageMode != 0) ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage,
            s_shopmenu_cpp, 0x2E2));
    m_shopMenu->Init(0);
}

/*
 * --INFO--
 * PAL Address: 0x801588ac
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CreateSmithMenu()
{
    m_shopMenu = reinterpret_cast<CShopMenu*>(
        operator new(0x158, (Game.m_gameWork.m_menuStageMode != 0) ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage,
            s_shopmenu_cpp, 0x2E9));
    m_shopMenu->Init(9);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 156b
 * EN Address: 0x80175348
 * EN Size: 192b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DestroyShopMenu()
{
    Game.m_scriptFoodBase[0]->CallShop(0, 0, 0, 0, 0);
    m_singleFadeState->done = 1;
    operator delete(m_shopMenu);
    m_shopMenu = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::Init(int mode)
{
    CPartMng::PppPdtSlot* slot;
    pppCacheChunk* cacheChunks;

    Graphic._WaitDrawDone(s_shopmenu_cpp, 0x2FE);
    m_unk00 = nullptr;
    m_caravanWork = Game.m_scriptFoodBase[0];
    SetMode(mode);
    m_pdtSlot = PartPcs.LoadMenuPdt(const_cast<char*>(s_shop_80332e54));

    slot = &PartMng.m_pdtSlots[m_pdtSlot];
    cacheChunks = slot->m_pppDataHead->m_cacheChunks;
    cacheChunks->m_pdt = reinterpret_cast<long*>(
        ppvAmemCacheSet.GetData(cacheChunks->m_cacheIndex, s_shopmenu_cpp, 0x32A));
    long* pdt = cacheChunks->m_pdt;
    pppCacheLoadShape(reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(pdt) + pdt[5]),
        slot->m_pppDataHead);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::Destroy()
{
    PartPcs.ReleasePdt(m_pdtSlot);
    MenuPcs.DestroyShopMenu();
}

/*
 * --INFO--
 * PAL Address: 0x801577ac
 * PAL Size: 4352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::Calc()
{
    int mode = m_mode;
    int& timer = m_timer;
    int& subMode = m_subMode;
    unsigned char& choice = m_topChoice;

    switch (mode) {
    case 0:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * FLOAT_80332E50;
        if (timer == 8) {
            this->SetMode(1);
        }
        break;
    case 1:
        if ((Pad.GetButtonDown(0) & 4) != 0) {
            ++choice;
            if (choice >= 3) {
                choice = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((Pad.GetButtonDown(0) & 8) != 0) {
            --choice;
            if (choice >= 3) {
                choice = 2;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((Pad.GetButtonDown(0) & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            this->SetMode(2);
        }

        if ((Pad.GetButtonDown(0) & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(2);
            choice = 2;
        }
        break;
    case 2:
        m_fade = static_cast<float>(8 - timer) * FLOAT_80332E50;
        if (timer == 8) {
            switch (choice) {
            case 0:
                this->SetMode(3);
                break;
            case 1:
                this->SetMode(6);
                break;
            case 2:
                Destroy();
                return;
            }
        }
        break;
    case 3:
        if (timer == 0) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * FLOAT_80332E50;
        if (timer == 8) {
            this->SetMode(4);
        }
        break;
    case 4:
        switch (subMode) {
        case 0:
            this->SelectItemIdx();
            if ((Pad.GetButtonDown(0) & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                this->SetMode(5);
            }
            break;
        case 1:
            this->SelectFigure();
            if ((Pad.GetButtonDown(0) & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                subMode = 0;
            }
            break;
        case 2:
            this->SelectYesNo();
            if ((Pad.GetButtonDown(0) & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                subMode = 1;
            }
            break;
        }
        break;
    case 5:
    case 8:
        m_fade = static_cast<float>(8 - timer) * FLOAT_80332E50;
        if (timer == 8) {
            this->SetMode(0);
        }
        break;
    case 6:
        if (timer == 0) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * FLOAT_80332E50;
        if (timer == 8) {
            this->SetMode(7);
        }
        break;
    case 7:
        switch (subMode) {
        case 0:
            this->SelectItemIdx();
            if ((Pad.GetButtonDown(0) & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                this->SetMode(8);
            }
            break;
        case 1:
            break;
        case 2:
            this->SelectYesNo();
            if ((Pad.GetButtonDown(0) & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                subMode = 0;
            }
            break;
        }
        break;
    case 9:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * FLOAT_80332E50;
        if (timer == 8) {
            this->SetMode(10);
        }
        break;
    case 10:
        this->SelectItemIdx();
        if ((Pad.GetButtonDown(0) & 0x200) != 0) {
            m_nextMode = -1;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(0xB);
        }
        break;
    case 11:
        m_fade = static_cast<float>(8 - timer) * FLOAT_80332E50;
        if (timer == 8) {
            if (m_nextMode == -1) {
                Destroy();
                return;
            }
            this->SetMode(m_nextMode);
        }
        break;
    case 12:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * FLOAT_80332E50;
        if (timer == 8) {
            this->SetMode(0xD);
        }
        break;
    case 13:
        this->SelectMake();
        if ((Pad.GetButtonDown(0) & 0x200) != 0) {
            m_nextMode = 9;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(0xE);
        }
        break;
    case 14:
        m_fade = static_cast<float>(8 - timer) * FLOAT_80332E50;
        if (timer == 8) {
            this->SetMode(m_nextMode);
        }
        break;
    case 15:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * FLOAT_80332E50;
        if (timer == 8) {
            CMenuPcs::MaterialInfo recipeMaterial;

            MenuPcs.GetRecipeMaterial(getItemNo(m_selectedIndex), &recipeMaterial);
            m_caravanWork->AddGil(-getMakeGil(getItemNo(m_selectedIndex)));
            m_caravanWork->DeleteItem(getItemNo(m_selectedIndex), 0);

            for (int i = 0; i < 3; i++) {
                if (recipeMaterial.m_itemNo[i] <= 0) {
                    break;
                }
                for (int count = 0; count < recipeMaterial.m_count[i]; count++) {
                    m_caravanWork->DeleteItem(recipeMaterial.m_itemNo[i], 0);
                }
            }

            m_caravanWork->AddItem(m_resultItem, &m_resultParam);
            this->SetMode(0x10);
        }
        break;
    case 16:
        this->SelectSOUBI();
        break;
    case 17:
        m_fade = static_cast<float>(8 - timer) * FLOAT_80332E50;
        if (timer == 8) {
            this->SetMode(m_nextMode);
        }
        break;
    }

    ++timer;
}

/*
 * --INFO--
 * PAL Address: 0x80156b4c
 * PAL Size: 3168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::SelectItemIdx()
{
    m_quantity = 1;

    if (m_selectedIndex >= getItemCnt()) {
        m_selectedIndex = getItemCnt() - 1;
    }

    if (getButtonRepeat(0, 8) != 0) {
        --m_selectedIndex;
        if (m_selectedIndex < 0) {
            bButtonNoRepeat(8);
            m_selectedIndex = 0;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    } else if (getButtonRepeat(0, 4) != 0) {
        ++m_selectedIndex;
        if (m_selectedIndex >= getItemCnt()) {
            bButtonNoRepeat(4);
            m_selectedIndex = getItemCnt() - 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    } else if ((Pad.GetButtonDown(0) & 0x100) != 0) {
        int canSelect;
        m_figureMode = 0;
        m_yesNo = 0;

        int listType = m_listType;
        if (listType == 0) {
            canSelect = CheckSell(m_selectedIndex);
            if (canSelect != 0) {
                CCaravanWork* caravanWork = m_caravanWork;
                if (m_quantity <= GetMaxExchange()) {
                    if (CanAddGil() != 0) {
                        m_subMode = 1;
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                        goto updateWindow;
                    }
                }
            }
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else if (listType == 1) {
            canSelect = CheckSell(m_selectedIndex);
            if (canSelect != 0) {
                m_subMode = 2;
                Sound.PlaySe(2, 0x40, 0x7F, 0);
            } else {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            }
        } else if (listType == 2) {
            canSelect = CheckSell(m_selectedIndex);
            if (canSelect != 0) {
                m_nextMode = 0xC;
                m_resultItem = MenuPcs.GetSmithItem(getItemNo(m_selectedIndex));
                SetMode(0xB);
                Sound.PlaySe(2, 0x40, 0x7F, 0);
            } else {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            }
        }
    }

updateWindow:
    if (m_listTop > m_selectedIndex) {
        m_listTop = m_selectedIndex;
    }
    if ((m_listTop + m_visibleRows) <= m_selectedIndex) {
        m_listTop = (m_selectedIndex - m_visibleRows) + 1;
    }
    if (m_listTop > 0) {
        m_canScrollUp = 1;
    } else {
        m_canScrollUp = 0;
    }
    if ((m_listTop + m_visibleRows) < getItemCnt()) {
        m_canScrollDown = 1;
    } else {
        m_canScrollDown = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80156170
 * PAL Size: 2524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::SelectFigure()
{
    if ((Pad.GetButtonDown(0) & 1) != 0) {
        ++m_figureMode;
        if (m_figureMode > 1) {
            m_figureMode = 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    } else if ((Pad.GetButtonDown(0) & 2) != 0) {
        --m_figureMode;
        if (m_figureMode < 0) {
            m_figureMode = 0;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    } else if ((Pad.GetButtonDown(0) & 0x100) != 0) {
        Sound.PlaySe(2, 0x40, 0x7F, 0);
        m_subMode = 2;
    }

    if (getButtonRepeat(0, 8) != 0) {
        switch (m_figureMode) {
        case 0: {
            ++m_quantity;
            if (m_quantity <= GetMaxExchange()) {
                if (CanAddGil() != 0) {
                    goto cancelInc1;
                }
            }

            bButtonNoRepeat(8);
            --m_quantity;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
            break;
        cancelInc1:
            Sound.PlaySe(1, 0x40, 0x7F, 0);
            break;
        }
        case 1: {
            m_quantity += 10;
            if (m_quantity <= GetMaxExchange()) {
                if (CanAddGil() != 0) {
                    goto cancelInc10;
                }
            }

            m_quantity -= 10;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
            break;
        cancelInc10:
            Sound.PlaySe(1, 0x40, 0x7F, 0);
            break;
        }
        }
        return;
    }

    if (getButtonRepeat(0, 4) == 0) {
        return;
    }

    switch (m_figureMode) {
    case 0:
        --m_quantity;
        if (m_quantity < 1) {
            bButtonNoRepeat(4);
            m_quantity = 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
        break;
    case 1:
        m_quantity -= 10;
        if (m_quantity < 1) {
            m_quantity += 10;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80155934
 * PAL Size: 2108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::SelectYesNo()
{
    if ((Pad.GetButtonDown(0) & 0xC) != 0) {
        m_yesNo ^= 1;
        Sound.PlaySe(1, 0x40, 0x7F, 0);
        return;
    }

    if ((Pad.GetButtonDown(0) & 0x100) == 0) {
        return;
    }

    switch (m_yesNo) {
    case 0:
        m_subMode = 0;
        if (m_listType == 0) {
            Sound.PlaySe(0x50, 0x40, 0x7F, 0);
            int itemId = getItemNo(m_selectedIndex);
            int quantity = 0;
            while (quantity < m_quantity) {
                CCaravanWork* caravanWork = m_caravanWork;
                unsigned char hasSpace = caravanWork->CanAddItem(1);
                if (hasSpace == 0) {
                    break;
                }
                int gilValue;
                if (m_listType == 0) {
                    if (itemId <= 0) {
                        gilValue = 0;
                    } else {
                        int gil = caravanWork->m_shopParam *
                                  reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2])[itemId].m_price;
                        gilValue = gil / 100;
                    }
                } else if (m_listType == 1) {
                    if (itemId <= 0) {
                        gilValue = 0;
                    } else {
                        int gil = caravanWork->m_shopParam *
                                  reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2])[itemId].m_price;
                        gilValue = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil / 100));
                    }
                } else {
                    gilValue = -1;
                }

                if (caravanWork->CanAddGil(-gilValue) == 0) {
                    return;
                }

                m_caravanWork->AddItem(itemId, 0);
                int gilValue2;
                if (m_listType == 0) {
                    if (itemId <= 0) {
                        gilValue2 = 0;
                    } else {
                        int gil = m_caravanWork->m_shopParam *
                                  reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2])[itemId].m_price;
                        gilValue2 = gil / 100;
                    }
                } else if (m_listType == 1) {
                    if (itemId <= 0) {
                        gilValue2 = 0;
                    } else {
                        int gil = m_caravanWork->m_shopParam *
                                  reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2])[itemId].m_price;
                        gilValue2 = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil / 100));
                    }
                } else {
                    gilValue2 = -1;
                }
                m_caravanWork->AddGil(-gilValue2);
                ++quantity;
            }
        } else if (CheckSell(m_selectedIndex) != 0) {
            Sound.PlaySe(0x50, 0x40, 0x7F, 0);
            int itemNo = getItemNo(m_selectedIndex);
            if (m_caravanWork->CanAddGil(getBuySellGil(itemNo)) != 0) {
                m_caravanWork->DeleteItemIdx(m_selectedIndex, 0);
                m_caravanWork->AddGil(getBuySellGil(itemNo));
            }
        } else {
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        }
        break;
    case 1:
        if (m_listType == 0) {
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            m_subMode = 1;
        } else {
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            m_subMode = 0;
        }
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801553a8
 * PAL Size: 1420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::SelectMake()
{
    int canSelect = MenuPcs.ChkEquipPossible(m_resultItem);
    canSelect = canSelect &&
                     (m_caravanWork->m_gil >= getMakeGil(getItemNo(m_selectedIndex)));

    int selected = getItemNo(m_selectedIndex);
    CMenuPcs::MaterialInfo recipeMaterial;
    MenuPcs.GetRecipeMaterial(selected, &recipeMaterial);

    short itemNo;
    for (int i = 0; i < 3; i++) {
        itemNo = recipeMaterial.m_itemNo[i];
        if (itemNo <= 0) {
            break;
        }

        canSelect = canSelect && (recipeMaterial.m_count[i] <= getItemHaveCnt(itemNo));
    }

    if (!canSelect) {
        m_yesNo = 1;
    }

    if ((Pad.GetButtonDown(0) & 0xC) != 0) {
        m_yesNo ^= 1;
        if (canSelect == 1) {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else {
            m_yesNo = 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        }
    } else if ((Pad.GetButtonDown(0) & 0x100) != 0) {
        switch (m_yesNo) {
        case 0:
            {
                int makeGil = getMakeGil(getItemNo(m_selectedIndex));
                if (m_caravanWork->CanAddGil(-makeGil) != 0) {
                    Sound.PlaySe(0x52, 0x40, 0x7F, 0);
                    m_nextMode = 0xF;
                    SetMode(0xE);
                    break;
                }
            }
        case 1:
            Sound.PlaySe(4, 0x40, 0x7F, 0);
            m_nextMode = 9;
            SetMode(0xE);
            break;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::SelectSOUBI()
{
    if ((Pad.GetButtonDown(0) & 0xC) != 0) {
        m_yesNo ^= 1;
        Sound.PlaySe(1, 0x40, 0x7F, 0);
    } else if ((Pad.GetButtonDown(0) & 0x100) != 0) {
        m_nextMode = 9;
        SetMode(0x11);

        switch (m_yesNo) {
        case 0: {
            int equipType = MenuPcs.GetEquipType(m_resultItem);
            m_caravanWork->ChgEquipPos(equipType, m_resultParam);
            Sound.PlaySe(0x51, 0x40, 0x7F, 0);
            break;
        }
        case 1:
            Sound.PlaySe(4, 0x40, 0x7F, 0);
            break;
        }
    }

    if ((Pad.GetButtonDown(0) & 0x200) != 0) {
        m_nextMode = 9;
        Sound.PlaySe(3, 0x40, 0x7F, 0);
        SetMode(0x11);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::DrawObi(int y)
{
    _GXColor colorA;
    _GXColor colorB;
    _GXColor colorC;
    _GXColor colorD;
    colorA.r = 0xFF; colorA.g = 0xFF; colorA.b = 0xFF; colorA.a = 0x00;
    colorC.r = 0xFF; colorC.g = 0xFF; colorC.b = 0xFF; colorC.a = 0x00;
    colorB.r = 0xFF; colorB.g = 0xFF; colorB.b = 0xFF; colorB.a = 0xFF;
    colorD.r = 0xFF; colorD.g = 0xFF; colorD.b = 0xFF; colorD.a = 0xFF;
    int x = 0x1C;
    drawShapeSeqGrouad(9, 0, x, y, FLOAT_80332d78, FLOAT_80332DC8, colorA, colorB, colorC, colorD);

    colorA.r = 0xFF; colorA.g = 0xFF; colorA.b = 0xFF; colorA.a = 0xFF;
    colorC.r = 0xFF; colorC.g = 0xFF; colorC.b = 0xFF; colorC.a = 0xFF;
    colorB.r = 0xFF; colorB.g = 0xFF; colorB.b = 0xFF; colorB.a = 0xFF;
    colorD.r = 0xFF; colorD.g = 0xFF; colorD.b = 0xFF; colorD.a = 0xFF;
    x += 0x20;
    while (x < 0x25C) {
        drawShapeSeqGrouad(9, 0, x, y, FLOAT_80332d78, FLOAT_80332DC8, colorA, colorB, colorC, colorD);
        x += 0x20;
    }

    colorA.r = 0xFF; colorA.g = 0xFF; colorA.b = 0xFF; colorA.a = 0xFF;
    colorC.r = 0xFF; colorC.g = 0xFF; colorC.b = 0xFF; colorC.a = 0xFF;
    colorB.r = 0xFF; colorB.g = 0xFF; colorB.b = 0xFF; colorB.a = 0x00;
    colorD.r = 0xFF; colorD.g = 0xFF; colorD.b = 0xFF; colorD.a = 0x00;
    drawShapeSeqGrouad(9, 0, x, y, FLOAT_80332d78, FLOAT_80332DC8, colorA, colorB, colorC, colorD);
}

/*
 * --INFO--
 * PAL Address: 0x80155058
 * PAL Size: 848b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifdef VERSION_GCCJGC
void CShopMenu::DrawShop0()
{
    DrawShopBase();

    for (int i = 0; i < 3; i++) {
        s_currentShopMenuTopMenuEntry = &s_shopMenuTopMenuEntries[i];
        int highlight = (m_topChoice == i) ? 1 : 0;

        Graphic.SetDrawDoneDebugData(0x1E);
        drawShapeSeq(0, highlight, s_currentShopMenuTopMenuEntry->x, s_currentShopMenuTopMenuEntry->y, 0xFF, 0, 0,
            FLOAT_80332D9C, 0);
        Graphic.SetDrawDoneDebugData(0x1F);
        drawShapeSeq(
            8, highlight, s_currentShopMenuTopMenuEntry->x - 0x30, s_currentShopMenuTopMenuEntry->y, 0xFF, 0, 0,
            FLOAT_80332D9C, 0);
        Graphic.SetDrawDoneDebugData(0x20);
    }

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(2.0f);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d8c);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    Graphic.SetDrawDoneDebugData(0x21);
    _drawNoShadowFont(font, "\x83\x56\x83\x87\x83\x62\x83\x76", FLOAT_80332d54, FLOAT_80332E30, 9, 0x12);

    Graphic.SetDrawDoneDebugData(0x22);
    font->SetMargin(FLOAT_80332d28);
    font->SetScale(FLOAT_80332d28);

    for (int i = 0; i < 3; i++) {
        s_currentShopMenuTopMenuEntry = &s_shopMenuTopMenuEntries[i];
        Graphic.SetDrawDoneDebugData(0x23);
        _drawNoShadowFont(font, s_currentShopMenuTopMenuEntry->text, s_currentShopMenuTopMenuEntry->x - 0x10,
            s_currentShopMenuTopMenuEntry->y - 0x0B, 0x18, 0x12);
        Graphic.SetDrawDoneDebugData(0x24);
    }

    MenuPcs.DrawInit();
    Graphic.SetDrawDoneDebugData(0x28);
}
#else
void CShopMenu::DrawShop0()
{
    int textId = SHOP_MENU_TEXT_BUY;
    int languageId = static_cast<int>(Game.m_gameWork.GetLanguage()) - 1;
    DrawShopBase();

    if (s_shopMenuTopMenuTextInitialized == 0) {
        char** mesTable = g_strShopMenuMes + languageId * 0x15;
        s_shopMenuTopMenuEntries[0].text = mesTable[textId++];
        s_shopMenuTopMenuEntries[1].text = mesTable[textId++];
        s_shopMenuTopMenuEntries[2].text = mesTable[textId++];
        s_shopMenuTopMenuTextInitialized = 1;
    }

    for (int i = 0; i < 3; i++) {
        s_currentShopMenuTopMenuEntry = &s_shopMenuTopMenuEntries[i];
        int highlight = (m_topChoice == i) ? 1 : 0;

        Graphic.SetDrawDoneDebugData(0x1E);
        int x = s_currentShopMenuTopMenuEntry->x;
        if (highlight != 0) {
            x += 8;
        }
        drawShapeSeq(0, highlight, x, s_currentShopMenuTopMenuEntry->y, 0xFF, 0, 0, FLOAT_80332D9C, 0);
        Graphic.SetDrawDoneDebugData(0x1F);
        drawShapeSeq(
            8, highlight, s_currentShopMenuTopMenuEntry->x - 0x30, s_currentShopMenuTopMenuEntry->y, 0xFF, 0, 0,
            FLOAT_80332D9C, 0);
        Graphic.SetDrawDoneDebugData(0x20);
    }

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d8c);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    Graphic.SetDrawDoneDebugData(0x21);
    _drawNoShadowFont(font, ShopMenuMes(languageId, SHOP_MENU_TEXT_TITLE), FLOAT_80332d54, FLOAT_80332E30, 9, 0x12);

    Graphic.SetDrawDoneDebugData(0x22);
    font->SetMargin(FLOAT_80332d28);
    font->SetScale(FLOAT_80332d28);

    for (int i = 0; i < 3; i++) {
        s_currentShopMenuTopMenuEntry = &s_shopMenuTopMenuEntries[i];
        Graphic.SetDrawDoneDebugData(0x23);
        _drawNoShadowFont(font, s_currentShopMenuTopMenuEntry->text, s_currentShopMenuTopMenuEntry->x - 0x10,
            s_currentShopMenuTopMenuEntry->y - 0x0B, 0x18, 0x12);
        Graphic.SetDrawDoneDebugData(0x24);
    }

    MenuPcs.DrawInit();
    Graphic.SetDrawDoneDebugData(0x28);
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: 0x8014F8F8
 * JP Size: 68b
 */
#ifndef VERSION_GCCJGC
inline
#endif
void CShopMenu::DrawBuy()
{
    DrawShopBase();
    DrawItemList();
    DrawItemInfo0();
    DrawBuySellInfo();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: 0x8014F8B4
 * JP Size: 68b
 */
#ifndef VERSION_GCCJGC
inline
#endif
void CShopMenu::DrawSell()
{
    DrawShopBase();
    DrawItemList();
    DrawItemInfo0();
    DrawBuySellInfo();
}

/*
 * --INFO--
 * PAL Address: 0x80154E98
 * PAL Size: 448b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifdef VERSION_GCCJGC
void CShopMenu::DrawSmith0()
{
    DrawShopBase();
    drawShapeSeqScale(0x11, 0, 0, 0x154, FLOAT_80332e48, FLOAT_80332d28, 0xFF);
    DrawItemList();
    DrawItemHelp(m_selectedIndex, 0x140, 0x176);

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(4.0f);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d8c);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();
    _drawNoShadowFont(font, "\x82\xA9\x82\xB6\x82\xE2", FLOAT_80332d54, FLOAT_80332e4c, 9, 0x12);
    MenuPcs.DrawInit();
}
#else
void CShopMenu::DrawSmith0()
{
    DrawShopBase();
    drawShapeSeqScale(0x11, 0, 0, 0x154, FLOAT_80332e48, FLOAT_80332d28, 0xFF);
    DrawItemList();
    DrawItemHelp(m_selectedIndex, 0x140, 0x172);

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d8c);

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    int languageId = static_cast<int>(Game.m_gameWork.GetLanguage()) - 1;
    const char* title;
    if (static_cast<signed char>(m_caravanWork->m_shopRequestFlags) != '\0') {
        title = MenuPcs.GetJobStr(1);
    } else {
        title = ShopMenuMes(languageId, SHOP_MENU_TEXT_BLACKSMITH);
    }

    int titleX = 0x108;
    titleX -= font->GetWidth(title);
    _drawNoShadowFont(font, const_cast<char*>(title), static_cast<float>(titleX), FLOAT_80332e4c, 9, 0x12);
    MenuPcs.DrawInit();
}
#endif

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#ifdef VERSION_GCCJGC
void CShopMenu::DrawMake()
{
    DrawMakeBase();

    drawShapeSeq(0xF, 0, 0xA8, 0x4A, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    MenuPcs.DrawInit();
    MenuPcs.DrawSingleIcon(m_resultItem, 0x3C, 0x32, FLOAT_80332d28, 0, FLOAT_80332d28);

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    _drawShadowFont(font, GetItemName(m_resultItem), FLOAT_80332d58, FLOAT_80332E0C, 0x18, 0x12);
    _drawNoShadowFont(font, "\x82\xBB\x82\xA4\x82\xD1\x82\xA9\x82\xCC\x82\xA4\x81\x40\x81\x46", FLOAT_80332E18, FLOAT_80332d58, 0x18, 0x12);

    char raceBuffer[128];
    MenuPcs.GetRaceStr(m_resultItem, raceBuffer);
    int raceColor = MenuPcs.ChkEquipPossible(m_resultItem) ? 0x18 : 2;
    _drawNoShadowFont(font, raceBuffer, 350.0f, FLOAT_80332d58, raceColor, 0x12);
    font->SetMargin(FLOAT_80332d28);

    int makeGil = getMakeGil(getItemNo(m_selectedIndex));
    DrawDecScale(makeGil, 0x13, 0x100, FLOAT_80332E18, FLOAT_80332D10, FLOAT_80332d8c, 1, 1, 0x12);
    int gilTlut = 2;
    if (m_caravanWork->m_gil >= getMakeGil(getItemNo(m_selectedIndex))) {
        gilTlut = 0x14;
    }
    DrawDecScale(m_caravanWork->m_gil, gilTlut, 0x1E2, FLOAT_80332E18, FLOAT_80332D10, FLOAT_80332d8c, 1, 1, 0x12);

    font->SetScale(FLOAT_80332d28);
    _drawNoShadowFont(font, "\x83\x4D\x83\x8B", 258.0f, 188.0f, 0x19, 0x12);
    _drawNoShadowFont(font, "/", FLOAT_80332E14, 188.0f, 0x1B, 0x12);
    _drawNoShadowFont(font, "\x83\x4D\x83\x8B", 484.0f, 188.0f, 0x19, 0x12);

    CMenuPcs* pcs = &MenuPcs;
    CFont* labelFont = pcs->GetFontItem();
    labelFont->SetMargin(FLOAT_80332d28);
    labelFont->SetShadow(0);
    labelFont->SetScale(FLOAT_80332d28);
    labelFont->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    labelFont->DrawInit();
    labelFont->SetPosX(FLOAT_80332E18);
    labelFont->SetPosY(FLOAT_80332E24);
    labelFont->Draw("\x82\xB9\x82\xA2\x82\xB3\x82\xAD\x82\xD0");
    labelFont->SetPosX(368.0f);
    labelFont->SetPosY(FLOAT_80332E24);
    labelFont->Draw("\x82\xB5\x82\xE5\x82\xB6\x82\xAB\x82\xF1");
    MenuPcs.DrawInit();

    int obiX = 0x32;
    drawShapeSeq(5, 0, 0x32, 0x104, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    do {
        obiX += 0x20;
        drawShapeSeq(6, 0, obiX, 0x104, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    } while (obiX < 0x20E);
    drawShapeSeq(5, 0, obiX + 0x40, 0x104, 0xFF, 1, 0, FLOAT_80332D9C, 0);

    CFont* headerFont = MenuPcs.GetFont22();
    headerFont->SetMargin(FLOAT_80332d28);
    headerFont->SetShadow(1);
    headerFont->SetScale(FLOAT_80332d28);
    headerFont->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    headerFont->DrawInit();
    _drawNoShadowFont(headerFont, "\x82\xD0\x82\xC2\x82\xE6\x82\xA4\x82\xC8\x82\xE0\x82\xCC", 130.0f, FLOAT_80332E34, 4, 0x12);
    _drawNoShadowFont(headerFont, "\x82\xB5\x82\xE5\x82\xB6\x82\xB7\x82\xA4", 400.0f, FLOAT_80332E34, 9, 0x12);

    int rowY = 300;
    CMenuPcs::MaterialInfo recipeMaterial;
    MenuPcs.GetRecipeMaterial(getItemNo(m_selectedIndex), &recipeMaterial);
    for (int i = 0; i < 3; i++, rowY += 0x1E) {
        if (recipeMaterial.m_itemNo[i] <= 0) {
            break;
        }

        headerFont->SetMargin(FLOAT_80332d28);
        headerFont->SetShadow(1);
        headerFont->SetScale(FLOAT_80332d28);
        float nameX = 290.0f - headerFont->GetWidth(GetItemName(recipeMaterial.m_itemNo[i]));
        _drawNoShadowFont(headerFont, GetItemName(recipeMaterial.m_itemNo[i]), nameX, rowY, 0x1B, 0x12);
        _drawNoShadowFont(headerFont, "\x81\x7E", 310.0f, rowY, 0x1B, 0x12);
        _drawNoShadowFont(headerFont, "/", 390.0f, rowY, 0x1B, 0x12);

        int ownedCount = getItemHaveCnt(recipeMaterial.m_itemNo[i]);
        DrawDec(recipeMaterial.m_count[i], 0x1B, 0x168, rowY, -3.0f, 0, 1, 0x12);
        int ownedTlut = 2;
        if (ownedCount >= recipeMaterial.m_count[i]) {
            ownedTlut = 0x1B;
        }
        DrawDec(ownedCount, ownedTlut, 0x1CC, rowY, -3.0f, 1, 1, 0x12);
    }
    MenuPcs.DrawInit();

    int barX = 0x1F6;
    while (barX > 0x32) {
        drawShapeSeq(0xC, 0, barX, 0x18C, 0xFF, 0, 0, FLOAT_80332D9C, 0);
        barX -= 0x10;
    }
    drawShapeSeq(0xB, 0, 0x226, 0x168, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    drawShapeSeq(1, 1, barX, 0x18C, 0xFF, 0, 0, FLOAT_80332D9C, 0);

    CFont* labelFont2 = pcs->GetFontItem();
    labelFont2->SetMargin(FLOAT_80332d28);
    labelFont2->SetShadow(0);
    labelFont2->SetScale(FLOAT_80332d28);
    labelFont2->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    labelFont2->DrawInit();
    labelFont2->SetPosX(FLOAT_80332E1C);
    labelFont2->SetPosY(FLOAT_80332DDC);
    labelFont2->Draw("\x82\xC2\x82\xAD\x82\xE9");
    labelFont2->SetPosX(510.0f);
    labelFont2->SetPosY(FLOAT_80332E44);
    labelFont2->Draw(SHOP_JP_CANCEL);
    MenuPcs.DrawInit();

    MenuPcs.DrawCursor(0x1E2, m_yesNo * 0x18 + 0x14C, FLOAT_80332d28);
}
#else
void CShopMenu::DrawMake()
{
    DrawMakeBase();

    drawShapeSeq(0xF, 0, 0xA8, 0x4A, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    MenuPcs.DrawInit();
    MenuPcs.DrawSingleIcon(m_resultItem, 0x40, 0x32, FLOAT_80332d28, 0, FLOAT_80332d28);

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    char* itemName = GetItemName(m_resultItem);
    _drawShadowFont(font, itemName, FLOAT_80332d54, FLOAT_80332E0C, 0x18, 0x12);

    int languageId = static_cast<int>(Game.m_gameWork.GetLanguage()) - 1;
    char* raceText = ShopMenuMes(languageId, SHOP_MENU_TEXT_RACE);
    int x = 180;
    _drawNoShadowFont(font, raceText, x, FLOAT_80332d58, 0x18, 0x12);

    x += FLOAT_80332d5c + font->GetWidth(raceText);
    char raceBuffer[132];
    MenuPcs.GetRaceStr(m_resultItem, raceBuffer);
    const int raceColor = MenuPcs.ChkEquipPossible(m_resultItem) ? 0x18 : 2;
    _drawNoShadowFont(font, raceBuffer, x, FLOAT_80332d58, raceColor, 0x12);

    font->SetMargin(FLOAT_80332d28);
    int makeGil = getMakeGil(getItemNo(m_selectedIndex));
    font->DrawInit();
    font->SetMargin(FLOAT_80332d28);
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    float gilUnitWidth = font->GetWidth(ShopMenuMes(languageId, SHOP_MENU_TEXT_GIL));

    float makeMarginW = FLOAT_80332E10;
    short makeAmountX = static_cast<int>(FLOAT_80332E14 - gilUnitWidth - FLOAT_80332d5c - FLOAT_80332d5c);
    CFont* amountFont = MenuPcs.GetFont22();
    SetupShopMenuAmountFont(amountFont);
    DrawShopMenuAmountTrunc(amountFont, makeGil, makeAmountX, FLOAT_80332E18, 0x13);

    int gilAmountX = static_cast<int>(FLOAT_80332E1C - gilUnitWidth - FLOAT_80332d5c);
    int makeGil2 = getMakeGil(getItemNo(m_selectedIndex));
    int gilTlut = 2;
    if (m_caravanWork->m_gil >= makeGil2) {
        gilTlut = 0x14;
    }
    int caravanGil = m_caravanWork->m_gil;
    CFont* amountFont2 = MenuPcs.GetFont22();
    SetupShopMenuAmountFont(amountFont2);
    DrawShopMenuAmountTrunc(amountFont2, caravanGil, gilAmountX, FLOAT_80332E18, gilTlut);

    font->SetScale(FLOAT_80332d28);
    font->DrawInit();
    font->SetMargin(FLOAT_80332d28);
    char* gilUnitText = ShopMenuMes(languageId, SHOP_MENU_TEXT_GIL);
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    float gilUnitWidth2 = font->GetWidth(gilUnitText);
    x = 312;
    _drawNoShadowFont(font, const_cast<char*>(s_Slash_80332d84), FLOAT_80332E14, FLOAT_80332E20, 0x1B, 0x12);

    x -= (FLOAT_80332d5c + gilUnitWidth2);
    _drawNoShadowFont(font, gilUnitText, x, FLOAT_80332E20, 0x19, 0x12);

    x = static_cast<int>(FLOAT_80332E1C - gilUnitWidth2);
    _drawNoShadowFont(font, gilUnitText, x, FLOAT_80332E20, 0x19, 0x12);

    CMenuPcs* pcs = &MenuPcs;
    CFont* labelFont = pcs->GetFontItem();
    labelFont->DrawInit();
    labelFont->SetMargin(FLOAT_80332d28);
    labelFont->SetShadow(0);
    labelFont->SetScale(FLOAT_80332d28);
    labelFont->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    labelFont->SetPosY(FLOAT_80332E24);
    char* priceLabel = ShopMenuMes(languageId, SHOP_MENU_TEXT_MAKE_PRICE);
    labelFont->SetPosX(static_cast<float>(static_cast<int>(
        (FLOAT_80332E28 - labelFont->GetWidth(priceLabel)) / 2 + FLOAT_80332d6c)));
    labelFont->Draw(priceLabel);
    char* moneyLabel = ShopMenuMes(languageId, SHOP_MENU_TEXT_MONEY);
    labelFont->SetPosX(static_cast<float>(static_cast<int>(
        (FLOAT_80332d68 - labelFont->GetWidth(moneyLabel)) / 2 + FLOAT_80332E2C)));
    labelFont->Draw(moneyLabel);
    MenuPcs.DrawInit();

    int obiX = 0x32;
    drawShapeSeq(5, 0, 0x32, 0x104, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    do {
        obiX += 0x20;
        drawShapeSeq(6, 0, obiX, 0x104, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    } while (obiX < 0x20E);
    drawShapeSeq(5, 0, obiX + 0x40, 0x104, 0xFF, 1, 0, FLOAT_80332D9C, 0);

    CFont* headerFont = MenuPcs.GetFont22();
    headerFont->SetMargin(FLOAT_80332d28);
    headerFont->SetShadow(1);
    headerFont->SetScale(FLOAT_80332d28);
    headerFont->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    headerFont->DrawInit();
    char* materialsText = ShopMenuMes(languageId, SHOP_MENU_TEXT_MATERIALS);
    x = 0x80;
    x += (FLOAT_80332E30 - headerFont->GetWidth(materialsText)) / 2;
    _drawNoShadowFont(headerFont, materialsText, x, FLOAT_80332E34, 4, 0x12);
    char* stockText = ShopMenuMes(languageId, SHOP_MENU_TEXT_STOCK);
    x = 0x1A4;
    x += (FLOAT_80332E38 - headerFont->GetWidth(stockText)) / 2;
    _drawNoShadowFont(headerFont, stockText, x, FLOAT_80332E34, 9, 0x12);

    int rowY = 300;
    int ownedRightX = 452;
    CMenuPcs::MaterialInfo recipeMaterial;
    MenuPcs.GetRecipeMaterial(getItemNo(m_selectedIndex), &recipeMaterial);
    float makeMarginScale = 1.0f;
    float makeMarginBase = -4.0f;
    for (int i = 0; i < 3; i++, rowY += 0x1E) {
        if (recipeMaterial.m_itemNo[i] <= 0) {
            break;
        }

        headerFont->DrawInit();
        headerFont->SetMargin(FLOAT_80332d28);
        headerFont->SetShadow(1);
        headerFont->SetScale(FLOAT_80332d28);
        _drawNoShadowFont(headerFont, const_cast<char*>(s_Slash_80332d84), FLOAT_80332E3C, rowY, 0x1B, 0x12);

        CFont* makeAmountFont = MenuPcs.GetFont22();
        x = 372;
        int neededCount = recipeMaterial.m_count[i];
        SetupShopMenuMakeFont(makeAmountFont, makeMarginW * makeMarginScale + makeMarginBase);
        char neededBuffer[64];
        sprintf(neededBuffer, s_DecimalFormat_80332d14, neededCount);
        x -= makeAmountFont->GetWidth(neededBuffer);
        MenuPcs.DrawNoShadowFont(makeAmountFont, neededBuffer, x, rowY, 0x1B, 0x12);
        MenuPcs.DrawInit();

        headerFont->DrawInit();
        headerFont->SetMargin(FLOAT_80332d28);
        headerFont->SetShadow(1);
        headerFont->SetScale(FLOAT_80332d28);
        x -= 8;
        x -= headerFont->GetWidth("/");
        _drawNoShadowFont(headerFont, const_cast<char*>("/"), x, rowY, 0x1B, 0x12);

        x -= 8;
        char* materialName = GetItemName(recipeMaterial.m_itemNo[i]);
        x -= headerFont->GetWidth(materialName);
        _drawNoShadowFont(headerFont, materialName, x, rowY, 0x1B, 0x12);

        int ownedCount = getItemHaveCnt(recipeMaterial.m_itemNo[i]);

        int ownedTlut = 2;
        makeMarginW = FLOAT_80332E10;
        if (ownedCount >= recipeMaterial.m_count[i]) {
            ownedTlut = 0x1B;
        }
        CFont* ownedFont = MenuPcs.GetFont22();
        x = ownedRightX;
        SetupShopMenuGilFont(ownedFont);
        char ownedBuffer[64];
        sprintf(ownedBuffer, s_TwoDigitFormat_80332d18, ownedCount);
        x -= ownedFont->GetWidth(ownedBuffer);
        MenuPcs.DrawNoShadowFont(ownedFont, ownedBuffer, x, rowY, ownedTlut, 0x12);
        MenuPcs.DrawInit();
    }
    MenuPcs.DrawInit();

    int barX = 0x1F6;
    while (barX > 0x32) {
        drawShapeSeq(0xC, 0, barX, 0x18C, 0xFF, 0, 0, FLOAT_80332D9C, 0);
        barX -= 0x10;
    }
    drawShapeSeq(0xB, 0, 0x226, 0x168, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    drawShapeSeq(1, 1, barX, 0x18C, 0xFF, 0, 0, FLOAT_80332D9C, 0);

    CFont* labelFont2 = pcs->GetFontItem();
    labelFont2->SetMargin(FLOAT_80332d28);
    labelFont2->SetShadow(0);
    labelFont2->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    labelFont2->SetScaleX(FLOAT_80332d2c);
    labelFont2->SetScaleY(FLOAT_80332d28);
    labelFont2->DrawInit();
    char* craftText = ShopMenuMes(languageId, SHOP_MENU_TEXT_CRAFT);
    x = 0x1F8;
    x += (FLOAT_80332DD4 - labelFont2->GetWidth(craftText)) / 2;
    labelFont2->SetPosX(x);
    labelFont2->SetPosY(FLOAT_80332DDC);
    labelFont2->Draw(craftText);

    char* cancelText = ShopMenuMes(languageId, SHOP_MENU_TEXT_CANCEL);
    x = 0x1F8;
    x += (FLOAT_80332DD4 - labelFont2->GetWidth(cancelText)) / 2;
    labelFont2->SetPosX(x);
    labelFont2->SetPosY(FLOAT_80332E44);
    labelFont2->Draw(cancelText);
    MenuPcs.DrawInit();

    MenuPcs.DrawCursor(x - 0x24, m_yesNo * 0x18 + 0x14C, FLOAT_80332d28);
}
#endif

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#ifdef VERSION_GCCJGC
void CShopMenu::DrawSoubi()
{
    DrawSoubiBase();

    drawShapeSeq(0xF, 0, 0xA8, 0x5A, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    MenuPcs.DrawInit();
    MenuPcs.DrawSingleIcon(m_resultItem, 0x3C, 0x42, FLOAT_80332d28, 0, FLOAT_80332d28);

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    _drawShadowFont(font, GetItemName(m_resultItem), 120.0f, FLOAT_80332E04, 0x18, 0x12);

    DrawItemInfo(m_resultItem, 0xD8, 0x7E, 0xD8, 0x9C, 0xD8, 0xBA, 0x138);
    MenuPcs.DrawInit();

    int barX = 0x1F6;
    while (barX > 0x42) {
        drawShapeSeq(0xC, 0, barX, 0x17C, 0xFF, 0, 0, FLOAT_80332D9C, 0);
        barX -= 0x10;
    }
    drawShapeSeq(0xB, 0, 0x226, 0x158, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    drawShapeSeq(1, 1, barX, 0x17C, 0xFF, 0, 0, FLOAT_80332D9C, 0);

    CFont* labelFont = MenuPcs.GetFontItem();
    labelFont->SetMargin(FLOAT_80332d28);
    labelFont->SetShadow(0);
    labelFont->SetScale(FLOAT_80332d28);
    labelFont->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    labelFont->DrawInit();

    labelFont->SetPosX(FLOAT_80332E1C);
    labelFont->SetPosY(FLOAT_80332E08);
    labelFont->Draw("\x82\xBB\x82\xA4\x82\xD1");
    labelFont->SetPosX(510.0f);
    labelFont->SetPosY(FLOAT_80332d88);
    labelFont->Draw(SHOP_JP_CANCEL);
    MenuPcs.DrawInit();

    MenuPcs.DrawCursor(0x1E2, m_yesNo * 0x18 + 0x13C, FLOAT_80332d28);
}
#else
void CShopMenu::DrawSoubi()
{
    DrawSoubiBase();

    drawShapeSeq(0xF, 0, 0xA8, 0x5A, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    MenuPcs.DrawInit();
    MenuPcs.DrawSingleIcon(m_resultItem, 0x40, 0x42, FLOAT_80332d28, 0, FLOAT_80332d28);

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    char* itemName = GetItemName(m_resultItem);
    _drawShadowFont(font, itemName, FLOAT_80332d54, FLOAT_80332E04, 0x18, 0x12);

    DrawItemInfo(m_resultItem, 0x98, 0x7E, 0x98, 0x9C, 0x98, 0xBA, 0x138);
    MenuPcs.DrawInit();

    int barX = 0x1F6;
    while (barX > 0x42) {
        drawShapeSeq(0xC, 0, barX, 0x17C, 0xFF, 0, 0, FLOAT_80332D9C, 0);
        barX -= 0x10;
    }
    drawShapeSeq(0xB, 0, 0x226, 0x158, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    drawShapeSeq(1, 1, barX, 0x17C, 0xFF, 0, 0, FLOAT_80332D9C, 0);

    CFont* labelFont = MenuPcs.GetFontItem();
    labelFont->SetMargin(FLOAT_80332d28);
    labelFont->SetShadow(0);
    {
        labelFont->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    }
    labelFont->SetScaleX(FLOAT_80332d2c);
    labelFont->SetScaleY(FLOAT_80332d28);
    labelFont->DrawInit();

    int languageId = static_cast<int>(Game.m_gameWork.GetLanguage()) - 1;
    labelFont->SetPosY(FLOAT_80332E08);
    char* equipText = ShopMenuMes(languageId, SHOP_MENU_TEXT_EQUIP);
    int equipTextX = 0x1F8;
    equipTextX += (FLOAT_80332DD4 - labelFont->GetWidth(equipText)) / 2;
    labelFont->SetPosX(static_cast<float>(equipTextX));
    labelFont->SetPosY(FLOAT_80332E08);
    labelFont->Draw(equipText);

    char* cancelText = ShopMenuMes(languageId, SHOP_MENU_TEXT_CANCEL);
    int cancelTextX = 0x1F8;
    cancelTextX += (FLOAT_80332DD4 - labelFont->GetWidth(cancelText)) / 2;
    labelFont->SetPosX(static_cast<float>(cancelTextX));
    labelFont->SetPosY(FLOAT_80332d88);
    labelFont->Draw(cancelText);
    MenuPcs.DrawInit();

    MenuPcs.DrawCursor(cancelTextX - 0x24, m_yesNo * 0x18 + 0x13C, FLOAT_80332d28);
}
#endif

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void drawGrouadQuad(int x, int y, int width, int height, _GXColor colorA, _GXColor colorB, _GXColor colorC,
                           _GXColor colorD)
{
    setOrtho(0x140, 0xE0, FLOAT_80332d78, FLOAT_80332DD0, FLOAT_80332D9C);

    _GXColor amb = {0xFF, 0xFF, 0xFF, 0xFF};
    _GXColor mat = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanAmbColor(GX_COLOR0A0, amb);
    GXSetChanMatColor(GX_COLOR0A0, mat);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    Vec minPos;
    minPos.x = static_cast<float>(x);
    minPos.y = static_cast<float>(y);
    minPos.z = 0.0f;
    Vec maxPos;
    maxPos.x = static_cast<float>(x + width);
    maxPos.y = static_cast<float>(y + height);
    maxPos.z = 0.0f;
    Graphic.RenderNoTexQuadGrouad(minPos, maxPos, colorA, colorB, colorC, colorD);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Draw()
{
    if (reinterpret_cast<int>(m_unk00) == 0) {
        m_unk00 = reinterpret_cast<void*>(1);
        return;
    }

    Graphic.SetDrawDoneDebugData(0x46);
    ppvEnv = &PartMng.m_pdtSlots[m_pdtSlot].m_env;

    MenuPcs.DrawInit();

    switch (m_mode) {
    case 0:
    case 1:
    case 2:
        DrawShop0();
        break;
    case 3:
    case 4:
    case 5:
        DrawBuy();
        break;
    case 6:
    case 7:
    case 8:
        DrawSell();
        break;
    case 9:
    case 0xA:
    case 0xB:
        DrawSmith0();
        break;
    case 0xC:
    case 0xD:
    case 0xE:
        DrawMake();
        break;
    case 0xF:
    case 0x10:
    case 0x11:
        DrawSoubi();
        break;
    }

    if (FLOAT_80332d28 != m_fade) {
        _GXColor fadeColor;
        fadeColor.r = 0;
        fadeColor.g = 0;
        fadeColor.b = 0;
        fadeColor.a = 0xFF - static_cast<int>(FLOAT_80332DE0 * m_fade);
        Graphic.SetDrawDoneDebugData(0x32);
        drawGrouadQuad(-0x280, -0x1C0, 0x77F, 0x53F, fadeColor, fadeColor, fadeColor, fadeColor);
        Graphic.SetDrawDoneDebugData(0x33);
    }
    Graphic.SetDrawDoneDebugData(0x3C);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::InitDrawEnvShape()
{
    pppInitDrawEnv(0);

    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
}

/*
 * --INFO--
 * PAL Address: 0x80152B2C
 * PAL Size: 1916b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::DrawShopBase()
{
    Graphic.SetDrawDoneDebugData(1);
#ifndef VERSION_GCCJGC
    int languageId = static_cast<int>(Game.m_gameWork.GetLanguage()) - 1;
#endif
    MenuPcs.DrawSingleBase(FLOAT_80332d28);
    Graphic.SetDrawDoneDebugData(2);
    InitDrawEnvShape();

    int panelY;
    if (m_mode <= 2) {
        panelY = 0xE6;
    } else if (m_mode <= 8) {
        panelY = 0x154;
    } else if (m_mode <= 0xB) {
        panelY = 0x118;
    }

    Graphic.SetDrawDoneDebugData(3);
    DrawObi(panelY + 0x22);
    Graphic.SetDrawDoneDebugData(4);

    if (m_mode >= 3) {
        int listX;
        int listY;
        if (m_mode >= 9) {
            listX = 0x118;
            listY = 0xAA;
        } else {
            listX = 0x64;
            listY = 0xAA;
        }
        int barX;
        for (barX = listX + 0x48; barX < 0x244; barX += 8) {
            Graphic.SetDrawDoneDebugData(5);
            drawShapeSeq(0x10, 0, barX, listY + 0x74, 0xFF, 0, 0, FLOAT_80332D9C, 0);
            Graphic.SetDrawDoneDebugData(6);
        }
        Graphic.SetDrawDoneDebugData(7);
        drawShapeSeq(0xD, 0, listX + 0x46, listY - 3, 0xFF, 0, 0, FLOAT_80332D9C, 0);
        Graphic.SetDrawDoneDebugData(8);
        Graphic.SetDrawDoneDebugData(9);
        drawShapeSeq(8, 0, barX, listY + 0x74, 0xFF, 0, 0, FLOAT_80332D9C, 0);
        Graphic.SetDrawDoneDebugData(10);

        if (m_mode <= 8) {
            int sideX;
            for (sideX = 0x4E; sideX > 0x32; sideX -= 0x10) {
                Graphic.SetDrawDoneDebugData(0xB);
                drawShapeSeq(0xC, 0, sideX, 0x174, 0xFF, 0, 0, FLOAT_80332D9C, 0);
                Graphic.SetDrawDoneDebugData(0xC);
            }
            Graphic.SetDrawDoneDebugData(0xD);
            drawShapeSeq(0xB, 0, 0x7E, 0x150, 0xFF, 0, 0, FLOAT_80332D9C, 0);
            Graphic.SetDrawDoneDebugData(0xE);
            drawShapeSeq(8, 0, sideX, 0x170, 0xFF, 0, 0, FLOAT_80332D9C, 0);
            Graphic.SetDrawDoneDebugData(0xF);
            CFont* font = MenuPcs.GetFontItem();
            font->SetMargin(FLOAT_80332d28);
            font->SetShadow(0);
#ifdef VERSION_GCCJGC
            font->SetScale(FLOAT_80332d28);
            font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
            font->DrawInit();

            font->SetPosX(118.0f);
            font->SetPosY(FLOAT_80332DD8);
            Graphic.SetDrawDoneDebugData(0x10);
            if (m_listType == 0) {
                font->Draw(SHOP_JP_BUY);
            } else {
                font->Draw(SHOP_JP_SELL);
            }
            Graphic.SetDrawDoneDebugData(0x11);

            font->SetPosX(86.0f);
            font->SetPosY(FLOAT_80332DDC);
            font->Draw(SHOP_JP_CANCEL);
#else
            font->SetScaleX(FLOAT_80332d2c);
            font->SetScaleY(FLOAT_80332d28);
            font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);

            font->DrawInit();
            Graphic.SetDrawDoneDebugData(0x10);
            char* confirmText = (m_listType == 0) ? ShopMenuMes(languageId, SHOP_MENU_TEXT_BUY) :
                                                    ShopMenuMes(languageId, SHOP_MENU_TEXT_SELL);
            int confirmCenterX = 0x50;
            float confirmTextX = CalcCenteredShopMenuX(font, confirmText, confirmCenterX);
            font->SetPosX(confirmTextX);
            font->SetPosY(FLOAT_80332DD8);
            font->Draw(confirmText);
            Graphic.SetDrawDoneDebugData(0x11);

            char* cancelText = ShopMenuMes(languageId, SHOP_MENU_TEXT_CANCEL);
            int cancelCenterX = 0x50;
            float cancelTextX = CalcCenteredShopMenuX(font, cancelText, cancelCenterX);
            font->SetPosX(cancelTextX);
            font->SetPosY(FLOAT_80332DDC);
            font->Draw(cancelText);
#endif
            Graphic.SetDrawDoneDebugData(0x12);
            MenuPcs.DrawInit();
            Graphic.SetDrawDoneDebugData(0x13);

            if (m_subMode == 2) {
                Graphic.SetDrawDoneDebugData(0x14);
#ifdef VERSION_GCCJGC
                MenuPcs.DrawCursor(0x3A, m_yesNo * 0x18 + 0x134, FLOAT_80332d28);
#else
                MenuPcs.DrawCursor(0x2C, m_yesNo * 0x18 + 0x134, FLOAT_80332d28);
#endif
                Graphic.SetDrawDoneDebugData(0x15);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801527EC
 * PAL Size: 832b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::DrawMakeBase()
{
    MenuPcs.DrawSingleBase(FLOAT_80332d28);
    InitDrawEnvShape();

    DrawObi(0xB8);

    drawShapeSeq(3, 0, 0xB4, 0x8C, 0xFF, 0, 0, FLOAT_80332D9C, 0);
    int x = 0xB4;
    while (x < 0x1CC) {
        drawShapeSeq(4, 0, x, 0x8C, 0xFF, 0, 0, FLOAT_80332D9C, 0);
        x += 0x20;
    }
    drawShapeSeq(3, 0, x, 0x8C, 0xFF, 1, 0, FLOAT_80332D9C, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801524C4
 * PAL Size: 808b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::DrawSoubiBase()
{
    MenuPcs.DrawSingleBase(FLOAT_80332d28);
    InitDrawEnvShape();

    DrawObi(0x10C);

    drawShapeSeqScale(3, 0, 0x106, 0xA4, FLOAT_80332d78, FLOAT_80332DCC, 0xFF);
    int x = 0x106;
    while (x < 0x17A) {
        drawShapeSeqScale(4, 0, x, 0xA4, FLOAT_80332d78, FLOAT_80332DCC, 0xFF);
        x += 0x20;
    }
    drawShapeSeqScale(3, 0, x, 0xA4, FLOAT_80332DD0, FLOAT_80332DCC, 0xFF);
}

/*
 * --INFO--
 * PAL Address: 0x80151F98
 * PAL Size: 1324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::DrawItemList()
{
    int y = 0x4C;
    int itemIndex = m_listTop;
    unsigned int selectableFrame = 10;
    if (m_listType == 2) {
        selectableFrame = 0xF;
    }

    for (int row = 0; row < m_visibleRows; ++row, y += 0x1C) {
        int itemCount = getItemCnt();

        if (itemIndex >= itemCount) {
            break;
        }

        int itemNo = getItemNo(itemIndex);

        int canTrade = CheckSell(itemIndex);

        int frame = 0xE;
        if (canTrade != 0) {
            frame = selectableFrame;
        }

        int frameX;
        if (m_selectedIndex == itemIndex) {
            frameX = 0x198;
            drawShapeSeq(frame, 1, frameX, y - 4, 0xFF, 0, 0, FLOAT_80332D9C, 0);
            MenuPcs.DrawInit();
            int cursorY = y - 0x14;
            if (m_subMode == 0) {
                MenuPcs.DrawCursor(0x114 + (static_cast<int>(System.m_frameCounter) % 8), cursorY, FLOAT_80332d28);
            } else if ((System.m_frameCounter & 1) == 0) {
                MenuPcs.DrawCursor(0x114, cursorY, FLOAT_80332d28);
            }
        } else {
            frameX = 0x1B8;
            drawShapeSeq(frame, 0, frameX, y, 0xFF, 0, 0, FLOAT_80332D9C, 0);
        }

        if (itemNo > 0) {
            CFont* font = MenuPcs.GetFontItem();
            font->SetMargin(FLOAT_80332d28);
            font->SetShadow(0);
            font->SetScale(FLOAT_80332d28);

            font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
            font->DrawInit();
            font->SetPosX(static_cast<float>(frameX - 0x54));
            font->SetPosY(static_cast<float>(y - 0x14));
            font->Draw(GetItemName(itemNo));
            MenuPcs.DrawInit();
            MenuPcs.DrawSingleIcon(itemNo, frameX + 0x54, y - 0x18, FLOAT_80332d28, 0, FLOAT_80332d28);
        }

        ++itemIndex;
    }

    int pulse = abs(static_cast<int>(System.m_frameCounter) % 0x14 - 10);
    unsigned char alpha = static_cast<unsigned char>(255.0 * (0.05 * static_cast<double>(pulse) + 0.5));
    float scale = static_cast<float>(0.5 * (0.03 * static_cast<double>(pulse) + 0.7));

    if (m_canScrollUp != 0) {
        drawShapeSeqScale(2, 0, 0x24E, 0x6A, scale, -scale, alpha);
    }
    if (m_canScrollDown != 0) {
        drawShapeSeqScale(2, 0, 0x24E, 0xEC, scale, scale, alpha);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8015173c
 * PAL Size: 2140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifdef VERSION_GCCJGC
void CShopMenu::DrawBuySellInfo()
{
    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    _drawNoShadowFont(font, "\x82\xCB\x82\xBE\x82\xF1", 184.0f, FLOAT_80332d80, 0x13, 0x12);
    _drawNoShadowFont(font, "/", FLOAT_80332e4c, FLOAT_80332d80, 0x18, 0x12);
    _drawNoShadowFont(font, "\x82\xB5\x82\xE5\x82\xB6\x82\xAB\x82\xF1", 272.0f, FLOAT_80332d80, 0x14, 0x12);

    int totalGil;
    if (CheckSell(m_selectedIndex)) {
        totalGil = GetTotalGil();
    } else {
        totalGil = 0;
    }

    DrawDecScale(totalGil, 0x13, 0x120, FLOAT_80332d90, FLOAT_80332D10, FLOAT_80332d8c, 1, 1, 0x12);
    DrawDecScale(m_caravanWork->m_gil, 0x14, 0x212, FLOAT_80332d90, FLOAT_80332D10, FLOAT_80332d8c, 1, 1, 0x12);

    font->SetScale(FLOAT_80332d28);
    _drawNoShadowFont(font, "\x83\x4D\x83\x8B", 290.0f, FLOAT_80332E2C, 0x19, 0x12);
    _drawNoShadowFont(font, "/", 349.0f, FLOAT_80332E2C, 0x1B, 0x12);
    _drawNoShadowFont(font, "\x83\x4D\x83\x8B", 532.0f, FLOAT_80332E2C, 0x19, 0x12);
}
#else
void CShopMenu::DrawBuySellInfo()
{
    int languageId = static_cast<int>(Game.m_gameWork.GetLanguage()) - 1;
    CFont* font = MenuPcs.GetFont22();

    font->DrawInit();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);

    char* priceText = ShopMenuMes(languageId, SHOP_MENU_TEXT_PRICE);
    int priceX = static_cast<int>(FLOAT_80332d7c - font->GetWidth(priceText));
    _drawNoShadowFont(font, priceText, static_cast<float>(priceX), FLOAT_80332d80, 0x13, 0x12);

    _drawNoShadowFont(font, const_cast<char*>(s_Slash_80332d84), FLOAT_80332d7c, FLOAT_80332d80, 0x18, 0x12);

    char* moneyText = ShopMenuMes(languageId, SHOP_MENU_TEXT_MONEY);
    float separatorWidth = font->GetWidth(s_Slash_80332d84);
    _drawNoShadowFont(font, moneyText, static_cast<float>(static_cast<int>(FLOAT_80332d7c + separatorWidth)), FLOAT_80332d80, 0x14, 0x12);

    font->DrawInit();
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    font->SetMargin(FLOAT_80332d28);
    char* unitText = ShopMenuMes(languageId, SHOP_MENU_TEXT_GIL);
    float unitWidth = font->GetWidth(unitText);

    int canTrade = CheckSell(m_selectedIndex);

    int totalGil;
    if (canTrade) {
        totalGil = GetTotalGil();
    } else {
        totalGil = 0;
    }

    float rightPrice = FLOAT_80332d88 - unitWidth;
    int amountRightPrice = static_cast<int>(rightPrice - FLOAT_80332d5c);
    CFont* amountFont = MenuPcs.GetFont22();
    SetupShopMenuAmountFont(amountFont);
    DrawShopMenuAmountTrunc(amountFont, totalGil, amountRightPrice, FLOAT_80332d90, 0x13);

    float rightMoney = FLOAT_80332d94 - unitWidth;
    int amountRightMoney = static_cast<int>(rightMoney - FLOAT_80332d5c);
    int currentMoney = m_caravanWork->m_gil;
    CFont* amountFont2 = MenuPcs.GetFont22();
    SetupShopMenuAmountFont(amountFont2);
    DrawShopMenuAmountTrunc(amountFont2, currentMoney, amountRightMoney, FLOAT_80332d90, 0x14);

    font->DrawInit();
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    font->SetMargin(FLOAT_80332d28);
    int rightPriceInt = static_cast<int>(rightPrice);
    _drawNoShadowFont(font, unitText, static_cast<float>(rightPriceInt), FLOAT_80332d98, 0x19, 0x12);

    _drawNoShadowFont(font, const_cast<char*>(s_Slash_80332d84), FLOAT_80332d7c, FLOAT_80332d98, 0x1B, 0x12);

    _drawNoShadowFont(font, unitText, static_cast<float>(static_cast<int>(rightMoney)), FLOAT_80332d98, 0x19, 0x12);
}
#endif

/*
 * --INFO--
 * PAL Address: 0x80150e50
 * PAL Size: 2284b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifdef VERSION_GCCJGC
void CShopMenu::DrawItemInfo0()
{
    if (m_selectedIndex == -1) {
        return;
    }

    int itemNo = getItemNo(m_selectedIndex);
    MenuPcs.DrawInit();
    if (itemNo > 0) {
        MenuPcs.DrawSingleIcon(itemNo, 0x46, 100, FLOAT_80332d28, 0, FLOAT_80332d28);
    }

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    if (itemNo > 0) {
        font->SetMargin(FLOAT_80332d28);
        _drawShadowFont(font, GetItemName(itemNo), 118.0f, FLOAT_80332d58, 0x18, 0x12);
        font->SetMargin(FLOAT_80332d28);
    }

    if (CheckSell(m_selectedIndex)) {
        font->SetMargin(FLOAT_80332d28);
        DrawDec(getBuySellGil(itemNo), 0x1B, 0xD2, FLOAT_80332d68, -3.0f, 0, 1, 0x12);
        font->SetMargin(FLOAT_80332d28);
        _drawNoShadowFont(font, "\x83\x4D\x83\x8B", 214.0f, FLOAT_80332d68, 0x19, 0x12);
    } else {
        font->SetMargin(FLOAT_80332d28);
        if (m_listType == 0) {
            _drawNoShadowFont(font, "\x82\xA9\x82\xA6\x82\xDC\x82\xB9\x82\xF1", 150.0f, FLOAT_80332d68, 0x19, 0x12);
        } else {
            _drawNoShadowFont(font, "\x82\xA4\x82\xEA\x82\xDC\x82\xB9\x82\xF1", 150.0f, FLOAT_80332d68, 0x19, 0x12);
        }
        font->SetMargin(FLOAT_80332d28);
    }

    if (m_subMode == 0) {
        DrawItemInfo(itemNo, 0x4E, 0xA8, 0x4E, 0xC6, 0x4E, 0xE4, 0xB2);
    }

    if ((m_subMode == 1) && (m_listType == 0)) {
        _drawNoShadowFont(font, "\x82\xA9\x82\xA4\x82\xA9\x82\xB8", 90.0f, FLOAT_80332d6c, 0x18, 0x12);
        _drawNoShadowFont(font, "\x81\x7E", 182.0f, FLOAT_80332d6c, 0x18, 0x12);
        DrawDec(m_quantity / 10, 4, 0xDE, FLOAT_80332d6c, -3.0f, 0, 1, 0x12);
        DrawDec(m_quantity % 10, 4, 0xF2, FLOAT_80332d6c, -3.0f, 0, 1, 0x12);

        if (m_subMode == 1) {
            drawShapeSeqScale(0x12, 0, 0xEA - m_figureMode * 0x14, 0xD4, FLOAT_80332d78, FLOAT_80332d78, 0xFF);
        }
    }
}
#else
void CShopMenu::DrawItemInfo0()
{
    if (m_selectedIndex == -1) {
        return;
    }

    int itemNo = getItemNo(m_selectedIndex);


    int languageId = static_cast<int>(Game.m_gameWork.GetLanguage()) - 1;
    MenuPcs.DrawInit();
    if (itemNo > 0) {
        MenuPcs.DrawSingleIcon(itemNo, 0x40, 100, FLOAT_80332d28, 0, FLOAT_80332d28);
    }

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    if (itemNo > 0) {
        font->SetMargin(FLOAT_80332d28);
        char* itemName = GetItemName(itemNo);
        _drawShadowFont(font, itemName, FLOAT_80332d54, FLOAT_80332d58, 0x18, 0x12);
        font->SetMargin(FLOAT_80332d28);
    }

    int canTrade = CheckSell(m_selectedIndex);

    if (canTrade) {
        font->SetMargin(FLOAT_80332d28);
        int amountRightX;
        char* unitText = ShopMenuMes(languageId, SHOP_MENU_TEXT_GIL);
        float unitWidth = font->GetWidth(unitText);
        float rightX = FLOAT_80332d3c - unitWidth;
        amountRightX = static_cast<int>(rightX - FLOAT_80332d5c);
        int totalGil = getBuySellGil(itemNo);

        CFont* amountFont = MenuPcs.GetFont22();
        SetupShopMenuGilFont(amountFont);
        DrawShopMenuAmountTrunc(amountFont, totalGil, amountRightX, FLOAT_80332d68, 0x1B);

        font->SetMargin(FLOAT_80332d28);
        _drawNoShadowFont(font, unitText, static_cast<float>(static_cast<int>(rightX)), FLOAT_80332d68, 0x19, 0x12);
    } else {
        font->SetMargin(FLOAT_80332d28);
        const char* message = (m_listType == 0) ? ShopMenuMes(languageId, SHOP_MENU_TEXT_CANNOT_BUY) :
                                                ShopMenuMes(languageId, SHOP_MENU_TEXT_CANNOT_SELL);
        float messageWidth = font->GetWidth(message);
        font->DrawInit();
        int messageX = static_cast<int>(FLOAT_80332d3c - messageWidth);
        MenuPcs.DrawNoShadowFont(font, const_cast<char*>(message), static_cast<float>(messageX), FLOAT_80332d68, 0x19, 0x12);
        MenuPcs.DrawInit();
        font->SetMargin(FLOAT_80332d28);
    }

    if (m_subMode == 0) {
        DrawItemInfo(itemNo, 0, 0xA8, 0, 0xC6, 0, 0xE4, 0x64);
    }

    if ((m_subMode == 1) && (m_listType == 0)) {
        CFont* countFont = MenuPcs.GetFont22();
        int countRightX = 0x108;
        int amount = m_quantity;
        SetupShopMenuValueFont(countFont);
        char countBuffer[64];
        sprintf(countBuffer, s_TwoDigitFormat_80332d18, amount);
        countRightX -= countFont->GetWidth(countBuffer);
        MenuPcs.DrawNoShadowFont(countFont, countBuffer, static_cast<float>(countRightX), FLOAT_80332d6c, 4, 0x12);
        MenuPcs.DrawInit();

        font->DrawInit();
        font->SetScale(FLOAT_80332d28);
        font->SetMargin(FLOAT_80332d28);
        const char* quantityText = ShopMenuMes(languageId, SHOP_MENU_TEXT_QUANTITY);
        float quantityWidth = font->GetWidth(quantityText);
        font->DrawInit();
        int quantityX = static_cast<int>(static_cast<float>(countRightX) - quantityWidth - FLOAT_80332d5c);
        MenuPcs.DrawNoShadowFont(font, const_cast<char*>(quantityText), static_cast<float>(quantityX), FLOAT_80332d6c, 0x18, 0x12);
        MenuPcs.DrawInit();

        if (m_subMode == 1) {
            int x = static_cast<int>(-(static_cast<float>(m_figureMode) * FLOAT_80332d74 - FLOAT_80332d70));
            drawShapeSeqScale(0x12, 0, x, 0xD4, FLOAT_80332d78, FLOAT_80332d78, 0xFF);
        }
    }
}
#endif

/*
 * --INFO--
 * PAL Address: 0x801507e0
 * PAL Size: 1640b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifdef VERSION_GCCJGC
void CShopMenu::DrawItemInfo(int itemNo, int x, int y, int attrX, int attrY, int effectX, int effectY, int colonX)
{
    if ((itemNo <= 0) || (itemNo > 0x9E)) {
        return;
    }

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    char* label = 0;
    int statType;
    if (MenuPcs.GetEquipType(itemNo) == 0) {
        label = "\x82\xB1\x82\xA4\x82\xB0\x82\xAB";
        statType = 0;
    } else if (MenuPcs.GetEquipType(itemNo) != 3) {
        label = "\x82\xDA\x82\xA4\x82\xAC\x82\xE5";
        statType = 1;
    } else {
        statType = 2;
    }

    SItemFlatRow* item = &reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2])[itemNo];
    unsigned short statValue = item->m_value;
    int attr = item->m_attribute;

    if (label != 0) {
        _drawNoShadowFont(font, label, static_cast<float>(x), static_cast<float>(y), 0x18, 0x12);
        _drawNoShadowFont(font, "\x81\x46", static_cast<float>(colonX), static_cast<float>(y), 0x18, 0x12);

        DrawDec(statValue, 0x1A, x + 0xB8, static_cast<float>(y), -1.0f, 0, 1, 0x12);

        font->SetMargin(4.0f);
        if ((statType == 1) && (attr >= 1)) {
            _drawNoShadowFont(font, "\x82\xC6\x82\xAD\x82\xB5\x82\xE3\x82\xB1\x82\xA4\x82\xA9", static_cast<float>(attrX), static_cast<float>(attrY), 0x16, 0x12);
            _drawNoShadowFont(font, MenuPcs.GetAttrStr(attr), static_cast<float>(effectX), static_cast<float>(effectY), 0x18, 0x12);

            char effectBuffer[256];
            effectX = static_cast<int>(static_cast<float>(effectX) + font->GetWidth(MenuPcs.GetAttrStr(attr)));
            if ((attr >= 1) && (attr <= 8)) {
                sprintf(effectBuffer, "%s", "\x81\x7B\x82\x50");
            } else {
                return;
            }
            _drawNoShadowFont(font, effectBuffer, static_cast<float>(effectX), static_cast<float>(effectY), 9, 0x12);
        }
    } else {
        _drawNoShadowFont(font, "\x82\xC6\x82\xAD\x82\xB5\x82\xE3\x82\xB1\x82\xA4\x82\xA9", static_cast<float>(x), static_cast<float>(y), 0x16, 0x12);
        _drawNoShadowFont(font, MenuPcs.GetAttrStr(attr), static_cast<float>(attrX), static_cast<float>(attrY), 0x18, 0x12);
        font->SetMargin(3.0f);

        char textBuffer[256];
        int fontColor = 9;
        attrX = static_cast<int>(static_cast<float>(attrX) + font->GetWidth(MenuPcs.GetAttrStr(attr)));
        if ((attr >= 1) && (attr <= 8)) {
            sprintf(textBuffer, "%s", "\x81\x7B\x82\x50");
        } else if ((attr == 0xB) || (attr == 0x11) || (attr == 0x12)) {
            sprintf(textBuffer, "%s%d", "\x81\x7B", statValue);
        } else if (!((attr != 9) && (attr != 10) && (attr != 0xC))) {
            sprintf(textBuffer, "%s%d", "\x81\x7C", statValue);
            fontColor = 3;
        } else {
            return;
        }
        _drawNoShadowFont(font, textBuffer, static_cast<float>(attrX), static_cast<float>(attrY), fontColor, 0x12);
    }
}
#else
void CShopMenu::DrawItemInfo(int itemNo, int x, int y, int unused0, int attrY, int unused1, int unused2, int unused3)
{
    (void)unused0;
    (void)unused1;
    (void)unused2;
    (void)unused3;

    if ((itemNo <= 0) || (itemNo > 0x9E)) {
        return;
    }

    CFont* font;
    int languageId;
    char* label;
    int langIndex;
    int equipType;
    SItemFlatRow* item;
    unsigned short statValue;
    int statType;
    int attr;
    float labelX;

    font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();

    languageId = static_cast<unsigned int>(Game.m_gameWork.GetLanguage());
    label = 0;
    langIndex = languageId - 1;
    equipType = MenuPcs.GetEquipType(itemNo);
    if (equipType == 0) {
        statType = 0;
        label = ShopMenuMes(langIndex, SHOP_MENU_TEXT_STRENGTH);
    } else {
        equipType = MenuPcs.GetEquipType(itemNo);
        if (equipType != 3) {
            statType = 1;
            label = ShopMenuMes(langIndex, SHOP_MENU_TEXT_DEFENCE);
        } else {
            statType = 2;
        }
    }

    item = &reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2])[itemNo];
    statValue = item->m_value;
    attr = item->m_attribute;
    char textBuffer[256];

    if (label != 0) {
        strcpy(textBuffer, label);
        strcat(textBuffer, s_Colon_80332d30);
        labelX = static_cast<float>(x + 0x40);
        _drawNoShadowFont(font, textBuffer, labelX, static_cast<float>(y), 0x18, 0x12);

        CFont* font2 = MenuPcs.m_fonts[0];
        int valueRightX = static_cast<int>(static_cast<float>(x + 0x108));
        SetupShopMenuValueFont(font2);

        char valueBuffer[64];
        sprintf(valueBuffer, s_DecimalFormat_80332d14, statValue);
        float valueWidth = font2->GetWidth(valueBuffer);
        valueRightX = static_cast<int>(static_cast<float>(valueRightX) - valueWidth);
        MenuPcs.DrawNoShadowFont(font2, valueBuffer, static_cast<float>(valueRightX), static_cast<float>(y), 0x1A, 0x12);
        MenuPcs.DrawInit();

        font->DrawInit();
        font->SetMargin(FLOAT_80332d28);
        font->SetScale(FLOAT_80332d28);

        if ((statType == 1) && (attr >= 1)) {
            font->SetScaleX(FLOAT_80332d2c);
            font->SetScaleY(FLOAT_80332d28);
            _drawNoShadowFont(font, MenuPcs.GetAttrStr(attr), labelX, static_cast<float>(attrY), 0x18, 0x12);

            font->SetScaleX(FLOAT_80332d28);
            font->GetWidth(MenuPcs.GetAttrStr(attr));
            if ((attr >= 1) && (attr <= 8)) {
                strcpy(textBuffer, s_PlusOne_80332d38);
                labelX = static_cast<float>(x) + (FLOAT_80332d3c - font->GetWidth(textBuffer));
            } else {
                return;
            }
            _drawNoShadowFont(font, textBuffer, labelX, static_cast<float>(attrY), 9, 0x12);
        }
    } else {
        font->SetScaleX(FLOAT_80332d2c);
        font->SetScaleY(FLOAT_80332d28);
        _drawNoShadowFont(font, MenuPcs.GetAttrStr(attr), static_cast<float>(x + 0x40), static_cast<float>(y), 0x18, 0x12);

        int fontColor = 9;
        if ((attr >= 1) && (attr <= 8)) {
            sprintf(textBuffer, s_StringFormat_80332d40, s_PlusOne_80332d38);
        } else {
            if ((attr == 0xB) || (attr == 0x11) || (attr == 0x12)) {
                sprintf(textBuffer, s_StringDecimalFormat_80332d44, s_Plus_80332d4c, statValue);
            } else {
                if (!((attr != 9) && (attr != 10) && (attr != 0xC))) {
                    sprintf(textBuffer, s_StringDecimalFormat_80332d44, s_Minus_80332d50, statValue);
                    fontColor = 3;
                } else {
                    return;
                }
            }
        }

        font->SetScaleX(FLOAT_80332d28);
        float valueWidth = font->GetWidth(textBuffer);
        _drawNoShadowFont(font, textBuffer, static_cast<float>(x) + (FLOAT_80332d3c - valueWidth), static_cast<float>(y), fontColor, 0x12);
    }
}
#endif

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#ifdef VERSION_GCCJGC
inline void CShopMenu::DrawItemHelp(int index, int centerX, int y)
{
    int itemNo = getItemNo(index);
    if (itemNo <= 0) {
        return;
    }

    char* text;
    if (CheckSell(index)) {
        text = Game.m_cFlatDataArr[1].TableStrings(6)[itemNo];
    } else {
        text = "\x82\xB1\x82\xCC\x82\xA9\x82\xB6\x82\xE2\x82\xC5\x82\xCD\x82\xC2\x82\xAD\x82\xEA\x82\xDC\x82\xB9\x82\xF1";
    }

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();
    int x = centerX - static_cast<int>(CMes::GetTagStringWidth(font, text)) / 2;
    font->SetPosX(static_cast<float>(x + 1));
    font->SetPosY(static_cast<float>(y - 3));
    font->SetTlut(0x12);
    CMes::DrawTagString(font, text);
    font->SetPosX(static_cast<float>(x));
    font->SetPosY(static_cast<float>(y - 4));
    font->SetTlut(7);
    CMes::DrawTagString(font, text);
}
#else
void CShopMenu::DrawItemHelp(int index, int centerX, int y)
{
    (void)index;

    int sel = m_selectedIndex;
    int itemNo = getItemNo(sel);
    int languageId = static_cast<int>(Game.m_gameWork.GetLanguage()) - 1;
    const char* sourceText;
    if (itemNo <= 0) {
        return;
    }

    int canSelect = CheckSell(sel);
    if (canSelect) {
        sourceText = Game.m_cFlatDataArr[1].TableStrings(6)[itemNo];
    } else {
        sourceText = ShopMenuMes(languageId, SHOP_MENU_TEXT_CANNOT_CRAFT_HERE);
    }

    char* helpText = new((Game.m_gameWork.m_menuStageMode != 0) ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage,
                         s_shopmenu_cpp, 0xBFF) char[0x200];
    if ((helpText == 0) && (static_cast<unsigned int>(System.m_execParam) >= 1)) {
        System.Printf(s_pcts_pctd_Error_memory_allocation_error_801DED9C, s_shopmenu_cpp, 0xC01);
    }
    memset(helpText, 0, 0x200);
    CMes::MakeAgbString(helpText, const_cast<char*>(sourceText), 0, 1);

    CFont* font = MenuPcs.GetFont22();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();
    int x = centerX - static_cast<int>(font->GetWidth(helpText)) / 2;
    font->SetPosX(static_cast<float>(x + 1));
    font->SetPosY(static_cast<float>(y - 3));
    font->SetTlut(0x12);
    font->Draw(helpText);
    font->SetPosX(static_cast<float>(x));
    font->SetPosY(static_cast<float>(y - 4));
    font->SetTlut(7);
    font->Draw(helpText);
    delete[] helpText;
}
#endif

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::DrawDec(int value, int tlut, int x, float y, float margin, int zeroPad, int fixed, int flags)
{
    CFont* font = MenuPcs.GetFont22();
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();
    font->SetFixed(fixed);
    font->SetMargin(margin);

    char buffer[64];
    if (zeroPad != 0) {
        sprintf(buffer, "%02d", value);
    } else {
        sprintf(buffer, "%d", value);
    }
    x -= font->GetWidth(buffer);
    MenuPcs.DrawNoShadowFont(font, buffer, static_cast<float>(x), y, tlut, flags);
    MenuPcs.DrawInit();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::DrawDecScale(int value, int tlut, int x, float y, float margin, float scaleY, int shadow, int fixed,
                                     int flags)
{
    CFont* font = MenuPcs.GetFont22();
    font->SetShadow(shadow);
    font->SetScaleX(FLOAT_80332d28);
    font->SetScaleY(scaleY);
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    font->DrawInit();
    font->SetFixed(fixed);
    font->SetMargin(margin);

    char buffer[64];
    sprintf(buffer, "%d", value);
    x -= font->GetWidth(buffer);
    MenuPcs.DrawNoShadowFont(font, buffer, static_cast<float>(x), y, tlut, flags);
    MenuPcs.DrawInit();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::setFaceAlpha(int, int alpha)
{
    m_faceAlpha = alpha;
}

extern const unsigned int gShopMenuAmbientWhite = 0xFFFFFFFF;
extern const unsigned int gShopMenuMaterialWhiteBase = 0xFFFFFFFF;
extern const unsigned int DAT_80332D04 = 0xFFFFFFFF;
extern const unsigned int DAT_80332D08 = 0xFFFFFFFF;
extern const unsigned int DAT_80332D0C = 0xFFFFFFFF;
extern const float FLOAT_80332D10 = -4.0f;
extern const double DOUBLE_80332D20 = 4503601774854144.0;
extern const float FLOAT_80332d28 = 1.0f;
extern const float FLOAT_80332d2c = 0.8f;
extern const float FLOAT_80332d34 = -5.0f;
extern const float FLOAT_80332d3c = 264.0f;
extern const float FLOAT_80332d54 = 100.0f;
extern const float FLOAT_80332d58 = 104.0f;
extern const float FLOAT_80332d5c = 8.0f;
extern const float FLOAT_80332d60 = 0.25f;
extern const float FLOAT_80332d64 = -6.0f;
extern const float FLOAT_80332d68 = 136.0f;
extern const float FLOAT_80332d6c = 172.0f;
extern const float FLOAT_80332d70 = 259.0f;
extern const float FLOAT_80332d74 = 18.0f;
extern const float FLOAT_80332d78 = 0.5f;
extern const float FLOAT_80332d7c = 352.0f;
extern const float FLOAT_80332d80 = 300.0f;
extern const float FLOAT_80332d88 = 340.0f;
extern const float FLOAT_80332d8c = 1.5f;
extern const float FLOAT_80332d90 = 336.0f;
extern const float FLOAT_80332d94 = 558.0f;
extern const float FLOAT_80332d98 = 348.0f;
extern const float FLOAT_80332D9C = 0.0f;
extern const double DOUBLE_80332DA0 = 255.0;
extern const double DOUBLE_80332DA8 = 0.5;
extern const double DOUBLE_80332DB0 = 0.05;
extern const double DOUBLE_80332DB8 = 0.7;
extern const double DOUBLE_80332DC0 = 0.03;
extern const float FLOAT_80332DC8 = 0.7f;
extern const float FLOAT_80332DCC = 0.4f;
extern const float FLOAT_80332DD0 = -0.5f;
extern const float FLOAT_80332DD4 = 88.0f;
extern const float FLOAT_80332DD8 = 308.0f;
extern const float FLOAT_80332DDC = 332.0f;
extern const float FLOAT_80332DE0 = 255.0f;
extern const float FLOAT_80332DE4 = 320.0f;
extern const float FLOAT_80332DE8 = 224.0f;
extern const float FLOAT_80332DEC = 448.0f;
extern const float FLOAT_80332DF0 = 640.0f;
extern const float FLOAT_80332DF4 = -640.0f;
extern const float FLOAT_80332DF8 = -448.0f;
extern const float FLOAT_80332DFC = 1279.0f;
extern const float FLOAT_80332E00 = 895.0f;
extern const float FLOAT_80332E04 = 70.0f;
extern const float FLOAT_80332E08 = 316.0f;
extern const float FLOAT_80332E0C = 54.0f;
extern const float FLOAT_80332E10 = -2.0f;
extern const float FLOAT_80332E14 = 312.0f;
extern const float FLOAT_80332E18 = 180.0f;
extern const float FLOAT_80332E1C = 520.0f;
extern const float FLOAT_80332E20 = 192.0f;
extern const float FLOAT_80332E24 = 144.0f;
extern const float FLOAT_80332E28 = 96.0f;
extern const float FLOAT_80332E2C = 344.0f;
extern const float FLOAT_80332E30 = 200.0f;
extern const float FLOAT_80332E34 = 260.0f;
extern const float FLOAT_80332E38 = 36.0f;
extern const float FLOAT_80332E3C = 384.0f;
extern const float FLOAT_80332E44 = 356.0f;
extern const float FLOAT_80332e48 = 40.0f;
extern const float FLOAT_80332e4c = 250.0f;
extern const float FLOAT_80332E50 = 0.125f;
