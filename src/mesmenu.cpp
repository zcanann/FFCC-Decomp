#include "ffcc/mesmenu.h"

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
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::CalcHeart()
{
	// TODO
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
