#include "ffcc/shopmenu.h"
#include "ffcc/graphic.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/sound.h"
#include "ffcc/linkage.h"
#include "ffcc/p_tina.h"
#include <string.h>

extern "C" {
void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
void _WaitDrawDone__8CGraphicFPci(void*, char*, int);
void SetDrawDoneDebugData__8CGraphicFSc(void*, signed char);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void SetMode__9CShopMenuFi(void*, int);
void DrawSingleBase__8CMenuPcsFf(void*, float);
void ReleasePdt__8CPartPcsFi(void*, int);
int LoadMenuPdt__8CPartPcsFPc(void*, char*);
int GetItemType__8CMenuPcsFii(void*, int, int);
const char* GetJobStr__8CMenuPcsFi(CMenuPcs*, int);
void GetRaceStr__8CMenuPcsFiPc(void*, int, char*);
int GetData__13CAmemCacheSetFsPci(void*, short, char*, int);
int ChkEquipPossible__8CMenuPcsFi(void*, int);
void GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo(void*, int, short*);
int CanAddGil__12CCaravanWorkFi(void*, int);
void AddItem__12CCaravanWorkFiPi(void*, int, int*);
void AddGil__12CCaravanWorkFi(void*, int);
void DeleteItem__12CCaravanWorkFii(void*, int, int);
void DeleteItemIdx__12CCaravanWorkFii(void*, int, int);
char EquipChk__8CMenuPcsFi(void*, int);
int GetSmithItem__8CMenuPcsFi(void*, int);
int __cntlzw(unsigned int);
void __dl__FPv(void*);
void pppCacheLoadShape__FPsP12_pppDataHead(short*, _pppDataHead*);
int GetEquipType__8CMenuPcsFi(void*, int);
void ChgEquipPos__12CCaravanWorkFii(void*, int, int);
char* GetAttrStr__8CMenuPcsFi(void*, int);
void SetScale__5CFontFf(float, CFont*);
void SetScaleX__5CFontFf(float, CFont*);
void SetScaleY__5CFontFf(float, CFont*);
void SetMargin__5CFontFf(float, CFont*);
void SetShadow__5CFontFi(CFont*, int);
void SetColor__5CFontF8_GXColor(CFont*, _GXColor*);
void SetPosX__5CFontFf(float, CFont*);
void SetPosY__5CFontFf(float, CFont*);
void SetTlut__5CFontFi(CFont*, int);
void DrawInit__5CFontFv(CFont*);
float GetWidth__5CFontFPc(CFont*, const char*);
void Draw__5CFontFPc(CFont*, const char*);
void DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(void*, CFont*, char*, float, float, int, int);
void DrawShadowFont__8CMenuPcsFP5CFontPcffii(void*, CFont*, char*, float, float, int, int);
void DrawSingleIcon__8CMenuPcsFiiifif(void*, int, int, int, float, float, float);
void DrawInit__8CMenuPcsFv(void*);
void DrawCursor__8CMenuPcsFiif(void*, int, int, float);
void MakeAgbString__4CMesFPcPcii(char*, char*, int, int);
int sprintf(char*, const char*, ...);
char* strcpy(char*, const char*);
char* strcat(char*, const char*);
}

char s_shopmenu_cpp_801ded8c[] = "shopmenu.cpp";
extern char DAT_80332e54[];
unsigned short gShopMenuInputLatch;
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
extern float FLOAT_80332dd0;
extern float FLOAT_80332de0;
extern float FLOAT_80332e48;
extern float FLOAT_80332e4c;
extern float FLOAT_80332d7c;
extern float FLOAT_80332d80;
extern float FLOAT_80332d88;
extern float FLOAT_80332d8c;
extern float FLOAT_80332d90;
extern float FLOAT_80332d94;
extern float FLOAT_80332d98;
extern char DAT_80332d84[];
extern char DAT_80332d14[];
extern char DAT_80332d18[];
extern char DAT_80332d30[];
extern char DAT_80332d38[];
extern char DAT_80332d40[];
extern char DAT_80332d44[];
extern char DAT_80332d4c[];
extern char DAT_80332d50[];
extern char* PTR_DAT_80214d90[];
extern char* PTR_DAT_80214d94[];
extern char* PTR_s_Cancel_80214d98[];
extern char* PTR_DAT_80214d9c[];
extern char* PTR_s_Blacksmith_80214da0[];
extern char* PTR_s_Price_80214dc4[];
extern char* PTR_s_Money_80214db0[];
extern char* PTR_DAT_80214da8[];
extern char* PTR_s_Equip_80214dc0[];
extern char* PTR_s_Cannot_buy_80214dc8[];
extern char* PTR_s_Cannot_sell_80214dcc[];
extern char* PTR_s_Cannot_be_crafted_here__80214de0[];
extern char* PTR_s_Quantity_80214dd0[];
extern char* PTR_s_Strength_80214dd4[];
extern char* PTR_s_Defence_80214dd8[];

static inline void* MenuPcsVoid()
{
    return &MenuPcs;
}

static inline unsigned char* MenuPcsRaw()
{
    return reinterpret_cast<unsigned char*>(&MenuPcs);
}

static inline void* PartPcsVoid()
{
    return &PartPcs;
}

static inline int& ShopMenuInt(CShopMenu* shopMenu, int offset)
{
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + offset);
}

struct ShopMenuFlatTableEntry {
    int count;
    const char** index;
    char* buffer;
};

struct ShopMenuFlatData {
    char pad[0x6C];
    ShopMenuFlatTableEntry table[8];
};

static inline int* GetShopMenuHelpMsgTable()
{
    return reinterpret_cast<int*>(reinterpret_cast<ShopMenuFlatData*>(&Game.m_cFlatDataArr[1])->table[6].index);
}

static inline float& ShopMenuFloat(CShopMenu* shopMenu, int offset)
{
    return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(shopMenu) + offset);
}

static inline unsigned short GetPadButtons()
{
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        return 0;
    }
    __cntlzw(static_cast<unsigned int>(Pad._448_4_));
    return static_cast<unsigned short>(Pad._8_2_);
}

static inline int ShopMenuCaravan(CShopMenu* shopMenu)
{
    return ShopMenuInt(shopMenu, 0x20);
}

static unsigned char s_shopMenuTabCacheLanguage = 0xFF;
static const char* s_shopMenuTabLabels[3];
static const int s_shopMenuTabLayout[3][2] = {
    {0x88, 0x92},
    {0x88, 0xB6},
    {0x88, 0xDA},
};

static void RefreshShopMenuTabLabels()
{
    unsigned char languageId = Game.m_gameWork.m_languageId;
    if (s_shopMenuTabCacheLanguage == languageId) {
        return;
    }

    int languageIndex = static_cast<int>(languageId) - 1;
    s_shopMenuTabLabels[0] = PTR_DAT_80214d90[languageIndex];
    s_shopMenuTabLabels[1] = PTR_DAT_80214d94[languageIndex];
    s_shopMenuTabLabels[2] = PTR_s_Cancel_80214d98[languageIndex];
    s_shopMenuTabCacheLanguage = languageId;
}

static float CalcCenteredShopMenuX(CFont* font, const char* text)
{
    if (text == 0) {
        return 0.0f;
    }
    return (464.0f - GetWidth__5CFontFPc(font, text)) * 0.5f;
}

static void DrawShopMenuFadeOverlay(float fade)
{
    if (fade == FLOAT_80332d28) {
        return;
    }

    int fadeStep = static_cast<int>(FLOAT_80332de0 * fade);
    unsigned char alpha = static_cast<unsigned char>(0xFF - (fadeStep & 0xFF));

    SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x32);

    Mtx screenMtx;
    Mtx44 projectionMtx;
    PSMTXIdentity(screenMtx);
    screenMtx[1][1] = -1.0f;
    screenMtx[1][3] = 480.0f;
    GXLoadPosMtxImm(screenMtx, 0);
    GXSetCurrentMtx(0);

    C_MTXOrtho(projectionMtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);

    _GXColor fadeColor = {0, 0, 0, alpha};
    GXSetChanAmbColor(GX_COLOR0A0, fadeColor);
    GXSetChanMatColor(GX_COLOR0A0, fadeColor);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 5);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 0, 7, 0xFF);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT6, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT6, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    Vec topLeft = {0.0f, 0.0f, 0.0f};
    Vec bottomRight = {640.0f, 480.0f, 0.0f};
    Graphic.RenderNoTexQuadGrouad(topLeft, bottomRight, fadeColor, fadeColor, fadeColor, fadeColor);

    SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x33);
}

static int ResolveShopMenuItemCount(CShopMenu* shopMenu)
{
    switch (ShopMenuInt(shopMenu, 0x14)) {
    case 0:
        return *reinterpret_cast<short*>(ShopMenuCaravan(shopMenu) + 0xBE4);
    case 1:
        return 0x40;
    case 2:
        return ShopMenuInt(shopMenu, 0x4C);
    default:
        return 0;
    }
}

static int ResolveShopMenuItemNo(CShopMenu* shopMenu, int index)
{
    int caravan = ShopMenuCaravan(shopMenu);
    if (index < 0) {
        return -1;
    }

    switch (ShopMenuInt(shopMenu, 0x14)) {
    case 0:
        return *reinterpret_cast<short*>(caravan + index * 2 + 0xBE6);
    case 1:
        return *reinterpret_cast<short*>(caravan + index * 2 + 0xB6);
    case 2: {
        int mapped = ShopMenuInt(shopMenu, 0x50 + index * 4);
        if (mapped == -1) {
            return -1;
        }
        return *reinterpret_cast<short*>(caravan + mapped * 2 + 0xB6);
    }
    default:
        return -1;
    }
}

static int ResolveShopMenuSelectedItemId(CShopMenu* shopMenu)
{
    int selected = ShopMenuInt(shopMenu, 0x28);
    int caravan = ShopMenuCaravan(shopMenu);

    switch (ShopMenuInt(shopMenu, 0x14)) {
    case 0:
        return *reinterpret_cast<short*>(caravan + selected * 2 + 0xBE6);
    case 1:
        return *reinterpret_cast<short*>(caravan + selected * 2 + 0xB6);
    case 2: {
        int mapped = ShopMenuInt(shopMenu, 0x50 + selected * 4);
        if (mapped == -1) {
            return -1;
        }
        return *reinterpret_cast<short*>(caravan + mapped * 2 + 0xB6);
    }
    default:
        return -1;
    }
}

static int CalcShopMenuMakeGil(CShopMenu* shopMenu, int itemId)
{
    if (itemId < 1) {
        return 0;
    }

    int caravan = ShopMenuCaravan(shopMenu);
    int gilValue = *reinterpret_cast<short*>(caravan + 0xBE2) *
                   *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x24);
    gilValue = gilValue / 100 + (gilValue >> 0x1F);
    return gilValue - (gilValue >> 0x1F);
}

