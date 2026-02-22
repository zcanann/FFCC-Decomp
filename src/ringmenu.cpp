#include "ffcc/ringmenu.h"
#include "ffcc/gobjwork.h"
#include "ffcc/joybus.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"

#include <math.h>

extern "C" int __cntlzw(unsigned int);
extern "C" int _GetIdxCmdList__12CCaravanWorkFv(CCaravanWork*);
extern "C" int GetNextCmdListIdx__12CCaravanWorkFii(CCaravanWork*, int, int);

extern unsigned char CFlat[];
extern unsigned char Chara[];
extern char DAT_801da01c[];
extern float FLOAT_803309c0;
extern float FLOAT_80330a54;
extern float FLOAT_80330ae8;
extern double DOUBLE_80330a98;

static inline int& RingMenuInt(CRingMenu* ringMenu, int offset)
{
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(ringMenu) + offset);
}

static inline float& RingMenuFloat(CRingMenu* ringMenu, int offset)
{
	return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(ringMenu) + offset);
}

static inline int clampDecToZero(int value)
{
	unsigned int next = static_cast<unsigned int>(value - 1);
	return static_cast<int>(next & ~static_cast<unsigned int>(static_cast<int>(next) >> 31));
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
	const int menuIndex = RingMenuInt(this, 0x0C);
	if ((Game.game.m_gameWork.m_menuStageMode == 0) || (menuIndex < 1)) {
		const int animDirection = RingMenuInt(this, 0x10);
		const unsigned int flatFlag0 = *reinterpret_cast<unsigned int*>(CFlat + 0x12A0);
		const unsigned int flatFlag1 = *reinterpret_cast<unsigned int*>(CFlat + 0x12A4);
		const int targetAnimDirection = static_cast<int>((flatFlag0 & flatFlag1) >> 2 & 1);

		if (animDirection != targetAnimDirection) {
			System.Printf(DAT_801da01c, menuIndex);
			RingMenuInt(this, 0x10) = targetAnimDirection;
			RingMenuInt(this, 0x500) = 0x10 - RingMenuInt(this, 0x500);
		}

		RingMenuInt(this, 0x500) = clampDecToZero(RingMenuInt(this, 0x500));
		RingMenuInt(this, 0x4EC) = clampDecToZero(RingMenuInt(this, 0x4EC));
		RingMenuInt(this, 0x4F0) = RingMenuInt(this, 0x4F0) + 1;
		RingMenuInt(this, 0x4F4) = clampDecToZero(RingMenuInt(this, 0x4F4));

		for (int i = 0; i < 8; i++) {
			RingMenuInt(this, 0x38 + i * 4) = clampDecToZero(RingMenuInt(this, 0x38 + i * 4));
		}
		RingMenuInt(this, 0x4F8) = clampDecToZero(RingMenuInt(this, 0x4F8));

		for (int i = 0; i < 9; i++) {
			float* animFloat = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x64 + i * 0x4C);
			for (int j = 0; j < 3; j++) {
				animFloat[j] = animFloat[j] - FLOAT_80330a54;
				if (animFloat[j] < FLOAT_803309c0) {
					animFloat[j] = FLOAT_803309c0;
				}
			}
		}

		fmod(static_cast<double>(RingMenuFloat(this, 0x50C)), DOUBLE_80330a98);
		for (volatile int i = 0x1B; i != 0; i--) {
		}

		unsigned int gbaConnected =
			(static_cast<unsigned int>(__cntlzw(1 - static_cast<int>(Joybus.GetCtrlMode(menuIndex)))) >> 5) & 0xFF;

		if (!Joybus.GetGBAStart(menuIndex)) {
			gbaConnected = 1;
		}

		const unsigned int padType = Joybus.GetPadType(menuIndex);
		if ((padType == 0x09000000) || (padType == 0x8B100000)) {
			gbaConnected = 0;
		}

		if (RingMenuInt(this, 0x4FC) != static_cast<int>(gbaConnected)) {
			RingMenuInt(this, 0x4FC) = static_cast<int>(gbaConnected);
			RingMenuInt(this, 0x508) = 0x0C - RingMenuInt(this, 0x508);
		}
		RingMenuInt(this, 0x508) = clampDecToZero(RingMenuInt(this, 0x508));

		CGPartyObj* partyObj = Game.game.m_partyObjArr[menuIndex];
		if (partyObj != 0) {
			(void)partyObj;
			CCaravanWork* caravanWork = &Game.game.m_caravanWorkArr[menuIndex];
			int currentCmd = *reinterpret_cast<int*>(Chara + 0x2004);

			if (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x19) {
				currentCmd = _GetIdxCmdList__12CCaravanWorkFv(caravanWork);
			}

			int* trackedCmd = &RingMenuInt(this, 0x504);
			if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
				trackedCmd = reinterpret_cast<int*>(Chara + 0x2008);
			}

			double scrollDelta = 0.0;
			if (*trackedCmd != currentCmd) {
				int prev = currentCmd;
				int next = currentCmd;
				for (int step = 1; step < 4; step++) {
					int nextCandidate = (currentCmd + step) % 5;
					int prevCandidate = (currentCmd + 5 - step) % 5;

					if (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x19) {
						nextCandidate = GetNextCmdListIdx__12CCaravanWorkFii(caravanWork, next, 1);
						prevCandidate = GetNextCmdListIdx__12CCaravanWorkFii(caravanWork, prev, -1);
					}

					prev = prevCandidate;
					next = nextCandidate;

					if (*trackedCmd == prevCandidate) {
						scrollDelta = static_cast<double>(step);
						break;
					}
					if (*trackedCmd == nextCandidate) {
						scrollDelta = -static_cast<double>(step);
						break;
					}
				}

				if (scrollDelta == 0.0) {
					int dirPos = (*trackedCmd == prev) ? 1 : 0;
					int dirNeg = (*trackedCmd == next) ? 1 : 0;
					if (dirPos != 0 && dirNeg != 0) {
						unsigned short trigger = 0;
						if ((Pad._452_4_ == 0) && !((menuIndex == 0) && (Pad._448_4_ != -1))) {
							const int idx =
								menuIndex &
								~(static_cast<int>(~(Pad._448_4_ - menuIndex | menuIndex - Pad._448_4_)) >> 31);
							trigger = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 4 + idx * 0x54);
						}
						scrollDelta = ((trigger & 0x40) != 0) ? static_cast<double>(dirPos) : -static_cast<double>(dirNeg);
					} else if (dirPos != 0) {
						scrollDelta = static_cast<double>(dirPos);
					} else if (dirNeg != 0) {
						scrollDelta = -static_cast<double>(dirNeg);
					}
				}
			}

			*trackedCmd = currentCmd;
			RingMenuFloat(this, 0x50C) =
				(RingMenuFloat(this, 0x50C) + static_cast<float>(scrollDelta)) * FLOAT_80330ae8;
		}
	}
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
