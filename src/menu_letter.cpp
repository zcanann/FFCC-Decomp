#include "ffcc/menu_letter.h"
#include "ffcc/p_game.h"

#include <string.h>

typedef signed short s16;
typedef unsigned char u8;

extern "C" int SingGetLetterAttachflg__8CMenuPcsFv(CMenuPcs*);
extern "C" void LetterInit1__8CMenuPcsFv(CMenuPcs*);
extern "C" void SetSingWinScl__8CMenuPcsFf(CMenuPcs*, float);

extern float FLOAT_803330bc;
extern float FLOAT_803330f8;

namespace {
unsigned char DAT_8032eeea = 0;
unsigned char DAT_8032eee8 = 0;
unsigned char DAT_8032eeec = 0;
unsigned char DAT_8032eeeb = 0;
unsigned int DAT_8032eef0 = 0;
unsigned char DAT_8032eeee = 0;
unsigned char DAT_8032eeed = 0;
int DAT_8032eef4 = 0;
s16 DAT_8032eef8 = 0;
s16 DAT_8032eefc = 0;
s16 DAT_8032ef00 = 0;
} // namespace

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit0()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit2()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit3()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit4()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80167844
 * PAL Size: 1016b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::LetterOpen()
{
	DAT_8032eeea = 1;
	if (*reinterpret_cast<char*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0xB) == '\0') {
		memset(*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x850), 0, 0x1008);

		float f = FLOAT_803330f8;
		int base = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850) + 8;
		for (int i = 0; i < 8; ++i) {
			*reinterpret_cast<float*>(base + 0x14) = f;
			*reinterpret_cast<float*>(base + 0x54) = f;
			*reinterpret_cast<float*>(base + 0x94) = f;
			*reinterpret_cast<float*>(base + 0xD4) = f;
			*reinterpret_cast<float*>(base + 0x114) = f;
			*reinterpret_cast<float*>(base + 0x154) = f;
			*reinterpret_cast<float*>(base + 0x194) = f;
			*reinterpret_cast<float*>(base + 0x1D4) = f;
			base += 0x200;
		}

		int panel = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
		*reinterpret_cast<int*>(panel + 0x24) = 0;
		*reinterpret_cast<int*>(panel + 0x2C) = 0;
		*reinterpret_cast<int*>(panel + 0x30) = 10;
		*reinterpret_cast<int*>(panel + 0x64) = 0;
		*reinterpret_cast<unsigned int*>(panel + 0x6C) =
			(static_cast<unsigned int>(-static_cast<int>(static_cast<char>(*reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x872)) != 0)) >> 31) & 10;
		*reinterpret_cast<int*>(panel + 0x70) = 10;
		**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) = 2;

		int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C);
		*reinterpret_cast<s16*>(state + 0x22) = 0;
		*reinterpret_cast<char*>(state + 0xB) = 1;

		int attachFlag = SingGetLetterAttachflg__8CMenuPcsFv(this);
		if (attachFlag < 0) {
			*reinterpret_cast<s16*>(state + 0x26) = 0;
			*reinterpret_cast<s16*>(state + 0x28) = 0;
			*reinterpret_cast<s16*>(state + 0x34) = 0;
			DAT_8032eef0 = 0;
			DAT_8032eef4 = 0;
			DAT_8032eeed = 2;
			DAT_8032eee8 = 0;
		} else {
			memset(*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x850), 0, 0x1008);
			base = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850) + 8;
			for (int i = 0; i < 8; ++i) {
				*reinterpret_cast<float*>(base + 0x14) = f;
				*reinterpret_cast<float*>(base + 0x54) = f;
				*reinterpret_cast<float*>(base + 0x94) = f;
				*reinterpret_cast<float*>(base + 0xD4) = f;
				*reinterpret_cast<float*>(base + 0x114) = f;
				*reinterpret_cast<float*>(base + 0x154) = f;
				*reinterpret_cast<float*>(base + 0x194) = f;
				*reinterpret_cast<float*>(base + 0x1D4) = f;
				base += 0x200;
			}

			panel = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
			*reinterpret_cast<int*>(panel + 0x24) = 0;
			*reinterpret_cast<int*>(panel + 0x2C) = 0;
			*reinterpret_cast<int*>(panel + 0x30) = 10;
			**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) = 1;

			*reinterpret_cast<s16*>(state + 0x22) = 0;
			*reinterpret_cast<s16*>(state + 0x26) = DAT_8032eef8;
			*reinterpret_cast<s16*>(state + 0x28) = DAT_8032eefc;
			*reinterpret_cast<s16*>(state + 0x34) = DAT_8032ef00;
			DAT_8032eee8 = static_cast<u8>(DAT_8032eef8 + DAT_8032ef00);
		}

		DAT_8032eef8 = 0;
		DAT_8032eefc = 0;
		DAT_8032ef00 = 0;
		SetSingWinScl__8CMenuPcsFf(this, FLOAT_803330f8);
	}

	int finished = 0;
	int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C);
	*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;

	int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
	s16* entry = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	int frame = static_cast<int>(*reinterpret_cast<s16*>(state + 0x22));

	for (int i = 0; i < panelCount; ++i, entry += 0x20) {
		float f = FLOAT_803330bc;
		if (*reinterpret_cast<int*>(entry + 0x12) <= frame) {
			if (frame < *reinterpret_cast<int*>(entry + 0x12) + *reinterpret_cast<int*>(entry + 0x14)) {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				*reinterpret_cast<float*>(entry + 8) =
					static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(entry + 0x14));
				if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
					f = static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(entry + 0x14));
					*reinterpret_cast<float*>(entry + 0x18) =
						(*reinterpret_cast<float*>(entry + 0x1C) - static_cast<float>(entry[0])) * f;
					*reinterpret_cast<float*>(entry + 0x1A) =
						(*reinterpret_cast<float*>(entry + 0x1E) - static_cast<float>(entry[1])) * f;
				}
			} else {
				++finished;
				*reinterpret_cast<float*>(entry + 8) = FLOAT_803330f8;
				*reinterpret_cast<float*>(entry + 0x18) = f;
				*reinterpret_cast<float*>(entry + 0x1A) = f;
			}
		}
	}

	if (panelCount == finished) {
		if (SingGetLetterAttachflg__8CMenuPcsFv(this) < 0) {
			*reinterpret_cast<s16*>(state + 0x12) = 1;
		} else {
			*reinterpret_cast<s16*>(state + 0x12) = 0;
			*reinterpret_cast<s16*>(state + 0x30) = 1;
			LetterInit1__8CMenuPcsFv(this);
		}
	}

	return panelCount == finished;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMenuPcs::LetterCtrl()
{
	return 0;
}