static int CalcShopMenuGilRatio(CShopMenu* shopMenu, int baseGil)
{
    if (baseGil <= 0) {
        return 0;
    }

    int gil = *reinterpret_cast<short*>(ShopMenuCaravan(shopMenu) + 0xBE2) * baseGil;
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

static int CountShopMenuOwnedItems(int caravan, int itemNo)
{
    if (itemNo < 1) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < 0x40; i++) {
        if (*reinterpret_cast<short*>(caravan + i * 2 + 0xB6) == itemNo) {
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

    int listType = ShopMenuInt(shopMenu, 0x14);
    if (listType == 0) {
        return true;
    }

    if (listType == 2) {
        unsigned int bit = static_cast<unsigned int>(itemNo - 0x191);
        int caravan = ShopMenuCaravan(shopMenu);
        return (*reinterpret_cast<unsigned int*>(caravan + ((itemNo - 0x191) >> 5) * 4 + 0xC08) & (1U << (bit & 0x1F))) != 0;
    }

    if (EquipChk__8CMenuPcsFi(MenuPcsVoid(), index) != 0) {
        return false;
    }

    return itemNo >= 0x9F;
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
    unsigned char* menuPcs = reinterpret_cast<unsigned char*>(this);
    void* stage = *reinterpret_cast<void**>(MenuPcsRaw() + 0xEC);
    if (Game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<void**>(MenuPcsRaw() + 0xF4);
    }

    CShopMenu* shopMenu = reinterpret_cast<CShopMenu*>(
        __nw__FUlPQ27CMemory6CStagePci(0x158, stage, s_shopmenu_cpp_801ded8c, 0x2E2));
    *reinterpret_cast<CShopMenu**>(menuPcs + 0x878) = shopMenu;
    shopMenu = *reinterpret_cast<CShopMenu**>(menuPcs + 0x878);

    _WaitDrawDone__8CGraphicFPci(&Graphic, s_shopmenu_cpp_801ded8c, 0x2FE);
    *reinterpret_cast<void**>(shopMenu) = nullptr;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x20) = Game.m_scriptFoodBase[0];
    SetMode__9CShopMenuFi(shopMenu, 0);
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x18) =
        LoadMenuPdt__8CPartPcsFPc(PartPcsVoid(), DAT_80332e54);

    int slotIndex = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x18);
    _pppDataHead* pppDataHead =
        *reinterpret_cast<_pppDataHead**>(reinterpret_cast<unsigned char*>(&PartMng) + 0x22E18 + slotIndex * 0x38);
    short* cacheChunks = reinterpret_cast<short*>(pppDataHead->m_cacheChunks);
    *reinterpret_cast<int*>(cacheChunks + 2) =
        GetData__13CAmemCacheSetFsPci(&ppvAmemCacheSet, *cacheChunks, s_shopmenu_cpp_801ded8c, 0x32A);
    int cacheData = *reinterpret_cast<int*>(cacheChunks + 2);
    pppCacheLoadShape__FPsP12_pppDataHead(
        reinterpret_cast<short*>(cacheData + *reinterpret_cast<int*>(cacheData + 0x14)), pppDataHead);
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
    unsigned char* menuPcs = reinterpret_cast<unsigned char*>(this);
    void* stage = *reinterpret_cast<void**>(MenuPcsRaw() + 0xEC);
    if (Game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<void**>(MenuPcsRaw() + 0xF4);
    }

    CShopMenu* shopMenu = reinterpret_cast<CShopMenu*>(
        __nw__FUlPQ27CMemory6CStagePci(0x158, stage, s_shopmenu_cpp_801ded8c, 0x2E9));
    *reinterpret_cast<CShopMenu**>(menuPcs + 0x878) = shopMenu;
    shopMenu = *reinterpret_cast<CShopMenu**>(menuPcs + 0x878);

    _WaitDrawDone__8CGraphicFPci(&Graphic, s_shopmenu_cpp_801ded8c, 0x2FE);
    *reinterpret_cast<void**>(shopMenu) = nullptr;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x20) = Game.m_scriptFoodBase[0];
    SetMode__9CShopMenuFi(shopMenu, 9);
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x18) =
        LoadMenuPdt__8CPartPcsFPc(PartPcsVoid(), DAT_80332e54);

    int slotIndex = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x18);
    _pppDataHead* pppDataHead =
        *reinterpret_cast<_pppDataHead**>(reinterpret_cast<unsigned char*>(&PartMng) + 0x22E18 + slotIndex * 0x38);
    short* cacheChunks = reinterpret_cast<short*>(pppDataHead->m_cacheChunks);
    *reinterpret_cast<int*>(cacheChunks + 2) =
        GetData__13CAmemCacheSetFsPci(&ppvAmemCacheSet, *cacheChunks, s_shopmenu_cpp_801ded8c, 0x32A);
    int cacheData = *reinterpret_cast<int*>(cacheChunks + 2);
    pppCacheLoadShape__FPsP12_pppDataHead(
        reinterpret_cast<short*>(cacheData + *reinterpret_cast<int*>(cacheData + 0x14)), pppDataHead);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _drawNoShadowFont(CFont* font, char* text, float x, float y, int tlut, int flags)
{
	DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, text, x, y, tlut, flags);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _drawShadowFont(CFont* font, char* text, float x, float y, int tlut, int flags)
{
	DrawShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, text, x, y, tlut, flags);
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
        bool hasInput = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20);
        }
    } else {
        bool hasInput = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = Pad._4_2_;
        }

        if ((buttons & gShopMenuInputLatch) == 0) {
            gShopMenuInputLatch = 0;
        }

        hasInput = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = Pad._8_2_;
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
 * PAL Address: 0x801593f8
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CShopMenu::SetMode(int mode)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    *reinterpret_cast<int*>(self + 0x0) = mode;
    *reinterpret_cast<int*>(self + 0xC) = 0;

    switch (*reinterpret_cast<int*>(self + 0x0)) {
    case 0:
        *reinterpret_cast<float*>(self + 0x1C) = 0.0f;
        *reinterpret_cast<unsigned char*>(self + 0x48) = 0xFF;
        break;
    case 1:
        *reinterpret_cast<unsigned char*>(self + 0x48) = 0;
        break;
    case 3:
        *reinterpret_cast<int*>(self + 0x14) = 0;
        goto mode_3_6_common;
    case 6:
        *reinterpret_cast<int*>(self + 0x14) = 1;
mode_3_6_common:
        *reinterpret_cast<int*>(self + 0x10) = 0;
        *reinterpret_cast<int*>(self + 0x28) = -1;
        *reinterpret_cast<int*>(self + 0x24) = 0;
        *reinterpret_cast<int*>(self + 0x2C) = 8;
        *reinterpret_cast<int*>(self + 0x34) = 0;
        *reinterpret_cast<int*>(self + 0x30) = 0;
        *reinterpret_cast<int*>(self + 0x40) = 0;
        *reinterpret_cast<int*>(self + 0x44) = 1;
        *reinterpret_cast<int*>(self + 0x38) = 0;
        *reinterpret_cast<int*>(self + 0x3C) = 0;
        break;
    case 4:
    case 7:
        *reinterpret_cast<int*>(self + 0x28) = 0;
        *reinterpret_cast<int*>(self + 0x24) = 0;
        *reinterpret_cast<int*>(self + 0x38) = 0;
        break;
    case 9: {
        *reinterpret_cast<float*>(self + 0x1C) = 0.0f;
        *reinterpret_cast<unsigned char*>(self + 0x48) = 0xFF;
        *reinterpret_cast<int*>(self + 0x14) = 2;
        *reinterpret_cast<int*>(self + 0x10) = 0;
        *reinterpret_cast<int*>(self + 0x28) = 0;
        *reinterpret_cast<int*>(self + 0x24) = 0;
        *reinterpret_cast<int*>(self + 0x2C) = 8;
        *reinterpret_cast<int*>(self + 0x34) = 0;
        *reinterpret_cast<int*>(self + 0x30) = 0;
        *reinterpret_cast<int*>(self + 0x40) = 0;
        *reinterpret_cast<int*>(self + 0x44) = 1;
        *reinterpret_cast<int*>(self + 0x38) = 0;
        *reinterpret_cast<int*>(self + 0x3C) = 0;
        *reinterpret_cast<int*>(self + 0x154) = -1;
        *reinterpret_cast<int*>(self + 0x4C) = 0;

        for (int i = 0; i < 0x40; i++) {
            if (GetItemType__8CMenuPcsFii(MenuPcsVoid(), i, 0) == 9) {
                int count = *reinterpret_cast<int*>(self + 0x4C);
                *reinterpret_cast<int*>(self + 0x4C) = count + 1;
                *reinterpret_cast<int*>(self + 0x50 + count * 4) = i;
            }
        }

        if (*reinterpret_cast<int*>(self + 0x4C) == 0) {
            *reinterpret_cast<int*>(self + 0x4C) = 1;
            *reinterpret_cast<int*>(self + 0x50) = -1;
            for (int i = 0; i < 7; i++) {
                int count = *reinterpret_cast<int*>(self + 0x4C);
                *reinterpret_cast<int*>(self + 0x4C) = count + 1;
                *reinterpret_cast<int*>(self + 0x50 + count * 4) = -1;
            }
        }
        break;
    }
    case 10:
        *reinterpret_cast<unsigned char*>(self + 0x48) = 0;
        break;
    case 12:
        *reinterpret_cast<int*>(self + 0x3C) = 0;
        break;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::getItemCnt()
{
    return ResolveShopMenuItemCount(this);
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
    return ResolveShopMenuItemNo(this, index);
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
    switch (ShopMenuInt(this, 0x14)) {
    case 0:
        return getBuyGil(itemNo);
    case 1:
        return getSellGil(itemNo);
    case 2:
        return getMakeGil(itemNo);
    default:
        return -1;
    }
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

    return reinterpret_cast<char*>(reinterpret_cast<int*>(Game.unkCFlatData0[1])[itemNo * 5 + 4]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::GetMaxExchange()
{
    int itemNo = getItemNo(ShopMenuInt(this, 0x28));
    if (itemNo < 1) {
        return 0;
    }

    int caravan = ShopMenuCaravan(this);
    switch (ShopMenuInt(this, 0x14)) {
    case 0: {
        int maxCount = 0x40 - *reinterpret_cast<unsigned short*>(caravan + 0x94);
        int unitGil = getBuyGil(itemNo);
        if (unitGil > 0) {
            int byMoney = *reinterpret_cast<int*>(caravan + 0x200) / unitGil;
            if (byMoney < maxCount) {
                maxCount = byMoney;
            }
        }
        return maxCount;
    }
    case 1:
        return getItemHaveCnt(itemNo);
    case 2:
        return 1;
    default:
        return 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CShopMenu::GetTotalGil()
{
    int unitGil = getBuySellGil(getItemNo(ShopMenuInt(this, 0x28)));
    if (unitGil < 0) {
        return unitGil;
    }

    return ShopMenuInt(this, 0x44) * unitGil;
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

    if (ShopMenuInt(this, 0x14) != 1) {
        totalGil = -totalGil;
    }
    return CanAddGil__12CCaravanWorkFi(reinterpret_cast<void*>(ShopMenuCaravan(this)), totalGil);
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
    return CountShopMenuOwnedItems(ShopMenuCaravan(this), itemNo);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setOrtho(int, int, float, float, float)
{
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetColorUpdate(GX_TRUE);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShp(tagOAN3_SHAPE*, CMaterialSet*, unsigned char)
{
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeq0(int, int, unsigned char, unsigned char)
{
    drawShapeSeq(0, 0, 0, 0, 0xFF, 0, 0, 0.0f, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeq(int, int, int, int, unsigned char, unsigned char, unsigned char, float, unsigned char)
{
    drawShapeSeqScale(0, 0, 0, 0, 1.0f, 1.0f, 0xFF);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeqScale(int, int, int, int, float, float, unsigned char)
{
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    drawShapeSeqGrouad(0, 0, 0, 0, 1.0f, 1.0f, white, white, white, white);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeqGrouad(int, int, int, int, float, float, _GXColor, _GXColor, _GXColor, _GXColor)
{
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    drawGrouadQuad(0, 0, 0x20, 0x20, white, white, white, white);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawGrouadQuad(int, int, int, int, _GXColor, _GXColor, _GXColor, _GXColor)
{
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Init(int mode)
{
    gShopMenuInputLatch = 0;
    SetMode__9CShopMenuFi(this, mode);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Destroy()
{
    ReleasePdt__8CPartPcsFi(PartPcsVoid(), ShopMenuInt(this, 0x18));
    if (*reinterpret_cast<void**>(MenuPcsRaw() + 0x878) == this) {
        *reinterpret_cast<void**>(MenuPcsRaw() + 0x878) = nullptr;
    }
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
    unsigned short buttons = GetPadButtons();
    int mode = ShopMenuInt(this, 0x0);
    int& timer = ShopMenuInt(this, 0xC);
    int& subMode = ShopMenuInt(this, 0x10);
    int& shopMode = ShopMenuInt(this, 0x14);
    int& choice = ShopMenuInt(this, 0x48);

    switch (mode) {
    case 0:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        ShopMenuFloat(this, 0x1C) = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(1);
        }
        break;
    case 1:
        if ((buttons & 4) != 0) {
            ++choice;
            if (choice > 2) {
                choice = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((buttons & 8) != 0) {
            --choice;
            if (choice > 2) {
                choice = 2;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((buttons & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            this->SetMode(2);
        }

        if ((buttons & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(2);
            choice = 2;
        }
        break;
    case 2:
        ShopMenuFloat(this, 0x1C) = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            if (choice == 0) {
                this->SetMode(3);
            } else if (choice == 1) {
                this->SetMode(6);
            } else if (choice == 2) {
                ReleasePdt__8CPartPcsFi(PartPcsVoid(), ShopMenuInt(this, 0x18));
                reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->CallShop(0, 0, 0, 0, 0);
                *reinterpret_cast<unsigned short*>(MenuPcsRaw() + 0x850 + 6) = 1;
                __dl__FPv(*reinterpret_cast<void**>(MenuPcsRaw() + 0x878));
                *reinterpret_cast<void**>(MenuPcsRaw() + 0x878) = nullptr;
                return;
            }
        }
        break;
    case 3:
        if (timer == 0) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        ShopMenuFloat(this, 0x1C) = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(4);
        }
        break;
    case 4:
        if (subMode == 0) {
            this->SelectItemIdx();
            if ((buttons & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                this->SetMode(5);
            }
        } else if (subMode == 1) {
            this->SelectFigure();
            if ((buttons & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                subMode = 0;
            }
        } else if (subMode == 2) {
            this->SelectYesNo();
            if ((buttons & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                subMode = 1;
            }
        }
        break;
    case 5:
    case 8:
        ShopMenuFloat(this, 0x1C) = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(0);
        }
        break;
    case 6:
        if (timer == 0) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        ShopMenuFloat(this, 0x1C) = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(7);
        }
        break;
    case 7:
        if (subMode == 0) {
            this->SelectItemIdx();
            if ((buttons & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                this->SetMode(8);
            }
        } else if (subMode == 2) {
            this->SelectYesNo();
            if ((buttons & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                subMode = 1;
            }
        }
        break;
    case 9:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        ShopMenuFloat(this, 0x1C) = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(10);
        }
        break;
    case 10:
        this->SelectItemIdx();
        if ((buttons & 0x200) != 0) {
            ShopMenuInt(this, 0x8) = -1;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(0xB);
        }
        break;
    case 11:
        ShopMenuFloat(this, 0x1C) = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            if (ShopMenuInt(this, 0x8) == -1) {
                ReleasePdt__8CPartPcsFi(PartPcsVoid(), ShopMenuInt(this, 0x18));
                reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->CallShop(0, 0, 0, 0, 0);
                *reinterpret_cast<unsigned short*>(MenuPcsRaw() + 0x850 + 6) = 1;
                __dl__FPv(*reinterpret_cast<void**>(MenuPcsRaw() + 0x878));
                *reinterpret_cast<void**>(MenuPcsRaw() + 0x878) = nullptr;
                return;
            }
            this->SetMode(ShopMenuInt(this, 0x8));
        }
        break;
    case 12:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        ShopMenuFloat(this, 0x1C) = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(0xD);
        }
        break;
    case 13:
        this->SelectMake();
        if ((buttons & 0x200) != 0) {
            ShopMenuInt(this, 0x8) = 9;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(0xE);
        }
        break;
    case 14:
        ShopMenuFloat(this, 0x1C) = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(ShopMenuInt(this, 0x8));
        }
        break;
    case 15:
        if (timer == 1) {
            Sound.PlaySe(5, 0x40, 0x7F, 0);
        }
        ShopMenuFloat(this, 0x1C) = static_cast<float>(timer) * 0.125f;
        if (timer == 8) {
            short recipeMaterial[8];
            int itemId = ResolveShopMenuSelectedItemId(this);

            GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo(MenuPcsVoid(), itemId, recipeMaterial);
            AddGil__12CCaravanWorkFi(reinterpret_cast<void*>(ShopMenuCaravan(this)), -CalcShopMenuMakeGil(this, itemId));
            DeleteItem__12CCaravanWorkFii(reinterpret_cast<void*>(ShopMenuCaravan(this)), itemId, 0);

            for (int i = 0; i < 3; i++) {
                if (recipeMaterial[i] < 1) {
                    break;
                }
                for (int count = 0; count < recipeMaterial[i + 3]; count++) {
                    DeleteItem__12CCaravanWorkFii(
                        reinterpret_cast<void*>(ShopMenuCaravan(this)),
                        recipeMaterial[i],
                        0);
                }
            }

            AddItem__12CCaravanWorkFiPi(
                reinterpret_cast<void*>(ShopMenuCaravan(this)),
                static_cast<short>(ShopMenuInt(this, 0x150)),
                &ShopMenuInt(this, 0x154));
            this->SetMode(0x10);
        }
        break;
    case 16:
        if ((buttons & 0xC) != 0) {
            ShopMenuInt(this, 0x3C) ^= 1;
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((buttons & 0x100) != 0) {
            ShopMenuInt(this, 0x8) = 9;
            this->SetMode(0x11);

            if (ShopMenuInt(this, 0x3C) == 1) {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else if (ShopMenuInt(this, 0x3C) == 0) {
                int equipType = GetEquipType__8CMenuPcsFi(MenuPcsVoid(), ShopMenuInt(this, 0x150));
                ChgEquipPos__12CCaravanWorkFii(
                    reinterpret_cast<void*>(ShopMenuCaravan(this)),
                    equipType,
                    static_cast<short>(ShopMenuInt(this, 0x154)));
                Sound.PlaySe(0x51, 0x40, 0x7F, 0);
            }
        }

        if ((buttons & 0x200) != 0) {
            ShopMenuInt(this, 0x8) = 9;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            this->SetMode(0x11);
        }
        break;
    case 17:
        ShopMenuFloat(this, 0x1C) = static_cast<float>(8 - timer) * 0.125f;
        if (timer == 8) {
            this->SetMode(ShopMenuInt(this, 0x8));
        }
        break;
    }

    ++timer;
    if (timer > 8) {
        timer = 8;
    }

    if ((shopMode == 0) || (shopMode == 1)) {
        gShopMenuInputLatch = 0;
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    bool hasInput = false;
    unsigned short buttons;

    *reinterpret_cast<int*>(self + 0x44) = 1;
    int listType = *reinterpret_cast<int*>(self + 0x14);
    int itemCount;
    if (listType == 0) {
        itemCount = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + 0xBE4);
    } else if (listType == 1) {
        itemCount = 0x40;
    } else if (listType == 2) {
        itemCount = *reinterpret_cast<int*>(self + 0x4C);
    } else {
        itemCount = -1;
    }

    if (itemCount <= *reinterpret_cast<int*>(self + 0x28)) {
        if (listType == 0) {
            listType = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + 0xBE4);
        } else if (listType == 1) {
            listType = 0x40;
        } else if (listType == 2) {
            listType = *reinterpret_cast<int*>(self + 0x4C);
        } else {
            listType = -1;
        }
        *reinterpret_cast<int*>(self + 0x28) = listType - 1;
    }

    if (gShopMenuInputLatch == 0) {
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            hasInput = true;
        }
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20);
        }
    } else {
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            hasInput = true;
        }
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = Pad._4_2_;
        }
        if ((buttons & gShopMenuInputLatch) == 0) {
            gShopMenuInputLatch = 0;
        }
        hasInput = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            hasInput = true;
        }
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = Pad._8_2_;
        }
    }

    if ((buttons & 8) == 0) {
        if (gShopMenuInputLatch == 0) {
            hasInput = false;
            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                hasInput = true;
            }
            if (hasInput) {
                buttons = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                buttons = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20);
            }
        } else {
            hasInput = false;
            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                hasInput = true;
            }
            if (hasInput) {
                buttons = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                buttons = Pad._4_2_;
            }
            if ((buttons & gShopMenuInputLatch) == 0) {
                gShopMenuInputLatch = 0;
            }
            hasInput = false;
            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                hasInput = true;
            }
            if (hasInput) {
                buttons = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                buttons = Pad._8_2_;
            }
        }

        if ((buttons & 4) == 0) {
            hasInput = false;
            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                hasInput = true;
            }
            if (hasInput) {
                buttons = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                buttons = Pad._8_2_;
            }

            if ((buttons & 0x100) != 0) {
                bool canSelect = false;
                *reinterpret_cast<int*>(self + 0x38) = 0;
                *reinterpret_cast<int*>(self + 0x3C) = 0;

                listType = *reinterpret_cast<int*>(self + 0x14);
                if (listType == 0) {
                    if (*reinterpret_cast<int*>(self + 0x28) != -1) {
                        canSelect = *reinterpret_cast<short*>(
                                        *reinterpret_cast<int*>(self + 0x20) + *reinterpret_cast<int*>(self + 0x28) * 2 + 0xBE6) >=
                                    1;
                    }
                    if (canSelect) {
                        int caravan = *reinterpret_cast<int*>(self + 0x20);
                        if (*reinterpret_cast<int*>(self + 0x44) <= 0x40 - *reinterpret_cast<unsigned short*>(caravan + 0x94)) {
                            int itemNo = *reinterpret_cast<int*>(self + 0x28);
                            if (itemNo == -1) {
                                itemNo = 0;
                            } else {
                                int mode = *reinterpret_cast<int*>(self + 0x14);
                                if (mode == 0) {
                                    itemNo = *reinterpret_cast<short*>(caravan + itemNo * 2 + 0xBE6);
                                } else if (mode == 1) {
                                    itemNo = *reinterpret_cast<short*>(caravan + itemNo * 2 + 0xB6);
                                } else if (mode == 2) {
                                    int mapped = *reinterpret_cast<int*>(self + 0x50 + itemNo * 4);
                                    if (mapped == -1) {
                                        itemNo = -1;
                                    } else {
                                        itemNo = *reinterpret_cast<short*>(caravan + mapped * 2 + 0xB6);
                                    }
                                } else {
                                    itemNo = -1;
                                }

                                if (mode == 0) {
                                    if (itemNo < 1) {
                                        itemNo = 0;
                                    } else {
                                        itemNo = *reinterpret_cast<short*>(caravan + 0xBE2) *
                                                 *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                                        itemNo = itemNo / 100 + (itemNo >> 0x1F);
                                        itemNo = itemNo - (itemNo >> 0x1F);
                                    }
                                } else if (mode == 1) {
                                    if (itemNo < 1) {
                                        itemNo = 0;
                                    } else {
                                        itemNo = *reinterpret_cast<short*>(caravan + 0xBE2) *
                                                 *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                                        itemNo = itemNo / 100 + (itemNo >> 0x1F);
                                        itemNo = itemNo - (itemNo >> 0x1F);
                                        itemNo = (itemNo * 3) / 4;
                                    }
                                } else {
                                    itemNo = -1;
                                }
                                itemNo = *reinterpret_cast<int*>(self + 0x44) * itemNo;
                            }

                            int canAdd = CanAddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravan), -itemNo);
                            if (canAdd != 0) {
                                *reinterpret_cast<int*>(self + 0x10) = 1;
                                Sound.PlaySe(2, 0x40, 0x7F, 0);
                                goto update_window;
                            }
                        }
                    }
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else if (listType == 1) {
                    int itemIdx = *reinterpret_cast<int*>(self + 0x28);
                    if (itemIdx != -1) {
                        short itemNo = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + itemIdx * 2 + 0xB6);
                        if (itemNo >= 1) {
                            canSelect = false;
                            if (EquipChk__8CMenuPcsFi(MenuPcsVoid(), itemIdx) == 0) {
                                canSelect = itemNo >= 0x9F;
                            }
                        }
                    }

                    if (canSelect) {
                        *reinterpret_cast<int*>(self + 0x10) = 2;
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                    } else {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                    }
                } else if (listType == 2) {
                    int itemNo = -1;
                    if (*reinterpret_cast<int*>(self + 0x28) != -1) {
                        int mapped = *reinterpret_cast<int*>(self + 0x50 + *reinterpret_cast<int*>(self + 0x28) * 4);
                        if (mapped != -1) {
                            itemNo = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + mapped * 2 + 0xB6);
                        }
                        canSelect = itemNo >= 1;
                        if (canSelect) {
                            unsigned int bit = static_cast<unsigned int>(itemNo - 0x191);
                            int caravan = *reinterpret_cast<int*>(self + 0x20);
                            if ((*reinterpret_cast<unsigned int*>(caravan + ((itemNo - 0x191) >> 5) * 4 + 0xC08) & (1U << (bit & 0x1F))) ==
                                0) {
                                canSelect = false;
                            }
                        }
                    }

                    if (canSelect) {
                        *reinterpret_cast<int*>(self + 0x8) = 0xC;
                        int mode = *reinterpret_cast<int*>(self + 0x14);
                        int itemIdx = *reinterpret_cast<int*>(self + 0x28);
                        int smithItem;
                        if (mode == 0) {
                            smithItem = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + itemIdx * 2 + 0xBE6);
                        } else if (mode == 1) {
                            smithItem = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + itemIdx * 2 + 0xB6);
                        } else if (mode == 2) {
                            int mapped = *reinterpret_cast<int*>(self + 0x50 + itemIdx * 4);
                            if (mapped == -1) {
                                smithItem = -1;
                            } else {
                                smithItem = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + mapped * 2 + 0xB6);
                            }
                        } else {
                            smithItem = -1;
                        }

                        *reinterpret_cast<int*>(self + 0x150) = GetSmithItem__8CMenuPcsFi(MenuPcsVoid(), smithItem);
                        SetMode__9CShopMenuFi(self, 0xB);
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                    } else {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                    }
                }
            }
        } else {
            *reinterpret_cast<int*>(self + 0x28) = *reinterpret_cast<int*>(self + 0x28) + 1;
            int mode = *reinterpret_cast<int*>(self + 0x14);
            if (mode == 0) {
                mode = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + 0xBE4);
            } else if (mode == 1) {
                mode = 0x40;
            } else if (mode == 2) {
                mode = *reinterpret_cast<int*>(self + 0x4C);
            } else {
                mode = -1;
            }

            if (*reinterpret_cast<int*>(self + 0x28) < mode) {
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            } else {
                gShopMenuInputLatch = 4;
                mode = *reinterpret_cast<int*>(self + 0x14);
                if (mode == 0) {
                    mode = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + 0xBE4);
                } else if (mode == 1) {
                    mode = 0x40;
                } else if (mode == 2) {
                    mode = *reinterpret_cast<int*>(self + 0x4C);
                } else {
                    mode = -1;
                }
                *reinterpret_cast<int*>(self + 0x28) = mode - 1;
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            }
        }
    } else {
        *reinterpret_cast<int*>(self + 0x28) = *reinterpret_cast<int*>(self + 0x28) - 1;
        if (*reinterpret_cast<int*>(self + 0x28) < 0) {
            gShopMenuInputLatch = 8;
            *reinterpret_cast<int*>(self + 0x28) = 0;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }
    }

