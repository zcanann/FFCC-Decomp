#include "ffcc/menu_item.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" int SingGetLetterAttachflg__8CMenuPcsFv(CMenuPcs*);
extern "C" void LetterSetAttachItem__8CMenuPcsFUii(CMenuPcs*, unsigned int, unsigned int);
extern "C" int EquipChk__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int CanPlayerUseItem__12CCaravanWorkFv(void*);
extern "C" int CanPlayerPutItem__12CCaravanWorkFv(void*);
extern "C" void GetSingWinSize__8CMenuPcsFiPsPsi(CMenuPcs*, int, s16*, s16*, int);
extern "C" void SetSingWinInfo__8CMenuPcsFiiii(CMenuPcs*, int, int, int, int);
extern "C" void FGUseItem__12CCaravanWorkFii(void*, int, int);
extern "C" void SingLifeInit__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void CalcStatus__12CCaravanWorkFv(void*);
extern "C" void FGPutItem__12CCaravanWorkFii(void*, int, int);
extern "C" void DeleteItemIdx__12CCaravanWorkFii(void*, int, int);

struct MenuItemOpenAnim {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    float alpha;
    float scale;
    int frame;
    int duration;
    unsigned int flags;
    float progress;
    float dx;
    float dy;
    float targetX;
    float targetY;
};

