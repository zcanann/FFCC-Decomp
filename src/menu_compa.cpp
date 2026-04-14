#include "ffcc/menu_compa.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>

typedef signed short s16;
typedef unsigned char u8;

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(CMenuPcs*, unsigned long, float, float, float, float, float, float, GXColor*, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern CMenuPcs MenuPcs;

extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* GetJobStr__8CMenuPcsFi(CMenuPcs*, int);

extern float FLOAT_80333000;
extern float FLOAT_80332ff8;
extern double DOUBLE_80333008;
extern double DOUBLE_80333030;

struct CompaOpenAnim {
	s16 x;
	s16 y;
	s16 w;
	s16 h;
	float u;
	float v;
	float alpha;
	float uvScale;
	int drawFlags;
	int tex;
	int frame;
	int startFrame;
	int duration;
	unsigned int flags;
	float dx;
	float dy;
	float targetX;
	float targetY;
};

struct CompaOpenAnimList
{
	s16 count;
	s16 pad_02;
	int pad_04;
	CompaOpenAnim entries[64];
};

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
	short* compaList = this->compaList;
	int compaState = (int)this->compaMenuState;

	memset(compaList, 0, 0x1008);
	fVar1 = 1.0f;
	iVar4 = (int)compaList + 8;
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

	iVar4 = (int)compaList;
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

	iVar4 = (int)compaList;
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

	iVar4 = (int)compaList;
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

	iVar4 = (int)compaList;
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
	iVar4 = (int)compaList;
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

	iVar4 = (int)compaList;
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

	*compaList = 6;
	*reinterpret_cast<short*>(compaState + 0x26) = 0;
	*reinterpret_cast<char*>(compaState + 0xB) = 1;
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
    float fVar1;
    double dVar2;
    double dVar3;
    short* psVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar8;

    if (*(char*)((int)this->compaMenuState + 0xB) == '\0') {
        CompaInit();
    }

    iVar5 = 0;
    *(short*)((int)this->compaMenuState + 0x22) = *(short*)((int)this->compaMenuState + 0x22) + 1;
    iVar6 = (int)*this->compaList;
    psVar4 = this->compaList + 4;
    iVar7 = (int)*(short*)((int)this->compaMenuState + 0x22);
    iVar8 = iVar6;
    if (0 < iVar6) {
        do {
            dVar3 = DOUBLE_80333030;
            fVar1 = FLOAT_80332ff8;
            if (*(int*)(psVar4 + 0x12) <= iVar7) {
                if (iVar7 < *(int*)(psVar4 + 0x12) + *(int*)(psVar4 + 0x14)) {
                    *(int*)(psVar4 + 0x10) = *(int*)(psVar4 + 0x10) + 1;
                    dVar2 = DOUBLE_80333008;
                    *(float*)(psVar4 + 8) =
                        (float)((DOUBLE_80333008 / (double)*(int*)(psVar4 + 0x14)) * (double)*(int*)(psVar4 + 0x10));
                    if ((*(unsigned int*)(psVar4 + 0x16) & 2) == 0) {
                        fVar1 =
                            (float)((dVar2 / (double)*(int*)(psVar4 + 0x14)) * (double)*(int*)(psVar4 + 0x10));
                        *(float*)(psVar4 + 0x18) =
                            (*(float*)(psVar4 + 0x1C) - (float)*psVar4) * fVar1;
                        *(float*)(psVar4 + 0x1A) =
                            (*(float*)(psVar4 + 0x1E) - (float)psVar4[1]) * fVar1;
                    }
                } else {
                    iVar5 = iVar5 + 1;
                    *(float*)(psVar4 + 8) = FLOAT_80333000;
                    *(float*)(psVar4 + 0x18) = fVar1;
                    *(float*)(psVar4 + 0x1A) = fVar1;
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
	short hold;
	bool doReset = false;
	CompaMenuState* compaState = this->compaMenuState;
	CompaOpenAnimList* compaList = reinterpret_cast<CompaOpenAnimList*>(this->compaList);

	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		press = 0;
	} else {
		press = Pad._8_2_;
	}

	activeInput = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		hold = 0;
	} else {
		hold = *reinterpret_cast<short*>(reinterpret_cast<char*>(&Pad) + 0x20);
	}

	if (hold == 0) {
		doReset = false;
	} else if ((press & 0x20) != 0) {
		compaState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = true;
	} else if ((press & 0x40) != 0) {
		compaState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = true;
	} else if ((press & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
		doReset = false;
	} else if ((press & 0x200) != 0) {
		compaState->closeRequested = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		doReset = true;
	} else {
		doReset = false;
	}

	if (doReset) {
		compaList->entries[0].startFrame = 2;
		compaList->entries[0].duration = 5;
		compaList->entries[1].startFrame = 2;
		compaList->entries[1].duration = 5;
		compaList->entries[2].startFrame = 2;
		compaList->entries[2].duration = 5;
		compaList->entries[3].startFrame = 7;
		compaList->entries[3].duration = 5;
		compaList->entries[4].startFrame = 7;
		compaList->entries[4].duration = 5;
		compaList->entries[5].flags = 2;
		compaList->entries[5].startFrame = 7;
		compaList->entries[5].duration = 5;

		unsigned int entryCount = static_cast<unsigned short>(compaList->count);
		CompaOpenAnim* entry = compaList->entries;
		while (entryCount != 0) {
			entry->frame = 0;
			entry->alpha = 1.0f;
			entry++;
			entryCount--;
		}
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
bool CMenuPcs::CompaClose()
{
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    short* psVar4;

    iVar5 = 0;
    *(short*)((int)this->compaMenuState + 0x22) = *(short*)((int)this->compaMenuState + 0x22) + 1;
    iVar6 = (int)*this->compaList;
    psVar4 = this->compaList + 4;
    iVar7 = (int)*(short*)((int)this->compaMenuState + 0x22);
    iVar8 = iVar6;
    if (0 < iVar6) {
        do {
            double dVar3 = DOUBLE_80333030;
            float fVar1 = FLOAT_80332ff8;
            if (*(int*)(psVar4 + 0x12) <= iVar7) {
                if (iVar7 < *(int*)(psVar4 + 0x12) + *(int*)(psVar4 + 0x14)) {
                    double dVar2 = DOUBLE_80333008;
                    *(int*)(psVar4 + 0x10) = *(int*)(psVar4 + 0x10) + 1;
                    *(float*)(psVar4 + 8) =
                        (float)-((DOUBLE_80333008 / (double)*(int*)(psVar4 + 0x14)) * (double)*(int*)(psVar4 + 0x10) -
                                 DOUBLE_80333008);
                    if ((*(unsigned int*)(psVar4 + 0x16) & 2) == 0) {
                        fVar1 =
                            (float)-((dVar2 / (double)*(int*)(psVar4 + 0x14)) * (double)*(int*)(psVar4 + 0x10) - dVar2);
                        *(float*)(psVar4 + 0x18) =
                            (*(float*)(psVar4 + 0x1C) - (float)*psVar4) * fVar1;
                        *(float*)(psVar4 + 0x1A) =
                            (*(float*)(psVar4 + 0x1E) - (float)psVar4[1]) * fVar1;
                    }
                } else {
                    iVar5 = iVar5 + 1;
                    *(float*)(psVar4 + 8) = FLOAT_80332ff8;
                    *(float*)(psVar4 + 0x18) = fVar1;
                    *(float*)(psVar4 + 0x1A) = fVar1;
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
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);

	int scriptFood = Game.m_scriptFoodBase[0];
	short* compaList = this->compaList;
	short* entry = reinterpret_cast<short*>((int)compaList + 8);
	int count = *compaList;
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
				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 1);
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);

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
								&MenuPcs, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, yStep, fillW, tileH, u, v,
								colors, uvScale, 1.0f, 0.0f);
							yStep += 24.0f;
						}
					} else {
						DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
							&MenuPcs, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, y, fillW, h, u, v,
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
								&MenuPcs, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, yStep, remainW, tileH, u, v,
								fadeColors, uvScale, 1.0f, 0.0f);
							yStep += 24.0f;
						}
					} else {
						DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
							&MenuPcs, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, y, remainW, h, u, v,
							fadeColors, uvScale, 1.0f, 0.0f);
					}
				}

				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);
			} else {
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);
				GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha * 255.0f)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, x, y, w, h, u, v, uvScale, uvScale, 0.0f);
			}
		}

		entry += 0x20;
	}

	int menuData = (int)compaList;
	float globalAlpha = *reinterpret_cast<float*>(menuData + 0x18);

	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(globalAlpha * 255.0f)};
	GXSetChanMatColor(GX_COLOR0A0, color);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x3A);

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
			&MenuPcs, 0,
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

	CFont* font = listFont;
	font->SetMargin(0.0f);
	font->SetShadow(0);
	font->SetScaleX(0.875f);
	font->SetScaleY(1.0f);
	font->DrawInit();

	GXColor textColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * globalAlpha)};
	font->SetColor(textColor);

	const CompaFlatData* flatData = reinterpret_cast<const CompaFlatData*>(&Game.m_cFlatDataArr[1]);
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
		font->SetPosX(static_cast<float>(*reinterpret_cast<short*>(menuData + 8) + 0x18));
		font->SetPosY(y);
		font->Draw(name);

		short food = *reinterpret_cast<short*>(scriptFood + 0x9CA + drawIndex * 2);
		if (food >= 0) {
			const char* value = flatData->table[2].strings[food];
			font->SetPosX(static_cast<float>(*reinterpret_cast<short*>(menuData + 8) + 0x90));
			font->SetPosY(y);
			font->Draw(value);
		}

		shown++;
		memberIndex = drawIndex + 1;
	}

	font = listFont;
	font->SetMargin(0.0f);
	font->SetShadow(0);
	font->SetScale(0.75f);
	font->DrawInit();
	font->SetColor(textColor);

	const char* job = GetJobStr__8CMenuPcsFi(this, *reinterpret_cast<int*>(scriptFood + 0x3AC));
	font->GetWidth(job);
	font->SetPosX(static_cast<float>(*reinterpret_cast<short*>(menuData + 8) + 0x18));
	font->SetPosY(static_cast<float>(*reinterpret_cast<short*>(menuData + 0xA) + 0x20) - 18.0f);
	font->Draw(job);

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
