#include "ffcc/menu_favo.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>

static unsigned char s_rank[0x20];

/*
 * --INFO--
 * PAL Address: 0x8016343c
 * PAL Size: 1296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::FavoInit()
{
	unsigned char uVar1;
	unsigned char uVar2;
	unsigned int uVar3;
	float fVar4;
	float fVar5;
	float fVar7;
	int iVar8;
	short sVar9;
	short sVar10;
	short sVar11;
	unsigned char* puVar12;
	unsigned char* puVar13;
	short* psVar14;
	int iVar15;
	int iVar16;
	int iVar17;

	uVar3 = Game.game.m_scriptFoodBase[0];
	memset(*(void**)&field_0x850, 0, 0x1008);
	fVar4 = 1.0f;
	iVar8 = *(int*)&field_0x850 + 8;
	iVar16 = 8;
	do {
		*(float*)(iVar8 + 0x14) = fVar4;
		*(float*)(iVar8 + 0x54) = fVar4;
		*(float*)(iVar8 + 0x94) = fVar4;
		*(float*)(iVar8 + 0xd4) = fVar4;
		*(float*)(iVar8 + 0x114) = fVar4;
		*(float*)(iVar8 + 0x154) = fVar4;
		*(float*)(iVar8 + 0x194) = fVar4;
		*(float*)(iVar8 + 0x1d4) = fVar4;
		iVar8 = iVar8 + 0x200;
		iVar16 = iVar16 - 1;
	} while (iVar16 != 0);

	iVar8 = *(int*)&field_0x850;
	*(int*)(iVar8 + 0x24) = 0x33;
	*(int*)(iVar8 + 0x20) = 4;
	*(short*)(iVar8 + 8) = 0x30;
	fVar4 = 0.0f;
	*(short*)(iVar8 + 10) = 0x28;
	fVar5 = 320.0f;
	*(short*)(iVar8 + 0xc) = 0x158;
	*(short*)(iVar8 + 0xe) = 0x20;
	*(float*)(iVar8 + 0x10) = fVar4;
	*(float*)(iVar8 + 0x14) = fVar4;
	*(float*)(iVar8 + 0x1c) = fVar5 / (float)*(short*)(iVar8 + 0xc);
	*(int*)(iVar8 + 0x2c) = 5;
	*(int*)(iVar8 + 0x30) = 5;

	iVar8 = *(int*)&field_0x850;
	*(int*)(iVar8 + 100) = 0x32;
	*(short*)(iVar8 + 0x48) = 0x30;
	*(short*)(iVar8 + 0x4a) = 0x48;
	*(short*)(iVar8 + 0x4c) = 0x158;
	*(short*)(iVar8 + 0x4e) = 200;
	*(float*)(iVar8 + 0x50) = fVar4;
	*(float*)(iVar8 + 0x54) = fVar4;
	*(float*)(iVar8 + 0x5c) = fVar5 / (float)*(short*)(iVar8 + 0x4c);
	*(int*)(iVar8 + 0x6c) = 5;
	*(int*)(iVar8 + 0x70) = 5;

	iVar8 = *(int*)&field_0x850;
	*(int*)(iVar8 + 0xa4) = 0x33;
	*(short*)(iVar8 + 0x88) = 0x30;
	*(short*)(iVar8 + 0x8a) = 0x110;
	*(short*)(iVar8 + 0x8c) = 0x158;
	*(short*)(iVar8 + 0x8e) = 0x20;
	*(float*)(iVar8 + 0x90) = fVar4;
	*(float*)(iVar8 + 0x94) = fVar4;
	*(float*)(iVar8 + 0x9c) = fVar5 / (float)*(short*)(iVar8 + 0x8c);
	*(int*)(iVar8 + 0xac) = 5;
	*(int*)(iVar8 + 0xb0) = 5;

	iVar8 = *(int*)&field_0x850;
	*(int*)(iVar8 + 0xe4) = 0x45;
	fVar5 = 1.0f;
	sVar9 = 0;
	*(short*)(iVar8 + 200) = 0x18;
	fVar7 = 0.5f;
	sVar11 = 6;
	*(short*)(iVar8 + 0xca) = 0xe;
	*(short*)(iVar8 + 0xcc) = 0x30;
	iVar16 = 0x180;
	*(short*)(iVar8 + 0xce) = 0x30;
	*(float*)(iVar8 + 0xd0) = fVar4;
	*(float*)(iVar8 + 0xd4) = fVar4;
	*(float*)(iVar8 + 0xdc) = fVar5;
	*(int*)(iVar8 + 0xec) = 0;
	*(int*)(iVar8 + 0xf0) = 5;

	iVar8 = *(int*)&field_0x850;
	*(int*)(iVar8 + 0x124) = 0x45;
	*(short*)(iVar8 + 0x108) = 0x1d;
	*(short*)(iVar8 + 0x10c) = 0x30;
	*(short*)(iVar8 + 0x10e) = 0x30;
	*(short*)(iVar8 + 0x10a) = 0x150 - *(short*)(iVar8 + 0x10e);
	*(float*)(iVar8 + 0x110) = fVar4;
	*(float*)(iVar8 + 0x114) = fVar4;
	*(float*)(iVar8 + 0x11c) = fVar7;
	*(int*)(iVar8 + 300) = 0;
	*(int*)(iVar8 + 0x130) = 5;

	iVar8 = *(int*)&field_0x850;
	*(int*)(iVar8 + 0x174) = 2;
	*(int*)(iVar8 + 0x164) = 0x2e;
	*(short*)(iVar8 + 0x148) = 0x18;
	*(short*)(iVar8 + 0x14a) = 8;
	*(short*)(iVar8 + 0x14c) = 0x48;
	*(short*)(iVar8 + 0x14e) = 0x140;
	*(float*)(iVar8 + 0x150) = fVar4;
	*(float*)(iVar8 + 0x154) = fVar4;
	*(int*)(iVar8 + 0x16c) = 0;
	*(int*)(iVar8 + 0x170) = 5;

	iVar8 = *(int*)&field_0x850;
	iVar17 = 4;
	do {
		psVar14 = (short*)(*(int*)&field_0x850 + iVar16 + 8);
		psVar14[0x16] = 0;
		psVar14[0x17] = 2;
		psVar14[0xe] = 0;
		psVar14[0xf] = 0x37;
		sVar11 = sVar11 + 2;
		*psVar14 = *(short*)(iVar8 + 8) + 0x28;
		sVar10 = sVar9 + 0x20;
		psVar14[1] = *(short*)(iVar8 + 10) + sVar9;
		psVar14[2] = 200;
		psVar14[3] = 0x28;
		*(float*)(psVar14 + 4) = fVar4;
		*(float*)(psVar14 + 6) = fVar4;
		psVar14[0x12] = 0;
		psVar14[0x13] = 7;
		psVar14[0x14] = 0;
		psVar14[0x15] = 5;

		iVar15 = iVar16 + 0x48;
		iVar16 = iVar16 + 0x80;
		psVar14 = (short*)(*(int*)&field_0x850 + iVar15);
		psVar14[0x16] = 0;
		psVar14[0x17] = 2;
		psVar14[0xe] = 0;
		psVar14[0xf] = 0x37;
		*psVar14 = *(short*)(iVar8 + 8) + 0x28;
		sVar9 = sVar9 + 0x40;
		psVar14[1] = *(short*)(iVar8 + 10) + sVar10;
		psVar14[2] = 200;
		psVar14[3] = 0x28;
		*(float*)(psVar14 + 4) = fVar4;
		*(float*)(psVar14 + 6) = fVar4;
		psVar14[0x12] = 0;
		psVar14[0x13] = 7;
		psVar14[0x14] = 0;
		psVar14[0x15] = 5;
		iVar17 = iVar17 - 1;
	} while (iVar17 != 0);

	**(short**)&field_0x850 = sVar11;

	memset(s_rank, 0, 0x20);
	iVar8 = 0;
	puVar13 = s_rank;
	s_rank[1] = 0;
	*(short*)&s_rank[2] = *(short*)(uVar3 + 0x3b8);
	s_rank[5] = 1;
	*(short*)&s_rank[6] = *(short*)(uVar3 + 0x3ba);
	s_rank[9] = 2;
	*(short*)&s_rank[10] = *(short*)(uVar3 + 0x3bc);
	s_rank[0xd] = 3;
	*(short*)&s_rank[14] = *(short*)(uVar3 + 0x3be);
	s_rank[0x11] = 4;
	*(short*)&s_rank[18] = *(short*)(uVar3 + 0x3c0);
	s_rank[0x15] = 5;
	*(short*)&s_rank[22] = *(short*)(uVar3 + 0x3c2);
	s_rank[0x19] = 6;
	*(short*)&s_rank[26] = *(short*)(uVar3 + 0x3c4);
	s_rank[0x1d] = 7;
	*(short*)&s_rank[30] = *(short*)(uVar3 + 0x3c6);

	do {
		iVar17 = iVar8 + 1;
		iVar16 = 8 - iVar17;
		puVar12 = s_rank + iVar17 * 4;
		if (iVar17 < 8) {
			do {
				sVar9 = *(short*)(puVar13 + 2);
				if (sVar9 < *(short*)(puVar12 + 2)) {
					uVar1 = *puVar13;
					uVar2 = puVar13[1];
					*puVar13 = *puVar12;
					puVar13[1] = puVar12[1];
					*(short*)(puVar13 + 2) = *(short*)(puVar12 + 2);
					*puVar12 = uVar1;
					puVar12[1] = uVar2;
					*(short*)(puVar12 + 2) = sVar9;
				}
				puVar12 = puVar12 + 4;
				iVar16 = iVar16 - 1;
			} while (iVar16 != 0);
		}
		iVar8 = iVar8 + 1;
		puVar13 = puVar13 + 4;
	} while (iVar8 < 8);

	iVar8 = 0;
	iVar17 = 0;
	iVar16 = 8;
	puVar13 = s_rank;
	do {
		if ((iVar17 != 0) && (*(short*)(puVar13 - 2) != *(short*)(puVar13 + 2))) {
			iVar8 = iVar17;
		}
		iVar17 = iVar17 + 1;
		*puVar13 = (char)iVar8 + 1;
		puVar13 = puVar13 + 4;
		iVar16 = iVar16 - 1;
	} while (iVar16 != 0);

	*(short*)(*(int*)((char*)this + 0x82c) + 0x26) = 0;
	*(char*)(*(int*)((char*)this + 0x82c) + 0xb) = 1;
}

/*
 * --INFO--
 * PAL Address: 801631d4
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::FavoInit0()
{
	int iVar2;
	float fVar1;
	short *psVar3;
	unsigned int uVar4;
	unsigned int uVar5;
	
	fVar1 = 0.0f;
	
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x2c) = 2;
	*(int *)(iVar2 + 0x30) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x6c) = 2;
	*(int *)(iVar2 + 0x70) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0xac) = 2;
	*(int *)(iVar2 + 0xb0) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0xec) = 7;
	*(int *)(iVar2 + 0xf0) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 300) = 7;
	*(int *)(iVar2 + 0x130) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x174) = 2;
	*(int *)(iVar2 + 0x16c) = 7;
	*(int *)(iVar2 + 0x170) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x1b4) = 2;
	*(int *)(iVar2 + 0x1ac) = 0;
	*(int *)(iVar2 + 0x1b0) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 500) = 2;
	*(int *)(iVar2 + 0x1ec) = 0;
	*(int *)(iVar2 + 0x1f0) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x234) = 2;
	*(int *)(iVar2 + 0x22c) = 0;
	*(int *)(iVar2 + 0x230) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x274) = 2;
	*(int *)(iVar2 + 0x26c) = 0;
	*(int *)(iVar2 + 0x270) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x2b4) = 2;
	*(int *)(iVar2 + 0x2ac) = 0;
	*(int *)(iVar2 + 0x2b0) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x2f4) = 2;
	*(int *)(iVar2 + 0x2ec) = 0;
	*(int *)(iVar2 + 0x2f0) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x334) = 2;
	*(int *)(iVar2 + 0x32c) = 0;
	*(int *)(iVar2 + 0x330) = 5;
	iVar2 = *(int *)&field_0x850;
	*(int *)(iVar2 + 0x374) = 2;
	*(int *)(iVar2 + 0x36c) = 0;
	*(int *)(iVar2 + 0x370) = 5;
	
	uVar4 = (unsigned int)**(short **)&field_0x850;
	psVar3 = *(short **)&field_0x850 + 4;
	if (0 < (int)uVar4) {
		uVar5 = uVar4 >> 3;
		if (uVar5 != 0) {
			do {
				psVar3[0x10] = 0;
				psVar3[0x11] = 0;
				*(float *)(psVar3 + 8) = fVar1;
				psVar3[0x30] = 0;
				psVar3[0x31] = 0;
				*(float *)(psVar3 + 0x28) = fVar1;
				psVar3[0x50] = 0;
				psVar3[0x51] = 0;
				*(float *)(psVar3 + 0x48) = fVar1;
				psVar3[0x70] = 0;
				psVar3[0x71] = 0;
				*(float *)(psVar3 + 0x68) = fVar1;
				psVar3[0x90] = 0;
				psVar3[0x91] = 0;
				*(float *)(psVar3 + 0x88) = fVar1;
				psVar3[0xb0] = 0;
				psVar3[0xb1] = 0;
				*(float *)(psVar3 + 0xa8) = fVar1;
				psVar3[0xd0] = 0;
				psVar3[0xd1] = 0;
				*(float *)(psVar3 + 200) = fVar1;
				psVar3[0xf0] = 0;
				psVar3[0xf1] = 0;
				*(float *)(psVar3 + 0xe8) = fVar1;
				psVar3 = psVar3 + 0x100;
				uVar5 = uVar5 - 1;
			} while (uVar5 != 0);
			uVar4 = uVar4 & 7;
			if (uVar4 == 0) {
				return;
			}
		}
		do {
			psVar3[0x10] = 0;
			psVar3[0x11] = 0;
			*(float *)(psVar3 + 8) = fVar1;
			psVar3 = psVar3 + 0x20;
			uVar4 = uVar4 - 1;
		} while (uVar4 != 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80163024
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::FavoOpen()
{
	short* psVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	if (*(char*)(*(int*)((char*)this + 0x82c) + 0xb) == 0) {
		FavoInit();
	}

	iVar5 = 0;
	*(short*)(*(int*)((char*)this + 0x82c) + 0x22) = *(short*)(*(int*)((char*)this + 0x82c) + 0x22) + 1;
	iVar6 = (int)**(short**)&field_0x850;
	psVar4 = *(short**)&field_0x850 + 4;
	iVar7 = (int)*(short*)(*(int*)((char*)this + 0x82c) + 0x22);
	iVar8 = iVar6;
	if (0 < iVar6) {
		do {
			if (*(int*)(psVar4 + 0x12) <= iVar7) {
				if (iVar7 < *(int*)(psVar4 + 0x12) + *(int*)(psVar4 + 0x14)) {
					*(int*)(psVar4 + 0x10) = *(int*)(psVar4 + 0x10) + 1;
					*(float*)(psVar4 + 8) = (float)*(int*)(psVar4 + 0x10) / (float)*(int*)(psVar4 + 0x14);
					if ((*(unsigned int*)(psVar4 + 0x16) & 2) == 0) {
						float fVar1 = (float)*(int*)(psVar4 + 0x10) / (float)*(int*)(psVar4 + 0x14);
						*(float*)(psVar4 + 0x18) = (*(float*)(psVar4 + 0x1c) - (float)psVar4[0]) * fVar1;
						*(float*)(psVar4 + 0x1a) = (*(float*)(psVar4 + 0x1e) - (float)psVar4[1]) * fVar1;
					}
				} else {
					iVar5 = iVar5 + 1;
					*(float*)(psVar4 + 8) = 1.0f;
					*(float*)(psVar4 + 0x18) = 0.0f;
					*(float*)(psVar4 + 0x1a) = 0.0f;
				}
			}
			psVar4 = psVar4 + 0x20;
			iVar8 = iVar8 + -1;
		} while (iVar8 != 0);
	}

	return iVar6 == iVar5;
}

/*
 * --INFO--
 * PAL Address: 0x80162e94
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::FavoCtrl()
{
	bool activeInput = false;
	unsigned short press;
	bool doReset;

	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		press = 0;
	} else {
		press = Pad._8_2_;
	}

	doReset = false;
	if (press != 0) {
		if ((press & 0x20) != 0) {
			*(short *)(*(int *)((char *)this + 0x82c) + 0x1e) = 1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			doReset = true;
		} else if ((press & 0x40) != 0) {
			*(short *)(*(int *)((char *)this + 0x82c) + 0x1e) = -1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			doReset = true;
		} else if ((press & 0x100) != 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else if ((press & 0x200) != 0) {
			*(char *)(*(int *)((char *)this + 0x82c) + 0xd) = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			doReset = true;
		}
	}

	if (doReset) {
		FavoInit0();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80162d18
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::FavoClose()
{
	short* psVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	iVar5 = 0;
	*(short*)(*(int*)((char*)this + 0x82c) + 0x22) = *(short*)(*(int*)((char*)this + 0x82c) + 0x22) + 1;
	iVar6 = (int)**(short**)&field_0x850;
	psVar4 = *(short**)&field_0x850 + 4;
	iVar7 = (int)*(short*)(*(int*)((char*)this + 0x82c) + 0x22);
	iVar8 = iVar6;
	if (0 < iVar6) {
		do {
			if (*(int*)(psVar4 + 0x12) <= iVar7) {
				if (iVar7 < *(int*)(psVar4 + 0x12) + *(int*)(psVar4 + 0x14)) {
					float fVar1;

					*(int*)(psVar4 + 0x10) = *(int*)(psVar4 + 0x10) + 1;
					fVar1 = 1.0f - (float)*(int*)(psVar4 + 0x10) / (float)*(int*)(psVar4 + 0x14);
					*(float*)(psVar4 + 8) = fVar1;
					if ((*(unsigned int*)(psVar4 + 0x16) & 2) == 0) {
						*(float*)(psVar4 + 0x18) = (*(float*)(psVar4 + 0x1c) - (float)psVar4[0]) * fVar1;
						*(float*)(psVar4 + 0x1a) = (*(float*)(psVar4 + 0x1e) - (float)psVar4[1]) * fVar1;
					}
				} else {
					iVar5 = iVar5 + 1;
					*(float*)(psVar4 + 8) = 0.0f;
					*(float*)(psVar4 + 0x18) = 0.0f;
					*(float*)(psVar4 + 0x1a) = 0.0f;
				}
			}
			psVar4 = psVar4 + 0x20;
			iVar8 = iVar8 + -1;
		} while (iVar8 != 0);
	}

	return iVar6 == iVar5;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::FavoDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::FavoCtrlCur()
{
	// TODO
}