/*
 * --INFO--
 * PAL Address: 0x8015aeb0
 * PAL Size: 680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemInit()
{
    s16* itemState = *(s16**)((u8*)this + 0x82C);
    s16* itemList = *(s16**)((u8*)this + 0x850);
    u8* itemListBytes = (u8*)itemList;
    const float zero = 0.0f;
    const float one = 1.0f;

    memset(itemList, 0, 0x1008);

    int entryBase = (int)itemList + 8;
    for (int i = 0; i < 8; i++) {
        *(float*)(entryBase + 0x14) = one;
        *(float*)(entryBase + 0x54) = one;
        *(float*)(entryBase + 0x94) = one;
        *(float*)(entryBase + 0xD4) = one;
        *(float*)(entryBase + 0x114) = one;
        *(float*)(entryBase + 0x154) = one;
        *(float*)(entryBase + 0x194) = one;
        *(float*)(entryBase + 0x1D4) = one;
        entryBase += 0x200;
    }

    *(int*)(itemListBytes + 0x24) = 0x2E;
    *(s16*)(itemListBytes + 8) = 0x68;
    *(s16*)(itemListBytes + 0xA) = 0x28;
    *(s16*)(itemListBytes + 0xC) = 0x78;
    *(s16*)(itemListBytes + 0xE) = 0x108;
    *(float*)(itemListBytes + 0x10) = zero;
    *(float*)(itemListBytes + 0x14) = zero;
    *(float*)(itemListBytes + 0x1C) = one;
    *(int*)(itemListBytes + 0x2C) = 5;
    *(int*)(itemListBytes + 0x30) = 5;

    *(int*)(itemListBytes + 0x64) = 0x47;
    *(s16*)(itemListBytes + 0x48) = 0x50;
    *(s16*)(itemListBytes + 0x4A) = 0xE;
    *(s16*)(itemListBytes + 0x4C) = 0x30;
    *(s16*)(itemListBytes + 0x4E) = 0x30;
    *(float*)(itemListBytes + 0x50) = zero;
    *(float*)(itemListBytes + 0x54) = zero;
    *(float*)(itemListBytes + 0x5C) = one;
    *(int*)(itemListBytes + 0x6C) = 0;
    *(int*)(itemListBytes + 0x70) = 5;

    *(int*)(itemListBytes + 0xA4) = 0x47;
    *(s16*)(itemListBytes + 0x88) = 0x55;
    *(s16*)(itemListBytes + 0x8C) = 0x30;
    *(s16*)(itemListBytes + 0x8E) = 0x30;
    *(s16*)(itemListBytes + 0x8A) = 0x150 - *(s16*)(itemListBytes + 0x8E);
    *(float*)(itemListBytes + 0x90) = zero;
    *(float*)(itemListBytes + 0x94) = zero;
    *(float*)(itemListBytes + 0x9C) = one;
    *(int*)(itemListBytes + 0xAC) = 0;
    *(int*)(itemListBytes + 0xB0) = 5;

    *(int*)(itemListBytes + 0xF4) = 2;
    *(int*)(itemListBytes + 0xE4) = 0x2E;
    *(s16*)(itemListBytes + 0xC8) = 0x50;
    *(s16*)(itemListBytes + 0xCA) = 8;
    *(s16*)(itemListBytes + 0xCC) = 0x48;
    *(s16*)(itemListBytes + 0xCE) = 0x140;
    *(float*)(itemListBytes + 0xD0) = zero;
    *(float*)(itemListBytes + 0xD4) = zero;
    *(int*)(itemListBytes + 0xEC) = 0;
    *(int*)(itemListBytes + 0xF0) = 5;

    s16 yOffset = 0;
    s16 count = 4;
    int offset = 0x100;
    for (int i = 0; i < 4; i++) {
        s16* itemA = (s16*)(itemListBytes + offset + 8);
        itemA[0x16] = 0;
        itemA[0x17] = 2;
        itemA[0xE] = 0;
        itemA[0xF] = 0x37;
        count += 2;

        s16 nextYOffset = yOffset + 0x20;
        itemA[0] = *(s16*)(itemListBytes + 8) + 0x24;
        itemA[1] = *(s16*)(itemListBytes + 0xA) + yOffset;
        itemA[2] = 200;
        itemA[3] = 0x28;
        *(float*)(itemA + 4) = zero;
        *(float*)(itemA + 6) = zero;
        itemA[0x12] = 0;
        itemA[0x13] = 7;
        itemA[0x14] = 0;
        itemA[0x15] = 5;

        int offsetB = offset + 0x48;
        offset += 0x80;
        s16* itemB = (s16*)(itemListBytes + offsetB);
        itemB[0x16] = 0;
        itemB[0x17] = 2;
        itemB[0xE] = 0;
        itemB[0xF] = 0x37;
        itemB[0] = *(s16*)(itemListBytes + 8) + 0x24;
        itemB[1] = *(s16*)(itemListBytes + 0xA) + nextYOffset;
        itemB[2] = 200;
        itemB[3] = 0x28;
        *(float*)(itemB + 4) = zero;
        *(float*)(itemB + 6) = zero;
        itemB[0x12] = 0;
        itemB[0x13] = 7;
        itemB[0x14] = 0;
        itemB[0x15] = 5;

        yOffset += 0x40;
    }

    itemList[0] = count;
    itemState[0x13] = 0;
    *((u8*)itemState + 0xB) = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8015ac54
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemInit1()
{
    s16* itemList = *(s16**)((u8*)this + 0x850);
    u8* itemListBytes = (u8*)itemList;

    *(int*)(itemListBytes + 0x24) = 0x2E;
    *(int*)(itemListBytes + 0x2C) = 2;
    *(int*)(itemListBytes + 0x30) = 5;

    *(int*)(itemListBytes + 0x64) = 0x47;
    *(int*)(itemListBytes + 0x6C) = 7;
    *(int*)(itemListBytes + 0x70) = 5;

    *(int*)(itemListBytes + 0xA4) = 0x47;
    *(int*)(itemListBytes + 0xAC) = 7;
    *(int*)(itemListBytes + 0xB0) = 5;

    *(int*)(itemListBytes + 0xF4) = 2;
    *(int*)(itemListBytes + 0xE4) = 0x2E;
    *(int*)(itemListBytes + 0xEC) = 7;
    *(int*)(itemListBytes + 0xF0) = 5;

    *(int*)(itemListBytes + 0x134) = 2;
    *(int*)(itemListBytes + 0x124) = 0x37;
    *(int*)(itemListBytes + 0x12C) = 0;
    *(int*)(itemListBytes + 0x130) = 5;

    *(int*)(itemListBytes + 0x174) = 2;
    *(int*)(itemListBytes + 0x164) = 0x37;
    *(int*)(itemListBytes + 0x16C) = 0;
    *(int*)(itemListBytes + 0x170) = 5;

    *(int*)(itemListBytes + 0x1B4) = 2;
    *(int*)(itemListBytes + 0x1A4) = 0x37;
    *(int*)(itemListBytes + 0x1AC) = 0;
    *(int*)(itemListBytes + 0x1B0) = 5;

    *(int*)(itemListBytes + 0x1F4) = 2;
    *(int*)(itemListBytes + 0x1E4) = 0x37;
    *(int*)(itemListBytes + 0x1EC) = 0;
    *(int*)(itemListBytes + 0x1F0) = 5;

    *(int*)(itemListBytes + 0x234) = 2;
    *(int*)(itemListBytes + 0x224) = 0x37;
    *(int*)(itemListBytes + 0x22C) = 0;
    *(int*)(itemListBytes + 0x230) = 5;

    *(int*)(itemListBytes + 0x274) = 2;
    *(int*)(itemListBytes + 0x264) = 0x37;
    *(int*)(itemListBytes + 0x26C) = 0;
    *(int*)(itemListBytes + 0x270) = 5;

    *(int*)(itemListBytes + 0x2B4) = 2;
    *(int*)(itemListBytes + 0x2A4) = 0x37;
    *(int*)(itemListBytes + 0x2AC) = 0;
    *(int*)(itemListBytes + 0x2B0) = 5;

    *(int*)(itemListBytes + 0x2F4) = 2;
    *(int*)(itemListBytes + 0x2E4) = 0x37;
    *(int*)(itemListBytes + 0x2EC) = 0;
    *(int*)(itemListBytes + 0x2F0) = 5;

    unsigned int count = (unsigned int)itemList[0];
    s16* entry = itemList + 4;
    if ((int)count <= 0) {
        return;
    }

    const float scale = 1.0f;
    unsigned int blocks = count >> 3;
    if (blocks != 0) {
        do {
            entry[0x10] = 0;
            entry[0x11] = 0;
            *(float*)(entry + 8) = scale;
            entry[0x30] = 0;
            entry[0x31] = 0;
            *(float*)(entry + 0x28) = scale;
            entry[0x50] = 0;
            entry[0x51] = 0;
            *(float*)(entry + 0x48) = scale;
            entry[0x70] = 0;
            entry[0x71] = 0;
            *(float*)(entry + 0x68) = scale;
            entry[0x90] = 0;
            entry[0x91] = 0;
            *(float*)(entry + 0x88) = scale;
            entry[0xB0] = 0;
            entry[0xB1] = 0;
            *(float*)(entry + 0xA8) = scale;
            entry[0xD0] = 0;
            entry[0xD1] = 0;
            *(float*)(entry + 0xC8) = scale;
            entry[0xF0] = 0;
            entry[0xF1] = 0;
            *(float*)(entry + 0xE8) = scale;
            entry += 0x100;
            blocks--;
        } while (blocks != 0);

        count &= 7;
        if (count == 0) {
            return;
        }
    }

    do {
        entry[0x10] = 0;
        entry[0x11] = 0;
        *(float*)(entry + 8) = scale;
        entry += 0x20;
        count--;
    } while (count != 0);
}

/*
 * --INFO--
 * PAL Address: 0x8015aa98
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::ItemOpen()
{
    s16* itemState = *reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x82C);
    s16* itemList = *reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x850);
    int finished = 0;
    int count = itemList[0];
    MenuItemOpenAnim* anim = reinterpret_cast<MenuItemOpenAnim*>(reinterpret_cast<u8*>(itemList) + 8);

    if (*reinterpret_cast<u8*>(itemState + 5) == 0) {
        SingLifeInit(-1);
        ItemInit();
    }

    itemState[0x11]++;

    for (int i = 0; i < count; i++, anim++) {
        if (anim->frame <= itemState[0x11]) {
            if (itemState[0x11] < anim->frame + anim->duration) {
                anim->frame++;
                anim->progress = (float)anim->frame / (float)anim->duration;
                if ((anim->flags & 2) == 0) {
                    float t = (float)anim->frame / (float)anim->duration;
                    anim->dx = (anim->targetX - (float)anim->x) * t;
                    anim->dy = (anim->targetY - (float)anim->y) * t;
                }
            } else {
                finished++;
                anim->progress = 1.0f;
                anim->dx = 0.0f;
                anim->dy = 0.0f;
            }
        }
    }

    return count == finished;
}

/*
 * --INFO--
 * PAL Address: 0x8015a994
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ItemCtrl()
{
    s16* itemState = *(s16**)((u8*)this + 0x82C);
    s16* selectState = *(s16**)((u8*)this + 0x848);
    int result = 0;

    itemState[0x19] = itemState[0x18];

    if ((itemState[0x18] == 0) || ((itemState[0x18] != 0) && (itemState[0x9] == 1))) {
        result = ItemCtrlCur();
    } else if ((itemState[0x18] == 1) && (itemState[0x9] == 0)) {
        if (selectState[5] == 1) {
            result = 0;
            itemState[0x9] = 1;
        }
    } else if ((itemState[0x18] == 1) && (itemState[0x9] == 2) && (selectState[5] == 3)) {
        result = 0;
        itemState[0x9] = 0;
        itemState[0x18] = 0;
        itemState[0x11] = 0;
    }

    if (result != 0) {
        SingLifeInit(-1);
        ItemInit1();
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x8015a818
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::ItemClose()
{
    s16* itemState = *(s16**)((u8*)this + 0x82C);
    s16* itemList = *(s16**)((u8*)this + 0x850);
    int finished = 0;
    int count = itemList[0];
    MenuItemOpenAnim* anim = (MenuItemOpenAnim*)((u8*)itemList + 8);

    itemState[0x11]++;

    for (int i = 0; i < count; i++, anim++) {
        if (anim->frame <= itemState[0x11]) {
            if (itemState[0x11] < anim->frame + anim->duration) {
                anim->frame++;
                anim->progress = 1.0f - ((float)anim->frame / (float)anim->duration);
                if ((anim->flags & 2) == 0) {
                    float t = 1.0f - ((float)anim->frame / (float)anim->duration);
                    anim->dx = (anim->targetX - (float)anim->x) * t;
                    anim->dy = (anim->targetY - (float)anim->y) * t;
                }
            } else {
                finished++;
                anim->progress = 0.0f;
                anim->dx = 0.0f;
                anim->dy = 0.0f;
            }
        }
    }

    return count == finished;
}

/*
 * --INFO--
 * Address:\tTODO
 * Size:\tTODO
 */
