#include "ffcc/ringmenu.h"
#include "ffcc/fontman.h"
#include "ffcc/gobjwork.h"
#include "ffcc/joybus.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/p_menu.h"
#include "ffcc/pad.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <math.h>

extern "C" int __cntlzw(unsigned int);
extern "C" void* __vt__9CRingMenu[];
extern "C" int _GetIdxCmdList__12CCaravanWorkFv(CCaravanWork*);
extern "C" int _GetWeaponAttrib__12CCaravanWorkFi(CCaravanWork*, int);
extern "C" int GetNextCmdListIdx__12CCaravanWorkFii(CCaravanWork*, int, int);
extern "C" CMenu* __dt__5CMenuFv(CMenu*, short);
extern "C" void __dl__FPv(void*);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(void*, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(void*, int);
extern "C" void DrawInit__8CMenuPcsFv(void*);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(void*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void SetColor__8CMenuPcsFR6CColor(void*, void*);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void SetTlut__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void SetScaleX__5CFontFf(float, CFont*);
extern "C" void SetScaleY__5CFontFf(float, CFont*);
extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" int GetWidth__5CFontFPc(CFont*, int);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void SetPosZ__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, int);
extern "C" void DrawInit__5CFontFv(CFont*);
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
extern "C" int GetGBAStart__6JoyBusFi(void*, int);
extern "C" int IsInitSend__6JoyBusFi(void*, int);

extern unsigned char DAT_8020fab8[];
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
extern float FLOAT_80330a08;
extern float FLOAT_80330a0c;
extern float FLOAT_80330a10;
extern float FLOAT_80330a14;
extern float FLOAT_80330a18;
extern float FLOAT_80330a54;
extern float FLOAT_80330a5c;
extern float FLOAT_80330a60;
extern float FLOAT_80330a64;
extern float FLOAT_80330a68;
extern float FLOAT_80330a6c;
extern float FLOAT_80330a70;
extern float FLOAT_80330a74;
extern float FLOAT_80330a78;
extern float FLOAT_80330a7c;
extern float FLOAT_80330a80;
extern float FLOAT_80330a84;
extern float FLOAT_80330a88;
extern float FLOAT_80330a8c;
extern float FLOAT_80330a2c;
extern float FLOAT_80330a30;
extern float FLOAT_80330a28;
extern float FLOAT_80330a34;
extern float FLOAT_80330a38;
extern float FLOAT_80330a3c;
extern float FLOAT_80330a40;
extern float FLOAT_80330a44;
extern float FLOAT_80330a48;
extern float FLOAT_80330a4c;
extern float FLOAT_80330a58;
extern float FLOAT_80330aac;
extern float FLOAT_80330ab0;
extern float FLOAT_80330ab4;
extern float FLOAT_80330ab8;
extern float FLOAT_80330abc;
extern float FLOAT_80330ac0;
extern float FLOAT_80330aa8;
extern float FLOAT_80330ac4;
extern float FLOAT_80330ae8;
extern double DOUBLE_80330a00;
extern double DOUBLE_80330a20;
extern double DOUBLE_80330a90;
extern double DOUBLE_80330a98;
extern double DOUBLE_80330aa0;
extern double DOUBLE_80330ac8;
extern double DOUBLE_80330ad0;
extern double DOUBLE_80330ad8;
extern double DOUBLE_80330ae0;

static inline void* MenuPcsVoid()
{
    return &MenuPcs;
}

static inline unsigned char* MenuPcsRaw()
{
    return reinterpret_cast<unsigned char*>(&MenuPcs);
}

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
 * PAL Address: 0x800a52dc
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::Create()
{
	register short shouldDelete;
	asm {
		mr shouldDelete, r4
	}

	if (this == 0) {
		return;
	}

	*reinterpret_cast<void***>(this) = __vt__9CRingMenu;
	reinterpret_cast<void (*)(CRingMenu*)>(reinterpret_cast<void**>(this)[4])(this);
	__dt__5CMenuFv(this, 0);
	if (0 < shouldDelete) {
		__dl__FPv(this);
	}
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
	const int displayCounter = RingMenuInt(this, 0x500);
	const float scaled = FLOAT_80330a08 * static_cast<float>(displayCounter) - FLOAT_803309cc;
	return -static_cast<double>(scaled);
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
	if ((Game.m_gameWork.m_menuStageMode == 0) || (menuIndex < 1)) {
		const int animDirection = RingMenuInt(this, 0x10);
		const unsigned int targetAnimDirection =
			((*reinterpret_cast<unsigned int*>(CFlat + 0x12A0) & *reinterpret_cast<unsigned int*>(CFlat + 0x12A4)) >> 2) & 1;
		if (animDirection != static_cast<int>(targetAnimDirection)) {
			System.Printf(DAT_801da01c, menuIndex);
			RingMenuInt(this, 0x10) = (static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(animDirection))) >> 5) & 0xFF;
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
		volatile int i = 0x1B;
		do {
			i--;
		} while (i != 0);

		unsigned int gbaConnected =
			(static_cast<unsigned int>(__cntlzw(1 - static_cast<int>(Joybus.GetCtrlMode(menuIndex)))) >> 5) & 0xFF;

		if (!Joybus.GetGBAStart(menuIndex)) {
			gbaConnected = 1;
		}

		if ((Joybus.GetPadType(menuIndex) == 0x09000000) || (Joybus.GetPadType(menuIndex) == 0x8B100000)) {
			gbaConnected = 0;
		}

		if (RingMenuInt(this, 0x4FC) != static_cast<int>(gbaConnected)) {
			RingMenuInt(this, 0x4FC) = static_cast<int>(gbaConnected);
			RingMenuInt(this, 0x508) = 0x0C - RingMenuInt(this, 0x508);
		}
		RingMenuInt(this, 0x508) = clampDecToZero(RingMenuInt(this, 0x508));

		CGPartyObj* partyObj = Game.m_partyObjArr[menuIndex];
		if (partyObj != 0) {
			(void)partyObj;
			CCaravanWork* caravanWork = &Game.m_caravanWorkArr[menuIndex];
			int currentCmd = *reinterpret_cast<int*>(Chara + 0x2004);

			if (Game.m_gameWork.m_bossArtifactStageIndex != 0x19) {
				currentCmd = _GetIdxCmdList__12CCaravanWorkFv(caravanWork);
			}

			int* trackedCmd = &RingMenuInt(this, 0x504);
			if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
				trackedCmd = reinterpret_cast<int*>(Chara + 0x2008);
			}

			double scrollDelta = 0.0;
			if (*trackedCmd != currentCmd) {
				int prev = currentCmd;
				int next = currentCmd;
				for (int step = 1; step < 4; step++) {
					int nextCandidate = (currentCmd + step) % 5;
					int prevCandidate = (currentCmd + 5 - step) % 5;

					if (Game.m_gameWork.m_bossArtifactStageIndex != 0x19) {
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
	const RingMenuFlatData* flatData = reinterpret_cast<const RingMenuFlatData*>(&Game.m_cFlatDataArr[1]);
	const int* cmdNameTable = reinterpret_cast<const int*>(flatData->table[4].strings);
	const bool isBossStage = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19);

	int commandLabel;
	if (isBossStage) {
		commandLabel = cmdNameTable[cmdIndex + 0x1E];
	} else if (cmdIndex < 2) {
		commandLabel = cmdNameTable[(cmdIndex == 0) ? 1 : 9];
	} else {
		commandLabel = _GetWeaponAttrib__12CCaravanWorkFi(caravanWork, cmdIndex);
	}

	if (isBossStage) {
		if (cmdIndex == 2) {
			SetTlut__5CFontFi(font, 4);
		} else if (cmdIndex < 2) {
			if (cmdIndex == 0) {
				SetTlut__5CFontFi(font, 2);
			} else if (cmdIndex >= 0) {
				SetTlut__5CFontFi(font, 1);
			} else {
				SetTlut__5CFontFi(font, 7);
			}
		} else if (cmdIndex == 4) {
			SetTlut__5CFontFi(font, 7);
		} else if (cmdIndex < 4) {
			SetTlut__5CFontFi(font, 6);
		} else {
			SetTlut__5CFontFi(font, 7);
		}
	} else if (cmdIndex == 0) {
		SetTlut__5CFontFi(font, 7);
	} else {
		SetTlut__5CFontFi(font, 4);
	}

	const double waveX = static_cast<double>(FLOAT_80330ac4 * static_cast<float>(sin(static_cast<double>(angle))));

	float waveDir = FLOAT_80330a40;
	if ((state == 0) || (state == 3)) {
		waveDir = -waveDir;
	}
	double waveY = static_cast<double>(waveDir * static_cast<float>(sin(static_cast<double>(angle))));
	if (isBossStage) {
		waveY = static_cast<double>(static_cast<float>(waveY + static_cast<double>(FLOAT_80330a28)));
	}

	SetScale__5CFontFf(static_cast<float>(-(DOUBLE_80330ad0 * fabs(static_cast<double>(angle)) - DOUBLE_80330ac8)), font);

	const double textWidth = static_cast<double>(GetWidth__5CFontFPc(font, commandLabel));
	const float alphaRange = static_cast<float>(-(DOUBLE_80330ad8 * fabs(static_cast<double>(angle)) - DOUBLE_80330a98));
	float clampedAlpha = FLOAT_803309c0;
	if (alphaRange >= FLOAT_803309c0) {
		clampedAlpha = alphaRange;
		if (alphaRange > FLOAT_803309cc) {
			clampedAlpha = FLOAT_803309cc;
		}
	}

	const int alpha = static_cast<int>(static_cast<float>(static_cast<double>(FLOAT_80330a34) * static_cast<double>(alphaScale)) * clampedAlpha);
	unsigned int colorRaw[1];
	__ct__6CColorFUcUcUcUc(colorRaw, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha));
	SetColor__5CFontF8_GXColor(font, reinterpret_cast<GXColor*>(colorRaw));

	const double textHeight = static_cast<double>(font->m_glyphWidth) * font->scaleY;
	const float textX = static_cast<float>(
		waveX + -(static_cast<double>(static_cast<float>(textWidth * static_cast<double>(FLOAT_803309c4) -
		                                                static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_80330aa8) +
		                                                                                       static_cast<double>(posX)))))));
	const float textY = FLOAT_80330a40 +
	                    static_cast<float>(waveY + -(static_cast<double>(static_cast<float>(textHeight * static_cast<double>(FLOAT_803309c4) -
	                                                                                         static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_803309ec) +
	                                                                                                                            static_cast<double>(posY)))))));

	SetPosX__5CFontFf(textX, font);
	SetPosY__5CFontFf(textY, font);
	SetPosZ__5CFontFf(FLOAT_803309c0, font);
	Draw__5CFontFPc(font, commandLabel);
}

