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
 * Address:\tTODO
 * Size:\tTODO
 */
void CMenuPcs::ItemInit1()
{
    // TODO
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
