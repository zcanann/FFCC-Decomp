#include "ffcc/ringmenu.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CRingMenu::CRingMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CRingMenu::~CRingMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::Create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::GetDispCounter()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::onCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawCommand(int, CFont*, float, float, CCaravanWork*, int, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::onDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::drawGBA()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::onScriptChanging(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::onScriptChanged(char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::SetFade(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800a33dc
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::SetBattleButton(int buttonIndex, int newValue)
{
	int* battleButtons = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x18);

	if (battleButtons[buttonIndex] == newValue) {
		return;
	}

	battleButtons[buttonIndex] = newValue;
}

/*
 * --INFO--
 * PAL Address: 0x800a3340
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::SetBattleCommand(int buttonGroupIndex, int newCommandId, int newRotation)
{
	int slot8 = buttonGroupIndex * 8;
	int slot12 = buttonGroupIndex * 12;
	char* self = reinterpret_cast<char*>(this);
	int* commandCurrent = reinterpret_cast<int*>(self + slot8 + 0x20);
	int currentCommand = *commandCurrent;

	if (newCommandId == 0) {
		newCommandId = -1;
	}

	if (currentCommand == newCommandId) {
		return;
	}

	if (((currentCommand >= 0) && (newCommandId < 0)) || ((currentCommand < 0) && (newCommandId >= 0))) {
		int* timer2 = reinterpret_cast<int*>(self + slot12 + 0x40);
		*timer2 = 8 - *timer2;
	}

	*reinterpret_cast<int*>(self + slot8 + 0x24) = currentCommand;
	*commandCurrent = newCommandId;

	int* timer0 = reinterpret_cast<int*>(self + slot12 + 0x38);
	*reinterpret_cast<int*>(self + slot12 + 0x3c) = 8 - *timer0;
	*timer0 = 8 - *timer0;

	if (buttonGroupIndex != 2) {
		return;
	}

	*reinterpret_cast<int*>(self + 0x60) = *reinterpret_cast<int*>(self + 0x5c);
	*reinterpret_cast<int*>(self + 0x5c) = newRotation;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::DrawIcon()
{
	// TODO
}