/*
 * --INFO--
 * PAL Address: 0x800a39c4
 * PAL Size: 3884b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::onDraw()
{
	const int menuIndex = RingMenuInt(this, 0x0C);
	const RingMenuFlatData* flatData = reinterpret_cast<const RingMenuFlatData*>(&Game.m_cFlatDataArr[1]);
	if (!((Game.m_gameWork.m_menuStageMode == 0) || (menuIndex < 1))) {
		return;
	}

	unsigned int scriptFood = Game.m_scriptFoodBase[menuIndex];
	if (scriptFood == 0) {
		return;
	}

	double showScale = static_cast<double>(static_cast<float>(RingMenuInt(this, 0x500)) * FLOAT_80330a08);
	if (RingMenuInt(this, 0x10) != 0) {
		showScale = static_cast<double>(FLOAT_803309cc) - showScale;
	}
	if (showScale == static_cast<double>(FLOAT_803309c0)) {
		return;
	}

	double transitionScale = static_cast<double>(static_cast<float>(RingMenuInt(this, 0x4EC)) * FLOAT_80330a08);
	if (RingMenuInt(this, 0x10) != 0) {
		transitionScale = -static_cast<double>(static_cast<float>(
			static_cast<double>(static_cast<float>(RingMenuInt(this, 0x4EC)) * FLOAT_80330a08) - FLOAT_803309cc));
	}

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x16);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

	float cycle = static_cast<float>(
		fmod(static_cast<double>(FLOAT_80330a18 * static_cast<float>(RingMenuInt(this, 0x4F4))), DOUBLE_80330a20));
	if (cycle > FLOAT_803309cc) {
		cycle = FLOAT_80330a28 - cycle;
	}

	const double pulse = sin(static_cast<double>(FLOAT_80330a0c) * showScale);

	const float alphaScaleBase = FLOAT_80330a34 * static_cast<float>(showScale * transitionScale);
	const float glowOffset = FLOAT_80330a5c * (FLOAT_803309cc - static_cast<float>(pulse));
	const float iconAlphaScale = static_cast<float>(showScale * transitionScale);

	const float posAltX = FLOAT_80330a60 + glowOffset;
	const float posAltY = FLOAT_80330a64 + glowOffset;
	const float posLeft = -glowOffset;
	const float posMainX = posAltX - FLOAT_80330a68;
	const float posMainY = FLOAT_80330a6c + glowOffset;

	for (int group = 2; group >= 0; group--) {
		float posX;
		float posY;

		if (group == 2) {
			float sideX = posLeft;
			if ((menuIndex & 1) != 0) {
				sideX = posAltX;
			}
			posX = FLOAT_80330a70 + sideX;

			float sideY = posLeft;
			if ((menuIndex & 2) != 0) {
				sideY = posAltY;
			}
			posY = FLOAT_80330a44 + sideY;
		} else {
			float sideX = posLeft;
			if ((menuIndex & 1) != 0) {
				sideX = posMainX;
			}
			posX = FLOAT_80330a68 + sideX;

			float sideY = posLeft;
			if ((menuIndex & 2) != 0) {
				sideY = posMainY;
			}
			posY = FLOAT_80330a74 + sideY;
		}

		double buttonAlpha = static_cast<double>(static_cast<float>(RingMenuInt(this, 0x40 + group * 0x0C)) * FLOAT_80330a78);
		if (RingMenuInt(this, 0x20 + group * 0x08) >= 0) {
			buttonAlpha = static_cast<double>(FLOAT_803309cc) - buttonAlpha;
		}

		if (group == 2) {
			CGPartyObj* partyObj = Game.m_partyObjArr[menuIndex];
			if (partyObj != 0) {
				buttonAlpha = static_cast<double>((-static_cast<int>(*reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(partyObj) + 0x6F4)) & 9) >> 31);
			}
		}

		if (buttonAlpha == static_cast<double>(FLOAT_803309c0)) {
			continue;
		}

		SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x1F);
		unsigned int buttonColor[1];
		__ct__6CColorFUcUcUcUc(buttonColor, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(static_cast<int>(buttonAlpha * alphaScaleBase)));
		SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), buttonColor);

		float drawX = posX;
		float drawY = posY;
		if (group == 1 || group == 0) {
			const float wobble = static_cast<float>(sin(static_cast<double>(FLOAT_80330a0c) * buttonAlpha));
			drawX = -(FLOAT_80330a70 * wobble - ((group == 0) ? (FLOAT_80330a10 + posX) : posX));
			drawY = posY + ((group == 1) ? FLOAT_80330a80 : FLOAT_803309c0);
		}

		if (group == 2) {
			DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 0, posX, posY, FLOAT_80330a84, FLOAT_80330a5c, FLOAT_803309c0, FLOAT_80330a88,
			                                 FLOAT_803309cc, FLOAT_803309cc, 0.0f);
		} else if (group == 1) {
			DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 0, drawX, drawY, FLOAT_80330a7c, FLOAT_80330a80, FLOAT_803309c0, FLOAT_80330a5c,
			                                 FLOAT_803309cc, FLOAT_803309cc, 0.0f);
			DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 0, drawX, drawY, FLOAT_80330a80, FLOAT_80330a80, FLOAT_80330a68, FLOAT_803309f0,
			                                 FLOAT_803309cc, FLOAT_803309cc, 0.0f);
		} else {
			DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 0, drawX, drawY, FLOAT_80330a7c, FLOAT_80330a5c, FLOAT_803309c0, FLOAT_803309c0,
			                                 FLOAT_803309cc, FLOAT_803309cc, 0.0f);
			DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 0, drawX, drawY, FLOAT_80330a68, FLOAT_80330a5c, FLOAT_803309c0, FLOAT_803309f0,
			                                 FLOAT_803309cc, FLOAT_803309cc, 0.0f);
		}

		if (group == 2) {
			CGPartyObj* partyObj = Game.m_partyObjArr[menuIndex];
			if (partyObj != 0) {
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(
					reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(partyObj) + 0x5C)[0]);
				int cmdIndex = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                   ? *reinterpret_cast<int*>(Chara + 0x2004)
				                   : _GetIdxCmdList__12CCaravanWorkFv(caravanWork);

				CFont* font = reinterpret_cast<CFont*>(*reinterpret_cast<int*>(MenuPcsRaw() + 0xFC));
				DrawInit__5CFontFv(font);
				SetMargin__5CFontFf(FLOAT_80330a8c, font);
				SetShadow__5CFontFi(font, 1);
				SetTlut__5CFontFi(font, 4);

				double scroll = static_cast<double>(RingMenuFloat(this, 0x50C));
				while (scroll >= static_cast<double>(FLOAT_803309cc)) {
					if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
						cmdIndex = (cmdIndex + 1) % 5;
					} else {
						cmdIndex = GetNextCmdListIdx__12CCaravanWorkFii(caravanWork, cmdIndex, -1);
					}
					scroll -= static_cast<double>(FLOAT_803309cc);
				}
				while (scroll < static_cast<double>(FLOAT_803309d0)) {
					if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
						cmdIndex = (cmdIndex + 4) % 5;
					} else {
						cmdIndex = GetNextCmdListIdx__12CCaravanWorkFii(caravanWork, cmdIndex, 1);
					}
					scroll += static_cast<double>(FLOAT_803309cc);
				}

				double labelAlphaScale = DOUBLE_80330a98;
				if (fabs(static_cast<double>(RingMenuFloat(this, 0x50C))) < DOUBLE_80330aa0) {
					labelAlphaScale = DOUBLE_80330a90 * fabs(static_cast<double>(RingMenuFloat(this, 0x50C)));
				}
				labelAlphaScale = static_cast<double>(static_cast<float>(labelAlphaScale * static_cast<double>(iconAlphaScale)));

				int prev1 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (cmdIndex + 4) % 5
				                : GetNextCmdListIdx__12CCaravanWorkFii(caravanWork, cmdIndex, -1);
				int prev2 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (prev1 + 4) % 5
				                : GetNextCmdListIdx__12CCaravanWorkFii(caravanWork, prev1, -1);
				int next1 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (cmdIndex + 1) % 5
				                : GetNextCmdListIdx__12CCaravanWorkFii(caravanWork, cmdIndex, 1);
				int next2 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (next1 + 1) % 5
				                : GetNextCmdListIdx__12CCaravanWorkFii(caravanWork, next1, 1);

				drawCommand(menuIndex, font, posX, posY, caravanWork, prev2, static_cast<float>(scroll - FLOAT_80330a28),
				            static_cast<float>(labelAlphaScale));
				drawCommand(menuIndex, font, posX, posY, caravanWork, prev1, static_cast<float>(scroll - FLOAT_803309cc),
				            static_cast<float>(labelAlphaScale));
				drawCommand(menuIndex, font, posX, posY, caravanWork, next2, static_cast<float>(scroll + FLOAT_80330a28),
				            static_cast<float>(labelAlphaScale));
				drawCommand(menuIndex, font, posX, posY, caravanWork, next1, static_cast<float>(scroll + FLOAT_803309cc),
				            static_cast<float>(labelAlphaScale));
				drawCommand(menuIndex, font, posX, posY, caravanWork, cmdIndex, static_cast<float>(scroll), iconAlphaScale);
				DrawInit__8CMenuPcsFv(MenuPcsVoid());
			}
		}

		CFont* font = reinterpret_cast<CFont*>(*reinterpret_cast<int*>(MenuPcsRaw() + 0xFC));
		for (int button = 1; button >= 0; button--) {
			const int buttonValue = RingMenuInt(this, 0x18 + group * 0x0C + button * 4);
			if (buttonValue < 0) {
				continue;
			}

			int labelId;
			if ((buttonValue & 0x8000) == 0) {
				labelId = reinterpret_cast<const int*>(flatData->table[4].strings)[buttonValue];
			} else {
				labelId = reinterpret_cast<const int*>(flatData->table[0].strings)[(buttonValue & 0x7FFF) * 5 + 4];
			}

			double fade = static_cast<double>(static_cast<float>(RingMenuInt(this, 0x3C + group * 0x0C + button * 4) * FLOAT_80330a78));
			if (button == 0) {
				fade = static_cast<double>(FLOAT_803309cc) - fade;
			}

			DrawInit__5CFontFv(font);
			SetMargin__5CFontFf(FLOAT_80330a8c, font);
			SetShadow__5CFontFi(font, 1);

			float textScale;
			if (group == 1) {
				SetTlut__5CFontFi(font, 0xE);
				textScale = FLOAT_80330a4c;
			} else if (group == 0) {
				SetTlut__5CFontFi(font, 0xD);
				textScale = FLOAT_80330ab8;
			} else {
				SetTlut__5CFontFi(font, (buttonValue == 1) ? 7 : 4);
				const double wobble = sin(static_cast<double>(FLOAT_80330a0c) * static_cast<double>(FLOAT_803309cc - fade));
				textScale = FLOAT_80330a4c * (FLOAT_80330abc * static_cast<float>(wobble) + FLOAT_803309cc);
			}

			SetScaleX__5CFontFf(textScale, font);
			SetScaleY__5CFontFf(textScale, font);

			const float width = static_cast<float>(GetWidth__5CFontFPc(font, labelId));
			int alpha = static_cast<int>(showScale * static_cast<double>(static_cast<float>(FLOAT_80330a34 * fade) * static_cast<float>(transitionScale)));
			if ((group == 2) && (RingMenuInt(this, 0x30) >= 0)) {
				alpha = static_cast<int>(FLOAT_80330ac0 * static_cast<float>(alpha));
			}

			GXColor textColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha)};
			SetColor__5CFontF8_GXColor(font, &textColor);

			float textX;
			float textY;
			if (group == 1) {
				textX = -(FLOAT_803309c4 * width - (FLOAT_803309f0 + posX + FLOAT_80330aac));
				textY = (FLOAT_80330ab0 + drawY) - FLOAT_803309ec;
			} else if (group == 0) {
				textX = -(FLOAT_803309c4 * width - (FLOAT_80330aa8 + posX + FLOAT_80330aac));
				textY = (FLOAT_80330a3c + drawY) - FLOAT_803309ec;
			} else {
				textX = -(FLOAT_803309c4 * width - (FLOAT_80330aa8 + posX));
				textY = FLOAT_80330ab4 + drawY;
			}

			SetPosX__5CFontFf(textX, font);
			SetPosY__5CFontFf(textY, font);
			SetPosZ__5CFontFf(FLOAT_803309c0, font);
			if (group != 2) {
				Draw__5CFontFPc(font, labelId);
			}
			DrawInit__8CMenuPcsFv(MenuPcsVoid());

			if (group == 2) {
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x1F);
				CGPartyObj* partyObj = Game.m_partyObjArr[menuIndex];
				if (partyObj != 0) {
					CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(
						reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(partyObj) + 0x5C)[0]);
					if ((caravanWork != 0) && ((*reinterpret_cast<unsigned char*>(CFlat + 0x12E4) & 2) == 0)) {
						const float barY = FLOAT_80330aac + textY;
						const float fullAlpha =
							static_cast<float>(showScale * static_cast<double>(static_cast<float>(FLOAT_80330a34 * fade) * static_cast<float>(transitionScale)));
						const float dimAlpha =
							static_cast<float>(showScale * static_cast<double>(static_cast<float>(FLOAT_80330a84 * fade) * static_cast<float>(transitionScale)));
						const float centerBase =
							(FLOAT_80330aa8 + posX) -
							static_cast<float>(static_cast<double>((((caravanWork->m_numCmdListSlots >> 28) & 1) +
							                                       (caravanWork->m_numCmdListSlots * 8)) >>
							                                      1));

						for (int i = 0; i < caravanWork->m_numCmdListSlots; i++) {
							int maxCharge;
							int curCharge;
							caravanWork->GetMagicCharge(i, maxCharge, curCharge);

							float blink = FLOAT_803309c0;
							if (maxCharge == 0) {
								if (!caravanWork->IsSelectedCmdList(i)) {
									unsigned int color[1];
									__ct__6CColorFUcUcUcUc(color, 0x80, 0x80, 0x80, static_cast<unsigned char>(static_cast<int>(dimAlpha)));
									SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), color);
								} else {
									unsigned int color[1];
									__ct__6CColorFUcUcUcUc(color, 0x20, 0xFF, 0x20, static_cast<unsigned char>(static_cast<int>(fullAlpha)));
									SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), color);
								}
							} else {
								unsigned int color[1];
								__ct__6CColorFUcUcUcUc(color, 0x00, 0xFF, 0x00, static_cast<unsigned char>(static_cast<int>(fullAlpha)));
								SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), color);
								blink = static_cast<float>((System.m_frameCounter >> 2) & 1);
							}

							DrawRect__8CMenuPcsFUlfffffffff(
								MenuPcsVoid(), 3, FLOAT_803309ec + centerBase + static_cast<float>(i * 8), barY, FLOAT_80330a38, FLOAT_80330a38,
								FLOAT_80330a38 * (FLOAT_80330a38 + blink), FLOAT_803309f0, FLOAT_803309cc, FLOAT_803309cc, 0.0f);
						}
					}
				}
			}
		}
	}

	DrawInit__8CMenuPcsFv(MenuPcsVoid());
}

/*
 * --INFO--
 * PAL Address: 0x800a3404
 * PAL Size: 1472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::drawGBA()
{
	const int menuIndex = RingMenuInt(this, 0x0C);
	if (!((Game.m_gameWork.m_menuStageMode == 0) || (menuIndex < 1))) {
		return;
	}

	const unsigned int scriptFood = Game.m_scriptFoodBase[menuIndex];
	if (scriptFood == 0) {
		return;
	}

	double showScale = static_cast<double>(static_cast<float>(static_cast<float>(RingMenuInt(this, 0x500)) * FLOAT_80330a08));
	if (RingMenuInt(this, 0x10) != 0) {
		showScale = static_cast<double>(FLOAT_803309cc) - showScale;
	}
	if (showScale == static_cast<double>(FLOAT_803309c0)) {
		return;
	}

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x16);

	double gbaAnim = static_cast<double>(
	    sin(static_cast<double>(FLOAT_80330a0c * static_cast<float>(RingMenuInt(this, 0x4F0))) / static_cast<double>(FLOAT_80330a10)));
	if (RingMenuInt(this, 0x4F8) == 1) {
		gbaAnim = static_cast<double>(FLOAT_803309cc) - gbaAnim;
	}

	float posX = 0x30;
	if ((menuIndex & 1) != 0) {
		posX = 0x250;
	}

	float posY = 0x30;
	if ((menuIndex & 2) != 0) {
		posY = 400.0f;
	}

	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

	const double sizePulse = static_cast<double>(FLOAT_80330a14 * static_cast<float>(static_cast<double>(FLOAT_803309cc) - gbaAnim) +
	                                             FLOAT_803309cc);
	float cycle = static_cast<float>(
	    fmod(static_cast<double>(FLOAT_80330a18 * static_cast<float>(RingMenuInt(this, 0x4F4))), DOUBLE_80330a20));
	if (cycle > FLOAT_803309cc) {
		cycle = FLOAT_80330a28 - cycle;
	}

	const double angle = static_cast<double>(FLOAT_80330a2c * cycle);
	const double sinA = static_cast<double>(sin(angle));
	const double sinB = static_cast<double>(sin(static_cast<double>(FLOAT_80330a30) + angle));

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x1E);

	const double alphaBase = static_cast<double>(FLOAT_80330a34) * gbaAnim;
	const unsigned int alphaShadow =
	    static_cast<unsigned int>(static_cast<int>(static_cast<double>(FLOAT_803309c4) * alphaBase * showScale));
	unsigned int shadowColor[1];
	__ct__6CColorFUcUcUcUc(shadowColor, 0, 0, 0, static_cast<unsigned char>(alphaShadow));
	SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), shadowColor);

	const double invSize = static_cast<double>(FLOAT_803309cc) - sizePulse;
	const float drawX = static_cast<float>(static_cast<double>(posX) + static_cast<double>(FLOAT_80330a3c * static_cast<float>(sizePulse * sinB)));
	const float drawY = static_cast<float>(static_cast<double>(posY) - static_cast<double>(FLOAT_80330a40 * static_cast<float>(sizePulse * sinA)));
	const float menuV = static_cast<float>(menuIndex * 0x30);
	DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 3, FLOAT_80330a38 + drawX, FLOAT_80330a38 + drawY, FLOAT_80330a44, FLOAT_80330a48,
	                                 FLOAT_803309c0, menuV, FLOAT_80330a4c * static_cast<float>(static_cast<double>(FLOAT_803309cc) + invSize),
	                                 FLOAT_80330a4c * static_cast<float>(sizePulse + invSize), 0.0f);

	const double alphaLit = alphaBase * showScale;
	const unsigned int alphaIcon = static_cast<unsigned int>(static_cast<int>(alphaLit));
	unsigned int iconColor[1];
	__ct__6CColorFUcUcUcUc(iconColor, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaIcon));
	SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), iconColor);
	DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 3, drawX, drawY, FLOAT_80330a44, FLOAT_80330a48, FLOAT_803309c0, menuV,
	                                 FLOAT_80330a4c * static_cast<float>(sizePulse), FLOAT_80330a4c * static_cast<float>(sizePulse), 0.0f);

	const unsigned int flatFlags = *reinterpret_cast<unsigned int*>(CFlat + 0x12A0) & *reinterpret_cast<unsigned int*>(CFlat + 0x12A4);
	if (((flatFlags & 8) != 0) && (GetGBAStart__6JoyBusFi(&Joybus, menuIndex) == 0)) {
		if (IsInitSend__6JoyBusFi(&Joybus, menuIndex) == 0) {
			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x1D);
			const double blink = static_cast<double>(sin(static_cast<double>(FLOAT_80330a54 * static_cast<float>(RingMenuInt(this, 0x4F4)))));
			const unsigned int sendAlpha = static_cast<unsigned int>(
			    static_cast<int>(static_cast<double>(FLOAT_803309c4) * (alphaLit * static_cast<double>(FLOAT_803309cc + static_cast<float>(blink)))));
			unsigned int sendColor[1];
			__ct__6CColorFUcUcUcUc(sendColor, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(sendAlpha));
			SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), sendColor);
			DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 3, drawX, drawY, FLOAT_80330a48, FLOAT_80330a48, FLOAT_803309c0, FLOAT_80330a58,
			                                 FLOAT_803309cc, FLOAT_803309cc, 0.0f);
		} else {
			int frameHalf = static_cast<int>(System.m_frameCounter) >> 1;
			int frameSign = frameHalf >> 31;
			unsigned int frameTex = static_cast<unsigned int>(
			    (frameSign * 0x10 | (frameHalf * 0x10000000 + frameSign) >> 28) - frameSign);
			if (frameTex > 3) {
				frameTex &= 1;
			}
			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x1D);
			DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 3, drawX, drawY, FLOAT_80330a48, FLOAT_80330a48, FLOAT_803309c0,
			                                 static_cast<float>(frameTex * 0x30), FLOAT_803309cc, FLOAT_803309cc, 0.0f);
		}
	}

	DrawInit__8CMenuPcsFv(MenuPcsVoid());
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
	int current = battleButtons[buttonIndex];

	if (current == newValue) {
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

	if (!((Game.m_gameWork.m_menuStageMode == 0) || (RingMenuInt(this, 0x0C) < 2))) {
		return;
	}

	const unsigned int flatFlags = *reinterpret_cast<unsigned int*>(CFlat + 0x12A0) &
	                               *reinterpret_cast<unsigned int*>(CFlat + 0x12A4);
	if ((flatFlags & 1) == 0) {
		return;
	}

	int menuIndex = RingMenuInt(this, 0x0C);
	CGPartyObj* partyObj = Game.m_partyObjArr[menuIndex];
	if (partyObj == 0 || static_cast<signed char>(*reinterpret_cast<unsigned char*>(&partyObj->m_weaponNodeFlags + 1)) >= 0) {
		return;
	}

	unsigned int scriptFood = Game.m_scriptFoodBase[menuIndex];
	Mtx cameraMtx;
	PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4), cameraMtx);

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
	PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x48), screenMtx);
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

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x19);
	int iconRow;
	unsigned int iconCol;
	if ((Game.m_gameWork.m_menuStageMode == 0) || (menuIndex < 1)) {
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
	SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), bgColor);
	DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 3, static_cast<float>(FLOAT_803309ec + posX),
	                                 static_cast<float>(FLOAT_803309ec + posY), FLOAT_803309f0, FLOAT_803309f0,
	                                 FLOAT_803309c0, FLOAT_803309c0, FLOAT_803309cc, FLOAT_803309cc, 0.0f);

	unsigned int fgColor[1];
	__ct__6CColorFUcUcUcUc(fgColor, 0xFF, 0xFF, 0xFF, 0xFF);
	SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), fgColor);
	DrawRect__8CMenuPcsFUlfffffffff(
	    MenuPcsVoid(), 3, static_cast<float>(posX), static_cast<float>(posY), FLOAT_803309f0, FLOAT_803309f0, FLOAT_803309c0,
	    static_cast<float>(iconRow * 0x38), FLOAT_803309cc, FLOAT_803309cc,
	    0.0f);

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x18);
	void* tlut = reinterpret_cast<void*>(0x802EA500);
	if (*reinterpret_cast<short*>(scriptFood + 0x1C) != 0) {
		tlut = 0;
	}
	SetExternalTlut__8CTextureFPvi(*reinterpret_cast<void**>(MenuPcsRaw() + 0x1EC), tlut, 1);
	GXSetTevDirect(GX_TEVSTAGE2);
	_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xF, 0, 0xC, 0xB);
	_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 0, 6, 7);
	_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 3, 1, 0);
	_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0xFF, 0xFF, 4);

	unsigned int iconColor[1];
	__ct__6CColorFUcUcUcUc(iconColor, 0xFF, 0xFF, 0xFF, blinkAlpha);
	SetColor__8CMenuPcsFR6CColor(MenuPcsVoid(), iconColor);

	int signedIconCol = static_cast<int>(iconCol);
	int colSign = signedIconCol >> 31;
	float u = static_cast<float>((((colSign * 8) | (signedIconCol * 0x20000000 + colSign) >> 29) - colSign) * 0x30);
	float v = static_cast<float>(((signedIconCol >> 3) + ((signedIconCol < 0) && ((iconCol & 7) != 0))) * 0x30);
	DrawRect__8CMenuPcsFUlfffffffff(MenuPcsVoid(), 3, static_cast<float>(posX), static_cast<float>(posY), FLOAT_803309f4,
	                                 FLOAT_803309f4, u, v, FLOAT_803309f8, FLOAT_803309f8, 0.0f);
}
