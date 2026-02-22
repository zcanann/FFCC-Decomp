#include "ffcc/menu_tmparti.h"
#include "ffcc/fontman.h"
#include "ffcc/sound.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include <string.h>

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" int __cntlzw(unsigned int);

extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);

extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" int GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);

struct TmpArtiTableEntry {
    int count;
    const char** strings;
    char* stringBuf;
};

struct TmpArtiFlatData {
    char pad0[0x6C];
    TmpArtiTableEntry table[8];
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::TmpArtiInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::TmpArtiInit0()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8015e04c
 * PAL Size: 816b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::TmpArtiOpen()
{
	double dVar1;
	float fVar2;
	float fVar3;
	double dVar4;
	double dVar5;
	int iVar6;
	short *psVar7;
	unsigned int uVar8;
	unsigned short *puVar9;
	int iVar10;
	unsigned int uVar11;

	if (*(char *)(*(int *)((char *)this + 0x82c) + 0xb) == '\0') {
		memset(*(void **)((char *)this + 0x850), 0, 0x1008);
		fVar3 = 1.0f;
		iVar6 = *(int *)((char *)this + 0x850) + 8;
		iVar10 = 8;
		do {
			*(float *)(iVar6 + 0x14) = fVar3;
			*(float *)(iVar6 + 0x54) = fVar3;
			*(float *)(iVar6 + 0x94) = fVar3;
			*(float *)(iVar6 + 0xd4) = fVar3;
			*(float *)(iVar6 + 0x114) = fVar3;
			*(float *)(iVar6 + 0x154) = fVar3;
			*(float *)(iVar6 + 0x194) = fVar3;
			*(float *)(iVar6 + 0x1d4) = fVar3;
			dVar5 = 2.0;
			dVar4 = 4607182418800017408.0;
			fVar2 = 0.0f;
			dVar1 = 4602678819172646912.0;
			iVar6 = iVar6 + 0x200;
			iVar10 = iVar10 - 1;
		} while (iVar10 != 0);
		iVar6 = 0;
		puVar9 = (unsigned short *)(*(int *)((char *)this + 0x850) + 8);
		iVar10 = 2;
		do {
			*(unsigned int *)(puVar9 + 0xe) = 0x37;
			puVar9[2] = 200;
			puVar9[3] = 0x28;
			*puVar9 = (short)(int)-(((double)((unsigned int)(short)puVar9[2] ^ 0x80000000 | 0x4330000000000000) - dVar4) * dVar1 - dVar5);
			puVar9[1] = (short)iVar6 * (puVar9[3] + -8) + 0x60;
			*(float *)(puVar9 + 4) = fVar2;
			*(float *)(puVar9 + 6) = fVar2;
			*(int *)(puVar9 + 0x12) = iVar6;
			*(unsigned int *)(puVar9 + 0x14) = 3;
			*(unsigned int *)(puVar9 + 0x2e) = 0x37;
			puVar9[0x22] = 200;
			puVar9[0x23] = 0x28;
			puVar9[0x20] = (short)(int)-(((double)((unsigned int)(short)puVar9[0x22] ^ 0x80000000 | 0x4330000000000000) - dVar4) * dVar1 - dVar5);
			puVar9[0x21] = (short)(iVar6 + 1) * (puVar9[0x23] + -8) + 0x60;
			*(float *)(puVar9 + 0x24) = fVar2;
			*(float *)(puVar9 + 0x26) = fVar2;
			*(int *)(puVar9 + 0x32) = iVar6 + 1;
			iVar6 = iVar6 + 2;
			*(unsigned int *)(puVar9 + 0x34) = 3;
			puVar9 = puVar9 + 0x40;
			iVar10 = iVar10 - 1;
		} while (iVar10 != 0);
		**(unsigned short **)((char *)this + 0x850) = 4;
		*(unsigned short *)(*(int *)((char *)this + 0x82c) + 0x26) = 0;
		*(unsigned char *)(*(int *)((char *)this + 0x82c) + 0xb) = 1;
	}
	iVar6 = 0;
	*(short *)(*(int *)((char *)this + 0x82c) + 0x22) = *(short *)(*(int *)((char *)this + 0x82c) + 0x22) + 1;
	uVar8 = (unsigned int)**(short **)((char *)this + 0x850);
	psVar7 = *(short **)((char *)this + 0x850) + 4;
	iVar10 = (int)*(short *)(*(int *)((char *)this + 0x82c) + 0x22);
	uVar11 = uVar8;
	if (0 < (int)uVar8) {
		do {
			dVar1 = 4607182418800017408.0;
			if (*(int *)(psVar7 + 0x12) <= iVar10) {
				if (iVar10 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
					*(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
					*(float *)(psVar7 + 8) = (float)((1.0 / 
						((double)((unsigned int)*(unsigned int *)(psVar7 + 0x14) ^ 0x80000000 | 0x4330000000000000) - dVar1)) *
						((double)((unsigned int)*(unsigned int *)(psVar7 + 0x10) ^ 0x80000000 | 0x4330000000000000) - dVar1));
				} else {
					iVar6 = iVar6 + 1;
					*(float *)(psVar7 + 8) = 1.0f;
				}
			}
			psVar7 = psVar7 + 0x20;
			uVar11 = uVar11 - 1;
		} while (uVar11 != 0);
	}
	fVar3 = 1.0f;
	if (**(short **)((char *)this + 0x850) == iVar6) {
		psVar7 = *(short **)((char *)this + 0x850) + 4;
		if (0 < (int)uVar8) {
			uVar11 = uVar8 >> 3;
			if (uVar11 != 0) {
				do {
					psVar7[0x12] = 0;
					psVar7[0x13] = 0;
					psVar7[0x14] = 0;
					psVar7[0x15] = 1;
					*(float *)(psVar7 + 8) = fVar3;
					psVar7[0x32] = 0;
					psVar7[0x33] = 0;
					psVar7[0x34] = 0;
					psVar7[0x35] = 1;
					*(float *)(psVar7 + 0x28) = fVar3;
					psVar7[0x52] = 0;
					psVar7[0x53] = 0;
					psVar7[0x54] = 0;
					psVar7[0x55] = 1;
					*(float *)(psVar7 + 0x48) = fVar3;
					psVar7[0x72] = 0;
					psVar7[0x73] = 0;
					psVar7[0x74] = 0;
					psVar7[0x75] = 1;
					*(float *)(psVar7 + 0x68) = fVar3;
					psVar7[0x92] = 0;
					psVar7[0x93] = 0;
					psVar7[0x94] = 0;
					psVar7[0x95] = 1;
					*(float *)(psVar7 + 0x88) = fVar3;
					psVar7[0xb2] = 0;
					psVar7[0xb3] = 0;
					psVar7[0xb4] = 0;
					psVar7[0xb5] = 1;
					*(float *)(psVar7 + 0xa8) = fVar3;
					psVar7[0xd2] = 0;
					psVar7[0xd3] = 0;
					psVar7[0xd4] = 0;
					psVar7[0xd5] = 1;
					*(float *)(psVar7 + 200) = fVar3;
					psVar7[0xf2] = 0;
					psVar7[0xf3] = 0;
					psVar7[0xf4] = 0;
					psVar7[0xf5] = 1;
					*(float *)(psVar7 + 0xe8) = fVar3;
					psVar7 = psVar7 + 0x100;
					uVar11 = uVar11 - 1;
				} while (uVar11 != 0);
				uVar8 = uVar8 & 7;
				if (uVar8 == 0) {
					return 1;
				}
			}
			do {
				psVar7[0x12] = 0;
				psVar7[0x13] = 0;
				psVar7[0x14] = 0;
				psVar7[0x15] = 1;
				*(float *)(psVar7 + 8) = fVar3;
				psVar7 = psVar7 + 0x20;
				uVar8 = uVar8 - 1;
			} while (uVar8 != 0);
		}
		return 1;
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8015dd64
 * PAL Size: 744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::TmpArtiCtrl()
{
	bool hasInput;
	float fVar2;
	unsigned short uVar3;
	unsigned int uVar4;
	unsigned int uVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	unsigned int uVar9;

	hasInput = false;
	*(short *)(*(int *)((char *)this + 0x82c) + 0x32) = *(short *)(*(int *)((char *)this + 0x82c) + 0x30);
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		hasInput = true;
	}

	if (hasInput) {
		uVar3 = 0;
	} else {
		__cntlzw((unsigned int)Pad._448_4_);
		uVar3 = Pad._8_2_;
	}

	if (uVar3 == 0) {
		hasInput = false;
	} else if ((uVar3 & 0x20) != 0) {
		*(short *)(*(int *)((char *)this + 0x82c) + 0x1e) = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		hasInput = true;
	} else if ((uVar3 & 0x40) != 0) {
		*(short *)(*(int *)((char *)this + 0x82c) + 0x1e) = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		hasInput = true;
	} else if ((uVar3 & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
		hasInput = false;
	} else if ((uVar3 & 0x200) != 0) {
		*(unsigned char *)(*(int *)((char *)this + 0x82c) + 0xd) = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		hasInput = true;
	} else {
		hasInput = false;
	}

	fVar2 = 1.0f;
	uVar4 = Game.game.m_scriptFoodBase[0];
	if (hasInput) {
		iVar6 = *(int *)((char *)this + 0x850) + 8;
		for (iVar7 = 0; iVar7 < **(short **)((char *)this + 0x850); iVar7 = iVar7 + 1) {
			*(float *)(iVar6 + 0x10) = fVar2;
			*(float *)(iVar6 + 0x14) = fVar2;
			iVar6 = iVar6 + 0x40;
		}

		uVar5 = (unsigned int)*(short *)(uVar4 + 0xbaa);
		iVar7 = 0;
		iVar6 = (uVar5 - 1) * 0x40;
		if (-1 < (int)(uVar5 - 1)) {
			uVar9 = uVar5 >> 3;
			if (uVar9 != 0) {
				do {
					iVar8 = *(int *)((char *)this + 0x850) + iVar6 + 8;
					*(int *)(iVar8 + 0x24) = iVar7;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = *(int *)((char *)this + 0x850) + iVar6 + -0x38;
					*(int *)(iVar8 + 0x24) = iVar7 + 1;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = *(int *)((char *)this + 0x850) + iVar6 + -0x78;
					*(int *)(iVar8 + 0x24) = iVar7 + 2;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = *(int *)((char *)this + 0x850) + iVar6 + -0xb8;
					*(int *)(iVar8 + 0x24) = iVar7 + 3;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = *(int *)((char *)this + 0x850) + iVar6 + -0xf8;
					*(int *)(iVar8 + 0x24) = iVar7 + 4;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = *(int *)((char *)this + 0x850) + iVar6 + -0x138;
					*(int *)(iVar8 + 0x24) = iVar7 + 5;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = *(int *)((char *)this + 0x850) + iVar6 + -0x178;
					*(int *)(iVar8 + 0x24) = iVar7 + 6;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = iVar6 + -0x1b8;
					iVar6 = iVar6 + -0x200;
					iVar8 = *(int *)((char *)this + 0x850) + iVar8;
					*(int *)(iVar8 + 0x24) = iVar7 + 7;
					iVar7 = iVar7 + 8;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					uVar9 = uVar9 - 1;
				} while (uVar9 != 0);
				uVar5 = uVar5 & 7;
				if (uVar5 == 0) {
					return;
				}
			}
			do {
				iVar8 = iVar6 + 8;
				iVar6 = iVar6 + -0x40;
				iVar8 = *(int *)((char *)this + 0x850) + iVar8;
				*(int *)(iVar8 + 0x24) = iVar7;
				iVar7 = iVar7 + 1;
				*(unsigned int *)(iVar8 + 0x28) = 3;
				uVar5 = uVar5 - 1;
			} while (uVar5 != 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015dbb8
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::TmpArtiClose()
{
	float fVar1;
	double dVar2;
	short *psVar4;
	int iVar5;
	unsigned int uVar6;
	int iVar7;
	unsigned int uVar8;
	
	iVar5 = 0;
	*(short *)(*(int *)((char *)this + 0x82c) + 0x22) = *(short *)(*(int *)((char *)this + 0x82c) + 0x22) + 1;
	uVar6 = (unsigned int)**(short **)((char *)this + 0x850);
	psVar4 = *(short **)((char *)this + 0x850) + 4;
	iVar7 = (int)*(short *)(*(int *)((char *)this + 0x82c) + 0x22);
	uVar8 = uVar6;
	
	if (0 < (int)uVar6) {
		do {
			dVar2 = 1.0;
			if (*(int *)(psVar4 + 0x12) <= iVar7) {
				if (iVar7 < *(int *)(psVar4 + 0x12) + *(int *)(psVar4 + 0x14)) {
					*(int *)(psVar4 + 0x10) = *(int *)(psVar4 + 0x10) + 1;
					*(float *)(psVar4 + 8) =
					    (float)-(1.0 / ((double)(unsigned int)*(unsigned int *)(psVar4 + 0x14) - dVar2) *
					            ((double)(unsigned int)*(unsigned int *)(psVar4 + 0x10) - dVar2) -
					            1.0);
					if (*(float *)(psVar4 + 8) < 0.0f) {
						*(float *)(psVar4 + 8) = 0.0f;
					}
				}
				else {
					iVar5 = iVar5 + 1;
					*(float *)(psVar4 + 8) = 0.0f;
				}
			}
			psVar4 = psVar4 + 0x20;
			uVar8 = uVar8 - 1;
		} while (uVar8 != 0);
	}
	
	fVar1 = 0.0f;
	if (**(short **)((char *)this + 0x850) == iVar5) {
		psVar4 = *(short **)((char *)this + 0x850) + 4;
		if (0 < (int)uVar6) {
			uVar8 = uVar6 >> 3;
			if (uVar8 != 0) {
				do {
					*(int *)(psVar4 + 0x12) = 0;
					*(int *)(psVar4 + 0x14) = 1;
					*(float *)(psVar4 + 8) = fVar1;
					*(int *)(psVar4 + 0x32) = 0;
					*(int *)(psVar4 + 0x34) = 1;
					*(float *)(psVar4 + 0x28) = fVar1;
					*(int *)(psVar4 + 0x52) = 0;
					*(int *)(psVar4 + 0x54) = 1;
					*(float *)(psVar4 + 0x48) = fVar1;
					*(int *)(psVar4 + 0x72) = 0;
					*(int *)(psVar4 + 0x74) = 1;
					*(float *)(psVar4 + 0x68) = fVar1;
					*(int *)(psVar4 + 0x92) = 0;
					*(int *)(psVar4 + 0x94) = 1;
					*(float *)(psVar4 + 0x88) = fVar1;
					*(int *)(psVar4 + 0xb2) = 0;
					*(int *)(psVar4 + 0xb4) = 1;
					*(float *)(psVar4 + 0xa8) = fVar1;
					*(int *)(psVar4 + 0xd2) = 0;
					*(int *)(psVar4 + 0xd4) = 1;
					*(float *)(psVar4 + 200) = fVar1;
					*(int *)(psVar4 + 0xf2) = 0;
					*(int *)(psVar4 + 0xf4) = 1;
					*(float *)(psVar4 + 0xe8) = fVar1;
					psVar4 = psVar4 + 0x100;
					uVar8 = uVar8 - 1;
				} while (uVar8 != 0);
				uVar6 = uVar6 & 7;
				if (uVar6 == 0) {
					return 1;
				}
			}
			do {
				*(int *)(psVar4 + 0x12) = 0;
				*(int *)(psVar4 + 0x14) = 1;
				*(float *)(psVar4 + 8) = fVar1;
				psVar4 = psVar4 + 0x20;
				uVar6 = uVar6 - 1;
			} while (uVar6 != 0);
		}
		return 1;
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8015d798
 * PAL Size: 1056b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::TmpArtiDraw()
{
	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	unsigned int scriptFood = Game.game.m_scriptFoodBase[0];
	short* entry = (short*)(*(int*)((char*)this + 0x850) + 8);
	unsigned int foodPtr = scriptFood;

	for (int i = 0; i < **(short**)((char*)this + 0x850); i++) {
		int tex = *(int*)(entry + 0xE);
		if (-1 < tex) {
			float alpha = *(float*)(entry + 8);
			float left = (float)entry[0];
			float top = (float)entry[1];
			float width = (float)entry[2];
			float height = (float)entry[3];
			float s = *(float*)(entry + 4);
			float t = *(float*)(entry + 6);
			float z = *(float*)(entry + 10);

			if (*(short*)(foodPtr + 0x1F6) < 0) {
				tex = 0x34;
				alpha = 0.5f * alpha;
			}

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);

			GXColor color;
			color.r = 0xFF;
			color.g = 0xFF;
			color.b = 0xFF;
			color.a = (unsigned char)(int)(255.0f * alpha);
			GXSetChanMatColor(GX_COLOR0A0, color);

			DrawRect__8CMenuPcsFUlfffffffff(this, 0, left, top, width, height, s, t, z, z, 0.0f);
		}
		foodPtr += 2;
		entry += 0x20;
	}

	entry = *(short**)((char*)this + 0x850) + 4;
	foodPtr = scriptFood;
	for (int i = 0; i < 4; i++) {
		short icon = *(short*)(foodPtr + 0x1F6);
		if (-1 < icon) {
			int posX = (int)entry[0] + (int)entry[2] - 0x10;
			int posY = (int)(((float)((int)entry[1] + 6)) - 1.0f);
			DrawSingleIcon__8CMenuPcsFiiifif(this, icon, posX, posY, *(float*)(entry + 8), 0, 0.0f);
		}
		entry += 0x20;
		foodPtr += 2;
	}

	CFont* font = *(CFont**)((char*)this + 0x108);
	SetMargin__5CFontFf(1.0f, font);
	SetShadow__5CFontFi(font, 0);
	SetScale__5CFontFf(1.0f, font);
	DrawInit__5CFontFv(font);

	const TmpArtiFlatData* flatData = (const TmpArtiFlatData*)&Game.game.m_cFlatDataArr[1];
	entry = (short*)(*(int*)((char*)this + 0x850) + 8);
	foodPtr = scriptFood;
	for (int i = 0; i < 4; i++) {
		short itemId = *(short*)(foodPtr + 0x1F6);
		if (-1 < itemId) {
			float alpha = *(float*)(entry + 8);
			GXColor textColor = { 0xFF, 0xFF, 0xFF, (unsigned char)(int)(255.0f * alpha) };
			SetColor__5CFontF8_GXColor(font, &textColor);

			const char* text = flatData->table[0].strings[itemId * 5 + 4];
			int width = GetWidth__5CFontFPc(font, text);
			float posX = ((((float)entry[2] - (float)width) * 0.5f) + (float)entry[0]);
			float posY = ((float)((int)entry[1] + 11)) - 1.0f;

			SetPosX__5CFontFf(posX, font);
			SetPosY__5CFontFf(posY, font);
			Draw__5CFontFPc(font, text);
		}
		entry += 0x20;
		foodPtr += 2;
	}

	DrawInit__8CMenuPcsFv(this);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::TmpArtiCtrlCur()
{
	// TODO
}
