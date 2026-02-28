#include "ffcc/menu_cmd.h"
#include "ffcc/fontman.h"
#include "ffcc/joybus.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "dolphin/types.h"
#include <string.h>

extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int GetItemIcon__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int EquipChk__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void CalcStatus__12CCaravanWorkFv(void*);
extern "C" void ChgCmdLst__12CCaravanWorkFii(void*, int, int);
extern "C" void UniteComList__12CCaravanWorkFiii(void*, int, int, int);
extern "C" void UnuniteComList__12CCaravanWorkFii(void*, int, int);
extern "C" unsigned int CmdCtrlCur__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdOpen0__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose0__8CMenuPcsFv(CMenuPcs*);
extern "C" void CmdInit1__8CMenuPcsFv(CMenuPcs*);
extern "C" void CmdInit2__8CMenuPcsFv(CMenuPcs*);
extern "C" int UniteOpenAnim__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int ChkUnite__8CMenuPcsFiPA2_i(CMenuPcs*, int, int (*)[2]);
extern "C" unsigned int CmdOpen1__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose1__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose2__8CMenuPcsFv(CMenuPcs*);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(CMenuPcs*, unsigned long, float, float, float, float, float, float, GXColor*, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" float CalcListPos__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void DrawListPosMark__8CMenuPcsFfff(CMenuPcs*, float, float, float);
extern "C" void DrawCursor__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(CMenuPcs*, int, CFont*, int, int, GXColor, int, float, float);
extern "C" void DrawEquipMark__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);

extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" int GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);

extern double DOUBLE_80332a58;
extern double DOUBLE_80332a60;
extern double DOUBLE_80332a68;
extern double DOUBLE_80332a78;
extern double DOUBLE_80332a80;
extern double DOUBLE_80332a90;
extern double DOUBLE_80332a98;
extern double DOUBLE_80332aa0;
extern double DOUBLE_80332aa8;
extern double DOUBLE_80332ab8;
extern double DOUBLE_80332ac0;
extern float FLOAT_80332ad0;
extern float FLOAT_80332ac8;
extern float FLOAT_80332a70;
extern float FLOAT_80332ab0;
extern float FLOAT_80332a88;
extern float FLOAT_80332b38;
extern float FLOAT_80332b3c;
extern float FLOAT_80332ad0;
extern float FLOAT_80332acc;
extern float FLOAT_80332ad8;
extern float FLOAT_80332ae8;
extern float FLOAT_80332b08;
extern float FLOAT_80332b10;
extern float FLOAT_80332b14;
extern float FLOAT_80332b18;
extern float FLOAT_80332b28;
extern double DOUBLE_80332af8;
extern double DOUBLE_80332b20;
extern s16 DAT_801de910[];
extern s16 DAT_801de914[];
extern s16 DAT_801de91c[];
extern const char* PTR_s_Flamestrike_80214d28[];
extern const char* PTR_s_Feuer_Hieb_80214d3c[];
extern const char* PTR_s_Colpo_Fire_80214d50[];
extern const char* PTR_s_Pyro_Frappe_80214d64[];
extern const char* PTR_s_Efecto_Fuego_80214d78[];
s32 DAT_8032eec8;
s32 s_UniteTop[3];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool IsMagicArti(int)
{
	// TODO
	return false;
}

