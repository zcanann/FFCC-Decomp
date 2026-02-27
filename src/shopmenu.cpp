#include "ffcc/shopmenu.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"
#include "ffcc/sound.h"

extern "C" {
void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
void _WaitDrawDone__8CGraphicFPci(void*, char*, int);
void SetMode__9CShopMenuFi(void*, int);
void ReleasePdt__8CPartPcsFi(void*, int);
int LoadMenuPdt__8CPartPcsFPc(void*, char*);
int GetItemType__8CMenuPcsFii(void*, int, int);
int GetData__13CAmemCacheSetFsPci(void*, short, char*, int);
int ChkEquipPossible__8CMenuPcsFi(void*, int);
void GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo(void*, int, short*);
int CanAddGil__12CCaravanWorkFi(void*, int);
void PlaySe__6CSoundFiiii(void*, int, int, int, int);
char EquipChk__8CMenuPcsFi(void*, int);
int GetSmithItem__8CMenuPcsFi(void*, int);
int __cntlzw(unsigned int);
void __dl__FPv(void*);
void pppCacheLoadShape__FPsP12_pppDataHead(short*, _pppDataHead*);
}

extern char s_shopmenu_cpp_801ded8c[];
extern char DAT_80332e54[];
extern unsigned short DAT_8032eed0;
extern unsigned char MenuPcs[];
extern unsigned char PartPcs[];
extern unsigned char PartMng[];
extern void* Graphic;
extern void* ppvAmemCacheSet;

