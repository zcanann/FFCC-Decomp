#include "ffcc/menu.h"

extern "C" void __dl__FPv(void*);
extern "C" void* __vt__5CMenu;
extern "C" CRef* dtor_80043D10(CRef* ref, short param_2);

/*
 * --INFO--
 * PAL Address: 0x8009b4a8
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMenu::CMenu()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009b448
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMenu::~CMenu()
{
}

/*
 * --INFO--
 * PAL Address: 0x8009b448
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CMenu* dtor_8009B448(CMenu* menu, short param_2)
{
	if (menu != 0) {
		*(void**)menu = &__vt__5CMenu;
		dtor_80043D10(menu, 0);
		if (0 < param_2) {
			__dl__FPv(menu);
		}
	}

	return menu;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenu::Create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenu::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenu::Calc()
{
	onCalc();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenu::Draw()
{
	onDraw();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenu::ScriptChanging(char* script)
{
	onScriptChanging(script);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenu::onCalc()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenu::onDraw()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenu::onScriptChanging(char*)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenu::onScriptChanged(char*, int)
{
	// TODO
}
