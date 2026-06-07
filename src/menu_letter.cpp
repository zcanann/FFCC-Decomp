#include "ffcc/menu_letter.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/mes.h"
#include "ffcc/linkage.h"

#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" char* strcat(char*, const char*);

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

extern float FLOAT_80333088;
extern float FLOAT_8033308c;
extern float FLOAT_803330a0;
extern float FLOAT_803330bc;
extern float FLOAT_803330b8;
extern float FLOAT_803330c0;
extern float FLOAT_803330d0;
extern float FLOAT_803330d4;
extern float FLOAT_803330e0;
extern float FLOAT_803330f0;
extern float FLOAT_803330f4;
extern float FLOAT_803330f8;
extern float FLOAT_80333108;
extern float FLOAT_8033310c;
extern float FLOAT_80333110;
extern float FLOAT_80333128;
extern float FLOAT_8033312c;
extern float FLOAT_80333130;
extern float FLOAT_80333134;
extern float FLOAT_80333138;
extern float FLOAT_8033313c;
extern float FLOAT_80333140;
extern float FLOAT_80333144;
extern float FLOAT_8033314c;
extern float FLOAT_80333148;
extern float FLOAT_80333150;
extern float FLOAT_80333154;
extern float FLOAT_80333158;
extern float FLOAT_8033315c;
extern float FLOAT_80333160;
extern float FLOAT_80333164;
extern float FLOAT_80333168;
extern double DOUBLE_80333090;
extern double DOUBLE_80333098;
extern double DOUBLE_803330a8;
extern double DOUBLE_803330b0;
extern double DOUBLE_803330c8;
extern double DOUBLE_803330d8;
extern double DOUBLE_803330e8;
extern double DOUBLE_80333100;
extern double DOUBLE_80333118;
extern double DOUBLE_80333120;

static short s_SelLetter = 0;
static unsigned char s_OpenClose = 0;
static unsigned char s_ReplyMax = 0;
static unsigned char s_ReplyPos = 0;
static signed char s_Attach = 0;
static signed char s_AttachItemIdx = 0;
static int s_AttachItem = 0;
static int s_AttachMode = 0;
static int s_BackUpCur[2];
static int s_BackUpTopPos = 0;
static char s_ReplyStr[0x80];

extern "C" const char s_menu_letter_cpp[];

