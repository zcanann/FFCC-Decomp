#include "ffcc/ringmenu.h"
#include "ffcc/joybus.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"

#include <math.h>

extern unsigned char CFlat[];
extern unsigned char Chara[];

static inline void decClamp0(int* value)
{
	*value -= 1;
	if (*value < 0) {
		*value = 0;
	}
}

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
 * PAL Address: 0x800a5204
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CRingMenu::~CRingMenu()
{
	reinterpret_cast<void (*)(CRingMenu*)>(reinterpret_cast<void**>(this)[4])(this);
	CMenu::Create();

	char* self = reinterpret_cast<char*>(this);
	*reinterpret_cast<int*>(self + 0x504) = 0;
	*reinterpret_cast<int*>(self + 0x500) = 0;
	*reinterpret_cast<int*>(self + 0x0C) = -1;
	*reinterpret_cast<int*>(self + 0x14) = 0x10;
	*reinterpret_cast<int*>(self + 0x10) = 1;
	*reinterpret_cast<int*>(self + 0x18) = 0;
	*reinterpret_cast<int*>(self + 0x20) = -1;
	*reinterpret_cast<int*>(self + 0x24) = -1;
	*reinterpret_cast<int*>(self + 0x38) = 0;
	*reinterpret_cast<int*>(self + 0x3C) = 0;
	*reinterpret_cast<int*>(self + 0x40) = 0;
	*reinterpret_cast<int*>(self + 0x1C) = 0;
	*reinterpret_cast<int*>(self + 0x28) = -1;
	*reinterpret_cast<int*>(self + 0x2C) = -1;
	*reinterpret_cast<int*>(self + 0x44) = 0;
	*reinterpret_cast<int*>(self + 0x48) = 0;
	*reinterpret_cast<int*>(self + 0x4C) = 0;
	*reinterpret_cast<int*>(self + 0x20) = 0;
	*reinterpret_cast<int*>(self + 0x30) = -1;
	*reinterpret_cast<int*>(self + 0x34) = -1;
	*reinterpret_cast<int*>(self + 0x50) = 0;
	*reinterpret_cast<int*>(self + 0x54) = 0;
	*reinterpret_cast<int*>(self + 0x58) = 0;
	*reinterpret_cast<int*>(self + 0x5C) = -1;
	*reinterpret_cast<int*>(self + 0x60) = -1;
	*reinterpret_cast<float*>(self + 0x64) = 0.0f;
	*reinterpret_cast<int*>(self + 0x4EC) = 0;
	*reinterpret_cast<int*>(self + 0x4F0) = 0;
	*reinterpret_cast<int*>(self + 0x4F4) = 0;
	*reinterpret_cast<int*>(self + 0x4F8) = 0;
	*reinterpret_cast<int*>(self + 0x4FC) = 0;
	*reinterpret_cast<int*>(self + 0x508) = 0;
	*reinterpret_cast<float*>(self + 0x50C) = 0.0f;
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
 * PAL Address: 0x800a51e4
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::Destroy()
{
	CMenu::Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x800a51ac
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
double CRingMenu::GetDispCounter()
{
	const int displayCounter = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x500);
	return -(static_cast<double>(static_cast<float>(displayCounter) * 0.0625f - 1.0f));
}

/*
 * --INFO--
 * PAL Address: 0x800a4c3c
 * PAL Size: 1392b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::onCalc()
{
	char* self = reinterpret_cast<char*>(this);

	if ((Game.game.m_gameWork.m_menuStageMode != 0) && (*reinterpret_cast<int*>(self + 0x0C) >= 1)) {
		return;
	}

	int* const menuIndex = reinterpret_cast<int*>(self + 0x0C);
	int* const animDirection = reinterpret_cast<int*>(self + 0x10);
	int* const transitionTimer = reinterpret_cast<int*>(self + 0x14);
	int* const displayCounter = reinterpret_cast<int*>(self + 0x500);
	int* const gbaAnimCounter = reinterpret_cast<int*>(self + 0x504);
	int* const gbaConnectedFlag = reinterpret_cast<int*>(self + 0x508);
	float* const commandScrollOffset = reinterpret_cast<float*>(self + 0x50C);
	int* const commonFrameCounter = reinterpret_cast<int*>(self + 0x4EC);
	int* const buttonTimers = reinterpret_cast<int*>(self + 0x38);
	int* const currentCommandIndex = reinterpret_cast<int*>(self + 0x5C);
	float* const animFloat = reinterpret_cast<float*>(self + 0x64);

	const int inputMask = *reinterpret_cast<int*>(CFlat + 0x12A0) & *reinterpret_cast<int*>(CFlat + 0x12A4);
	const int nextDirection = (inputMask >> 2) & 1;
	if (*animDirection != nextDirection) {
		*animDirection = nextDirection;
		*displayCounter = 0x10 - *displayCounter;
	}

	decClamp0(displayCounter);
	decClamp0(transitionTimer);
	*commonFrameCounter += 1;
	decClamp0(reinterpret_cast<int*>(self + 0x4F8));
	for (int i = 0; i < 8; i++) {
		decClamp0(&buttonTimers[i]);
	}
	decClamp0(reinterpret_cast<int*>(self + 0x4FC));

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			float& v = animFloat[i * 3 + j];
			v -= 0.1f;
			if (v < 0.0f) {
				v = 0.0f;
			}
		}
	}

	float& spinAccumulator = *reinterpret_cast<float*>(self + 0x4F4);
	spinAccumulator = (float)fmod(spinAccumulator, 360.0f);

	bool gbaConnected = Joybus.GetCtrlMode(*menuIndex) == 1;
	if (!Joybus.GetGBAStart(*menuIndex)) {
		gbaConnected = true;
	}

	const unsigned int padType = Joybus.GetPadType(*menuIndex);
	if ((padType == 0x09000000) || (padType == 0x8B100000)) {
		gbaConnected = false;
	}

	if (*gbaConnectedFlag != static_cast<int>(gbaConnected)) {
		*gbaConnectedFlag = static_cast<int>(gbaConnected);
		*gbaAnimCounter = 0x0C - *gbaAnimCounter;
	}
	decClamp0(gbaAnimCounter);

	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.game.m_scriptFoodBase[*menuIndex]);
	if (caravanWork == nullptr) {
		return;
	}

	int commandIndex = static_cast<int>(caravanWork->m_currentCmdListIndex);
	if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
		commandIndex = *reinterpret_cast<int*>(Chara + 0x2008);
	}

	float step = 0.0f;
	if (*currentCommandIndex != commandIndex) {
		for (int dist = 1; dist < 4; dist++) {
			const int cw = (commandIndex + dist) % 5;
			const int ccw = (commandIndex + 5 - dist) % 5;
			if (*currentCommandIndex == ccw) {
				step = static_cast<float>(dist);
				break;
			}
			if (*currentCommandIndex == cw) {
				step = -static_cast<float>(dist);
				break;
			}
		}
	}

	*currentCommandIndex = commandIndex;
	*commandScrollOffset = (*commandScrollOffset + step) * 0.95f;
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
	if (newCommandId == 0) {
		newCommandId = -1;
	}

	int slot8 = buttonGroupIndex * 8;
	int currentCommand = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slot8 + 0x20);

	if (currentCommand == newCommandId) {
		return;
	}

	if (((currentCommand >= 0) && (newCommandId < 0)) || ((currentCommand < 0) && (newCommandId >= 0))) {
		int slot12 = buttonGroupIndex * 12;
		int* timer2 = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slot12 + 0x40);
		*timer2 = 8 - *timer2;
	}

	*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slot8 + 0x24) = currentCommand;
	*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slot8 + 0x20) = newCommandId;

	int slot12 = buttonGroupIndex * 12;
	char* self = reinterpret_cast<char*>(this);
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