/*
 * --INFO--
 * PAL Address: 80166490
 * PAL Size: 488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::LetterClose()
{
	DAT_8032eeea = 1;
	int finished = 0;

	int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C);
	*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;

	int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
	s16* entry = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	int frame = static_cast<int>(*reinterpret_cast<s16*>(state + 0x22));

	for (int i = 0; i < panelCount; ++i, entry += 0x20) {
		float f = FLOAT_803330bc;
		if (*reinterpret_cast<int*>(entry + 0x12) <= frame) {
			if (frame < *reinterpret_cast<int*>(entry + 0x12) + *reinterpret_cast<int*>(entry + 0x14)) {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				*reinterpret_cast<float*>(entry + 8) =
					1.0f - static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(entry + 0x14));
				if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
					f = 1.0f - static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(entry + 0x14));
					*reinterpret_cast<float*>(entry + 0x18) =
						(*reinterpret_cast<float*>(entry + 0x1C) - static_cast<float>(entry[0])) * f;
					*reinterpret_cast<float*>(entry + 0x1A) =
						(*reinterpret_cast<float*>(entry + 0x1E) - static_cast<float>(entry[1])) * f;
				}
			} else {
				++finished;
				*reinterpret_cast<float*>(entry + 8) = FLOAT_803330bc;
				*reinterpret_cast<float*>(entry + 0x18) = f;
				*reinterpret_cast<float*>(entry + 0x1A) = f;
			}
		}
	}

	if (panelCount == finished && SingGetLetterAttachflg__8CMenuPcsFv(this) >= 0) {
		DAT_8032eef8 = *reinterpret_cast<s16*>(state + 0x26);
		DAT_8032ef00 = static_cast<s16>(DAT_8032eee8 - DAT_8032eef8);
		DAT_8032eefc = *reinterpret_cast<s16*>(state + 0x28);
	}

	return panelCount == finished;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterLstOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterLstClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterMessOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterMessClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterItemWinOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterItemWinClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterReplyWinOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterReplyWinClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterAttachWinOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterAttachWinClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterConfirmOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterConfirmClose()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80165b4c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::LetterDraw()
{
	if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x30) == 0) {
		LetterListDraw();
	} else {
		LetterMessDraw();
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterListDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterMessDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterCtrlCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterLstBaseDraw(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterDrawPageMark(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8016394c
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::LetterSetAttachItem(unsigned int itemIndex, int flag)
{
	DAT_8032eef0 = itemIndex;
	if (DAT_8032eeed == 0) {
		DAT_8032eeee = static_cast<unsigned char>(itemIndex);
		DAT_8032eef0 = static_cast<unsigned int>(*reinterpret_cast<short*>(Game.game.m_scriptFoodBase[0] + itemIndex * 2 + 0xB6));
	}
	DAT_8032eef4 = flag;
}
