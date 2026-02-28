#include "ffcc/menu_letter.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"

#include <string.h>

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

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
extern "C" void PlaySe__6CSoundFiiii(void*, int, int, int, int);
extern "C" void AddItem__12CCaravanWorkFiPi(void*, int, int*);
extern "C" void AddGil__12CCaravanWorkFi(void*, int);
extern "C" int CanAddGil__12CCaravanWorkFi(void*, int);
extern "C" void FGLetterReply__12CCaravanWorkFiiii(void*, int, int, int, int);
extern "C" void DeleteItemIdx__12CCaravanWorkFii(void*, int, int);
extern "C" int m_tempVar__4CMes[];
extern u8 CFlat[];

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
char s_ReplyStr[0x80];

struct FlatDataTableView {
	int m_numEntries;
	char** m_strings;
	char* m_stringBuf;
};

struct FlatDataView {
	int m_dataCount;
	unsigned char _pad[0x68 - 4];
	int m_tableCount;
	FlatDataTableView m_tabl[8];
};
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
bool CMenuPcs::LetterConfirmOpen()
{
	unsigned int caravanWork = Game.game.m_scriptFoodBase[0];
	unsigned char languageId = Game.game.m_gameWork.m_languageId;
	int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C);

	if (*reinterpret_cast<char*>(state + 0xC) == '\0') {
		char lines[8][0x80];
		memset(lines, 0, sizeof(lines));

		FlatDataView* flatData = reinterpret_cast<FlatDataView*>(&Game.game.m_cFlatDataArr[1]);
		unsigned int letterWord = *reinterpret_cast<unsigned int*>(caravanWork + DAT_8032eee8 * 0xC + 0x3EC);
		char** subjectTable = flatData->m_tabl[2].m_strings;
		char** itemTable = flatData->m_tabl[0].m_strings;

		const char* title = subjectTable[(letterWord >> 7) & 0x1FF];
		if (languageId == 3) {
			sprintf(lines[0], "%s%s", GetMenuStr__8CMenuPcsFi(this, 0x26), title);
		} else if (languageId == 2) {
			sprintf(lines[0], "%s%s", title, GetMenuStr__8CMenuPcsFi(this, 0x26));
		} else if (languageId == 5) {
			sprintf(lines[0], "%s%s", GetMenuStr__8CMenuPcsFi(this, 0x26), title);
		} else if (languageId == 4) {
			sprintf(lines[0], "%s%s%s", GetMenuStr__8CMenuPcsFi(this, 0x26), title, GetMenuStr__8CMenuPcsFi(this, 0x25));
		} else {
			sprintf(lines[0], "%s%s%s", GetMenuStr__8CMenuPcsFi(this, 0x25), title, GetMenuStr__8CMenuPcsFi(this, 0x26));
		}

		const char* left = GetMenuStr__8CMenuPcsFi(this, 0x23);
		const char* right = GetMenuStr__8CMenuPcsFi(this, 0x24);
		const char* reply = "Reply";
		if (languageId == 2) {
			sprintf(lines[1], "%s%s%s", left, reply, right);
		} else {
			sprintf(lines[1], "%s%s%s", left, reply, right);
		}

		int lineCount = 2;
		if (DAT_8032eeed != 2) {
			if (languageId == 2) {
				if (DAT_8032eeed == 0) {
					int itemValue = flatData->m_tabl[0].m_numEntries > DAT_8032eef0 * 5 + 4
									 ? DAT_8032eef0 * 5 + 4
									 : 0;
					sprintf(lines[2], "%s%d%s", left, itemValue, right);
				} else if (DAT_8032eeed == 1) {
					sprintf(lines[2], "%d%s", DAT_8032eef0, GetMenuStr__8CMenuPcsFi(this, 4));
				}
				strcat(lines[2], GetMenuStr__8CMenuPcsFi(this, 0x28), 0x80);
			} else {
				strcpy(lines[2], GetMenuStr__8CMenuPcsFi(this, 0x28));
				if (DAT_8032eeed == 0) {
					strcat(lines[2], itemTable[DAT_8032eef0 * 5 + 4], 0x80);
				} else if (DAT_8032eeed == 1) {
					int offs = strlen(lines[2]);
					sprintf(lines[2] + offs, "%d%s", DAT_8032eef0, GetMenuStr__8CMenuPcsFi(this, 4));
				}
			}
			lineCount = 3;
		}

		strcat(lines[lineCount], GetMenuStr__8CMenuPcsFi(this, 0x21), 0x80);
		strcpy(lines[lineCount + 1], "");
		strcat(lines[lineCount + 1], GetMenuStr__8CMenuPcsFi(this, 1), 0x80);
		strcpy(lines[lineCount + 2], "");
		strcat(lines[lineCount + 2], GetMenuStr__8CMenuPcsFi(this, 2), 0x80);

		SetSingDynamicWinMessInfo__8CMenuPcsFiPcPcPcPcPcPcPcPc(
			this, lineCount + 3, lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[6], lines[7]);

		s16 winW;
		s16 winH;
		GetSingWinSize__8CMenuPcsFiPsPsi(this, 0, &winW, &winH, 1);
		SetMcWinInfo__8CMenuPcsFii(this, winW, winH);
		*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 0;
		*reinterpret_cast<s16*>(state + 0x28) = 0;
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
int CMenuPcs::LetterCtrlCur()
{
	bool blocked = false;
	u16 press;
	u16 hold;
	int caravanWork = Game.game.m_scriptFoodBase[0];

	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		press = Pad._8_2_;
	}

	blocked = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		hold = *reinterpret_cast<u16*>(reinterpret_cast<u8*>(&Pad) + 0x20);
	}

	if (hold == 0) {
		return 0;
	}

	int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C);
	s16 menuMode = *reinterpret_cast<s16*>(state + 0x30);
	if (menuMode != 0) {
		if (menuMode == 1) {
			if ((press & 0x100) != 0) {
				int entry = caravanWork + DAT_8032eee8 * 0xC;
				if (((*reinterpret_cast<u16*>(entry + 0x3EE) & 0x1FF) != 0) &&
				    (((*reinterpret_cast<u8*>(entry + 0x3EC) >> 6) & 1) == 0)) {
					*reinterpret_cast<u8*>(state + 8) = 1;
					*reinterpret_cast<u8*>(state + 9) = 5;
					if (((*reinterpret_cast<u8*>(entry + 0x3EC) >> 3) & 1) == 0) {
						if (*reinterpret_cast<u16*>(caravanWork + 0xB4) + 1 < 0x41) {
							*reinterpret_cast<u8*>(state + 9) |= 2;
						}
					} else {
						int canAdd = CanAddGil__12CCaravanWorkFi(
						    reinterpret_cast<void*>(caravanWork),
						    (*reinterpret_cast<u16*>(entry + 0x3EE) & 0x1FF) * 100);
						if (canAdd != 0) {
							*reinterpret_cast<u8*>(state + 9) |= 2;
						}
					}
					*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
					PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
					return 0;
				}

				if ((*reinterpret_cast<int*>(CFlat + 0x10408) != 0) &&
				    (((*reinterpret_cast<u8*>(entry + 0x3EC) >> 4) & 1) != 0) &&
				    (((*reinterpret_cast<u8*>(entry + 0x3EC) >> 5) & 1) == 0)) {
					*reinterpret_cast<u8*>(state + 8) = 2;
					*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
					PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
					return 0;
				}
				PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
				return 0;
			}

			if ((press & 0x200) == 0) {
				return 0;
			}

			*reinterpret_cast<u8*>(state + 8) = 0xFF;
			*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
			int openAnim = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
			*reinterpret_cast<int*>(openAnim + 0x2C) = 0;
			*reinterpret_cast<int*>(openAnim + 0x30) = 10;
			*reinterpret_cast<int*>(openAnim + 0x6C) = 0;
			*reinterpret_cast<int*>(openAnim + 0x70) = 10;

			float f = FLOAT_803330f8;
			int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
			s16* panel = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
			for (int i = 0; i < panelCount; ++i, panel += 0x20) {
				panel[0x10] = 0;
				panel[0x11] = 0;
				*reinterpret_cast<float*>(panel + 8) = f;
			}

			*reinterpret_cast<s16*>(state + 0x22) = 0;
			PlaySe__6CSoundFiiii(&Sound, 3, 0x40, 0x7F, 0);
			return 0;
		}

		if (menuMode == 2) {
			if ((hold & 0xC) != 0) {
				*reinterpret_cast<u16*>(state + 0x28) ^= 1;
				PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
				return 0;
			}
			if ((press & 0x100) == 0) {
				if ((press & 0x200) == 0) {
					return 0;
				}
				u8 letterFlags = *reinterpret_cast<u8*>(caravanWork + DAT_8032eee8 * 0xC + 0x3EC);
				if ((*reinterpret_cast<int*>(CFlat + 0x10408) == 0) || (((letterFlags >> 4) & 1) == 0) ||
				    (((letterFlags >> 5) & 1) != 0)) {
					*reinterpret_cast<u8*>(state + 8) = 0xFF;
				} else {
					*reinterpret_cast<u8*>(state + 8) = 1;
				}
				*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
				*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 2;
				PlaySe__6CSoundFiiii(&Sound, 3, 0x40, 0x7F, 0);
				return 0;
			}

			s16 sel = *reinterpret_cast<s16*>(state + 0x28);
			if ((static_cast<int>(static_cast<signed char>(*reinterpret_cast<char*>(state + 9))) & (1 << (sel + 1))) != 0) {
				if (sel == 0) {
					int entry = caravanWork + DAT_8032eee8 * 0xC;
					unsigned int value = *reinterpret_cast<u16*>(entry + 0x3EE) & 0x1FF;
					if (((*reinterpret_cast<u8*>(entry + 0x3EC) >> 3) & 1) == 0) {
						AddItem__12CCaravanWorkFiPi(reinterpret_cast<void*>(caravanWork), static_cast<int>(value), 0);
					} else {
						AddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravanWork), static_cast<int>(value * 100));
					}
					*reinterpret_cast<u8*>(entry + 0x3EC) = (*reinterpret_cast<u8*>(entry + 0x3EC) & 0xBF) | 0x40;
				}

				u8 letterFlags = *reinterpret_cast<u8*>(caravanWork + DAT_8032eee8 * 0xC + 0x3EC);
				if ((*reinterpret_cast<int*>(CFlat + 0x10408) == 0) || (((letterFlags >> 4) & 1) == 0) ||
				    (((letterFlags >> 5) & 1) != 0)) {
					*reinterpret_cast<u8*>(state + 8) = 0xFF;
				} else {
					*reinterpret_cast<u8*>(state + 8) = 1;
				}
				*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
				*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 2;
				PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
				return 0;
			}

			PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
			return 0;
		}

		if (menuMode == 3) {
			int maxReply = static_cast<int>(DAT_8032eeeb);
			if ((hold & 8) == 0) {
				if ((hold & 4) != 0) {
					if (static_cast<int>(*reinterpret_cast<s16*>(state + 0x28)) < maxReply - 1) {
						*reinterpret_cast<s16*>(state + 0x28) = *reinterpret_cast<s16*>(state + 0x28) + 1;
					} else {
						*reinterpret_cast<s16*>(state + 0x28) = 0;
					}
					PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
				}
			} else {
				if (*reinterpret_cast<s16*>(state + 0x28) == 0) {
					*reinterpret_cast<s16*>(state + 0x28) = DAT_8032eeeb - 1;
				} else {
					*reinterpret_cast<s16*>(state + 0x28) = *reinterpret_cast<s16*>(state + 0x28) - 1;
				}
				PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
			}

			if ((hold & 0xC) != 0) {
				return 0;
			}
			if ((press & 0x100) == 0) {
				if ((press & 0x200) == 0) {
					return 0;
				}
				*reinterpret_cast<u8*>(state + 8) = 0xFF;
				*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
				*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 2;
				PlaySe__6CSoundFiiii(&Sound, 3, 0x40, 0x7F, 0);
				return 0;
			}

			s16 curReply = *reinterpret_cast<s16*>(state + 0x28);
			if (static_cast<int>(curReply) < maxReply - 1) {
				DAT_8032eeec = static_cast<u8>(curReply);
				CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(
				    reinterpret_cast<char*>(this) + (Game.game.m_gameWork.m_menuStageMode == '\0' ? 0xEC : 0xF4));
				char* srcText = reinterpret_cast<char*>(
				    __nwa__FUlPQ27CMemory6CStagePci(0x400, stage, const_cast<char*>("menu_letter.cpp"), 0x65E));
				stage = *reinterpret_cast<CMemory::CStage**>(
				    reinterpret_cast<char*>(this) + (Game.game.m_gameWork.m_menuStageMode == '\0' ? 0xEC : 0xF4));
				char* workText = reinterpret_cast<char*>(
				    __nwa__FUlPQ27CMemory6CStagePci(0x400, stage, const_cast<char*>("menu_letter.cpp"), 0x660));
				memset(srcText, 0, 0x400);
				memset(workText, 0, 0x400);

				u16 msgIndex = *reinterpret_cast<u16*>(caravanWork + DAT_8032eee8 * 0xC + 0x3EC);
				char** mesPtr = reinterpret_cast<char**>(reinterpret_cast<char*>(&Game.game.m_cFlatDataArr[1]) + 0x44);
				strcpy(srcText, mesPtr[(msgIndex & 0x7FC) >> 1]);
				MakeAgbString__4CMesFPcPcii(workText, srcText, *reinterpret_cast<u16*>(caravanWork + 0x3E2), 0);

				char* line = workText;
				for (int i = 0; i < 8; ++i) {
					char* newline = strchr(line, '\n');
					if (newline != 0) {
						*newline = '\0';
					}
					if (i == DAT_8032eeec) {
						strcpy(s_ReplyStr, line);
					}
					if (newline == 0) {
						break;
					}
					line = newline + 1;
				}

				__dla__FPv(srcText);
				__dla__FPv(workText);
				*reinterpret_cast<u8*>(state + 8) = 1;
			} else {
				*reinterpret_cast<u8*>(state + 8) = 0xFF;
			}

			*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 2;
			PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
			return 0;
		}

		if (menuMode == 4) {
			if ((hold & 8) == 0) {
				if ((hold & 4) != 0) {
					if (*reinterpret_cast<s16*>(state + 0x28) < 3) {
						*reinterpret_cast<s16*>(state + 0x28) = *reinterpret_cast<s16*>(state + 0x28) + 1;
					} else {
						*reinterpret_cast<s16*>(state + 0x28) = 0;
					}
					PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
				}
			} else {
				if (*reinterpret_cast<s16*>(state + 0x28) == 0) {
					*reinterpret_cast<s16*>(state + 0x28) = 3;
				} else {
					*reinterpret_cast<s16*>(state + 0x28) = *reinterpret_cast<s16*>(state + 0x28) - 1;
				}
				PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
			}

			if ((hold & 0xC) != 0) {
				return 0;
			}
			if ((press & 0x100) != 0) {
				s16 choice = *reinterpret_cast<s16*>(state + 0x28);
				if (choice < 3) {
					DAT_8032eeed = static_cast<signed char>(choice);
					*reinterpret_cast<u8*>(state + 8) = 1;
				} else {
					DAT_8032eeed = 2;
					*reinterpret_cast<u8*>(state + 8) = 0xFF;
				}
				*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
				DAT_8032eef4 = 0;
				DAT_8032eef0 = 0;
				*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 2;
				PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
				return 0;
			}
			if ((press & 0x200) == 0) {
				return 0;
			}
			*reinterpret_cast<u8*>(state + 8) = 0xFF;
			*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 2;
			PlaySe__6CSoundFiiii(&Sound, 3, 0x40, 0x7F, 0);
			return 0;
		}

		if (menuMode != 5) {
			return 0;
		}

		if ((hold & 0xC) != 0) {
			*reinterpret_cast<u16*>(state + 0x28) ^= 1;
			PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
			return 0;
		}
		if ((press & 0x100) != 0) {
			if (*reinterpret_cast<s16*>(state + 0x28) == 0) {
				int itemValue = DAT_8032eef0;
				int gilValue = 0;
				if (DAT_8032eeed != 0) {
					itemValue = 0;
					if (DAT_8032eeed == 1) {
						gilValue = DAT_8032eef0;
					}
				}
				FGLetterReply__12CCaravanWorkFiiii(
				    reinterpret_cast<void*>(caravanWork),
				    static_cast<int>(DAT_8032eee8),
				    static_cast<int>(DAT_8032eeec),
				    itemValue,
				    gilValue);
				if (DAT_8032eeed == 0) {
					DeleteItemIdx__12CCaravanWorkFii(
					    reinterpret_cast<void*>(caravanWork), static_cast<int>(DAT_8032eeee), 0);
				} else {
					AddGil__12CCaravanWorkFi(reinterpret_cast<void*>(caravanWork), -gilValue);
				}
				*reinterpret_cast<u8*>(state + 8) = 1;
			} else {
				*reinterpret_cast<u8*>(state + 8) = 0xFF;
			}

			*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
			*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 2;
			PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
			return 0;
		}
		if ((press & 0x200) == 0) {
			return 0;
		}
		*reinterpret_cast<u8*>(state + 8) = 0xFF;
		*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
		*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 2;
		PlaySe__6CSoundFiiii(&Sound, 3, 0x40, 0x7F, 0);
		return 0;
	}

	int letterCount = *reinterpret_cast<int*>(caravanWork + 1000);
	if ((letterCount == 0) && ((hold & 0xC) != 0)) {
		PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
		return 0;
	}

	if ((hold & 8) == 0) {
		if ((hold & 4) != 0) {
			int cursor = static_cast<int>(*reinterpret_cast<s16*>(state + 0x26));
			if ((cursor < 8) && (cursor < letterCount - 1)) {
				*reinterpret_cast<s16*>(state + 0x26) = *reinterpret_cast<s16*>(state + 0x26) + 1;
				PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
			} else if (*reinterpret_cast<s16*>(state + 0x34) + cursor < letterCount - 1) {
				*reinterpret_cast<s16*>(state + 0x34) = *reinterpret_cast<s16*>(state + 0x34) + 1;
				PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
			} else {
				PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
			}
		}
	} else if (*reinterpret_cast<s16*>(state + 0x26) == 0) {
		if (*reinterpret_cast<s16*>(state + 0x34) == 0) {
			PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
		} else {
			*reinterpret_cast<s16*>(state + 0x34) = *reinterpret_cast<s16*>(state + 0x34) - 1;
			PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
		}
	} else {
		*reinterpret_cast<s16*>(state + 0x26) = *reinterpret_cast<s16*>(state + 0x26) - 1;
		PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7F, 0);
	}

	if ((hold & 0xC) != 0) {
		return 0;
	}
	if ((press & 0x20) != 0) {
		*reinterpret_cast<s16*>(state + 0x1E) = 1;
		PlaySe__6CSoundFiiii(&Sound, 0x5A, 0x40, 0x7F, 0);
		return 1;
	}
	if ((press & 0x40) != 0) {
		*reinterpret_cast<s16*>(state + 0x1E) = -1;
		PlaySe__6CSoundFiiii(&Sound, 0x5A, 0x40, 0x7F, 0);
		return 1;
	}
	if ((press & 0x100) == 0) {
		if ((press & 0x200) == 0) {
			return 0;
		}
		*reinterpret_cast<u8*>(state + 0xD) = 1;
		PlaySe__6CSoundFiiii(&Sound, 3, 0x40, 0x7F, 0);
		return 1;
	}

	if (letterCount == 0) {
		PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7F, 0);
		return 0;
	}

	*reinterpret_cast<s16*>(state + 0x12) = *reinterpret_cast<s16*>(state + 0x12) + 1;
	DAT_8032eee8 = *reinterpret_cast<s16*>(state + 0x34) + *reinterpret_cast<s16*>(state + 0x26);
	int entry = caravanWork + DAT_8032eee8 * 0xC;
	m_tempVar__4CMes[0] = *reinterpret_cast<u16*>(entry + 0x3F0);
	m_tempVar__4CMes[1] = *reinterpret_cast<u16*>(entry + 0x3F2);
	m_tempVar__4CMes[2] = *reinterpret_cast<u16*>(entry + 0x3F4);
	m_tempVar__4CMes[3] = *reinterpret_cast<u16*>(entry + 0x3F6);

	int openAnim = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(openAnim + 0x24) = 0;
	*reinterpret_cast<int*>(openAnim + 0x2C) = 10;
	*reinterpret_cast<int*>(openAnim + 0x30) = 10;
	*reinterpret_cast<int*>(openAnim + 0x64) = 0;
	*reinterpret_cast<int*>(openAnim + 0x6C) = 0;
	*reinterpret_cast<int*>(openAnim + 0x70) = 10;

	int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
	s16* panel = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	for (int i = 0; i < panelCount; ++i, panel += 0x20) {
		panel[0x10] = 0;
		panel[0x11] = 0;
		*reinterpret_cast<float*>(panel + 8) = FLOAT_803330f8;
	}

	*reinterpret_cast<s16*>(state + 0x22) = 0;
	PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7F, 0);
	return 0;
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