static inline int& ShopMenuInt(CShopMenu* shopMenu, int offset)
{
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + offset);
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
    void* stage = *reinterpret_cast<void**>(MenuPcs + 0xEC);
    if (Game.game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<void**>(MenuPcs + 0xF4);
    }

    CShopMenu* shopMenu = reinterpret_cast<CShopMenu*>(
        __nw__FUlPQ27CMemory6CStagePci(0x158, stage, s_shopmenu_cpp_801ded8c, 0x2E2));
    *reinterpret_cast<CShopMenu**>(menuPcs + 0x878) = shopMenu;
    shopMenu = *reinterpret_cast<CShopMenu**>(menuPcs + 0x878);

    _WaitDrawDone__8CGraphicFPci(&Graphic, s_shopmenu_cpp_801ded8c, 0x2FE);
    *reinterpret_cast<void**>(shopMenu) = nullptr;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x20) = Game.game.m_scriptFoodBase[0];
    SetMode__9CShopMenuFi(shopMenu, 0);
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x18) =
        LoadMenuPdt__8CPartPcsFPc(PartPcs, DAT_80332e54);

    int slotIndex = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x18);
    _pppDataHead* pppDataHead = *reinterpret_cast<_pppDataHead**>(PartMng + 0x22E18 + slotIndex * 0x38);
    short* cacheChunks = reinterpret_cast<short*>(pppDataHead->m_cacheChunks);
    *reinterpret_cast<int*>(cacheChunks + 2) =
        GetData__13CAmemCacheSetFsPci(ppvAmemCacheSet, *cacheChunks, s_shopmenu_cpp_801ded8c, 0x32A);
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
    void* stage = *reinterpret_cast<void**>(MenuPcs + 0xEC);
    if (Game.game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<void**>(MenuPcs + 0xF4);
    }

    CShopMenu* shopMenu = reinterpret_cast<CShopMenu*>(
        __nw__FUlPQ27CMemory6CStagePci(0x158, stage, s_shopmenu_cpp_801ded8c, 0x2E9));
    *reinterpret_cast<CShopMenu**>(menuPcs + 0x878) = shopMenu;
    shopMenu = *reinterpret_cast<CShopMenu**>(menuPcs + 0x878);

    _WaitDrawDone__8CGraphicFPci(&Graphic, s_shopmenu_cpp_801ded8c, 0x2FE);
    *reinterpret_cast<void**>(shopMenu) = nullptr;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x20) = Game.game.m_scriptFoodBase[0];
    SetMode__9CShopMenuFi(shopMenu, 9);
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x18) =
        LoadMenuPdt__8CPartPcsFPc(PartPcs, DAT_80332e54);

    int slotIndex = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(shopMenu) + 0x18);
    _pppDataHead* pppDataHead = *reinterpret_cast<_pppDataHead**>(PartMng + 0x22E18 + slotIndex * 0x38);
    short* cacheChunks = reinterpret_cast<short*>(pppDataHead->m_cacheChunks);
    *reinterpret_cast<int*>(cacheChunks + 2) =
        GetData__13CAmemCacheSetFsPci(ppvAmemCacheSet, *cacheChunks, s_shopmenu_cpp_801ded8c, 0x32A);
    int cacheData = *reinterpret_cast<int*>(cacheChunks + 2);
    pppCacheLoadShape__FPsP12_pppDataHead(
        reinterpret_cast<short*>(cacheData + *reinterpret_cast<int*>(cacheData + 0x14)), pppDataHead);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _drawNoShadowFont(CFont*, char*, float, float, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _drawShadowFont(CFont*, char*, float, float, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void getButtonRepeat(int, unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void bButtonNoRepeat(unsigned short)
{
	// TODO
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
            if (GetItemType__8CMenuPcsFii(MenuPcs, i, 0) == 9) {
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
void CShopMenu::getItemCnt()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::calcGilRatio(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::getItemNo(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::getBuyGil(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::getSellGil(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::getMakeGil(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::getBuySellGil(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::GetItemName(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::GetMaxExchange()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::GetTotalGil()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::CanAddGil()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::CheckSell(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::getItemHaveCnt(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setOrtho(int, int, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShp(tagOAN3_SHAPE*, CMaterialSet*, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeq0(int, int, unsigned char, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeq(int, int, int, int, unsigned char, unsigned char, unsigned char, float, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeqScale(int, int, int, int, float, float, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawShapeSeqGrouad(int, int, int, int, float, float, _GXColor, _GXColor, _GXColor, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawGrouadQuad(int, int, int, int, _GXColor, _GXColor, _GXColor, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Init(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Destroy()
{
	// TODO
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
            PlaySe__6CSoundFiiii((void*)&Sound, 5, 0x40, 0x7F, 0);
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
            PlaySe__6CSoundFiiii((void*)&Sound, 1, 0x40, 0x7F, 0);
        } else if ((buttons & 8) != 0) {
            --choice;
            if (choice > 2) {
                choice = 2;
            }
            PlaySe__6CSoundFiiii((void*)&Sound, 1, 0x40, 0x7F, 0);
        } else if ((buttons & 0x100) != 0) {
            PlaySe__6CSoundFiiii((void*)&Sound, 2, 0x40, 0x7F, 0);
            this->SetMode(2);
        }

        if ((buttons & 0x200) != 0) {
            PlaySe__6CSoundFiiii((void*)&Sound, 3, 0x40, 0x7F, 0);
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
                ReleasePdt__8CPartPcsFi(PartPcs, ShopMenuInt(this, 0x18));
                reinterpret_cast<CCaravanWork*>(Game.game.m_scriptFoodBase[0])->CallShop(0, 0, 0, 0, 0);
                *reinterpret_cast<unsigned short*>(MenuPcs + 0x850 + 6) = 1;
                __dl__FPv(*reinterpret_cast<void**>(MenuPcs + 0x878));
                *reinterpret_cast<void**>(MenuPcs + 0x878) = nullptr;
                return;
            }
        }
        break;
    case 3:
        if (timer == 0) {
            PlaySe__6CSoundFiiii((void*)&Sound, 5, 0x40, 0x7F, 0);
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
                PlaySe__6CSoundFiiii((void*)&Sound, 3, 0x40, 0x7F, 0);
                this->SetMode(5);
            }
        } else if (subMode == 1) {
            this->SelectFigure();
            if ((buttons & 0x200) != 0) {
                PlaySe__6CSoundFiiii((void*)&Sound, 3, 0x40, 0x7F, 0);
                subMode = 0;
            }
        } else if (subMode == 2) {
            this->SelectYesNo();
            if ((buttons & 0x200) != 0) {
                PlaySe__6CSoundFiiii((void*)&Sound, 3, 0x40, 0x7F, 0);
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
            PlaySe__6CSoundFiiii((void*)&Sound, 5, 0x40, 0x7F, 0);
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
                PlaySe__6CSoundFiiii((void*)&Sound, 3, 0x40, 0x7F, 0);
                this->SetMode(8);
            }
        } else if (subMode == 2) {
            this->SelectYesNo();
            if ((buttons & 0x200) != 0) {
                PlaySe__6CSoundFiiii((void*)&Sound, 3, 0x40, 0x7F, 0);
                subMode = 1;
            }
        }
        break;
    case 9:
        this->SelectSOUBI();
        break;
    case 10:
        this->SelectMake();
        break;
    case 11:
        this->SelectFigure();
        break;
    case 12:
        this->SelectYesNo();
        break;
    }

    ++timer;
    if (timer > 8) {
        timer = 8;
    }

    if ((shopMode == 0) || (shopMode == 1)) {
        DAT_8032eed0 = 0;
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

    if (DAT_8032eed0 == 0) {
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
        if ((buttons & DAT_8032eed0) == 0) {
            DAT_8032eed0 = 0;
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
        if (DAT_8032eed0 == 0) {
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
            if ((buttons & DAT_8032eed0) == 0) {
                DAT_8032eed0 = 0;
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
                                                 *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                                        itemNo = itemNo / 100 + (itemNo >> 0x1F);
                                        itemNo = itemNo - (itemNo >> 0x1F);
                                    }
                                } else if (mode == 1) {
                                    if (itemNo < 1) {
                                        itemNo = 0;
                                    } else {
                                        itemNo = *reinterpret_cast<short*>(caravan + 0xBE2) *
                                                 *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
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
                                PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
                                goto update_window;
                            }
                        }
                    }
                    PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
                } else if (listType == 1) {
                    int itemIdx = *reinterpret_cast<int*>(self + 0x28);
                    if (itemIdx != -1) {
                        short itemNo = *reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x20) + itemIdx * 2 + 0xB6);
                        if (itemNo >= 1) {
                            canSelect = false;
                            if (EquipChk__8CMenuPcsFi(MenuPcs, itemIdx) == 0) {
                                canSelect = itemNo >= 0x9F;
                            }
                        }
                    }

                    if (canSelect) {
                        *reinterpret_cast<int*>(self + 0x10) = 2;
                        PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
                    } else {
                        PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
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

                        *reinterpret_cast<int*>(self + 0x150) = GetSmithItem__8CMenuPcsFi(MenuPcs, smithItem);
                        SetMode__9CShopMenuFi(self, 0xB);
                        PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
                    } else {
                        PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
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
                PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
            } else {
                DAT_8032eed0 = 4;
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
                PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
            }
        }
    } else {
        *reinterpret_cast<int*>(self + 0x28) = *reinterpret_cast<int*>(self + 0x28) - 1;
        if (*reinterpret_cast<int*>(self + 0x28) < 0) {
            DAT_8032eed0 = 8;
            *reinterpret_cast<int*>(self + 0x28) = 0;
            PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
        } else {
            PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
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
                PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
                *reinterpret_cast<int*>(self + 0x10) = 2;
            }
        } else {
            *reinterpret_cast<int*>(self + 0x38) = *reinterpret_cast<int*>(self + 0x38) - 1;
            if (*reinterpret_cast<int*>(self + 0x38) < 0) {
                *reinterpret_cast<int*>(self + 0x38) = 0;
                PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
            } else {
                PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
            }
        }
    } else {
        *reinterpret_cast<int*>(self + 0x38) = *reinterpret_cast<int*>(self + 0x38) + 1;
        if (*reinterpret_cast<int*>(self + 0x38) < 2) {
            PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
        } else {
            *reinterpret_cast<int*>(self + 0x38) = 1;
            PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
        }
    }

    if (DAT_8032eed0 == 0) {
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
        if ((buttons & DAT_8032eed0) == 0) {
            DAT_8032eed0 = 0;
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
        if (DAT_8032eed0 == 0) {
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
            if ((buttons & DAT_8032eed0) == 0) {
                DAT_8032eed0 = 0;
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
                    PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
                } else {
                    PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
                }
            } else if (mode == 0) {
                *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) - 1;
                if (*reinterpret_cast<int*>(self + 0x44) < 1) {
                    DAT_8032eed0 = 4;
                    *reinterpret_cast<int*>(self + 0x44) = 1;
                    PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
                } else {
                    PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
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
                                     *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                            itemNo = itemNo / 100 + (itemNo >> 0x1F);
                            itemNo = itemNo - (itemNo >> 0x1F);
                        }
                    } else if (listType == 1) {
                        if (itemNo < 1) {
                            itemNo = 0;
                        } else {
                            itemNo = *reinterpret_cast<short*>(caravan + 0xBE2) *
                                     *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
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
                    PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
                    return;
                }
            }
            *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) - 10;
            PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
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
                                     *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
                            itemNo = itemNo / 100 + (itemNo >> 0x1F);
                            itemNo = itemNo - (itemNo >> 0x1F);
                        }
                    } else if (listType == 1) {
                        if (itemNo < 1) {
                            itemNo = 0;
                        } else {
                            itemNo = *reinterpret_cast<short*>(caravan + 0xBE2) *
                                     *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + itemNo * 0x48 + 0x20);
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
                    PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
                    return;
                }
            }
            DAT_8032eed0 = 8;
            *reinterpret_cast<int*>(self + 0x44) = *reinterpret_cast<int*>(self + 0x44) - 1;
            PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::SelectYesNo()
{
	// TODO
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

    canSelect = ChkEquipPossible__8CMenuPcsFi(MenuPcs, *reinterpret_cast<int*>(self + 0x150)) != 0;
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
                      *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + selected * 0x48 + 0x24);
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
    GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo(MenuPcs, selected, recipeMaterial);
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
                              *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + itemIdx * 0x48 + 0x24);
                    gil = gil / 100 + (gil >> 0x1F);
                    itemIdx = gil - (gil >> 0x1F);
                }

                int canAdd = CanAddGil__12CCaravanWorkFi(reinterpret_cast<void*>(*reinterpret_cast<int*>(self + 0x20)), -itemIdx);
                if (canAdd != 0) {
                    PlaySe__6CSoundFiiii(&Sound, 0x52, 0x40, 0x7F, 0);
                    *reinterpret_cast<int*>(self + 0x8) = 0xF;
                    SetMode__9CShopMenuFi(self, 0xE);
                    return;
                }
            }

            PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
            *reinterpret_cast<int*>(self + 0x8) = 9;
            SetMode__9CShopMenuFi(self, 0xE);
        }
    } else {
        *reinterpret_cast<unsigned int*>(self + 0x3C) ^= 1;
        if (canSelect == 1) {
            PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
        } else {
            *reinterpret_cast<int*>(self + 0x3C) = 1;
            PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawShop0()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawBuy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawSell()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawSmith0()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawMake()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawSoubi()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::Draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::InitDrawEnvShape()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawShopBase()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawMakeBase()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawSoubiBase()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawObi(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawItemList()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawBuySellInfo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawItemInfo0()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawItemInfo(int, int, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawItemHelp(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawDec(int, int, int, float, float, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::DrawDecScale(int, int, int, float, float, float, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CShopMenu::setFaceAlpha(int, int)
{
	// TODO
}
