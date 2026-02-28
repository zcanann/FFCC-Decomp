#include "ffcc/menu_letter.h"
#include "ffcc/p_game.h"

#include <string.h>

typedef signed short s16;
typedef unsigned char u8;

extern "C" int SingGetLetterAttachflg__8CMenuPcsFv(CMenuPcs*);
extern "C" void LetterInit1__8CMenuPcsFv(CMenuPcs*);
extern "C" void SetSingWinScl__8CMenuPcsFf(CMenuPcs*, float);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dla__FPv(void*);
extern "C" void MakeAgbString__4CMesFPcPcii(char*, char*, int, int);
extern "C" int sprintf(char*, const char*, ...);
extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void SetSingDynamicWinMessInfo__8CMenuPcsFiPcPcPcPcPcPcPcPc(CMenuPcs*, int, char*, char*, char*, char*, char*, char*, char*, char*);
extern "C" void GetSingWinSize__8CMenuPcsFiPsPsi(CMenuPcs*, int, s16*, s16*, int);
extern "C" void SetMcWinInfo__8CMenuPcsFii(CMenuPcs*, int, int);

extern float FLOAT_803330bc;
extern float FLOAT_803330f8;

namespace {
unsigned char DAT_8032eeea = 0;
short DAT_8032eee8 = 0;
unsigned char DAT_8032eeec = 0;
unsigned char DAT_8032eeeb = 0;
int DAT_8032eef0 = 0;
unsigned char DAT_8032eeee = 0;
signed char DAT_8032eeed = 0;
int DAT_8032eef4 = 0;
int DAT_8032eef8 = 0;
int DAT_8032eefc = 0;
int DAT_8032ef00 = 0;
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
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar8;
	float fVar1;
	s16* psVar7;

