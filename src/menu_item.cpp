#include "ffcc/menu_item.h"

typedef signed short s16;
typedef unsigned char u8;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ItemInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ItemInit1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ItemOpen()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ItemClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ItemDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMenuPcs::ItemCtrlCur()
{
    return 0;
}
