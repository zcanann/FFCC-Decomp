#include "ffcc/menu_letter.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"

#include <string.h>

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" int SingGetLetterAttachflg__8CMenuPcsFv(CMenuPcs*);
extern "C" void SingSetLetterAttachflg__8CMenuPcsFi(CMenuPcs*, int);
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
extern "C" void DrawSingleCrescent__8CMenuPcsFff(CMenuPcs*, float, float);
extern "C" void DrawSingleStat__8CMenuPcsFf(CMenuPcs*, float);
extern "C" void DrawSingleHelpWim__8CMenuPcsFf(CMenuPcs*, float);
extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" int GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void DrawShadowFont__8CMenuPcsFP5CFontPcffii(CMenuPcs*, CFont*, const char*, float, float, int, int);
extern "C" void SetTlut__5CFontFi(CFont*, int);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(double, double, double, double, double, double, double, double, CMenuPcs*, int);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(double, CMenuPcs*, int, int, int, float);
extern "C" void DrawCursor__8CMenuPcsFiif(double, CMenuPcs*, int, int);
extern "C" int m_tempVar__4CMes[];
extern u8 CFlat[];

extern float FLOAT_80333088;
extern float FLOAT_8033308c;
extern float FLOAT_803330a0;
extern float FLOAT_803330bc;
extern float FLOAT_803330b8;
extern float FLOAT_803330c0;
extern float FLOAT_803330f4;
extern float FLOAT_803330f8;
extern float FLOAT_80333148;
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
extern double DOUBLE_803330e8;

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

	memset(*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x850), 0, 0x1008);
	fVar1 = FLOAT_803330f8;
	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850) + 8;
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

	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(iVar4 + 0x24) = 0x5F;
	*reinterpret_cast<s16*>(iVar4 + 0xC) = 0x238;
	*reinterpret_cast<s16*>(iVar4 + 0xE) = 0x178;
	*reinterpret_cast<s16*>(iVar4 + 8) = static_cast<s16>((0x280 - *reinterpret_cast<s16*>(iVar4 + 0xC)) * DOUBLE_803330a8);
	*reinterpret_cast<s16*>(iVar4 + 0xA) = static_cast<s16>((0x1C0 - *reinterpret_cast<s16*>(iVar4 + 0xE)) * DOUBLE_803330a8);
	fVar1 = FLOAT_803330bc;
	*reinterpret_cast<float*>(iVar4 + 0x10) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x14) = fVar1;
	*reinterpret_cast<int*>(iVar4 + 0x2C) = 0;
	*reinterpret_cast<int*>(iVar4 + 0x30) = 10;

	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(iVar4 + 0x64) = 0x3E;
	*reinterpret_cast<s16*>(iVar4 + 0x4C) = 0xA8;
	*reinterpret_cast<s16*>(iVar4 + 0x4E) = 0x60;
	*reinterpret_cast<s16*>(iVar4 + 0x48) = 0x20;
	*reinterpret_cast<s16*>(iVar4 + 0x4A) = static_cast<s16>(0x1A0 - *reinterpret_cast<s16*>(iVar4 + 0x4E));
	*reinterpret_cast<float*>(iVar4 + 0x50) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x54) = fVar1;
	*reinterpret_cast<int*>(iVar4 + 0x6C) = 0;
	*reinterpret_cast<int*>(iVar4 + 0x70) = 10;

	**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) = 2;
	*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x22) = 0;
	*reinterpret_cast<char*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0xB) = 1;
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
	int state = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C);
	*reinterpret_cast<s16*>(state + 0x32) = *reinterpret_cast<s16*>(state + 0x30);
	DAT_8032eeea = 0;

	s16 phase = *reinterpret_cast<s16*>(state + 0x12);
	if (phase == 0) {
		s16 mode = *reinterpret_cast<s16*>(state + 0x30);
		if (mode == 0) {
			*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;
			int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
			s16* panel = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
			int frame = static_cast<int>(*reinterpret_cast<s16*>(state + 0x22));
			for (int i = 0; i < panelCount; ++i, panel += 0x20) {
				float f = FLOAT_803330bc;
				if (*reinterpret_cast<int*>(panel + 0x12) <= frame) {
					if (frame < *reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14)) {
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
				*reinterpret_cast<s16*>(state + 0x34) = DAT_8032eee8 - *reinterpret_cast<s16*>(state + 0x26);
				*reinterpret_cast<s16*>(state + 0x12) = 1;
			}
		} else if (mode == 1) {
			int letterOffs = DAT_8032eee8 * 0xC + 0x3EC;
			signed char letterFlags = *reinterpret_cast<signed char*>(Game.game.m_scriptFoodBase[0] + letterOffs);
			if (letterFlags >= 0) {
				*reinterpret_cast<unsigned char*>(Game.game.m_scriptFoodBase[0] + letterOffs) =
					(static_cast<unsigned char>(letterFlags) & 0x7F) | 0x80;
			}

			*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;
			int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
			s16* panel = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
			int frame = static_cast<int>(*reinterpret_cast<s16*>(state + 0x22));
			done = 0;
			for (int i = 0; i < panelCount; ++i, panel += 0x20) {
				float f = FLOAT_803330bc;
				if (*reinterpret_cast<int*>(panel + 0x12) <= frame) {
					if (frame < *reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14)) {
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
				if (SingGetLetterAttachflg__8CMenuPcsFv(this) < 0) {
					*reinterpret_cast<s16*>(state + 0x12) = 1;
				} else {
					if (DAT_8032eef4 < 1) {
						DAT_8032eeed = 2;
						*reinterpret_cast<s16*>(state + 0x30) = 3;
						*reinterpret_cast<s16*>(state + 0x28) = static_cast<s16>(DAT_8032eeec);
					} else {
						*reinterpret_cast<s16*>(state + 0x30) = 5;
					}
					*reinterpret_cast<s16*>(state + 0x12) = 0;
					*reinterpret_cast<char*>(state + 0xC) = 0;
					SingSetLetterAttachflg__8CMenuPcsFi(this, -1);
				}
			}
		} else if (mode == 2) {
			if (*reinterpret_cast<char*>(state + 0xC) == '\0') {
				char info[0x80];
				char left[0x10];
				char right[0x10];
				s16 winW;
				s16 winH;

				int letter = Game.game.m_scriptFoodBase[0] + DAT_8032eee8 * 0xC;
				if (((*reinterpret_cast<unsigned char*>(letter + 0x3EC) >> 3) & 1) == 0) {
					FlatDataView* flatData = reinterpret_cast<FlatDataView*>(&Game.game.m_cFlatDataArr[1]);
					int itemId = (*reinterpret_cast<u16*>(letter + 0x3EE) & 0x1FF) * 5 + 4;
					int value = reinterpret_cast<int*>(flatData->m_tabl[0].m_strings)[itemId];
					if (Game.game.m_gameWork.m_languageId == 2) {
						sprintf(info, "%s%d%s%s",
							GetMenuStr__8CMenuPcsFi(this, 0x23),
							value,
							GetMenuStr__8CMenuPcsFi(this, 0x24),
							GetMenuStr__8CMenuPcsFi(this, 0x22));
					} else {
						sprintf(info, "%s%d",
							GetMenuStr__8CMenuPcsFi(this, 0x22),
							value);
					}
				} else {
					int gil = static_cast<int>(*reinterpret_cast<u16*>(letter + 0x3EE) & 0x1FF) * 100;
					if (Game.game.m_gameWork.m_languageId == 2) {
						sprintf(info, "%d%s%s",
							gil,
							GetMenuStr__8CMenuPcsFi(this, 4),
							GetMenuStr__8CMenuPcsFi(this, 0x22));
					} else {
						sprintf(info, "%s%d%s",
							GetMenuStr__8CMenuPcsFi(this, 0x22),
							gil,
							GetMenuStr__8CMenuPcsFi(this, 4));
					}
				}

				strcpy(left, "");
				strcat(left, GetMenuStr__8CMenuPcsFi(this, 1), 0x10);
				strcpy(right, "");
				strcat(right, GetMenuStr__8CMenuPcsFi(this, 2), 0x10);
				SetSingDynamicWinMessInfo__8CMenuPcsFiPcPcPcPcPcPcPcPc(this, 3, info, left, right, 0, 0, 0, 0, 0);
				GetSingWinSize__8CMenuPcsFiPsPsi(this, 0, &winW, &winH, 1);
				SetMcWinInfo__8CMenuPcsFii(this, static_cast<int>(winW), static_cast<int>(winH));
				*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 0;
				*reinterpret_cast<s16*>(state + 0x28) = 0;
				*reinterpret_cast<char*>(state + 0xC) = 1;
			}
			if (*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) == 1) {
				*reinterpret_cast<s16*>(state + 0x12) = 1;
			}
		} else if (mode == 3) {
			if (LetterReplyWinOpen()) {
				*reinterpret_cast<s16*>(state + 0x12) = 1;
			}
		} else if (mode == 4) {
			if (*reinterpret_cast<char*>(state + 0xC) == '\0') {
				s16 winW;
				s16 winH;
				GetSingWinSize__8CMenuPcsFiPsPsi(this, 2, &winW, &winH, 0);
				SetMcWinInfo__8CMenuPcsFii(this, static_cast<int>(winW), static_cast<int>(winH));
				*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) = 0;
				*reinterpret_cast<s16*>(state + 0x28) = 0;
				*reinterpret_cast<unsigned char*>(state + 9) = 0xFF;
				*reinterpret_cast<char*>(state + 0xC) = 1;
			}
			if (*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) == 1) {
				*reinterpret_cast<s16*>(state + 0x12) = 1;
			}
		} else if (mode == 5) {
			if (LetterConfirmOpen()) {
				*reinterpret_cast<s16*>(state + 0x12) = 1;
			}
		}
	} else if (phase == 1) {
		ret = LetterCtrlCur();
	} else if (phase == 2) {
		s16 mode = *reinterpret_cast<s16*>(state + 0x30);
		if (mode == 0) {
			*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;
			int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
			s16* panel = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
			int frame = static_cast<int>(*reinterpret_cast<s16*>(state + 0x22));
			done = 0;
			for (int i = 0; i < panelCount; ++i, panel += 0x20) {
				float f = FLOAT_803330bc;
				if (*reinterpret_cast<int*>(panel + 0x12) <= frame) {
					if (frame < *reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14)) {
						*reinterpret_cast<int*>(panel + 0x10) = *reinterpret_cast<int*>(panel + 0x10) + 1;
						*reinterpret_cast<float*>(panel + 8) = 1.0f -
							static_cast<float>(*reinterpret_cast<int*>(panel + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(panel + 0x14));
						if ((*reinterpret_cast<unsigned int*>(panel + 0x16) & 2) == 0) {
							f = 1.0f - static_cast<float>(*reinterpret_cast<int*>(panel + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(panel + 0x14));
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
				LetterInit1__8CMenuPcsFv(this);
				*reinterpret_cast<s16*>(state + 0x30) = 1;
				*reinterpret_cast<s16*>(state + 0x12) = 0;
			}
		} else if (mode == 1) {
			signed char action = *reinterpret_cast<signed char*>(state + 8);
			if (action < 1) {
				*reinterpret_cast<s16*>(state + 0x22) = *reinterpret_cast<s16*>(state + 0x22) + 1;
				int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
				s16* panel = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
				int frame = static_cast<int>(*reinterpret_cast<s16*>(state + 0x22));
				done = 0;
				for (int i = 0; i < panelCount; ++i, panel += 0x20) {
					float f = FLOAT_803330bc;
					if (*reinterpret_cast<int*>(panel + 0x12) <= frame) {
						if (frame < *reinterpret_cast<int*>(panel + 0x12) + *reinterpret_cast<int*>(panel + 0x14)) {
							*reinterpret_cast<int*>(panel + 0x10) = *reinterpret_cast<int*>(panel + 0x10) + 1;
							*reinterpret_cast<float*>(panel + 8) = 1.0f -
								static_cast<float>(*reinterpret_cast<int*>(panel + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(panel + 0x14));
							if ((*reinterpret_cast<unsigned int*>(panel + 0x16) & 2) == 0) {
								f = 1.0f - static_cast<float>(*reinterpret_cast<int*>(panel + 0x10)) / static_cast<float>(*reinterpret_cast<int*>(panel + 0x14));
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
					if (DAT_8032eeed == 2) {
						memset(*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x850), 0, 0x1008);
						int p = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850) + 8;
						for (int i = 0; i < 8; ++i) {
							*reinterpret_cast<float*>(p + 0x14) = FLOAT_803330f8;
							*reinterpret_cast<float*>(p + 0x54) = FLOAT_803330f8;
							*reinterpret_cast<float*>(p + 0x94) = FLOAT_803330f8;
							*reinterpret_cast<float*>(p + 0xD4) = FLOAT_803330f8;
							*reinterpret_cast<float*>(p + 0x114) = FLOAT_803330f8;
							*reinterpret_cast<float*>(p + 0x154) = FLOAT_803330f8;
							*reinterpret_cast<float*>(p + 0x194) = FLOAT_803330f8;
							*reinterpret_cast<float*>(p + 0x1D4) = FLOAT_803330f8;
							p += 0x200;
						}
						int anim = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
						*reinterpret_cast<int*>(anim + 0x24) = 0;
						*reinterpret_cast<int*>(anim + 0x2C) = 0;
						*reinterpret_cast<int*>(anim + 0x30) = 10;
						*reinterpret_cast<int*>(anim + 0x64) = 0;
						*reinterpret_cast<int*>(anim + 0x6C) =
							~(((-static_cast<int>(static_cast<char>(*reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x872))) |
								static_cast<int>(static_cast<char>(*reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x872)))) >>
							   31)) &
							10;
						*reinterpret_cast<int*>(anim + 0x70) = 10;
						**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) = 2;
						*reinterpret_cast<s16*>(state + 0x22) = 0;
						*reinterpret_cast<char*>(state + 0xB) = 1;
					} else {
						ret = 1;
					}
					*reinterpret_cast<s16*>(state + 0x12) = 0;
					*reinterpret_cast<s16*>(state + 0x30) = 0;
				}
			} else {
				if (action == 1) {
					*reinterpret_cast<s16*>(state + 0x30) = 2;
				} else if (action == 2) {
					*reinterpret_cast<s16*>(state + 0x28) = 0;
					*reinterpret_cast<s16*>(state + 0x30) = 3;
				}
				*reinterpret_cast<s16*>(state + 0x12) = 0;
				*reinterpret_cast<unsigned char*>(state + 8) = 0;
				*reinterpret_cast<unsigned char*>(state + 0xC) = 0;
			}
			*reinterpret_cast<unsigned char*>(state + 8) = 0;
		} else if (mode == 2) {
			if (*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) == 3) {
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
		} else if (mode == 3) {
			if (*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) == 3) {
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
		} else if (mode == 4) {
			if (*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) == 3) {
				*reinterpret_cast<char*>(state + 0xC) = 0;
				if (*reinterpret_cast<signed char*>(state + 8) < 1) {
					*reinterpret_cast<s16*>(state + 0x30) = 3;
					*reinterpret_cast<s16*>(state + 0x12) = 0;
					*reinterpret_cast<char*>(state + 0xC) = 0;
					*reinterpret_cast<s16*>(state + 0x28) = static_cast<s16>(DAT_8032eeec);
				} else {
					if (DAT_8032eeed == 2) {
						*reinterpret_cast<s16*>(state + 0x30) = 5;
						*reinterpret_cast<s16*>(state + 0x12) = 0;
					} else {
						if (DAT_8032eeed == 0) {
							SingSetLetterAttachflg__8CMenuPcsFi(this, 1);
						} else {
							SingSetLetterAttachflg__8CMenuPcsFi(this, 5);
						}
						*reinterpret_cast<s16*>(state + 0x30) = 1;
						*reinterpret_cast<s16*>(state + 0x12) = 2;
						*reinterpret_cast<unsigned char*>(state + 8) = 0xFF;
						int anim = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
						*reinterpret_cast<int*>(anim + 0x2C) = 0;
						*reinterpret_cast<int*>(anim + 0x30) = 10;
						*reinterpret_cast<int*>(anim + 0x6C) = 0;
						*reinterpret_cast<int*>(anim + 0x70) = 10;
						int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
						s16* panel = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
						for (int i = 0; i < panelCount; ++i, panel += 0x20) {
							panel[0x10] = 0;
							panel[0x11] = 0;
							*reinterpret_cast<float*>(panel + 8) = FLOAT_803330f8;
						}
						*reinterpret_cast<s16*>(state + 0x22) = 0;
					}
					*reinterpret_cast<char*>(state + 0xC) = 0;
				}
			}
		} else if (mode == 5) {
			if (*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 0xA) == 3) {
				*reinterpret_cast<char*>(state + 0xC) = 0;
				if (*reinterpret_cast<signed char*>(state + 8) < 1) {
					*reinterpret_cast<s16*>(state + 0x30) = 3;
					*reinterpret_cast<s16*>(state + 0x12) = 0;
					*reinterpret_cast<char*>(state + 0xC) = 0;
					*reinterpret_cast<s16*>(state + 0x28) = static_cast<s16>(DAT_8032eeec);
				} else {
					DAT_8032eeed = 2;
					*reinterpret_cast<s16*>(state + 0x30) = 1;
					*reinterpret_cast<s16*>(state + 0x12) = 2;
					*reinterpret_cast<unsigned char*>(state + 8) = 0xFF;
					int anim = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
					*reinterpret_cast<int*>(anim + 0x2C) = 0;
					*reinterpret_cast<int*>(anim + 0x30) = 10;
					*reinterpret_cast<int*>(anim + 0x6C) = 0;
					*reinterpret_cast<int*>(anim + 0x70) = 10;
					int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
					s16* panel = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
					for (int i = 0; i < panelCount; ++i, panel += 0x20) {
						panel[0x10] = 0;
						panel[0x11] = 0;
						*reinterpret_cast<float*>(panel + 8) = FLOAT_803330f8;
					}
					*reinterpret_cast<s16*>(state + 0x22) = 0;
					*reinterpret_cast<char*>(state + 0xC) = 0;
				}
			}
		}
	}

	if (ret == 0) {
		return 0;
	}

	int anim = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(anim + 0x24) = 0;
	if (DAT_8032eeed == 2) {
		*reinterpret_cast<int*>(anim + 0x2C) = 10;
		*reinterpret_cast<int*>(anim + 0x30) = 10;
		*reinterpret_cast<int*>(anim + 0x64) = 0;
		*reinterpret_cast<int*>(anim + 0x6C) = 0;
		*reinterpret_cast<int*>(anim + 0x70) = 10;
	} else {
		*reinterpret_cast<int*>(anim + 0x2C) = 0;
		*reinterpret_cast<int*>(anim + 0x30) = 10;
		**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) = 1;
	}

	int panelCount = static_cast<int>(**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850));
	s16* panel = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	for (int i = 0; i < panelCount; ++i, panel += 0x20) {
		panel[0x10] = 0;
		panel[0x11] = 0;
		*reinterpret_cast<float*>(panel + 8) = FLOAT_803330f8;
	}
	*reinterpret_cast<s16*>(state + 0x22) = 0;
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
 * PAL Address: 80165554
 * PAL Size: 1528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::LetterListDraw()
{
	int menuDataBase = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);

	if ((DAT_8032eeea != 0) && (*reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x872) == '\0')) {
		float anim = static_cast<float>(DOUBLE_803330e8 - static_cast<double>(*reinterpret_cast<float*>(menuDataBase + 0x18)));
		DrawSingleCrescent__8CMenuPcsFff(this, FLOAT_803330f8, anim);
		DrawSingleStat__8CMenuPcsFf(this, anim);
		DrawSingleHelpWim__8CMenuPcsFf(this, anim);
	}

	if (**reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850) == 1) {
		return;
	}

	LetterLstBaseDraw(*reinterpret_cast<float*>(menuDataBase + 0x58));

	CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<char*>(this) + 0xF8);
	SetMargin__5CFontFf(FLOAT_803330f8, font);
	SetShadow__5CFontFi(font, 1);
	SetScale__5CFontFf(FLOAT_803330f8, font);
	DrawInit__5CFontFv(font);

	GXColor titleColor = {0xFF, 0xFF, 0xFF, static_cast<u8>(FLOAT_803330a0 * *reinterpret_cast<float*>(menuDataBase + 0x58))};
	SetColor__5CFontF8_GXColor(font, &titleColor);

	const char* menuTitle = GetMenuStr__8CMenuPcsFi(this, 0x1D);
	float titleX = static_cast<float>((static_cast<double>(FLOAT_80333158) - static_cast<double>(GetWidth__5CFontFPc(font, menuTitle))) *
	                                  DOUBLE_803330a8);
	DrawShadowFont__8CMenuPcsFP5CFontPcffii(this, font, menuTitle, titleX, FLOAT_8033315c, 0x18, 0x12);

	if (DOUBLE_803330e8 > static_cast<double>(*reinterpret_cast<float*>(menuDataBase + 0x58))) {
		return;
	}

	GXColor textColor = {0xFF, 0xFF, 0xFF, 0xFF};
	SetColor__5CFontF8_GXColor(font, &textColor);

	const unsigned int caravanWork = Game.game.m_scriptFoodBase[0];
	const int topRow = static_cast<int>(*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x34));
	FlatDataView* flatData = reinterpret_cast<FlatDataView*>(&Game.game.m_cFlatDataArr[1]);

	int y = 0x60;
	for (int row = 0; row < 9; ++row) {
		const int letterIndex = topRow + row;
		if (letterIndex >= *reinterpret_cast<int*>(caravanWork + 1000)) {
			break;
		}

		const int letterOffset = caravanWork + letterIndex * 0xC + 0x3EC;
		const unsigned int letterWord = *reinterpret_cast<unsigned int*>(letterOffset);

		int tlut = 9;
		if (static_cast<signed char>(*reinterpret_cast<unsigned char*>(letterOffset)) < 0) {
			tlut = ((*reinterpret_cast<unsigned char*>(letterOffset) >> 5) & 1) ? 8 : 0;
		}

		SetTlut__5CFontFi(font, tlut);

		const char* from = flatData->m_tabl[5].m_strings[(letterWord & 0x7FC) >> 2];
		SetPosX__5CFontFf(FLOAT_80333160, font);
		SetPosY__5CFontFf(static_cast<float>(static_cast<double>(y) - static_cast<double>(FLOAT_80333148)), font);
		Draw__5CFontFPc(font, from);

		const char* subject = flatData->m_tabl[2].m_strings[(letterWord >> 7) & 0x1FF];
		SetPosX__5CFontFf(FLOAT_80333164, font);
		SetPosY__5CFontFf(static_cast<float>(static_cast<double>(y) - static_cast<double>(FLOAT_80333148)), font);
		Draw__5CFontFPc(font, subject);

		y += 0x20;
	}

	DrawInit__8CMenuPcsFv(this);

	unsigned char pageMark = (*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x34) != 0) ? 1 : 0;
	if (topRow + 9 < *reinterpret_cast<int*>(caravanWork + 1000)) {
		pageMark = static_cast<unsigned char>(pageMark | 2);
	}

	if (pageMark != 0) {
		const int frame = static_cast<int>(System.m_frameCounter);
		const int cycle = ((frame / 0x14) + (frame >> 31));
		const int phase = (frame + (cycle - (cycle >> 31)) * -0x14) - 10;
		const unsigned int absPhase = static_cast<unsigned int>(phase < 0 ? -phase : phase);
		const double markScale = static_cast<double>(static_cast<float>(DOUBLE_80333098 * static_cast<double>(absPhase) + DOUBLE_80333090));

		SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

		const int alpha = static_cast<int>(FLOAT_803330a0 *
		                                   static_cast<float>(DOUBLE_803330b0 * static_cast<double>(absPhase) + DOUBLE_803330a8));
		GXColor markColor = {0xFF, 0xFF, 0xFF, static_cast<u8>(alpha)};
		GXSetChanMatColor(GX_COLOR0A0, markColor);
		SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x43);

		const double iconSize = static_cast<double>(FLOAT_803330b8);
		const double iconOffset = -static_cast<double>(static_cast<float>((iconSize * markScale - iconSize) * DOUBLE_803330a8));
		const double markX = static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_80333088) + iconOffset));
		const double markY = static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_8033308c) + iconOffset));

		if ((pageMark & 1) != 0) {
			DrawRect__8CMenuPcsFUlfffffffff(
			    markX, markY, iconSize, iconSize,
			    static_cast<double>(FLOAT_803330bc), static_cast<double>(FLOAT_803330bc),
			    markScale, markScale, this, 4);
		}
		if ((pageMark & 2) != 0) {
			DrawRect__8CMenuPcsFUlfffffffff(
			    markX, static_cast<double>(static_cast<float>(markY + static_cast<double>(FLOAT_803330c0))),
			    iconSize, iconSize,
			    static_cast<double>(FLOAT_803330bc), static_cast<double>(FLOAT_803330bc),
			    markScale, markScale, this, 0);
		}
	}

	unsigned int iconY = 0x5B;
	const int iconX = static_cast<int>(FLOAT_80333168);
	for (int row = 0; row < 9; ++row) {
		const int letterIndex = topRow + row;
		if (letterIndex >= *reinterpret_cast<int*>(caravanWork + 1000)) {
			break;
		}

		const int entry = caravanWork + letterIndex * 0xC;
		if ((*reinterpret_cast<u16*>(entry + 0x3EE) & 0x1FF) != 0) {
			const int icon = 0x26 + ((*reinterpret_cast<unsigned char*>(entry + 0x3EC) >> 6) & 1);
			DrawSingleIcon__8CMenuPcsFiiifif(
			    FLOAT_803330f8, this, icon, iconX,
			    static_cast<int>(iconY), FLOAT_803330f8);
		}
		iconY += 0x20;
	}

	const int cursorState = *reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82C) + 0x26);
	const int cursorX = static_cast<int>(FLOAT_803330f4 + static_cast<float>(System.m_frameCounter & 7));
	const int cursorY = cursorState * 0x20 + 0x60;
	DrawCursor__8CMenuPcsFiif(FLOAT_803330f8, this, cursorX, cursorY);
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
