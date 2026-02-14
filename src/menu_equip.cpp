#include "ffcc/menu_equip.h"

extern float FLOAT_80332eb8;
extern float FLOAT_80332ee0;
extern float FLOAT_80332f10;
extern float FLOAT_80332f14;
extern float FLOAT_80332f18;

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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipClose()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipCtrlCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipOpen0()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipClose0()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkEquipActive(int)
{
	// TODO
}
