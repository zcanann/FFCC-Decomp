#include "ffcc/menu.h"

extern "C" void* __vt__5CMenu[];
extern "C" CRef* __dt__4CRefFv(CRef*, short);
extern "C" void __dl__FPv(void*);

/*
 * --INFO--
 * PAL Address: 0x8009b3b4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenu::onScriptChanging(char*)
{
}

/*
 * --INFO--
 * PAL Address: 0x8009b3b8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenu::onScriptChanged(char*, int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8009b3bc
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenu::ScriptChanging(char* script)
{
	onScriptChanging(script);
}

/*
 * --INFO--
 * PAL Address: 0x8009b3e8
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenu::Draw()
{
	onDraw();
}

/*
 * --INFO--
 * PAL Address: 0x8009b414
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenu::Calc()
{
	onCalc();
}

/*
 * --INFO--
 * PAL Address: 0x8009b440
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenu::Destroy()
{
}

/*
 * --INFO--
 * PAL Address: 0x8009b444
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenu::Create()
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
extern "C" CMenu* __dt__5CMenuFv(CMenu* menu, short shouldDelete)
{
	if (menu != 0) {
		*(void***)menu = __vt__5CMenu;
		__dt__4CRefFv(menu, 0);
		if (0 < shouldDelete) {
			__dl__FPv(menu);
		}
	}

	return menu;
}

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
}
