#include "ffcc/menu_favo.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

unsigned char s_rank[0x20];

extern float FLOAT_80333040;
extern float FLOAT_80333048;
extern double DOUBLE_80333050;
extern double DOUBLE_80333078;

struct FavoFlatTableEntry
{
	int count;
	const char** strings;
	char* stringBuf;
};

struct FavoFlatData
{
	char pad0[0x6C];
	FavoFlatTableEntry table[8];
};

struct FavoEntry {
	short x;
	short y;
	short w;
	short h;
	float u;
	float v;
	float alpha;
	float uvScale;
	int drawFlags;
	int tex;
	int step;
	int startFrame;
	int duration;
	unsigned int flags;
	float dx;
	float dy;
	float targetX;
	float targetY;
};

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

	uVar3 = Game.m_scriptFoodBase[0];
	memset(favoList, 0, 0x1008);
	fVar4 = 1.0f;
	iVar8 = (int)favoList + 8;
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

	iVar8 = (int)favoList;
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

	iVar8 = (int)favoList;
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

	iVar8 = (int)favoList;
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

	iVar8 = (int)favoList;
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

	iVar8 = (int)favoList;
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

	iVar8 = (int)favoList;
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

	iVar8 = (int)favoList;
	iVar17 = 4;
	do {
		psVar14 = (short*)((int)favoList + iVar16 + 8);
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
		psVar14 = (short*)((int)favoList + iVar15);
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

	*favoList = sVar11;

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

	singMenuState->selectedIndex = 0;
	singMenuState->initialized = 1;
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

	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x2c) = 2;
	*(int *)(iVar2 + 0x30) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x6c) = 2;
	*(int *)(iVar2 + 0x70) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0xac) = 2;
	*(int *)(iVar2 + 0xb0) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0xec) = 7;
	*(int *)(iVar2 + 0xf0) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 300) = 7;
	*(int *)(iVar2 + 0x130) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x174) = 2;
	*(int *)(iVar2 + 0x16c) = 7;
	*(int *)(iVar2 + 0x170) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x1b4) = 2;
	*(int *)(iVar2 + 0x1ac) = 0;
	*(int *)(iVar2 + 0x1b0) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 500) = 2;
	*(int *)(iVar2 + 0x1ec) = 0;
	*(int *)(iVar2 + 0x1f0) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x234) = 2;
	*(int *)(iVar2 + 0x22c) = 0;
	*(int *)(iVar2 + 0x230) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x274) = 2;
	fVar1 = FLOAT_80333048;
	*(int *)(iVar2 + 0x26c) = 0;
	*(int *)(iVar2 + 0x270) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x2b4) = 2;
	*(int *)(iVar2 + 0x2ac) = 0;
	*(int *)(iVar2 + 0x2b0) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x2f4) = 2;
	*(int *)(iVar2 + 0x2ec) = 0;
	*(int *)(iVar2 + 0x2f0) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x334) = 2;
	*(int *)(iVar2 + 0x32c) = 0;
	*(int *)(iVar2 + 0x330) = 5;
	iVar2 = (int)favoList;
	*(int *)(iVar2 + 0x374) = 2;
	*(int *)(iVar2 + 0x36c) = 0;
	*(int *)(iVar2 + 0x370) = 5;
	
	uVar4 = (unsigned int)*favoList;
	psVar3 = favoList + 4;
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
	int finished = 0;

	if (singMenuState->initialized == 0) {
		FavoInit();
	}

	singMenuState->frame++;

	int count = favoList[0];
	FavoEntry* anim = reinterpret_cast<FavoEntry*>((unsigned char*)favoList + 8);
	int frame = singMenuState->frame;

	for (int i = 0; i < count; i++, anim++) {
		float zeroF = FLOAT_80333040;
		if (anim->startFrame <= frame) {
			if (!(frame < anim->startFrame + anim->duration)) {
				finished++;
				anim->alpha = FLOAT_80333048;
				anim->dx = zeroF;
				anim->dy = zeroF;
			} else {
				anim->step++;
				double oneD = DOUBLE_80333050;
				anim->alpha = (float)((DOUBLE_80333050 / (double)anim->duration) * (double)anim->step);
				if ((anim->flags & 2) == 0) {
					float ratio = (float)((oneD / (double)anim->duration) * (double)anim->step);
					anim->dx = (anim->targetX - (float)anim->x) * ratio;
					anim->dy = (anim->targetY - (float)anim->y) * ratio;
				}
			}
		}
	}

	return count == finished;
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
unsigned int CMenuPcs::FavoCtrl()
{
	bool activeInput = false;
	unsigned short press;
	int doReset;

	if (Pad._452_4_ == 0) {
		if (Pad._448_4_ != -1) {
			activeInput = true;
		}
	} else {
		activeInput = true;
	}

	if (activeInput) {
		press = 0;
	} else {
		unsigned int port = 0;

		__cntlzw((unsigned int)Pad._448_4_);
		port &= ~((int)~(Pad._448_4_ - (int)port | (int)port - Pad._448_4_) >> 0x1f);
		press = *(unsigned short*)((unsigned char*)&Pad + port * 0x54 + 8);
	}

	if (press == 0) {
		doReset = 0;
	} else if ((press & 0x20) != 0) {
		singMenuState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else if ((press & 0x40) != 0) {
		singMenuState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else if ((press & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
		doReset = 0;
	} else if ((press & 0x200) != 0) {
		singMenuState->closeRequested = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		doReset = 1;
	} else {
		doReset = 0;
	}

	if (doReset != 0) {
		FavoInit0();
	}

	return doReset;
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
	int finished = 0;
	singMenuState->frame++;

	int count = favoList[0];
	FavoEntry* anim = reinterpret_cast<FavoEntry*>((unsigned char*)favoList + 8);
	int frame = singMenuState->frame;

	for (int i = 0; i < count; i++, anim++) {
		float zeroF = FLOAT_80333040;
		if (anim->startFrame <= frame) {
			if (!(frame < anim->startFrame + anim->duration)) {
				finished++;
				anim->alpha = FLOAT_80333040;
				anim->dx = zeroF;
				anim->dy = zeroF;
			} else {
				anim->step++;
				double oneD = DOUBLE_80333050;
				anim->alpha = (float)-((DOUBLE_80333050 / (double)anim->duration) * (double)anim->step - DOUBLE_80333050);
				if ((anim->flags & 2) == 0) {
					float ratio = (float)-((oneD / (double)anim->duration) * (double)anim->step - oneD);
					anim->dx = (anim->targetX - (float)anim->x) * ratio;
					anim->dy = (anim->targetY - (float)anim->y) * ratio;
				}
			}
		}
	}

	return count == finished;
}

/*
 * --INFO--
 * PAL Address: 0x80162360
 * PAL Size: 2488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::FavoDraw()
{
	_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)5, (_GXLogicOp)1);
	SetAttrFmt((FMT)0);

	FavoEntry* entry = reinterpret_cast<FavoEntry*>((unsigned char*)favoList + 8);
	int count = *favoList;
	for (int i = 0; i < count; i++) {
		int tex = entry->tex;
		if (tex >= 0) {
			float x = (float)entry->x;
			float y = (float)entry->y;
			float w = (float)entry->w;
			float h = (float)entry->h;
			float u = entry->u;
			float v = entry->v;
			float alpha = entry->alpha;
			float uvScale = entry->uvScale;

			if (i < 3) {
				SetAttrFmt((FMT)1);
				SetTexture((TEX)tex);

				GXColor colors[4] = {
					{0xFF, 0xFF, 0xFF, 0xFF},
					{0xFF, 0xFF, 0xFF, 0xFF},
					{0xFF, 0xFF, 0xFF, 0xFF},
					{0xFF, 0xFF, 0xFF, 0xFF},
				};
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);

				float fillW = alpha * w;
				if (fillW > 0.0f) {
					if (tex == 0x32) {
						float xStep = y;
						float end = y + h;
						while (xStep < end) {
							float tile = end - xStep;
							if (tile > 32.0f) {
								tile = 32.0f;
							}
							DrawRect((unsigned long)entry->drawFlags, x, xStep, fillW, tile, u, v, colors, uvScale, 1.0f,
							         0.0f);
							xStep += 32.0f;
						}
					} else {
						DrawRect((unsigned long)entry->drawFlags, x, y, fillW, h, u, v, colors, uvScale, 1.0f, 0.0f);
					}
				}

				if (fillW > 0.0f && fillW < w) {
					GXColor fadeColors[4] = {
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
					};
					float remainW = (48.0f / (float)entry->duration) * w;
					if (tex == 0x32) {
						float xStep = y;
						float end = y + h;
						while (xStep < end) {
							float tile = end - xStep;
							if (tile > 32.0f) {
								tile = 32.0f;
							}
							DrawRect((unsigned long)entry->drawFlags, x + fillW, xStep, remainW, tile, u, v, fadeColors,
							         uvScale, 1.0f, 0.0f);
							xStep += 32.0f;
						}
					} else {
						DrawRect((unsigned long)entry->drawFlags, x + fillW, y, remainW, h, u, v, fadeColors, uvScale,
						         1.0f, 0.0f);
					}
				}

				SetAttrFmt((FMT)0);
			} else {
				SetTexture((TEX)tex);
				GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, 0.0f);
			}
		}
		entry++;
	}

	FavoEntry* rankEntry = reinterpret_cast<FavoEntry*>((unsigned char*)favoList + 8);
	int scanCount = count;
	while (scanCount > 0) {
		if (rankEntry->tex == 0x37) {
			break;
		}
		rankEntry++;
		scanCount--;
	}

	unsigned char* rank = s_rank;
	for (int i = 0; i < 8; i++) {
		int barX = (int)rankEntry->x + rankEntry->w + 0x18;
		int barY = (int)((float)(rankEntry->h - 6) * 0.5f + (float)rankEntry->y);
		DrawSingBar(barX, barY, *(short*)(rank + 2), rankEntry->alpha);
		rank += 4;
		rankEntry++;
	}

	rank = s_rank;
	rankEntry = reinterpret_cast<FavoEntry*>((unsigned char*)favoList + 8);
	while (count > 0) {
		if (rankEntry->tex == 0x37) {
			break;
		}
		rankEntry++;
		count--;
	}

	for (int i = 0; i < 8; i++) {
		int iconX = (int)rankEntry->x + rankEntry->w - 0x10;
		int iconY = (int)((float)(rankEntry->h - 32) * 0.5f + (float)rankEntry->y);
		DrawSingleIcon((int)(rank[1] + 0x14), iconX, iconY, rankEntry->alpha, 1, 1.0f);
		rank += 4;
		rankEntry++;
	}

	CFont* rankFont = font22;
	rankFont->SetShadow(1);
	rankFont->SetScale(1.0f);
	rankFont->DrawInit();

	char textBuf[0x10];
	rank = s_rank;
	rankEntry = reinterpret_cast<FavoEntry*>((unsigned char*)favoList + 8);
	int tmpCount = *favoList;
	while (tmpCount > 0) {
		if (rankEntry->tex == 0x37) {
			break;
		}
		rankEntry++;
		tmpCount--;
	}

	for (int i = 0; i < 8; i++) {
		rankFont->SetTlut(6);
		GXColor textColor = {0xFF, 0xFF, 0xFF, (unsigned char)(255.0f * rankEntry->alpha)};
		rankFont->SetColor(textColor);
		rankFont->SetMargin(1.0f);
		sprintf(textBuf, "%d", (int)rank[0]);
		rankFont->SetPosX((float)rankEntry->x - 12.0f);
		rankFont->SetPosY((float)rankEntry->y);
		rankFont->Draw(textBuf);
		rankFont->SetShadow(0);
		rank += 4;
		rankEntry++;
	}

	CFont* nameFont = font16;
	nameFont->SetShadow(0);
	nameFont->SetScale(0.875f);
	nameFont->SetMargin(1.0f);
	nameFont->DrawInit();

	const FavoFlatData* flatData = (const FavoFlatData*)&Game.m_cFlatDataArr[1];
	rank = s_rank;
	rankEntry = reinterpret_cast<FavoEntry*>((unsigned char*)favoList + 8);
	tmpCount = *favoList;
	while (tmpCount > 0) {
		if (rankEntry->tex == 0x37) {
			break;
		}
		rankEntry++;
		tmpCount--;
	}

	for (int i = 0; i < 8; i++) {
		GXColor textColor = {0xFF, 0xFF, 0xFF, (unsigned char)(255.0f * rankEntry->alpha)};
		nameFont->SetColor(textColor);
		const char* name = flatData->table[0].strings[((char)rank[1] + 0x17D) * 5 + 4];
		nameFont->SetPosX((float)rankEntry->x + 28.0f);
		nameFont->SetPosY((float)rankEntry->y);
		nameFont->Draw((char*)name);
		rank += 4;
		rankEntry++;
	}

	DrawInit();
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
