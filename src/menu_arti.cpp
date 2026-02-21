#include "ffcc/menu_arti.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

typedef signed short s16;
typedef unsigned char u8;

extern double DOUBLE_80332fb0;
extern double DOUBLE_80332fb8;
extern double DOUBLE_80332fe0;
extern float FLOAT_80332fa8;
extern float FLOAT_80332fac;
extern float FLOAT_80332fc0;
extern float FLOAT_80332fc4;
extern float FLOAT_80332fc8;
extern float FLOAT_80332fcc;
extern float FLOAT_80332fd0;
extern float FLOAT_80332fd4;
extern float FLOAT_80332fd8;
extern float FLOAT_80332fe8;
extern float FLOAT_80332fec;
extern float FLOAT_80332ff0;

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(CMenuPcs*, unsigned long, float, float, float, float, float, float, GXColor*, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" float CalcListPos__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void DrawListPosMark__8CMenuPcsFfff(CMenuPcs*, float, float, float);
extern "C" void DrawCursor__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" void DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(CMenuPcs*, int, CFont*, int, int, GXColor, int, float, float);
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

struct ArtiFlatTableEntry
{
	int count;
	const char** strings;
	char* stringBuf;
};

struct ArtiFlatData
{
	char pad0[0x6C];
	ArtiFlatTableEntry table[8];
};

struct ArtiOpenAnim {
	s16 x;
	s16 y;
	s16 w;
	s16 h;
	float u;
	float v;
	float alpha;
	float scale;
	int stepMax;
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

static inline double IntToF64(unsigned int value)
{
	unsigned long long bits = ((unsigned long long)0x43300000 << 32) | (unsigned long long)(value ^ 0x80000000);
	return (double)bits - DOUBLE_80332fe0;
}

/*
 * --INFO--
 * PAL Address: 0x80160c34
 * PAL Size: 680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiInit()
{
	short sVar1;
	float fVar2;
	float fVar3;
	float fVar4;
	int iVar5;
	short sVar6;
	short sVar7;
	short* psVar8;
	int iVar9;
	int iVar10;
	int iVar11;

	memset(*(void**)((char*)this + 0x850), 0, 0x1008);
	fVar2 = FLOAT_80332fac;
	iVar5 = *(int*)((char*)this + 0x850) + 8;
	iVar10 = 8;
	do {
		*(float*)(iVar5 + 0x14) = fVar2;
		*(float*)(iVar5 + 0x54) = fVar2;
		*(float*)(iVar5 + 0x94) = fVar2;
		*(float*)(iVar5 + 0xd4) = fVar2;
		*(float*)(iVar5 + 0x114) = fVar2;
		*(float*)(iVar5 + 0x154) = fVar2;
		*(float*)(iVar5 + 0x194) = fVar2;
		*(float*)(iVar5 + 0x1d4) = fVar2;
		iVar5 = iVar5 + 0x200;
		iVar10 = iVar10 - 1;
	} while (iVar10 != 0);

	iVar5 = *(int*)((char*)this + 0x850);
	*(int*)(iVar5 + 0x24) = 0x2e;
	*(short*)(iVar5 + 8) = 0x68;
	*(short*)(iVar5 + 10) = 0x28;
	*(short*)(iVar5 + 0xc) = 0x78;
	fVar2 = FLOAT_80332fe8;
	*(short*)(iVar5 + 0xe) = 0x108;
	fVar4 = FLOAT_80332fec;
	*(float*)(iVar5 + 0x10) = fVar2;
	fVar3 = FLOAT_80332fac;
	*(float*)(iVar5 + 0x14) = fVar4;
	fVar2 = FLOAT_80332fa8;
	sVar6 = 0;
	*(float*)(iVar5 + 0x1c) = fVar3;
	fVar4 = FLOAT_80332ff0;
	sVar7 = 4;
	*(int*)(iVar5 + 0x2c) = 5;
	*(int*)(iVar5 + 0x30) = 5;
	iVar5 = 0x100;
	iVar10 = *(int*)((char*)this + 0x850);
	*(int*)(iVar10 + 100) = 0x44;
	*(short*)(iVar10 + 0x48) = 0x50;
	*(short*)(iVar10 + 0x4a) = 0xe;
	*(short*)(iVar10 + 0x4c) = 0x30;
	*(short*)(iVar10 + 0x4e) = 0x30;
	*(float*)(iVar10 + 0x50) = fVar2;
	*(float*)(iVar10 + 0x54) = fVar2;
	*(float*)(iVar10 + 0x5c) = fVar3;
	*(int*)(iVar10 + 0x6c) = 0;
	*(int*)(iVar10 + 0x70) = 5;

	iVar10 = *(int*)((char*)this + 0x850);
	*(int*)(iVar10 + 0xa4) = 0x44;
	*(short*)(iVar10 + 0x88) = 0x55;
	*(short*)(iVar10 + 0x8c) = 0x30;
	*(short*)(iVar10 + 0x8e) = 0x30;
	*(short*)(iVar10 + 0x8a) = 0x150 - *(short*)(iVar10 + 0x8e);
	*(float*)(iVar10 + 0x90) = fVar2;
	*(float*)(iVar10 + 0x94) = fVar2;
	*(float*)(iVar10 + 0x9c) = fVar4;
	*(int*)(iVar10 + 0xac) = 0;
	*(int*)(iVar10 + 0xb0) = 5;

	iVar10 = *(int*)((char*)this + 0x850);
	*(int*)(iVar10 + 0xf4) = 2;
	*(int*)(iVar10 + 0xe4) = 0x2e;
	*(short*)(iVar10 + 200) = 0x50;
	*(short*)(iVar10 + 0xca) = 8;
	*(short*)(iVar10 + 0xcc) = 0x48;
	*(short*)(iVar10 + 0xce) = 0x140;
	*(float*)(iVar10 + 0xd0) = fVar2;
	*(float*)(iVar10 + 0xd4) = fVar2;
	*(int*)(iVar10 + 0xec) = 0;
	*(int*)(iVar10 + 0xf0) = 5;

	iVar10 = *(int*)((char*)this + 0x850);
	iVar11 = 4;
	do {
		psVar8 = (short*)(*(int*)((char*)this + 0x850) + iVar5 + 8);
		psVar8[0x16] = 0;
		psVar8[0x17] = 2;
		psVar8[0xe] = 0;
		psVar8[0xf] = 0x37;
		sVar7 = sVar7 + 2;
		*psVar8 = *(short*)(iVar10 + 8) + 0x24;
		sVar1 = sVar6 + 0x20;
		psVar8[1] = *(short*)(iVar10 + 10) + sVar6;
		psVar8[2] = 200;
		psVar8[3] = 0x28;
		*(float*)(psVar8 + 4) = fVar2;
		*(float*)(psVar8 + 6) = fVar2;
		psVar8[0x12] = 0;
		psVar8[0x13] = 7;
		psVar8[0x14] = 0;
		psVar8[0x15] = 5;
		iVar9 = iVar5 + 0x48;
		iVar5 = iVar5 + 0x80;
		psVar8 = (short*)(*(int*)((char*)this + 0x850) + iVar9);
		psVar8[0x16] = 0;
		psVar8[0x17] = 2;
		psVar8[0xe] = 0;
		psVar8[0xf] = 0x37;
		*psVar8 = *(short*)(iVar10 + 8) + 0x24;
		sVar6 = sVar6 + 0x40;
		psVar8[1] = *(short*)(iVar10 + 10) + sVar1;
		psVar8[2] = 200;
		psVar8[3] = 0x28;
		*(float*)(psVar8 + 4) = fVar2;
		*(float*)(psVar8 + 6) = fVar2;
		psVar8[0x12] = 0;
		psVar8[0x13] = 7;
		psVar8[0x14] = 0;
		psVar8[0x15] = 5;
		iVar11 = iVar11 - 1;
	} while (iVar11 != 0);

	**(short**)((char*)this + 0x850) = sVar7;
	*(short*)(*(int*)((char*)this + 0x82c) + 0x26) = 0;
	*(char*)(*(int*)((char*)this + 0x82c) + 0xb) = 1;
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
	float fVar1;
	int iVar2;
	short* psVar3;
	unsigned int uVar4;
	unsigned int uVar5;

	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0x24) = 0x2e;
	*(int*)(iVar2 + 0x2c) = 2;
	*(int*)(iVar2 + 0x30) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 100) = 0x44;
	*(int*)(iVar2 + 0x6c) = 7;
	*(int*)(iVar2 + 0x70) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0xa4) = 0x44;
	*(int*)(iVar2 + 0xac) = 7;
	*(int*)(iVar2 + 0xb0) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0xf4) = 2;
	*(int*)(iVar2 + 0xe4) = 0x2e;
	*(int*)(iVar2 + 0xec) = 7;
	*(int*)(iVar2 + 0xf0) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0x134) = 2;
	*(int*)(iVar2 + 0x124) = 0x37;
	*(int*)(iVar2 + 300) = 0;
	*(int*)(iVar2 + 0x130) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0x174) = 2;
	*(int*)(iVar2 + 0x164) = 0x37;
	*(int*)(iVar2 + 0x16c) = 0;
	*(int*)(iVar2 + 0x170) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0x1b4) = 2;
	*(int*)(iVar2 + 0x1a4) = 0x37;
	*(int*)(iVar2 + 0x1ac) = 0;
	*(int*)(iVar2 + 0x1b0) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 500) = 2;
	*(int*)(iVar2 + 0x1e4) = 0x37;
	fVar1 = FLOAT_80332fac;
	*(int*)(iVar2 + 0x1ec) = 0;
	*(int*)(iVar2 + 0x1f0) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0x234) = 2;
	*(int*)(iVar2 + 0x224) = 0x37;
	*(int*)(iVar2 + 0x22c) = 0;
	*(int*)(iVar2 + 0x230) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0x274) = 2;
	*(int*)(iVar2 + 0x264) = 0x37;
	*(int*)(iVar2 + 0x26c) = 0;
	*(int*)(iVar2 + 0x270) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0x2b4) = 2;
	*(int*)(iVar2 + 0x2a4) = 0x37;
	*(int*)(iVar2 + 0x2ac) = 0;
	*(int*)(iVar2 + 0x2b0) = 5;
	iVar2 = *(int*)((char*)this + 0x850);
	*(int*)(iVar2 + 0x2f4) = 2;
	*(int*)(iVar2 + 0x2e4) = 0x37;
	*(int*)(iVar2 + 0x2ec) = 0;
	*(int*)(iVar2 + 0x2f0) = 5;

	uVar4 = (unsigned int)**(short**)((char*)this + 0x850);
	psVar3 = *(short**)((char*)this + 0x850) + 4;
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
	s16* artiState = *(s16**)((u8*)this + 0x82C);
	s16* artiList = *(s16**)((u8*)this + 0x850);
	int finished = 0;
	int count = artiList[0];
	ArtiOpenAnim* anim = (ArtiOpenAnim*)((u8*)artiList + 8);
	int frame = artiState[0x11];

	if (*(u8*)(artiState + 5) == 0) {
		ArtiInit();
	}

	artiState[0x11]++;
	frame = artiState[0x11];

	for (int i = 0; i < count; i++, anim++) {
		if (anim->startFrame <= frame) {
			if (frame < anim->startFrame + anim->duration) {
				anim->step++;
				anim->alpha = (float)anim->step / (float)anim->duration;
				if ((anim->flags & 2) == 0) {
					float t = (float)anim->step / (float)anim->duration;
					anim->dx = (anim->targetX - (float)anim->x) * t;
					anim->dy = (anim->targetY - (float)anim->y) * t;
				}
			} else {
				finished++;
				anim->alpha = 1.0f;
				anim->dx = 0.0f;
				anim->dy = 0.0f;
			}
		}
	}

	return (unsigned int)(count == finished);
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
	s16* artiState = *(s16**)((u8*)this + 0x82C);
	s16* artiList = *(s16**)((u8*)this + 0x850);
	int finished = 0;
	int count = artiList[0];
	ArtiOpenAnim* anim = (ArtiOpenAnim*)((u8*)artiList + 8);
	int frame;

	artiState[0x11]++;
	frame = artiState[0x11];

	for (int i = 0; i < count; i++, anim++) {
		if (anim->startFrame <= frame) {
			if (frame < anim->startFrame + anim->duration) {
				anim->step++;
				anim->alpha = 1.0f - ((float)anim->step / (float)anim->duration);
				if ((anim->flags & 2) == 0) {
					float t = 1.0f - ((float)anim->step / (float)anim->duration);
					anim->dx = (anim->targetX - (float)anim->x) * t;
					anim->dy = (anim->targetY - (float)anim->y) * t;
				}
			} else {
				finished++;
				anim->alpha = 0.0f;
				anim->dx = 0.0f;
				anim->dy = 0.0f;
			}
		}
	}

	return (unsigned int)(count == finished);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiDraw()
{
	bool hasSelectedArtifact = false;
	int selectedArtifactId = -1;
	u32 scriptFood = Game.game.m_scriptFoodBase[0];

	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	short state = *(short*)(*(int*)((char*)this + 0x82c) + 0x10);
	short* entry = (short*)(*(int*)((char*)this + 0x850) + 8);
	int count = **(short**)((char*)this + 0x850);
	int drawIndex = 0;

	for (int i = 0; i < count; i++) {
		int tex = *(int*)(entry + 0xe);
		if (tex >= 0) {
			float x = (float)entry[0];
			float y = (float)entry[1];
			float w = (float)entry[2];
			float h = (float)entry[3];
			float u = *(float*)(entry + 4);
			float v = *(float*)(entry + 6);
			float alpha = *(float*)(entry + 8);
			float uvScale = *(float*)(entry + 10);

			if (i == 0) {
				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 1);
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);

				GXColor colors[4] = {
					{0xFF, 0xFF, 0xFF, 0xFF},
					{0xFF, 0xFF, 0xFF, 0xFF},
					{0xFF, 0xFF, 0xFF, 0xFF},
					{0xFF, 0xFF, 0xFF, 0xFF},
				};
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);

				float fillW = alpha * w;
				if (fillW > 0.0f) {
					DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
						this, 0, x, y, fillW, h, u, v, colors, 1.0f, 1.0f, 0.0f);
					x += fillW;
					u += fillW;
				}

				if (fillW > 0.0f && fillW < w) {
					GXColor fadeColors[4] = {
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
					};
					float remainW = (48.0f / (float)*(int*)(entry + 0x14)) * w;
					DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
						this, 0, x, y, remainW, h, u, v, fadeColors, 1.0f, 1.0f, 0.0f);
				}

				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
			} else {
				float itemAlpha = alpha;
				if (tex == 0x37) {
					short itemCount = *(short*)(scriptFood + (drawIndex + *(short*)(*(int*)((char*)this + 0x82c) + 0x34)) * 2 + 0x136);
					if (itemCount < 1) {
						tex = 0x34;
						itemAlpha *= 0.5f;
					}

					if (tex == 0x37 && drawIndex == *(short*)(*(int*)((char*)this + 0x82c) + 0x26)) {
						v += h;
					}
					drawIndex++;
				}

				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
				GXColor color = {0xFF, 0xFF, 0xFF, (u8)(255.0f * itemAlpha)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				DrawRect__8CMenuPcsFUlfffffffff(this, 0, x, y, w, h, u, v, uvScale, uvScale, 0.0f);
			}
		}
		entry += 0x20;
	}

	CFont* listFont = *(CFont**)((char*)this + 0x108);
	SetMargin__5CFontFf(0.0f, listFont);
	SetShadow__5CFontFi(listFont, 0);
	SetScale__5CFontFf(0.875f, listFont);
	DrawInit__5CFontFv(listFont);

	short* listStart = (short*)(*(int*)((char*)this + 0x850) + 8);
	int listCount = **(short**)((char*)this + 0x850);
	for (int i = 0; i < listCount; i++) {
		if (*(int*)(listStart + 0xe) == 0x37) {
			break;
		}
		listStart += 0x20;
	}

	const ArtiFlatData* flatData = reinterpret_cast<const ArtiFlatData*>(&Game.game.m_cFlatDataArr[1]);
	for (int i = 0; i < 8; i++) {
		u8 alpha = (u8)(255.0f * *(float*)(listStart + 8));
		GXColor color = {0xFF, 0xFF, 0xFF, alpha};
		SetColor__5CFontF8_GXColor(listFont, &color);

		int menuIndex = i + *(short*)(*(int*)((char*)this + 0x82c) + 0x34);
		short itemCount = *(short*)(scriptFood + menuIndex * 2 + 0x136);
		const char* text;
		if (itemCount < 1) {
			text = GetMenuStr__8CMenuPcsFi(this, 0x14);
		} else {
			text = flatData->table[0].strings[itemCount * 5 + 4];
			if (menuIndex == (int)*(short*)(*(int*)((char*)this + 0x82c) + 0x26) + (int)*(short*)(*(int*)((char*)this + 0x82c) + 0x34)) {
				hasSelectedArtifact = true;
				selectedArtifactId = itemCount;
			}
		}

		GetWidth__5CFontFPc(listFont, text);
		SetPosX__5CFontFf((float)(listStart[0] + 0x1c), listFont);
		SetPosY__5CFontFf((float)(listStart[1] + 0xb) - 5.0f, listFont);
		Draw__5CFontFPc(listFont, text);
		listStart += 0x20;
	}

	DrawInit__8CMenuPcsFv(this);

	listStart = (short*)(*(int*)((char*)this + 0x850) + 8);
	listCount = **(short**)((char*)this + 0x850);
	for (int i = 0; i < listCount; i++) {
		if (*(int*)(listStart + 0xe) == 0x37) {
			break;
		}
		listStart += 0x20;
	}

	for (int i = 0; i < 8; i++) {
		short itemCount = *(short*)(scriptFood + (i + *(short*)(*(int*)((char*)this + 0x82c) + 0x34)) * 2 + 0x136);
		if (itemCount > 0) {
			int iconY = (int)((float)listStart[1] + 6.0f - 1.0f);
			int iconX = (int)((float)(listStart[0] + listStart[2] - 0x10));
			DrawSingleIcon__8CMenuPcsFiiifif(this, itemCount, iconX, iconY, *(float*)(listStart + 8), 0, 0.0f);
		}
		listStart += 0x20;
	}

	if (state == 1) {
		int menuData = *(int*)((char*)this + 0x850);
		float mark = CalcListPos__8CMenuPcsFiii(this, *(short*)(*(int*)((char*)this + 0x82c) + 0x34), 0x49, 0);
		if (mark > 0.0f) {
			DrawListPosMark__8CMenuPcsFfff(this, (float)*(short*)(menuData + 8), (float)*(short*)(menuData + 10), mark);
		}
	}

	if (state == 1) {
		short* cursorBase = (short*)(*(int*)((char*)this + 0x850) + 8);
		int cursorCount = **(short**)((char*)this + 0x850);
		for (int i = 0; i < cursorCount; i++) {
			if (*(int*)(cursorBase + 0xe) == 0x37) {
				break;
			}
			cursorBase += 0x20;
		}

		cursorBase += *(short*)(*(int*)((char*)this + 0x82c) + 0x26) * 0x20;
		int cursorY = (int)(((float)(cursorBase[3] - 0x20) * 0.5f) + (float)cursorBase[1]);
		int cursorX = (int)((float)(cursorBase[0] - 0x14) + (float)(System.m_frameCounter & 7));
		DrawCursor__8CMenuPcsFiif(this, cursorX, cursorY, 1.0f);
	}

	CFont* helpFont = *(CFont**)((char*)this + 0xf8);
	u8 helpAlpha = (u8)(FLOAT_80332fc0 * *(float*)(*(int*)((char*)this + 0x850) + 0x18));
	if (!hasSelectedArtifact) {
		selectedArtifactId = -1;
	}

	if (selectedArtifactId == -1) {
		const char* text = GetMenuStr__8CMenuPcsFi(this, 0x14);
		GXColor color = {0xFF, 0xFF, 0xFF, helpAlpha};
		SetColor__5CFontF8_GXColor(helpFont, &color);
		SetPosX__5CFontFf(0.0f, helpFont);
		SetPosY__5CFontFf(FLOAT_80332fcc, helpFont);
		Draw__5CFontFPc(helpFont, text);
	} else {
		GXColor helpColor = {0xFF, 0xFF, 0xFF, helpAlpha};
		DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(this, selectedArtifactId, helpFont, 0, -20, helpColor, 0, 1.0f, 0.0f);
	}
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
