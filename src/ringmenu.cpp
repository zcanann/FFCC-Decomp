#include "ffcc/ringmenu.h"
#include "ffcc/fontman.h"
#include "ffcc/gobjwork.h"
#include "ffcc/joybus.h"
#include "ffcc/math.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <math.h>

extern "C" int __cntlzw(unsigned int);
extern "C" int _GetIdxCmdList__12CCaravanWorkFv(CCaravanWork*);
extern "C" int _GetWeaponAttrib__12CCaravanWorkFi(CCaravanWork*, int);
extern "C" int GetNextCmdListIdx__12CCaravanWorkFii(CCaravanWork*, int, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(void*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(void*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void SetColor__8CMenuPcsFR6CColor(void*, void*);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void SetTlut__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" int GetWidth__5CFontFPc(CFont*, int);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void SetPosZ__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, int);
extern "C" void SetExternalTlut__8CTextureFPvi(void*, void*, int);
extern "C" void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int, int, int, int, int);
extern "C" void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int, int, int, int, int);
extern "C" void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(
    int, int, int, int, int, int);
extern "C" void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(
    int, int, int, int, int, int);
extern "C" void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" asm void MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d(register void*, register float (*)[4], register Vec*,
                                                            register void*);

extern unsigned char CFlat[];
extern unsigned char Chara[];
extern unsigned char CameraPcs[];
extern unsigned char DAT_8020fab8[];
extern unsigned char MenuPcs[];
extern char DAT_801da01c[];
extern float FLOAT_803309c0;
extern float FLOAT_803309c4;
extern float FLOAT_803309c8;
extern float FLOAT_803309cc;
extern float FLOAT_803309d0;
extern float FLOAT_803309d4;
extern float FLOAT_803309d8;
extern float FLOAT_803309dc;
extern float FLOAT_803309e0;
extern float FLOAT_803309e4;
extern float FLOAT_803309e8;
extern float FLOAT_803309ec;
extern float FLOAT_803309f0;
extern float FLOAT_803309f4;
extern float FLOAT_803309f8;
extern float FLOAT_80330a54;
extern float FLOAT_80330a28;
extern float FLOAT_80330a34;
extern float FLOAT_80330a40;
extern float FLOAT_80330aa8;
extern float FLOAT_80330ac4;
extern float FLOAT_80330ae8;
extern double DOUBLE_80330a00;
extern double DOUBLE_80330a98;
extern double DOUBLE_80330ac8;
extern double DOUBLE_80330ad0;
extern double DOUBLE_80330ad8;
extern double DOUBLE_80330ae0;

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

struct Vec4d
{
	float x;
	float y;
	float z;
	float w;
};

static inline unsigned int frameNibble(int value)
{
	int sign = value >> 31;
	return static_cast<unsigned int>((sign * 0x10 | (value * 0x10000000 + sign) >> 28) - sign);
}

struct RingMenuFlatTableEntry
{
	int count;
	const char** strings;
	char* stringBuf;
};