void CMenuPcs::ItemDraw()
{
    // TODO
}

/*
 * --INFO--
 * PAL Address: 0x80159654
 * PAL Size: 1952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ItemCtrlCur()
{
    bool blocked = false;
    u16 press;
    u16 hold;
    int caravanWork = Game.game.m_scriptFoodBase[0];

    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        blocked = true;
    }
    if (blocked) {
        press = 0;
    } else {
        press = Pad._8_2_;
    }

    blocked = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        blocked = true;
    }
    if (blocked) {
        hold = 0;
    } else {
        hold = *(u16*)((u8*)&Pad + 0x20);
    }

    if (hold == 0) {
        return 0;
    }

    int menuState = *(int*)((u8*)this + 0x82C);
    s16 letterAttachFlg = SingGetLetterAttachflg__8CMenuPcsFv(this);
    int mode = (int)*(s16*)(menuState + 0x30);

    if (mode == 0) {
        if ((hold & 8) == 0) {
            if ((hold & 4) != 0) {
                if (*(s16*)(menuState + 0x26) < 7) {
                    *(s16*)(menuState + 0x26) = *(s16*)(menuState + 0x26) + 1;
                } else {
                    s16 scroll = *(s16*)(menuState + 0x34);
                    if (scroll > 0x3E) {
                        *(s16*)(menuState + 0x34) = 0;
                    } else {
                        *(s16*)(menuState + 0x34) = scroll + 1;
                    }
                }
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        } else if (*(s16*)(menuState + 0x26) == 0) {
            if (*(s16*)(menuState + 0x34) == 0) {
                *(s16*)(menuState + 0x34) = 0x3F;
            } else {
                *(s16*)(menuState + 0x34) = *(s16*)(menuState + 0x34) - 1;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else {
            *(s16*)(menuState + 0x26) = *(s16*)(menuState + 0x26) - 1;
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((hold & 0xC) == 0) {
            if ((press & 0x20) != 0) {
                if (letterAttachFlg < 0) {
                    *(s16*)(menuState + 0x1E) = 1;
                    Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
                    return 1;
                }
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else if ((press & 0x40) != 0) {
                if (letterAttachFlg < 0) {
                    *(s16*)(menuState + 0x1E) = -1;
                    Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
                    return 1;
                }
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else if ((press & 0x100) != 0) {
                int idx = (int)*(s16*)(menuState + 0x34) + (int)*(s16*)(menuState + 0x26);
                if (idx > 0x3F) {
                    idx -= 0x40;
                }

                int itemEntry = caravanWork + idx * 2;
                s16 itemId = *(s16*)(itemEntry + 0xB6);

                if ((itemId < 1) || (EquipChk__8CMenuPcsFi(this, idx) != 0) ||
                    ((letterAttachFlg >= 0) && (itemId < 0x125))) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else if (letterAttachFlg >= 0) {
                    LetterSetAttachItem__8CMenuPcsFUii(this, (unsigned int)idx, 1);
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                    return 1;
                } else {
                    *(u8*)(menuState + 9) = 0xC;
                    int itemType = GetItemType__8CMenuPcsFii(this, idx, 0);

                    if ((itemType == 7) && (CanPlayerUseItem__12CCaravanWorkFv((void*)caravanWork) != 0)) {
                        *(u8*)(menuState + 9) = *(u8*)(menuState + 9) | 1;
                    }
                    if ((itemType != 1) && (CanPlayerPutItem__12CCaravanWorkFv((void*)caravanWork) != 0)) {
                        *(u8*)(menuState + 9) = *(u8*)(menuState + 9) | 2;
                    }

                    s16 winW;
                    s16 winH;
                    GetSingWinSize__8CMenuPcsFiPsPsi(this, 0, &winW, &winH, 0);
                    SetSingWinInfo__8CMenuPcsFiiii(this, 0xF0, 0xA0, winW, winH);

                    *(s16*)(*(int*)((u8*)this + 0x848) + 10) = 0;
                    *(s16*)(menuState + 0x12) = 0;
                    *(s16*)(menuState + 0x30) = 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                }
            } else if ((press & 0x200) != 0) {
                if (letterAttachFlg >= 0) {
                    LetterSetAttachItem__8CMenuPcsFUii(this, 0, 0xFFFFFFFF);
                    Sound.PlaySe(3, 0x40, 0x7F, 0);
                    return 1;
                }
                *(u8*)(menuState + 0xD) = 1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                return 1;
            }
        }
    } else {
        int optBase = menuState + mode * 2;

        if ((hold & 8) == 0) {
            if ((hold & 4) != 0) {
                if (*(s16*)(optBase + 0x26) < 3) {
                    *(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) + 1;
                } else {
                    *(s16*)(optBase + 0x26) = 0;
                }
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        } else {
            if (*(s16*)(optBase + 0x26) == 0) {
                *(s16*)(optBase + 0x26) = 3;
            } else {
                *(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) - 1;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((hold & 0xC) == 0) {
            if ((press & 0x100) != 0) {
                int option = (int)*(s16*)(optBase + 0x26);
                if (((int)*(char*)(menuState + 9) & (1 << option)) == 0) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else {
                    int idx = (int)*(s16*)(menuState + 0x34) + (int)*(s16*)(menuState + 0x26);
                    if (idx > 0x3F) {
                        idx -= 0x40;
                    }

                    if (option == 0) {
                        FGUseItem__12CCaravanWorkFii((void*)caravanWork, idx, 0);
                        SingLifeInit__8CMenuPcsFi(this, 0);
                        CalcStatus__12CCaravanWorkFv((void*)caravanWork);
                    } else if (option == 1) {
                        FGPutItem__12CCaravanWorkFii((void*)caravanWork, idx, 0);
                    } else if (option == 2) {
                        DeleteItemIdx__12CCaravanWorkFii((void*)caravanWork, idx, 0);
                    }

                    *(s16*)(*(int*)((u8*)this + 0x848) + 10) = 2;
                    *(s16*)(menuState + 0x12) = *(s16*)(menuState + 0x12) + 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                }
            } else if ((press & 0x200) != 0) {
                *(s16*)(*(int*)((u8*)this + 0x848) + 10) = 2;
                *(s16*)(menuState + 0x12) = *(s16*)(menuState + 0x12) + 1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
            }
        }
    }

    return 0;
}