update_window:
    if (*reinterpret_cast<int*>(self + 0x28) < *reinterpret_cast<int*>(self + 0x24)) {
        *reinterpret_cast<int*>(self + 0x24) = *reinterpret_cast<int*>(self + 0x28);
    }
    if (*reinterpret_cast<int*>(self + 0x24) + *reinterpret_cast<int*>(self + 0x2C) <= *reinterpret_cast<int*>(self + 0x28)) {
        *reinterpret_cast<int*>(self + 0x24) = (*reinterpret_cast<int*>(self + 0x28) - *reinterpret_cast<int*>(self + 0x2C)) + 1;
    }
    if (*reinterpret_cast<int*>(self + 0x24) < 1) {
        *reinterpret_cast<int*>(self + 0x30) = 0;
    } else {
        *reinterpret_cast<int*>(self + 0x30) = 1;
    }

    listType = *reinterpret_cast<int*>(self + 0x14);
    if (listType == 0) {
        listType = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + 0xBE4);
    } else if (listType == 1) {
        listType = 0x40;
    } else if (listType == 2) {
        listType = *reinterpret_cast<int*>(self + 0x4C);
    } else {
        listType = -1;
    }

    if (*reinterpret_cast<int*>(self + 0x24) + *reinterpret_cast<int*>(self + 0x2C) < listType) {
        *reinterpret_cast<int*>(self + 0x34) = 1;
    } else {
        *reinterpret_cast<int*>(self + 0x34) = 0;
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    bool hasInput = false;
    unsigned short buttons;

    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        hasInput = true;
    }
    if (hasInput) {
        buttons = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        buttons = Pad._8_2_;
    }

    if ((buttons & 1) == 0) {
        hasInput = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            hasInput = true;
        }
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = Pad._8_2_;
        }

        if ((buttons & 2) == 0) {
            hasInput = false;
            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                hasInput = true;
            }
            if (hasInput) {
                buttons = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                buttons = Pad._8_2_;
            }

            if ((buttons & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7F, 0);
                *reinterpret_cast<int*>(self + 0x10) = 2;
            }
        } else {
            *reinterpret_cast<int*>(self + 0x38) = *reinterpret_cast<int*>(self + 0x38) - 1;
            if (*reinterpret_cast<int*>(self + 0x38) < 0) {
                *reinterpret_cast<int*>(self + 0x38) = 0;
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else {
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        }
    } else {
        *reinterpret_cast<int*>(self + 0x38) = *reinterpret_cast<int*>(self + 0x38) + 1;
        if (*reinterpret_cast<int*>(self + 0x38) < 2) {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else {
            *reinterpret_cast<int*>(self + 0x38) = 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        }
    }

    if (gShopMenuInputLatch == 0) {
        hasInput = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            hasInput = true;
        }
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20);
        }
    } else {
        hasInput = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            hasInput = true;
        }
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = Pad._4_2_;
        }
        if ((buttons & gShopMenuInputLatch) == 0) {
            gShopMenuInputLatch = 0;
        }

        hasInput = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            hasInput = true;
        }
        if (hasInput) {
            buttons = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            buttons = Pad._8_2_;
        }
    }

    if ((buttons & 8) == 0) {
        if (gShopMenuInputLatch == 0) {
            hasInput = false;
            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                hasInput = true;
            }
            if (hasInput) {
                buttons = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                buttons = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 0x20);
            }
        } else {
            hasInput = false;
            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                hasInput = true;
            }
            if (hasInput) {
                buttons = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                buttons = Pad._4_2_;
            }
            if ((buttons & gShopMenuInputLatch) == 0) {
                gShopMenuInputLatch = 0;
            }
            hasInput = false;
            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                hasInput = true;
            }
            if (hasInput) {
                buttons = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                buttons = Pad._8_2_;
            }
        }

        if ((buttons & 4) != 0) {
            int mode = *reinterpret_cast<int*>(self + 0x38);
            if (mode == 1) {
                *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) - 10;
                if (*reinterpret_cast<int*>(self + 0x44) < 1) {
                    *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) + 10;
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else {
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
            } else if (mode == 0) {
                *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) - 1;
                if (*reinterpret_cast<int*>(self + 0x44) < 1) {
                    gShopMenuInputLatch = 4;
                    *reinterpret_cast<int*>(self + 0x44) = 1;
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else {
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
            }
        }
    } else {
        int mode = *reinterpret_cast<int*>(self + 0x38);
        if (mode == 1) {
            *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) + 10;
            int caravan = *reinterpret_cast<int*>(self + 0x20);
            if (*reinterpret_cast<int*>(self + 0x44) <= 0x40 - *reinterpret_cast<unsigned short*>(caravan + 0x94)) {
                int itemNo = *reinterpret_cast<int*>(self + 0x28);
                if (itemNo == -1) {
                    itemNo = 0;
                } else {
                    int listType = *reinterpret_cast<int*>(self + 0x14);
                    if (listType == 0) {
                        itemNo = *reinterpret_cast<short*>(caravan + itemNo * 2 + 0xBE6);
                    } else if (listType == 1) {
                        itemNo = *reinterpret_cast<short*>(caravan + itemNo * 2 + 0xB6);
                    } else if (listType == 2) {
                        int mapped = *reinterpret_cast<int*>(self + 0x50 + itemNo * 4);
                        if (mapped == -1) {
                            itemNo = -1;
                        } else {
                            itemNo = *reinterpret_cast<short*>(caravan + mapped * 2 + 0xB6);
                        }
                    } else {
                        itemNo = -1;
                    }

                    if (listType == 0) {
                        if (itemNo < 1) {
                            itemNo = 0;
                        } else {
                            itemNo = *reinterpret_cast<short*>(caravan + 0xBE2) *
                                     *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                            itemNo = itemNo / 100 + (itemNo >> 0x1F);
                            itemNo = itemNo - (itemNo >> 0x1F);
                        }
                    } else if (listType == 1) {
                        if (itemNo < 1) {
                            itemNo = 0;
                        } else {
                            itemNo = *reinterpret_cast<short*>(caravan + 0xBE2) *
                                     *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                            itemNo = itemNo / 100 + (itemNo >> 0x1F);
                            itemNo = itemNo - (itemNo >> 0x1F);
                            itemNo = (itemNo * 3) / 4;
                        }
                    } else {
                        itemNo = -1;
                    }
                    itemNo = *reinterpret_cast<int*>(self + 0x44) * itemNo;
                }

                if (CanAddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravan), -itemNo) != 0) {
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                    return;
                }
            }
            *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) - 10;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        } else if (mode == 0) {
            *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) + 1;
            int caravan = *reinterpret_cast<int*>(self + 0x20);
            if (*reinterpret_cast<int*>(self + 0x44) <= 0x40 - *reinterpret_cast<unsigned short*>(caravan + 0x94)) {
                int itemNo = *reinterpret_cast<int*>(self + 0x28);
                if (itemNo == -1) {
                    itemNo = 0;
                } else {
                    int listType = *reinterpret_cast<int*>(self + 0x14);
                    if (listType == 0) {
                        itemNo = *reinterpret_cast<short*>(caravan + itemNo * 2 + 0xBE6);
                    } else if (listType == 1) {
                        itemNo = *reinterpret_cast<short*>(caravan + itemNo * 2 + 0xB6);
                    } else if (listType == 2) {
                        int mapped = *reinterpret_cast<int*>(self + 0x50 + itemNo * 4);
                        if (mapped == -1) {
                            itemNo = -1;
                        } else {
                            itemNo = *reinterpret_cast<short*>(caravan + mapped * 2 + 0xB6);
                        }
                    } else {
                        itemNo = -1;
                    }

                    if (listType == 0) {
                        if (itemNo < 1) {
                            itemNo = 0;
                        } else {
                            itemNo = *reinterpret_cast<short*>(caravan + 0xBE2) *
                                     *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                            itemNo = itemNo / 100 + (itemNo >> 0x1F);
                            itemNo = itemNo - (itemNo >> 0x1F);
                        }
                    } else if (listType == 1) {
                        if (itemNo < 1) {
                            itemNo = 0;
                        } else {
                            itemNo = *reinterpret_cast<short*>(caravan + 0xBE2) *
                                     *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                            itemNo = itemNo / 100 + (itemNo >> 0x1F);
                            itemNo = itemNo - (itemNo >> 0x1F);
                            itemNo = (itemNo * 3) / 4;
                        }
                    } else {
                        itemNo = -1;
                    }
                    itemNo = *reinterpret_cast<int*>(self + 0x44) * itemNo;
                }

                if (CanAddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravan), -itemNo) != 0) {
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                    return;
                }
            }
            gShopMenuInputLatch = 8;
            *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) - 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        }
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned short buttons;
    int listType;
    int itemIndex;
    int itemId;
    int gilValue;
    int i;
    int count;
    int itemBits;
    bool canExecute = false;
    int caravan = *reinterpret_cast<int*>(self + 0x20);

    buttons = GetPadButtons();
    if ((buttons & 0xC) != 0) {
        *reinterpret_cast<unsigned int*>(self + 0x3C) ^= 1;
        Sound.PlaySe(1, 0x40, 0x7F, 0);
        return;
    }

    buttons = GetPadButtons();
    if ((buttons & 0x100) == 0) {
        return;
    }

    if (*reinterpret_cast<int*>(self + 0x3C) == 1) {
        Sound.PlaySe(3, 0x40, 0x7F, 0);
        if (*reinterpret_cast<int*>(self + 0x14) == 0) {
            *reinterpret_cast<int*>(self + 0x10) = 1;
        } else {
            *reinterpret_cast<int*>(self + 0x10) = 0;
        }
        return;
    }

    *reinterpret_cast<int*>(self + 0x10) = 0;
    listType = *reinterpret_cast<int*>(self + 0x14);

    if (listType == 0) {
        Sound.PlaySe(0x50, 0x40, 0x7F, 0);
        itemIndex = *reinterpret_cast<int*>(self + 0x28);
        if (listType == 0) {
            itemId = *reinterpret_cast<short*>(caravan + itemIndex * 2 + 0xBE6);
        } else if (listType == 1) {
            itemId = *reinterpret_cast<short*>(caravan + itemIndex * 2 + 0xB6);
        } else if (listType == 2) {
            itemIndex = *reinterpret_cast<int*>(self + 0x50 + itemIndex * 4);
            if (itemIndex == -1) {
                itemId = -1;
            } else {
                itemId = *reinterpret_cast<short*>(caravan + itemIndex * 2 + 0xB6);
            }
        } else {
            itemId = -1;
        }

        i = 0;
        itemBits = itemId * 0x48;
        while ((i < *reinterpret_cast<int*>(self + 0x44)) &&
               ((unsigned short)(*reinterpret_cast<unsigned short*>(caravan + 0x94) + 1) < 0x41)) {
            if (*reinterpret_cast<int*>(self + 0x14) == 0) {
                if (itemId < 1) {
                    gilValue = 0;
                } else {
                    gilValue = *reinterpret_cast<short*>(caravan + 0xBE2) *
                               *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemBits + 0x20);
                    gilValue = gilValue / 100 + (gilValue >> 0x1F);
                    gilValue = gilValue - (gilValue >> 0x1F);
                }
            } else if (*reinterpret_cast<int*>(self + 0x14) == 1) {
                if (itemId < 1) {
                    gilValue = 0;
                } else {
                    gilValue = *reinterpret_cast<short*>(caravan + 0xBE2) *
                               *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemBits + 0x20);
                    gilValue = gilValue / 100 + (gilValue >> 0x1F);
                    gilValue = gilValue - (gilValue >> 0x1F);
                    gilValue = (gilValue * 3) / 4;
                }
            } else {
                gilValue = -1;
            }

            if (CanAddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravan), -gilValue) == 0) {
                return;
            }

            AddItem__12CCaravanWorkFiPi(reinterpret_cast<void*>(caravan), static_cast<short>(itemId), 0);

            if (*reinterpret_cast<int*>(self + 0x14) == 0) {
                if (itemId < 1) {
                    gilValue = 0;
                } else {
                    gilValue = *reinterpret_cast<short*>(caravan + 0xBE2) *
                               *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemBits + 0x20);
                    gilValue = gilValue / 100 + (gilValue >> 0x1F);
                    gilValue = gilValue - (gilValue >> 0x1F);
                }
            } else if (*reinterpret_cast<int*>(self + 0x14) == 1) {
                if (itemId < 1) {
                    gilValue = 0;
                } else {
                    gilValue = *reinterpret_cast<short*>(caravan + 0xBE2) *
                               *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemBits + 0x20);
                    gilValue = gilValue / 100 + (gilValue >> 0x1F);
                    gilValue = gilValue - (gilValue >> 0x1F);
                    gilValue = (gilValue * 3) / 4;
                }
            } else {
                gilValue = -1;
            }

            AddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravan), -gilValue);
            i = i + 1;
        }
        return;
    }

    itemIndex = *reinterpret_cast<int*>(self + 0x28);
    if (itemIndex != -1) {
        if (listType == 0) {
            itemId = *reinterpret_cast<short*>(caravan + itemIndex * 2 + 0xBE6);
        } else if (listType == 1) {
            itemId = *reinterpret_cast<short*>(caravan + itemIndex * 2 + 0xB6);
        } else if (listType == 2) {
            count = *reinterpret_cast<int*>(self + 0x50 + itemIndex * 4);
            if (count == -1) {
                itemId = -1;
            } else {
                itemId = *reinterpret_cast<short*>(caravan + count * 2 + 0xB6);
            }
        } else {
            itemId = -1;
        }

        if (itemId < 1) {
            canExecute = false;
        } else if (listType == 0) {
            canExecute = true;
        } else if (listType == 2) {
            canExecute = true;
            count = (itemId - 0x191U) & 0x1F;
            itemBits = (itemId - 0x191U) >> 5;
            if (((*reinterpret_cast<unsigned int*>(caravan + itemBits * 4 + 0xC08) & (1U << count))) == 0) {
                canExecute = false;
            }
        } else {
            if (EquipChk__8CMenuPcsFi(&MenuPcs, itemIndex) == 0) {
                canExecute = (itemId >= 0x9F);
            } else {
                canExecute = false;
            }
        }
    }

    if (!canExecute) {
        Sound.PlaySe(4, 0x40, 0x7F, 0);
        return;
    }

    Sound.PlaySe(0x50, 0x40, 0x7F, 0);
    listType = *reinterpret_cast<int*>(self + 0x14);
    itemIndex = *reinterpret_cast<int*>(self + 0x28);
    if (listType == 0) {
        itemId = *reinterpret_cast<short*>(caravan + itemIndex * 2 + 0xBE6);
    } else if (listType == 1) {
        itemId = *reinterpret_cast<short*>(caravan + itemIndex * 2 + 0xB6);
    } else if (listType == 2) {
        count = *reinterpret_cast<int*>(self + 0x50 + itemIndex * 4);
        if (count == -1) {
            itemId = -1;
        } else {
            itemId = *reinterpret_cast<short*>(caravan + count * 2 + 0xB6);
        }
    } else {
        itemId = -1;
    }

    if (listType == 0) {
        if (itemId < 1) {
            gilValue = 0;
        } else {
            gilValue = *reinterpret_cast<short*>(caravan + 0xBE2) *
                       *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
            gilValue = gilValue / 100 + (gilValue >> 0x1F);
            gilValue = gilValue - (gilValue >> 0x1F);
        }
    } else if (listType == 1) {
        if (itemId < 1) {
            gilValue = 0;
        } else {
            gilValue = *reinterpret_cast<short*>(caravan + 0xBE2) *
                       *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
            gilValue = gilValue / 100 + (gilValue >> 0x1F);
            gilValue = gilValue - (gilValue >> 0x1F);
            gilValue = (gilValue * 3) / 4;
        }
    } else {
        gilValue = -1;
    }

    if (CanAddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravan), gilValue) == 0) {
        return;
    }

    DeleteItemIdx__12CCaravanWorkFii(reinterpret_cast<void*>(caravan), *reinterpret_cast<int*>(self + 0x28), 0);

    if (*reinterpret_cast<int*>(self + 0x14) == 0) {
        if (itemId < 1) {
            itemId = 0;
        } else {
            itemId = *reinterpret_cast<short*>(caravan + 0xBE2) *
                     *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
            itemId = itemId / 100 + (itemId >> 0x1F);
            itemId = itemId - (itemId >> 0x1F);
        }
    } else if (*reinterpret_cast<int*>(self + 0x14) == 1) {
        if (itemId < 1) {
            itemId = 0;
        } else {
            itemId = *reinterpret_cast<short*>(caravan + 0xBE2) *
                     *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x20);
            itemId = itemId / 100 + (itemId >> 0x1F);
            itemId = itemId - (itemId >> 0x1F);
            itemId = (itemId * 3) / 4;
        }
    } else {
        itemId = -1;
    }

    AddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravan), itemId);
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned int canSelect;

    canSelect = ChkEquipPossible__8CMenuPcsFi(MenuPcsVoid(), *reinterpret_cast<int*>(self + 0x150)) != 0;
    if (canSelect != 0) {
        int listType = *reinterpret_cast<int*>(self + 0x14);
        int selected = *reinterpret_cast<int*>(self + 0x28);

        if (listType == 0) {
            selected = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + selected * 2 + 0xBE6);
        } else if (listType == 1) {
            selected = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + selected * 2 + 0xB6);
        } else if (listType == 2) {
            int index = *reinterpret_cast<int*>(self + 0x50 + selected * 4);
            if (index == -1) {
                selected = -1;
            } else {
                selected = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + index * 2 + 0xB6);
            }
        } else {
            selected = -1;
        }

        unsigned int money = *reinterpret_cast<unsigned int*>(*reinterpret_cast<int*>(self + 0x20) + 0x200);
        unsigned int craftGil;
        if (selected < 1) {
            craftGil = 0;
        } else {
            int gil = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + 0xBE2) *
                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + selected * 0x48 + 0x24);
            gil = gil / 100 + (gil >> 0x1F);
            craftGil = gil - (gil >> 0x1F);
        }

        canSelect = static_cast<unsigned int>(
            static_cast<int>(money >> 0x1F) + (static_cast<unsigned int>(craftGil <= money) - static_cast<int>(craftGil >> 0x1F)));
    }

    int listType = *reinterpret_cast<int*>(self + 0x14);
    canSelect &= 0xFF;
    int selected = *reinterpret_cast<int*>(self + 0x28);
    if (listType == 0) {
        selected = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + selected * 2 + 0xBE6);
    } else if (listType == 1) {
        selected = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + selected * 2 + 0xB6);
    } else if (listType == 2) {
        int index = *reinterpret_cast<int*>(self + 0x50 + selected * 4);
        if (index == -1) {
            selected = -1;
        } else {
            selected = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + index * 2 + 0xB6);
        }
    } else {
        selected = -1;
    }

    short recipeMaterial[8];
    GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo(MenuPcsVoid(), selected, recipeMaterial);
    int i = 0;
    short* material = recipeMaterial;
    do {
        short itemNo = *material;
        if (itemNo < 1) {
            break;
        }

        canSelect = static_cast<unsigned int>(-static_cast<int>(-canSelect) >> 0x1F);
        if (canSelect != 0) {
            int checkOffset = 0;
            unsigned int total = 0;
            int checkCount = 8;
            do {
                if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + checkOffset + 0xB6) == itemNo) {
                    total++;
                }
                if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + checkOffset + 0xB8) == itemNo) {
                    total++;
                }
                if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + checkOffset + 0xBA) == itemNo) {
                    total++;
                }
                if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + checkOffset + 0xBC) == itemNo) {
                    total++;
                }
                if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + checkOffset + 0xBE) == itemNo) {
                    total++;
                }
                if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + checkOffset + 0xC0) == itemNo) {
                    total++;
                }
                if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + checkOffset + 0xC2) == itemNo) {
                    total++;
                }
                if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + checkOffset + 0xC4) == itemNo) {
                    total++;
                }
                checkOffset += 0x10;
                checkCount--;
            } while (checkCount != 0);

            canSelect = static_cast<unsigned int>(
                static_cast<int>(total >> 0x1F) +
                (static_cast<unsigned int>(static_cast<unsigned int>(material[3]) <= total) - static_cast<int>(material[3] >> 0x1F)));
        }

        i++;
        canSelect &= 0xFF;
        material++;
    } while (i < 3);

    if (canSelect == 0) {
        *reinterpret_cast<int*>(self + 0x3C) = 1;
    }

    bool hasInput = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        hasInput = true;
    }

    unsigned short press;
    if (hasInput) {
        press = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        press = Pad._8_2_;
    }

    if ((press & 0xC) == 0) {
        hasInput = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            hasInput = true;
        }

        if (hasInput) {
            press = 0;
        } else {
            __cntlzw(static_cast<unsigned int>(Pad._448_4_));
            press = Pad._8_2_;
        }

        if ((press & 0x100) != 0) {
            int yesNo = *reinterpret_cast<int*>(self + 0x3C);
            if (yesNo != 1) {
                if (yesNo > 0) {
                    return;
                }
                if (yesNo < 0) {
                    return;
                }

                int mode = *reinterpret_cast<int*>(self + 0x14);
                int itemIdx = *reinterpret_cast<int*>(self + 0x28);
                if (mode == 0) {
                    itemIdx = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + itemIdx * 2 + 0xBE6);
                } else if (mode == 1) {
                    itemIdx = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + itemIdx * 2 + 0xB6);
                } else if (mode == 2) {
                    int index = *reinterpret_cast<int*>(self + 0x50 + itemIdx * 4);
                    if (index == -1) {
                        itemIdx = -1;
                    } else {
                        itemIdx = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + index * 2 + 0xB6);
                    }
                } else {
                    itemIdx = -1;
                }

                if (itemIdx < 1) {
                    itemIdx = 0;
                } else {
                    int gil = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + 0xBE2) *
                              *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemIdx * 0x48 + 0x24);
                    gil = gil / 100 + (gil >> 0x1F);
                    itemIdx = gil - (gil >> 0x1F);
                }

                int canAdd = CanAddGil__12CCaravanWorkFi(reinterpret_cast<void*>(*reinterpret_cast<int*>(self + 0x20)), -itemIdx);
                if (canAdd != 0) {
                    Sound.PlaySe(0x52, 0x40, 0x7F, 0);
                    *reinterpret_cast<int*>(self + 0x8) = 0xF;
                    SetMode__9CShopMenuFi(self, 0xE);
                    return;
                }
            }

            Sound.PlaySe(4, 0x40, 0x7F, 0);
            *reinterpret_cast<int*>(self + 0x8) = 9;
            SetMode__9CShopMenuFi(self, 0xE);
        }
    } else {
        *reinterpret_cast<unsigned int*>(self + 0x3C) ^= 1;
        if (canSelect == 1) {
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else {
            *reinterpret_cast<int*>(self + 0x3C) = 1;
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::SelectSOUBI()
{
    unsigned short buttons = GetPadButtons();
    if ((buttons & 0xC) != 0) {
        ShopMenuInt(this, 0x3C) ^= 1;
        Sound.PlaySe(1, 0x40, 0x7F, 0);
        return;
    }

    if ((buttons & 0x200) != 0) {
        Sound.PlaySe(3, 0x40, 0x7F, 0);
        ShopMenuInt(this, 0x8) = 9;
        SetMode__9CShopMenuFi(this, 0xE);
        return;
    }

    if ((buttons & 0x100) == 0) {
        return;
    }

    if (ShopMenuInt(this, 0x3C) != 0) {
        Sound.PlaySe(3, 0x40, 0x7F, 0);
        ShopMenuInt(this, 0x8) = 9;
        SetMode__9CShopMenuFi(this, 0xE);
        return;
    }

    if (ChkEquipPossible__8CMenuPcsFi(MenuPcsVoid(), ShopMenuInt(this, 0x150)) != 0) {
        Sound.PlaySe(0x52, 0x40, 0x7F, 0);
        ShopMenuInt(this, 0x8) = 0xF;
        SetMode__9CShopMenuFi(this, 0xE);
    } else {
        Sound.PlaySe(4, 0x40, 0x7F, 0);
        ShopMenuInt(this, 0x3C) = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawShop0()
{
    DrawShopBase();

    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    RefreshShopMenuTabLabels();
    int selected = ShopMenuInt(this, 0x48);

    CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x248);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetShadow__5CFontFi(font, 1);
    SetScale__5CFontFf(FLOAT_80332d8c, font);

    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    SetColor__5CFontF8_GXColor(font, &white);

    for (int i = 0; i < 3; i++) {
        int x = s_shopMenuTabLayout[i][0];
        int y = s_shopMenuTabLayout[i][1];
        int highlight = (i == selected) ? 1 : 0;

        SetDrawDoneDebugData__8CGraphicFSc(&Graphic, static_cast<signed char>(0x1E + i));
        drawShapeSeq(0, highlight, x, y, 0xFF, 0, 0, 0.0f, 0);
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic, static_cast<signed char>(0x21 + i));
        drawShapeSeq(8, highlight, x - 0x30, y, 0xFF, 0, 0, 0.0f, 0);

        DrawInit__5CFontFv(font);
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
            MenuPcsVoid(), font, const_cast<char*>(s_shopMenuTabLabels[i]),
            static_cast<float>(x + 0x48), static_cast<float>(y - 0x0B),
            highlight != 0 ? 0x18 : 9, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());
    }

    SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x24);
    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, PTR_DAT_80214d9c[languageId], FLOAT_80332d54, 88.0f, 9, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x28);
    DrawCursor__8CMenuPcsFiif(MenuPcsVoid(), 0xA8, 0x9C + selected * 0x24, 1.0f);
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
    DrawItemHelp(ShopMenuInt(this, 0x28), 0x140, 0x172);

    CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x248);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetShadow__5CFontFi(font, 1);
    SetScale__5CFontFf(FLOAT_80332d8c, font);

    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    SetColor__5CFontF8_GXColor(font, &white);
    DrawInit__5CFontFv(font);

    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    int caravan = ShopMenuInt(this, 0x20);
    const char* title = PTR_s_Blacksmith_80214da0[languageId];
    if (*reinterpret_cast<char*>(caravan + 0xBE1) != '\0') {
        title = GetJobStr__8CMenuPcsFi(reinterpret_cast<CMenuPcs*>(MenuPcsVoid()), 1);
    }
    if (title == 0) {
        title = "";
    }

    float textX = 264.0f - GetWidth__5CFontFPc(font, title);

    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, const_cast<char*>(title), textX, FLOAT_80332e4c, 9, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());
    DrawInit__8CMenuPcsFv(MenuPcsVoid());
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawMake()
{
    DrawMakeBase();

    int resultItem = ShopMenuInt(this, 0x150);
    int selectedItem = getItemNo(ShopMenuInt(this, 0x28));
    int makeGil = getMakeGil(selectedItem);
    int currentMoney = *reinterpret_cast<int*>(ShopMenuCaravan(this) + 0x200);
    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;

    drawShapeSeq(0xF, 0, 0xA8, 0x4A, 0xFF, 0, 0, 0.0f, 0);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());
    DrawSingleIcon__8CMenuPcsFiiifif(MenuPcsVoid(), resultItem, 0x40, 0x32, 0.0f, FLOAT_80332d28, FLOAT_80332d28);

    CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x248);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetShadow__5CFontFi(font, 1);
    SetScale__5CFontFf(FLOAT_80332d28, font);
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    SetColor__5CFontF8_GXColor(font, &white);

    const char* itemName = GetItemName(resultItem);
    DrawInit__5CFontFv(font);
    DrawShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, const_cast<char*>(itemName), FLOAT_80332d54, 108.0f, 0x18, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    char raceBuffer[64];
    GetRaceStr__8CMenuPcsFiPc(MenuPcsVoid(), resultItem, raceBuffer);
    const int raceColor = (ChkEquipPossible__8CMenuPcsFi(MenuPcsVoid(), resultItem) != 0) ? 0x18 : 2;

    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, PTR_DAT_80214da8[languageId], 176.0f, 120.0f, 0x18, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    float raceX = 176.0f + FLOAT_80332d5c + GetWidth__5CFontFPc(font, PTR_DAT_80214da8[languageId]);
    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, raceBuffer, raceX, 120.0f, raceColor, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    char buffer[64];
    sprintf(buffer, DAT_80332d14, makeGil);
    float valueRightX = 308.0f;
    float makeGilX = valueRightX - GetWidth__5CFontFPc(font, buffer);
    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, buffer, makeGilX, 132.0f, 0x13, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    sprintf(buffer, DAT_80332d14, currentMoney);
    float moneyX = valueRightX - GetWidth__5CFontFPc(font, buffer);
    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, PTR_s_Money_80214db0[languageId], 176.0f, 148.0f, 0x18, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());
    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, buffer, moneyX, 160.0f, (makeGil <= currentMoney) ? 0x14 : 2, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    DrawItemInfo(resultItem, 0x98, 0x7E, 0, 0x9C, 0, 0, 0);
    DrawItemHelp(ShopMenuInt(this, 0x28), 0x140, 0x172);
    DrawCursor__8CMenuPcsFiif(MenuPcsVoid(), 0xD8, ShopMenuInt(this, 0x3C) * 0x18 + 0x13C, 1.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawSoubi()
{
    DrawSoubiBase();

    drawShapeSeq(0xF, 0, 0xA8, 0x5A, 0xFF, 0, 0, 0.0f, 0);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());
    DrawSingleIcon__8CMenuPcsFiiifif(MenuPcsVoid(), ShopMenuInt(this, 0x150), 0x40, 0x42, 0.0f, FLOAT_80332d28, FLOAT_80332d28);

    CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x248);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetShadow__5CFontFi(font, 1);
    SetScale__5CFontFf(FLOAT_80332d28, font);

    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    SetColor__5CFontF8_GXColor(font, &white);
    DrawInit__5CFontFv(font);
    DrawShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, GetItemName(ShopMenuInt(this, 0x150)), FLOAT_80332d54, 112.0f, 0x18, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    DrawItemInfo(ShopMenuInt(this, 0x150), 0x98, 0x7E, 0, 0x9C, 0, 0, 0);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    int barX = 0x1F6;
    while (barX > 0x42) {
        drawShapeSeq(0xC, 0, barX, 0x17C, 0xFF, 0, 0, 0.0f, 0);
        barX -= 0x10;
    }
    drawShapeSeq(0xB, 0, 0x226, 0x158, 0xFF, 0, 0, 0.0f, 0);
    drawShapeSeq(1, 1, barX, 0x17C, 0xFF, 0, 0, 0.0f, 0);

    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    CFont* labelFont = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x264);
    SetMargin__5CFontFf(FLOAT_80332d28, labelFont);
    SetShadow__5CFontFi(labelFont, 0);
    SetScaleX__5CFontFf(FLOAT_80332d2c, labelFont);
    SetScaleY__5CFontFf(FLOAT_80332d28, labelFont);
    SetColor__5CFontF8_GXColor(labelFont, &white);

    char* equipText = PTR_s_Equip_80214dc0[languageId];
    float equipTextX = CalcCenteredShopMenuX(labelFont, equipText);
    DrawInit__5CFontFv(labelFont);
    SetPosX__5CFontFf(equipTextX, labelFont);
    SetPosY__5CFontFf(312.0f, labelFont);
    Draw__5CFontFPc(labelFont, equipText);

    char* cancelText = PTR_s_Cancel_80214d98[languageId];
    float cancelTextX = CalcCenteredShopMenuX(labelFont, cancelText);
    DrawInit__5CFontFv(labelFont);
    SetPosX__5CFontFf(cancelTextX, labelFont);
    SetPosY__5CFontFf(346.0f, labelFont);
    Draw__5CFontFPc(labelFont, cancelText);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    DrawCursor__8CMenuPcsFiif(MenuPcsVoid(), 0xD8, ShopMenuInt(this, 0x3C) * 0x18 + 0x13C, 1.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Draw()
{
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x46);
    int pdtSlot = ShopMenuInt(this, 0x18);
    if ((pdtSlot >= 0) && (pdtSlot < static_cast<int>(sizeof(PartMng.m_pdtSlots) / sizeof(PartMng.m_pdtSlots[0])))) {
        pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(PartMng.m_pdtSlots[pdtSlot].m_envFields);
    }

    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    int mode = ShopMenuInt(this, 0x0);
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

    DrawShopMenuFadeOverlay(ShopMenuFloat(this, 0x1C));
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x3C);
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
void CShopMenu::DrawShopBase()
{
    DrawSingleBase__8CMenuPcsFf(reinterpret_cast<CMenuPcs*>(MenuPcsVoid()), 1.0f);
    pppInitDrawEnv(0);

    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)11, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)13, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetChanCtrl((GXChannelID)2, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);

    int mode = ShopMenuInt(this, 0x0);
    int panelBottom = 0x108;
    if ((mode >= 3) && (mode < 9)) {
        panelBottom = 0x176;
    } else if ((mode >= 9) && (mode < 0xC)) {
        panelBottom = 0x13A;
    } else if (mode >= 0xC) {
        panelBottom = 0x10C;
    }

    _GXColor fadeA = {0xFF, 0xFF, 0xFF, 0x00};
    _GXColor fadeB = {0xFF, 0xFF, 0xFF, 0xFF};
    _GXColor fadeC = {0xFF, 0xFF, 0xFF, 0x00};
    _GXColor fadeD = {0xFF, 0xFF, 0xFF, 0xFF};
    drawShapeSeqGrouad(9, 0, 0x1C, panelBottom, 0.5f, 0.7f, fadeA, fadeB, fadeC, fadeD);

    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    int x = 0x3C;
    while (x < 0x25C) {
        drawShapeSeqGrouad(9, 0, x, panelBottom, 0.5f, 0.7f, white, white, white, white);
        x += 0x20;
    }

    _GXColor endA = {0xFF, 0xFF, 0xFF, 0xFF};
    _GXColor endB = {0xFF, 0xFF, 0xFF, 0x00};
    _GXColor endC = {0xFF, 0xFF, 0xFF, 0xFF};
    _GXColor endD = {0xFF, 0xFF, 0xFF, 0x00};
    drawShapeSeqGrouad(9, 0, x, panelBottom, 0.5f, 0.7f, endA, endB, endC, endD);

    if ((mode >= 3) && (mode < 0xC)) {
        int listX = (mode < 9) ? 0x64 : 0x118;
        for (int barX = listX + 0x48; barX < 0x244; barX += 8) {
            drawShapeSeq(0x10, 0, barX, 0x11E, 0xFF, 0, 0, 0.0f, 0);
        }
        drawShapeSeq(0xD, 0, listX + 0x46, 0xA7, 0xFF, 0, 0, 0.0f, 0);
        drawShapeSeq(8, 0, 0x244, 0x11E, 0xFF, 0, 0, 0.0f, 0);
    }

    if ((mode >= 3) && (mode < 9)) {
        for (int sideX = 0x4E; sideX > 0x32; sideX -= 0x10) {
            drawShapeSeq(0xC, 0, sideX, 0x174, 0xFF, 0, 0, 0.0f, 0);
        }
        drawShapeSeq(0xB, 0, 0x7E, 0x150, 0xFF, 0, 0, 0.0f, 0);
        drawShapeSeq(8, 0, 0x2E, 0x170, 0xFF, 0, 0, 0.0f, 0);

        int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
        CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x264);
        SetMargin__5CFontFf(FLOAT_80332d28, font);
        SetShadow__5CFontFi(font, 0);
        SetScaleX__5CFontFf(FLOAT_80332d2c, font);
        SetScaleY__5CFontFf(FLOAT_80332d28, font);
        SetColor__5CFontF8_GXColor(font, &white);

        char* confirmText = (ShopMenuInt(this, 0x14) == 0) ? PTR_DAT_80214d90[languageId] : PTR_DAT_80214d94[languageId];
        float confirmTextX = CalcCenteredShopMenuX(font, confirmText);
        DrawInit__5CFontFv(font);
        SetPosX__5CFontFf(confirmTextX, font);
        SetPosY__5CFontFf(312.0f, font);
        Draw__5CFontFPc(font, confirmText);

        float cancelTextX = CalcCenteredShopMenuX(font, PTR_s_Cancel_80214d98[languageId]);
        DrawInit__5CFontFv(font);
        SetPosX__5CFontFf(cancelTextX, font);
        SetPosY__5CFontFf(346.0f, font);
        Draw__5CFontFPc(font, PTR_s_Cancel_80214d98[languageId]);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());

        if (ShopMenuInt(this, 0x10) == 2) {
            DrawCursor__8CMenuPcsFiif(MenuPcsVoid(), 0x2C, ShopMenuInt(this, 0x3C) * 0x18 + 0x134, 1.0f);
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
    DrawSingleBase__8CMenuPcsFf(reinterpret_cast<CMenuPcs*>(MenuPcsVoid()), 1.0f);
    pppInitDrawEnv(0);

    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)11, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)13, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetChanCtrl((GXChannelID)2, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);

    _GXColor colorA = {0xFF, 0xFF, 0xFF, 0x00};
    _GXColor colorB = {0xFF, 0xFF, 0xFF, 0xFF};
    _GXColor colorC = {0xFF, 0xFF, 0xFF, 0x00};
    _GXColor colorD = {0xFF, 0xFF, 0xFF, 0xFF};
    drawShapeSeqGrouad(9, 0, 0x1C, 0xB8, 0.5f, 0.7f, colorA, colorB, colorC, colorD);

    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    int x = 0x3C;
    while (x < 0x25C) {
        drawShapeSeqGrouad(9, 0, x, 0xB8, 0.5f, 0.7f, white, white, white, white);
        x += 0x20;
    }

    _GXColor endA = {0xFF, 0xFF, 0xFF, 0xFF};
    _GXColor endB = {0xFF, 0xFF, 0xFF, 0x00};
    _GXColor endC = {0xFF, 0xFF, 0xFF, 0xFF};
    _GXColor endD = {0xFF, 0xFF, 0xFF, 0x00};
    drawShapeSeqGrouad(9, 0, x, 0xB8, 0.5f, 0.7f, endA, endB, endC, endD);

    drawShapeSeq(3, 0, 0xB4, 0x8C, 0xFF, 0, 0, 0.0f, 0);
    x = 0xB4;
    while (x < 0x1CC) {
        drawShapeSeq(4, 0, x, 0x8C, 0xFF, 0, 0, 0.0f, 0);
        x += 0x20;
    }
    drawShapeSeq(3, 0, x, 0x8C, 0xFF, 1, 0, 0.0f, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawSoubiBase()
{
    DrawSingleBase__8CMenuPcsFf(reinterpret_cast<CMenuPcs*>(MenuPcsVoid()), 1.0f);
    pppInitDrawEnv(0);

    _GXColor fadeA = {0xFF, 0xFF, 0xFF, 0x00};
    _GXColor fadeB = {0xFF, 0xFF, 0xFF, 0xFF};
    _GXColor fadeC = {0xFF, 0xFF, 0xFF, 0x00};
    _GXColor fadeD = {0xFF, 0xFF, 0xFF, 0xFF};
    drawShapeSeqGrouad(9, 0, 0x1C, 0x10C, 0.5f, 0.7f, fadeA, fadeB, fadeC, fadeD);

    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    int x = 0x3C;
    while (x < 0x25C) {
        drawShapeSeqGrouad(9, 0, x, 0x10C, 0.5f, 0.7f, white, white, white, white);
        x += 0x20;
    }
    drawShapeSeqGrouad(9, 0, x, 0x10C, 0.5f, 0.7f, white, fadeA, white, fadeC);

    drawShapeSeqScale(3, 0, 0x106, 0xA4, FLOAT_80332d78, 0.7f, 0xFF);
    x = 0x106;
    while (x < 0x17A) {
        drawShapeSeqScale(4, 0, x, 0xA4, FLOAT_80332d78, 0.7f, 0xFF);
        x += 0x20;
    }
    drawShapeSeqScale(3, 0, x, 0xA4, FLOAT_80332dd0, 0.7f, 0xFF);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawObi(int)
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
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawItemList()
{
    int itemIndex = ShopMenuInt(this, 0x24);
    int y = 0x4C;
    int visibleCount = ShopMenuInt(this, 0x2C);
    int selectableFrame = (ShopMenuInt(this, 0x14) == 2) ? 0xF : 0xA;

    CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x264);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetShadow__5CFontFi(font, 0);
    SetScale__5CFontFf(FLOAT_80332d28, font);

    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    SetColor__5CFontF8_GXColor(font, &white);

    for (int row = 0; row < visibleCount; row++, itemIndex++, y += 0x1C) {
        if (itemIndex >= ResolveShopMenuItemCount(this)) {
            break;
        }

        int itemNo = ResolveShopMenuItemNo(this, itemIndex);
        bool canTrade = CanTradeShopMenuItem(this, itemIndex, itemNo);
        int frame = canTrade ? selectableFrame : 0xE;
        int frameX;
        if (ShopMenuInt(this, 0x28) == itemIndex) {
            frameX = 0x198;
            drawShapeSeq(frame, 1, frameX, y - 4, 0xFF, 0, 0, 0.0f, 0);
            DrawInit__8CMenuPcsFv(MenuPcsVoid());
            if (ShopMenuInt(this, 0x10) == 0) {
                DrawCursor__8CMenuPcsFiif(MenuPcsVoid(), 0x114 + (System.m_frameCounter & 7), y - 0x14, 1.0f);
            } else if ((System.m_frameCounter & 1) == 0) {
                DrawCursor__8CMenuPcsFiif(MenuPcsVoid(), 0x114, y - 0x14, 1.0f);
            }
        } else {
            frameX = 0x1B8;
            drawShapeSeq(frame, 0, frameX, y, 0xFF, 0, 0, 0.0f, 0);
        }

        if (itemNo > 0) {
            DrawInit__5CFontFv(font);
            SetPosX__5CFontFf(static_cast<float>(frameX - 0x54), font);
            SetPosY__5CFontFf(static_cast<float>(y - 0x14), font);
            Draw__5CFontFPc(font, GetItemName(itemNo));
            DrawInit__8CMenuPcsFv(MenuPcsVoid());
            DrawSingleIcon__8CMenuPcsFiiifif(
                MenuPcsVoid(), itemNo, frameX + 0x54, y - 0x18, 0.0f, FLOAT_80332d28, FLOAT_80332d28);
        }
    }

    int alpha = 0xC0 + (System.m_frameCounter & 0x3F);
    if (ShopMenuInt(this, 0x30) != 0) {
        drawShapeSeqScale(2, 0, 0x24E, 0x6A, 1.0f, -1.0f, alpha);
    }
    if (ShopMenuInt(this, 0x34) != 0) {
        drawShapeSeqScale(2, 0, 0x24E, 0xEC, 1.0f, 1.0f, alpha);
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x248);
    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;

    DrawInit__5CFontFv(font);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetShadow__5CFontFi(font, 1);
    SetScaleX__5CFontFf(FLOAT_80332d28, font);
    SetScaleY__5CFontFf(FLOAT_80332d28, font);

    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    SetColor__5CFontF8_GXColor(font, &white);

    char* priceText = PTR_s_Price_80214dc4[languageId];
    float priceWidth = GetWidth__5CFontFPc(font, priceText);
    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, priceText, FLOAT_80332d7c - priceWidth, FLOAT_80332d80, 0x13, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, DAT_80332d84, FLOAT_80332d7c, FLOAT_80332d80, 0x18, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    char* moneyText = PTR_s_Money_80214db0[languageId];
    float separatorWidth = GetWidth__5CFontFPc(font, DAT_80332d84);
    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, moneyText, FLOAT_80332d7c + separatorWidth, FLOAT_80332d80, 0x14, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    DrawInit__5CFontFv(font);
    SetScaleX__5CFontFf(FLOAT_80332d2c, font);
    SetScaleY__5CFontFf(FLOAT_80332d28, font);
    SetMargin__5CFontFf(FLOAT_80332d28, font);

    char* unitText = PTR_DAT_80214da8[languageId];
    float unitWidth = GetWidth__5CFontFPc(font, unitText);

    int selected = *reinterpret_cast<int*>(self + 0x28);
    int listType = *reinterpret_cast<int*>(self + 0x14);

    int itemNo = -1;
    if (selected != -1) {
        if (listType == 0) {
            itemNo = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + selected * 2 + 0xBE6);
        } else if (listType == 1) {
            itemNo = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + selected * 2 + 0xB6);
        } else if (listType == 2) {
            int mapped = *reinterpret_cast<int*>(self + 0x50 + selected * 4);
            if (mapped != -1) {
                itemNo = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + mapped * 2 + 0xB6);
            }
        }
    }

    bool canTrade = false;
    if (itemNo >= 1) {
        if (listType == 0) {
            canTrade = true;
        } else if (listType == 2) {
            unsigned int bit = static_cast<unsigned int>(itemNo - 0x191);
            int caravan = *reinterpret_cast<int*>(self + 0x20);
            canTrade = (*reinterpret_cast<unsigned int*>(caravan + ((itemNo - 0x191) >> 5) * 4 + 0xC08) &
                        (1U << (bit & 0x1F))) != 0;
        } else {
            if (EquipChk__8CMenuPcsFi(MenuPcsVoid(), selected) == 0) {
                canTrade = itemNo >= 0x9F;
            }
        }
    }

    int totalGil = 0;
    if (canTrade) {
        int unitGil = 0;
        int caravan = *reinterpret_cast<int*>(self + 0x20);
        if (listType == 0) {
            unitGil = *reinterpret_cast<short*>(caravan + 0xBE2) *
                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
            unitGil = unitGil / 100 + (unitGil >> 0x1F);
            unitGil = unitGil - (unitGil >> 0x1F);
        } else if (listType == 1) {
            unitGil = *reinterpret_cast<short*>(caravan + 0xBE2) *
                      *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
            unitGil = unitGil / 100 + (unitGil >> 0x1F);
            unitGil = unitGil - (unitGil >> 0x1F);
            unitGil = static_cast<int>(FLOAT_80332d60 * static_cast<float>(unitGil));
        }
        totalGil = *reinterpret_cast<int*>(self + 0x44) * unitGil;
    }

    char amountBuffer[64];
    float rightPrice = FLOAT_80332d88 - unitWidth;
    float amountRightPrice = rightPrice - FLOAT_80332d5c;

    SetShadow__5CFontFi(font, 1);
    SetScaleX__5CFontFf(FLOAT_80332d28, font);
    SetScaleY__5CFontFf(FLOAT_80332d8c, font);
    SetColor__5CFontF8_GXColor(font, &white);
    DrawInit__5CFontFv(font);
    reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
    SetMargin__5CFontFf(FLOAT_80332d64, font);
    sprintf(amountBuffer, DAT_80332d14, totalGil);
    float amountWidth = GetWidth__5CFontFPc(font, amountBuffer);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, amountBuffer, amountRightPrice - amountWidth, FLOAT_80332d90, 0x13, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    float rightMoney = FLOAT_80332d94 - unitWidth;
    float amountRightMoney = rightMoney - FLOAT_80332d5c;
    int currentMoney = *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x20) + 0x200);
    SetShadow__5CFontFi(font, 1);
    SetScaleX__5CFontFf(FLOAT_80332d28, font);
    SetScaleY__5CFontFf(FLOAT_80332d8c, font);
    SetColor__5CFontF8_GXColor(font, &white);
    DrawInit__5CFontFv(font);
    reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
    SetMargin__5CFontFf(FLOAT_80332d64, font);
    sprintf(amountBuffer, DAT_80332d14, currentMoney);
    amountWidth = GetWidth__5CFontFPc(font, amountBuffer);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, amountBuffer, amountRightMoney - amountWidth, FLOAT_80332d90, 0x14, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    DrawInit__5CFontFv(font);
    SetScaleX__5CFontFf(FLOAT_80332d2c, font);
    SetScaleY__5CFontFf(FLOAT_80332d28, font);
    SetMargin__5CFontFf(FLOAT_80332d28, font);

    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, unitText, rightPrice, FLOAT_80332d98, 0x19, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, DAT_80332d84, FLOAT_80332d7c, FLOAT_80332d98, 0x1B, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, unitText, rightMoney, FLOAT_80332d98, 0x19, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    int selected = *reinterpret_cast<int*>(self + 0x28);
    if (selected == -1) {
        return;
    }

    int listType = *reinterpret_cast<int*>(self + 0x14);
    int caravan = *reinterpret_cast<int*>(self + 0x20);
    int itemNo = -1;
    if (listType == 0) {
        itemNo = *reinterpret_cast<short*>(caravan + selected * 2 + 0xBE6);
    } else if (listType == 1) {
        itemNo = *reinterpret_cast<short*>(caravan + selected * 2 + 0xB6);
    } else if (listType == 2) {
        int mapped = *reinterpret_cast<int*>(self + 0x50 + selected * 4);
        if (mapped != -1) {
            itemNo = *reinterpret_cast<short*>(caravan + mapped * 2 + 0xB6);
        }
    }

    int languageId = static_cast<int>(Game.m_gameWork.m_languageId) - 1;
    DrawInit__8CMenuPcsFv(MenuPcsVoid());
    if (itemNo > 0) {
        DrawSingleIcon__8CMenuPcsFiiifif(MenuPcsVoid(), itemNo, 0x40, 100, 0.0f, FLOAT_80332d28, FLOAT_80332d28);
    }

    CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x248);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetShadow__5CFontFi(font, 1);
    SetScaleX__5CFontFf(FLOAT_80332d2c, font);
    SetScaleY__5CFontFf(FLOAT_80332d28, font);
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    SetColor__5CFontF8_GXColor(font, &white);
    DrawInit__5CFontFv(font);

    if (itemNo > 0) {
        SetMargin__5CFontFf(FLOAT_80332d28, font);
        char* itemName = (char*)0;
        if (itemNo >= 1) {
            itemName = reinterpret_cast<char*>(reinterpret_cast<int*>(Game.unkCFlatData0[1])[itemNo * 5 + 4]);
        }
        DrawInit__5CFontFv(font);
        DrawShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, itemName, FLOAT_80332d54, FLOAT_80332d58, 0x18, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());
        SetMargin__5CFontFf(FLOAT_80332d28, font);
    }

    bool canTrade = false;
    if (itemNo > 0) {
        if (listType == 0) {
            canTrade = true;
        } else if (listType == 2) {
            unsigned int bit = static_cast<unsigned int>(itemNo - 0x191);
            canTrade = (*reinterpret_cast<unsigned int*>(caravan + ((itemNo - 0x191) >> 5) * 4 + 0xC08) &
                        (1U << (bit & 0x1F))) != 0;
        } else {
            if (EquipChk__8CMenuPcsFi(MenuPcsVoid(), selected) == 0) {
                canTrade = itemNo >= 0x9F;
            }
        }
    }

    if (canTrade) {
        SetMargin__5CFontFf(FLOAT_80332d28, font);
        char* unitText = PTR_DAT_80214da8[languageId];
        float unitWidth = GetWidth__5CFontFPc(font, unitText);
        float rightX = FLOAT_80332d3c - unitWidth;
        float amountRightX = rightX - FLOAT_80332d5c;

        int unitGil = -1;
        if (listType == 0) {
            if (itemNo > 0) {
                unitGil = *reinterpret_cast<short*>(caravan + 0xBE2) *
                          *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                unitGil = unitGil / 100 + (unitGil >> 0x1F);
                unitGil = unitGil - (unitGil >> 0x1F);
            } else {
                unitGil = 0;
            }
        } else if (listType == 1) {
            if (itemNo > 0) {
                unitGil = *reinterpret_cast<short*>(caravan + 0xBE2) *
                          *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                unitGil = unitGil / 100 + (unitGil >> 0x1F);
                unitGil = unitGil - (unitGil >> 0x1F);
                unitGil = static_cast<int>(FLOAT_80332d60 * static_cast<float>(unitGil));
            } else {
                unitGil = 0;
            }
        }

        int totalGil = *reinterpret_cast<int*>(self + 0x44) * unitGil;
        SetShadow__5CFontFi(font, 1);
        SetScale__5CFontFf(FLOAT_80332d28, font);
        SetColor__5CFontF8_GXColor(font, &white);
        DrawInit__5CFontFv(font);
        reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
        SetMargin__5CFontFf(FLOAT_80332d64, font);
        char amountBuffer[64];
        sprintf(amountBuffer, DAT_80332d14, totalGil);
        float amountWidth = GetWidth__5CFontFPc(font, amountBuffer);
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
            MenuPcsVoid(), font, amountBuffer, amountRightX - amountWidth, FLOAT_80332d68, 0x1B, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());

        SetMargin__5CFontFf(FLOAT_80332d28, font);
        DrawInit__5CFontFv(font);
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, unitText, rightX, FLOAT_80332d68, 0x19, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());
    } else {
        SetMargin__5CFontFf(FLOAT_80332d28, font);
        char* message = (listType == 0) ? PTR_s_Cannot_buy_80214dc8[languageId] : PTR_s_Cannot_sell_80214dcc[languageId];
        float width = GetWidth__5CFontFPc(font, message);
        DrawInit__5CFontFv(font);
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
            MenuPcsVoid(), font, message, FLOAT_80332d3c - width, FLOAT_80332d68, 0x19, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());
        SetMargin__5CFontFf(FLOAT_80332d28, font);
    }

    if (*reinterpret_cast<int*>(self + 0x10) == 0) {
        DrawItemInfo(itemNo, 0, 0xA8, 0, 0xC6, 0, 0, 0);
    }

    if ((*reinterpret_cast<int*>(self + 0x10) == 1) && (listType == 0)) {
        int amount = *reinterpret_cast<int*>(self + 0x44);
        SetShadow__5CFontFi(font, 1);
        SetScale__5CFontFf(FLOAT_80332d28, font);
        SetColor__5CFontF8_GXColor(font, &white);
        DrawInit__5CFontFv(font);
        reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
        SetMargin__5CFontFf(FLOAT_80332d34, font);

        char countBuffer[64];
        sprintf(countBuffer, DAT_80332d18, amount);
        float countWidth = GetWidth__5CFontFPc(font, countBuffer);
        float countRightX = 116.0f - countWidth;
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, countBuffer, countRightX, FLOAT_80332d6c, 4, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());

        DrawInit__5CFontFv(font);
        SetScale__5CFontFf(FLOAT_80332d28, font);
        SetMargin__5CFontFf(FLOAT_80332d28, font);
        char* quantityText = PTR_s_Quantity_80214dd0[languageId];
        float quantityWidth = GetWidth__5CFontFPc(font, quantityText);
        DrawInit__5CFontFv(font);
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
            MenuPcsVoid(), font, quantityText, countRightX - quantityWidth - FLOAT_80332d5c, FLOAT_80332d6c, 0x18, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());

        int x = static_cast<int>(-(*reinterpret_cast<int*>(self + 0x38) * FLOAT_80332d74 - FLOAT_80332d70));
        drawShapeSeqScale(0x12, 0, x, 0xD4, FLOAT_80332d78, FLOAT_80332d78, 0xFF);
    }
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

    if ((itemNo <= 0) || (itemNo >= 0x9F)) {
        return;
    }

    CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0xF8);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetShadow__5CFontFi(font, 1);
    SetScaleX__5CFontFf(FLOAT_80332d2c, font);
    SetScaleY__5CFontFf(FLOAT_80332d28, font);
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    SetColor__5CFontF8_GXColor(font, &white);
    DrawInit__5CFontFv(font);

    int languageId = static_cast<unsigned int>(Game.m_gameWork.m_languageId);
    int equipType = GetEquipType__8CMenuPcsFi(MenuPcsVoid(), itemNo);
    int statType;
    char* label = 0;
    if (equipType == 0) {
        statType = 0;
        label = PTR_s_Strength_80214dd4[(languageId - 1) * 0x15];
    } else {
        equipType = GetEquipType__8CMenuPcsFi(MenuPcsVoid(), itemNo);
        if (equipType == 3) {
            statType = 2;
        } else {
            statType = 1;
            label = PTR_s_Defence_80214dd8[(languageId - 1) * 0x15];
        }
    }

    int itemData = Game.unkCFlatData0[2] + itemNo * 0x48;
    unsigned short statValue = *reinterpret_cast<unsigned short*>(itemData + 6);
    unsigned int attr = *reinterpret_cast<unsigned short*>(itemData + 8);
    char textBuffer[256];

    if (label == 0) {
        SetScaleX__5CFontFf(FLOAT_80332d2c, font);
        SetScaleY__5CFontFf(FLOAT_80332d28, font);
        char* attrStr = GetAttrStr__8CMenuPcsFi(MenuPcsVoid(), attr);
        DrawInit__5CFontFv(font);
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(MenuPcsVoid(), font, attrStr, static_cast<float>(x + 0x40), static_cast<float>(y), 0x18, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());

        int fontColor = 9;
        if ((attr == 0) || (attr > 8)) {
            if ((attr == 0xB) || (attr == 0x11) || (attr == 0x12)) {
                sprintf(textBuffer, DAT_80332d44, DAT_80332d4c, statValue);
            } else {
                if ((attr != 9) && (attr != 10) && (attr != 0xC)) {
                    return;
                }
                sprintf(textBuffer, DAT_80332d44, DAT_80332d50, statValue);
                fontColor = 3;
            }
        } else {
            sprintf(textBuffer, DAT_80332d40, DAT_80332d38);
        }

        SetScaleX__5CFontFf(FLOAT_80332d28, font);
        float valueWidth = GetWidth__5CFontFPc(font, textBuffer);
        DrawInit__5CFontFv(font);
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
            MenuPcsVoid(), font, textBuffer, static_cast<float>(x) + (FLOAT_80332d3c - valueWidth), static_cast<float>(y), fontColor, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());
        return;
    }

    strcpy(textBuffer, label);
    strcat(textBuffer, DAT_80332d30);
    DrawInit__5CFontFv(font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, textBuffer, static_cast<float>(x + 0x40), static_cast<float>(y), 0x18, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    int valueRightX = x + 0x108;
    SetShadow__5CFontFi(font, 1);
    SetScale__5CFontFf(FLOAT_80332d28, font);
    SetColor__5CFontF8_GXColor(font, &white);
    DrawInit__5CFontFv(font);
    reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
    SetMargin__5CFontFf(FLOAT_80332d34, font);

    char valueBuffer[64];
    sprintf(valueBuffer, DAT_80332d14, statValue);
    float valueWidth = GetWidth__5CFontFPc(font, valueBuffer);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
        MenuPcsVoid(), font, valueBuffer, static_cast<float>(valueRightX) - valueWidth, static_cast<float>(y), 0x1A, 0x12);
    DrawInit__8CMenuPcsFv(MenuPcsVoid());

    DrawInit__5CFontFv(font);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetScale__5CFontFf(FLOAT_80332d28, font);

    if ((statType == 1) && (attr != 0)) {
        SetScaleX__5CFontFf(FLOAT_80332d2c, font);
        SetScaleY__5CFontFf(FLOAT_80332d28, font);
        char* attrStr = GetAttrStr__8CMenuPcsFi(MenuPcsVoid(), attr);
        DrawInit__5CFontFv(font);
        DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
            MenuPcsVoid(), font, attrStr, static_cast<float>(x + 0x40), static_cast<float>(attrY), 0x18, 0x12);
        DrawInit__8CMenuPcsFv(MenuPcsVoid());

        SetScaleX__5CFontFf(FLOAT_80332d28, font);
        attrStr = GetAttrStr__8CMenuPcsFi(MenuPcsVoid(), attr);
        GetWidth__5CFontFPc(font, attrStr);
        if ((attr != 0) && (attr < 9)) {
            strcpy(textBuffer, DAT_80332d38);
            valueWidth = GetWidth__5CFontFPc(font, textBuffer);
            DrawInit__5CFontFv(font);
            DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(
                MenuPcsVoid(), font, textBuffer, static_cast<float>(x) + (FLOAT_80332d3c - valueWidth), static_cast<float>(attrY), 9, 0x12);
            DrawInit__8CMenuPcsFv(MenuPcsVoid());
        }
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
    if (CanTradeShopMenuItem(this, index, itemNo)) {
        sourceText = reinterpret_cast<const char*>(GetShopMenuHelpMsgTable()[itemNo]);
    } else {
        sourceText = PTR_s_Cannot_be_crafted_here__80214de0[languageId];
    }
    if (sourceText == 0) {
        return;
    }

    char* helpText = new char[0x200];
    if (helpText == 0) {
        return;
    }
    memset(helpText, 0, 0x200);
    MakeAgbString__4CMesFPcPcii(helpText, const_cast<char*>(sourceText), 0, 1);

    CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x248);
    SetMargin__5CFontFf(FLOAT_80332d28, font);
    SetShadow__5CFontFi(font, 1);
    SetScaleX__5CFontFf(FLOAT_80332d2c, font);
    SetScaleY__5CFontFf(FLOAT_80332d28, font);

    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    SetColor__5CFontF8_GXColor(font, &white);
    float width = GetWidth__5CFontFPc(font, helpText);
    float x = static_cast<float>(centerX) - width * 0.5f;
    DrawInit__5CFontFv(font);
    SetPosX__5CFontFf(x + 1.0f, font);
    SetPosY__5CFontFf(static_cast<float>(y - 3), font);
    SetTlut__5CFontFi(font, 0x12);
    Draw__5CFontFPc(font, helpText);
    SetPosX__5CFontFf(x, font);
    SetPosY__5CFontFf(static_cast<float>(y - 4), font);
    SetTlut__5CFontFi(font, 7);
    Draw__5CFontFPc(font, helpText);
    delete[] helpText;
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
    ShopMenuInt(this, 0x40) = alpha;
}

