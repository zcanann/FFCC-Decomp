#include "ffcc/menu_favo.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::FavoInit()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::FavoClose()
{
	// TODO
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
