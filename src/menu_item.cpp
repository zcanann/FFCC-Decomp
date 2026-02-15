#include "ffcc/menu_item.h"

typedef signed short s16;
typedef unsigned char u8;

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
 * Address:\tTODO
 * Size:\tTODO
 */
void CMenuPcs::ItemInit()
{
    // TODO
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
 * Address:\tTODO
 * Size:\tTODO
 */
void CMenuPcs::ItemClose()
{
    // TODO
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
 * Address:\tTODO
 * Size:\tTODO
 */
int CMenuPcs::ItemCtrlCur()
{
    return 0;
}
