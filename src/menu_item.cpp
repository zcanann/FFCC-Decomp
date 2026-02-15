#include "ffcc/menu_item.h"

extern "C" void SingLifeInit__8CMenuPcsFi(CMenuPcs* menuPcs, int mode);
extern "C" void ItemInit__8CMenuPcsFv(CMenuPcs* menuPcs);
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
 * PAL Address: 0x8015aa98
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::ItemOpen()
{
    int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
    if (*reinterpret_cast<char*>(menuState + 0xb) == '\0') {
        SingLifeInit__8CMenuPcsFi(this, -1);
        ItemInit__8CMenuPcsFv(this);
    }

    short* menuTimer = reinterpret_cast<short*>(menuState + 0x22);
    *menuTimer = static_cast<short>(*menuTimer + 1);
    int timer = static_cast<int>(*menuTimer);

    int completeCount = 0;
    int entryCount = static_cast<int>(**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850));
    short* entry = *reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) + 4;

    for (int i = 0; i < entryCount; i++) {
        int startFrame = *reinterpret_cast<int*>(entry + 0x12);
        if (startFrame <= timer) {
            int duration = *reinterpret_cast<int*>(entry + 0x14);
            if (timer < startFrame + duration) {
                int* currentFrame = reinterpret_cast<int*>(entry + 0x10);
                *currentFrame = *currentFrame + 1;
                float progress = static_cast<float>(*currentFrame) / static_cast<float>(duration);
                *reinterpret_cast<float*>(entry + 8) = progress;

                if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
                    *reinterpret_cast<float*>(entry + 0x18) =
                        (*reinterpret_cast<float*>(entry + 0x1c) - static_cast<float>(entry[0])) * progress;
                    *reinterpret_cast<float*>(entry + 0x1a) =
                        (*reinterpret_cast<float*>(entry + 0x1e) - static_cast<float>(entry[1])) * progress;
                }
            } else {
                completeCount = completeCount + 1;
                *reinterpret_cast<float*>(entry + 8) = 1.0f;
                *reinterpret_cast<float*>(entry + 0x18) = 0.0f;
                *reinterpret_cast<float*>(entry + 0x1a) = 0.0f;
            }
        }

        entry = entry + 0x20;
    }

    return entryCount == completeCount;
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