	DAT_8032eeea = 1;
	if (*reinterpret_cast<char*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0xB) == '\0') {
		memset(*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x850), 0, 0x1008);
		iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850) + 8;
		iVar8 = 8;
		do {
			*reinterpret_cast<float*>(iVar4 + 0x14) = FLOAT_803330f8;
			*reinterpret_cast<float*>(iVar4 + 0x54) = FLOAT_803330f8;
			*reinterpret_cast<float*>(iVar4 + 0x94) = FLOAT_803330f8;
			*reinterpret_cast<float*>(iVar4 + 0xD4) = FLOAT_803330f8;
			*reinterpret_cast<float*>(iVar4 + 0x114) = FLOAT_803330f8;
			*reinterpret_cast<float*>(iVar4 + 0x154) = FLOAT_803330f8;
			*reinterpret_cast<float*>(iVar4 + 0x194) = FLOAT_803330f8;
			*reinterpret_cast<float*>(iVar4 + 0x1D4) = FLOAT_803330f8;
			iVar4 += 0x200;
			--iVar8;
		} while (iVar8 != 0);
		iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
		*reinterpret_cast<int*>(iVar4 + 0x24) = 0;
		*reinterpret_cast<int*>(iVar4 + 0x2C) = 0;
		*reinterpret_cast<int*>(iVar4 + 0x30) = 10;
		iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
		*reinterpret_cast<int*>(iVar4 + 0x64) = 0;
		*reinterpret_cast<unsigned int*>(iVar4 + 0x6C) =
			~(((-static_cast<int>(static_cast<char>(*reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x872))) |
				static_cast<int>(static_cast<char>(*reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x872)))) >>
			   31)) &
			10;
		*reinterpret_cast<int*>(iVar4 + 0x70) = 10;
		**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) = 2;
		*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x22) = 0;
		*reinterpret_cast<char*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0xB) = 1;
		iVar4 = SingGetLetterAttachflg__8CMenuPcsFv(this);
		if (iVar4 < 0) {
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x26) = 0;
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x28) = 0;
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x34) = 0;
			DAT_8032eef0 = 0;
			DAT_8032eef4 = 0;
			DAT_8032eeed = 2;
			DAT_8032eee8 = 0;
		} else {
			memset(*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x850), 0, 0x1008);
			iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850) + 8;
			iVar8 = 8;
			do {
				*reinterpret_cast<float*>(iVar4 + 0x14) = FLOAT_803330f8;
				*reinterpret_cast<float*>(iVar4 + 0x54) = FLOAT_803330f8;
				*reinterpret_cast<float*>(iVar4 + 0x94) = FLOAT_803330f8;
				*reinterpret_cast<float*>(iVar4 + 0xD4) = FLOAT_803330f8;
				*reinterpret_cast<float*>(iVar4 + 0x114) = FLOAT_803330f8;
				*reinterpret_cast<float*>(iVar4 + 0x154) = FLOAT_803330f8;
				*reinterpret_cast<float*>(iVar4 + 0x194) = FLOAT_803330f8;
				*reinterpret_cast<float*>(iVar4 + 0x1D4) = FLOAT_803330f8;
				iVar4 += 0x200;
				--iVar8;
			} while (iVar8 != 0);
			iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
			*reinterpret_cast<int*>(iVar4 + 0x24) = 0;
			*reinterpret_cast<int*>(iVar4 + 0x2C) = 0;
			*reinterpret_cast<int*>(iVar4 + 0x30) = 10;
			**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) = 1;
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x22) = 0;
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x26) = static_cast<s16>(DAT_8032eef8);
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x28) = static_cast<s16>(DAT_8032eefc);
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x34) = static_cast<s16>(DAT_8032ef00);
			DAT_8032eee8 = static_cast<s16>(DAT_8032eef8 + DAT_8032ef00);
		}
		DAT_8032eef8 = 0;
		DAT_8032eefc = 0;
		DAT_8032ef00 = 0;
		SetSingWinScl__8CMenuPcsFf(this, FLOAT_803330f8);
	}
	iVar6 = 0;
	*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x22) =
		*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x22) + 1;
	iVar5 = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
	psVar7 = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	iVar8 = static_cast<int>(*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x22));
	iVar4 = iVar5;
	if (0 < iVar5) {
		do {
			fVar1 = FLOAT_803330bc;
			if (*reinterpret_cast<int*>(psVar7 + 0x12) <= iVar8) {
				if (iVar8 < *reinterpret_cast<int*>(psVar7 + 0x12) + *reinterpret_cast<int*>(psVar7 + 0x14)) {
					*reinterpret_cast<int*>(psVar7 + 0x10) = *reinterpret_cast<int*>(psVar7 + 0x10) + 1;
					*reinterpret_cast<float*>(psVar7 + 8) =
						static_cast<float>(*reinterpret_cast<int*>(psVar7 + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(psVar7 + 0x14));
					if ((*reinterpret_cast<unsigned int*>(psVar7 + 0x16) & 2) == 0) {
						fVar1 = static_cast<float>(*reinterpret_cast<int*>(psVar7 + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(psVar7 + 0x14));
						*reinterpret_cast<float*>(psVar7 + 0x18) =
							(*reinterpret_cast<float*>(psVar7 + 0x1C) - static_cast<float>(psVar7[0])) * fVar1;
						*reinterpret_cast<float*>(psVar7 + 0x1A) =
							(*reinterpret_cast<float*>(psVar7 + 0x1E) - static_cast<float>(psVar7[1])) * fVar1;
					}
				} else {
					iVar6 = iVar6 + 1;
					*reinterpret_cast<float*>(psVar7 + 8) = FLOAT_803330f8;
					*reinterpret_cast<float*>(psVar7 + 0x18) = fVar1;
					*reinterpret_cast<float*>(psVar7 + 0x1A) = fVar1;
				}
			}
			psVar7 += 0x20;
			iVar4 = iVar4 + -1;
		} while (iVar4 != 0);
	}
	if (iVar5 == iVar6) {
		iVar4 = SingGetLetterAttachflg__8CMenuPcsFv(this);
		if (iVar4 < 0) {
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x12) = 1;
		} else {
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x12) = 0;
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x30) = 1;
			LetterInit1__8CMenuPcsFv(this);
		}
	}
	return iVar5 == iVar6;
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
 * PAL Address: 80166194
 * PAL Size: 764b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::LetterReplyWinOpen()
{
	unsigned int caravanWork = Game.game.m_scriptFoodBase[0];
	unsigned char languageId = Game.game.m_gameWork.m_languageId;
	int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C);
	if (*reinterpret_cast<char*>(state + 0xC) == '\0') {
		char lines[8][0x80];
		char unused0[0x80];
		char unused1[0x80];
		char unused2[0x80];
		char unused3[0x80];
		char unused4[0x80];
		char unused5[0x80];
		char unused6[0x88];
		memset(lines, 0, 0x400);

		CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(
			reinterpret_cast<char*>(this) + (Game.game.m_gameWork.m_menuStageMode == '\0' ? 0xEC : 0xF4));
		char* srcText = reinterpret_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
			0x400, stage, const_cast<char*>("menu_letter.cpp"), 0x323));
		stage = *reinterpret_cast<CMemory::CStage**>(
			reinterpret_cast<char*>(this) + (Game.game.m_gameWork.m_menuStageMode == '\0' ? 0xEC : 0xF4));
		char* workText = reinterpret_cast<char*>(__nwa__FUlPQ27CMemory6CStagePci(
			0x400, stage, const_cast<char*>("menu_letter.cpp"), 0x325));

		memset(srcText, 0, 0x400);
		memset(workText, 0, 0x400);

		unsigned short msgIndex = *reinterpret_cast<unsigned short*>(
			caravanWork + DAT_8032eee8 * 0xC + 0x3EC);
		char** mesPtr = reinterpret_cast<char**>(reinterpret_cast<char*>(&Game.game.m_cFlatDataArr[1]) + 0x44);
		strcpy(srcText, mesPtr[(msgIndex & 0x7FC) >> 1]);
		MakeAgbString__4CMesFPcPcii(workText, srcText, *reinterpret_cast<unsigned short*>(caravanWork + 0x3E2), 0);

		DAT_8032eeeb = 0;
		char* curLine = workText;
		for (int i = 0; i < 8; ++i) {
			char* newline = strchr(curLine, '\n');
			if (newline != 0) {
				*newline = '\0';
			}

			const char* right = GetMenuStr__8CMenuPcsFi(this, 0x24);
			const char* left = GetMenuStr__8CMenuPcsFi(this, 0x23);
			if (languageId == 2) {
				sprintf(lines[i], "%s%s%s", left, curLine, right);
			} else {
				sprintf(lines[i], "%s%s%s", left, curLine, right);
			}

			DAT_8032eeeb = static_cast<unsigned char>(DAT_8032eeeb + 1);
			if (newline == 0) {
				break;
			}
			curLine = newline + 1;
		}

		__dla__FPv(srcText);
		__dla__FPv(workText);

		const char* closeText = GetMenuStr__8CMenuPcsFi(this, 3);
		int lineIndex = DAT_8032eeeb;
		DAT_8032eeeb = static_cast<unsigned char>(DAT_8032eeeb + 1);
		strcat(lines[lineIndex], closeText, 0x80);

		SetSingDynamicWinMessInfo__8CMenuPcsFiPcPcPcPcPcPcPcPc(
			this,
			DAT_8032eeeb,
			lines[0],
			unused0,
			unused1,
			unused2,
			unused3,
			unused4,
			unused5,
			unused6);

		s16 winW;
		s16 winH;
		GetSingWinSize__8CMenuPcsFiPsPsi(this, 0, &winW, &winH, 1);
		SetMcWinInfo__8CMenuPcsFii(this, winW, winH);
		*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 0;
		*reinterpret_cast<unsigned char*>(state + 0x9) = 0xFF;
		*reinterpret_cast<char*>(state + 0xC) = 1;
	}
	return *reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) == 1;
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
		DAT_8032eef0 = *reinterpret_cast<short*>(Game.game.m_scriptFoodBase[0] + itemIndex * 2 + 0xB6);
	}
	DAT_8032eef4 = flag;
}
