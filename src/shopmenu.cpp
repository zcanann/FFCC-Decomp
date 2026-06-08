#include "ffcc/shopmenu.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/materialman.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/sound.h"
#include "ffcc/linkage.h"
#include "ffcc/mes.h"
#include "ffcc/memory.h"
#include "ffcc/p_tina.h"
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>

char s_shopmenu_cpp[] = "shopmenu.cpp";
extern char s_shop_80332e54[];
unsigned short gShopMenuInputLatch;
extern CShopMenu* g_shopMenu;
extern float FLOAT_80332d10;
extern float FLOAT_80332d28;
extern float FLOAT_80332d2c;
extern float FLOAT_80332d34;
extern float FLOAT_80332d3c;
extern float FLOAT_80332d5c;
extern float FLOAT_80332d60;
extern float FLOAT_80332d64;
extern float FLOAT_80332d54;
extern float FLOAT_80332d58;
extern float FLOAT_80332d68;
extern float FLOAT_80332d6c;
extern float FLOAT_80332d70;
extern float FLOAT_80332d74;
extern float FLOAT_80332d78;
extern float FLOAT_80332dc8;
extern float FLOAT_80332dcc;
extern float FLOAT_80332dd0;
extern float FLOAT_80332dec;
extern float FLOAT_80332df0;
extern float FLOAT_80332de0;
extern float FLOAT_80332e0c;
extern float FLOAT_80332e10;
extern float FLOAT_80332e14;
extern float FLOAT_80332e18;
extern float FLOAT_80332e1c;
extern float FLOAT_80332e20;
extern float FLOAT_80332e24;
extern float FLOAT_80332e28;
extern float FLOAT_80332e2c;
extern float FLOAT_80332e30;
extern float FLOAT_80332e34;
extern float FLOAT_80332e38;
extern float FLOAT_80332e3c;
extern float FLOAT_80332e44;
extern float FLOAT_80332e48;
extern float FLOAT_80332e4c;
extern float FLOAT_80332d7c;
extern float FLOAT_80332d80;
extern float FLOAT_80332d88;
extern float FLOAT_80332d8c;
extern float FLOAT_80332d90;
extern float FLOAT_80332d94;
extern float FLOAT_80332d98;
extern float FLOAT_80332d9c;
extern double DOUBLE_80332DA0;
extern double DOUBLE_80332DA8;
extern double DOUBLE_80332DB0;
extern double DOUBLE_80332DB8;
extern double DOUBLE_80332DC0;
extern unsigned int gShopMenuAmbientWhite;
extern unsigned int gShopMenuMaterialWhiteBase;
extern char s_Slash_80332d84[];
extern char s_DecimalFormat_80332d14[];
extern char s_TwoDigitFormat_80332d18[];
extern char s_Colon_80332d30[];
extern char s_PlusOne_80332d38[];
extern char s_StringFormat_80332d40[];
extern char s_StringDecimalFormat_80332d44[];
extern char s_Plus_80332d4c[];
extern char s_Minus_80332d50[];
extern "C" char* g_strShopMenuMes[];

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

ShopMenuTopMenuEntry s_shopMenuTopMenuEntries[] = {
    {0x1AE, 0x78, 0},
    {0x186, 0xDC, 0},
    {0x1AE, 0x140, 0},
};
ShopMenuTopMenuEntry* s_currentShopMenuTopMenuEntry;
s8 s_shopMenuTopMenuTextInitialized;

enum ShopMenuTextIndex {
    SHOP_MENU_TEXT_BUY = 0,
    SHOP_MENU_TEXT_SELL = 1,
    SHOP_MENU_TEXT_CANCEL = 2,
    SHOP_MENU_TEXT_TITLE = 3,
    SHOP_MENU_TEXT_BLACKSMITH = 4,
    SHOP_MENU_TEXT_RACE = 5,
    SHOP_MENU_TEXT_GIL = 6,
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

static inline char* ShopMenuMes(int languageIndex, int textIndex)
{
    return g_strShopMenuMes[languageIndex * 0x15 + textIndex];
}

static inline void* PartPcsVoid()
{
    return &PartPcs;
}

static inline int& ShopMenuInt(CShopMenu* shopMenu, int offset)
{
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + offset);
}

static inline int* GetShopMenuHelpMsgTable()
{
    return reinterpret_cast<int*>(Game.m_cFlatDataArr[1].TableStrings(6));
}

static inline float& ShopMenuFloat(CShopMenu* shopMenu, int offset)
{
    return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(shopMenu) + offset);
}

static inline unsigned short GetPadButtons()
{
    bool hasInput = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
    unsigned short buttons;
    if (hasInput) {
        buttons = 0;
    } else {
        int padIndex = 0;
        padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
        buttons = Pad.GetPadInputs()[padIndex].buttonDown[0];
    }
    return buttons;
}

static unsigned short GetShopMenuListButtons()
{
    unsigned short buttons;
    if (gShopMenuInputLatch == 0) {
        bool hasInput = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
        if (hasInput) {
            buttons = 0;
        } else {
            int padIndex = 0;
            padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
            buttons = Pad.GetPadInputs()[padIndex].repeatButton;
        }
        return buttons;
    }

    bool hasInput = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
    if (hasInput) {
        buttons = 0;
    } else {
        int padIndex = 0;
        padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
        buttons = Pad.GetPadInputs()[padIndex].button[0];
    }

    if ((buttons & gShopMenuInputLatch) == 0) {
        gShopMenuInputLatch = 0;
    }

    hasInput = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
    if (hasInput) {
        buttons = 0;
    } else {
        int padIndex = 0;
        padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
        buttons = Pad.GetPadInputs()[padIndex].buttonDown[0];
    }
    return buttons;
}

static inline CCaravanWork* ShopMenuCaravanWork(CShopMenu* shopMenu)
{
    return shopMenu->m_caravanWork;
}

static float CalcCenteredShopMenuX(CFont* font, const char* text)
{
    return static_cast<float>(static_cast<int>((464.0f - font->GetWidth(text)) * 0.5f + 80.0f));
}

static int ResolveShopMenuItemCount(CShopMenu* shopMenu)
{
    int listType = shopMenu->m_listType;
    const CCaravanWork* const caravanWork = ShopMenuCaravanWork(shopMenu);
    if (listType == 0) {
        return caravanWork->m_shopListCount;
    }
    if (listType == 1) {
        return 0x40;
    }
    if (listType == 2) {
        return shopMenu->m_itemCount;
    }
    return 0;
}

static int ResolveShopMenuItemNo(CShopMenu* shopMenu, int index)
{
    int listType = shopMenu->m_listType;
    const CCaravanWork* const caravanWork = ShopMenuCaravanWork(shopMenu);
    if (listType == 0) {
        return caravanWork->m_shopList[index];
    }
    if (listType == 1) {
        return caravanWork->m_inventoryItems[index];
    }
    if (listType == 2) {
        int mapped = shopMenu->m_itemTable[index];
        if (mapped == -1) {
            return -1;
        }
        return caravanWork->m_inventoryItems[mapped];
    }
    return -1;
}

static int CalcShopMenuMakeGil(CShopMenu* shopMenu, int itemId)
{
    if (itemId < 1) {
        return 0;
    }

    const CCaravanWork* const caravanWork = ShopMenuCaravanWork(shopMenu);
    int gilValue = caravanWork->m_shopParam *
                   *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x24);
    return gilValue / 100;
}

static int CalcShopMenuGilRatio(CShopMenu* shopMenu, int baseGil)
{
    if (baseGil <= 0) {
        return 0;
    }

    const CCaravanWork* const caravanWork = ShopMenuCaravanWork(shopMenu);
    int gil = caravanWork->m_shopParam * baseGil;
    gil = gil / 100 + (gil >> 0x1F);
    return gil - (gil >> 0x1F);
}

static int GetShopMenuItemBaseGil(int itemNo, int offset)
{
    if (itemNo < 1) {
        return 0;
    }

    return *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + offset);
}

static int CalcShopMenuTradeGil(CShopMenu* shopMenu, int itemNo)
{
    int gilValue = CalcShopMenuGilRatio(shopMenu, GetShopMenuItemBaseGil(itemNo, 0x20));
    if (shopMenu->m_listType == 1) {
        return static_cast<int>(FLOAT_80332d60 * static_cast<float>(gilValue));
    }
    if ((shopMenu->m_listType != 0) && (shopMenu->m_listType != 1)) {
        return -1;
    }
    return gilValue;
}

static int CountShopMenuOwnedItems(CCaravanWork* caravanWork, int itemNo)
{
    if (itemNo < 1) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < 0x40; i++) {
        if (caravanWork->m_inventoryItems[i] == itemNo) {
            ++count;
        }
    }
    return count;
}

static bool CanTradeShopMenuItem(CShopMenu* shopMenu, int index, int itemNo)
{
    if ((index < 0) || (itemNo < 1)) {
        return false;
    }

    int listType = shopMenu->m_listType;
    if (listType == 0) {
        return true;
    }

    if (listType == 2) {
        unsigned int bit = static_cast<unsigned int>(itemNo - 0x191);
        return (ShopMenuCaravanWork(shopMenu)->m_shopArgs[(itemNo - 0x191) >> 5] & (1U << (bit & 0x1F))) != 0;
    }

    if (MenuPcs.EquipChk(index) != 0) {
        return false;
    }

    return itemNo >= 0x9F;
}


static void SetupShopMenuInfoFont(CFont* font)
{
    font->DrawInit();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
}

static void SetupShopMenuUnitFont(CFont* font)
{
    font->DrawInit();
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    font->SetMargin(FLOAT_80332d28);
}

static void SetupShopMenuAmountFont(CFont* font)
{
    font->SetShadow(1);
    font->SetScaleX(FLOAT_80332d28);
    font->SetScaleY(FLOAT_80332d8c);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
    font->DrawInit();
    reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
    font->SetMargin(FLOAT_80332d64);
}

static void SetupShopMenuMakeAmountFont(CFont* font)
{
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
    font->DrawInit();
    reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
    font->SetMargin(FLOAT_80332e10 * FLOAT_80332d28 + FLOAT_80332d10);
}

static void SetupShopMenuMakeOwnedFont(CFont* font)
{
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
    font->DrawInit();
    reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
    font->SetMargin(FLOAT_80332d64);
}

static void DrawShopMenuAmount(CFont* font, int value, float rightEdge, float y, int tlut)
{
    char amountBuffer[64];
    sprintf(amountBuffer, s_DecimalFormat_80332d14, value);
    float amountWidth = font->GetWidth(amountBuffer);
    MenuPcs.DrawNoShadowFont(font, amountBuffer, rightEdge - amountWidth, y, tlut, 0x12);
    MenuPcs.DrawInit();
}

static void DrawShopMenuRightAlignedText(CFont* font, const char* text, float rightEdge, float y, int tlut)
{
    if (text == 0) {
        return;
    }

    float textWidth = font->GetWidth(text);
    MenuPcs.DrawNoShadowFont(font, const_cast<char*>(text), rightEdge - textWidth, y, tlut, 0x12);
    MenuPcs.DrawInit();
}

static void SetupShopMenuLabelFont(CFont* font)
{
    font->DrawInit();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(0);
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
}

static inline CFont* GetShopMenuInfoPanelFont()
{
    return MenuPcs.m_fonts[0];
}

static void DrawShopMenuCenteredText(CFont* font, const char* text, float centerX, float y)
{
    if (text == 0) {
        return;
    }

    float textX = centerX - font->GetWidth(text) * FLOAT_80332d78;
    font->DrawInit();
    font->SetPosX(textX);
    font->SetPosY(y);
    font->Draw(text);
}

static int GetShopMenuFigureStep(CShopMenu* shopMenu)
{
    return (shopMenu->m_figureMode == 1) ? 10 : 1;
}



