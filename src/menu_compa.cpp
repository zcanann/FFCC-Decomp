#include "ffcc/menu_compa.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(CMenuPcs*, unsigned long, float, float, float, float, float, float, GXColor*, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);

extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScaleX__5CFontFf(float, CFont*);
extern "C" void SetScaleY__5CFontFf(float, CFont*);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" int GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);
extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* GetJobStr__8CMenuPcsFi(CMenuPcs*, int);

struct CompaFlatTableEntry
{
	int count;
	const char** strings;
	char* stringBuf;
};

struct CompaFlatData
{
	char pad0[0x6C];
	CompaFlatTableEntry table[8];
};

/*
 * --INFO--
 * PAL Address: 801620f8
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaInit()
{
	float fVar1;
	float fVar2;
	float fVar3;
	int iVar4;
	int iVar5;

	memset(*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x850), 0, 0x1008);
	fVar1 = 1.0f;
	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850) + 8;
	iVar5 = 8;
	do {
		*reinterpret_cast<float*>(iVar4 + 0x14) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x54) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x94) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0xd4) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x114) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x154) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x194) = fVar1;
		*reinterpret_cast<float*>(iVar4 + 0x1d4) = fVar1;
		iVar4 += 0x200;
		iVar5 += -1;
	} while (iVar5 != 0);

	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(iVar4 + 0x24) = 0x52;
	*reinterpret_cast<int*>(iVar4 + 0x20) = 4;
	*reinterpret_cast<short*>(iVar4 + 8) = 0x28;
	*reinterpret_cast<short*>(iVar4 + 10) = 0x30;
	fVar1 = 0.0f;
	*reinterpret_cast<short*>(iVar4 + 0xc) = 0x198;
	fVar2 = 1.0f;
	*reinterpret_cast<short*>(iVar4 + 0xe) = 0x18;
	*reinterpret_cast<float*>(iVar4 + 0x10) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x14) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x1c) = fVar2;
	*reinterpret_cast<int*>(iVar4 + 0x2c) = 5;
	*reinterpret_cast<int*>(iVar4 + 0x30) = 5;

	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(iVar4 + 100) = 0x51;
	*reinterpret_cast<short*>(iVar4 + 0x48) = 0x28;
	*reinterpret_cast<short*>(iVar4 + 0x4a) = 0x48;
	*reinterpret_cast<short*>(iVar4 + 0x4c) = 0x198;
	*reinterpret_cast<short*>(iVar4 + 0x4e) = 200;
	*reinterpret_cast<float*>(iVar4 + 0x50) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x54) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x5c) = fVar2;
	*reinterpret_cast<int*>(iVar4 + 0x6c) = 5;
	*reinterpret_cast<int*>(iVar4 + 0x70) = 5;

	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(iVar4 + 0xa4) = 0x52;
	*reinterpret_cast<short*>(iVar4 + 0x88) = 0x28;
	*reinterpret_cast<short*>(iVar4 + 0x8a) = 0x110;
	*reinterpret_cast<short*>(iVar4 + 0x8c) = 0x198;
	*reinterpret_cast<short*>(iVar4 + 0x8e) = 0x18;
	*reinterpret_cast<float*>(iVar4 + 0x90) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x94) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x9c) = fVar2;
	*reinterpret_cast<int*>(iVar4 + 0xac) = 5;
	*reinterpret_cast<int*>(iVar4 + 0xb0) = 5;

	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(iVar4 + 0xe4) = 0x5e;
	*reinterpret_cast<short*>(iVar4 + 200) = 0x10;
	*reinterpret_cast<short*>(iVar4 + 0xca) = 0xe;
	*reinterpret_cast<short*>(iVar4 + 0xcc) = 0x30;
	*reinterpret_cast<short*>(iVar4 + 0xce) = 0x30;
	*reinterpret_cast<float*>(iVar4 + 0xd0) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0xd4) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0xdc) = fVar2;
	*reinterpret_cast<int*>(iVar4 + 0xec) = 0;
	*reinterpret_cast<int*>(iVar4 + 0xf0) = 5;

	fVar3 = 6.0f;
	fVar2 = -13.0f;
	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(iVar4 + 0x124) = 0x5e;
	*reinterpret_cast<short*>(iVar4 + 0x108) = 0x15;
	*reinterpret_cast<short*>(iVar4 + 0x10c) = 0x30;
	*reinterpret_cast<short*>(iVar4 + 0x10e) = 0x30;
	*reinterpret_cast<short*>(iVar4 + 0x10a) = static_cast<short>(0x150 - *reinterpret_cast<short*>(iVar4 + 0x10e));
	*reinterpret_cast<float*>(iVar4 + 0x110) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x114) = fVar1;
	*reinterpret_cast<float*>(iVar4 + 0x11c) = fVar2;
	*reinterpret_cast<int*>(iVar4 + 300) = 0;
	*reinterpret_cast<int*>(iVar4 + 0x130) = 5;

	iVar4 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(iVar4 + 0x174) = 2;
	*reinterpret_cast<int*>(iVar4 + 0x164) = 0x2e;
	*reinterpret_cast<short*>(iVar4 + 0x148) = 0x10;
	*reinterpret_cast<short*>(iVar4 + 0x14a) = 8;
	*reinterpret_cast<short*>(iVar4 + 0x14c) = 0x30;
	*reinterpret_cast<short*>(iVar4 + 0x14e) = 0x140;
	*reinterpret_cast<float*>(iVar4 + 0x150) = fVar3;
	*reinterpret_cast<float*>(iVar4 + 0x154) = fVar1;
	*reinterpret_cast<int*>(iVar4 + 0x16c) = 0;
	*reinterpret_cast<int*>(iVar4 + 0x170) = 5;

	**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) = 6;
	*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0x26) = 0;
	*reinterpret_cast<char*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0xb) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CompaInit0()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80161f48
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::CompaOpen()
{
	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
	if (*reinterpret_cast<char*>(menuState + 0xb) == 0) {
		CompaInit();
	}

	*reinterpret_cast<short*>(menuState + 0x22) = static_cast<short>(*reinterpret_cast<short*>(menuState + 0x22) + 1);
	int time = static_cast<int>(*reinterpret_cast<short*>(menuState + 0x22));

	int entryCount = static_cast<int>(**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850));
	short* entry = *reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	int completeCount = 0;
	for (int i = 0; i < entryCount; ++i) {
		if (*reinterpret_cast<int*>(entry + 0x12) <= time) {
			int duration = *reinterpret_cast<int*>(entry + 0x14);
			if (time < *reinterpret_cast<int*>(entry + 0x12) + duration) {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				float t = static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) / static_cast<float>(duration);
				*reinterpret_cast<float*>(entry + 8) = t;

				if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
					*reinterpret_cast<float*>(entry + 0x18) =
						(*reinterpret_cast<float*>(entry + 0x1c) - static_cast<float>(*entry)) * t;
					*reinterpret_cast<float*>(entry + 0x1a) =
						(*reinterpret_cast<float*>(entry + 0x1e) - static_cast<float>(entry[1])) * t;
				}
			} else {
				completeCount = completeCount + 1;
				*reinterpret_cast<float*>(entry + 8) = 1.0f;
				*reinterpret_cast<float*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<float*>(entry + 0x1a) = 0.0f;
			}
		}

		entry += 0x20;
	}
	return entryCount == completeCount;
}

/*
 * --INFO--
 * PAL Address: 80161c28
 * PAL Size: 800b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaCtrl()
{
	bool activeInput = false;
	unsigned short press;
	unsigned short hold;
	bool doReset = false;

	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		press = 0;
	} else {
		press = Pad._8_2_;
	}

	if (activeInput) {
		hold = 0;
	} else {
		hold = *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(&Pad) + 0x20);
	}

	if (hold != 0) {
		if ((press & 0x20) != 0) {
			*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0x1e) = 1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			doReset = true;
		} else if ((press & 0x40) != 0) {
			*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0x1e) = -1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			doReset = true;
		} else if ((press & 0x100) != 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else if ((press & 0x200) != 0) {
			*reinterpret_cast<char*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0xd) = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			doReset = true;
		}
	}

	if (!doReset) {
		return;
	}

	int menuData = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(menuData + 0x2c) = 2;
	*reinterpret_cast<int*>(menuData + 0x30) = 5;
	*reinterpret_cast<int*>(menuData + 0x6c) = 2;
	*reinterpret_cast<int*>(menuData + 0x70) = 5;
	*reinterpret_cast<int*>(menuData + 0xac) = 2;
	*reinterpret_cast<int*>(menuData + 0xb0) = 5;
	*reinterpret_cast<int*>(menuData + 0xec) = 7;
	*reinterpret_cast<int*>(menuData + 0xf0) = 5;
	*reinterpret_cast<int*>(menuData + 300) = 7;
	*reinterpret_cast<int*>(menuData + 0x130) = 5;
	*reinterpret_cast<int*>(menuData + 0x174) = 2;
	*reinterpret_cast<int*>(menuData + 0x16c) = 7;
	*reinterpret_cast<int*>(menuData + 0x170) = 5;

	int entryCount = static_cast<int>(**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850));
	short* entry = *reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	for (int i = 0; i < entryCount; ++i) {
		*reinterpret_cast<int*>(entry + 0x10) = 0;
		*reinterpret_cast<int*>(entry + 0x12) = 0;
		*reinterpret_cast<float*>(entry + 8) = 1.0f;
		entry += 0x20;
	}
}

/*
 * --INFO--
 * PAL Address: 80161aac
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaClose()
{
	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
	short time = static_cast<short>(*reinterpret_cast<short*>(menuState + 0x22) + 1);
	*reinterpret_cast<short*>(menuState + 0x22) = time;

	short* entry = *reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850);
	int entryCount = static_cast<int>(*entry);
	short currentTime = *reinterpret_cast<short*>(menuState + 0x22);
	entry += 4;
	for (int i = 0; i < entryCount; ++i) {
		if (*reinterpret_cast<int*>(entry + 0x12) <= currentTime) {
			if (currentTime < *reinterpret_cast<int*>(entry + 0x12) + *reinterpret_cast<int*>(entry + 0x14)) {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				float fade = 1.0f - static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) /
					static_cast<float>(*reinterpret_cast<int*>(entry + 0x14));
				*reinterpret_cast<float*>(entry + 8) = fade;
				if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
					*reinterpret_cast<float*>(entry + 0x18) =
						(*reinterpret_cast<float*>(entry + 0x1c) - static_cast<float>(*entry)) * fade;
					*reinterpret_cast<float*>(entry + 0x1a) =
						(*reinterpret_cast<float*>(entry + 0x1e) - static_cast<float>(entry[1])) * fade;
				}
			} else {
				*reinterpret_cast<float*>(entry + 8) = 0.0f;
				*reinterpret_cast<float*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<float*>(entry + 0x1a) = 0.0f;
			}
		}
		entry += 0x20;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80160edc
 * PAL Size: 3024b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaDraw()
{
	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	unsigned int scriptFood = Game.game.m_scriptFoodBase[0];
	short* entry = (short*)(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850) + 8);
	int count = static_cast<int>(**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850));
	for (int i = 0; i < count; i++) {
		int tex = *reinterpret_cast<int*>(entry + 0xE);
		if (tex >= 0) {
			float x = static_cast<float>(entry[0]);
			float y = static_cast<float>(entry[1]);
			float w = static_cast<float>(entry[2]);
			float h = static_cast<float>(entry[3]);
			float u = *reinterpret_cast<float*>(entry + 4);
			float v = *reinterpret_cast<float*>(entry + 6);
			float alpha = *reinterpret_cast<float*>(entry + 8);
			float uvScale = *reinterpret_cast<float*>(entry + 10);

			if (i < 3) {
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
					if (tex == 0x51) {
						float yStep = y;
						float end = y + h;
						while (yStep < end) {
							float tileH = end - yStep;
							if (tileH > 24.0f) {
								tileH = 24.0f;
							}
							DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
								this, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, yStep, fillW, tileH, u, v,
								colors, uvScale, 1.0f, 0.0f);
							yStep += 24.0f;
						}
					} else {
						DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
							this, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, y, fillW, h, u, v,
							colors, uvScale, 1.0f, 0.0f);
					}

					x += fillW * *reinterpret_cast<float*>(entry + 10);
				}

				if (fillW > 0.0f && fillW < w) {
					GXColor fadeColors[4] = {
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
					};
					float remainW = (48.0f / static_cast<float>(*reinterpret_cast<int*>(entry + 0x14))) * w;
					if (tex == 0x51) {
						float yStep = y;
						float end = y + h;
						while (yStep < end) {
							float tileH = end - yStep;
							if (tileH > 24.0f) {
								tileH = 24.0f;
							}
							DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
								this, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, yStep, remainW, tileH, u, v,
								fadeColors, uvScale, 1.0f, 0.0f);
							yStep += 24.0f;
						}
					} else {
						DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
							this, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, y, remainW, h, u, v,
							fadeColors, uvScale, 1.0f, 0.0f);
					}
				}

				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
			} else {
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
				GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha * 255.0f)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				DrawRect__8CMenuPcsFUlfffffffff(this, 0, x, y, w, h, u, v, uvScale, uvScale, 0.0f);
			}
		}

		entry += 0x20;
	}

	int menuData = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	float globalAlpha = *reinterpret_cast<float*>(menuData + 0x18);

	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(globalAlpha * 255.0f)};
	GXSetChanMatColor(GX_COLOR0A0, color);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x3A);

	int familyCount = 2;
	for (int i = 0; i < 5; i++) {
		if (*reinterpret_cast<short*>(scriptFood + 0x9CA + i * 2) > 0) {
			familyCount++;
		}
	}
	if (familyCount > 4) {
		familyCount = 4;
	}

	for (int i = 0; i < familyCount; i++) {
		DrawRect__8CMenuPcsFUlfffffffff(
			this, 0,
			static_cast<float>(*reinterpret_cast<short*>(menuData + 8) + 0x10),
			static_cast<float>(*reinterpret_cast<short*>(menuData + 0xA) + 0x40 + i * 0x28),
			12.0f, 24.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}

	int memberIndex = 0;
	int shown = 0;
	for (int i = 0; i < 8 && shown < familyCount; i++) {
		int drawIndex = memberIndex;
		if (memberIndex > 1) {
			while (drawIndex < 8 && *reinterpret_cast<short*>(scriptFood + 0x9CA + drawIndex * 2) <= 0) {
				drawIndex++;
			}
			if (drawIndex > 7) {
				break;
			}
		}

		short food = *reinterpret_cast<short*>(scriptFood + 0x9CA + drawIndex * 2);
		int icon = 0x1D;
		if (food < 0x15) {
			icon = 0x21;
		} else if (food < 0x29) {
			icon = 0x20;
		} else if (food < 0x3D) {
			icon = 0x1F;
		} else if (food < 0x51) {
			icon = 0x1E;
		}

		DrawSingleIcon__8CMenuPcsFiiifif(
			this, icon,
			static_cast<int>(*reinterpret_cast<short*>(menuData + 8) + 0x128),
			static_cast<int>(*reinterpret_cast<short*>(menuData + 0xA) + 0x40 + shown * 0x28),
			globalAlpha, 0, 0.0f);

		shown++;
		memberIndex = drawIndex + 1;
	}

	CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<char*>(this) + 0x108);
	SetMargin__5CFontFf(0.0f, font);
	SetShadow__5CFontFi(font, 0);
	SetScaleX__5CFontFf(0.875f, font);
	SetScaleY__5CFontFf(1.0f, font);
	DrawInit__5CFontFv(font);

	GXColor textColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * globalAlpha)};
	SetColor__5CFontF8_GXColor(font, &textColor);

	const CompaFlatData* flatData = reinterpret_cast<const CompaFlatData*>(&Game.game.m_cFlatDataArr[1]);
	memberIndex = 0;
	shown = 0;
	for (int i = 0; i < 8 && shown < familyCount; i++) {
		int drawIndex = memberIndex;
		if (memberIndex > 1) {
			while (drawIndex < 8 && *reinterpret_cast<short*>(scriptFood + 0x9CA + drawIndex * 2) <= 0) {
				drawIndex++;
			}
			if (drawIndex > 7) {
				break;
			}
		}

		const char* name = GetMenuStr__8CMenuPcsFi(this, drawIndex + 0x16);
		float y = static_cast<float>(*reinterpret_cast<short*>(menuData + 0xA) + 0x45 + shown * 0x28) - 8.0f;
		SetPosX__5CFontFf(static_cast<float>(*reinterpret_cast<short*>(menuData + 8) + 0x18), font);
		SetPosY__5CFontFf(y, font);
		Draw__5CFontFPc(font, name);

		int food = *reinterpret_cast<short*>(scriptFood + 0x9CA + drawIndex * 2);
		if (food >= 0) {
			const char* value = flatData->table[2].strings[food];
			SetPosX__5CFontFf(static_cast<float>(*reinterpret_cast<short*>(menuData + 8) + 0x90), font);
			SetPosY__5CFontFf(y, font);
			Draw__5CFontFPc(font, value);
		}

		shown++;
		memberIndex = drawIndex + 1;
	}

	font = *reinterpret_cast<CFont**>(reinterpret_cast<char*>(this) + 0x108);
	SetMargin__5CFontFf(0.0f, font);
	SetShadow__5CFontFi(font, 0);
	SetScale__5CFontFf(0.75f, font);
	DrawInit__5CFontFv(font);
	SetColor__5CFontF8_GXColor(font, &textColor);

	const char* job = GetJobStr__8CMenuPcsFi(this, *reinterpret_cast<int*>(scriptFood + 0x3AC));
	GetWidth__5CFontFPc(font, job);
	SetPosX__5CFontFf(static_cast<float>(*reinterpret_cast<short*>(menuData + 8) + 0x18), font);
	SetPosY__5CFontFf(static_cast<float>(*reinterpret_cast<short*>(menuData + 0xA) + 0x20) - 18.0f, font);
	Draw__5CFontFPc(font, job);

	DrawInit__8CMenuPcsFv(this);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CompaCtrlCur()
{
	// TODO
}
