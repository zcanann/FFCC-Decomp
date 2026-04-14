#include "ffcc/menu_equip.h"
#include "ffcc/joybus.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>
#include "ffcc/fontman.h"

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int EquipCtrlCur__8CMenuPcsFv(CMenuPcs*);
extern "C" bool EquipOpen0__8CMenuPcsFv(CMenuPcs*);
extern "C" bool EquipClose0__8CMenuPcsFv(CMenuPcs*);
extern "C" int ChkEquipPossible__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int GetEquipType__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int EquipChk__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void CmdInit1__8CMenuPcsFv(CMenuPcs*);
extern "C" void CmdInit2__8CMenuPcsFv(CMenuPcs*);
extern "C" int CanPlayerPutItem__12CCaravanWorkFv(void*);
extern "C" void ChgEquipPos__12CCaravanWorkFii(void*, int, int);
extern "C" void CalcStatus__12CCaravanWorkFv(void*);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(double, double, double, double, double, double, double, double, CMenuPcs*,
                                                 int);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(double, double, double, double, double, double, double, double,
                                                           CMenuPcs*, int, void*);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(double, CMenuPcs*, int, int, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" s16* GetLetterBuffer__6JoyBusFi(void*, int);
extern "C" double CalcListPos__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void DrawListPosMark__8CMenuPcsFfff(double, double, double, CMenuPcs*);
extern "C" void DrawCursor__8CMenuPcsFiif(double, CMenuPcs*, int, int);
extern "C" void DrawEquipMark__8CMenuPcsFiif(double, CMenuPcs*, int, int);
extern "C" void DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(CMenuPcs*, int);
extern "C" int GetAttrStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);

static const float FLOAT_80332eb8 = 0.0f;
static const float FLOAT_80332ee0 = 1.0f;
static const float FLOAT_80332ee4 = 255.0f;
static const float FLOAT_80332ee8 = 0.8999999761581421f;
static const float FLOAT_80332eec = 4.0f;
static const float FLOAT_80332ef0 = 12.0f;
static const float FLOAT_80332ef4 = 24.0f;
static const float FLOAT_80332ef8 = 320.0f;
static const float FLOAT_80332efc = 0.5f;
static const float FLOAT_80332f00 = 352.0f;
static const float FLOAT_80332f10 = 128.0f;
static const float FLOAT_80332f14 = 8.0f;
static const float FLOAT_80332f18 = 0.75f;
static const double DOUBLE_80332ec0 = 1.0;
static const double DOUBLE_80332ec8 = 216.0;
static const double DOUBLE_80332ed0 = 0.5;
static const double DOUBLE_80332ed8 = 4503601774854144.0;