struct RingMenuFlatData
{
	char pad0[0x6C];
	RingMenuFlatTableEntry table[8];
};

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
 * PAL Address: 0x800a48f0
 * PAL Size: 844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void drawCommand(int state, CFont* font, float posX, float posY, CCaravanWork* caravanWork, int cmdIndex, float angle, float alphaScale)
{
	const RingMenuFlatData* flatData = reinterpret_cast<const RingMenuFlatData*>(&Game.game.m_cFlatDataArr[1]);
	const int* cmdNameTable = reinterpret_cast<const int*>(flatData->table[4].strings);

	int commandLabel;
	if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
		commandLabel = cmdNameTable[cmdIndex + 0x1E];
	} else if (cmdIndex < 2) {
		commandLabel = cmdNameTable[(cmdIndex == 0) ? 1 : 9];
	} else {
		commandLabel = _GetWeaponAttrib__12CCaravanWorkFi(caravanWork, cmdIndex);
	}

	int tlut = 7;
	if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
		if (cmdIndex == 2) {
			tlut = 4;
		} else if (cmdIndex < 2) {
			if (cmdIndex == 0) {
				tlut = 2;
			} else if (cmdIndex >= 0) {
				tlut = 1;
			}
		} else if ((cmdIndex < 4) && (cmdIndex != 4)) {
			tlut = 6;
		}
	} else if (cmdIndex != 0) {
		tlut = 4;
	}
	SetTlut__5CFontFi(font, tlut);

	const double angleSin = sin(static_cast<double>(angle));
	const double waveX = static_cast<double>(FLOAT_80330ac4 * static_cast<float>(angleSin));

	const bool reverseDir = (state == 0) || (state == 3);
	double waveY = static_cast<double>((reverseDir ? -FLOAT_80330a40 : FLOAT_80330a40) * static_cast<float>(angleSin));
	if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
		waveY += static_cast<double>(FLOAT_80330a28);
	}

	SetScale__5CFontFf(static_cast<float>(-(DOUBLE_80330ad0 * fabs(static_cast<double>(angle)) - DOUBLE_80330ac8)), font);

	const int textWidth = GetWidth__5CFontFPc(font, commandLabel);
	const float alphaRange = static_cast<float>(-(DOUBLE_80330ad8 * fabs(static_cast<double>(angle)) - DOUBLE_80330a98));
	float clampedAlpha = FLOAT_803309c0;
	if (alphaRange >= FLOAT_803309c0) {
		clampedAlpha = alphaRange;
		if (alphaRange > FLOAT_803309cc) {
			clampedAlpha = FLOAT_803309cc;
		}
	}

	const int alpha = static_cast<int>(FLOAT_80330a34 * alphaScale * clampedAlpha);
	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha)};
	SetColor__5CFontF8_GXColor(font, &color);

	const float textX = static_cast<float>(waveX + static_cast<double>(posX + FLOAT_80330aa8) - static_cast<double>(textWidth) * DOUBLE_80330ae0);
	const double textHeight = static_cast<double>(font->m_glyphWidth) * font->scaleY;
	const float textY = static_cast<float>(FLOAT_80330a40 + waveY + static_cast<double>(posY + FLOAT_803309ec) - textHeight * DOUBLE_80330ae0);

	SetPosX__5CFontFf(textX, font);
	SetPosY__5CFontFf(textY, font);
	SetPosZ__5CFontFf(FLOAT_803309c0, font);
	Draw__5CFontFPc(font, commandLabel);
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
	drawGBA();

	if (!((Game.game.m_gameWork.m_menuStageMode == 0) || (RingMenuInt(this, 0x0C) < 2))) {
		return;
	}

	const unsigned int flatFlags = *reinterpret_cast<unsigned int*>(CFlat + 0x12A0) &
	                               *reinterpret_cast<unsigned int*>(CFlat + 0x12A4);
	if ((flatFlags & 1) == 0) {
		return;
	}

	int menuIndex = RingMenuInt(this, 0x0C);
	CGPartyObj* partyObj = Game.game.m_partyObjArr[menuIndex];
	if (partyObj == 0 || static_cast<signed char>(*reinterpret_cast<unsigned char*>(&partyObj->m_weaponNodeFlags + 1)) >= 0) {
		return;
	}

	unsigned int scriptFood = Game.game.m_scriptFoodBase[menuIndex];
	Mtx cameraMtx;
	PSMTXCopy(*reinterpret_cast<Mtx*>(CameraPcs + 0x4), cameraMtx);

	Vec offset;
	offset.x = FLOAT_803309c0;
	offset.y = FLOAT_803309c4 * partyObj->unk_0x188;
	offset.z = FLOAT_803309c0;

	Vec worldPos;
	PSVECAdd(&partyObj->m_worldPosition, &offset, &worldPos);

	Vec viewPos;
	PSMTXMultVec(cameraMtx, &worldPos, &viewPos);
	if (viewPos.z < FLOAT_803309c8) {
		viewPos.z = FLOAT_803309c8;
	}

	Mtx44 screenMtx;
	PSMTX44Copy(*reinterpret_cast<Mtx44*>(CameraPcs + 0x48), screenMtx);
	Vec4d clipPos;
	MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d(0, screenMtx, &viewPos, &clipPos);

	float screenX = clipPos.x * (FLOAT_803309cc / clipPos.w);
	float screenY = clipPos.y * (FLOAT_803309cc / clipPos.w);
	if ((FLOAT_803309d0 < screenX) && (screenX < FLOAT_803309cc) && (FLOAT_803309d0 < screenY) &&
	    (screenY < FLOAT_803309cc)) {
		return;
	}

	float clampedX = FLOAT_803309d4;
	if (FLOAT_803309d4 <= screenX) {
		clampedX = screenX;
		if (FLOAT_803309d8 < screenX) {
			clampedX = FLOAT_803309d8;
		}
	}

	float clampedY = FLOAT_803309dc;
	if (FLOAT_803309dc <= screenY) {
		clampedY = screenY;
		if (FLOAT_803309e0 < screenY) {
			clampedY = FLOAT_803309e0;
		}
	}

	(void)atan2(static_cast<double>(clampedX), static_cast<double>(clampedY));

	double posX = static_cast<double>(FLOAT_803309e4 * clampedX + FLOAT_803309e4);
	double posY = -static_cast<double>(FLOAT_803309e8 * clampedY - FLOAT_803309e8);
	unsigned char blinkAlpha = DAT_8020fab8[frameNibble(System.m_frameCounter)];

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcs, 0x19);
	int iconRow;
	unsigned int iconCol;
	if ((Game.game.m_gameWork.m_menuStageMode == 0) || (menuIndex < 1)) {
		iconRow = *reinterpret_cast<int*>(scriptFood + 0x3B4);
		int progress = static_cast<int>(*reinterpret_cast<unsigned short*>(scriptFood + 0x14)) - 100;
		int q = progress / 100 + (progress >> 31);
		iconCol = static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(scriptFood + 0x14)) % 100 +
		          static_cast<unsigned int>((q - (q >> 31)) * 4);
	} else {
		iconRow = 1;
		iconCol = 0x65;
	}

	unsigned int bgColor[1];
	__ct__6CColorFUcUcUcUc(bgColor, 0, 0, 0, 0x80);
	SetColor__8CMenuPcsFR6CColor(MenuPcs, bgColor);
	DrawRect__8CMenuPcsFUlfffffffff(MenuPcs, 3, static_cast<float>(FLOAT_803309ec + posX),
	                                 static_cast<float>(FLOAT_803309ec + posY), FLOAT_803309f0, FLOAT_803309f0,
	                                 FLOAT_803309c0, FLOAT_803309c0, FLOAT_803309cc, FLOAT_803309cc, 0.0f);

	unsigned int fgColor[1];
	__ct__6CColorFUcUcUcUc(fgColor, 0xFF, 0xFF, 0xFF, 0xFF);
	SetColor__8CMenuPcsFR6CColor(MenuPcs, fgColor);
	DrawRect__8CMenuPcsFUlfffffffff(
	    MenuPcs, 3, static_cast<float>(posX), static_cast<float>(posY), FLOAT_803309f0, FLOAT_803309f0, FLOAT_803309c0,
	    static_cast<float>(iconRow * 0x38), FLOAT_803309cc, FLOAT_803309cc,
	    0.0f);

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcs, 0x18);
	void* tlut = reinterpret_cast<void*>(0x802EA500);
	if (*reinterpret_cast<short*>(scriptFood + 0x1C) != 0) {
		tlut = 0;
	}
	SetExternalTlut__8CTextureFPvi(*reinterpret_cast<void**>(MenuPcs + 0x1EC), tlut, 1);
	GXSetTevDirect(GX_TEVSTAGE2);
	_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xF, 0, 0xC, 0xB);
	_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 0, 6, 7);
	_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 3, 1, 0);
	_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0xFF, 0xFF, 4);

	unsigned int iconColor[1];
	__ct__6CColorFUcUcUcUc(iconColor, 0xFF, 0xFF, 0xFF, blinkAlpha);
	SetColor__8CMenuPcsFR6CColor(MenuPcs, iconColor);

	int signedIconCol = static_cast<int>(iconCol);
	int colSign = signedIconCol >> 31;
	float u = static_cast<float>((((colSign * 8) | (signedIconCol * 0x20000000 + colSign) >> 29) - colSign) * 0x30);
	float v = static_cast<float>(((signedIconCol >> 3) + ((signedIconCol < 0) && ((iconCol & 7) != 0))) * 0x30);
	DrawRect__8CMenuPcsFUlfffffffff(MenuPcs, 3, static_cast<float>(posX), static_cast<float>(posY), FLOAT_803309f4,
	                                 FLOAT_803309f4, u, v, FLOAT_803309f8, FLOAT_803309f8, 0.0f);
}
