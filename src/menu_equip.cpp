#include "ffcc/menu_equip.h"
#include "ffcc/joybus.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int EquipCtrlCur__8CMenuPcsFv(CMenuPcs*);
extern "C" int EquipOpen0__8CMenuPcsFv(CMenuPcs*);
extern "C" int EquipClose0__8CMenuPcsFv(CMenuPcs*);
extern "C" int ChkEquipPossible__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int GetEquipType__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int EquipChk__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void CmdInit1__8CMenuPcsFv(CMenuPcs*);
extern "C" void CmdInit2__8CMenuPcsFv(CMenuPcs*);
extern "C" int CanPlayerPutItem__12CCaravanWorkFv(void*);
extern "C" void ChgEquipPos__12CCaravanWorkFii(void*, int, int);
extern "C" void CalcStatus__12CCaravanWorkFv(void*);

extern float FLOAT_80332eb8;
extern float FLOAT_80332ee0;
extern float FLOAT_80332f10;
extern float FLOAT_80332f14;
extern float FLOAT_80332f18;
extern double DOUBLE_80332ec0;
extern double DOUBLE_80332ec8;
extern double DOUBLE_80332ed0;
extern double DOUBLE_80332ed8;

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

	workPtr = (int*)((char*)this + 0x850);
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
	u8* self = reinterpret_cast<u8*>(this);
	u8* equipState = *reinterpret_cast<u8**>(self + 0x82c);

	if (equipState[0xb] == 0) {
		memset(*reinterpret_cast<void**>(self + 0x850), 0, 0x1008);

		float fVar = FLOAT_80332ee0;
		int scalePtr = *reinterpret_cast<int*>(self + 0x850) + 8;
		for (int i = 0; i < 8; i++) {
			*reinterpret_cast<float*>(scalePtr + 0x14) = fVar;
			*reinterpret_cast<float*>(scalePtr + 0x54) = fVar;
			*reinterpret_cast<float*>(scalePtr + 0x94) = fVar;
			*reinterpret_cast<float*>(scalePtr + 0xd4) = fVar;
			*reinterpret_cast<float*>(scalePtr + 0x114) = fVar;
			*reinterpret_cast<float*>(scalePtr + 0x154) = fVar;
			*reinterpret_cast<float*>(scalePtr + 0x194) = fVar;
			*reinterpret_cast<float*>(scalePtr + 0x1d4) = fVar;
			scalePtr += 0x200;
		}

		int menuIndex = 0;
		s16* entry = reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x850) + 8);
		for (int i = 0; i < 2; i++) {
			*reinterpret_cast<int*>(entry + 0xe) = 0x34;
			entry[2] = 200;
			entry[3] = 0x28;
			*entry = static_cast<s16>(-((static_cast<double>(entry[2]) * 0.5) - 320.0));
			entry[1] = static_cast<s16>(menuIndex * (entry[3] - 8) + 0x60);
			*reinterpret_cast<float*>(entry + 4) = FLOAT_80332eb8;
			*reinterpret_cast<float*>(entry + 6) = FLOAT_80332eb8;
			*reinterpret_cast<int*>(entry + 0x12) = menuIndex;
			*reinterpret_cast<int*>(entry + 0x14) = 3;

			*reinterpret_cast<int*>(entry + 0x2e) = 0x34;
			entry[0x22] = 200;
			entry[0x23] = 0x28;
			entry[0x20] = static_cast<s16>(-((static_cast<double>(entry[0x22]) * 0.5) - 320.0));
			entry[0x21] = static_cast<s16>((menuIndex + 1) * (entry[0x23] - 8) + 0x60);
			*reinterpret_cast<float*>(entry + 0x24) = FLOAT_80332eb8;
			*reinterpret_cast<float*>(entry + 0x26) = FLOAT_80332eb8;
			*reinterpret_cast<int*>(entry + 0x32) = menuIndex + 1;
			*reinterpret_cast<int*>(entry + 0x34) = 3;

			entry += 0x40;
			menuIndex += 2;
		}

		**reinterpret_cast<s16**>(self + 0x850) = 4;
		EquipInit1();

		s16* letterBuf = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		s16 itemCount = 0;
		for (int i = 0; i < 0x40; i++) {
			if (GetItemType__8CMenuPcsFii(this, i, 0) == 1) {
				letterBuf++;
				*letterBuf = static_cast<s16>(i);
				itemCount++;
			}
		}

		*reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0)) = itemCount + 1;
		*reinterpret_cast<s16*>(equipState + 0x26) = 0;
		equipState[0xb] = 1;
	}

	int doneCount = 0;
	*reinterpret_cast<s16*>(equipState + 0x22) = *reinterpret_cast<s16*>(equipState + 0x22) + 1;

	s16* entries = *reinterpret_cast<s16**>(self + 0x850);
	u32 count = static_cast<u32>(entries[0]);
	s16* entry = entries + 4;
	int timer = static_cast<int>(*reinterpret_cast<s16*>(equipState + 0x22));

	for (u32 i = 0; i < count; i++) {
		if (*reinterpret_cast<int*>(entry + 0x12) <= timer) {
			if (timer < (*reinterpret_cast<int*>(entry + 0x12) + *reinterpret_cast<int*>(entry + 0x14))) {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				*reinterpret_cast<float*>(entry + 8) = static_cast<float>(
					(1.0 / static_cast<double>(*reinterpret_cast<int*>(entry + 0x14))) *
					static_cast<double>(*reinterpret_cast<int*>(entry + 0x10)));
			} else {
				doneCount++;
				*reinterpret_cast<float*>(entry + 8) = FLOAT_80332ee0;
			}
		}
		entry += 0x20;
	}

	if (entries[0] == doneCount) {
		entry = entries + 4;
		if (count != 0) {
			u32 blockCount = count >> 3;
			if (blockCount != 0) {
				do {
					entry[0x12] = 0;
					entry[0x13] = 0;
					entry[0x14] = 0;
					entry[0x15] = 1;
					*reinterpret_cast<float*>(entry + 8) = FLOAT_80332ee0;
					entry[0x32] = 0;
					entry[0x33] = 0;
					entry[0x34] = 0;
					entry[0x35] = 1;
					*reinterpret_cast<float*>(entry + 0x28) = FLOAT_80332ee0;
					entry[0x52] = 0;
					entry[0x53] = 0;
					entry[0x54] = 0;
					entry[0x55] = 1;
					*reinterpret_cast<float*>(entry + 0x48) = FLOAT_80332ee0;
					entry[0x72] = 0;
					entry[0x73] = 0;
					entry[0x74] = 0;
					entry[0x75] = 1;
					*reinterpret_cast<float*>(entry + 0x68) = FLOAT_80332ee0;
					entry[0x92] = 0;
					entry[0x93] = 0;
					entry[0x94] = 0;
					entry[0x95] = 1;
					*reinterpret_cast<float*>(entry + 0x88) = FLOAT_80332ee0;
					entry[0xb2] = 0;
					entry[0xb3] = 0;
					entry[0xb4] = 0;
					entry[0xb5] = 1;
					*reinterpret_cast<float*>(entry + 0xa8) = FLOAT_80332ee0;
					entry[0xd2] = 0;
					entry[0xd3] = 0;
					entry[0xd4] = 0;
					entry[0xd5] = 1;
					*reinterpret_cast<float*>(entry + 200) = FLOAT_80332ee0;
					entry[0xf2] = 0;
					entry[0xf3] = 0;
					entry[0xf4] = 0;
					entry[0xf5] = 1;
					*reinterpret_cast<float*>(entry + 0xe8) = FLOAT_80332ee0;
					entry += 0x100;
					blockCount--;
				} while (blockCount != 0);

				count &= 7;
				if (count == 0) {
					return 1;
				}
			}

			do {
				entry[0x12] = 0;
				entry[0x13] = 0;
				entry[0x14] = 0;
				entry[0x15] = 1;
				*reinterpret_cast<float*>(entry + 8) = FLOAT_80332ee0;
				entry += 0x20;
				count--;
			} while (count != 0);
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
	u8* self = reinterpret_cast<u8*>(this);
	u8* equipState = *reinterpret_cast<u8**>(self + 0x82c);
	s16 mode;

	*reinterpret_cast<s16*>(equipState + 0x32) = *reinterpret_cast<s16*>(equipState + 0x30);
	mode = *reinterpret_cast<s16*>(equipState + 0x30);

	if ((mode == 0) || ((mode != 0) && (*reinterpret_cast<s16*>(equipState + 0x12) == 1))) {
		state = EquipCtrlCur__8CMenuPcsFv(this);
	} else if ((mode == 1) && (*reinterpret_cast<s16*>(equipState + 0x12) == 0)) {
		state = EquipOpen0__8CMenuPcsFv(this);
		if (state != 0) {
			state = 0;
			*reinterpret_cast<s16*>(equipState + 0x12) = *reinterpret_cast<s16*>(equipState + 0x12) + 1;
		}
	} else if ((mode == 1) && (*reinterpret_cast<s16*>(equipState + 0x12) == 2) && (EquipClose0__8CMenuPcsFv(this) != 0)) {
		*reinterpret_cast<s16*>(equipState + 0x12) = 0;
		*reinterpret_cast<s16*>(equipState + 0x30) = 0;
		*reinterpret_cast<s16*>(equipState + 0x22) = 0;
		CmdInit1__8CMenuPcsFv(this);
		state = 0;
	}

	if (state != 0) {
		float fVar = FLOAT_80332ee0;
		int menuData = *reinterpret_cast<int*>(self + 0x850);
		s16 count = **reinterpret_cast<s16**>(self + 0x850);
		int item = menuData + 8;

		for (int i = 0; i < count; i++) {
			*reinterpret_cast<float*>(item + 0x10) = fVar;
			*reinterpret_cast<float*>(item + 0x14) = fVar;
			item += 0x40;
		}

		u32 caravanWork = Game.game.m_scriptFoodBase[0];
		u32 equipCount = static_cast<u32>(*reinterpret_cast<s16*>(caravanWork + 0xbaa));
		int index = 0;
		int offset = static_cast<int>(equipCount - 1) * 0x40;

		if (static_cast<int>(equipCount - 1) >= 0) {
			for (u32 i = 0; i < equipCount; i++) {
				int slot = menuData + offset + 8;
				*reinterpret_cast<int*>(slot + 0x24) = index;
				*reinterpret_cast<int*>(slot + 0x28) = 3;
				index++;
				offset -= 0x40;
			}
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipDraw()
{
	// TODO
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
	u32 caravanWork = Game.game.m_scriptFoodBase[0];

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
int CMenuPcs::EquipOpen0()
{
	float fVar1;
	double dVar2;
	int timer;
	int selectedOffset;
	s16* item;
	int doneCount;
	int itemCount;
	int remaining;

	*(s16*)(*(int*)((char*)this + 0x82c) + 0x22) = *(s16*)(*(int*)((char*)this + 0x82c) + 0x22) + 1;
	timer = (int)*(s16*)(*(int*)((char*)this + 0x82c) + 0x22);
	selectedOffset = *(s16*)(*(int*)((char*)this + 0x82c) + 0x26) * 0x40 + 8;

	if (timer < 5) {
		*(s16*)(*(int*)((char*)this + 0x850) + selectedOffset) = *(s16*)(*(int*)((char*)this + 0x850) + selectedOffset) - 0x13;
	}

	item = *(s16**)((char*)this + 0x850);
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
int CMenuPcs::EquipClose0()
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

	*(s16*)(*(int*)((char*)this + 0x82c) + 0x22) = *(s16*)(*(int*)((char*)this + 0x82c) + 0x22) + 1;
	timer = (int)*(s16*)(*(int*)((char*)this + 0x82c) + 0x22);
	if (7 < timer) {
		*(s16*)(*(int*)((char*)this + 0x850) + *(s16*)(*(int*)((char*)this + 0x82c) + 0x26) * 0x40 + 8) =
		    *(s16*)(*(int*)((char*)this + 0x850) + *(s16*)(*(int*)((char*)this + 0x82c) + 0x26) * 0x40 + 8) + 0x13;
	}

	item = *(s16**)((char*)this + 0x850);
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
		selected = (s16*)(*(int*)((char*)this + 0x850) + *(s16*)(*(int*)((char*)this + 0x82c) + 0x26) * 0x40 + 8);
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
	unsigned int caravanWork = Game.game.m_scriptFoodBase[0];
	s16* entries = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	int equipIndex = static_cast<int>(*reinterpret_cast<s16*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0x26));

	if ((index < 0) || (entries[0] <= index)) {
		return 0;
	}

	if (index == 0) {
		if (equipIndex < 3) {
			return 0;
		}
		return *reinterpret_cast<s16*>(caravanWork + equipIndex * 2 + 0xac) >= 0;
	}

	int item = static_cast<int>(*reinterpret_cast<s16*>(caravanWork + entries[index] * 2 + 0xb6));
	int active = ChkEquipPossible__8CMenuPcsFi(this, item);

	if ((active != 0) && (GetEquipType__8CMenuPcsFi(this, item) != equipIndex)) {
		active = 0;
	}

	return active;
}