namespace {
struct MenuEquipMembers {
	unsigned char pad_0000[0x108];
	void* m_equipFont;
	unsigned char pad_010C[0x720];
	s16* m_equipState;
	unsigned char pad_0830[0x20];
	s16* m_equipList;
};

STATIC_ASSERT(offsetof(MenuEquipMembers, m_equipFont) == 0x108);
STATIC_ASSERT(offsetof(MenuEquipMembers, m_equipState) == 0x82C);
STATIC_ASSERT(offsetof(MenuEquipMembers, m_equipList) == 0x850);

static inline MenuEquipMembers& GetMenuEquipMembers(CMenuPcs* menu)
{
	return *reinterpret_cast<MenuEquipMembers*>(menu);
}

static inline s16* GetEquipState(CMenuPcs* menu)
{
	return GetMenuEquipMembers(menu).m_equipState;
}

static inline s16* GetEquipList(CMenuPcs* menu)
{
	return GetMenuEquipMembers(menu).m_equipList;
}

static inline int GetEquipStateBase(CMenuPcs* menu)
{
	return reinterpret_cast<int>(GetEquipState(menu));
}

static inline int GetEquipListBase(CMenuPcs* menu)
{
	return reinterpret_cast<int>(GetEquipList(menu));
}

static inline void* GetEquipFont(CMenuPcs* menu)
{
	return GetMenuEquipMembers(menu).m_equipFont;
}
} // namespace

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipInit0()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8015d4bc
 * PAL Size: 732b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::EquipInit1()
{
	short sVar1;
	float fVar2;
	float fVar3;
	float fVar4;
	float fVar5;
	unsigned int uVar6;
	short sVar7;
	int iVar8;
	int iVar9;
	short* psVar10;
	int iVar11;
	short* puVar12;
	short* psVar13;
	int iVar14;
	unsigned int uVar15;
	int* workPtr;

	workPtr = (int*)GetEquipListBase(this);
	fVar5 = FLOAT_80332f14;
	fVar4 = FLOAT_80332f10;
	fVar3 = FLOAT_80332ee0;
	fVar2 = FLOAT_80332eb8;
	sVar7 = 0;
	iVar8 = (int)**(short**)workPtr;
	psVar10 = *(short**)workPtr + iVar8 * 0x20 + 4;
	psVar10[0xe] = 0;
	psVar10[0xf] = 0x2e;
	*psVar10 = 0xb8;
	psVar10[1] = 0x28;
	iVar9 = iVar8 + 4;
	psVar10[2] = 0x78;
	iVar11 = iVar9 * 0x40;
	psVar10[3] = 0x108;
	*(float*)(psVar10 + 4) = fVar4;
	fVar4 = FLOAT_80332f18;
	*(float*)(psVar10 + 6) = fVar5;
	*(float*)(psVar10 + 10) = fVar3;
	psVar10[0x12] = 0;
	psVar10[0x13] = 5;
	psVar10[0x14] = 0;
	psVar10[0x15] = 5;

	puVar12 = (short*)(*workPtr + (iVar8 + 1) * 0x40 + 8);
	*(int*)(puVar12 + 0xe) = 0x2f;
	*puVar12 = 0xa0;
	puVar12[1] = 0xe;
	puVar12[2] = 0x30;
	puVar12[3] = 0x30;
	*(float*)(puVar12 + 4) = fVar2;
	*(float*)(puVar12 + 6) = fVar2;
	*(float*)(puVar12 + 10) = fVar3;
	*(int*)(puVar12 + 0x12) = 0;
	*(int*)(puVar12 + 0x14) = 5;

	puVar12 = (short*)(*workPtr + (iVar8 + 2) * 0x40 + 8);
	*(int*)(puVar12 + 0xe) = 0x2f;
	puVar12[2] = 0x30;
	puVar12[3] = 0x30;
	*puVar12 = 0xa5;
	puVar12[1] = 0x150 - puVar12[3];
	*(float*)(puVar12 + 4) = fVar2;
	*(float*)(puVar12 + 6) = fVar2;
	*(float*)(puVar12 + 10) = fVar4;
	*(int*)(puVar12 + 0x12) = 0;
	*(int*)(puVar12 + 0x14) = 5;

	puVar12 = (short*)(*workPtr + (iVar8 + 3) * 0x40 + 8);
	*(int*)(puVar12 + 0x16) = 2;
	*(int*)(puVar12 + 0xe) = 0x2e;
	*puVar12 = 0xa0;
	puVar12[1] = 8;
	puVar12[2] = 0x48;
	puVar12[3] = 0x140;
	*(float*)(puVar12 + 4) = fVar2;
	*(float*)(puVar12 + 6) = fVar2;
	*(int*)(puVar12 + 0x12) = 0;
	*(int*)(puVar12 + 0x14) = 5;

	psVar10 = *(short**)workPtr + **(short**)workPtr * 0x20 + 4;
	iVar8 = 4;
	do {
		psVar13 = (short*)(*workPtr + iVar11 + 8);
		psVar13[0x16] = 0;
		psVar13[0x17] = 2;
		psVar13[0xe] = 0;
		psVar13[0xf] = 0x37;
		iVar9 = iVar9 + 2;
		*psVar13 = *psVar10 + 0x24;
		sVar1 = sVar7 + 0x20;
		psVar13[1] = psVar10[1] + sVar7;
		psVar13[2] = 200;
		psVar13[3] = 0x28;
		*(float*)(psVar13 + 4) = fVar2;
		*(float*)(psVar13 + 6) = fVar2;
		psVar13[0x12] = 0;
		psVar13[0x13] = 7;
		psVar13[0x14] = 0;
		psVar13[0x15] = 5;

		iVar14 = iVar11 + 0x48;
		iVar11 = iVar11 + 0x80;
		psVar13 = (short*)(*workPtr + iVar14);
		psVar13[0x16] = 0;
		psVar13[0x17] = 2;
		psVar13[0xe] = 0;
		psVar13[0xf] = 0x37;
		*psVar13 = *psVar10 + 0x24;
		sVar7 = sVar7 + 0x40;
		psVar13[1] = psVar10[1] + sVar1;
		psVar13[2] = 200;
		psVar13[3] = 0x28;
		*(float*)(psVar13 + 4) = fVar2;
		*(float*)(psVar13 + 6) = fVar2;
		psVar13[0x12] = 0;
		psVar13[0x13] = 7;
		psVar13[0x14] = 0;
		fVar3 = FLOAT_80332eb8;
		psVar13[0x15] = 5;
		iVar8 = iVar8 - 1;
	} while (iVar8 != 0);

	*(short*)(*workPtr + 2) = (short)iVar9;
	psVar10 = *(short**)workPtr;
	uVar6 = (unsigned int)((int)psVar10[1] - (int)*psVar10);
	psVar10 = psVar10 + *psVar10 * 0x20 + 4;
	if (0 < (int)uVar6) {
		uVar15 = uVar6 >> 3;
		if (uVar15 != 0) {
			do {
				psVar10[0x10] = 0;
				psVar10[0x11] = 0;
				*(float*)(psVar10 + 8) = fVar3;
				psVar10[0x30] = 0;
				psVar10[0x31] = 0;
				*(float*)(psVar10 + 0x28) = fVar3;
				psVar10[0x50] = 0;
				psVar10[0x51] = 0;
				*(float*)(psVar10 + 0x48) = fVar3;
				psVar10[0x70] = 0;
				psVar10[0x71] = 0;
				*(float*)(psVar10 + 0x68) = fVar3;
				psVar10[0x90] = 0;
				psVar10[0x91] = 0;
				*(float*)(psVar10 + 0x88) = fVar3;
				psVar10[0xb0] = 0;
				psVar10[0xb1] = 0;
				*(float*)(psVar10 + 0xa8) = fVar3;
				psVar10[0xd0] = 0;
				psVar10[0xd1] = 0;
				*(float*)(psVar10 + 200) = fVar3;
				psVar10[0xf0] = 0;
				psVar10[0xf1] = 0;
				*(float*)(psVar10 + 0xe8) = fVar3;
				psVar10 = psVar10 + 0x100;
				uVar15 = uVar15 - 1;
			} while (uVar15 != 0);
			uVar6 = uVar6 & 7;
			if (uVar6 == 0) {
				return;
			}
		}
		do {
			psVar10[0x10] = 0;
			psVar10[0x11] = 0;
			*(float*)(psVar10 + 8) = fVar3;
			psVar10 = psVar10 + 0x20;
			uVar6 = uVar6 - 1;
		} while (uVar6 != 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015d108
 * PAL Size: 948b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::EquipOpen()
{
	float fVar1;
	double dVar2;
	double dVar3;
	double dVar4;
	float fVar5;
	int iVar6;
	s16* psVar7;
	u32 uVar8;
	s16* puVar9;
	s16 sVar10;
	int iVar11;
	u32 uVar12;
	double dVar20;

	if (*(char*)(GetEquipStateBase(this) + 0xb) == '\0') {
		memset((void*)GetEquipList(this), 0, 0x1008);
		fVar5 = FLOAT_80332ee0;
		iVar6 = GetEquipListBase(this) + 8;
		iVar11 = 8;
		do {
			*(float*)(iVar6 + 0x14) = fVar5;
			*(float*)(iVar6 + 0x54) = fVar5;
			*(float*)(iVar6 + 0x94) = fVar5;
			*(float*)(iVar6 + 0xd4) = fVar5;
			*(float*)(iVar6 + 0x114) = fVar5;
			*(float*)(iVar6 + 0x154) = fVar5;
			*(float*)(iVar6 + 0x194) = fVar5;
			*(float*)(iVar6 + 0x1d4) = fVar5;
			dVar4 = DOUBLE_80332ed8;
			dVar3 = DOUBLE_80332ed0;
			dVar2 = DOUBLE_80332ec8;
			fVar1 = FLOAT_80332eb8;
			iVar6 += 0x200;
			iVar11--;
		} while (iVar11 != 0);

		iVar6 = 0;
		puVar9 = (s16*)(GetEquipListBase(this) + 8);
		iVar11 = 2;
		do {
			*(int*)(puVar9 + 0xe) = 0x34;
			puVar9[2] = 200;
			puVar9[3] = 0x28;
			*puVar9 =
			    (s16)(int)-(((double)(((u64)((u32)(u16)puVar9[2] ^ 0x80000000U)) | 0x4330000000000000ULL) - dVar4) * dVar3 - dVar2);
			puVar9[1] = (s16)iVar6 * (puVar9[3] - 8) + 0x60;
			*(float*)(puVar9 + 4) = fVar1;
			*(float*)(puVar9 + 6) = fVar1;
			*(int*)(puVar9 + 0x12) = iVar6;
			*(int*)(puVar9 + 0x14) = 3;

			*(int*)(puVar9 + 0x2e) = 0x34;
			puVar9[0x22] = 200;
			puVar9[0x23] = 0x28;
			puVar9[0x20] =
			    (s16)(int)-(((double)(((u64)((u32)(u16)puVar9[0x22] ^ 0x80000000U)) | 0x4330000000000000ULL) - dVar4) * dVar3 - dVar2);
			puVar9[0x21] = (s16)(iVar6 + 1) * (puVar9[0x23] - 8) + 0x60;
			*(float*)(puVar9 + 0x24) = fVar1;
			*(float*)(puVar9 + 0x26) = fVar1;
			*(int*)(puVar9 + 0x32) = iVar6 + 1;
			iVar6 += 2;
			*(int*)(puVar9 + 0x34) = 3;
			puVar9 += 0x40;
			iVar11--;
		} while (iVar11 != 0);

		*GetEquipList(this) = 4;
		EquipInit1();
		puVar9 = GetLetterBuffer__6JoyBusFi(&Joybus, 0);
		sVar10 = 0;
		for (iVar6 = 0; iVar6 < 0x40; iVar6++) {
			iVar11 = GetItemType__8CMenuPcsFii(this, iVar6, 0);
			if (iVar11 == 1) {
				puVar9++;
				*puVar9 = (s16)iVar6;
				sVar10++;
			}
		}

		psVar7 = GetLetterBuffer__6JoyBusFi(&Joybus, 0);
		*psVar7 = sVar10 + 1;
		*(s16*)(GetEquipStateBase(this) + 0x26) = 0;
		*(u8*)(GetEquipStateBase(this) + 0xb) = 1;
	}

	iVar6 = 0;
	*(s16*)(GetEquipStateBase(this) + 0x22) = *(s16*)(GetEquipStateBase(this) + 0x22) + 1;
	uVar8 = (u32)*GetEquipList(this);
	psVar7 = GetEquipList(this) + 4;
	iVar11 = (int)*(s16*)(GetEquipStateBase(this) + 0x22);
	uVar12 = uVar8;
	if (0 < (int)uVar8) {
		do {
			dVar2 = DOUBLE_80332ed8;
			if (*(int*)(psVar7 + 0x12) <= iVar11) {
				if (iVar11 < *(int*)(psVar7 + 0x12) + *(int*)(psVar7 + 0x14)) {
					*(int*)(psVar7 + 0x10) = *(int*)(psVar7 + 0x10) + 1;
					dVar20 = (double)(((u64)((u32)*(u32*)(psVar7 + 0x14) ^ 0x80000000U)) | 0x4330000000000000ULL);
					*(float*)(psVar7 + 8) =
					    (float)((DOUBLE_80332ec0 / (dVar20 - dVar2)) *
					            ((double)(((u64)((u32)*(u32*)(psVar7 + 0x10) ^ 0x80000000U)) | 0x4330000000000000ULL) - dVar2));
				} else {
					iVar6++;
					*(float*)(psVar7 + 8) = FLOAT_80332ee0;
				}
			}
			psVar7 += 0x20;
			uVar12--;
		} while (uVar12 != 0);
	}

	fVar5 = FLOAT_80332ee0;
	if (*GetEquipList(this) == iVar6) {
		psVar7 = GetEquipList(this) + 4;
		if (0 < (int)uVar8) {
			uVar12 = uVar8 >> 3;
			if (uVar12 != 0) {
				do {
					psVar7[0x12] = 0;
					psVar7[0x13] = 0;
					psVar7[0x14] = 0;
					psVar7[0x15] = 1;
					*(float*)(psVar7 + 8) = fVar5;
					psVar7[0x32] = 0;
					psVar7[0x33] = 0;
					psVar7[0x34] = 0;
					psVar7[0x35] = 1;
					*(float*)(psVar7 + 0x28) = fVar5;
					psVar7[0x52] = 0;
					psVar7[0x53] = 0;
					psVar7[0x54] = 0;
					psVar7[0x55] = 1;
					*(float*)(psVar7 + 0x48) = fVar5;
					psVar7[0x72] = 0;
					psVar7[0x73] = 0;
					psVar7[0x74] = 0;
					psVar7[0x75] = 1;
					*(float*)(psVar7 + 0x68) = fVar5;
					psVar7[0x92] = 0;
					psVar7[0x93] = 0;
					psVar7[0x94] = 0;
					psVar7[0x95] = 1;
					*(float*)(psVar7 + 0x88) = fVar5;
					psVar7[0xb2] = 0;
					psVar7[0xb3] = 0;
					psVar7[0xb4] = 0;
					psVar7[0xb5] = 1;
					*(float*)(psVar7 + 0xa8) = fVar5;
					psVar7[0xd2] = 0;
					psVar7[0xd3] = 0;
					psVar7[0xd4] = 0;
					psVar7[0xd5] = 1;
					*(float*)(psVar7 + 200) = fVar5;
					psVar7[0xf2] = 0;
					psVar7[0xf3] = 0;
					psVar7[0xf4] = 0;
					psVar7[0xf5] = 1;
					*(float*)(psVar7 + 0xe8) = fVar5;
					psVar7 += 0x100;
					uVar12--;
				} while (uVar12 != 0);
				uVar8 &= 7;
				if (uVar8 == 0) {
					return 1;
				}
			}

			do {
				psVar7[0x12] = 0;
				psVar7[0x13] = 0;
				psVar7[0x14] = 0;
				psVar7[0x15] = 1;
				*(float*)(psVar7 + 8) = fVar5;
				psVar7 += 0x20;
				uVar8--;
			} while (uVar8 != 0);
		}
		return 1;
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8015ceb4
 * PAL Size: 596b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::EquipCtrl()
{
	int state = 0;
	int menuState;
	int item;
	int index;
	int offset;
	u32 equipCount;
	s16 mode;

	*reinterpret_cast<s16*>(GetEquipStateBase(this) + 0x32) = *reinterpret_cast<s16*>(GetEquipStateBase(this) + 0x30);
	menuState = GetEquipStateBase(this);
	mode = *reinterpret_cast<s16*>(menuState + 0x30);
	if ((mode == 0) || ((mode != 0) && (*reinterpret_cast<s16*>(menuState + 0x12) == 1))) {
		state = EquipCtrlCur();
	} else if ((mode == 1) && (*reinterpret_cast<s16*>(menuState + 0x12) == 0)) {
		state = EquipOpen0();
		if (state != 0) {
			state = 0;
			*reinterpret_cast<s16*>(menuState + 0x12) = *reinterpret_cast<s16*>(menuState + 0x12) + 1;
		}
	} else if (((mode == 1) && (*reinterpret_cast<s16*>(menuState + 0x12) == 2)) && EquipClose0()) {
		*reinterpret_cast<s16*>(menuState + 0x12) = 0;
		*reinterpret_cast<s16*>(GetEquipStateBase(this) + 0x30) = 0;
		*reinterpret_cast<s16*>(GetEquipStateBase(this) + 0x22) = 0;
		CmdInit1__8CMenuPcsFv(this);
		state = 0;
	}
	if (state != 0) {
		item = GetEquipListBase(this) + 8;
		for (index = 0; index < *GetEquipList(this); index++) {
			*reinterpret_cast<float*>(item + 0x10) = FLOAT_80332ee0;
			*reinterpret_cast<float*>(item + 0x14) = FLOAT_80332ee0;
			item += 0x40;
		}
		equipCount = (u32)*(s16*)(Game.m_scriptFoodBase[0] + 0xbaa);
		index = 0;
		offset = (equipCount - 1) * 0x40;
		if (-1 < (int)(equipCount - 1)) {
			do {
				item = GetEquipListBase(this) + offset + 8;
				*reinterpret_cast<int*>(item + 0x24) = index;
				index = index + 1;
				*reinterpret_cast<int*>(item + 0x28) = 3;
				offset = offset + -0x40;
			} while (index < (int)equipCount);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015cd08
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::EquipClose()
{
	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
	s16* menuData = *reinterpret_cast<s16**>(reinterpret_cast<char*>(this) + 0x850);
	int doneCount = 0;

	*reinterpret_cast<s16*>(menuState + 0x22) = *reinterpret_cast<s16*>(menuState + 0x22) + 1;
	int timer = static_cast<int>(*reinterpret_cast<s16*>(menuState + 0x22));
	int itemCount = static_cast<int>(*menuData);
	s16* item = menuData + 4;

	for (int i = 0; i < itemCount; i++) {
		if (*reinterpret_cast<int*>(item + 0x12) <= timer) {
			if (timer < (*reinterpret_cast<int*>(item + 0x12) + *reinterpret_cast<int*>(item + 0x14))) {
				*reinterpret_cast<int*>(item + 0x10) = *reinterpret_cast<int*>(item + 0x10) + 1;
				float ratio = FLOAT_80332ee0 -
				              (static_cast<float>(*reinterpret_cast<int*>(item + 0x10)) /
				               static_cast<float>(*reinterpret_cast<int*>(item + 0x14)));
				*reinterpret_cast<float*>(item + 8) = ratio;
				if (*reinterpret_cast<float*>(item + 8) < FLOAT_80332eb8) {
					*reinterpret_cast<float*>(item + 8) = FLOAT_80332eb8;
				}
			} else {
				doneCount++;
				*reinterpret_cast<float*>(item + 8) = FLOAT_80332eb8;
			}
		}
		item += 0x20;
	}

	if (itemCount == doneCount) {
		item = menuData + 4;
		for (int i = 0; i < itemCount; i++) {
			*reinterpret_cast<int*>(item + 0x12) = 0;
			*reinterpret_cast<int*>(item + 0x13) = 0;
			*reinterpret_cast<int*>(item + 0x14) = 0;
			*reinterpret_cast<int*>(item + 0x15) = 1;
			*reinterpret_cast<float*>(item + 8) = FLOAT_80332eb8;
			item += 0x20;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015bc50
 * PAL Size: 4280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::EquipDraw()
{
	int menuState = GetEquipStateBase(this);
	int mode = (int)*(s16*)(menuState + 0x30);
	int listState = (int)*(s16*)(menuState + 0x10);
	u32 caravanWork = Game.m_scriptFoodBase[0];
	s16* menuData = GetEquipList(this);
	s16* item = menuData + 4;
	int helpItem = -1;

	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	for (int i = 0; i < menuData[0]; i++) {
		if (*(int*)(item + 0xe) >= 0) {
			double x = (double)(float)((double)item[0] - DOUBLE_80332ed8);
			double y = (double)*(float*)(item + 4);
			double w = (double)(float)((double)item[2] - DOUBLE_80332ed8);
			double h = (double)(float)((double)item[3] - DOUBLE_80332ed8);
			double sx = (double)*(float*)(item + 6);
			int tex = *(int*)(item + 0xe);

			if ((listState == 1) && (i == (int)*(s16*)(menuState + 0x26))) {
				sx = sx + h;
			}

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
			GXColor color = {0xff, 0xff, 0xff, (u8)(FLOAT_80332ee4 * *(float*)(item + 8))};
			GXSetChanMatColor((GXChannelID)4, color);
			DrawRect__8CMenuPcsFUlfffffffff(x, (double)(float)((double)item[1] - DOUBLE_80332ed8), w, h, y, sx,
			                                (double)*(float*)(item + 10), (double)*(float*)(item + 10), this, 0);
		}
		item += 0x20;
	}

	item = menuData + 4;
	for (int i = 0; i < 4; i++) {
		if (*(s16*)(caravanWork + 0xac + i * 2) >= 0) {
			int iconY = item[1] + 6;
			int iconX = item[0] + item[2] - 0x10;
			int itemIdx = *(s16*)(caravanWork + *(s16*)(caravanWork + 0xac + i * 2) * 2 + 0xb6);
			DrawSingleIcon__8CMenuPcsFiiifif((double)*(float*)(item + 8), this, itemIdx, iconX, iconY, 0.0f);
		}
		item += 0x20;
	}

	CFont* font = (CFont*)GetEquipFont(this);
	font->SetMargin(FLOAT_80332ee0);
	font->SetShadow(0);
	font->SetScale(FLOAT_80332ee8);
	font->DrawInit();

	item = menuData + 4;
	for (int i = 0; i < 4; i++) {
		if (*(s16*)(caravanWork + 0xac + i * 2) >= 0) {
			u8 alpha = (u8)(FLOAT_80332ee4 * *(float*)(item + 8));
			u32 color = (u32)alpha | 0xFFFFFF00;
			font->SetColor(*reinterpret_cast<_GXColor*>(&color));
			int itemIdx = *(s16*)(caravanWork + *(s16*)(caravanWork + 0xac + i * 2) * 2 + 0xb6);
			const char* str = (const char*)GetAttrStr__8CMenuPcsFi(this, itemIdx);
			if ((mode == 0) && (i == (int)*(s16*)(menuState + 0x26))) {
				helpItem = itemIdx;
			}
			double textX = (double)item[0] + ((double)item[2] - (double)font->GetWidth(str)) * DOUBLE_80332ed0;
			double textY = (double)item[1] + 11.0;
			font->SetPosX((float)textX);
			font->SetPosY((float)(textY - (double)FLOAT_80332eec));
			font->Draw(str);
		}
		item += 0x20;
	}
	DrawInit__8CMenuPcsFv(this);

	if ((mode == 1) && (*(s16*)(menuState + 0x12) == 1)) {
		s16* listStart = menuData + menuData[0] * 0x20 + 4;
		s16* letter = GetLetterBuffer__6JoyBusFi(&Joybus, 0);
		double pos = CalcListPos__8CMenuPcsFiii(this, (int)*(s16*)(menuState + 0x34), (int)letter[0], 0);
		if (pos > (double)FLOAT_80332eb8) {
			DrawListPosMark__8CMenuPcsFfff((double)listStart[0], (double)listStart[1], pos, this);
		}
	}

	if (((mode == 0) && (*(s16*)(menuState + 0x10) == 1)) || ((mode != 0) && (*(s16*)(menuState + 0x12) == 1))) {
		s16* cursorItem;
		if (mode == 0) {
			cursorItem = (s16*)((char*)menuData + *(s16*)(menuState + 0x26) * 0x40 + 8);
		} else {
			s16* listBase = menuData + menuData[0] * 0x20 + 4;
			cursorItem = listBase + *(s16*)(menuState + 0x28) * 0x20;
		}
		int cursorX = (int)((double)cursorItem[1] + ((double)(cursorItem[3] - 0x20) * DOUBLE_80332ed0));
		int frame = (int)System.m_frameCounter;
		int cursorY = (cursorItem[0] - 0x14) + (frame & 7);
		DrawCursor__8CMenuPcsFiif((double)FLOAT_80332ee0, this, cursorY, cursorX);
	}

	if ((mode == 1) && (*(s16*)(menuState + 0x12) == 1)) {
		s16* letter = GetLetterBuffer__6JoyBusFi(&Joybus, 0);
		int idx = *(s16*)(menuState + 0x28) + *(s16*)(menuState + 0x34);
		if ((idx > 0) && (idx < letter[0]) && (letter[idx] >= 0)) {
			if (EquipChk__8CMenuPcsFi(this, (int)letter[idx]) != 0) {
				s16* listBase = menuData + menuData[0] * 0x20 + 4;
				s16* markItem = listBase + *(s16*)(menuState + 0x28) * 0x20;
				int markX = (int)((double)markItem[0] - (double)FLOAT_80332ef0);
				int markY = (int)(((double)markItem[3] - (double)FLOAT_80332ef4) * DOUBLE_80332ed0 + (double)markItem[1]);
				DrawEquipMark__8CMenuPcsFiif((double)*(float*)(markItem + 8), this, markX, markY);
			}
		}
	}

	int listIndex = (int)*(s16*)(menuState + mode * 2 + 0x26) + (int)*(s16*)(menuState + 0x34);
	if ((mode == 1) && (listIndex < 1)) {
		helpItem = -1;
	}
	if (((mode == 0) && (*(s16*)(menuState + 0x2c) == 0)) && (helpItem < 0)) {
		helpItem = 0x267;
	}
	DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(this, helpItem);
	if ((mode == 1) && (listIndex < 1)) {
		DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(this, 0x265);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015b618
 * PAL Size: 1592b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::EquipCtrlCur()
{
	bool blocked = false;
	u16 press;
	u16 hold;
	u32 caravanWork = Game.m_scriptFoodBase[0];

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
		hold = *reinterpret_cast<u16*>(reinterpret_cast<char*>(&Pad) + 0x20);
	}

	if (hold == 0) {
		return 0;
	}

	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
	int mode = static_cast<int>(*reinterpret_cast<s16*>(menuState + 0x30));

	if (mode == 0) {
		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (*reinterpret_cast<s16*>(menuState + 0x26) < 3) {
					*reinterpret_cast<s16*>(menuState + 0x26) = *reinterpret_cast<s16*>(menuState + 0x26) + 1;
				} else {
					*reinterpret_cast<s16*>(menuState + 0x26) = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
		} else {
			if (*reinterpret_cast<s16*>(menuState + 0x26) == 0) {
				*reinterpret_cast<s16*>(menuState + 0x26) = 3;
			} else {
				*reinterpret_cast<s16*>(menuState + 0x26) = *reinterpret_cast<s16*>(menuState + 0x26) - 1;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0xc) == 0) {
			if ((press & 0x20) != 0) {
				*reinterpret_cast<s16*>(menuState + 0x1e) = 1;
				Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
				return 1;
			}

			if ((press & 0x40) != 0) {
				*reinterpret_cast<s16*>(menuState + 0x1e) = -1;
				Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
				return 1;
			}

			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					*reinterpret_cast<u8*>(menuState + 0xd) = 1;
					Sound.PlaySe(3, 0x40, 0x7f, 0);
					return 1;
				}
			} else if (CanPlayerPutItem__12CCaravanWorkFv(reinterpret_cast<void*>(caravanWork)) == 0) {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			} else {
				*reinterpret_cast<s16*>(menuState + 0x30) = 1;
				*reinterpret_cast<s16*>(menuState + 0x12) = 0;
				*reinterpret_cast<s16*>(menuState + 0x22) = 0;
				Sound.PlaySe(2, 0x40, 0x7f, 0);
			}
		}
	} else {
		s16* letterBuffer = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				int base = menuState + mode * 2;
				s16 selected = *reinterpret_cast<s16*>(base + 0x26);

				if (selected < 7) {
					*reinterpret_cast<s16*>(base + 0x26) = selected + 1;
				} else if (static_cast<int>(*reinterpret_cast<s16*>(menuState + 0x34)) + static_cast<int>(selected) <
				           letterBuffer[0] - 1) {
					*reinterpret_cast<s16*>(menuState + 0x34) = *reinterpret_cast<s16*>(menuState + 0x34) + 1;
					Sound.PlaySe(1, 0x40, 0x7f, 0);
				} else {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				}

				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
		} else {
			int base = menuState + mode * 2;
			s16 selected = *reinterpret_cast<s16*>(base + 0x26);

			if (selected == 0) {
				if (*reinterpret_cast<s16*>(menuState + 0x34) == 0) {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				} else {
					*reinterpret_cast<s16*>(menuState + 0x34) = *reinterpret_cast<s16*>(menuState + 0x34) - 1;
					Sound.PlaySe(1, 0x40, 0x7f, 0);
				}
			} else {
				*reinterpret_cast<s16*>(base + 0x26) = selected - 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
		}

		if ((hold & 0xc) == 0) {
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					*reinterpret_cast<s16*>(menuState + 0x12) = *reinterpret_cast<s16*>(menuState + 0x12) + 1;
					*reinterpret_cast<s16*>(menuState + 0x22) = 0;
					CmdInit2__8CMenuPcsFv(this);
					Sound.PlaySe(3, 0x40, 0x7f, 0);
				}
			} else {
				int index = static_cast<int>(*reinterpret_cast<s16*>(menuState + 0x34)) +
				            static_cast<int>(*reinterpret_cast<s16*>(menuState + mode * 2 + 0x26));
				s16* entries = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
				int equipIndex = static_cast<int>(*reinterpret_cast<s16*>(menuState + 0x26));
				bool valid = false;

				if ((index >= 0) && (index < entries[0])) {
					if (index == 0) {
						if (equipIndex >= 3) {
							valid = *reinterpret_cast<s16*>(caravanWork + equipIndex * 2 + 0xac) >= 0;
						}
					} else {
						int item = static_cast<int>(*reinterpret_cast<s16*>(caravanWork + entries[index] * 2 + 0xb6));
						valid = ChkEquipPossible__8CMenuPcsFi(this, item) != 0;
						if (valid && (GetEquipType__8CMenuPcsFi(this, item) != equipIndex)) {
							valid = false;
						}
					}
				}

				if (!valid || ((index != 0) && (EquipChk__8CMenuPcsFi(this, entries[index]) != 0))) {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				} else {
					int item = (index == 0) ? -1 : static_cast<int>(entries[index]);
					ChgEquipPos__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), equipIndex, item);
					CalcStatus__12CCaravanWorkFv(reinterpret_cast<void*>(caravanWork));
					*reinterpret_cast<s16*>(menuState + 0x12) = *reinterpret_cast<s16*>(menuState + 0x12) + 1;
					*reinterpret_cast<s16*>(menuState + 0x22) = 0;
					CmdInit2__8CMenuPcsFv(this);
					Sound.PlaySe(2, 0x40, 0x7f, 0);
				}
			}
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8015b468
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::EquipOpen0()
{
	float fVar1;
	double dVar2;
	int timer;
	int selectedOffset;
	s16* item;
	int doneCount;
	int itemCount;
	int remaining;

	*(s16*)(GetEquipStateBase(this) + 0x22) = *(s16*)(GetEquipStateBase(this) + 0x22) + 1;
	timer = (int)*(s16*)(GetEquipStateBase(this) + 0x22);
	selectedOffset = *(s16*)(GetEquipStateBase(this) + 0x26) * 0x40 + 8;

	if (timer < 5) {
		*(s16*)(GetEquipListBase(this) + selectedOffset) = *(s16*)(GetEquipListBase(this) + selectedOffset) - 0x13;
	}

	item = GetEquipList(this);
	doneCount = 0;
	itemCount = (int)item[1] - (int)*item;
	item = item + *item * 0x20 + 4;
	remaining = itemCount;

	if (0 < itemCount) {
		do {
			fVar1 = FLOAT_80332eb8;
			if (*(int*)(item + 0x12) <= timer) {
				if (timer < *(int*)(item + 0x12) + *(int*)(item + 0x14)) {
					*(int*)(item + 0x10) = *(int*)(item + 0x10) + 1;
					dVar2 = DOUBLE_80332ec0;
					*(float*)(item + 8) = (float)((DOUBLE_80332ec0 / (double)*(int*)(item + 0x14)) * (double)*(int*)(item + 0x10));
					if ((*(unsigned int*)(item + 0x16) & 2) == 0) {
						fVar1 = (float)((dVar2 / (double)*(int*)(item + 0x14)) * (double)*(int*)(item + 0x10));
						*(float*)(item + 0x18) = (*(float*)(item + 0x1c) - (float)(double)(int)*item) * fVar1;
						*(float*)(item + 0x1a) = (*(float*)(item + 0x1e) - (float)(double)(int)item[1]) * fVar1;
					}
				} else {
					doneCount = doneCount + 1;
					*(float*)(item + 8) = FLOAT_80332ee0;
					*(float*)(item + 0x18) = fVar1;
					*(float*)(item + 0x1a) = fVar1;
				}
			}
			item = item + 0x20;
			remaining = remaining - 1;
		} while (remaining != 0);
	}

	return itemCount == doneCount;
}

/*
 * --INFO--
 * PAL Address: 0x8015b264
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::EquipClose0()
{
	float fVar1;
	double dVar2;
	double dVar3;
	s16* selected;
	int doneCount;
	int timer;
	int remaining;
	s16* item;
	int itemCount;
	int selectedOffset;

	*(s16*)(GetEquipStateBase(this) + 0x22) = *(s16*)(GetEquipStateBase(this) + 0x22) + 1;
	timer = (int)*(s16*)(GetEquipStateBase(this) + 0x22);
	selectedOffset = *(s16*)(GetEquipStateBase(this) + 0x26) * 0x40 + 8;
	if (7 < timer) {
		*(s16*)(GetEquipListBase(this) + selectedOffset) = *(s16*)(GetEquipListBase(this) + selectedOffset) + 0x13;
	}

	item = GetEquipList(this);
	doneCount = 0;
	itemCount = (int)item[1] - (int)*item;
	item = item + *item * 0x20 + 4;
	remaining = itemCount;
	if (0 < itemCount) {
		do {
			dVar3 = DOUBLE_80332ed8;
			fVar1 = FLOAT_80332eb8;
			if (*(int*)(item + 0x12) <= timer) {
				if (timer < *(int*)(item + 0x12) + *(int*)(item + 0x14)) {
					*(int*)(item + 0x10) = *(int*)(item + 0x10) + 1;
					dVar2 = DOUBLE_80332ec0;
					*(float*)(item + 8) =
					    (float)-((DOUBLE_80332ec0 /
					              ((double)(((unsigned int)*(unsigned int*)(item + 0x14) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
					             ((double)(((unsigned int)*(unsigned int*)(item + 0x10) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3) -
					             DOUBLE_80332ec0);
					if ((*(unsigned int*)(item + 0x16) & 2) == 0) {
						fVar1 = (float)-((dVar2 /
						                  ((double)(((unsigned int)*(unsigned int*)(item + 0x14) ^ 0x80000000U) | 0x4330000000000000ULL) -
						                   dVar3)) *
						                 ((double)(((unsigned int)*(unsigned int*)(item + 0x10) ^ 0x80000000U) | 0x4330000000000000ULL) -
						                  dVar3) -
						                 dVar2);
						*(float*)(item + 0x18) =
						    (*(float*)(item + 0x1c) - (float)((double)(((unsigned int)(int)*item ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
						    fVar1;
						*(float*)(item + 0x1a) =
						    (*(float*)(item + 0x1e) - (float)((double)(((unsigned int)(int)item[1] ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
						    fVar1;
					}
				} else {
					doneCount = doneCount + 1;
					*(float*)(item + 8) = FLOAT_80332eb8;
					*(float*)(item + 0x18) = fVar1;
					*(float*)(item + 0x1a) = fVar1;
				}
			}
			item = item + 0x20;
			remaining = remaining + -1;
		} while (remaining != 0);
	}

	if (itemCount == doneCount) {
		selected = (s16*)(GetEquipListBase(this) + selectedOffset);
		*selected = (s16)(int)-(((double)(((unsigned int)(short)selected[2] ^ 0x80000000U) | 0x4330000000000000ULL) - DOUBLE_80332ed8) *
		                        DOUBLE_80332ed0 -
		                        DOUBLE_80332ec8);
	}

	return itemCount == doneCount;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetEquipItem()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8015b158
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ChkEquipActive(int index)
{
	unsigned int caravanWork = Game.m_scriptFoodBase[0];
	s16* entries = GetLetterBuffer__6JoyBusFi(&Joybus, 0);
	s16* itemEntries = entries + 1;

	if ((index < 0) || (entries[0] <= index)) {
		return 0;
	}

	int equipIndex = static_cast<int>(*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0x26));

	if (index == 0) {
		if (equipIndex < 3) {
			return 0;
		}
		return (unsigned int)(int)*reinterpret_cast<s16*>(caravanWork + equipIndex * 2 + 0xac) >> 0x1f ^ 1;
	}

	int item = static_cast<int>(*reinterpret_cast<s16*>(caravanWork + itemEntries[index - 1] * 2 + 0xb6));
	int active = ChkEquipPossible__8CMenuPcsFi(this, item);

	if ((active != 0) && (GetEquipType__8CMenuPcsFi(this, item) != equipIndex)) {
		return 0;
	}
	return active;
}