namespace {
static const char s_letterItemInfoFmt[] = "%s%s%s%s";
enum {
	kLetterTextScratchSize = 0x400,
};

struct LetterAnimStorage {
	s16 count;
	s16 pad_02;
	unsigned char pad_04[4];
	unsigned char entries[64][0x40];
};

STATIC_ASSERT(sizeof(LetterAnimStorage) == 0x1008);

static inline int GetLetterStateBase(CMenuPcs* menu)
{
	return reinterpret_cast<int>(menu->m_singMenuState);
}

static inline LetterAnimStorage* GetLetterAnimStorage(CMenuPcs* menu)
{
	return reinterpret_cast<LetterAnimStorage*>(menu->m_singleFadeState);
}

static inline char* GetLetterItemName(int itemId)
{
	return Game.m_cFlatDataArr[1].TableStrings(0)[itemId];
}

static inline int GetLetterAnimBase(CMenuPcs* menu)
{
	return reinterpret_cast<int>(menu->m_singleFadeState);
}

static inline s16* GetLetterPanelBase(CMenuPcs* menu)
{
	return reinterpret_cast<s16*>(menu->m_singleFadeState) + 4;
}

static inline CCaravanWork* GetLetterCaravanWork()
{
	return reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
}

static inline void ResetLetterPanelProgress(CMenuPcs* menu)
{
	int panelCount = static_cast<int>(GetLetterAnimStorage(menu)->count);
	s16* panel = GetLetterPanelBase(menu);
	for (int i = 0; i < panelCount; ++i, panel += 0x20) {
		panel[0x10] = 0;
		panel[0x11] = 0;
		*reinterpret_cast<float*>(panel + 8) = FLOAT_803330f8;
	}
}

static inline void ClearLetterAnimStorage(CMenuPcs* menu)
{
	memset(GetLetterAnimStorage(menu), 0, sizeof(*GetLetterAnimStorage(menu)));
	int anim = GetLetterAnimBase(menu) + 8;
	for (int i = 0; i < 8; ++i) {
		*reinterpret_cast<float*>(anim + 0x14) = FLOAT_803330f8;
		*reinterpret_cast<float*>(anim + 0x54) = FLOAT_803330f8;
		*reinterpret_cast<float*>(anim + 0x94) = FLOAT_803330f8;
		*reinterpret_cast<float*>(anim + 0xD4) = FLOAT_803330f8;
		*reinterpret_cast<float*>(anim + 0x114) = FLOAT_803330f8;
		*reinterpret_cast<float*>(anim + 0x154) = FLOAT_803330f8;
		*reinterpret_cast<float*>(anim + 0x194) = FLOAT_803330f8;
		*reinterpret_cast<float*>(anim + 0x1D4) = FLOAT_803330f8;
		anim += 0x200;
	}
}

static inline CMemory::CStage* GetLetterMenuStage(CMenuPcs* menu)
{
	(void)menu;
	if (Game.m_gameWork.m_menuStageMode != 0) {
		return MenuPcs.m_stageF4;
	}
	return MenuPcs.m_menuStage;
}
} // namespace

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit()
{
	int state = GetLetterStateBase(this);
	ClearLetterAnimStorage(this);

	int anim = GetLetterAnimBase(this);
	*reinterpret_cast<int*>(anim + 0x24) = 0;
	*reinterpret_cast<int*>(anim + 0x2C) = 0;
	*reinterpret_cast<int*>(anim + 0x30) = 10;
	*reinterpret_cast<int*>(anim + 0x64) = 0;
	*reinterpret_cast<unsigned int*>(anim + 0x6C) =
	    ~(((-static_cast<int>(static_cast<char>(m_singleMenuCtrlResetFlag)) |
	        static_cast<int>(static_cast<char>(m_singleMenuCtrlResetFlag))) >>
	       31)) &
	    10;
	*reinterpret_cast<int*>(anim + 0x70) = 10;
	GetLetterAnimStorage(this)->count = 2;

	*reinterpret_cast<s16*>(state + 0x22) = 0;
	*reinterpret_cast<s16*>(state + 0x26) = 0;
	*reinterpret_cast<s16*>(state + 0x28) = 0;
	*reinterpret_cast<s16*>(state + 0x34) = 0;
	*reinterpret_cast<char*>(state + 0xB) = 1;

	s_AttachItem = 0;
	s_AttachMode = 0;
	s_Attach = 2;
	s_SelLetter = 0;
	s_BackUpCur[0] = 0;
	s_BackUpCur[1] = 0;
	s_BackUpTopPos = 0;

	SetSingWinScl(FLOAT_803330f8);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit0()
{
	int state = GetLetterStateBase(this);
	ClearLetterAnimStorage(this);

	int anim = GetLetterAnimBase(this);
	*reinterpret_cast<int*>(anim + 0x24) = 0;
	*reinterpret_cast<int*>(anim + 0x2C) = 0;
	*reinterpret_cast<int*>(anim + 0x30) = 10;
	GetLetterAnimStorage(this)->count = 1;

	*reinterpret_cast<s16*>(state + 0x22) = 0;
	*reinterpret_cast<s16*>(state + 0x26) = static_cast<s16>(s_BackUpCur[0]);
	*reinterpret_cast<s16*>(state + 0x28) = static_cast<s16>(s_BackUpCur[1]);
	*reinterpret_cast<s16*>(state + 0x34) = static_cast<s16>(s_BackUpTopPos);
	s_SelLetter = static_cast<s16>(s_BackUpCur[0] + s_BackUpTopPos);

	s_BackUpCur[0] = 0;
	s_BackUpCur[1] = 0;
	s_BackUpTopPos = 0;

	SetSingWinScl(FLOAT_803330f8);
}

/*
 * --INFO--
 * PAL Address: 80167c3c
 * PAL Size: 408b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::LetterInit1()
{
	int iVar4;
	int iVar5;
	float fVar1;

	memset(GetLetterAnimStorage(this), 0, sizeof(*GetLetterAnimStorage(this)));
	fVar1 = FLOAT_803330f8;
	iVar4 = GetLetterAnimBase(this) + 8;
	iVar5 = 8;
	do {
		*reinterpret_cast<float*>(iVar4 + 0x14) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x54) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x94) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0xD4) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x114) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x154) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x194) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x1D4) = fVar1;
		iVar4 += 0x200;
		--iVar5;
	} while (iVar5 != 0);

	iVar4 = GetLetterAnimBase(this);
	*reinterpret_cast<int*>(iVar4 + 0x24) = 0x5F;
	*reinterpret_cast<s16*>(iVar4 + 0xC) = 0x238;
	*reinterpret_cast<s16*>(iVar4 + 0xE) = 0x178;
	double scale = DOUBLE_803330a8;
	*reinterpret_cast<s16*>(iVar4 + 8) = static_cast<s16>((0x280 - *reinterpret_cast<s16*>(iVar4 + 0xC)) * scale);
	*reinterpret_cast<s16*>(iVar4 + 0xA) = static_cast<s16>((0x1C0 - *reinterpret_cast<s16*>(iVar4 + 0xE)) * scale);
	fVar1 = FLOAT_803330bc;
	*reinterpret_cast<float*>(iVar4 + 0x10) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x14) = fVar1;
	*reinterpret_cast<int*>(iVar4 + 0x2C) = 0;
	*reinterpret_cast<int*>(iVar4 + 0x30) = 10;

	iVar4 = GetLetterAnimBase(this);
	*reinterpret_cast<int*>(iVar4 + 0x64) = 0x3E;
	*reinterpret_cast<s16*>(iVar4 + 0x4C) = 0xA8;
	*reinterpret_cast<s16*>(iVar4 + 0x4E) = 0x60;
	*reinterpret_cast<s16*>(iVar4 + 0x48) = 0x20;
	*reinterpret_cast<s16*>(iVar4 + 0x4A) = static_cast<s16>(0x1A0 - *reinterpret_cast<s16*>(iVar4 + 0x4E));
	*reinterpret_cast<float*>(iVar4 + 0x50) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x54) = fVar1;
	*reinterpret_cast<int*>(iVar4 + 0x6C) = 0;
	*reinterpret_cast<int*>(iVar4 + 0x70) = 10;

	GetLetterAnimStorage(this)->count = 2;
	m_singMenuState->frame = 0;
	m_singMenuState->initialized = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit2()
{
	int state = GetLetterStateBase(this);
	if (*reinterpret_cast<char*>(state + 0xC) != '\0') {
		return;
	}

	char info[0x80];
	char left[0x10];
	char right[0x10];
	s16 winW;
	s16 winH;

	CCaravanWork* caravanWork = GetLetterCaravanWork();
	CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
	if (!letter->AttachmentIsGil()) {
		int itemId = letter->AttachmentValue() * 5 + 4;
		char* value = GetLetterItemName(itemId);
		if (Game.m_gameWork.m_languageId == 2) {
			sprintf(info, s_letterItemInfoFmt,
			        GetMenuStr(0x23),
			        value,
			        GetMenuStr(0x24),
			        GetMenuStr(0x22));
		} else {
			sprintf(info, "%s%s", GetMenuStr(0x22), value);
		}
	} else {
		int gil = static_cast<int>(letter->AttachmentValue()) * 100;
		if (Game.m_gameWork.m_languageId == 2) {
			sprintf(info, "%d%s%s", gil, GetMenuStr(4), GetMenuStr(0x22));
		} else {
			sprintf(info, "%s%d%s", GetMenuStr(0x22), gil, GetMenuStr(4));
		}
	}

	strcpy(left, "");
	strcat(left, GetMenuStr(1), 0x10);
	strcpy(right, "");
	strcat(right, GetMenuStr(2), 0x10);
	SetSingDynamicWinMessInfo(3, info, left, right, 0, 0, 0, 0, 0);
	GetSingWinSize(0, &winW, &winH, 1);
	SetMcWinInfo(static_cast<int>(winW), static_cast<int>(winH));
	m_menuWindowInfo->state = 0;
	*reinterpret_cast<s16*>(state + 0x28) = 0;
	*reinterpret_cast<char*>(state + 0xC) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit3()
{
	int state = GetLetterStateBase(this);
	if (*reinterpret_cast<char*>(state + 0xC) != '\0') {
		return;
	}

	CCaravanWork* caravanWork = GetLetterCaravanWork();
	CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
	char lines[8][0x80];
	char unused0[0x80];
	char unused1[0x80];
	char unused2[0x80];
	char unused3[0x80];
	char unused4[0x80];
	char unused5[0x80];
	char unused6[0x88];
	memset(lines, 0, sizeof(lines));

	char* srcText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x323) char[kLetterTextScratchSize];
	char* workText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x325) char[kLetterTextScratchSize];
	memset(srcText, 0, kLetterTextScratchSize);
	memset(workText, 0, kLetterTextScratchSize);

	unsigned short msgIndex = letter->HeaderWord();
	strcpy(srcText, Game.m_cFlatDataArr[1].Message(((msgIndex & 0x7FC) >> 1) + 0x10));
	CMes::MakeAgbString(workText, srcText, caravanWork->m_genderFlag, 0);

	s_ReplyMax = 0;
	char* curLine = workText;
	for (int i = 0; i < 8; ++i) {
		char* newline = strchr(curLine, '\n');
		if (newline != 0) {
			*newline = '\0';
		}

		sprintf(lines[i], "%s%s%s", GetMenuStr(0x23), curLine, GetMenuStr(0x24));
		s_ReplyMax = static_cast<unsigned char>(s_ReplyMax + 1);
		if (newline == 0) {
			break;
		}
		curLine = newline + 1;
	}

	delete[] srcText;
	delete[] workText;

	int closeLine = s_ReplyMax;
	s_ReplyMax = static_cast<unsigned char>(s_ReplyMax + 1);
	strcat(lines[closeLine], GetMenuStr(3), 0x80);
	SetSingDynamicWinMessInfo(s_ReplyMax, lines[0], unused0, unused1, unused2, unused3, unused4, unused5, unused6);

	s16 winW;
	s16 winH;
	GetSingWinSize(0, &winW, &winH, 1);
	SetMcWinInfo(winW, winH);
	m_menuWindowInfo->state = 0;
	*reinterpret_cast<unsigned char*>(state + 0x9) = 0xFF;
	*reinterpret_cast<char*>(state + 0xC) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterInit4()
{
	int state = GetLetterStateBase(this);
	if (*reinterpret_cast<char*>(state + 0xC) != '\0') {
		return;
	}

	CCaravanWork* caravanWork = GetLetterCaravanWork();
	CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
	unsigned char languageId = Game.m_gameWork.m_languageId;
	char lines[8][0x80];
	memset(lines, 0, sizeof(lines));
	unsigned int letterWord = letter->Word0();
	char** subjectTable = Game.m_cFlatDataArr[1].TableStrings(2);
	char** itemTable = Game.m_cFlatDataArr[1].TableStrings(0);

	const char* title = subjectTable[(letterWord >> 9) & 0x1FF];
	if (languageId == 3) {
		sprintf(lines[0], "%s%s", GetMenuStr(0x26), title);
	} else if (languageId == 2) {
		sprintf(lines[0], "%s%s", title, GetMenuStr(0x26));
	} else if (languageId == 5) {
		sprintf(lines[0], "%s%s", GetMenuStr(0x26), title);
	} else if (languageId == 4) {
		sprintf(lines[0], "%s%s%s", GetMenuStr(0x26), title, GetMenuStr(0x25));
	} else {
		sprintf(lines[0], "%s%s%s", GetMenuStr(0x25), title, GetMenuStr(0x26));
	}

	sprintf(lines[1], "%s%s%s", GetMenuStr(0x23), s_ReplyStr, GetMenuStr(0x24));

	int lineCount = 2;
	if (s_Attach != 2) {
		if (languageId == 2) {
			if (s_Attach == 0) {
				sprintf(lines[2], "%s%s%s", GetMenuStr(0x23),
				        GetLetterItemName(s_AttachItem * 5 + 4),
				        GetMenuStr(0x24));
			} else if (s_Attach == 1) {
				sprintf(lines[2], "%d%s", s_AttachItem, GetMenuStr(4));
			}
			strcat(lines[2], GetMenuStr(0x28), 0x80);
		} else {
			strcpy(lines[2], GetMenuStr(0x28));
			if (s_Attach == 0) {
				strcat(lines[2], itemTable[s_AttachItem * 5 + 4], 0x80);
			} else if (s_Attach == 1) {
				int offs = strlen(lines[2]);
				sprintf(lines[2] + offs, "%d%s", s_AttachItem, GetMenuStr(4));
			}
		}
		lineCount = 3;
	}

	strcat(lines[lineCount], GetMenuStr(0x21), 0x80);
	strcpy(lines[lineCount + 1], "");
	strcat(lines[lineCount + 1], GetMenuStr(1), 0x80);
	strcpy(lines[lineCount + 2], "");
	strcat(lines[lineCount + 2], GetMenuStr(2), 0x80);
	SetSingDynamicWinMessInfo(lineCount + 3, lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[6], lines[7]);

	s16 winW;
	s16 winH;
	GetSingWinSize(0, &winW, &winH, 1);
	SetMcWinInfo(winW, winH);
	m_menuWindowInfo->state = 0;
	*reinterpret_cast<s16*>(state + 0x28) = 0;
	*reinterpret_cast<unsigned char*>(state + 0x9) = 0xFF;
	*reinterpret_cast<char*>(state + 0xC) = 1;
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

	s_OpenClose = 1;
	if (m_singMenuState->initialized == '\0') {
		memset(GetLetterAnimStorage(this), 0, sizeof(*GetLetterAnimStorage(this)));
		fVar1 = FLOAT_803330f8;
		iVar4 = GetLetterAnimBase(this) + 8;
		iVar8 = 8;
		do {
			*reinterpret_cast<float*>(iVar4 + 0x14) = fVar1;
			*reinterpret_cast<float*>(iVar4 + 0x54) = fVar1;
			*reinterpret_cast<float*>(iVar4 + 0x94) = fVar1;
			*reinterpret_cast<float*>(iVar4 + 0xD4) = fVar1;
			*reinterpret_cast<float*>(iVar4 + 0x114) = fVar1;
			*reinterpret_cast<float*>(iVar4 + 0x154) = fVar1;
			*reinterpret_cast<float*>(iVar4 + 0x194) = fVar1;
			*reinterpret_cast<float*>(iVar4 + 0x1D4) = fVar1;
			iVar4 += 0x200;
			--iVar8;
		} while (iVar8 != 0);
		iVar4 = GetLetterAnimBase(this);
		*reinterpret_cast<int*>(iVar4 + 0x24) = 0;
		*reinterpret_cast<int*>(iVar4 + 0x2C) = 0;
		*reinterpret_cast<int*>(iVar4 + 0x30) = 10;
		iVar4 = GetLetterAnimBase(this);
		*reinterpret_cast<int*>(iVar4 + 0x64) = 0;
		*reinterpret_cast<unsigned int*>(iVar4 + 0x6C) =
			~(((-static_cast<int>(static_cast<char>(m_singleMenuCtrlResetFlag)) |
				static_cast<int>(static_cast<char>(m_singleMenuCtrlResetFlag))) >>
			   31)) &
			10;
		*reinterpret_cast<int*>(iVar4 + 0x70) = 10;
		GetLetterAnimStorage(this)->count = 2;
		m_singMenuState->frame = 0;
		m_singMenuState->initialized = 1;
		iVar4 = SingGetLetterAttachflg();
		if (iVar4 >= 0) {
			memset(GetLetterAnimStorage(this), 0, sizeof(*GetLetterAnimStorage(this)));
			fVar1 = FLOAT_803330f8;
			iVar4 = GetLetterAnimBase(this) + 8;
			iVar8 = 8;
			do {
				*reinterpret_cast<float*>(iVar4 + 0x14) = fVar1;
				*reinterpret_cast<float*>(iVar4 + 0x54) = fVar1;
				*reinterpret_cast<float*>(iVar4 + 0x94) = fVar1;
				*reinterpret_cast<float*>(iVar4 + 0xD4) = fVar1;
				*reinterpret_cast<float*>(iVar4 + 0x114) = fVar1;
				*reinterpret_cast<float*>(iVar4 + 0x154) = fVar1;
				*reinterpret_cast<float*>(iVar4 + 0x194) = fVar1;
				*reinterpret_cast<float*>(iVar4 + 0x1D4) = fVar1;
				iVar4 += 0x200;
				--iVar8;
			} while (iVar8 != 0);
			iVar4 = GetLetterAnimBase(this);
			*reinterpret_cast<int*>(iVar4 + 0x24) = 0;
			*reinterpret_cast<int*>(iVar4 + 0x2C) = 0;
			*reinterpret_cast<int*>(iVar4 + 0x30) = 10;
			GetLetterAnimStorage(this)->count = 1;
			m_singMenuState->frame = 0;
			m_singMenuState->selectedIndex = static_cast<s16>(s_BackUpCur[0]);
			m_singMenuState->scrollIndex = static_cast<s16>(s_BackUpCur[1]);
			m_singMenuState->topIndex = static_cast<s16>(s_BackUpTopPos);
			s_SelLetter = static_cast<s16>(s_BackUpCur[0] + s_BackUpTopPos);
		} else {
			m_singMenuState->selectedIndex = 0;
			m_singMenuState->scrollIndex = 0;
			m_singMenuState->topIndex = 0;
			s_AttachItem = 0;
			s_AttachMode = 0;
			s_Attach = 2;
			s_SelLetter = 0;
		}
		s_BackUpCur[0] = 0;
		s_BackUpCur[1] = 0;
		s_BackUpTopPos = 0;
		SetSingWinScl(FLOAT_803330f8);
	}
	iVar6 = 0;
	m_singMenuState->frame =
		m_singMenuState->frame + 1;
	iVar5 = static_cast<int>(GetLetterAnimStorage(this)->count);
	psVar7 = GetLetterPanelBase(this);
	iVar8 = static_cast<int>(m_singMenuState->frame);
	iVar4 = iVar5;
	if (0 < iVar5) {
		do {
			fVar1 = FLOAT_803330bc;
			if (iVar8 >= *reinterpret_cast<int*>(psVar7 + 0x12)) {
				if (*reinterpret_cast<int*>(psVar7 + 0x12) + *reinterpret_cast<int*>(psVar7 + 0x14) <= iVar8) {
					iVar6 = iVar6 + 1;
					*reinterpret_cast<float*>(psVar7 + 8) = FLOAT_803330f8;
					*reinterpret_cast<float*>(psVar7 + 0x18) = fVar1;
					*reinterpret_cast<float*>(psVar7 + 0x1A) = fVar1;
				} else {
					*reinterpret_cast<int*>(psVar7 + 0x10) = *reinterpret_cast<int*>(psVar7 + 0x10) + 1;
					*reinterpret_cast<float*>(psVar7 + 8) =
						static_cast<float>((DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(psVar7 + 0x14)))) *
						                   static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(psVar7 + 0x10))));
					if ((*reinterpret_cast<unsigned int*>(psVar7 + 0x16) & 2) == 0) {
						fVar1 = static_cast<float>((DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(psVar7 + 0x14)))) *
						                           static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(psVar7 + 0x10))));
						*reinterpret_cast<float*>(psVar7 + 0x18) =
							(*reinterpret_cast<float*>(psVar7 + 0x1C) - static_cast<float>(psVar7[0])) * fVar1;
						*reinterpret_cast<float*>(psVar7 + 0x1A) =
							(*reinterpret_cast<float*>(psVar7 + 0x1E) - static_cast<float>(psVar7[1])) * fVar1;
					}
				}
			}
			psVar7 += 0x20;
			iVar4 = iVar4 + -1;
		} while (iVar4 != 0);
	}
	bool allFinished = iVar5 == iVar6;
	if (allFinished) {
		iVar4 = SingGetLetterAttachflg();
		if (iVar4 < 0) {
			m_singMenuState->procState = 1;
		} else {
			m_singMenuState->procState = 0;
			m_singMenuState->uniteState = 1;
			LetterInit1();
		}
	}
	return allFinished;
}

/*
 * --INFO--
 * PAL Address: 80166678
 * PAL Size: 4556b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::LetterCtrl()
{
	int done = 0;
	int ret = 0;
	*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x32) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30);
	s_OpenClose = 0;

	int state = GetLetterStateBase(this);
	s16 phase = *reinterpret_cast<s16*>(state + 0x12);
	if (phase == 0) {
		s16 mode = *reinterpret_cast<s16*>(state + 0x30);
		if (mode == 0) {
			*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;
			int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
			s16* panel = GetLetterPanelBase(this);
			int frame = static_cast<int>(*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22));
			done = 0;
			for (int i = 0; i < panelCount; ++i, panel += 0x20) {
				float f = FLOAT_803330bc;
				if (frame >= *reinterpret_cast<int*>(panel + 0x12)) {
					if (*reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14) <= frame) {
						++done;
						*reinterpret_cast<float*>(panel + 8) = FLOAT_803330f8;
						*reinterpret_cast<float*>(panel + 0x18) = f;
						*reinterpret_cast<float*>(panel + 0x1A) = f;
					} else {
						*reinterpret_cast<int*>(panel + 0x10) = *reinterpret_cast<int*>(panel + 0x10) + 1;
						*reinterpret_cast<float*>(panel + 8) =
						    static_cast<float>((DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
						                       static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
						if ((*reinterpret_cast<unsigned int*>(panel + 0x16) & 2) == 0) {
							f = static_cast<float>((DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
							                       static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
							*reinterpret_cast<float*>(panel + 0x18) =
							    (*reinterpret_cast<float*>(panel + 0x1C) - static_cast<float>(panel[0])) * f;
							*reinterpret_cast<float*>(panel + 0x1A) =
							    (*reinterpret_cast<float*>(panel + 0x1E) - static_cast<float>(panel[1])) * f;
						}
					}
				}
			}
			int listOpenFinished = 0;
			if (panelCount == done) {
				listOpenFinished = 1;
			}
			if (listOpenFinished) {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x34) = s_SelLetter - *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x26);
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 1;
			}
		} else if (mode == 1) {
			CCaravanWork::CLetterWork* letter = &GetLetterCaravanWork()->m_letters[s_SelLetter];
			if (!letter->IsOpened()) {
				letter->SetOpened();
			}

			*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22) + 1;
			int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
			s16* panel = GetLetterPanelBase(this);
			int frame = static_cast<int>(*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22));
			int messOpenDone = 0;
			for (int i = 0; i < panelCount; ++i, panel += 0x20) {
				float f = FLOAT_803330bc;
				if (frame >= *reinterpret_cast<int*>(panel + 0x12)) {
					if (*reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14) <= frame) {
						++messOpenDone;
						*reinterpret_cast<float*>(panel + 8) = FLOAT_803330f8;
						*reinterpret_cast<float*>(panel + 0x18) = f;
						*reinterpret_cast<float*>(panel + 0x1A) = f;
					} else {
						*reinterpret_cast<int*>(panel + 0x10) = *reinterpret_cast<int*>(panel + 0x10) + 1;
						*reinterpret_cast<float*>(panel + 8) =
						    static_cast<float>((DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
						                       static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
						if ((*reinterpret_cast<unsigned int*>(panel + 0x16) & 2) == 0) {
							f = static_cast<float>((DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
							                       static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
							*reinterpret_cast<float*>(panel + 0x18) =
							    (*reinterpret_cast<float*>(panel + 0x1C) - static_cast<float>(panel[0])) * f;
							*reinterpret_cast<float*>(panel + 0x1A) =
							    (*reinterpret_cast<float*>(panel + 0x1E) - static_cast<float>(panel[1])) * f;
						}
					}
				}
			}
			int messOpenFinished = 0;
			if (panelCount == messOpenDone) {
				messOpenFinished = 1;
			}
			if (messOpenFinished) {
				if (SingGetLetterAttachflg() >= 0) {
					if (s_AttachMode > 0) {
						*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 5;
					} else {
						s_Attach = 2;
						*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 3;
						*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = static_cast<s16>(s_ReplyPos);
					}
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 0;
					*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
					SingSetLetterAttachflg(-1);
				} else {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 1;
				}
			}
		} else if (mode == 2) {
			if (*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) == '\0') {
				char info[0x80];
				char left[0x10];
				char right[0x10];
				s16 winW;
				s16 winH;
				CCaravanWork::CLetterWork* letter = &GetLetterCaravanWork()->m_letters[s_SelLetter];
				if (letter->AttachmentIsGil()) {
					s16 gil = static_cast<int>(letter->AttachmentValue()) * 100;
					if (Game.m_gameWork.m_languageId == 2) {
						sprintf(info, "%d%s%s",
						        gil,
						        GetMenuStr(4),
						        GetMenuStr(0x22));
					} else {
						sprintf(info, "%s%d%s",
						        GetMenuStr(0x22),
						        gil,
						        GetMenuStr(4));
					}
				} else {
					int itemId = letter->AttachmentValue() * 5 + 4;
					char* value = GetLetterItemName(itemId);
					if (Game.m_gameWork.m_languageId == 2) {
						sprintf(info, s_letterItemInfoFmt,
						        GetMenuStr(0x23),
						        value,
						        GetMenuStr(0x24),
						        GetMenuStr(0x22));
					} else {
						sprintf(info, "%s%s", GetMenuStr(0x22), value);
					}
				}
				strcpy(left, "");
				strcat(left, GetMenuStr(1));
				strcpy(right, "");
				strcat(right, GetMenuStr(2));
				SetSingDynamicWinMessInfo(3, info, left, right, 0, 0, 0, 0, 0);
				GetSingWinSize(0, &winW, &winH, 1);
				SetMcWinInfo(static_cast<int>(winW), static_cast<int>(winH));
				m_menuWindowInfo->state = 0;
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = 0;
				*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 1;
			}
			if (m_menuWindowInfo->state == 1) {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 1;
			}
		} else if (mode == 3) {
			if (LetterReplyWinOpen()) {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 1;
			}
		} else if (mode == 4) {
			if (*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) == '\0') {
				s16 winW;
				s16 winH;
				GetSingWinSize(2, &winW, &winH, 0);
				SetMcWinInfo(static_cast<int>(winW), static_cast<int>(winH));
				m_menuWindowInfo->state = 0;
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = 0;
				*reinterpret_cast<unsigned char*>(GetLetterStateBase(this) + 9) = 0xFF;
				*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 1;
			}
			if (m_menuWindowInfo->state == 1) {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 1;
			}
		} else if (mode == 5) {
			if (LetterConfirmOpen()) {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 1;
			}
		}
	} else if (phase == 1) {
		ret = LetterCtrlCur();
	} else if (phase == 2) {
		s16 mode = *reinterpret_cast<s16*>(state + 0x30);
		if (mode == 0) {
			*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;
			int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
			s16* panel = GetLetterPanelBase(this);
			int frame = static_cast<int>(*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22));
			done = 0;
			for (int i = 0; i < panelCount; ++i, panel += 0x20) {
				float f = FLOAT_803330bc;
				if (frame >= *reinterpret_cast<int*>(panel + 0x12)) {
					if (*reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14) <= frame) {
						++done;
						*reinterpret_cast<float*>(panel + 8) = FLOAT_803330bc;
						*reinterpret_cast<float*>(panel + 0x18) = f;
						*reinterpret_cast<float*>(panel + 0x1A) = f;
					} else {
						*reinterpret_cast<int*>(panel + 0x10) = *reinterpret_cast<int*>(panel + 0x10) + 1;
						*reinterpret_cast<float*>(panel + 8) =
						    static_cast<float>(DOUBLE_803330e8 -
						                       (DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
						                           static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
						if ((*reinterpret_cast<unsigned int*>(panel + 0x16) & 2) == 0) {
							f = static_cast<float>(DOUBLE_803330e8 -
							                       (DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
							                           static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
							*reinterpret_cast<float*>(panel + 0x18) =
							    (*reinterpret_cast<float*>(panel + 0x1C) - static_cast<float>(panel[0])) * f;
							*reinterpret_cast<float*>(panel + 0x1A) =
							    (*reinterpret_cast<float*>(panel + 0x1E) - static_cast<float>(panel[1])) * f;
						}
					}
				}
			}
			int uniteFinished = 0;
			if (panelCount == done) {
				uniteFinished = 1;
			}
			if (uniteFinished) {
				LetterInit1();
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 1;
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 0;
			}
		} else if (mode == 1) {
			signed char action = *reinterpret_cast<signed char*>(state + 8);
			if (action < 1) {
				*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;
				int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
				s16* panel = GetLetterPanelBase(this);
				int frame = static_cast<int>(*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22));
				for (int i = 0; i < panelCount; ++i, panel += 0x20) {
					float f = FLOAT_803330bc;
					if (frame >= *reinterpret_cast<int*>(panel + 0x12)) {
						if (*reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14) <= frame) {
							++done;
							*reinterpret_cast<float*>(panel + 8) = FLOAT_803330bc;
							*reinterpret_cast<float*>(panel + 0x18) = f;
							*reinterpret_cast<float*>(panel + 0x1A) = f;
						} else {
							*reinterpret_cast<int*>(panel + 0x10) = *reinterpret_cast<int*>(panel + 0x10) + 1;
							*reinterpret_cast<float*>(panel + 8) =
							    static_cast<float>(DOUBLE_803330e8 -
							                       (DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
							                           static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
							if ((*reinterpret_cast<unsigned int*>(panel + 0x16) & 2) == 0) {
								f = static_cast<float>(DOUBLE_803330e8 -
								                       (DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
								                           static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
								*reinterpret_cast<float*>(panel + 0x18) =
								    (*reinterpret_cast<float*>(panel + 0x1C) - static_cast<float>(panel[0])) * f;
								*reinterpret_cast<float*>(panel + 0x1A) =
								    (*reinterpret_cast<float*>(panel + 0x1E) - static_cast<float>(panel[1])) * f;
							}
						}
					}
				}
				int replyFinished = 0;
				if (panelCount == done) {
					replyFinished = 1;
				}
				if (replyFinished) {
					if (s_Attach == 2) {
						memset(GetLetterAnimStorage(this), 0, 0x1008);
						float resetAlpha = FLOAT_803330f8;
						int anim = GetLetterAnimBase(this) + 8;
						for (int i = 0; i < 8; ++i) {
							*reinterpret_cast<float*>(anim + 0x14) = resetAlpha;
							*reinterpret_cast<float*>(anim + 0x54) = resetAlpha;
							*reinterpret_cast<float*>(anim + 0x94) = resetAlpha;
							*reinterpret_cast<float*>(anim + 0xD4) = resetAlpha;
							*reinterpret_cast<float*>(anim + 0x114) = resetAlpha;
							*reinterpret_cast<float*>(anim + 0x154) = resetAlpha;
							*reinterpret_cast<float*>(anim + 0x194) = resetAlpha;
							*reinterpret_cast<float*>(anim + 0x1D4) = resetAlpha;
							anim += 0x200;
						}
						anim = GetLetterAnimBase(this);
						*reinterpret_cast<int*>(anim + 0x24) = 0;
						*reinterpret_cast<int*>(anim + 0x2C) = 0;
						*reinterpret_cast<int*>(anim + 0x30) = 10;
						anim = GetLetterAnimBase(this);
						*reinterpret_cast<int*>(anim + 0x64) = 0;
						*reinterpret_cast<unsigned int*>(anim + 0x6C) =
						    ~(((-static_cast<int>(static_cast<char>(m_singleMenuCtrlResetFlag)) |
						        static_cast<int>(static_cast<char>(m_singleMenuCtrlResetFlag))) >>
						       31)) &
						    10;
						*reinterpret_cast<int*>(anim + 0x70) = 10;
						GetLetterAnimStorage(this)->count = 2;
						*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22) = 0;
						*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xB) = 1;
					} else {
						ret = 1;
					}
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 0;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 0;
				}
			} else {
				if (action == 1) {
					*reinterpret_cast<s16*>(state + 0x30) = 2;
				} else if (action == 2) {
					*reinterpret_cast<s16*>(state + 0x28) = 0;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 3;
				}
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 0;
				*reinterpret_cast<unsigned char*>(GetLetterStateBase(this) + 8) = 0;
				*reinterpret_cast<unsigned char*>(GetLetterStateBase(this) + 0xC) = 0;
			}
			*reinterpret_cast<unsigned char*>(GetLetterStateBase(this) + 8) = 0;
		} else if (mode == 2) {
			if (m_menuWindowInfo->state == 3) {
				*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
				if (*reinterpret_cast<signed char*>(GetLetterStateBase(this) + 8) < 1) {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 1;
				} else {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 3;
				}
				*reinterpret_cast<unsigned char*>(GetLetterStateBase(this) + 8) = 0;
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 0;
				*reinterpret_cast<unsigned char*>(GetLetterStateBase(this) + 0xC) = 0;
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = 0;
			}
		} else if (mode == 3) {
			if (m_menuWindowInfo->state == 3) {
				*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
				if (*reinterpret_cast<signed char*>(GetLetterStateBase(this) + 8) < 1) {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 1;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 1;
				} else {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 4;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 0;
				}
				*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
			}
		} else if (mode == 4) {
			if (m_menuWindowInfo->state == 3) {
				*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
				if (*reinterpret_cast<signed char*>(GetLetterStateBase(this) + 8) < 1) {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 3;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 0;
					*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = static_cast<s16>(s_ReplyPos);
				} else {
					if (s_Attach != 2) {
						if (s_Attach == 0) {
							SingSetLetterAttachflg(1);
						} else {
							SingSetLetterAttachflg(5);
						}
						*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 1;
						float resetAlpha = FLOAT_803330f8;
						*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 2;
						*reinterpret_cast<unsigned char*>(GetLetterStateBase(this) + 8) = 0xFF;
						int anim = GetLetterAnimBase(this);
						*reinterpret_cast<int*>(anim + 0x2C) = 0;
						*reinterpret_cast<int*>(anim + 0x30) = 10;
						*reinterpret_cast<int*>(anim + 0x6C) = 0;
						*reinterpret_cast<int*>(anim + 0x70) = 10;
						int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
						s16* panel = GetLetterPanelBase(this);
						for (int i = 0; i < panelCount; ++i, panel += 0x20) {
							*reinterpret_cast<int*>(panel + 0x10) = 0;
							*reinterpret_cast<float*>(panel + 8) = resetAlpha;
						}
						*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22) = 0;
					} else {
						*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 5;
						*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 0;
					}
					*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
				}
			}
		} else if (mode == 5) {
			if (m_menuWindowInfo->state == 3) {
				*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
				if (*reinterpret_cast<signed char*>(GetLetterStateBase(this) + 8) < 1) {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 3;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 0;
					*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = static_cast<s16>(s_ReplyPos);
				} else {
					s_Attach = 2;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30) = 1;
					float resetAlpha = FLOAT_803330f8;
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = 2;
					*reinterpret_cast<unsigned char*>(GetLetterStateBase(this) + 8) = 0xFF;
					int anim = GetLetterAnimBase(this);
					*reinterpret_cast<int*>(anim + 0x2C) = 0;
					*reinterpret_cast<int*>(anim + 0x30) = 10;
					*reinterpret_cast<int*>(anim + 0x6C) = 0;
					*reinterpret_cast<int*>(anim + 0x70) = 10;
					int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
					s16* panel = GetLetterPanelBase(this);
					for (int i = 0; i < panelCount; ++i, panel += 0x20) {
						*reinterpret_cast<int*>(panel + 0x10) = 0;
						*reinterpret_cast<float*>(panel + 8) = resetAlpha;
					}
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22) = 0;
					*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 0;
				}
			}
		}
	}

	float f = FLOAT_803330f8;
	if (ret == 0) {
		return 0;
	}

	int anim = GetLetterAnimBase(this);
	*reinterpret_cast<int*>(anim + 0x24) = 0;
	if (s_Attach == 2) {
		*reinterpret_cast<int*>(anim + 0x2C) = 10;
		*reinterpret_cast<int*>(anim + 0x30) = 10;
		*reinterpret_cast<int*>(anim + 0x64) = 0;
		*reinterpret_cast<int*>(anim + 0x6C) = 0;
		*reinterpret_cast<int*>(anim + 0x70) = 10;
	} else {
		*reinterpret_cast<int*>(anim + 0x2C) = 0;
		*reinterpret_cast<int*>(anim + 0x30) = 10;
		GetLetterAnimStorage(this)->count = 1;
	}

	int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
	s16* panel = GetLetterPanelBase(this);
	for (int i = 0; i < panelCount; ++i, panel += 0x20) {
		*reinterpret_cast<int*>(panel + 0x10) = 0;
		*reinterpret_cast<float*>(panel + 8) = f;
	}
	*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22) = 0;
	return ret;
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
	s_OpenClose = 1;
	int finished = 0;

	int state = GetLetterStateBase(this);
	*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;

	int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
	s16* entry = GetLetterPanelBase(this);
	int frame = static_cast<int>(*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22));

	for (int i = 0; i < panelCount; ++i, entry += 0x20) {
		float f = FLOAT_803330bc;
		if (frame >= *reinterpret_cast<int*>(entry + 0x12)) {
			if (*reinterpret_cast<int*>(entry + 0x12) + *reinterpret_cast<int*>(entry + 0x14) <= frame) {
				++finished;
				*reinterpret_cast<float*>(entry + 8) = FLOAT_803330bc;
				*reinterpret_cast<float*>(entry + 0x18) = f;
				*reinterpret_cast<float*>(entry + 0x1A) = f;
			} else {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				*reinterpret_cast<float*>(entry + 8) =
				    static_cast<float>(DOUBLE_803330e8 -
				                       (DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(entry + 0x14)))) *
				                           static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(entry + 0x10))));
				if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
					f = static_cast<float>(DOUBLE_803330e8 -
					                       (DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(entry + 0x14)))) *
					                           static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(entry + 0x10))));
					*reinterpret_cast<float*>(entry + 0x18) =
					    (*reinterpret_cast<float*>(entry + 0x1C) - static_cast<float>(entry[0])) * f;
					*reinterpret_cast<float*>(entry + 0x1A) =
					    (*reinterpret_cast<float*>(entry + 0x1E) - static_cast<float>(entry[1])) * f;
				}
			}
		}
	}

	int allFinished = 0;
	if (panelCount == finished) {
		allFinished = 1;
	}
	if (allFinished && SingGetLetterAttachflg() >= 0) {
		int state2 = GetLetterStateBase(this);
		s_BackUpCur[0] = *reinterpret_cast<s16*>(state2 + 0x26);
		s_BackUpCur[1] = *reinterpret_cast<s16*>(state2 + 0x28);
		s_BackUpTopPos = s_SelLetter - s_BackUpCur[0];
	}

	return allFinished;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterLstOpen()
{
	int state = GetLetterStateBase(this);
	*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;

	int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
	s16* panel = GetLetterPanelBase(this);
	int frame = static_cast<int>(*reinterpret_cast<s16*>(state + 0x22));
	int done = 0;

	for (int i = 0; i < panelCount; ++i, panel += 0x20) {
		float f = FLOAT_803330bc;
		if (frame >= *reinterpret_cast<int*>(panel + 0x12)) {
			if (*reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14) > frame) {
				*reinterpret_cast<int*>(panel + 0x10) = *reinterpret_cast<int*>(panel + 0x10) + 1;
				*reinterpret_cast<float*>(panel + 8) =
				    static_cast<float>(*reinterpret_cast<int*>(panel + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(panel + 0x14));
				if ((*reinterpret_cast<unsigned int*>(panel + 0x16) & 2) == 0) {
					f = static_cast<float>(*reinterpret_cast<int*>(panel + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(panel + 0x14));
					*reinterpret_cast<float*>(panel + 0x18) =
					    (*reinterpret_cast<float*>(panel + 0x1C) - static_cast<float>(panel[0])) * f;
					*reinterpret_cast<float*>(panel + 0x1A) =
					    (*reinterpret_cast<float*>(panel + 0x1E) - static_cast<float>(panel[1])) * f;
				}
			} else {
				++done;
				*reinterpret_cast<float*>(panel + 8) = FLOAT_803330f8;
				*reinterpret_cast<float*>(panel + 0x18) = f;
				*reinterpret_cast<float*>(panel + 0x1A) = f;
			}
		}
	}

	if (panelCount == done) {
		*reinterpret_cast<s16*>(state + 0x34) = s_SelLetter - *reinterpret_cast<s16*>(state + 0x26);
		*reinterpret_cast<s16*>(state + 0x12) = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterLstClose()
{
	int state = GetLetterStateBase(this);
	*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;

	int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
	s16* panel = GetLetterPanelBase(this);
	int frame = static_cast<int>(*reinterpret_cast<s16*>(state + 0x22));
	int done = 0;

	for (int i = 0; i < panelCount; ++i, panel += 0x20) {
		float f = FLOAT_803330bc;
		if (frame >= *reinterpret_cast<int*>(panel + 0x12)) {
			if (*reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14) > frame) {
				*reinterpret_cast<int*>(panel + 0x10) = *reinterpret_cast<int*>(panel + 0x10) + 1;
				*reinterpret_cast<float*>(panel + 8) =
				    static_cast<float>(DOUBLE_803330e8 -
				                       (DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
				                           static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
				if ((*reinterpret_cast<unsigned int*>(panel + 0x16) & 2) == 0) {
					f = static_cast<float>(DOUBLE_803330e8 -
					                       (DOUBLE_803330e8 / static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x14)))) *
					                           static_cast<double>(static_cast<float>(*reinterpret_cast<int*>(panel + 0x10))));
					*reinterpret_cast<float*>(panel + 0x18) =
					    (*reinterpret_cast<float*>(panel + 0x1C) - static_cast<float>(panel[0])) * f;
					*reinterpret_cast<float*>(panel + 0x1A) =
					    (*reinterpret_cast<float*>(panel + 0x1E) - static_cast<float>(panel[1])) * f;
				}
			} else {
				++done;
				*reinterpret_cast<float*>(panel + 8) = FLOAT_803330bc;
				*reinterpret_cast<float*>(panel + 0x18) = f;
				*reinterpret_cast<float*>(panel + 0x1A) = f;
			}
		}
	}

	if (panelCount == done) {
		LetterInit1();
		*reinterpret_cast<s16*>(state + 0x30) = 1;
		*reinterpret_cast<s16*>(state + 0x12) = 0;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterMessOpen()
{
	int state = GetLetterStateBase(this);
	CCaravanWork::CLetterWork* letter = &GetLetterCaravanWork()->m_letters[s_SelLetter];
	if (!letter->IsOpened()) {
		letter->SetOpened();
	}

	*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;
	int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
	s16* panel = GetLetterPanelBase(this);
	int frame = static_cast<int>(*reinterpret_cast<s16*>(state + 0x22));
	int done = 0;

	for (int i = 0; i < panelCount; ++i, panel += 0x20) {
		float f = FLOAT_803330bc;
		if (frame >= *reinterpret_cast<int*>(panel + 0x12)) {
			if (*reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14) > frame) {
				*reinterpret_cast<int*>(panel + 0x10) = *reinterpret_cast<int*>(panel + 0x10) + 1;
				*reinterpret_cast<float*>(panel + 8) =
				    static_cast<float>(*reinterpret_cast<int*>(panel + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(panel + 0x14));
				if ((*reinterpret_cast<unsigned int*>(panel + 0x16) & 2) == 0) {
					f = static_cast<float>(*reinterpret_cast<int*>(panel + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(panel + 0x14));
					*reinterpret_cast<float*>(panel + 0x18) =
					    (*reinterpret_cast<float*>(panel + 0x1C) - static_cast<float>(panel[0])) * f;
					*reinterpret_cast<float*>(panel + 0x1A) =
					    (*reinterpret_cast<float*>(panel + 0x1E) - static_cast<float>(panel[1])) * f;
				}
			} else {
				++done;
				*reinterpret_cast<float*>(panel + 8) = FLOAT_803330f8;
				*reinterpret_cast<float*>(panel + 0x18) = f;
				*reinterpret_cast<float*>(panel + 0x1A) = f;
			}
		}
	}

	if (panelCount == done) {
		if (SingGetLetterAttachflg() < 0) {
			*reinterpret_cast<s16*>(state + 0x12) = 1;
		} else {
			if (s_AttachMode < 1) {
				s_Attach = 2;
				*reinterpret_cast<s16*>(state + 0x30) = 3;
				*reinterpret_cast<s16*>(state + 0x28) = static_cast<s16>(s_ReplyPos);
			} else {
				*reinterpret_cast<s16*>(state + 0x30) = 5;
			}
			*reinterpret_cast<s16*>(state + 0x12) = 0;
			*reinterpret_cast<char*>(state + 0xC) = 0;
			SingSetLetterAttachflg(-1);
		}
	}
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterItemWinOpen()
{
	int state = GetLetterStateBase(this);
	if (*reinterpret_cast<char*>(state + 0xC) == '\0') {
		char info[0x80];
		char left[0x10];
		char right[0x10];
		s16 winW;
		s16 winH;

		CCaravanWork::CLetterWork* letter = &GetLetterCaravanWork()->m_letters[s_SelLetter];
		if (!letter->AttachmentIsGil()) {
			int itemId = letter->AttachmentValue() * 5 + 4;
			char* value = GetLetterItemName(itemId);
			if (Game.m_gameWork.m_languageId == 2) {
				sprintf(info, s_letterItemInfoFmt,
				        GetMenuStr(0x23),
				        value,
				        GetMenuStr(0x24),
				        GetMenuStr(0x22));
			} else {
				sprintf(info, "%s%s", GetMenuStr(0x22), value);
			}
		} else {
			int gil = static_cast<int>(letter->AttachmentValue()) * 100;
			if (Game.m_gameWork.m_languageId == 2) {
				sprintf(info, "%d%s%s",
				        gil,
				        GetMenuStr(4),
				        GetMenuStr(0x22));
			} else {
				sprintf(info, "%s%d%s",
				        GetMenuStr(0x22),
				        gil,
				        GetMenuStr(4));
			}
		}

		strcpy(left, "");
		strcat(left, GetMenuStr(1), 0x10);
		strcpy(right, "");
		strcat(right, GetMenuStr(2), 0x10);
		SetSingDynamicWinMessInfo(3, info, left, right, 0, 0, 0, 0, 0);
		GetSingWinSize(0, &winW, &winH, 1);
		SetMcWinInfo(static_cast<int>(winW), static_cast<int>(winH));
		m_menuWindowInfo->state = 0;
		*reinterpret_cast<s16*>(state + 0x28) = 0;
		*reinterpret_cast<char*>(state + 0xC) = 1;
	}

	if (m_menuWindowInfo->state == 1) {
		*reinterpret_cast<s16*>(state + 0x12) = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterItemWinClose()
{
	int state = GetLetterStateBase(this);
	if (m_menuWindowInfo->state == 3) {
		*reinterpret_cast<char*>(state + 0xC) = 0;
		if (*reinterpret_cast<signed char*>(state + 8) < 1) {
			*reinterpret_cast<s16*>(state + 0x30) = 1;
		} else {
			*reinterpret_cast<s16*>(state + 0x30) = 3;
		}
		*reinterpret_cast<unsigned char*>(state + 8) = 0;
		*reinterpret_cast<s16*>(state + 0x12) = 0;
		*reinterpret_cast<unsigned char*>(state + 0xC) = 0;
		*reinterpret_cast<s16*>(state + 0x28) = 0;
	}
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
	CCaravanWork* caravanWork = GetLetterCaravanWork();
	int languageId = Game.m_gameWork.m_languageId;
	if (*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) == '\0') {
		char lines[8][0x80];
		memset(lines, 0, sizeof(lines));

		char* srcText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x323) char[kLetterTextScratchSize];
		char* workText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x325) char[kLetterTextScratchSize];

		memset(srcText, 0, kLetterTextScratchSize);
		memset(workText, 0, kLetterTextScratchSize);

		CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
		unsigned short msgIndex = letter->HeaderWord();
		strcpy(srcText, Game.m_cFlatDataArr[1].Message(((msgIndex & 0x7FC) >> 1) + 0x11));
		CMes::MakeAgbString(workText, srcText, caravanWork->m_genderFlag, 0);

		s_ReplyMax = 0;
		char* curLine = workText;
		int i = 0;
		do {
			char* newline = strchr(curLine, '\n');
			if (newline != 0) {
				*newline = '\0';
			}

			if (languageId == 2) {
				sprintf(lines[i], "%s%s%s", GetMenuStr(0x23), curLine, GetMenuStr(0x24));
			} else {
				sprintf(lines[i], "%s%s%s", GetMenuStr(0x23), curLine, GetMenuStr(0x24));
			}

			s_ReplyMax = static_cast<unsigned char>(s_ReplyMax + 1);
			if (newline == 0) {
				break;
			}
			++i;
			curLine = newline + 1;
		} while (i < 7);

		delete[] srcText;
		delete[] workText;

		const char* closeText = GetMenuStr(3);
		int lineIndex = static_cast<signed char>(s_ReplyMax);
		s_ReplyMax = static_cast<unsigned char>(s_ReplyMax + 1);
		strcat(lines[lineIndex], closeText);

		SetSingDynamicWinMessInfo(static_cast<signed char>(s_ReplyMax),
			lines[0],
			lines[1],
			lines[2],
			lines[3],
			lines[4],
			lines[5],
			lines[6],
			lines[7]);

		s16 winW;
		s16 winH;
		GetSingWinSize(0, &winW, &winH, 1);
		SetMcWinInfo(winW, winH);
		m_menuWindowInfo->state = 0;
		*reinterpret_cast<char*>(GetLetterStateBase(this) + 0x9) = -1;
		*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 1;
	}
	bool opened = false;
	if (m_menuWindowInfo->state == 1) {
		opened = true;
	}
	return opened;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterReplyWinClose()
{
	int state = GetLetterStateBase(this);
	if (m_menuWindowInfo->state == 3) {
		*reinterpret_cast<char*>(state + 0xC) = 0;
		if (*reinterpret_cast<signed char*>(state + 8) < 1) {
			*reinterpret_cast<s16*>(state + 0x30) = 1;
			*reinterpret_cast<s16*>(state + 0x12) = 1;
		} else {
			*reinterpret_cast<s16*>(state + 0x30) = 4;
			*reinterpret_cast<s16*>(state + 0x12) = 0;
		}
		*reinterpret_cast<char*>(state + 0xC) = 0;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterAttachWinOpen()
{
	int state = GetLetterStateBase(this);
	if (*reinterpret_cast<char*>(state + 0xC) == '\0') {
		s16 winW;
		s16 winH;
		GetSingWinSize(2, &winW, &winH, 0);
		SetMcWinInfo(static_cast<int>(winW), static_cast<int>(winH));
		m_menuWindowInfo->state = 0;
		*reinterpret_cast<s16*>(state + 0x28) = 0;
		*reinterpret_cast<unsigned char*>(state + 9) = 0xFF;
		*reinterpret_cast<char*>(state + 0xC) = 1;
	}

	if (m_menuWindowInfo->state == 1) {
		*reinterpret_cast<s16*>(state + 0x12) = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterAttachWinClose()
{
	int state = GetLetterStateBase(this);
	if (m_menuWindowInfo->state == 3) {
		*reinterpret_cast<char*>(state + 0xC) = 0;
		if (*reinterpret_cast<signed char*>(state + 8) < 1) {
			*reinterpret_cast<s16*>(state + 0x30) = 3;
			*reinterpret_cast<s16*>(state + 0x12) = 0;
			*reinterpret_cast<char*>(state + 0xC) = 0;
			*reinterpret_cast<s16*>(state + 0x28) = static_cast<s16>(s_ReplyPos);
		} else {
			if (s_Attach == 2) {
				*reinterpret_cast<s16*>(state + 0x30) = 5;
				*reinterpret_cast<s16*>(state + 0x12) = 0;
			} else {
				if (s_Attach == 0) {
					SingSetLetterAttachflg(1);
				} else {
					SingSetLetterAttachflg(5);
				}
				*reinterpret_cast<s16*>(state + 0x30) = 1;
				*reinterpret_cast<s16*>(state + 0x12) = 2;
				*reinterpret_cast<unsigned char*>(state + 8) = 0xFF;
				int anim = GetLetterAnimBase(this);
				*reinterpret_cast<int*>(anim + 0x2C) = 0;
				*reinterpret_cast<int*>(anim + 0x30) = 10;
				*reinterpret_cast<int*>(anim + 0x6C) = 0;
				*reinterpret_cast<int*>(anim + 0x70) = 10;
				ResetLetterPanelProgress(this);
				*reinterpret_cast<s16*>(state + 0x22) = 0;
			}
			*reinterpret_cast<char*>(state + 0xC) = 0;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CMenuPcs::LetterConfirmOpen()
{
	CCaravanWork* caravanWork = GetLetterCaravanWork();
	int languageId = Game.m_gameWork.m_languageId;

	if (*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) == '\0') {
		char lines[8][0x80];
		memset(lines, 0, sizeof(lines));
		switch (languageId) {
		case 3: {
			const char* title = Game.m_cFlatDataArr[1].TableStrings(2)[caravanWork->m_letters[s_SelLetter].SenderId()];
			sprintf(lines[0], "%s%s", GetMenuStr(0x26), title);
			break;
		}
		case 2: {
			const char* title = Game.m_cFlatDataArr[1].TableStrings(2)[caravanWork->m_letters[s_SelLetter].SenderId()];
			sprintf(lines[0], "%s%s", title, GetMenuStr(0x26));
			break;
		}
		case 5: {
			const char* title = Game.m_cFlatDataArr[1].TableStrings(2)[caravanWork->m_letters[s_SelLetter].SenderId()];
			sprintf(lines[0], "%s%s", GetMenuStr(0x26), title);
			break;
		}
		case 4: {
			const char* title = Game.m_cFlatDataArr[1].TableStrings(2)[caravanWork->m_letters[s_SelLetter].SenderId()];
			sprintf(lines[0], "%s%s%s", GetMenuStr(0x26), title, GetMenuStr(0x25));
			break;
		}
		case 0:
		case 1:
		default: {
			const char* title = Game.m_cFlatDataArr[1].TableStrings(2)[caravanWork->m_letters[s_SelLetter].SenderId()];
			sprintf(lines[0], "%s%s%s", GetMenuStr(0x25), title, GetMenuStr(0x26));
			break;
		}
		}

		switch (languageId) {
		case 3:
			sprintf(lines[1], "%s%s%s%s",
			        GetMenuStr(0x25),
			        GetMenuStr(0x23),
			        s_ReplyStr,
			        GetMenuStr(0x24));
			break;
		case 2:
			sprintf(lines[1], "%s%s%s%s",
			        GetMenuStr(0x23),
			        s_ReplyStr,
			        GetMenuStr(0x24),
			        GetMenuStr(0x27));
			break;
		case 0:
		case 1:
		default:
			sprintf(lines[1], "%s%s%s", GetMenuStr(0x23), s_ReplyStr, GetMenuStr(0x24));
			break;
		}

		int lineCount = 2;
		if (s_Attach != 2) {
			if (languageId == 2) {
				if (s_Attach == 0) {
					sprintf(lines[2], "%s%s%s", GetMenuStr(0x23),
					        GetLetterItemName(s_AttachItem * 5 + 4),
					        GetMenuStr(0x24));
				} else if (s_Attach == 1) {
					sprintf(lines[2], "%d%s", s_AttachItem, GetMenuStr(4));
				}
				strcat(lines[2], GetMenuStr(0x28));
			} else {
				strcpy(lines[2], GetMenuStr(0x28));
				if (s_Attach == 0) {
					strcat(lines[2], Game.m_cFlatDataArr[1].TableStrings(0)[s_AttachItem * 5 + 4]);
				} else if (s_Attach == 1) {
					int offs = strlen(lines[2]);
					sprintf(lines[2] + offs, "%d%s", s_AttachItem, GetMenuStr(4));
				}
			}
			lineCount = 3;
		}

		strcat(lines[lineCount], GetMenuStr(0x21));
		strcpy(lines[lineCount + 1], "");
		strcat(lines[lineCount + 1], GetMenuStr(1));
		strcpy(lines[lineCount + 2], "");
		strcat(lines[lineCount + 2], GetMenuStr(2));

		SetSingDynamicWinMessInfo(lineCount + 3, lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[6], lines[7]);

		s16 winW;
		s16 winH;
		GetSingWinSize(0, &winW, &winH, 1);
		SetMcWinInfo(winW, winH);
		m_menuWindowInfo->state = 0;
		*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = 0;
		*reinterpret_cast<char*>(GetLetterStateBase(this) + 0x9) = -1;
		*reinterpret_cast<char*>(GetLetterStateBase(this) + 0xC) = 1;
	}

	bool opened = false;
	if (m_menuWindowInfo->state == 1) {
		opened = true;
	}
	return opened;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LetterConfirmClose()
{
	int state = GetLetterStateBase(this);
	if (m_menuWindowInfo->state == 3) {
		*reinterpret_cast<char*>(state + 0xC) = 0;
		if (*reinterpret_cast<signed char*>(state + 8) < 1) {
			*reinterpret_cast<s16*>(state + 0x30) = 3;
			*reinterpret_cast<s16*>(state + 0x12) = 0;
			*reinterpret_cast<char*>(state + 0xC) = 0;
			*reinterpret_cast<s16*>(state + 0x28) = static_cast<s16>(s_ReplyPos);
		} else {
			s_Attach = 2;
			*reinterpret_cast<s16*>(state + 0x30) = 1;
			*reinterpret_cast<s16*>(state + 0x12) = 2;
			*reinterpret_cast<unsigned char*>(state + 8) = 0xFF;
			int anim = GetLetterAnimBase(this);
			*reinterpret_cast<int*>(anim + 0x2C) = 0;
			*reinterpret_cast<int*>(anim + 0x30) = 10;
			*reinterpret_cast<int*>(anim + 0x6C) = 0;
			*reinterpret_cast<int*>(anim + 0x70) = 10;
			ResetLetterPanelProgress(this);
			*reinterpret_cast<s16*>(state + 0x22) = 0;
			*reinterpret_cast<char*>(state + 0xC) = 0;
		}
	}
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
	if (m_singMenuState->uniteState == 0) {
		LetterListDraw();
	} else {
		LetterMessDraw();
	}
}

/*
 * --INFO--
 * PAL Address: 80165554
 * PAL Size: 1528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::LetterListDraw()
{
	int menuDataBase = GetLetterAnimBase(this);

	if ((static_cast<char>(s_OpenClose) != 0) && (static_cast<char>(m_singleMenuCtrlResetFlag) == '\0')) {
		DrawSingleCrescent(FLOAT_803330f8,
			static_cast<float>(DOUBLE_803330e8 - static_cast<double>(*reinterpret_cast<float*>(menuDataBase + 0x18))));
		DrawSingleStat(
			static_cast<float>(DOUBLE_803330e8 - static_cast<double>(*reinterpret_cast<float*>(menuDataBase + 0x18))));
		DrawSingleHelpWim(
			static_cast<float>(DOUBLE_803330e8 - static_cast<double>(*reinterpret_cast<float*>(menuDataBase + 0x18))));
	}

	if (GetLetterAnimStorage(this)->count == 1) {
		return;
	}

	LetterLstBaseDraw(*reinterpret_cast<float*>(menuDataBase + 0x58));

	CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<char*>(this) + 0xF8);
	font->SetMargin(FLOAT_803330f8);
	font->SetShadow(1);
	font->SetScale(FLOAT_803330f8);
	font->DrawInit();

	CColor titleColor(0xFF, 0xFF, 0xFF, static_cast<u8>(FLOAT_803330a0 * *reinterpret_cast<float*>(menuDataBase + 0x58)));
	font->SetColor(titleColor.color);

	char* menuTitle = GetMenuStr(0x1D);
	float titleX = static_cast<float>((FLOAT_80333158 - font->GetWidth(menuTitle)) *
	                                  DOUBLE_803330a8);
	DrawShadowFont(font, menuTitle, titleX, FLOAT_8033315c, 0x18, 0x12);

	if (static_cast<double>(*reinterpret_cast<float*>(menuDataBase + 0x58)) < DOUBLE_803330e8) {
		return;
	}

	CColor textColor(0xFF, 0xFF, 0xFF, 0xFF);
	font->SetColor(textColor.color);

	CCaravanWork* caravanWork = GetLetterCaravanWork();
	const int topRow = static_cast<int>(m_singMenuState->topIndex);

	int y = 0x60;
	int letterIndex;
	for (int row = 0; row < 9 && (letterIndex = topRow + row) < caravanWork->m_letterCount; ++row) {
		CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[letterIndex];

		int tlut;
		if (!letter->IsOpened()) {
			tlut = 9;
		} else if (letter->IsReplySent()) {
			tlut = 8;
		} else {
			tlut = 0;
		}

		font->SetTlut(tlut);

		float rowY = static_cast<float>(y) - FLOAT_80333148;
		const char* from = Game.m_cFlatDataArr[1].TableStrings(5)[(letter->Word0() & 0x7FC) >> 2];
		font->SetPosX(FLOAT_80333160);
		font->SetPosY(rowY);
		font->Draw(from);

		const char* subject = Game.m_cFlatDataArr[1].TableStrings(2)[(letter->Word0() >> 9) & 0x1FF];
		font->SetPosX(FLOAT_80333164);
		font->SetPosY(rowY);
		font->Draw(subject);

		y += 0x20;
	}

	DrawInit();

	s16 topVal = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x34);
	unsigned char pageMark = 0;
	if (topVal != 0) {
		pageMark = 1;
	}
	if (topVal + 9 < caravanWork->m_letterCount) {
		pageMark = static_cast<unsigned char>(pageMark | 2);
	}

	if (pageMark != 0) {
		const int frame = static_cast<int>(System.m_frameCounter);
		const int cycle = ((frame / 0x14) + (frame >> 31));
		const int phase = (frame + (cycle - (cycle >> 31)) * -0x14) - 10;
		const unsigned int absPhase = static_cast<unsigned int>(phase < 0 ? -phase : phase);
		const float markScale =
		    static_cast<float>(DOUBLE_80333098 * static_cast<double>(absPhase) + DOUBLE_80333090);

		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

		const int alpha = static_cast<int>(
		    FLOAT_803330a0 * static_cast<float>(DOUBLE_803330b0 * static_cast<double>(absPhase) + DOUBLE_803330a8));
		GXColor markColor;
		markColor.r = 0xFF;
		markColor.g = 0xFF;
		markColor.b = 0xFF;
		markColor.a = static_cast<u8>(alpha);
		GXSetChanMatColor(GX_COLOR0A0, markColor);
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x43));

		const float iconSize = FLOAT_803330b8;
		const double iconOffset = (iconSize - iconSize * markScale) * DOUBLE_803330a8;
		const double markX = static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_80333088) + iconOffset));
		const double markY = static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_8033308c) + iconOffset));

		if ((pageMark & 1) != 0) {
			MenuPcs.DrawRect(
			    4, static_cast<float>(markX), static_cast<float>(markY), FLOAT_803330b8,
			    FLOAT_803330b8, FLOAT_803330bc, FLOAT_803330bc, static_cast<float>(markScale),
			    static_cast<float>(markScale), 0.0f);
		}

		if ((pageMark & 2) != 0) {
			MenuPcs.DrawRect(
			    0, static_cast<float>(markX), static_cast<float>(static_cast<float>(markY + static_cast<double>(FLOAT_803330c0))),
			    FLOAT_803330b8, FLOAT_803330b8, FLOAT_803330bc, FLOAT_803330bc,
			    static_cast<float>(markScale), static_cast<float>(markScale), 0.0f);
		}
	}

	unsigned int iconY = 0x5B;
	const int iconX = static_cast<int>(FLOAT_80333168);
	int iconLetterIndex;
	for (int row = 0; row < 9 && (iconLetterIndex = topRow + row) < caravanWork->m_letterCount; ++row) {
		CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[iconLetterIndex];
		if (letter->AttachmentValue() != 0) {
			const int icon = 0x26 + (letter->IsAttachmentClaimed() ? 1 : 0);
			DrawSingleIcon(icon, iconX, static_cast<int>(static_cast<double>(iconY)), FLOAT_803330f8, 0, FLOAT_803330f8);
		}
		iconY += 0x20;
	}

	const int cursorX = static_cast<int>(FLOAT_803330f4 + static_cast<float>(static_cast<int>(System.m_frameCounter) % 8));
	const int cursorY = static_cast<int>(static_cast<double>(*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x26) * 0x20 + 0x60));
	DrawCursor(cursorX, cursorY, FLOAT_803330f8);
}

/*
 * --INFO--
 * PAL Address: 80164ee0
 * PAL Size: 1652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::LetterMessDraw()
{
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	CCaravanWork* const caravanWork = GetLetterCaravanWork();
	int state = GetLetterStateBase(this);
	s16 mode = *reinterpret_cast<s16*>(state + 0x32);

	s16* panel = reinterpret_cast<s16*>(m_singleFadeState) + 4;
	for (int i = 0; i < reinterpret_cast<s16*>(m_singleFadeState)[0]; ++i, panel += 0x20) {
		int tex = *reinterpret_cast<int*>(panel + 0xE);
		if (tex < 0) {
			continue;
		}

		float x0 = static_cast<float>(panel[0]);
		float y0 = static_cast<float>(panel[1]);
		float x1 = static_cast<float>(panel[2]);
		float y1 = static_cast<float>(panel[3]);
		u8 alpha = static_cast<u8>(FLOAT_803330a0 * *reinterpret_cast<float*>(panel + 8));
		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = alpha;
		GXSetChanMatColor(GX_COLOR0A0, color);
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(*reinterpret_cast<int*>(panel + 0xE)));
		MenuPcs.DrawRect(
		    0, x0, y0, x1,
		    y1, *reinterpret_cast<float*>(panel + 4), *reinterpret_cast<float*>(panel + 6),
		    *reinterpret_cast<float*>(panel + 10), *reinterpret_cast<float*>(panel + 10), 0.0f);
	}

	s16* animBase = reinterpret_cast<s16*>(m_singleFadeState);
	CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<char*>(this) + 0xF8);
	font->SetShadow(0);
	font->SetMargin(FLOAT_8033313c);
	font->SetScale(FLOAT_80333140);
	font->DrawInit();
	font->SetTlut(0x1C);

	{
		u8 alpha = static_cast<u8>(FLOAT_803330a0 * *reinterpret_cast<float*>(animBase + 0xC));
		CColor color(0xFF, 0xFF, 0xFF, alpha);
		font->SetColor(color.color);
	}

	CMemory::CStage* stage = GetLetterMenuStage(this);
	char* srcText = new (stage, const_cast<char*>(s_menu_letter_cpp), 0x535) char[kLetterTextScratchSize];
	stage = GetLetterMenuStage(this);
	char* workText = new (stage, const_cast<char*>(s_menu_letter_cpp), 0x537) char[kLetterTextScratchSize];

	memset(srcText, 0, kLetterTextScratchSize);
	memset(workText, 0, kLetterTextScratchSize);

	CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
	u16 msgIndex = letter->HeaderWord();
	strcpy(srcText, Game.m_cFlatDataArr[1].Message(((msgIndex & 0x7FC) >> 1) + 0x10));
	CMes::MakeAgbString(workText, srcText, caravanWork->m_genderFlag, 0);

	char* curLine = workText;
	int y = 0x58;
	for (int i = 0; i < 7; ++i) {
		char* newline = strchr(curLine, '\n');
		const float yf = static_cast<float>(y);
		if (newline != 0) {
			*newline = '\0';
		}

		if (strlen(curLine) != 0) {
			font->SetPosX(FLOAT_80333144);
			font->SetPosY(yf - FLOAT_80333148);
			font->Draw(curLine);
		}

		if (newline == 0) {
			break;
		}

		curLine = newline + 1;
		y += 0x20;
	}

	delete[] srcText;
	delete[] workText;

	DrawInit();

	if (letter->AttachmentValue() != 0) {
		int icon = 0x26 + (letter->IsAttachmentClaimed() ? 1 : 0);
		DrawSingleIcon(
		    icon, static_cast<int>(FLOAT_8033314c), static_cast<int>(FLOAT_80333150),
		    *reinterpret_cast<float*>(animBase + 0xC), 0, FLOAT_80333154);
	}

	if (mode <= 1) {
		return;
	}

	DrawSingWin(-1);
	if ((*reinterpret_cast<s16*>(state + 0x12) == 1) &&
	    (m_menuWindowInfo->state == 1)) {
		int msgType = static_cast<int>(*reinterpret_cast<signed char*>(state + 9));
		if (mode == 4) {
			DrawSingWinMess(2, msgType, 0);
		} else {
			DrawSingWinMess(0, msgType, 1);
		}

		float cursorX;
		float cursorY;
		MenuWindowInfo* window = m_menuWindowInfo;
		int itemSel = *reinterpret_cast<s16*>(state + 0x28);
		if ((mode == 2) || (mode == 5)) {
			if (mode == 2) {
				itemSel += 1;
			} else {
				itemSel += ((s_Attach == 2) ? 1 : 0) + 4;
			}
			cursorX = static_cast<float>(window->x + 0x14);
			cursorY = static_cast<float>(window->y + itemSel * SingWinMessHeight() + 0x20);
		} else if ((mode == 3) || (mode == 4)) {
			cursorX = static_cast<float>(window->x - 8);
			if (mode == 4) {
				cursorX += FLOAT_80333110;
			}
			cursorY = static_cast<float>(window->y + *reinterpret_cast<s16*>(state + 0x28) * SingWinMessHeight() + 0x20);
		}

		int frameAnim = static_cast<int>(System.m_frameCounter) % 8;
		DrawCursor(static_cast<int>(cursorX + static_cast<float>(frameAnim)), static_cast<int>(cursorY), FLOAT_803330f8);
	}
}

/*
 * --INFO--
 * PAL Address: 80163fdc
 * PAL Size: 3844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::LetterCtrlCur()
{
	bool blocked = false;
	unsigned int press;
	s16 hold;
	int padState = Pad.m_debugPadLock;

	if ((padState != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		int padIndex = 0;
		int mask = -((__cntlzw((unsigned int)Pad.m_debugPadPort) >> 5) & 1);
		padIndex &= ~mask;
		press = Pad.GetPadInputs()[padIndex].buttonDown[0];
	}

	blocked = false;
	if ((padState != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		int padIndex = 0;
		int mask = -((__cntlzw((unsigned int)Pad.m_debugPadPort) >> 5) & 1);
		padIndex &= ~mask;
		hold = Pad.GetPadInputs()[padIndex].repeatButton;
	}

	if (hold == 0) {
		return 0;
	}

	CCaravanWork* const caravanWork = GetLetterCaravanWork();
	int menuMode = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x30);
	if (menuMode == 0) {
		int letterCount = caravanWork->m_letterCount;
		if ((letterCount == 0) && ((hold & 0xC) != 0)) {
			Sound.PlaySe(4, 0x40, 0x7F, 0);
			return 0;
		}

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				int cursor = static_cast<int>(*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x26));
				if ((cursor < 8) && (cursor < letterCount - 1)) {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x26) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x26) + 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else if (*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x34) + cursor < letterCount - 1) {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x34) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x34) + 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				}
			}
		} else if (*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x26) == 0) {
			if (*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x34) == 0) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			} else {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x34) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x34) - 1;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x26) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x26) - 1;
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) != 0) {
			return 0;
		}
		if ((press & 0x20) != 0) {
			*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x1E) = 1;
			Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
			return 1;
		}
		if ((press & 0x40) != 0) {
			*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x1E) = -1;
			Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
			return 1;
		}
		if ((press & 0x100) == 0) {
			if ((press & 0x200) == 0) {
				return 0;
			}
			*reinterpret_cast<u8*>(GetLetterStateBase(this) + 0xD) = 1;
			Sound.PlaySe(3, 0x40, 0x7F, 0);
			return 1;
		}

		if (letterCount == 0) {
			Sound.PlaySe(4, 0x40, 0x7F, 0);
			return 0;
		}

		*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
		s_SelLetter = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x34) + *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x26);
		CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
		CMes::m_tempVar[0] = letter->TempVar(0);
		CMes::m_tempVar[1] = letter->TempVar(1);
		CMes::m_tempVar[2] = letter->TempVar(2);
		CMes::m_tempVar[3] = letter->TempVar(3);

		int openAnim = GetLetterAnimBase(this);
		*reinterpret_cast<int*>(openAnim + 0x24) = 0;
		*reinterpret_cast<int*>(openAnim + 0x2C) = 10;
		*reinterpret_cast<int*>(openAnim + 0x30) = 10;
		*reinterpret_cast<int*>(openAnim + 0x64) = 0;
		*reinterpret_cast<int*>(openAnim + 0x6C) = 0;
		*reinterpret_cast<int*>(openAnim + 0x70) = 10;

		float f = FLOAT_803330f8;
		int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
		s16* panel = GetLetterPanelBase(this);
		for (int i = 0; i < panelCount; ++i, panel += 0x20) {
			*reinterpret_cast<int*>(panel + 0x10) = 0;
			*reinterpret_cast<float*>(panel + 8) = f;
		}

		*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22) = 0;
		Sound.PlaySe(2, 0x40, 0x7F, 0);
		return 0;
	}

	if (menuMode == 1) {
		if ((press & 0x100) != 0) {
			CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
			if ((letter->AttachmentValue() != 0) && !letter->IsAttachmentClaimed()) {
				*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 1;
				*reinterpret_cast<u8*>(GetLetterStateBase(this) + 9) = 5;
				if (!letter->AttachmentIsGil()) {
					if (caravanWork->m_inventoryItemCount + 1 < 0x41) {
						*reinterpret_cast<u8*>(GetLetterStateBase(this) + 9) |= 2;
					}
				} else {
					int canAdd = caravanWork->CanAddGil(letter->AttachmentValue() * 100);
					if (canAdd != 0) {
						*reinterpret_cast<u8*>(GetLetterStateBase(this) + 9) |= 2;
					}
				}
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
				return 0;
			}

			if ((CFlatLetterEventEnabled() != 0) &&
			    letter->HasReply() &&
			    !letter->IsReplySent()) {
				*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 2;
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
				return 0;
			}
			Sound.PlaySe(4, 0x40, 0x7F, 0);
			return 0;
		}

		if ((press & 0x200) == 0) {
			return 0;
		}

		*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 0xFF;
		*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
		int openAnim = GetLetterAnimBase(this);
		*reinterpret_cast<int*>(openAnim + 0x2C) = 0;
		*reinterpret_cast<int*>(openAnim + 0x30) = 10;
		*reinterpret_cast<int*>(openAnim + 0x6C) = 0;
		*reinterpret_cast<int*>(openAnim + 0x70) = 10;

		float f = FLOAT_803330f8;
		int panelCount = static_cast<int>(GetLetterAnimStorage(this)->count);
		s16* panel = GetLetterPanelBase(this);
		for (int i = 0; i < panelCount; ++i, panel += 0x20) {
			*reinterpret_cast<int*>(panel + 0x10) = 0;
			*reinterpret_cast<float*>(panel + 8) = f;
		}

		*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x22) = 0;
		Sound.PlaySe(3, 0x40, 0x7F, 0);
		return 0;
	}

	if (menuMode == 2) {
		if ((hold & 0xC) != 0) {
			*reinterpret_cast<u16*>(GetLetterStateBase(this) + 0x28) ^= 1;
			Sound.PlaySe(1, 0x40, 0x7F, 0);
			return 0;
		}
		if ((press & 0x100) == 0) {
			if ((press & 0x200) == 0) {
				return 0;
			}
			CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
			if ((CFlatLetterEventEnabled() == 0) || !letter->HasReply() ||
			    letter->IsReplySent()) {
				*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 0xFF;
			} else {
				*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 1;
			}
			*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
			m_menuWindowInfo->state = 2;
			Sound.PlaySe(3, 0x40, 0x7F, 0);
			return 0;
		}

		s16 sel = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28);
		if ((static_cast<int>(static_cast<signed char>(*reinterpret_cast<char*>(GetLetterStateBase(this) + 9))) & (1 << (sel + 1))) != 0) {
			CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
			if (sel == 0) {
				unsigned int value = letter->AttachmentValue();
				if (!letter->AttachmentIsGil()) {
					caravanWork->AddItem(static_cast<short>(value), 0);
				} else {
					caravanWork->AddGil(static_cast<int>(value * 100));
				}
				letter->SetAttachmentClaimed();
			}

			if ((CFlatLetterEventEnabled() == 0) || !letter->HasReply() ||
			    letter->IsReplySent()) {
				*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 0xFF;
			} else {
				*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 1;
			}
			*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
			m_menuWindowInfo->state = 2;
			Sound.PlaySe(2, 0x40, 0x7F, 0);
			return 0;
		}

		Sound.PlaySe(4, 0x40, 0x7F, 0);
		return 0;
	}

	if (menuMode == 3) {
		int maxReply = static_cast<int>(s_ReplyMax);
		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (static_cast<int>(*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28)) < maxReply - 1) {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) + 1;
				} else {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) == 0) {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = s_ReplyMax - 1;
			} else {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) - 1;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) != 0) {
			return 0;
		}
		if ((press & 0x100) == 0) {
			if ((press & 0x200) == 0) {
				return 0;
			}
			*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 0xFF;
			*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
			m_menuWindowInfo->state = 2;
			Sound.PlaySe(3, 0x40, 0x7F, 0);
			return 0;
		}

		s16 curReply = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28);
		if (static_cast<int>(curReply) < maxReply - 1) {
			s_ReplyPos = static_cast<u8>(curReply);
			CMemory::CStage* stage = GetLetterMenuStage(this);
			char* srcText = new (stage, const_cast<char*>(s_menu_letter_cpp), 0x65E) char[kLetterTextScratchSize];
			stage = GetLetterMenuStage(this);
			char* workText = new (stage, const_cast<char*>(s_menu_letter_cpp), 0x660) char[kLetterTextScratchSize];
			memset(srcText, 0, kLetterTextScratchSize);
			memset(workText, 0, kLetterTextScratchSize);

			CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
			u16 msgIndex = letter->HeaderWord();
			strcpy(srcText, Game.m_cFlatDataArr[1].Message(((msgIndex & 0x7FC) >> 1) + 0x11));
			CMes::MakeAgbString(workText, srcText, caravanWork->m_genderFlag, 0);

			char* line = workText;
			int i = 0;
			do {
				char* newline = strchr(line, '\n');
				if (newline != 0) {
					*newline = '\0';
				}
				if (i == s_ReplyPos) {
					strcpy(s_ReplyStr, line);
				}
				if (newline == 0) {
					break;
				}
				++i;
				line = newline + 1;
			} while (i < 7);

			delete[] srcText;
			delete[] workText;
			*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 1;
		} else {
			*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 0xFF;
		}

		*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
		m_menuWindowInfo->state = 2;
		Sound.PlaySe(2, 0x40, 0x7F, 0);
		return 0;
	}

	if (menuMode == 4) {
		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) < 3) {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) + 1;
				} else {
					*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) == 0) {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = 3;
			} else {
				*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) - 1;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) != 0) {
			return 0;
		}
		if ((press & 0x100) != 0) {
			s16 choice = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28);
			if (choice < 3) {
				s_Attach = static_cast<signed char>(choice);
				*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 1;
			} else {
				s_Attach = 2;
				*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 0xFF;
			}
			*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
			s_AttachMode = 0;
			s_AttachItem = 0;
			m_menuWindowInfo->state = 2;
			Sound.PlaySe(2, 0x40, 0x7F, 0);
			return 0;
		}
		if ((press & 0x200) == 0) {
			return 0;
		}
		*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 0xFF;
		*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
		m_menuWindowInfo->state = 2;
		Sound.PlaySe(3, 0x40, 0x7F, 0);
		return 0;
	}

	if (menuMode != 5) {
		return 0;
	}

	if ((hold & 0xC) != 0) {
		*reinterpret_cast<u16*>(GetLetterStateBase(this) + 0x28) ^= 1;
		Sound.PlaySe(1, 0x40, 0x7F, 0);
		return 0;
	}
	if ((press & 0x100) != 0) {
		if (*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x28) == 0) {
			int itemValue = s_AttachItem;
			int gilValue = 0;
			if (s_Attach != 0) {
				itemValue = 0;
				if (s_Attach == 1) {
					gilValue = s_AttachItem;
				}
			}
			caravanWork->FGLetterReply(
			    static_cast<int>(s_SelLetter),
			    static_cast<int>(s_ReplyPos),
			    itemValue,
			    gilValue);
			if (s_Attach == 0) {
				caravanWork->DeleteItemIdx(static_cast<int>(s_AttachItemIdx), 0);
			} else {
				caravanWork->AddGil(-gilValue);
			}
			*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 1;
		} else {
			*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 0xFF;
		}

		*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
		m_menuWindowInfo->state = 2;
		Sound.PlaySe(2, 0x40, 0x7F, 0);
		return 0;
	}
	if ((press & 0x200) == 0) {
		return 0;
	}
	*reinterpret_cast<u8*>(GetLetterStateBase(this) + 8) = 0xFF;
	*reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) = *reinterpret_cast<s16*>(GetLetterStateBase(this) + 0x12) + 1;
	m_menuWindowInfo->state = 2;
	Sound.PlaySe(3, 0x40, 0x7F, 0);
	return 0;
}

/*
 * --INFO--
 * PAL Address: 8016398c
 * PAL Size: 1616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::LetterLstBaseDraw(float param_1)
{
	double param = static_cast<double>(param_1);
	if (param <= static_cast<double>(FLOAT_803330bc)) {
		return;
	}

	float x0 = static_cast<float>(static_cast<int>(static_cast<double>(FLOAT_803330d4 - static_cast<float>(static_cast<double>(FLOAT_803330d0) * param * DOUBLE_803330a8)) - DOUBLE_803330a8));
	float y0 = static_cast<float>(static_cast<int>(static_cast<double>(static_cast<float>(DOUBLE_803330d8 + static_cast<double>(FLOAT_803330d0) * param)) - DOUBLE_803330e8));
	float w = static_cast<float>(static_cast<int>(static_cast<double>(FLOAT_803330e0) - DOUBLE_803330a8));
	float h = static_cast<float>(static_cast<int>(static_cast<double>(FLOAT_803330f0) - DOUBLE_803330e8));

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor white;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	white.a = 0xFF;
	GXSetChanMatColor(GX_COLOR0A0, white);

	float x1 = static_cast<float>(x0 + w - FLOAT_803330f4);
	float y1 = static_cast<float>(y0 + h - FLOAT_803330f4);

	for (int i = 0; i < 4; ++i) {
		int tex;
		int flip = 0;
		if (i == 0) {
			tex = 0x3C;
		} else if (i == 1) {
			tex = 0x3C;
		} else if (i == 2) {
			tex = 0x4B;
		} else {
			tex = 0x4D;
		}

		double x = x0;
		double y = y0;
		if ((i & 1) != 0) {
			x = x1;
			if (i == 1) {
				flip = 8;
			}
		}
		if ((i & 2) != 0) {
			y = y1;
		}

		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
		MenuPcs.DrawRect(
		    flip, static_cast<float>(x), static_cast<float>(y), FLOAT_803330f4, FLOAT_803330f4,
		    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, 0.0f);
	}

	float innerW = static_cast<float>(w - DOUBLE_803330d8);
	float innerH = static_cast<float>(h - DOUBLE_803330d8);
	float innerX = static_cast<float>(x0 + FLOAT_803330f4);
	float innerY = static_cast<float>(y0 + FLOAT_803330f4);

	for (int i = 0; i < 2; ++i) {
		int tex = (i == 0) ? 0x49 : 0x4C;
		float y = (i == 0) ? y0 : y1;
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
		MenuPcs.DrawRect(
		    0, static_cast<float>(innerX), static_cast<float>(y), static_cast<float>(innerW), FLOAT_803330f4,
		    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, 0.0f);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x4A));
	for (int i = 0; i < 2; ++i) {
		int flip = (i == 0) ? 0 : 8;
		double x = (i == 0) ? x0 : x1;
		MenuPcs.DrawRect(
		    flip, static_cast<float>(x), static_cast<float>(innerY), FLOAT_803330f4, static_cast<float>(innerH),
		    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, 0.0f);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x4E));
	MenuPcs.DrawRect(
	    0, static_cast<float>(innerX), static_cast<float>(innerY), static_cast<float>(innerW), static_cast<float>(innerH),
	    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, 0.0f);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x4F));
	double decoX0 = static_cast<double>(static_cast<float>(x0 + w - static_cast<double>(FLOAT_80333108)));
	double decoY0 = y0 - DOUBLE_80333100;
	double decoX1 = DOUBLE_80333100 + decoX0;
	double decoY1 = DOUBLE_80333100 + static_cast<double>(static_cast<float>(y0 + h - static_cast<double>(FLOAT_8033310c)));
	for (int i = 0; i < 4; ++i) {
		double x = ((i & 1) == 0) ? (x0 - static_cast<double>(FLOAT_80333110)) : decoX1;
		double y = ((i & 2) == 0) ? decoY0 : decoY1;
		int flip = ((i & 2) == 0) ? 0 : 4;
		MenuPcs.DrawRect(
		    flip, static_cast<float>(x), static_cast<float>(y), FLOAT_80333108, FLOAT_8033310c,
		    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, 0.0f);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x50));
	double barX0 = static_cast<double>(static_cast<float>(x0 - static_cast<double>(FLOAT_80333110)));
	double barX1 = static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_80333110) + decoX0));
	double barY0 = static_cast<double>(static_cast<float>((DOUBLE_80333118 + y0) - DOUBLE_80333100));
	double barY1 = static_cast<double>(static_cast<float>(barY0 + static_cast<double>(static_cast<float>(h - DOUBLE_80333120))));
	for (int side = 0; side < 2; ++side) {
		double x = (side == 0) ? barX0 : barX1;
		double y = barY0;
		while (y < barY1) {
			double seg = static_cast<double>(static_cast<float>(barY1 - y));
			if (DOUBLE_80333118 <= seg) {
				seg = static_cast<double>(FLOAT_8033310c);
			}
			MenuPcs.DrawRect(
			    0, static_cast<float>(x), static_cast<float>(y), FLOAT_80333108, static_cast<float>(seg),
			    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, 0.0f);
			y = static_cast<double>(static_cast<float>(y + seg));
		}
	}

	if (param >= DOUBLE_803330e8) {
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3D));
		MenuPcs.DrawRect(
		    0, static_cast<float>(x0 - static_cast<double>(FLOAT_803330f4)),
		    static_cast<float>(y0 - static_cast<double>(FLOAT_80333108)),
		    FLOAT_80333128, FLOAT_8033312c, FLOAT_80333130, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, 0.0f);
		MenuPcs.DrawRect(
		    0, static_cast<float>(x0 + w - static_cast<double>(FLOAT_80333134)),
		    static_cast<float>(y0 + h - static_cast<double>(FLOAT_803330c0)),
		    FLOAT_80333130, FLOAT_80333138, FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, 0.0f);
	}
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
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

	if (s_Attach == 0) {
		s_AttachItemIdx = static_cast<signed char>(itemIndex);
		s_AttachItem = caravanWork->m_inventoryItems[itemIndex];
	} else {
		s_AttachItem = itemIndex;
	}
	s_AttachMode = flag;
}