/*
 * --INFO--
 * PAL Address: 0x8015023c
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdInit()
{
	u8* self = reinterpret_cast<u8*>(this);
	u32 caravanWork = Game.game.m_scriptFoodBase[0];
	memset(*reinterpret_cast<void**>(self + 0x850), 0, 0x1008);

	float fVar2 = FLOAT_80332a70;
	s32 iVar5 = *reinterpret_cast<s32*>(self + 0x850) + 8;
	s32 iVar8 = 8;
	do {
		*reinterpret_cast<float*>(iVar5 + 0x14) = fVar2;
		*reinterpret_cast<float*>(iVar5 + 0x54) = fVar2;
		*reinterpret_cast<float*>(iVar5 + 0x94) = fVar2;
		*reinterpret_cast<float*>(iVar5 + 0xD4) = fVar2;
		*reinterpret_cast<float*>(iVar5 + 0x114) = fVar2;
		*reinterpret_cast<float*>(iVar5 + 0x154) = fVar2;
		*reinterpret_cast<float*>(iVar5 + 0x194) = fVar2;
		*reinterpret_cast<float*>(iVar5 + 0x1D4) = fVar2;
		iVar5 += 0x200;
		iVar8--;
	} while (iVar8 != 0);

	s16* puVar7 = reinterpret_cast<s16*>(*reinterpret_cast<s32*>(self + 0x850) + 8);
	iVar5 = 0;
	iVar8 = 8;
	u32 uVar6 = caravanWork;
	float fVar3 = FLOAT_80332ab0;
	float fVar4 = FLOAT_80332ad0;
	do {
		if (iVar5 < *reinterpret_cast<s16*>(caravanWork + 0xBAA)) {
			*reinterpret_cast<u32*>(puVar7 + 0xE) = 0x2D;
		} else {
			*reinterpret_cast<u32*>(puVar7 + 0xE) = 0xFFFFFFFF;
		}

		puVar7[2] = 200;
		puVar7[3] = 0x20;
		*puVar7 = 0x74;
		puVar7[1] = static_cast<s16>(iVar5 * puVar7[3] + 0x28);
		*reinterpret_cast<float*>(puVar7 + 4) = fVar3;
		*reinterpret_cast<float*>(puVar7 + 6) = fVar4;

		if ((1 < iVar5) && (*reinterpret_cast<s16*>(uVar6 + 0x204) < 0)) {
			*reinterpret_cast<float*>(puVar7 + 6) += static_cast<float>(static_cast<double>(puVar7[3]));
		}

		*reinterpret_cast<s32*>(puVar7 + 0x12) = iVar5;
		uVar6 += 2;
		iVar5++;
		*reinterpret_cast<u32*>(puVar7 + 0x14) = 3;
		puVar7 += 0x20;
		iVar8--;
	} while (iVar8 != 0);

	**reinterpret_cast<s16**>(self + 0x850) = 8;
	CmdInit1__8CMenuPcsFv(this);
	GetCmdItem();
	*reinterpret_cast<s16*>(*reinterpret_cast<s32*>(self + 0x82C) + 0x26) = 2;
	*reinterpret_cast<u8*>(*reinterpret_cast<s32*>(self + 0x82C) + 0x0B) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdInit0()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8014ff0c
 * PAL Size: 816b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdInit1()
{
	float fVar2;
	float fVar3;
	float fVar4;
	u32 uVar5;
	s16 sVar1;
	s16 sVar6;
	s16 sVar7;
	s16* psVar8;
	s16* psVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	u32 uVar14;

	fVar4 = FLOAT_80332b38;
	fVar3 = FLOAT_80332ad0;
	fVar2 = FLOAT_80332a70;
	iVar10 = (int)**(s16**)((u8*)this + 0x850);
	psVar8 = *(s16**)((u8*)this + 0x850) + iVar10 * 0x20 + 4;
	psVar8[0xe] = 0;
	psVar8[0xf] = 0x2e;
	*psVar8 = 0xb8;
	psVar8[1] = 0x28;
	psVar8[2] = 0x78;
	psVar8[3] = 0x108;
	*(float*)(psVar8 + 4) = fVar4;
	*(float*)(psVar8 + 6) = fVar3;
	*(float*)(psVar8 + 10) = fVar2;
	psVar8[0x12] = 0;
	psVar8[0x13] = 5;
	psVar8[0x14] = 0;
	psVar8[0x15] = 5;

	iVar11 = 0x2f;
	if (*(s16*)((u8*)this + 0x864) == 0) {
		iVar11 = 0x46;
	}

	psVar8 = (s16*)(*(int*)((u8*)this + 0x850) + (iVar10 + 1) * 0x40 + 8);
	*(int*)(psVar8 + 0xe) = iVar11;
	*psVar8 = 0xa0;
	fVar3 = FLOAT_80332ab0;
	psVar8[1] = 0xe;
	fVar2 = FLOAT_80332a70;
	psVar8[2] = 0x30;
	psVar8[3] = 0x30;
	*(float*)(psVar8 + 4) = fVar3;
	*(float*)(psVar8 + 6) = fVar3;
	*(float*)(psVar8 + 10) = fVar2;
	*(int*)(psVar8 + 0x12) = 0;
	*(int*)(psVar8 + 0x14) = 5;

	psVar8 = (s16*)(*(int*)((u8*)this + 0x850) + (iVar10 + 2) * 0x40 + 8);
	*(int*)(psVar8 + 0xe) = iVar11;
	psVar8[2] = 0x30;
	fVar2 = FLOAT_80332ab0;
	sVar7 = 0;
	psVar8[3] = 0x30;
	fVar3 = FLOAT_80332b3c;
	*psVar8 = 0xa5;
	iVar12 = iVar10 + 4;
	psVar8[1] = (s16)(0x150 - psVar8[3]);
	iVar13 = iVar12 * 0x40;
	*(float*)(psVar8 + 4) = fVar2;
	*(float*)(psVar8 + 6) = fVar2;
	*(float*)(psVar8 + 10) = fVar3;
	*(int*)(psVar8 + 0x12) = 0;
	*(int*)(psVar8 + 0x14) = 5;

	psVar8 = (s16*)(*(int*)((u8*)this + 0x850) + (iVar10 + 3) * 0x40 + 8);
	*(int*)(psVar8 + 0x16) = 2;
	*(int*)(psVar8 + 0xe) = 0x2e;
	*psVar8 = 0xa0;
	psVar8[1] = 8;
	psVar8[2] = 0x48;
	psVar8[3] = 0x140;
	*(float*)(psVar8 + 4) = fVar2;
	*(float*)(psVar8 + 6) = fVar2;
	*(int*)(psVar8 + 0x12) = 0;
	*(int*)(psVar8 + 0x14) = 5;

	psVar9 = *(s16**)((u8*)this + 0x850) + **(s16**)((u8*)this + 0x850) * 0x20 + 4;
	iVar10 = 4;
	do {
		psVar8 = (s16*)(*(int*)((u8*)this + 0x850) + iVar13 + 8);
		psVar8[0x16] = 0;
		psVar8[0x17] = 2;
		psVar8[0xe] = 0;
		psVar8[0xf] = 0x37;
		iVar12 += 2;
		*psVar8 = *psVar9 + 0x24;
		sVar1 = sVar7 + 0x20;
		psVar8[1] = psVar9[1] + sVar7;
		psVar8[2] = 200;
		psVar8[3] = 0x28;
		*(float*)(psVar8 + 4) = fVar2;
		*(float*)(psVar8 + 6) = fVar2;
		psVar8[0x12] = 0;
		psVar8[0x13] = 7;
		psVar8[0x14] = 0;
		psVar8[0x15] = 5;

		iVar11 = iVar13 + 0x48;
		iVar13 += 0x80;
		psVar8 = (s16*)(*(int*)((u8*)this + 0x850) + iVar11);
		psVar8[0x16] = 0;
		psVar8[0x17] = 2;
		psVar8[0xe] = 0;
		psVar8[0xf] = 0x37;
		*psVar8 = *psVar9 + 0x24;
		sVar7 += 0x40;
		psVar8[1] = psVar9[1] + sVar1;
		psVar8[2] = 200;
		psVar8[3] = 0x28;
		*(float*)(psVar8 + 4) = fVar2;
		*(float*)(psVar8 + 6) = fVar2;
		psVar8[0x12] = 0;
		psVar8[0x13] = 7;
		psVar8[0x14] = 0;
		fVar3 = FLOAT_80332ab0;
		psVar8[0x15] = 5;
		iVar10 -= 1;
	} while (iVar10 != 0);
	*(s16*)(*(int*)((u8*)this + 0x850) + 2) = (s16)iVar12;

	psVar8 = *(s16**)((u8*)this + 0x850);
	uVar5 = (u32)((int)psVar8[1] - (int)*psVar8);
	psVar8 = psVar8 + *psVar8 * 0x20 + 4;
	if ((int)uVar5 > 0) {
		uVar14 = uVar5 >> 3;
		if (uVar14 != 0) {
			do {
				psVar8[0x10] = 0;
				psVar8[0x11] = 0;
				*(float*)(psVar8 + 8) = fVar3;
				psVar8[0x30] = 0;
				psVar8[0x31] = 0;
				*(float*)(psVar8 + 0x28) = fVar3;
				psVar8[0x50] = 0;
				psVar8[0x51] = 0;
				*(float*)(psVar8 + 0x48) = fVar3;
				psVar8[0x70] = 0;
				psVar8[0x71] = 0;
				*(float*)(psVar8 + 0x68) = fVar3;
				psVar8[0x90] = 0;
				psVar8[0x91] = 0;
				*(float*)(psVar8 + 0x88) = fVar3;
				psVar8[0xb0] = 0;
				psVar8[0xb1] = 0;
				*(float*)(psVar8 + 0xa8) = fVar3;
				psVar8[0xd0] = 0;
				psVar8[0xd1] = 0;
				*(float*)(psVar8 + 200) = fVar3;
				psVar8[0xf0] = 0;
				psVar8[0xf1] = 0;
				*(float*)(psVar8 + 0xe8) = fVar3;
				psVar8 += 0x100;
				uVar14 -= 1;
			} while (uVar14 != 0);
			uVar5 &= 7;
			if (uVar5 == 0) {
				return;
			}
		}
		do {
			psVar8[0x10] = 0;
			psVar8[0x11] = 0;
			*(float*)(psVar8 + 8) = fVar3;
			psVar8 += 0x20;
			uVar5 -= 1;
		} while (uVar5 != 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8014fc50
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdInit2()
{
	s16* psVar7;
	s16 sVar1;
	float fVar2;
	u32 uVar4;
	u32 uVar5;
	u32 uVar8;
	int iVar3;
	int iVar6;

	uVar4 = 0x2f;
	psVar7 = *(s16**)((u8*)this + 0x850);
	sVar1 = *psVar7;
	iVar3 = (int)sVar1;
	(psVar7 + iVar3 * 0x20 + 0x12)[0] = 0;
	(psVar7 + iVar3 * 0x20 + 0x12)[1] = 0x2e;
	(psVar7 + iVar3 * 0x20 + 0x16)[0] = 0;
	(psVar7 + iVar3 * 0x20 + 0x16)[1] = 2;
	(psVar7 + iVar3 * 0x20 + 0x18)[0] = 0;
	(psVar7 + iVar3 * 0x20 + 0x18)[1] = 5;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 1) * 0x40 + 8;
	if (*(s16*)((u8*)this + 0x864) == 0) {
		uVar4 = 0x46;
	}
	*(u32*)(iVar6 + 0x1c) = uVar4;
	*(u32*)(iVar6 + 0x24) = 7;
	uVar4 = 0x2f;
	*(u32*)(iVar6 + 0x28) = 5;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 2) * 0x40 + 8;
	if (*(s16*)((u8*)this + 0x864) == 0) {
		uVar4 = 0x46;
	}
	*(u32*)(iVar6 + 0x1c) = uVar4;
	*(u32*)(iVar6 + 0x24) = 7;
	*(u32*)(iVar6 + 0x28) = 5;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 3) * 0x40 + 8;
	*(u32*)(iVar6 + 0x2c) = 2;
	*(u32*)(iVar6 + 0x1c) = 0x2e;
	*(u32*)(iVar6 + 0x24) = 7;
	*(u32*)(iVar6 + 0x28) = 5;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 4) * 0x40 + 8;
	*(u32*)(iVar6 + 0x2c) = 2;
	*(u32*)(iVar6 + 0x1c) = 0x37;
	*(u32*)(iVar6 + 0x24) = 0;
	*(u32*)(iVar6 + 0x28) = 5;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 5) * 0x40 + 8;
	*(u32*)(iVar6 + 0x2c) = 2;
	*(u32*)(iVar6 + 0x1c) = 0x37;
	*(u32*)(iVar6 + 0x24) = 0;
	*(u32*)(iVar6 + 0x28) = 5;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 6) * 0x40 + 8;
	*(u32*)(iVar6 + 0x2c) = 2;
	*(u32*)(iVar6 + 0x1c) = 0x37;
	*(u32*)(iVar6 + 0x24) = 0;
	*(u32*)(iVar6 + 0x28) = 5;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 7) * 0x40 + 8;
	*(u32*)(iVar6 + 0x2c) = 2;
	*(u32*)(iVar6 + 0x1c) = 0x37;
	*(u32*)(iVar6 + 0x24) = 0;
	*(u32*)(iVar6 + 0x28) = 5;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 8) * 0x40 + 8;
	*(u32*)(iVar6 + 0x2c) = 2;
	*(u32*)(iVar6 + 0x1c) = 0x37;
	*(u32*)(iVar6 + 0x24) = 0;
	*(u32*)(iVar6 + 0x28) = 5;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 9) * 0x40 + 8;
	*(u32*)(iVar6 + 0x2c) = 2;
	*(u32*)(iVar6 + 0x1c) = 0x37;
	*(u32*)(iVar6 + 0x24) = 0;
	*(u32*)(iVar6 + 0x28) = 5;
	fVar2 = FLOAT_80332a70;
	iVar6 = *(int*)((u8*)this + 0x850) + (iVar3 + 10) * 0x40 + 8;
	*(u32*)(iVar6 + 0x2c) = 2;
	*(u32*)(iVar6 + 0x1c) = 0x37;
	*(u32*)(iVar6 + 0x24) = 0;
	*(u32*)(iVar6 + 0x28) = 5;
	iVar3 = *(int*)((u8*)this + 0x850) + (iVar3 + 0xb) * 0x40 + 8;
	*(u32*)(iVar3 + 0x2c) = 2;
	*(u32*)(iVar3 + 0x1c) = 0x37;
	*(u32*)(iVar3 + 0x24) = 0;
	*(u32*)(iVar3 + 0x28) = 5;
	*(s16*)(*(int*)((u8*)this + 0x850) + 2) = sVar1 + 0xc;
	psVar7 = *(s16**)((u8*)this + 0x850);
	uVar5 = (u32)((int)psVar7[1] - (int)*psVar7);
	psVar7 = psVar7 + *psVar7 * 0x20 + 4;
	if ((int)uVar5 > 0) {
		uVar8 = uVar5 >> 3;
		if (uVar8 != 0) {
			do {
				psVar7[0x10] = 0;
				psVar7[0x11] = 0;
				*(float*)(psVar7 + 8) = fVar2;
				psVar7[0x30] = 0;
				psVar7[0x31] = 0;
				*(float*)(psVar7 + 0x28) = fVar2;
				psVar7[0x50] = 0;
				psVar7[0x51] = 0;
				*(float*)(psVar7 + 0x48) = fVar2;
				psVar7[0x70] = 0;
				psVar7[0x71] = 0;
				*(float*)(psVar7 + 0x68) = fVar2;
				psVar7[0x90] = 0;
				psVar7[0x91] = 0;
				*(float*)(psVar7 + 0x88) = fVar2;
				psVar7[0xb0] = 0;
				psVar7[0xb1] = 0;
				*(float*)(psVar7 + 0xa8) = fVar2;
				psVar7[0xd0] = 0;
				psVar7[0xd1] = 0;
				*(float*)(psVar7 + 200) = fVar2;
				psVar7[0xf0] = 0;
				psVar7[0xf1] = 0;
				*(float*)(psVar7 + 0xe8) = fVar2;
				psVar7 += 0x100;
				uVar8 -= 1;
			} while (uVar8 != 0);
			uVar5 &= 7;
			if (uVar5 == 0) {
				return;
			}
		}
		do {
			psVar7[0x10] = 0;
			psVar7[0x11] = 0;
			*(float*)(psVar7 + 8) = fVar2;
			psVar7 += 0x20;
			uVar5 -= 1;
		} while (uVar5 != 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8014fa78
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdOpen()
{
	u8* self = reinterpret_cast<u8*>(this);
	s16* cmd = *reinterpret_cast<s16**>(self + 0x82c);
	s16* list = *reinterpret_cast<s16**>(self + 0x850);

	if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(cmd) + 0x0b) == 0) {
		CmdInit();
	}

	s32 finishedCount = 0;
	cmd[0x11] = static_cast<s16>(cmd[0x11] + 1);

	u32 count = static_cast<u32>(list[0]);
	s16* entry = list + 4;
	const s32 timer = static_cast<s32>(cmd[0x11]);
	u32 remaining = count;

	if (static_cast<s32>(remaining) > 0) {
		do {
			if (*reinterpret_cast<s32*>(entry + 0x12) <= timer) {
				const s32 start = *reinterpret_cast<s32*>(entry + 0x12);
				const s32 length = *reinterpret_cast<s32*>(entry + 0x14);
				if (timer < (start + length)) {
					s32 value = *reinterpret_cast<s32*>(entry + 0x10);
					value += 1;
					*reinterpret_cast<s32*>(entry + 0x10) = value;
					*reinterpret_cast<float*>(entry + 8) = static_cast<float>(
					    (DOUBLE_80332a58 / static_cast<double>(length)) * static_cast<double>(value));
				} else {
					finishedCount += 1;
					*reinterpret_cast<float*>(entry + 8) = FLOAT_80332a70;
				}
			}
			entry += 0x20;
			remaining -= 1;
		} while (remaining != 0);
	}

	bool done = false;
	if (list[0] == finishedCount) {
		float anim = FLOAT_80332a70;
		entry = list + 4;
		if (static_cast<s32>(count) > 0) {
			u32 batch = count >> 3;
			if (batch != 0) {
				do {
					entry[0x12] = 0;
					entry[0x13] = 0;
					entry[0x14] = 0;
					entry[0x15] = 1;
					*reinterpret_cast<float*>(entry + 8) = anim;
					entry[0x32] = 0;
					entry[0x33] = 0;
					entry[0x34] = 0;
					entry[0x35] = 1;
					*reinterpret_cast<float*>(entry + 0x28) = anim;
					entry[0x52] = 0;
					entry[0x53] = 0;
					entry[0x54] = 0;
					entry[0x55] = 1;
					*reinterpret_cast<float*>(entry + 0x48) = anim;
					entry[0x72] = 0;
					entry[0x73] = 0;
					entry[0x74] = 0;
					entry[0x75] = 1;
					*reinterpret_cast<float*>(entry + 0x68) = anim;
					entry[0x92] = 0;
					entry[0x93] = 0;
					entry[0x94] = 0;
					entry[0x95] = 1;
					*reinterpret_cast<float*>(entry + 0x88) = anim;
					entry[0xb2] = 0;
					entry[0xb3] = 0;
					entry[0xb4] = 0;
					entry[0xb5] = 1;
					*reinterpret_cast<float*>(entry + 0xa8) = anim;
					entry[0xd2] = 0;
					entry[0xd3] = 0;
					entry[0xd4] = 0;
					entry[0xd5] = 1;
					*reinterpret_cast<float*>(entry + 200) = anim;
					entry[0xf2] = 0;
					entry[0xf3] = 0;
					entry[0xf4] = 0;
					entry[0xf5] = 1;
					*reinterpret_cast<float*>(entry + 0xe8) = anim;
					entry += 0x100;
					batch -= 1;
				} while (batch != 0);
				count &= 7;
				if (count == 0) {
					done = true;
				}
			}

			if (done == false) {
				do {
					entry[0x12] = 0;
					entry[0x13] = 0;
					entry[0x14] = 0;
					entry[0x15] = 1;
					*reinterpret_cast<float*>(entry + 8) = anim;
					entry += 0x20;
					count -= 1;
				} while (count != 0);
			}
		}
		done = true;
	}

	if (done) {
		UniteOpenAnim__8CMenuPcsFi(this, -1);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8014f4e8
 * PAL Size: 1424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdCtrl()
{
	u8* self = reinterpret_cast<u8*>(this);
	u32 actionHandled = 0;
	s32 caravanWork = Game.game.m_scriptFoodBase[0];
	s32 cmd = *reinterpret_cast<s32*>(self + 0x82c);

	CalcStatus__12CCaravanWorkFv(reinterpret_cast<void*>(caravanWork));

	*reinterpret_cast<s16*>(cmd + 0x32) = *reinterpret_cast<s16*>(cmd + 0x30);

	s16 mode = *reinterpret_cast<s16*>(cmd + 0x30);
	s16 state = *reinterpret_cast<s16*>(cmd + 0x12);

	if ((mode == 0) || ((mode != 0) && (state == 1))) {
		actionHandled = CmdCtrlCur__8CMenuPcsFv(this);
	} else if ((mode == 1) && (state == 0)) {
		actionHandled = CmdOpen0__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x12) + 1);
		}
	} else if ((mode == 1) && (state == 2)) {
		actionHandled = CmdClose0__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			if (*reinterpret_cast<u8*>(cmd + 8) == 0) {
				*reinterpret_cast<s16*>(cmd + 0x12) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x12) + 1);
			} else {
				*reinterpret_cast<s16*>(cmd + 0x12) = 0;
				*reinterpret_cast<s16*>(cmd + 0x30) = 3;
				*reinterpret_cast<s16*>(cmd + 0x22) = 0;
				*reinterpret_cast<u8*>(cmd + 8) = 0;
				CmdInit1__8CMenuPcsFv(this);
			}
			actionHandled = 0;
		}
	} else if ((mode == 1) && (state == 3)) {
		actionHandled = static_cast<u32>(UniteOpenAnim__8CMenuPcsFi(this, -1));
		if (actionHandled != 0) {
			*reinterpret_cast<s16*>(cmd + 0x12) = 0;
			*reinterpret_cast<s16*>(cmd + 0x30) = 0;
			*reinterpret_cast<s16*>(cmd + 0x22) = 0;
			CmdInit1__8CMenuPcsFv(this);
			actionHandled = 0;
		}
	} else if ((mode == 2) && (state == 0)) {
		actionHandled = CmdOpen1__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x12) + 1);
		}
	} else if ((mode == 2) && (state == 2)) {
		actionHandled = CmdClose1__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			if (*reinterpret_cast<u8*>(cmd + 8) == 0) {
				*reinterpret_cast<s16*>(cmd + 0x30) = 0;
			} else {
				*reinterpret_cast<s16*>(cmd + 0x14) = 0;
				*reinterpret_cast<s16*>(cmd + 0x30) = 3;
			}
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = 0;
			*reinterpret_cast<s16*>(cmd + 0x22) = 0;
		}
	} else if ((mode == 3) && (state == 0)) {
		*reinterpret_cast<s16*>(cmd + 0x22) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x22) + 1);

		s32 selected = static_cast<s32>(*reinterpret_cast<s16*>(cmd + 0x26));
		s32 prev = selected - 1;
		for (; prev > 2; --prev) {
			if (*reinterpret_cast<s16*>(caravanWork + prev * 2 + 0x214) >= 0) {
				break;
			}
		}

		s32 next = selected + 1;
		s32 limit = static_cast<s32>(*reinterpret_cast<s16*>(caravanWork + 0xbaa));
		for (; next < limit; ++next) {
			if (*reinterpret_cast<s16*>(caravanWork + next * 2 + 0x214) >= 0) {
				break;
			}
		}

		s16* list = *reinterpret_cast<s16**>(self + 0x850);
		float minAnim = static_cast<float>(DOUBLE_80332a60);
		double timer = static_cast<double>(static_cast<s32>(*reinterpret_cast<s16*>(cmd + 0x22)));
		double anim = -((DOUBLE_80332a68 * timer) - DOUBLE_80332a58);
		for (s32 i = 0; i < static_cast<s32>(list[0]); i++) {
			if ((i < prev) || (next < i)) {
				float value = static_cast<float>(anim);
				if (static_cast<double>(value) < static_cast<double>(minAnim)) {
					value = FLOAT_80332a88;
				}
				*reinterpret_cast<float*>(list + i * 0x20 + 0x0c) = value;
			}
		}

		actionHandled = (static_cast<double>(static_cast<s32>(*reinterpret_cast<s16*>(cmd + 0x22))) >= DOUBLE_80332a78);
		if (actionHandled != 0) {
			*reinterpret_cast<s16*>(cmd + mode * 2 + 0x26) = static_cast<s16>(prev);
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x12) + 1);
		}
	} else if ((mode == 3) && (state == 2)) {
		actionHandled = CmdClose2__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = 0;
			*reinterpret_cast<s16*>(cmd + 0x30) = 0;
			*reinterpret_cast<s16*>(cmd + 0x22) = 0;
			*reinterpret_cast<u8*>(cmd + 8) = 0;
		}
	}

	if (actionHandled == 0) {
		return;
	}

	s16* list = *reinterpret_cast<s16**>(self + 0x850);
	for (s32 i = 0; i < static_cast<s32>(list[0]); i++) {
		*reinterpret_cast<float*>(list + i * 0x20 + 0x0c) = FLOAT_80332a70;
		*reinterpret_cast<float*>(list + i * 0x20 + 0x0e) = FLOAT_80332a70;
	}

	u32 count = static_cast<u32>(*reinterpret_cast<s16*>(caravanWork + 0xbaa));
	for (s32 i = static_cast<s32>(count) - 1, idx = 0; i >= 0; i--, idx++) {
		*reinterpret_cast<s32*>(list + i * 0x20 + 0x14) = idx;
		*reinterpret_cast<s32*>(list + i * 0x20 + 0x16) = 3;
	}

	*reinterpret_cast<u8*>(cmd + 8) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014f2e8
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CmdClose()
{
	u8* self = reinterpret_cast<u8*>(this);
	s32 cmd = *reinterpret_cast<s32*>(self + 0x82c);
	if (*reinterpret_cast<u8*>(cmd + 8) == 0) {
		if (UniteCloseAnim(-1) != 0) {
			*reinterpret_cast<s16*>(cmd + 0x22) = 0;
			*reinterpret_cast<u8*>(cmd + 8) = 1;
		}
		return 0;
	}

	s32 doneCount = 0;
	*reinterpret_cast<s16*>(cmd + 0x22) = *reinterpret_cast<s16*>(cmd + 0x22) + 1;

	s16* list = *reinterpret_cast<s16**>(self + 0x850);
	u32 count = static_cast<u32>(list[0]);
	s16* entry = list + 4;
	s32 closeTimer = static_cast<s32>(*reinterpret_cast<s16*>(cmd + 0x22));
	u32 remaining = count;

	if (remaining != 0) {
		do {
			if (*reinterpret_cast<s32*>(entry + 0x12) <= closeTimer) {
				if (closeTimer < (*reinterpret_cast<s32*>(entry + 0x12) + *reinterpret_cast<s32*>(entry + 0x14))) {
					*reinterpret_cast<s32*>(entry + 0x10) = *reinterpret_cast<s32*>(entry + 0x10) + 1;
					*reinterpret_cast<float*>(entry + 8) =
					    static_cast<float>(
					        -((1.0 / static_cast<double>(*reinterpret_cast<s32*>(entry + 0x14))) *
					              static_cast<double>(*reinterpret_cast<s32*>(entry + 0x10)) -
					          1.0));
					if (static_cast<double>(*reinterpret_cast<float*>(entry + 8)) < 0.0) {
						*reinterpret_cast<float*>(entry + 8) = 0.0f;
					}
				} else {
					doneCount = doneCount + 1;
					*reinterpret_cast<float*>(entry + 8) = 0.0f;
				}
			}
			entry = entry + 0x20;
			remaining = remaining - 1;
		} while (remaining != 0);
	}

	if (list[0] == doneCount) {
		entry = list + 4;
		if (count != 0) {
			u32 blockCount = count >> 3;
			if (blockCount != 0) {
				do {
					entry[0x12] = 0;
					entry[0x13] = 0;
					entry[0x14] = 0;
					entry[0x15] = 1;
					*reinterpret_cast<float*>(entry + 8) = 0.0f;
					entry[0x32] = 0;
					entry[0x33] = 0;
					entry[0x34] = 0;
					entry[0x35] = 1;
					*reinterpret_cast<float*>(entry + 0x28) = 0.0f;
					entry[0x52] = 0;
					entry[0x53] = 0;
					entry[0x54] = 0;
					entry[0x55] = 1;
					*reinterpret_cast<float*>(entry + 0x48) = 0.0f;
					entry[0x72] = 0;
					entry[0x73] = 0;
					entry[0x74] = 0;
					entry[0x75] = 1;
					*reinterpret_cast<float*>(entry + 0x68) = 0.0f;
					entry[0x92] = 0;
					entry[0x93] = 0;
					entry[0x94] = 0;
					entry[0x95] = 1;
					*reinterpret_cast<float*>(entry + 0x88) = 0.0f;
					entry[0xb2] = 0;
					entry[0xb3] = 0;
					entry[0xb4] = 0;
					entry[0xb5] = 1;
					*reinterpret_cast<float*>(entry + 0xa8) = 0.0f;
					entry[0xd2] = 0;
					entry[0xd3] = 0;
					entry[0xd4] = 0;
					entry[0xd5] = 1;
					*reinterpret_cast<float*>(entry + 200) = 0.0f;
					entry[0xf2] = 0;
					entry[0xf3] = 0;
					entry[0xf4] = 0;
					entry[0xf5] = 1;
					*reinterpret_cast<float*>(entry + 0xe8) = 0.0f;
					entry = entry + 0x100;
					blockCount = blockCount - 1;
				} while (blockCount != 0);
				count = count & 7;
				if (count == 0) {
					return 1;
				}
			}
			do {
				entry[0x12] = 0;
				entry[0x13] = 0;
				entry[0x14] = 0;
				entry[0x15] = 1;
				*reinterpret_cast<float*>(entry + 8) = 0.0f;
				entry = entry + 0x20;
				count = count - 1;
			} while (count != 0);
		}
		return 1;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014dd88
 * PAL Size: 5472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdDraw()
{
	u8* self = reinterpret_cast<u8*>(this);
	s16* cmdState = *reinterpret_cast<s16**>(self + 0x82C);
	s16* drawList = *reinterpret_cast<s16**>(self + 0x850);
	const s32 caravanWork = Game.game.m_scriptFoodBase[0];
	s32 caravanIter = caravanWork;
	s16* entry = drawList + 4;
	const s16 cmdMode = *reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + 0x30);
	const s16 animState = *reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + 0x10);
	s32 i;
	s32 helpId = -1;
	bool hasItemHelp = false;

	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	for (i = 0; i < drawList[0]; i++) {
		const s32 tex = *reinterpret_cast<s32*>(entry + 0xE);
		if (tex >= 0) {
			const float x = static_cast<float>(entry[0]);
			const float y = static_cast<float>(entry[1]);
			const float w = static_cast<float>(entry[2]);
			float h = static_cast<float>(entry[3]);
			float t = FLOAT_80332ad0;

			if ((i > 7) || (*reinterpret_cast<s16*>(caravanIter + 0x214) == 0)) {
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
				if ((*reinterpret_cast<s16*>(caravanIter + 0x204) > 1) &&
				    (*reinterpret_cast<s16*>(caravanIter + 0x204) == -1)) {
					t += h;
				}
				if ((animState == 1) && (i < *reinterpret_cast<s16*>(caravanWork + 0xBAA)) &&
				    (i == *reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + 0x26))) {
					t = FLOAT_80332b10;
					h += FLOAT_80332ad0;
				}

				GXColor boxColor;
				boxColor.r = 0xFF;
				boxColor.g = 0xFF;
				boxColor.b = 0xFF;
				boxColor.a = static_cast<u8>(FLOAT_80332acc * *reinterpret_cast<float*>(entry + 8));
				GXSetChanMatColor(GX_COLOR0A0, boxColor);

				DrawRect__8CMenuPcsFUlfffffffff(
				    this, 0, x, y, w, h, *reinterpret_cast<float*>(entry + 4), t,
				    *reinterpret_cast<float*>(entry + 10), *reinterpret_cast<float*>(entry + 10), 0.0f);
			}
		}
		caravanIter += 2;
		entry += 0x20;
	}

	CFont* nameFont = *reinterpret_cast<CFont**>(self + 0x108);
	SetMargin__5CFontFf(FLOAT_80332a70, nameFont);
	SetShadow__5CFontFi(nameFont, 0);
	SetScale__5CFontFf(FLOAT_80332ad8, nameFont);
	DrawInit__5CFontFv(nameFont);

	entry = drawList + 4;
	caravanIter = caravanWork;
	for (i = 0; i < *reinterpret_cast<s16*>(caravanWork + 0xBAA); i++) {
		if ((i > 7) || (*reinterpret_cast<s16*>(caravanIter + 0x214) == 0)) {
			float alpha = *reinterpret_cast<float*>(entry + 8);
			if (cmdMode == 3) {
				alpha = FLOAT_80332a70;
			}

			GXColor textColor;
			textColor.r = 0xFF;
			textColor.g = 0xFF;
			textColor.b = 0xFF;
			textColor.a = static_cast<u8>(FLOAT_80332acc * alpha);
			SetColor__5CFontF8_GXColor(nameFont, &textColor);

			const char* text;
			if (i < 2) {
				text = GetMenuStr__8CMenuPcsFi(this, i + 9);
			} else {
				const s16 cmdId = *reinterpret_cast<s16*>(caravanIter + 0x204);
				if (cmdId < 0) {
					caravanIter += 2;
					entry += 0x20;
					continue;
				}
				const s16 skillId = *reinterpret_cast<s16*>(caravanWork + cmdId * 2 + 0xB6);
				const char** flatText = *reinterpret_cast<const char***>(
				    reinterpret_cast<u8*>(&Game.game.m_cFlatDataArr[1]) + 0x70);
				text = flatText[skillId * 5 + 4];
				if ((cmdMode == 0) && (i == *reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + 0x26))) {
					hasItemHelp = true;
					helpId = skillId;
				}
			}

			const float textW = static_cast<float>(GetWidth__5CFontFPc(nameFont, text));
			const float px = static_cast<float>(entry[0]) + ((static_cast<float>(entry[2]) - textW) * 0.5f);
			const float py = static_cast<float>(entry[1] + 3) - FLOAT_80332ae8;
			SetPosX__5CFontFf(px, nameFont);
			SetPosY__5CFontFf(py, nameFont);
			Draw__5CFontFPc(nameFont, text);
		}
		caravanIter += 2;
		entry += 0x20;
	}

	DrawInit__8CMenuPcsFv(this);
	DrawUniteList();

	entry = drawList + 4;
	caravanIter = caravanWork;
	for (i = 0; i < *reinterpret_cast<s16*>(caravanWork + 0xBAA); i++) {
		if ((i > 1) && (*reinterpret_cast<s16*>(caravanIter + 0x204) >= 0)) {
			DrawSingleIcon__8CMenuPcsFiiifif(
			    this, *reinterpret_cast<s16*>(caravanWork + *reinterpret_cast<s16*>(caravanIter + 0x204) * 2 + 0xB6),
			    entry[0] + entry[2] - 0x10, entry[1] - 1, *reinterpret_cast<float*>(entry + 8), 0, 0.0f);
		}
		caravanIter += 2;
		entry += 0x20;
	}

	if ((cmdMode == 1) && (*reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + 0x12) == 1)) {
		const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const float mark = CalcListPos__8CMenuPcsFiii(this, cmdState[0x1A], letter[0], 1);
		s16* listPos = drawList + drawList[0] * 0x20 + 4;
		if (mark > FLOAT_80332ab0) {
			DrawListPosMark__8CMenuPcsFfff(this, static_cast<float>(listPos[0]), static_cast<float>(listPos[1]), mark);
		}
	}

	if (((cmdMode == 0) && (animState == 1)) ||
	    ((cmdMode != 0) && (*reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + 0x12) == 1))) {
		float cursorX = FLOAT_80332a70;
		float cursorY = FLOAT_80332a70;
		s16* cursorEntry = drawList + 4;

		if ((cmdMode == 0) || (cmdMode == 3)) {
			s32 index = *reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + cmdMode * 2 + 0x26);
			if (*reinterpret_cast<s16*>(caravanWork + index * 2 + 0x214) == 0) {
				cursorEntry = reinterpret_cast<s16*>(*reinterpret_cast<s32*>(self + 0x850) + index * 0x40 + 8);
			} else {
				s32 uniteIdx = 0;
				while ((uniteIdx < DAT_8032eec8) && (s_UniteTop[uniteIdx] != index)) {
					uniteIdx++;
				}
				cursorEntry = reinterpret_cast<s16*>(
				    *reinterpret_cast<s32*>(self + 0x850) +
				    (*reinterpret_cast<s16*>(*reinterpret_cast<s32*>(self + 0x850) + 2) + uniteIdx) * 0x40 + 8);
			}
			cursorX = static_cast<float>(cursorEntry[0] - 0x14);
			cursorY = static_cast<float>(cursorEntry[1]);
			if (cmdMode != 0) {
				cursorY += FLOAT_80332ad0;
			}
		} else if (cmdMode == 1) {
			const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
			s32 idx = 0;
			s16* scan = drawList + drawList[0] * 0x20 + 4;
			while (idx < 8) {
				if (*reinterpret_cast<s32*>(scan + 0xE) == 0x37) {
					break;
				}
				scan += 0x20;
				idx++;
			}
			const s32 cur = cmdState[0x14] + cmdState[0x1A];
			s32 wrapped = cur;
			if (letter[0] <= cur) {
				wrapped -= letter[0];
			}
			scan += wrapped * 0x20;
			cursorX = static_cast<float>(scan[0] - 0x14);
			cursorY = static_cast<float>(scan[1]);
		} else {
			s16* panel = reinterpret_cast<s16*>(
			    *reinterpret_cast<s32*>(self + 0x850) +
			    (*reinterpret_cast<s16*>(*reinterpret_cast<s32*>(self + 0x850) + 2) + 3) * 0x40 + 8);
			const s32 choices = (DOUBLE_80332a58 == static_cast<double>(*reinterpret_cast<float*>(panel + 10))) ? 2 : 3;
			const float pitch = static_cast<float>(
			    ((static_cast<float>(panel[3]) * *reinterpret_cast<float*>(panel + 10)) - DOUBLE_80332b20) /
			    static_cast<float>(choices));
			cursorX = static_cast<float>(panel[0] - 0x14);
			cursorY = ((pitch - static_cast<float>(DOUBLE_80332af8)) * static_cast<float>(DOUBLE_80332a60)) +
			          ((pitch * static_cast<float>(*reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + 0x2A))) +
			           static_cast<float>(panel[1] + 8));
		}

		const s32 frame = System.m_frameCounter & 7;
		DrawCursor__8CMenuPcsFiif(this, static_cast<s32>(cursorX + static_cast<float>(frame)), static_cast<s32>(cursorY),
		                          FLOAT_80332a70);
	}

	if (!hasItemHelp) {
		helpId = -1;
	}
	if ((cmdMode == 0) && (helpId == -1) &&
	    (*reinterpret_cast<s16*>(caravanWork + *reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + 0x26) * 2 + 0x214) == 0)) {
		helpId = 0x266;
	}
	if (cmdMode == 1) {
		const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		s32 idx = cmdState[0x14] + cmdState[0x1A];
		if (letter[0] <= idx) {
			idx -= letter[0];
		}
		if (idx < 2) {
			helpId = idx + 0x259;
		}
	}
	if (cmdMode == 2) {
		if (*reinterpret_cast<s16*>(reinterpret_cast<u8*>(cmdState) + 0x2A) == 0) {
			helpId = 0x25B;
		} else {
			helpId = -1;
		}
	}

	float helpAlpha = *reinterpret_cast<float*>(drawList + drawList[0] * 0x20 + 0xC);
	if ((cmdMode == 0) || (cmdMode == 2)) {
		helpAlpha = *reinterpret_cast<float*>(drawList + 0xC);
	}

	GXColor helpColor;
	helpColor.r = 0xFF;
	helpColor.g = 0xFF;
	helpColor.b = 0xFF;
	helpColor.a = static_cast<u8>(FLOAT_80332acc * helpAlpha);
	DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(
	    this, helpId, *reinterpret_cast<CFont**>(self + 0xF8), 0, static_cast<s32>(-FLOAT_80332b28), helpColor, 0,
	    FLOAT_80332a88, FLOAT_80332b08);
}

/*
 * --INFO--
 * PAL Address: TODO  
 * PAL Size: 2836b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdCtrlCur()
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

	s16* menuState = *reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x82C);
	int mode = menuState[0x18];

	if (mode == 0) {
		s16 cmdCount = *reinterpret_cast<s16*>(caravanWork + 0xBAA);

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (menuState[0x13] < cmdCount - 1) {
					menuState[0x13]++;
				} else {
					menuState[0x13] = 2;
				}

				int cursor = menuState[0x13];
				if (*reinterpret_cast<s16*>(caravanWork + cursor * 2 + 0x214) < 0) {
					if (*reinterpret_cast<s16*>(caravanWork + (cursor + 1) * 2 + 0x214) < 0) {
						if (*reinterpret_cast<s16*>(caravanWork + (cursor + 2) * 2 + 0x214) >= 0) {
							menuState[0x13] = static_cast<s16>(cursor + 2);
						}
					} else {
						menuState[0x13] = static_cast<s16>(cursor + 1);
					}
					if (menuState[0x13] > cmdCount - 1) {
						menuState[0x13] = 2;
					}
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (menuState[0x13] < 3) {
				menuState[0x13] = static_cast<s16>(cmdCount - 1);
			} else {
				menuState[0x13]--;
			}

			int cursor = menuState[0x13];
			if (*reinterpret_cast<s16*>(caravanWork + cursor * 2 + 0x214) < 0) {
				if (*reinterpret_cast<s16*>(caravanWork + (cursor - 1) * 2 + 0x214) < 0) {
					if (*reinterpret_cast<s16*>(caravanWork + (cursor - 2) * 2 + 0x214) >= 0) {
						menuState[0x13] = static_cast<s16>(cursor - 2);
					}
				} else {
					menuState[0x13] = static_cast<s16>(cursor - 1);
				}
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x20) != 0) {
				menuState[0x0F] = 1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x40) != 0) {
				menuState[0x0F] = -1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					*reinterpret_cast<u8*>(menuState + 6) = 1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
					return 1;
				}
			} else {
				if (*reinterpret_cast<s16*>(caravanWork + menuState[0x13] * 2 + 0x214) == 0) {
					menuState[0x18] = 1;
				} else {
					*reinterpret_cast<u8*>(menuState + 6) = 0;
					menuState[0x18] = 2;
				}
				menuState[0x09] = 0;
				menuState[0x11] = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
	} else if (mode == 1) {
		s16* list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int itemCount = static_cast<int>(list[0]);

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (((itemCount < 9) || (menuState[0x14] < 7)) &&
				    ((itemCount <= 8) || ((itemCount - 1) > menuState[0x14]))) {
					if (itemCount < 9) {
						menuState[0x14] = 0;
					} else if (menuState[0x1A] < itemCount - 1) {
						menuState[0x1A]++;
					} else {
						menuState[0x1A] = 0;
					}
				} else {
					menuState[0x14]++;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (menuState[0x14] == 0) {
				if (itemCount < 9) {
					menuState[0x14] = static_cast<s16>(itemCount - 1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else if (menuState[0x1A] == 0) {
					menuState[0x1A] = static_cast<s16>(itemCount - 1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					menuState[0x1A]--;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			} else {
				menuState[0x14]--;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					menuState[0x09]++;
					menuState[0x11] = 0;
					*reinterpret_cast<u8*>(menuState + 4) = 0;
					CmdInit2__8CMenuPcsFv(this);
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			} else {
				int selected = static_cast<int>(menuState[0x1A]) + static_cast<int>(menuState[0x14]);
				if (itemCount <= selected) {
					selected -= itemCount;
				}

				u32 canUse = 0;
				if (selected < 0 || list[0] <= selected) {
					canUse = 0;
				} else if (selected == 0) {
					canUse = static_cast<u32>(*reinterpret_cast<s16*>(caravanWork + menuState[0x13] * 2 + 0x204) >= 0);
				} else if (selected == 1) {
					int combo[5][2];
					canUse = static_cast<u32>(ChkUnite__8CMenuPcsFiPA2_i(this, menuState[0x13], combo) > 0);
				} else {
					canUse = static_cast<u32>(EquipChk__8CMenuPcsFi(this, static_cast<int>(list[selected - 1])) != 0);
				}

				if ((canUse & 0xFF) == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (selected == 0) {
						ChgCmdLst__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), menuState[0x13], -1);
					} else if (selected != 1) {
						ChgCmdLst__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), menuState[0x13], list[selected - 1]);
					}

					*reinterpret_cast<u8*>(menuState + 4) = 0;
					if (selected != 0) {
						int comboChoice[2][2];
						int comboCount = ChkUnite__8CMenuPcsFiPA2_i(this, menuState[0x13], comboChoice);
						if (comboCount == 1) {
							UniteComList__12CCaravanWorkFiii(reinterpret_cast<void*>(caravanWork), comboChoice[0][1], 0, 0);
						} else if (comboCount > 1) {
							*reinterpret_cast<u8*>(menuState + 4) = 1;
						}
					}

					menuState[0x09]++;
					menuState[0x11] = 0;
					CmdInit2__8CMenuPcsFv(this);
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				}
			}
		}
	} else if (mode == 2) {
		int maxPos;
		if (DOUBLE_80332a58 == static_cast<double>(*reinterpret_cast<float*>(
		                         reinterpret_cast<u8*>(*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x850)) +
		                         ((*reinterpret_cast<s16*>(*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x850) + 2) + 3) * 0x40 + 0x1C)))) {
			maxPos = 2;
		} else {
			maxPos = 3;
		}

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (menuState[0x15] < maxPos - 1) {
					menuState[0x15]++;
				} else {
					menuState[0x15] = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (menuState[0x15] == 0) {
				menuState[0x15] = static_cast<s16>(maxPos - 1);
			} else {
				menuState[0x15]--;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			menuState[0x0A] = 0;
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					menuState[0x09]++;
					menuState[0x11] = 0;
					*reinterpret_cast<u8*>(menuState + 4) = 0xFF;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			} else {
				menuState[0x09]++;
				menuState[0x11] = 0;
				*reinterpret_cast<u8*>(menuState + 4) = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
	} else {
		if ((hold & 0xC) != 0) {
			int selected = menuState[0x13];
			int prev = selected - 1;
			int remaining = selected - 3;
			int check = caravanWork + prev * 2;
			if (prev > 2) {
				do {
					if (*reinterpret_cast<s16*>(check + 0x214) >= 0) {
						break;
					}
					check -= 2;
					prev--;
					remaining--;
				} while (remaining != 0);
			}

			int next = selected + 1;
			remaining = *reinterpret_cast<s16*>(caravanWork + 0xBAA) - next;
			check = caravanWork + next * 2;
			if (next < *reinterpret_cast<s16*>(caravanWork + 0xBAA)) {
				do {
					if (*reinterpret_cast<s16*>(check + 0x214) >= 0) {
						break;
					}
					check += 2;
					next++;
					remaining--;
				} while (remaining != 0);
			}

			s16* modeCursor = menuState + mode;
			if (modeCursor[0x13] == prev) {
				modeCursor[0x13] = static_cast<s16>(next);
			} else {
				modeCursor[0x13] = static_cast<s16>(prev);
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			*reinterpret_cast<u8*>(menuState + 4) = 0;
			menuState[0x0A] = 0;
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					*reinterpret_cast<u8*>(menuState + 4) = 0xFF;
					menuState[0x09]++;
					menuState[0x11] = 0;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			} else {
				menuState[0x09]++;
				menuState[0x11] = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014d0c4
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdOpen0()
{
	u8* self = reinterpret_cast<u8*>(this);
	u8* menuState = *reinterpret_cast<u8**>(self + 0x82c);

	*reinterpret_cast<s16*>(menuState + 0x22) = static_cast<s16>(*reinterpret_cast<s16*>(menuState + 0x22) + 1);
	s32 time = static_cast<s32>(*reinterpret_cast<s16*>(menuState + 0x22));
	s32 selectedOffset = static_cast<s32>(*reinterpret_cast<s16*>(menuState + 0x26)) * 0x40 + 8;

	if (time < 5) {
		*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) =
		    static_cast<s16>(*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) - 0x13);
	}

	s16* base = *reinterpret_cast<s16**>(self + 0x850);
	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(base[1]) - static_cast<s32>(base[0]);
	s16* entry = base + base[0] * 0x20 + 4;

	for (s32 i = 0; i < entryCount; i++) {
		if (*reinterpret_cast<s32*>(entry + 0x12) <= time) {
			if (time < (*reinterpret_cast<s32*>(entry + 0x12) + *reinterpret_cast<s32*>(entry + 0x14))) {
				*reinterpret_cast<s32*>(entry + 0x10) = *reinterpret_cast<s32*>(entry + 0x10) + 1;
				const f64 denom = static_cast<f64>(*reinterpret_cast<s32*>(entry + 0x14));
				const f64 numer = static_cast<f64>(*reinterpret_cast<s32*>(entry + 0x10));

				*reinterpret_cast<f32*>(entry + 8) = static_cast<f32>(numer / denom);
				if ((*reinterpret_cast<u32*>(entry + 0x16) & 2) == 0) {
					const f32 t = static_cast<f32>(numer / denom);
					*reinterpret_cast<f32*>(entry + 0x18) =
					    (*reinterpret_cast<f32*>(entry + 0x1c) - static_cast<f32>(entry[0])) * t;
					*reinterpret_cast<f32*>(entry + 0x1a) =
					    (*reinterpret_cast<f32*>(entry + 0x1e) - static_cast<f32>(entry[1])) * t;
				}
			} else {
				doneCount++;
				*reinterpret_cast<f32*>(entry + 8) = 1.0f;
				*reinterpret_cast<f32*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<f32*>(entry + 0x1a) = 0.0f;
			}
		}
		entry += 0x20;
	}

	return static_cast<unsigned int>(entryCount == doneCount);
}

/*
 * --INFO--
 * PAL Address: 0x8014cef8
 * PAL Size: 460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdClose0()
{
	u8* self = reinterpret_cast<u8*>(this);
	u8* menuState = *reinterpret_cast<u8**>(self + 0x82c);

	*reinterpret_cast<s16*>(menuState + 0x22) = static_cast<s16>(*reinterpret_cast<s16*>(menuState + 0x22) + 1);
	s32 time = static_cast<s32>(*reinterpret_cast<s16*>(menuState + 0x22));
	s32 selectedOffset = static_cast<s32>(*reinterpret_cast<s16*>(menuState + 0x26)) * 0x40 + 8;

	if (time > 7) {
		*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) =
		    static_cast<s16>(*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) + 0x13);
	}

	s16* base = *reinterpret_cast<s16**>(self + 0x850);
	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(base[1]) - static_cast<s32>(base[0]);
	s16* entry = base + base[0] * 0x20 + 4;

	for (s32 i = 0; i < entryCount; i++) {
		if (*reinterpret_cast<s32*>(entry + 0x12) <= time) {
			if (time < (*reinterpret_cast<s32*>(entry + 0x12) + *reinterpret_cast<s32*>(entry + 0x14))) {
				*reinterpret_cast<s32*>(entry + 0x10) = *reinterpret_cast<s32*>(entry + 0x10) + 1;
				const f64 denom = static_cast<f64>(*reinterpret_cast<s32*>(entry + 0x14));
				const f64 numer = static_cast<f64>(*reinterpret_cast<s32*>(entry + 0x10));

				*reinterpret_cast<f32*>(entry + 8) = static_cast<f32>(1.0 - (numer / denom));
				if ((*reinterpret_cast<u32*>(entry + 0x16) & 2) == 0) {
					const f32 t = static_cast<f32>(1.0 - (numer / denom));
					*reinterpret_cast<f32*>(entry + 0x18) =
					    (*reinterpret_cast<f32*>(entry + 0x1c) - static_cast<f32>(entry[0])) * t;
					*reinterpret_cast<f32*>(entry + 0x1a) =
					    (*reinterpret_cast<f32*>(entry + 0x1e) - static_cast<f32>(entry[1])) * t;
				}
			} else {
				doneCount++;
				*reinterpret_cast<f32*>(entry + 8) = 0.0f;
				*reinterpret_cast<f32*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<f32*>(entry + 0x1a) = 0.0f;
			}
		}
		entry += 0x20;
	}

	if (entryCount == doneCount) {
		*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) =
		    *reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + 8);
	}

	return static_cast<unsigned int>(entryCount == doneCount);
}

/*
 * --INFO--
 * PAL Address: 0x8014cce0
 * PAL Size: 536b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetCmdItem()
{
	u32 scriptFood = Game.game.m_scriptFoodBase[0];
	s16* list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	s16* write = list;
	s32 count = 0;
	u32 itemIndexPtr = scriptFood + 0xb6;

	for (s32 i = 0; i < 0x40; i++) {
		s32 itemType = GetItemType__8CMenuPcsFii(this, i, 0);
		if ((itemType != 0) && (itemType != 5) && (itemType != 6) && (itemType != 8) && (itemType != 9)) {
			if ((itemType != 1) ||
			    (static_cast<u32>(GetItemIcon__8CMenuPcsFi(this, *reinterpret_cast<s16*>(itemIndexPtr))) ==
			     (*reinterpret_cast<u16*>(scriptFood + 0x3e0) & 3))) {
				write++;
				*write = static_cast<s16>(i);
				count++;
			}
		}
		itemIndexPtr += 2;
	}

	s16* write2 = list + count;
	u32 artifactPtr = scriptFood;
	for (s32 i = 0; i < 0x49; i++) {
		s32 arti = i + 0x9f;
		if (*reinterpret_cast<s16*>(artifactPtr + 0x136) == arti) {
			if ((arti > 0xde) && (arti < 0xe4)) {
				count++;
				write2++;
				*write2 = static_cast<s16>(i + 0x40);
			}
		}
		artifactPtr += 2;
	}

	s16* write3 = list + count;
	if ((*reinterpret_cast<s16*>(scriptFood + 0x1f6) > 0xde) && (*reinterpret_cast<s16*>(scriptFood + 0x1f6) < 0xe4)) {
		count++;
		write3++;
		*write3 = 0xa0;
	}
	if ((*reinterpret_cast<s16*>(scriptFood + 0x1f8) > 0xde) && (*reinterpret_cast<s16*>(scriptFood + 0x1f8) < 0xe4)) {
		count++;
		write3++;
		*write3 = 0xa1;
	}
	if ((*reinterpret_cast<s16*>(scriptFood + 0x1fa) > 0xde) && (*reinterpret_cast<s16*>(scriptFood + 0x1fa) < 0xe4)) {
		count++;
		write3++;
		*write3 = 0xa2;
	}
	if ((*reinterpret_cast<s16*>(scriptFood + 0x1fc) > 0xde) && (*reinterpret_cast<s16*>(scriptFood + 0x1fc) < 0xe4)) {
		count++;
		write3[1] = 0xa3;
	}

	*reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0)) = static_cast<s16>(count + 2);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkCmdActive(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMenuPcs::ChkUnite(int selected, int (*comboOut)[2])
{
	u8* self = reinterpret_cast<u8*>(this);
	const s32 caravanWork = Game.game.m_scriptFoodBase[0];
	s16* const cmd = *reinterpret_cast<s16**>(self + 0x82c);

	int candidates[10];
	int itemKinds[11];
	int matches[10];

	memset(candidates, -1, sizeof(candidates));
	memset(itemKinds, -1, sizeof(itemKinds));
	memset(matches, -1, sizeof(matches));

	if (comboOut != nullptr) {
		for (int i = 0; i < 5; i++) {
			comboOut[i][0] = -1;
			comboOut[i][1] = -1;
		}
	}

	const s16 selectedState = *reinterpret_cast<s16*>(caravanWork + selected * 2 + 0x214);
	const u32 selectedNegMask = static_cast<u32>(-selectedState) & ~static_cast<u32>(selectedState);

	if ((cmd[0x18] == 1) && (cmd[0x09] == 2)) {
		if (selectedState < 0) {
			selected--;
		}
		if (*reinterpret_cast<s16*>(caravanWork + selected * 2 + 0x214) < 0) {
			selected--;
		}
	}

	int write = 2;
	for (int slot = 2; slot < 8;) {
		int nextWrite = write;
		int nextSlot = slot + 1;
		int entryOffset = slot * 2;

		if (slot == selected) {
			if (*reinterpret_cast<s16*>(caravanWork + entryOffset + 0x214) == 0) {
				candidates[write] = 0;
			} else {
				candidates[write] = 0;
				candidates[write + 1] = 0;
				nextWrite = write + 1;
				nextSlot = slot + 2;
				entryOffset += 2;
				if (*reinterpret_cast<s16*>(caravanWork + entryOffset + 0x214) < 0) {
					candidates[write + 2] = 0;
					nextWrite = write + 2;
					entryOffset += 2;
					nextSlot = slot + 3;
				}
			}
		} else {
			const u32 v = static_cast<u32>(*reinterpret_cast<s16*>(caravanWork + entryOffset + 0x214));
			candidates[write] = static_cast<s32>((-v | v) >> 31);
		}

		write = nextWrite + 1;
		slot = nextSlot;
	}

	int index = 2;
	for (int slot = 2; slot < 8; slot++, index++) {
		if (*reinterpret_cast<s16*>(caravanWork + 0xbaa) <= slot) {
			break;
		}
		const s16 itemRef = *reinterpret_cast<s16*>(caravanWork + slot * 2 + 0x204);
		if (itemRef < 0) {
			continue;
		}

		const int itemId = *reinterpret_cast<s16*>(caravanWork + itemRef * 2 + 0xb6);
		const int icon = GetItemIcon__8CMenuPcsFi(this, itemId);

		if ((itemId > 0xde) && (itemId < 0xe4)) {
			if (itemId == 0xdf) {
				itemKinds[index] = 0x100;
			} else if (itemId == 0xe0) {
				itemKinds[index] = 0x101;
			} else if (itemId == 0xe1) {
				itemKinds[index] = 0x102;
			} else if (itemId == 0xe2) {
				itemKinds[index] = 0x105;
			} else {
				itemKinds[index] = 0x107;
			}
		} else if ((icon == 0) || (icon == 1) || (icon == 2) || (icon == 3)) {
			itemKinds[index] = 999;
		} else if ((icon == 0x10) || (icon == 0x11)) {
			itemKinds[index] = itemId;
		}
	}

	int matchCount = 0;
	if (itemKinds[selected] > 0) {
		if ((itemKinds[selected] == 999) && (selected > 2)) {
			int patIdx = 0;
			for (s16* pat = DAT_801de910; pat[1] >= 0; pat += 6, patIdx++) {
				if ((pat[0] == 0) || ((pat[2] == 2) && (static_cast<s32>(selectedNegMask) < 0))) {
					continue;
				}
				int ok = 0;
				for (int k = 0; k < pat[2]; k++) {
					const int slot = selected - (pat[2] - 1 - k);
					if (candidates[slot] != 0) {
						break;
					}
					if (pat[3 + k] == itemKinds[slot]) {
						ok++;
					}
				}
				if (ok == pat[2] - 1) {
					matches[matchCount * 2] = patIdx;
					matches[matchCount * 2 + 1] = selected - (pat[2] - 1);
					matchCount++;
				}
			}
		} else if (static_cast<s32>(selectedNegMask) >= 0) {
			const int baseLen = static_cast<int>(DAT_801de914[0]);
			int start = selected - (baseLen - 1);
			for (int i = 0; i < baseLen; i++, start++) {
				int ok = 0;
				for (int k = 0; k < baseLen; k++) {
					const int slot = i + (selected - ((baseLen - 1) - k));
					if (candidates[slot] != 0) {
						break;
					}
					if (DAT_801de910[3 + k] == itemKinds[slot]) {
						ok++;
					}
				}
				if (ok == baseLen) {
					matches[matchCount * 2] = 0;
					matches[matchCount * 2 + 1] = start;
					matchCount++;
				}
			}
		}

		int group = 1;
		int* matchWrite = matches + matchCount * 2;
		for (s16* pat = DAT_801de91c; pat[1] >= 0; pat += 6, group++) {
			if (((pat[0] != 0) && (itemKinds[selected] == 999) && (selected >= 3)) ||
			    ((pat[2] == 2) && (static_cast<s32>(selectedNegMask) < 0))) {
				continue;
			}

			const int len = static_cast<int>(pat[2]);
			for (int start = 0; start < len; start++) {
				if ((start == 0) && (static_cast<s32>(selectedNegMask) < 0)) {
					start = 1;
				}

				int ok = 0;
				for (int k = 0; k < len; k++) {
					const int slot = start + (selected - ((len - 1) - k));
					if (candidates[slot] != 0) {
						break;
					}
					if (pat[3 + k] == itemKinds[slot]) {
						ok++;
					}
				}

				if (ok == len) {
					matchWrite[0] = group;
					matchWrite[1] = start + (selected - (len - 1));
					matchWrite += 2;
					matchCount++;
				}
			}
		}
	}

	if (comboOut != nullptr) {
		for (int rank = 0; rank < 2; rank++) {
			int (*dst)[2] = comboOut;
			for (int i = 0; i < matchCount; i++) {
				const int* m = &matches[i * 2];
				if (rank + 2 == DAT_801de914[m[0] * 6]) {
					dst[0][0] = m[0];
					dst[0][1] = m[1];
					dst++;
				}
			}
			comboOut = dst;
		}
	}

	return matchCount;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdUnite(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdDismantle(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8014ba20
 * PAL Size: 3228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawUniteList()
{
	// Basic implementation structure for unite list drawing
	int i;
	int j;
	bool isActive = false;
	int itemCount = 0;
	
	// Initialize graphics state
	// GXSetBlendMode operations would go here
	
	// Main processing loop for unite items
	for (i = 0; i < 16; i++) {
		if (itemCount > 0) {
			isActive = true;
		}
		
		// Draw unite list item
		for (j = 0; j < 8; j++) {
			// Item rendering logic
		}
		
		itemCount++;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8014b7ec
 * PAL Size: 564b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::UniteOpenAnim(int topIdx)
{
	s16* const list = *reinterpret_cast<s16**>((u8*)this + 0x850);
	const s32 caravanWork = Game.game.m_scriptFoodBase[0];
	const float baseX = static_cast<float>(static_cast<double>(list[4]) - DOUBLE_80332a80);

	if (DAT_8032eec8 == 0) {
		return 1;
	}

	if (topIdx < 0) {
		s32 finished = 0;
		const float targetX = FLOAT_80332ac8 + baseX;
		for (s32 i = 0; i < DAT_8032eec8; i++) {
			for (s32 j = 0; j < 3; j++) {
				const s32 idx = j + s_UniteTop[i];
				const s32 entry = idx * 0x20 + 4;
				if ((j != 0) && (*reinterpret_cast<s16*>(caravanWork + idx * 2 + 0x214) != -1)) {
					break;
				}

				float value = static_cast<float>(static_cast<double>(list[entry]) - DOUBLE_80332a80);
				value += static_cast<float>(DOUBLE_80332ab8);
				list[entry] = static_cast<s16>(value);

				const float delta = static_cast<float>(static_cast<double>(list[entry]) - DOUBLE_80332a80) - baseX;
				if ((delta > static_cast<float>(DOUBLE_80332ac0)) || (delta < -static_cast<float>(DOUBLE_80332ac0))) {
					list[entry] = static_cast<s16>(targetX);
					if (j == 0) {
						finished++;
					}
				}
			}
		}
		return static_cast<int>(finished == DAT_8032eec8);
	}

	for (s32 i = 0; i < 3; i++) {
		const s32 idx = i + s_UniteTop[topIdx];
		const s32 entry = idx * 0x20 + 4;
		if ((i != 0) && (*reinterpret_cast<s16*>(caravanWork + idx * 2 + 0x214) != -1)) {
			break;
		}

		float value = static_cast<float>(static_cast<double>(list[entry]) - DOUBLE_80332a80);
		value += static_cast<float>(DOUBLE_80332ab8);
		list[entry] = static_cast<s16>(value);

		const float delta = static_cast<float>(static_cast<double>(list[entry]) - DOUBLE_80332a80) - baseX;
		if ((delta > static_cast<float>(DOUBLE_80332ac0)) || (delta < -static_cast<float>(DOUBLE_80332ac0))) {
			list[entry] = static_cast<s16>(FLOAT_80332ac8 + baseX);
			return 1;
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014b5cc
 * PAL Size: 544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::UniteCloseAnim(int topIdx)
{
	s16* const list = *reinterpret_cast<s16**>((u8*)this + 0x850);
	const s32 caravanWork = Game.game.m_scriptFoodBase[0];
	const float baseX = static_cast<float>(static_cast<double>(list[4]) - DOUBLE_80332a80);

	if (DAT_8032eec8 == 0) {
		return 1;
	}

	if (topIdx < 0) {
		s32 finished = 0;
		for (s32 i = 0; i < DAT_8032eec8; i++) {
			for (s32 j = 0; j < 3; j++) {
				const s32 idx = j + s_UniteTop[i];
				const s32 entry = idx * 0x20 + 4;
				if ((j != 0) && (*reinterpret_cast<s16*>(caravanWork + idx * 2 + 0x214) != -1)) {
					break;
				}

				float value = static_cast<float>(static_cast<double>(list[entry]) - DOUBLE_80332a80);
				value -= static_cast<float>(DOUBLE_80332ab8);
				list[entry] = static_cast<s16>(value);

				if (static_cast<float>(static_cast<double>(list[entry]) - DOUBLE_80332a80) <= baseX) {
					list[entry] = static_cast<s16>(baseX);
					if (j == 0) {
						finished++;
					}
				}
			}
		}
		return static_cast<int>(finished == DAT_8032eec8);
	}

	bool finished = false;
	for (s32 i = 0; i < 3; i++) {
		const s32 idx = i + s_UniteTop[topIdx];
		const s32 entry = idx * 0x20 + 4;
		if ((i != 0) && (*reinterpret_cast<s16*>(caravanWork + idx * 2 + 0x214) != -1)) {
			break;
		}

		float value = static_cast<float>(static_cast<double>(list[entry]) - DOUBLE_80332a80);
		value -= static_cast<float>(DOUBLE_80332ab8);
		list[entry] = static_cast<s16>(value);

		if (static_cast<float>(static_cast<double>(list[entry]) - DOUBLE_80332a80) <= baseX) {
			finished = true;
			list[entry] = static_cast<s16>(baseX);
		}
	}

	return static_cast<int>(finished);
}

/*
 * --INFO--
 * PAL Address: 0x8014b244
 * PAL Size: 904b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdOpen1()
{
	u8* self = reinterpret_cast<u8*>(this);
	const s32 caravanWork = Game.game.m_scriptFoodBase[0];
	s16* const cmd = *reinterpret_cast<s16**>(self + 0x82c);
	s16* const list = *reinterpret_cast<s16**>(self + 0x850);

	cmd[0x11] = static_cast<s16>(cmd[0x11] + 1);

	const s32 selected = static_cast<s32>(cmd[0x13]);
	const f32 t = static_cast<f32>(-((DOUBLE_80332a90 * static_cast<f64>(cmd[0x11])) - DOUBLE_80332a58));
	*reinterpret_cast<f32*>(list + selected * 0x20 + 0x0c) = t;

	s32 chainCount = 1;
	if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) == -1) {
		chainCount = 2;
		*reinterpret_cast<f32*>(list + (selected + 1) * 0x20 + 0x0c) = t;
		if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) == -1) {
			chainCount = 3;
			*reinterpret_cast<f32*>(list + (selected + 2) * 0x20 + 0x0c) = t;
		}
	}

	s32 slot = 3;
	for (s32 i = 0; i < 3; i++) {
		if (selected == static_cast<s32>(cmd[0x13 + i])) {
			slot = i;
			break;
		}
	}

	s16* const baseEntry = list + (static_cast<s32>(list[1]) + slot) * 0x20 + 4;
	s16* const animEntry = list + (static_cast<s32>(list[1]) + 3) * 0x20 + 4;

	if (*reinterpret_cast<u8*>(cmd + 6) == 0) {
		const s32 endX = static_cast<s32>(baseEntry[0] + baseEntry[2]) - static_cast<s32>(DOUBLE_80332a98);
		animEntry[0] = static_cast<s16>(endX);

		s32 uniteCount = 0;
		if (chainCount == 2) {
			int combo[5][2];
			uniteCount = ChkUnite__8CMenuPcsFiPA2_i(this, static_cast<int>(cmd[0x13]), combo);
		}

		animEntry[0x0A] = 1.0f;
		if (uniteCount != 0) {
			animEntry[0x0A] = static_cast<f32>(DOUBLE_80332aa0);
		}
		animEntry[2] = 0xC0;
		animEntry[3] = 0x40;
		animEntry[1] = static_cast<s16>(((-((static_cast<f64>(animEntry[3]) * animEntry[0x0A]) -
		                                    static_cast<f64>(baseEntry[3])) *
		                                   DOUBLE_80332a60) +
		                                  static_cast<f64>(baseEntry[1])) -
		                                 DOUBLE_80332aa8);
		animEntry[4] = FLOAT_80332ab0;
		animEntry[6] = FLOAT_80332ab0;
		*reinterpret_cast<s32*>(animEntry + 0x0e) = 0x39;
		*reinterpret_cast<u8*>(cmd + 6) = 1;
	}

	animEntry[8] = static_cast<f32>(DOUBLE_80332a90 * static_cast<f64>(cmd[0x11]));
	if (static_cast<f64>(cmd[0x11]) >= DOUBLE_80332a78) {
		cmd[0x15] = 0;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014ad90
 * PAL Size: 1204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdClose1()
{
	u8* self = reinterpret_cast<u8*>(this);
	s32 caravanWork = Game.game.m_scriptFoodBase[0];
	s32 cmd = *reinterpret_cast<s32*>(self + 0x82c);
	s16* list = *reinterpret_cast<s16**>(self + 0x850);

	*reinterpret_cast<s16*>(cmd + 0x22) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x22) + 1);
	const s16 timer = *reinterpret_cast<s16*>(cmd + 0x22);
	const s16 selected = *reinterpret_cast<s16*>(cmd + 0x26);
	s32 state = *reinterpret_cast<s16*>(cmd + 0x14);
	u32 done = 0;

	if (state == 0) {
		const float t = static_cast<float>(timer) * 0.125f;
		*reinterpret_cast<float*>(list + selected * 0x20 + 0x0c) = t;

		if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) < 0) {
			*reinterpret_cast<float*>(list + (selected + 1) * 0x20 + 0x0c) = t;
			if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) < 0) {
				*reinterpret_cast<float*>(list + (selected + 2) * 0x20 + 0x0c) = t;
			}
		}

		float pos = 1.0f - t;
		if (pos < 0.0f) {
			pos = 0.0f;
		}
		*reinterpret_cast<float*>(list + (static_cast<s32>(list[1]) + 3) * 0x20 + 0x0c) = pos;

		done = static_cast<u32>(static_cast<float>(timer) >= 8.0f);
		if ((done != 0) && (*reinterpret_cast<u8*>(cmd + 8) != 0)) {
			*reinterpret_cast<u8*>(cmd + 8) = 0;
			if (*reinterpret_cast<s16*>(cmd + 0x2a) == 0) {
				*reinterpret_cast<s16*>(cmd + 0x14) = 1;
				done = 0;
			} else if ((static_cast<double>(*reinterpret_cast<float*>(list + (static_cast<s32>(list[1]) + 3) * 0x20 + 0x0d)) ==
			            DOUBLE_80332a58) &&
			           (*reinterpret_cast<s16*>(cmd + 0x2a) == 1)) {
				*reinterpret_cast<s16*>(cmd + 0x14) = 2;
				done = 0;
			}
		}
		if (done != 0) {
			*reinterpret_cast<u8*>(cmd + 8) = 0;
		}
	} else if (state == 1) {
		s32 uniteIdx = 0;
		s32 topCount = static_cast<s32>(list[0]);
		for (; uniteIdx < topCount; uniteIdx++) {
			if (list[uniteIdx * 0x20 + 2] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx) != 0);
		if (done != 0) {
			s32 ununiteCount = 1;
			if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) < 0) {
				ununiteCount = 2;
				if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) < 0) {
					ununiteCount = 3;
				}
			}
			UnuniteComList__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), selected, ununiteCount);
		}
	} else if (state == 2) {
		int combo[2][2];
		const s32 count = ChkUnite__8CMenuPcsFiPA2_i(this, static_cast<int>(selected), combo);
		if (count == 1) {
			done = 0;
			*reinterpret_cast<s16*>(cmd + 0x14) = 3;
		} else {
			done = 1;
			*reinterpret_cast<u8*>(cmd + 8) = 1;
		}
	} else if (state == 3) {
		s32 uniteIdx = 0;
		s32 topCount = static_cast<s32>(list[0]);
		for (; uniteIdx < topCount; uniteIdx++) {
			if (list[uniteIdx * 0x20 + 2] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx) != 0);
		if (done != 0) {
			int combo[2][2];
			ChkUnite__8CMenuPcsFiPA2_i(this, static_cast<int>(selected), combo);

			s32 ununiteCount = 1;
			if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) < 0) {
				ununiteCount = 2;
				if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) < 0) {
					ununiteCount = 3;
				}
			}

			UnuniteComList__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), selected, ununiteCount);
			UniteComList__12CCaravanWorkFiii(reinterpret_cast<void*>(caravanWork), combo[0][1], 0, 0);

			done = 0;
			*reinterpret_cast<s16*>(cmd + 0x26) = static_cast<s16>(combo[0][1]);
			*reinterpret_cast<s16*>(cmd + 0x14) = 4;
		}
	} else if (state == 4) {
		done = static_cast<u32>(UniteOpenAnim__8CMenuPcsFi(this, -1) != 0);
	}

	return done;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdOpen2()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8014a9dc
 * PAL Size: 948b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdClose2()
{
	u8* self = reinterpret_cast<u8*>(this);
	s16* const cmd = *reinterpret_cast<s16**>(self + 0x82c);
	s16* const list = *reinterpret_cast<s16**>(self + 0x850);
	const s32 caravanWork = Game.game.m_scriptFoodBase[0];

	const s32 selected = static_cast<s32>(cmd[0x13]);
	const s32 modeSel = static_cast<s32>(cmd[0x13 + cmd[0x18]]);

	cmd[0x11] = static_cast<s16>(cmd[0x11] + 1);

	switch (cmd[0x0A]) {
	case 0:
		cmd[0x11] = 0;
		if (*reinterpret_cast<s8*>(cmd + 4) < 0) {
			cmd[0x0A] = 3;
		} else if (*reinterpret_cast<s16*>(caravanWork + selected * 2 + 0x214) == 0) {
			cmd[0x0A] = 2;
		} else {
			cmd[0x0A] = 1;
		}
		return 0;
	case 1: {
		s32 uniteIdx = 0;
		for (; uniteIdx < static_cast<s32>(list[0]); uniteIdx++) {
			if (list[uniteIdx * 0x20 + 2] == selected) {
				break;
			}
		}

		if (UniteCloseAnim(uniteIdx) != 0) {
			int combo[2][2];
			ChkUnite__8CMenuPcsFiPA2_i(this, selected, combo);

			s32 comboIdx = 0;
			if (combo[0][1] < combo[1][1]) {
				comboIdx = (combo[0][1] == modeSel) ? 0 : 1;
			} else {
				comboIdx = (combo[1][1] == modeSel) ? 1 : 0;
			}

			s32 ununiteCount = 1;
			if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) == -1) {
				ununiteCount = 2;
				if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) == -1) {
					ununiteCount = 3;
				}
			}

			UnuniteComList__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), selected, ununiteCount);
			UniteComList__12CCaravanWorkFiii(reinterpret_cast<void*>(caravanWork), combo[comboIdx][1], 0, 0);
			cmd[0x13] = static_cast<s16>(combo[comboIdx][1]);
			cmd[0x0A] = 2;
		}
		return 0;
	}
	case 2:
		if (*reinterpret_cast<s16*>(caravanWork + selected * 2 + 0x214) == 0) {
			int combo[2][2];
			ChkUnite__8CMenuPcsFiPA2_i(this, selected, combo);

			s32 comboIdx = 0;
			if (combo[0][1] < combo[1][1]) {
				comboIdx = (combo[0][1] == modeSel) ? 0 : 1;
			} else {
				comboIdx = (combo[1][1] == modeSel) ? 1 : 0;
			}

			UniteComList__12CCaravanWorkFiii(reinterpret_cast<void*>(caravanWork), combo[comboIdx][1], 0, 0);
			cmd[0x13] = static_cast<s16>(combo[comboIdx][1]);
		} else if (UniteOpenAnim__8CMenuPcsFi(this, -1) != 0) {
			cmd[0x0A] = 3;
		}
		return 0;
	case 3:
		for (s32 i = 0; i < static_cast<s32>(list[0]); i++) {
			f32* const xAnim = reinterpret_cast<f32*>(list + i * 0x20 + 0x0c);
			if (static_cast<f64>(*xAnim) < DOUBLE_80332a58) {
				*xAnim = static_cast<f32>((DOUBLE_80332a68 * static_cast<f64>(cmd[0x11])) + DOUBLE_80332a60);
				if (static_cast<f64>(*xAnim) > DOUBLE_80332a58) {
					*xAnim = FLOAT_80332a70;
				}
			}
		}
		return static_cast<u32>(static_cast<f64>(cmd[0x11]) >= DOUBLE_80332a78);
	default:
		return 0;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
const char* CMenuPcs::GetSkillStr(int index)
{
	const s8 languageId = Game.game.m_gameWork.m_languageId;

	if (languageId == '\x03') {
		return PTR_s_Colpo_Fire_80214d50[index];
	}
	if (languageId < 3) {
		if ((languageId != '\x01') && (languageId != '\0')) {
			return PTR_s_Feuer_Hieb_80214d3c[index];
		}
	} else {
		if (languageId == '\x05') {
			return PTR_s_Efecto_Fuego_80214d78[index];
		}
		if (languageId < 5) {
			return PTR_s_Pyro_Frappe_80214d64[index];
		}
	}
	return PTR_s_Flamestrike_80214d28[index];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetFontItem()
{
	// TODO
}
