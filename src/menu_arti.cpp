#include "ffcc/menu_arti.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"

extern double DOUBLE_80332fb0;
extern double DOUBLE_80332fe0;
extern float FLOAT_80332fa8;
extern float FLOAT_80332fac;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiInit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801609d8
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiInit1()
{
	int iVar2;
	float fVar1;
	short* psVar3;
	unsigned int uVar4;
	unsigned int uVar5;
	int* workPtr;

	fVar1 = 0.0f;
	workPtr = (int*)((char*)this + 0x850);

	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x24) = 0x2e;
	*(int*)(iVar2 + 0x2c) = 2;
	*(int*)(iVar2 + 0x30) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 100) = 0x44;
	*(int*)(iVar2 + 0x6c) = 7;
	*(int*)(iVar2 + 0x70) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0xa4) = 0x44;
	*(int*)(iVar2 + 0xac) = 7;
	*(int*)(iVar2 + 0xb0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0xf4) = 2;
	*(int*)(iVar2 + 0xe4) = 0x2e;
	*(int*)(iVar2 + 0xec) = 7;
	*(int*)(iVar2 + 0xf0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x134) = 2;
	*(int*)(iVar2 + 0x124) = 0x37;
	*(int*)(iVar2 + 300) = 0;
	*(int*)(iVar2 + 0x130) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x174) = 2;
	*(int*)(iVar2 + 0x164) = 0x37;
	*(int*)(iVar2 + 0x16c) = 0;
	*(int*)(iVar2 + 0x170) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x1b4) = 2;
	*(int*)(iVar2 + 0x1a4) = 0x37;
	*(int*)(iVar2 + 0x1ac) = 0;
	*(int*)(iVar2 + 0x1b0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 500) = 2;
	*(int*)(iVar2 + 0x1e4) = 0x37;
	*(int*)(iVar2 + 0x1ec) = 0;
	*(int*)(iVar2 + 0x1f0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x234) = 2;
	*(int*)(iVar2 + 0x224) = 0x37;
	*(int*)(iVar2 + 0x22c) = 0;
	*(int*)(iVar2 + 0x230) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x274) = 2;
	*(int*)(iVar2 + 0x264) = 0x37;
	*(int*)(iVar2 + 0x26c) = 0;
	*(int*)(iVar2 + 0x270) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x2b4) = 2;
	*(int*)(iVar2 + 0x2a4) = 0x37;
	*(int*)(iVar2 + 0x2ac) = 0;
	*(int*)(iVar2 + 0x2b0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x2f4) = 2;
	*(int*)(iVar2 + 0x2e4) = 0x37;
	*(int*)(iVar2 + 0x2ec) = 0;
	*(int*)(iVar2 + 0x2f0) = 5;

	uVar4 = (unsigned int)**(short**)workPtr;
	psVar3 = *(short**)workPtr + 4;
	if (0 < (int)uVar4) {
		uVar5 = uVar4 >> 3;
		if (uVar5 != 0) {
			do {
				psVar3[0x10] = 0;
				psVar3[0x11] = 0;
				*(float*)(psVar3 + 8) = fVar1;
				psVar3[0x30] = 0;
				psVar3[0x31] = 0;
				*(float*)(psVar3 + 0x28) = fVar1;
				psVar3[0x50] = 0;
				psVar3[0x51] = 0;
				*(float*)(psVar3 + 0x48) = fVar1;
				psVar3[0x70] = 0;
				psVar3[0x71] = 0;
				*(float*)(psVar3 + 0x68) = fVar1;
				psVar3[0x90] = 0;
				psVar3[0x91] = 0;
				*(float*)(psVar3 + 0x88) = fVar1;
				psVar3[0xb0] = 0;
				psVar3[0xb1] = 0;
				*(float*)(psVar3 + 0xa8) = fVar1;
				psVar3[0xd0] = 0;
				psVar3[0xd1] = 0;
				*(float*)(psVar3 + 200) = fVar1;
				psVar3[0xf0] = 0;
				psVar3[0xf1] = 0;
				*(float*)(psVar3 + 0xe8) = fVar1;
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
			*(float*)(psVar3 + 8) = fVar1;
			psVar3 = psVar3 + 0x20;
			uVar4 = uVar4 - 1;
		} while (uVar4 != 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80160828
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::ArtiOpen()
{
	float fVar1;
	double dVar2;
	double dVar3;
	short* psVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	if (*(char*)(*(int*)((char*)this + 0x82c) + 0xb) == '\0') {
		ArtiInit();
	}

	iVar5 = 0;
	*(short*)(*(int*)((char*)this + 0x82c) + 0x22) = *(short*)(*(int*)((char*)this + 0x82c) + 0x22) + 1;
	iVar6 = (int)**(short**)((char*)this + 0x850);
	psVar4 = *(short**)((char*)this + 0x850) + 4;
	iVar7 = (int)*(short*)(*(int*)((char*)this + 0x82c) + 0x22);
	iVar8 = iVar6;
	if (0 < iVar6) {
		do {
			dVar3 = DOUBLE_80332fe0;
			fVar1 = FLOAT_80332fa8;
			if (*(int*)(psVar4 + 0x12) <= iVar7) {
				if (iVar7 < *(int*)(psVar4 + 0x12) + *(int*)(psVar4 + 0x14)) {
					*(int*)(psVar4 + 0x10) = *(int*)(psVar4 + 0x10) + 1;
					dVar2 = DOUBLE_80332fb0;
					*(float*)(psVar4 + 8) =
					    (float)((DOUBLE_80332fb0 /
					             ((double)(((unsigned int)*(unsigned int*)(psVar4 + 0x14) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
					            ((double)(((unsigned int)*(unsigned int*)(psVar4 + 0x10) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3));
					if ((*(unsigned int*)(psVar4 + 0x16) & 2) == 0) {
						fVar1 = (float)((dVar2 /
						                 ((double)(((unsigned int)*(unsigned int*)(psVar4 + 0x14) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
						                ((double)(((unsigned int)*(unsigned int*)(psVar4 + 0x10) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3));
						*(float*)(psVar4 + 0x18) =
						    (*(float*)(psVar4 + 0x1c) -
						     (float)((double)(((unsigned int)(int)*psVar4 ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
						    fVar1;
						*(float*)(psVar4 + 0x1a) =
						    (*(float*)(psVar4 + 0x1e) -
						     (float)((double)(((unsigned int)(int)psVar4[1] ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
						    fVar1;
					}
				} else {
					iVar5 = iVar5 + 1;
					*(float*)(psVar4 + 8) = FLOAT_80332fac;
					*(float*)(psVar4 + 0x18) = fVar1;
					*(float*)(psVar4 + 0x1a) = fVar1;
				}
			}
			psVar4 = psVar4 + 0x20;
			iVar8 = iVar8 + -1;
		} while (iVar8 != 0);
	}

	return (unsigned int)(iVar6 == iVar5);
}

/*
 * --INFO--
 * PAL Address: 0x801607d4
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ArtiCtrl()
{
	int result;

	*(short*)(*(int*)((char*)this + 0x82c) + 0x32) = *(short*)(*(int*)((char*)this + 0x82c) + 0x30);
	result = ArtiCtrlCur();
	if (result != 0) {
		ArtiInit1();
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x80160658
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::ArtiClose()
{
	float fVar1;
	double dVar2;
	double dVar3;
	int iVar4;
	short* psVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	iVar4 = 0;
	*(short*)(*(int*)((char*)this + 0x82c) + 0x22) = *(short*)(*(int*)((char*)this + 0x82c) + 0x22) + 1;
	iVar6 = (int)**(short**)((char*)this + 0x850);
	psVar5 = *(short**)((char*)this + 0x850) + 4;
	iVar7 = (int)*(short*)(*(int*)((char*)this + 0x82c) + 0x22);
	iVar8 = iVar6;
	if (0 < iVar6) {
		do {
			dVar3 = DOUBLE_80332fe0;
			fVar1 = FLOAT_80332fa8;
			if (*(int*)(psVar5 + 0x12) <= iVar7) {
				if (iVar7 < *(int*)(psVar5 + 0x12) + *(int*)(psVar5 + 0x14)) {
					*(int*)(psVar5 + 0x10) = *(int*)(psVar5 + 0x10) + 1;
					dVar2 = DOUBLE_80332fb0;
					*(float*)(psVar5 + 8) =
					    (float)-((DOUBLE_80332fb0 /
					              ((double)(((unsigned int)*(unsigned int*)(psVar5 + 0x14) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
					             ((double)(((unsigned int)*(unsigned int*)(psVar5 + 0x10) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3) -
					             DOUBLE_80332fb0);
					if ((*(unsigned int*)(psVar5 + 0x16) & 2) == 0) {
						fVar1 = (float)-((dVar2 /
						                  ((double)(((unsigned int)*(unsigned int*)(psVar5 + 0x14) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
						                 ((double)(((unsigned int)*(unsigned int*)(psVar5 + 0x10) ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3) -
						                 dVar2);
						*(float*)(psVar5 + 0x18) =
						    (*(float*)(psVar5 + 0x1c) -
						     (float)((double)(((unsigned int)(int)*psVar5 ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
						    fVar1;
						*(float*)(psVar5 + 0x1a) =
						    (*(float*)(psVar5 + 0x1e) -
						     (float)((double)(((unsigned int)(int)psVar5[1] ^ 0x80000000U) | 0x4330000000000000ULL) - dVar3)) *
						    fVar1;
					}
				} else {
					iVar4 = iVar4 + 1;
					*(float*)(psVar5 + 8) = FLOAT_80332fa8;
					*(float*)(psVar5 + 0x18) = fVar1;
					*(float*)(psVar5 + 0x1a) = fVar1;
				}
			}
			psVar5 = psVar5 + 0x20;
			iVar8 = iVar8 + -1;
		} while (iVar8 != 0);
	}

	return (unsigned int)(iVar6 == iVar4);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiDraw()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8015fa28
 * PAL Size: 812b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ArtiCtrlCur()
{
	short sVar1;
	bool bVar2;
	unsigned short uVar3;
	unsigned short uVar4;
	int iVar5;
	int iVar6;

	bVar2 = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		bVar2 = true;
	}
	if (bVar2) {
		uVar3 = 0;
	} else {
		uVar3 = Pad._8_2_;
	}

	bVar2 = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		bVar2 = true;
	}
	if (bVar2) {
		uVar4 = 0;
	} else {
		uVar4 = *(unsigned short*)((char*)&Pad + 0x20);
	}

	if (uVar4 == 0) {
		return 0;
	}

	iVar5 = *(int*)((char*)this + 0x82c);
	if ((uVar4 & 8) == 0) {
		if ((uVar4 & 4) != 0) {
			iVar6 = iVar5 + *(short*)(iVar5 + 0x30) * 2;
			sVar1 = *(short*)(iVar6 + 0x26);
			if (sVar1 < 7) {
				*(short*)(iVar6 + 0x26) = sVar1 + 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else if ((int)*(short*)(iVar5 + 0x34) + (int)sVar1 < 0x48) {
				*(short*)(iVar5 + 0x34) = *(short*)(iVar5 + 0x34) + 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			}
		}
	} else {
		iVar6 = iVar5 + *(short*)(iVar5 + 0x30) * 2;
		sVar1 = *(short*)(iVar6 + 0x26);
		if (sVar1 == 0) {
			if (*(short*)(iVar5 + 0x34) == 0) {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			} else {
				*(short*)(iVar5 + 0x34) = *(short*)(iVar5 + 0x34) + -1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
		} else {
			*(short*)(iVar6 + 0x26) = sVar1 + -1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}
	}

	if ((uVar4 & 0xc) == 0) {
		if ((uVar3 & 0x20) != 0) {
			*(short*)(*(int*)((char*)this + 0x82c) + 0x1e) = 1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return 1;
		}
		if ((uVar3 & 0x40) != 0) {
			*(short*)(*(int*)((char*)this + 0x82c) + 0x1e) = -1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return 1;
		}
		if ((uVar3 & 0x100) == 0) {
			if ((uVar3 & 0x200) != 0) {
				*(char*)(*(int*)((char*)this + 0x82c) + 0xd) = 1;
				Sound.PlaySe(3, 0x40, 0x7f, 0);
				return 1;
			}
		} else {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		}
	}

	return 0;
}
