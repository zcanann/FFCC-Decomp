#include "ffcc/menu.h"

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
CMenu::~CMenu()
{
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
