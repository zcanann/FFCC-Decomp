#include "ffcc/mesmenu.h"
#include "ffcc/p_game.h"

extern "C" {
void Set__4CMesFPci(void* mes, char* script, int flags);
void PlaySe__6CSoundFiiii(void* sound, int id, int volume, int pan, int unk);
void SetFade__9CRingMenuFi(void* ringMenu, int fade);
void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void* flatRuntime, int object, int type, int id, int stackCount, void* stack, void* stack2);

extern unsigned char CFlat[];
extern unsigned char MenuPcs[];
extern unsigned char Sound[];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMesMenu::CMesMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMesMenu::~CMesMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::Create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::onCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::onDraw()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009bcec
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::CalcHeart()
{
    unsigned int scriptFood = Game.game.m_scriptFoodBase[*(int*)((char*)this + 0x18)];
    if (scriptFood == 0) {
        return;
    }

    unsigned int foodCount = (unsigned int)*(unsigned short*)(scriptFood + 0x1C);
    int targetValue = (int)(foodCount * 6);
    if (*(int*)((char*)this + 0x3DAC) < targetValue) {
        *(int*)((char*)this + 0x3DAC) = targetValue;
    } else if (targetValue < *(int*)((char*)this + 0x3DAC)) {
        *(unsigned int*)((char*)this + 0x3DAC) = foodCount * 6;
    }

    int currentValue = *(int*)((char*)this + 0x3DA8);
    if (currentValue < *(int*)((char*)this + 0x3DAC)) {
        int index = currentValue / 0xC + (currentValue >> 0x1F);
        int base = (int)this + (index - (index >> 0x1F)) * 4;
        if (*(int*)(base + 0x3DB0) == 0) {
            *(int*)(base + 0x3DB0) = 0x10;
        }

        int nextValue = currentValue + 2;
        int maxValue = *(int*)((char*)this + 0x3DAC);
        if (nextValue < maxValue) {
            maxValue = nextValue;
        }
        *(int*)((char*)this + 0x3DA8) = maxValue;
    } else if (*(int*)((char*)this + 0x3DAC) < currentValue) {
        *(unsigned int*)((char*)this + 0x3DA8) = (currentValue - 2U) & ~((int)(currentValue - 2U) >> 0x1F);

        int decValue = *(int*)((char*)this + 0x3DA8);
        int index = decValue / 0xC + (decValue >> 0x1F);
        int base = (int)this + (index - (index >> 0x1F)) * 4;
        if (*(int*)(base + 0x3DD0) == 0) {
            *(int*)(base + 0x3DD0) = 0x10;
        }
        if (*(int*)((char*)this + 0x3DF0) == 0) {
            *(int*)((char*)this + 0x3DF0) = 0x10;
        }
    }

    int i = 2;
    int base = (int)this;
    do {
        unsigned int value = *(int*)(base + 0x3DB0) - 1;
        *(unsigned int*)(base + 0x3DB0) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DD0) - 1;
        *(unsigned int*)(base + 0x3DD0) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DB4) - 1;
        *(unsigned int*)(base + 0x3DB4) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DD4) - 1;
        *(unsigned int*)(base + 0x3DD4) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DB8) - 1;
        *(unsigned int*)(base + 0x3DB8) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DD8) - 1;
        *(unsigned int*)(base + 0x3DD8) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DBC) - 1;
        *(unsigned int*)(base + 0x3DBC) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DDC) - 1;
        *(unsigned int*)(base + 0x3DDC) = value & ~((int)value >> 0x1F);

        base += 0x10;
        i--;
    } while (i != 0);

    unsigned int value = *(int*)((char*)this + 0x3DF0) - 1;
    *(unsigned int*)((char*)this + 0x3DF0) = value & ~((int)value >> 0x1F);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::DrawHeart(float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009b8e8
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::onScriptChanging(char*)
{
    Set__4CMesFPci((char*)this + 0x1C, 0, 0);
    *(int*)((char*)this + 0x0C) = 4;
    *(int*)((char*)this + 0x08) = 0;
    if (*(int*)((char*)this + 0x18) < 4) {
        SetFade__9CRingMenuFi(*(void**)((char*)MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b8e4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::onScriptChanged(char*, int)
{
    return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::Open(char*, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009b4f0
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::CloseRequest(int closeReason)
{
    int stack[2];

    *(int*)((char*)this + 0x3DA4) = closeReason;
    if (*(int*)((char*)this + 0x0C) <= 1) {
        if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x40) != 0) {
            Set__4CMesFPci((char*)this + 0x1C, 0, 0);
            stack[0] = *(int*)((char*)this + 0x18);
            stack[1] = *(int*)((char*)this + 0x3DA4);
            SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
                CFlat, 0, 1, 3, 2, stack, 0);
            *(int*)((char*)this + 0x0C) = 4;
            *(int*)((char*)this + 0x08) = 0;
            if (*(int*)((char*)this + 0x18) < 4) {
                SetFade__9CRingMenuFi(*(void**)((char*)MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 1);
            }
        } else {
            *(int*)((char*)this + 0x0C) = 2;
            *(int*)((char*)this + 0x10) = 0;
            *(int*)((char*)this + 0x14) = 4;
            if (((*(unsigned int*)((char*)this + 0x3D8C) & 1) == 0) &&
                ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
                PlaySe__6CSoundFiiii(Sound, 6, 0x40, 0x7F, 0);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b4e4
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::SetPos(float x, float y)
{
	*(float*)((char*)this + 0x3d74) = x;
	*(float*)((char*)this + 0x3d78) = y;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::close(int)
{
	// TODO
}