/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _drawNoShadowFont(CFont* font, char* text, float x, float y, int tlut, int flags)
{
	MenuPcs.DrawNoShadowFont(font, text, x, y, tlut, flags);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _drawShadowFont(CFont* font, char* text, float x, float y, int tlut, int flags)
{
	MenuPcs.DrawShadowFont(font, text, x, y, tlut, flags);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned short getButtonRepeat(int, unsigned short noRepeatMask)
{
    unsigned short buttons;

    if (gShopMenuInputLatch == 0) {
        bool hasInput = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort));
            buttons = Pad.GetPadInputs()[0].repeatButton;
        }
    } else {
        bool hasInput = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort));
            buttons = Pad.GetPadInputs()[0].button[0];
        }

        if ((buttons & gShopMenuInputLatch) == 0) {
            gShopMenuInputLatch = 0;
        }

        hasInput = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort));
            buttons = Pad.GetPadInputs()[0].buttonDown[0];
        }
    }

    if ((buttons & noRepeatMask) != 0) {
        gShopMenuInputLatch = noRepeatMask;
    }

    return buttons;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void bButtonNoRepeat(unsigned short button)
{
    gShopMenuInputLatch = button;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::getItemCnt()
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
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::calcGilRatio(int baseGil)
{
    return CalcShopMenuGilRatio(this, baseGil);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::getItemNo(int index)
{
    int listType = m_listType;
    if (listType == 0) {
        return m_caravanWork->m_shopList[index];
    }
    if (listType == 1) {
        return m_caravanWork->m_inventoryItems[index];
    }
    if (listType == 2) {
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
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::getBuyGil(int itemNo)
{
    return calcGilRatio(GetShopMenuItemBaseGil(itemNo, 0x20));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::getSellGil(int itemNo)
{
    return static_cast<int>(FLOAT_80332d60 * static_cast<float>(getBuyGil(itemNo)));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::getMakeGil(int itemNo)
{
    return calcGilRatio(GetShopMenuItemBaseGil(itemNo, 0x24));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::getBuySellGil(int itemNo)
{
    int listType = m_listType;
    if (listType == 0) {
        return getBuyGil(itemNo);
    }
    if (listType == 1) {
        return getSellGil(itemNo);
    }
    if (listType == 2) {
        return getMakeGil(itemNo);
    }
    return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
char* CShopMenu::GetItemName(int itemNo)
{
    if (itemNo < 1) {
        return 0;
    }

    return reinterpret_cast<char*>(reinterpret_cast<int*>(Game.m_cFlatDataArr[1].TableStrings(0))[itemNo * 5 + 4]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::GetMaxExchange()
{
    int itemNo = getItemNo(m_selectedIndex);
    if (itemNo < 1) {
        return 0;
    }

    const CCaravanWork* const caravanWork = ShopMenuCaravanWork(this);
    int listType = m_listType;
    if (listType == 0) {
        int maxCount = 0x40 - caravanWork->m_inventoryItemCount;
        int unitGil = getBuyGil(itemNo);
        if (unitGil > 0) {
            int byMoney = caravanWork->m_gil / unitGil;
            if (byMoney < maxCount) {
                maxCount = byMoney;
            }
        }
        return maxCount;
    }
    if (listType == 1) {
        return getItemHaveCnt(itemNo);
    }
    if (listType == 2) {
        return 1;
    }
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::GetTotalGil()
{
    int unitGil = getBuySellGil(getItemNo(m_selectedIndex));
    if (unitGil < 0) {
        return unitGil;
    }

    return m_quantity * unitGil;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::CanAddGil()
{
    int totalGil = GetTotalGil();
    if (totalGil < 0) {
        return 0;
    }

    if (m_listType != 1) {
        totalGil = -totalGil;
    }
    return ShopMenuCaravanWork(this)->CanAddGil(totalGil);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::CheckSell(int index)
{
    return CanTradeShopMenuItem(this, index, getItemNo(index)) ? 1 : 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::getItemHaveCnt(int itemNo)
{
    return CountShopMenuOwnedItems(ShopMenuCaravanWork(this), itemNo);
}

static long* GetShopMenuShapeAnimData(int shapeNo)
{
    pppShapeSt** shapeTable = ppvEnv->m_resourceTables.m_shapeTablePtr;
    if (shapeTable == 0) {
        return 0;
    }

    pppShapeSt* shape = shapeTable[shapeNo];
    if ((shape == 0) || (shape->m_animData == 0)) {
        return 0;
    }

    return reinterpret_cast<long*>(shape->m_animData);
}

static tagOAN3_SHAPE* GetShopMenuFrameShape(long* animData, int groupNo)
{
    if ((animData == 0) || (groupNo < 0)) {
        return 0;
    }

    pppShapeAnimData* shapeAnim = reinterpret_cast<pppShapeAnimData*>(animData);
    if (groupNo >= shapeAnim->m_frameCount) {
        return 0;
    }

    int shapeOffset = shapeAnim->m_frames[groupNo].m_shapeOffset;
    return reinterpret_cast<tagOAN3_SHAPE*>(reinterpret_cast<u8*>(shapeAnim) + shapeOffset);
}

static void SetupShopMenuShapeDrawColor(unsigned char alpha)
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
void setOrtho(int x, int y, float scaleX, float scaleY, float zOffset)
{
    Mtx screenMtx;
    Mtx44 projectionMtx;

    PSMTXIdentity(screenMtx);
    screenMtx[0][0] = scaleX;
    screenMtx[1][1] = -scaleY;
    screenMtx[0][3] = static_cast<float>(x);
    screenMtx[1][3] = static_cast<float>(y);
    screenMtx[2][2] = FLOAT_80332d78;

    GXLoadPosMtxImm(screenMtx, 0);
    GXSetCurrentMtx(0);

    C_MTXOrtho(projectionMtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, FLOAT_80332d28);
    projectionMtx[2][3] += zOffset;
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);

    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetColorUpdate(GX_TRUE);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShp(tagOAN3_SHAPE* shape, CMaterialSet* materialSet, unsigned char alpha)
{
    if ((shape == 0) || (materialSet == 0)) {
        return;
    }

    SetupShopMenuShapeDrawColor(alpha);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    MaterialMan.SetMaterialMenu(
        materialSet, static_cast<int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(shape) + 10)), 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    unsigned char* shapeBytes = reinterpret_cast<unsigned char*>(shape);
    int shapeCount = *reinterpret_cast<unsigned short*>(shapeBytes + 2);
    for (int i = 0; i < shapeCount; i++) {
        GXCallDisplayList(*reinterpret_cast<void**>(shapeBytes + 0xC + i * 8), 0x60);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeq0(int shapeNo, int groupNo, unsigned char alpha, unsigned char tlut)
{
    drawShapeSeq(shapeNo, groupNo, 0, 0, alpha, 0, 0, 0.0f, tlut);
}




/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawGrouadQuad(int x, int y, int width, int height, _GXColor colorA, _GXColor colorB, _GXColor colorC, _GXColor colorD)
{
    setOrtho(x, y, FLOAT_80332d78, FLOAT_80332d78, 0.0f);
    SetupShopMenuShapeDrawColor(0xFF);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);

    Vec minPos = {0.0f, 0.0f, 0.0f};
    Vec maxPos = {static_cast<float>(width), static_cast<float>(height), 0.0f};
    Graphic.RenderNoTexQuadGrouad(minPos, maxPos, colorA, colorB, colorC, colorD);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Init(int mode)
{
    gShopMenuInputLatch = 0;
    SetMode(mode);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Destroy()
{
    PartPcs.ReleasePdt(m_pdtSlot);
    if (MenuPcs.m_shopMenu == this) {
        MenuPcs.m_shopMenu = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawItemHelp(int index, int centerX, int y)
{
    int itemNo = getItemNo(index);
    if (itemNo <= 0) {
        return;
    }

    const char* sourceText;
    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    if (CanTradeShopMenuItem(this, index, getItemNo(index))) {
        sourceText = reinterpret_cast<const char*>(GetShopMenuHelpMsgTable()[itemNo]);
    } else {
        sourceText = ShopMenuMes(languageId, SHOP_MENU_TEXT_CANNOT_CRAFT_HERE);
    }
    if (sourceText == 0) {
        return;
    }

    char* helpText = new((Game.m_gameWork.m_menuStageMode != 0) ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage,
                         s_shopmenu_cpp, 0xBFF) char[0x200];
    if (helpText == 0) {
        return;
    }
    memset(helpText, 0, 0x200);
    CMes::MakeAgbString(helpText, const_cast<char*>(sourceText), 0, 1);

    CFont* font = MenuPcs.m_fonts[0];
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);

    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
    float width = font->GetWidth(helpText);
    float x = static_cast<float>(centerX) - width * 0.5f;
    font->DrawInit();
    font->SetPosX(x + 1.0f);
    font->SetPosY(static_cast<float>(y - 3));
    font->SetTlut(0x12);
    font->Draw(helpText);
    font->SetPosX(x);
    font->SetPosY(static_cast<float>(y - 4));
    font->SetTlut(7);
    font->Draw(helpText);
    delete[] helpText;
}
/*
 * --INFO--
 * PAL Address: 0x801507e0
 * PAL Size: 1640b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::DrawItemInfo(int itemNo, int x, int y, int unused0, int attrY, int unused1, int unused2, int unused3)
{
    (void)unused0;
    (void)unused1;
    (void)unused2;
    (void)unused3;

    if ((itemNo <= 0) || (itemNo > 0x9E)) {
        return;
    }

    CFont* font = GetShopMenuInfoPanelFont();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
    font->DrawInit();

    int languageId = static_cast<unsigned int>(Game.m_gameWork.m_languageId);
    int equipType = MenuPcs.GetEquipType(itemNo);
    int statType;
    char* label = 0;
    if (equipType == 0) {
        statType = 0;
        label = ShopMenuMes(languageId - 1, SHOP_MENU_TEXT_STRENGTH);
    } else {
        equipType = MenuPcs.GetEquipType(itemNo);
        if (equipType == 3) {
            statType = 2;
        } else {
            statType = 1;
            label = ShopMenuMes(languageId - 1, SHOP_MENU_TEXT_DEFENCE);
        }
    }

    int itemData = Game.unkCFlatData0[2] + itemNo * 0x48;
    short statValue = *reinterpret_cast<short*>(itemData + 6);
    int attr = *reinterpret_cast<unsigned short*>(itemData + 8);
    char textBuffer[256];

    if (label != 0) {

    strcpy(textBuffer, label);
    strcat(textBuffer, s_Colon_80332d30);
    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, textBuffer, static_cast<float>(x + 0x40), static_cast<float>(y), 0x18, 0x12);
    MenuPcs.DrawInit();

    unsigned int valueRightX = x + 0x108;
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    {
        CColor valueWhite(0xFF, 0xFF, 0xFF, 0xFF);
        font->SetColor(valueWhite.color);
    }
    font->DrawInit();
    reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
    font->SetMargin(FLOAT_80332d34);

    char valueBuffer[64];
    sprintf(valueBuffer, s_DecimalFormat_80332d14, statValue);
    float valueWidth = font->GetWidth(valueBuffer);
    MenuPcs.DrawNoShadowFont(font, valueBuffer, static_cast<float>(valueRightX) - valueWidth, static_cast<float>(y), 0x1A, 0x12);
    MenuPcs.DrawInit();

    font->DrawInit();
    font->SetMargin(FLOAT_80332d28);
    font->SetScale(FLOAT_80332d28);

    if ((statType == 1) && (attr != 0)) {
        font->SetScaleX(FLOAT_80332d2c);
        font->SetScaleY(FLOAT_80332d28);
        char* attrStr = MenuPcs.GetAttrStr(attr);
        font->DrawInit();
        MenuPcs.DrawNoShadowFont(font, attrStr, static_cast<float>(x + 0x40), static_cast<float>(attrY), 0x18, 0x12);
        MenuPcs.DrawInit();

        font->SetScaleX(FLOAT_80332d28);
        attrStr = MenuPcs.GetAttrStr(attr);
        font->GetWidth(attrStr);
        if ((attr != 0) && (attr < 9)) {
            strcpy(textBuffer, s_PlusOne_80332d38);
            valueWidth = font->GetWidth(textBuffer);
            font->DrawInit();
            MenuPcs.DrawNoShadowFont(font, textBuffer, static_cast<float>(x) + (FLOAT_80332d3c - valueWidth), static_cast<float>(attrY), 9, 0x12);
            MenuPcs.DrawInit();
        }
    }
    } else {
        font->SetScaleX(FLOAT_80332d2c);
        font->SetScaleY(FLOAT_80332d28);
        char* attrStr = MenuPcs.GetAttrStr(attr);
        font->DrawInit();
        MenuPcs.DrawNoShadowFont(font, attrStr, static_cast<float>(x + 0x40), static_cast<float>(y), 0x18, 0x12);
        MenuPcs.DrawInit();

        int fontColor = 9;
        if ((attr == 0) || (attr >= 9)) {
            if ((attr == 0xB) || (attr == 0x11) || (attr == 0x12)) {
                sprintf(textBuffer, s_StringDecimalFormat_80332d44, s_Plus_80332d4c, statValue);
            } else {
                if ((attr != 9) && (attr != 10) && (attr != 0xC)) {
                    return;
                }
                sprintf(textBuffer, s_StringDecimalFormat_80332d44, s_Minus_80332d50, statValue);
                fontColor = 3;
            }
        } else {
            sprintf(textBuffer, s_StringFormat_80332d40, s_PlusOne_80332d38);
        }

        font->SetScaleX(FLOAT_80332d28);
        float valueWidth = font->GetWidth(textBuffer);
        font->DrawInit();
        MenuPcs.DrawNoShadowFont(font, textBuffer, static_cast<float>(x) + (FLOAT_80332d3c - valueWidth), static_cast<float>(y), fontColor, 0x12);
        MenuPcs.DrawInit();
    }
}
/*
 * --INFO--
 * PAL Address: 0x80150e50
 * PAL Size: 2284b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::DrawItemInfo0()
{
    int itemIndex = m_selectedIndex;
    if (itemIndex == -1) {
        return;
    }

    const CCaravanWork* const caravanWork = ShopMenuCaravanWork(this);
    int itemNo = getItemNo(itemIndex);

    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    MenuPcs.DrawInit();
    if (itemNo > 0) {
        MenuPcs.DrawSingleIcon(itemNo, 0x40, 100, FLOAT_80332d28, 0, FLOAT_80332d28);
    }

    CFont* font = GetShopMenuInfoPanelFont();
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScaleX(FLOAT_80332d2c);
    font->SetScaleY(FLOAT_80332d28);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
    font->DrawInit();

    if (itemNo > 0) {
        font->SetMargin(FLOAT_80332d28);
        char* itemName = 0;
        if (itemNo >= 1) {
            itemName = reinterpret_cast<char*>(reinterpret_cast<int*>(Game.m_cFlatDataArr[1].TableStrings(0))[itemNo * 5 + 4]);
        }
        font->DrawInit();
        MenuPcs.DrawShadowFont(font, itemName, FLOAT_80332d54, FLOAT_80332d58, 0x18, 0x12);
        MenuPcs.DrawInit();
        font->SetMargin(FLOAT_80332d28);
    }

    bool canTrade = false;
    if (itemNo > 0) {
        if (m_listType == 0) {
            canTrade = true;
        } else if (m_listType == 2) {
            canTrade = true;
            if ((caravanWork->m_shopArgs[(itemNo - 0x191U) >> 5] &
                 (1U << ((itemNo - 0x191U) & 0x1F))) == 0) {
                canTrade = false;
            }
        } else if (m_listType == 1) {
            if (MenuPcs.EquipChk(itemIndex) == 0) {
                canTrade = itemNo >= 0x9F;
            }
        }
    }

    if (canTrade) {
        SetupShopMenuUnitFont(font);
        char* unitText = ShopMenuMes(languageId, SHOP_MENU_TEXT_GIL);
        float unitWidth = font->GetWidth(unitText);
        float rightX = FLOAT_80332d3c - unitWidth;
        float amountRightX = rightX - FLOAT_80332d5c;
        int totalGil;

        if (m_listType == 0) {
            if (itemNo < 1) {
                totalGil = 0;
            } else {
                totalGil = static_cast<int>(caravanWork->m_shopParam) *
                           *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                totalGil = totalGil / 100;
            }
        } else if (m_listType == 1) {
            if (itemNo < 1) {
                totalGil = 0;
            } else {
                int gil = static_cast<int>(caravanWork->m_shopParam) *
                          *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                gil = gil / 100;
                totalGil = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil));
            }
        } else {
            totalGil = -1;
        }

        SetupShopMenuAmountFont(font);
        DrawShopMenuAmount(font, totalGil, amountRightX, FLOAT_80332d68, 0x1B);

        SetupShopMenuUnitFont(font);
        font->DrawInit();
        MenuPcs.DrawNoShadowFont(font, unitText, rightX, FLOAT_80332d68, 0x19, 0x12);
        MenuPcs.DrawInit();
    } else {
        SetupShopMenuUnitFont(font);
        const char* message = (m_listType == 0) ? ShopMenuMes(languageId, SHOP_MENU_TEXT_CANNOT_BUY) :
                                                ShopMenuMes(languageId, SHOP_MENU_TEXT_CANNOT_SELL);
        font->DrawInit();
        DrawShopMenuRightAlignedText(font, message, FLOAT_80332d3c, FLOAT_80332d68, 0x19);
    }

    if (m_subMode == 0) {
        DrawItemInfo(itemNo, 0, 0xA8, 0, 0xC6, 0, 0, 0);
    }

    if ((m_subMode == 1) && (m_listType == 0)) {
        int amount = m_quantity;
        font->SetShadow(1);
        font->SetScale(FLOAT_80332d28);
        font->SetColor(white.color);
        font->DrawInit();
        reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
        font->SetMargin(FLOAT_80332d34);
        char countBuffer[64];
        sprintf(countBuffer, s_TwoDigitFormat_80332d18, amount);
        float countRightX = FLOAT_80332d70 - font->GetWidth(countBuffer);
        MenuPcs.DrawNoShadowFont(font, countBuffer, countRightX, FLOAT_80332d6c, 4, 0x12);
        MenuPcs.DrawInit();

        SetupShopMenuInfoFont(font);
        const char* quantityText = ShopMenuMes(languageId, SHOP_MENU_TEXT_QUANTITY);
        font->DrawInit();
        DrawShopMenuRightAlignedText(font, quantityText, countRightX - FLOAT_80332d5c, FLOAT_80332d6c, 0x18);

        int x = static_cast<int>(-(static_cast<float>(m_figureMode) * FLOAT_80332d74 - FLOAT_80332d70));
        drawShapeSeqScale(0x12, 0, x, 0xD4, FLOAT_80332d78, FLOAT_80332d78, 0xFF);
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
void CShopMenu::DrawBuySellInfo()
{
    CFont* font = MenuPcs.m_fonts[0];
    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    int listType = m_listType;

    SetupShopMenuInfoFont(font);

    char* priceText = ShopMenuMes(languageId, SHOP_MENU_TEXT_PRICE);
    float priceWidth = font->GetWidth(priceText);
    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, priceText, FLOAT_80332d7c - priceWidth, FLOAT_80332d80, 0x13, 0x12);
    MenuPcs.DrawInit();

    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, s_Slash_80332d84, FLOAT_80332d7c, FLOAT_80332d80, 0x18, 0x12);
    MenuPcs.DrawInit();

    char* moneyText = ShopMenuMes(languageId, SHOP_MENU_TEXT_MONEY);
    float separatorWidth = font->GetWidth(s_Slash_80332d84);
    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, moneyText, FLOAT_80332d7c + separatorWidth, FLOAT_80332d80, 0x14, 0x12);
    MenuPcs.DrawInit();

    SetupShopMenuUnitFont(font);
    char* unitText = ShopMenuMes(languageId, SHOP_MENU_TEXT_GIL);
    float unitWidth = font->GetWidth(unitText);

    int itemNo = -1;
    bool canTrade = false;
    if (m_selectedIndex != -1) {
        const CCaravanWork* const caravanWork = ShopMenuCaravanWork(this);
        itemNo = getItemNo(m_selectedIndex);

        if (itemNo > 0) {
            if (listType == 0) {
                canTrade = true;
            } else if (listType == 2) {
                unsigned int bit = static_cast<unsigned int>(itemNo - 0x191);
                canTrade = (caravanWork->m_shopArgs[(itemNo - 0x191) >> 5] &
                            (1U << (bit & 0x1F))) != 0;
            } else if ((listType == 1) && MenuPcs.EquipChk(m_selectedIndex) == 0 && itemNo >= 0x9F) {
                canTrade = true;
            }
        }
    }

    int totalGil = 0;
    if (canTrade) {
        if (listType == 0) {
            int gil = 0;
            if (itemNo >= 1) {
                const CCaravanWork* const caravanWork = ShopMenuCaravanWork(this);
                gil = static_cast<int>(caravanWork->m_shopParam) *
                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                gil = gil / 100;
            }
            totalGil = m_quantity * gil;
        } else if (listType == 1) {
            int sellGil = 0;
            if (itemNo >= 1) {
                const CCaravanWork* const caravanWork = ShopMenuCaravanWork(this);
                sellGil = static_cast<int>(caravanWork->m_shopParam) *
                          *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                sellGil = sellGil / 100;
            }
            sellGil = static_cast<int>(FLOAT_80332d60 * static_cast<float>(sellGil));
            totalGil = m_quantity * sellGil;
        }
    }

    float rightPrice = FLOAT_80332d88 - unitWidth;
    float amountRightPrice = rightPrice - FLOAT_80332d5c;
    SetupShopMenuAmountFont(font);
    DrawShopMenuAmount(font, totalGil, amountRightPrice, FLOAT_80332d90, 0x13);

    float rightMoney = FLOAT_80332d94 - unitWidth;
    float amountRightMoney = rightMoney - FLOAT_80332d5c;
    int currentMoney = ShopMenuCaravanWork(this)->m_gil;
    SetupShopMenuAmountFont(font);
    DrawShopMenuAmount(font, currentMoney, amountRightMoney, FLOAT_80332d90, 0x14);

    SetupShopMenuUnitFont(font);
    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, unitText, rightPrice, FLOAT_80332d98, 0x19, 0x12);
    MenuPcs.DrawInit();

    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, s_Slash_80332d84, FLOAT_80332d7c, FLOAT_80332d98, 0x1B, 0x12);
    MenuPcs.DrawInit();

    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, unitText, rightMoney, FLOAT_80332d98, 0x19, 0x12);
    MenuPcs.DrawInit();
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

    for (int row = 0; row < m_visibleRows; ++row) {
        unsigned int listType = m_listType;
        int itemCount = ResolveShopMenuItemCount(this);

        if (itemCount <= itemIndex) {
            break;
        }

        int itemNo = getItemNo(itemIndex);

        bool canTrade = false;
        if (itemIndex != -1) {
            int tradeItemNo = getItemNo(itemIndex);

            if (tradeItemNo > 0) {
                if (listType == 0) {
                    canTrade = true;
                } else if (listType == 2) {
                    unsigned int bit = static_cast<unsigned int>(tradeItemNo - 0x191);
                    if ((ShopMenuCaravanWork(this)->m_shopArgs[(tradeItemNo - 0x191) >> 5] &
                         (1U << (bit & 0x1F))) != 0) {
                        canTrade = true;
                    }
                } else if (MenuPcs.EquipChk(itemIndex) == 0 && tradeItemNo >= 0x9F) {
                    canTrade = true;
                }
            }
        }

        int frame = 0xE;
        if (canTrade) {
            frame = selectableFrame;
        }

        int frameX;
        if (m_selectedIndex == itemIndex) {
            frameX = 0x198;
            drawShapeSeq(frame, 1, frameX, y - 4, 0xFF, 0, 0, FLOAT_80332d9c, 0);
            MenuPcs.DrawInit();
            if (m_subMode == 0) {
                MenuPcs.DrawCursor(0x114 + (System.m_frameCounter & 7), y - 0x14, FLOAT_80332d28);
            } else if ((System.m_frameCounter & 1) == 0) {
                MenuPcs.DrawCursor(0x114, y - 0x14, FLOAT_80332d28);
            }
        } else {
            frameX = 0x1B8;
            drawShapeSeq(frame, 0, frameX, y, 0xFF, 0, 0, FLOAT_80332d9c, 0);
        }

        if (itemNo > 0) {
            CFont* font = MenuPcs.m_fonts[4];
            font->SetMargin(FLOAT_80332d28);
            font->SetShadow(0);
            font->SetScale(FLOAT_80332d28);

            CColor white(0xFF, 0xFF, 0xFF, 0xFF);
            font->SetColor(white.color);
            font->DrawInit();
            font->SetPosX(static_cast<float>(frameX - 0x54));
            font->SetPosY(static_cast<float>(y - 0x14));
            font->Draw(reinterpret_cast<char*>(reinterpret_cast<int*>(Game.m_cFlatDataArr[1].TableStrings(0))[itemNo * 5 + 4]));
            MenuPcs.DrawInit();
            MenuPcs.DrawSingleIcon(itemNo, frameX + 0x54, y - 0x18, FLOAT_80332d28, 0, FLOAT_80332d28);
        }

        ++itemIndex;
        y += 0x1C;
    }

    int pulseFrame = System.m_frameCounter % 0x14;
    int pulse = pulseFrame - 10;
    if (pulse < 0) {
        pulse = -pulse;
    }
    int alpha = static_cast<int>(DOUBLE_80332DA0 * (DOUBLE_80332DB0 * static_cast<double>(pulse) + DOUBLE_80332DA8));
    float scale = static_cast<float>(DOUBLE_80332DA8 * (DOUBLE_80332DC0 * static_cast<double>(pulse) + DOUBLE_80332DB8));

    if (m_canScrollUp != 0) {
        drawShapeSeqScale(2, 0, 0x24E, 0x6A, scale, -scale, alpha);
    }
    if (m_canScrollDown != 0) {
        drawShapeSeqScale(2, 0, 0x24E, 0xEC, scale, scale, alpha);
    }
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
    pppInitDrawEnv(0);

    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)11, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)13, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl((GXChannelID)2, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);

    _GXColor fadeA;
    fadeA.r = 0xFF; fadeA.g = 0xFF; fadeA.b = 0xFF; fadeA.a = 0x00;
    _GXColor fadeB;
    fadeB.r = 0xFF; fadeB.g = 0xFF; fadeB.b = 0xFF; fadeB.a = 0xFF;
    _GXColor fadeC;
    fadeC.r = 0xFF; fadeC.g = 0xFF; fadeC.b = 0xFF; fadeC.a = 0x00;
    _GXColor fadeD;
    fadeD.r = 0xFF; fadeD.g = 0xFF; fadeD.b = 0xFF; fadeD.a = 0xFF;
    drawShapeSeqGrouad(9, 0, 0x1C, 0x10C, FLOAT_80332d78, FLOAT_80332dc8, fadeA, fadeB, fadeC, fadeD);

    _GXColor white;
    white.r = 0xFF; white.g = 0xFF; white.b = 0xFF; white.a = 0xFF;
    int x = 0x3C;
    while (x < 0x25C) {
        drawShapeSeqGrouad(9, 0, x, 0x10C, FLOAT_80332d78, FLOAT_80332dc8, white, white, white, white);
        x += 0x20;
    }
    drawShapeSeqGrouad(9, 0, x, 0x10C, FLOAT_80332d78, FLOAT_80332dc8, white, fadeA, white, fadeC);

    drawShapeSeqScale(3, 0, 0x106, 0xA4, FLOAT_80332d78, FLOAT_80332dcc, 0xFF);
    x = 0x106;
    while (x < 0x17A) {
        drawShapeSeqScale(4, 0, x, 0xA4, FLOAT_80332d78, FLOAT_80332dcc, 0xFF);
        x += 0x20;
    }
    drawShapeSeqScale(3, 0, x, 0xA4, FLOAT_80332dd0, FLOAT_80332dcc, 0xFF);
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::DrawObi(int)
{
    drawShapeSeq(5, 0, 0x32, 0x104, 0xFF, 0, 0, 0.0f, 0);
    int x = 0x52;
    while (x < 0x20E) {
        drawShapeSeq(6, 0, x, 0x104, 0xFF, 0, 0, 0.0f, 0);
        x += 0x20;
    }
    drawShapeSeq(5, 0, x, 0x104, 0xFF, 1, 0, 0.0f, 0);
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
    pppInitDrawEnv(0);

    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)11, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)13, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl((GXChannelID)2, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);

    _GXColor colorA;
    colorA.r = 0xFF; colorA.g = 0xFF; colorA.b = 0xFF; colorA.a = 0x00;
    _GXColor colorB;
    colorB.r = 0xFF; colorB.g = 0xFF; colorB.b = 0xFF; colorB.a = 0xFF;
    _GXColor colorC;
    colorC.r = 0xFF; colorC.g = 0xFF; colorC.b = 0xFF; colorC.a = 0x00;
    _GXColor colorD;
    colorD.r = 0xFF; colorD.g = 0xFF; colorD.b = 0xFF; colorD.a = 0xFF;
    drawShapeSeqGrouad(9, 0, 0x1C, 0xB8, FLOAT_80332d78, FLOAT_80332dc8, colorA, colorB, colorC, colorD);

    _GXColor white;
    white.r = 0xFF; white.g = 0xFF; white.b = 0xFF; white.a = 0xFF;
    int x = 0x3C;
    while (x < 0x25C) {
        drawShapeSeqGrouad(9, 0, x, 0xB8, FLOAT_80332d78, FLOAT_80332dc8, white, white, white, white);
        x += 0x20;
    }

    _GXColor endA;
    endA.r = 0xFF; endA.g = 0xFF; endA.b = 0xFF; endA.a = 0xFF;
    _GXColor endB;
    endB.r = 0xFF; endB.g = 0xFF; endB.b = 0xFF; endB.a = 0x00;
    _GXColor endC;
    endC.r = 0xFF; endC.g = 0xFF; endC.b = 0xFF; endC.a = 0xFF;
    _GXColor endD;
    endD.r = 0xFF; endD.g = 0xFF; endD.b = 0xFF; endD.a = 0x00;
    drawShapeSeqGrouad(9, 0, x, 0xB8, FLOAT_80332d78, FLOAT_80332dc8, endA, endB, endC, endD);

    drawShapeSeq(3, 0, 0xB4, 0x8C, 0xFF, 0, 0, FLOAT_80332d9c, 0);
    x = 0xB4;
    while (x < 0x1CC) {
        drawShapeSeq(4, 0, x, 0x8C, 0xFF, 0, 0, FLOAT_80332d9c, 0);
        x += 0x20;
    }
    drawShapeSeq(3, 0, x, 0x8C, 0xFF, 1, 0, FLOAT_80332d9c, 0);
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
    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    MenuPcs.DrawSingleBase(FLOAT_80332d28);
    Graphic.SetDrawDoneDebugData(2);
    pppInitDrawEnv(0);

    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)11, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)13, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl((GXChannelID)2, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);

    int mode = m_mode;
    int panelY;
    if (mode < 3) {
        panelY = 0xE6;
    } else if (mode < 9) {
        panelY = 0x154;
    } else if (mode < 0xC) {
        panelY = 0x118;
    } else {
        panelY = 0xEA;
    }

    Graphic.SetDrawDoneDebugData(3);
    _GXColor fadeA;
    fadeA.r = 0xFF; fadeA.g = 0xFF; fadeA.b = 0xFF; fadeA.a = 0x00;
    _GXColor fadeB;
    fadeB.r = 0xFF; fadeB.g = 0xFF; fadeB.b = 0xFF; fadeB.a = 0xFF;
    _GXColor fadeC;
    fadeC.r = 0xFF; fadeC.g = 0xFF; fadeC.b = 0xFF; fadeC.a = 0x00;
    _GXColor fadeD;
    fadeD.r = 0xFF; fadeD.g = 0xFF; fadeD.b = 0xFF; fadeD.a = 0xFF;
    drawShapeSeqGrouad(9, 0, 0x1C, panelY + 0x22, FLOAT_80332d78, FLOAT_80332dc8, fadeA, fadeB, fadeC, fadeD);

    _GXColor white;
    white.r = 0xFF; white.g = 0xFF; white.b = 0xFF; white.a = 0xFF;
    unsigned int x = 0x3C;
    while (x < 0x25C) {
        drawShapeSeqGrouad(9, 0, x, panelY + 0x22, FLOAT_80332d78, FLOAT_80332dc8, white, white, white, white);
        x += 0x20;
    }

    _GXColor endA;
    endA.r = 0xFF; endA.g = 0xFF; endA.b = 0xFF; endA.a = 0xFF;
    _GXColor endB;
    endB.r = 0xFF; endB.g = 0xFF; endB.b = 0xFF; endB.a = 0x00;
    _GXColor endC;
    endC.r = 0xFF; endC.g = 0xFF; endC.b = 0xFF; endC.a = 0xFF;
    _GXColor endD;
    endD.r = 0xFF; endD.g = 0xFF; endD.b = 0xFF; endD.a = 0x00;
    drawShapeSeqGrouad(9, 0, x, panelY + 0x22, FLOAT_80332d78, FLOAT_80332dc8, endA, endB, endC, endD);
    Graphic.SetDrawDoneDebugData(4);

    if ((mode >= 3) && (mode < 0xC)) {
        int listX = (mode < 9) ? 0x64 : 0x118;
        for (int barX = listX + 0x48; barX < 0x244; barX += 8) {
            Graphic.SetDrawDoneDebugData(5);
            drawShapeSeq(0x10, 0, barX, 0x11E, 0xFF, 0, 0, FLOAT_80332d9c, 0);
            Graphic.SetDrawDoneDebugData(6);
        }
        Graphic.SetDrawDoneDebugData(7);
        drawShapeSeq(0xD, 0, listX + 0x46, 0xA7, 0xFF, 0, 0, FLOAT_80332d9c, 0);
        Graphic.SetDrawDoneDebugData(8);
        Graphic.SetDrawDoneDebugData(9);
        drawShapeSeq(8, 0, 0x244, 0x11E, 0xFF, 0, 0, FLOAT_80332d9c, 0);
        Graphic.SetDrawDoneDebugData(10);
    }

    if ((mode >= 3) && (mode < 9)) {
        for (int sideX = 0x4E; sideX > 0x32; sideX -= 0x10) {
            Graphic.SetDrawDoneDebugData(0xB);
            drawShapeSeq(0xC, 0, sideX, 0x174, 0xFF, 0, 0, FLOAT_80332d9c, 0);
            Graphic.SetDrawDoneDebugData(0xC);
        }
        Graphic.SetDrawDoneDebugData(0xD);
        drawShapeSeq(0xB, 0, 0x7E, 0x150, 0xFF, 0, 0, FLOAT_80332d9c, 0);
        Graphic.SetDrawDoneDebugData(0xE);
        drawShapeSeq(8, 0, 0x2E, 0x170, 0xFF, 0, 0, FLOAT_80332d9c, 0);
        Graphic.SetDrawDoneDebugData(0xF);
        CFont* font = MenuPcs.m_fonts[4];
        font->SetMargin(FLOAT_80332d28);
        font->SetShadow(0);
        font->SetScaleX(FLOAT_80332d2c);
        font->SetScaleY(FLOAT_80332d28);
        font->SetColor(white);

        font->DrawInit();
        Graphic.SetDrawDoneDebugData(0x10);
        char* confirmText = (m_listType == 0) ? ShopMenuMes(languageId, SHOP_MENU_TEXT_BUY) :
                                                ShopMenuMes(languageId, SHOP_MENU_TEXT_SELL);
        font->SetPosX(CalcCenteredShopMenuX(font, confirmText));
        font->SetPosY(312.0f);
        font->Draw(confirmText);
        Graphic.SetDrawDoneDebugData(0x11);

        char* cancelText = ShopMenuMes(languageId, SHOP_MENU_TEXT_CANCEL);
        font->SetPosX(CalcCenteredShopMenuX(font, cancelText));
        font->SetPosY(346.0f);
        font->Draw(cancelText);
        Graphic.SetDrawDoneDebugData(0x12);
        MenuPcs.DrawInit();
        Graphic.SetDrawDoneDebugData(0x13);

        if (m_subMode == 2) {
            Graphic.SetDrawDoneDebugData(0x14);
            MenuPcs.DrawCursor(0x2C, m_yesNo * 0x18 + 0x134, FLOAT_80332d28);
            Graphic.SetDrawDoneDebugData(0x15);
        }
    }
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Draw()
{
    if (m_unk00 == 0) {
        m_unk00 = reinterpret_cast<void*>(1);
        return;
    }

    Graphic.SetDrawDoneDebugData(0x46);
    ppvEnv = reinterpret_cast<_pppEnvSt*>(PartMng.m_pdtSlots[m_pdtSlot].m_envFields);

    MenuPcs.DrawInit();

    int mode = m_mode;
    if ((mode >= 0) && (mode < 3)) {
        DrawShop0();
    } else if (mode < 6) {
        DrawShopBase();
        DrawItemList();
        DrawItemInfo0();
        DrawBuySellInfo();
    } else if (mode < 9) {
        DrawShopBase();
        DrawItemList();
        DrawItemInfo0();
        DrawBuySellInfo();
    } else if (mode < 0xC) {
        DrawSmith0();
    } else if (mode < 0xF) {
        DrawMake();
    } else if (mode < 0x12) {
        DrawSoubi();
    }

    float fade = m_fade;
    if (fade != FLOAT_80332d28) {
        int fadeStep = static_cast<int>(FLOAT_80332de0 * fade);
        signed char alpha = static_cast<unsigned char>(0xFF - (fadeStep & 0xFF));

        Graphic.SetDrawDoneDebugData(0x32);

        Mtx screenMtx;
        Mtx44 projectionMtx;
        PSMTXIdentity(screenMtx);
        screenMtx[0][0] = FLOAT_80332d78;
        screenMtx[1][1] = FLOAT_80332dd0;
        screenMtx[2][2] = FLOAT_80332d78;
        screenMtx[0][3] = 0.0f;
        screenMtx[1][3] = 480.0f;
        GXLoadPosMtxImm(screenMtx, 0);
        GXSetCurrentMtx(0);

        C_MTXOrtho(projectionMtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, FLOAT_80332d28);
        projectionMtx[2][3] += 0.0f;
        GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);

        _GXColor fadeColor = {0, 0, 0, alpha};
        GXSetChanAmbColor(GX_COLOR0A0, fadeColor);
        GXSetChanMatColor(GX_COLOR0A0, fadeColor);
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
        GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

        Vec topLeft = {0.0f, 0.0f, 0.0f};
        Vec bottomRight = {640.0f, 480.0f, 0.0f};
        Graphic.RenderNoTexQuadGrouad(topLeft, bottomRight, fadeColor, fadeColor, fadeColor, fadeColor);

        Graphic.SetDrawDoneDebugData(0x33);
    }
    Graphic.SetDrawDoneDebugData(0x3C);
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawSoubi()
{
    DrawSoubiBase();

    int resultItem = m_resultItem;
    drawShapeSeq(0xF, 0, 0xA8, 0x5A, 0xFF, 0, 0, FLOAT_80332d9c, 0);
    MenuPcs.DrawInit();
    MenuPcs.DrawSingleIcon(m_resultItem, 0x40, 0x42, FLOAT_80332d28, 0, FLOAT_80332d28);

    CFont* font = MenuPcs.m_fonts[0];
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);

    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
    font->DrawInit();

    char* itemName = 0;
    if (resultItem >= 1) {
        itemName = reinterpret_cast<char*>(reinterpret_cast<int*>(Game.m_cFlatDataArr[1].TableStrings(0))[resultItem * 5 + 4]);
    }
    MenuPcs.DrawShadowFont(font, itemName, FLOAT_80332d54, 112.0f, 0x18, 0x12);
    MenuPcs.DrawInit();

    DrawItemInfo(m_resultItem, 0x98, 0x7E, 0x98, 0x9C, 0x98, 0xBA, 0x138);
    MenuPcs.DrawInit();

    int barX = 0x1F6;
    while (barX > 0x42) {
        drawShapeSeq(0xC, 0, barX, 0x17C, 0xFF, 0, 0, FLOAT_80332d9c, 0);
        barX -= 0x10;
    }
    drawShapeSeq(0xB, 0, 0x226, 0x158, 0xFF, 0, 0, FLOAT_80332d9c, 0);
    drawShapeSeq(1, 1, barX, 0x17C, 0xFF, 0, 0, FLOAT_80332d9c, 0);

    CFont* labelFont = MenuPcs.m_fonts[4];
    labelFont->SetMargin(FLOAT_80332d28);
    labelFont->SetShadow(0);
    {
        CColor labelWhite(0xFF, 0xFF, 0xFF, 0xFF);
        labelFont->SetColor(labelWhite.color);
    }
    labelFont->SetScaleX(FLOAT_80332d2c);
    labelFont->SetScaleY(FLOAT_80332d28);
    labelFont->DrawInit();

    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    labelFont->SetPosY(312.0f);
    char* equipText = ShopMenuMes(languageId, SHOP_MENU_TEXT_EQUIP);
    float equipTextX = CalcCenteredShopMenuX(labelFont, equipText);
    labelFont->SetPosX(equipTextX);
    labelFont->SetPosY(312.0f);
    labelFont->Draw(equipText);

    char* cancelText = ShopMenuMes(languageId, SHOP_MENU_TEXT_CANCEL);
    float cancelTextX = CalcCenteredShopMenuX(labelFont, cancelText);
    labelFont->SetPosX(cancelTextX);
    labelFont->SetPosY(346.0f);
    labelFont->Draw(cancelText);
    MenuPcs.DrawInit();

    MenuPcs.DrawCursor(static_cast<unsigned int>(cancelTextX) - 0x24, m_yesNo * 0x18 + 0x13C, 1.0f);
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawMake()
{
    DrawMakeBase();

    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;

    drawShapeSeq(0xF, 0, 0xA8, 0x4A, 0xFF, 0, 0, FLOAT_80332d9c, 0);
    MenuPcs.DrawInit();
    MenuPcs.DrawSingleIcon(m_resultItem, 0x40, 0x32, FLOAT_80332d28, 0, FLOAT_80332d28);

    CFont* font = MenuPcs.m_fonts[0];
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);

    const char* itemName = GetItemName(m_resultItem);
    font->DrawInit();
    MenuPcs.DrawShadowFont(font, const_cast<char*>(itemName), FLOAT_80332d54, FLOAT_80332e0c, 0x18, 0x12);
    MenuPcs.DrawInit();

    char raceBuffer[64];
    MenuPcs.GetRaceStr(m_resultItem, raceBuffer);
    const int raceColor = (MenuPcs.ChkEquipPossible(m_resultItem) != 0) ? 0x18 : 2;
    const char* raceText = ShopMenuMes(languageId, SHOP_MENU_TEXT_RACE);

    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, const_cast<char*>(raceText), 180, FLOAT_80332d58, 0x18, 0x12);
    MenuPcs.DrawInit();

    float raceX = 180 + FLOAT_80332d5c + font->GetWidth(raceText);
    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, raceBuffer, raceX, FLOAT_80332d58, raceColor, 0x12);
    MenuPcs.DrawInit();

    const char* gilUnitText = ShopMenuMes(languageId, SHOP_MENU_TEXT_GIL);
    SetupShopMenuUnitFont(font);
    float gilUnitWidth = font->GetWidth(gilUnitText);

    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, s_Slash_80332d84, FLOAT_80332e14, FLOAT_80332e20, 0x1B, 0x12);
    MenuPcs.DrawInit();

    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font,
        const_cast<char*>(gilUnitText),
        FLOAT_80332e14 - gilUnitWidth - FLOAT_80332d5c - FLOAT_80332d5c,
        FLOAT_80332e20,
        0x19,
        0x12);
    MenuPcs.DrawInit();

    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, const_cast<char*>(gilUnitText), FLOAT_80332e1c - gilUnitWidth, FLOAT_80332e20, 0x19, 0x12);
    MenuPcs.DrawInit();

    SetupShopMenuAmountFont(font);
    int makeGil = getItemNo(m_selectedIndex) > 0 ? CalcShopMenuMakeGil(this, getItemNo(m_selectedIndex)) : 0;
    DrawShopMenuAmount(font, makeGil, FLOAT_80332e14 - gilUnitWidth - FLOAT_80332d5c - FLOAT_80332d5c, FLOAT_80332e18, 0x13);
    SetupShopMenuAmountFont(font);
    int makeGil2 = getItemNo(m_selectedIndex) > 0 ? CalcShopMenuMakeGil(this, getItemNo(m_selectedIndex)) : 0;
    DrawShopMenuAmount(font, ShopMenuCaravanWork(this)->m_gil,
        FLOAT_80332e1c - gilUnitWidth - FLOAT_80332d5c, FLOAT_80332e18,
        (makeGil2 <= ShopMenuCaravanWork(this)->m_gil) ? 0x14 : 2);

    CFont* labelFont = MenuPcs.m_fonts[4];
    SetupShopMenuLabelFont(labelFont);
    DrawShopMenuCenteredText(labelFont, ShopMenuMes(languageId, SHOP_MENU_TEXT_PRICE), FLOAT_80332e28, FLOAT_80332e24);
    DrawShopMenuCenteredText(labelFont, ShopMenuMes(languageId, SHOP_MENU_TEXT_MONEY), FLOAT_80332d68, FLOAT_80332e2c);
    MenuPcs.DrawInit();

    DrawObi(0);

    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d28);
    {
        CColor materialsColor(0xFF, 0xFF, 0xFF, 0xFF);
        font->SetColor(materialsColor.color);
    }
    font->DrawInit();
    const char* materialsText = ShopMenuMes(languageId, SHOP_MENU_TEXT_MATERIALS);
    float materialsX = FLOAT_80332e30 - font->GetWidth(materialsText) * FLOAT_80332d78;
    MenuPcs.DrawNoShadowFont(font, const_cast<char*>(materialsText), materialsX, FLOAT_80332e34, 4, 0x12);
    MenuPcs.DrawInit();
    const char* stockText = ShopMenuMes(languageId, SHOP_MENU_TEXT_STOCK);
    float stockX = FLOAT_80332e38 - font->GetWidth(stockText) * FLOAT_80332d78;
    MenuPcs.DrawNoShadowFont(font, const_cast<char*>(stockText), stockX, FLOAT_80332e34, 9, 0x12);
    MenuPcs.DrawInit();

    unsigned short recipeMaterial[8];
    MenuPcs.GetRecipeMaterial(getItemNo(m_selectedIndex), reinterpret_cast<CMenuPcs::MaterialInfo*>(recipeMaterial));
    int rowY = 300;
    for (int i = 0; i < 3; i++, rowY += 0x1E) {
        int materialItem = recipeMaterial[i];
        if (materialItem < 1) {
            break;
        }

        int neededCount = recipeMaterial[i + 3];
        const char* materialName = GetItemName(materialItem);
        char neededBuffer[64];
        char ownedBuffer[64];
        sprintf(neededBuffer, s_DecimalFormat_80332d14, neededCount);

        font->DrawInit();
        font->SetMargin(FLOAT_80332d28);
        font->SetShadow(1);
        font->SetScale(FLOAT_80332d28);

        font->DrawInit();
        MenuPcs.DrawNoShadowFont(font, s_Slash_80332d84, FLOAT_80332e3c, rowY, 0x1B, 0x12);
        MenuPcs.DrawInit();

        SetupShopMenuMakeAmountFont(font);
        int rightEdge = static_cast<int>(372.0f - font->GetWidth(neededBuffer));
        MenuPcs.DrawNoShadowFont(font, neededBuffer, rightEdge, rowY, 0x1B, 0x12);
        MenuPcs.DrawInit();

        font->DrawInit();
        font->SetMargin(FLOAT_80332d28);
        font->SetShadow(1);
        font->SetScale(FLOAT_80332d28);
        rightEdge = static_cast<int>(static_cast<float>(rightEdge - 8) - font->GetWidth("/"));
        font->DrawInit();
        MenuPcs.DrawNoShadowFont(font, const_cast<char*>("/"), rightEdge, rowY, 0x1B, 0x12);
        MenuPcs.DrawInit();

        rightEdge = static_cast<int>(static_cast<float>(rightEdge - 8) - font->GetWidth(materialName));
        font->DrawInit();
        MenuPcs.DrawNoShadowFont(font, const_cast<char*>(materialName), rightEdge, rowY, 0x1B, 0x12);
        MenuPcs.DrawInit();

        int ownedCount = 0;
        for (int slot = 0; slot < 0x40; slot++) {
            if (ShopMenuCaravanWork(this)->m_inventoryItems[slot] == materialItem) {
                ++ownedCount;
            }
        }
        sprintf(ownedBuffer, s_TwoDigitFormat_80332d18, ownedCount);

        SetupShopMenuMakeOwnedFont(font);
        float ownedX = 356.0f - font->GetWidth(ownedBuffer);
        MenuPcs.DrawNoShadowFont(font, ownedBuffer, ownedX, rowY, (ownedCount >= neededCount) ? 0x1B : 2, 0x12);
        MenuPcs.DrawInit();
    }
    MenuPcs.DrawInit();

    for (int barX = 0x1F6; barX > 0x32; barX -= 0x10) {
        drawShapeSeq(0xC, 0, barX, 0x18C, 0xFF, 0, 0, 0.0f, 0);
    }
    drawShapeSeq(0xB, 0, 0x226, 0x168, 0xFF, 0, 0, 0.0f, 0);
    drawShapeSeq(1, 1, 0x36, 0x18C, 0xFF, 0, 0, 0.0f, 0);

    SetupShopMenuLabelFont(labelFont);
    DrawShopMenuCenteredText(labelFont, ShopMenuMes(languageId, SHOP_MENU_TEXT_CRAFT), 148.0f, 332.0f);
    DrawShopMenuCenteredText(labelFont, ShopMenuMes(languageId, SHOP_MENU_TEXT_CANCEL), 148.0f, FLOAT_80332e44);
    MenuPcs.DrawInit();

    DrawItemInfo(m_resultItem, 0x98, 0x7E, 0, 0x9C, 0, 0, 0);
    DrawItemHelp(m_selectedIndex, 0x140, 0x172);
    MenuPcs.DrawCursor(0xD8, m_yesNo * 0x18 + 0x14C, 1.0f);
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
void CShopMenu::DrawSmith0()
{
    DrawShopBase();
    drawShapeSeqScale(0x11, 0, 0, 0x154, FLOAT_80332e48, FLOAT_80332d28, 0xFF);
    DrawItemList();
    DrawItemHelp(m_selectedIndex, 0x140, 0x172);

    CFont* font = MenuPcs.m_fonts[0];
    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d8c);

    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
    font->DrawInit();

    const char* title;
    if (m_caravanWork->m_shopRequestFlags != '\0') {
        title = MenuPcs.GetJobStr(1);
    } else {
        title = ShopMenuMes(static_cast<int>(Game.m_gameWork.m_languageId) - 1, SHOP_MENU_TEXT_BLACKSMITH);
    }

    float width = font->GetWidth(title);

    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, const_cast<char*>(title), 264.0f - width, FLOAT_80332e4c, 9, 0x12);
    MenuPcs.DrawInit();
    MenuPcs.DrawInit();
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
void CShopMenu::DrawShop0()
{
    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    DrawShopBase();

    if (s_shopMenuTopMenuTextInitialized == 0) {
        s_shopMenuTopMenuEntries[0].text = ShopMenuMes(languageId, SHOP_MENU_TEXT_BUY);
        s_shopMenuTopMenuEntries[1].text = ShopMenuMes(languageId, SHOP_MENU_TEXT_SELL);
        s_shopMenuTopMenuEntries[2].text = ShopMenuMes(languageId, SHOP_MENU_TEXT_CANCEL);
        s_shopMenuTopMenuTextInitialized = 1;
    }

    CFont* font;
    ShopMenuTopMenuEntry* entry = s_shopMenuTopMenuEntries;
    for (int i = 0; i < 3; i++, entry++) {
        int highlight = (i == m_topChoice) ? 1 : 0;
        s_currentShopMenuTopMenuEntry = entry;

        Graphic.SetDrawDoneDebugData(0x1E);
        int x = s_currentShopMenuTopMenuEntry->x;
        if (highlight != 0) {
            x += 8;
        }
        drawShapeSeq(0, highlight, x, s_currentShopMenuTopMenuEntry->y, 0xFF, 0, 0, FLOAT_80332d9c, 0);
        Graphic.SetDrawDoneDebugData(0x1F);
        drawShapeSeq(
            8, highlight, s_currentShopMenuTopMenuEntry->x - 0x30, s_currentShopMenuTopMenuEntry->y, 0xFF, 0, 0,
            FLOAT_80332d9c, 0);
        Graphic.SetDrawDoneDebugData(0x20);
        font = MenuPcs.m_fonts[0];
    }

    font->SetMargin(FLOAT_80332d28);
    font->SetShadow(1);
    font->SetScale(FLOAT_80332d8c);
    CColor white(0xFF, 0xFF, 0xFF, 0xFF);
    font->SetColor(white.color);
    font->DrawInit();

    Graphic.SetDrawDoneDebugData(0x21);
    font->DrawInit();
    MenuPcs.DrawNoShadowFont(font, ShopMenuMes(languageId, SHOP_MENU_TEXT_TITLE), FLOAT_80332d54, FLOAT_80332e30, 9, 0x12);
    MenuPcs.DrawInit();

    Graphic.SetDrawDoneDebugData(0x22);
    font->SetMargin(FLOAT_80332d28);
    font->SetScale(FLOAT_80332d28);

    entry = s_shopMenuTopMenuEntries;
    for (unsigned int i = 0; i < 3; i++, entry++) {
        s_currentShopMenuTopMenuEntry = entry;
        Graphic.SetDrawDoneDebugData(0x23);
        font->DrawInit();
        MenuPcs.DrawNoShadowFont(font, s_currentShopMenuTopMenuEntry->text,
            static_cast<float>(s_currentShopMenuTopMenuEntry->x - 0x10),
            static_cast<float>(s_currentShopMenuTopMenuEntry->y - 0x0B), 0x18, 0x12);
        MenuPcs.DrawInit();
        Graphic.SetDrawDoneDebugData(0x24);
    }

    MenuPcs.DrawInit();
    Graphic.SetDrawDoneDebugData(0x28);
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
    bool canSelect = MenuPcs.ChkEquipPossible(m_resultItem) &&
                     (CalcShopMenuMakeGil(this, getItemNo(m_selectedIndex)) <= m_caravanWork->m_gil);

    int selected = getItemNo(m_selectedIndex);
    short recipeMaterial[8];
    MenuPcs.GetRecipeMaterial(selected, reinterpret_cast<CMenuPcs::MaterialInfo*>(recipeMaterial));

    short* material = recipeMaterial;
    for (int i = 0; i < 3; i++, material++) {
        short itemNo = *material;
        if (itemNo < 1) {
            break;
        }

        if (canSelect) {
            short* inventory = m_caravanWork->m_inventoryItems;
            int total = 0;
            for (int j = 0; j < 8; j++, inventory += 8) {
                if (inventory[0] == itemNo) {
                    ++total;
                }
                if (inventory[1] == itemNo) {
                    ++total;
                }
                if (inventory[2] == itemNo) {
                    ++total;
                }
                if (inventory[3] == itemNo) {
                    ++total;
                }
                if (inventory[4] == itemNo) {
                    ++total;
                }
                if (inventory[5] == itemNo) {
                    ++total;
                }
                if (inventory[6] == itemNo) {
                    ++total;
                }
                if (inventory[7] == itemNo) {
                    ++total;
                }
            }
            canSelect = material[3] <= total;
        }
    }

    if (!canSelect) {
        m_yesNo = 1;
    }

    if ((GetPadButtons() & 0xC) != 0) {
        m_yesNo ^= 1;
        if (canSelect == 1) {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else {
            m_yesNo = 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        }
    } else if ((GetPadButtons() & 0x100) != 0) {
        int yesNo = m_yesNo;
        if (yesNo != 1) {
            if (yesNo > 0) {
                return;
            }
            if (yesNo < 0) {
                return;
            }

            int itemId = getItemNo(m_selectedIndex);
            int makeGil;
            if (itemId < 1) {
                makeGil = 0;
            } else {
                int gil = m_caravanWork->m_shopParam *
                          *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x24);
                makeGil = gil / 100;
            }
            if (m_caravanWork->CanAddGil(-makeGil) != 0) {
                Sound.PlaySe(0x52, 0x40, 0x7F, 0);
                m_nextMode = 0xF;
                SetMode(0xE);
                return;
            }
        }

        Sound.PlaySe(4, 0x40, 0x7F, 0);
        m_nextMode = 9;
        SetMode(0xE);
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
    if ((GetPadButtons() & 0xC) != 0) {
        m_yesNo ^= 1;
        Sound.PlaySe(1, 0x40, 0x7F, 0);
        return;
    }

    if ((GetPadButtons() & 0x100) == 0) {
        return;
    }

    unsigned int yesNo = m_yesNo;
    if (yesNo == 1) {
        if (m_listType == 0) {
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            m_subMode = 1;
        } else {
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            m_subMode = 0;
        }
        return;
    }

    if ((yesNo >= 1) || (yesNo < 0)) {
        return;
    }

    m_subMode = 0;
    int itemId = getItemNo(m_selectedIndex);
    if (m_listType == 0) {
        Sound.PlaySe(0x50, 0x40, 0x7F, 0);
        int costBase = itemId * 0x48;
        int quantity = 0;
        CCaravanWork* caravanWork;
        while ((quantity < m_quantity) &&
               (caravanWork = m_caravanWork,
                static_cast<short>(caravanWork->m_inventoryItemCount + 1) < 0x41)) {
            int gilValue;
            if (m_listType == 0) {
                if (itemId < 1) {
                    gilValue = 0;
                } else {
                    int gil = caravanWork->m_shopParam *
                              *reinterpret_cast<unsigned short*>(costBase + Game.unkCFlatData0[2] + 0x20);
                    gilValue = gil / 100;
                }
            } else if (m_listType == 1) {
                if (itemId < 1) {
                    gilValue = 0;
                } else {
                    int gil = caravanWork->m_shopParam *
                              *reinterpret_cast<unsigned short*>(costBase + Game.unkCFlatData0[2] + 0x20);
                    gilValue = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil / 100));
                }
            } else {
                gilValue = -1;
            }

            if (caravanWork->CanAddGil(-gilValue) == 0) {
                return;
            }

            m_caravanWork->AddItem(static_cast<short>(itemId), 0);
            int gilValue2;
            if (m_listType == 0) {
                if (itemId < 1) {
                    gilValue2 = 0;
                } else {
                    int gil = m_caravanWork->m_shopParam *
                              *reinterpret_cast<unsigned short*>(costBase + Game.unkCFlatData0[2] + 0x20);
                    gilValue2 = gil / 100;
                }
            } else if (m_listType == 1) {
                if (itemId < 1) {
                    gilValue2 = 0;
                } else {
                    int gil = m_caravanWork->m_shopParam *
                              *reinterpret_cast<unsigned short*>(costBase + Game.unkCFlatData0[2] + 0x20);
                    gilValue2 = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil / 100));
                }
            } else {
                gilValue2 = -1;
            }
            m_caravanWork->AddGil(-gilValue2);
            ++quantity;
        }
        return;
    }

    int itemIndex = m_selectedIndex;
    bool canTrade = false;
    if (itemIndex != -1) {
        int tradeItem = getItemNo(itemIndex);
        if (tradeItem < 1) {
            canTrade = false;
        } else if (m_listType == 0) {
            canTrade = true;
        } else if (m_listType == 2) {
            canTrade = true;
            if ((m_caravanWork->m_shopArgs[((int)(tradeItem - 0x191U) >> 5)] &
                 (1 << ((tradeItem - 0x191U) & 0x1F))) == 0) {
                canTrade = false;
            }
        } else {
            if (MenuPcs.EquipChk(itemIndex) == 0) {
                canTrade = tradeItem >= 0x9F;
            } else {
                canTrade = false;
            }
        }
    }

    if (canTrade) {
        Sound.PlaySe(0x50, 0x40, 0x7F, 0);
        int sellId = getItemNo(m_selectedIndex);
        int gilValue;
        if (m_listType == 0) {
            if (sellId < 1) {
                gilValue = 0;
            } else {
                int gil = m_caravanWork->m_shopParam *
                          *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + sellId * 0x48 + 0x20);
                gil = gil / 100 + (gil >> 0x1F);
                gilValue = gil - (gil >> 0x1F);
            }
        } else if (m_listType == 1) {
            if (sellId < 1) {
                gilValue = 0;
            } else {
                int gil = m_caravanWork->m_shopParam *
                          *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + sellId * 0x48 + 0x20);
                gil = gil / 100 + (gil >> 0x1F);
                gilValue = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil - (gil >> 0x1F)));
            }
        } else {
            gilValue = -1;
        }

        if (m_caravanWork->CanAddGil(gilValue) != 0) {
            m_caravanWork->DeleteItemIdx(m_selectedIndex, 0);
            int gilValue2;
            if (m_listType == 0) {
                if (sellId < 1) {
                    gilValue2 = 0;
                } else {
                    int gil = m_caravanWork->m_shopParam *
                              *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + sellId * 0x48 + 0x20);
                    gil = gil / 100 + (gil >> 0x1F);
                    gilValue2 = gil - (gil >> 0x1F);
                }
            } else if (m_listType == 1) {
                if (sellId < 1) {
                    gilValue2 = 0;
                } else {
                    int gil = m_caravanWork->m_shopParam *
                              *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + sellId * 0x48 + 0x20);
                    gil = gil / 100 + (gil >> 0x1F);
                    gilValue2 = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil - (gil >> 0x1F)));
                }
            } else {
                gilValue2 = -1;
            }
            m_caravanWork->AddGil(gilValue2);
        }
    } else {
        Sound.PlaySe(4, 0x40, 0x7F, 0);
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
    if ((GetPadButtons() & 1) != 0) {
        ++m_figureMode;
        if (m_figureMode >= 2) {
            m_figureMode = 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    } else if ((GetPadButtons() & 2) != 0) {
        --m_figureMode;
        if (m_figureMode < 0) {
            m_figureMode = 0;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    } else if ((GetPadButtons() & 0x100) != 0) {
        Sound.PlaySe(2, 0x40, 0x7F, 0);
        m_subMode = 2;
    }

    if ((GetShopMenuListButtons() & 8) != 0) {
        int figureMode = m_figureMode;
        if (figureMode == 1) {
            m_quantity += 10;
            CCaravanWork* caravanWork = m_caravanWork;
            if (m_quantity <= (0x40 - static_cast<short>(caravanWork->m_inventoryItemCount))) {
                int totalGil = 0;
                if (m_selectedIndex != -1) {
                    unsigned int itemId = getItemNo(m_selectedIndex);
                    int unitGil;
                    if (m_listType == 0) {
                        if (itemId < 1) {
                            unitGil = 0;
                        } else {
                            int gil = caravanWork->m_shopParam *
                                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
                            gil = gil / 100 + (gil >> 0x1F);
                            unitGil = gil - (gil >> 0x1F);
                        }
                    } else if (m_listType == 1) {
                        if (itemId < 1) {
                            unitGil = 0;
                        } else {
                            int gil = caravanWork->m_shopParam *
                                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
                            gil = gil / 100 + (gil >> 0x1F);
                            unitGil = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil - (gil >> 0x1F)));
                        }
                    } else {
                        unitGil = -1;
                    }
                    totalGil = m_quantity * unitGil;
                }
                if (caravanWork->CanAddGil(-totalGil) != 0) {
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                    return;
                }
            }

            m_quantity -= 10;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else if (figureMode == 0) {
            ++m_quantity;
            CCaravanWork* caravanWork = m_caravanWork;
            if (m_quantity <= (0x40 - static_cast<unsigned short>(caravanWork->m_inventoryItemCount))) {
                int totalGil = 0;
                if (m_selectedIndex != -1) {
                    int itemId = getItemNo(m_selectedIndex);
                    int unitGil;
                    if (m_listType == 0) {
                        if (itemId < 1) {
                            unitGil = 0;
                        } else {
                            int gil = caravanWork->m_shopParam *
                                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
                            gil = gil / 100 + (gil >> 0x1F);
                            unitGil = gil - (gil >> 0x1F);
                        }
                    } else if (m_listType == 1) {
                        if (itemId < 1) {
                            unitGil = 0;
                        } else {
                            int gil = caravanWork->m_shopParam *
                                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
                            gil = gil / 100 + (gil >> 0x1F);
                            unitGil = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil - (gil >> 0x1F)));
                        }
                    } else {
                        unitGil = -1;
                    }
                    totalGil = m_quantity * unitGil;
                }
                if (caravanWork->CanAddGil(-totalGil) != 0) {
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                    return;
                }
            }

            gShopMenuInputLatch = 8;
            --m_quantity;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        }
        return;
    }

    if ((GetShopMenuListButtons() & 4) == 0) {
        return;
    }

    int figureMode = m_figureMode;
    if (figureMode == 1) {
        m_quantity -= 10;
        if (m_quantity < 1) {
            m_quantity += 10;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    } else if (figureMode == 0) {
        --m_quantity;
        if (m_quantity < 1) {
            gShopMenuInputLatch = 4;
            m_quantity = 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    }
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

    if ((GetShopMenuListButtons() & 8) != 0) {
        --m_selectedIndex;
        if (m_selectedIndex < 0) {
            gShopMenuInputLatch = 8;
            m_selectedIndex = 0;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    } else if ((GetShopMenuListButtons() & 4) != 0) {
        ++m_selectedIndex;
        if (m_selectedIndex < getItemCnt()) {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else {
            gShopMenuInputLatch = 4;
            m_selectedIndex = getItemCnt() - 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        }
    } else if ((GetPadButtons() & 0x100) != 0) {
        bool canSelect = false;
        m_figureMode = 0;
        m_yesNo = 0;

        int listType = m_listType;
        if (listType == 0) {
            if (m_selectedIndex != -1) {
                canSelect = getItemNo(m_selectedIndex) >= 1;
            }
            if (canSelect) {
                CCaravanWork* caravanWork = m_caravanWork;
                if (m_quantity <= (0x40 - static_cast<unsigned short>(caravanWork->m_inventoryItemCount))) {
                    int itemId = getItemNo(m_selectedIndex);
                    int unitGil;
                    if (m_listType == 0) {
                        if (itemId < 1) {
                            unitGil = 0;
                        } else {
                            int gil = caravanWork->m_shopParam *
                                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
                            unitGil = gil / 100;
                        }
                    } else if (m_listType == 1) {
                        if (itemId < 1) {
                            unitGil = 0;
                        } else {
                            int gil = caravanWork->m_shopParam *
                                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
                            unitGil = static_cast<int>(FLOAT_80332d60 * static_cast<float>(gil / 100));
                        }
                    } else {
                        unitGil = -1;
                    }
                    int totalGil = m_quantity * unitGil;
                    if (caravanWork->CanAddGil(-totalGil) != 0) {
                        m_subMode = 1;
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                        goto updateWindow;
                    }
                }
            }
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else if (listType == 1) {
            int idx = m_selectedIndex;
            if (idx != -1) {
                int itemNo = getItemNo(m_selectedIndex);
                if (itemNo < 1) {
                    canSelect = false;
                } else if (MenuPcs.EquipChk(idx) == 0) {
                    canSelect = itemNo >= 0x9F;
                } else {
                    canSelect = false;
                }
            }
            if (canSelect) {
                m_subMode = 2;
                Sound.PlaySe(2, 0x40, 0x7F, 0);
            } else {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            }
        } else if (listType == 2) {
            if (m_selectedIndex != -1) {
                int itemNo = getItemNo(m_selectedIndex);
                if (itemNo < 1) {
                    canSelect = false;
                } else {
                    canSelect = true;
                    if ((m_caravanWork->m_shopArgs[((int)(itemNo - 0x191U) >> 5)] &
                         (1 << ((itemNo - 0x191U) & 0x1F))) == 0) {
                        canSelect = false;
                    }
                }
            }
            if (canSelect) {
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
    if (m_selectedIndex < m_listTop) {
        m_listTop = m_selectedIndex;
    }
    if ((m_listTop + m_visibleRows) <= m_selectedIndex) {
        m_listTop = (m_selectedIndex - m_visibleRows) + 1;
    }
    m_canScrollUp = (m_listTop < 1) ? 0 : 1;
    m_canScrollDown = ((m_listTop + m_visibleRows) < getItemCnt()) ? 1 : 0;
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CShopMenu::SelectSOUBI()
{
    if ((GetPadButtons() & 0xC) != 0) {
        m_yesNo ^= 1;
        Sound.PlaySe(1, 0x40, 0x7F, 0);
        return;
    }

    if ((GetPadButtons() & 0x200) != 0) {
        Sound.PlaySe(3, 0x40, 0x7F, 0);
        m_nextMode = 9;
        SetMode(0x11);
        return;
    }

    if ((GetPadButtons() & 0x100) == 0) {
        return;
    }

    if (m_yesNo != 0) {
        m_nextMode = 9;
        SetMode(0x11);
        Sound.PlaySe(4, 0x40, 0x7F, 0);
        return;
    }

    m_nextMode = 9;
    SetMode(0x11);

    int equipType = MenuPcs.GetEquipType(m_resultItem);
    ShopMenuCaravanWork(this)->ChgEquipPos(equipType, static_cast<short>(m_resultParam));
    Sound.PlaySe(0x51, 0x40, 0x7F, 0);
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
    int& shopMode = m_listType;
    unsigned char& choice = m_topChoice;

    switch (mode) {
    case 0:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(1);
        }
        break;
    case 1:
        if ((GetPadButtons() & 4) != 0) {
            ++choice;
            if (choice > 2) {
                choice = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((GetPadButtons() & 8) != 0) {
            --choice;
            if (choice > 2) {
                choice = 2;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((GetPadButtons() & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            this->SetMode(2);
        }

        if ((GetPadButtons() & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(2);
            choice = 2;
        }
        break;
    case 2:
        m_fade = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            if (choice == 0) {
                this->SetMode(3);
            } else if (choice == 1) {
                this->SetMode(6);
            } else if (choice == 2) {
                PartPcs.ReleasePdt(m_pdtSlot);
                reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->CallShop(0, 0, 0, 0, 0);
                MenuPcs.m_singleFadeState->done = 1;
                operator delete(MenuPcs.m_shopMenu);
                MenuPcs.m_shopMenu = 0;
                return;
            }
        }
        break;
    case 3:
        if (timer == 0) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(4);
        }
        break;
    case 4:
        if (subMode == 1) {
            this->SelectFigure();
            if ((GetPadButtons() & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                subMode = 0;
            }
        } else if (subMode < 1) {
            if (subMode >= 0) {
                this->SelectItemIdx();
                if ((GetPadButtons() & 0x200) != 0) {
                    Sound.PlaySe(3, 0x40, 0x7F, 0);
                    this->SetMode(5);
                }
            }
        } else if (subMode < 3) {
            this->SelectYesNo();
            if ((GetPadButtons() & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                subMode = 1;
            }
        }
        break;
    case 5:
    case 8:
        m_fade = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(0);
        }
        break;
    case 6:
        if (timer == 0) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(7);
        }
        break;
    case 7:
        if (subMode != 1) {
            if (subMode < 1) {
                if (subMode >= 0) {
                    this->SelectItemIdx();
                    if ((GetPadButtons() & 0x200) != 0) {
                        Sound.PlaySe(3, 0x40, 0x7F, 0);
                        this->SetMode(8);
                    }
                }
            } else if (subMode < 3) {
                this->SelectYesNo();
                if ((GetPadButtons() & 0x200) != 0) {
                    Sound.PlaySe(3, 0x40, 0x7F, 0);
                    subMode = 0;
                }
            }
        }
        break;
    case 9:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(10);
        }
        break;
    case 10:
        this->SelectItemIdx();
        if ((GetPadButtons() & 0x200) != 0) {
            m_nextMode = -1;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(0xB);
        }
        break;
    case 11:
        m_fade = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            if (m_nextMode == -1) {
                PartPcs.ReleasePdt(m_pdtSlot);
                reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->CallShop(0, 0, 0, 0, 0);
                MenuPcs.m_singleFadeState->done = 1;
                operator delete(MenuPcs.m_shopMenu);
                MenuPcs.m_shopMenu = 0;
                return;
            }
            this->SetMode(m_nextMode);
        }
        break;
    case 12:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(0xD);
        }
        break;
    case 13:
        this->SelectMake();
        if ((GetPadButtons() & 0x200) != 0) {
            m_nextMode = 9;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(0xE);
        }
        break;
    case 14:
        m_fade = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(m_nextMode);
        }
        break;
    case 15:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        m_fade = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            unsigned short recipeMaterial[8];
            int itemId = getItemNo(m_selectedIndex);
            CCaravanWork* const caravanWork = ShopMenuCaravanWork(this);

            MenuPcs.GetRecipeMaterial(itemId, reinterpret_cast<CMenuPcs::MaterialInfo*>(recipeMaterial));
            caravanWork->AddGil(-CalcShopMenuMakeGil(this, itemId));
            caravanWork->DeleteItem(itemId, 0);

            for (int i = 0; i < 3; i++) {
                if (recipeMaterial[i] < 1) {
                    break;
                }
                for (int count = 0; count < recipeMaterial[i + 3]; count++) {
                    caravanWork->DeleteItem(recipeMaterial[i], 0);
                }
            }

            caravanWork->AddItem(static_cast<short>(m_resultItem), &m_resultParam);
            this->SetMode(0x10);
        }
        break;
    case 16:
        this->SelectSOUBI();
        break;
    case 17:
        m_fade = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(m_nextMode);
        }
        break;
    }

    ++timer;

    if ((shopMode == 0) || (shopMode == 1)) {
        gShopMenuInputLatch = 0;
    }
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
    CShopMenu* shopMenu = reinterpret_cast<CShopMenu*>(
        operator new(0x158, (Game.m_gameWork.m_menuStageMode != 0) ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage,
            s_shopmenu_cpp, 0x2E9));
    m_shopMenu = shopMenu;
    shopMenu = m_shopMenu;

    Graphic._WaitDrawDone(s_shopmenu_cpp, 0x2FE);
    shopMenu->m_unk00 = nullptr;
    shopMenu->m_caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
    shopMenu->SetMode(9);
    shopMenu->m_pdtSlot = PartPcs.LoadMenuPdt(s_shop_80332e54);

    int slotIndex = shopMenu->m_pdtSlot;
    _pppDataHead* pppDataHead = PartMng.m_pdtSlots[slotIndex].m_pppDataHead;
    short* cacheChunks = reinterpret_cast<short*>(pppDataHead->m_cacheChunks);
    *reinterpret_cast<int*>(cacheChunks + 2) =
        ppvAmemCacheSet.GetData(*cacheChunks, s_shopmenu_cpp, 0x32A);
    int cacheData = *reinterpret_cast<int*>(cacheChunks + 2);
    pppCacheLoadShape(
        reinterpret_cast<short*>(cacheData + *reinterpret_cast<int*>(cacheData + 0x14)), pppDataHead);
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
    CShopMenu* shopMenu = reinterpret_cast<CShopMenu*>(
        operator new(0x158, (Game.m_gameWork.m_menuStageMode != 0) ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage,
            s_shopmenu_cpp, 0x2E2));
    m_shopMenu = shopMenu;
    shopMenu = m_shopMenu;

    Graphic._WaitDrawDone(s_shopmenu_cpp, 0x2FE);
    shopMenu->m_unk00 = nullptr;
    shopMenu->m_caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
    shopMenu->SetMode(0);
    shopMenu->m_pdtSlot = PartPcs.LoadMenuPdt(s_shop_80332e54);

    int slotIndex = shopMenu->m_pdtSlot;
    _pppDataHead* pppDataHead = PartMng.m_pdtSlots[slotIndex].m_pppDataHead;
    short* cacheChunks = reinterpret_cast<short*>(pppDataHead->m_cacheChunks);
    *reinterpret_cast<int*>(cacheChunks + 2) =
        ppvAmemCacheSet.GetData(*cacheChunks, s_shopmenu_cpp, 0x32A);
    int cacheData = *reinterpret_cast<int*>(cacheChunks + 2);
    pppCacheLoadShape(
        reinterpret_cast<short*>(cacheData + *reinterpret_cast<int*>(cacheData + 0x14)), pppDataHead);
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeqGrouad(int shapeNo, int groupNo, int x, int y, float scaleX, float scaleY, _GXColor colorA,
                        _GXColor colorB, _GXColor colorC, _GXColor colorD)
{
    Mtx44 projectionMtx;
    Mtx screenMtx;

    PSMTXIdentity(screenMtx);
    screenMtx[0][0] = scaleX;
    screenMtx[1][1] = -scaleY;
    screenMtx[2][2] = FLOAT_80332d78;
    screenMtx[0][3] = static_cast<float>(x);
    screenMtx[1][3] = static_cast<float>(y);
    GXLoadPosMtxImm(screenMtx, 0);
    GXSetCurrentMtx(0);

    C_MTXOrtho(projectionMtx, FLOAT_80332d9c, FLOAT_80332dec, FLOAT_80332d9c, FLOAT_80332df0, FLOAT_80332d9c,
               FLOAT_80332d28);
    projectionMtx[2][3] += FLOAT_80332d9c;
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);

    _GXColor matColor;
    *reinterpret_cast<unsigned int*>(&matColor) = reinterpret_cast<unsigned int>(g_shopMenu);

    int shapeData = reinterpret_cast<int>(ppvEnv->m_resourceTables.m_shapeTablePtr[shapeNo]->m_animData);
    tagOAN3_SHAPE* shape =
        reinterpret_cast<tagOAN3_SHAPE*>(shapeData + *reinterpret_cast<short*>(shapeData + groupNo * 8 + 0x10));

    MaterialMan.SetDefaultStdDrawEnv(0xACE0F);

    _GXColor drawColor = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanAmbColor(GX_COLOR0A0, drawColor);
    GXSetChanMatColor(GX_COLOR0A0, matColor);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetZCompLoc(GX_TRUE);

    MaterialMan.SetMaterialMenu(
        ppvEnv->m_materialSetPtr,
        static_cast<int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(shape) + 10)), 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    Vec minPos;
    Vec maxPos;
    int vertexData = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shape) + 0xC);
    *reinterpret_cast<unsigned int*>(&minPos.x) = *reinterpret_cast<unsigned int*>(vertexData + 3);
    *reinterpret_cast<unsigned int*>(&minPos.y) = *reinterpret_cast<unsigned int*>(vertexData + 7);
    minPos.z = FLOAT_80332d9c;
    *reinterpret_cast<unsigned int*>(&maxPos.x) = *reinterpret_cast<unsigned int*>(vertexData + 0x2B);
    *reinterpret_cast<unsigned int*>(&maxPos.y) = *reinterpret_cast<unsigned int*>(vertexData + 0x2F);
    maxPos.z = FLOAT_80332d9c;

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    Graphic.RenderTexQuadGrouad(minPos, maxPos, colorA, colorB, colorC, colorD);
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeqScale(int shapeNo, int groupNo, int x, int y, float scaleX, float scaleY, unsigned char alpha)
{
    Mtx44 projectionMtx;
    Mtx screenMtx;

    PSMTXIdentity(screenMtx);
    screenMtx[0][0] = scaleX;
    screenMtx[1][1] = -scaleY;
    screenMtx[2][2] = FLOAT_80332d78;
    screenMtx[0][3] = static_cast<float>(x);
    screenMtx[1][3] = static_cast<float>(y);
    GXLoadPosMtxImm(screenMtx, 0);
    GXSetCurrentMtx(0);

    C_MTXOrtho(projectionMtx, FLOAT_80332d9c, FLOAT_80332dec, FLOAT_80332d9c, FLOAT_80332df0, FLOAT_80332d9c,
               FLOAT_80332d28);
    projectionMtx[2][3] += FLOAT_80332d9c;
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);

    _GXColor mat;
    *reinterpret_cast<unsigned int*>(&mat) = (gShopMenuMaterialWhiteBase & 0xFFFFFF00) | alpha;

    int shapeData = reinterpret_cast<int>(ppvEnv->m_resourceTables.m_shapeTablePtr[shapeNo]->m_animData);
    tagOAN3_SHAPE* shape =
        reinterpret_cast<tagOAN3_SHAPE*>(shapeData + *reinterpret_cast<short*>(shapeData + groupNo * 8 + 0x10));

    MaterialMan.SetDefaultStdDrawEnv(0xACE0F);

    _GXColor amb;
    *reinterpret_cast<unsigned int*>(&amb) = gShopMenuAmbientWhite;
    GXSetChanAmbColor(GX_COLOR0A0, amb);
    GXSetChanMatColor(GX_COLOR0A0, mat);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);

    MaterialMan.SetMaterialMenu(
        ppvEnv->m_materialSetPtr,
        static_cast<int>(*reinterpret_cast<signed char*>(reinterpret_cast<unsigned char*>(shape) + 10)), 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    unsigned char* displayList = reinterpret_cast<unsigned char*>(shape);
    int shapeCount = *reinterpret_cast<unsigned short*>(displayList + 2);
    for (int i = 0; i < shapeCount; i++) {
        GXCallDisplayList(*reinterpret_cast<void**>(displayList + 0xC), 0x60);
        displayList += 8;
    }
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeq(int shapeNo, int groupNo, int x, int y, unsigned char alpha, unsigned char flipX, unsigned char flipY,
                  float zOffset, unsigned char tlut)
{
    (void)tlut;

    Mtx44 projectionMtx;
    Mtx screenMtx;

    PSMTXIdentity(screenMtx);
    float scaleX;
    if (flipX != 0) {
        scaleX = FLOAT_80332dd0;
    } else {
        scaleX = FLOAT_80332d78;
    }
    screenMtx[0][0] = scaleX;

    float scaleY;
    if (flipY != 0) {
        scaleY = FLOAT_80332d78;
    } else {
        scaleY = FLOAT_80332dd0;
    }
    screenMtx[1][1] = scaleY;
    screenMtx[0][3] = static_cast<float>(x);
    screenMtx[1][3] = static_cast<float>(y);
    screenMtx[2][2] = FLOAT_80332d78;
    GXLoadPosMtxImm(screenMtx, 0);
    GXSetCurrentMtx(0);

    C_MTXOrtho(projectionMtx, FLOAT_80332d9c, FLOAT_80332dec, FLOAT_80332d9c, FLOAT_80332df0, FLOAT_80332d9c,
               FLOAT_80332d28);
    projectionMtx[2][3] += zOffset;
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);

    int shapeData = reinterpret_cast<int>(ppvEnv->m_resourceTables.m_shapeTablePtr[shapeNo]->m_animData);
    tagOAN3_SHAPE* shape =
        reinterpret_cast<tagOAN3_SHAPE*>(shapeData + *reinterpret_cast<short*>(shapeData + groupNo * 8 + 0x10));

    MaterialMan.SetDefaultStdDrawEnv(0xACE0F);

    _GXColor amb;
    *reinterpret_cast<unsigned int*>(&amb) = gShopMenuAmbientWhite;
    GXSetChanAmbColor(GX_COLOR0A0, amb);

    _GXColor mat;
    *reinterpret_cast<unsigned int*>(&mat) = (gShopMenuMaterialWhiteBase & 0xFFFFFF00) | alpha;
    GXSetChanMatColor(GX_COLOR0A0, mat);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);

    MaterialMan.SetMaterialMenu(
        ppvEnv->m_materialSetPtr,
        static_cast<int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(shape) + 10)), 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    unsigned char* shapeBytes = reinterpret_cast<unsigned char*>(shape);
    unsigned char* displayList = shapeBytes;
    int shapeCount = *reinterpret_cast<unsigned short*>(shapeBytes + 2);
    for (int i = 0; i < shapeCount; i++) {
        GXCallDisplayList(*reinterpret_cast<void**>(displayList + 0xC), 0x60);
        displayList += 8;
    }
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
        m_fade = 0.0f;
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
        m_fade = 0.0f;
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

        CMenuPcs* menuPcs = &MenuPcs;
        for (int i = 0; i < 0x40; i++) {
            if (menuPcs->GetItemType(i, 0) == 9) {
                int count = m_itemCount;
                m_itemCount = count + 1;
                m_itemTable[count] = i;
            }
        }

        if (m_itemCount == 0) {
            for (int i = 0; i < 8; i++) {
                int count = m_itemCount;
                m_itemCount = count + 1;
                m_itemTable[count] = -1;
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
void CShopMenu::DrawBuy()
{
    DrawShopBase();
    DrawItemList();
    DrawItemInfo0();
    DrawBuySellInfo();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawSell()
{
    DrawShopBase();
    DrawItemList();
    DrawItemInfo0();
    DrawBuySellInfo();
}





/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::InitDrawEnvShape()
{
    pppInitDrawEnv(0);
}






/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawDec(int shapeNo, int groupNo, int x, float y, float alpha, int flipX, int flipY, int tlut)
{
    drawShapeSeq(shapeNo, groupNo, x, static_cast<int>(y), static_cast<unsigned char>(alpha), static_cast<unsigned char>(flipX),
        static_cast<unsigned char>(flipY), 0.0f, static_cast<unsigned char>(tlut));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawDecScale(int shapeNo, int groupNo, int x, float y, float scaleX, float scaleY, int alpha, int, int)
{
    drawShapeSeqScale(shapeNo, groupNo, x, static_cast<int>(y), scaleX, scaleY, static_cast<unsigned char>(alpha));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::setFaceAlpha(int, int alpha)
{
    m_faceAlpha = alpha;
}
